//====================================================================================
// @Title:      ENTITY
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cEntity.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  An entity is an active object the screen that has interactive properties and/or
//  relationships with other possible entities or objects within the running
//  application.
//
//====================================================================================
#ifndef __PROLIX_COMMON_ENTITY_H__
#define __PROLIX_COMMON_ENTITY_H__ 

#include "../include/xDraw.h"
#include "../../engine/include/PrlxPhysics.h"
#include "../../common/include/cAnimation.h"
#include "../../common/include/cConstants.h"
#include "../../common/include/cSprite.h"
#include "../include/cTexture.h"

//====================================================================================
//                                                                             cEntity
//====================================================================================
class cEntity
{
     // provide aliasing of physics
    typedef PrlxPhysics::Motion::Position Position;
    typedef PrlxPhysics::Motion::Velocity Velocity;
    typedef PrlxPhysics::Motion::Acceleration Acceleration;

  public:
    // motion
    PrlxPhysics::Motion motion;

	eDirection direction;
    Dimensions dim;

    // texture, sprite and animation
    cTexture *texture;              // static image display (optional)
    cSpriteGroup *SpriteGroup;
    cAnimationGroup *AnimationGroup;

    // Collision detection shapes/boundaries
    PRLX_Circle coll_circle;    // collision circle
    PRLX_Rect coll_rect;        // collision rectangle
    PRLX_Point coll_point;      // collision point

    virtual void Move();    // maintain entity's movement
    virtual void Draw();    // draw entity at position
    virtual void Update();  // update movement and drawing

    // Constructor
    cEntity();

    // Destructor
    virtual ~cEntity();
};

#endif