//====================================================================================
// @Title:      PROLIX PHYSICS
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxPhysics.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Backbone for realistic movements and collision detection. In particular, required
//  collision detection features include rectangle collisions, circular collisions,
//  and per-pixel collisions.
//
//====================================================================================
#ifndef __PROLIX_ENGINE_PHYSICS_H__
#define __PROLIX_ENGINE_PHYSICS_H__

#include <SDL.h>
#include <string>
#include "../../common/include/xDraw.h"

// forward declarations
struct Object;
struct PRLX_Point;

//====================================================================================
//                                                                        PrlxPhysics
//====================================================================================
class PrlxPhysics 
{
  public:

	// Motion
	struct Motion 
    {
		// Position
		struct Position	
        {
			float x, y;				// x,y-coord representing position
			std::string Format();	// returns string of Formatted x,y-coord

            void Center(Dimensions dim);    // centers based on dimensions

			// constructor
            Position(PRLX_Point &point);
            Position(float xpos = 0.0f, float ypos = 0.0f);
		}
        pos;
		
        // Velocity
		struct Velocity	
        {
			float x, y;				// x,y-coord representing velocity vector
			std::string Format();	// returns string of Formatted x,y-coord

			// constructor
			Velocity(float xvel = 0.0f, float yvel = 0.0f);
		}
        vel;
		
		struct Acceleration 
        {
			float x, y;				// x,y-coord representing acceleration vector
			std::string Format();	// returns string of Formatted x,y-coord

			// constructor
			Acceleration(float xacc = 0.0f, float yacc = 0.0f);
		}
        acc;

        // update position taking into account velocity and acceleration
		void Move();

        // complete stop movement
        void Stop();
		
		// constructor
		Motion (Position pos = Position(0.0f,0.0f), 
				Velocity vel = Velocity(0.0f,0.0f), 
				Acceleration acc = Acceleration(0.0f,0.0f));
	};

    // distance between two points
    float CalculateDistance(PRLX_Point A, PRLX_Point B);
    float CalculateDistance(Motion::Position A, Motion::Position B);
	
	// returns true if collision is detected
	bool HitTest(PRLX_Rect A, PRLX_Rect B);
    bool HitTest(PRLX_Rect rect, PRLX_Point point);
    bool HitTest(PRLX_Point point, PRLX_Rect rect);
    bool HitTest(PRLX_Circle A, PRLX_Circle B);
    bool HitTest(PRLX_Circle circle, PRLX_Point point);
    bool HitTest(PRLX_Point point, PRLX_Circle circle);

	// set rectangle parameters
	void SetBoundary(PRLX_Rect box, int &left, int &right, int &top, int &bottom);

	// Constructor
	PrlxPhysics();

    // Destructor
    ~PrlxPhysics();
};

#endif