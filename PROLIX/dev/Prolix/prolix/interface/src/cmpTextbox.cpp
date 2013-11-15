//====================================================================================
// @Title:      TEXTBOX
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpTextbox.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cmpTextbox.h"

//====================================================================================
//                                                                          cmpTextbox
//====================================================================================
cmpTextbox::cmpTextbox(cFont rFont, std::string rText,
				 Point rPos, Dimensions rDim, cTextureId rSkinId):
    font(rFont),
    text(rText),
    cmpWindow(rPos, rDim, rSkinId) 
{
	LogMgr->Write(VERBOSE, "cmpTextbox::cmpTextbox >>>> Created a textbox of type interface window");
	
	// set top display to 0
	currentLine = 0;

	// create commands
	scrollDown = new cCommand(SDLK_DOWN, 100);
	scrollUp   = new cCommand(SDLK_UP, 100);

    // process text
	Process(text);
}

void cmpTextbox::Process(std::string text) 
{
	// refresh data structures
	strlines.clear();
	lines.clear();

	// Format text
	strlines = LineWrap(font, text, dim.w - 32);

	// pre-render text line-by-line
	for (unsigned int i=0; i<strlines.size(); i++) 
    {
		lines.push_back(Engine->Text->Prerender(font, strlines[i]));
	}

	// calculate display range
	int lineheight = lines[0]->dim.h;
	for (displayRange = 0; displayRange*lineheight < dim.h-32; displayRange++);
	displayRange--;

	// determine if an overlow will occur
	if ((unsigned int)displayRange >= lines.size()) 
    {
		overflow = false;
		displayRange = lines.size();
	}
    else
    {
		overflow = true;
	}
}

void cmpTextbox::Draw() {
	// draw window
	cmpWindow::Draw();

	// display text
	int line = 0;
	for (int i=currentLine; i<currentLine + displayRange; i++) 
    {
		int linespacing = line*lines[0]->dim.h;
		lines[i]->Draw(Point(pos.x + 16, pos.y + 16 + linespacing));
		line++;
	}

	// draw continuation arrow if necessary
	if (overflow) 
    {
		if (currentLine > 0) 
        {
			frames->DrawFrame(F_L1N1, Point(pos.x + (dim.w - frames->spriteset[F_L1N1].dim.w)/2, pos.y + 8));
		}
		if (currentLine < (int)(lines.size() - displayRange)) 
        {
			frames->DrawFrame(F_L2N2, Point(pos.x + (dim.w - frames->spriteset[F_L2N2].dim.w)/2, pos.y + dim.h - 35));
		}
	}
}

void cmpTextbox::ShiftUp() 
{
	if (currentLine == 0) 
    {
        currentLine = 0;
    }
	else 
    {
        currentLine--;
    }
}

void cmpTextbox::ShiftDown() 
{
	if (currentLine == lines.size() - displayRange)
    {
		currentLine = lines.size() - displayRange;
    }
	else
    {
        currentLine++;
    }
}

void cmpTextbox::Move() 
{
	if (overflow) 
    {
		if (scrollDown->Pollable()) ShiftDown();
		if (scrollUp->Pollable()) ShiftUp();
	}
}

void cmpTextbox::Update() 
{
	Draw();
	Move();
}

cmpTextbox::~cmpTextbox() 
{
	// remove all lines of text from text stack
	for (unsigned int i=0;i<strlines.size();i++) 
    {
        AssetMgr->Remove<Texture>(font.id + font.color.Format() + strlines[i]);
	}
	LogMgr->Write(VERBOSE, "cmpTextbox::~cmpTextbox >>>> Deleted a textbox window");
}