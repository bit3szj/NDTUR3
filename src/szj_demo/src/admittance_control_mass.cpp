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
#include "szj_demo/toolStatus.h"


const double veloity_limit=1;
double linear_mass=30;
double linear_damp=100;
const double angular_mass=1;
const double angular_damp=2;
const double desireForce = 0;


class AdmittanceControlMassDrag
{
public:
    AdmittanceControlMassDrag()
    {

       
        wrench_base.resize(6);
        command_vel.resize(6);
        actual_vel.resize(6);

        for(int i = 0; i < 6; i ++)
        {   
            command_vel[i]=0;
            wrench_base[i]=0;
            actual_vel[i]=0;       
        }

        wrench_sub = nh.subscribe("/compensate_wrench_base_filter", 5, &AdmittanceControlMassDrag::WrenchsubCallback,this);    
        // tool_velocity_sub=nh.subscribe("/szj/endVel",5,&AdmittanceControlMassDrag::ToolVelocitysubCallback,this);
        ur_pub = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",5);
        sub_toolPose = nh.subscribe("/szj/toolStatus", 5, &AdmittanceControlMassDrag::ToolPoseCallback, this);
        nh.setParam("global_paraM", linear_mass);
        nh.setParam("global_paraB", linear_damp);
        ros::Duration(1.0).sleep();

        ROS_INFO("robot starts to move");
        ros::Rate loop_rate(50);
        ros::Time last_time=ros::Time::now();
        ros::Time time_now;
        while (ros::ok())
        {
            time_now=ros::Time::now();
            nh.getParam("global_paraM", linear_mass);
            nh.getParam("global_paraM", linear_damp);
            // 导纳控制添加质量项和阻尼项进行拖动控制
            for(int i=0;i<2;i++){
                double xdd=(1/linear_mass)*(this->wrench_base[i]-linear_damp*actual_vel[i]);
                command_vel[i]=actual_vel[i]+xdd*(time_now-last_time).toSec();
            }    
            double err = this->wrench_base[2] - desireForce;
            double xddz=(1/linear_mass)*(err-linear_damp*actual_vel[2]);
            command_vel[2]=actual_vel[2]+xddz*(time_now-last_time).toSec();


            for(int i=3;i<6;i++){
                double xdd=(1/angular_mass)*(this->wrench_base[i]-angular_damp*actual_vel[i]);
                command_vel[i]=actual_vel[i]+xdd*(time_now-last_time).toSec();
            }
            
            last_time=time_now;
            // std::cout<<actual_vel[4]<<","<<command_vel[4]<<std::endl;
            urMove();
            
            // std::cout<<std::endl;
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber wrench_sub;
    ros::Subscriber tool_velocity_sub;
    ros::Publisher ur_pub;
    ros::Subscriber sub_toolPose;
    std::vector<double> command_vel;
    std::vector<double> wrench_base;
    std::vector<double> actual_vel;
    // double m_M;

    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);
    void ToolVelocitysubCallback(const geometry_msgs::Twist& msg);
    void ToolPoseCallback(const szj_demo::toolStatus& msg);

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
void AdmittanceControlMassDrag::ToolPoseCallback(const szj_demo::toolStatus& msg){
    // actual_pos[0] = msg.linearX;
    // actual_pos[1] = msg.linearY;
    // actual_pos[2] = msg.linearZ;
    // actual_pos[3] = msg.angularX;
    // actual_pos[4] = msg.angularY;
    // actual_pos[5] = msg.angularZ;
    
    actual_vel[0] = msg.velLinearX;
    actual_vel[1] = msg.velLinearY;
    actual_vel[2] = msg.velLinearZ;
    actual_vel[3] = msg.velAngularX;
    actual_vel[4] = msg.velAngularY;
    actual_vel[5] = msg.velAngularZ;
}

//力矩传感器回调函数
void AdmittanceControlMassDrag::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = msg.wrench.force.x;
    wrench_base[1] = msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = msg.wrench.torque.x;
    wrench_base[4] = msg.wrench.torque.y;
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
    double time2move = 0.2;
    double acc=0.5;
    std::string move_msg;
    move_msg = "speedl([";
    move_msg = move_msg + double2string(command_vel[0]) + ",";
    move_msg = move_msg + double2string(command_vel[1]) + ",";
    move_msg = move_msg + double2string(command_vel[2]) + ",";
    move_msg = move_msg + double2string(command_vel[3]) + ",";
    move_msg = move_msg + double2string(command_vel[4]) + ",";
    move_msg = move_msg + double2string(command_vel[5]) + "]";
    move_msg = move_msg + ",";
    move_msg = move_msg + double2string(acc) + ",";
    move_msg = move_msg + double2string(time2move) + ")";
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