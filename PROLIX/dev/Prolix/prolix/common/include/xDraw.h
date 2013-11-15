//====================================================================================
// @Title:      DRAWING
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xDraw.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Coloring and primitive shapes defined for text, textures, and physics bounding
//  regions. Provides OpenGL drawing in addition to providing backwards compatibility
//  for native SDL imaging libraries.
//
//====================================================================================
#ifndef __PROLIX_COMMON_DRAWING_H__
#define __PROLIX_COMMON_DRAWING_H__

#include <SDL.h>
#include "../include/cCartesian.h"

// defined colors
#define PRLX_Black			cColor(0,0,0)
#define PRLX_Gray			cColor(150,150,150)
#define PRLX_White			cColor(255,255,255)
#define PRLX_Red			cColor(255,0,0)
#define PRLX_Blue			cColor(0,0,255)
#define PRLX_Green			cColor(0,255,0)
#define PRLX_Transparent	cColor(0,0,0,0);

//====================================================================================
//                                                                              cColor
//====================================================================================
struct cColor 
{
	// Hues and alpha level
	int r, g, b, a;

	// converts cColor to SDL_Color
	SDL_Color toSDL();

	// returns a 4-tuple representing the color, ie. (r,g,b,a)
	std::string Format();

	// Constructor
	cColor(int r = 255, int g = 255, int b = 255, int a = 255);
};

cColor operator+(cColor color1, cColor color2);
cColor operator-(cColor color1, cColor color2);

// sets a cColor to a glColor4ub
void SetColor(cColor color);

//====================================================================================
//                                                                          Dimensions
//====================================================================================
struct Dimensions 
{
    // width and height of the shape
	int w;
    int h;
	
	// Constructor
	Dimensions(int w = 0, int h = 0);
}; 

Dimensions operator +(Dimensions dim1, Dimensions dim2);
Dimensions operator -(Dimensions dim1, Dimensions dim2);

//====================================================================================
//                                                                          PRLX_Shape
//====================================================================================
struct PRLX_Shape 
{
    // origin of the shape
	Point pos;

	// draw the primitive shape
	// Note: drawing of primitive shapes must always occur after every
	// instance of game application elements otherwise GL_TEXTURE_2D will be
	// enabled which will result in undesired results.
	virtual void Draw(float value, cColor);

	// Constructor
	PRLX_Shape(Point pos = Point(0,0));
};

//====================================================================================
//                                                             PRLX_Point : PRLX_Shape
//====================================================================================
struct PRLX_Point : public PRLX_Shape 
{
	// draw the point
	void Draw(float pointSize = 1, cColor color = cColor(255,255,255,255));

	// constructor
	PRLX_Point(Point pos = Point(0,0));
};

//====================================================================================
//                                                              PRLX_Line : PRLX_Shape
//====================================================================================
struct PRLX_Line : public PRLX_Shape 
{
    // destination position of the line
	Point pos2;
	
	// draw the line
	void Draw(float lineWidth = 1, cColor color = cColor(255,255,255,255));

	// Constructor
	PRLX_Line(Point pos1 = Point(0,0), Point pos2 = Point(0,0));
};

//====================================================================================
//                                                              PRLX_Rect : PRLX_Shape
//====================================================================================
struct PRLX_Rect : public PRLX_Shape 
{
	int nX, nY;		// special variables tracking number of partitions in shape
					// used primarily for parsing spritesheets (defaults to 1)
	Dimensions dim;	// dimensions of the rectangle

	// draw the rectangle
	void Draw(float fill = 1.0f, cColor color = cColor(255,255,255,255));

	// constructor
	PRLX_Rect(Point pos = Point(0,0), Dimensions dim = Dimensions(0,0), int nX = 1, int nY = 1);
};

//====================================================================================
//                                                          PRLX_Triangle : PRLX_Shape
//====================================================================================
struct PRLX_Triangle : public PRLX_Shape 
{
	Point pos2;	// location of second vertex
	Point pos3;	// location of third vertex

	// draw the triangle
	void Draw(bool fill = true, cColor color = cColor(255,255,255,255));

	// constructor
	PRLX_Triangle(Point pos1 = Point(0,0), Point pos2 = Point(0,0), Point pos3 = Point(0,0));
};

//====================================================================================
//                                                            PRLX_Circle : PRLX_Shape
//====================================================================================
struct PRLX_Circle : public PRLX_Shape 
{
    // radius of the circle
	int radius;	

	// draw the circle
	void Draw(int smoothness = 5, cColor color = cColor(255,255,255,255));

	// constructor)
	PRLX_Circle(Point pos = Point(0,0), int radius = 0);
};

#endif