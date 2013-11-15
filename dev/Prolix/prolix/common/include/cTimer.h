//====================================================================================
// @Title:      TIMER
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cTimer.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Timer class for time-related events and regulating frame rate. Serves as common
//  medium between local time, clock-based events and ticks elapsed at application
//  instantiation.
//
//====================================================================================
#ifndef __PROLIX_COMMON_TIMER_H__
#define __PROLIX_COMMON_TIMER_H__

#include <string>

// returns the local time as a Formatted string
std::string GetLocalTime();

//====================================================================================
//                                                                              cTimer
//====================================================================================
struct cTimer 
{
	// timer counters
	int startTicks;
    int pausedTicks;
	
    // timer states
    bool paused;
    bool started;

    // timer controls
	void Start();		    // start the timer
	void Stop();		    // stop the timer
	void Pause();		    // pause the timer
	void Unpause();		    // unpause the timer
	int GetTicks();	        // return number of ticks since time instantiation
	std::string Format();	// return string of ticks since timer instantiation

	// Constructor
	cTimer();
};

#endif