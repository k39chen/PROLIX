//====================================================================================
// @Title:      CURSOR
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cCursor.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cCursor.h"
#include "../../engine/include/PrlxEngine.h"
#include "../../engine/include/PrlxGraphics.h"
#include "../../framework/include/cAssetMgr.h"

//====================================================================================
//                                                                             cCursor
//====================================================================================
cCursor::cCursor()
{
	// hide default system Cursor
	SDL_ShowCursor(SDL_DISABLE);

    mImage = AssetMgr->Load<Texture>("cursor.png");

	// set initial position
	pos = Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	
	// set pointer size
	size = 1;

	// set pointer bounding box
	coll_rect.dim.w = size;
	coll_rect.dim.h = size;
}

void cCursor::Move() 
{
    pos = Engine->Input->Mouse->pos;
    coll_rect.pos = pos;
}

void cCursor::Update()
{
    Move();
    Draw();
}

void cCursor::Draw()
{
    mImage->Draw(pos);
}

cCursor::~cCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}