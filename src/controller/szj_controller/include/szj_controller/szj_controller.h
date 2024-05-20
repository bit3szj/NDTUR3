#ifndef SZJ_CONTROLLER_H_
#define SZJ_CONTROLLER_H_

#include <ros/node_handle.h>
#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>

namespace szj_controller
{
    class Szj_controller:public controller_interface::Controller<hardware_interface::PositionJointInterface>
    {
        public:
            Szj_controller() {}
            ~Szj_controller() {}

            bool init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &n);

            void starting(const ros::Time& time);
            void update(const ros::Time& time, const ros::Duration& period);
        private:
            void writeVelocityCommands(const ros::Duration& period);
            void writePositionCommands(const ros::Duration& period);
        protected:
            std::vector<hardware_interface::JointHandle> joint_handles_;
            int _joint_len_ = 6;
            std::string _links[6] = {
                "shoulder_pan_joint",
                "shoulder_lift_joint",
                "elbow_joint",
                "wrist_1_joint",
                "wrist_2_joint",
                "wrist_3_joint"
            };
        
    };

}



#endif