//publish a pose infomation, whose z-value is a sine function

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <cmath>

    // Define the amplitude and period of the sine wave
    const double amplitude = 0.1;
    const double period = 2 * M_PI;

    int main(int argc, char** argv)
    {
    // Initialize the ROS node
    ros::init(argc, argv, "sine_publisher");

    // Create a ROS node handle
    ros::NodeHandle nh("~");

    // Create a publisher object
    ros::Publisher pub = nh.advertise<geometry_msgs::Pose>("/cartesian_velocity_position_controller/command_cart_pos_correct", 1);

    // Create a pose object
    geometry_msgs::Pose pose;

    // Set the position x and y to zero
    pose.position.x = 0.0;
    pose.position.y = 0.0;

    // Set the orientation to identity
    pose.orientation.x = 0;
    pose.orientation.y = 0;
    pose.orientation.z = 0;
    pose.orientation.w = 1;

    // Create a rate object
    ros::Rate rate(125);

    // Create a variable to store the current time
    double t = 0.0;

    // Loop until the node is shutdown
    while (ros::ok())
    {
        // Update the position z to a sine value
        pose.position.z = amplitude * sin(0.5 * t * period);

        // Publish the pose
        pub.publish(pose);
        ROS_INFO("Published pose with z = %f", pose.position.z);

        // Sleep for the desired rate
        rate.sleep();

        // Update the current time
        t += rate.expectedCycleTime().toSec();
    }

    return 0;
    }
