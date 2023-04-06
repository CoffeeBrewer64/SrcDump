/**
* @file trlEmuMenuDataAnim.h
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"

/////////////
//standby
enum ECGBVCMStateChange_StandBySelect
{
	eCGBVCMStateChange_StandBySelect2Main = 0,
	eCGBVCMStateChange_StandBySelect2NMainPre,
	eCGBVCMStateChange_StandBySelect2DLPS,
	eCGBVCMStateChange_StandBySelect2DLPMain
};

/////////////
//first time
enum ECGBVCMStateChange_FirstTimeW00
{
	eCGBVCMStateChange_FirstTimeW00_2_W02 = 0,
	eCGBVCMStateChange_FirstTimeW00_2_W01
};

enum ECGBVCMStateChange_FirstTimeW01
{
	eCGBVCMStateChange_FirstTimeW01_2_NMain = 0,
	eCGBVCMStateChange_FirstTimeW01_2_ModeChangeNTOA0
};

enum ECGBVCMStateChange_FirstTimeW02
{
	eCGBVCMStateChange_FirstTimeW02_2_W00 = 0,
	eCGBVCMStateChange_FirstTimeW02_2_W03
};

enum ECGBVCMStateChange_FirstTimeW03
{
	eCGBVCMStateChange_FirstTimeW03_2_W02 = 0,
	eCGBVCMStateChange_FirstTimeW03_2_W01
};


/////////////
//main
enum ECGBVCMStateChange_Main
{
	eCGBVCMStateChange_Main2StandBy = 0,
	eCGBVCMStateChange_MainClose2StanBy,
	eCGBVCMStateChange_Main2Save,
	eCGBVCMStateChange_Main2Reset,
	eCGBVCMStateChange_Main2Load,
	eCGBVCMStateChange_Main2ModeChangeATON0
};

enum EEmuMenuMainStateChange
{
	eEmuMenuMainStateChange_Main2StandBy = 0,
	eEmuMenuMainStateChange_MainClose2StandBy,
	eEmuMenuMainStateChange_Main2Save,
	eEmuMenuMainStateChange_Main2Reset,
	eEmuMenuMainStateChange_Main2Load,
	eEmuMenuMainStateChange_Main2ModeChangeATON0,
	eEmuMenuMainStateChange_Main2DLPPre
};



/////////////
//message
enum ECGBVCMStateChange_Save
{
	eCGBVCMStateChange_Save2Main = 0,
	eCGBVCMStateChange_Save2Saveing
};

enum ECGBVCMStateChange_Load
{
	eCGBVCMStateChange_Load2Main = 0,
	eCGBVCMStateChange_Load2Loading
};

enum ECGBVCMStateChange_Reset
{
	eCGBVCMStateChange_Reset2Main = 0,
	eCGBVCMStateChange_Reset2Reseting
};

enum ECGBVCMStateChange_Saving
{
	eCGBVCMStateChange_Saving2SaveOk = 0
};

enum ECGBVCMStateChange_Loading
{
	eCGBVCMStateChange_Loading2SaveOk = 0
};

enum ECGBVCMStateChange_Resetting
{
	eCGBVCMStateChange_Reseting2MainStandBy = 0
};

enum ECGBVCMStateChange_SaveOk
{
	eCGBVCMStateChange_SaveOk2Main = 0
};

enum ECGBVCMStateChange_LoadOk
{
	eCGBVCMStateChange_LoadOk2Main = 0
};

/////////////
//nmain
enum ECGBVCMStateChange_NMainPre
{
	eCGBVCMStateChange_NMainPre2Nmain = 0,
	eCGBVCMStateChange_NMainPre2FirstTimeW00
};

enum ECGBVCMStateChange_NMain
{
	eCGBVCMStateChange_NMain2StandBy = 0,
	eCGBVCMStateChange_NMainClose2StandBy,
	eCGBVCMStateChange_NMain2Reset,
	eCGBVCMStateChange_NMain2ModeChangeW00,
	eCGBVCMStateChange_NMain2DLPPre
};

enum ECGBVCMStateChange_NReset
{
	eCGBVCMStateChange_NReset2NMain = 0,
	eCGBVCMStateChange_NReset2NReseting
};
enum ECGBVCMStateChange_NReseting
{
	eCGBVCMStateChange_NReseting2NMainStandBy
};

/////////////
//mode change
enum ECGBVCMStateChange_ModeChangeW00
{
	eCGBVCMStateChange_ModeChangeW00_2_NMain = 0,
	ECGBVCMStateChange_ModeChangeW00_2_W01
};

enum ECGBVCMStateChange_ModeChangeW01
{
	eCGBVCMStateChange_ModeChangeW01_2_NMain = 0,
	eCGBVCMStateChange_ModeChangeW01_2_ModeChangeNTOA0
};

enum ECGBVCMStateChange_ModeChange_3_5
{
	eCGBVCMStateChange_ModeChange_3_5_2_Main = 0
};
//////////////////
//
enum ECGBVCMStateChange_BackToMain
{
	eCGBVCMStateChange_BackToMain2Main = 0,
	eCGBVCMStateChange_BackToMain2NMain
};
//////////////////
//
enum
{
	eCGBVCMStateChange_WireLessOff2BackToMain = 0
};

enum ECGBVCMStateChange_NetConnConfirm
{
	eCGBVCMStateChange_NetConnConfirm2NetInit = 0,
	eCGBVCMStateChange_NetConnConfirm2Main
};

enum ECGBVCMStateChange_NetInit
{
	eCGBVCMStateChange_NetInit2DLPBegin = 0,
	eCGBVCMStateChange_NetInit2DLPDLPError
};

enum ECGBVCMStateChange_DLPDLPError
{
	eCGBVCMStateChange_DLPDLPError2StandBy = 0
};

enum ECGBVCMStateChange_DLPPre
{
	eCGBVCMStateChange_NetOpPre2NetConfirm = 0,
	eCGBVCMStateChange_NetOpPre2WireLessOff
};

enum ECGBVCMStateChange_DLPBeginBack
{
	ECGBVCMStateChange_DLPBeginBack2DLPBegin = 0,
	ECGBVCMStateChange_DLPBeginBack2Main,
	eCGBVCMStateChange_DLPBeginBack2DLPDLPError
};

enum ECGBVCMStateChange_DLPBegin
{
	eCGBVCMStateChange_DLPBegin2DLPBeginBack = 0,
	eCGBVCMStateChange_DLPBegin2DLPConn,
	eCGBVCMStateChange_DLPBegin2DLPDLPError
};

enum ECGBVCMStateChange_DLPConn
{
	eCGBVCMStateChange_DLPConn2DLPConnBack = 0,
	eCGBVCMStateChange_DLPConn2DLP,
	eCGBVCMStateChange_DLPConn2DLPDLPError
};

enum ECGBVCMStateChange_DLPConnBack
{
	eCGBVCMStateChange_DLPConnBack2DLPConn = 0,
	eCGBVCMStateChange_DLPConnBack2BackMain,
	eCGBVCMStateChange_DLPConnBack2DLPDLPError
};

enum ECGBVCMStateChange_DLPConnQuit
{
	eCGBVCMStateChange_DLPConnQuit2DLPBegin = 0
};

enum ECGBVCMStateChange_DLP
{
	eCGBVCMStateChange_DLP2DLPNetInit = 0,
	eCGBVCMStateChange_DLP2DLPDLPError,
	eCGBVCMStateChange_DLP2DLPBack
};

enum ECGBVCMStateChange_DLPBack
{
	eCGBVCMStateChange_DLPBack2DLP = 0,
	eCGBVCMStateChange_DLPBack2BackMain,
	eCGBVCMStateChange_DLPBack2DLPDLPError
};


enum ECGBVCMStateChange_DLPNetInit
{
	eCGBVCMStateChange_DLPNetInit2DLPS = 0,
	eCGBVCMStateChange_DLPNetInit2DLPSWithError,
	eCGBVCMStateChange_DLPNetInit2DLPNetInitBack
};

enum ECGBVCMStateChange_DLPNetInitBack
{
	eCGBVCMStateChange_DLPNetInitBack2DLPNetInit = 0,
	eCGBVCMStateChange_DLPNetInitBack2BackMain,
	eCGBVCMStateChange_DLPNetInitBack2DLPDLPError
};

enum ECGBVCMStateChange_DLPS
{
	eCGBVCMStateChange_DLPS2DLPOk = 0,
	eCGBVCMStateChange_DLPS2DLPStandBy,
	eCGBVCMStateChange_DLPS2DLPNStandBy,
	eCGBVCMStateChange_DLPS2DLPWait,
	eCGBVCMStateChange_DLPS2DLPDLPError
};

enum ECGBVCMStateChange_DLPWait
{
	eCGBVCMStateChange_DLPWait2DLPStandBy = 0,
	eCGBVCMStateChange_DLPWait2DLPChildError,
	eCGBVCMStateChange_DLPWait2DLPWaitBack
};

enum ECGBVCMStateChange_DLPWaitBack
{	
	eCGBVCMStateChange_DLPWaitBack2DLPWait = 0,
	eCGBVCMStateChange_DLPWaitBack2DLPChildEndWait,
	eCGBVCMStateChange_DLPWaitBack2DLPChildError
};


enum ECGBVCMStateChange_DLPOk
{
	eCGBVCMStateChange_DLPOk2DLPStandBy = 0,
	eCGBVCMStateChange_DLPOk2DLPNStandBy,
	eCGBVCMStateChange_DLPOk2DLPError
};
enum ECGBVCMStateChange_DLPChildStandBy
{
	eCGBVCMStateChange_DLPChildStandBy2DLPChildMain = 0,
	eCGBVCMStateChange_DLPChildStandBy2DLPChildOtherMenu,
	eCGBVCMStateChange_DLPChildStandBy2DLPChildError
};

enum ECGBVCMStateChange_DLPStandBy
{
	eCGBVCMStateChange_DLPStandBy2DLPMain = 0,
	eCGBVCMStateChange_DLPStandBy2DLPNMain,
	eCGBVCMStateChange_DLPStandBy2DLPOtherMenu,
	eCGBVCMStateChange_DLPStandBy2DLPNOtherMenu,
	eCGBVCMStateChange_DLPStandBy2DLPError,
	eCGBVCMStateChange_DLPStandBy2DLPNError
};

enum ECGBVCMStateChange_DLPChildOtherMenu
{
	eCGBVCMStateChange_DLPChildOtherMenu2ChildDLPStandBy = 0,
	eCGBVCMStateChange_DLPChildOtherMenu2DLPChildErrorSelect,
	eCGBVCMStateChange_DLPChildOtherMenu2DLPChildEndWait
};

enum ECGBVCMStateChange_DLPChildErrorSelect
{
	eCGBVCMStateChange_DLPChildErrorSelect2DLPChildError = 0
};

enum ECGBVCMStateChange_DLPOtherMenu
{
	eCGBVCMStateChange_DLPOtherMenu2DLPStandBy = 0,
	eCGBVCMStateChange_DLPOtherMenu2DLPNStandBy,
	eCGBVCMStateChange_DLPOtherMenu2DLPError
};

enum ECGBVCMStateChange_DLPAllLeaveOk
{
	eCGBVCMStateChange_DLPAllLeaveOk2DLPBegin = 0	
};

enum ECGBVCMStateChange_DLPHaveLeaveOk
{
	eCGBVCMStateChange_DLPHaveLeaveOk2DLPStandBy = 0,
	eCGBVCMStateChange_DLPHaveLeaveOk2ErrorEnd
};

enum ECGBVCMStateChange_DLPMain
{
	eCGBVCMStateChange_DLPMain2DLPStandBy = 0,
	eCGBVCMStateChange_DLPMain2DLPReset,
	eCGBVCMStateChange_DLPMain2DLPEnd,
	eCGBVCMStateChange_DLPMain2DLPError,
	eCGBVCMStateChange_DLPMain2DLPOtherMenu
};

enum ECGBVCMStateChange_DLPNMain
{
	eCGBVCMStateChange_DLPNMain2DLPStandBy = 0,
	eCGBVCMStateChange_DLPNMain2DLPReset,
	eCGBVCMStateChange_DLPNMain2DLPEnd,
	eCGBVCMStateChange_DLPNMain2DLPError
};

enum ECGBVCMStateChange_DlpChildMain
{
	eCGBVCMStateChange_DLPChildMain2DLPChildStandBy = 0,
	eCGBVCMStateChange_DLPChildMain2DLPChildEnd,
	eCGBVCMStateChange_DLPChildMain2DLPChildError,
	eCGBVCMStateChange_DLPChildMain2DLPChildOtherMenu
};

enum ECGBVCMStateChange_DlpChildEnd
{
	eCGBVCMStateChange_DlpChildEnd2DLPChildMain = 0,
	eCGBVCMStateChange_DlpChildEnd2DLPChildEndWait,
	eCGBVCMStateChange_DlpChildEnd2DLPChildError,
	eCGBVCMStateChange_DlpChildEnd2DLPChildOtherMenu
};

enum ECGBVCMStateChange_DLPEnd
{
	eCGBVCMStateChange_DLPEnd2DLPMain = 0,
	eCGBVCMStateChange_DLPEnd2DLPEndS,
	eCGBVCMStateChange_DLPEnd2DLPError
};

enum ECGBVCMStateChange_DLPReset
{
	eCGBVCMStateChange_DLPReset2DLPMain = 0,
	eCGBVCMStateChange_DLPReset2DLPNMain,
	eCGBVCMStateChange_DLPReset2DLPStandBy,
	eCGBVCMStateChange_DLPReset2DLPNStandBy,
	eCGBVCMStateChange_DLPReset2DLPError
};

enum ECGBVCMStateChange_DLPNEnd
{
	eCGBVCMStateChange_DLPNEnd2DLPNMain = 0,
	eCGBVCMStateChange_DLPNEnd2DLPEndS
};

enum ECGBVCMStateChange_DLPEndS
{
	eCGBVCMStateChange_DLPEndS2DLPEndOk = 0
};

enum ECGBVCMStateChange_DLPEndOk
{
	eCGBVCMStateChange_DLPEndOk2StandBy = 0,
	eCGBVCMStateChange_DLPNEndOk2StandBy,
};

enum ECGBVCMStateChange_DLPError
{
	eCGBVCMStateChange_DLPError2DLPHaveLeaveOk = 0,
	eCGBVCMStateChange_DLPError2DLPErrorOk
};

enum ECGBVCMStateChange_DLPErrorOK
{
	eCGBVCMStateChange_DLPErrorOK2StandBy = 0,
	eCGBVCMStateChange_DLPNErrorOK2StandBy
};

enum ECGBVCMStateChange_DLPErrorEnd
{
	eCGBVCMStateChange_DLPErrorEnd2DLPStandBy = 0,
	eCGBVCMStateChange_DLPErrorEnd2DLPMain
};

/////////////
//error
enum EErrVCMStateChange_Begin
{
	eErrVCMStateChange_Begin2NotFormatWait = 0,
	eErrVCMStateChange_Begin2BadFormatOk,
	eErrVCMStateChange_Begin2VFailedOk,
	eErrVCMStateChange_Begin2OPDeniedWait
};

enum EErrVCMStateChange_NotFormatWait
{
	eErrVCMStateChange_NotFormatWait2End = 0
};

enum EErrVCMStateChange_BadFormatOk
{
	eErrVCMStateChange_BadFormatOk2BandForamtWait = 0	
};

enum EErrVCMStateChange_BadFormatWait
{
	eErrVCMStateChange_BadFormatWait2BadForamtDone = 0	
};

enum EErrVCMStateChange_BadFormatDone
{
	eErrVCMStateChange_BadFormatDone2End = 0	
};

enum EErrVCMStateChange_VFailedOk
{
	eErrVCMStateChange_VFailedOk2BandForamtWait = 0	
};

enum EErrVCMStateChange_VFailedWait
{
	eErrVCMStateChange_VFailedWait2BadForamtDone = 0	
};

enum EErrVCMStateChange_VFailedDone
{
	eErrVCMStateChange_VFailedDone2End = 0	
};


///////////////////////////////////
enum EEmuMenuState
{
	eEmuMenuState_Init = 0,
	eEmuMenuState_StandBy,
	eEmuMenuState_StandBySelect,
	eEmuMenuState_Main,
	eEmuMenuState_Save,
	eEmuMenuState_Saveing,
	eEmuMenuState_SaveOk,
	eEmuMenuState_Load,
	eEmuMenuState_Loading,
	eEmuMenuState_LoadOk,
	eEmuMenuState_Reset,
	eEmuMenuState_Reseting,
	eEmuMenuState_NMainPre,
	eEmuMenuState_NMain,
	eEmuMenuState_NReset,
	eEmuMenuState_NReseting,
	eEmuMenuState_ModeChange_W00,
	eEmuMenuState_ModeChange_W01,	
	eEmuMenuState_ModeChange_NTOA0,
	eEmuMenuState_ModeChange_NTOA1,
	eEmuMenuState_ModeChange_ATON0,
	eEmuMenuState_FirstTime_W00,
	eEmuMenuState_FirstTime_W01,
	eEmuMenuState_FirstTime_W02,
	eEmuMenuState_FirstTime_W03,
	eEmuMenuState_Error_Begin,
	eEmuMenuState_Error_NotFormatWait,
	eEmuMenuState_Error_BadFormatOk,
	eEmuMenuState_Error_BadFormatWait,
	eEmuMenuState_Error_BadFormatDone,
	eEmuMenuState_Error_VFailedOk,
	eEmuMenuState_Error_VFailedWait,
	eEmuMenuState_Error_VFailedDone,
	eEmuMenuState_Error_OPDeniedWait,
	eEmuMenuState_Error_End,
	eEmuMenuState_BackToMain,
	eEmuMenuState_NetOpPre,
	eEmuMenuState_NetConnConfirm,
	eEmuMenuState_NetInit,
	eEmuMenuState_DLPDLPError,
	eEmuMenuState_DLPBegin,
	eEmuMenuState_DLPBeginBack,
	eEmuMenuState_DLPConn,
	eEmuMenuState_DLPConnBack,	
	eEmuMenuState_DLP,
	eEmuMenuState_DLPBack,
	eEmuMenuState_DLPNetInit,
	eEmuMenuState_DLPNetInitBack,
	eEmuMenuState_DLPS,
	eEmuMenuState_DLPWait,
	eEmuMenuState_DLPWaitBack,
	eEmuMenuState_DLPOk,	
	eEmuMenuState_DLPChildStandBy,
	eEmuMenuState_DLPChildMain,
	eEmuMenuState_DLPChildOtherMenu,	
	eEmuMenuState_DLPChildEnd,
	eEmuMenuState_DLPChildEndWait,
	eEmuMenuState_DLPChildErrorS,
	eEmuMenuState_DLPChildError,
	eEmuMenuState_DLPStandBy,
	eEmuMenuState_DLPMain,
	eEmuMenuState_DLPNMain,
	eEmuMenuState_DLPReset,	
	eEmuMenuState_DLPEnd,
	eEmuMenuState_DLPNEnd,
	eEmuMenuState_DLPEndS,
	eEmuMenuState_DLPEndOk,
	eEmuMenuState_DLPEndWait,
	eEmuMenuState_DLPOtherMenu,
	eEmuMenuState_DLPError,
	eEmuMenuState_DLPHaveLeaveOk,
	eEmuMenuState_DLPErrorOk,
	eEmuMenuState_DLPHaveErrorOk,
	eEmuMenuState_DLPAllLeaveOk,
	eEmuMenuState_DLPErrorEnd,
	eEmuMenuStateNum
};

extern trlEmuMenuState cgbvcmstate_init;
extern trlEmuMenuState cgbvcmstate_standby;
extern trlEmuMenuState cgbvcmstate_standbyselect;
extern trlEmuMenuState cgbvcmstate_main;
extern trlEmuMenuState cgbvcmstate_save;
extern trlEmuMenuState cgbvcmstate_saveing;
extern trlEmuMenuState cgbvcmstate_saveok;
extern trlEmuMenuState cgbvcmstate_load;
extern trlEmuMenuState cgbvcmstate_loading;
extern trlEmuMenuState cgbvcmstate_loadok;
extern trlEmuMenuState cgbvcmstate_reset;
extern trlEmuMenuState cgbvcmstate_reseting;
extern trlEmuMenuState cgbvcmstate_nmainpre;
extern trlEmuMenuState cgbvcmstate_nmain;
extern trlEmuMenuState cgbvcmstate_nreset;
extern trlEmuMenuState cgbvcmstate_nreseting;
extern trlEmuMenuState cgbvcmstate_modechangew00;
extern trlEmuMenuState cgbvcmstate_modechangew01;
extern trlEmuMenuState cgbvcmstate_modechangentoa0;
extern trlEmuMenuState cgbvcmstate_modechangentoa1;
extern trlEmuMenuState cgbvcmstate_modechangeaton0;

extern trlEmuMenuState cgbvcmstate_firsttime_w00;
extern trlEmuMenuState cgbvcmstate_firsttime_w01;
extern trlEmuMenuState cgbvcmstate_firsttime_w02;
extern trlEmuMenuState cgbvcmstate_firsttime_w03;

extern trlEmuMenuState errvcmstate_begin;
extern trlEmuMenuState errvcmstate_notformatwait;
extern trlEmuMenuState errvcmstate_badformatok;
extern trlEmuMenuState errvcmstate_badformatwait;
extern trlEmuMenuState errvcmstate_badformatdone;
extern trlEmuMenuState errvcmstate_vfailedok;
extern trlEmuMenuState errvcmstate_vfailedwait;
extern trlEmuMenuState errvcmstate_vfaileddone;
extern trlEmuMenuState errvcmstate_opdeniedwait;
extern trlEmuMenuState errvcmstate_end;

extern trlEmuMenuState cgbvcmstate_backtomain;
extern trlEmuMenuState cgbvcmstate_netoppre;
extern trlEmuMenuState cgbvcmstate_netconnconfirm;
extern trlEmuMenuState cgbvcmstate_netinit;
extern trlEmuMenuState cgbvcmstate_dlpdlperror;

extern trlEmuMenuState cgbvcmstate_dlpbegin;
extern trlEmuMenuState cgbvcmstate_dlpbeginback;
extern trlEmuMenuState cgbvcmstate_dlpconn;
extern trlEmuMenuState cgbvcmstate_dlpconnback;

extern trlEmuMenuState cgbvcmstate_dlpdlperror;
extern trlEmuMenuState cgbvcmstate_dlp;
extern trlEmuMenuState cgbvcmstate_dlpback;
extern trlEmuMenuState cgbvcmstate_dlpnetinit;
extern trlEmuMenuState cgbvcmstate_dlpnetinitback;
extern trlEmuMenuState cgbvcmstate_dlps;
extern trlEmuMenuState cgbvcmstate_dlpwait;
extern trlEmuMenuState cgbvcmstate_dlpwaitback;
extern trlEmuMenuState cgbvcmstate_dlpok;
extern trlEmuMenuState cgbvcmstate_dlpstandby;
extern trlEmuMenuState cgbvcmstate_dlpchildstandby;
extern trlEmuMenuState cgbvcmstate_dlpmain;
extern trlEmuMenuState cgbvcmstate_dlpnmain;
extern trlEmuMenuState cgbvcmstate_dlpreset;
extern trlEmuMenuState cgbvcmstate_dlpchildmain;
extern trlEmuMenuState cgbvcmstate_dlpend;
extern trlEmuMenuState cgbvcmstate_dlpnend;
extern trlEmuMenuState cgbvcmstate_dlpchildend;
extern trlEmuMenuState cgbvcmstate_dlpends;
extern trlEmuMenuState cgbvcmstate_dlpendok;
extern trlEmuMenuState cgbvcmstate_dlpendwait;
extern trlEmuMenuState cgbvcmstate_dlpchildendwait;
extern trlEmuMenuState cgbvcmstate_dlpothermenu;
extern trlEmuMenuState cgbvcmstate_dlpchildothermenu;
extern trlEmuMenuState cgbvcmstate_dlpchilderrors;
extern trlEmuMenuState cgbvcmstate_dlpchilderror;
extern trlEmuMenuState cgbvcmstate_dlphaveleaveok;
extern trlEmuMenuState cgbvcmstate_dlphaveerrorok;
extern trlEmuMenuState cgbvcmstate_dlpallleaveok;
extern trlEmuMenuState cgbvcmstate_dlperrorok;
extern trlEmuMenuState cgbvcmstate_dlperror;
extern trlEmuMenuState cgbvcmstate_dlperrorend;

