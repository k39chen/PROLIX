//====================================================================================
// @Title:      PLAYER PREFERENCE MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cPlayerPreferenceMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  This class records the player preferences and makes computational decisions based
//  on the parameters provided.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_PREFERENCES_H__
#define __PROLIX_FRAMEWORK_PREFERENCES_H__

#include <string>
#include <map>

// singleton accessor
#define PlayerPreferenceMgr cPlayerPreferenceMgr::GetInstance()

//====================================================================================
//                                                                cPlayerPreferenceMgr
//====================================================================================
class cPlayerPreferenceMgr
{
    static cPlayerPreferenceMgr *mInstance;  // instance of singleton class

    cPlayerPreferenceMgr();                                             // Constructor
    cPlayerPreferenceMgr(const cPlayerPreferenceMgr &){}                // Copy constructor
    cPlayerPreferenceMgr &operator=(const cPlayerPreferenceMgr &){}     // Assigment operator
    ~cPlayerPreferenceMgr();                                            // Destructor
  public:
    // returns instance of singleton class
    static cPlayerPreferenceMgr *GetInstance();
};

#endif