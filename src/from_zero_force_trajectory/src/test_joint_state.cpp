#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

sensor_msgs::JointState joint_state;
std::vector<double> joint_position;
std::vector<double> joint_velocity;
void joint_states_callback(const sensor_msgs::JointStateConstPtr &msg){
    ROS_INFO("start callback");
    joint_state = *msg;
    ROS_INFO("get pointer");
    // ROS_INFO("joint_state.position.size() = %ld", joint_state.position.size());
    joint_position.resize(joint_state.position.size());
    joint_velocity.resize(joint_state.velocity.size());
    for (unsigned int i = 0; i < joint_state.position.size(); i++) {
        // joint_position.push_back();
        joint_position[i] = joint_state.position[i];
        ROS_INFO("get position partial");
    }
    ROS_INFO("get position");
    for (unsigned int i = 0; i < joint_state.velocity.size(); i++) {
        joint_velocity[i] = joint_state.velocity[i];
    }
    ROS_INFO("get velocity");
    
    ROS_INFO("joint position : %.2f, %.2f, %.2f, %.2f, %.2f, %.2f", joint_position[0], joint_position[1], joint_position[2], joint_position[3], joint_position[4], joint_position[5]);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_joint_state_node");
    ros::NodeHandle nh;
    ros::Subscriber sub_joint_state = nh.subscribe<sensor_msgs::JointState>("/joint_states",1,joint_states_callback);
    ros::Duration(1).sleep();


    ros::Rate loop_rate(1);
    ROS_INFO("init sucssess");
    while(ros::ok()){
        ROS_INFO("start output");
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}