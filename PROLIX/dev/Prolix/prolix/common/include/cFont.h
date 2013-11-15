//====================================================================================
// @Title:      FONT
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cFont.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  An ADT for storing basic text writing properties.
//
//====================================================================================
#ifndef __PROLIX_COMMON_FONT_H__
#define __PROLIX_COMMON_FONT_H__

#include <SDL_opengl.h>
#include <string>
#include "../include/xDraw.h"
#include "../../engine/include/PrlxText.h"

//====================================================================================
//                                                                               cFont
//====================================================================================
class cFont
{
  public:
	std::string id;         // alias derived from fontpath
    int size;               // the size of the font
    cColor color;       // color of the text
    eFontQuality quality;   // render quality

    // Constructors
    cFont();

    cFont(std::string id, int size, cColor color = PRLX_Black,
        eFontQuality quality = DEFAULT_FONT_QUALITY);
};

static const cFont DEFAULT_FONT = cFont("droid.ttf", 20, PRLX_White);

#endif