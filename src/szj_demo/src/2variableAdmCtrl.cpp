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


const double veloity_limit=0.1;
const double linear_mass=1;
const double linear_damp=100;
const double angular_mass=1;
const double angular_damp=2;
const double desireFz = 10;


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
        lastFz = 0;
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
            double actualFz = this->wrench_base[2];
            ROS_INFO("actual Force = %f", wrench_base[2]);
            double vel_now = actual_vel[2];
            double fzErr = actualFz - desireFz;
            double sigma = 1/(1*fabs(fzErr) + 1*fabs(lastErr) + 15);
            time_now=ros::Time::now();
            phi -= sigma*(lastErr)/linear_damp;
            // 导纳控制添加质量项和阻尼项进行拖动控制
            double zdd = (1/linear_mass)*(fzErr - linear_damp*(vel_now-0) - linear_damp*phi*(vel_now-0));
            ROS_INFO("damp_facotor = %f",linear_damp*phi);
            lastErr = fzErr;
            command_vel[2]=actual_vel[2]+zdd*(time_now-last_time).toSec();
            lastFz = actualFz;
            ROS_INFO("forceErr = %lf", fzErr);
            if(fabs(fzErr) < 5) loopFlag++;
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
            ROS_INFO_STREAM("the actual vel is:"<<vel_now<<" and command_vel is: "<<command_vel[2]<<" the phi is: "<<phi);
            this->limitVelocity(command_vel);
            command_pos[2]=actual_pos[2]+command_vel[2]*(time_now-last_time).toSec();
            command_pos[1]=actual_pos[1]+command_vel[1]*(time_now-last_time).toSec();

            ROS_INFO("actual pos z = %lf", actual_pos[2]);
            ROS_INFO("command pos z = %lf", command_pos[2]);
            // std::cout<<actual_vel[4]<<","<<command_vel[4]<<std::endl;
            szj_demo::AdmStatus pubData_admStatus;
            pubData_admStatus.forceTarget = desireFz;
            pubData_admStatus.forceNow = actualFz;
            pubData_admStatus.zdd = zdd;
            pub_admStatus.publish(pubData_admStatus);
            this->urMoveL();
            last_time=time_now;
            std::cout<<std::endl;
            ros::spinOnce();
            loop_rate.sleep();
        }
        std::string move_msg="stopl(1)\n";
        std_msgs::String ur_script_msgs;
        ur_script_msgs.data = move_msg;
        ur_pub.publish(ur_script_msgs);
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
    double lastFz;
    double phi;

    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);

    // void ToolPoseCallback(const geometry_msgs::TwistStamped& msg);

    void ToolPoseCallback(const szj_demo::toolStatus& msg);


    void limitVelocity(std::vector<double> &velocity);

    void urMoveL();
    void urMoveSpeed();
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
    move_msg = move_msg + double2string(0.5) + ",";
    move_msg = move_msg + double2string(0.1) + ")";

    move_msg = move_msg + "\n";

    ur_script_msgs.data=move_msg;
    ROS_INFO("PUB CommandZ = %lf", command_pos[2]);
    ur_pub.publish(ur_script_msgs);
}

void variableAdmCtrl::urMoveSpeed(){
        std_msgs::String ur_script_msgs;
    double time2move = 0.1;
    double acc=1;
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
    ros::init(argc, argv, "variableAdmCtrlNode");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    variableAdmCtrl ad;
    ros::waitForShutdown();
    return 0;
}