//====================================================================================
// @Title:      TEXTBOX
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpTextbox.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  A window that displays blocks of text inside the window.
//
//====================================================================================
#ifndef __PROLIX_INTERFACE_TEXTBOX_H__
#define __PROLIX_INTERFACE_TEXTBOX_H__

#include "../include/cmpWindow.h"

//====================================================================================
//                                                                          cmpTextbox
//====================================================================================
struct cmpTextbox : public cmpWindow 
{
    cFont font;     // font to write text in
    std::string text;	// written text
	
	std::vector<cTexture *> lines; // rendered lines of text in prescribed width
	std::vector<std::string> strlines; // line wrapped vector of strings corresponding to the rendered lines above
	int currentLine;                   // the current line that the window is focussed
	int displayRange;                  // the range of lines that can be shown on the textbox display
	bool overflow;                     // flag set to true if the text overflows the window
	cCommand *scrollDown;              // scroll down the selection
	cCommand *scrollUp;                // scroll up the selection
	
	// processes a received text and Formats it into pargraph form
	void Process(std::string text);

	void ShiftDown();  // scroll down one line of visibility
	void ShiftUp();    // scroll up one line of visibility

	void Draw();     // derived method draw
	void Move();     // moves the selection
	void Update();   // performs both draw and move

	// Constructor
	cmpTextbox(
        cFont font,
        std::string text,
		Point position = Point(0,0),
        Dimensions dimensions = Dimensions(400,400), 
		cTextureId skinId = DEFAULT_WSKIN_ID);

	// Destructor
	~cmpTextbox();
};

#endif