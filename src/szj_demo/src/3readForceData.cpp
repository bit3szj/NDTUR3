// 引入必要的头文件
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "szj_demo/AdmStatus.h"
#include <geometry_msgs/WrenchStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <fstream>
#include "szj_demo/AdmStatus.h"

// 定义一个全局变量，用于存储txt文件的路径
std::string file_path = "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/forceSensor20240308.txt";
std::string file_path_dynamicData = "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/forceDynamic20240308.txt";
std::string file_path_filtData= "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/forceFilt20240308.txt";
std::string file_path_comData= "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/forceCom20240308.txt";
const int readNum = 1000;
int dataNum = 0;
int filtDataNum = 0;
int dynamicNum=0;
int comNum = 0;
// 定义一个回调函数，用于处理订阅的geometry::pose类型的数据
void poseCallback(const geometry_msgs::WrenchStamped& msg)
{
  // 打开txt文件，以追加模式写入
  std::ofstream ofs(file_path, std::ios::app);
  if (ofs.is_open())
  {
    if(dataNum < readNum){
        
        double x = msg.wrench.force.x;
        double y = msg.wrench.force.y;
        double z = msg.wrench.force.z;
        double tx = msg.wrench.torque.x;
        double ty = msg.wrench.torque.y;
        double tz = msg.wrench.torque.z;
        // 将x和y的值写入txt文件，用空格隔开，每一行记录一组数据
        ofs << x << " " << y << " "<< z<< " " << tx << " " << ty<< " "<< tz <<std::endl;
        // 关闭txt文件
        ofs.close();

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


void dynamicDataCallback(const szj_demo::AdmStatusConstPtr& msg)
{
  // 打开txt文件，以追加模式写入
  std::ofstream ofs_dynamicData(file_path_dynamicData, std::ios::app);
  if (ofs_dynamicData.is_open())
  {
    if(dynamicNum < readNum){
      // 获取position.x和position.y的值
      double forceTarget = msg->forceTarget;
      double forceNow = msg->forceNow;
      // double delta_B = msg->deltaB;
      double para_B = msg->paraB;
      double zdd = msg->zdd;
      double command_vel = msg->commandVel;
      // 将x和y的值写入txt文件，用空格隔开，每一行记录一组数据
      // ofs << forceTarget << " " << forceNow << " "<< delta_B << " " << para_B <<" " << zdd<<std::endl;
      ofs_dynamicData << forceTarget << " " << forceNow << " "<< zdd<< " " << para_B << " " << command_vel <<std::endl;
      // 关闭txt文件
      ofs_dynamicData.close();
      // 打印日志信息
      // ROS_INFO("Recorded : (%f, %f, %f, %F)", forceTarget, forceNow,zdd , para_B);
    }else{
      exit(0);
    }
    dynamicNum++;

  }
  else
  {
    // 如果打开文件失败，打印错误信息
    ROS_ERROR("Failed to open file: %s", file_path.c_str());
  }
}

void filtDataCallback(const geometry_msgs::WrenchStamped& msg)
{
    std::ofstream ofs_filtData(file_path_filtData, std::ios::app);

  // 打开txt文件，以追加模式写入
  if (ofs_filtData.is_open())
  {
    if(filtDataNum < readNum){
    double x= msg.wrench.force.x;
    double y= msg.wrench.force.y;
    double z= msg.wrench.force.z;
    double tx= msg.wrench.torque.x;
    double ty= msg.wrench.torque.y;
    double tz= msg.wrench.torque.z;
      // 将x和y的值写入txt文件，用空格隔开，每一行记录一组数据
      // ofs << forceTarget << " " << forceNow << " "<< delta_B << " " << para_B <<" " << zdd<<std::endl;
      ofs_filtData << x << " " << y << " "<< z<< " " << tx << " " << ty << " "<< tz<<std::endl;
      // 关闭txt文件
      ofs_filtData.close();
      // 打印日志信息
      // ROS_INFO("Recorded : (%f, %f, %f, %F)", forceTarget, forceNow,zdd , para_B);
    }else{
      exit(0);
    }
    filtDataNum++;

  }
  else
  {
    // 如果打开文件失败，打印错误信息
    ROS_ERROR("Failed to open file: %s", file_path.c_str());
  }
}

void comDataCallback(const geometry_msgs::WrenchStamped& msg)
{
  std::ofstream ofs_comData(file_path_comData, std::ios::app);

  // 打开txt文件，以追加模式写入
  if (ofs_comData.is_open())
  {
    if(comNum < 3000){
    double x= msg.wrench.force.x;
    double y= msg.wrench.force.y;
    double z= msg.wrench.force.z;
    double tx= msg.wrench.torque.x;
    double ty= msg.wrench.torque.y;
    double tz= msg.wrench.torque.z;
      // 将x和y的值写入txt文件，用空格隔开，每一行记录一组数据
      // ofs << forceTarget << " " << forceNow << " "<< delta_B << " " << para_B <<" " << zdd<<std::endl;
      ofs_comData << x << " " << y << " "<< z<< " " << tx << " " << ty << " "<< tz<<std::endl;
      // 关闭txt文件
      ofs_comData.close();
      // 打印日志信息
      // ROS_INFO("Recorded : (%f, %f, %f, %F)", forceTarget, forceNow,zdd , para_B);
    }else{
      exit(0);
    }
    comNum++;

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
  ros::init(argc, argv, "forceSensor_subscriber");
  // 创建ROS节点句柄
  ros::NodeHandle nh;
  // 从参数服务器获取txt文件的路径，如果没有设置，默认为/home/user/pose.txt
//   nh.param<std::string>("file_path", file_path, "/home/szj/myTask/test_link_UR/src/szj_demo/src/data/pose20231227.txt");
  // 创建一个订阅者，订阅名为"pose"的话题，注册回调函数poseCallback
  std::ofstream ofs(file_path, std::ios::app);
  std::ofstream ofs_dynamicData(file_path_dynamicData, std::ios::app);
  std::ofstream ofs_filtData(file_path_filtData, std::ios::app);
  std::ofstream ofs_comData(file_path_comData, std::ios::app);
  // ofs <<  "forceTarget " << "forceNow " << "delta_B " << "para_B" <<std::endl;
  ofs <<  "x " << "y " << "z " << "Tx " << "Ty "<< "Tz "<<std::endl;
  ofs_dynamicData <<  "x " << "y " << "z " << "Tx " << "Ty "<< "Tz "<<std::endl;
  ofs_filtData <<  "x " << "y " << "z " << "Tx " << "Ty "<< "Tz "<<std::endl;
  ofs_comData <<  "x " << "y " << "z " << "Tx " << "Ty "<< "Tz "<<std::endl;
  // ros::Subscriber sub = nh.subscribe("/szj/AdmStatusPub", 5, poseCallback);
  ros::Subscriber sub = nh.subscribe("/ethdaq_data", 1000, poseCallback);
  ros::Subscriber sub_dynamicData = nh.subscribe("/szj/admStatus", 5, dynamicDataCallback);
  ros::Subscriber sub_filtData = nh.subscribe("/compensate_wrench_base_filter", 1000, filtDataCallback);
  // ros::Subscriber sub_comData = nh.subscribe("/compensate_wrench_tool", 1000, comDataCallback);

  // 进入循环，等待回调函数被调用
  ros::spin();
  return 0;
}
