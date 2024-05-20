
#include <ros/ros.h>
#include <controller_manager_msgs/SwitchController.h>






int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_switch_controller");
    ros::NodeHandle nh;
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
    ros::Duration(5).sleep();

}