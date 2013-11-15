//====================================================================================
// @Title:      PROLIX GRAPHICS
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxGraphics.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include "../include/PrlxGraphics.h"
#include "../include/PrlxEngine.h"
#include "../../common/include/cConstants.h"
#include "../../common/include/xDraw.h"
#include "../../framework/include/cAssetMgr.h"

//====================================================================================
//                                                                       PrlxGraphics
//====================================================================================
PrlxGraphics::PrlxGraphics() 
{
    LogMgr->Write(INFO, "PrlxGraphics::PrlxGraphics >>>> PROLIX Graphics Engine initialized");
}

void PrlxGraphics::Enable2D() 
{
    // configure drawing environment
	glClear(GL_COLOR_BUFFER_BIT);	// rendering to screen
	glPushMatrix();				    // Start rendering phase
	glEnable(GL_TEXTURE_2D);		// Enable textures when we are going to blend an texture
}

void PrlxGraphics::Disable2D() 
{
    // clean up drawing environment
	glDisable(GL_TEXTURE_2D);	// Disable textures when we are done using them
	glPopMatrix();				// End rendering phase		
	SDL_GL_SwapBuffers();		// Swap GL buffers when refreshing screen
}

cTexture *PrlxGraphics::Create(std::string url) 
{
	// load an image to encoded SDL Format
	SDL_Surface *image = IMG_Load(url.c_str());

	if (image == NULL) 
    {
		LogMgr->Write(FATAL, "PrlxGraphics::Create >>>> Could not find file " + url + ". Skipping");
		return NULL;
	}

	SDL_DisplayFormatAlpha(image);

    // configure SDL Format to OpenGL texture Format
	unsigned object(0);

	glGenTextures(1, &object);

	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    // Convert OpenGL texture Format to cTexture
	cTexture *texture = new cTexture(object, GetResourceName(url), Dimensions(image->w, image->h));

    if (!AssetMgr->Exists<Texture>(texture->id))
    {
        AssetMgr->AddUrl(url);
        AssetMgr->mTexture->add(cResource<cTexture *>(texture->id, texture));
    }
	else
    {
        LogMgr->Write(VERBOSE, "PrlxGraphics::Create >>>> Texture at " + url + " already exists");
    }
	
	SDL_FreeSurface (image);

	return texture;
}

cTexture *PrlxGraphics::Convert(SDL_Surface *srfc) 
{
	// convert SDL_Surface to cTexture
    SDL_DisplayFormatAlpha(srfc);

	unsigned object(0);

	glGenTextures(1, &object);

	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, srfc->w, srfc->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, srfc->pixels);

	cTexture *texture = new cTexture(object, "", Dimensions(srfc->w, srfc->h));

	SDL_FreeSurface(srfc);
	
	return texture;
}

cTexture *PrlxGraphics::Load(cTextureId ident) 
{
    // return the texture from texture stack if it has been created already
    if (AssetMgr->Exists<Texture>(ident))
    {
        return AssetMgr->Load<Texture>(ident);
    }

	LogMgr->Write(FATAL, "PrlxGraphics::Load >>>> Texture " + ident + " does not exist in Texture Stack");
	return NULL;
}

void PrlxGraphics::Free(cTextureId id) 
{
    // remove texture from stack
    AssetMgr->mTexture->remove(id);
}

void PrlxGraphics::Resize(cTexture *texture, Dimensions dim) 
{
    // destructively resize texture
	texture->dim.w = dim.w;
	texture->dim.h = dim.h;
}

bool PrlxGraphics::ValidTexture(cTexture *texture)
{
	// validate give texture
	if (texture == NULL) 
    {
		LogMgr->Write(FATAL, "PrlxGraphics::ValidTexture >>>> Received NULL texture. Skipping.");
        return false;
	}
	
    if (!AssetMgr->Exists<Texture>(texture->id)) 
    {
		LogMgr->Write(FATAL, "PrlxGraphics::ValidTexture >>>> " + texture->id + " does not exist in Texture Stack. Skipping.");
		return false;
	}

	return true;
}

