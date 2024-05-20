#include "ros/ros.h"
#include "geometry_msgs/WrenchStamped.h"
#include "std_msgs/String.h"
#include "Eigen/Eigen"
#include "Eigen/Geometry"
#include "Eigen/Core"
#include "cmath"
#include "std_msgs/Float64.h"
#include "szj_demo/toolStatus.h"
#include <Eigen/Dense>
#include "sensor_msgs/JointState.h"
#include <geometry_msgs/TwistStamped.h>
#include "geometry_msgs/Pose.h"
#include "szj_demo/AdmStatus.h"

// 一阶IIR低通滤波器
class LowPassFilter {
private:
  // 滤波器的系数
  double a0, a1, b0, b1;
  // 滤波器的状态
  double x1, y1;
  double fc=200, fs=50;
public:
  // 构造函数，根据截止频率和采样频率计算滤波器的系数
  LowPassFilter() {
    // 计算归一化截止频率
    double wc = 2 * M_PI * fc / fs;
    // 计算滤波器的系数
    a0 = 1 + sin(wc) / cos(wc);
    a1 = -1;
    b0 = (1 + cos(wc)) / 2;
    b1 = b0;
    // 初始化滤波器的状态
    x1 = 0;
    y1 = 0;
  }
  // 滤波函数，对输入的数据进行低通滤波，返回滤波后的数据
  double low_pass_filter(double x) {
    // 计算滤波后的数据
    double y = b0 * x + b1 * x1 - a1 * y1;
    // 更新滤波器的状态
    x1 = x;
    y1 = y;
    // 返回滤波后的数据
    return y;
  }
};

// 一阶IIR高通滤波器
class HighPassFilter {
private:
  // 滤波器的系数
  double a0, a1, b0, b1;
  // 滤波器的状态
  double x1, y1, fc=50, fs=50;
public:
  // 构造函数，根据截止频率和采样频率计算滤波器的系数
  HighPassFilter()
   
  {
    // 计算归一化截止频率
    double wc = 2 * M_PI * fc / fs;
    // 计算滤波器的系数
    a0 = 1 + sin(wc) / cos(wc);
    a1 = -1;
    b0 = (1 - cos(wc)) / 2;
    b1 = -b0;
    // 初始化滤波器的状态
    x1 = 0;
    y1 = 0;
  }
  // 滤波函数，对输入的数据进行高通滤波，返回滤波后的数据
  double high_pass_filter(double x) {
    // 计算滤波后的数据
    double y = b0 * x + b1 * x1 - a1 * y1;
    // 更新滤波器的状态
    x1 = x;
    y1 = y;
    // 返回滤波后的数据
    return y;
  }
};





