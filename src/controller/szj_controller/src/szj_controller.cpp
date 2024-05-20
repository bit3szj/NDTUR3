#include <szj_controller/szj_controller.h>
#include <hardware_interface/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>
#include <string>

// using namespace std;

namespace szj_controller
{
    bool Szj_controller::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &node_handle){
        ROS_INFO("Szj_controller init");
        

        std::string name_space = node_handle.getNamespace();
        // ROS_INFO_STREAM(name_space);
        std::string test_value;
        if(!node_handle.getParam(name_space + "/test_value", test_value)){
            ROS_ERROR("SzjController: Could not read parameter test_value");
            return false;
        }else{
            ROS_INFO_STREAM("test_value: "<< test_value);
        }

        for (int i = 0; i < _joint_len_; i++){
            joint_handles_.push_back(robot->getHandle(_links[i]));
        }
        joint_handles_[0].setCommand(0.00);
        joint_handles_[1].setCommand(-M_PI_2);
        joint_handles_[2].setCommand(0.00);
        joint_handles_[3].setCommand(-M_PI_2);
        joint_handles_[4].setCommand(0.00);
        joint_handles_[5].setCommand(0.00);

        //initial PID controller
        // for(size_t i = 0; i < joint_handles_.size(); ++i){
        //     //Get PID gain from parameter server
        //     double P, I, D;
        //     if(!node_handle.getParam("/Pgains" , P) ||
        //        !node_handle.getParam("/Igains" , I) ||
        //        !node_handle.getParam("/Dgains" , D))        
        //     {
        //         ROS_ERROR("Failed to get PID gains");
        //     }


        // }

        return true;
    }

    void Szj_controller::starting(const ros::Time& time){
        ROS_INFO("Szj_controller starting");
    }

    void Szj_controller::update(const ros::Time &time, const ros::Duration& period){
        // std::string _str = "";
        // for (int i = 0; i < _joint_len_; ++i){
        //     _str = " " + std::to_string(this->joint_handles_[i].getPosition());
        // }
        // ROS_INFO_STREAM("joint positions" << _str);
        std::string _str = "";
        for (int i = 0; i < _joint_len_; i ++) {
            _str += " " + std::to_string(this->joint_handles_[i].getPosition());
        }
        ROS_INFO_STREAM("Joint positions" << _str);
    }
    
    void Szj_controller::writeVelocityCommands(const ros::Duration& period){
        
    }
    void Szj_controller::writePositionCommands(
                                    const ros::Duration& period)  {
        
    }
}


PLUGINLIB_EXPORT_CLASS(szj_controller::Szj_controller,
                         controller_interface::ControllerBase)