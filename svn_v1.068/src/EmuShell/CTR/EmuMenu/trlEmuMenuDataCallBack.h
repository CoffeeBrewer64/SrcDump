/**
* @file trlEmuMenuDataCallBack.h
* @author zhfang
* @date 2011.07.04
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"

#define TRL_EMUMENU_CALLBACK_END 0
#define TRL_EMUMENU_CALLBACK_RUN 1

enum EEmuMenuCallBackState
{
	eEmuMenuCallBackState_Wait = -1,
	eEmuMenuCallBackState_Done = 0	
};

///////////////////
//select the state to change
s32 trlEmuMenuCallBack_StandySelect();
s32 trlEmuMenuCallBack_ErrorSelect();
s32 trlEmuMenuCallBack_NMainPreSelect();

s32 trlEmuMenuCallBack_BackToMainSelect();

s32 trlEmuMenuCallBack_DLPSSelect();
s32 trlEmuMenuCallBack_NetOpPreSelect();
s32 trlEmuMenuCallBack_DLPBeginSelect();
s32 trlEmuMenuCallBack_DLPBeginBackSelect();
s32 trlEmuMenuCallBack_DLPConnBackSelect();
s32 trlEmuMenuCallBack_DLPStandBySelect();
s32 trlEmuMenuCallBack_DLPChildStandBySelect();

s32 trlEmuMenuCallBack_DLPEndsSelect();
s32 trlEmuMenuCallBack_DLPOkSelect();
s32 trlEmuMenuCallBack_NetInitSelect();

s32 trlEmuMenuCallBack_DLPErrorSelect();
s32 trlEmuMenuCallBack_DLPErrorEndSelect();
s32 trlEmuMenuCallBack_DLPErrorOkSelect();

s32 trlEmuMenuCallBack_DLPHaveLeaveOkSelect();
s32 trlEmuMenuCallBack_DLPEndOkSelect();

s32 trlEmuMenuCallBack_DLPResetYesSelect();
s32 trlEmuMenuCallBack_DLPResetNoSelect();
s32 trlEmuMenuCallBack_DLPOkWaitSelect();

s32 trlEmuMenuCallBack_DLPMainSelect();
s32 trlEmuMenuCallBack_DLPNMainSelect();
s32 trlEmuMenuCallBack_DLPEndSelect();
s32 trlEmuMenuCallBack_DLPResetSelect();
s32 trlEmuMenuCallBack_DLPChildMainSelect();
s32 trlEmuMenuCallBack_DLPChildEndSelect();
s32 trlEmuMenuCallBack_DLPChildEndWaitProc();
s32 trlEmuMenuCallBack_DLPChildErrorSelect();
///////////////////
//open thead and wait
s32 trlEmuMenuCallBack_EndProc();

s32 trlEmuMenuCallBack_ProcSave();
s32 trlEmuMenuCallBack_ProcLoad();
s32 trlEmuMenuCallBack_ProcReset();
s32 trlEmuMenuCallBack_ProcNotFormat();
s32 trlEmuMenuCallBack_ProcBadFormat();


///////////////////
//wait some condition been fit
s32 trlEmuMenuCallBack_DLPWait();
s32 trlEmuMenuCallBack_DLPWaitBack();
s32 trlEmuMenuCallBack_ProcNetInit();
s32 trlEmuMenuCallBack_ProcNetInitBack();
void trlEmuMenuCallBack_MakeDLPName();
s32 trlEmuMenuCallBack_ProcDLP();
s32  trlEmuMenuCallBack_ProcDLPBack();
s32 trlEmuMenuCallBakc_LoadFade_FadeIn1End();
s32 trlEmuMenuCallBakc_LoadFade_FadeIn2End();
s32 trlEmuMenuCallBakc_LoadFade_FadeOutEnd();


s32 trlEmuMenuCallBack_DLPOtherMenu();
s32 trlEmuMenuCallBack_DLPChildOtherMenu();

///////////////////
//direct do some thing

void trlEmuNetworkWaitThreadEnd();

void trlEmuMenuCallBack_PiaCommonInit();
void trlEmuMenuCallBack_SetDLPChildErrorMessage();
void trlEmuMenuCallBack_SetDLPErrorMessage();
void trlEmuMenuCallBack_SetDLPErrorOkMessage();
void trlEmuMenuCallBack_SetDLPDLPErrorOkMessage();

void trlEmuMenuCallBack_SetMenuNormalMode();
void trlEmuMenuCallBack_SetMenuAdvMode();
void trlEmuMenuCallBack_UpdateSavePreview();
void trlEmuMenuCallBack_SetNetMode();
void trlEmuMenuCallBack_SetNoneNetMode();

void trlEmuMenuCallBack_CloseDLPWarning();

void trlEmuMenuCallBack_Init4PMessage();
void trlEmuMenuCallBack_InitNetChild();
void trlEmuMenuCallBack_InitDLP();
void trlEmuMenuCallBack_CloseDLP();
void trlEmuMenuCallBack_ReleaseDLP();
void trlEmuMenuCallBack_BeginTrans();
void trlEmuMenuCallBack_EndDLPMenu();
void trlEmuMenuCallBack_EnableHomeButton();

void trlEmuMenuCallBack_AllLeaveOk();
void trlEmuMenuCallBack_ErrorHaveLeaveOk();
void trlEmuMenuCallBack_CloseNet();

void trlEmuMenuCallBack_NetCommand(u32 command);
void trlEmuMenuCallBack_NetSetState(u32 nState);


void trlEmuMenuCallBack_ChangeCommonWNDMessage();
void trlEmuMenuCallBack_ChangeErrorMessage();

void trlEmuMenuCallBack_Convert4PMessage();

#define HVC_VCM_00 38
#define HVC_VCM_END 47
#define HVC_VCM_4P_00 48
#define HVC_VCM_4P_END 57

#define HVC_VCM_07 45
#define HVC_VCM_4P_07 55

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
#define HVC_VCM_01 46
#define HVC_VCM_02 47
#else
#define HVC_VCM_01 39
#define HVC_VCM_02 40
#endif

void trlEmuMenuCallBack_SetMainDLBtMessage(u32 msg_no);

#define ERR_MSG_00 4
#define ERR_MSG_01 5
#define ERR_MSG_02 6
#define ERR_MSG_03 7
#define ERR_MSG_04 8
#define ERR_MSG_05 9
#define ERR_MSG_06 10
#define ERR_MSG_07 11
#define ERR_MSG_08 12
#define ERR_MSG_09 13
#define ERR_MSG_10 14
#define ERR_MSG_11 15

void trlEmuMenuCallBakc_SetErrorMessageYN(u32 msg_no);
void trlEmuMenuCallBakc_SetErrorMessageOK(u32 msg_no);
void trlEmuMenuCallBakc_SetErrorMessageWait(u32 msg_no);



#define WND_MSG_00 3
#define WND_MSG_01 4
#define WND_MSG_02 5
#define WND_MSG_03 6
#define WND_MSG_04 7
#define WND_MSG_05 8
#define WND_MSG_06 9
#define WND_MSG_07 10
#define WND_MSG_08 11
#define WND_MSG_09 12
#define WND_MSG_10 13

/////////////////////
//if this have som echange, please see trlEmuMenuCallBack_DLPMessage2PTo4P
#define HVC_WND_00 4
#define HVC_WND_01 5
#define HVC_WND_02 6
#define HVC_WND_03 7
#define HVC_WND_04 8
#define HVC_WND_05 9
#define HVC_WND_06 10
#define HVC_WND_07 11
#define HVC_WND_08 12
#define HVC_WND_09 13
#define HVC_WND_10 14
#define HVC_WND_11 15
#define HVC_WND_12 16

#define HVC_WND_4P_00 17
#define HVC_WND_4P_12 29


void trlEmuMenuCallBakc_SetDLPMessageYN(u32 msg_no);
void trlEmuMenuCallBakc_SetDLPMessageOK(u32 msg_no);
void trlEmuMenuCallBakc_SetDLPMessageWait(u32 msg_no);



void trlEmuMenuCallBakc_LoadFade_To_FadeIn1();
void trlEmuMenuCallBakc_LoadFade_To_FadeIn2();
void trlEmuMenuCallBakc_LoadFade_To_FadeOut();


