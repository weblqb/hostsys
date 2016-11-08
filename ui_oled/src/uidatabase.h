#ifndef UIDATABASE_H
#define UIDATABASE_H

#include<string>

using namespace std;

struct Section{
    Section * pSecPrevious;
    Section * pSecNext;
    string strTitle;
    string strAbstracts;
    string strReqCode;
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
    void AddSection(int indexChain, string title, string Abstract, string ReqCode, int indexDiveIn);
    Section * getChainhead(int);
    int getChainLen(int);
    Section * getNextSec(Section * Sec);
    Section * getPrevSec(Section * Sec);
    string getTitle(Section * Sec);
    string getAbstract(Section * Sec);
    string getReqCode(Section * Sec);
    int getChain(Section * Sec);
    int getNextChain(Section * Sec);
    Section * getFatherSec(int);

};

#endif // UIDATABASE_H
