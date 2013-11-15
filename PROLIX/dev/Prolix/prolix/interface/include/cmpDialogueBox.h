//====================================================================================
// @Title:      DIALOGUE BOX
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpDialogueBox.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  A derived class of cmpWindow that supports facesets and dialogue.
//
//====================================================================================
#ifndef __PROLIX_INTERFACE_DIALOGUEBOX_H__
#define __PROLIX_INTERFACE_DIALOGUEBOX_H__

#include "../include/cmpWindow.h"
#include "../../common/include/cConstants.h"

//====================================================================================
//                                                                      cmpDialogueBox
//====================================================================================
struct cmpDialogueBox : public cmpWindow
{
    // default window height for dialogue box
    static const int DefaultWindowHeight = 128;

	std::string script;    // lines of speech to be presented in the dialogue box
	cFont font;        // font for script

	// pages generated for the script provided
	std::vector< std::vector<std::string> > pages;

    // the current page in focus
	int currentPage;

	cSprite *faceset;             // a faceset of emotions to accompany the dialogue (optional)
	std::vector<int> face_frames; // desired face frame index
	eDirection orientation;        // the orientation of the face relative to the window
	eDirection location;           // the location of the face relative to the window

    // a command to move onto the next page
	cCommand *flipPage;

	void Draw();      // derived method draw
	void Move();      // moves the selection
	void Update();    // performs both draw and move
	void Configure(); // initialize and configure pages

	// Constructors
	
	// Script and portrait presented
	cmpDialogueBox(
        std::string script, 
        cSprite *faceset, 
        int frame,
		cFont font, 
        eDirection orientation = RIGHT, 
        eDirection location = LEFT, 
		Point pos = Point(0,SCREEN_HEIGHT -  DefaultWindowHeight), 
        Dimensions dim = Dimensions(SCREEN_WIDTH,128),
		cTextureId skinId = DEFAULT_WSKIN_ID);

	// Only script presented
	cmpDialogueBox(
        std::string script, 
        cFont font,
		Point pos = Point(0,SCREEN_HEIGHT -  DefaultWindowHeight), 
        Dimensions dim = Dimensions(SCREEN_WIDTH,128),
		cTextureId skinId = DEFAULT_WSKIN_ID);

	// Script and series of portraits presented
	cmpDialogueBox(
        std::string script, 
        cSprite *faceset, 
        std::vector<int> frames,
		cFont font, 
        eDirection orientation = RIGHT, 
        eDirection location = LEFT, 
		Point pos = Point(0,SCREEN_HEIGHT -  DefaultWindowHeight), 
        Dimensions dim = Dimensions(SCREEN_WIDTH,128),
		cTextureId skinId = DEFAULT_WSKIN_ID);

	// Destructor
	~cmpDialogueBox();
};

#endif