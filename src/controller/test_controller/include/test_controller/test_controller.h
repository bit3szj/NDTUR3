#ifndef TEST_CONTROLLER_H
#define TEST_CONTROLLER_H

#include"PID_controller.h"
#include <ros/node_handle.h>

#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainfksolvervel_recursive.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>
#include <kdl/chainiksolvervel_pinv.hpp>
#include <kdl/frames.hpp>
#include <geometry_msgs/PoseStamped.h>
#include <control_toolbox/pid.h>
#include<kdl/jntarray.hpp>
#include <kdl/chainiksolverpos_lma.hpp>
#include <hardware_interface/posvel_command_interface.h>



namespace test_controller {
    class Test_Controller: public controller_interface::Controller<hardware_interface::PositionJointInterface>{
        public:
            Test_Controller() {}
            ~Test_Controller() {}

            /** \brief The init function is called to initialize the controller from a
            * non-realtime thread with a pointer to the hardware interface, itself,
            * instead of a pointer to a RobotHW.
            *s
            * \param robot The specific hardware interface used by this controller.
            *
            * \param n A NodeHandle in the namespace from which the controller
            * should read its configuration, and where it should set up its ROS
            * interface.
            *
            * \returns True if initialization was successful and the controller
            * is ready to be started.
            */
            bool init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &n);

            /** \brief This is called from within the realtime thread just before the
            * first call to \ref update
            *
            * \param time The current time
            */
            void starting(const ros::Time& time);

            /*!
            * \brief Issues commands to the joint. Called at regular intervals
            */
            void update(const ros::Time& time, const ros::Duration& period);
        private:
            /** \brief Write current commands to the hardware interface
            */
            void writeVelocityCommands(const ros::Duration& period);
            void writePositionCommands(const ros::Duration& period);
            void output_joint_data(int N);
            void initJoint();
            void initKDL();
            void poseCallback(const geometry_msgs::PoseStamped& msg);

        protected:
            std::vector<hardware_interface::JointHandle> joint_handles_;
            // std::vector<hardware_interface::PosVelJointHandle> joint_handles_;
            int _joint_len_ = 6;
            std::string _links[6] = { "shoulder_pan_joint",
                    "shoulder_lift_joint",
                    "elbow_joint",
                    "wrist_1_joint",
                    "wrist_2_joint",
                    "wrist_3_joint" };
        private:
            double altitude = 0.5;
            // std::vector<control_toolbox::Pid> pid_controllers_;
            boost::shared_ptr<PIDController> pid_controller_;
            //kinemic
            KDL::Chain chain;
            boost::shared_ptr<KDL::ChainFkSolverPos_recursive> fk_solver_;
            boost::shared_ptr<KDL::ChainFkSolverVel> fk_solver_vel_;
            boost::shared_ptr<KDL::ChainIkSolverPos_NR_JL> ik_solver_pos_;
            boost::shared_ptr<KDL::ChainIkSolverVel_pinv> ik_solver_vel_;
            // boost::shared_ptr<KDL::ChainIkSolverVel> ik_solver_vel_;
            boost::shared_ptr<KDL::ChainIkSolverPos_LMA> ik_solver;
            KDL::JntArray joint_positions_;
            KDL::JntArray joint_velocities_;
            KDL::JntArray joint_command_;
            KDL::JntArray qdot_des_;
            KDL::JntArray qdot_cmd_;
            KDL::Twist twist_;

            KDL::JntArray desired_joint_positions_;
            KDL::Frame desired_pose_;
            KDL::Frame current_pose_;

            ros::Time time_last_cout;
            ros::Time time_now_cout;

            //topic
            ros::Subscriber pose_sub_;

            double Kp = 0.1;
            double Ki = 0;
            double Kd = 0;

            // Define error variables
            std::vector<double> error_; // Current error
            
            std::vector<double> error_prior_; // Previous error
            std::vector<double> integral_; // Integral term
            std::vector<double> derivative_; // Derivative term
            std::vector<double> output_; // Output command


    };

}



#endif