#include "ros/ros.h"
#include "std_msgs/String.h"
#include "hardware_interface/hardware_interface.h"
#include<iostream>
//使用函数urmove发送指令到UR

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "test_script");
    //TestScript my_test;
    //my_test.my_init();

    ros::NodeHandle nh;
    //ros::Rate loop_rate(50);
    ros::Publisher ur_pub = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",1);
    ros::Duration(1).sleep();

    if(ros::ok())
    {
            //urmove(command_pose, ur_pub);
            // std::string command = "movel(p[-0.143,-0.435,0.200,0.001,-3.166,-0.04],a=0.5,v=0.3)";
            std_msgs::String send_command;
            // send_command.data = "movel(p[-0.143,-0.435,0.200,0.001,-3.166,-0.04],a=0.5,v=0.3)";
            send_command.data = "movel(p[-0.143,-0.435,0.200,-0.00142,3.11635,0.03989],a=0.5,v=0.3)";
            ur_pub.publish(send_command);
            ros::Duration(2).sleep();
            ROS_INFO("SEND");
            std::string command = send_command.data;
            //std::cout<<"the gravity and zero point of sensor is\n"<<std::endl;
            std::cout<<command<<std::endl;
    }
    return 0;

}

