//====================================================================================
// @Title:      OPTION LIST
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpOptionList.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cmpOptionList.h"

//====================================================================================
//                                                                       cmpOptionList
//====================================================================================
cmpOptionList::cmpOptionList(cFont rFont, cFont rHoverFont,
				  std::vector<std::string> rStrOptions,
				  Point rPos, Dimensions rDim, cTextureId rSkinId):
    cmpWindow(rPos, rDim, rSkinId)
{
	font = rFont;
    hover_font = rHoverFont;
	current = 0;
	terminated = false;
	stroptions = rStrOptions;

	// create animatino for Cursor
	std::vector<int> CursorFrames;
	CursorFrames.push_back(M_TOPH2);
	CursorFrames.push_back(M_TOPRIGHT);
	CursorFrames.push_back(M_L1N2);
	CursorFrames.push_back(M_VRIGHT1);
	Cursor = new cAnimation(frames, CursorFrames);

    Action = new cCommandGroup();
    Action->AddCommand("Move Down", new cCommand(SDLK_DOWN, 100));
    Action->AddCommand("Move Up", new cCommand(SDLK_UP, 100));
    Action->AddCommand("Select", new cCommand(SDLK_z, 100));
    Action->AddCommand("Cancel", new cCommand(SDLK_x, 100));

	int maxWidth = 0;
	
	// pre-render options
	for (unsigned int i=0; i<rStrOptions.size(); i++) 
    {
		options.push_back(Engine->Text->Prerender(font, rStrOptions[i]));
		
        if (options[i]->dim.w > maxWidth)
        {
            maxWidth = options[i]->dim.w;
        }
	}

	for (unsigned int i=0; i<rStrOptions.size(); i++) 
    {
		options.push_back(Engine->Text->Prerender(hover_font, rStrOptions[i]));
	}

	if (dim.w == -1) 
    {
        dim.w = maxWidth + Cursor->Sprite->spriteset[0].dim.w + 45;
    }
	if (dim.h == -1) 
    {
        dim.h = rStrOptions.size() * options[0]->dim.h + 32;
    }

	LogMgr->Write(VERBOSE, "cmpOptionList::cmpOptionList >>>> Created an option list of type interface window");
}

void cmpOptionList::Move() 
{
	// controls for option list
    if (Action->GetCommand("Move Up")->Pollable()) 
    {
		if (current == 0) 
        {
			current = 0;
		}
        else 
        {
			current--;
		}
	}
	if (Action->GetCommand("Move Down")->Pollable()) 
    {
		if (current == options.size()/2-1) 
        {
			current = options.size()/2-1;
		}
        else 
        {
			current++;
		}
	}

	if (Action->GetCommand("Select")->Pollable()) 
    {
		terminated = true;
	}
	if (Action->GetCommand("Cancel")->Pollable()) 
    {
		terminated = true;
		current = options.size()/2-1;
	}
}

void cmpOptionList::Draw() 
{
	// draw window
	cmpWindow::Draw();

	// apply option text onto screen
	for (unsigned int i=0;i<options.size()/2;i++) 
    {
		if (i == current) 
        {
			options[i + options.size()/2]->Draw(Point(pos.x + 20 + Cursor->Sprite->spriteset[0].dim.w, pos.y + 16 + i*options[0]->dim.h));
		}
        else 
        {
			options[i]->Draw(Point(pos.x + 20 + Cursor->Sprite->spriteset[0].dim.w, pos.y + 16 + i*options[0]->dim.h));
		}
	}

	// draw Cursor
	Cursor->Play(Point(pos.x + 16, pos.y + 16 + current * options[0]->dim.h));
}

void cmpOptionList::Update() 
{
	Draw();
	Move();
}

int cmpOptionList::Response () 
{
	if (terminated) 
    {
		alive = false;
		return current;
	}
	return -1;  // no response detected yet
}

cmpOptionList::~cmpOptionList() 
{
	// remove all used texts from text stack
	for (unsigned int i=0;i<stroptions.size();i++) 
    {
		AssetMgr->Remove<Font>(font.id + font.color.Format() + stroptions[i]);
		AssetMgr->Remove<Font>(hover_font.id + hover_font.color.Format() + stroptions[i]);
	}
	LogMgr->Write(VERBOSE, "cmpOptionList::~cmpOptionList >>>> Deleted an option window");
}