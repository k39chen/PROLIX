//====================================================================================
// @Title:      PLAYER DATA MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cPlayerDataMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cPlayerDataMgr.h"

//====================================================================================
//                                                                      cPlayerDataMgr
//====================================================================================
cPlayerDataMgr *cPlayerDataMgr::mInstance = NULL;

cPlayerDataMgr::cPlayerDataMgr()
{
}

cPlayerDataMgr *cPlayerDataMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cPlayerDataMgr;
        return mInstance;
    }
    return mInstance;
}

cPlayerDataMgr::~cPlayerDataMgr()
{
}