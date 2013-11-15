//====================================================================================
// @Title:      TIMER
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cTimer.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <ctime>
#include <SDL.h>
#include <string>
#include "../include/cTimer.h"
#include "../include/xString.h"

std::string GetLocalTime() 
{
	time_t rawtime;
	struct tm *timeinfo;
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	return toString(asctime(timeinfo));
}

//====================================================================================
//                                                                              cTimer
//====================================================================================
cTimer::cTimer() 
{
	startTicks = pausedTicks = 0;
	paused = started = false;
}

void cTimer::Start() 
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void cTimer::Stop() 
{
	started = false;
	paused = false;
}

int cTimer::GetTicks() 
{
	if (started) 
    {
        return (paused)
            ? pausedTicks
            : SDL_GetTicks() - startTicks;
	}
	return 0;
}

void cTimer::Pause() 
{
	if (started && !paused) 
    {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void cTimer::Unpause() 
{
	if (paused) 
    {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

std::string cTimer::Format() 
{
	std::stringstream tstream;
	tstream << GetTicks() / 1000.f;
	return tstream.str();
}
