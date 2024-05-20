#include <ros/ros.h>
#include <robot_state_publisher/robot_state_publisher.h>
#include <tf/transform_listener.h>
#include "geometry_msgs/Twist.h"
#include "szj_demo/toolStatus.h"
#include <kdl/frames.hpp>
std::vector<double> actual_pos(6,0);
std::vector<double> last_pos(6,0);
std::vector<std::vector<double>> endVel;
std::vector<double> pubVel(6,0);
std::vector<double> endVel_sum;
const int frequency=3;
const double constRate = 250;
int flag =0;


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
    endVel[0][flag]= (actual_pos[0] - last_pos[0])*constRate;
    endVel[1][flag]= (actual_pos[1] - last_pos[1])*constRate;
    endVel[2][flag]= (actual_pos[2] - last_pos[2])*constRate;
    endVel[3][flag]= (actual_pos[3] - last_pos[3])*constRate;
    endVel[4][flag]= (actual_pos[4] - last_pos[4])*constRate;
    endVel[5][flag]= (actual_pos[5] - last_pos[5])*constRate;
    flag=(flag+1)%frequency;
    for(int i=0;i<6;i++){
        for(int j=0;j<frequency;j++){
            endVel_sum[i]+=endVel[i][j];
        }
    }
    pubVel[0]=endVel_sum[0]/frequency;
    pubVel[1]=endVel_sum[1]/frequency;
    pubVel[2]=endVel_sum[2]/frequency;
    pubVel[3]=endVel_sum[3]/frequency;
    pubVel[4]=endVel_sum[4]/frequency;
    pubVel[5]=endVel_sum[5]/frequency;
    for(int i=0;i<6;i++) endVel_sum[i]=0;
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
    // ros::Publisher pub_velInTool = nh.advertise<szj_demo::toolStatus>("/szj/velInTool",5);
    tf::TransformListener listener;
    tf::StampedTransform transform;
    ros::Rate loopRate(constRate);
    flag=0;
    std::vector<double> temp(frequency,0);
    for(int i=0;i<6;i++) endVel.push_back(temp);
    endVel_sum.resize(6);

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
        pubToolMsg.velLinearX = pubVel[0]; pubToolMsg.velLinearY = pubVel[1]; pubToolMsg.velLinearZ = pubVel[2];
        pubToolMsg.velAngularX = pubVel[3]; pubToolMsg.velAngularY = pubVel[4]; pubToolMsg.velAngularZ = pubVel[5]; 
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
