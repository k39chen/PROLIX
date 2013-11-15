//====================================================================================
// @Title:      PLAYER PREFERENCE MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cPlayerPreferenceMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cPlayerPreferenceMgr.h"

//====================================================================================
//                                                                cPlayerPreferenceMgr
//====================================================================================
cPlayerPreferenceMgr *cPlayerPreferenceMgr::mInstance = NULL;

cPlayerPreferenceMgr::cPlayerPreferenceMgr()
{
}

cPlayerPreferenceMgr *cPlayerPreferenceMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cPlayerPreferenceMgr;
        return mInstance;
    }
    return mInstance;
}

cPlayerPreferenceMgr::~cPlayerPreferenceMgr()
{
}