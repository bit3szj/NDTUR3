#include "from_zero_force_trajectory/admittance_controller.h"

namespace from_zero
{



from_zero::admittance_control::admittance_control(
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
    std::vector<double> maximum_acceleration):

    nh(n), loop_rate(ros_rate), mass_matrix(mass_model_matrix.data()), damping_matrix(damping_model_matrix.data()),
    joint_lim(joint_limits.data()), max_vel(maximum_velocity.data()), max_acc(maximum_acceleration.data()){
        
    }


void from_zero::admittance_control::send_velocity_to_robot(Vector6d velocity){
    
    std_msgs::Float64MultiArray msg;

    std::vector<double> velocity_vector(velocity.data(), velocity.data() + velocity.size());

    msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
    msg.layout.dim[0].size = velocity.size();
    msg.layout.dim[0].stride = 1;
    msg.layout.dim[0].label = "velocity";

    // copy in the data
    msg.data.clear();
    msg.data.insert(msg.data.end(), velocity_vector.begin(), velocity_vector.end());

    joint_group_vel_controller_publisher.publish(msg);
}


void from_zero::admittance_control::stop_robot(void){
    Vector6d stop;
    stop.setZero();

    send_velocity_to_robot(stop);
}

void from_zero::admittance_control::wait_for_position_reached (Vector6d desired_position, double maximum_time) {

    joint_state_callback = false;

    // Wait for Joint State Callback
    while (ros::ok() && !joint_state_callback) {ros::spinOnce();}

    Vector6d current_position(joint_state.position.data());

    ros::Time start_time = ros::Time::now();

    // Wait until desired_position and current_position are equal with a little tolerance
    while (ros::ok() && (Eigen::abs(desired_position.array() - current_position.array()) > 0.0001).all() && (ros::Time::now() - start_time).toSec() < maximum_time) {

        ros::spinOnce();
        current_position = Vector6d(joint_state.position.data());
        ROS_INFO_ONCE("Wait for Starting Position...");
    }

}

void from_zero::admittance_control::send_position_to_robot(Vector6d position){
    
    switch_controller_srv.request.stop_controllers.resize(1);
    switch_controller_srv.request.stop_controllers.resize(1);

    //switch controller velocity to position
    switch_controller_srv.request.stop_controllers[0] = "joint_group_vel_controller";
    switch_controller_srv.request.start_controllers[0] = "scaled_pos_joint_traj_controller";
    switch_controller_srv.request.strictness = switch_controller_srv.request.STRICT;
    //STRICT 表示如果出现任何问题（控制器名称无效、控制器启动失败等），切换将失败。 BEST_EFFORT 表示即使控制器出现问题，服务仍会尝试启动/停止剩余的控制器。

    // Call Switch Controller Service
    if (switch_controller_client.call(switch_controller_srv)) {
        
        ROS_WARN("Controller Changed from \"%s\" to \"%s\"", switch_controller_srv.request.stop_controllers[0].c_str(), switch_controller_srv.request.start_controllers[0].c_str());
        ros::Duration(1).sleep();

    } else {
        
        ROS_ERROR("Failed to Call Service: \"/controller_manager/switch_controller\"");
        ROS_ERROR("Failed to Switch Controllers");
    }

    trajectory_msgs::JointTrajectory trajectory_temp;
    double execution_time = 10;

    trajectory_temp.joint_names = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};
    trajectory_temp.points.resize(1);
    trajectory_temp.points[0].positions = {position[0], position[1], position[2], position[3], position[4], position[5]};
    trajectory_temp.points[0].time_from_start = ros::Duration(execution_time);

    // Publish Trajectory Position
    joint_trajectory_publisher.publish(trajectory_temp);
    ROS_INFO("GoTo Initial Position in %.2fs: %.2f %.2f %.2f %.2f %.2f %.2f", execution_time, position[0], position[1], position[2], position[3], position[4], position[5]);



}

void from_zero::admittance_control::trajectory_execution(std::vector<sensor_msgs::JointState> desired_trajectory){
    // stop the robot if moving
    stop_robot();

    // compute trajectory time
    const double T = (desired_trajectory[desired_trajectory.size() - 1].header.stamp - desired_trajectory[0].header.stamp).toSec();

    //compute trajectory scaling

    //move robot to point 0(position controller)
    Vector6d starting_position(desired_trajectory[0].position.data());
    // send_position;
}

//-------------------------------------------------------- MAIN --------------------------------------------------------//

void from_zero::admittance_control::spinner(void){
    ros::spinOnce();

    trajectory_execution(desired_trajectory);
    loop_rate.sleep();
}

}