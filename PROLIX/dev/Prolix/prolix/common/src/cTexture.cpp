//====================================================================================
// @Title:      TEXTURE
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cTexture.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../../engine/include/PrlxEngine.h"
#include "../include/cTexture.h"

//====================================================================================
//                                                                            cTexture
//====================================================================================
cTexture::cTexture(GLuint rImg, std::string rId, Dimensions rDim, cColor rColor) 
{
	img = mDefaultImg = rImg;
	id = rId;
	dim = mDefaultDim = rDim;
	color = mDefaultColor = rColor;
}

void cTexture::Reset() 
{
	img = mDefaultImg;
	id = mDefaultId;
	dim = mDefaultDim;
	color = mDefaultColor;
}

cTexture *cTexture::Clone()
{
	return NULL;
}

void cTexture::Draw(Point pos, PRLX_Rect *clip)
{
	Engine->Graphics->Draw(this, pos, clip);
}

void cTexture::Draw(cColor color, Point pos, PRLX_Rect *clip)
{
	Engine->Graphics->Draw(this, color, pos, clip);
}

void cTexture::Draw(float scaleX, float scaleY, Point pos, PRLX_Rect *clip)
{
	Engine->Graphics->Draw(this, scaleX, scaleY, pos, clip);
}

void cTexture::Draw(Dimensions dim, Point pos, PRLX_Rect *clip)
{
	Engine->Graphics->Draw(this, dim, pos, clip);
}

void cTexture::Draw(float rotation, Point pos, Dimensions bound_size)
{
	Engine->Graphics->Draw(this, rotation, pos, bound_size);
}

void cTexture::Draw(Quad quad)
{
	Engine->Graphics->Draw(this, quad);
}

void cTexture::DrawExt(Point pos, cColor color, float scaleX, float scaleY, float rotation, PRLX_Rect *clip)
{
	Engine->Graphics->DrawExt(this, pos, color, scaleX, scaleY, rotation, clip);
}