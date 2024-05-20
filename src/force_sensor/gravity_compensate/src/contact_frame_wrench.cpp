////////////////////////////这个函数的意思应该是，用户坐标系frame下的力，即沿z轴平移了89mm的坐标系下的力，我这里用不到///////////////////////////////
//////////////////////////////////////////////////////作为一个思路可以留着/////////////////////////////////////////////////////////////////////
//////////////////////////这里可能是，以tool0为力传感器的原点进行了重力补偿，然后在根据力传感器坐标进行了修正，为一个猜想不知道是否可行////////////////
//////////////////////////////////////////后续把这里搞懂以后，查一下这个方法有没有人写专利/////////////////////////////////////////////////////////
#include <ros/ros.h>
#include <geometry_msgs/WrenchStamped.h>


ros::Publisher wrench_pub;
const double z=0.089; //超声探头、力传感器法兰，和支架的总长度

void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    geometry_msgs::WrenchStamped pub_msg;

    pub_msg.wrench.force.x=msg.wrench.force.x;
    pub_msg.wrench.force.y=msg.wrench.force.y;
    pub_msg.wrench.force.z=msg.wrench.force.z;
    pub_msg.wrench.torque.x=msg.wrench.torque.x+msg.wrench.force.y*z;
    pub_msg.wrench.torque.y=msg.wrench.torque.y-msg.wrench.force.x*z;
    pub_msg.wrench.torque.z=msg.wrench.torque.z;
    pub_msg.header.frame_id="tool2";
    pub_msg.header.stamp=ros::Time::now();
    wrench_pub.publish(pub_msg);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "contact_frame_wrench");
    ros::NodeHandle nh;

    wrench_pub = nh.advertise<geometry_msgs::WrenchStamped>("/compensate_wrench_contact", 1000);
    ros::Subscriber wrench_sub = nh.subscribe("/compensate_wrench_tool", 1000, WrenchsubCallback);

    ros::spin();
    return 0;
}
