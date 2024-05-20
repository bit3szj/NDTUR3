#include "ros/ros.h"
#include"geometry_msgs/TwistStamped.h"

#include<cstring>
#include<vector>
#include <arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
#include<cmath>

const char* tool_speed = "tool_speed";

//定义大小端转换
#define ntohll(x) ( ((uint64_t)x & 0xff00000000000000LL) >>56 |\
((uint64_t)x & 0x00ff000000000000LL) >> 40 |\
((uint64_t)x & 0x0000ff0000000000LL)>>24 | \
((uint64_t)x & 0x000000ff00000000LL)>>8 | \
((uint64_t)x & 0x00000000ff000000LL)<<8 | \
((uint64_t)x & 0x0000000000ff0000LL)<<24 | \
((uint64_t)x & 0x000000000000ff00LL)<<40 | \
((uint64_t)x & 0x00000000000000ffLL)<<56 ) 

double swapDoubleEndian(double *val) {
    uint64_t llVal = ntohll(*((uint64_t*)val));//这个一个宏函数,在此文件头部,这里转换成指针原因见下两行
    return *((double*)&llVal);//uint64是无符号数,和double储存格式不一样,不能进行强制转换直接返回double类型,会错误; \
    所以这里将uint64的地址取出来,再把这个uint64类型的地址指针转换成double类型指针,再返回double指针的内容,这种基础数据类型要谨慎隐式转换
}

int main(int argc, char** argv)
{
    //1、创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd ==-1)
    {
        perror("socket");
        exit(-1);
    }

    //2连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.50", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(30003);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if(ret == -1){
        perror("connect");
        exit(-1);
    }

    //3通信
    char recvBuf[2048] = {0};
    double buff;
    double joint_position[8] = {0};
    double joint_velocity[8] = {0};
    // std::vector<char> coordinate;
    // std::vector<char> coordinate_speed;
    double coordinate[8] = {0};
    double coordinate_speed[8] = {0};



    
    //ros初始化
    ros::init(argc,argv,"publish_tool_velocity");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::TwistStamped>("tool_velocity",1000);
    ros::Duration(1).sleep();

    ros::Rate loop_rate(25);
    geometry_msgs::TwistStamped pub_info;
    while(ros::ok()){
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if(len == 0){
            perror("server closed...");
            exit(-1);
        }else if(len > 0){
            int offset = 444;
            for (int i = 0; i < 6; i++, offset += 8) {//读取末端位置,x,y,z,Rx,Ry,Rz
                memcpy(&buff, recvBuf + offset, 8);
                buff = swapDoubleEndian(&buff);
                coordinate[i] = buff;
            }
            for (int i = 0; i < 6; i++, offset += 8) {//读取末端速度,x,y,z,Rx,Ry,Rz
                memcpy(&buff, recvBuf + offset, 8);
                buff = swapDoubleEndian(&buff);
                if(fabs(buff) < 1e-4) buff = 0;
                //if(buff < 0.0001) buff = 0;
                coordinate_speed[i] = buff;
            }
            pub_info.twist.linear.x = coordinate_speed[0];
            pub_info.twist.linear.y = coordinate_speed[1];
            pub_info.twist.linear.z = coordinate_speed[2];
            pub_info.twist.angular.x = coordinate_speed[3];
            pub_info.twist.angular.y = coordinate_speed[4];
            pub_info.twist.angular.z = coordinate_speed[5];
            pub.publish(pub_info);
        }
        
        loop_rate.sleep();
    }
    ros::waitForShutdown();
    return 0;
}