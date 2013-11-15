//====================================================================================
// @Title:      PROLIX TEXT
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxText.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <SDL.h>
#include "../include/PrlxEngine.h"
#include "../include/PrlxText.h"
#include "../../common/include/cFont.h"
#include "../../common/include/xString.h"
#include "../../framework/include/cAssetMgr.h"

//====================================================================================
//                                                                            PrlxText
//====================================================================================
PrlxText::PrlxText()
{
	LogMgr->Write(INFO, "PrlxText::PrlxText >>>> PROLIX Text Engine initalized");

    // initialize SDL Font processor
	if (TTF_Init() == -1) 
    {
		LogMgr->Write(INFO, "PrlxText::PrlxText >>>> PROLIX Text Engine could not be initalized");
	}
}

void PrlxText::AddFont(std::string url, int size) 
{
    // load font
	TTF_Font *font = NULL;
	font = TTF_OpenFont(url.c_str(), size);
	
    // validate font processing
    if (font == NULL) 
    {
		LogMgr->Write(FATAL, "PrlxText::AddFont >>>> Could not find '" + url + "'");
		return;
	}
	
    // commit to resource stacks
    bool duplicate = false;
    for (unsigned int i=0;i<1000;i++)
    {
        if (AssetMgr->Exists<Font>(GetResourceName(url) + toString(i)))
        {
            duplicate = true;
            break;
        }
    }

    if (!duplicate)
    {
        AssetMgr->AddUrl(url);
    }
	AssetMgr->mFont->add(cResource<TTF_Font *>(GetResourceName(url) + toString(size), font));
}

void PrlxText::AddFont(cFont font)
{
    AddFont(AssetMgr->GetUrl(font.id), font.size);
}

cTexture *PrlxText::Prerender(cFont font, std::string message) 
{
	// formulate resource stack search key
    std::string id = GetAssetKey(font, message);
	
    // add font to font stack if it doesn't already exist
    if (!AssetMgr->Exists<Font>(font.id + toString(font.size)))
    {
        AddFont(font);
    }
    
    // simply return the text from the text stack if pre-rendered
    if (AssetMgr->Exists<Texture>(id)) 
    {
        return AssetMgr->Load<Texture>(id);
	}
	
    // render a new text
    cTexture *texture = NULL;
	
    // render specified quality for font
	if (font.quality == ::HIGH)
    {
		texture = Engine->Graphics->Convert 
            (TTF_RenderText_Blended (AssetMgr->Load<Font>(font.id + toString(font.size)), message.c_str(), PRLX_White.toSDL()));
    }
	if (font.quality == ::AVERAGE)
    {
        texture = Engine->Graphics->Convert 
			(TTF_RenderText_Shaded (AssetMgr->Load<Font>(font.id + toString(font.size)), message.c_str(), PRLX_White.toSDL(), PRLX_Black.toSDL()));
    }
	if (font.quality == ::LOW)
    {
        texture = Engine->Graphics->Convert 
			(TTF_RenderText_Solid (AssetMgr->Load<Font>(font.id + toString(font.size)), message.c_str(), PRLX_White.toSDL()));
    }

    // add text to stack
	texture->id = id;
	texture->color = font.color;

    AssetMgr->mTexture->add(cResource<cTexture *>(texture->id, texture));
	return texture;
}

void PrlxText::Write(cFont font, std::string message, Point point, bool deleteAfterRender) 
{
    // render and draw the text to screen
	cTexture *srfc = Prerender(font, message);
	srfc->Draw(point);

    if (deleteAfterRender)
    {
        AssetMgr->Remove<Texture>(GetAssetKey(font, message));
    }
}

std::string PrlxText::GetAssetKey(cFont font, std::string message)
{
    return font.id + font.color.Format() + message;
}

PrlxText::~PrlxText() 
{
    TTF_Quit();

    LogMgr->Write(INFO, "PrlxText::~PrlxText >>>> Cleaning up PROLIX Text");
}