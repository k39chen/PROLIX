//====================================================================================
// @Title:      TWEEN
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cTween.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cTween.h"
#include "../../common/include/cBaseObject.h"
#include "../../common/include/xVector.h"
#include "../../framework/include/cLogMgr.h"
#include "../../framework/include/cTweenMgr.h"

// usability interface
void TWEEN::FromTo(cBaseObject *object, eObjectProperty propertyType, int duration, float from, float to, void (*FinishedTweenCB)())
{
	cTweenMgr::GetInstance()->Create(new cTween(object, propertyType, duration, from, to, FinishedTweenCB));
}

void TWEEN::FromTo(cBaseObject *object, eObjectProperty propertyType, int duration, int from, int to, void (*FinishedTweenCB)())
{
	FromTo(object, propertyType, duration, (float)from, (float)to, FinishedTweenCB);
}

//====================================================================================
//                                                                              cTween
//====================================================================================
cTween::cTween(cBaseObject *rObject, eObjectProperty rProperty, int rDuration, float rFrom, float rTo, void (*rFinishedTweenCB)())
{
    mObject = rObject;
    mProperty = rProperty;
    mFrom = rFrom;
    mTo = rTo;
    mActive = false;
    mDuration = rDuration;
    mTimer = 0;
	mCanDelete = false;
    FinishedTweenCB = rFinishedTweenCB;
}

bool cTween::operator==(cTween *Tween)
{
	return	mObject == Tween->Object() &&
			mProperty == Tween->Property();
			//mDuration == Tween->Duration() &&
			//mFrom == Tween->From() &&
			//mTo == Tween->To();
}

void cTween::Play()
{
    // if the tween is already playing, update and don't interrupt current process
    if (mActive)
    {
        return;
    }

    // start the tween from start
    if (mTimer == 0)
    {
        CalculateStep();
        mActive = true;

        switch (mProperty)
        {
        case ALPHA:
            mObject->mAlpha = mFrom;
            break;
        case MOD_R:
            mObject->mFilter.r = (int)mFrom;
            break;
        case MOD_G:
            mObject->mFilter.g = (int)mFrom;
            break;
        case MOD_B:
            mObject->mFilter.b = (int)mFrom;
            break;
        case SCALE_X:
            mObject->mScaleX = mFrom;
            break;
        case SCALE_Y:
            mObject->mScaleY = mFrom;
            break;
        case POS_X:
            mObject->mPos.x = (int)mFrom;
            mMotion.pos.x = mFrom;
            break;
        case POS_Y:
            mObject->mPos.y = (int)mFrom;
            mMotion.pos.y = mFrom;
            break;
        case ROTATION:
            mObject->mRotation = mFrom;
            break;
        default:
            LogMgr->Write(FATAL, "cTween::Play >>>> Given invalid property. Ignoring tween command.");
            break;
        }
    }
}

void cTween::CalculateStep()
{
    switch (mProperty)
    {
    case ALPHA:
        mAlpha = (mTo - mFrom)/mDuration;
        break;
    case MOD_R:
        mModR = (int)((mTo - mFrom)/mDuration);
        break;
    case MOD_G:
        mModG = (int)((mTo - mFrom)/mDuration);
        break;
    case MOD_B:
        mModB = (int)((mTo - mFrom)/mDuration);
        break;
    case SCALE_X:
        mScaleX = (mTo - mFrom)/mDuration;
        break;
    case SCALE_Y:
        mScaleY = (mTo - mFrom)/mDuration;
        break;
    case POS_X:
        mMotion.vel.x = (mTo - mFrom)/mDuration;
        break;
    case POS_Y:
        mMotion.vel.y = (mTo - mFrom)/mDuration;
        break;
    case ROTATION:
        mRotation = (mTo - mFrom)/mDuration;
        break;
    default:
        LogMgr->Write(FATAL, "cTween::CalculateStep >>>> Given invalid property. Ignoring tween command.");
        break;
    }
}

void cTween::Update()
{
    if (IsComplete())
    {
        Stop();
		if (FinishedTweenCB)
        {
            FinishedTweenCB();
        }
		mCanDelete = true;
    }

    if (mActive)
    {
        mMotion.Move();
        
        switch (mProperty)
        {
        case ALPHA:
            mObject->mAlpha += mAlpha;
            break;
        case MOD_R:
            mObject->mFilter.r += mModR;
            break;
        case MOD_G:
            mObject->mFilter.g += mModG;
            break;
        case MOD_B:
            mObject->mFilter.b += mModB;
            break;
        case SCALE_X:
            mObject->mScaleX += mScaleX;
            break;
        case SCALE_Y:
            mObject->mScaleY += mScaleY;
            break;
        case POS_X:
            mObject->mPos.x = (int)mMotion.pos.x;
            break;
        case POS_Y:
            mObject->mPos.y = (int)mMotion.pos.y;
            break;
        case ROTATION:
            mObject->mRotation += mRotation;
            break;
        default:
            LogMgr->Write(FATAL, "cTween::Update >>>> Given invalid property. Ignoring tween command.");
            break;
        }
        
        mTimer++;
    }
}

bool cTween::IsComplete()
{
    return (mTimer >= mDuration);
}

void cTween::Stop()
{
    mActive = false;
    mTimer = 0;

    switch (mProperty)
    {
    case ALPHA:
        mObject->mAlpha = mTo;
        break;
    case MOD_R:
        mObject->mFilter.r = (int)mTo;
        break;
    case MOD_G:
        mObject->mFilter.g = (int)mTo;
        break;
    case MOD_B:
        mObject->mFilter.b = (int)mTo;
        break;
    case SCALE_X:
        mObject->mScaleX = mTo;
        break;
    case SCALE_Y:
        mObject->mScaleY = mTo;
        break;
    case POS_X:
        mObject->mPos.x = (int)mTo;
        break;
    case POS_Y:
        mObject->mPos.y = (int)mTo;
        break;
    case ROTATION:
        mObject->mRotation = mTo;
        break;
    default:
        LogMgr->Write(FATAL, "cTween::Stop >>>>> Given invalid property. Ignoring tween command.");
        break;
    }
}

cTween::~cTween()
{
}

// get functions
cBaseObject *cTween::Object() const       {return mObject;}
bool cTween::Active() const               {return mActive;}
eObjectProperty cTween::Property() const  {return mProperty;}
int cTween::Duration() const              {return mDuration;}
float cTween::From() const                {return mFrom;}
float cTween::To() const                  {return mTo;}

// set functions
void cTween::Object(cBaseObject *newObject)        {mObject = newObject;}
void cTween::Property(eObjectProperty newProperty) {mProperty = newProperty;}
void cTween::Duration(int newDuration)             {mDuration = newDuration;}
void cTween::From(float newFrom)                   {mFrom = newFrom;}
void cTween::To(float newTo)                       {mTo = newTo;}