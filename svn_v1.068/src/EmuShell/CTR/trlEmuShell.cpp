/**
* @file trlEmuShell_CTR.cpp
* @author zhfang, chentian
* @date 2009.11.24
* @brief TRL Emulate For CTR - EmuShell Main
*/
#include "..\trlEmuShell.h"
#include "..\trlEmuShellVideo.h"
#include "..\trlEmuShellAudio.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellNetwork.h"
#include "..\trlEmuShellDebug.h"
#include "..\trlEmuShellMenu.h"
#include "..\trlEmuShellPatch.h"
#include "..\trlEmuShellInput.h"
#include "..\trlEmuShellSuspend.h"
#include "EmuMenu\trlEmuMenu.h"

#include <nn\os.h>
#include <nn\fs.h>
#include <nn\ptm.h>
#include <nn\hid.h>
#include <nn\hid\CTR\hid_PadReaderForVc.h>
#include <nn\cfg.h>

using namespace nn::hid::CTR;
using namespace nn::os;

/** @name Global Variable */
//@{
u32 g_nTrlEmuVideoPause = 0;
trlSEmuShellBuffer g_sEmuShellBuffer;
trlSEmuShellCore* g_pEmuShellCore = NULL;
trlSEmuShellConfig g_sEmuShellConfig;
trlSEmuShellConfig g_sEmuShellPatch;
u32 g_bQuit = 0;
s32 g_sEmuShellRomIndex = 0;
s32 g_eTrlEmuShellState;
s32 g_bTrlEmuBootError;
s32 g_bTrlEmuLayoutMenuShow = 0;
s32 g_bTrlEmuLayoutMenuShow1 = 0;
u32 g_nTrlEmuMenuCt = 0;
u32 g_nTrlEmuMenuColorTime = 0;
u32 g_nTrlEmuMenuDebugTime = 0;
u32 g_nTrlEmuMenuSwitchGBColorTime = 0;
u32 g_nTrlEmuShellSwitchRom = 1;
s32 g_nFileErrorResult = TRL_FILE_SUCCESS;
extern trlSEmuShellResumeInfo g_sEmuShellResumeInfo;
extern u32 g_nTrlInputMenuDelay;	
extern u32 g_nTrlInputGBColorDelay;

s32 g_bTrlEmuNetRole = eTrlEmuNetNone;
//@}

void trlEmuShellInit()
{
	nn::ptm::CTR::Initialize();
	nn::cfg::Initialize();
	
	//use PIA will use some static memory, the free memory will less than 0x01000000, so reduce the trmMemInit to 0x00c00000
	trlMemInit(0x00C00000);
	trlTimeInit();
	trlFileInit();
	trlEmuShellDataInit(g_sEmuShellRomIndex);
	trlEmuShellInputInit();
	trlTraceHioInit();

	PadReaderForVc sPad;
	PadStatus sPadStatus;
	sPad.ReadLatest(&sPadStatus);
	trlEmuShellVideoInit((sPadStatus.hold & (BUTTON_START | BUTTON_SELECT_FOR_DEBUGGING)) && trlEmuShellDataGetConfigData("CGB", "Dotbydot", 1));
	trlEmuShellAudioInit();

	g_pEmuShellCore->trlEmuCoreInit(&g_sEmuShellBuffer);
	trlEmuShellDebugInit();
	trlEmuShellMenuInit();

	trlEmuShellVideoStart();
	trlEmuShellAudioStart();

	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_NONE;

	g_nTrlEmuVideoPause = 0;
}

