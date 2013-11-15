//====================================================================================
// @Title:      CARTESIAN
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cCartesian.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Cartesian tools to create 2-tuple typed inputs, particularly window coordinates
//  to indicate drawing locations.
//
//====================================================================================
#ifndef __PROLIX_BASE_COMMON_CARTESIAN_H__
#define __PROLIX_BASE_COMMON_CARTESIAN_H__

#include <string>

// forward declarations
struct Dimensions;

//====================================================================================
//                                                                          cCartesian
//====================================================================================
struct cCartesian 
{
    int x;  // x-coord
    int y;  // y-coord

    // prints out string Format of cartesian coordinate
	std::string Format();

	// Constructors
	cCartesian(int x = 0, int y = 0);
	cCartesian(float x, float y);
	cCartesian(double x, double y);
};

//====================================================================================
//                                                                               Point
//====================================================================================
struct Point : public cCartesian 
{
    void Center(Dimensions dim);
    
    // Constructors
	Point(int x = 0, int y = 0);
	Point(float x, float y);
	Point(double x, double y);
};

// Arithmetic operations for Point manipulation
Point operator +(Point pos1, Point pos2);
Point operator -(Point pos1, Point pos2);
bool operator ==(Point pos1, Point pos2);
bool operator !=(Point pos1, Point pos2);

//====================================================================================
//                                                                                Quad
//====================================================================================
struct Quad
{
    // corners of the quadrilateral
	Point top_left;
	Point top_right;
	Point bottom_left;
	Point bottom_right;

	// Constructor
	Quad(Point top_left, Point top_right, Point bottom_left, Point bottom_right);
};

#endif