void PrlxGraphics::Draw(cTexture *texture, Point pos, PRLX_Rect *clip) 
{
	if (!ValidTexture(texture)) return;
	
	// color and alpha level
	SetColor(texture->color);
	
	// configure texture for use
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	double divX = 1.0;	// limit width of clip
	double divY = 1.0;	// limit height of clip
	double parX = 0.0;	// initial x-position of clip
	double parY = 0.0;	// initial y-position of clip

	if (clip != NULL) 
    {
		parX = (double)clip->pos.x/(double)texture->dim.w * clip->nX;
		parY = (double)clip->pos.y/(double)texture->dim.h * clip->nY;
		divX = (double)clip->dim.w/(double)texture->dim.w;
		divY = (double)clip->dim.h/(double)texture->dim.h;
	}
	
	glBegin(GL_QUADS);
		// Top-Left corner
		glTexCoord2d(parX * divX, parY * divY);
		glVertex2d(pos.x, pos.y);
	
		// Top-Right corner
		glTexCoord2d(divX * (parX + 1), parY * divY);
		glVertex2d(texture->dim.w*divX + pos.x, pos.y);
	
		// Bottom-Right corner
		glTexCoord2d(divX * (parX + 1), divY * (parY + 1));	
		glVertex2d(texture->dim.w*divX + pos.x, texture->dim.h*divY + pos.y);

		// Bottom-Left corner 
		glTexCoord2d(parX * divX, divY * (parY + 1));
		glVertex2d(pos.x, texture->dim.h*divY + pos.y);
	glEnd();
}

void PrlxGraphics::Draw(cTexture *texture, cColor color, Point pos, PRLX_Rect *clip)
{
    if (!ValidTexture(texture)) return;
	
	// color and alpha level
	SetColor(color);
	
	// configure texture for use
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	double divX = 1.0;	// limit width of clip
	double divY = 1.0;	// limit height of clip
	double parX = 0.0;	// initial x-position of clip
	double parY = 0.0;	// initial y-position of clip

	if (clip != NULL) 
    {
		parX = (double)clip->pos.x/(double)texture->dim.w * clip->nX;
		parY = (double)clip->pos.y/(double)texture->dim.h * clip->nY;
		divX = (double)clip->dim.w/(double)texture->dim.w;
		divY = (double)clip->dim.h/(double)texture->dim.h;
	}
	
	glBegin(GL_QUADS);
		// Top-Left corner
		glTexCoord2d(parX * divX, parY * divY);
		glVertex2d(pos.x, pos.y);
	
		// Top-Right corner
		glTexCoord2d(divX * (parX + 1), parY * divY);
		glVertex2d(texture->dim.w*divX + pos.x, pos.y);
	
		// Bottom-Right corner
		glTexCoord2d(divX * (parX + 1), divY * (parY + 1));	
		glVertex2d(texture->dim.w*divX + pos.x, texture->dim.h*divY + pos.y);

		// Bottom-Left corner 
		glTexCoord2d(parX * divX, divY * (parY + 1));
		glVertex2d(pos.x, texture->dim.h*divY + pos.y);
	glEnd();
}

void PrlxGraphics::Draw(cTexture *texture, float scaleX, float scaleY, Point pos, PRLX_Rect *clip) 
{
	if (!ValidTexture(texture)) return;
	
	// color and alpha level
	SetColor(texture->color);
	
	// Bind the texture to which subsequent calls refer to
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	int w = (int)(texture->dim.w * scaleX);
	int h = (int)(texture->dim.h * scaleY);

	if (scaleX < 0) 
    {
		pos.x = pos.x - w;

		if (clip != NULL)
		{
			pos.x = pos.x - (clip->nX - 1) * texture->dim.w/clip->nX;
		}
	}
	if (scaleY < 0) 
    {
		pos.y = pos.y - h;

		if (clip != NULL)
		{
			pos.y = pos.y - (clip->nY - 1) * texture->dim.h/clip->nY;
		}
	}

	double divX = 1.0;	// limit width of clip
	double divY = 1.0;	// limit height of clip
	double parX = 0.0;	// initial x-position of clip
	double parY = 0.0;	// initial y-position of clip

	if (clip != NULL) 
    {
		(scaleX > 0)
            ? parX = (double)clip->pos.x/(double)w * clip->nX 
            : parX = (double)-clip->pos.x/(double)w * clip->nX;

		(scaleY > 0)
            ? parY = (double)clip->pos.y/(double)h * clip->nY 
            : parY = (double)-clip->pos.y/(double)h * clip->nY;
		
        divX = (double)(clip->dim.w * scaleX)/(double)w;
		divY = (double)(clip->dim.h * scaleY)/(double)h;
	}

	glBegin(GL_QUADS);
		// Top-Left corner
		glTexCoord2d(parX * divX, parY * divY);
		glVertex2d(pos.x, pos.y);
	
		// Top-Right corner
		glTexCoord2d(divX * (parX + 1), parY * divY);
		glVertex2d(w*divX + pos.x, pos.y);
	
		// Bottom-Right corner
		glTexCoord2d(divX * (parX + 1), divY * (parY + 1));	
		glVertex2d(w*divX + pos.x, h*divY + pos.y);

		// Bottom-Left corner 
		glTexCoord2d(parX * divX, divY * (parY + 1));
		glVertex2d(pos.x, h*divY + pos.y);
	glEnd();
}