/** @brief EmuShell Exit */
void trlEmuShellExit()
{
	NN_LOG("trlEmuShellExit Start...\n");
	trlEmuShellsupendDisableSleep();

#if TRL_NETWORK
	trlEmuShellNetworkExit();
	NN_LOG("trlEmuShellExit Network.\n");
#endif

	trlEmuShellDataExitAutoSave();
	NN_LOG("trlEmuShellExit AutoSave.\n");

	g_pEmuShellCore->trlEmuCoreExit();
	NN_LOG("trlEmuShellExit Core.\n");

	trlEmuShellAudioExit();
	NN_LOG("trlEmuShellExit Audio.\n");

	trlEmuShellVideoExit();
	NN_LOG("trlEmuShellExit Video.\n");

	trlEmuShellInputExit();
	NN_LOG("trlEmuShellExit Input.\n");

	trlEmuShellDataExit();
	NN_LOG("trlEmuShellExit Data.\n");

	trlTraceHioRelease();

	trlFileExit();
	trlMemExit();
	NN_LOG("trlEmuShellExit BaseTool.\n");

	nn::cfg::Finalize();
	nn::ptm::CTR::Finalize();
	NN_LOG("trlEmuShellExit CTR.\n");
}


inline void trlEmuShellUpdateInput()
{
	u32 nPad = trlEmuShellInputUpdate();

#if TRL_DEBUGINFO// Debug Menu
	if(trlEmuShellInputGetKey(TRL_INPUT_KEY_CLEARTIME))
	{
		NN_LOG("Mem status: %d  %d\n", trlMemGetFree(), trlMemGetTotalSize());
		g_nMaxTime = 0;
		g_nMaxTimeV = 0;
	}
#endif
#if TRL_HVC_FDSDISK// FDS Switch Disk
	if(trlEmuShellInputGetKey(TRL_INPUT_KEY_SWITCHDISK))
		g_sEmuShellBuffer.nSwitchDisk = 60;
#endif

	if(trlEmuShellColorMenuOpened() != 0)
		trlEmuShellDebugMenuUpdate(trlEmuShellInputGetButton(TRL_INPUT_BUTTON_TRIGGER), trlEmuShellInputGetButton(TRL_INPUT_BUTTON_HOLD));
	else
	{
		{
			//static u32 nLastPad = 0;
			if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
			{
				//trlEmuShellNetworkUpdateInput();
				if(trlEmuShellNetworkInputValid())
					g_pEmuShellCore->trlEmuCoreInput(g_nTrlNetworkInput);
			}
			else //if(nLastPad != nPad)
			{
				//nLastPad = nPad;
				g_pEmuShellCore->trlEmuCoreInput(nPad);
			}
		}
		if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_SWITCH)
		{
			if(trlEmuShellInputGetKey(TRL_INPUT_KEY_GBCOLORSWITCH))
			{
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_SWITCHING;
				if(g_pEmuShellCore->trlEmuCoreSwap)
				{
					g_pEmuShellCore->trlEmuCoreSwap(2);
					g_sEmuShellBuffer.nVCMState = 2;
					g_pEmuShellCore->trlEmuCoreInput(nPad);
				}
			}
		}
	}

	if(g_bTrlEmuLayoutMenuShow != 1 && g_bTrlEmuLayoutMenuShow1 != 1)
	{
#if TRL_SWITCHICON
		if(trlEmuShellInputGetKey(TRL_INPUT_KEY_SWITCHICON))
		{
			switch(g_sEmuShellBuffer.nRomType)
			{
			case TRL_EMUCORE_ROMTYPE_AGB:
				break;
			case TRL_EMUCORE_ROMTYPE_CGB:
				if(g_sEmuShellBuffer.nRomSubType == TRL_EMUCORE_GBTYPE_DMG)
				{
					if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_CLOSED)
					{
						++g_nTrlEmuMenuSwitchGBColorTime;
						if(g_nTrlEmuMenuSwitchGBColorTime > g_nTrlInputGBColorDelay)
							g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_OPEN;
					}
#if !TRL_PRODUCTION// Debug Menu
					g_nTrlEmuMenuDebugTime = 0;
					g_nTrlEmuMenuColorTime = 0;
#endif
				}
				break;
			case TRL_EMUCORE_ROMTYPE_NES:
				{
					if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_CLOSED)
					{
						if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
						{
							++g_nTrlEmuMenuSwitchGBColorTime;
							if(g_nTrlEmuMenuSwitchGBColorTime > g_nTrlInputGBColorDelay)
								g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_OPEN;
						}
					}
#if !TRL_PRODUCTION// Debug Menu
					g_nTrlEmuMenuDebugTime = 0;
					g_nTrlEmuMenuColorTime = 0;
#endif
				}
				break;
			}
		}
		else
