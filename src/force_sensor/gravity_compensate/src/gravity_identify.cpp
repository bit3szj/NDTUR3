#include <iostream>
#include <string>
#include <fstream>

#include <ros/ros.h>
#include <ros/package.h>
#include <geometry_msgs/WrenchStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <tf/transform_listener.h>
#include <cmath>

#include <yaml-cpp/yaml.h>

#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/Geometry> 
#include <Eigen/Core>


const std::string PLANNING_GROUP = "manipulator";
const int pos_num=9;

class GravityIdentify
{
public:
    GravityIdentify():move_group(PLANNING_GROUP)
    {
        wrenchb_temp.resize(6,0);  
        index=0;
        sensor_point=0;

        flag=false;
        wrench_sub = nh.subscribe("/filtered_wrench", 1000, &GravityIdentify::WrenchsubCallback,this);
       
        ros::Duration(5).sleep();
        int exit_code=urMove();
        if(exit_code!=0){
            std::cout<<"move failed"<<std::endl;
            return;
        }
        calculateP();
        calculateG();
        writeToYaml();
        ros::shutdown();
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber wrench_sub;


    moveit::planning_interface::MoveGroupInterface move_group;
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    tf::TransformListener listener;

    Eigen::Matrix<double,pos_num*3,1> F;
    Eigen::Matrix<double,pos_num*3,1> M;
    Eigen::Matrix<double,pos_num*3,3> R;

    std::vector<double> wrenchb_temp;
   

    Eigen::Matrix<double,6,1> p;//负载的重心
    Eigen::Matrix<double,6,1> G;

    bool flag;
    int sensor_point; 
    int index;
    void WrenchsubCallback(const geometry_msgs::WrenchStamped& msg); //订阅力传感器回调函数
    void getSE3();

    Eigen::Matrix3d getAntisymmetric(Eigen::Matrix<double,3,1> v);
    Eigen::Matrix3d quaternion2Rotation(double x,double y,double z,double w);//四元数转旋转矩阵

    void calculateP();
    void calculateG();
    int urMove();
    void writeToYaml() const;

    double G_sum;
};

//四元数转旋转矩阵
Eigen::Matrix3d GravityIdentify::quaternion2Rotation(double x,double y,double z,double w){
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

//机器人每到达一个点就会将flag=true，计算完100个点的平均值之后将flag=false
void GravityIdentify::WrenchsubCallback(const geometry_msgs::WrenchStamped& msg){
    if(flag){
        std::string dir_package,dir_param_file;
        dir_package = ros::package::getPath("gravity_compensate");
        dir_param_file = dir_package + "/config/forceData.txt";
        std::ofstream fileForce(dir_param_file, std::ios::app);
        sensor_point++;//累加100次
        wrenchb_temp[0] += msg.wrench.force.x;//将100次的力数据进行累加
        wrenchb_temp[1] += msg.wrench.force.y;
        wrenchb_temp[2] += msg.wrench.force.z;
        wrenchb_temp[3] += msg.wrench.torque.x;
        wrenchb_temp[4] += msg.wrench.torque.y;
        wrenchb_temp[5] += msg.wrench.torque.z;
        for(int i = 0; i < 6; ++i){
            fileForce << wrenchb_temp[i] << " ";
        }fileForce<<"\n";
         
        if(sensor_point==100){
            std::cout<<"average started"<<std::endl;
            // calculate 100 times force average date
            for(int i=0;i<6;i++){
                wrenchb_temp[i]/=100;
            }
            Eigen::Matrix<double,3,1> M_temp;
            Eigen::Matrix<double,3,1> F_temp;
            M_temp<<wrenchb_temp[3],wrenchb_temp[4],wrenchb_temp[5];//vector放入Eigen库matrix矩阵中
            F_temp<<wrenchb_temp[0],wrenchb_temp[1],wrenchb_temp[2];
            M.block(index*3,0,3,1)=M_temp;//将M_temp存入M从index*3,0开始的3行1列中
            F.block(index*3,0,3,1)=F_temp;
            for(int i=0;i<6;i++){//将累加100次的数据清零
                wrenchb_temp[i]=0;
            }           
            getSE3();
            sensor_point=0;//100计数器归零
            flag=false;     //标志位复位，表示不需要再进行平均计算，该函数if（flag）下不再执行
            
        }
        fileForce.close();
    }
}


//利用tf_listener 查询机器人末端相对于基座的位姿
void GravityIdentify::getSE3(){
    std::cout<<"calculate R started"<<std::endl;
    tf::StampedTransform transform;
    try{
        listener.lookupTransform("base", "tool1",ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
    }

    double x=transform.getRotation().getX();//获取四元数
    double y=transform.getRotation().getY();
    double z=transform.getRotation().getZ();
    double w=transform.getRotation().getW();

    R.block(3*index,0,3,3)=quaternion2Rotation(x,y,z,w).transpose();//将四元数转换为旋转矩阵，放入R中 一共9个3*3的矩阵
    std::cout<<"calculate R finished"<<std::endl;
}

//获取向量对应的反对称矩阵
Eigen::Matrix3d GravityIdentify::getAntisymmetric(Eigen::Matrix<double,3,1> v){
    Eigen::Matrix3d temp;
    temp<<0,v(2,0),-v(1,0),
          -v(2,0),0,v(0,0),
          v(1,0),-v(0,0),0;
    return temp;
}

//计算负载的质心
void GravityIdentify::calculateP(){
    std::cout<<"calculate P started"<<std::endl;
    Eigen::Matrix<double,pos_num*3,6> E;
    Eigen::Matrix<double,3,3> I33=Eigen::Matrix3d::Identity();  
    for(int i=0;i<pos_num;i++){       
        E.block(i*3,0,3,3)=getAntisymmetric(F.block(i*3,0,3,1));
        E.block(i*3,3,3,3)=I33;
    }

    p=((E.transpose()*E).inverse())*E.transpose()*M;//最小二乘法
    std::cout<<"the trans of gravity is\n"<<p<<std::endl;
}

//计算负载的质量以及力矩传感器的零点
void GravityIdentify::calculateG(){
    
    Eigen::Matrix<double,pos_num*3,6> E;
    Eigen::Matrix3d I33=Eigen::Matrix3d::Identity();
    E.block(0,0,pos_num*3,3)=R;
    for(int i=0;i<pos_num;i++) E.block(i*3,3,3,3)=I33;
    G=(E.transpose()*E).inverse()*E.transpose()*F;//最小二乘法
    G_sum = sqrt(G(0,0)*G(0,0) + G(1,0)*G(1,0) + G(2,0)*G(2,0));
    std::cout<<"the gravity and zero point of sensor is\n"<<G<<std::endl;
}

//利用Moveit控制机器人进行运动
int GravityIdentify::urMove()
{
    std::string pos="pose";
    for(int i=1;i<=pos_num;i++){
        move_group.setNamedTarget(pos+std::to_string(i));
        bool plan_success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
        
        if(!plan_success) return -1;
        std::cout<<"plan success："<<i<<std::endl;
        bool execute_success = (move_group.execute(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
        if(!execute_success) return -1;
        ros::Duration(5).sleep();
        flag=true;
        std::cout<<"execute success:"<<i<<std::endl;
        while(flag) continue;
        ros::Duration(5).sleep();
        index++;
    }
    return 0;
}

//将标识出的参数写入yaml文件
void GravityIdentify::writeToYaml() const
{
    std::string dir_package,dir_param_file;
    dir_package = ros::package::getPath("gravity_compensate");
    dir_param_file = dir_package + "/config/param.yaml";
    std::ofstream fout(dir_param_file);

    YAML::Emitter out(fout);
    out << YAML::BeginMap;
    out << YAML::Key << "pos";
    out << YAML::BeginSeq;
    out << YAML::Value << p(0,0);
    out << YAML::Value << p(1,0);
    out << YAML::Value << p(2,0);
    out << YAML::EndSeq;
    out << YAML::Key << "Gm";
    out << YAML::BeginSeq;
    out << YAML::Value << G(0,0);
    out << YAML::Value << G(1,0);
    out << YAML::Value << G(2,0);
    out << YAML::EndSeq;
    out << YAML::Key << "F0";
    out << YAML::BeginSeq;
    out << YAML::Value << G(3,0);
    out << YAML::Value << G(4,0);
    out << YAML::Value << G(5,0);
    out << YAML::Value << p(3,0)-G(4,0)*p(2,0)+G(5,0)*p(1,0);
    out << YAML::Value << p(4,0)-G(5,0)*p(0,0)+G(3,0)*p(2,0);
    out << YAML::Value << p(5,0)-G(3,0)*p(1,0)+G(4,0)*p(0,0);
    out << YAML::EndSeq;
    out << YAML::Key << "angle";
    out << YAML::BeginSeq;
    out << YAML::Value << asin(-G(1,0)/G_sum);
    out << YAML::Value << atan(-G(0,0)/G(2,0));
    out << YAML::EndSeq;
    out << YAML::EndMap;
    fout.close();
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "GravityIdentify");
    ros::AsyncSpinner spinner(2);//ros非阻塞线程
    spinner.start();
    GravityIdentify gc;
    return 0;
}
