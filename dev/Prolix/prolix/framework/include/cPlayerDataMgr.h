//====================================================================================
// @Title:      PLAYER DATA MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cPlayerDataMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The player data manager manages all of the player-specific information and profile
//  properties. This may be used as a vehicle for storing save information.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_PLAYER_H__
#define __PROLIX_FRAMEWORK_PLAYER_H__

#include <string>
#include <map>

// singleton accessor
#define PlayerDataMgr cPlayerDataMgr::GetInstance()

//====================================================================================
//                                                                      cPlayerDataMgr
//====================================================================================
class cPlayerDataMgr
{
    static cPlayerDataMgr *mInstance;  // instance of singleton class

    cPlayerDataMgr();                                    // Constructor
    cPlayerDataMgr(const cPlayerDataMgr &){}             // Copy constructor
    cPlayerDataMgr &operator=(const cPlayerDataMgr &){}  // Assigment operator
    ~cPlayerDataMgr();                                   // Destructor
  public:
    // returns instance of singleton class
    static cPlayerDataMgr *GetInstance();
};

#endif