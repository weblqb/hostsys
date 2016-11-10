#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "ui_oled/DataCallBack.h"

using namespace std;

bool SDCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());
    if(req.reqcd == string("SystemSDCK")){
        stringstream ss;
        ss << "Shuting Down";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        system("sudo poweroff");
    }else{
        stringstream ss;
        ss << "Shut Down";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
    }
  return true;
}

bool RBCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());
    if(req.reqcd == string("SystemSDCK")){
        stringstream ss;
        ss << "Shuting Down";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        system("sudo reboot");
    }else{
        stringstream ss;
        ss << "Reboot!";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
    }
  return true;
}

bool CPUTCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

  return true;
}

bool CPUFCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

  return true;
}

bool CPUUCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

  return true;
}

bool GPUTCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

  return true;
}

bool RAMUCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "syscdtsrv");
  ros::NodeHandle n;
  system("free");
  ros::ServiceServer service1 = n.advertiseService("SystemCPUT", CPUTCallback);
  ros::ServiceServer service2 = n.advertiseService("SystemCPUF", CPUFCallback);
  ros::ServiceServer service3 = n.advertiseService("SystemCPUU", CPUUCallback);
  ros::ServiceServer service4 = n.advertiseService("SystemGPUT", GPUTCallback);
  ros::ServiceServer service5 = n.advertiseService("SystemRAMU", RAMUCallback);
  ros::ServiceServer service6 = n.advertiseService("SystemSD", SDCallback);
  ros::ServiceServer service7 = n.advertiseService("SystemRB", RBCallback);
  ROS_INFO("Ready to response.");
  ros::spin();
  return 0;
}

