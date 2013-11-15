//====================================================================================
// @Title:      BUTTON
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpButton.cpp
// @Author:     Adnan Alam
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cmpButton.h"
#include "../../framework/include/cAssetMgr.h"

//====================================================================================
//                                                                           cmpButton
//====================================================================================

cmpButton::cmpButton(Point bPos, Point cursorPos, std::string imageFirst, std::string imageSecond)
{
	pos = bPos;
	cPos = cursorPos;
	stateUp = AssetMgr->Load<Texture>(imageFirst);
	stateDown = AssetMgr->Load<Texture>(imageSecond);
	state = stateUp;
	coll_rect = PRLX_Rect(pos, stateUp->dim);
}

void cmpButton::ButtonDraw()
{
	Engine->Graphics->Draw(state, pos);
}

bool cmpButton::collisionDetect()
{
	if(Engine->Physics->HitTest(coll_rect, PRLX_Point(cPos)))
	{
		state = stateUp;
		return true;
	}else{
		state = stateDown;
		return false;
	}
}

cmpButton::~cmpButton()
{
}