
#include <test_controller/test_controller.h>

#include <hardware_interface/hardware_interface.h>
// #include <ur_robot_driver/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>
#include <string>
#include "kdl_conversions/kdl_msg.h"
using namespace std;
#define SZJ_DEBUG 0
#define DEBUG_PID_OUT 0
#define DEBUG_POSE_CALLBACK 0

namespace test_controller {
    /** \brief Initialize the kinematic chain for kinematics-based computation.
    *
    */
    bool Test_Controller::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &node_handle) {
        ROS_INFO("Test_Controller init");
        
        //  read param out side
        std::string name_space = node_handle.getNamespace();
        std::string test_value;
        //init joint positions
        //here 
        joint_positions_.resize(6);
        desired_joint_positions_.resize(6);
        joint_velocities_.resize(6);
        joint_command_.resize(6);
        joint_command_.data.setZero();
        //test getparama
        if (!node_handle.getParam(name_space + "/test_value", test_value)) {
            ROS_ERROR("TestController: Could not read parameter test_value");
            return false;
        } else {
            ROS_INFO_STREAM("test_value: " << test_value);
        }
            
        //get joint handler
        for (int i = 0; i< _joint_len_; i++){
            joint_handles_.push_back(robot->getHandle(_links[i]));
            // joint_positions_(i) = joint_handles_[i].getPosition();
            // joint_velocities_(i) = joint_handles_[i].getVelocity();
            // joint_handles_[i].setCommand(joint_command_(i));
        }
        //initial joint position
        // initJoint();


        //initial the KDL chain and solver
        initKDL();
        ROS_INFO("init KDL success");

        //initial PID controller
        pid_controller_.reset(new PIDController(0.1, 0.0, 0.01, 0.1, -0.01));


        //initial the desired pose and now pose
        desired_pose_ = KDL::Frame();
        desired_pose_.p.data[0] = 0;
        desired_pose_.p.data[1] = -0.194;
        desired_pose_.p.data[2] = 0.69420;
        desired_pose_.M = KDL::Rotation::EulerZYX(3.136, 0, -1.571);
        // Initialize the twist and joint velocity variables
        twist_ = KDL::Twist::Zero();
        qdot_des_.resize(6);
        qdot_cmd_.resize(6);
        //subcribe to the pose topic
        pose_sub_ = node_handle.subscribe("/pose", 1, &Test_Controller::poseCallback, this);
        ROS_INFO("pose_sub success");
        return true;


    }

    /** \brief This is called from within the realtime thread just before the
    * first call to \ref update
    *
    * \param time The current time
    */
    void Test_Controller::starting(const ros::Time& time){

        
        ROS_INFO("Test_Controller starting");
        int joint_positions_size = joint_positions_.rows();
        ROS_INFO_STREAM("joint positions num:" << joint_positions_size << " joint_len_:" << _joint_len_);
        for (int i = 0; i< _joint_len_; i++){
            qdot_cmd_(i) = 0.0;
            joint_positions_(i) = joint_handles_[i].getPosition();
            joint_velocities_(i) = 0.0;
        }
        
    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Test_Controller::update(const ros::Time& time, const ros::Duration& period) {


        for (int i = 0; i< _joint_len_; i++){
            joint_positions_(i) = joint_handles_[i].getPosition();
        }


        // 计算机器人位置的误差
        KDL::Frame current_frame;
        fk_solver_->JntToCart(joint_positions_, current_frame);
        KDL::Twist twist_error;
        twist_error = KDL::diff(desired_pose_, current_frame);  // 计算位姿之间的差异
        // 当误差小于一定范围时，就不对机器人进行控制
        if (twist_error.vel.Norm() < 0.1 && twist_error.rot.Norm() < 0.1) {
            for(int i = 0; i < _joint_len_; ++i){
                joint_positions_(i) = joint_handles_[i].getPosition();
            }

            for(int i =0; i < 6; ++i){
                // joint_handles_[i].setCommand(desired_joint_positions_(i));
                joint_handles_[i].setCommand(joint_handles_[i].getPosition());
                desired_joint_positions_(i) = joint_handles_[i].getPosition();
                // joint_handles_[i].setCommand(pid_command(i));
            }
            return;
        }

        //PID CONTROL
        KDL::JntArray pid_command = pid_controller_->computeCommand(joint_positions_, desired_joint_positions_);
        for(int i =0; i < 6; ++i){
            // joint_handles_[i].setCommand(desired_joint_positions_(i));
            joint_handles_[i].setCommand(joint_positions_(i) + 0.1*pid_command(i));
            // joint_handles_[i].setCommand(pid_command(i));
        }
        
        fk_solver_->JntToCart(joint_positions_, current_pose_);
        if(DEBUG_PID_OUT){
            for(unsigned int i =0; i < pid_command.rows(); ++i){
                cout<< "q"<< i+1<< "="<< joint_positions_(i)<< " ";
            }
            cout<<endl;
            for(unsigned int i =0; i < pid_command.rows(); ++i){
                cout<< "q_des"<< i+1<< "="<< desired_joint_positions_(i)<< " ";
            }
            cout<<endl;
            for(unsigned int i =0; i < pid_command.rows(); ++i){
                cout<< "pid"<< i+1<< "="<< pid_command(i)<< " ";
            }
            cout<<endl;
        }




    }

    //***********************************************init*************************************************//
    //initial joint position
    void Test_Controller::initJoint(){
        
        this->joint_handles_[0].setCommand(0.00);
        this->joint_handles_[1].setCommand(-M_PI_2);
        this->joint_handles_[2].setCommand(0.00);
        this->joint_handles_[3].setCommand(-M_PI_2);
        this->joint_handles_[4].setCommand(0.00);
        this->joint_handles_[5].setCommand(0.00);
    }

    //initial KDL chain for kinemic

    void Test_Controller::initKDL(){
        chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ), KDL::Frame::DH(0.0, M_PI_2, 0.1519, 0.0)));
        chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ), KDL::Frame::DH(-0.24365, 0.0, 0.0, 0.0)));
        chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ), KDL::Frame::DH(-0.21325, 0.0, 0.0, 0.0)));
        chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ), KDL::Frame::DH(0.0, M_PI_2, 0.11235, 0.0)));
        chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ), KDL::Frame::DH(0.0, -M_PI_2, 0.08535, 0.0)));
        chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ), KDL::Frame::DH(0.0, 0.0, 0.0819, 0.0)));
        fk_solver_.reset(new KDL::ChainFkSolverPos_recursive(chain));
        ik_solver_vel_.reset(new KDL::ChainIkSolverVel_pinv(chain));
        // ik_solver_pos_.reset(new KDL::ChainIkSolverPos_NR_JL(chain, fk_solver_, ik_solver_vel_, 100, 1e-6));
        // ik_solver_pos_.reset(new KDL::ChainIkSolverPos_NR_JL(chain, *fk_solver_, *ik_solver_vel_,2000));
        ik_solver.reset(new KDL::ChainIkSolverPos_LMA(chain));
        fk_solver_vel_.reset(new KDL::ChainFkSolverVel_recursive(chain));

        error_.resize(6);
        error_prior_.resize(6);
        integral_.resize(6);
        derivative_.resize(6);
        output_.resize(6);

    }


    void Test_Controller::poseCallback(const geometry_msgs::PoseStamped &msg){
        //convert the geometry_msgs pose to a KDL frame
        //in "kdl_conversions/kdl_msg.h"
        tf::poseMsgToKDL(msg.pose, desired_pose_);
        if(DEBUG_POSE_CALLBACK){
            ROS_INFO("poseCallback run\n");
        }
        
        int status = ik_solver->CartToJnt(joint_positions_, desired_pose_, desired_joint_positions_);
        if (status >= 0)
        {
            ROS_INFO("IK solution found.");
        }
        else
        {
            ROS_WARN("IK solution not found.");
            // TODO: handle the failure case
            for(int i = 0; i < _joint_len_; ++i){
                joint_positions_(i) = joint_handles_[i].getPosition();
            }

            for(int i =0; i < 6; ++i){
                // joint_handles_[i].setCommand(desired_joint_positions_(i));
                joint_handles_[i].setCommand(joint_handles_[i].getPosition());
                desired_joint_positions_(i) = joint_handles_[i].getPosition();
                // joint_handles_[i].setCommand(pid_command(i));
            }
            return;
        }

    }

    void Test_Controller::writeVelocityCommands(const ros::Duration& period){
        for(size_t i=0; i<this->joint_handles_.size(); ++i){
            this->joint_handles_[i].setCommand(this->joint_positions_(i) + qdot_cmd_(i)*period.toSec());
        }
    }
}   

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(test_controller::Test_Controller,
                       controller_interface::ControllerBase)
