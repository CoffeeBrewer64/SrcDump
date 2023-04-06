/**
* @file trlEmuMenuDataCallBack.cpp
* @author zhfang
* @date 2011.07.04
* @brief trlEmuMenu
*/
#include "../../trlEmuShell.h"
#include "../../trlEmuShellSuspend.h"
#include "../../trlEmuShellStruct.h"
#include "../../trlEmuShellData.h"
#include "../../trlEmuShellNetWork.h"
#include "../trlEmuShellDLP.h"
#include "trlEmuMenu.h"
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataButton.h"
#include "trlEmuMenuDataLayout.h"
#include "trlEmuMenuDataScene.h"
#include "trlEmuMenuDataState.h"
#include "trlEmuMenuDataCallBack.h"
/** @name Global Variable */
//@{
extern CEmuMenu g_hTrlEmuMenu;
extern u32 g_bVCMSkipFadeIn;
extern u32 g_bVCMHaveBreakSave;
extern u32 g_bVCMHaveSave;

nn::os::Thread g_VCMThread;
u32 g_VCMThreadIsRun = 0;
//@}

/** @brief VCM Call Back Select func of error proc */
s32 trlEmuMenuCallBack_ErrorSelect()
{
	extern s32 g_nFileErrorResult;
	switch(g_nFileErrorResult)
	{
	case TRL_FILE_NOTFORMATTED:
		NN_LOG("trlEmuMenuCallBack_ErrorSelect NotFormat\n");
		return eErrVCMStateChange_Begin2NotFormatWait;
	case TRL_FILE_BADFORMAT:
		NN_LOG("trlEmuMenuCallBack_ErrorSelect Badormat\n");
		return eErrVCMStateChange_Begin2BadFormatOk;
	case TRL_FILE_VERIFICATIONFAILED:
	case TRL_FILE_NOTFOUND:
		NN_LOG("trlEmuMenuCallBack_ErrorSelect VFailed\n");
		return eErrVCMStateChange_Begin2VFailedOk;
	case TRL_FILE_OPERATIONDENIED:
		NN_LOG("trlEmuMenuCallBack_ErrorSelect OPDenied\n");
		return eErrVCMStateChange_Begin2OPDeniedWait;
	default:
		NN_LOG("trlEmuMenuCallBack_ErrorSelect OPDenied\n");
		return eErrVCMStateChange_Begin2NotFormatWait;
	}
}

/** @brief VCM Call Back Select func of NMainPre */
s32 trlEmuMenuCallBack_NMainPreSelect()
{
	if(g_bVCMHaveBreakSave)
		return eCGBVCMStateChange_NMainPre2Nmain;
	else
	{
		if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Init)
		{
			if(g_sEmuShellBuffer.nBackupDataSize == 0)
			{
				g_hTrlEmuMenu.SetNMode();
			}
			NN_LOG("select to firsttime\n");
			return eCGBVCMStateChange_NMainPre2FirstTimeW00;
		}
		else
		{			
			NN_LOG("select to nmain\n");
			return eCGBVCMStateChange_NMainPre2Nmain;
		}
	}
}

/** @brief VCM Call Back Select func of StandBy */
s32 trlEmuMenuCallBack_StandySelect()
{
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_PARENT
	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
	{
		cgbvcm_bt_main_load.mEnable = 0;
		cgbvcm_layout_main.mpButtonSet->bindanim("N_LoadBtn_00", eMainAnim_visible_on_00);
		cgbvcm_bt_main_save.mEnable = 0;
		cgbvcm_layout_main.mpButtonSet->bindanim("N_SaveBtn_00", eMainAnim_visible_on_00);
		return eCGBVCMStateChange_StandBySelect2DLPMain;
	}
#endif

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	return eCGBVCMStateChange_StandBySelect2DLPS;
#else

	cgbvcm_bt_main_save.mEnable = 1;
	cgbvcm_layout_main.mpButtonSet->bindanim("N_SaveBtn_00", eMainAnim_visible_off_00);

	g_hTrlEmuMenu.beHaveSave = g_bVCMHaveSave;	
	if(g_hTrlEmuMenu.beHaveSave == 1)
	{
		cgbvcm_bt_main_load.mEnable = 1;
		cgbvcm_layout_main.mpButtonSet->bindanim("N_LoadBtn_00", eMainAnim_visible_off_00);
	}
	else
	{
		cgbvcm_bt_main_load.mEnable = 0;
		cgbvcm_layout_main.mpButtonSet->bindanim("N_LoadBtn_00", eMainAnim_visible_on_00);
	}

	g_hTrlEmuMenu.updateSavePreview();
	
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)
		return eCGBVCMStateChange_StandBySelect2NMainPre;
	else if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Advance)
		return eCGBVCMStateChange_StandBySelect2Main;
	else 
	{
		if(g_sEmuShellBuffer.nBackupDataSize == 0)
		{
			g_hTrlEmuMenu.SetAMode();
			return eCGBVCMStateChange_StandBySelect2Main;
		}
		else
		{
			NN_LOG("select to normal\n");
			return eCGBVCMStateChange_StandBySelect2NMainPre;
		}
	}
#endif
}

/** @brief VCM Call Back selct for DLP End*/
s32 trlEmuMenuCallBack_DLPSSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		trlEmuShellNetworkExit();
		return eCGBVCMStateChange_DLPS2DLPDLPError;
	}

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	NN_LOG("trlEmuMenuCallBack_DLPSSelect Child To Wait\n");
	return eCGBVCMStateChange_DLPS2DLPWait;
