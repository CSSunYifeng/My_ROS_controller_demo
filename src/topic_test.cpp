#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "topic_test/topictest1.h"
#include "topic_test/srvtest.h"
#include "trajectory_msgs/JointTrajectory.h"
#include <iostream>
#include <sstream>
float c = 0;
bool hander_function(topic_test::srvtest::Request &req,topic_test::srvtest::Response &res)
{
    res.out = "Please in:";
    c = req.num;
    return true;
}
void trajectory_test_msg_init()
{
}
int main(int argc, char **argv)
{
    ros::init(argc,argv,"example");
    ros::NodeHandle n;
    topic_test::topictest1 msg;
    msg.x = 0.1;
    msg.y = 0.1;
    
    //ros::Publisher chatter_pub = n.advertise<topic_test::topictest1>("topictest1",1000);
    ros::Publisher arm_trajectory = n.advertise<trajectory_msgs::JointTrajectory>("trajecory_topictest1",1000);
    ros::ServiceServer service = n.advertiseService("servicetest1",hander_function);
    ros::Rate loop_rate(10);
    float mine;
    std::string arm_joints[6] = {"A1","A2","A3","A4","A5","A6"};
    trajectory_msgs::JointTrajectoryPoint tra_point;
    tra_point.positions.resize(6);
    for(int i = 0;i < 6;i++)
    {
        tra_point.positions[i] = i;
    }
    trajectory_msgs::JointTrajectory tra_msg;
    tra_msg.joint_names.resize(6);
    for(int i = 0;i < 6;i++)
    {
        tra_msg.joint_names[i] = arm_joints[i];
    }
    /*
    tra_msg.joint_names.push_back("A1");
    tra_msg.joint_names.push_back("A2");
    tra_msg.joint_names.push_back("A3");
    tra_msg.joint_names.push_back("A4");
    tra_msg.joint_names.push_back("A5");
    tra_msg.joint_names.push_back("A6");
    */
    tra_msg.points.resize(1);
    tra_msg.points[0] = tra_point; 


    
    //memcpy(tra_msg.joint_names,arm_joints,sizeof(arm_joints));
    //tra_msg.points[0] = tra_point;
    
    while(ros::ok())
    { 
        //std_msgs::String msg;
        //std::stringstream ss;
        //ss << "Hello world!";
        //msg.data=ss.str();
        //msg.x = msg.x + 0.1;
        //std::cin >> mine;
        //msg.x = c;
        tra_msg.points[0].positions[3] = c;
        arm_trajectory.publish(tra_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}