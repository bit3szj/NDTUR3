
#include <test_controller/test_controller.h>

#include <hardware_interface/hardware_interface.h>
// #include <ur_robot_driver/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>
#include <string>
#include "kdl_conversions/kdl_msg.h"
using namespace std;
#define SZJ_DEBUG 0

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

        //initial PID Controller
        // pid_controller_.reset(new PIDController(1.0, 0.1, 0.01));

        //initial the desired pose and now pose
        desired_pose_ = KDL::Frame();
        desired_pose_.p.data[0] = -0.457662;
        desired_pose_.p.data[1] = -0.194157;
        desired_pose_.p.data[2] = 0.0679784;
        desired_pose_.M = KDL::Rotation::Quaternion(0.707107, 0, 0, 0.707107);
        current_pose_ = KDL::Frame();

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
            joint_positions_(i) = 0.0;
            joint_velocities_(i) = 0.0;
        }
        
    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Test_Controller::update(const ros::Time& time, const ros::Duration& period) {

        
        for(int i =0; i<_joint_len_; ++i)
        {
            // if (i>=joint_positions_.rows())
            // {
            //     ROS_ERROR("num of joint error");
            //     break;
            // }
            if(fabs(this->joint_handles_[i].getPosition() - (this->joint_positions_(i) + qdot_cmd_(i)*period.toSec()) )<0.0000001 || qdot_cmd_(i) != 0){
                joint_positions_(i) = joint_handles_[i].getPosition();  
                joint_velocities_(i) = joint_handles_[i].getVelocity();
            }


        }
        ik_solver_vel_->CartToJnt(this->joint_positions_, twist_, qdot_cmd_);
        writeVelocityCommands(period);
        for(size_t i=0; i<this->joint_handles_.size(); ++i){
            this->joint_handles_[i].setCommand(this->joint_positions_(i) + qdot_cmd_(i)*period.toSec());
        }
        fk_solver_->JntToCart(joint_positions_, current_pose_);
        // fk_solver_vel_->JntToCart(this->joint_velocities_, )
        // if(SZJ_DEBUG){
        //     ROS_INFO_STREAM("current_pose:"<< " x="<< current_pose_.p.data[0] <<" y=" <<current_pose_.p.data[1]<< " z="<< current_pose_.p.data[2]);
        // }
        
        // //compute current error
        KDL::Vector _vec = (desired_pose_.p - current_pose_.p);
        if(_vec.Norm() > 1e-3){
            _vec = 0.1*_vec / _vec.Norm();
        }
        // cout<< "piancha vec = " << _vec.data[0] <<" " <<_vec.data[1]<< " "<< _vec.data[2] <<endl;
        twist_.vel = _vec;

        KDL::Rotation _rot = desired_pose_.M * current_pose_.M.Inverse();
        KDL::Vector _theta = _rot.GetRot();
        if(_theta.Norm() > 1e-3){
            _theta = 0.3*_theta / _theta.Norm();
        }
        twist_.rot = _theta;

        // twist_ = KDL::diff(current_pose_, desired_pose_);
        // for(int i = 0; i<3; ++i){
        //     cout << current_pose_.p.data[i]<<" ";
        // }
        // cout<<endl;
        // for(int i = 0; i<3; ++i){
        //     cout << desired_pose_.p.data[i]<<" ";
        // }
        // cout<<endl;
        // cout << "current_pose_.M.data"<< endl ;
        // for(int i =0; i < 3; ++i){
        //     for(int j = 0; j < 3; ++j){
        //         cout<<current_pose_.M.data[i*3+j]<<" ";
        //     }
        //     cout<<endl;
        // }
        // cout << "desired_pose_.M.data"<< endl ;
        // for(int i =0; i < 3; ++i){
        //     for(int j = 0; j < 3; ++j){
        //         cout<<desired_pose_.M.data[i*3+j]<<" ";
        //     }
        //     cout<<endl;
        // }



        // //compute desired joint velocity

        // int status = ik_solver_vel_->CartToJnt(joint_positions_, twist_, qdot_des_);
        // cout << qdot_des_.rows()<<endl;
        // cout<<"qdot_des_.data"<<endl;
        // for(int i = 0; i<qdot_des_.rows(); ++i){
        //     cout << qdot_des_.data[i]<<" ";
        // }
        // cout<<endl;

        // cout << joint_velocities_.rows()<<endl;
        // cout<<"joint_velocities_.data"<<endl;
        // for(int i = 0; i<joint_velocities_.rows(); ++i){
        //     cout << joint_velocities_.data[i]<<" ";
        // }
        // cout<<endl;
        // if(status == KDL::ChainIkSolverVel_pinv::E_NO_CONVERGE){
        //     ROS_ERROR("not get inverse velocity\n");
        // }

        //【20230602】【23：45】问题在这，joint_velocities段错误
        // qdot_cmd_ = pid_controller_->computeCommand(joint_velocities_, qdot_des_);
        // cout << qdot_cmd_.rows()<<endl;
        //   Write the control command to the joint handles
        // for (size_t i = 0; i < _joint_len_; i++)
        // {
        //     joint_command_(i) += qdot_cmd_(i) * period.toSec(); // Integrate the joint velocity command to get position command
        //     joint_handles_[i].setCommand(joint_command_(i));
        // }


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

    }


    void Test_Controller::poseCallback(const geometry_msgs::PoseStamped &msg){
        //convert the geometry_msgs pose to a KDL frame
        //in "kdl_conversions/kdl_msg.h"
        tf::poseMsgToKDL(msg.pose, desired_pose_);

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
