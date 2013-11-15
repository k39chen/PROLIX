//====================================================================================
// @Title:      BASE OBJECT
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cBaseObject.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Base structure for in game entities and objects. Template for polling keyboard
//  and mouse events, physics collision detections and movement, and single texture 
//  instances actions.
//
//====================================================================================
#ifndef __PROLIX_COMMON_BASE_OBJECT_H__
#define __PROLIX_COMMON_BASE_OBJECT_H__

#include <SDL.h>
#include <vector>
#include "../../common/include/cTexture.h"
#include "../../engine/include/PrlxPhysics.h"

// eObjectProperty
enum eObjectProperty
{
    ALPHA,
    MOD_R,
    MOD_G,
    MOD_B,
    SCALE_X,
    SCALE_Y,
    POS_X,
    POS_Y,
    ROTATION
};

//====================================================================================
//                                                                         cBaseObject
//====================================================================================
class cBaseObject
{
  private:
	friend class cTween;

  protected:
	cTexture *mSource;	// source
	bool mVisible;		// state of object visibility
    float mAlpha;		// opacity of object (%)
    Point mPos;			// position of object (x,y)
    cColor mFilter;		// color filter
    float mScaleX;		// scaling of X plane
    float mScaleY;		// scaling of Y plane
    float mRotation;	// current rotation of the object

	PRLX_Rect *mCollRect;	// collision rectangle
    PRLX_Circle *mCollCirc; // collision circle
    PRLX_Point *mCollPoint; // collision point

	cBaseObject *mParent;
	std::vector<cBaseObject *> mChildren;

  public:
	// Constructors
	cBaseObject();
	cBaseObject(cTexture *Source);
	cBaseObject(cBaseObject *Parent, cTexture *Source = NULL);
	cBaseObject(cBaseObject *Parent, cBaseObject *Children, cTexture *Source = NULL);
	cBaseObject(cBaseObject *Parent, std::vector<cBaseObject *> Children, cTexture *Source = NULL);
    
	// Destructor
	~cBaseObject();
	
    virtual void Initialize();              // initialize properties
    virtual void Update();                  // move and draw object

	// render object
	virtual void Display(Point offset = Point(0,0), PRLX_Rect *clip = NULL);

	void SetParent(cBaseObject *Object);		// sets a parent object
	void AddChild(cBaseObject *Object);			// adds an immediate child object
	void RemoveChild(cBaseObject *Object);		// removes immediate child object

	// getters
	cTexture *Source() const;
	bool Visible() const;
	float Alpha() const;
	Point Position() const;
	cColor Filter() const;
	float ScaleX() const;
	float ScaleY() const;
	float Rotation() const;

	// setters
    void Source	(cTexture *newVal);
	void Visible(bool newVal);
	void Alpha(float newVal);
	void Position(int newX, int newY);
	void Filter(int newR, int newG, int newB);
	void ScaleX(float newVal);
	void ScaleY(float newVal);
	void Rotation(float newVal);

};

#endif