class variableAdmCtrl
{
public:
    variableAdmCtrl()
    {
        wrench_base.resize(6);
        command_vel.resize(6);
        actual_vel.resize(6);
        actual_pos.resize(6);
        command_pos.resize(6);
        phi = 0;
        for(int i = 0; i <6; ++i){
            wrench_base[i] = 0;
            command_vel[i] = 0;
            actual_vel[i] = 0;
            actual_pos[i] = 0;
            command_pos[i] = 0;
        }

        wrench_sub = nh.subscribe("/compensate_wrench_base_filter", 5, &variableAdmCtrl::WrenchsubCallback,this);    
        // tool_velocity_sub=nh.subscribe("/szj/endVel",5,&variableAdmCtrl::ToolVelocitysubCallback,this);
        ur_pub = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",5);
        pub_admStatus = nh.advertise<szj_demo::AdmStatus>("/szj/AdmStatusPub",5);
        // sub_toolPose = nh.subscribe("/szj/toolPose", 5, &variableAdmCtrl::ToolPoseCallback, this);
        sub_toolPose = nh.subscribe("/szj/toolStatus", 5, &variableAdmCtrl::ToolPoseCallback, this);
        // nh.setParam("glbLinearMass",linear_mass);
        // nh.setParam("glbLinearDamp",linear_damp);
        // nh.setParam("glbForceTarget",desireFz);
        // nh.setParam("glbParaBp",para_Bp);
        // nh.setParam("glbParaBv",para_Bv);

        ros::Duration(1.0).sleep();
        for(int i = 0; i < 6; ++i){
            command_pos[i] = actual_pos[i];
        }
        this->urMoveL();
        ros::Duration(1.0).sleep();

        ROS_INFO("robot starts to move");
        int loopFlag = 0;
        int directionFlag = 0;
        double lastErr = 0;
        ros::Rate loop_rate(75);
        ros::Time last_time=ros::Time::now();
        ros::Time time_now;
        while (ros::ok())
        {
            nh.getParam("glbLinearMass",linear_mass);
            nh.getParam("glbLinearDamp",linear_damp);
            nh.getParam("glbForceTarget",desireFz);
            nh.getParam("glbParaBp",para_Bp);
            nh.getParam("glbParaBv",para_Bv);
            time_now=ros::Time::now();
            double actualFz = this->wrench_base[2];
            ROS_INFO("actual Force = %f", wrench_base[2]);
            double vel_now = actual_vel[2];
            double fzErr = actualFz - desireFz;
            fzErr_diff = (fzErr - fzErr_last)/(time_now - last_time).toSec();
            
            delta_B = -(para_Bp * fzErr + para_Bv * fzErr_diff) / (vel_now - 0);
            if(delta_B > deltaB_limit)
                delta_B = deltaB_limit;
            else if(delta_B < -deltaB_limit)
                delta_B = -deltaB_limit;
            para_B = linear_damp + delta_B;
            // para_B = linear_damp;
            ROS_INFO("deltaB = %f, para_B = %f",delta_B, para_B);
            
            // phi -= sigma*(lastErr)/linear_damp;
            // 导纳控制添加质量项和阻尼项进行拖动控制
            double zdd = (1/linear_mass)*(fzErr - para_B*(vel_now-0));
            // zdd = m_filter.low_pass_filter(zdd);
            // zdd = m_highFilter.high_pass_filter(zdd);
            ROS_INFO("zdd = %f", zdd);

            command_vel[2]=actual_vel[2]+zdd*(time_now-last_time).toSec();
            ROS_INFO("forceErr = %lf", fzErr);
            if(fabs(fzErr) < 1) loopFlag++;
            ROS_INFO("loop = %d", loopFlag);
            if(loopFlag>100){
                ROS_INFO_ONCE("STARTED X MOVE");
                if(directionFlag<980) command_vel[1]=1;
                else if(directionFlag<1000) command_vel[1]=0;
                else if(directionFlag<1980) command_vel[1]=-1;
                else command_vel[1]=0;
                directionFlag=(directionFlag+1)%2000;
            }
            ROS_INFO("direction = %d", directionFlag);
            ROS_INFO_STREAM("the actual force is: "<<actualFz);
            ROS_INFO_STREAM("command_vel is: "<<command_vel[2]);
            this->limitVelocity(command_vel);
            admitVel = std::abs(command_vel[2]);
            command_pos[2]=actual_pos[2]+command_vel[2]*(time_now-last_time).toSec();
            // command_pos[1]=actual_pos[1]+command_vel[1]*(time_now-last_time).toSec();

            ROS_INFO("actual pos z = %lf", actual_pos[2]);
            ROS_INFO("command pos z = %lf", command_pos[2]);
            // std::cout<<actual_vel[4]<<","<<command_vel[4]<<std::endl;
            // geometry_msgs::Pose pubData_force;
            // pubData_force.position.x = desireFz;
            // pubData_force.position.y = actualFz;
            // pub_force.publish(pubData_force);
            szj_demo::AdmStatus pubData_admStatus;
            pubData_admStatus.forceTarget = desireFz;
            pubData_admStatus.forceNow = actualFz;
            pubData_admStatus.deltaB = delta_B;
            pubData_admStatus.paraB = para_B;
            pubData_admStatus.zdd = zdd;
            pub_admStatus.publish(pubData_admStatus);

            this->urMoveL();
            last_time=time_now;
            vel_last = vel_now;
            fzErr_last = fzErr;
            std::cout<<std::endl;
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
    ros::Publisher pub_admStatus;

    std::vector<double> command_vel;
    std::vector<double> wrench_base;
    std::vector<double> actual_vel;
    std::vector<double> actual_pos;
    std::vector<double> command_pos;
    double fzErr_last = 0;
    double fzErr_diff = 0;
    double phi = 0;
    double vel_last = 0;
    double delta_B = 0;
    double para_B = 0;
    double veloity_limit=0.25;
    double deltaB_limit = 1000;
    double linear_mass=1;
    double linear_damp=100;
    double angular_mass=1;
    double angular_damp=2;
    double desireFz = 10;
    double para_Bp = 1;
    double para_Bv = 1;
    double admitVel = 0.2;


    // LowPassFilter m_filter;
    // HighPassFilter m_hictaghFilter;
    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);

    // void ToolPoseCallback(const geometry_msgs::TwistStamped& msg);

    void ToolPoseCallback(const szj_demo::toolStatus& msg);


    void limitVelocity(std::vector<double> &velocity);

    void urMoveL();
    std::string double2string(double input);
};



void variableAdmCtrl::ToolPoseCallback(const szj_demo::toolStatus& msg){
    actual_pos[0] = msg.linearX;
    actual_pos[1] = msg.linearY;
    actual_pos[2] = msg.linearZ;
    actual_pos[3] = msg.angularX;
    actual_pos[4] = msg.angularY;
    actual_pos[5] = msg.angularZ;
    
    actual_vel[0] = msg.velLinearX;
    actual_vel[1] = msg.velLinearY;
    actual_vel[2] = msg.velLinearZ;
    actual_vel[3] = msg.velAngularX;
    actual_vel[4] = msg.velAngularY;
    actual_vel[5] = msg.velAngularZ;
}

//力矩传感器回调函数
void variableAdmCtrl::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = -msg.wrench.force.x;
    wrench_base[1] = -msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = -msg.wrench.torque.x;
    wrench_base[4] = -msg.wrench.torque.y;
    wrench_base[5] = msg.wrench.torque.z;
}


