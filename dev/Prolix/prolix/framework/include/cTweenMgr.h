//====================================================================================
// @Title:      TWEEN MANAGER
//------------------------------------------------------------------------------------
// @Location:   /prolix/framework/include/cTweenMgr.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  The tween manager monitors the life cycle of new entry, active, and expired tweens.
//  All tweens created, are circumvented through to this manager which serves as a 
//  central hub of tween access and control. However, its design is to keep the user
//  as detatched from the appCore mechanism as possible.
//
//====================================================================================
#ifndef __PROLIX_FRAMEWORK_TWEEN_MANAGER_H__
#define __PROLIX_FRAMEWORK_TWEEN_MANAGER_H__

#include <iostream>
#include <vector>

class cBaseObject;
class cTween;
enum eObjectProperty;

// singleton accessor
#define TweenMgr cTweenMgr::GetInstance()

//====================================================================================
//                                                                           cTweenMgr
//====================================================================================
class cTweenMgr
{
    friend class cGame;
	friend class cTween;
	
    static cTweenMgr *mInstance;

    std::vector<cTween *> mRegisteredTweens;
    
    cTweenMgr();
    cTweenMgr(const cTweenMgr &){}
    cTweenMgr &operator=(const cTweenMgr &){}
    ~cTweenMgr();

    void Register(cTween *Tween);
	void Update();
  public:
      static cTweenMgr *GetInstance();

	  void Create(cTween *Tween);

	  bool RegisteredForProperty(cBaseObject *object, eObjectProperty propertyType);
      unsigned int GetNumRegistered();
};

#endif