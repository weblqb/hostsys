#include "uikeeper.h"
#include <iostream>

using namespace std;

void UIkeeper::Refresh()
{
    mpDRI->SSD1306_clear();
    //print titles
    mpDRI->SSD1306_string(0, 2, "<", 12, 1);
    mpDRI->SSD1306_string(6, 2, (mCurrentSection->pSecPrevious->strTitle).c_str(), 12, 1);
    int dttoffset;
    switch((mCurrentSection->strTitle).length()){
    case 1:
        dttoffset=61;
        break;
    case 2:
        dttoffset=58;
        break;
    case 3:
        dttoffset=55;
        break;
    case 4:
        dttoffset=52;
        break;
    case 5:
        dttoffset=49;
        break;
    default:
        dttoffset=49;
        break;
    }
    mpDRI->SSD1306_string(dttoffset, 2, (mCurrentSection->strTitle).c_str(), 12, 0);

    switch((mCurrentSection->pSecNext->strTitle).length()){
    case 1:
        dttoffset=116;
        break;
    case 2:
        dttoffset=110;
        break;
    case 3:
        dttoffset=104;
        break;
    case 4:
        dttoffset=98;
        break;
    case 5:
        dttoffset=92;
        break;
    default:
        dttoffset=92;
        break;
    }
    mpDRI->SSD1306_string(dttoffset, 2, (mCurrentSection->pSecNext->strTitle).c_str(), 12, 1);
    mpDRI->SSD1306_string(122, 2, ">", 12, 1);

    //print abstracts

    if(mCurrentSection->dChainNext<0){
        mpDRI->SSD1306_string(0, 18+16, "[", 12, 1);
        mpDRI->SSD1306_string(122, 18+16, "]", 12, 1);
		string strTmp = mReqFunc(mCurrentSection->strReqCode, mCurrentSection->dReqIndex);
        if(strTmp.length()>19) strTmp = strTmp.substr(0,19);
        mpDRI->SSD1306_string(64-strTmp.length()*3, 18+16, strTmp.c_str(), 12, 1);
    }else{
        if(mpUIdt->getChainLen(mpUIdt->getNextChain(mCurrentSection))>0){
            mpDRI->SSD1306_string(0, 18, "[", 12, 1);
            mpDRI->SSD1306_string(122, 18, "]", 12, 1);
            string strTmp = extractAbstract(mpUIdt->getChainhead(mCurrentSection->dChainNext));
            if(strTmp.length()>19) strTmp = strTmp.substr(0,19);
            mpDRI->SSD1306_string(64-strTmp.length()*3, 18, strTmp.c_str(), 12, 1);
        }
        if(mpUIdt->getChainLen(mpUIdt->getNextChain(mCurrentSection))>1){
            mpDRI->SSD1306_string(0, 18+16, "[", 12, 1);
            mpDRI->SSD1306_string(122, 18+16, "]", 12, 1);
            string strTmp = extractAbstract(mpUIdt->getChainhead(mCurrentSection->dChainNext)->pSecNext);
            if(strTmp.length()>19) strTmp = strTmp.substr(0,19);
            mpDRI->SSD1306_string(64-strTmp.length()*3, 18+16, strTmp.c_str(), 12, 1);
        }
        if(mpUIdt->getChainLen(mpUIdt->getNextChain(mCurrentSection))>2){
            mpDRI->SSD1306_string(0, 18+16+16, "[", 12, 1);
            if(mpUIdt->getChainLen(mpUIdt->getNextChain(mCurrentSection))>3){
                mpDRI->SSD1306_string(120, 18+16+16, "]..", 12, 1);
                string strTmp = extractAbstract(mpUIdt->getChainhead(mCurrentSection->dChainNext)->pSecNext);
                if(strTmp.length()>17) strTmp = strTmp.substr(0,17);
                mpDRI->SSD1306_string(63-strTmp.length()*3, 18+16+16, strTmp.c_str(), 12, 1);
            }else{
                mpDRI->SSD1306_string(122, 18+16+16, "]", 12, 1);
                string strTmp = extractAbstract(mpUIdt->getChainhead(mCurrentSection->dChainNext)->pSecNext->pSecNext);
                if(strTmp.length()>19) strTmp = strTmp.substr(0,19);
                mpDRI->SSD1306_string(64-strTmp.length()*3, 18+16+16, strTmp.c_str(), 12, 1);
            }
        }

    }
    mpDRI->SSD1306_display();
}

string UIkeeper::extractAbstract(Section *sec)
{
    return sec->strAbstracts;
}

UIkeeper::UIkeeper(TrFunc pf)
{
    mpUIdt = new UIdatabase();
    mpDRI = new DispDriver();
    mReqFunc = pf;
    isConstra=false;
}

UIkeeper::UIkeeper(TrFunc pf, ifstream & file, vector<ros::ServiceClient> & vecClnt, ros::NodeHandle & n)
{
    mpUIdt = new UIdatabase();
    mpDRI = new DispDriver();
    mReqFunc = pf;
    isConstra = false;
    ConstructUI(file, vecClnt, n);
}

UIkeeper::~UIkeeper()
{
    delete mpUIdt;
    delete mpDRI;
    mpUIdt = NULL;
    mpDRI = NULL;
}

void UIkeeper::TurnNext()
{
    mCurrentSection = mpUIdt->getNextSec(mCurrentSection);
    Refresh();
}

void UIkeeper::TurnPrevious()
{
    mCurrentSection = mpUIdt->getPrevSec(mCurrentSection);
    Refresh();
}

void UIkeeper::DiveIn()
{
    if(mpUIdt->getNextChain(mCurrentSection)>=0){
        mCurrentSection = mpUIdt->getChainhead(mpUIdt->getNextChain(mCurrentSection));
    }
    Refresh();
}

void UIkeeper::Back()
{
    if(mpUIdt->getFatherSec(mpUIdt->getChain(mCurrentSection))!=NULL)
    mCurrentSection = mpUIdt->getFatherSec(mpUIdt->getChain(mCurrentSection));
    Refresh();
}

void UIkeeper::RefreshAbstracts()
{

}

void UIkeeper::ConstructUI(ifstream & file, vector<ros::ServiceClient> & vecClnt, ros::NodeHandle & n)
{
    int dChainNum,
        arrSecNum[10];
    int indexChain; //
    string title;
    string Abstract;
    string ReqCode;
    int indexDiveIn;

    file>>dChainNum;
    for(int i = 0;i < dChainNum;i++){
        file>>arrSecNum[i];
    }
    for(int i = 0;i < dChainNum;i++){
        mpUIdt->NewChain();
        for(int j = 0;j < arrSecNum[i];j++){
            //file >> indexChain >> title >> Abstract >> ReqCode >> indexDiveIn;
            file >> indexChain;
            getline(file, title); // read a single enter
            getline(file, title);
            getline(file, Abstract);
            getline(file, ReqCode);
            file >> indexDiveIn ;
            if(title.length()>5) title= title.substr(0,5); //the lenght of titles can not be longer than 5.
			if (indexDiveIn == -1){
				vecClnt.push_back(n.n.serviceClient<env_sensor::DataCallBack>(ReqCode.c_str()));
				mpUIdt->AddSection(indexChain, title, Abstract, ReqCode, vecClnt.length()-1, indexDiveIn);
			}
			else{
				mpUIdt->AddSection(indexChain, title, Abstract, ReqCode, -1, indexDiveIn);
			}
			
        }
    }
    mCurrentSection = mpUIdt->getChainhead(0);
    isConstra=true;
    Refresh();
}
