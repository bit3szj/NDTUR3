// 引入必要的头文件
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "szj_demo/AdmStatus.h"
#include <fstream>

// 定义一个全局变量，用于存储txt文件的路径
std::string file_path = "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/pose20240307.txt";
int dataNum = 0;
// 定义一个回调函数，用于处理订阅的geometry::pose类型的数据
void poseCallback(const szj_demo::AdmStatusConstPtr& msg)
{
  // 打开txt文件，以追加模式写入
  std::ofstream ofs(file_path, std::ios::app);
  if (ofs.is_open())
  {
    if(dataNum < 3000){
      // 获取position.x和position.y的值
      double forceTarget = msg->forceTarget;
      double forceNow = msg->forceNow;
      // double delta_B = msg->deltaB;
      double para_B = msg->paraB;
      double zdd = msg->zdd;
      double command_vel = msg->commandVel;
      // 将x和y的值写入txt文件，用空格隔开，每一行记录一组数据
      // ofs << forceTarget << " " << forceNow << " "<< delta_B << " " << para_B <<" " << zdd<<std::endl;
      ofs << forceTarget << " " << forceNow << " "<< zdd<< " " << para_B << " " << command_vel <<std::endl;
      // 关闭txt文件
      ofs.close();
      // 打印日志信息
      ROS_INFO("Recorded : (%f, %f, %f, %F)", forceTarget, forceNow,zdd , para_B);
    }else{
      exit(0);
    }
    dataNum++;

  }
  else
  {
    // 如果打开文件失败，打印错误信息
    ROS_ERROR("Failed to open file: %s", file_path.c_str());
  }
}

int main(int argc, char **argv)
{
  // 初始化ROS节点
  ros::init(argc, argv, "pose_subscriber");
  // 创建ROS节点句柄
  ros::NodeHandle nh;
  // 从参数服务器获取txt文件的路径，如果没有设置，默认为/home/user/pose.txt
//   nh.param<std::string>("file_path", file_path, "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/pose20231227.txt");
  // 创建一个订阅者，订阅名为"pose"的话题，注册回调函数poseCallback
  std::ofstream ofs(file_path, std::ios::app);
  // ofs <<  "forceTarget " << "forceNow " << "delta_B " << "para_B" <<std::endl;
  ofs <<  "forceTarget " << "forceNow " << "zdd " << "para_B " << "commandVel"<<std::endl;
  // ros::Subscriber sub = nh.subscribe("/szj/AdmStatusPub", 5, poseCallback);
  ros::Subscriber sub = nh.subscribe("/szj/AdmStatusPub", 5, poseCallback);
  // 进入循环，等待回调函数被调用
  ros::spin();
  return 0;
}
