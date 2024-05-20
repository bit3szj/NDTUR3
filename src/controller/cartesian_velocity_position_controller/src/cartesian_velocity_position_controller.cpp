#include "cartesian_velocity_position_controller/cartesian_velocity_position_controller.h"
#include <pluginlib/class_list_macros.h>
#include "kdl_conversions/kdl_msg.h"


#include "cartesian_velocity_position_controller/kdl_base.h"
#define szj_debug 1

namespace cartesian_velocity_position_controller {
    /** \brief Initialize the kinematic chain for kinematics-based computation.
    *
    */
    bool Cartesian_Velocity_Position_Controller::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &node_handle) {
        ROS_INFO("Cartesian_Velocity_Position_Controller init");
        //  read param out side
        std::string name_space = node_handle.getNamespace();
        std::string test_value;
        if (!node_handle.getParam(name_space + "/test_value", test_value)) {
            ROS_ERROR("Cartesian_Velocity_Position_Controller: Could not read parameter test_value");
            return false;
        } else {
            ROS_INFO_STREAM("test_value: " << test_value);
        }

        ros::NodeHandle &n = node_handle;
        // KDL
        kdl_base::KDL_Base::init(robot, n);

        ik_vel_solver_.reset(new KDL::ChainIkSolverVel_pinv_givens(this->kdl_chain_));
        fk_vel_solver_.reset(new KDL::ChainFkSolverVel_recursive(this->kdl_chain_));
        fk_pos_solver_.reset(new KDL::ChainFkSolverPos_recursive(this->kdl_chain_));

        // get publishing period
        if (!n.getParam("publish_rate", publish_rate_)){
            ROS_ERROR("Parameter 'publish_rate' not set");
            return false;
        }
        realtime_pub_.reset(new realtime_tools::RealtimePublisher
            <cartesian_state_msgs::PoseTwist>(n, "ee_state", 4));


        // Topics
        // sub_command_ = n.subscribe("command_cart_vel", 5,
        //     &Cartesian_Velocity_Position_Controller::command_cart_vel, this,
        //     ros::TransportHints().reliable().tcpNoDelay());

        // Topics
        sub_command_ = n.subscribe("command_cart_pos", 5,
            &Cartesian_Velocity_Position_Controller::command_cart_pos, this,
            ros::TransportHints().reliable().tcpNoDelay());
        ros::Duration(0.1).sleep();
        //Topic subcribe the correct pose
        sub_command_correct = n.subscribe("command_cart_pos_correct",5,
            &Cartesian_Velocity_Position_Controller::command_cart_pos_correct, this,
            ros::TransportHints().reliable().tcpNoDelay());
        //this topic is used to publish the end-tool velocity
        pub_endVel = n.advertise<geometry_msgs::Pose>("endVel",1);
        pub_urScript = n.advertise<std_msgs::String>("ur_hardware_interface/script_command",10);


        ros::Duration(0.1).sleep();
        ROS_INFO("sub compelete");
        

        // Variable init
        this->joint_state_.resize(this->kdl_chain_.getNrOfJoints());
        //this->joint_effort_.resize(this->kdl_chain_.getNrOfJoints());
        Jnt_Vel_Cmd_.resize(this->kdl_chain_.getNrOfJoints());
        End_Vel_Cmd_ = KDL::Twist::Zero();
        End_Pos_.p.Zero();
        End_Pos_.M.Identity();
        End_Vel_.p.Zero();
        End_Vel_.M.Identity();
        End_Pos_sub1.p.Zero();
        End_Pos_sub1.M.Identity();
        End_Pos_sub2.p.Zero();
        End_Pos_sub2.M.Identity();


        //--- method1 : set the robot's initial positions to the specified value
        /* Todo initial pose
            End_Pos_Cmd_ = 
            desired_pose_orientation_ = 
            arm_orientation_ 
        */
        // KDL::Vector init_pos_vec;

        // // this->joint_handles_[0].setCommand();
        // init_pos_vec[0] = -0.1;
        // init_pos_vec[1] = 0.16;
        // init_pos_vec[2] = 0.354;

        // End_Pos_Cmd_.p = init_pos_vec;
        // // End_Pos_Cmd_.M = End_Pos_Rotation.Quaternion(0.68,-0.66,-0.31,0.061);
        // End_Pos_Cmd_.M = End_Pos_Rotation.Quaternion(-0.76, -0.65, 0.01, 0.02);

        // --- method2 : set the robot's initial position to its own value
        KDL::JntArray initJ(6);
        KDL::Frame initP;
        for(int i = 0; i < 6; ++i){
            initJ(i) = this->joint_handles_[i].getPosition();
        }
        // initJ(0) = 0; initJ(1) = 0; initJ(2) = 0; 
        // initJ(3) = -1.570796327; initJ(4) = 0; initJ(5) = 0;
        fk_pos_solver_->JntToCart(initJ, initP);
        End_Pos_Cmd_ = initP;
        return true;
    }

    /** \brief This is called from within the realtime thread just before the
    * first call to \ref update
    *
    * \param time The current time
    */
    void Cartesian_Velocity_Position_Controller::starting(const ros::Time& time){  
        ROS_INFO("Cartesian_Velocity_Position_Controller starting");
        for(std::size_t i=0; i < this->joint_handles_.size(); i++) {
            Jnt_Vel_Cmd_(i) = 0.0;
            this->joint_state_.q(i)     = 0.0;
            this->joint_state_.qdot(i)  = 0.0;
        }

        End_Vel_Cmd_ = KDL::Twist::Zero();
        last_publish_time_ = time;

    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Cartesian_Velocity_Position_Controller::update(const ros::Time& time, const ros::Duration& period) {
        // Get joint positions
        for(std::size_t i=0; i < this->joint_handles_.size(); i++)
        {
            //if current position reaches the last command position or the speed movement command is not zero
            //then it will be updated
            if(fabs(this->joint_handles_[i].getPosition()-(this->joint_state_.q(i) + Jnt_Vel_Cmd_(i)*period.toSec()))<0.0000001 
            || Jnt_Vel_Cmd_(i)!=0
            )  //  joint will keep running without 
            {
            this->joint_state_.q(i)         = this->joint_handles_[i].getPosition();
            this->joint_state_.qdot(i)      = this->joint_handles_[i].getVelocity();
            }
        }
        // Compute inverse kinematics velocity solver
        //  http://docs.ros.org/en/hydro/api/orocos_kdl/html/classKDL_1_1ChainIkSolverVel.html
        //calculate joint speed based on cartesian velocity
        //szj_warn: i think the reason for shaking of manipulator may be that it has not reached the designated position
        //          and the speed command has been repeatedly calculated.
        //          logically speaking,the calculate result should be same,but because the result obtained by the analytical
        //          solution is not fixed,there will be a slight error,which causes the manipulator to shake.
        //szj_solution(**unfinished business**): create a flag used to record whether calculation is required
        ik_vel_solver_->CartToJnt(this->joint_state_.q, End_Vel_Cmd_, Jnt_Vel_Cmd_);

        writeVelocityCommands(period);

        // Forward kinematics
        //计算笛卡尔位置和速度
        //szj_info:the control process is compeleted through joint control,here we solve the cartesian position ,
        //which is used to calculate the speed in cartesian system in the follwing steps,and publish it for user
        fk_vel_solver_->JntToCart(this->joint_state_, End_Vel_);
        fk_pos_solver_->JntToCart(this->joint_state_.q, End_Pos_);

        // Limit rate of publishing
        //实时发布笛卡尔位置和速度
        if (publish_rate_ > 0.0 && last_publish_time_
            + ros::Duration(1.0/publish_rate_) < time) {

            // try to publish
            if (realtime_pub_->trylock()) {
            last_publish_time_ = last_publish_time_
                                + ros::Duration(1.0/publish_rate_);
            // populate message
            realtime_pub_->msg_.header.stamp = time;
            tf::poseKDLToMsg(End_Pos_, realtime_pub_->msg_.pose);
            tf::twistKDLToMsg(End_Vel_.GetTwist(), realtime_pub_->msg_.twist);
            
            realtime_pub_->unlockAndPublish();
            }
        }

        //  direction 
        //szj_info:here we calculate the speed command in the cartesian system,which is used to calculate the joint speed command
        //at the beginning of the update loop
        KDL::Vector _vec = (End_Pos_Cmd_.p - End_Pos_.p);
        //  static velocity above 1e-3        
        if(_vec.Norm() > 1e-3)
        {
            _vec = 0.1 * _vec / _vec.Norm();
        }        
        End_Vel_Cmd_.vel = _vec;
   
        // KDL implement
        KDL::Rotation _rot = End_Pos_Cmd_.M * End_Pos_.M.Inverse();
        KDL::Vector _theta = _rot.GetRot();
        //  static velocity above 1e-3        
        if(_theta.Norm() > 1e-3)
        {
            _theta = 0.3 * _theta / _theta.Norm(); // reduce speed or it will be too fast
        }  
        End_Vel_Cmd_.rot = _theta;

        //pub the tool velocity
        //the following method has the same result as the realtime_pub method above
        /*
        KDL::ChainJntToJacSolver solver(this->kdl_chain_);
        KDL::JntArrayVel jntVel(this->kdl_chain_.getNrOfJoints());
        for(int i = 0; i < 6; ++i){
            jntVel.qdot(i) = this->joint_handles_[i].getVelocity();
            jntVel.q(i) = this->joint_handles_[i].getPosition();
        }        
        KDL::Jacobian jac(this->kdl_chain_.getNrOfJoints());
        solver.JntToJac(jntVel.q, jac);
        KDL::Twist endEffectorVel;
        KDL::MultiplyJacobian(jac, jntVel.qdot, endEffectorVel);
        for(unsigned int i=0;i<this->kdl_chain_.getNrOfJoints();i++)
            endEffectorVel = endEffectorVel + jac.getColumn(i)*jntVel.qdot(i);
        // ROS_INFO("the velocity %lf, %lf, %lf, %lf, %lf, %lf",jntVel.q(0), jntVel.q(1), jntVel.q(2), jntVel.q(3), jntVel.q(4), jntVel.q(5));
        // ROS_INFO("the cartesian velocity %lf, %lf, %lf", endEffectorVel.vel(0), endEffectorVel.vel(1), endEffectorVel.vel(2));
        // ROS_INFO_STREAM("endEffectorVel = " << endEffectorVel.vel.data[0]<< " "<< endEffectorVel.vel.data[1]<< " "<< endEffectorVel.vel.data[2]);
        */ 

    //    std::cout << joint_state_.q.data[0] << " # " << joint_state_.q.data[1] << " # "<<joint_state_.q.data[2] << " # "
    //    << joint_state_.q.data[3] << " # " << joint_state_.q.data[4]<< " # " << joint_state_.q.data[5] 
    //    << std::endl;
        

    
    
    }   

    /*!
    * \brief Subscriber's callback: copies twist commands
    */
    void Cartesian_Velocity_Position_Controller::command_cart_vel(const geometry_msgs::TwistConstPtr &msg) {
        //ROS_INFO("End_Vel_Cmd_ %f %f %f", End_Vel_Cmd_.vel(0), End_Vel_Cmd_.vel(1), End_Vel_Cmd_.vel(2));
        End_Vel_Cmd_.vel(0) = msg->linear.x;
        End_Vel_Cmd_.vel(1) = msg->linear.y;
        End_Vel_Cmd_.vel(2) = msg->linear.z;
        End_Vel_Cmd_.rot(0) = msg->angular.x;
        End_Vel_Cmd_.rot(1) = msg->angular.y;
        End_Vel_Cmd_.rot(2) = msg->angular.z;
    }

    
    void Cartesian_Velocity_Position_Controller::command_cart_pos(const geometry_msgs::PoseConstPtr &msg) {

        boost::mutex::scoped_lock lock(data_mutex);
        tf::poseMsgToKDL(*msg, End_Pos_sub1);
        // End_Pos_Cmd_ = End_Pos_sub1 * End_Pos_sub2; 
        End_Pos_Cmd_ = End_Pos_sub2 * End_Pos_sub1;  
    }

    void Cartesian_Velocity_Position_Controller::command_cart_pos_correct(const geometry_msgs::PoseConstPtr &msg) {
        //ROS_INFO("position %f %f %f", msg->position.x, msg->position.y, msg->position.z);
       boost::mutex::scoped_lock lock(data_mutex);
       tf::poseMsgToKDL(*msg, End_Pos_sub2);
    //    End_Pos_Cmd_ = End_Pos_sub1 * End_Pos_sub2;
        End_Pos_Cmd_ = End_Pos_sub2 * End_Pos_sub1; 
    } 

    /********************************************/
    /**FUNCTIONS OF INSTANCES OF THE BASE CLASS**/
    /********************************************/
    std::string Cartesian_Velocity_Position_Controller::double2string(double input){
        std::string string_temp;
        std::stringstream stream;
        stream<<input;
        string_temp = stream.str();
        return string_temp;
    }

    /** \brief write the desired velocity command in the hardware interface input
    * for a PositionJointInterface
    * \param period The duration of an update cycle
    */
    void Cartesian_Velocity_Position_Controller::writeVelocityCommands(
                                        const ros::Duration& period) {
                                            

        for(std::size_t i=0; i < this->joint_handles_.size(); i++) {                   
            this->joint_handles_[i].setCommand(this->joint_state_.q(i) + Jnt_Vel_Cmd_(i)*period.toSec());
        }

    }


}

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(cartesian_velocity_position_controller::Cartesian_Velocity_Position_Controller, controller_interface::ControllerBase)
