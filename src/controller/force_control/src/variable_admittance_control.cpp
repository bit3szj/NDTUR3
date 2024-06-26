#include "ros/ros.h"
#include "geometry_msgs/WrenchStamped.h"
#include "std_msgs/String.h"
#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include "cmath"
#include "std_msgs/Float64.h"
#include <std_msgs/String.h>
#include "sensor_msgs/JointState.h"
#include <geometry_msgs/TwistStamped.h>
#include <tf/transform_listener.h>

const double m=15;
// const double b=500;
const double k=25;
const double desire_fz=10;
const double sigma=0.0;

class VariableAdmittanceControl
{
public:
    VariableAdmittanceControl()
    {
        command_vel.resize(6,0);
        actual_vel.resize(6,0);
        wrench_base.resize(6,0);
        actual_pos.resize(6,0);
        command_pos.resize(6,0);
       

        phi=0;
        last_fz=0;
        wrench_sub = nh.subscribe("/compensate_wrench_base", 1000, &VariableAdmittanceControl::WrenchsubCallback,this);
        tool_velocity_sub=nh.subscribe("/tool_velocity",1000,&VariableAdmittanceControl::ToolVelocitysubCallback,this);
        ur_pub = nh.advertise<std_msgs::String>("ur_driver/URScript",1000);
       
        ros::Duration(5.0).sleep();
        
        tf::StampedTransform transform;

        try{
            listener.lookupTransform("base", "tool1",  
                                ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        actual_pos[0]=transform.getOrigin().getX();
        actual_pos[1]=transform.getOrigin().getY();
        actual_pos[2]=transform.getOrigin().getZ();
        double x=transform.getRotation().getX();
        double y=transform.getRotation().getY();
        double z=transform.getRotation().getZ();
        double w=transform.getRotation().getW();


        Eigen::Matrix3d rotation_matrix=quaternion2Rotation(x,y,z,w);
        double theta=acos((rotation_matrix(0,0)+rotation_matrix(1,1)+rotation_matrix(2,2)-1)/2);//等效角度-轴线表示法
        double rx=1/(2*sin(theta))*(rotation_matrix(2,1)-rotation_matrix(1,2));
        double ry=1/(2*sin(theta))*(rotation_matrix(0,2)-rotation_matrix(2,0));
        double rz=1/(2*sin(theta))*(rotation_matrix(1,0)-rotation_matrix(0,1));

        actual_pos[3]=rx*theta;
        actual_pos[4]=ry*theta;
        actual_pos[5]=rz*theta;
        for(int i=0;i<6;i++){
            command_pos[i]=actual_pos[i];     
        }
        command_pos[2]-=0.01;
        this->urMoveL(command_pos);
        ros::Duration(1.0).sleep();

        int loop_flag=0;
        int direction_flag=0;
        double last_error=0;
        ros::Time last_time=ros::Time::now();

        const double b=250;
        ros::Rate loop_rate(50);
        while (ros::ok())
        {   
            double actual_fz=this->wrench_base[2];
            double vel_now=actual_vel[2];
            double error=actual_fz-desire_fz;
            double sigma=1/(1*fabs(error)+1*fabs(last_error)+10);
            
            
            ros::Time now_time=ros::Time::now();
            ROS_INFO_STREAM("the actual vel");
            phi-=sigma*(last_error)/b;
            double zdd=5*((actual_fz-desire_fz)-b*(vel_now-0)-b*phi);
            last_error=error;
            command_vel[2]=actual_vel[2]+zdd*(now_time-last_time).toSec();
            
            last_fz=actual_fz;
            // double error=actual_fz-desire_fz;
            if(fabs(error)<0.01) loop_flag++;
            if(loop_flag>100){
                ROS_INFO_ONCE("STARTED X MOVE");
                if(direction_flag<480) command_vel[1]=0.02;
                else if(direction_flag<500) command_vel[1]=0;
                else if(direction_flag<980) command_vel[1]=-0.02;
                else command_vel[1]=0;
                direction_flag=(direction_flag+1)%1000;
            }
            command_vel[1]=0;
            ROS_INFO_STREAM("the actual force is: "<<actual_fz);
            ROS_INFO_STREAM("the actual vel is:"<<vel_now<<" and command_vel is: "<<command_vel[2]<<" the phi is: "<<phi);
            this->limitVelocity(command_vel);
            // command_pos[2]+=0.01;
            // for(int i=0;i<6;i++){
                
            //     std::cout<<command_pos[i]<<",";
            // }
            // std::cout<<std::endl;
            try{
                listener.lookupTransform("base", "tool1",  
                                    ros::Time(0), transform);
            }
            catch (tf::TransformException ex){
                ROS_ERROR("%s",ex.what());
                ros::Duration(1.0).sleep();
            }
            actual_pos[1]=transform.getOrigin().getY();
            actual_pos[2]=transform.getOrigin().getZ();
            // command_pos[1]=actual_pos[1]+command_vel[1]*(now_time-last_time).toSec();
            command_pos[2]=actual_pos[2]+command_vel[2]*(now_time-last_time).toSec();
            ROS_INFO_STREAM("the error of command_pos and actual_pos is: "<<command_pos[2]-actual_pos[2]);
            this->urMoveL(command_pos);
            last_time=now_time;
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
    tf::TransformListener listener;

    std::vector<double> command_vel;
    std::vector<double> actual_vel;
    std::vector<double> wrench_base;
    std::vector<double> actual_pos;
    std::vector<double> command_pos;
    double phi;
    double last_fz;

    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);
    void ToolVelocitysubCallback(const geometry_msgs::TwistStamped& msg);
    void getSE3();
    void urMove();
    void urMoveL(std::vector<double> &command_pose);
    std::string double2string(double input);
    void limitVelocity(std::vector<double> &velocity);
    Eigen::Matrix3d quaternion2Rotation(double x,double y,double z,double w);
};


// 限制发送速度指令大小
void VariableAdmittanceControl::limitVelocity(std::vector<double> &velocity){
    // std::cout<<"limit velocity"<<std::endl;
    for(int i=0;i<velocity.size();i++){
        if(fabs(velocity[i])<1e-4) velocity[i]=0;
        else if(velocity[i]>1) velocity[i]=1;
        else if(velocity[i]<-1) velocity[i]=-1;
        else ;
    }
}

//世界坐标系力矩传感器回调函数
void VariableAdmittanceControl::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg)
{
    wrench_base[0] = msg.wrench.force.x;
    wrench_base[1] = msg.wrench.force.y;
    wrench_base[2] = msg.wrench.force.z;
    wrench_base[3] = msg.wrench.torque.x;
    wrench_base[4] = msg.wrench.torque.y;
    wrench_base[5] = msg.wrench.torque.z;
}

//世界坐标系末端速度回调函数
void VariableAdmittanceControl::ToolVelocitysubCallback(const geometry_msgs::TwistStamped& msg)
{
    actual_vel[0]=msg.twist.linear.x;
    actual_vel[1]=msg.twist.linear.y;
    actual_vel[2]=msg.twist.linear.z;
    actual_vel[3]=msg.twist.angular.x;
    actual_vel[4]=msg.twist.angular.y;
    actual_vel[5]=msg.twist.angular.z;
}

// 四元数转旋转矩阵
Eigen::Matrix3d VariableAdmittanceControl::quaternion2Rotation(double x,double y,double z,double w){
    Eigen::Matrix3d R;
    R(0,0)=1-2*y*y-2*z*z;
    R(0,1)=2*(x*y-z*w);
    R(0,2)=2*(x*z+y*w);
    R(1,0)=2*(x*y+z*w);
    R(1,1)=1-2*x*x-2*z*z;
    R(1,2)=2*(y*z-x*w);
    R(2,0)=2*(x*z-y*w);
    R(2,1)=2*(y*z+x*w);
    R(2,2)=1-2*x*x-2*y*y;
    return R;
}


//得到机器人末端相对于基座的位姿
void VariableAdmittanceControl::getSE3(){
    tf::StampedTransform transform;
    try{
      listener.lookupTransform("base", "tool1",  
                               ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    double x=transform.getRotation().getX();
    double y=transform.getRotation().getY();
    double z=transform.getRotation().getZ();
    double w=transform.getRotation().getW();
    actual_pos[0]=transform.getOrigin().getX();
    actual_pos[1]=transform.getOrigin().getY();
    actual_pos[2]=transform.getOrigin().getZ();
    Eigen::Matrix3d R=quaternion2Rotation(x,y,z,w).transpose();
}   

//double转string
std::string VariableAdmittanceControl::double2string(double input)
{
    std::string string_temp;
    std::stringstream stream;
    stream<<input;
    string_temp = stream.str();
    return string_temp;
}


//UR机器人运动函数
void VariableAdmittanceControl::urMove()
{
    std_msgs::String ur_script_msgs;
    double time2move = 0.1;
    double acc=2;
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



//UR机器人运动函数
void VariableAdmittanceControl::urMoveL(std::vector<double> &command_pose)
{
    std_msgs::String ur_script_msgs;
    double time2move = 0.1;
    double acc=2;
    std::string move_msg;
    move_msg = "movel(p[";
    move_msg = move_msg + double2string(command_pose[0]) + ",";
    move_msg = move_msg + double2string(command_pose[1]) + ",";
    move_msg = move_msg + double2string(command_pose[2]) + ",";
    move_msg = move_msg + double2string(command_pose[3]) + ",";
    move_msg = move_msg + double2string(command_pose[4]) + ",";
    move_msg = move_msg + double2string(command_pose[5]) + "]";
    move_msg = move_msg + ",";
    move_msg = move_msg + double2string(0.25) + ",";
    move_msg = move_msg + double2string(0.5) + ")";

    move_msg = move_msg + "\n";

    ur_script_msgs.data=move_msg;
    ur_pub.publish(ur_script_msgs);
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "variable_admittance_control_node");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    VariableAdmittanceControl ad;
    return 0;
}

