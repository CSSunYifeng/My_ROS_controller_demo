#pragma once

#ifndef XMLSOURCE
#define XMLSOURCE


//#include "pch.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#endif // XMLSOURCE
using namespace tinyxml2;
using namespace std;

void Position_Xml_node_add(double &xx, double &yy, double &zz, int &i, XMLDocument &doc);
void load_xml_node(int &i, vector<const char*> Point_value, vector<vector<const char*> > Point);
void GetPointNum();