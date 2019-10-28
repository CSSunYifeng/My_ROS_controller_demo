#include "ros/ros.h"
#include "topic_test/srvtest.h"
#include <sstream>
#include <iostream>
#include "tinyxml2.h"
#include "topic_test/XmlSource.h"
#include <string>
#include <vector>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace tinyxml2;
using namespace std;


void load_xml_node(XMLDocument &doc,unsigned int &i, vector<vector<double> > &Point);
void GetPointNum(XMLDocument &doc,unsigned int &k);
void server_type_1(topic_test::srvtest &srv);
void Point_load(topic_test::srvtest &srv,vector<vector<double> > &Point,unsigned int Point_num);
void server_type_2(topic_test::srvtest &srv,vector<vector<double> > &Point,unsigned int Point_sum,unsigned int &cunt);

unsigned int k = 0;




int main(int argc, char **argv)
{
    vector<vector<double> > Point;
    unsigned int cunt = 1; //start with 1

    ros::init(argc,argv,"client_test");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<topic_test::srvtest>("servicetest1");

    topic_test::srvtest srv;
    srv.request.in = "HAN";
    srv.request.num = 2;
    srv.request.A.resize(6);
    srv.request.A_value.resize(6);
    ros::Rate loop_rate(5);  //Hz

    XMLDocument doc;
    doc.LoadFile("fool.xml");
    GetPointNum(doc,k);
    for(unsigned int mm = 1; mm<=k;mm++)
    {
        load_xml_node(doc, mm, Point);
    }

    printf("save ok!!!!!\n");
    
    cout << Point[0][0]<<endl;

    //cout << ros::ok();
    while(ros::ok())
    {
        cout << "rosok: "<<ros::ok()<<endl;
        cout << "rosok: "<<ros::ok()<<endl;
        cout << "Continue?";
        if(client.call(srv))
        {
            cout << "Continue?";
            server_type_2(srv,Point,k,cunt);
            //server_type_1(srv);
            /*
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
            */
        }
        else
        {
            ROS_ERROR("Failed");
            return 1;
        }
        ros::spinOnce();
        loop_rate.sleep();
        if(cunt == 121)
            break;
    }
    return 0;
}








void load_xml_node(XMLDocument &doc,unsigned int &i, vector<vector<double> >  &Point)
{
	
	const char* title;
	stringstream value_str;
	stringstream pval;
	string value_m;
	XMLElement* titleElement;
	double val;
	vector<double> Point_value;

	value_str << "Point" << i;
	value_m = value_str.str();
	value_str.str("");





	titleElement = doc.FirstChildElement("ROBOT")->FirstChildElement(value_m.c_str())->FirstChildElement("A1");
	title = titleElement->GetText();
	pval << title;
	pval >> val;
	pval.clear();
	Point_value.push_back(val);

	titleElement = doc.FirstChildElement("ROBOT")->FirstChildElement(value_m.c_str())->FirstChildElement("A2");
	title = titleElement->GetText();
	pval << title;
	pval >> val;
	pval.clear();
	Point_value.push_back(val);

	titleElement = doc.FirstChildElement("ROBOT")->FirstChildElement(value_m.c_str())->FirstChildElement("A3");
	title = titleElement->GetText();
	pval << title;
	pval >> val;
	pval.clear();
	Point_value.push_back(val);

	titleElement = doc.FirstChildElement("ROBOT")->FirstChildElement(value_m.c_str())->FirstChildElement("A4");
	title = titleElement->GetText();
	pval << title;
	pval >> val;
	pval.clear();
	Point_value.push_back(val);

	titleElement = doc.FirstChildElement("ROBOT")->FirstChildElement(value_m.c_str())->FirstChildElement("A5");
	title = titleElement->GetText();
	pval << title;
	pval >> val;
	pval.clear();
	Point_value.push_back(val);

	titleElement = doc.FirstChildElement("ROBOT")->FirstChildElement(value_m.c_str())->FirstChildElement("A6");
	title = titleElement->GetText();
	pval << title;
	pval >> val;
	pval.clear();
	Point_value.push_back(val);
    Point.push_back(Point_value);
}

void GetPointNum(XMLDocument &doc,unsigned int &k)
{
	const char* title;
	XMLElement* titleElement;
	vector<const char*> Point_value;

	titleElement = doc.FirstChildElement("ROBOT")->LastChildElement()->LastChildElement("NUM");
	title = titleElement->GetText();
	Point_value.push_back(title);
	stringstream numget;
	numget << title;
	numget >> k;
	printf("Name of play (2): %d\n", k);
}

void server_type_1(topic_test::srvtest &srv)
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


void server_type_2(topic_test::srvtest &srv,vector<vector<double> > &Point,unsigned int Point_sum,unsigned int &cunt)
{
    string t;
    //cin >> t;
    t = "y";
    if(t == "y")
    {
        Point_load(srv,Point,cunt);
        //cout << Point[cunt - 1][0] << endl;
        //cout << Point[cunt - 1][1] << endl;
        //cout << Point[cunt - 1][2] << endl;
        //cout << Point[cunt - 1][3] << endl;
        //cout << Point[cunt - 1][4] << endl;
        //cout << Point[cunt - 1][5] << endl;
        //cout << cunt << endl;
        cunt++;
    }
    else
    {
        cout<<"error";
    }
    if(cunt == 122)
    {
        cunt = 1;
    }
}




void Point_load(topic_test::srvtest &srv,vector<vector<double> > &Point,unsigned int Point_num)
{
    //cout << Point[Point_num-1][0] << endl;
    //cout << Point[Point_num-1][1] << endl;
    //cout << Point[Point_num-1][2] << endl;
    //cout << Point[Point_num-1][3] << endl;
    //cout << Point[Point_num-1][4] << endl;
    //cout << Point[Point_num-1][5] << endl;
    srv.request.A_value[0] = Point[Point_num-1][0]*M_PI/180;
    srv.request.A_value[1] = Point[Point_num-1][1]*M_PI/180;
    srv.request.A_value[2] = Point[Point_num-1][2]*M_PI/180;
    srv.request.A_value[3] = Point[Point_num-1][3]*M_PI/180;
    srv.request.A_value[4] = Point[Point_num-1][4]*M_PI/180;
    srv.request.A_value[5] = Point[Point_num-1][5]*M_PI/180;
    srv.request.A[0] = true;
    srv.request.A[1] = true;
    srv.request.A[2] = true;
    srv.request.A[3] = true;
    srv.request.A[4] = true;
    srv.request.A[5] = true;
    cout << Point_num << endl;
}