#else

	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)
		return eCGBVCMStateChange_DLPS2DLPNStandBy;
	else
		return eCGBVCMStateChange_DLPS2DLPStandBy;
	//return eCGBVCMStateChange_DLPS2DLPOk;
#endif
}
/** @brief VCM Call Back select for BackToMain*/
s32 trlEmuMenuCallBack_BackToMainSelect()
{
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)
		return eCGBVCMStateChange_BackToMain2NMain;
	else
		return eCGBVCMStateChange_BackToMain2Main;
}

/** @brief VCM Call Back selct for DLP pre*/
s32 trlEmuMenuCallBack_NetOpPreSelect()
{
	return eCGBVCMStateChange_NetOpPre2NetConfirm;
}

/** @brief VCM Call Back selct for DLP Begin*/
s32 trlEmuMenuCallBack_DLPBeginSelect()
{	
	if(g_trlEmuDLPDLPError != TRL_EMU_DLPDLP_ERROR_NONE)
		return eCGBVCMStateChange_DLPBegin2DLPDLPError;

	if(trlEmuDLPGetConnPlayerNum() > 1)
		return eCGBVCMStateChange_DLPBegin2DLPConn;
	return eEmuMenuCallBackState_Wait;
}

/** @brief VCM Call Back selct for DLP Begin*/
s32 trlEmuMenuCallBack_DLPBeginBackSelect()
{	
	if(g_trlEmuDLPDLPError != TRL_EMU_DLPDLP_ERROR_NONE)
		return eCGBVCMStateChange_DLPBeginBack2DLPDLPError;
	return eEmuMenuCallBackState_Wait;
}

/** @brief VCM Call Back selct for DLP Begin*/
s32 trlEmuMenuCallBack_DLPConnBackSelect()
{	
	if(g_trlEmuDLPDLPError != TRL_EMU_DLPDLP_ERROR_NONE)
		return eCGBVCMStateChange_DLPConnBack2DLPDLPError;
	return eEmuMenuCallBackState_Wait;
}


s32 trlEmuMenuCallBack_NetInitSelect()
{
	s32 r = trlEmuDLPInit();		
	if(r == eEmuDLPResult_Success)
		return eCGBVCMStateChange_NetInit2DLPBegin;
	else if(r == eEmuDLPResult_WireLessOff)
		return eCGBVCMStateChange_NetInit2DLPDLPError;
	return eCGBVCMStateChange_NetInit2DLPDLPError;
}

s32 trlEmuMenuCallBack_DLPOkSelect()
{	
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)		
		return eCGBVCMStateChange_DLPOk2DLPNStandBy;
	else		
		return eCGBVCMStateChange_DLPOk2DLPStandBy;	
}

s32 trlEmuMenuCallBack_DLPOkWaitSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		NN_LOG("trlEmuMenuCallBack_DLPOkWaitSelect to Error\n");
		return eCGBVCMStateChange_DLPOk2DLPError;
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPChildStandBySelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NETWORK)
			return eCGBVCMStateChange_DLPChildStandBy2DLPChildError;
		else
		{
			trlEmuMenuCallBack_SetDLPErrorMessage();
			return eCGBVCMStateChange_DLPChildStandBy2DLPChildOtherMenu;
		}
	}

	if(g_bTrlEmuNetRole == eTrlEmuNetMaster)
	{	
		return eCGBVCMStateChange_DLPChildStandBy2DLPChildMain;
	}
	else if(g_bTrlEmuNetRole == eTrlEmuNetSlave)
	{
		NN_LOG("trlEmuMenuCallBack_DLPChildStandBySelect to other\n");		
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_04);
		return eCGBVCMStateChange_DLPChildStandBy2DLPChildOtherMenu;
	}
	NN_LOG("trlEmuMenuCallBack_DLPChildStandBySelect  bad select\n");
	return eCGBVCMStateChange_DLPChildStandBy2DLPChildOtherMenu;
}

s32 trlEmuMenuCallBack_DLPStandBySelect()
{
	cgbvcm_bt_main_load.mEnable = 0;
	cgbvcm_layout_main.mpButtonSet->bindanim("N_LoadBtn_00", eMainAnim_visible_on_00);
	cgbvcm_bt_main_save.mEnable = 0;
	cgbvcm_layout_main.mpButtonSet->bindanim("N_SaveBtn_00", eMainAnim_visible_on_00);

	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)
			return eCGBVCMStateChange_DLPStandBy2DLPNError;
		else
			return eCGBVCMStateChange_DLPStandBy2DLPError;
	}

	if(g_bTrlEmuNetRole == eTrlEmuNetMaster)
	{	
		if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)
		{
			NN_LOG("trlEmuMenuCallBack_DLPStandBySelect DLPNMain\n");
			return eCGBVCMStateChange_DLPStandBy2DLPNMain;
		}
		else
		{
			NN_LOG("trlEmuMenuCallBack_DLPStandBySelect DLPMain\n");
			return eCGBVCMStateChange_DLPStandBy2DLPMain;		
		}
	}
	else if(g_bTrlEmuNetRole == eTrlEmuNetSlave)
	{
		NN_LOG("trlEmuMenuCallBack_DLPStandBySelect to other\n");		
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_04);
		if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)
			return eCGBVCMStateChange_DLPStandBy2DLPNOtherMenu;
		else
			return eCGBVCMStateChange_DLPStandBy2DLPOtherMenu;
	}
	NN_LOG("trlEmuMenuCallBack_DLPStandBySelect  bad select\n");
	return eCGBVCMStateChange_DLPStandBy2DLPOtherMenu;
}

