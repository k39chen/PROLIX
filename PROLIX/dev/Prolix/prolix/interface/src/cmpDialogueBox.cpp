//====================================================================================
// @Title:      DIALOGUE BOX
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpDialogueBox.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cmpDialogueBox.h"

//====================================================================================
//                                                                      cmpDialogueBox
//====================================================================================
cmpDialogueBox::cmpDialogueBox(std::string rScript, cSprite *rFaceset, int rFaceFrame,
				   cFont rFont, eDirection rOrientation, 
                   eDirection rLocation, Point rPos, Dimensions rDim,
				   cTextureId rSkinId):
    cmpWindow(rPos, rDim, rSkinId)
{
	// setting default values
	faceset = rFaceset;
	face_frames.push_back(rFaceFrame);
	orientation = rOrientation;
	location = rLocation;
	script = rScript;
	font = rFont;
	currentPage = 0;

	Configure();
}

cmpDialogueBox::cmpDialogueBox(std::string rScript, cFont rFont,
	Point rPos, Dimensions rDim, cTextureId rSkinId):
    cmpWindow(rPos, rDim, rSkinId)
{
	script = rScript;
	font = rFont;
	faceset = NULL;
	currentPage = 0;

	Configure();
}

cmpDialogueBox::cmpDialogueBox(std::string rScript, cSprite *rFaceset, 
	std::vector<int> rFaceFrames, cFont rFont, eDirection rOrientation, 
	eDirection rLocation, Point rPos, Dimensions rDim, cTextureId rSkinId):
    cmpWindow(rPos, rDim, rSkinId)
{
	script = rScript;
	faceset = rFaceset;
	face_frames = rFaceFrames;
	font = rFont;
	orientation = rOrientation;
	location = rLocation;
	currentPage = 0;

	Configure();
}

void cmpDialogueBox::Configure() 
{
	// configure flipping page command
	flipPage = new cCommand(SDLK_z, 100, false);

	std::string page;
	int width;

	while (script.find ("@") != std::string::npos) 
    {
		page = script.substr(0, script.find ("@") + 1);
		
		if (faceset != NULL) width = dim.w - faceset->spriteset[0].dim.w - 32;
		else width = dim.w - 32;

		pages.push_back(LineWrapParagraph (font, page, width));
		script = script.substr(script.find ("@") + 1, script.length());
	}
}

void cmpDialogueBox::Move() 
{
	if (flipPage->Pollable()) 
    {
		currentPage++;
	}

	if (currentPage == pages.size()) 
    {
		currentPage = pages.size() - 1;
		alive = false;
	}

	if (currentPage == face_frames.size()) 
    {
		faceset = NULL;
	}
}

void cmpDialogueBox::Draw() 
{
	cmpWindow::Draw();

	if (faceset != NULL) 
    {
		int line = 0;

		Point facePos;

		if (location == LEFT) 
        {
			facePos = pos + Point(16,16);
		}
        else
        {
			facePos = Point(pos.x + dim.w - faceset->spriteset[0].dim.w - 16, pos.y + 16);
		}

		float flip = 1;
		if (orientation == LEFT) flip = -1;
		faceset->spritesheet->Draw(flip, 1, facePos, &faceset->spriteset[currentPage]);

		cTexture *rendered = Engine->Text->Prerender(font, pages[currentPage][0]);
		
        for (unsigned int i=0; i<pages[currentPage].size(); i++) 
        {
			int linespacing = line*rendered->dim.h;
			if (location == LEFT) 
            {
				Engine->Text->Write(font, pages[currentPage][i], pos + Point(32 + faceset->spriteset[face_frames[0]].dim.w, 16 + linespacing));
			}
            else 
            {
				Engine->Text->Write(font, pages[currentPage][i], pos + Point(16, 16 + linespacing));
			}
			line++;
		}
	}
    else 
    {
		cTexture *rendered = Engine->Text->Prerender(font, pages[currentPage][0]);
		int line = 0;

		for (unsigned int i=0; i<pages[currentPage].size(); i++)
        {
			int linespacing = line*rendered->dim.h;
			Engine->Text->Write(font, pages[currentPage][i], pos + Point(16, 16 + linespacing));
			line++;
		}
	}

	// draw continuation arrow
	if (pages.size() > 1) 
    {
		frames->DrawFrame(F_L2N2, Point(pos.x + (dim.w - frames->spriteset[F_L2N2].dim.w)/2, pos.y + dim.h - 32));
	}
}

void cmpDialogueBox::Update() 
{
	Draw();
	Move();
}

cmpDialogueBox::~cmpDialogueBox() 
{
	// remove all lines of text from text stack
	for (unsigned int i=0; i<pages.size(); i++) 
    {
		for (unsigned int j=0; j<pages[i].size(); j++) 
        {
			AssetMgr->Remove<Texture>(font.id + font.color.Format() + pages[i][j]);
		}
	}

	LogMgr->Write(VERBOSE, "cmpDialogueBox::~cmpDialogueBox >>>> Deleted a dialogue window");
}