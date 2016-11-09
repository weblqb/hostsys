#include "ros/ros.h"
#include "std_msgs/String.h"
#include <wiringPi.h>
#include "bmp180.h"
#include <iostream>
#include <sstream>
#include <string>
#include "env_sensor/DataCallBack.h"

using namespace std;

BMP180 *ptrSensor;

bool chatterCallback(env_sensor::DataCallBack::Request  &req,
         env_sensor::DataCallBack::Response &res)
{
    ROS_INFO("Got a call: [%s]", req.reqcd.c_str());

    if(req.reqcd== string("temperatureBoard")){
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
    }
  return false;
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
  ros::ServiceServer service = n.advertiseService("ivkcast", chatterCallback);
  ROS_INFO("Ready to response.");
  ros::spin();
  return 0;
}

