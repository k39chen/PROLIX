//====================================================================================
// @Title:      LOG MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cLogMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <SDL.h>
#include <fstream>
#include <string>
#include <ctime>
#include "../../common/include/cTimer.h"
#include "../../common/include/xString.h"
#include "../include/cLogMgr.h"

//====================================================================================
//                                                                             cLogMgr
//====================================================================================
cLogMgr *cLogMgr::mInstance = NULL;

cLogMgr::cLogMgr()
{
    // set inital logger settings
	mOutfile = LOG_PATH;
	mVerbosity = LOG_VERBOSITY;
	mActive = true;

	if (mOutfile != "") 
    {
		mWriter = new std::ofstream(mOutfile);
		Write(INFO, "OVERSEER log manager initalized");
		Write(INFO, "Set log verbosity: " + GetVerbosityName());
		Write(INFO, ("Logging printed to " + toString(mOutfile)));
	
	}
    else 
    {
		WriteToConsole(INFO, "OVERSEER log manager initalized");
		WriteToConsole(INFO, "Set log verbosity: " + GetVerbosityName());
		WriteToConsole(INFO, "No file will be written");
	}
}

cLogMgr *cLogMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cLogMgr;
        return mInstance;
    }
    return mInstance;
}

bool cLogMgr::IsInVerbosityRange(eLogLevel verbosity) 
{
	return (mVerbosity >= verbosity);
}

std::string cLogMgr::GetVerbosityName() 
{
	switch (mVerbosity) 
    {
		case 0: return "INFO";
		case 1: return "VERBOSE";
		case 2: return "DEBUG";
		case 3: return "FATAL";
		case 4: return "WARNING";
		default: return "INVALID LOG LEVEL";
	}
}

std::string cLogMgr::GetVerbosityToken(eLogLevel verbosity) 
{
	switch (verbosity) 
    {
		case 0:	return "I: ";
		case 1:	return "V: ";
		case 2:	return "D: ";
		case 3:	return "F: ";
		case 4: return "W: ";
		default: return "X: ";
	}
}

std::string cLogMgr::GetTimeStamp() 
{
	return "(" + GetLocalTime().substr(11,8) + ")";
}

void cLogMgr::ViewLog() 
{
	system (("notepad.exe " + toString(mOutfile)).c_str());
}

void cLogMgr::WriteToFile(eLogLevel verbosity, std::string entry) 
{
	if (IsInVerbosityRange (verbosity)) 
    {
		(mOutfile != "")
            ? *mWriter << entry << std::endl
            : WriteToConsole(FATAL, "cLogMgr::WriteToFile >>>> Could not print to file. No path specified");
	}
}

void cLogMgr::WriteToConsole(eLogLevel verbosity, std::string entry) 
{
	if (IsInVerbosityRange(verbosity)) 
    {
		std::cout << entry << std::endl;
	}
}

unsigned int cLogMgr::Verbosity() const
{
    return mVerbosity;
}

void cLogMgr::Write(eLogLevel verbosity, std::string entry) 
{
	if (ENABLE_LOGGING)
	{
		WriteToConsole(verbosity, GetTimeStamp() + GetVerbosityToken(verbosity) + entry);
		WriteToFile(verbosity, GetTimeStamp() + GetVerbosityToken(verbosity) + entry);
	}
}

void cLogMgr::ClearScreen() 
{
	system("cls");
}

cLogMgr::~cLogMgr() 
{
	if (mOutfile != "") 
    {
		mWriter->close();
	}
}