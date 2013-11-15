//====================================================================================
// @Title:      PROLIX GRAPHICS
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxGraphics.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Will handle loading, blitting/rendering, and display of images and textures. 
//  Will only accept 32 bit-depth PNG file Formats, otherwise improper pixel processing
//  will occur and will yield unexpected results.
//
//====================================================================================
#ifndef __PROLIX_ENGINE_GRAPHICS_H__
#define __PROLIX_ENGINE_GRAPHICS_H__

#include <SDL.h>
#include <vector>
#include <string>
#include "../../common/include/cCartesian.h"
#include "../../common/include/cResources.h"
#include "../../common/include/cTexture.h"
#include "../include/PrlxPhysics.h"
#include <SDL_opengl.h>

//====================================================================================
//                                                                       PrlxGraphics
//====================================================================================
class PrlxGraphics 
{
    friend class cGame;
    friend class cAssetMgr;
    friend class PrlxText;

	cTexture *Create(std::string url);	    // creates a texture and add to Texture Stack
	cTexture *Load(cTextureId ident);	// loads a pre-existing texture from stack
	cTexture *Convert(SDL_Surface *srfc);	// returns a cTexture converted from a SDL_Surface
	void Free(cTextureId id);               // remove a texture from Texture Stack
    void Enable2D();                            // initialize rendering phase
	void Disable2D();                           // terminate rendering phase

  public:
    // destructively resize texture
	void Resize(cTexture *texture, Dimensions dim);

	bool ValidTexture(cTexture *texture);
	void Draw(cTexture *texture, Point pos = Point(0,0), PRLX_Rect *clip = NULL);                               // draw texture to application screen
    void Draw(cTexture *texture, cColor color, Point pos = Point(0,0), PRLX_Rect *clip = NULL);					// draw tinted texture to application screen
	void Draw(cTexture *texture, float scaleX, float scaleY, Point pos = Point(0,0), PRLX_Rect *clip = NULL);   // draw a scaled equivalent of a texture
	void Draw(cTexture *texture, Dimensions dim, Point pos = Point(0,0), PRLX_Rect *clip = NULL);               // draw an explicitly scaled equivalent of a texture
	void Draw(cTexture *texture, float rotation, Point pos, Dimensions bound_size = Dimensions(-1,-1));         // draw a rotation of the texture
	void Draw(cTexture *texture, Quad quad);                                                                    // draw dimensionalized texture to application screen
	void Draw(PRLX_Shape *shape, float value = 0.0f, cColor color = PRLX_White);                                // draw primitive shapes to application screen

    // extended draw function
    void DrawExt(cTexture *texture, Point pos = Point(0,0), 
        cColor color = PRLX_White, float scaleX = 1.0f, float scaleY = 1.0f,
        float rotation = 0.0f, PRLX_Rect *clip = NULL);

	// Constructor
	PrlxGraphics();

	// Destructor
	~PrlxGraphics();
};

#endif