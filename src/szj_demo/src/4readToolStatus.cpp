#include "ros/ros.h"
#include "szj_demo/toolStatus.h"
#include <fstream>
#include <geometry_msgs/WrenchStamped.h>
int countii = 0;

void toolBack(const szj_demo::toolStatus& msg) {
    if (countii < 3000) {
        std::string filename = "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/toolStatus.txt";
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {

            file <<  msg.linearX << " " << msg.linearY << " " << msg.linearZ << " "<< msg.angularX<< " " << msg.angularY<< " "<< msg.angularZ<< std::endl;            // 记录力矩向量
            // file <<  msg.velLinearX << " " << msg.velLinearY << " " << msg.velLinearZ << " "<< msg.velAngularX<< " " << msg.velAngularY<< " "<< msg.velAngularZ<< std::endl;            // 记录力矩向量
            countii++;
            file.close();
            ROS_INFO("run1 ````");
        }
    }
}
int counti = {0};

void wrenchStampedCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
    if (counti < 3000) {
        std::string filenamei = "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/zeroForceZ.txt";
        std::ofstream file(filenamei, std::ios::app);
        if (file.is_open()) {
            // 记录时间戳
            file << msg->header.stamp.sec << " " << msg->header.stamp.nsec << " ";
            // 记录参考坐标系
            file << msg->header.frame_id << " ";
            // 记录力向量
            file << msg->wrench.force.x << " " << msg->wrench.force.y << " " << msg->wrench.force.z << " ";
            // 记录力矩向量
            file << msg->wrench.torque.x << " " << msg->wrench.torque.y << " " << msg->wrench.torque.z << std::endl;
            counti++;
            file.close();
            ROS_INFO("run ````");
        }
    }
}
int main(int argc, char** argv) {
    // 初始化ROS节点
    ros::init(argc, argv, "readTool");

    // 创建ROS节点句柄
    ros::NodeHandle nh;

    // 订阅三个话题
    ros::Subscriber sub1 = nh.subscribe("/szj/toolStatus", 1000, toolBack);
    ros::Subscriber sub2 = nh.subscribe("/compensate_wrench_base", 1000, wrenchStampedCallback);

    // 循环，直到所有消息都被记录
    ros::spin();

    return 0;
}