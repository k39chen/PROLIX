//====================================================================================
// @Title:      WINDOW
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpWindow.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Creates a window for the game interface. Serves as a parent class for dialog 
//  boxes, option lists, and menus. For each interactive window type, there can only
//  be one that is in focus since they all share the same navigational movement.
//
//  Requirements:
//    - Dimensions must be a multiple of 16 greater than 0
//
//  Specifications for window skin (see wskin_default.png):
//    - 128 x 128 png image
//    - 4 sections (total 64 frames):
//        - backdrop (4x4=16 frames)
//        - frame (4x4=16 frames)
//        - texture (4x4=16 frames)
//        - Cursor and color themes (4x4=16 frames)
//
//
//====================================================================================
#ifndef __PROLIX_INTERFACE_WINDOW_H__
#define __PROLIX_INTERFACE_WINDOW_H__

#include "../../engine/include/PrlxEngine.h"
#include "../../common/include/cResources.h"
#include "../../common/include/cFont.h"
#include "../../framework/include/cGame.h"
#include "../../common/include/cSprite.h"
#include "../../common/include/cAnimation.h"

//====================================================================================
//                     **** WINDOW CONSTANTS AND SETTINGS ****
//====================================================================================
// [DEFAULT WINDOW SKIN]
const std::string DEFAULT_WSKIN_ID    = "wskin_default.png";

//////////////////////////////////////////////////////////////////////////////////
// returns a vector of strings of Formatted lines to fit within a prescribed width.
// supported only for single paragraphs
std::vector<std::string> LineWrap
	(cFont font, std::string text, int width = 400);

//////////////////////////////////////////////////////////////////////////////////
// performs the above method but accepts multiple paragraphs each of have paragraph
// endings represented by '@'
std::vector<std::string> LineWrapParagraph 
	(cFont font, std::string paragraph, int width = 400);

//====================================================================================
//                                                                           cmpWindow
//====================================================================================
struct cmpWindow 
{
    ////////////////////////////// FRAME INDEX LEGEND ////////////////////////////////
	// B_ = backdrop      F_ = border/frame    T_ = texture        M_ = miscellaneous     
	// *H = horiz bar     *V = vertical bar    *L = level          *N = none
	//////////////////////////////////////////////////////////////////////////////////
	enum eFrameSlice 
    {
		B_TOPLEFT,  B_TOPH1, B_TOPH2, B_TOPRIGHT, F_TOPLEFT, F_TOPH1, F_TOPH2, F_TOPRIGHT,
		B_VLEFT1,   B_L1N1,  B_L1N2,  B_VRIGHT1,  F_VLEFT1,  F_L1N1,  F_L1N2,  F_VRIGHT1, 
		B_VLEFT2,   B_L2N1,  B_L2N2,  B_VRIGHT2,  F_VLEFT2,  F_L2N1,  F_L2N2,  F_VRIGHT2, 
		B_BOTLEFT,  B_BOTH1, B_BOTH2, B_BOTRIGHT, F_BOTLEFT, F_BOTH1, F_BOTH2, F_BOTRIGHT,
		T_TOPLEFT,  T_TOPH1, T_TOPH2, T_TOPRIGHT, M_TOPLEFT, M_TOPH1, M_TOPH2, M_TOPRIGHT,
		T_VLEFT1,   T_L1N1,  T_L1N2,  T_VRIGHT1,  M_VLEFT1,  M_L1N1,  M_L1N2,  M_VRIGHT1, 
		T_VLEFT2,   T_L2N1,  T_L2N2,  T_VRIGHT2,  M_VLEFT2,  M_L2N1,  M_L2N2,  M_VRIGHT2, 
		T_BOTLEFT,  T_BOTH1, T_BOTH2, T_BOTRIGHT, M_BOTLEFT, M_BOTH1, M_BOTH2, M_BOTRIGHT
	};

	bool alive;          // flag indicating the state of the window
	int id;              // window unique ID for Window Manager
    cTexture *skin;  // the window skin
	Dimensions dim;      // dimensions of the window
	Point pos;           // position of the window

	cSprite *frames;		 // frames of the window components

    // applies the window to the screen
	virtual void Draw();

	// Constructor
	//   Sets default position to Point(0,0)
	//   Sets default dimensions to Dimensions(128,128)
	//   Default skin is set to prescribed window skin theme
	cmpWindow(
        Point position = Point(0,0),
        Dimensions dimensions = Dimensions(128,128), 
		cTextureId skinId = DEFAULT_WSKIN_ID);
	
	// Destructor
	~cmpWindow();
};

#endif