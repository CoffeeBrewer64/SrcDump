/**
* @file trlEmuMenuDataAnim.cpp
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#include "../../../trlMacro.h"
#include "../../trlEmuShellStruct.h"
#include "trlEmuMenuDataScene.h"
#include "trlEmuMenuDataAction.h"
#include "trlEmuMenuDataCallBack.h"
#include "trlEmuMenuDataState.h"
////////////////
//init
trlEmuMenuStateChange cgbvcm_statechange_init2standby =
{
	eEmuMenuState_Init,
	eEmuMenuState_StandBy,
	&cgbvcm_action_init
};

//////////////
//standby
trlEmuMenuStateChange cgbvcm_statechange_standby2standbyselect =
{
	eEmuMenuState_StandBy,
	eEmuMenuState_StandBySelect,
	NULL
};

trlEmuMenuStateChange cgbvcm_statechange_standbyselect2main =
{
	eEmuMenuState_StandBySelect,
	eEmuMenuState_Main,
	&cgbvcm_action_mainopen
};

trlEmuMenuStateChange cgbvcm_statechange_standbyselect2nmainpre =
{
	eEmuMenuState_StandBySelect,
	eEmuMenuState_NMainPre,
	&cgbvcm_action_nmainopen0
};

trlEmuMenuStateChange cgbvcm_statechange_standbyselect2dlps =
{
	eEmuMenuState_StandBySelect,
	eEmuMenuState_DLPS,
	NULL
};
trlEmuMenuStateChange cgbvcm_statechange_standbyselect2dlpmain =
{
	eEmuMenuState_StandBySelect,
	eEmuMenuState_DLPMain,
	&cgbvcm_action_dlpmain_open
};
//////////////
//firsttime
trlEmuMenuStateChange cgbvcm_statechange_nmainpre2firsttimew00 =
{
	eEmuMenuState_NMainPre,
	eEmuMenuState_FirstTime_W00,
	&cgbvcm_action_firsttime_w00_open
};

trlEmuMenuStateChange cgbvcm_statechange_firsttimew00_2_firsttimew01 =
{
	eEmuMenuState_FirstTime_W00,
	eEmuMenuState_FirstTime_W01,
	&cgbvcm_action_firsttime_w00_2_w01
};
trlEmuMenuStateChange cgbvcm_statechange_firsttimew00_2_firsttimew02 =
{
	eEmuMenuState_FirstTime_W00,
	eEmuMenuState_FirstTime_W02,
	&cgbvcm_action_firsttime_w00_2_w02
};

trlEmuMenuStateChange cgbvcm_statechange_firsttimew02_2_firsttimew03 =
{
	eEmuMenuState_FirstTime_W02,
	eEmuMenuState_FirstTime_W03,
	&cgbvcm_action_firsttime_w02_2_w03
};
trlEmuMenuStateChange cgbvcm_statechange_firsttimew02_2_firsttimew00 =
{
	eEmuMenuState_FirstTime_W02,
	eEmuMenuState_FirstTime_W00,
	&cgbvcm_action_firsttime_w02_2_w00
};

trlEmuMenuStateChange cgbvcm_statechange_firsttimew03_2_firsttimew02 =
{
	eEmuMenuState_FirstTime_W03,
	eEmuMenuState_FirstTime_W02,
	&cgbvcm_action_firsttime_w03_2_w02
};
trlEmuMenuStateChange cgbvcm_statechange_firsttimew03_2_firsttimew01 =
{
	eEmuMenuState_FirstTime_W03,
	eEmuMenuState_FirstTime_W01,
	&cgbvcm_action_firsttime_w03_2_w01
};

trlEmuMenuStateChange cgbvcm_statechange_firsttimew01_2_nmain =
{
	eEmuMenuState_FirstTime_W01,
	eEmuMenuState_NMain,
	&cgbvcm_action_firsttime_w01_2_nmain
};
trlEmuMenuStateChange cgbvcm_statechange_firsttimew01_2_modechangentoa0 =
{
	eEmuMenuState_FirstTime_W01,
	eEmuMenuState_ModeChange_NTOA0,
	&cgbvcm_action_firsttime_w01_2_modechangentoa0
};





//////////////
//main
trlEmuMenuStateChange cgbvcm_statechange_main2standby =
{
	eEmuMenuState_Main,
	eEmuMenuState_StandBy,
	&cgbvcm_action_mainclose
};

trlEmuMenuStateChange cgbvcm_statechange_mainclose2standby =
{
	eEmuMenuState_Main,
	eEmuMenuState_StandBy,
	&cgbvcm_action_mainclosex
};

trlEmuMenuStateChange cgbvcm_statechange_main2save =
{
	eEmuMenuState_Main,
	eEmuMenuState_Save,
	&cgbvcm_action_saveopen
};

trlEmuMenuStateChange cgbvcm_statechange_main2load =
{
	eEmuMenuState_Main,
	eEmuMenuState_Load,
	&cgbvcm_action_loadopen
};

trlEmuMenuStateChange cgbvcm_statechange_main2reset =
{
	eEmuMenuState_Main,
	eEmuMenuState_Reset,
	&cgbvcm_action_resetopen,
	2,
	{&cgbvcm_scene_main, &cgbvcm_scene_reset}
};

//////////////
//save
trlEmuMenuStateChange cgbvcm_statechange_save2main =
{
	eEmuMenuState_Save,
	eEmuMenuState_Main,
	&cgbvcm_action_saveback
};

trlEmuMenuStateChange cgbvcm_statechange_save2saveing =
{
	eEmuMenuState_Save,
	eEmuMenuState_Saveing,
	&cgbvcm_action_saveing
};

trlEmuMenuStateChange cgbvcm_statechange_saveing2saveok =
{
	eEmuMenuState_Saveing,
	eEmuMenuState_SaveOk,
	&cgbvcm_action_saveokopen
};

trlEmuMenuStateChange cgbvcm_statechange_saveok2main =
{
	eEmuMenuState_SaveOk,
	eEmuMenuState_Main,
	&cgbvcm_action_saveokclose
};
//////////////
//load
trlEmuMenuStateChange cgbvcm_statechange_load2main =
{
	eEmuMenuState_Load,
	eEmuMenuState_Main,
	&cgbvcm_action_loadback
};

trlEmuMenuStateChange cgbvcm_statechange_load2loading =
{
	eEmuMenuState_Load,
	eEmuMenuState_Loading,
	&cgbvcm_action_loading
};

trlEmuMenuStateChange cgbvcm_statechange_loading2loadok =
{
	eEmuMenuState_Loading,
	eEmuMenuState_LoadOk,
	&cgbvcm_action_loadokopen
};

trlEmuMenuStateChange cgbvcm_statechange_loadok2main =
{
	eEmuMenuState_LoadOk,
	eEmuMenuState_Main,
	&cgbvcm_action_loadokclose
};

//////////////
//reset
trlEmuMenuStateChange cgbvcm_statechange_reset2main =
{
	eEmuMenuState_Reset,
	eEmuMenuState_Main,
	&cgbvcm_action_resetback
};

trlEmuMenuStateChange cgbvcm_statechange_reset2reseting =
{
	eEmuMenuState_Reset,
	eEmuMenuState_Reseting,
	&cgbvcm_action_reseting
};

trlEmuMenuStateChange cgbvcm_statechange_reseting2standby =
{
	eEmuMenuState_Reseting,
	eEmuMenuState_StandBy,
	&cgbvcm_action_resetingclose
};


//////////////
//normal main
trlEmuMenuStateChange cgbvcm_statechange_nmainpre2nmain =
{
	eEmuMenuState_NMainPre,
	eEmuMenuState_NMain,
	&cgbvcm_action_nmainopen1
};



trlEmuMenuStateChange cgbvcm_statechange_nmain2standby =
{
	eEmuMenuState_NMain,
	eEmuMenuState_StandBy,
	&cgbvcm_action_nmainclose
};

trlEmuMenuStateChange cgbvcm_statechange_nmainclose2standby =
{
	eEmuMenuState_NMain,
	eEmuMenuState_StandBy,
	&cgbvcm_action_nmainclosex
};

trlEmuMenuStateChange cgbvcm_statechange_nmain2nreset =
{
	eEmuMenuState_NMain,
	eEmuMenuState_NReset,
	&cgbvcm_action_nresetopen
};

//////////////
//normal reset
trlEmuMenuStateChange cgbvcm_statechange_nreset2nmain =
{
	eEmuMenuState_NReset,
	eEmuMenuState_NMain,
	&cgbvcm_action_nresetback
};

trlEmuMenuStateChange cgbvcm_statechange_nreset2nreseting =
{
	eEmuMenuState_NReset,
	eEmuMenuState_NReseting,
	&cgbvcm_action_nreseting
};

trlEmuMenuStateChange cgbvcm_statechange_nreseting2standby =
{
	eEmuMenuState_NReseting,
	eEmuMenuState_StandBy,
	&cgbvcm_action_nresetingclose
};

//////////////
//mode change
trlEmuMenuStateChange cgbvcm_statechange_nmain2modechangew00 =
{
	eEmuMenuState_NMain,
	eEmuMenuState_ModeChange_W00,
	&cgbvcm_action_modechange_w00_open
};

trlEmuMenuStateChange cgbvcm_statechange_modechangew00_2_nmain =
{
	eEmuMenuState_ModeChange_W00,
	eEmuMenuState_NMain,
	&cgbvcm_action_modechange_w00_back
};

trlEmuMenuStateChange cgbvcm_statechange_modechangew00_2_modechangew01 =
{
	eEmuMenuState_ModeChange_W00,
	eEmuMenuState_ModeChange_W01,
	&cgbvcm_action_modechange_w01_open
};

trlEmuMenuStateChange cgbvcm_statechange_modechangew01_2_nmain =
{
	eEmuMenuState_ModeChange_W01,
	eEmuMenuState_NMain,
	&cgbvcm_action_modechange_w01_back
};

trlEmuMenuStateChange cgbvcm_statechange_modechangew01_2_modechangentoa0 =
{
	eEmuMenuState_ModeChange_W01,
	eEmuMenuState_ModeChange_NTOA0,
	&cgbvcm_action_modechange_w01_close
};

trlEmuMenuStateChange cgbvcm_statechange_modechangentoa0_2_ntoa1 =
{
	eEmuMenuState_ModeChange_NTOA0,
	eEmuMenuState_ModeChange_NTOA1,
	&cgbvcm_action_modechange_ntoa0
};

trlEmuMenuStateChange cgbvcm_statechange_modechangentoa1_2_main =
{
	eEmuMenuState_ModeChange_NTOA1,
	eEmuMenuState_Main,
	&cgbvcm_action_modechange_ntoa1
};

trlEmuMenuStateChange cgbvcm_statechange_main2modechangeaton0 =
{
	eEmuMenuState_Main,
	eEmuMenuState_ModeChange_ATON0,
	&cgbvcm_action_modechange_aton0
};

trlEmuMenuStateChange cgbvcm_statechange_modechangeaton0_2_nmain =
{
	eEmuMenuState_ModeChange_ATON0,
	eEmuMenuState_NMain,
	&cgbvcm_action_modechange_aton1
};

//////////////////////////
//error opdenied
trlEmuMenuStateChange errvcm_statechange_begin2opdeniedwait =
{
	eEmuMenuState_Error_Begin,
	eEmuMenuState_Error_OPDeniedWait,
	&errvcm_action_opdeniedwait_open
};


//////////////////////////
//error notformatwait
trlEmuMenuStateChange errvcm_statechange_begin2notformatwait =
{
	eEmuMenuState_Error_Begin,
	eEmuMenuState_Error_NotFormatWait,
	&errvcm_action_notformatwait_open
};


trlEmuMenuStateChange errvcm_statechange_notformatwait2end =
{
	eEmuMenuState_Error_NotFormatWait,
	eEmuMenuState_Error_End,
	&errvcm_action_notformatwait_close
};



//////////////////////////
//error badformat
trlEmuMenuStateChange errvcm_statechange_begin2badformatok =
{
	eEmuMenuState_Error_Begin,
	eEmuMenuState_Error_BadFormatOk,
	&errvcm_action_badformatok_open
};

trlEmuMenuStateChange errvcm_statechange_badformatok2badformatwait =
{
	eEmuMenuState_Error_BadFormatOk,
	eEmuMenuState_Error_BadFormatWait,
	&errvcm_action_badformatok_beginwait
};

trlEmuMenuStateChange errvcm_statechange_badformatwait2badformatdone =
{
	eEmuMenuState_Error_BadFormatWait,
	eEmuMenuState_Error_BadFormatDone,
	&errvcm_action_badformatok_closewait_done
};

trlEmuMenuStateChange errvcm_statechange_badformatdone2end =
{
	eEmuMenuState_Error_BadFormatDone,
	eEmuMenuState_Error_End,
	&errvcm_action_badformatdone_close
};
//////////////////////////
//error vfailed
trlEmuMenuStateChange errvcm_statechange_begin2vfailedok =
{
	eEmuMenuState_Error_Begin,
	eEmuMenuState_Error_VFailedOk,
	&errvcm_action_vfailedok_open
};

trlEmuMenuStateChange errvcm_statechange_vfailedok2vfailedwait =
{
	eEmuMenuState_Error_VFailedOk,
	eEmuMenuState_Error_VFailedWait,
	&errvcm_action_vfailedok_beginwait
};

trlEmuMenuStateChange errvcm_statechange_vfailedwait2vfaileddone =
{
	eEmuMenuState_Error_VFailedWait,
	eEmuMenuState_Error_VFailedDone,
	&errvcm_action_vfailedok_closewait_done
};

trlEmuMenuStateChange errvcm_statechange_vfaileddone2end =
{
	eEmuMenuState_Error_VFailedDone,
	eEmuMenuState_Error_End,
	&errvcm_action_vfaileddone_close
};


//////////////////////////
//dlp
trlEmuMenuStateChange cgbvcm_statechange_main2NetOpPre =
{
	eEmuMenuState_Main,
	eEmuMenuState_NetOpPre,
	&cgbvcm_action_mainfadein
};
trlEmuMenuStateChange cgbvcm_statechange_nmain2NetOpPre =
{
	eEmuMenuState_NMain,
	eEmuMenuState_NetOpPre,
	&cgbvcm_action_nmainfadein
};
trlEmuMenuStateChange cgbvcm_statechange_dlpbeginback2dlpbegin =
{
	eEmuMenuState_DLPBeginBack,
	eEmuMenuState_DLPBegin,
	&cgbvcm_action_dlpbeginback2dlpbegin
};
trlEmuMenuStateChange cgbvcm_statechange_dlpbeginback2backmain =
{
	eEmuMenuState_DLPBeginBack,
	eEmuMenuState_BackToMain,
	&cgbvcm_action_dlpbeginback2backmain
};

trlEmuMenuStateChange cgbvcm_statechange_dlpbeginback2dlpdlperror =
{
	eEmuMenuState_DLPBeginBack,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlpbeginback2dlpdlperror
};


trlEmuMenuStateChange cgbvcm_statechange_backtomain2main =
{
	eEmuMenuState_BackToMain,
	eEmuMenuState_Main,
	&cgbvcm_action_mainfadeout
};

trlEmuMenuStateChange cgbvcm_statechange_backtomain2nmain =
{
	eEmuMenuState_BackToMain,
	eEmuMenuState_NMain,
	&cgbvcm_action_nmainfadeout
};

trlEmuMenuStateChange cgbvcm_statechange_netoppre2netconnconfirm =
{
	eEmuMenuState_NetOpPre,
	eEmuMenuState_NetConnConfirm,
	&cgbvcm_action_netconnconfirmopen
};

trlEmuMenuStateChange cgbvcm_statechange_netconnconfirm2backtomain =
{
	eEmuMenuState_NetConnConfirm,
	eEmuMenuState_BackToMain,
	&cgbvcm_action_netconnconfirmback
};

trlEmuMenuStateChange cgbvcm_statechange_netinit2dlpdlperror =
{
	eEmuMenuState_NetInit,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_netinit2dlpdlperror
};


trlEmuMenuStateChange cgbvcm_statechange_dlpdlperror2backtomain =
{
	eEmuMenuState_DLPDLPError,
	eEmuMenuState_BackToMain,
	&cgbvcm_action_dlpdlperrorclose
};

trlEmuMenuStateChange cgbvcm_statechange_dlperrokclose =
{
	eEmuMenuState_DLPErrorOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlperrorokclose
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnerrokclose =
{
	eEmuMenuState_DLPErrorOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlpnerrorokclose
};

trlEmuMenuStateChange cgbvcm_statechange_netconnconfirm2netinit =
{
	eEmuMenuState_NetConnConfirm,
	eEmuMenuState_NetInit,
	&cgbvcm_action_netconnconfirm2netinit
};

trlEmuMenuStateChange cgbvcm_statechange_netinit2dlpbegin =
{
	eEmuMenuState_NetInit,
	eEmuMenuState_DLPBegin,
	&cgbvcm_action_netinit2dlpbegin
};


trlEmuMenuStateChange cgbvcm_statechange_netoppre2dlpdlperror =
{
	eEmuMenuState_NetOpPre,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_netoppre2dlpdlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpbegin2dlpbeginback =
{
	eEmuMenuState_DLPBegin,
	eEmuMenuState_DLPBeginBack,
	&cgbvcm_action_dlpbegin2dlpbeginback
};

trlEmuMenuStateChange cgbvcm_statechange_dlpbegin2dlpconn =
{
	eEmuMenuState_DLPBegin,
	eEmuMenuState_DLPConn,
	&cgbvcm_action_dlpbegin2dlpconn
};

trlEmuMenuStateChange cgbvcm_statechange_dlpbegin2dlpdlperror =
{
	eEmuMenuState_DLPBegin,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlpbegin2dlpdlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpconn2dlpdlperror =
{
	eEmuMenuState_DLPConn,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlpconn2dlpdlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpconn2dlpconnback =
{
	eEmuMenuState_DLPConn,
	eEmuMenuState_DLPConnBack,
	&cgbvcm_action_dlpconn2dlpconnback
};

trlEmuMenuStateChange cgbvcm_statechange_dlpconnback2dlpconn =
{
	eEmuMenuState_DLPConnBack,
	eEmuMenuState_DLPConn,
	&cgbvcm_action_dlpconnback2dlpconn
};

trlEmuMenuStateChange cgbvcm_statechange_dlpconnback2backmain =
{
	eEmuMenuState_DLPConnBack,
	eEmuMenuState_BackToMain,
	&cgbvcm_action_dlpconnback2backmain
};

trlEmuMenuStateChange cgbvcm_statechange_dlpconnback2dlpdlperror =
{
	eEmuMenuState_DLPConnBack,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlpconnback2dlpdlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpconn2dlp =
{
	eEmuMenuState_DLPConn,
	eEmuMenuState_DLP,
	&cgbvcm_action_dlpconn2dlp
};

trlEmuMenuStateChange cgbvcm_statechange_dlp2dlpnetinit =
{
	eEmuMenuState_DLP,
	eEmuMenuState_DLPNetInit,
	&cgbvcm_action_dlp2dlpnetinit
};

trlEmuMenuStateChange cgbvcm_statechange_dlp2dlpdlperror =
{
	eEmuMenuState_DLP,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlp2dlpdlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlp2dlpback =
{
	eEmuMenuState_DLP,
	eEmuMenuState_DLPBack,
	&cgbvcm_action_dlp2dlpback
};

trlEmuMenuStateChange cgbvcm_statechange_dlpback2dlp =
{
	eEmuMenuState_DLPBack,
	eEmuMenuState_DLP,
	&cgbvcm_action_dlpback2dlp
};

trlEmuMenuStateChange cgbvcm_statechange_dlpback2backmain =
{
	eEmuMenuState_DLPBack,
	eEmuMenuState_BackToMain,
	&cgbvcm_action_dlpback2backmain
};

trlEmuMenuStateChange cgbvcm_statechange_dlpback2dlpdlperror =
{
	eEmuMenuState_DLPBack,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlpback2dlpdlperror
};


trlEmuMenuStateChange cgbvcm_statechange_dlpnetinit2dlps =
{
	eEmuMenuState_DLPNetInit,
	eEmuMenuState_DLPS,
	&cgbvcm_action_dlpnetinit2dlps
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnetinit2dlpnetinitback =
{
	eEmuMenuState_DLPNetInit,
	eEmuMenuState_DLPNetInitBack,
	&cgbvcm_action_dlpnetinit2dlpnetinitback
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnetinitback2dlpnetinit = 
{
	eEmuMenuState_DLPNetInitBack,
	eEmuMenuState_DLPNetInit,
	&cgbvcm_action_dlpnetinitback2dlpnetinit
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnetinitback2backmain = 
{
	eEmuMenuState_DLPNetInitBack,
	eEmuMenuState_BackToMain,
	&cgbvcm_action_dlpnetinitback2backmain
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnetinitback2dlps = 
{
	eEmuMenuState_DLPNetInitBack,
	eEmuMenuState_DLPS,
	&cgbvcm_action_dlpnetinitback2dlps
};

trlEmuMenuStateChange cgbvcm_statechange_dlps2dlpwait =
{
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPWait,
	&cgbvcm_action_dlps2dlpwait
};

trlEmuMenuStateChange cgbvcm_statechange_dlps2dlpok =
{
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPOk,
	&cgbvcm_action_dlps2dlpok
};

trlEmuMenuStateChange cgbvcm_statechange_dlps2dlpstandby =
{
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlps2dlpstandby
};

trlEmuMenuStateChange cgbvcm_statechange_dlps2dlpnstandby =
{
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlps2dlpnstandby
};

trlEmuMenuStateChange cgbvcm_statechange_dlpwait2dlpchilderror =
{
	eEmuMenuState_DLPWait,
	eEmuMenuState_DLPChildError,
	&cgbvcm_action_dlpwait2dlpchilderror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpwait2dlpwaitback =
{
	eEmuMenuState_DLPWait,
	eEmuMenuState_DLPWaitBack,
	&cgbvcm_action_dlpwait2dlpwaitback
};

trlEmuMenuStateChange cgbvcm_statechange_dlpwaitback2dlpwait =
{
	eEmuMenuState_DLPWaitBack,
	eEmuMenuState_DLPWait,	
	&cgbvcm_action_dlpwaitback2dlpwait
};

trlEmuMenuStateChange cgbvcm_statechange_dlpwaitback2dlpchilderror =
{
	eEmuMenuState_DLPWaitBack,
	eEmuMenuState_DLPChildError,
	&cgbvcm_action_dlpwaitback2dlpchilderror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpwaitback2dlpchildendwait =
{
	eEmuMenuState_DLPWaitBack,
	eEmuMenuState_DLPChildEndWait,
	&cgbvcm_action_dlpwaitback2dlpchildendwait
};

trlEmuMenuStateChange cgbvcm_statechange_dlps2dlperror =
{
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPError,
	NULL
};

trlEmuMenuStateChange cgbvcm_statechange_dlps2dlpdlperror =
{
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPDLPError,
	&cgbvcm_action_dlps2dlpdlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpok2dlpstandby =
{
	eEmuMenuState_DLPOk,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpok2dlpstandby
};

trlEmuMenuStateChange cgbvcm_statechange_dlpok2dlpnstandby =
{
	eEmuMenuState_DLPOk,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpok2dlpnstandby
};

trlEmuMenuStateChange cgbvcm_statechange_dlpok2dlperror =
{
	eEmuMenuState_DLPOk,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpok2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpwait2dlpchildstandby =
{
	eEmuMenuState_DLPWait,
	eEmuMenuState_DLPChildStandBy,
	&cgbvcm_action_dlpwait2dlpchildstandby
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2dlpmain =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPMain,
	&cgbvcm_action_dlpmain_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2dlpnmain =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPNMain,
	&cgbvcm_action_dlpnmain_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildstandby2dlpchildmain =
{
	eEmuMenuState_DLPChildStandBy,
	eEmuMenuState_DLPChildMain,
	&cgbvcm_action_dlpchildmain_open
};


trlEmuMenuStateChange cgbvcm_statechange_dlpnmain2dlpstandby =
{
	eEmuMenuState_DLPNMain,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpnmain_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnmain2dlpnend =
{
	eEmuMenuState_DLPNMain,
	eEmuMenuState_DLPNEnd,
	&cgbvcm_action_dlpnend_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpmain2dlpstandby =
{
	eEmuMenuState_DLPMain,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpmain_close
};


trlEmuMenuStateChange cgbvcm_statechange_dlpmain2dlpreset =
{
	eEmuMenuState_DLPMain,
	eEmuMenuState_DLPReset,
	&cgbvcm_action_dlpreset_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnmain2dlpreset =
{
	eEmuMenuState_DLPNMain,
	eEmuMenuState_DLPReset,
	&cgbvcm_action_dlpnreset_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildmain2dlpchildstandby =
{
	eEmuMenuState_DLPChildMain,
	eEmuMenuState_DLPChildStandBy,
	&cgbvcm_action_dlpchildmain_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildmain2dlpchildend =
{
	eEmuMenuState_DLPChildMain,
	eEmuMenuState_DLPChildEnd,
	&cgbvcm_action_dlpchildend_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildmain2dlpchilderrors =
{
	eEmuMenuState_DLPChildMain,
	eEmuMenuState_DLPChildErrorS,
	&cgbvcm_action_dlpchilderrors_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildmain2dlpchildothermenu =
{
	eEmuMenuState_DLPChildMain,
	eEmuMenuState_DLPChildOtherMenu,
	&cgbvcm_action_dlpchildothermenu_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpmain2dlpend =
{
	eEmuMenuState_DLPMain,
	eEmuMenuState_DLPEnd,
	&cgbvcm_action_dlpend_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpmain2dlperror =
{
	eEmuMenuState_DLPMain,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpmain2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnmain2dlperror =
{
	eEmuMenuState_DLPNMain,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpnmain2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpmain2dlpothermenu =
{
	eEmuMenuState_DLPMain,
	eEmuMenuState_DLPOtherMenu,
	&cgbvcm_action_dlpothermenu_open
};




trlEmuMenuStateChange cgbvcm_statechange_dlpchildend2dlpchildmain =
{
	eEmuMenuState_DLPChildEnd,
	eEmuMenuState_DLPChildMain,
	&cgbvcm_action_dlpchildend_close1
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildend2dlpchildendwait =
{
	eEmuMenuState_DLPChildEnd,
	eEmuMenuState_DLPChildEndWait,
	&cgbvcm_action_dlpchildendtochildendwait
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildend2dlpchilderror =
{
	eEmuMenuState_DLPChildEnd,
	eEmuMenuState_DLPChildErrorS,
	&cgbvcm_action_dlpchildend2dlpchilderrors
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildend2dlpothermenu =
{
	eEmuMenuState_DLPChildEnd,
	eEmuMenuState_DLPChildOtherMenu,
	&cgbvcm_action_dlpchildend2dlpchildothermenu
};



trlEmuMenuStateChange cgbvcm_statechange_dlpreset2dlpmain =
{
	eEmuMenuState_DLPReset,
	eEmuMenuState_DLPMain,
	&cgbvcm_action_dlpreset_close1
};

trlEmuMenuStateChange cgbvcm_statechange_dlpreset2dlpnmain =
{
	eEmuMenuState_DLPReset,
	eEmuMenuState_DLPNMain,
	&cgbvcm_action_dlpnreset_close1
};

trlEmuMenuStateChange cgbvcm_statechange_dlpreset2dlpstandby =
{
	eEmuMenuState_DLPReset,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpreset_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpreset2dlpnstandby =
{
	eEmuMenuState_DLPReset,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpnreset_close
};


trlEmuMenuStateChange cgbvcm_statechange_dlpend2dlpmain =
{
	eEmuMenuState_DLPEnd,
	eEmuMenuState_DLPMain,
	&cgbvcm_action_dlpend_close1
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnend2dlpnmain =
{
	eEmuMenuState_DLPNEnd,
	eEmuMenuState_DLPNMain,
	&cgbvcm_action_dlpnend_close1
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnend2dlpends =
{
	eEmuMenuState_DLPNEnd,
	eEmuMenuState_DLPEndS,
	&cgbvcm_action_dlpend_close
};


trlEmuMenuStateChange cgbvcm_statechange_dlpend2dlpends =
{
	eEmuMenuState_DLPEnd,
	eEmuMenuState_DLPEndS,
	&cgbvcm_action_dlpend_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpreset2dlperror =
{
	eEmuMenuState_DLPReset,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpreset2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpend2dlperror =
{
	eEmuMenuState_DLPEnd,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpend2dlperror
};
trlEmuMenuStateChange cgbvcm_statechange_dlpnend2dlperrorok =
{
	eEmuMenuState_DLPEnd,
	eEmuMenuState_DLPErrorOk,
	&cgbvcm_action_dlpend2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpends2dlpendok =
{
	eEmuMenuState_DLPEndS,
	eEmuMenuState_DLPEndOk,
	&cgbvcm_action_dlpendok_open
};


trlEmuMenuStateChange cgbvcm_statechange_dlpends2dlpendwait =
{
	eEmuMenuState_DLPEndS,
	eEmuMenuState_DLPEndWait,
	&cgbvcm_action_dlpendwait_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpendok2standby =
{
	eEmuMenuState_DLPEndOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlpendok2standby
};

trlEmuMenuStateChange cgbvcm_statechange_dlpnendok2standby =
{
	eEmuMenuState_DLPEndOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlpnendok2standby
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2dlpothermenu =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPOtherMenu,
	&cgbvcm_action_dlpothermenu_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2dlpnothermenu =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPOtherMenu,
	&cgbvcm_action_dlpnothermenu_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildstandby2dlpchildothermenu =
{
	eEmuMenuState_DLPChildStandBy,
	eEmuMenuState_DLPChildOtherMenu,
	&cgbvcm_action_dlpchildothermenu_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildstandby2dlpchilderrors =
{
	eEmuMenuState_DLPChildStandBy,
	eEmuMenuState_DLPChildErrorS,
	&cgbvcm_action_dlpchilderrors_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2dlperror =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpstandby2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2dlpnerror =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpstandby2dlpnerror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpstandby2allleaveok =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPAllLeaveOk,
	&cgbvcm_action_dlpallleaveok_open1
};

trlEmuMenuStateChange cgbvcm_statechange_dlpothermenu2dlpstandby =
{
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpothermenu_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpothermenu2dlpnstandby =
{
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuState_DLPStandBy,
	&cgbvcm_action_dlpnothermenu_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildothermenu2dlpchildstandby =
{
	eEmuMenuState_DLPChildOtherMenu,
	eEmuMenuState_DLPChildStandBy,
	&cgbvcm_action_dlpchildothermenu_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildothermenu2dlpchilderrors = 
{
	eEmuMenuState_DLPChildOtherMenu,
	eEmuMenuState_DLPChildErrorS,
	&cgbvcm_action_dlpchildothermenu2dlpchilderrors
};

trlEmuMenuStateChange cgbvcm_statechange_dlpchildothermenu2dlpchildendwait = 
{
	eEmuMenuState_DLPChildOtherMenu,
	eEmuMenuState_DLPChildEndWait,
	&cgbvcm_action_dlpchildothermenutodlpchildendwait
};


trlEmuMenuStateChange cgbvcm_statechange_dlpchilderrors2dlpchilderror =
{
	eEmuMenuState_DLPChildErrorS,
	eEmuMenuState_DLPChildError,
	&cgbvcm_action_dlpchilderrors2dlpchilderror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpothermenu2dlpallleaveok =
{
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuState_DLPAllLeaveOk,
	&cgbvcm_action_dlpallleaveok_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlpothermenu2dlpendwait =
{
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuState_DLPEndWait,
	NULL
};

trlEmuMenuStateChange cgbvcm_statechange_dlpothermenu2dlperror =
{
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuState_DLPError,
	&cgbvcm_action_dlpothermenu2dlperror
};

trlEmuMenuStateChange cgbvcm_statechange_dlpallleaveok2dlpbegin =
{
	eEmuMenuState_DLPAllLeaveOk,
	eEmuMenuState_DLPBegin,
	&cgbvcm_action_dlpallleaveok_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlpallleaveok2standby =
{
	eEmuMenuState_DLPAllLeaveOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlpallleaveok_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlphaveleaveok2standby =
{
	eEmuMenuState_DLPHaveLeaveOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlphaveleaveok_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlphaveleaveok2nstandby =
{
	eEmuMenuState_DLPHaveLeaveOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlphaveleaveok_nclose
};

trlEmuMenuStateChange cgbvcm_statechange_dlphaveerrorok2standby =
{
	eEmuMenuState_DLPErrorOk,
	eEmuMenuState_StandBy,
	&cgbvcm_action_dlphaveerrorok_close
};

trlEmuMenuStateChange cgbvcm_statechange_dlphaveleaveok2dlperrorend =
{
	eEmuMenuState_DLPHaveLeaveOk,
	eEmuMenuState_DLPErrorEnd,
	&cgbvcm_action_dlphaveleaveok_close1
};

trlEmuMenuStateChange cgbvcm_statechange_dlperror2dlpallleaveok =
{
	eEmuMenuState_DLPError,
	eEmuMenuState_DLPAllLeaveOk,
	&cgbvcm_action_dlpallleaveok_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlperror2dlphaveerrorok =
{
	eEmuMenuState_DLPError,
	eEmuMenuState_DLPErrorOk,
	&cgbvcm_action_dlphaveerrorok_open
};



trlEmuMenuStateChange cgbvcm_statechange_dlperror2dlphaveleaveok =
{
	eEmuMenuState_DLPError,
	eEmuMenuState_DLPHaveLeaveOk,
	&cgbvcm_action_dlphaveleaveok_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlperror2dlperrorok =
{
	eEmuMenuState_DLPError,
	eEmuMenuState_DLPErrorOk,
	&cgbvcm_action_dlperrorok_open
};


trlEmuMenuStateChange cgbvcm_statechange_dlperror2dlpothermenu =
{
	eEmuMenuState_DLPError,
	eEmuMenuState_DLPOtherMenu,
	&cgbvcm_action_dlpothermenu_open
};

trlEmuMenuStateChange cgbvcm_statechange_dlperrorend2dlpstandby =
{
	eEmuMenuState_DLPErrorEnd,
	eEmuMenuState_DLPStandBy,
	NULL
};

trlEmuMenuStateChange cgbvcm_statechange_dlperrorend2dlpmain =
{
	eEmuMenuState_DLPErrorEnd,
	eEmuMenuState_DLPMain,
	&cgbvcm_action_dlpmain_open
};

////////////////////////////
////////////////////////////
////////////////////////////
//state

trlEmuMenuState cgbvcmstate_init =
{
	eEmuMenuState_Init,
	eEmuMenuStateType_Wait,
	&cgbvcm_scene_main,
	0,
	{},
	NULL,
	{
		&cgbvcm_statechange_init2standby
	}
};

trlEmuMenuState cgbvcmstate_standby =
{
	eEmuMenuState_StandBy,
	eEmuMenuStateType_Wait,
	&cgbvcm_scene_main,
	0,
	{},
	trlEmuMenuCallBack_StandySelect,
	{
		&cgbvcm_statechange_standbyselect2main,
			&cgbvcm_statechange_standbyselect2nmainpre,
			&cgbvcm_statechange_standbyselect2dlps,
			&cgbvcm_statechange_standbyselect2dlpmain,
	}
};



trlEmuMenuState cgbvcmstate_standbyselect =
{
	eEmuMenuState_StandBySelect,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_main,
	0,
	{},
	trlEmuMenuCallBack_StandySelect,
	{
		&cgbvcm_statechange_standbyselect2main,
			&cgbvcm_statechange_standbyselect2nmainpre,
			&cgbvcm_statechange_standbyselect2dlps
	}
};

trlEmuMenuState cgbvcmstate_main =
{
	eEmuMenuState_Main,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_main,
	0,
	{},
	NULL,
	{
		&cgbvcm_statechange_main2standby,
			&cgbvcm_statechange_mainclose2standby,
			&cgbvcm_statechange_main2save,
			&cgbvcm_statechange_main2reset,
			&cgbvcm_statechange_main2load,
			&cgbvcm_statechange_main2modechangeaton0,
			&cgbvcm_statechange_main2NetOpPre
	}
};

trlEmuMenuState cgbvcmstate_save =
{
	eEmuMenuState_Save,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_save,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_save2main,
			&cgbvcm_statechange_save2saveing,
	}
};

trlEmuMenuState cgbvcmstate_saveing =
{
	eEmuMenuState_Saveing,
	eEmuMenuStateType_WaitThread,
	&cgbvcm_scene_saveing,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcSave,
	{
		&cgbvcm_statechange_saveing2saveok
	}
};

trlEmuMenuState cgbvcmstate_saveok =
{
	eEmuMenuState_SaveOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_saveok,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_saveok2main
	}
};

trlEmuMenuState cgbvcmstate_load =
{
	eEmuMenuState_Load,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_load,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_load2main,
			&cgbvcm_statechange_load2loading,
	}
};

trlEmuMenuState cgbvcmstate_loading =
{
	eEmuMenuState_Loading,
	eEmuMenuStateType_WaitThread,
	&cgbvcm_scene_loading,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcLoad,
	{
		&cgbvcm_statechange_loading2loadok
	}
};

trlEmuMenuState cgbvcmstate_loadok =
{
	eEmuMenuState_LoadOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_loadok,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_loadok2main
	}
};

trlEmuMenuState cgbvcmstate_reset =
{
	eEmuMenuState_Reset,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_reset,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_reset2main,
			&cgbvcm_statechange_reset2reseting,
	}
};

trlEmuMenuState cgbvcmstate_reseting =
{
	eEmuMenuState_Reseting,
	eEmuMenuStateType_WaitThread,
	&cgbvcm_scene_reseting,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcReset,
	{
		&cgbvcm_statechange_reseting2standby
	}
};

trlEmuMenuState cgbvcmstate_nmainpre =
{
	eEmuMenuState_NMainPre,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_nmain,
	0,
	{},
	trlEmuMenuCallBack_NMainPreSelect,
	{
		&cgbvcm_statechange_nmainpre2nmain,
			&cgbvcm_statechange_nmainpre2firsttimew00
	}
};

trlEmuMenuState cgbvcmstate_nmain =
{
	eEmuMenuState_NMain,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_nmain,
	0,
	{},
	NULL,
	{
		&cgbvcm_statechange_nmain2standby,
			&cgbvcm_statechange_nmainclose2standby,
			&cgbvcm_statechange_nmain2nreset,
			&cgbvcm_statechange_nmain2modechangew00,
			&cgbvcm_statechange_nmain2NetOpPre
	}
};

trlEmuMenuState cgbvcmstate_nreset =
{
	eEmuMenuState_NReset,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_nreset,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_nreset2nmain,
			&cgbvcm_statechange_nreset2nreseting,
	}
};

trlEmuMenuState cgbvcmstate_nreseting =
{
	eEmuMenuState_NReseting,
	eEmuMenuStateType_WaitThread,
	&cgbvcm_scene_nreseting,
	1,
	{&cgbvcm_scene_nmain},
	trlEmuMenuCallBack_ProcReset,
	{
		&cgbvcm_statechange_nreseting2standby
	}
};

trlEmuMenuState cgbvcmstate_modechangew00 =
{
	eEmuMenuState_ModeChange_W00,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_modechange_w00,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_modechangew00_2_nmain,
			&cgbvcm_statechange_modechangew00_2_modechangew01
	}
};

trlEmuMenuState cgbvcmstate_modechangew01 =
{
	eEmuMenuState_ModeChange_W01,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_modechange_w01,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_modechangew01_2_nmain,
			&cgbvcm_statechange_modechangew01_2_modechangentoa0
	}
};

trlEmuMenuState cgbvcmstate_modechangentoa0 =
{
	eEmuMenuState_ModeChange_NTOA0,
	eEmuMenuStateType_WaitAnim,
	&cgbvcm_scene_modechange_ntoa0,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_modechangentoa0_2_ntoa1
	}
};

trlEmuMenuState cgbvcmstate_modechangentoa1 =
{
	eEmuMenuState_ModeChange_NTOA1,
	eEmuMenuStateType_WaitAnim,
	&cgbvcm_scene_modechange_ntoa1,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_modechangentoa1_2_main
	}
};

trlEmuMenuState cgbvcmstate_modechangeaton0 =
{
	eEmuMenuState_ModeChange_ATON0,
	eEmuMenuStateType_WaitAnim,
	&cgbvcm_scene_modechange_aton0,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_modechangeaton0_2_nmain
	}
};

trlEmuMenuState errvcmstate_begin =
{
	eEmuMenuState_Error_Begin,
	eEmuMenuStateType_Select,
	&errvcm_scene_begin,
	0,
	{},
	trlEmuMenuCallBack_ErrorSelect,
	{
		&errvcm_statechange_begin2notformatwait,
			&errvcm_statechange_begin2badformatok,
			&errvcm_statechange_begin2vfailedok,
			&errvcm_statechange_begin2opdeniedwait
	}
};

trlEmuMenuState errvcmstate_end =
{
	eEmuMenuState_Error_End,
	eEmuMenuStateType_Wait,
	&errvcm_scene_end,
	0,
	{},
	NULL,
	{}
};

trlEmuMenuState errvcmstate_opdeniedwait =
{
	eEmuMenuState_Error_OPDeniedWait,
	eEmuMenuStateType_WaitInfi,
	&errvcm_scene_opdeniedwait,
	0,
	{},
	NULL,
	{
	}
};


trlEmuMenuState errvcmstate_notformatwait =
{
	eEmuMenuState_Error_NotFormatWait,
	eEmuMenuStateType_WaitThread,
	&errvcm_scene_notformatwait,
	0,
	{},
	trlEmuMenuCallBack_ProcNotFormat,
	{
		&errvcm_statechange_notformatwait2end
	}
};

trlEmuMenuState errvcmstate_badformatok =
{
	eEmuMenuState_Error_BadFormatOk,
	eEmuMenuStateType_WaitButton,
	&errvcm_scene_badformatok,
	0,
	{},
	NULL,
	{
		&errvcm_statechange_badformatok2badformatwait
	}
};

trlEmuMenuState errvcmstate_badformatwait =
{
	eEmuMenuState_Error_BadFormatWait,
	eEmuMenuStateType_WaitThread,
	&errvcm_scene_badformatok,
	0,
	{},
	trlEmuMenuCallBack_ProcBadFormat,
	{
		&errvcm_statechange_badformatwait2badformatdone
	}
};

trlEmuMenuState errvcmstate_badformatdone =
{
	eEmuMenuState_Error_BadFormatDone,
	eEmuMenuStateType_WaitButton,
	&errvcm_scene_badformatdone,
	0,
	{},
	NULL,
	{
		&errvcm_statechange_badformatdone2end
	}
};

trlEmuMenuState errvcmstate_vfailedok =
{
	eEmuMenuState_Error_VFailedOk,
	eEmuMenuStateType_WaitButton,
	&errvcm_scene_vfailedok,
	0,
	{},
	NULL,
	{
		&errvcm_statechange_vfailedok2vfailedwait
	}
};

trlEmuMenuState errvcmstate_vfailedwait =
{
	eEmuMenuState_Error_VFailedWait,
	eEmuMenuStateType_WaitThread,
	&errvcm_scene_vfailedok,
	0,
	{},
	trlEmuMenuCallBack_ProcBadFormat,
	{
		&errvcm_statechange_vfailedwait2vfaileddone
	}
};

trlEmuMenuState errvcmstate_vfaileddone =
{
	eEmuMenuState_Error_VFailedDone,
	eEmuMenuStateType_WaitButton,
	&errvcm_scene_vfaileddone,
	0,
	{},
	NULL,
	{
		&errvcm_statechange_vfaileddone2end
	}
};

trlEmuMenuState cgbvcmstate_firsttime_w00 =
{
	eEmuMenuState_FirstTime_W00,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_firsttime_w00,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_firsttimew00_2_firsttimew02,
			&cgbvcm_statechange_firsttimew00_2_firsttimew01
	}
};

trlEmuMenuState cgbvcmstate_firsttime_w01 =
{
	eEmuMenuState_FirstTime_W01,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_firsttime_w01,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_firsttimew01_2_nmain,
			&cgbvcm_statechange_firsttimew01_2_modechangentoa0
	}
};

trlEmuMenuState cgbvcmstate_firsttime_w02 =
{
	eEmuMenuState_FirstTime_W02,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_firsttime_w02,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_firsttimew02_2_firsttimew00,
			&cgbvcm_statechange_firsttimew02_2_firsttimew03
	}
};

trlEmuMenuState cgbvcmstate_firsttime_w03 =
{
	eEmuMenuState_FirstTime_W03,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_firsttime_w03,
	1,
	{&cgbvcm_scene_nmain},
	NULL,
	{
		&cgbvcm_statechange_firsttimew03_2_firsttimew02,
			&cgbvcm_statechange_firsttimew03_2_firsttimew01
	}
};

trlEmuMenuState cgbvcmstate_netoppre =
{
	eEmuMenuState_NetOpPre,
	eEmuMenuStateType_Select, //eEmuMenuStateType_Select,
	&cgbvcm_scene_netoppre,
	0,
	{NULL},
	trlEmuMenuCallBack_NetOpPreSelect,
	{
		&cgbvcm_statechange_netoppre2netconnconfirm,
			&cgbvcm_statechange_netoppre2dlpdlperror,
	}
};

trlEmuMenuState cgbvcmstate_backtomain =
{
	eEmuMenuState_BackToMain,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_main,
	1,
	{&cgbvcm_scene_nmain},
	trlEmuMenuCallBack_BackToMainSelect,
	{
		&cgbvcm_statechange_backtomain2main,
			&cgbvcm_statechange_backtomain2nmain
	}
};

trlEmuMenuState cgbvcmstate_netconnconfirm =
{
	eEmuMenuState_NetConnConfirm,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_netconnconfirm,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_netconnconfirm2netinit,
			&cgbvcm_statechange_netconnconfirm2backtomain
	}
};

trlEmuMenuState cgbvcmstate_netinit =
{
	eEmuMenuState_NetInit,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_netconnconfirm,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_NetInitSelect,
	{
		&cgbvcm_statechange_netinit2dlpbegin,
			&cgbvcm_statechange_netinit2dlpdlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpdlperror =
{
	eEmuMenuState_DLPDLPError,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlpdlperror,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_dlpdlperror2backtomain
	}
};

trlEmuMenuState cgbvcmstate_dlpbeginback =
{
	eEmuMenuState_DLPBeginBack,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpbeginback,
	2,
	{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin},
	trlEmuMenuCallBack_DLPBeginBackSelect,
	{
		&cgbvcm_statechange_dlpbeginback2dlpbegin,
			&cgbvcm_statechange_dlpbeginback2backmain,
			&cgbvcm_statechange_dlpbeginback2dlpdlperror
	}
};


trlEmuMenuState cgbvcmstate_dlpbegin =
{
	eEmuMenuState_DLPBegin,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpbegin,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_DLPBeginSelect,
	{
		&cgbvcm_statechange_dlpbegin2dlpbeginback,
			&cgbvcm_statechange_dlpbegin2dlpconn,
			&cgbvcm_statechange_dlpbegin2dlpdlperror
	}
};



trlEmuMenuState cgbvcmstate_dlpconn =
{
	eEmuMenuState_DLPConn,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpconn,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcDLP,
	{
		&cgbvcm_statechange_dlpconn2dlpconnback,
			&cgbvcm_statechange_dlpconn2dlp,
			&cgbvcm_statechange_dlpconn2dlpdlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpconnback =
{
	eEmuMenuState_DLPConnBack,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpconnback,
	2,
	{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn},
	trlEmuMenuCallBack_DLPConnBackSelect,
	{
		&cgbvcm_statechange_dlpconnback2dlpconn,
			&cgbvcm_statechange_dlpconnback2backmain,
			&cgbvcm_statechange_dlpconnback2dlpdlperror
	}
};

trlEmuMenuState cgbvcmstate_dlp =
{
	eEmuMenuState_DLP,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlp,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcDLP,
	{
		&cgbvcm_statechange_dlp2dlpnetinit,
			&cgbvcm_statechange_dlp2dlpdlperror,
			&cgbvcm_statechange_dlp2dlpback
	}
};

trlEmuMenuState cgbvcmstate_dlpback =
{
	eEmuMenuState_DLPBack,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpback,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcDLPBack,
	{
		&cgbvcm_statechange_dlpback2dlp,
			&cgbvcm_statechange_dlpback2backmain,
			&cgbvcm_statechange_dlpback2dlpdlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpnetinit =
{
	eEmuMenuState_DLPNetInit,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpnetinit,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcNetInit,
	{
		&cgbvcm_statechange_dlpnetinit2dlps,
			&cgbvcm_statechange_dlpnetinit2dlps,
			&cgbvcm_statechange_dlpnetinit2dlpnetinitback,
	}
};

trlEmuMenuState cgbvcmstate_dlpnetinitback =
{
	eEmuMenuState_DLPNetInitBack,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpnetinitback,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_ProcNetInitBack,
	{
		&cgbvcm_statechange_dlpnetinitback2dlpnetinit,
			&cgbvcm_statechange_dlpnetinitback2backmain,
			&cgbvcm_statechange_dlpnetinitback2dlps
	}
};


trlEmuMenuState cgbvcmstate_dlps =
{
	eEmuMenuState_DLPS,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_dlps,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_DLPSSelect,
	{
		&cgbvcm_statechange_dlps2dlpok,
			&cgbvcm_statechange_dlps2dlpstandby,
			&cgbvcm_statechange_dlps2dlpstandby,
			&cgbvcm_statechange_dlps2dlpwait,
			&cgbvcm_statechange_dlps2dlpdlperror
	}
};


trlEmuMenuState cgbvcmstate_dlpwait =
{
	eEmuMenuState_DLPWait,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpwait,
	1,
	{&cgbvcm_scene_dlpchildmain},
	trlEmuMenuCallBack_DLPWait,
	{
		&cgbvcm_statechange_dlpwait2dlpchildstandby,
			&cgbvcm_statechange_dlpwait2dlpchilderror,
			&cgbvcm_statechange_dlpwait2dlpwaitback
	}
};


trlEmuMenuState cgbvcmstate_dlpwaitback =
{
	eEmuMenuState_DLPWaitBack,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpwaitback,
	1,
	{&cgbvcm_scene_dlpchildmain},
	trlEmuMenuCallBack_DLPWaitBack,
	{
		&cgbvcm_statechange_dlpwaitback2dlpwait,
			&cgbvcm_statechange_dlpwaitback2dlpchildendwait,
			&cgbvcm_statechange_dlpwaitback2dlpchilderror,
	}
};


trlEmuMenuState cgbvcmstate_dlpok =
{
	eEmuMenuState_DLPOk,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpok,
	1,
	{&cgbvcm_scene_main},
	trlEmuMenuCallBack_DLPOkWaitSelect,
	{
		&cgbvcm_statechange_dlpok2dlpstandby,
			&cgbvcm_statechange_dlpok2dlpnstandby,
			&cgbvcm_statechange_dlpok2dlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpchildstandby =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuStateType_Wait,
	&cgbvcm_scene_dlpchildstandby,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPChildStandBySelect,
	{
		&cgbvcm_statechange_dlpchildstandby2dlpchildmain,
			&cgbvcm_statechange_dlpchildstandby2dlpchildothermenu,
			&cgbvcm_statechange_dlpchildstandby2dlpchilderrors
	}
};


trlEmuMenuState cgbvcmstate_dlpstandby =
{
	eEmuMenuState_DLPStandBy,
	eEmuMenuStateType_Wait,
	&cgbvcm_scene_dlpstandby,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPStandBySelect,
	{
		&cgbvcm_statechange_dlpstandby2dlpmain,
			&cgbvcm_statechange_dlpstandby2dlpnmain,
			&cgbvcm_statechange_dlpstandby2dlpothermenu,
			&cgbvcm_statechange_dlpstandby2dlpnothermenu,			
			&cgbvcm_statechange_dlpstandby2dlperror,
			&cgbvcm_statechange_dlpstandby2dlpnerror
	}
};

trlEmuMenuState cgbvcmstate_dlpmain =
{
	eEmuMenuState_DLPMain,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpmain,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPMainSelect,
	{
		&cgbvcm_statechange_dlpmain2dlpstandby,
			&cgbvcm_statechange_dlpmain2dlpreset,
			&cgbvcm_statechange_dlpmain2dlpend,
			&cgbvcm_statechange_dlpmain2dlperror			
	}
};

trlEmuMenuState cgbvcmstate_dlpnmain =
{
	eEmuMenuState_DLPNMain,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlpnmain,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPNMainSelect,
	{
		&cgbvcm_statechange_dlpnmain2dlpstandby,
			&cgbvcm_statechange_dlpnmain2dlpreset,
			&cgbvcm_statechange_dlpnmain2dlpnend,
			&cgbvcm_statechange_dlpnmain2dlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpchildmain =
{
	eEmuMenuState_DLPChildMain,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpchildmain,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPChildMainSelect,
	{
		&cgbvcm_statechange_dlpchildmain2dlpchildstandby,
			&cgbvcm_statechange_dlpchildmain2dlpchildend,
			&cgbvcm_statechange_dlpchildmain2dlpchilderrors,
			&cgbvcm_statechange_dlpchildmain2dlpchildothermenu
	}
};

trlEmuMenuState cgbvcmstate_dlpchildend =
{
	eEmuMenuState_DLPChildEnd,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpend,
	1,
	{&cgbvcm_scene_dlpchildmain},
	trlEmuMenuCallBack_DLPChildEndSelect,
	{
		&cgbvcm_statechange_dlpchildend2dlpchildmain,
			&cgbvcm_statechange_dlpchildend2dlpchildendwait,
			&cgbvcm_statechange_dlpchildend2dlpchilderror,
			&cgbvcm_statechange_dlpchildend2dlpothermenu
	}
};


trlEmuMenuState cgbvcmstate_dlpreset =
{
	eEmuMenuState_DLPReset,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpreset,
	1,
	{&cgbvcm_scene_dlpmain},
	trlEmuMenuCallBack_DLPResetSelect,
	{
		&cgbvcm_statechange_dlpreset2dlpmain,
			&cgbvcm_statechange_dlpreset2dlpnmain,
			&cgbvcm_statechange_dlpreset2dlpstandby,
			&cgbvcm_statechange_dlpreset2dlpnstandby,
			&cgbvcm_statechange_dlpreset2dlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpend =
{
	eEmuMenuState_DLPEnd,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpend,
	1,
	{&cgbvcm_scene_dlpmain},
	trlEmuMenuCallBack_DLPEndSelect,
	{
		&cgbvcm_statechange_dlpend2dlpmain,
			&cgbvcm_statechange_dlpend2dlpends,
			&cgbvcm_statechange_dlpend2dlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpnend =
{
	eEmuMenuState_DLPNEnd,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	&cgbvcm_scene_dlpend,
	1,
	{&cgbvcm_scene_dlpmain},
	trlEmuMenuCallBack_DLPEndSelect,
	{
		&cgbvcm_statechange_dlpnend2dlpnmain,
			&cgbvcm_statechange_dlpnend2dlpends,
			&cgbvcm_statechange_dlpnend2dlperrorok
	}
};

trlEmuMenuState cgbvcmstate_dlpends =
{
	eEmuMenuState_DLPEndS,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_dlpends,
	1,
	{&cgbvcm_scene_dlpmain},
	trlEmuMenuCallBack_DLPEndsSelect,
	{
		&cgbvcm_statechange_dlpends2dlpendok
	}
};

trlEmuMenuState cgbvcmstate_dlpendok =
{
	eEmuMenuState_DLPEndOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlpendok,
	1,
	{&cgbvcm_scene_dlpmain},
	NULL,
	{
		&cgbvcm_statechange_dlpendok2standby,
		&cgbvcm_statechange_dlpnendok2standby
	}
};

trlEmuMenuState cgbvcmstate_dlpchildendwait =
{
	eEmuMenuState_DLPChildEndWait,
	eEmuMenuStateType_WaitProc,
	&cgbvcm_scene_dlpendwait,
	1,
	{&cgbvcm_scene_dlpchildmain},
	trlEmuMenuCallBack_DLPChildEndWaitProc,
	{
	}
};

trlEmuMenuState cgbvcmstate_dlpendwait =
{
	eEmuMenuState_DLPEndWait,
	eEmuMenuStateType_WaitInfi,
	&cgbvcm_scene_dlpendwait,
	1,
	{&cgbvcm_scene_dlpmain},
	NULL,
	{
	}
};

trlEmuMenuState cgbvcmstate_dlpothermenu =
{
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuStateType_WaitProc,
	&cgbvcm_scene_dlpothermenu,
	1,
	{&cgbvcm_scene_dlpmain},
	trlEmuMenuCallBack_DLPOtherMenu,
	{
		&cgbvcm_statechange_dlpothermenu2dlpstandby,
			&cgbvcm_statechange_dlpothermenu2dlpnstandby,
			&cgbvcm_statechange_dlpothermenu2dlperror
	}
};

trlEmuMenuState cgbvcmstate_dlpchildothermenu =
{
	eEmuMenuState_DLPChildOtherMenu,
	eEmuMenuStateType_WaitProc,
	&cgbvcm_scene_dlpothermenu,
	1,
	{&cgbvcm_scene_dlpchildmain},
	trlEmuMenuCallBack_DLPChildOtherMenu,
	{
		&cgbvcm_statechange_dlpchildothermenu2dlpchildstandby,
			&cgbvcm_statechange_dlpchildothermenu2dlpchilderrors,
			&cgbvcm_statechange_dlpchildothermenu2dlpchildendwait
	}
};

trlEmuMenuState cgbvcmstate_dlpchilderrors =
{
	eEmuMenuState_DLPChildErrorS,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_dlpchilderror,
	1,
	{&cgbvcm_scene_dlpchildmain},
	trlEmuMenuCallBack_DLPChildErrorSelect,
	{
		&cgbvcm_statechange_dlpchilderrors2dlpchilderror
	}
};


trlEmuMenuState cgbvcmstate_dlpchilderror =
{
	eEmuMenuState_DLPChildError,
	eEmuMenuStateType_WaitInfi,
	&cgbvcm_scene_dlpchilderror,
	1,
	{&cgbvcm_scene_dlpchildmain},
	NULL,
	{
	}
};



trlEmuMenuState cgbvcmstate_dlperrorok =
{
	eEmuMenuState_DLPErrorOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlperrorok,
	1,
	{&cgbvcm_scene_main},
	NULL,
	{
		&cgbvcm_statechange_dlperrokclose,
		&cgbvcm_statechange_dlpnerrokclose
	}
};

trlEmuMenuState cgbvcmstate_dlpallleaveok =
{
	eEmuMenuState_DLPAllLeaveOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlpallleaveok,
	0,
	{NULL},
	NULL,
	{
		&cgbvcm_statechange_dlpallleaveok2standby
	}
};

trlEmuMenuState cgbvcmstate_dlphaveleaveok =
{
	eEmuMenuState_DLPHaveLeaveOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlphaveleaveok,
	1,
	{&cgbvcm_scene_dlpmain},
	NULL,
	{
		&cgbvcm_statechange_dlphaveleaveok2standby,
			&cgbvcm_statechange_dlphaveleaveok2nstandby
	}
};

trlEmuMenuState cgbvcmstate_dlphaveerrorok =
{
	eEmuMenuState_DLPErrorOk,
	eEmuMenuStateType_WaitButton,
	&cgbvcm_scene_dlphaveleaveok,
	0,
	{NULL},
	NULL,
	{
		&cgbvcm_statechange_dlphaveerrorok2standby
	}
};


trlEmuMenuState cgbvcmstate_dlperror =
{
	eEmuMenuState_DLPError,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_dlperror,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPErrorSelect,
	{
		&cgbvcm_statechange_dlperror2dlphaveleaveok,
			&cgbvcm_statechange_dlperror2dlperrorok
	}
};

trlEmuMenuState cgbvcmstate_dlperrorend =
{
	eEmuMenuState_DLPError,
	eEmuMenuStateType_Select,
	&cgbvcm_scene_dlperrorend,
	0,
	{NULL},
	trlEmuMenuCallBack_DLPErrorEndSelect,
	{
		&cgbvcm_statechange_dlperrorend2dlpstandby,
			&cgbvcm_statechange_dlperrorend2dlpmain,
			&cgbvcm_statechange_dlperror2dlpothermenu
	}
};
