#ifndef ZERO_ADMITTANCE_CONTROLLER_H
#define ZERO_ADMITTANCE_CONTROLLER_H
#include <ros/ros.h>
#include <Eigen/Eigen>
#include <moveit/robot_model_loader/robot_model_loader.h>
// #include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <sensor_msgs/JointState.h>
#include <controller_manager_msgs/SwitchController.h>
#include <controller_manager_msgs/ListControllers.h>
#include <std_srvs/Trigger.h>
#include <std_srvs/SetBool.h>
#include <std_msgs/Float64MultiArray.h>
#include <trajectory_msgs/JointTrajectory.h>

#include <controller_manager_msgs/SwitchController.h>
#include <controller_manager_msgs/ListControllers.h>

#include <iostream>

using namespace Eigen;

typedef Matrix<double, 7, 1> Vector7d;
typedef Matrix<double, 6, 1> Vector6d;
typedef Matrix<double, 6, 6> Matrix6d;
typedef Array<double, 6, 1> Array6d;


#define GET_VARIABLE_NAME(Variable) (#Variable)

namespace from_zero
{
class admittance_control{
    public:

        admittance_control(
            ros::NodeHandle &n,
            ros::Rate ros_rate,
            std::string topic_force_sensor_subscriber,
            std::string topic_joint_states_subscriber,
            std::string tpoic_joint_trajectory_publisher,
            std::string topic_action_trajectory_publisher, 
            std::string topic_joint_group_vel_controller_publisher, 
            std::vector<double> mass_model_matrix,
            std::vector<double> damping_model_matrix, 
            std::vector<double> joint_limits,
            std::vector<double> maximum_velocity,
            std::vector<double> maximum_acceleration
        );

        ~admittance_control();

        void spinner(void);

        bool my_debug;

    private:
        ros::NodeHandle nh;
        ros::Rate loop_rate;
//----------------------------------------------------------------------------------------------------------------------//
        // ----Admittance Parameters ----//
        Matrix6d mass_matrix, damping_matrix;
        bool use_feedback_velocity, use_ur_real_robot;

        // ---- Admittance IO ---- //
        Vector6d external_wrench, ftsensor_start_offset, x_dot, q_dot;
        Vector6d q_dot_last_cycle, x_dot_last_cycle;//上一周期

        // ---- Limits ---- //
        Vector6d joint_lim, max_vel, max_acc;

        // ---- MoveIt Robot Model ---- //
        robot_model_loader::RobotModelLoader robot_model_loader;
        robot_model::RobotModelPtr kinematic_model;
        robot_state::RobotStatePtr kinematic_state;
        const robot_state::JointModelGroup *joint_model_group;
        std::vector<std::string> joint_names;
        Eigen::MatrixXd J;

        // ---- Trajectory Execution ---- //
        std::vector<sensor_msgs::JointState> desired_trajectory;
        // ---- Feedback Variables ---- //
        bool force_callback, joint_state_callback;
        sensor_msgs::JointState joint_state;
        std::vector<double> joint_position, joint_velocity;
        std::vector<Vector6d> filter_elements;


// ---------------------------------------------------------------------------------------------------------------------------//

        // ---- PUBLISHERS & SUBSCRIBERS ---- //
        ros::Subscriber force_sensor_subscriber, joint_states_subscriber, trajectory_execution_subscriber;
        ros::Publisher joint_trajectory_publisher, joint_group_vel_controller_publisher, ur3_script_command_publisher;
        ros::Publisher cartesian_position_publisher;

        // ---- ROS SERVICE CLIENTS ---- //
        ros::ServiceClient ur3_resend_robot_program, ur3_play_urcap,switch_controller_client;
        controller_manager_msgs::SwitchController switch_controller_srv;
        controller_manager_msgs::ListControllers list_controllers_srv;
        std_srvs::Trigger  ur3_resend_robot_program_srv, ur3_play_urcap_srv;
        
        // ---- ROS SERVICE SERVERS ---- //
        ros::ServiceServer ur10e_freedrive_mode_service, ur10e_restart_urcap_service;
        bool admittance_control_request, freedrive_mode_request, trajectory_execution_request;

//----------------------------------------------------------------------------------------------------------------------//

    // ---- ADMITTANCE FUNCTIONS ---- //
    void compute_admittance (void);

    // ---- TRAJECTORY FUNCTIONS ---- //
    void trajectory_execution (std::vector<sensor_msgs::JointState> desired_trajectory);

    // ---- CONTROL FUNC ---- //
    void send_velocity_to_robot(Vector6d velocity);

    void stop_robot(void);

    void send_position_to_robot (Vector6d position);
    void wait_for_position_reached (Vector6d desired_position, double maximum_time);


    // ---- DEBUG ----//
    void csv_debug (std::vector<double> vector, std::string name);
    void csv_debug (std::vector<Vector6d> vector6d, std::string name);
    void csv_debug (std::string outString);
    void trajectory_debug_csv (std::vector<sensor_msgs::JointState> trajectory, std::string trajectory_name);
};



}
















#endif