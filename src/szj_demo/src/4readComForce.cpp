#include <ros/ros.h>
#include <fstream>
#include <geometry_msgs/WrenchStamped.h>
//读取力原始数据，补偿数据，和设置阈值之后的数据
// 全局变量，用于记录每个话题的消息数量
int count[3] = {0};

// 回调函数模板，用于处理订阅的话题消息
template<int Index>
void wrenchStampedCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg) {
    if (count[Index] < 19000) {
        std::string filename = "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/topic" + std::to_string(Index) + "_data.txt";
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            // 记录时间戳
            file << msg->header.stamp.sec << " " << msg->header.stamp.nsec << " ";
            // 记录参考坐标系
            file << msg->header.frame_id << " ";
            // 记录力向量
            file << msg->wrench.force.x << " " << msg->wrench.force.y << " " << msg->wrench.force.z << " ";
            // 记录力矩向量
            file << msg->wrench.torque.x << " " << msg->wrench.torque.y << " " << msg->wrench.torque.z << std::endl;
            count[Index]++;
            file.close();
            ROS_INFO("run ````");
        }
    }
}

int main(int argc, char** argv) {
    // 初始化ROS节点
    ros::init(argc, argv, "wrench_recorder");

    // 创建ROS节点句柄
    ros::NodeHandle nh;

    // 订阅三个话题
    ros::Subscriber sub1 = nh.subscribe<geometry_msgs::WrenchStamped>("/ethdaq_data", 1000, wrenchStampedCallback<1>);
    ros::Subscriber sub2 = nh.subscribe<geometry_msgs::WrenchStamped>("/compensate_wrench_base", 1000, wrenchStampedCallback<2>);
    ros::Subscriber sub3 = nh.subscribe<geometry_msgs::WrenchStamped>("/compensate_wrench_base_filter", 1000, wrenchStampedCallback<3>);

    // 循环，直到所有消息都被记录
    ros::spin();

    return 0;
}