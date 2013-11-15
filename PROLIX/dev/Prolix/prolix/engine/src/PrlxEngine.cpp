//====================================================================================
// @Title:      PROLIX ENGINE
//------------------------------------------------------------------------------------
// @Location:   /prolix/engine/PrlxEngine.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <iostream>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "../include/PrlxEngine.h"
#include "../../framework/include/cGame.h"

//====================================================================================
//                                                                          PrlxEngine
//====================================================================================
PrlxEngine *PrlxEngine::mInstance = NULL;

PrlxEngine::PrlxEngine() 
{
    // initialize PROLIX components
	Graphics	= new PrlxGraphics();
	Input		= new PrlxInput();
	Text		= new PrlxText();
	Physics		= new PrlxPhysics();
	Mixer		= new PrlxMixer();

    LogMgr->Write(INFO, "PrlxEngine::PrlxEngine >>>> PROLIX Engine components initalized successfully");

	mScreen = NULL;
	mWindowed = true;
	mTimer.Start();
	mExit = false;
    mFirstIter = true;

	// hook onto key state
	Input->KeyState = SDL_GetKeyState(NULL);

	// hook onto mouse state
	Input->MouseState = SDL_GetMouseState (NULL, NULL);

	if (!Initialize()) 
    {
        LogMgr->Write(FATAL, "PrlxEngine::PrlxEngine >>>> Failed to initialize SDL and OpenGL");
    }
}

PrlxEngine *PrlxEngine::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new PrlxEngine;
        return mInstance;
    }
    return mInstance;
}

bool PrlxEngine::Initialize() 
{
    // validate SDL initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
    {
		LogMgr->Write(FATAL, "PrlxEngine::Initialize >>>> Could not initialize application");
		return false;
	}

    // Configure environment for OpenGL
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,		1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,			8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,			8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,			8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,			8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,			16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,		    32);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,		8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,	    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    // set video mode for screen configuration
	if ((mScreen = SDL_SetVideoMode 
        (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 
         WINDOWED | SDL_HWSURFACE | SDL_OPENGL)) == NULL)
	{
		LogMgr->Write(FATAL, "PrlxEngine::Initialize >>>> Could not initialize OpenGL color surface");
		return false;
	}

    // prepare matrix for OpenGL(PRLX) Textures
	glClearColor	(0, 0, 0, 0);
	glClearDepth	(1.0f);
	glViewport		(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glShadeModel	(GL_SMOOTH);
	glMatrixMode	(GL_PROJECTION);
    glPushMatrix();
	glLoadIdentity	();

	glDisable		(GL_DEPTH_TEST);
	glEnable		(GL_BLEND);
	glBlendFunc		(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glOrtho			(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
	glMatrixMode	(GL_MODELVIEW);
	glEnable		(GL_TEXTURE_2D);
	glLoadIdentity	();

    GLint iViewport[4];

	// Get a copy of the viewport
	glGetIntegerv(GL_VIEWPORT, iViewport);

    // Set up the orthographic projection
	glOrtho( iViewport[0], iViewport[0] + iViewport[2], iViewport[1] + iViewport[3], iViewport[1], -1, 1 );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	
	return true;
}

void PrlxEngine::SetCaptionAndIcon(std::string caption, std::string iconPath)
{
    // set the window caption and icon image
	SDL_WM_SetCaption(caption.c_str(), iconPath.c_str());

	Uint32 colorkey;
	SDL_Surface *image;
	image = IMG_Load(iconPath.c_str());

	if (image == NULL)
    {
        LogMgr->Write(FATAL, "PrlxEngine::SetCaptionAndIcon >>>> Could not find file '" + iconPath + "'. Skipping");
    }
	
    // configure color keying for icon image
    SDL_DisplayFormatAlpha(image);
	colorkey = SDL_MapRGB(image->format, 255, 0, 255);
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);

	SDL_WM_SetIcon(image,NULL);
}

bool PrlxEngine::Loop() 
{
    if (!mFirstIter)
    {
        // mark end of drawing scene
        cGame::GetInstance()->ExitScene();
    }

    if (mFirstIter) mFirstIter = false;

    // start the fps timer
    RegulateFps();

    // initialize drawing scene
    cGame::GetInstance()->InitScene();

    // update the engine elements
    Update();

    // indicate application activity state
	return !mExit;
}

bool PrlxEngine::Update() 
{
    // poll for keyboard/mouse input
    Input->GetInput();
	
    // only update mouse if it exists
    if (Input->Mouse->Cursor != NULL)
    {
        Input->Mouse->Cursor->Move();
    }

    // global keyboard commands
    HandleInput();
	
    // hook onto key state
    Input->KeyState = SDL_GetKeyState(NULL);

    // hook onto mouse state
    Input->MouseState = SDL_GetMouseState(NULL, NULL);

    // flip screen
    if (SDL_Flip(mScreen) == -1) 
    {
	    LogMgr->Write(FATAL, "PrlxEngine::Update >>>> Could not flip screen");
	    return false;
    }

    // sleep for required time
    if (mFps.GetTicks() < 1000/FRAMES_PER_SECOND)
    {
	    SDL_Delay (1000/FRAMES_PER_SECOND - mFps.GetTicks());
    }

	// indication of successful update
	return true;
}

void PrlxEngine::RegulateFps()
{
    mFps.Start();
}

void PrlxEngine::HandleInput() 
{
	if (Input->KeyState[SDLK_ESCAPE])		CloseApplication();
	//if (Input->KeyState[SDLK_SPACE])		ToggleWindow();
	//if (Input->KeyState[SDLK_RETURN])	Logger->ViewLog();
	//if (Input->KeyState[SDLK_BACKSPACE])	Logger->ClearScreen();
}

void PrlxEngine::ToggleWindow() 
{
	if (mWindowed) {} // make full screen
	else {} // make windowed
}

void PrlxEngine::CloseApplication() 
{
	mExit = true;
}

void PrlxEngine::Shutdown() 
{
    // clean opengl matrices
    glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

    // clean up PROLIX components
	LogMgr->Write(INFO, "PrlxEngine::Shutdown >>>> Exiting application");
	delete Graphics;
	delete Input;
	delete Text;
	delete Physics;
	delete Mixer;

	//if (Logger->verbosity == DEBUG) Logger->viewLog ();
	
	SDL_Quit();
}

PrlxEngine::~PrlxEngine()
{
	Shutdown();
    LogMgr->Write(INFO, "PrlxEngine::~PrlxEngine >>>> Application terminated");
}