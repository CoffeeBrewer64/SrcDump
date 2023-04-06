/**
* @file trlEmuMenuDataScene.h
* @author zhfang
* @date 2011.07.02
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"

enum Button
{
	BUTTON_A = 1 << 0,
	BUTTON_B = 1 << 1,
	BUTTON_R = 1 << 2,
	BUTTON_L = 1 << 3,
	BUTTON_X = 1 << 4,
	BUTTON_Y = 1 << 5,
	BUTTON_SELECT = 1 << 6,
	BUTTON_START = 1 << 7,
	BUTTON_DEBUG = 1 << 8,
	KEY_UP = 1 << 9,
	KEY_DOWN = 1 << 10,
	KEY_LEFT = 1 << 11,
	KEY_RIGHT = 1 << 12,
	BUTTON_HOLD = 0x80000000,
	NONE = 0
};


extern trlEmuMenuScene cgbvcm_scene_firsttime_w00;
extern trlEmuMenuScene cgbvcm_scene_firsttime_w01;
extern trlEmuMenuScene cgbvcm_scene_firsttime_w02;
extern trlEmuMenuScene cgbvcm_scene_firsttime_w03;

extern trlEmuMenuScene cgbvcm_scene_main;
extern trlEmuMenuScene cgbvcm_scene_save;
extern trlEmuMenuScene cgbvcm_scene_saveing;
extern trlEmuMenuScene cgbvcm_scene_saveok;
extern trlEmuMenuScene cgbvcm_scene_load;
extern trlEmuMenuScene cgbvcm_scene_loading;
extern trlEmuMenuScene cgbvcm_scene_loadok;
extern trlEmuMenuScene cgbvcm_scene_reset;
extern trlEmuMenuScene cgbvcm_scene_reseting;
extern trlEmuMenuScene cgbvcm_scene_nmain;
extern trlEmuMenuScene cgbvcm_scene_nreset;
extern trlEmuMenuScene cgbvcm_scene_nreseting;

extern trlEmuMenuScene cgbvcm_scene_modechange_w00;
extern trlEmuMenuScene cgbvcm_scene_modechange_w01;
extern trlEmuMenuScene cgbvcm_scene_modechange_ntoa0;
extern trlEmuMenuScene cgbvcm_scene_modechange_ntoa1;
extern trlEmuMenuScene cgbvcm_scene_modechange_aton0;
extern trlEmuMenuScene cgbvcm_scene_modechange_aton1;

extern trlEmuMenuScene errvcm_scene_begin;
extern trlEmuMenuScene errvcm_scene_notformatwait;
extern trlEmuMenuScene errvcm_scene_badformatok;
extern trlEmuMenuScene errvcm_scene_badformatdone;
extern trlEmuMenuScene errvcm_scene_vfailedok;
extern trlEmuMenuScene errvcm_scene_vfaileddone;
extern trlEmuMenuScene errvcm_scene_opdeniedwait;
extern trlEmuMenuScene errvcm_scene_end;

extern trlEmuMenuScene cgbvcm_scene_dlppre;
extern trlEmuMenuScene cgbvcm_scene_dlpbegin;
extern trlEmuMenuScene cgbvcm_scene_dlpbeginback;
extern trlEmuMenuScene cgbvcm_scene_dlpconn;
extern trlEmuMenuScene cgbvcm_scene_dlpconnback;
extern trlEmuMenuScene cgbvcm_scene_dlpconnquit;
extern trlEmuMenuScene cgbvcm_scene_dlp;
extern trlEmuMenuScene cgbvcm_scene_dlpback;
extern trlEmuMenuScene cgbvcm_scene_dlpnetinit;
extern trlEmuMenuScene cgbvcm_scene_dlpnetinitback;
extern trlEmuMenuScene cgbvcm_scene_dlps;
extern trlEmuMenuScene cgbvcm_scene_dlpwait;
extern trlEmuMenuScene cgbvcm_scene_dlpwaitback;
extern trlEmuMenuScene cgbvcm_scene_dlpok;
extern trlEmuMenuScene cgbvcm_scene_dlpstandby;
extern trlEmuMenuScene cgbvcm_scene_dlpmain;
extern trlEmuMenuScene cgbvcm_scene_dlpnmain;
extern trlEmuMenuScene cgbvcm_scene_dlpchildstandby;
extern trlEmuMenuScene cgbvcm_scene_dlpchildmain;
extern trlEmuMenuScene cgbvcm_scene_dlpreset;
extern trlEmuMenuScene cgbvcm_scene_dlpend;
extern trlEmuMenuScene cgbvcm_scene_dlpends;
extern trlEmuMenuScene cgbvcm_scene_dlpendok;
extern trlEmuMenuScene cgbvcm_scene_dlpendwait;
extern trlEmuMenuScene cgbvcm_scene_dlpothermenu;
extern trlEmuMenuScene cgbvcm_scene_dlpchilderror;
extern trlEmuMenuScene cgbvcm_scene_dlpallleaveok;
extern trlEmuMenuScene cgbvcm_scene_dlphaveleaveok;
extern trlEmuMenuScene cgbvcm_scene_dlphaveleaveend;
extern trlEmuMenuScene cgbvcm_scene_dlperror;
extern trlEmuMenuScene cgbvcm_scene_dlperrorend;

extern trlEmuMenuScene cgbvcm_scene_netoppre;
extern trlEmuMenuScene cgbvcm_scene_netconnconfirm;

extern trlEmuMenuScene cgbvcm_scene_dlpdlperror;
extern trlEmuMenuScene cgbvcm_scene_dlperrorok;