void PrlxGraphics::Draw(cTexture *texture, Dimensions dim, Point pos, PRLX_Rect *clip) 
{
    if (!ValidTexture(texture)) return;
	
	if (!AssetMgr->Exists<Texture>(texture->id)) 
    {
		LogMgr->Write(FATAL, texture->id + " does not exist in Texture Stack. Skipping.");
		return;
	}
	
	// color and alpha level
	SetColor(texture->color);
	
	// configure texture for use
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	double divX = 1.0;	// limit width of clip
	double divY = 1.0;	// limit height of clip
	double parX = 0.0;	// initial x-position of clip
	double parY = 0.0;	// initial y-position of clip

	if (clip != NULL) 
    {
		parX = (double)clip->pos.x/(double)dim.w * clip->nX;
		parY = (double)clip->pos.y/(double)dim.h * clip->nY;
		divX = (double)clip->dim.w/(double)dim.w;
		divY = (double)clip->dim.h/(double)dim.h;
	}
	
	glBegin(GL_QUADS);
		// Top-Left corner
		glTexCoord2d(parX * divX, parY * divY);
		glVertex2d(pos.x, pos.y);
	
		// Top-Right corner
		glTexCoord2d(divX * (parX + 1), parY * divY);
		glVertex2d(dim.w*divX + pos.x, pos.y);
	
		// Bottom-Right corner
		glTexCoord2d(divX * (parX + 1), divY * (parY + 1));	
		glVertex2d(dim.w*divX + pos.x, dim.h*divY + pos.y);

		// Bottom-Left corner 
		glTexCoord2d(parX * divX, divY * (parY + 1));
		glVertex2d(pos.x, dim.h*divY + pos.y);
	glEnd();
}

void PrlxGraphics::Draw(cTexture *texture, float rotation, Point origin, Dimensions bound_size) 
{
    if (!ValidTexture(texture)) return;

	// reduce problem subset to [0,360] degrees
	rotation = (float)((int)rotation % 360);
	
	// color and alpha level
	SetColor(texture->color);
	
	// Bind the texture to which subsequent calls refer to
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	// create rotation
	glTranslatef (0.5, 0.5, 0);
	glRotatef (rotation, 0.0, 0.0, 0.5);

	// deviation parameters
	float w, h;
	int x, y;

	w = texture->dim.w - (texture->dim.w - texture->dim.h) * (float)std::sin (rotation * PI / 180);
	h = texture->dim.h + (texture->dim.w - texture->dim.h) * (float)std::sin (rotation * PI / 180);

	if (rotation == 270) 
    {
		w = (float)texture->dim.h;
		h = (float)texture->dim.w;
	}

	// calculate deviation from point of origin
	x = origin.x - (int)w/2;
	y = origin.y - (int)h/2;
	
    if (bound_size.w > 0) 
    {
        w = (float)bound_size.w;
    }
	if (bound_size.h > 0) 
    {
        h = (float)bound_size.h;
    }

	glBegin(GL_QUADS);
		// Top-Left corner
		glTexCoord2d(-0.5,-0.5); glVertex2d(x, y);
		// Top-Right corner
		glTexCoord2d(0.5,-0.5); glVertex2d(w + x, y);
		// Bottom-Right corner
		glTexCoord2d(0.5,0.5); glVertex2d(w + x, h + y);
		// Bottom-Left corner 
		glTexCoord2d(-0.5,0.5); glVertex2d(x, h + y);
	glEnd();

	glTranslatef(-0.5,-0.5,0);
}

void PrlxGraphics::Draw(PRLX_Shape *shape, float value, cColor color) 
{
    // draw PRLX_Shape to screen
	shape->Draw(value, color);
}

