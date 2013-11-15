//====================================================================================
// @Title:      CURSOR
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cCursor.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Abstracted data type for replacing default operating system Cursor. Behaves
//  identically to mouse instance cMouse as implemented in game_engine_input.h
//
//====================================================================================
#ifndef __PROLIX_INTERFACE_CURSOR_H__
#define __PROLIX_INTERFACE_CURSOR_H__

#include <SDL.h>
#include <string>
#include <vector>
#include "../../common/include/cTexture.h"
#include "../../engine/include/PrlxPhysics.h"

//====================================================================================
//                                                                             cCursor
//====================================================================================
class cCursor
{
    cTexture *mImage;

public:
    Point pos;              // position of the cursor
    PRLX_Rect coll_rect;    // collision rectangle

	int size;       // size of the pointer bounding box (pointer precision)
	void Move();    // handle move Cursor events
    void Update();  // update the cursor
    void Draw();    // draw the cursor

	cCursor();      // Constructor
	~cCursor();     // Destructor
};

#endif