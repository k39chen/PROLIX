//====================================================================================
// @Title:      LOCALIZATION MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cLocMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The localization table as maintained here consists of a localization token
//  that maps to its direct text. This way, we can desensitize the code development
//  process to that of the game designer process.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_LOCALIZATION_H__
#define __PROLIX_FRAMEWORK_LOCALIZATION_H__

#include <string>
#include <map>
#include <iostream>

// the loctable contains a dictionary of localized tokens and their respective text.
static std::map<std::string, std::string> LOCTABLE;

// singleton accessor
#define LocMgr cLocMgr::GetInstance()

//====================================================================================
//                                                                             cLocMgr
//====================================================================================
class cLocMgr
{
    friend extern std::string L(std::string token);

    static cLocMgr *mInstance;

    void BuildLocalizationTable();

    cLocMgr();                           // Constructor
    cLocMgr(const cLocMgr &){}           // Copy constructor
    cLocMgr &operator=(const cLocMgr &){}// Assignment operator
    ~cLocMgr();                          // Destructor
  public:
    void Print();                       // print out loc table
    static cLocMgr *GetInstance();      // get instance of singleton class
};

extern std::string L(std::string token);

#endif