s32 trlEmuMenuCallBack_DLPEndsSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		trlEmuMenuCallBack_CloseNet();
		return eCGBVCMStateChange_DLPEndS2DLPEndOk;
	}

	if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_WAIT_TO_QUIT)
	{
		trlEmuMenuCallBack_CloseNet();
		return eCGBVCMStateChange_DLPEndS2DLPEndOk;
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPErrorSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NETWORK)
	{
		NN_LOG("trlEmuMenuCallBack_DLPErrorSelect eCGBVCMStateChange_DLPError2DLPErrorOk\n");
		if(trlEmuShellNetworkGetSelfPlayerState() <= PLAYER_STATE_SYNC_DONE)
			trlEmuMenuCallBakc_SetErrorMessageOK(ERR_MSG_08);
		else
			trlEmuMenuCallBakc_SetErrorMessageOK(ERR_MSG_09);
		trlEmuShellNetworkExit();
		return eCGBVCMStateChange_DLPError2DLPErrorOk;
	}
	else
	{
		NN_LOG("trlEmuMenuCallBack_DLPErrorSelect eCGBVCMStateChange_DLPError2DLPHaveLeaveOk\n");
		trlEmuMenuCallBack_SetDLPErrorOkMessage();
		trlEmuShellNetworkExit();
		return eCGBVCMStateChange_DLPError2DLPHaveLeaveOk;
	}
}

s32 trlEmuMenuCallBack_DLPErrorEndSelect()
{
	if(g_hTrlEmuMenu.bHaveNetErrorInMenu)
	{
		g_hTrlEmuMenu.bHaveNetErrorInMenu = 0;
		NN_LOG("trlEmuMenuCallBack_DLPErrorEndSelect to eCGBVCMStateChange_DLPErrorEnd2DLPMain\n");
		return eCGBVCMStateChange_DLPErrorEnd2DLPMain;
	}
	NN_LOG("trlEmuMenuCallBack_DLPErrorEndSelect to eCGBVCMStateChange_DLPErrorEnd2DLPStandBy\n");
	return eCGBVCMStateChange_DLPErrorEnd2DLPStandBy;
	
}
s32 trlEmuMenuCallBack_DLPHaveLeaveOkSelect()
{
	NN_LOG("trlEmuMenuCallBack_DLPHaveLeaveOkSelect\n");
	if(g_hTrlEmuMenu.bHaveNetError == 1)
	{		
		return eCGBVCMStateChange_DLPHaveLeaveOk2ErrorEnd;
	}
	return eCGBVCMStateChange_DLPHaveLeaveOk2DLPStandBy;	
}

s32 trlEmuMenuCallBack_DLPEndOkSelect()
{
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)		
		return eCGBVCMStateChange_DLPNEndOk2StandBy;
	else		
		return eCGBVCMStateChange_DLPEndOk2StandBy;	
}

s32 trlEmuMenuCallBack_DLPResetYesSelect()
{
	trlEmuMenuCallBack_NetSetState(PLAYER_COMMAND_RESET);
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)		
		return eCGBVCMStateChange_DLPReset2DLPNStandBy;
	else		
		return eCGBVCMStateChange_DLPReset2DLPStandBy;	
}


s32 trlEmuMenuCallBack_DLPResetNoSelect()
{
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)		
		return eCGBVCMStateChange_DLPReset2DLPNMain;
	else		
		return eCGBVCMStateChange_DLPReset2DLPMain;	
}

s32 trlEmuMenuCallBack_DLPErrorOkSelect()
{
	if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)		
		return eCGBVCMStateChange_DLPNErrorOK2StandBy;
	else		
		return eCGBVCMStateChange_DLPErrorOK2StandBy;	
}

