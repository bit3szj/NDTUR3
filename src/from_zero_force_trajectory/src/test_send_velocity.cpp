#include <std_msgs/Float64MultiArray.h>
#include <Eigen/Eigen>
#include <ros/ros.h>
#include <controller_manager_msgs/SwitchController.h>

using namespace Eigen;
typedef Matrix<double, 6, 1> Vector6d;

void send_velocity_to_robot (Vector6d velocity);
ros::Publisher pub_send_velocity;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_send_velocity");
    ros::NodeHandle nh;
    ros::Publisher pub_send_velocity = nh.advertise<std_msgs::Float64MultiArray>("/joint_group_vel_controller/command",1);
    ros::Duration(1).sleep();
    controller_manager_msgs::SwitchController switch_controller_srv;
    ros::ServiceClient switch_controller_client = nh.serviceClient<controller_manager_msgs::SwitchController>("/controller_manager/switch_controller");
    switch_controller_srv.request.stop_controllers.resize(1);
    switch_controller_srv.request.start_controllers.resize(1);

    //switch controller (velocity to position)
    switch_controller_srv.request.stop_controllers[0] = "joint_group_pos_controller";
    switch_controller_srv.request.start_controllers[0] = "joint_group_vel_controller";
    switch_controller_srv.request.strictness = switch_controller_srv.request.STRICT;
    // Call Switch Controller Service
    if (switch_controller_client.call(switch_controller_srv)) {
        
        ROS_WARN("Controller Changed from \"%s\" to \"%s\"", switch_controller_srv.request.stop_controllers[0].c_str(), switch_controller_srv.request.start_controllers[0].c_str());
        ros::Duration(1).sleep();
    } else {
        
        ROS_ERROR("Failed to Call Service: \"/controller_manager/switch_controller\"");
        ROS_ERROR("Failed to Switch Controllers");
    }
    

}

void send_velocity_to_robot (Vector6d velocity){
    std_msgs::Float64MultiArray msg;
    std::vector<double> velocity_vector(velocity.data(), velocity.data() + velocity.size());

    msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
    msg.layout.dim[0].size = velocity.size();
    msg.layout.dim[0].stride = 1;
    msg.layout.dim[0].label = "velocity";

    // copy in the data
    msg.data.clear();
    msg.data.insert(msg.data.end(), velocity_vector.begin(), velocity_vector.end());

    pub_send_velocity.publish(msg);
}