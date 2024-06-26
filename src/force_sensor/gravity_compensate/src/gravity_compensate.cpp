#include <iostream>
#include <string>
#include <cmath>

#include <ros/ros.h>
#include <ros/package.h>
#include <geometry_msgs/WrenchStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <tf/transform_listener.h>

#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <Eigen/Core>

const std::string PLANNING_GROUP = "manipulator";
const int pos_num=6;
class GravityCompensate
{
public:
    GravityCompensate()
    {
        std::vector<double> temp;
        if(!nh.getParam("pos",temp)){
            ROS_FATAL_STREAM("pos Missing");
            return;
        }
        p<<temp[0],temp[1],temp[2];
        if(!nh.getParam("Gm",temp)){
            ROS_FATAL_STREAM("Gm Missing");
            return;
        }
        G0<<temp[0],temp[1],temp[2];
        if(!nh.getParam("F0",temp)){
            ROS_FATAL_STREAM("F0 Missing");
            return;
        }
        F0<<temp[0],temp[1],temp[2],temp[3],temp[4],temp[5];

        origin_wrench_sub = nh.subscribe("/filtered_wrench", 1000, &GravityCompensate::WrenchsubCallback,this);
        wrench_tool_pub = nh.advertise<geometry_msgs::WrenchStamped>("/compensate_wrench_tool",1000);
        wrench_base_pub = nh.advertise<geometry_msgs::WrenchStamped>("/compensate_wrench_base",1000);
        // wrench_base_pub = nh.advertise<geometry_msgs::WrenchStamped>("/compensate_wrench_base",1000);

        ROS_INFO("init finished");
        ros::Duration(1).sleep();
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber origin_wrench_sub;
    ros::Publisher wrench_tool_pub;
    ros::Publisher wrench_base_pub;

    Eigen::Matrix<double,3,1> p;    //重心位置？
    Eigen::Matrix<double,3,1> G0;   //重力分量？
    Eigen::Matrix<double,6,1> F0;   //零点漂移？
    tf::TransformListener listener;

    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg);   //力传感器订阅回调函数
    //获取基座标系与工具坐标系的旋转
    Eigen::Matrix3d getSO3();

    Eigen::Matrix<double,3,3> getAntisymmetric(Eigen::Matrix<double,3,1> v);    //反对称，好像没用到
    // 四元数转旋转矩阵
    Eigen::Matrix3d quaternion2Rotation(double x,double y,double z,double w);   
};



void GravityCompensate::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg){
    Eigen::Matrix<double,6,1> wrenchb_temp;
    wrenchb_temp(0) = msg.wrench.force.x;
    wrenchb_temp(1) = msg.wrench.force.y;
    wrenchb_temp(2) = msg.wrench.force.z;
    wrenchb_temp(3) = msg.wrench.torque.x;
    wrenchb_temp(4) = msg.wrench.torque.y;
    wrenchb_temp(5) = msg.wrench.torque.z;

    Eigen::Matrix3d R=getSO3();//获得实时的变化坐标
    std::cout<<R<<std::endl;

    Eigen::Matrix<double,3,1> Gb=(R.transpose()*G0);//transpose 矩阵转置，将重力转换到工具坐标系下
    
    Eigen::Matrix<double,6,1> GF;
    //根据标定后的重力和质心坐标计算，基座标系下的重力和重力矩
    GF<<Gb(0),Gb(1),Gb(2),
        Gb(2)*p(1)-Gb(1)*p(2),Gb(0)*p(2)-Gb(2)*p(0),Gb(1)*p(0)-Gb(0)*p(1);

    Eigen::Matrix<double,6,6> T;
    Eigen::Matrix3d zeros33=Eigen::Matrix3d::Zero();
    Eigen::Matrix<double,6,1> wrench_tool,wrench_base;
    T.block(0,0,3,3)=R;
    T.block(3,3,3,3)=R;
    T.block(0,3,3,3)=zeros33;
    T.block(3,0,3,3)=zeros33;   //6*6的矩阵，为了转换力和力矩是6*1的向量，前三行前半部分为R,即前三行为力，后三行后半部分为R，即后三行为力矩

    wrench_tool=wrenchb_temp-GF-F0; //实时力-重力-零点力
    wrench_base=T*(wrenchb_temp-GF-F0);
    geometry_msgs::WrenchStamped tool_pub_msg,base_pub_msg;
    tool_pub_msg.header.stamp=ros::Time::now();
    tool_pub_msg.header.frame_id="tool1";
    tool_pub_msg.wrench.force.x=wrench_tool(0);
    tool_pub_msg.wrench.force.y=wrench_tool(1);
    tool_pub_msg.wrench.force.z=wrench_tool(2);
    tool_pub_msg.wrench.torque.x=wrench_tool(3);
    tool_pub_msg.wrench.torque.y=wrench_tool(4);
    tool_pub_msg.wrench.torque.z=wrench_tool(5);
    wrench_tool_pub.publish(tool_pub_msg);

    base_pub_msg.header.stamp=ros::Time::now();
    base_pub_msg.header.frame_id="base_link";
    base_pub_msg.wrench.force.x=wrench_base(0);
    base_pub_msg.wrench.force.y=wrench_base(1);
    base_pub_msg.wrench.force.z=wrench_base(2);
    base_pub_msg.wrench.torque.x=wrench_base(3);
    base_pub_msg.wrench.torque.y=wrench_base(4);
    base_pub_msg.wrench.torque.z=wrench_base(5);
    wrench_base_pub.publish(base_pub_msg);
 
}
//四元素转旋转矩阵
Eigen::Matrix3d GravityCompensate::quaternion2Rotation(double x,double y,double z,double w){
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

//获取基座标系和工具坐标系的变换矩阵
Eigen::Matrix<double,3,3> GravityCompensate::getSO3(){
    std::cout<<"calculate R started"<<std::endl;
    tf::StampedTransform transform;
    try{
        listener.lookupTransform("base", "tool1", ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
    }
    double x=transform.getRotation().getX();
    double y=transform.getRotation().getY();
    double z=transform.getRotation().getZ();
    double w=transform.getRotation().getW();

    return quaternion2Rotation(x,y,z,w);

}

Eigen::Matrix<double,3,3> GravityCompensate::getAntisymmetric(Eigen::Matrix<double,3,1> v){
    Eigen::Matrix<double,3,3> temp;
    temp<<0,v(2,0),-v(1,0),
          -v(2,0),0,v(0,0),
          v(1,0),-v(0,0),0;
    return temp;
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "GravityCompensate");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    GravityCompensate ad;
    ros::waitForShutdown();
    return 0;
}



