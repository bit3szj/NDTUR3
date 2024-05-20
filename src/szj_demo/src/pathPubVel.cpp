#include "pathPubVel.h"
#define SZJDEBUG 0
#define SZJDEBUG1 0
#define SZJDEBUG_CORRECT 1
PathPubVel::PathPubVel(){
    // jointState_.resize(6);
    // for(unsigned int i = 0; i < 6; ++i){
    //     jointState_[i] = 0;
    // }
    jointState_.resize(6);
    endVelCmd_.resize(6);
    correctVelCmd_.resize(6);
    for(int i =0; i < 6; ++i){
        endVelCmd_[i] = 0;
    }
    endCommand_.p.Zero();
    endCommand_.M.Identity();
    endFrame_.p.Zero();
    endFrame_.M.Identity();
    endFrame_.p.data[0] = -0.33347;
    endFrame_.p.data[1] = -0.09729;
    endFrame_.p.data[2] = 0.3;
    // endFrame_.M.RPY(3.079, 0.027, 1.636);
    endFrame_.M = KDL::Rotation::Quaternion(-0.76, -0.65, 0.01, 0.02);

    endCommand_.p = endFrame_.p;
    endCommand_.M = endFrame_.M;
}
PathPubVel::~PathPubVel(){}

int PathPubVel::init(){
    namespace_ = nh_.getNamespace();
    sub_jState = nh_.subscribe("/joint_states",1, &PathPubVel::sub_jStateCall, this);
    sub_endCommand = nh_.subscribe("/szj/endCommand",5, &PathPubVel::sub_endCommandCall, this);
    pub_endPos = nh_.advertise<geometry_msgs::Pose>("/szj/endPos",5);
    pub_ur = nh_.advertise<std_msgs::String>("ur_hardware_interface/script_command",5);
    sub_correctVel = nh_.subscribe("/szj/corVel",1000, &PathPubVel::sub_correctVelCall,this);
    ros::Duration(0.1).sleep();
    ROS_INFO("subscribe jointStates\n");
    std::cout << "name space:" << namespace_ << std::endl;
    if(!ros::param::search(namespace_,"robot_description", robotDescription_)){
        ROS_ERROR_STREAM("Kinematics_Base: No robot description (URDF)"
                "found on parameter server (" << nh_.getNamespace() <<
                "robot_description)");
        
        return -1;
    }
    ROS_INFO_STREAM("robotDescription_ : " << robotDescription_);

    if(!nh_.getParam(namespace_ + "root_name", rootName_)){
        ROS_ERROR_STREAM("Kinematics_Base: No root name found on "
                        "parameter server ("<<nh_.getNamespace()<<"root_name)");
        return -2;
    }

    if(!nh_.getParam(namespace_ + "tip_name", tipName_)){
        ROS_ERROR_STREAM("Kinematics_Base: No tip name found on "
                        "parameter server ("<<nh_.getNamespace()<<"tip_name)");
        return -3;
    }
    if (nh_.hasParam(robotDescription_))
        nh_.getParam(robotDescription_.c_str(), xmlString_);
    else
    {
        ROS_ERROR("Parameter %s not set, shutting down node...",
                    robotDescription_.c_str());
        nh_.shutdown();
        return -4;
    }

    if (xmlString_.size() == 0)
    {
        ROS_ERROR("Unable to load robot model from parameter %s",
                    robotDescription_.c_str());
        nh_.shutdown();
        return -5;
    }

    if (!model_.initString(xmlString_))
    {
        ROS_ERROR("Failed to parse urdf file");
        nh_.shutdown();
        return -6;
    }
    ROS_INFO("Successfully parsed urdf file");
    if (!kdl_parser::treeFromUrdfModel(model_, kdlTree_))
    {
        ROS_ERROR("Failed to construct kdl tree");
        nh_.shutdown();
        return -7;
    }

    if(!kdlTree_.getChain(rootName_, tipName_, kdlChain_))
    {
        ROS_ERROR_STREAM("Failed to get KDL chain from tree: ");
        ROS_ERROR_STREAM("  "<<rootName_<<" --> "<<tipName_);
        ROS_ERROR_STREAM("  Tree has "<<kdlTree_.getNrOfJoints()<<" joints");
        ROS_ERROR_STREAM("  Tree has "<<kdlTree_.getNrOfSegments()<<" segments");
        ROS_ERROR_STREAM("  The segments are:");

        KDL::SegmentMap segment_map = kdlTree_.getSegments();
        KDL::SegmentMap::iterator it;

        for( it=segment_map.begin(); it != segment_map.end(); it++ )
            ROS_ERROR_STREAM( "    "<<(*it).first);

        return -8;
    }
    ROS_INFO("tip_name:  %s",tipName_.c_str());
    ROS_INFO("root_name: %s",rootName_.c_str());
    ROS_INFO("Number of segments: %d", kdlChain_.getNrOfSegments());
    ROS_INFO("Number of joints in chain: %d", kdlChain_.getNrOfJoints());
    for(std::size_t i = 0; i < kdlChain_.getNrOfSegments(); i++){
        ROS_INFO_STREAM("segment("<<i<<"): " << kdlChain_.getSegment(i).getName());
    }

    // // Parsing joint limits from urdf model along kdl chain
    // std::shared_ptr<const urdf::Link> link_ = model_.getLink(tipName_);
    // std::shared_ptr<const urdf::Joint> joint_;
    // joint_limits_.min.resize(kdlChain_.getNrOfJoints());
    // joint_limits_.max.resize(kdlChain_.getNrOfJoints());
    // joint_limits_.center.resize(kdlChain_.getNrOfJoints());
    // int index;

    // for (std::size_t i = 0; i < kdlChain_.getNrOfJoints() && link_; i++)
    // {
    //     joint_ = model_.getJoint(link_->parent_joint->name);
    //     ROS_INFO("Getting limits for joint: %s", joint_->name.c_str());
    //     index = kdlChain_.getNrOfJoints() - i - 1;

    //     if(joint_->limits){
    //         joint_limits_.min(index) = joint_->limits->lower;
    //         joint_limits_.max(index) = joint_->limits->upper;
    //         joint_limits_.center(index) = (joint_limits_.min(index) +
    //                                     joint_limits_.max(index))/2;
    //     }else{
    //         joint_limits_.min(index) = 0;
    //         joint_limits_.max(index) = 0;
    //         joint_limits_.center(index) = 0;
    //         ROS_INFO("joint_->limits is NULL %s",joint_->name.c_str());
    //     }

    //     link_ = model_.getLink(link_->getParent()->name);
    // }
    // for(int i = 0; i < 6; ++i){
    //     ROS_INFO("the max limit of joint %d : %lf", i, joint_limits_.max.data[i]);
    //     ROS_INFO("the min limit of joint %d : %lf", i, joint_limits_.min.data[i]);
    // }

    fkSolverPos_.reset(new KDL::ChainFkSolverPos_recursive(this->kdlChain_));
    // KDL::ChainFkSolverPos
    
    return 0;
}

