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
#include<pthread.h>

const char* tool_speed = "tool_speed";

#define debug 1
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

//创建数据结构体用于传参
typedef struct data_struct{
    double coordinate[6] = {0};
    double coordinate_speed[6] = {0};
}data_struct_;

//定义读写锁
pthread_rwlock_t rwlock;

void *callback(void * arg){
    int circle_num = 0;
    data_struct* data_point = (data_struct_ *)arg;
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
    char recvBuf[2048] = {0};
    double buff;
    while(1){
        circle_num++;
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
            pthread_rwlock_wrlock(&rwlock);
            int offset = 444;
            for (int i = 0; i < 6; i++, offset += 8) {//读取末端位置,x,y,z,Rx,Ry,Rz
                memcpy(&buff, recvBuf + offset, 8);
                buff = swapDoubleEndian(&buff);
                data_point->coordinate[i] = buff;
            }
            #if debug
            //debug输出位置信息
            for(int i = 0; i < 6; i++){
                std::cout << "poin" << i << ":" <<data_point->coordinate[i] << " ";
            }
            std::cout << std::endl;
            #endif

            for (int i = 0; i < 6; i++, offset += 8) {//读取末端速度,x,y,z,Rx,Ry,Rz
                memcpy(&buff, recvBuf + offset, 8);
                buff = swapDoubleEndian(&buff);
                if(fabs(buff) < 1e-4) buff = 0;
                //if(buff < 0.0001) buff = 0;
                data_point->coordinate_speed[i] = buff;
                 //coordinate_speed[i] = buff;
            }
            pthread_rwlock_wrlock(&rwlock);
            //std::cout << "z_speed = " << coordinate_speed[2] << std::endl;
 
            //print_data(tool_speed, coordinate_speed);
            //sleep(1);
            if(circle_num == 20) pthread_exit(NULL);
        }
    }
        
}

int main(int argc, char** argv)
{
    
    //读写锁初始化
    pthread_rwlock_init(&rwlock, NULL);
    //3通信
    // char recvBuf[2048] = {0};
    // double buff;
    // double joint_position[6] = {0};
    // double joint_velocity[6] = {0};
    // std::vector<char> coordinate;
    // std::vector<char> coordinate_speed;


    // double coordinate[6] = {0};
    // double coordinate_speed[6] = {0};

    data_struct_*  all_data = new data_struct_;

    //创建线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback,(void *)all_data);
    //设置线程分离
    //pthread_detach(tid);
    
    //ros初始化
    ros::init(argc,argv,"publish_tool_velocity");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::TwistStamped>("tool_velocity",200);
    ros::Duration(1).sleep();

    ros::Rate loop_rate(25);
    geometry_msgs::TwistStamped pub_info;
    while(ros::ok()){
        //读锁
        pthread_rwlock_rdlock(&rwlock);
        pub_info.twist.linear.x = all_data->coordinate_speed[0];
        pub_info.twist.linear.y = all_data->coordinate_speed[1];
        pub_info.twist.linear.z = all_data->coordinate_speed[2];
        pub_info.twist.angular.x = all_data->coordinate_speed[3];
        pub_info.twist.angular.y = all_data->coordinate_speed[4];
        pub_info.twist.angular.z = all_data->coordinate_speed[5];
        pthread_rwlock_unlock(&rwlock);
        pub.publish(pub_info);
       // ROS_INFO("pub velocity:%lf %lf %lf",pub_info.twist.linear.x, pub_info.twist.linear.y, pub_info.twist.linear.z);
        loop_rate.sleep();
    }
    //pthread_join(tid,NULL);

    ros::waitForShutdown();
    return 0;
}