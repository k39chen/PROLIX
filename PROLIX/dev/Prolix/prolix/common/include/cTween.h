//====================================================================================
// @Title:      TWEEN
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cTween.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Controls the animation from one point to another which gives a smooth flow
//  between the two points.
//
//====================================================================================
#ifndef __PROLIX_COMMON_TWEEN_H__
#define __PROLIX_COMMON_TWEEN_H__

#include "../../engine/include/PrlxPhysics.h"

class cBaseObject;
enum eObjectProperty;

// usability interface
//  - We shouldn't have to do anything with cTween, or cTweenMgr and can do everything
// with just Tween.
static struct TWEEN
{
	void FromTo(cBaseObject *object, eObjectProperty propertyType, int duration, float from, float to, void (*FinishedTweenCB)() = NULL);
	void FromTo(cBaseObject *object, eObjectProperty propertyType, int duration, int from, int to, void (*FinishedTweenCB)() = NULL);
	// with bounce
	// with acceleration
	// ... extra stuff

} Tween;

//====================================================================================
//                                                                              cTween
//====================================================================================
class cTween
{
	friend class cTweenMgr;

    cBaseObject *mObject;
    eObjectProperty mProperty;
    float mFrom;
    float mTo;
    bool mActive;
    int mDuration;  // milliseconds
    int mTimer;
	bool mCanDelete;

    // variables used to track per/frame steppings
    PrlxPhysics::Motion mMotion;
    float mAlpha;
    int mModR;
    int mModG;
    int mModB;
    float mScaleX;
    float mScaleY;
    float mRotation;

    void (*FinishedTweenCB)();

public:
	bool operator==(cTween *Tween);

    void Play();
    void Update();
    bool IsComplete();
    void Stop();
    void CalculateStep();

    // get functions
    cBaseObject *Object() const;
    bool Active() const;
    eObjectProperty Property() const;
    int Duration() const;
    float From() const;
    float To() const;

    // set functions
    void Object(cBaseObject *newObject);
    void Property(eObjectProperty newProperty);
    void Duration(int newDuration);
    void From(float newFrom);
    void To(float newTo);

    cTween(cBaseObject *rObject, eObjectProperty rProperty, int rDuration, float rFrom, float rTo, void (*FinishedTweenCB)() = NULL);
    ~cTween();
};

#endif