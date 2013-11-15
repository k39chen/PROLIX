//====================================================================================
// @Title:      PROLIX ENGINE
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/include/PrlxEngine.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The PROLIX Game Engine, created and developed by Visionary Games, is designed to
//  interface with SDL and OpenGL to create Cadabolg.
//
//====================================================================================
#ifndef __PROLIX_ENGINE_H__
#define __PROLIX_ENGINE_H__

#include <SDL.h>
#include "../include/PrlxInput.h"
#include "../include/PrlxGraphics.h"
#include "../include/PrlxText.h"
#include "../include/PrlxPhysics.h"
#include "../include/PrlxMixer.h"
#include "../../common/include/cTimer.h"

//====================================================================================
//                     **** ENGINE CONSTANTS AND SETTINGS ****
//====================================================================================
// [PROLIX RESOLUTION SETTINGS]
#define SCREEN_WIDTH		1024
#define SCREEN_HEIGHT		640
#define SCREEN_BPP			32

// [WINDOW STATE DEFINITIONS]
#define FULLSCREEN		SDL_HWPALETTE | SDL_DOUBLEBUF | SDL_FULLSCREEN
#define RESIZABLE		SDL_HWPALETTE | SDL_DOUBLEBUF | SDL_RESIZABLE
#define WINDOWED		SDL_HWPALETTE | SDL_DOUBLEBUF

// [FRAME RATE SETTINGS]
#define	FRAMES_PER_SECOND 120

// singleton accessor
#define Engine PrlxEngine::GetInstance()

//====================================================================================
//                                                                          PrlxEngine
//====================================================================================
class PrlxEngine 
{
    friend class cGame;

    static PrlxEngine *mInstance;  // instance of the singleton class

	// frame regulating variables
	cTimer mFps;
    cTimer mTimer;

	// engine state variables
	bool mExit;
	bool mWindowed;
    bool mFirstIter;
	SDL_Surface *mScreen;

    bool Initialize();  // intializes Engine and window properties/attributes
    void RegulateFps(); // regulates the frames per second
    bool Update();		// poll inputs, regulate frame rate and refresh window
    bool Loop();		// returns true if Engine is still in operation
	void HandleInput();	// poll inputs and executes actions
    
	PrlxEngine();                                  // Constructor
    PrlxEngine(const PrlxEngine &);               // Copy constructor
    PrlxEngine &operator=(const PrlxEngine &);    // Assignment operator
	~PrlxEngine();                                 // Destructor

  public:
    // Get instance of the singleton class
    static PrlxEngine *GetInstance();

    // PROLIX components
	PrlxGraphics *Graphics;	// Graphics manager
	PrlxInput *Input;			// Keyboard/Mouse handler
	PrlxText *Text;			// Font and text blit manager
	PrlxPhysics *Physics;		// Physics manager
	PrlxMixer *Mixer;			// Audio manager

    // set the caption and icon for the application
    void SetCaptionAndIcon(std::string caption, std::string iconPath);

    void ToggleWindow();		// toggles between windowed and fullscreen mode
	void CloseApplication();	// terminate application
	void Shutdown();			// safely close application and free resources
};

#endif