//====================================================================================
// @Title:      LOCALIZATION MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cLocMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cLocMgr.h"

//====================================================================================
//                                                                LOCALIZATION_MANAGER
//====================================================================================
cLocMgr *cLocMgr::mInstance = NULL;

cLocMgr::cLocMgr()
{
    // initalize localization table
    BuildLocalizationTable();
}

void cLocMgr::BuildLocalizationTable()
{
    // ...
}

void cLocMgr::Print()
{
    for (std::map<std::string,std::string>::iterator i=LOCTABLE.begin(); i!=LOCTABLE.end(); i++)
    {
        std::cout << i->first << "\t\t" << i->second << std::endl;
    }
}

cLocMgr *cLocMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cLocMgr();
        return mInstance;
    }
    return mInstance;
}

std::string L(std::string token)
{
    return (LOCTABLE.count(token) != 0)
        ? LOCTABLE[token]
        : "#" + token + "#";
}