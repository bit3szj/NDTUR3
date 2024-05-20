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


const double veloity_limit=1;
const double linear_damp=0.0075;
const double angular_damp=0.5;

class ReadAndPub
{
public:
    ReadAndPub()
    {
        command_vel.resize(6);
        for(int i = 0; i < 6; i ++)
        {   
            command_vel[i]=0;
        }
        sub_point = nh.subscribe("/pointRead",1,&ReadAndPub::pointReadCallback,this);
        pub_ur = nh.advertise<std_msgs::String>("ur_hardware_interface/script_command",1);

        ros::Duration(1.0).sleep();
        ROS_INFO("robot starts to move");

        ros::Rate loop_rate(125);
        while (ros::ok())
        {
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
    ros::Subscriber sub_point;
    ros::Publisher pub_ur;
    szj_controller::pointData readPoint;

    std::vector<double> command_vel;
    std::vector<double> wrench_base;
    void pointReadCallback(const szj_controller::pointData &msg);
    void limitVelocity(std::vector<double> &velocity);
    void urMove();
    std::string double2string(double input);
};

void ReadAndPub::pointReadCallback(const szj_controller::pointData &msg){
    command_vel[0] = msg.x;
    command_vel[1] = msg.y;
    command_vel[2] = msg.z;
    command_vel[3] = msg.rx;
    command_vel[4] = msg.ry;
    command_vel[5] = msg.rz;
}

//浮点数转string
std::string ReadAndPub::double2string(double input)
{
    std::string string_temp;
    std::stringstream stream;
    stream<<input;
    string_temp = stream.str();
    return string_temp;
}

//限制速度大小
void ReadAndPub::limitVelocity(std::vector<double> &velocity){
    for(int i=0;i<velocity.size();i++){
        if(fabs(velocity[i])<1e-3) velocity[i]=0;
        if(velocity[i]>veloity_limit) velocity[i]=veloity_limit;
        else if(velocity[i]<-veloity_limit) velocity[i]=-veloity_limit;
        else ;
    }
}


//UR机器人回调函数
void ReadAndPub::urMove()
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
    pub_ur.publish(ur_script_msgs);
}



int main(int argc, char *argv[])
{
    ros::init(argc, argv, "AdmittanceControlDragUR");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ReadAndPub m_readAndPub;
    ros::waitForShutdown();
    return 0;
}