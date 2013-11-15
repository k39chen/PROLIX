//====================================================================================
// @Title:      PROLIX TEXT
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxText.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Processes *.ttf files to write rendered messages on to the application screen
//  post-conversions from native SDL rendered font surfaces to cTextures. Intuitive
//  API and robust text registering methodology results in optimal text-writing
//  efficiency.
//
//====================================================================================
#ifndef __PROLIX_ENGINE_TEXT_H__
#define __PROLIX_ENGINE_TEXT_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include "../../common/include/cResources.h"
#include "../../common/include/cCartesian.h"
#include "../../common/include/xDraw.h"
#include "../../common/include/cTexture.h"
#include "../../common/include/cUrl.h"

class cFont;

//====================================================================================
//                  **** TEXT RENDERING CONSTANTS AND SETTINGS ****
//====================================================================================
// [FONT QUALITY LEVELS]
enum eFontQuality
{
    HIGH,           // High:    Smoothest rendering setting for fonts
    AVERAGE,        // Average: Rendered font is smooth but is overlayed onto a coloured rectangle
    LOW             // Low:     Lowest setting for rendering
};

// [FONT QUALITY SETTINGS]
static eFontQuality DEFAULT_FONT_QUALITY = HIGH;

//====================================================================================
//                                                                            PrlxText
//====================================================================================
class PrlxText 
{
    friend class cAssetMgr;
    friend class PrlxGraphics;

    // add font to Font Stack
	void AddFont(std::string url, int size = 15);
    void AddFont(cFont font);

  public:
    // return a rendered text and add to Text Stack
	cTexture *Prerender(cFont font, std::string message);

	// render a message and write to screen
	void Write(cFont font, std::string message, Point point = Point(0,0), bool deleteAfterRender = false);

    // return a text asset key
    std::string GetAssetKey(cFont font, std::string message);

    // Constructor
	PrlxText();

	// Destructor
	~PrlxText();
};

#endif