void PathPubVel::sub_jStateCall(sensor_msgs::JointStateConstPtr msg){
    jointState_(0) = msg->position[2];
    jointState_(1) = msg->position[1];
    jointState_(2) = msg->position[0];
    for(unsigned int i = 3; i < 6; ++i){
        jointState_(i) = msg->position[i];
    }
}

void PathPubVel::sub_endCommandCall(const geometry_msgs::PoseConstPtr msg){
    endCommand_.p.data[0] = msg->position.x; 
    endCommand_.p.data[1] = msg->position.y; 
    endCommand_.p.data[2] = msg->position.z; 
    endCommand_.M = KDL::Rotation::Quaternion(msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);
    #if SZJDEBUG1
    ROS_INFO_STREAM( "---endCommand get:---  " << endCommand_.p.x() << " # "<< endCommand_.p.y() <<" # "<< endCommand_.p.z());
    #endif
}

void PathPubVel::sub_correctVelCall(const geometry_msgs::Twist msg){
    correctVelCmd_[0] = msg.linear.x;
    correctVelCmd_[1] = msg.linear.y;
    correctVelCmd_[2] = msg.linear.z;
    correctVelCmd_[3] = msg.angular.x;
    correctVelCmd_[4] = msg.angular.y;
    correctVelCmd_[5] = msg.angular.z;
    #if SZJDEBUG_CORRECT
    ROS_INFO("recieve: %lf %lf %lf %lf %lf %lf", correctVelCmd_[0], correctVelCmd_[1], correctVelCmd_[2], correctVelCmd_[3], correctVelCmd_[4], correctVelCmd_[5]);
    #endif
}