#endif
		{
			g_nTrlEmuMenuSwitchGBColorTime = 0;
			if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_SWITCH)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_CLOSE;

#if !TRL_PRODUCTION// Debug Menu
			if(trlEmuShellInputGetKey(TRL_INPUT_KEY_DEBUGMENU))
			{
				NN_LOG("g_eTrlEmuShellState = eShellMainStateDebugMenuOpen\n");
				g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuOpen;
			}

			if(trlEmuShellInputGetKey(TRL_INPUT_KEY_COLORMENU))
				trlEmuShellOpenColorMenu();
#endif
		}
	}
	else
	{
		if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_SWITCH)
			g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_CLOSE;
		g_nTrlEmuMenuSwitchGBColorTime = 0;
#if !TRL_PRODUCTION// Debug Menu
		g_nTrlEmuMenuDebugTime = 0;
		g_nTrlEmuMenuColorTime = 0;
#endif
	}

#if TRL_MENU
	if(trlEmuShellInputGetTouch(TRL_INPUT_TOUCH_VALUE) && trlEmuShellMenuTouchIn() == 1)
	{
		if(g_bTrlEmuLayoutMenuShow1 == 0)
			g_bTrlEmuLayoutMenuShow1 = 1;
	}
	else
	{
		if(g_bTrlEmuLayoutMenuShow1 == -1)
			g_bTrlEmuLayoutMenuShow1 = 0;
	}

	if( (g_bTrlEmuLayoutMenuShow == 1 || g_bTrlEmuLayoutMenuShow1 == 1) && g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_CLOSED)
	{
		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
		{
			trlEmuShellNetworkSetState(PLAYER_COMMAND_OPENMENU);
			g_bTrlEmuLayoutMenuShow = 2;
			g_bTrlEmuLayoutMenuShow1 = 2;
		}
		else
		{
			g_eTrlEmuShellState = eTrlEmuShellStateVCMOpen;
			g_bTrlEmuLayoutMenuShow = -1;
			g_bTrlEmuLayoutMenuShow1 = -1;
		}
	}

	if((g_bTrlEmuLayoutMenuShow == 2 && g_bTrlEmuLayoutMenuShow1 == 2))
	{
		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
		{
			g_bTrlEmuLayoutMenuShow = 0;
			g_bTrlEmuLayoutMenuShow1 = 0;
		}
	}

	if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_MENU || trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_OTHER_MENU)
	{
		NN_LOG("PLAYER_STATE_MENU || tPLAYER_STATE_OTHERMENU  goto eTrlEmuShellStateVCMOpen\n");
		g_eTrlEmuShellState = eTrlEmuShellStateVCMOpen;
		g_bTrlEmuLayoutMenuShow = -1;
		g_bTrlEmuLayoutMenuShow1 = -1;
		if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_MENU)		
			g_bTrlEmuNetRole = eTrlEmuNetMaster;
		else
			g_bTrlEmuNetRole = eTrlEmuNetSlave;
	}
#endif
}