void PrlxGraphics::Draw(cTexture *texture, Quad quad) 
{
    if (!ValidTexture(texture)) return;
	
	// color and alpha level
	SetColor(texture->color);
	
	// configure texture for use
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	
	// draw quad
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex2d(quad.top_left.x, quad.top_left.y);          // Top-Left corner
		glTexCoord2d(1,0); glVertex2d(quad.top_right.x, quad.top_right.y);        // Top-Right corner
		glTexCoord2d(1,1);	glVertex2d(quad.bottom_right.x, quad.bottom_right.y);  // Bottom-Right corner
		glTexCoord2d(0,1); glVertex2d(quad.bottom_left.x, quad.bottom_left.y);    // Bottom-Left corner 
	glEnd();
}

void PrlxGraphics::DrawExt(cTexture *texture, Point pos, cColor color, float scaleX, float scaleY, float rotation, PRLX_Rect *clip)
{
    if (!ValidTexture(texture)) return;
	
	// reduce problem subset to [0,360] degrees
	rotation = (float)((int)rotation % 360);

    bool validRotate = (rotation != 0.0f);
	
    // color and alpha level
	SetColor(color);
	
	// Bind the texture to which subsequent calls refer to
	glBindTexture(GL_TEXTURE_2D, texture->img);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

    if (validRotate && (texture->dim.w == texture->dim.h))
    {
        scaleX *= 2.0f;
        scaleY *= 2.0f;
    }

	int w = (int)(texture->dim.w * scaleX);
	int h = (int)(texture->dim.h * scaleY);

	if (scaleX < 0) 
    {
		pos.x = pos.x - w;

		if (clip != NULL)
		{
			pos.x = pos.x - (clip->nX - 1) * texture->dim.w/clip->nX;
		}
	}
	if (scaleY < 0) 
    {
		pos.y = pos.y - h;
		
		if (clip != NULL)
		{
			pos.y = pos.y - (clip->nY - 1) * texture->dim.h/clip->nY;
		}
	}

    if (validRotate)
    {
        // create rotation
	    glTranslatef (0.5, 0.5, 0);
	    glRotatef (rotation, 0.0, 0.0, 0.5);
    }

	double divX = 1.0;	// limit width of clip
	double divY = 1.0;	// limit height of clip
	double parX = 0.0;	// initial x-position of clip
	double parY = 0.0;	// initial y-position of clip

	if (clip != NULL) 
    {
		(scaleX > 0)
            ? parX = (double)clip->pos.x/(double)w * clip->nX 
            : parX = (double)-clip->pos.x/(double)w * clip->nX;

		(scaleY > 0)
            ? parY = (double)clip->pos.y/(double)h * clip->nY 
            : parY = (double)-clip->pos.y/(double)h * clip->nY;
		
        divX = (double)(clip->dim.w * scaleX)/(double)w;
		divY = (double)(clip->dim.h * scaleY)/(double)h;
	}

	glBegin(GL_QUADS);
	// Top-Left corner
        glTexCoord2d(parX * divX - ((validRotate)? 0.5 : 0.0), parY * divY - ((validRotate)? 0.5 : 0.0));
		glVertex2d(pos.x, pos.y);
	
		// Top-Right corner
		glTexCoord2d(divX * (parX + 1) + ((validRotate)? 0.5 : 0.0), parY * divY - ((validRotate)? 0.5 : 0.0));
		glVertex2d(w*divX + pos.x, pos.y);
	
		// Bottom-Right corner
		glTexCoord2d(divX * (parX + 1) + ((validRotate)? 0.5 : 0.0), divY * (parY + 1) + ((validRotate)? 0.5 : 0.0));	
		glVertex2d(w*divX + pos.x, h*divY + pos.y);

		// Bottom-Left corner 
		glTexCoord2d(parX * divX - ((validRotate)? 0.5 : 0.0), divY * (parY + 1) + ((validRotate)? 0.5 : 0.0));
		glVertex2d(pos.x, h*divY + pos.y);
	glEnd();

    if (validRotate)
    {
        glTranslatef(-0.5,-0.5,0);
    }
}

PrlxGraphics::~PrlxGraphics() 
{
    LogMgr->Write(INFO, "PrlxGraphics::~PrlxGraphics >>>> Cleaning up PROLIX Graphics");
}