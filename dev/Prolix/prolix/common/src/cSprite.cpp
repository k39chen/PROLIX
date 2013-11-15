//====================================================================================
// @Title:      SPRITE
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cSprite.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cSprite.h"
#include "../../common/include/cAnimation.h"
#include "../../engine/include/PrlxEngine.h"
#include "../../common/include/xVector.h"
#include "../../framework/include/cAssetMgr.h"

//====================================================================================
//                                                                             cSprite
//====================================================================================
cSprite::cSprite(cTexture *rTexture, int rNumX, int rNumY)
{
	spritesheet = rTexture;

	numX = rNumX;
	numY = rNumY;
	
    if (spritesheet == NULL) 
    {
		LogMgr->Write(FATAL, "cSprite::cSprite >>>> Received NULL texture of Texture ID '" + rTexture->id + "'");
	}
	
    dim = Dimensions(spritesheet->dim.w, spritesheet->dim.h);
    frameDim = Dimensions(dim.w/numX, dim.h/numY);
	position = Point(0,0);
	spriteset.resize(numX * numY);
	CreateAnimatedStrip();
}

cSprite::cSprite(cTextureId rSpritesheetId, int rNumX, int rNumY) 
{
	spritesheet = AssetMgr->Load<Texture>(rSpritesheetId);

	numX = rNumX;
	numY = rNumY;
	
    if (spritesheet == NULL) 
    {
		LogMgr->Write(FATAL, "cSprite::cSprite >>>> Received NULL texture of Texture ID '" + rSpritesheetId + "'");
	}
	
    dim = Dimensions(spritesheet->dim.w, spritesheet->dim.h);
    frameDim = Dimensions(dim.w/numX, dim.h/numY);
	position = Point(0,0);
	spriteset.resize(numX * numY);
	CreateAnimatedStrip();
}

bool cSprite::IsPlaying(std::string anim) 
{
	return Animation[anim]->Timer.started;
}

void cSprite::CreateAnimatedStrip() 
{
	int curr;
	for (int row=0; row<numY; row++) 
    {
		for (int col=0; col<numX; col++) 
        {
			curr = row*numX + col;
			spriteset[curr].dim.w = dim.w/numX;
			spriteset[curr].dim.h = dim.h/numY;
			spriteset[curr].pos.x = col * spriteset[curr].dim.w;
			spriteset[curr].pos.y = row * spriteset[curr].dim.h;
			spriteset[curr].nX = numX;
			spriteset[curr].nY = numY;
		}
	}		
}

void cSprite::CreateAnimation(std::string animId, std::vector<int> frameset, int speed) 
{
	Animation[animId] = new cAnimation(this, frameset);
}

void cSprite::CreateAnimation(std::string animId, std::vector<int> frameset, int start, int end, int speed) 
{
	std::vector<int> t(0);
	t.insert(t.begin(), frameset.begin() + start, frameset.begin() + end);
	CreateAnimation(animId, t, speed);
}

void cSprite::CreateAnimation(std::string animId, int frameset[], int numframes, int speed) 
{
	CreateAnimation(animId, arrayToVector(frameset,numframes), speed);
}

void cSprite::DrawFrame(int frame) 
{
	DrawFrame(frame, Point(position.x, position.y));
}

void cSprite::DrawFrame(int frame, Point pos) 
{
	spritesheet->Draw(pos, &spriteset[frame]);
}

void cSprite::Resize(Dimensions dim) 
{
	Engine->Graphics->Resize(spritesheet, dim);
	int curr;
	for (int row=0; row<numY; row++) 
    {
		for (int col=0; col<numX; col++) 
        {
			curr = row*numX + col;
			spriteset[curr].dim.w = dim.w/numX;
			spriteset[curr].dim.h = dim.h/numY;
			spriteset[curr].pos.x = col * spriteset[curr].dim.w;
			spriteset[curr].pos.y = row * spriteset[curr].dim.h;
			spriteset[curr].nX = numX;
			spriteset[curr].nY = numY;
		}
	}
}

//====================================================================================
//                                                                        cSpriteGroup
//====================================================================================
cSpriteGroup::cSpriteGroup() 
{
	SpriteGroup.clear();
}

cSpriteGroup::cSpriteGroup(std::map<std::string, cSprite*> spr_group) 
{
	SpriteGroup = spr_group;
}

cSprite *cSpriteGroup::GetSprite(std::string spr_id) 
{
    if (!SpriteGroup.count(spr_id))
    {
        LogMgr->Write(FATAL, "cSpriteGroup::GetSprite >>>> Sprite group given invalid sprite id: '" + spr_id + "'");
        return NULL;
    }
	return SpriteGroup[spr_id];
}

void cSpriteGroup::AddSprite(std::string spr_id, cSprite *sprite) 
{
	SpriteGroup[spr_id] = sprite;
}

bool cSpriteGroup::ExistsSprite(std::string spr_id) 
{
	return (SpriteGroup.count(spr_id) > 0);
}

void cSpriteGroup::RemoveSprite(std::string spr_id) 
{
	std::map<std::string, cSprite *>::iterator loc;
	loc = SpriteGroup.find(spr_id);
	SpriteGroup.erase(loc);
}