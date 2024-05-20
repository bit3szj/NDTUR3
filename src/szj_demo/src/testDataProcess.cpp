// #include "../include/DataProcess.h"
#include "DataProcess.cpp"


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pubPath");
    DataProcess m_dataProcess;
    m_dataProcess.readData("/home/szj/myTask/test_link_UR/src/szj_demo/src/data/pathData.txt");
    std::cout<< "print original data : " << std::endl;
    m_dataProcess.printData();
    m_dataProcess.rpy2quant();
    std::cout<< "print QuantData : " << std::endl;
    m_dataProcess.printQuantData();
    ros::Rate loopRate(10);
    // m_dataProcess.nextPoint();
    m_dataProcess.pubPath();
    ros::Duration(0.1).sleep();
    while (ros::ok())
    {
        if(m_dataProcess.calculateDiff()){
            ROS_INFO("change data");
            m_dataProcess.nextPoint();
        }
        else{
            m_dataProcess.pubPath();
            ROS_INFO("pub position");
        }
        ros::spinOnce();
        loopRate.sleep();
    }
    
    return 0;
}