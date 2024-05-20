#include <ros/ros.h>
#include <robot_state_publisher/robot_state_publisher.h>
#include <tf/transform_listener.h>
#include "geometry_msgs/Twist.h"
#include "szj_demo/toolStatus.h"
#include <kdl/frames.hpp>
std::vector<double> actual_pos(6,0);
std::vector<double> last_pos(6,0);
std::vector<double> endVel(6,0);
const double constRate = 250;


void getVel(const tf::StampedTransform &tf){
    actual_pos[0]=tf.getOrigin().getX();
    actual_pos[1]=tf.getOrigin().getY();
    actual_pos[2]=tf.getOrigin().getZ();
    double x=tf.getRotation().getX();
    double y=tf.getRotation().getY();
    double z=tf.getRotation().getZ();
    double w=tf.getRotation().getW();
    KDL::Rotation rotMat = KDL::Rotation::Quaternion(x, y, z, w);
    KDL::Vector rotVec = rotMat.GetRot();
    actual_pos[3] = rotVec.data[0];
    actual_pos[4] = rotVec.data[1];
    actual_pos[5] = rotVec.data[2];
    for(int i = 0; i < endVel.size(); ++i){
        endVel[i] = (actual_pos[i] - last_pos[i]) * constRate;
        // if(endVel[i] < 1e-5) endVel[i] = 0;
    }
    // std::vector<double> retVec = {actual_pos[0], actual_pos[1], actual_pos[2], rotVec.data[0], rotVec.data[1], rotVec.data[2]};
    // return retVec;
}

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "toolVel");
    ros::NodeHandle nh;
    // ros::Publisher pub_velocity = nh.advertise<geometry_msgs::Twist>("/szj/endVel", 5);
    // ros::Publisher pub_pose = nh.advertise<geometry_msgs::TwistStamped>("/szj/toolPose",5);
    ros::Publisher pub_toolStatus = nh.advertise<szj_demo::toolStatus>("/szj/toolStatus",5);
    tf::TransformListener listener;
    tf::StampedTransform transform;
    ros::Rate loopRate(constRate);
    ros::Duration(0.1).sleep();

    while(ros::ok()){
        try{
            listener.lookupTransform("base_link", "tool0", 
            // listener.lookupTransform("wrist_1_link", "wrist_3_link",  
                                ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        getVel(transform);
        szj_demo::toolStatus pubToolMsg;
        // geometry_msgs::Twist pubMsg;
        pubToolMsg.velLinearX = endVel[0]; pubToolMsg.velLinearY = endVel[1]; pubToolMsg.velLinearZ = endVel[2];
        pubToolMsg.velAngularX = endVel[3]; pubToolMsg.velAngularY = endVel[4]; pubToolMsg.velAngularZ = endVel[5]; 
        // pubMsg.linear.x = endVel[0]; pubMsg.linear.y = endVel[1]; pubMsg.linear.z = endVel[2];
        // pubMsg.angular.x = endVel[3]; pubMsg.angular.y = endVel[4]; pubMsg.angular.z = endVel[5];
        // pub_velocity.publish(pubMsg);
        // geometry_msgs::TwistStamped pubMsgPose;
        // pubMsgPose.header.stamp = ros::Time::now();
        // pubMsgPose.twist.linear.x = actual_pos[0]; pubMsgPose.twist.linear.y = actual_pos[1]; pubMsgPose.twist.linear.z = actual_pos[2];
        // pubMsgPose.twist.angular.x = actual_pos[3]; pubMsgPose.twist.angular.y = actual_pos[4]; pubMsgPose.twist.angular.z = actual_pos[5];
        // pub_pose.publish(pubMsgPose);
        pubToolMsg.linearX = actual_pos[0]; pubToolMsg.linearY = actual_pos[1]; pubToolMsg.linearZ = actual_pos[2];
        pubToolMsg.angularX = actual_pos[3];  pubToolMsg.angularY = actual_pos[4]; pubToolMsg.angularZ = actual_pos[5]; 
        pub_toolStatus.publish(pubToolMsg);
        ROS_INFO_ONCE("begin!");
        last_pos = actual_pos;
        // 进入循环，等待回调函数被调用
        ros::spinOnce();
        loopRate.sleep();
    }


    return 0;
}
