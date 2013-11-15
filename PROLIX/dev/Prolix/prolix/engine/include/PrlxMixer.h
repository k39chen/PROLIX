//====================================================================================
// @Title:      PROLIX MIXER
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxMixer.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Mixer API for music and sound control. Accepts *.mp3 and *.wav file Formats.
//  Registers audio files in BGM and Sound stacks.
//
//====================================================================================
#ifndef __PROLIX_ENGINE_MIXER_H__
#define __PROLIX_ENGINE_MIXER_H__

#include <SDL_mixer.h>
#include "../../common/include/cResources.h"

//====================================================================================
//                                                                          PrlxMixer
//====================================================================================
class PrlxMixer 
{
    friend class cAssetMgr;
    
    Mix_Music *LoadBGM(std::string path);	// load mp3 file
	Mix_Chunk *LoadSFX(std::string path);	// load wav file
	void FreeBGM(std::string track);	    // remove mp3 file from stack
	void FreeSFX(std::string track);	    // remove sound file from stack

  public:
    void PlayBGM(std::string track);	    // play mp3 file
	void PlaySFX(std::string track);	    // play wav file
	void PauseBGM(std::string track);	    // pause mp3 file
	void ResumeBGM(std::string track);	    // resume mp3 file
	void StopBGM(std::string track);	    // stop bgm

	// Constructor
	PrlxMixer();
	
	// Destructor
	~PrlxMixer();
};


#endif