#include "ros/ros.h"
#include "geometry_msgs/WrenchStamped.h"
#include "std_msgs/String.h"
#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include "cmath"
#include "std_msgs/Float64.h"
#include "sensor_msgs/JointState.h"
#include <geometry_msgs/TwistStamped.h>
#include <tf/transform_listener.h>
#include "szj_demo/toolStatus.h"
#include "szj_demo/AdmStatus.h"
#include "2PDcontrol.cpp"
//目前最好使的程序20240313
double m=20;
double b=5;
double k=20;
double desire_fz=25;

double desire_fx=0;
double desire_fy=0;
double desire_tx=0;
double desire_ty=0;
double desire_tz=0;
double acc = 1.0;

const double angular_mass=0.5;
const double angular_damp=2;

class FixedPointAdmittanceControl
{
public:
    FixedPointAdmittanceControl()
    {
        command_vel.resize(6);
        actual_vel.resize(6);
        actual_pos.resize(6);
        wrench_base.resize(6);
        for(int i = 0; i < 6; i ++)
        {   
            command_vel[i]=0;
            actual_pos[i] = 0;
            actual_vel[i]=0;
            wrench_base[i]=0;
        }

        wrench_sub = nh.subscribe("/compensate_wrench_base_filter", 1000, &FixedPointAdmittanceControl::WrenchsubCallback,this);
        // tool_velocity_sub=nh.subscribe("/tool_velocity",1000,&FixedPointAdmittanceControl::ToolVelocitysubCallback,this);
        ur_pub = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",1000);
        sub_toolPose = nh.subscribe("/szj/toolStatus", 5, &FixedPointAdmittanceControl::ToolPoseCallback, this);
        pub_admStatus = nh.advertise<szj_demo::AdmStatus>("/szj/admStatus",5);
        m_PdCntrol = new szjspace::PdControl(m_kp, m_kd);
        nh.setParam("global_paraForce", desire_fz);
        // nh.setParam("global_paraEnvK", k);
        nh.setParam("global_paraB", b);
        nh.setParam("global_paraM", m);
        nh.setParam("global_paraK", k);
        nh.setParam("global_acc", acc);
        nh.setParam("global_usePD", usePD);
        nh.setParam("global_kp", m_kp);
        nh.setParam("global_kd", m_kd); 
        nh.setParam("global_paraPosLim", B_max);
        nh.setParam("global_paraNegLim", B_min);
        int loopFlag = 0;
        int directionFlag = 0;
        

        // nh.setParam("global_paraKp", m_kp);
        // nh.setParam("global_paraKd", m_kd);
        // nh.setParam("global_paraPosLim", m_posLim);
        // nh.setParam("global_paraNegLim", m_negLim);
        // nh.setParam("global_paraEnvPosFlag", envPosFlag);
        ros::Duration(1).sleep();
        ros::Rate loop_rate(50);
        double delta_t=0.02;
        ros::Time last_time=ros::Time::now();
        ros::Time time_now;
        while (ros::ok())
        {
            time_now=ros::Time::now();
            // double xdd=1/m*((-this->wrench_base[0]-desire_fz)-b*(actual_vel[0]-0));
            // command_vel[0]=xdd*delta_t;
            // double ydd=1/m*((-this->wrench_base[1]-desire_fz)-b*(actual_vel[1]-0));
            // command_vel[1]=ydd*delta_t;
            nh.getParam("global_paraB", b);
            nh.getParam("global_paraM", m);
            nh.getParam("global_paraK", k);
            nh.getParam("global_paraForce", desire_fz);
            nh.getParam("global_acc", acc);
            nh.getParam("global_usePD", usePD);
            nh.getParam("global_paraKp", m_kp);
            nh.getParam("global_paraKd", m_kd);
            nh.getParam("global_paraPosLim", B_max);
            nh.getParam("global_paraNegLim", B_min);
            fzErr = this->wrench_base[2]-desire_fz;
            fzErrDiff = (fzErr - lastFzErr) / (time_now-last_time).toSec();
            m_PdCntrol->setParam(m_kp,m_kd);
            m_PdCntrol->setLimitValue(B_max,B_min);
           ///////////
            if(usePD==1)
            {
                delta_B = m_PdCntrol->calculate(fzErr, fzErrDiff)/actual_vel[2];
                m_PdCntrol->limitDeltaB(delta_B);
                b=b_init + delta_B;
                // ROS_INFO("USE pd");
            }else{
                // b = b_init;
            }



            double zdd=1/m*((this->wrench_base[2]-desire_fz)-b*(actual_vel[2]-0));
            // command_vel[2]=zdd*delta_t;
            command_vel[2]=zdd*(time_now-last_time).toSec();

            double txdd = 1/angular_mass*((this->wrench_base[3]-desire_tx) - angular_damp*actual_vel[3]);
            // command_vel[3] = txdd*(time_now-last_time).toSec();

            double tydd = 1/angular_mass*((this->wrench_base[4]-desire_ty) - angular_damp*actual_vel[4]);
            // command_vel[4] = tydd*(time_now-last_time).toSec();

            // if(fabs(fzErr) < 1 && (this->wrench_base[3] < 0.1) && (this->wrench_base[4] < 0.1)) loopFlag++;
            if(fabs(fzErr) < 1) loopFlag++;
            ROS_INFO("loop = %d,desire_tx = %f", loopFlag, desire_tx);
            if(loopFlag>100){
            // if(0){
                // if(actual_vel[2]<0) desire_tx=0.5;
                // else if(actual_vel[2]>0) desire_tx=-0.5;
                ROS_INFO_ONCE("STARTED X MOVE");
                if(directionFlag<480) 
                {
                    command_vel[1]=-0.01;
                    // desire_tx=0.5;
                }
                else if(directionFlag<500) command_vel[1]=0;
                else if(directionFlag<980) 
                {
                    command_vel[1]=0.01;
                    // desire_tx=-0.5;
                }
                else command_vel[1]=0;
                directionFlag=(directionFlag+1)%1000;
            }

            //阻尼控制
            // command_vel[2]=(this->wrench_base[2]-desire_fz)/b;
  

            // double txdd=angular_mass*(this->wrench_base[3]-angular_damp*actual_vel[3]);
            // command_vel[3]=actual_vel[3]+txdd*delta_t;

            szj_demo::AdmStatus pubData_admStatus;

            nh.setParam("global_paraLocalB", b); 
            
            this->limitVelocity(command_vel);
            // acc = 2*command_vel[2] /(time_now-last_time).toSec();

            pubData_admStatus.forceTarget = desire_fz;
            pubData_admStatus.forceNow = wrench_base[2];
            pubData_admStatus.commandVel = command_vel[2];
            pubData_admStatus.actualVel = actual_vel[2];
            // pubData_admStatus.paraB = b;
            pub_admStatus.publish(pubData_admStatus);
            // nh.setParam("global_acc", acc);
            this->urMove();
            last_time=time_now;
            lastFzErr=fzErr;
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;

    ros::Subscriber wrench_sub;
    ros::Subscriber tool_velocity_sub;
    ros::Publisher ur_pub;
    ros::Publisher pub_admStatus;
    ros::Subscriber sub_toolPose;

    std::vector<double> actual_pos;

    std::vector<double> command_vel;
    std::vector<double> actual_vel;
    std::vector<double> wrench_base;
    szjspace::PdControl *m_PdCntrol;
    double m_kp = 1;
    double m_kd = -0.1;
    double fzErr = 0;
    double lastFzErr = 0;
    double fzErrDiff = 0;
    double usePD = 0;
    double b_init = 5;
    double m_init = 15;
    double delta_B = 0;

    double B_max = 2000;
    double B_min = 0;
    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);
    void ToolVelocitysubCallback(const geometry_msgs::TwistStamped& msg);
    void ToolPoseCallback(const szj_demo::toolStatus& msg);

    void urMove();
    std::string double2string(double input);
    void limitVelocity(std::vector<double> &velocity);
};


// 限制发送速度指令大小
void FixedPointAdmittanceControl::limitVelocity(std::vector<double> &velocity){
    for(int i=0;i<velocity.size();i++){
        if(abs(velocity[i])<1e-4) velocity[i]=0;
        else if(velocity[i]>1) velocity[i]=1;
        else if(velocity[i]<-1) velocity[i]=-1;
        else ;
    }
}
void FixedPointAdmittanceControl::ToolPoseCallback(const szj_demo::toolStatus& msg){
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
//世界坐标系力矩传感器回调函数
void FixedPointAdmittanceControl::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = msg.wrench.force.x;
    wrench_base[1] = msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = msg.wrench.torque.x;
    wrench_base[4] = msg.wrench.torque.y;
    wrench_base[5] = msg.wrench.torque.z;
}

//世界坐标系末端速度回调函数
void FixedPointAdmittanceControl::ToolVelocitysubCallback(const geometry_msgs::TwistStamped& msg)
{
    actual_vel[0]=msg.twist.linear.x;
    actual_vel[1]=msg.twist.linear.y;
    actual_vel[2]=msg.twist.linear.z;
    actual_vel[3]=msg.twist.angular.x;
    actual_vel[4]=msg.twist.angular.y;
    actual_vel[5]=msg.twist.angular.z;
}

//double转string
std::string FixedPointAdmittanceControl::double2string(double input)
{
    std::string string_temp;
    std::stringstream stream;
    stream<<input;
    string_temp = stream.str();
    return string_temp;
}


//UR机器人运动函数
void FixedPointAdmittanceControl::urMove()
{
    std_msgs::String ur_script_msgs;
    double time2move = 0.5;
    // double acc=1;


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
    ros::init(argc, argv, "fixed_point_admittance_control");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    FixedPointAdmittanceControl ad;
    return 0;
}

