//====================================================================================
// @Title:      WINDOW
//------------------------------------------------------------------------------------
// @Location:   /prolix/interface/include/cmpWindow.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cmpWindow.h"

//====================================================================================
//                                                                           cmpWindow
//====================================================================================
cmpWindow::cmpWindow(Point rPos, Dimensions rDim, cTextureId rSkinId) 
{
	pos = rPos;
	dim = rDim;

	alive = true;

	// check dimensions
	if (dim.w != 0 && (float)(dim.w/16) != 0) 
    {
		LogMgr->Write(WARNING, "cmpWindow::cmpWindow >>>> Width of window is not a multiple of 32 > 0 as required");
	}
	if (dim.h != 0 && (float)(dim.h/16) != 0) 
    {
		LogMgr->Write(WARNING, "cmpWindow::cmpWindow >>>> Height of window is not a multiple of 32 > 0 as required");
	}

	skin = AssetMgr->Load<Texture>(rSkinId);
	frames = new cSprite(rSkinId, 8, 8);

	frames->spriteset[F_L1N1].pos.x += 8;

	frames->spriteset[F_L1N2].pos.x -= 22;
	frames->spriteset[F_L1N2].pos.y += 8;

	frames->spriteset[F_L2N1].pos.x += 16;
	frames->spriteset[F_L2N1].pos.y -= 8;

	frames->spriteset[F_L2N2].pos.x -= 8;
	frames->spriteset[F_L2N2].pos.y += 0;

	LogMgr->Write(VERBOSE, "cmpWindow::cmpWindow >>>> Created an interface window");
}

void cmpWindow::Draw() 
{
	int numX = dim.w/16 - 2;
	int numY = dim.h/16 - 2;

	// top texture bar
	frames->DrawFrame(B_TOPLEFT, Point(pos.x + 8, pos.y + 8));
	frames->DrawFrame(T_TOPLEFT, Point(pos.x + 8, pos.y + 8));
	for (int i=0;i<numX-1;i++) 
    {
		if (i%2 == 0) 
        {
			frames->DrawFrame(B_TOPH1, Point(pos.x + (i+1)*16 + 8, pos.y + 8));
			frames->DrawFrame(T_TOPH1, Point(pos.x + (i+1)*16 + 8, pos.y + 8));
		}
		if (i%2 == 1) 
        {
			frames->DrawFrame(B_TOPH2, Point(pos.x + (i+1)*16 + 8, pos.y + 8));
			frames->DrawFrame(T_TOPH2, Point(pos.x + (i+1)*16 + 8, pos.y + 8));
		}
	}
	frames->DrawFrame(B_TOPRIGHT, Point(pos.x + numX*16 + 8,pos.y + 8));
	frames->DrawFrame(T_TOPRIGHT, Point(pos.x + numX*16 + 8,pos.y + 8));

	for (int i=0;i<numY;i++) 
    {
		for (int j=0;j<numX+1;j++) 
        {
			Point coord = Point(pos.x + j*16 + 8, pos.y + (i+1)*16 + 8);

			if (i%2 == 0) 
            {
				if (j%2 == 0) 
                {
					frames->DrawFrame(B_L1N1, coord);
					frames->DrawFrame(T_L1N1, coord);
				}
                else
                {
					frames->DrawFrame(B_L1N2, coord);
					frames->DrawFrame(T_L1N2, coord);
				}
			}
            else 
            {
				if (j%2 == 0)
                {
					frames->DrawFrame(B_L2N1, coord);
					frames->DrawFrame(T_L2N1, coord);
				}
                else
                {
					frames->DrawFrame(B_L2N2, coord);
					frames->DrawFrame(T_L2N2, coord);
				}
			}
		
		}
	}

	// bottom texture bar
	frames->DrawFrame(B_BOTLEFT, Point(pos.x + 8, pos.y + numY*16 + 8));
	frames->DrawFrame(T_BOTLEFT, Point(pos.x + 8, pos.y + numY*16 + 8));

	for (int i=0;i<numX-1;i++) 
    {
		if (i%2 == 0) 
        {
			frames->DrawFrame(B_BOTH1, Point(pos.x + (i+1)*16 + 8, pos.y + numY*16 + 8));
			frames->DrawFrame(T_BOTH1, Point(pos.x + (i+1)*16 + 8, pos.y + numY*16 + 8));
		}
		if (i%2 == 1) 
        {
			frames->DrawFrame(B_BOTH2, Point(pos.x + (i+1)*16 + 8, pos.y + numY*16 + 8));
			frames->DrawFrame(T_BOTH2, Point(pos.x + (i+1)*16 + 8, pos.y + numY*16 + 8));
		}
	}

	frames->DrawFrame(B_BOTRIGHT, Point(pos.x + numX*16 + 8,pos.y + numY*16 + 8));
	frames->DrawFrame(T_BOTRIGHT, Point(pos.x + numX*16 + 8,pos.y + numY*16 + 8));

	////////////////////////////////////////////////////////////////////////////////

	// draw top bar
	frames->DrawFrame(F_TOPLEFT, Point(pos.x,pos.y));

	for (int i=0;i<numX;i++) 
    {
		if (i%2 == 0) frames->DrawFrame(F_TOPH1, Point(pos.x + (i+1)*16, pos.y));
		if (i%2 == 1) frames->DrawFrame(F_TOPH2, Point(pos.x + (i+1)*16, pos.y));
	}
	frames->DrawFrame(F_TOPRIGHT, Point(pos.x + (numX+1)*16,pos.y));

	// draw vertical frame
	for (int i=0;i<numY;i++) 
    {
		if (i%2 == 0) 
        {
			frames->DrawFrame(F_VLEFT1, Point(pos.x, pos.y + (i+1)*16));
			frames->DrawFrame(F_VRIGHT1, Point(pos.x + (numX+1)*16, pos.y + (i+1)*16));
		}
		if (i%2 == 1) 
        {
			frames->DrawFrame(F_VLEFT2, Point(pos.x, pos.y + (i+1)*16));
			frames->DrawFrame(F_VRIGHT2, Point(pos.x + (numX+1)*16, pos.y + (i+1)*16));
		}
	}
	
	// draw bottom bar
	frames->DrawFrame(F_BOTLEFT, Point(pos.x,pos.y + (numY + 1)*16));

	for (int i=0;i<numX;i++) 
    {
		if (i%2 == 0) frames->DrawFrame(F_BOTH1, Point(pos.x + (i+1)*16, pos.y + (numY + 1)*16));
		if (i%2 == 1) frames->DrawFrame(F_BOTH2, Point(pos.x + (i+1)*16, pos.y + (numY + 1)*16));
	}

	frames->DrawFrame(F_BOTRIGHT, Point(pos.x + (numX+1)*16,pos.y + (numY + 1)*16));

	return;
}

