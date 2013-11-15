//====================================================================================
// @Title:      BUTTON
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpButton.h
// @Author:     Adnan Alam
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  A derived class of cmpWindow that supports 
//
//====================================================================================
#ifndef __PROLIX_INTERFACE_BUTTON_H__
#define __PROLIX_INTERFACE_BUTTON_H__

#include "../../engine/include/PrlxEngine.h"
#include "../../common/include/cCartesian.h"
#include "../../common/include/xDraw.h"
#include "../../engine/include/PrlxPhysics.h"
struct cmpButton
{
	Dimensions dim;
	Point pos, cPos;
	cTexture *stateUp, *stateDown, *state;
	PRLX_Rect coll_rect;


	void ButtonDraw ();
	bool collisionDetect();
	cmpButton(
		Point position = Point(0,0),
		Point cPosition = Point (0,0),
		std::string imageOne = "but1.png",
		std::string imageTwo = "but2.png" );

	~cmpButton();	
};
#endif