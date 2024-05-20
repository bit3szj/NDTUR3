#include"ros/ros.h"
#include<std_msgs/String.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "control_move");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",1000);
    ros::Duration(1).sleep();

    ros::Rate loop_rate(25);

    while(ros::ok())
    {
        std_msgs::String ur_script_msgs;
        double time2move = 0.1;
        double acc=2;
        std::string move_msg;
        move_msg = "movel(p[-0.253124,-0.129071,0.391322,-0.11943,-3.00177,0.129966],0.1,0.05,0,0)\n";
        // move_msg = move_msg + "0.2" + ",";
        // move_msg = move_msg + double2string(command_pose[1]) + ",";
        // move_msg = move_msg + double2string(command_pose[2]) + ",";
        // move_msg = move_msg + double2string(command_pose[3]) + ",";
        // move_msg = move_msg + double2string(command_pose[4]) + ",";
        // move_msg = move_msg + double2string(command_pose[5]) + "]";
        // move_msg = move_msg + ",";
        // move_msg = move_msg + double2string(0.25) + ",";
        // move_msg = move_msg + double2string(0.5) + ")";
        // move_msg = move_msg + "\n";

        ur_script_msgs.data=move_msg;
        pub.publish(ur_script_msgs);
        loop_rate.sleep();
    }


    return 0;
}