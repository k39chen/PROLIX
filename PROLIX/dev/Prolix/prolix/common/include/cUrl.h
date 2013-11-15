//====================================================================================
// @Title:      URL
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/cUrl.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Stores a relative file path and aliased file path for simple storing and reference.
//
//====================================================================================
#ifndef __PROLIX_COMMON_FILEPATH_H__
#define __PROLIX_COMMON_FILEPATH_H__

#include <string>

// alias cUrlId type
typedef std::string cUrlId;

//====================================================================================
//                                                                                cUrl
//====================================================================================
struct cUrl
{
    cUrlId alias; // alias of the filepath
    std::string path;    // relative path of the file

    // Constructor
    cUrl(std::string path);
};

#endif