s32 trlEmuMenuCallBack_DLPMainSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		return eCGBVCMStateChange_DLPMain2DLPError;
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPNMainSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		return eCGBVCMStateChange_DLPNMain2DLPError;
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPEndSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		return eCGBVCMStateChange_DLPEnd2DLPError;
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPResetSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		return eCGBVCMStateChange_DLPReset2DLPError;
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPChildMainSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NETWORK)
			return eCGBVCMStateChange_DLPChildMain2DLPChildError;
		else
		{
			trlEmuMenuCallBack_SetDLPErrorMessage();
			trlEmuShellNetworkExit();
			return eCGBVCMStateChange_DLPChildMain2DLPChildOtherMenu;
		}
	}
	return eEmuMenuCallBackState_Wait;
}
s32 trlEmuMenuCallBack_DLPChildEndSelect()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NETWORK)
			return eCGBVCMStateChange_DlpChildEnd2DLPChildError;
		else
		{
			trlEmuMenuCallBack_SetDLPErrorMessage();
			trlEmuShellNetworkExit();
			return eCGBVCMStateChange_DlpChildEnd2DLPChildOtherMenu;
		}
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPChildEndWaitProc()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		trlEmuMenuCallBack_CloseNet();
		trlEmuShellSuspendEnableHomeButton();		
	}
	if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_WAIT_TO_QUIT)
	{
		trlEmuMenuCallBack_CloseNet();
		trlEmuShellSuspendEnableHomeButton();
	}
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPChildErrorSelect()
{
	trlEmuMenuCallBakc_SetErrorMessageWait(ERR_MSG_11);
	trlEmuShellNetworkExit();
	return eCGBVCMStateChange_DLPChildErrorSelect2DLPChildError;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void trlEmuNetworkWaitThreadEnd()
{
	if(g_VCMThreadIsRun == 1)
	{
		g_VCMThread.Join();
		g_VCMThread.Finalize();
		g_VCMThreadIsRun = 0;
	}
}

void trlEmuNetworkInitThreadFunc()
{
	trlEmuShellNetworkInit(1);
}

void trlEmuMenuCallBack_PiaCommonInit()
{
	void triPiaCommonInit();
	triPiaCommonInit();
	g_VCMThreadIsRun = 1;
	g_VCMThread.StartUsingAutoStack(trlEmuNetworkInitThreadFunc, 4096);
}

/** @brief VCM Call Back proc func of updatesavepreview */
void trlEmuMenuCallBack_UpdateSavePreview()
{
	g_hTrlEmuMenu.updateSavePreview();
}

/** @brief VCM Call Back proc func of set vcmmode to normal */
void trlEmuMenuCallBack_SetMenuNormalMode()
{	
	g_hTrlEmuMenu.beNormal = 1;
	g_hTrlEmuMenu.SetNMode();
}

/** @brief VCM Call Back proc func of set vcmmode to advance */
void trlEmuMenuCallBack_SetMenuAdvMode()
{
	g_hTrlEmuMenu.beNormal = 0;
	g_hTrlEmuMenu.SetAMode();
}


/** @brief VCM Call Back func for set net mode open*/
void trlEmuMenuCallBack_SetNetMode()
{
	g_vcmstate_netmode = eVCMStateNetMode_Net;
	NN_LOG("g_vcmstate_netmode = %d\n", g_vcmstate_netmode);
}

/** @brief VCM Call Back func for set net mode none*/
void trlEmuMenuCallBack_SetNoneNetMode()
{
	g_vcmstate_netmode = eVCMStateNetMode_None;
	NN_LOG("g_vcmstate_netmode = %d\n", g_vcmstate_netmode);
}

void trlEmuMenuCallBack_SetDLPDLPErrorOkMessage()
{
	trlEmuMenuCallBakc_SetDLPMessageOK(HVC_WND_08);
}

void trlEmuMenuCallBack_SetDLPErrorOkMessage()
{
	if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_EEEOR_STATE_MASTERLEAVE)
	{	
		trlEmuMenuCallBakc_SetDLPMessageOK(HVC_WND_06);
		trlEmuShellNetworkExit();
	}
	else if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_LEAVE)
	{	
		trlEmuMenuCallBakc_SetDLPMessageOK(HVC_WND_09);
		trlEmuShellNetworkExit();
	}	
}

void trlEmuMenuCallBack_SetDLPChildErrorMessage()
{
	if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_EEEOR_STATE_MASTERLEAVE)
	{	
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_07);
		trlEmuShellNetworkExit();
	}
	else if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_LEAVE)
	{	
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_07);
		trlEmuShellNetworkExit();
	}
	else if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NETWORK)
	{
		trlEmuMenuCallBakc_SetDLPMessageWait(ERR_MSG_11);
		trlEmuShellNetworkExit();
	}

}

void trlEmuMenuCallBack_SetDLPErrorMessage()
{
	if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_EEEOR_STATE_MASTERLEAVE)
	{	
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_07);
		trlEmuShellNetworkExit();
	}
	else if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_LEAVE)
	{	
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_07);
		trlEmuShellNetworkExit();
	}
	else if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NETWORK)
	{
		trlEmuMenuCallBakc_SetDLPMessageWait(HVC_WND_08);
		trlEmuShellNetworkExit();
	}
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
/** @brief VCM Call Back proc func for end of thread*/
s32 trlEmuMenuCallBack_EndProc()
{
	if(!g_VCMThread.IsAlive())
	{
		NN_LOG("Thread End\n");
		g_VCMThread.Join();
		g_VCMThread.Finalize();
		return TRL_EMUMENU_CALLBACK_END;
	}
	return TRL_EMUMENU_CALLBACK_RUN;
}


/** @brief VCM Thread func for save*/
void savethread()
{
	if(g_hTrlEmuMenu.pSaveFunc != NULL)
	{
		trlEmuShellsupendDisableSleep();
		g_hTrlEmuMenu.bSaveSuccess = g_hTrlEmuMenu.pSaveFunc(0);
		trlEmuShellsupendEnableSleep();

		if(g_hTrlEmuMenu.bSaveSuccess)
		{
			g_hTrlEmuMenu.beHaveSave = 1;
			cgbvcm_bt_main_load.mEnable = 1;
		}		
	}
}
/** @brief VCM Thread func for load*/
void loadthread()
{	
	if(g_hTrlEmuMenu.pLoadFunc!= NULL)
	{
		g_hTrlEmuMenu.bLoadSuccess = g_hTrlEmuMenu.pLoadFunc(0);		
		if(g_hTrlEmuMenu.bLoadSuccess > 0)
		{
			if(g_hTrlEmuMenu.pResumeFunc != NULL)
				g_hTrlEmuMenu.pResumeFunc();
		}
	}
	trlEmuShellsupendEnableSleep();
}
/** @brief VCM Thread func for reset*/
void resetthread()
{
	if(g_hTrlEmuMenu.pResetFunc != NULL)
	{
		g_hTrlEmuMenu.pResetFunc();
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		/*if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_PAUSE)	
			trlEmuShellNetworkCommand(TRL_NETWORK_COMMAND_RESET);
		while(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_RESET)
		{
			nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(2000));		
		}*/
#endif
	}
}
/** @brief VCM Thread func for not format error proc*/
void notformatthread()
{
	extern s32 g_nFileErrorResult;
	u64 curtime = trlTimeGet_ms();
	s32 trlEmuShellDataSaveDataCreate();
	trlEmuShellsupendDisableSleep();
	g_nFileErrorResult = trlEmuShellDataSaveDataCreate();
	if(g_nFileErrorResult ==TRL_FILE_SUCCESS)		
	{
		curtime = trlTimeGet_ms() - curtime;
		if(curtime < 2000)
			nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(2000 - curtime));		
	}
	else
	{
		NN_LOG("BootErrorProc occur FsError\n");
	}
	trlEmuShellsupendEnableSleep();
	return;
}
/** @brief VCM Thread func for bad format error proc*/
void badformatthread()
{
	extern s32 g_nFileErrorResult;
	NN_LOG("badformatthread...\n");
	if(g_bTrlEmuBootError != TRL_EMU_BOOTERROR)
	{
		NN_LOG("badformatthread...\n");
		u64 curtime = trlTimeGet_ms();
		s32 trlEmuShellDataSaveDataReset();
		trlEmuShellsupendDisableSleep();
		
		g_nFileErrorResult = trlEmuShellDataSaveDataReset();
		curtime = trlTimeGet_ms() - curtime;
		if(curtime < 2000)
			nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(2000 - curtime));
		trlEmuShellsupendEnableSleep();	
		return;
	}
	else
		notformatthread();
}

