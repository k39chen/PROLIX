//====================================================================================
// @Title:      GAME MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cGame.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The Game Manager integrates all of the managing game components (including
//  PROLIX) as a central hub of communication between all managers.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_H__
#define __PROLIX_FRAMEWORK_H__

#include "../../engine/include/PrlxEngine.h"
#include "../include/cAssetMgr.h"
#include "../include/cGameDataMgr.h"
#include "../include/cLocMgr.h"
#include "../include/cLogMgr.h"
#include "../include/cPlayerDataMgr.h"
#include "../include/cPlayerPreferenceMgr.h"
#include "../include/cTweenMgr.h"
#include "../../engine/include/PrlxEngine.h"

// singleton accessor
#define Game cGame::GetInstance()

//====================================================================================
//                                                                               cGame
//====================================================================================
class cGame
{
    typedef PrlxGraphics Graphics;

    static cGame *mInstance;    // instance of the singleton class

    void Initialize();  // Initialize application managers

    cGame();                        // Constructor
    cGame(const cGame &){}          // Copy constructor
    cGame &operator= (cGame &){}    // Assignment operator
    ~cGame();                       // Destructor

  public:
    static cGame *GetInstance();    // get instance of the singleton class
      
    bool Loop();    // the game loop
    void InitScene();   // start the rendering phase
    void ExitScene();   // end the rendering phase
};

#endif