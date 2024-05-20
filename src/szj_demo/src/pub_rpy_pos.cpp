/*this program is used to control robot to move between two points*/
// 引入ros头文件
#include <ros/ros.h>
// 引入geometry_msgs头文件
#include <geometry_msgs/Pose.h>
#include <tf/transform_datatypes.h>

double lastPos = 0;
double currentPos = 0;
double dt = 1.0/125.0;
double vel = 0;
double now_y = -0.1;
double now_target_y = 0.0; 
// void Callback(cartesian_state_msgs::PoseTwistConstPtr _msg){
//   currentPos = _msg->pose.position.z;
//   vel = (currentPos - lastPos) / dt;
//   // 更新上一次的位置
//   lastPos = currentPos;
//   ROS_INFO("now vel = %lf\n", vel);
// }

int main(int argc, char **argv)
    {
    // 初始化ros节点
    ros::init(argc, argv, "pose_publisher");
    // 创建ros节点句柄
    ros::NodeHandle nh;
    // 创建一个Publisher，发布名为/command_cart_pos的话题，消息类型为geometry_msgs::Pose，队列长度为10
    ros::Publisher pose_pub = nh.advertise<geometry_msgs::Pose>("/cartesian_velocity_position_controller/command_cart_pos", 1);
    // ros::Subscriber sub_cartState = nh.subscribe<cartesian_state_msgs::PoseTwistConstPtr>
    // ("cartesian_velocity_position_controller/ee_state",1, &Callback);
    ros::Duration(0.1).sleep();
    // 设置循环的频率
    ros::Rate loop_rate(125);
    bool flag = false;
    ros::Time last_time = ros::Time::now();
    std::vector<double> vec_pose1(6);
    vec_pose1[0] = -0.47087; vec_pose1[1] = -0.11169; vec_pose1[2] = 0.24134;
    vec_pose1[3] = 3.141; vec_pose1[4] = -0.005; vec_pose1[5] = 1.571;
    tf::Quaternion qua_pose1;
    qua_pose1.setRPY(vec_pose1[3], vec_pose1[4], vec_pose1[5]);
    geometry_msgs::Pose pose1;
    pose1.position.x = -0.47087;
    pose1.position.y = -0.11169;
    pose1.position.z = 0.24134;
    pose1.orientation.x = qua_pose1.x();
    pose1.orientation.y = qua_pose1.y();
    pose1.orientation.z = qua_pose1.z();
    pose1.orientation.w = qua_pose1.w();

    std::vector<double> vec_pose2(6);
    vec_pose2[0] = -0.47087; vec_pose2[1] = 0; vec_pose2[2] = 0.24134;
    vec_pose2[3] = 3.141; vec_pose2[4] = -0.005; vec_pose2[5] = 1.571;
    tf::Quaternion qua_pose2;
    qua_pose2.setRPY(vec_pose2[3], vec_pose2[4], vec_pose2[5]);
    geometry_msgs::Pose pose1;
    pose1.position.x = vec_pose2[0];
    pose1.position.y = vec_pose2[1];
    pose1.position.z = vec_pose2[2];
    pose1.orientation.x = qua_pose2.x();
    pose1.orientation.y = qua_pose2.y();
    pose1.orientation.z = qua_pose2.z();
    pose1.orientation.w = qua_pose2.w();
    
    


  while (ros::ok())
  {
    // 初始化geometry_msgs::Pose类型的消息
    geometry_msgs::Pose pose;
    double target_z = 0.35;
    nh.getParam("global_posZ", target_z);
    if((ros::Time::now() - last_time).toSec() > 2.0){
        if((flag == false) ){
            // 设置位置坐标
            pose.position.x = 0.15;
            pose.position.y = 0.1;
            now_target_y = 0.1;
            pose.position.z = target_z;
            // 设置姿态四元数
            pose.orientation.x = -0.76;
            pose.orientation.y = -0.65;
            pose.orientation.z = 0.01;
            pose.orientation.w = 0.02;
            flag = true;
            pose_pub.publish(pose);
            last_time = ros::Time::now();
            ROS_INFO("Publish first position: position(%.2f, %.2f, %.2f), orientation(%.2f, %.2f, %.2f, %.2f)", 
            pose.position.x, pose.position.y, pose.position.z,
            pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
        }else if(flag == true ){
            // 设置位置坐标
            pose.position.x = 0.15;
            pose.position.y = -0.1;
            now_target_y = -0.1;
            pose.position.z = target_z;
            // 设置姿态四元数
            pose.orientation.x = -0.76;
            pose.orientation.y = -0.65;
            pose.orientation.z = 0.01;
            pose.orientation.w = 0.02;
            flag = false;
            pose_pub.publish(pose);
            last_time = ros::Time::now();
            ROS_INFO("Publish second position: position(%.2f, %.2f, %.2f), orientation(%.2f, %.2f, %.2f, %.2f)", 
            pose.position.x, pose.position.y, pose.position.z,
            pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
        }

    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
