#include "ros/ros.h"
#include "geometry_msgs/WrenchStamped.h"
#include "std_msgs/String.h"
#include "Eigen/Eigen"
#include "Eigen/Geometry"
#include "Eigen/Core"
#include "cmath"
#include "std_msgs/Float64.h"
#include <Eigen/Dense>
#include "sensor_msgs/JointState.h"
#include <geometry_msgs/TwistStamped.h>


const double veloity_limit=1;
const double linear_mass=5;
const double linear_damp=10;
const double angular_mass=1;
const double angular_damp=2;
const double desireForce = 1;


class AdmittanceControlMassDrag
{
public:
    AdmittanceControlMassDrag()
    {

       
        wrench_base.resize(6);
        command_vel.resize(6);
        actual_vel.resize(6);
        command_pose.resize(6);
        actual_pose.resize(6);

        for(int i = 0; i < 6; i ++)
        {   
            command_vel[i]=0;
            wrench_base[i]=0;
            actual_vel[i]=0;       
            command_pose[i]=0;
            actual_pose[i]=0;
        }

        wrench_sub = nh.subscribe("/compensate_wrench_base_filter", 5, &AdmittanceControlMassDrag::WrenchsubCallback,this);    
        tool_velocity_sub=nh.subscribe("/szj/endVel",5,&AdmittanceControlMassDrag::ToolVelocitysubCallback,this);
        ur_pub = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",5);
        sub_toolPose = nh.subscribe("/szj/toolPose",5, &AdmittanceControlMassDrag::ToolPoseSubCallback,this);

        ros::Duration(1.0).sleep();

        ROS_INFO("robot starts to move");
        ros::Rate loop_rate(125);
        ros::Time last_time=ros::Time::now();
        ros::Time time_now;
        while (ros::ok())
        {
            time_now=ros::Time::now();
            // 导纳控制添加质量项和阻尼项进行拖动控制
            for(int i=0;i<2;i++){
                double xdd=(1/linear_mass)*(this->wrench_base[i]-linear_damp*actual_vel[i]);
                command_vel[i]=actual_vel[i]+xdd*(time_now-last_time).toSec();
                command_pose[i]=actual_pose[i]+command_vel[i]*(time_now-last_time).toSec();
            }    
            double err = this->wrench_base[2] - desireForce;
            double xddz=(1/linear_mass)*(err-linear_damp*actual_vel[2]);
            command_vel[2]=actual_vel[2]+xddz*(time_now-last_time).toSec();
            command_pose[2]=actual_pose[2]+command_vel[2]*(time_now-last_time).toSec();


            for(int i=3;i<6;i++){
                double xdd=(1/angular_mass)*(this->wrench_base[i]-angular_damp*actual_vel[i]);
                command_vel[i]=actual_vel[i]+xdd*(time_now-last_time).toSec();
                command_pose[i]=actual_pose[i]+command_vel[i]*(time_now-last_time).toSec();
            }
            
            last_time=time_now;
            // std::cout<<actual_vel[4]<<","<<command_vel[4]<<std::endl;
            urMove();
            
            std::cout<<std::endl;
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber wrench_sub;
    ros::Subscriber tool_velocity_sub;
    ros::Subscriber sub_toolPose;
    ros::Publisher ur_pub;

    std::vector<double> command_vel;
    std::vector<double> command_pose;
    std::vector<double> wrench_base;
    std::vector<double> actual_vel;
    std::vector<double> actual_pose;
    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);
    void ToolVelocitysubCallback(const geometry_msgs::Twist& msg);
    void ToolPoseSubCallback(const geometry_msgs::TwistStamped& msg);
    
    void limitVelocity(std::vector<double> &velocity);
    void urMove();
    std::string double2string(double input);
};


//机器人末端速度回调函数
void AdmittanceControlMassDrag::ToolVelocitysubCallback(const geometry_msgs::Twist& msg)
{
    actual_vel[0]=msg.linear.x;
    actual_vel[1]=msg.linear.y;
    actual_vel[2]=msg.linear.z;
    actual_vel[3]=msg.angular.x;
    actual_vel[4]=msg.angular.y;
    actual_vel[5]=msg.angular.z;
}
//the position of robot
void AdmittanceControlMassDrag::ToolPoseSubCallback(const geometry_msgs::TwistStamped& msg)
{
    actual_pose[0]=msg.twist.linear.x;
    actual_pose[1]=msg.twist.linear.y;
    actual_pose[2]=msg.twist.linear.z;
    actual_pose[3]=msg.twist.angular.x;
    actual_pose[4]=msg.twist.angular.y;
    actual_pose[5]=msg.twist.angular.z;
}

//力矩传感器回调函数
void AdmittanceControlMassDrag::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = -msg.wrench.force.x;
    wrench_base[1] = -msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = -msg.wrench.torque.x;
    wrench_base[4] = -msg.wrench.torque.y;
    wrench_base[5] = msg.wrench.torque.z;
}


//浮点数转string
std::string AdmittanceControlMassDrag::double2string(double input)
{
    std::string string_temp;
    std::stringstream stream;
    stream<<input;
    string_temp = stream.str();
    return string_temp;
}


//限制速度大小
void AdmittanceControlMassDrag::limitVelocity(std::vector<double> &velocity){
    for(int i=0;i<velocity.size();i++){
        if(fabs(velocity[i])<0.001) velocity[i]=0;
        if(velocity[i]>veloity_limit) velocity[i]=veloity_limit;
        else if(velocity[i]<-veloity_limit) velocity[i]=-veloity_limit;
        else ;
    }
}


//UR机器人回调函数
void AdmittanceControlMassDrag::urMove()
{
    this->limitVelocity(command_vel);
    std_msgs::String ur_script_msgs;
    double acc=0.5;
    double velocity = 0.2;
    std::string move_msg;
    move_msg = "movel(p[";
    move_msg = move_msg + double2string(command_pose[0]) + ",";
    move_msg = move_msg + double2string(command_pose[1]) + ",";
    move_msg = move_msg + double2string(command_pose[2]) + ",";
    move_msg = move_msg + double2string(command_pose[3]) + ",";
    move_msg = move_msg + double2string(command_pose[4]) + ",";
    move_msg = move_msg + double2string(command_pose[5]) + "]";
    move_msg = move_msg + ",";
    move_msg = move_msg + double2string(acc) + ",";
    move_msg = move_msg + double2string(velocity) + ")";
    move_msg = move_msg + "\n";
    ur_script_msgs.data=move_msg;
    ur_pub.publish(ur_script_msgs);
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "AdmittanceControlMassDragUR");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    AdmittanceControlMassDrag ad;
    ros::waitForShutdown();
    return 0;
}