/** @brief VCM Call Back func for start save*/
s32 trlEmuMenuCallBack_ProcSave()
{
	g_VCMThread.StartUsingAutoStack(savethread, 4096);
	return 0;
}
/** @brief VCM Call Back func for start load*/
s32 trlEmuMenuCallBack_ProcLoad()
{
	trlEmuShellsupendDisableSleep();
	g_VCMThread.StartUsingAutoStack(loadthread, 4096);
	return 0;
}
/** @brief VCM Call Back func for start reset*/
s32 trlEmuMenuCallBack_ProcReset()
{
	g_VCMThread.StartUsingAutoStack(resetthread, 4096);
	return 0;
}

/** @brief VCM Call Back func for start error proc*/
s32 trlEmuMenuCallBack_ProcNotFormat()
{
	g_VCMThread.StartUsingAutoStack(notformatthread, 4096);
	return 0;
}
/** @brief VCM Call Back func for start error proc*/
s32 trlEmuMenuCallBack_ProcBadFormat()
{
	g_VCMThread.StartUsingAutoStack(badformatthread, 4096);
	return 0;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
/** @brief VCM Call Back func  Child Wait DLP end*/
s32 trlEmuMenuCallBack_DLPWait()
{
	//static int ct = 0;	
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		//ct = 0;
		NN_LOG("trlEmuMenuCallBack_DLPWait Error\n");
		return eCGBVCMStateChange_DLPWait2DLPChildError;
	}

	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
	{
		if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_WAIT_TO_PLAY)
		{
			NN_LOG("trlEmuMenuCallBack_DLPWait eCGBVCMStateChange_DLPWait2DLPStandBy\n");
			//ct = 0;
			return eCGBVCMStateChange_DLPWait2DLPStandBy;
		}
		return eEmuMenuCallBackState_Wait;
	}	
	else
	{
		//NN_LOG("trlEmuShellNetworkGetSelfPlayerState() = %d\n", trlEmuShellNetworkGetSelfPlayerState());
		/*if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_INIT || trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_SENDSAVE)
		{
			ct++;
			if(ct>= 60*15)
			{
				NN_LOG("trlEmuMenuCallBack_DLPWait timeout\n");
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
				ct = 0;
				return eCGBVCMStateChange_DLPWait2DLPChildError;
			}
		}*/
		return eEmuMenuCallBackState_Wait;
	}
}

/** @brief VCM Call Back func  Child Wait DLP end*/
s32 trlEmuMenuCallBack_DLPWaitBack()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		return eCGBVCMStateChange_DLPWaitBack2DLPChildError;
	}
	return eEmuMenuCallBackState_Wait;
}

/** @brief VCM Call Back for LoadFade*/
s32 trlEmuMenuCallBakc_LoadFade_FadeIn1End()
{	
	if(g_hTrlEmuMenu.LoadFade_FadeIn1End() == 1)
		return TRL_EMUMENU_ACTION_WAITFUNC_DONE;
	return TRL_EMUMENU_ACTION_WAITFUNC_WAIT;
	
}

/** @brief VCM Call Back for LoadFade*/
s32 trlEmuMenuCallBakc_LoadFade_FadeIn2End()
{	
	if(g_hTrlEmuMenu.LoadFade_FadeIn2End() == 1)
		return TRL_EMUMENU_ACTION_WAITFUNC_DONE;
	return TRL_EMUMENU_ACTION_WAITFUNC_WAIT;
	
}

/** @brief VCM Call Back for LoadFade*/
s32 trlEmuMenuCallBakc_LoadFade_FadeOutEnd()
{
	if(g_hTrlEmuMenu.LoadFade_FadeOutEnd() == 1)
		return TRL_EMUMENU_ACTION_WAITFUNC_DONE;
	return TRL_EMUMENU_ACTION_WAITFUNC_WAIT;
}

