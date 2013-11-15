//====================================================================================
// @Title:      TWEEN MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cTweenMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cTweenMgr.h"
#include "../../common/include/cTween.h"
#include "../../framework/include/cLogMgr.h"

//====================================================================================
//                                                                           cTweenMgr
//====================================================================================
cTweenMgr *cTweenMgr::mInstance = NULL;

cTweenMgr::cTweenMgr()
{
}

cTweenMgr *cTweenMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cTweenMgr();
        return mInstance;
    }
    return mInstance;
}

void cTweenMgr::Create(cTween *Tween)
{
	for each (cTween *registeredTween in mRegisteredTweens)
	{
		if (*registeredTween == Tween)
		{
			delete Tween;
			return;
		}
	}

	Register(Tween);
}

void cTweenMgr::Register(cTween *Tween)
{
	mRegisteredTweens.push_back(Tween);
	Tween->Play();
}

void cTweenMgr::Update()
{
	if (mRegisteredTweens.size() == 0) return;

    for (unsigned int i=0; i<mRegisteredTweens.size(); i++)
    {
		if (mRegisteredTweens[i]->mCanDelete)
		{
			delete mRegisteredTweens[i];
			mRegisteredTweens.erase(mRegisteredTweens.begin() + i);
			i--;
			continue;
		}
		mRegisteredTweens[i]->Update();
    }
}

unsigned int cTweenMgr::GetNumRegistered()
{
    return mRegisteredTweens.size();
}

bool cTweenMgr::RegisteredForProperty(cBaseObject *object, eObjectProperty propertyType)
{
	for each (cTween *Tween in mRegisteredTweens)
	{
		if (Tween->Object() == object && Tween->Property() == propertyType)
		{
			return true;
		}
	}
	return false;
}

cTweenMgr::~cTweenMgr()
{
}