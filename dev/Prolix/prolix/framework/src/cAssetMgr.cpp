//====================================================================================
// @Title:      ASSET MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cAssetMgr.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/cAssetMgr.h"

//====================================================================================
//                                                                           cAssetMgr
//====================================================================================
cAssetMgr *cAssetMgr::mInstance = NULL;

cAssetMgr::cAssetMgr()
{
    // initalize asset stacks
    mUrl    = new cStack<cUrlId>("Asset Aliasing Stack");
    mTexture     = new cStack<Texture>("Texture Stack");
    mFont        = new cStack<Font>("Font Stack");
    mMusic       = new cStack<Music>("BGM Stack");
    mSound       = new cStack<Sound>("SFX Stack");
}

cAssetMgr *cAssetMgr::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cAssetMgr();
        return mInstance;
    }
    return mInstance;
}

cUrlId cAssetMgr::GetUrl(std::string key)
{
    if (!mUrl->data.count(key))
    {
        LogMgr->Write(WARNING, "cAssetMgr::GetUrl >>>> No file with key '" + key + "' has been processed.");
        return "NULL";
    }
    return mUrl->get(key);
}

void cAssetMgr::AddUrl(std::string path)
{
    if (mUrl->exists(GetResourceName(path)))
    {
        LogMgr->Write(VERBOSE, "cAssetMgr::AddUrl >>>> Duplicate: File path '" + path + "' already registered and aliased to '" + GetResourceName(path) + "'");
        return;
    }

    LogMgr->Write(VERBOSE, "cAssetMgr::AddUrl >>>> File path '" + path + "' registered and aliased to '" + GetResourceName(path) + "'");

    mUrl->add(GetResourceName(path), path);
}

template<> Texture cAssetMgr::Create<Texture>(std::string url, int data) {Engine->Graphics->Create(url);    return mTexture->get(GetResourceName(url));}
template<> Font cAssetMgr::Create<Font>(std::string url, int data)       {Engine->Text->AddFont(url, data); return mFont->get(GetResourceName(url));}
template<> Music cAssetMgr::Create<Music>(std::string url, int data)     {Engine->Mixer->LoadBGM(url);      return mMusic->get(GetResourceName(url));}
template<> Sound cAssetMgr::Create<Sound>(std::string url, int data)     {Engine->Mixer->LoadSFX(url);      return mSound->get(GetResourceName(url));}

template<> bool cAssetMgr::Exists<Texture>(std::string key)  {return mTexture->exists(key);}
template<> bool cAssetMgr::Exists<Font>(std::string key)     {return mFont->exists(key);}
template<> bool cAssetMgr::Exists<Music>(std::string key)    {return mMusic->exists(key);}
template<> bool cAssetMgr::Exists<Sound>(std::string key)    {return mSound->exists(key);}

template<> Texture cAssetMgr::Load<Texture>(std::string key) {return (Texture)mTexture->get(key);}
template<> Font cAssetMgr::Load<Font>(std::string key)       {return (Font)mFont->get(key);}
template<> Music cAssetMgr::Load<Music>(std::string key)     {return (Music)mMusic->get(key);}
template<> Sound cAssetMgr::Load<Sound>(std::string key)     {return (Sound)mSound->get(key);}

template<> void cAssetMgr::Remove<Texture>(std::string key)  {Engine->Graphics->Free(key);}
template<> void cAssetMgr::Remove<Font>(std::string key)     {mFont->remove(key);}
template<> void cAssetMgr::Remove<Music>(std::string key)    {Engine->Mixer->FreeBGM(key);}
template<> void cAssetMgr::Remove<Sound>(std::string key)    {Engine->Mixer->FreeSFX(key);}

template<> void cAssetMgr::RemoveLast<Texture>() {mTexture->removeLast();}
template<> void cAssetMgr::RemoveLast<Font>()    {mFont->removeLast();}
template<> void cAssetMgr::RemoveLast<Music>()   {mMusic->removeLast();}
template<> void cAssetMgr::RemoveLast<Sound>()   {mSound->removeLast();}

template<> void cAssetMgr::Debug<Texture>() {mTexture->print();}
template<> void cAssetMgr::Debug<Font>()    {mFont->print();}
template<> void cAssetMgr::Debug<Music>()   {mMusic->print();}
template<> void cAssetMgr::Debug<Sound>()   {mSound->print();}

cAssetMgr::~cAssetMgr()
{
    delete mTexture;
    delete mFont;
    delete mMusic;
    delete mSound;
    delete mUrl;
    LogMgr->Write(INFO, "cAssetMgr::~cAssetMgr >>>> Deactivated Asset Manager");
}

//====================================================================================
//                                                                   Pre-loaded Assets
//====================================================================================
void BuildResourceTable()
{
	////////////
    // IMAGES
	AssetMgr->Create<Texture>   ("../assets/img/msn.png");

    ////////////
    // FONTS
    AssetMgr->Create<Font>      ("../assets/font/ninjapenguin.ttf");

    ////////////
    // MUSIC
    AssetMgr->Create<Music>     ("../assets/music/music.mp3");
    
    ////////////
    // SOUNDS
    AssetMgr->Create<Sound>     ("../assets/sound/sample.wav");
}