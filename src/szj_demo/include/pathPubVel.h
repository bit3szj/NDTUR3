#include <iostream>
#include "kdl/chain.hpp"
#include "urdf/model.h"
#include "kdl/tree.hpp"
#include "ros/ros.h"
#include "kdl_parser/kdl_parser.hpp"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/robot_hw.h"
#include "kdl/jntarray.hpp"
#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include <kdl/chainfksolverpos_recursive.hpp>
#include "geometry_msgs/Pose.h"
#include "std_msgs/String.h"
#include "Eigen/Geometry"
#include "Eigen/Core"
#include "cmath"
#include "geometry_msgs/Twist.h"

class PathPubVel:public hardware_interface::RobotHW
{
public:
    PathPubVel();
    ~PathPubVel();
    int init();
    // Eigen::Vector3d rpy2vec(double roll, double pitch, double yaw);
    void urMove();

public:
    // std::vector<double> jointState_;
    KDL::JntArray jointState_;
    KDL::Frame endFrame_;
    KDL::Frame endCommand_;
    std::vector<double> endVelCmd_;
    std::vector<double> correctVelCmd_;
    void urFk();
    ros::Publisher pub_endPos;
    KDL::Vector cmdRotVec_;
    KDL::Vector rotVec_;
    
private:
    ros::NodeHandle nh_;
    std::string robotDescription_, rootName_, tipName_, namespace_, xmlString_;
    urdf::Model model_;
    KDL::Tree kdlTree_;
    KDL::Chain kdlChain_;
    std::vector<hardware_interface::JointHandle> joint_handles_;
    ros::Subscriber sub_jState;
    ros::Subscriber sub_endCommand;
    ros::Subscriber sub_correctVel;
    ros::Publisher pub_ur;


    struct limits_
    {
        KDL::JntArray min;
        KDL::JntArray max;
        KDL::JntArray center;
    } joint_limits_;

    boost::shared_ptr<KDL::ChainFkSolverPos> fkSolverPos_;
    
    

private:
    void sub_jStateCall(sensor_msgs::JointStateConstPtr msg);
    void sub_endCommandCall(const geometry_msgs::PoseConstPtr msg);
    void sub_correctVelCall(const geometry_msgs::Twist msg);
    // Eigen::Matrix3d rpy2rot(double roll, double pitch, double yaw);
    // Eigen::Vector3d rot2vec(Eigen::Matrix3d R);
    std::string double2string(double input);
    void limitVel();
    
    
};