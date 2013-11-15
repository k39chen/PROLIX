//====================================================================================
// @Title:      BASE OBJECT
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cBaseObject.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cBaseObject.h"
#include "../../engine/include/PrlxEngine.h"
#include "../../framework/include/cAssetMgr.h"
#include <iostream>
#include <cmath>

//====================================================================================
//                                                                         cBaseObject
//====================================================================================
cBaseObject::cBaseObject()
{
    Initialize();
}

cBaseObject::cBaseObject(cTexture *rSource)
{
	Initialize();
	Source(rSource);

}

cBaseObject::cBaseObject(cBaseObject *rParent, cTexture *rSource)
{
	Initialize();
	SetParent(rParent);
	Source(rSource);
}

cBaseObject::cBaseObject(cBaseObject *rParent, cBaseObject *rChildren, cTexture *rSource)
{
	Initialize();
	SetParent(rParent);
	mChildren.push_back(rChildren);
	Source(rSource);	
}

cBaseObject::cBaseObject(cBaseObject *rParent, std::vector<cBaseObject *> rChildren, cTexture *rSource)
{
	Initialize();
	SetParent(rParent);
	mChildren.assign(rChildren.begin(), rChildren.end());
	Source(rSource);
}

void cBaseObject::Initialize()
{
	Source(NULL);

	mParent = NULL;
	mChildren.clear();

    mVisible = true;

    mPos = Point(0,0);
    mAlpha = 1.0f;
    mFilter = cColor(255,255,255,(int)(255 * mAlpha));
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mRotation = 0.0f;

    mCollRect = NULL;
    mCollCirc = NULL;
    mCollPoint = NULL;
}

void cBaseObject::SetParent(cBaseObject *Object)
{	
	mParent = Object;
}

void cBaseObject::AddChild(cBaseObject *Object)
{
	mChildren.push_back(Object);
}

/******************************************************************************************/
// We don't want to have to use this function. Messes up deeper children.
/******************************************************************************************/
void cBaseObject::RemoveChild(cBaseObject *Object)
{
	unsigned int index;
	bool found = false;

    for (index = 0; index < mChildren.size(); index++)
    {
        if (mChildren[index] == Object)
        {
			found = true;
            break;
        }
    }

	if (found) mChildren.erase(mChildren.begin() + index);
}
/******************************************************************************************/

void cBaseObject::Display(Point offset, PRLX_Rect *clip)
{
    // reject draw request when source is not yet specified
    if (mSource == NULL)
    {
        return;
    }

	bool absVisible		= mVisible;
    float absAlpha		= mAlpha;
    Point absPos		= mPos;
    cColor absFilter	= mFilter;
    float absScaleX		= mScaleX;
    float absScaleY		= mScaleY;
    float absRotation	= mRotation;

	bool definitelyInvisible = false;

	// inherit parent's properties
	for (cBaseObject *iterator = mParent; iterator != NULL; iterator = iterator->mParent)
	{
		absPos = absPos + iterator->mPos;
		absScaleX = absScaleX * iterator->mScaleX;
		absScaleY = absScaleY * iterator->mScaleY;
		absRotation = absRotation + iterator->mRotation;

		absAlpha *= iterator->mAlpha;

		absFilter = cColor(
			(absFilter.r + iterator->mFilter.r),
			(absFilter.g + iterator->mFilter.g),
			(absFilter.b + iterator->mFilter.b),
			(absFilter.a + iterator->mFilter.a)
		);

		if (!definitelyInvisible || absVisible)
		{
			if (!iterator->mVisible)
			{
				absVisible = false;
				definitelyInvisible = true;
			}
		}
	}

    if (absVisible) 
    {
        mSource->DrawExt(
			absPos + offset, cColor(absFilter.r, absFilter.g, absFilter.b, (int)(absAlpha * 255)),
            absScaleX, absScaleY, absRotation, clip
        );
	}   
}

void cBaseObject::Update() 
{
    if (mAlpha <= 0.0f) mAlpha = 0.0f;
	if (mAlpha > 0.0f && mVisible) Display();
}

cBaseObject::~cBaseObject()
{
}

void cBaseObject::Source(cTexture *newVal)
{
    mSource = newVal;
    
	if (mSource != NULL)
	{
		mCollPoint = new PRLX_Point(mPos);
		mCollRect = new PRLX_Rect(mPos, mSource->dim);
		mCollCirc = new PRLX_Circle(mPos + Point(mSource->dim.w/2, mSource->dim.h/2), (int)(std::min(mSource->dim.w, mSource->dim.h) / 2));
	}
}

void cBaseObject::Visible(bool newVal)					{mVisible = newVal;}
void cBaseObject::Alpha(float newVal)					{mAlpha = newVal;}
void cBaseObject::Position(int newX, int newY)			{mPos = Point(newX, newY);}
void cBaseObject::Filter(int newR, int newG, int newB)	{mFilter = cColor(newR, newG, newB);}
void cBaseObject::ScaleX(float newVal)					{mScaleX = newVal;}
void cBaseObject::ScaleY(float newVal)					{mScaleY = newVal;}
void cBaseObject::Rotation(float newVal)				{mRotation = newVal;}

cTexture *cBaseObject::Source() const	{return mSource;}
bool cBaseObject::Visible() const		{return mVisible;}
float cBaseObject::Alpha() const		{return mAlpha;}
Point cBaseObject::Position() const		{return mPos;}
cColor cBaseObject::Filter() const		{return mFilter;}
float cBaseObject::ScaleX() const		{return mScaleX;}
float cBaseObject::ScaleY() const		{return mScaleY;}
float cBaseObject::Rotation() const		{return mRotation;}