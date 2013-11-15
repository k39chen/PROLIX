//====================================================================================
// @Title:      OPTION LIST
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpOptionList.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  A derived class of the cmpWindow class that displays an option list that can be
//  controlled by the directional keys on the keyboard.
//
//====================================================================================
#ifndef __PROLIX_INTERFACE_OPTIONLIST_H__
#define __PROLIX_INTERFACE_OPTIONLIST_H__

#include "../include/cmpWindow.h"

//====================================================================================
//                                                                       cmpOptionList
//====================================================================================
struct cmpOptionList : public cmpWindow 
{
	cFont font;                       // font to write options in
    cFont hover_font;                 // font for the focussed option

	std::vector<cTexture *> options;  // list of options as rendered text
	std::vector<std::string> stroptions;  // string equivalent of options

	cAnimation *Cursor;  // Cursor animation
	int current;         // current option selected
	bool terminated;     // flag to indicate that the selection has been made
	
    // group of commands to move navigate the options
    cCommandGroup *Action;

	void Draw();     // derived method draw
	void Move();     // moves the selection
	void Update();   // performs both draw and move
	
	int Response();  // returns the reponse selected

	// Constructor
	cmpOptionList (
        cFont font,
        cFont hover_font,
		std::vector<std::string> options,
		Point position = Point(0,0),
        Dimensions dimensions = Dimensions(-1,-1), 
		cTextureId skinId = DEFAULT_WSKIN_ID);

	// Destructor
	~cmpOptionList ();
};

#endif