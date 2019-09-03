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
    srv.request.A.resize(6);
    srv.request.A_value.resize(6);
    while(ros::ok())
    {
        if(client.call(srv))
        {
            ROS_INFO_STREAM("State is  " + srv.response.out + " /n Plase put in the Joint's No. :" );
            int a;
            std::cin >> a;
            int c = 0;
            for(int b = 32;b>0;b = b/2)
            {
                if(a/b)
                {
                    std::cout << "\n" << bool(a/b) << "\n";
                    srv.request.A[5-c] = true;
                    a = a-b;
                }
                else
                {
                   std::cout << "\n" << bool(a/b) << "\n";
                   srv.request.A[5-c] = false;
                }
                
                c++;
            }
            std::cout << "\n" << c << "\n";
            ROS_INFO_STREAM("State is  " + srv.response.out + " /n Plase put in the Joint's value :" );
            std::cin >> srv.request.A_value[0];
            std::cin >> srv.request.A_value[1];
            std::cin >> srv.request.A_value[2];
            std::cin >> srv.request.A_value[3];
            std::cin >> srv.request.A_value[4];
            std::cin >> srv.request.A_value[5];
            //std::cin >> srv.request.num;
        }
        else
        {
            ROS_ERROR("Failed");
            return 1;
        }
    }
    return 0;
}