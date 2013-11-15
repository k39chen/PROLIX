//====================================================================================
// @Title:      LABEL
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cLabel.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cLabel.h"
#include "../../engine/include/PrlxEngine.h"

//====================================================================================
//                                                                              cLabel
//====================================================================================
cLabel::cLabel()
{
	mText = NULL;
}

cLabel::cLabel(cFont font, std::string message)
{
	mFont = font;
	mMessage = message;
	
	mText = new cBaseObject;
	mText->Source(Engine->Text->Prerender(mFont, mMessage));
}

void cLabel::Render(Point point, bool deleteAfterRender)
{
	if (mText != NULL)
	{
		Engine->Text->Write(mFont, mMessage, point, deleteAfterRender);
	}
}

void cLabel::Message(std::string newMessage) {mMessage = newMessage;}
void cLabel::Font(cFont newFont) {mFont = newFont;}

cLabel::~cLabel()
{
}