cmpWindow::~cmpWindow() 
{
	LogMgr->Write(VERBOSE, "cmpWindow::~cmpWindow >>>> Deleted an interface window");
}

//====================================================================================
//                                                                              Extern
//====================================================================================
std::vector<std::string> LineWrap
	(cFont font, std::string text, int width) 
{
	std::vector<std::string> lines;

	std::string paragraph;
	std::vector<std::string> temp;

    while (text.find ("@") != std::string::npos) 
    {
		temp.clear();
		paragraph = text.substr(0, text.find ("@") + 1); 
		temp = LineWrapParagraph(font, paragraph, width);
	
		for (unsigned int i=0;i<temp.size();i++) 
        {
			if (temp[i] != "") 
            {
				lines.push_back(temp[i]);
			}
		}

		text = text.substr(text.find ("@") + 1, text.length());
	}	

	return lines;
}

std::vector<std::string> LineWrapParagraph 
	(cFont font, std::string paragraph, int width) 
{
	std::vector<std::string> words;  // stores the words 
	std::vector<std::string> lines;  // stores the Formatted lines
	
    // constructing words vector
	int search; // search index for delimiters
	while (paragraph.find (" ") != std::string::npos || paragraph.find ("@") != std::string::npos) 
    {
		// if found period but not space
		if (paragraph.find ("@") != std::string::npos && paragraph.find (" ") == std::string::npos) 
        {
			// add word to words vector
			search = paragraph.find ("@");
			words.push_back(paragraph.substr(0,search));
			break;
		}

		// else a space is found
		// add words to word vector
		search = paragraph.find (" ");
		words.push_back(paragraph.substr(0, search));
		paragraph = paragraph.substr(search + 1, paragraph.length());
	};

	// Formatting lines
	cTexture *line; // the current calculated line
	
    // progressive Formatted lines as strings
	std::string curr = "", prevCurr = "";
	
    // iterate through registered words
	for (unsigned int i=0; i<words.size(); i++) 
    {
		curr = curr + words[i] + " ";

        line = Engine->Text->Prerender(font, curr);
		
        // maximum width not reached
		if (line->dim.w < width) 
        {
            // continue to next word
			prevCurr = curr;

            AssetMgr->RemoveLast<Texture>();

			continue;
		}

		// maximum width reached. Commit to lines vector
		curr = words[i] + " ";
		lines.push_back(prevCurr);
        AssetMgr->RemoveLast<Texture>();
	}
	lines.push_back(curr);

	// finished
	return lines;
}