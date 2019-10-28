#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "topic_test/topictest1.h"
#include "topic_test/srvtest.h"
#include "trajectory_msgs/JointTrajectory.h"
#include <iostream>
#include <sstream>
float c[6] = {0,0,0,0,0,0};
bool flag[6] = {false,false,false,false,false,false};
bool hander_function(topic_test::srvtest::Request &req,topic_test::srvtest::Response &res)
{
    res.out = "ok";
    for(int i = 0; i<6;i++)
    {
        c[i] = req.A_value[i];
        flag[i] = req.A[i];
    }
    //c = req.num;
    return true;
}
int main(int argc, char **argv)
{

    ros::init(argc,argv,"example");
    ros::NodeHandle n;
    topic_test::topictest1 msg;
    msg.x = 0.1;
    msg.y = 0.1;
    //ros::Publisher chatter_pub = n.advertise<topic_test::topictest1>("topictest1",1000);
    ros::Publisher arm_trajectory = n.advertise<trajectory_msgs::JointTrajectory>("/position_trajectory_controller/command",1000); // /kuka_kr5_arc/kr5_controller/command
    //ros::Publisher arm_trajectory = n.advertise<trajectory_msgs::JointTrajectory>("/kuka_kr5_arc/kr5_controller/command",1000); // /kuka_kr5_arc/kr5_controller/command
    ros::ServiceServer service = n.advertiseService("servicetest1",hander_function);
    ros::Rate loop_rate(5); //Hz
    float mine;
    std::string arm_joints[6] = {"joint_a1","joint_a2","joint_a3","joint_a4","joint_a5","joint_a6"};
    double a[6] = {-12.517,-48.777,122.466,-102.038,86.506,-15.953};
    double Home_Point[6] = {a[0]*3.1415926/180,a[1]*3.1415926/180,a[2]*3.1415926/180,a[3]*3.1415926/180,a[4]*3.1415926/180,a[5]*3.1415926/180};
    trajectory_msgs::JointTrajectoryPoint tra_point;

    tra_point.positions.resize(6);
    for(int i = 0;i < 6;i++)
    {
        tra_point.positions[i] = Home_Point[i];
    }
    trajectory_msgs::JointTrajectory tra_msg;
    tra_msg.joint_names.resize(6);
    for(int i = 0;i < 6;i++)
    {
        tra_msg.joint_names[i] = arm_joints[i];
    }
    tra_msg.points.resize(1);
    tra_msg.points[0] = tra_point; 
    tra_msg.points[0].time_from_start = ros::Duration(0.5);
    while(ros::ok())
    { 
        for(int i = 0;i<6;i++)
        {
            if(flag[i])//&&(c[i]<1.57&&c[i]>-1.57))      //flag[i]&&(c[i]<1.57&&c[i]>-1.57)
            {
                tra_msg.points[0].positions[i] = c[i];
            }
        }
        arm_trajectory.publish(tra_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}