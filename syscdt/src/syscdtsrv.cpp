#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "ui_oled/DataCallBack.h"

using namespace std;

bool chatterCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

/*    if(req.reqcd== string("temperatureBoard")){
        stringstream ss;
        ss <<ptrSensor->read_temperature()<<" 'C" ;
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        return true;
    }else if(req.reqcd== string("Altitude")){
        stringstream ss;
        ss << ptrSensor->read_altitude() <<" meter";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        return true;
    }else if(req.reqcd == string("Pressure")){
        stringstream ss;
        ss << ptrSensor->read_pressure()<<" Pa";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        return true;
    }*/
  return false;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "syscdtsrv");
  ros::NodeHandle n;
  system("free");
  ros::ServiceServer service = n.advertiseService("ivkcast", chatterCallback);
  ROS_INFO("Ready to response.");
  ros::spin();
  return 0;
}

