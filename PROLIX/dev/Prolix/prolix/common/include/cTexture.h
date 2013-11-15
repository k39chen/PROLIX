//====================================================================================
// @Title:      TEXTURE
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cTexture.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Encapsulating ADT for a primitive OpenGL texture with additional SDL properties. 
//  To be used when loading an image and rendering TTF fonts. Replaces the SDL_Surface 
//  feature from the SDL libraries.
//
//====================================================================================
#ifndef __PROLIX_COMMON_TEXTURE_H__
#define __PROLIX_COMMON_TEXTURE_H__

#include <SDL_opengl.h>
#include <string>
#include "../include/xDraw.h"

// alias cTextureId type
typedef std::string cTextureId;

//====================================================================================
//                                                                            cTexture
//====================================================================================
class cTexture 
{
	// default settings
	GLuint mDefaultImg;
	std::string mDefaultId;
	Dimensions mDefaultDim;
	cColor mDefaultColor;

  public:
	GLuint img;			// native OpenGL texture type
	std::string id;		// associated texture string identifier
	Dimensions dim;		// dimensions of the texture
	cColor color;	// brightness/hue/transparency of the texture

	void Reset();		// resets texture to intial properties
	cTexture *Clone();	// creates new texture on AssetMgr and returns instance of it here

	void Draw(Point pos = Point(0,0), PRLX_Rect *clip = NULL);                               // draw texture to application screen
    void Draw(cColor color, Point pos = Point(0,0), PRLX_Rect *clip = NULL);				 // draw tinted texture to application screen
	void Draw(float scaleX, float scaleY, Point pos = Point(0,0), PRLX_Rect *clip = NULL);   // draw a scaled equivalent of a texture
	void Draw(Dimensions dim, Point pos = Point(0,0), PRLX_Rect *clip = NULL);               // draw an explicitly scaled equivalent of a texture
	void Draw(float rotation, Point pos, Dimensions bound_size = Dimensions(-1,-1));         // draw a rotation of the texture
	void Draw(Quad quad);                                                                    // draw dimensionalized texture to application screen
	
	// extended draw function
	void DrawExt(Point pos, cColor color = PRLX_White, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f, PRLX_Rect *clip = NULL);

	// Constructor
	cTexture(GLuint img, std::string id, Dimensions dim, cColor color = PRLX_White);
};

#endif