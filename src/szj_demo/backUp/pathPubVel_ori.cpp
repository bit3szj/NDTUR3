#include "pathPubVel.h"
#define SZJDEBUG 0
#define SZJDEBUG1 1
PathPubVel::PathPubVel(){
    // jointState_.resize(6);
    // for(unsigned int i = 0; i < 6; ++i){
    //     jointState_[i] = 0;
    // }
    jointState_.resize(6);
    endVelCmd_.resize(6);
    for(int i =0; i < 6; ++i){
        endVelCmd_[i] = 0;
    }
    endCommand_.p.Zero();
    endCommand_.M.Identity();
    endFrame_.p.Zero();
    endFrame_.M.Identity();
    endFrame_.p.data[0] = -0.47086;
    endFrame_.p.data[1] = -0.11169;
    endFrame_.p.data[2] = 0.24135;
    endFrame_.M.RPY(3.142, 0, 1.571);

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

void PathPubVel::urFk(){
    int ret = this->fkSolverPos_->JntToCart(jointState_, endFrame_);
    //xy与实际xy正负相反，暂时直接更改正负值使用
    endFrame_.p.data[0] = -endFrame_.p.data[0];
    endFrame_.p.data[1] = -endFrame_.p.data[1];
    #ifdef SZJDEBUG1
    // ROS_INFO("endFrame_ : %lf, %lf, %lf", endFrame_.p.data[0], endFrame_.p.data[1], endFrame_.p.data[2]);
    ROS_INFO("the joint state in fk: %lf, %lf, %lf, %lf, %lf, %lf",jointState_.data[0],jointState_.data[1], jointState_.data[2], jointState_.data[3], jointState_.data[4], jointState_.data[5]);
    #endif
    if(ret < 0)
    {
        ROS_ERROR("JntToCart error");
    }
}


Eigen::Matrix3d PathPubVel::rpy2rot(double roll, double pitch, double yaw){
    // 定义旋转矩阵的三个基本旋转
    Eigen::Matrix3d Rx, Ry, Rz;
    Rx << 1, 0, 0,
            0, cos(roll), -sin(roll),
            0, sin(roll), cos(roll);
    Ry << cos(pitch), 0, sin(pitch),
            0, 1, 0,
            -sin(pitch), 0, cos(pitch);
    Rz << cos(yaw), -sin(yaw), 0,
            sin(yaw), cos(yaw), 0,
            0, 0, 1;
    // 返回绕z-y-x轴的旋转矩阵
    return Rz * Ry * Rx;  
}

Eigen::Vector3d PathPubVel::rot2vec(Eigen::Matrix3d R){
    // 定义旋转矢量的角度和轴
    double angle, x, y, z;
    // 计算旋转角度
    angle = acos((R.trace() - 1) / 2);
    // 判断旋转角度是否为0或180度
    if (angle == 0)
    {
        // 如果旋转角度为0，返回零向量
        return Eigen::Vector3d::Zero();
    }
    else if (angle == M_PI)
    {
        // 如果旋转角度为180度，需要特殊处理
        // 找到旋转矩阵对角线上最大的元素
        int max_index = 0;
        double max_value = R(0, 0);
        for (int i = 1; i < 3; i++)
        {
        if (R(i, i) > max_value)
        {
            max_index = i;
            max_value = R(i, i);
        }
        }
        // 根据最大的元素，计算旋转轴的分量
        switch (max_index)
        {
        case 0:
        x = sqrt((R(0, 0) + 1) / 2);
        y = R(0, 1) / (2 * x);
        z = R(0, 2) / (2 * x);
        break;
        case 1:
        y = sqrt((R(1, 1) + 1) / 2);
        x = R(1, 0) / (2 * y);
        z = R(1, 2) / (2 * y);
        break;
        case 2:
        z = sqrt((R(2, 2) + 1) / 2);
        x = R(2, 0) / (2 * z);
        y = R(2, 1) / (2 * z);
        break;
        }
    }
    else
    {
        // 如果旋转角度不为0或180度，按照正常公式计算旋转轴的分量
        x = (R(2, 1) - R(1, 2)) / (2 * sin(angle));
        y = (R(0, 2) - R(2, 0)) / (2 * sin(angle));
        z = (R(1, 0) - R(0, 1)) / (2 * sin(angle));
    }
    // 返回旋转矢量，其方向为旋转轴，长度为旋转角度
    return angle * Eigen::Vector3d(x, y, z);
}

Eigen::Vector3d PathPubVel::rpy2vec(double roll, double pitch, double yaw){
    Eigen::Matrix3d rotM = rpy2rot(roll, pitch, yaw);
    Eigen::Vector3d rotV = rot2vec(rotM);
    return rotV;
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
        if(abs(endVelCmd_[i]) > 0.05){
            endVelCmd_[i] = 0.05 * (endVelCmd_[i] / (abs(endVelCmd_[i])));
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
    move_msg = move_msg + double2string(endVelCmd_[0]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[1]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[2]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[3]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[4]) + ",";
    move_msg = move_msg + double2string(endVelCmd_[5]) + "]";
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
        #if SZJDEBUG1
        for(unsigned int i = 0; i < 6; ++i){
            std::cout << "jointState_["<< i << "] : " << m_PathPubVel.jointState_(i) << "; ";
        }std::cout << std::endl;
        #endif
        /*---compute the current end pose---*/ 
        m_PathPubVel.urFk();
        double quat[4];
        m_PathPubVel.endFrame_.M.GetQuaternion(quat[0], quat[1], quat[2], quat[3]);
        #ifdef SZJDEBUG1
        ROS_INFO("quaternion : %lf, %lf, %lf, %lf", quat[0], quat[1], quat[2], quat[3]);
        #endif
        // KDL::Vector rotFrame = m_PathPubVel.endFrame_.M.GetRot();

        double rpyArr[3];
        m_PathPubVel.endFrame_.M.GetRPY(rpyArr[0], rpyArr[1], rpyArr[2]);
        ROS_INFO(" ");  
        ROS_INFO("------------Debug begin: rpyFrame------------");
        ROS_INFO_STREAM(rpyArr[0] << " # " << rpyArr[1] << " # "  << rpyArr[2]);
        ROS_INFO("------------Debug end: rpyFrame------------");
        ROS_INFO(" ");
        //这里获得的RZ与机器人面板上相差pi，比面板上多个pi
        if(rpyArr[2] < 0){
            rpyArr[2] = rpyArr[2] + M_PI;
        }else{
            rpyArr[2] = rpyArr[2] - M_PI;
        }
        Eigen::Vector3d rotVec = m_PathPubVel.rpy2vec(rpyArr[0], rpyArr[1], rpyArr[2]);

        #if SZJDEBUG
        ROS_INFO("\n");
        ROS_INFO("------------Debug begin: rotFrame------------");
        // ROS_INFO("the size of rotFrame is : %ld",sizeof(rotFrame.data)/sizeof(rotFrame.data[0]));
        // ROS_INFO_STREAM(rotFrame.data[0] << " # " << rotFrame.data[1] << " # "  << rotFrame.data[2]);
        // ROS_INFO_STREAM(rotVec[0] << " # " << rotVec[1] << " # "  << rotVec.z());
          std::cout << "The rotation vector is:\n"
            << rotVec << std::endl;
        // ROS_INFO("origin rot vec = %lf, %lf, %lf",rotFrame.data[0], rotFrame.data[1], rotFrame.data[2]);
        ROS_INFO("------------Debug end: rotFrame------------");
        
        ROS_INFO("\n");
        ROS_INFO("------------Debug begin: rpyFrame------------");
        ROS_INFO_STREAM(rpyArr[0] << " # " << rpyArr[1] << " # "  << rpyArr[2]);
        ROS_INFO("------------Debug end: rpyFrame------------");
        ROS_INFO("\n");

        // ROS_INFO("------------Debug begin: zyxFrame------------");
        // ROS_INFO_STREAM(eulerZYXArr[0] << " # " << eulerZYXArr[1] << " # "  << eulerZYXArr[2]);
        // ROS_INFO("------------Debug end: zyxFrame------------");
        // ROS_INFO("\n");

        #endif

        
        #if SZJDEBUG
        std::cout << m_PathPubVel.endFrame_.p.x() << " # " << m_PathPubVel.endFrame_.p.y() << " # " <<
        m_PathPubVel.endFrame_.p.z()<< " # " << quat[0] << " # " << quat[1] << " # " << quat[2] << " # " << quat[3] << " # " 
        << std::endl;
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
        #if SZJDEBUG1
        ROS_INFO_STREAM("endCommand_.p : " << m_PathPubVel.endCommand_.p.data[0] << " # "
                        <<m_PathPubVel.endCommand_.p.data[1] << " # "
                        <<m_PathPubVel.endCommand_.p.data[2]);

        ROS_INFO_STREAM("endFrame_.p : " << m_PathPubVel.endFrame_.p.data[0] << " # "
                        <<m_PathPubVel.endFrame_.p.data[1] << " # "
                        <<m_PathPubVel.endFrame_.p.data[2]);
        #endif
        if(cmdVec.Norm() > 1e-2){
            cmdVec = 0.1 * cmdVec / cmdVec.Norm(); 
        }else{
            cmdVec = 0 * cmdVec / cmdVec.Norm(); 
        }
        #if SZJDEBUG1
        ROS_INFO_STREAM("---cmdVec---  " << cmdVec.data[0] << " # " << cmdVec.data[1] << " # " << cmdVec.data[2]);
        #endif
        m_PathPubVel.endVelCmd_[0] = cmdVec.x();
        m_PathPubVel.endVelCmd_[1] = cmdVec.y();
        m_PathPubVel.endVelCmd_[2] = cmdVec.z();
        #if SZJDEBUG1
        ROS_INFO_STREAM("---cmdVec_vecotr---  " << m_PathPubVel.endVelCmd_[0]  << " # " << m_PathPubVel.endVelCmd_[1] << " # " << m_PathPubVel.endVelCmd_[2]);
        #endif

        /*---calculate rotation vector*/
        #if SZJDEBUG1
        // double endCmdM[3];
        // KDL::Vector endCmdM = m_PathPubVel.endCommand_.M.GetRot();
        // ROS_INFO("---原始指令角度---  %lf %lf %lf", endCmdM[0], endCmdM[1], endCmdM[2]);        
        #endif

        KDL::Rotation cmdRot = m_PathPubVel.endCommand_.M * m_PathPubVel.endFrame_.M.Inverse();
        double cmdRPYArr[3];
        cmdRot.GetRPY(cmdRPYArr[0], cmdRPYArr[1], cmdRPYArr[2]);
        #if SZJDEBUG1
        ROS_INFO("---cmdRot---  %lf %lf %lf", cmdRPYArr[0], cmdRPYArr[1], cmdRPYArr[2]);
        #endif
        if(cmdRPYArr[2] < 0){
            cmdRPYArr[2] = cmdRPYArr[2] + M_PI;
        }else{
            cmdRPYArr[2] = cmdRPYArr[2] - M_PI;
        }
        Eigen::Vector3d cmdRotVec3d = m_PathPubVel.rpy2vec(cmdRPYArr[0], cmdRPYArr[1], cmdRPYArr[2]);
        #if SZJDEBUG1
        ROS_INFO("---cmdRotVec3d--- : %lf  %lf  %lf", cmdRotVec3d[0], cmdRotVec3d[1], cmdRotVec3d[2]);
        #endif
        KDL::Vector cmdRotVec(cmdRotVec3d.x(), cmdRotVec3d.y(), cmdRotVec3d.z());
        if(cmdRotVec.Norm() > 1e-2){
            cmdRotVec = 0.3 * cmdRotVec / cmdRotVec.Norm();
        }else{
            cmdRotVec = 0 * cmdRotVec / cmdRotVec.Norm();
        }
        m_PathPubVel.endVelCmd_[3] = cmdRotVec.x();
        m_PathPubVel.endVelCmd_[4] = cmdRotVec.y();
        m_PathPubVel.endVelCmd_[5] = cmdRotVec.z();
        #if SZJDEBUG1
        ROS_INFO("---cmdRotVec--- : %lf  %lf  %lf", cmdRotVec[0], cmdRotVec[1], cmdRotVec[2]);
        #endif
        ROS_INFO(" ");
        // m_PathPubVel.urMove();

        // std::cout << std::endl;
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}