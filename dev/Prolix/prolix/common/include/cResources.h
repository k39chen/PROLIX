//====================================================================================
// @Title:      RESOURCES
//------------------------------------------------------------------------------------
// @Location:   /prolix/resources/include/cResources.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Resource stack comprised of media based resources such as textures, messages,
//  audio files, etc. Provides simple method for removing resources from the game
//  and convenient access to pre-rendered or pre-processed resources.
//
//====================================================================================
#ifndef __PROLIX_COMMON_RESOURCES_H__
#define __PROLIX_COMMON_RESOURCES_H__

#include <iostream>
#include <string>
#include <map>
#include "../include/xString.h"
#include "../../framework/include/cLogMgr.h"

std::string GetResourceName(std::string path);

//====================================================================================
//                                                                           cResource
//====================================================================================
template <class T>
struct cResource 
{
    // resource string identifier
	std::string id;

    // type of resource
	T Resource;

	// constructor
	cResource(std::string rId, T rResource) 
    {
		id = rId;
		Resource = rResource;
	}
};

//====================================================================================
//                                                                              cStack
//====================================================================================
template <class T> struct cStack 
{
	std::string name;				// resource string identifier
	std::string last;				// last resource ID added
	std::map<std::string, T> data;	// hash table of resources
	
	// return true if resource already exists in data hash table
	bool exists(std::string id) 
    {
		return (data.count(id) > 0);
	}

	// adds resource to data hash table given a resource
	void add(cResource<T> rsrc) 
    {
		if (exists(rsrc.id)) 
        {
			LogMgr->Write(FATAL, "cStack::add >>>> Resource '" + rsrc.id + "' already exists in " + name);
			return;
		}

		last = rsrc.id;
		data[rsrc.id] = rsrc.Resource;
		LogMgr->Write(DEBUG, "cStack::add >>>> Added '" + rsrc.id + "' to " + name);
	}

	// adds resource to data hash table given a string and mapping
	void add(std::string id, T resource) 
    {
		if (exists(id)) 
        {
			LogMgr->Write(FATAL, "cStack::add >>>> Resource '" + id + "' already exists in " + name);
			return;
		}

		last = id;
		data[id] = resource;
		LogMgr->Write(DEBUG, "cStack::add >>>> Added '" + id + "' to " + name);
	}

	// removes a resource from the data hash table
	void remove(std::string id) 
    {
		if (exists(id)) 
        {
			data.erase (id);
			LogMgr->Write(DEBUG, "cStack::remove >>>> Removed '" + id + "' from " + name);
		}
	}

	// removes last added resource from data has table
	void removeLast() 
    {
		if (exists(last)) 
        {
			data.erase (last);
			LogMgr->Write(DEBUG, "cStack::removeLast >>>> Removed '" + last + "' from " + name);
		}
	}

	// return the mapping associated with the given resource string ident
	T get(std::string id) 
    {
        if (!exists(id))
        {
            LogMgr->Write(FATAL, "cStack::get >>>> Could not get asset with id: '" + id + "'");
            return NULL;
        }
		return data[id];
	}

	// returns the last added resource
	T getLast() 
    {
		return data[last];
	}

	// prints out the data hash table
	void print() 
    {
		std::map<std::string, T>::iterator rsrc;
		for (rsrc = data.begin(); rsrc != data.end(); rsrc++) 
        {
			std::cout << rsrc->first << "\t\t" << rsrc->second << std::endl;
		}
	}

	// Constructor
	cStack(std::string rName = "stack") 
    {
		name = rName;
		last = "";
		LogMgr->Write(INFO, "cStack::cStack >>>> " + name + " initialized");
	}

	// Destructor
	~cStack() 
    {
		std::map<std::string, T>::iterator rsrc;
		for (rsrc = data.begin(); rsrc != data.end(); rsrc++) 
        {
			LogMgr->Write(DEBUG, "cStack::cStack >>>> Removed '" + rsrc->first + "' from " + name);
		}
		data.clear();
	}
};
	
#endif