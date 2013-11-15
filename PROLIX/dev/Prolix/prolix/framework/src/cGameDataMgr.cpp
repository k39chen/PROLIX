//====================================================================================
// @Title:      DATA MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cGameDataMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cGameDataMgr.h"
#include "../include/cLogMgr.h"
#include <iostream>
#include <fstream>

//====================================================================================
//                                                                        cGameDataMgr
//====================================================================================
cGameDataMgr *cGameDataMgr::mInstance = NULL;

cGameDataMgr::cGameDataMgr()
{
    LogMgr->Write(INFO, "cGameDataMgr::cGameDataMgr >>>> Initialized Game Data Manager");

    // start with a clean database
    DataModules.clear();
}

cGameDataMgr *cGameDataMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cGameDataMgr;
        return mInstance;
    }
    return mInstance;
}

void cGameDataMgr::ParseDelimitedFile(std::vector<String> srclines, char delim)
{
    cDataModule *DataModule = new cDataModule();
}

void cGameDataMgr::ParseXML(std::vector<String> srclines)
{
    cDataModule *DataModule = new cDataModule();

    // iterate through all the lines
    for (unsigned int i=0; i<srclines.size(); i++)
    {
        // ignore comments
        if (srclines[i].exists("<!--"))
        {
            // lookahead to see when the comment ends
            unsigned int j;
            for (j=i; j<srclines.size(); j++)
            {
                if (srclines[j].exists("-->"))
                {
                    break;
                }
            }
            // found the end so set current line to it
            // and continue with the parsing
            i = j;
            continue;
        }

        std::cout << srclines[i] << std::endl;
    }
}

void cGameDataMgr::ParseDataFile(std::vector<String> srclines)
{
    cDataModule *DataModule = new cDataModule();
}

void cGameDataMgr::ParseIniFile(std::vector<String> srclines)
{
    cDataModule *DataModule = new cDataModule();
}

std::vector<String> cGameDataMgr::ExtractLines(std::string dataFilepath)
{
    // vector to return
    std::vector<String> srclines(0);

    // reader properties
    std::ifstream reader(dataFilepath.c_str());

    std::string _line;
    String line;

    // read data in from file
    while (getline(reader, _line))
    {
        if (reader.fail()) break;
        line = String(_line);

        line = line.format();
        
        if (String(line) == String("")) continue;
        srclines.push_back(line);
    }

    // return vector
    return srclines;
}

void cGameDataMgr::CreateDataModule(std::string dataFilepath)
{
    String path = String(dataFilepath);

    std::vector<String> srclines = ExtractLines(dataFilepath);

    if (path.exists(".xml"))
    {
        LogMgr->Write(VERBOSE, "cGameDataMgr::CreateDataModule >>>> Processing XML Data File: '" + dataFilepath + "'");
        ParseXML(srclines);
    }
    else if (path.exists(".csv"))
    {
        LogMgr->Write(VERBOSE, "cGameDataMgr::CreateDataModule >>>> Processing CSV Data File: '" + dataFilepath + "'");
        ParseDelimitedFile(srclines, ',');
    }
    else if (path.exists(".tsv"))
    {
        LogMgr->Write(VERBOSE, "cGameDataMgr::CreateDataModule >>>> Processing TSV Data File: '" + dataFilepath + "'");
        ParseDelimitedFile(srclines, '\t');
    }
    else if (path.exists(".dat"))
    {
        LogMgr->Write(VERBOSE, "cGameDataMgr::CreateDataModule >>>> Processing DAT Data File: '" + dataFilepath + "'");
        ParseDataFile(srclines);
    }
    else if (path.exists(".ini"))
    {
        LogMgr->Write(VERBOSE, "cGameDataMgr::CreateDataModule >>>> Processing INI Data File: '" + dataFilepath + "'");
        ParseIniFile(srclines);
    }
    else
    {
        LogMgr->Write(VERBOSE, "cGameDataMgr::CreateDataModule >>>> Could not determine data file type for: '" + dataFilepath + "'");
    }
}

cDataModule *cGameDataMgr::GetDataModule(std::string key)
{
    return DataModules[key];
}

cGameDataMgr::~cGameDataMgr()
{
}

//====================================================================================
//                                                                         cDataModule
//====================================================================================
cDataModule::cDataModule()
{
}

cDataModule::~cDataModule()
{
}