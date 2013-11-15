//====================================================================================
// @Title:      DRAWING
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xDraw.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <iostream>
#include <cmath>
#include "../include/xDraw.h"
#include "../../engine/include/PrlxGraphics.h"
#include <SDL_opengl.h>

#define PI 3.1415926535897932384626433832795

//====================================================================================
//                                                                              cColor
//====================================================================================
cColor::cColor(int red, int green, int blue, int alpha) 
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

SDL_Color cColor::toSDL() 
{
	SDL_Color color = {r, g, b};
	return color;
}

std::string cColor::Format() 
{
	return "(" + toString(r) + "," + toString(g) + "," + toString(b) + "," + toString(a) + ")";
}

cColor operator+(cColor color1, cColor color2)
{
	return cColor(color1.r + color2.r, color1.g + color2.g, color1.b + color2.b, color1.a + color2.a);
}

cColor operator-(cColor color1, cColor color2)
{
	return cColor(color1.r - color2.r, color1.g - color2.g, color1.b - color2.b, color1.a - color2.a);
}

void SetColor(cColor color) 
{
	glColor4ub(color.r, color.g, color.b, color.a);
}

//====================================================================================
//                                                                          Dimensions
//====================================================================================
Dimensions::Dimensions(int rW, int rH): 
    w(rW),
    h(rH)
{
}

Dimensions operator +(Dimensions dim1, Dimensions dim2) 
{
	return Dimensions(dim1.w + dim2.w, dim1.h + dim2.h);
}

Dimensions operator -(Dimensions dim1, Dimensions dim2) 
{
	return Dimensions(dim1.w - dim2.w, dim1.h - dim2.h);
}

//====================================================================================
//                                                                          PRLX_Shape
//====================================================================================
PRLX_Shape::PRLX_Shape(Point rPos): 
    pos(rPos)
{
}

void PRLX_Shape::Draw(float value, cColor) 
{
	// disable texture drawings
	glDisable	    (GL_TEXTURE_2D); 
	glEnable	    (GL_BLEND); 
	glBlendFunc	    (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glLoadIdentity  ();
}

//====================================================================================
//                                                             PRLX_Point : PRLX_Shape
//====================================================================================
PRLX_Point::PRLX_Point(Point rPos): 
    PRLX_Shape(rPos)
{
}

void PRLX_Point::Draw(float pointSize, cColor color) 
{
	// set up primitive shape drawing environment
	PRLX_Shape::Draw(pointSize, color);

	// set line properties
	SetColor(color);
	
	glPointSize(pointSize);

	// draw point
	glBegin(GL_POINTS);
		glVertex2i(pos.x, pos.y);
	glEnd();
}

//====================================================================================
//                                                              PRLX_Line : PRLX_Shape
//====================================================================================
PRLX_Line::PRLX_Line (Point rPos1, Point rPos2): 
    PRLX_Shape(rPos1),
    pos2(rPos2)
{
}

void PRLX_Line::Draw(float lineWidth, cColor color) 
{
	// set up primitive shape drawing environment
	PRLX_Shape::Draw(lineWidth, color);

	// set line properties
	SetColor(color);
	glLineWidth(lineWidth); 
	
	// draw line
	glBegin(GL_LINES); 
		glVertex2i(pos.x,pos.y);
		glVertex2i(pos2.x,pos2.y); 
	glEnd();
}

//====================================================================================
//                                                              PRLX_Rect : PRLX_Shape
//====================================================================================
PRLX_Rect::PRLX_Rect(Point rPos, Dimensions rDim, int rNX, int rNY): 
    PRLX_Shape(rPos),
    dim(rDim),
    nX(rNX),
    nY(rNY)
{
}

void PRLX_Rect::Draw(float fill, cColor color) 
{
	// set up primitive shape drawing environment
	PRLX_Shape::Draw(fill, color);

	// set line properties
	SetColor(color);

	// determine fill type
	GLenum mode;

	(fill)
        ? mode = GL_QUADS
        : mode = GL_LINE_LOOP;

	// draw rectangle
	glBegin(mode);
		glVertex2i(pos.x, pos.y);
		glVertex2i(pos.x + dim.w, pos.y);
		glVertex2i(pos.x + dim.w, pos.y + dim.h);
		glVertex2i(pos.x, pos.y + dim.h);
	glEnd();
}

//====================================================================================
//                                                          PRLX_Triangle : PRLX_Shape
//====================================================================================
PRLX_Triangle::PRLX_Triangle(Point rPos1, Point rPos2, Point rPos3):
    PRLX_Shape(rPos1),
    pos2(rPos2),
    pos3(rPos3)
{
}

void PRLX_Triangle::Draw(bool fill, cColor color) 
{
	// set up primitive shape drawing environment
	PRLX_Shape::Draw(fill, color);

	// set line properties
	SetColor(color);

	// determine fill type
	GLenum mode;

    (fill)
        ? mode = GL_QUADS
        : mode = GL_LINE_LOOP;

	// draw triangle
	glBegin(GL_TRIANGLES);
		glVertex2i(pos.x, pos.y);
		glVertex2i(pos2.x, pos2.y);
		glVertex2i(pos3.x, pos3.y);
	glEnd();
}

//====================================================================================
//                                                            PRLX_Circle : PRLX_Shape
//====================================================================================
PRLX_Circle::PRLX_Circle(Point rPos, int rRadius):
    PRLX_Shape(rPos),
    radius(rRadius) 
{
}

void PRLX_Circle::Draw(int smoothness, cColor color) 
{
	PRLX_Triangle triangle, prev;
	Point origin = pos, vertex, vertex2, vertex3;	
	int shade, index = 0;

	shade = 255;
	vertex2 = Point(pos.x + (index-1)*smoothness, pos.y + prev.pos2.y - radius);
	vertex3 = Point(pos.x + (index+1)*smoothness, pos.y - radius);
	triangle = PRLX_Triangle(origin, vertex2, vertex3);
	prev = triangle;
	index++;
	triangle.Draw(false, cColor(shade,shade,shade,255));

	shade = 245;
	vertex2 = prev.pos3;
	vertex3 = Point(pos.x + (index+1)*smoothness, pos.y - radius);
	triangle = PRLX_Triangle(origin, vertex2, vertex3);
	triangle.Draw(false, cColor(shade,shade,shade,255));

	return;
}