s32 trlEmuMenuCallBack_DLPChildOtherMenu()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_EEEOR_STATE_MASTERLEAVE || g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_LEAVE)
		{
			return eCGBVCMStateChange_DLPChildOtherMenu2DLPChildEndWait;
		}
		return eCGBVCMStateChange_DLPChildOtherMenu2DLPChildErrorSelect;
	}
	


	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
	{
		if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_OTHER_MENU)
			return eEmuMenuCallBackState_Wait;
		else if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_WAIT_TO_PLAY)
			return eCGBVCMStateChange_DLPChildOtherMenu2ChildDLPStandBy;		
		return eEmuMenuCallBackState_Wait;
	}
	else if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
	{
		return eEmuMenuCallBackState_Wait;
	}
	else if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_EXIT)
	{
		return eEmuMenuCallBackState_Wait;
	}
	NN_LOG("trlEmuMenuCallBack_DLPChildOtherMenu bad, %d %d\n", g_sEmuShellBuffer.nNetworkState, trlEmuShellNetworkGetSelfPlayerState());
	return eEmuMenuCallBackState_Wait;
}

s32 trlEmuMenuCallBack_DLPOtherMenu()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{	
		return eCGBVCMStateChange_DLPOtherMenu2DLPError;
	}

	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
	{	
		if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_OTHER_MENU)
			return eEmuMenuCallBackState_Wait;
		else if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_WAIT_TO_PLAY)
		{
			if(g_sEmuShellBuffer.nVCMMode == eVCMMode_Normal)			
				return eCGBVCMStateChange_DLPOtherMenu2DLPNStandBy;
			else
				return eCGBVCMStateChange_DLPOtherMenu2DLPStandBy;
		}
		return eEmuMenuCallBackState_Wait;
	}
	else if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
	{
		return eEmuMenuCallBackState_Wait;
	}
	else if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_EXIT)
	{
		return eEmuMenuCallBackState_Wait;
	}
	NN_LOG("trlEmuMenuCallBack_DLPOtherMenu bad, %d %d\n", g_sEmuShellBuffer.nNetworkState, trlEmuShellNetworkGetSelfPlayerState());
	return eEmuMenuCallBackState_Wait;
}

char *g_trlEmuMenuNetPlayerLabel[] =
{
	"T_Player_00",
	"T_Player_01",
	"T_Player_02",
	"T_Player_03"
};

/** @brief VCM Call Back func  check pia init*/
s32  trlEmuMenuCallBack_ProcNetInitBack()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{		
		return eCGBVCMStateChange_DLPNetInit2DLPS;
	}
	return eEmuMenuCallBackState_Wait;
}

/** @brief VCM Call Back func  check pia init*/
s32  trlEmuMenuCallBack_ProcNetInit()
{
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		return eCGBVCMStateChange_DLPNetInit2DLPS;
	}

	if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_SYNC_DONE)
	{
		return eCGBVCMStateChange_DLPNetInit2DLPS;
	}

	/*if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_INIT || trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_SENDSAVE)
	{
		ct++;
		if(ct >= 60*15)
		{
			NN_LOG("trlEmuMenuCallBack_ProcNetInit TimeOut\n");
			trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
			ct = 0;
			return eCGBVCMStateChange_DLPNetInit2DLPS;
		}
	}*/
	return eEmuMenuCallBackState_Wait;
}

void trlEmuMenuCallBack_MakeDLPName()
{
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE	
	CButtonSet2 *pButtonSet = cgbvcm_layout_messagedl.mpButtonSet;
	nw::lyt::TextBox *pTb;

	pTb = (nw::lyt::TextBox*)pButtonSet->search("T_DLPlayer_00");
	if(pTb != NULL)
	{
		pTb->SetString(pTb->GetString());		
		/*wchar_t namebuf[0x80];
		int namebufct = 0;
		wchar_t *pstr;
		for(int i=0;i<g_nTrlNetworkClintNum + 1;i++)
		{
			if(i == 0)
				pstr = trlEmuDLPGetSelfName();
			else
				pstr = trlEmuDLPGetChildName(i - 1);
			
			if(pstr != NULL)
			{
				if(i != 0)
				{
					namebuf[namebufct++] = 0x0D;
					namebuf[namebufct++] = 0x0A;
				}
				int pstrct = 0;
				while(pstr[pstrct] != 0)
					namebuf[namebufct++] = pstr[pstrct++];
			}			
		}
		namebuf[namebufct] = 0;
		if(pTb->GetStringBufferLength() < namebufct)
		{
			pTb->FreeStringBuffer();
			pTb->AllocStringBuffer(namebufct);
		}
		pTb->SetString(namebuf);*/
	}
#endif
}

/** @brief VCM Call Back func  update the connected user name on conn state*/
s32  trlEmuMenuCallBack_ProcDLPBack()
{
	if(g_trlEmuDLPDLPError != TRL_EMU_DLPDLP_ERROR_NONE)
		return eCGBVCMStateChange_DLPBack2DLPDLPError;
	return eEmuMenuCallBackState_Wait;
}

