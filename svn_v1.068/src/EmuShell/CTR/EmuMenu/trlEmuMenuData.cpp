/**
* @file trlEmuMenuData.cpp
* @author zhfang
* @date 2011.06.29
* @brief trlEmuMenu
*/
#include "trlEmuMenuData.h"
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataLayout.h"
#include "trlEmuMenuDataButton.h"
#include "trlEmuMenuDataScene.h"
#include "trlEmuMenuDataState.h"

s32 g_vcmstate_thread_state;
s32 g_vcmstatechange_state;
s32 g_vcmstate_state  = eVCMState_Normal;
s32 g_vcmstate_go = VCM_STATE_NO_FORCE_GO;
s32 g_vcmstate = eEmuMenuState_Init;
s32 g_vcmstate_changeindex = VCM_STATE_CHANGE_NOCHANGE; //no change
s32 g_vcmchange_actionstep;

s32 g_vcm_specialplayer = -1;

trlEmuMenuState* vcmmenu_state[] =
{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
	&cgbvcmstate_init,
	&cgbvcmstate_standby,
	&cgbvcmstate_standbyselect,
	&cgbvcmstate_main,
	&cgbvcmstate_save,
	&cgbvcmstate_saveing,
	&cgbvcmstate_saveok,
	&cgbvcmstate_load,
	&cgbvcmstate_loading,
	&cgbvcmstate_loadok,
	&cgbvcmstate_reset,
	&cgbvcmstate_reseting,
	&cgbvcmstate_nmainpre,
	&cgbvcmstate_nmain,
	&cgbvcmstate_nreset,
	&cgbvcmstate_nreseting,
	&cgbvcmstate_modechangew00,
	&cgbvcmstate_modechangew01,
	&cgbvcmstate_modechangentoa0,
	&cgbvcmstate_modechangentoa1,
	&cgbvcmstate_modechangeaton0,
	&cgbvcmstate_firsttime_w00,
	&cgbvcmstate_firsttime_w01,
	&cgbvcmstate_firsttime_w02,
	&cgbvcmstate_firsttime_w03,
	&errvcmstate_begin,
	&errvcmstate_notformatwait,
	&errvcmstate_badformatok,
	&errvcmstate_badformatwait,
	&errvcmstate_badformatdone,
	&errvcmstate_vfailedok,
	&errvcmstate_vfailedwait,
	&errvcmstate_vfaileddone,
	&errvcmstate_opdeniedwait,
	&errvcmstate_end,
	&cgbvcmstate_backtomain,
	&cgbvcmstate_netoppre,
	&cgbvcmstate_netconnconfirm,
	&cgbvcmstate_netinit,
	&cgbvcmstate_dlpdlperror,
	&cgbvcmstate_dlpbegin,
	&cgbvcmstate_dlpbeginback,
	&cgbvcmstate_dlpconn,
	&cgbvcmstate_dlpconnback,
	&cgbvcmstate_dlp,
	&cgbvcmstate_dlpback,
	&cgbvcmstate_dlpnetinit,
	&cgbvcmstate_dlpnetinitback,
	&cgbvcmstate_dlps,
	&cgbvcmstate_dlpwait,
	&cgbvcmstate_dlpwaitback,
	&cgbvcmstate_dlpok,	
	&cgbvcmstate_dlpchildstandby,
	&cgbvcmstate_dlpchildmain,
	&cgbvcmstate_dlpchildothermenu,
	&cgbvcmstate_dlpchildend,
	&cgbvcmstate_dlpchildendwait,
	&cgbvcmstate_dlpchilderrors,
	&cgbvcmstate_dlpchilderror,
	&cgbvcmstate_dlpstandby,
	&cgbvcmstate_dlpmain,
	&cgbvcmstate_dlpnmain,
	&cgbvcmstate_dlpreset,
	&cgbvcmstate_dlpend,
	&cgbvcmstate_dlpnend,
	&cgbvcmstate_dlpends,	
	&cgbvcmstate_dlpendok,
	&cgbvcmstate_dlpendwait,
	&cgbvcmstate_dlpothermenu,
	&cgbvcmstate_dlperror,
	&cgbvcmstate_dlphaveleaveok,
	&cgbvcmstate_dlperrorok,
	&cgbvcmstate_dlphaveerrorok,
	&cgbvcmstate_dlpallleaveok,
	&cgbvcmstate_dlperrorend
};


s32 g_vcmstate_netmode = eVCMStateNetMode_None;
