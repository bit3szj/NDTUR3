#include "ros/ros.h"
#include "geometry_msgs/WrenchStamped.h"
#include "std_msgs/String.h"
#include "Eigen/Eigen"
#include "Eigen/Geometry"
#include "Eigen/Core"
#include "cmath"
#include "std_msgs/Float64.h"
#include "Eigen/Dense"
#include "sensor_msgs/JointState.h"
#include "szj_controller/pointData.h"
#include <sstream>


const double veloity_limit=1;
const double linear_damp=0.0075;
const double angular_damp=0.5;

class AdmPubVel
{
public:
    AdmPubVel()
    {
        wrench_base.resize(6);

        for(int i = 0; i < 6; i ++)
        {   
            wrench_base[i]=0;
        }
      
        wrench_sub = nh.subscribe("/compensate_wrench_base_filter", 1, &AdmPubVel::WrenchsubCallback,this);
        pub_vel = nh.advertise<szj_controller::pointData>("/pointRead",1);

        ros::Duration(1.0).sleep();
        ROS_INFO("robot starts to move");

        ros::Rate loop_rate(25);
        while (ros::ok())
        {
            //导纳控制仅添加阻尼项进行拖动控制
            data_pubVel.x = linear_damp*this->wrench_base[0];
            data_pubVel.y = linear_damp*this->wrench_base[1];
            data_pubVel.z = linear_damp*this->wrench_base[2];
            data_pubVel.rx = angular_damp*this->wrench_base[3];
            data_pubVel.ry = angular_damp*this->wrench_base[4];
            data_pubVel.rz = angular_damp*this->wrench_base[5];
            pub_vel.publish(data_pubVel);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;

    ros::Subscriber wrench_sub; 
    ros::Publisher pub_vel;
    szj_controller::pointData data_pubVel;

    std::vector<double> wrench_base;

    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);
};



//基坐标系力矩信息回调函数
void AdmPubVel::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = msg.wrench.force.x;
    wrench_base[1] = msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = msg.wrench.torque.x;
    wrench_base[4] = msg.wrench.torque.y;
    wrench_base[5] = msg.wrench.torque.z;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "admPubVel");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    AdmPubVel m_admPubVel;
    ros::waitForShutdown();
    return 0;
}