inline void trlEmuShellUpdate()
{
#if TRL_DEBUGINFO
	trlTimeStart();
#endif

	trlEmuShellUpdateInput();
	if(trlEmuShellNetworkInputValid())
	{
		trlEmuShellAudioPlay();
#if TRL_DEBUG
		extern s32 g_nTrlEmuCoreOn;
		if(g_nTrlEmuCoreOn == 1)
			g_pEmuShellCore->trlEmuCoreRunOneFrame();
#else
		g_pEmuShellCore->trlEmuCoreRunOneFrame();
#endif
	}
	else
	{
		trlEmuShellAudioPause();
	}

	// Switch GB Color
	if(g_nTrlEmuMenuSwitchGBColorState != MENU_SWITCHGBCOLOR_CLOSED)
		trlEmuShellMenuSwitchColor();

	// Patch
	trlEmuShellPatch();

	// CTR Render
	if(g_nTrlEmuVideoPause > 0)
		g_nTrlEmuVideoPause--;
	else
		trlEmuShellVideoFrame();

	// Auto Save
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_CHILD
	trlEmuShellDataUpdateAutoSave();
#endif

#if TRL_DEBUGINFO
	// Debug Info
	trlEmuShellDebugInfoUpdate();
#endif

	s32 nDisplay = NN_GX_DISPLAY0;
#if !TRL_PRODUCTION
	if(trlEmuShellColorMenuOpened()!=0)
	{
		trlEmuShellDebugMenuDraw();
		trlEmuShellVideoFrameMenu();
		nDisplay = NN_GX_DISPLAY_BOTH;
	}
#endif

	trlEmuShellMenuHomeNix();
#if TRL_DEBUGINFO
	g_nFrameTimeV = trlTimeStop();
#endif
	// CTR Swap Buffer
	trlEmuShellVideoSwapBuffer(nDisplay, g_sEmuShellBuffer.nVSyncEnable);

#if TRL_DEBUGINFO
	g_nFrameTime = trlTimeStop();
#endif

	
	trlEmuShellAudioMain();
}