/** @brief VCM Call Back func  update the connected user name on conn state*/
s32  trlEmuMenuCallBack_ProcDLP()
{
	if(g_vcmstate == eEmuMenuState_DLPConn)
	{
		if(g_trlEmuDLPDLPError != TRL_EMU_DLPDLP_ERROR_NONE)
			return eCGBVCMStateChange_DLPConn2DLPDLPError;
	}
	else if(g_vcmstate == eEmuMenuState_DLP)
	{
		if(g_trlEmuDLPDLPError != TRL_EMU_DLPDLP_ERROR_NONE)
			return eCGBVCMStateChange_DLP2DLPDLPError;
	}

	if(g_vcmstate == eEmuMenuState_DLPConn)
	{
		if(g_vcmstate_state == eVCMState_Normal)
		{
			if(g_nTrlEmuDLPConnClientNum < 1)
			{
				if(cgbvcm_bt_messagedl_yes.mEnable == 1)
				{
					NN_LOG("g_nTrlEmuDLPConnClientNum ... %d  %d\n", g_nTrlEmuDLPConnClientNum, g_vcmstate_state);
					cgbvcm_bt_messagedl_yes.mEnable = 0;
					cgbvcm_scene_dlpconn.pLayout->mpButtonSet->bindanim("N_DLRFade_00", emessage_DLAnim_visible_on_00);
					cgbvcm_scene_dlpconn.pLayout->mpButtonSet->search("N_DLSet_00")->SetVisible(true);
					cgbvcm_scene_dlpconn.pLayout->mpButtonSet->search("N_DLPlayer_00")->SetVisible(false);
				}
			}
			else
			{
				if(cgbvcm_bt_messagedl_yes.mEnable == 0)
				{
					NN_LOG("g_nTrlEmuDLPConnClientNum ... %d %d\n", g_nTrlEmuDLPConnClientNum, g_vcmstate_state);
					cgbvcm_bt_messagedl_yes.mEnable = 1;
					cgbvcm_scene_dlpconn.pLayout->mpButtonSet->bindanim("N_DLRFade_00", emessage_DLAnim_visible_off_00);
					cgbvcm_scene_dlpconn.pLayout->mpButtonSet->search("N_DLSet_00")->SetVisible(false);
					cgbvcm_scene_dlpconn.pLayout->mpButtonSet->search("N_DLPlayer_00")->SetVisible(true);
				}
			
				trlEmuMenuCallBack_MakeDLPName();
			}
		}
	}	
	else
	{
		if(g_trlEmuDLPThreadFlag == TRL_EMU_DLPTHREAD_RECON_SUCCESS)
		{		
			if(g_VCMThread.IsAlive())
				return eEmuMenuCallBackState_Wait;
			g_VCMThread.Join();
			g_VCMThread.Finalize();
			return eCGBVCMStateChange_DLP2DLPNetInit;
		}		
	}	
	return eEmuMenuCallBackState_Wait;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
/** @brief VCM Call Back func  Init child thread*/
void trlEmuMenuCallBack_InitNetChild()
{
	NN_LOG("trlEmuMenuCallBack_InitNetChild\n");
	void triPiaCommonInit();
	triPiaCommonInit();
	g_VCMThread.StartUsingAutoStack(trlEmuNetThreadChildFunc, 4096);	
}

void trlEmuMenuCallBack_Init4PMessage()
{
	g_nTrlNetworkClintNum = g_sEmuShellBuffer.funcConfigData("NES", "MultiPlayer", 2) - 1;
	if(g_nTrlNetworkClintNum > 1)
	{
		g_nTrlNetwork4PMsg = 1;
	}
	else
	{
		g_nTrlNetwork4PMsg = 0;
	}
	g_hTrlEmuMenu.Convert4PMessage();
}

void trlEmuMenuCallBack_CloseDLPWarning()
{
	NN_LOG("trlEmuMenuCallBack_CloseDLPWarning\n");
	g_bTrlEmuDLPNotice = false;
	g_bTrlEmuDLPNoticeDraw = false;
}

/** @brief VCM Call Back func  Init DLP thread*/
void trlEmuMenuCallBack_InitDLP()
{
	trlEmuDLPStateInit();
	g_VCMThread.StartUsingAutoStack(trlEmuDLPThreadFunc, 4096, nn::os::DEFAULT_THREAD_PRIORITY - 1);
}

/** @brief VCM Call Back func  Close DLP thread*/
void trlEmuMenuCallBack_EnableHomeButton()
{
	trlEmuShellSuspendEnableHomeButton();
	trlEmuShellsupendEnableSleep();
}
/** @brief VCM Call Back func  Close DLP thread*/
void trlEmuMenuCallBack_CloseDLP()
{
	trlEmuShellSuspendEnableHomeButton();
	trlEmuShellsupendEnableSleep();
	trlEmuDLPThreadStop();
	//NN_LOG("trlEmuMenuCallBack_CloseDLP wait thread to end\n");
	//while(g_VCMThread.IsAlive())
	//{
	//	nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(1));
	//}
	//NN_LOG("trlEmuMenuCallBack_CloseDLP thread end\n");
	{
		g_VCMThread.Join();
		g_VCMThread.Finalize();
	}
}

/** @brief VCM Call Back func  release DLP resource*/
void trlEmuMenuCallBack_ReleaseDLP()
{
	trlEmuDLPRelease();
}

/** @brief VCM Call Back func  begin DLP translate*/
void trlEmuMenuCallBack_BeginTrans()
{
	trlEmuDLPBeginTrans();
}

void trlEmuMenuCallBack_EndDLPMenu()
{
	//if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
	//	trlEmuShellNetworkCommand(TRL_NETWORK_COMMAND_RESUME);
	trlEmuShellNetworkSetState(PLAYER_COMMAND_CLOSEMENU);
	g_bTrlEmuNetRole = eTrlEmuNetMaster;
}

void trlEmuMenuCallBack_AllLeaveOk()
{
	g_hTrlEmuMenu.bHaveNetError = 0;
}

void trlEmuMenuCallBack_ErrorHaveLeaveOk()
{
	g_hTrlEmuMenu.bHaveNetError = 0;
	if(g_hTrlEmuMenu.bHaveNetErrorInMenu)	
		trlEmuMenuCallBack_NetCommand(TRL_NETWORK_COMMAND_RESUME);//TRL_NETWORK_COMMAND_CLOSE);
	else
		trlEmuMenuCallBack_NetCommand(TRL_NETWORK_COMMAND_RESUME);
}

void trlEmuMenuCallBack_CloseNet()
{
	trlEmuShellNetworkExit();
	return;
}

void trlEmuMenuCallBack_NetCommand(u32 command)
{
	(void)command;
	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
	{
		NN_LOG("trlEmuMenuCallBack_NetCommand %d\n", command);
		trlEmuShellNetworkCommand(command);
	}
}

void trlEmuMenuCallBack_NetSetState(u32 nState)
{
	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
	{
		trlEmuShellNetworkSetState(nState);
	}
}

void trlEmuMenuCallBack_ChangeCommonWNDMessage()
{
	static int ct = HVC_WND_00;
	g_vcm_specialplayer = 1;
	g_hTrlEmuMenu.SetDLPMessageYN(ct);
	ct++;
	if(ct > HVC_WND_4P_12)
		ct = HVC_WND_00;
}

void trlEmuMenuCallBack_ChangeErrorMessage()
{
	static int ct = ERR_MSG_07;
	g_vcm_specialplayer = 1;
	g_hTrlEmuMenu.SetErrorMessageOK(ct);
	ct++;
	if(ct > ERR_MSG_11)
		ct = ERR_MSG_07;
}

void trlEmuMenuCallBack_Convert4PMessage()
{	
	if(g_nTrlNetworkClintNum > 1)
	{
		g_nTrlNetwork4PMsg = 1;
	}
	else
	{
		g_nTrlNetwork4PMsg = 0;
	}
	g_hTrlEmuMenu.Convert4PMessage();
}


u32 trlEmuMenuCallBack_MainMessage2PTo4P(u32 msg_no)
{
	if(g_nTrlNetwork4PMsg == 1)
	{
		if(msg_no >= HVC_VCM_00 && msg_no <= HVC_VCM_END)
			return msg_no + HVC_VCM_4P_00 - HVC_VCM_00;
	}
	return msg_no;
}

/** @brief VCM Call Back Set Main Message*/
void trlEmuMenuCallBack_SetMainDLBtMessage(u32 msg_no)
{
	g_hTrlEmuMenu.SetMainMessage("T_DLBtn_00", trlEmuMenuCallBack_MainMessage2PTo4P(msg_no));
	g_hTrlEmuMenu.SetMainMessage("T_DLBtn_01", trlEmuMenuCallBack_MainMessage2PTo4P(msg_no));
}

/** @brief VCM Call Back Set Error Message*/
void trlEmuMenuCallBakc_SetErrorMessageYN(u32 msg_no)
{
	g_hTrlEmuMenu.SetErrorMessageYN(msg_no);
}
/** @brief VCM Call Back Set Error Message*/
void trlEmuMenuCallBakc_SetErrorMessageOK(u32 msg_no)
{
	g_hTrlEmuMenu.SetErrorMessageOK(msg_no);
}
/** @brief VCM Call Back Set Error Message*/
void trlEmuMenuCallBakc_SetErrorMessageWait(u32 msg_no)
{
	g_hTrlEmuMenu.SetErrorMessageWait(msg_no);
}

u32 trlEmuMenuCallBack_DLPMessage2PTo4P(u32 msg_no)
{
	if(g_nTrlNetwork4PMsg == 1)
	{
		if(msg_no >= HVC_WND_00 && msg_no <= HVC_WND_12)
			return msg_no + HVC_WND_4P_00 - HVC_WND_00;
	}
	return msg_no;
}

/** @brief VCM Call Back Set DLP Message*/
void trlEmuMenuCallBakc_SetDLPMessageYN(u32 msg_no)
{
	NN_LOG("trlEmuMenuCallBakc_SetDLPMessageYN %d\n", msg_no);
	g_hTrlEmuMenu.SetDLPMessageYN(trlEmuMenuCallBack_DLPMessage2PTo4P(msg_no));
}
/** @brief VCM Call Back Set DLP Message*/
void trlEmuMenuCallBakc_SetDLPMessageOK(u32 msg_no)
{
	NN_LOG("trlEmuMenuCallBakc_SetDLPMessageOK %d\n", msg_no);
	g_hTrlEmuMenu.SetDLPMessageOK(trlEmuMenuCallBack_DLPMessage2PTo4P(msg_no));
}


/** @brief VCM Call Back Set DLP Message*/
void trlEmuMenuCallBakc_SetDLPMessageWait(u32 msg_no)
{
	NN_LOG("trlEmuMenuCallBakc_SetDLPMessageWait %d\n", msg_no);
	g_hTrlEmuMenu.SetDLPMessageWait(trlEmuMenuCallBack_DLPMessage2PTo4P(msg_no));
}

/** @brief VCM Call Back for LoadFade*/
void trlEmuMenuCallBakc_LoadFade_To_FadeIn1()
{
	g_hTrlEmuMenu.LoadFade_To_FadeIn1();
}

/** @brief VCM Call Back for LoadFade*/
void trlEmuMenuCallBakc_LoadFade_To_FadeIn2()
{
	g_hTrlEmuMenu.LoadFade_To_FadeIn2();
}

/** @brief VCM Call Back for LoadFade*/
void trlEmuMenuCallBakc_LoadFade_To_FadeOut()
{
	g_hTrlEmuMenu.LoadFade_To_FadeOut();
}
