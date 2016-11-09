#ifndef UIDATABASE_H
#define UIDATABASE_H

#include<string>

using namespace std;

//Section contains the information to show on the screen
// A whole view of the screen is shown like:
// <[Previous]  [Title of this]  [Next]>
// [  1st title of the next of chain   ]
// [  2st title of the next of chain   ]
// [  3st title of the next of chain]...(if the number of nodes is more than 3, the ellipsis will be shown)

// if the Section has not a next level chain, the view will be like :
// <[Previous]  [Title of this]  [Next]>
// 
// [            Abstraction            ]
// 

struct Section{
    Section * pSecPrevious;	// pointer to the previous Section(node)
    Section * pSecNext;		// pointer to the next Section
    string strTitle;		// Title of the Section
    string strAbstracts;	// Title
    string strReqCode;      // a string as the name of request in ROS
	int dReqIndex;
    int dChain;
    int dChainNext;
};

struct Chain{

    Section * pHeadSection;
    Section * pFaterSection;
    int len;
};

class UIdatabase
{
private:


    Chain * mChains[10];
    int mChNum;
public:
    UIdatabase();
    ~UIdatabase();
    void NewChain();
	void AddSection(int indexChain, string title, string Abstract, string ReqCode, int dReqIndex, int indexDiveIn);
    Section * getChainhead(int);
    int getChainLen(int);
    Section * getNextSec(Section * Sec);
    Section * getPrevSec(Section * Sec);
    string getTitle(Section * Sec);
    string getAbstract(Section * Sec);
    string getReqCode(Section * Sec);
	int getReqIndex(Section * Sec);
    int getChain(Section * Sec);
    int getNextChain(Section * Sec);
    Section * getFatherSec(int);

};

#endif // UIDATABASE_H