void trlEmuShellMain()
{
	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
	{
#if TRL_NETWORK_PIA_WITH_MIC
		trlEmuShellInputUpdateMicrophone();
#endif
		trlEmuShellNetworkUpdateInput();
	}
	switch(g_eTrlEmuShellState)
	{
	case eTrlEmuShellStateInitSleep:
		trlEmuShellSuspendEnableHomeButton();
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
		trlEmuShellSuspendDisableHomeButton();
#endif
		trlEmuShellSuspendInit0();
		if(g_bQuit == eTrlQuit_NONE)
			g_eTrlEmuShellState = eTrlEmuShellStateEnableSleep;
		else
			g_eTrlEmuShellState = eTrlEmuShellStateExitSleep;
		break;
	case eTrlEmuShellStateEnableSleep:
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_CHILD
		trlEmuShellSuspendInit1();
#endif
		g_eTrlEmuShellState = eTrlEmuShellStateInitShell;
		break;
	case eTrlEmuShellStateInitShell:
		trlEmuShellInit();
		g_eTrlEmuShellState = eTrlEmuShellStateSwitchRomCheck;
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
		g_eTrlEmuShellState = eTrlEmuShellStateInitSave;
#endif
		break;
	case eTrlEmuShellStateSwitchRomCheck:

		if(g_nTrlEmuShellSwitchRom == 1 && trlEmuShellDataGetRomListCountDebug() > 1)
		{
			trlEmushellOpenSwitchRom();
			g_nTrlEmuShellSwitchRom = 0;
			g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuOpen;
		}
		else
		{
			g_eTrlEmuShellState = eTrlEmuShellStateInitSave;

		}
		break;
	case eTrlEmuShellStateInitSave:
		g_bTrlEmuBootError = TRL_EMU_BOOTERROR;
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
		g_nFileErrorResult = trlEmuShellDataSaveDataInit(0);
#else
		g_nFileErrorResult = trlEmuShellDataSaveDataInit(1);
#endif
		if(g_nFileErrorResult != TRL_FILE_SUCCESS)
			g_eTrlEmuShellState = eTrlEmuShellStateBootDataErrorOpen;
		else
		{
			g_bTrlEmuBootError = TRL_EMU_FSERROR;
			g_eTrlEmuShellState = eTrlEmuShellStateLoadBackup;
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
			g_eTrlEmuShellState = eTrlEmuShellStateNetChildInit;
#endif
		}
		break;
	case eTrlEmuShellStateLoadBackup:
		if(g_sEmuShellBuffer.nBackupDataSize)
		{
			NN_LOG("LoadBackup...\n");
			s32 result = trlEmuShellDataLoadBackup();
			if(result < 0)
			{
				NN_LOG("LoadBackup Fail.\n");
				g_nFileErrorResult = result;
				g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorOpen;
			}
			else
				g_eTrlEmuShellState = eTrlEmuShellStateStartAutoSave;
		}
		else
			g_eTrlEmuShellState = eTrlEmuShellStateStartAutoSave;
		break;
	case eTrlEmuShellStateStartAutoSave:
		trlEmuShellDataInitAutoSave();
		g_eTrlEmuShellState = eTrlEmuShellStateCheckResume;
		break;
	case eTrlEmuShellStateCheckResume:
#if TRL_MENU
		{
			//zhfang test
			//trlEmuShellDataCheckResume 's return value should be modify
			trlEmuShellVideoMaskMode(true);
			s32 result = trlEmuShellDataCheckResume(TRL_DATA_RESUME_SUSPEND);
			if(result < TRL_FILE_SUCCESS)
			{
				NN_LOG("CheckResume Fail: %d.\n", g_nFileErrorResult);
				g_nFileErrorResult = result;
				g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorOpen;
			}
			else
			{
				g_sEmuShellBuffer.bInitFlag = 1;
				if(result == TRL_FILE_SUCCESS)
				{
					NN_LOG("have resume,so to load resume\n");
					trlEmuShellMenuDrawBeforeGameRun();
					g_eTrlEmuShellState = eTrlEmuShellStateLoadResume;
				}
				else
				{
					NN_LOG("have no resume,so to game\n");
					trlEmuShellMenuDrawBeforeGameRun();
					trlEmuShellAudioPlay();
					g_eTrlEmuShellState = eTrlEmuShellStateGameRun;
				}
			}
		}
#else
		trlEmuShellAudioPlay();
		g_eTrlEmuShellState = eTrlEmuShellStateGameRun;
#endif
		break;
	case eTrlEmuShellStateLoadResume:
		{
			//zhfnag test
			s32 result = trlEmuShellDataLoadResume(g_sEmuShellResumeInfo.nType);
			if(result < TRL_FILE_SUCCESS)
			{
				NN_LOG("LoadResume Fail: %d.\n", g_nFileErrorResult);
				g_nFileErrorResult = result;
				g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorOpen;
			}
			else
			{
				trlEmuShellDataResume();
				trlEmuShellMenuSetParam(1,1);
				g_eTrlEmuShellState = eTrlEmuShellStateVCMOpen;
			}
		}
		break;
	case eTrlEmuShellStateNetChildInit:
		trlEmuShellMenuDrawBeforeGameRun();
		trlEmuShellAudioPlay();
		g_bTrlEmuNetRole = eTrlEmuNetSlave;
		g_eTrlEmuShellState = eTrlEmuShellStateVCMOpen;
		break;
	case eTrlEmuShellStateGameRunNet:
	case eTrlEmuShellStateGameRun:
		trlEmuShellUpdate();
		if(g_sEmuShellBuffer.nSaveFlag < 0)
			g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorOpen;
		break;
	case eTrlEmuShellStateVCMOpen:
		g_sEmuShellBuffer.nVCMState = 1;
		trlEmuShellMenuOpen();
		g_eTrlEmuShellState = eTrlEmuShellStateVCMMain;
		NN_LOG("VCM OPEn g_sEmuShellBuffer.nNetworkState = %d\n", g_sEmuShellBuffer.nNetworkState);
		break;
	case eTrlEmuShellStateVCMMain:
		if(trlEmuShellMenuRun() == eTrlEmuShellMenuResult_End)
			g_eTrlEmuShellState = eTrlEmuShellStateVCMClose;
		break;
	case eTrlEmuShellStateVCMClose:
		g_sEmuShellBuffer.nVCMState = 2;
		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
		{
			NN_LOG("VCM Close. go to eTrlEmuShellStateGameRun\n");
			trlEmuShellSuspendEnableHomeButton();
			trlEmuShellsupendEnableSleep();
			trlEmuShellAudioPlay();
			g_eTrlEmuShellState = eTrlEmuShellStateGameRun;
		}
		else
		{
			NN_LOG("VCM Close. go to eTrlEmuShellStateNetStartGame g_sEmuShellBuffer.nNetworkState = %d\n", g_sEmuShellBuffer.nNetworkState);
			g_eTrlEmuShellState = eTrlEmuShellStateNetStartGame;
		}
		break;
	case eTrlEmuShellStateNetStartFromDebugMenu:
		g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_RUN;
		if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_SYNC_DONE)
		{	
			g_eTrlEmuShellState = eTrlEmuShellStateNetStartGame;
			trlEmuShellNetworkSetState(PLAYER_COMMAND_CLOSEMENU);
		}
		nngxWaitVSync(NN_GX_DISPLAY_BOTH);
		break;
	case eTrlEmuShellStateNetStartGame:
		#if TRL_NETWORK_PIA
		g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_RUN;
		if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_WAIT_TO_PLAY || trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_CLOSEMENU)
		{	
			g_eTrlEmuShellState = eTrlEmuShellStateNetStartGameSync;
			trlEmuShellNetworkSetState(PLAYER_COMMAND_PLAYGAME);
		}
		nngxWaitVSync(NN_GX_DISPLAY_BOTH);
		#endif
		break;
	case eTrlEmuShellStateNetStartGameSync:
		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
		{
			if(trlEmuShellNetworkGetSelfPlayerState() == PLAYER_STATE_PLAYGAME)
			{
				NN_LOG("EmuShell NetState goto Run, so game run\n");
				trlEmuShellAudioPlay();
				g_eTrlEmuShellState = eTrlEmuShellStateGameRunNet;
				g_bTrlEmuNetRole = eTrlEmuNetNone;				
			}
		}
		trlEmuShellMenuHomeNix();
		trlEmuShellVideoFrame();
		trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH, g_sEmuShellBuffer.nVSyncEnable);
		//nngxWaitVSync(NN_GX_DISPLAY_BOTH);
		break;
	case eTrlEmuShellStateDebugMenuOpen:
