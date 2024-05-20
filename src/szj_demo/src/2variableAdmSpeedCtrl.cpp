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
#include "2PDcontrol.cpp"


// const double veloity_limit=0.02;
const double veloity_limit=0.05;

double linear_mass=15;
double linear_damp=20;
const double angular_mass=1;
const double angular_damp=2;
double desireFz = 10;


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
        pub_admStatus = nh.advertise<szj_demo::AdmStatus>("/szj/admStatus",5);
        // sub_toolPose = nh.subscribe("/szj/toolPose", 5, &variableAdmCtrl::ToolPoseCallback, this);
        sub_toolPose = nh.subscribe("/szj/toolStatus", 5, &variableAdmCtrl::ToolPoseCallback, this);
        m_PdCntrol = new szjspace::PdControl(m_kp, m_kd);
        ros::Duration(1.0).sleep();
        // for(int i = 0; i < 6; ++i){
        //     command_pos[i] = actual_pos[i];
        // }
        command_pos[0] = -0.383;
        command_pos[1] = -0.229;
        command_pos[2] = 0.241;
        command_pos[3] = 2.223;
        command_pos[4] = 2.224;
        command_pos[5] = 0.005;
        this->urMoveL();
        ros::Duration(1.0).sleep();
        nh.setParam("global_paraForce", desireFz);
        nh.setParam("global_paraM", linear_mass);
        nh.setParam("global_paraB", linear_damp);
        ROS_INFO("robot starts to move");
        int loopFlag = 0;
        int directionFlag = 0;
        double lastErr = 0;
        ros::Rate loop_rate(50);
        ros::Time last_time=ros::Time::now();
        ros::Time time_now;
        lastErr = this->wrench_base[2] - desireFz;
        while (ros::ok())
        {
            nh.getParam("global_paraForce", desireFz);
            nh.getParam("global_paraM", linear_mass);
            nh.getParam("global_paraB", linear_damp);
            time_now=ros::Time::now();
            double actualFz = this->wrench_base[2];
            ROS_INFO("actual Force = %f", wrench_base[2]);
            double vel_now = actual_vel[2];
            double fzErr = actualFz - desireFz;
            fzErrDiff = (fzErr - lastErr) / (time_now-last_time).toSec();
            delta_B = m_PdCntrol->calculate(fzErr, fzErrDiff)/vel_now;
            m_PdCntrol->limitDeltaB(delta_B);
            // double localB = linear_damp - delta_B;
            double localB = linear_damp;
            // double sigma = 1/(1*fabs(fzErr) + 1*fabs(lastErr) + 10);
            
            // phi -= sigma*(lastErr)/linear_damp;
            // phi = 0;
            // 导纳控制添加质量项和阻尼项进行拖动控制
            // double zdd = (1/linear_mass)*(fzErr - linear_damp*(vel_now-0) - linear_damp*phi*(vel_now-0));
            double zdd = (1/linear_mass)*(fzErr - localB*(vel_now-0));
            // ROS_INFO("damp_facotor = %f",linear_damp*phi);

            command_vel[2]=actual_vel[2]+zdd*(time_now-last_time).toSec();
            lastFz = actualFz;
            ROS_INFO("forceErr = %lf", fzErr);
            if(fabs(fzErr) < 4) loopFlag++;
            ROS_INFO("loop = %d", loopFlag);
            if(loopFlag>100){
            // if(0){
                ROS_INFO_ONCE("STARTED X MOVE");
                if(directionFlag<80) command_vel[1]=1;
                else if(directionFlag<100) command_vel[1]=0;
                else if(directionFlag<180) command_vel[1]=-1;
                else command_vel[1]=0;
                directionFlag=(directionFlag+1)%200;
            }
            ROS_INFO("direction = %d", directionFlag);
            ROS_INFO_STREAM("the actual force is: "<<actualFz);
            if(actualFz != 0){
                velChangeFlag = true;
                ROS_WARN_ONCE("flag to true");

            }
            if(actualFz == 0 &&  !velChangeFlag){
                command_vel[2] = -0.02;
            }
            this->limitVelocity(command_vel);
            moveZdd = command_vel[2]*2;

            ROS_INFO_STREAM("the actual vel is:"<<vel_now<<" and command_vel is: "<<command_vel[2]);
            ROS_INFO_STREAM("command_vel is: "<<command_vel[2]);

            // ROS_INFO_STREAM(" the phi is: "<<phi);


            // std::cout<<actual_vel[4]<<","<<command_vel[4]<<std::endl;
            szj_demo::AdmStatus pubData_admStatus;
            pubData_admStatus.forceTarget = desireFz;
            pubData_admStatus.forceNow = actualFz;
            pubData_admStatus.zdd = zdd;
            pubData_admStatus.paraB = localB;
            pubData_admStatus.commandVel = command_vel[2];
            pub_admStatus.publish(pubData_admStatus);
            this->urMoveSpeed();
            last_time=time_now;
            lastErr = fzErr;
            std::cout<<std::endl;
            ros::spinOnce();
            loop_rate.sleep();
        }
        std::string move_msg="stopl(1)\n";
        std_msgs::String ur_script_msgs;
        ur_script_msgs.data = move_msg;
        ur_pub.publish(ur_script_msgs);
    }
    ~variableAdmCtrl();

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
    double lastFz = 0;
    double fzErrDiff = 0;
    double phi;
    bool velChangeFlag = false;
    double m_kp = 1;
    double m_kd = 450;
    double delta_B = 0;

    double moveZdd = 0.5;
    szjspace::PdControl *m_PdCntrol;

    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);

    // void ToolPoseCallback(const geometry_msgs::TwistStamped& msg);

    void ToolPoseCallback(const szj_demo::toolStatus& msg);


    void limitVelocity(std::vector<double> &velocity);

    void urMoveL();
    void urMoveSpeed();
    std::string double2string(double input);
};


variableAdmCtrl::~variableAdmCtrl(){
    delete m_PdCntrol;
}
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
    // move_msg = move_msg + double2string(moveZdd) + ",";
    move_msg = move_msg + double2string(0.1) + ")";

    move_msg = move_msg + "\n";

    ur_script_msgs.data=move_msg;
    ROS_INFO("PUB CommandZ = %lf", command_pos[2]);
    ur_pub.publish(ur_script_msgs);
}

void variableAdmCtrl::urMoveSpeed(){
        std_msgs::String ur_script_msgs;
    double time2move = 0.1;
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
    ros::init(argc, argv, "variableAdmCtrlNode");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    variableAdmCtrl ad;
    ros::waitForShutdown();
    return 0;
}