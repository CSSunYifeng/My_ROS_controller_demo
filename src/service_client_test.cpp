#include "ros/ros.h"
#include "topic_test/srvtest.h"
#include <sstream>
#include <iostream>
int main(int argc, char **argv)
{
    ros::init(argc,argv,"client_test");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<topic_test::srvtest>("servicetest1");

    topic_test::srvtest srv;
    srv.request.in = "HAN";
    srv.request.num = 2;
    while(ros::ok())
    {
        if(client.call(srv))
        {
            ROS_INFO_STREAM("feedback from server123: " + srv.response.out);
            std::cin >> srv.request.num;
        }
        else
        {
            ROS_ERROR("Failed");
            return 1;
        }
    }
    return 0;
}