#if TRL_DEBUGINFO
		trlTimePause();
#endif
		trlEmuShellAudioPause();
		trlEmuShellDataListResumeDebug();
		trlEmuShellOpenDebugMenu();

		trlEmuShellVideoMaskMode(true);
		trlEmuShellVideoFrame();

		trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, false);

		g_sEmuShellBuffer.nVCMState = 1;
		g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuMain;
		break;
	case eTrlEmuShellStateDebugMenuMain:
		trlEmuShellInputUpdate();
		trlEmuShellDebugMenuUpdate(trlEmuShellInputGetButton(TRL_INPUT_BUTTON_TRIGGER), trlEmuShellInputGetButton(TRL_INPUT_BUTTON_HOLD));
		trlEmuShellDebugMenuDraw();

		trlEmuShellVideoFrameMenu();
		trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY1, true);

		if(trlEmuShellMenuOpened() != 1)
			g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuClose;
		break;
	case eTrlEmuShellStateDebugMenuClose:
		trlEmuShellVideoMaskMode(false);
		trlEmuShellVideoFrame();

		trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, false);

#if TRL_DEBUGINFO
		trlTimeResume();
#endif
		g_sEmuShellBuffer.nVCMState = 2;
		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
		{			
			trlEmuShellAudioPlay();
			g_eTrlEmuShellState = eTrlEmuShellStateGameRun;
		}
		else
		{
			NN_LOG(" eTrlEmuShellStateDebugMenuClose go to eTrlEmuShellStateNetStartFromDebugMenu %d\n", g_sEmuShellBuffer.nNetworkState);
			g_eTrlEmuShellState = eTrlEmuShellStateNetStartFromDebugMenu;
		}
		break;	
	case eTrlEmuShellStateBootDataErrorOpen:
		NN_LOG("eTrlEmuShellStateBootDataErrorOpen\n");
		trlEmuShellBootErrorMenuOpen(g_nFileErrorResult);
		g_eTrlEmuShellState = eTrlEmuShellStateBootDataErrorMain;
		trlEmuShellSuspendDisableHomeButton();
		break;
	case eTrlEmuShellStateBootDataErrorMain:
		if(trlEmuShellBootErrorMenuMain() == 1)
			g_eTrlEmuShellState = eTrlEmuShellStateBootDataErrorClose;
		break;
	case eTrlEmuShellStateBootDataErrorClose:
		NN_LOG("eTrlEmuShellStateBootDataErrorClose\n");
		g_nFileErrorResult = TRL_FILE_SUCCESS;
		g_eTrlEmuShellState = eTrlEmuShellStateLoadBackup;
		trlEmuShellSuspendEnableHomeButton();
		break;
	case eTrlEmuShellStateFSDataErrorOpen:
