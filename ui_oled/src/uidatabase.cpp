#include "uidatabase.h"

using namespace std;

UIdatabase::UIdatabase()
{
    for(int i = 0;i < 10;i++){
        mChains[i]=new Chain;
        mChains[i]->pFaterSection=NULL;
        mChains[i]->pHeadSection=NULL;
        mChains[i]->len=0;
    }
    mChNum=0;
}

UIdatabase::~UIdatabase()
{
    for(int i = 0;i < 10;i++){
        if(mChains[i]!=NULL && getChainhead(i)!=NULL){
            Section * pfd = getChainhead(i);
            Section * pfn = pfd->pSecNext;
            Section * pfhd = pfd;
            do{
                   delete pfd;
                   pfd = pfn;
                   pfn = pfn->pSecNext;
            }while(pfn!=pfhd);
        }
        delete mChains[i];
        mChains[i]=NULL;
    }
    mChNum=0;
}

void UIdatabase::NewChain()
{
    mChNum++;
}

void UIdatabase::AddSection(int indexChain, string title, string Abstract, string ReqCode, int ReqIndex, int indexDiveIn)
{
    Section * tmpSec;
    if(mChains[indexChain]->pHeadSection == NULL){
        tmpSec = new Section;
        mChains[indexChain]->pHeadSection = tmpSec;
        tmpSec->pSecNext = tmpSec;
        tmpSec->pSecPrevious = tmpSec;
        tmpSec->strTitle = title;
        tmpSec->strAbstracts = Abstract;
        tmpSec->strReqCode = ReqCode;
        tmpSec->dChainNext = indexDiveIn;
        tmpSec->dChain = indexChain;
		tmpSec->dReqIndex = ReqIndex;
        if(indexDiveIn>=0) mChains[indexDiveIn]->pFaterSection = tmpSec;
    }else{
        tmpSec = new Section;
        tmpSec->pSecNext = mChains[indexChain]->pHeadSection;
        tmpSec->pSecPrevious = mChains[indexChain]->pHeadSection->pSecPrevious;
        mChains[indexChain]->pHeadSection->pSecPrevious->pSecNext=tmpSec;
        mChains[indexChain]->pHeadSection->pSecPrevious=tmpSec;
        tmpSec->strTitle = title;
        tmpSec->strAbstracts = Abstract;
        tmpSec->strReqCode = ReqCode;
        tmpSec->dChainNext = indexDiveIn;
        tmpSec->dChain = indexChain;
		tmpSec->dReqIndex = ReqIndex;
        if(indexDiveIn>=0) mChains[indexDiveIn]->pFaterSection = tmpSec;
    }
    (mChains[indexChain]->len)++;
}

Section *UIdatabase::getChainhead(int index)
{
    return mChains[index]->pHeadSection;
}

int UIdatabase::getChainLen(int index)
{
    return mChains[index]->len;
}

Section *UIdatabase::getNextSec(Section *Sec)
{
    return Sec->pSecNext;
}

Section *UIdatabase::getPrevSec(Section *Sec)
{
    return Sec->pSecPrevious;
}

string UIdatabase::getTitle(Section *Sec)
{
    return Sec->strTitle;
}

string UIdatabase::getAbstract(Section *Sec)
{
    return Sec->strAbstracts;
}

string UIdatabase::getReqCode(Section *Sec)
{
    return Sec->strReqCode;
}

int getReqIndex(){
	return Sec->dReqIndex;
}


int UIdatabase::getChain(Section *Sec)
{
    return Sec->dChain;
}

int UIdatabase::getNextChain(Section *Sec)
{
    return Sec->dChainNext;
}

Section *UIdatabase::getFatherSec(int index)
{
    return mChains[index]->pFaterSection;
}
