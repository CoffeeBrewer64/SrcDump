/**
* @file trlEmuMenuDataFunc.h
* @author zhfang
* @date 2011.06.20
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"


///////////////////////////////////
//
void trlEmuMenuInitRes();

///////////////////////////////////
//scene
#define TRL_EMUMENU_SCENE_MOVEBUTTON_SUCCESS 0
#define TRL_EMUMENU_SCENE_MOVEBUTTON_FAIL	 1
s32 trlEmuMenuSceneMoveButton(trlEmuMenuScene *pScene, s32 newindex);

///////////////////////////////////
//state change

//go to change state, and select No. changeindex StateChange in current State
void trlEmuMenuStateToChange(s32 changeindex);
//go to normal state
void trlEmuMenuStateToNormal();
//change state
void trlEmuMenuChangeState(s32 newstate);

void trlEmuMenuStateInit();

