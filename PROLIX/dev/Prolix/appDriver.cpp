//====================================================================================
// @Title:      APPLICATION DRIVER
//------------------------------------------------------------------------------------
// @Location:   /appDriver.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//   Serves as a primary test environment and game init area
//
//====================================================================================
#include <SDL.h>
#include <iostream>
#include "libDriver.h"

using namespace std;

//====================================================================================
//                                                                     MAIN DEFINITION
//====================================================================================
int main (int argc, char **argv) 
{
    cGame::GetInstance();

	cBaseObject *Thing = new cBaseObject(AssetMgr->Load<Texture>("msn.png"));

	cLabel *Label = new cLabel(cFont("ninjapenguin.ttf", 80, PRLX_White), "something");

	while (Game->Loop())
	{
		if (Engine->Input->KeyState[SDLK_RIGHT])
		{
			Tween.FromTo(Thing, POS_X, 20, Thing->Position().x, Thing->Position().x + 32);
		}
		
		Label->Render();
		Thing->Update();
	}

	return 0;
}