//====================================================================================
// @Title:      DATA MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cGameDataMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The game data manager handles all information read in from an external data file
//  and makes it available for the client. The type of information that resides here
//  are game specific elements such as elements for the RPG component.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_DATA_H__
#define __PROLIX_FRAMEWORK_DATA_H__

#include <string>
#include <map>
#include <vector>
#include "../include/cGame.h"
#include "../../common/include/xString.h"

//====================================================================================
//                 **** GAME DATA MANGAER CONSTANTS AND SETTINGS ****
//====================================================================================
// determines how to parse the data file
enum eDataType
{
    XML,
    CSV,
    TSV
};

// forward reference
class cDataModule;

// singleton accessor
#define GameDataMgr cGameDataMgr::GetInstance()

//====================================================================================
//                                                                        cGameDataMgr
//====================================================================================
class cGameDataMgr
{
    std::map<std::string, cDataModule *> DataModules;

    static cGameDataMgr *mInstance; // singleton instance

    // parses a data file and creates a data module from it
    void ParseXML(std::vector<String> srclines);
    void ParseDelimitedFile(std::vector<String> srclines, char delim);
    void ParseDataFile(std::vector<String> srclines);
    void ParseIniFile(std::vector<String> srclines);

    // split the file into lines and store each line in an array
    std::vector<String> ExtractLines(std::string dataFilepath);

    cGameDataMgr();                                  // Constructor
    cGameDataMgr(const cGameDataMgr &){}             // Copy constructor
    cGameDataMgr &operator=(const cGameDataMgr &){}  // Assignment operator
    ~cGameDataMgr();                                 // Destructor
  public:
    // returns instance of singleton class
    static cGameDataMgr *GetInstance();

    // data module life cycle handlers
    void CreateDataModule(std::string dataFilepath);    // creates a data module given a data file
    cDataModule *GetDataModule(std::string key);        // fetches a data module from the database
};

//====================================================================================
//                                                                         cDataModule
//====================================================================================
// what is a data module?

// Hierarchy:
// fields
// values
// records

// for now, a data module is a bunch of lines
class cDataModule
{
    std::map<std::string, std::map<std::string, std::string> > data;

  public:
    // Constructor
    cDataModule();

    // Destructor
    ~cDataModule();
};

#endif