//浮点数转string
std::string variableAdmCtrl::double2string(double input)
{
    std::string string_temp;
    std::stringstream stream;
    stream<<input;
    string_temp = stream.str();
    return string_temp;
}


//限制速度大小
void variableAdmCtrl::limitVelocity(std::vector<double> &velocity){
    for(int i=0;i<velocity.size();i++){
        if(fabs(velocity[i])<0.001) velocity[i]=0;
        if(velocity[i]>veloity_limit) velocity[i]=veloity_limit;
        else if(velocity[i]<-veloity_limit) velocity[i]=-veloity_limit;
        else ;
    }
}

void variableAdmCtrl::urMoveL(){
    std_msgs::String ur_script_msgs;
    double time2move = 0.1;
    double acc=2;
    std::string move_msg;
    move_msg = "movel(p[";
    move_msg = move_msg + double2string(command_pos[0]) + ",";
    move_msg = move_msg + double2string(command_pos[1]) + ",";
    move_msg = move_msg + double2string(command_pos[2]) + ",";
    move_msg = move_msg + double2string(command_pos[3]) + ",";
    move_msg = move_msg + double2string(command_pos[4]) + ",";
    move_msg = move_msg + double2string(command_pos[5]) + "]";
    move_msg = move_msg + ",";
    move_msg = move_msg + double2string(1.2) + ",";
    move_msg = move_msg + double2string(0.25) + ")";
    // move_msg = move_msg + double2string(admitVel) + ")";

    move_msg = move_msg + "\n";

    ur_script_msgs.data=move_msg;
    ROS_INFO("PUB CommandZ = %lf", command_pos[2]);
    ur_pub.publish(ur_script_msgs);
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "variableAdmCtrlNode");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    variableAdmCtrl ad;
    ros::waitForShutdown();
    return 0;
}