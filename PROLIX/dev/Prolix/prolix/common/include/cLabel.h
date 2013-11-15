//====================================================================================
// @Title:      LABEL
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cLabel.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Labels are rendered text buffered into this class. It provides an encapsulated
//  PrlxText rendered texture API.
//
//====================================================================================
#ifndef __PROLIX_COMMON_LABEL_H__
#define __PROLIX_COMMON_LABEL_H__

#include "../include/cBaseObject.h"
#include "../include/cFont.h"

//====================================================================================
//                                                                              cLabel
//====================================================================================
class cLabel
{
	cBaseObject *mText;
	cFont mFont;
	std::string mMessage;

  public:
	void Render(Point point = Point(0,0), bool deleteAfterRender = false);
	
	void Message(std::string newMessage);
	void Font(cFont newFont);

	// Constructor
	cLabel();
	cLabel(cFont font, std::string message);

	// Destructor
	~cLabel();
};

#endif