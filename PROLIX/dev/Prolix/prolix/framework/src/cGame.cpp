//====================================================================================
// @Title:      GAME MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cGame.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include <cstdlib>
#include <ctime>
#include "../include/cGame.h"
#include "../include/cTweenMgr.h"
#include "../../engine/include/PrlxEngine.h"

//====================================================================================
//                                                                               cGame
//====================================================================================
cGame *cGame::mInstance = NULL;

cGame::cGame()
{
    Initialize();
}

cGame *cGame::GetInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new cGame();
        return mInstance;
    }
    return mInstance;
}

void cGame::Initialize()
{
	srand((unsigned int)(time(NULL)));

    BuildResourceTable();
}

bool cGame::Loop()
{
    return Engine->Loop();
}

void cGame::InitScene()
{
    Engine->Graphics->Enable2D();
}

void cGame::ExitScene()
{
    cTweenMgr::GetInstance()->Update();

    // only draw mouse if it exists
    if (Engine->Input->Mouse->Cursor != NULL)
    {
        Engine->Input->Mouse->Cursor->Draw();
    }
    Engine->Graphics->Disable2D();
}

cGame::~cGame()
{
}