void PathPubVel::urFk(){
    int ret = this->fkSolverPos_->JntToCart(jointState_, endFrame_);

    #ifdef SZJDEBUG
    // ROS_INFO("endFrame_ : %lf, %lf, %lf", endFrame_.p.data[0], endFrame_.p.data[1], endFrame_.p.data[2]);
    // ROS_INFO("the joint state in fk: %lf, %lf, %lf, %lf, %lf, %lf",jointState_.data[0],jointState_.data[1], jointState_.data[2], jointState_.data[3], jointState_.data[4], jointState_.data[5]);
    #endif
    if(ret < 0)
    {
        ROS_ERROR("JntToCart error");
    }
}



std::string PathPubVel::double2string(double input){
    std::string string_temp;
    std::stringstream stream;
    stream<<input;
    string_temp = stream.str();
    return string_temp;
}

void PathPubVel::limitVel(){
    for(unsigned int i = 0; i <6; ++i){
        if(abs(endVelCmd_[i]) > 0.1){
            endVelCmd_[i] = 0.1 * (endVelCmd_[i] / (abs(endVelCmd_[i])));
        }
    }
    // for(unsigned int i = 0; i < 3; ++i){
    //     if(endCommand_.p.data[i] - endFrame_.p.data[i] < 1e-3){
    //         endVelCmd_[i] = 0;
    //     }
    // }
    // for(int i = 0; i < 3; ++i){
    //     if(endCommand_.p.data[i] - endFrame_.p.data[i] < 1e-3){
    //         endVelCmd_[i] = 0;
    //     }        
    // }

}
void PathPubVel::urMove(){
    std_msgs::String ur_script_msgs;
    double time2move = 0.2;
    double acc=0.5;
    std::string move_msg;
    limitVel();
    move_msg = "speedl([";
    move_msg = move_msg + double2string(endVelCmd_[0] + correctVelCmd_[0]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[1] + correctVelCmd_[1]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[2] + correctVelCmd_[2]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[3] + correctVelCmd_[3]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[4] + correctVelCmd_[4]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[5] + correctVelCmd_[5]) + "]";
    // move_msg = move_msg + double2string(endVelCmd_[0]) + ",";
    // move_msg = move_msg + double2string(endVelCmd_[1]) + ",";
    // move_msg = move_msg + double2string(endVelCmd_[2]) + ",";
    // move_msg = move_msg + double2string(endVelCmd_[3]) + ",";
    // move_msg = move_msg + double2string(endVelCmd_[4]) + ",";
    // move_msg = move_msg + double2string(endVelCmd_[5]) + "]";
    move_msg = move_msg + ",";
    move_msg = move_msg + double2string(acc) + ",";
    move_msg = move_msg + double2string(time2move) + ")";
    move_msg = move_msg + "\n";
    ur_script_msgs.data=move_msg;
    #if SZJDEBUG1
    ROS_INFO_STREAM("---move_msg---  " << move_msg);
    #endif
    pub_ur.publish(ur_script_msgs);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "pathPubVelNode");
    PathPubVel m_PathPubVel;
    int initRet = m_PathPubVel.init();
    if(initRet == 0)
        std::cout << "init success!" << std::endl;
    ros::Rate loop_rate(125);
    while(ros::ok()){
        // #if SZJDEBUG
        // for(unsigned int i = 0; i < 6; ++i){
        //     std::cout << "jointState_["<< i << "] : " << m_PathPubVel.jointState_(i) << "; ";
        // }std::cout << std::endl;
        // #endif
        /*---compute the current end pose---*/ 
        m_PathPubVel.urFk();
        double quat[4];
        m_PathPubVel.endFrame_.M.GetQuaternion(quat[0], quat[1], quat[2], quat[3]);
        
        double rpyArr[3];
        m_PathPubVel.endFrame_.M.GetRPY(rpyArr[0], rpyArr[1], rpyArr[2]);
        m_PathPubVel.rotVec_ = m_PathPubVel.endFrame_.M.GetRot();
        #if SZJDEBUG
        ROS_INFO("quaternion : %lf, %lf, %lf, %lf", quat[0], quat[1], quat[2], quat[3]);
        // KDL::Vector rotFrame = m_PathPubVel.endFrame_.M.GetRot();
        ROS_INFO(" ");  
        ROS_INFO("------------Debug begin: rpyFrame------------");
        ROS_INFO_STREAM(rpyArr[0] << " # " << rpyArr[1] << " # "  << rpyArr[2]);
        ROS_INFO("------------Debug end: rpyFrame------------");
        ROS_INFO(" ");
        ROS_INFO("------------Debug begin: rotVec------------");
        ROS_INFO_STREAM(m_PathPubVel.rotVec_[0] << " # " << m_PathPubVel.rotVec_[1] << " # "  << m_PathPubVel.rotVec_[2]);
        ROS_INFO("------------Debug end: rotVec------------");
        ROS_INFO(" ");
        ROS_INFO("------------Debug begin: pos------------");
        ROS_INFO_STREAM(m_PathPubVel.endFrame_.p[0] << " # " << m_PathPubVel.endFrame_.p[1] << " # "  << m_PathPubVel.endFrame_.p[2]);
        ROS_INFO("------------Debug end: rotVec------------");
        #endif
        /*---publish the current end pose---*/
        geometry_msgs::Pose msgPos;
        msgPos.orientation.x = quat[0];msgPos.orientation.y = quat[1];
        msgPos.orientation.z = quat[2];msgPos.orientation.w = quat[3];
        msgPos.position.x = m_PathPubVel.endFrame_.p.x();
        msgPos.position.y = m_PathPubVel.endFrame_.p.y();
        msgPos.position.z = m_PathPubVel.endFrame_.p.z();
        m_PathPubVel.pub_endPos.publish(msgPos);

        /*---calculate the different between the command pose and the current pose*/
        //direction
        KDL::Vector cmdVec = m_PathPubVel.endCommand_.p - m_PathPubVel.endFrame_.p;
        #if SZJDEBUG
        ROS_INFO_STREAM("endCommand_.p : " << m_PathPubVel.endCommand_.p.data[0] << " # "
                        <<m_PathPubVel.endCommand_.p.data[1] << " # "
                        <<m_PathPubVel.endCommand_.p.data[2]);

        ROS_INFO_STREAM("endFrame_.p : " << m_PathPubVel.endFrame_.p.data[0] << " # "
                        <<m_PathPubVel.endFrame_.p.data[1] << " # "
                        <<m_PathPubVel.endFrame_.p.data[2]);
        #endif
        if(cmdVec.Norm() > 1e-2){
            cmdVec = 0.1 * cmdVec / cmdVec.Norm(); 
        }
        // else{
        //     cmdVec = 0 * cmdVec / cmdVec.Norm(); 
        // }
        #if SZJDEBUG
        ROS_INFO_STREAM("---cmdVec---  " << cmdVec.data[0] << " # " << cmdVec.data[1] << " # " << cmdVec.data[2]);
        #endif
        m_PathPubVel.endVelCmd_[0] = cmdVec.x();
        m_PathPubVel.endVelCmd_[1] = cmdVec.y();
        m_PathPubVel.endVelCmd_[2] = cmdVec.z();
        #if SZJDEBUG
        ROS_INFO_STREAM("---cmdVec_vecotr---  " << m_PathPubVel.endVelCmd_[0]  << " # " << m_PathPubVel.endVelCmd_[1] << " # " << m_PathPubVel.endVelCmd_[2]);
        #endif

        /*---calculate rotation vector*/

        KDL::Rotation cmdRot = m_PathPubVel.endCommand_.M * m_PathPubVel.endFrame_.M.Inverse();
        KDL::Vector cmdRotVec = cmdRot.GetRot();


        if(cmdRotVec.Norm() > 1e-2){
            cmdRotVec = 0.3 * cmdRotVec / cmdRotVec.Norm();
        }
        // else{
        //     cmdRotVec = 0 * cmdRotVec / cmdRotVec.Norm();
        // }
        m_PathPubVel.endVelCmd_[3] = cmdRotVec.x();
        m_PathPubVel.endVelCmd_[4] = cmdRotVec.y();
        m_PathPubVel.endVelCmd_[5] = cmdRotVec.z();
        #if SZJDEBUG1
        ROS_INFO("---cmdRotVec--- : %lf  %lf  %lf", cmdRotVec[0], cmdRotVec[1], cmdRotVec[2]);
        ROS_INFO("---correct--- : %lf %lf %lf %lf %lf %lf", m_PathPubVel.correctVelCmd_[0],
                m_PathPubVel.correctVelCmd_[1],m_PathPubVel.correctVelCmd_[2],m_PathPubVel.correctVelCmd_[3],
                m_PathPubVel.correctVelCmd_[4],m_PathPubVel.correctVelCmd_[5]);
        #endif
        // ROS_INFO(" ");
        m_PathPubVel.urMove();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}