#if TRL_DEBUGINFO
		trlTimePause();
#endif
		trlEmuShellAudioPause();
		trlEmuShellFsErrorMenuOpen(g_nFileErrorResult);
		g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorMain;
		trlEmuShellSuspendDisableHomeButton();
		break;
	case eTrlEmuShellStateFSDataErrorMain:
		if(trlEmuShellFsErrorMenuMain() == 1)
			g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorClose;
		break;
	case eTrlEmuShellStateFSDataErrorClose:
		g_nFileErrorResult = TRL_FILE_SUCCESS;
		g_bQuit = eTrlQuit_ReBoot;
		g_eTrlEmuShellState = eTrlEmuShellStateExit;
		trlEmuShellSuspendEnableHomeButton();
		break;
	case eTrlEmuShellStateExit:
		trlEmuShellsupendDisableSleep();
		trlEmuShellExit();
		if(g_bQuit == eTrlQuit_ReBoot)
		{
			g_bQuit = eTrlQuit_NONE;

			g_eTrlEmuShellState = eTrlEmuShellStateEnableSleep;

		}
		else
			g_eTrlEmuShellState = eTrlEmuShellStateExitSleep;
		break;
	case eTrlEmuShellStateExitSleep:
#if TRL_DEMO == 0
		trlEmuShellSuspendExit1();
