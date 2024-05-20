#include "ros/ros.h"
#include "geometry_msgs/WrenchStamped.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/String.h"
#include "Eigen/Eigen"
#include "Eigen/Geometry"
#include "Eigen/Core"
#include "cmath"
#include "std_msgs/Float64.h"
#include "Eigen/Dense"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/Pose.h"
#include <tf/transform_datatypes.h>
#include "geometry_msgs/Twist.h"


const double veloity_limit=0.2;
// const double linear_damp=0.0075;
const double linear_damp=0.005;

const double angular_damp=0.5;

const double desireForce = 3;

class AdmittanceControlDrag
{
public:
    AdmittanceControlDrag()
    {
        wrench_base.resize(6);
        command_vel.resize(6);

        for(int i = 0; i < 6; i ++)
        {   
            command_vel[i]=0;
        }
      
        wrench_sub = nh.subscribe("/compensate_wrench_base_filter", 1000, &AdmittanceControlDrag::WrenchsubCallback,this);
        ur_pub = nh.advertise<geometry_msgs::Twist>("/szj/corVel",5);
        // sub_endPos = nh.subscribe("/szj/endPos", 5, &AdmittanceControlDrag::endPoseCallback, this);

        ros::Duration(1.0).sleep();
        ROS_INFO("robot starts to move");

        ros::Rate loop_rate(125);
        while (ros::ok())
        {
            // double err = this->wrench_base[2] - desireForce;
            //导纳控制仅添加阻尼项进行拖动控制
            for(int i=0;i<3;i++){
                command_vel[i]=linear_damp*this->wrench_base[i];
            }
            // command_vel[2]+=linear_damp*err;
            for(int i=3;i<6;i++){
                command_vel[i]=angular_damp*this->wrench_base[i];
            }
            urMove();
            for(int i=0;i<6;i++) std::cout<<command_vel[i]<<"#   ";
            std::cout<<std::endl;
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;

    ros::Subscriber wrench_sub; 
    ros::Publisher ur_pub;
    // ros::Subscriber sub_endPos;

    std::vector<double> command_vel;
    std::vector<double> command_pos;
    std::vector<double> wrench_base;

    geometry_msgs::Twist pubMsg_vel;
    



    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);
    // void endPoseCallback(const geometry_msgs::PoseConstPtr msg);
    void limitVelocity(std::vector<double> &velocity);
    void urMove();

};



//基坐标系力矩信息回调函数
void AdmittanceControlDrag::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = -msg.wrench.force.x;
    wrench_base[1] = -msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = -msg.wrench.torque.x;
    wrench_base[4] = -msg.wrench.torque.y;
    wrench_base[5] = msg.wrench.torque.z;
}




//限制速度大小
void AdmittanceControlDrag::limitVelocity(std::vector<double> &velocity){
    for(int i=0;i<velocity.size();i++){
        if(fabs(velocity[i])<1e-3) velocity[i]=0;
        if(velocity[i]>veloity_limit) velocity[i]=veloity_limit;
        else if(velocity[i]<-veloity_limit) velocity[i]=-veloity_limit;
        else ;
    }
}



//UR机器人回调函数
void AdmittanceControlDrag::urMove()
{
    pubMsg_vel.linear.x = command_vel[0];
    pubMsg_vel.linear.y = command_vel[1];
    pubMsg_vel.linear.z = command_vel[2];
    pubMsg_vel.angular.x = command_vel[3];
    pubMsg_vel.angular.y = command_vel[4];
    pubMsg_vel.angular.z = command_vel[5];
    ur_pub.publish(pubMsg_vel);
}



int main(int argc, char *argv[])
{
    ros::init(argc, argv, "AdmittanceControlDragUR");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    AdmittanceControlDrag adg;
    ros::waitForShutdown();
    return 0;
}