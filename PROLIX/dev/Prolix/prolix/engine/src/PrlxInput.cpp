//====================================================================================
// @Title:      PROLIX INPUT
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxInput.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <SDL.h>
#include "../include/PrlxEngine.h"
#include "../include/PrlxInput.h"
#include "../include/PrlxPhysics.h"
#include "../../common/include/xString.h"

//====================================================================================
//                                                                          PrlxInput
//====================================================================================
PrlxInput::PrlxInput() 
{
	LogMgr->Write(INFO, "PrlxInput::PrlxInput >>>> PROLIX Input Engine initalized");

	Mouse = new cMouse();
	Mouse->Cursor = NULL;
}

int PrlxInput::IsMouseButtonPressed(Uint8 mouse_button) 
{
	return (MouseState & SDL_BUTTON(mouse_button));
}

//====================================================================================
//                                                              PrlxInput::cMouse
//====================================================================================
PrlxInput::cMouse::cMouse () 
{
	pos.x = SCREEN_WIDTH / 2;
	pos.y = SCREEN_HEIGHT / 2;
	prev_pos.x = pos.x;
	prev_pos.y = pos.y;
}

std::string PrlxInput::cMouse::Format() 
{
	return "(" + toString(pos.x) + "," + toString(pos.y) + ")";
}

bool PrlxInput::cMouse::IsHover(PRLX_Rect rect) 
{
	if (Cursor == NULL) 
    {
        return false;
    }

	if (Engine->Physics->HitTest(Cursor->coll_rect, rect)) 
    {
		return true;
	}
	
    return false;
}

void PrlxInput::cMouse::Update() 
{
	SDL_GetMouseState(&pos.x, &pos.y);
	//if (prevX != X && prevY != Y)
	//	Engine.Logger->Write(DEBUG, "Mouse at (" + toString(X) + "," + toString(Y) + ")");
	prev_pos.x = pos.x;
	prev_pos.y = pos.y;
}

void PrlxInput::GetInput() 
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) 
    {
		switch (event.type) 
        {
			// when window is manually closed
			case SDL_QUIT:
				Engine->CloseApplication();
				break;
		}
	}
	Mouse->Update();
}

PrlxInput::~PrlxInput()
{
    LogMgr->Write(INFO, "PrlxInput::~PrlxInput >>>> Cleaning up PROLIX Input");
}

//====================================================================================
//                                                                            cCommand
//====================================================================================
cCommand::cCommand(SDLKey rKey, int rDelay, bool rAllowHold) 
{
	key = rKey;
	pressed = false;
	allow_hold = rAllowHold;
	delay = rDelay;
	Timer.Start();
}

bool cCommand::Pollable() 
{
	if (allow_hold) 
    {
		if (Engine->Input->KeyState[key]) 
        {
			if (Timer.GetTicks() > delay) 
            {
				Timer.Start();
				return true;
			}
		}
	}
    else 
    {
		if (Engine->Input->KeyState[key]) 
        {
			if (!pressed) 
            {
				pressed = true;
				if (Timer.GetTicks() > delay) 
                {
					Timer.Start();
					return true;
				}
			}
		}
        else 
        {
            pressed = false;
        }
	}
	return false;
}

//====================================================================================
//                                                                       cCommandGroup
//====================================================================================
cCommandGroup::cCommandGroup() 
{
	CommandGroup.clear();
}

cCommandGroup::cCommandGroup(std::map<std::string, cCommand *> command_group) 
{
	CommandGroup = command_group;
}

cCommand *cCommandGroup::GetCommand(std::string command_id) 
{
    if (!CommandGroup.count(command_id))
    {
        LogMgr->Write(FATAL, "cCommandGroup::GetCommand >>>> Command group given invalid command id: '" + command_id + "'");
        return NULL;
    }
	return CommandGroup[command_id];
}

void cCommandGroup::AddCommand(std::string command_id, cCommand *command) 
{
	CommandGroup[command_id] = command;
}

bool cCommandGroup::ExistsCommand(std::string command_id) 
{
	return (CommandGroup.count(command_id) > 0);
}

void cCommandGroup::RemoveCommand(std::string command_id) 
{
	std::map<std::string, cCommand *>::iterator loc;
	loc = CommandGroup.find (command_id);
	CommandGroup.erase(loc);
}

//====================================================================================
//                                                                          UserInput
//====================================================================================
UserInput::UserInput() 
{
	input = "";
	delay.Start();

	Uint8 lower[] = 
    {
		SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j,
		SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t,
		SDLK_u, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z
	};

	Uint8 nums[] = 
    {
		SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9
	};

	lowerCase.insert(lowerCase.begin(), lower, lower + sizeof(lower)/sizeof(Uint8));
	numbers.insert(numbers.begin(), nums, nums + sizeof(nums)/sizeof(Uint8));
}

void UserInput::Update() 
{
	if (delay.GetTicks() > 58) {
		for (unsigned int i=0;i<lowerCase.size();i++)
        {
			if (Engine->Input->KeyState[lowerCase[i]]) input += (char)((int)('a') + i);
        }

		for (unsigned int i=0;i<numbers.size();i++)
        {
			if (Engine->Input->KeyState[numbers[i]]) input += (char)((int)('0') + i);
        }

		if (Engine->Input->KeyState[SDLK_SPACE]) input += (char)((int)(' '));
		if (Engine->Input->KeyState[SDLK_BACKSLASH]) input += (char)((int)('\\'));
		if (Engine->Input->KeyState[SDLK_SEMICOLON]) input += (char)((int)(':'));
		if (Engine->Input->KeyState[SDLK_BACKSPACE]) input = input.substr(0,input.length()-1);

		delay.Start();
	}
}
 
UserInput::~UserInput () 
{
}