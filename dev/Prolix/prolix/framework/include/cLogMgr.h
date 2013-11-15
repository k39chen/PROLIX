//====================================================================================
// @Title:      LOG MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cLogMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Logs application inFormation including alerts, errors, instantiation events,
//  additions to resource stacks. Option of writing to two different streams
//  (independently or concurrently): to the console's standard output or to an
//  extern .txt file.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_LOGGER_H__
#define __PROLIX_FRAMEWORK_LOGGER_H__

#include <iostream>
#include <string>
#include <map>

//====================================================================================
//                    **** LOGGING CONSTANTS AND SETTINGS ****
//====================================================================================
// [VERBOSITY  LEVELS]
enum eLogLevel
{
	FATAL,      // Fatal:   Error occurred while executing application
    WARNING,    // Warning: Directs caution to the developer/designer
    INFO,		// Info:    Provides high level inFormation of ongoing game events
    VERBOSE,    // Verbose: Detailed inFormation of backend game events
    DEBUG       // Debug:   Lowest level inFormation of backend game handlers
};

// [OVERSEER LOG SETTINGS]
static char *LOG_PATH			= "overseer.log";
static eLogLevel LOG_VERBOSITY	= VERBOSE;
static bool ENABLE_LOGGING		= true;

// singleton accessor
#define LogMgr cLogMgr::GetInstance()

//====================================================================================
//                                                                             cLogMgr
//====================================================================================
class cLogMgr
{
    static cLogMgr *mInstance;  // instance of singleton class

    char *mOutfile;				// file to be written to
	std::ofstream *mWriter;		// file stream writer
	eLogLevel mVerbosity;		// current logging verbosity level
	std::string mTimestamp;		// current local time
	bool mActive;				// state of logging inFormation
	
	// returns true if verbosity setting is within current range
	bool IsInVerbosityRange(eLogLevel verbosity);

	// returns string of the verbosity level
	std::string GetVerbosityName();

	// returns token of the verbosity level
	std::string GetVerbosityToken(eLogLevel verbosity);
	
	std::string GetTimeStamp();	// returns string of the current local time

    cLogMgr();                             // Constructor
    cLogMgr(const cLogMgr &){}             // Copy constructor
    cLogMgr &operator=(const cLogMgr &){}  // Assigment operator
    ~cLogMgr();                            // Destructor

  public:
    static cLogMgr *GetInstance();   // returns instance of singleton class

    void ViewLog();                  // opens notepad with loggin inFormation
    unsigned int Verbosity() const;  // returns the verbosity level

	// writing methods
	void WriteToFile(eLogLevel verbosity, std::string entry);
	void WriteToConsole(eLogLevel verbosity, std::string entry);
	void Write(eLogLevel verbosity, std::string entry);

	// clear standard output screen
	void ClearScreen();
};

#endif