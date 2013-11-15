//====================================================================================
// @Title:      SPRITE
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cSprite.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Creates, Formats and displays sprites given a string mapped to a PNG file
//  Formatted surface/texture. Prepares spriteset and spritesheet for animation
//  if desired.
//
//====================================================================================
#ifndef __PROLIX_COMMON_SPRITE_H__
#define __PROLIX_COMMON_SPRITE_H__

#include <SDL.h>
#include <vector>
#include <string>
#include <map>
#include "../../common/include/cCartesian.h"
#include "../../common/include/xDraw.h"
#include "../../common/include/cTimer.h"
#include "../../common/include/cTexture.h"
#include "../../engine/include/PrlxPhysics.h"

// forward declarations
class cAnimation;

//====================================================================================
//                                                                             cSprite
//====================================================================================
class cSprite 
{
  public:
    // registered animations
	std::map<std::string, cAnimation *> Animation;

	Point position;	// current position of sprite
	int numX, numY;	// number of frames for each axis 
	Dimensions dim;	// spritesheet dimensions
    Dimensions frameDim;    // dimensions of an arbitrary frame
	
	cTexture *spritesheet;			// spritesheet with frames
	std::vector<PRLX_Rect> spriteset;	// parsed frames from spritesheet

	// returns true if specified animation is currently playing
	bool IsPlaying(std::string anim);

	// parse spritesheet
	void CreateAnimatedStrip();
	
	// add animation to animation map
	void CreateAnimation(std::string animId, std::vector<int> frameSet, int speed = 100);
	void CreateAnimation(std::string animId, std::vector<int> frameSet, int start, int end, int speed = 100);
	void CreateAnimation(std::string animId, int frameSet[], int numframes, int speed = 100);

	// draw specific frame from spriteset
	void DrawFrame(int frame);
	void DrawFrame(int frame, Point pos);

	// resize spritesheet and reclip PRLX_Rectangles
	void Resize(Dimensions dim);
	
	// Constructors
    cSprite(cTexture *texture, int numX = 1, int numY = 1);
	cSprite(cTextureId spritesheetId, int numX = 1, int numY = 1);
};

//====================================================================================
//                                                                        cSpriteGroup
//====================================================================================
class cSpriteGroup 
{
  public:
	std::map<std::string, cSprite *> SpriteGroup;

	cSprite *GetSprite(std::string spr_id);				// returns a sprite given a sprite identifier
	void AddSprite(std::string spr_id, cSprite *sprite);// adds a sprite to the sprite group
	bool ExistsSprite(std::string spr_id);				// checks if sprite exists in the group (by id)
	void RemoveSprite(std::string spr_id);				// removes a sprite from the sprite group

    // Constructors
	cSpriteGroup();
	cSpriteGroup(std::map<std::string, cSprite *> SpriteGroup);
};

#endif