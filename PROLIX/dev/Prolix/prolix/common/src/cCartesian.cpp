//====================================================================================
// @Title:      CARTESIAN
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cCartesian.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cCartesian.h"
#include "../include/xString.h"
#include "../include/xDraw.h"

//====================================================================================
//                                                                          cCartesian
//====================================================================================
cCartesian::cCartesian(int rX, int rY):
    x(rX),
    y(rY)
{
}

cCartesian::cCartesian(float rX, float rY):
    x((int)rX),
    y((int)rY) 
{
}

cCartesian::cCartesian(double rX, double rY):
    x((int)rX),
    y((int)rY)
{
}

std::string cCartesian::Format() 
{
	return "(" + toString(x) + "," + toString(y) + ")";
}

//====================================================================================
//                                                                               Point
//====================================================================================
Point::Point(int rX, int rY): 
    cCartesian(rX, rY) 
{
}

Point::Point(float rX, float rY):
    cCartesian((int)rX, (int)rY) 
{
}

Point::Point(double rX, double rY): 
    cCartesian((int)rX, (int)rY) 
{
}

void Point::Center(Dimensions dim)
{
    x -= dim.w/2;
    y -= dim.h/2;
}

Point operator +(Point pos1, Point pos2) 
{
	return Point(pos1.x + pos2.x, pos1.y + pos2.y);
}

Point operator -(Point pos1, Point pos2)
{
	return Point(pos1.x - pos2.x, pos1.y - pos2.y);
}

bool operator ==(Point pos1, Point pos2) 
{
	return pos1.x == pos2.x && pos1.y == pos2.y;
}

bool operator !=(Point pos1, Point pos2) 
{
	return pos1.x != pos2.x || pos1.y != pos2.y;
}

//====================================================================================
//                                                                                Quad
//====================================================================================
Quad::Quad(Point tl, Point tr, Point bl, Point br) 
{
	top_left = tl;
	top_right = tr;
	bottom_left = bl;
	bottom_right = br;
}