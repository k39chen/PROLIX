//====================================================================================
// @Title:      ANIMATION
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cAnimation.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cAnimation.h"
#include "../../engine/include/PrlxEngine.h"

//====================================================================================
//                                                                          cAnimation
//====================================================================================
cAnimation::cAnimation(cSprite *rSprite, std::vector<int> rframeset) 
{
	frameset = rframeset;
	frameset.resize(rframeset.size());
	index = 0;
    frame = frameset[index];
	Sprite = rSprite;
	playing = false;
}

void cAnimation::Play(Point pos, int spd) 
{
	if (!Timer.started) 
    {
		Timer.Start();
		playing = true;
	}
	if (spd - Timer.GetTicks() < 0) 
    {
		index = (index+1)%frameset.size();
		frame = frameset[index];
		Timer.Start();
	}

    Draw(pos);
}

void cAnimation::PlayOnce(Point pos, int spd) 
{
	if (!Timer.started) 
    {
		playing = true;
		Timer.Start();
	}
	if (index == frameset.size() - 1) 
    {
		playing = false;
		return;
	}
    if (spd - Timer.GetTicks() < 0) 
    {
		index = index + 1;
		frame = frameset[index];
		Timer.Start();
	}

    if (playing)
    {
        Draw(pos);
    }
}

void cAnimation::Stop() 
{
	index = 0;
	frame = frameset[index];
	Timer.Stop();
	playing = false;
}

bool cAnimation::IsPlaying() 
{
	return playing;
}

void cAnimation::Draw(Point pos) 
{
	Sprite->position = pos;
	Sprite->spritesheet->Draw(Sprite->position, &Sprite->spriteset[frame]);
}

//====================================================================================
//                                                                     cAnimationGroup
//====================================================================================
cAnimationGroup::cAnimationGroup() 
{
	AnimationGroup.clear();
}

cAnimationGroup::cAnimationGroup(std::map<std::string, cAnimation *> anim_group) 
{
	AnimationGroup = anim_group;
}

cAnimation *cAnimationGroup::GetAnimation(std::string anim_id) 
{
    if (!AnimationGroup.count(anim_id))
    {
        LogMgr->Write(FATAL, "cAnimationGroup::GetAnimation >>>> Animation group given invalid animation id: '" + anim_id + "'");
        return NULL;
    }
	return AnimationGroup[anim_id];
}

void cAnimationGroup::AddAnimation(std::string anim_id, cAnimation *animation) 
{
	AnimationGroup[anim_id] = animation;
}

bool cAnimationGroup::ExistsAnimation(std::string anim_id) 
{
	return (AnimationGroup.count(anim_id) > 0);
}

void cAnimationGroup::RemoveAnimation(std::string anim_id) 
{
	std::map<std::string, cAnimation *>::iterator loc;
	loc = AnimationGroup.find (anim_id);
	AnimationGroup.erase(loc);
}