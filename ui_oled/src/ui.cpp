#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include "uikeeper.h"
#include "keyscaner.h"
#include "env_sensor/DataCallBack.h"

using namespace std;

string uiofile("/home/pi/catkin_ws/src/ui_oled/src/UIdata.oui");
ifstream ifs;
ros::ServiceClient * ptrclient;

string Transport(string reqcode){
    env_sensor::DataCallBack srv;
    srv.request.reqcd = reqcode;
     if (ptrclient->call(srv))
    {
         ROS_INFO("receive: %s", srv.response.backdata.c_str());
         return srv.response.backdata;
    }else{
         ROS_INFO("Failed to call service add_two_ints");
         return string("-No Data-");
    }

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ui");
  ros::NodeHandle n;
  ros::Rate loop_rate(100);
  ros::ServiceClient client = n.serviceClient<env_sensor::DataCallBack>("ivkcast");
  ptrclient = &client;
  if(wiringPiSetup() < 0){
      ROS_INFO("wiringPi failed");
      return 1;
  }
  ifs.open(uiofile.c_str());
  if(!ifs.is_open()){
      cout<<"file failed"<<endl;
      return 1;
  }
  UIkeeper *UIK = new UIkeeper(Transport,ifs);
  KeyScaner KSC;
  ROS_INFO("init done.");
  while (ros::ok())
  {
      switch(KSC.ScanKeys()){
      case KEYU:
            UIK->Back();
          break;
      case KEYD:
            UIK->DiveIn();
          break;
      case KEYL:
            UIK->TurnPrevious();
          break;
      case KEYR:
            UIK->TurnNext();
          break;
      case KEYC:

          break;
      }


    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
// %EndTag(FULLTEXT)%