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
#include <vector>
#include "uikeeper.h"
#include "keyscaner.h"
#include "ui_oled/DataCallBack.h"

using namespace std;

string uiofile("/home/pi/catkin_ws/src/ui_oled/src/UIdata.oui");
ifstream ifs;
vector<ros::ServiceClient> vecClnt;
ros::ServiceClient * ptrclient;

string Transport(string reqcode, int reqindex){
    ui_oled::DataCallBack srv;
    srv.request.reqcd = reqcode;
    ROS_INFO("send: %d - %s", reqindex,reqcode.c_str());
     if (vecClnt[reqindex].call(srv))
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
  //ros::ServiceClient client = n.serviceClient<ui_oled::DataCallBack>("ivkcast");
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
  UIkeeper *UIK = new UIkeeper(Transport, ifs, vecClnt, n);
  KeyScaner KSC;
  ROS_INFO("init done.");
  int cnt=0;
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

    if(cnt>=50){
        cnt=0;
        UIK->RefreshAbstracts();
    }else{
        cnt++
    }
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
// %EndTag(FULLTEXT)%
