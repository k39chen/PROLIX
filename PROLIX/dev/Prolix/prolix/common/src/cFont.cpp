//====================================================================================
// @Title:      FONT
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cFont.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cFont.h"

//====================================================================================
//                                                                               cFont
//====================================================================================
cFont::cFont()
{
}

cFont::cFont(std::string rId, int rSize, cColor rColor, eFontQuality rQuality)
{
    id = rId;
    size = rSize;
    color = rColor;
    quality = rQuality;
}