#endif
		g_bQuit = eTrlQuit_Close;
		NN_LOG("...close\n");
		break;
	}

	if(g_eTrlEmuShellState != eTrlEmuShellStateExit &&
			g_eTrlEmuShellState != eTrlEmuShellStateExitSleep)
	{
		if(g_nFileErrorResult != TRL_FILE_SUCCESS && g_bTrlEmuBootError != TRL_EMU_BOOTERROR)
		{
			if(g_eTrlEmuShellState != eTrlEmuShellStateFSDataErrorOpen &&
				g_eTrlEmuShellState != eTrlEmuShellStateFSDataErrorMain &&
				g_eTrlEmuShellState != eTrlEmuShellStateFSDataErrorClose)
			{
				NN_LOG("Find g_nFileErrorResult = %d, go to FsError\n", g_nFileErrorResult);
				g_eTrlEmuShellState = eTrlEmuShellStateFSDataErrorOpen;
			}
		}

		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
			if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
			{
				if(g_eTrlEmuShellState != eTrlEmuShellStateVCMOpen &&
					g_eTrlEmuShellState != eTrlEmuShellStateVCMMain &&
					g_eTrlEmuShellState != eTrlEmuShellStateVCMClose)
				{
					extern CEmuMenu g_hTrlEmuMenu;
					g_hTrlEmuMenu.bHaveNetError = 1;
					NN_LOG("Net Error occur\n");
					g_eTrlEmuShellState = eTrlEmuShellStateVCMOpen;
				}
			}
	}


	//SleepCheck
	//if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE || g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_EXIT)
	{
		switch(g_eTrlEmuShellState)
		{
		case eTrlEmuShellStateInitSleep:
		case eTrlEmuShellStateEnableSleep:
		case eTrlEmuShellStateInitShell:
			break;
		case eTrlEmuShellStateInitSave:
		case eTrlEmuShellStateLoadBackup:
		case eTrlEmuShellStateStartAutoSave:
		case eTrlEmuShellStateCheckResume:
		case eTrlEmuShellStateLoadResume:
			trlEmuShellSuspendMain(eTrlSuspendMenuState_Init);
			break;
		case eTrlEmuShellStateGameRun:
		case eTrlEmuShellStateGameRunNet:
			trlEmuShellSuspendMain(eTrlSuspendMenuState_Normal);
			break;
		case eTrlEmuShellStateVCMOpen:
		case eTrlEmuShellStateVCMMain:
		case eTrlEmuShellStateVCMClose:
		case eTrlEmuShellStateNetStartGame:
		case eTrlEmuShellStateNetStartGameSync:
			trlEmuShellSuspendMain(eTrlSuspendMenuState_VCM);
			break;
		case eTrlEmuShellStateDebugMenuOpen:
		case eTrlEmuShellStateDebugMenuMain:
		case eTrlEmuShellStateDebugMenuClose:
		case eTrlEmuShellStateNetStartFromDebugMenu:
			trlEmuShellSuspendMain(eTrlSuspendMenuState_Normal);
			break;
		case eTrlEmuShellStateBootDataErrorOpen:
		case eTrlEmuShellStateBootDataErrorMain:
		case eTrlEmuShellStateBootDataErrorClose:
		case eTrlEmuShellStateFSDataErrorOpen:
		case eTrlEmuShellStateFSDataErrorMain:
		case eTrlEmuShellStateFSDataErrorClose:
			trlEmuShellSuspendMain(eTrlSuspendMenuState_VCM_ERROR);
			break;
		case eTrlEmuShellStateExit:
		case eTrlEmuShellStateExitSleep:
			break;
		};
	}

	switch(g_eTrlEmuShellState)
	{
	case eTrlEmuShellStateInitSleep:
	case eTrlEmuShellStateEnableSleep:
	case eTrlEmuShellStateInitShell:
		break;
	case eTrlEmuShellStateInitSave:
	case eTrlEmuShellStateLoadBackup:
	case eTrlEmuShellStateStartAutoSave:
	case eTrlEmuShellStateCheckResume:
	case eTrlEmuShellStateLoadResume:
		trlEmuShellSuspendProcHomeButton(eTrlSuspendMenuState_Init);
		break;
	case eTrlEmuShellStateGameRun:
		trlEmuShellSuspendProcHomeButton(eTrlSuspendMenuState_Normal);
		break;
	case eTrlEmuShellStateVCMOpen:
	case eTrlEmuShellStateVCMMain:
	case eTrlEmuShellStateVCMClose:
		trlEmuShellSuspendProcHomeButton(eTrlSuspendMenuState_VCM);
		break;
	case eTrlEmuShellStateDebugMenuOpen:
	case eTrlEmuShellStateDebugMenuMain:
	case eTrlEmuShellStateDebugMenuClose:
	case eTrlEmuShellStateNetStartFromDebugMenu:
		trlEmuShellSuspendProcHomeButton(eTrlSuspendMenuState_Normal);
		break;
	case eTrlEmuShellStateBootDataErrorOpen:
	case eTrlEmuShellStateBootDataErrorMain:
	case eTrlEmuShellStateBootDataErrorClose:
	case eTrlEmuShellStateFSDataErrorOpen:
	case eTrlEmuShellStateFSDataErrorMain:
	case eTrlEmuShellStateFSDataErrorClose:
		trlEmuShellSuspendProcHomeButton(eTrlSuspendMenuState_VCM_ERROR);
		break;
	case eTrlEmuShellStateExit:
	case eTrlEmuShellStateExitSleep:
		break;
	};


	if(g_bQuit != eTrlQuit_NONE && g_eTrlEmuShellState != eTrlEmuShellStateExit && g_eTrlEmuShellState != eTrlEmuShellStateExitSleep)
	{
		NN_LOG("g_bQuit = %d\n", g_bQuit);
		g_eTrlEmuShellState = eTrlEmuShellStateExit;
	}
}

