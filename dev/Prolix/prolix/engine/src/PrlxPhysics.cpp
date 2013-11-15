//====================================================================================
// @Title:      PROLIX PHYSICS
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxPhysics.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <cmath>
#include "../include/PrlxPhysics.h"
#include "../include/PrlxEngine.h"
#include "../../common/include/xString.h"

//====================================================================================
//                                                                        PrlxPhysics
//====================================================================================
PrlxPhysics::PrlxPhysics()
{
    LogMgr->Write(INFO, "PrlxPhysics::PrlxPhysics >>>> PROLIX Physics Engine initalized");
}

PrlxPhysics::Motion::Motion(Position rPos, Velocity rVel, Acceleration rAcc):
    pos(rPos),
    vel(rVel),
    acc(rAcc)
{
}

PrlxPhysics::Motion::Position::Position(float rX, float rY) 
{
	x = rX;
	y = rY;
}

PrlxPhysics::Motion::Velocity::Velocity(float rX, float rY) 
{
	x = rX;
	y = rY;
}

PrlxPhysics::Motion::Acceleration::Acceleration(float rX, float rY) 
{
	x = rX;
	y = rY;
}

PrlxPhysics::Motion::Position::Position(PRLX_Point &point)
{
    x = (float)point.pos.x;
    y = (float)point.pos.y;
}

std::string PrlxPhysics::Motion::Position::Format() 
{
	return "pos(" + toString(x) + "," + toString(y) + ")";
}

void PrlxPhysics::Motion::Position::Center(Dimensions dim)
// UNSAFE TO USE DURING GAME
{
    x -= dim.w/2;
    y -= dim.h/2;
}

std::string PrlxPhysics::Motion::Velocity::Format() 
{
	return "vel(" + toString(x) + "," + toString(y) + ")";
}

std::string PrlxPhysics::Motion::Acceleration::Format()
{
	return "acc(" + toString(x) + "," + toString(y) + ")";
}

void PrlxPhysics::Motion::Stop()
{
    acc.x = 0;
    acc.y = 0;
    vel.x = 0;
    vel.y = 0;
}

void PrlxPhysics::Motion::Move() 
{
    // handle horizontal motion
	if (acc.x > 0) 
    {
		if (vel.x >= 0)
        {
			acc.x = vel.x = 0;
        }
	}
    else if (acc.x < 0)
    {
		if (vel.x <= 0)
        {
			acc.x = vel.x = 0;
        }
	}
    else
    {
	}

    // handle vertical motion (symmetrical to horizontal motion)
	if (acc.y > 0) 
    {
		if (vel.y >= 0) 
        {
			acc.y = vel.y = 0;
        }
	} 
    else if (acc.y < 0)
    {
		if (vel.y <= 0) 
        {
			acc.y = vel.y = 0;
        }
	}
    else
    {
	}

	pos.x += vel.x += acc.x;
	pos.y += vel.y += acc.y;
}

float PrlxPhysics::CalculateDistance(PRLX_Point A, PRLX_Point B)
{
    return (float)(sqrt(pow((double)(B.pos.x - A.pos.x), 2.0) + pow((double)(B.pos.y - A.pos.y), 2.0)));
}

float PrlxPhysics::CalculateDistance(PrlxPhysics::Motion::Position A, PrlxPhysics::Motion::Position B)
{
    return CalculateDistance
        (
            PRLX_Point(Point(A.x, A.y)),
            PRLX_Point(Point(B.x, B.y))
        );
}

bool PrlxPhysics::HitTest(PRLX_Rect A, PRLX_Rect B) 
{
	int leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	SetBoundary(A, leftA, rightA, topA, bottomA);
	SetBoundary(B, leftB, rightB, topB, bottomB);

	if (bottomA < topB) return false;
	if (topA > bottomB) return false;
	if (rightA < leftB) return false;
	if (leftA > rightB) return false;
	return true;
}

bool PrlxPhysics::HitTest(PRLX_Rect rect, PRLX_Point point)
{
    int left, right, top, bottom;
    SetBoundary(rect, left, right, top, bottom);
    
    return (point.pos.x >= left && point.pos.x <= right &&
            point.pos.y >= top && point.pos.y <= bottom);
}

bool PrlxPhysics::HitTest(PRLX_Point point, PRLX_Rect rect)
{
    return HitTest(rect, point);
}

bool PrlxPhysics::HitTest(PRLX_Circle A, PRLX_Circle B)
{
    return (CalculateDistance(Point(A.pos.x, A.pos.y), Point(B.pos.x, B.pos.y)) <= A.radius + B.radius);
}

bool PrlxPhysics::HitTest(PRLX_Circle circle, PRLX_Point point)
{
    return (CalculateDistance(Point(circle.pos.x, circle.pos.y), point) <= circle.radius);
}

bool PrlxPhysics::HitTest(PRLX_Point point, PRLX_Circle circle)
{
    return HitTest(circle, point);
}

void PrlxPhysics::SetBoundary(PRLX_Rect box, int &left, int &right, int &top, int &bottom)
{
	left = box.pos.x;
	right = box.pos.x + box.dim.w;
	top = box.pos.y;
	bottom = box.pos.y + box.dim.h;
}

PrlxPhysics::~PrlxPhysics()
{
    LogMgr->Write(INFO, "PrlxPhysics::~PrlxPhysics >>>> Cleaning up PROLIX Physics");
}