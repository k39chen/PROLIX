//====================================================================================
// @Title:      ANIMATION
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cAnimation.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Handles animation controls. Requires Sprite data type in order to manipulate
//  Formatted spritesheets and respective rectangle clippings.
//
//====================================================================================
#ifndef __PROLIX_COMMON_ANIMATION_H__
#define __PROLIX_COMMON_ANIMATION_H__

#include "../include/cSprite.h"

//====================================================================================
//                                                                          cAnimation
//====================================================================================
class cAnimation 
{
	void (*FinishedAnimation)();
  public:
	cTimer Timer;	// delay until next frame
	int index;		// index of current frame in frameset
	int frame;		// current frame
	int speed;		// animation speed
	bool playing;	// state of animation
	
	// animation properties
	std::vector<int> frameset;	// set of frames in animation
	cSprite *Sprite;			// parent sprite
	
	// animation controls
	void Play(Point pos = Point(0,0), int spd = 100);            // play and draw animation at specified speed and position
	void PlayOnce(Point pos = Point(0,0), int spd = 100);        // play and draw animation once
	void Stop();                                                 // stop animation and draw at specified position
	void Draw(Point pos = Point(0,0));                           // draw animation
	bool IsPlaying();                                            // returns state of animation

	// constructor
	cAnimation(cSprite *sprite, std::vector<int> frameset);
};

//====================================================================================
//                                                                     cAnimationGroup
//====================================================================================
class cAnimationGroup 
{
  public:
	std::map<std::string, cAnimation *> AnimationGroup;

	cAnimation *GetAnimation(std::string anim_id);				// returns an animation given an animation identifier
	void AddAnimation(std::string anim_id, cAnimation *anim);	// adds an animation to the animation group
	bool ExistsAnimation(std::string anim_id);				    // checks if animation exists in the group (by id)
	void RemoveAnimation(std::string anim_id);				    // removes an animation from the animation group

    // Constructors
	cAnimationGroup();
	cAnimationGroup(std::map<std::string, cAnimation *> AnimationGroup);
};


#endif