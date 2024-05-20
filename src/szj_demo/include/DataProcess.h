#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <kdl/frames.hpp>
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
class DataProcess
{
private:
    /* data */
    std::vector<std::vector<double>> oriData_;
    ros::NodeHandle nh_;
    
    ros::Subscriber sub_pos_;
public:
    std::vector<std::vector<double>> quantData_;
    std::vector<std::vector<double>> rotvecData_;
    std::vector<double> nowCommand_;
    KDL::Vector nowKdlCommand_;
    std::vector<double> nowPos_;
    ros::Publisher pub_data_;
    int index = 0;
    bool pubFlag_ = false;

public:
    DataProcess();
    ~DataProcess();
    void readData(std::string filePath);
    void rpy2quant();
    void rpy2rotvec();
    void printData();
    void printQuantData();
    void pubPath();
    void nextPoint();
    bool calculateDiff();
    std::vector<double> quant2rotvec(std::vector<double> quantData);
private:
    void subPosCallback(geometry_msgs::PoseConstPtr msg);
    
};