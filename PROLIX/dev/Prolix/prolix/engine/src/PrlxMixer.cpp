//====================================================================================
// @Title:      PROLIX MIXER
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxMixer.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/PrlxEngine.h"
#include "../include/PrlxMixer.h"
#include "../../framework/include/cAssetMgr.h"

//====================================================================================
//                                                                          PrlxMixer
//====================================================================================
PrlxMixer::PrlxMixer() 
{
	LogMgr->Write(INFO, "PrlxMixer::PrlxMixer >>>> PROLIX Mixer Engine initialized");
	
    // 22050
	if (Mix_OpenAudio(49000, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1) 
    {
		LogMgr->Write(INFO, "PrlxMixer::PrlxMixer >>>> PROLIX Mixer Engine could not be initalized");
	}
}

Mix_Music *PrlxMixer::LoadBGM(std::string track) 
{
	Mix_Music *trk = NULL;
	trk = Mix_LoadMUS(track.c_str());

	if (trk == NULL) 
    {
		LogMgr->Write(FATAL, "PrlxMixer::LoadBGM >>>> Could not open '" + track + "' BGM file.");
		return trk;
	}

    AssetMgr->AddUrl(track);
    AssetMgr->mMusic->add(cResource<Mix_Music *> (GetResourceName(track), trk));

	return trk;
}

Mix_Chunk *PrlxMixer::LoadSFX(std::string track) 
{
	Mix_Chunk *trk = NULL;
	trk = Mix_LoadWAV(track.c_str());

	if (trk == NULL) 
    {
		LogMgr->Write(FATAL, "PrlxMixer::LoadSFX >>>> Could not open '" + track + "' SFX file.");
		return trk;
	}
	
    AssetMgr->AddUrl(track);
	AssetMgr->mSound->add(cResource<Mix_Chunk *> (GetResourceName(track), trk));

	return trk;
}

void PrlxMixer::PlayBGM(std::string track) 
{
    if (!AssetMgr->Exists<Music>(track)) 
    {
		LogMgr->Write(INFO, "PrlxMixer::PlayBGM >>>> Track '" + track + "' could not be found");
		return;
	}
	
    if (Mix_PlayMusic (AssetMgr->Load<Music>(track), -1) == -1) 
    {
		LogMgr->Write(FATAL, "PrlxMixer::PlayBGM >>>> Could not play '" + track + "'");
	}
    else
    {
		LogMgr->Write(VERBOSE, "PrlxMixer::PlayBGM >>>> Start playing '" + track + "'");
	}
}

void PrlxMixer::PlaySFX(std::string track) 
{
	if (!AssetMgr->Exists<Sound>(track)) 
    {
		LogMgr->Write(FATAL, "PrlxMixer::PlaySFX >>>> Track '" + track + "' could not be found");
		return;
	}
	
    if (Mix_PlayChannel (-1, AssetMgr->Load<Sound>(track), 0) == -1) 
    {
		LogMgr->Write(FATAL, "PrlxMixer::PlaySFX >>>> Could not play '" + track + "'");
	}
    else
    {
		LogMgr->Write(VERBOSE, "PrlxMixer::PlaySFX >>>> Start playing '" + track + "'");
	}
}

void PrlxMixer::PauseBGM(std::string track) 
{
	Mix_PauseMusic();
}

void PrlxMixer::ResumeBGM(std::string track) 
{
	Mix_ResumeMusic();
}

void PrlxMixer::StopBGM(std::string track) 
{
	Mix_HaltMusic();
}

void PrlxMixer::FreeBGM(std::string track) 
{
    AssetMgr->mMusic->remove(track);
}

void PrlxMixer::FreeSFX(std::string track) 
{
    AssetMgr->mSound->remove(track);
}

PrlxMixer::~PrlxMixer() 
{
    Mix_CloseAudio();
	Mix_Quit();

    LogMgr->Write(INFO, "PrlxMixer::~PrlxMixer >>>> Cleaning up PROLIX Mixer");
}