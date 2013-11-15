//====================================================================================
// @Title:      RESOURCES
//------------------------------------------------------------------------------------
// @Location:   /prolix/resources/include/cResources.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cResources.h"

std::string GetResourceName(std::string path) 
{
	size_t location = path.rfind ("/");
	std::string aliased;

    return (location != std::string::npos)
        ? path.substr(location + 1, path.length())
        : path;
}