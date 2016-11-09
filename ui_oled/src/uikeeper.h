#ifndef UIKEEPER_H
#define UIKEEPER_H

#include <string>
#include <fstream>
#include "uidatabase.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "dispdriver.h"
#include <vector>

typedef string (*TrFunc)(string reqcode, int reqindex);

typedef void (*reccb)(const std_msgs::String::ConstPtr& msg);

using namespace std;

class UIkeeper
{
private:
    Section * mCurrentSection;
    UIdatabase * mpUIdt;
    DispDriver * mpDRI;
    TrFunc mReqFunc;
    bool isConstra;
    void Refresh();
    string extractAbstract(Section * sec);

public:
    UIkeeper(TrFunc pf);
	UIkeeper(TrFunc pf, ifstream & file, vector<ros::ServiceClient> & vecClnt, ros::NodeHandle & n);
    ~UIkeeper();
    void TurnNext();
    void TurnPrevious();
    void DiveIn();
    void Back();
    void RefreshAbstracts();
	void ConstructUI(ifstream & file, vector<ros::ServiceClient> & vecClnt, ros::NodeHandle & n);
};

#endif // UIKEEPER_H
