//====================================================================================
// @Title:      ASSET MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cAssetMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The asset manager is the central location for main game asset loading and
//  reference. Assets include images, sounds, and font files.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_ASSET_H__
#define __PROLIX_FRAMEWORK_ASSET_H__

#include <map>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "../include/cGame.h"
#include "../../common/include/cResources.h"
#include "../../common/include/cTexture.h"
#include "../../common/include/cUrl.h"

//====================================================================================
//                   **** ASSET MANAGER CONSTANTS AND SETTINGS ****
//====================================================================================
typedef cTexture* Texture;
typedef TTF_Font* Font;
typedef Mix_Music* Music;
typedef Mix_Chunk* Sound;

static std::map<std::string, std::string> RESOURCE_TABLE;

// singleton accessor
#define AssetMgr cAssetMgr::GetInstance()

//====================================================================================
//                                                                           cAssetMgr
//====================================================================================
class cAssetMgr
{
    // instance of the singleton class
    static cAssetMgr *mInstance;

    // friend classes for resource load functionality
    friend class PrlxGraphics;
    friend class PrlxMixer;
    friend class PrlxText;
    
    // list of filepath to alias mappings
    cStack<cUrlId> *mUrl;

    cStack<Texture> *mTexture;  // texture stack holding loaded images and rendered texts
    cStack<Font> *mFont;         // font stack holding loaded fonts
    cStack<Music> *mMusic;       // music stack holding .mp3 files
    cStack<Sound> *mSound;       // sound stack holding .wav files

    cAssetMgr();                                    // Constructor
    cAssetMgr(const cAssetMgr &){}              // Copy constructor
    cAssetMgr &operator=(const cAssetMgr &){}   // Assignment operator
    ~cAssetMgr();                                   // Destructor
    
  public:
    // get an instance of the singleton class
    static cAssetMgr *GetInstance();

    cUrlId GetUrl(std::string key);   // get original filepath
    void AddUrl(std::string path);             // add and alias a filepath
        
    template<typename T> T Create(std::string filepath, int data = 0);  // checks existence of asset
    template<typename T> bool Exists(std::string key);                  // checks existence of asset
    template<typename T> T Load(std::string key);                       // load the asset
    template<typename T> void Remove(std::string key);                  // remove asset from stack
    template<typename T> void RemoveLast();                             // remove last asset pushed onto stack
    template<typename T> void Debug();                                 // print the stack
};

//====================================================================================
//                                                                   Pre-loaded Assets
//====================================================================================
// TODO: Read paths in from external data file
void BuildResourceTable();

#endif