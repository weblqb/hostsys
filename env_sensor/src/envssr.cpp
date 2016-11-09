#include "ros/ros.h"
#include "std_msgs/String.h"
#include <wiringPi.h>
#include "bmp180.h"
#include <iostream>
#include <sstream>
#include <string>
#include "ui_oled/DataCallBack.h"

using namespace std;

BMP180 *ptrSensor;

bool temperatureBoardCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());
	stringstream ss;
	ss <<ptrSensor->read_temperature()<<" 'C" ;
	res.backdata=  ss.str();
	ROS_INFO("sent requst: %s", ss.str().c_str());
	return true;
}

bool AltitudeCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());
        stringstream ss;
        ss << ptrSensor->read_altitude() <<" meter";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        return true;
}

bool PressureCallback(ui_oled::DataCallBack::Request  &req,
         ui_oled::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());
        stringstream ss;
        ss << ptrSensor->read_pressure()<<" Pa";
        res.backdata=  ss.str();
        ROS_INFO("sent requst: %s", ss.str().c_str());
        return true;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "envssr");
  ros::NodeHandle n;
  if(wiringPiSetup() < 0){
     ROS_INFO("wiringPi failed");
      return 1;
  }
  BMP180 sensor;
  ptrSensor = &sensor;
  cout << sensor.read_altitude() <<endl;
  cout << sensor.read_temperature() <<endl;
  ros::ServiceServer service1 = n.advertiseService("temperatureBoard", temperatureBoardCallback);
  ros::ServiceServer service2 = n.advertiseService("Altitude", AltitudeCallback);
  ros::ServiceServer service3 = n.advertiseService("Pressure", PressureCallback);
  ROS_INFO("Ready to response.");
  ros::spin();
  return 0;
}

