//====================================================================================
// @Title:      ENTITY
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cEntity.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cEntity.h"

//====================================================================================
//                                                                             cEntity
//====================================================================================
cEntity::cEntity()
{
    SpriteGroup = new cSpriteGroup;
    AnimationGroup = new cAnimationGroup;
    texture = NULL;
}

void cEntity::Move()
{
    motion.Move();
}

void cEntity::Draw()
{
}

void cEntity::Update()
{
    Move();
    Draw();
}

cEntity::~cEntity() 
{
}