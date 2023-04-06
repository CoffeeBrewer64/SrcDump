/**
* @file trlEmuShell.h
* @author zhfang, chentian
* @date 2009.11.24
* @brief TRL Emulate For PC - EmuShell Main
*/
#include "..\trlEmuShell.h"
#include "..\trlEmuShellVideo.h"
#include "..\trlEmuShellAudio.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellSuspend.h"
#include "..\trlEmuShellNetwork.h"
#include "..\trlEmuShellDebug.h"
#include "..\trlEmuShellMenu.h"
#include "..\trlEmuShellPatch.h"
#include "..\trlEmuShellInput.h"

/** @name Global Variable */
//@{
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
u32 g_nTrlEmuMenuDelay = 200;
u32 g_nTrlEmuMenuSwitchGBColorDelay = 60;
u32 g_nTrlEmuMenuCt = 0;
u32 g_nTrlEmuMenuColorTime = 0;
u32 g_nTrlEmuMenuDebugTime = 0;
u32 g_nTrlEmuMenuSwitchGBColorTime = 0;
u32 g_nTrlEmuShellSwitchRom = 1;
u16 g_nKeyBuf = 0xFFFF;
MENU_SWITCHGBCOLOR_STATE		g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_CLOSED;
extern trlSEmuShellResumeInfo g_sEmuShellResumeInfo;
extern HWND g_hWnd;
u32 g_bStepRun = 0;
//@}

/** @brief EmuShell Init */
void trlEmuShellInit()
{
	trlTraceInit();
	trlMemInit(0x04000000); // 64MB
	trlTimeInit();
	trlEmuShellDataInit(g_sEmuShellRomIndex);
	trlEmuShellVideoInit((u32)g_hWnd);
	trlEmuShellAudioInit();
	trlEmuShellInputInit();
	trlEmuShellDebugInit();
	g_pEmuShellCore->trlEmuCoreInit(&g_sEmuShellBuffer);
	trlEmuShellDataSaveDataInit();
	if(g_sEmuShellBuffer.nBackupDataSize)
		trlEmuShellDataLoadBackup();

	SetWindowPos(g_hWnd, NULL, 0,0, g_sEmuShellBuffer.nWidth+8, g_sEmuShellBuffer.nHeight*2+51, SWP_NOMOVE|SWP_SHOWWINDOW);

	g_sEmuShellRomIndex = -1;
	trlEmuShellAudioStart();

	g_sEmuShellBuffer.bInitFlag = 1;
}

/** @brief EmuShell Exit */
void trlEmuShellExit()
{
	g_pEmuShellCore->trlEmuCoreExit();
	trlEmuShellAudioExit();
	trlEmuShellVideoExit();
	trlEmuShellInputExit();
	trlEmuShellDataExit();
	trlFileExit();
	trlMemExit();
}

/** @brief EmuShell Input */
void trlEmuShellInput(u32 nKey, u32 nPush)
{
	switch(nKey)
	{
	case 'L': // A Button
		if(nPush)
			g_nKeyBuf &= 0xFFFE;
		else
			g_nKeyBuf |= 1;
		break;
	case 'K': // B Button
		if(nPush)
			g_nKeyBuf &= 0xFFFD;
		else
			g_nKeyBuf |= 2;
		break;
	case 'F': // Select Button
		if(nPush)
			g_nKeyBuf &= 0xFFFB;
		else
			g_nKeyBuf |= 4;
		break;
	case 'J': // Start Button
		if(nPush)
			g_nKeyBuf &= 0xFFF7;
		else
			g_nKeyBuf |= 8;
		break;
	case 'D': // Right Button
		if(nPush)
			g_nKeyBuf &= 0xFFEF;
		else
			g_nKeyBuf |= 16;
		break;
	case 'A': // Left Button
		if(nPush)
			g_nKeyBuf &= 0xFFDF;
		else
			g_nKeyBuf |= 32;
		break;
	case 'W': // Up Button
		if(nPush)
			g_nKeyBuf &= 0xFFBF;
		else
			g_nKeyBuf |= 64;
		break;
	case 'S': // Down Button
		if(nPush)
			g_nKeyBuf &= 0xFF7F;
		else
			g_nKeyBuf |= 128;
		break;
	case 'P': // R Button
		if(nPush)
			g_nKeyBuf &= 0xFEFF;
		else
			g_nKeyBuf |= 256;
		break;
	case 'U': // L Button
		if(nPush)
			g_nKeyBuf &= 0xFDFF;
		else
			g_nKeyBuf |= 512;
		break;
	case 'I': // Y Button
		if(nPush)
			g_nKeyBuf &= 0xF7FF;
		else
			g_nKeyBuf |= 0x800;
		break;
	case 'O': // X Button
		if(nPush)
			g_nKeyBuf &= 0xFBFF;
		else
			g_nKeyBuf |= 0x400;
		break;
		// Debug Key
	case 'Z':
		g_pEmuShellCore->trlEmuCoreReset();
		break;
	case 'H': // Open BBB Menu
		if(!nPush)
		{
			g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuOpen;			
		}
		break;
	case 'G': // Open Color Menu
		if(!nPush)
		{
			trlEmuShellOpenColorMenu();
		}
		break;
	case 'C': // CPU Log On
		if(nPush)
			g_sEmuShellBuffer.nDebugKey |= 1;
		else
			g_sEmuShellBuffer.nDebugKey &= ~1;
		break;
	case 'V': // CPU Log OFF
		if(nPush)
			g_sEmuShellBuffer.nDebugKey |= 2;
		else
			g_sEmuShellBuffer.nDebugKey &= ~2;
		break;
	case ' ': // CPU SpeepUp
		{
			extern u32 bTrlTimeEmuFast;
			if(nPush)
				bTrlTimeEmuFast = 1;
			else
				bTrlTimeEmuFast = 0;
		}
		break;
	case 'R': // CPU Normal Run
		if(nPush)
		{
			g_bStepRun = 0;
			trlEmuShellAudioPlay();
		}
		break;
	case 'T':// CPU Step Run
		if(nPush)
		{
			if(g_bStepRun == 0)
			{
				trlEmuShellAudioPause();
				g_bStepRun = 1;
			}
			else if(g_bStepRun == 3)
			{
				g_bStepRun = 1;
			}
		}
		else
		{
			if(g_bStepRun == 2)
				g_bStepRun = 3;
		}
		/*if(nPush)
		{
		if(g_eShellMainState == eShellMainStateNormal)
		g_eShellMainState = eShellMainStateStepBegin;
		if(g_eShellMainState == eShellMainStateStepWait)
		g_eShellMainState = eShellMainStateStepWait1;
		}
		else if(g_eShellMainState == eShellMainStateStepWait1)
		g_eShellMainState = eShellMainStateStepRun;*/
		break;
	case 'Y': // Switch
		if(nPush)
			g_pEmuShellCore->trlEmuCoreSwap(2);
		break;
	case 'Q': // NES FDS Switch Disk Side
		if(nPush)
			g_sEmuShellBuffer.nSwitchDisk = 60;
		break;
	case 'B': // Record Wav
		if(nPush)
			trlEmuShellAudioRecordUpdate();
		break;
	}
	/*if(trlEmuShellMenuOpened() != 0)
	trlEmuShellDebugMenuUpdate(~g_nKeyBuf, 0);
	else
	g_pEmuShellCore->trlEmuCoreInput(g_nKeyBuf);*/
	if(((~g_nKeyBuf) & 0x300) == 0x300)
		g_pEmuShellCore->trlEmuCoreSwap(2);

}

inline void trlEmuShellUpdateInput()
{
	u32 nPad = trlEmuShellInputUpdate();

#if TRL_DEBUGINFO	// Debug Menu
	if(trlEmuShellInputGetKey(TRL_INPUT_KEY_CLEARTIME))
	{
		NN_LOG("Mem status: %d  %d\n", trlMemGetFree(), trlMemGetTotalSize());
		g_nMaxTime = 0;
		g_nMaxTimeV = 0;
	}
#endif
#if TRL_HVC_FDSDISK	// FDS Switch Disk
	if(trlEmuShellInputGetKey(TRL_INPUT_KEY_SWITCHDISK))
		g_sEmuShellBuffer.nSwitchDisk = 60;
#endif

	if(trlEmuShellColorMenuOpened() != 0)
		trlEmuShellDebugMenuUpdate(trlEmuShellInputGetButton(TRL_INPUT_BUTTON_TRIGGER), trlEmuShellInputGetButton(TRL_INPUT_BUTTON_HOLD));
	else
	{
		if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_CLOSED)
		{
			static u32 nLastPad = 0;
			if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
			{
				if(g_sEmuShellBuffer.bNetworkAsync == 0)
					g_pEmuShellCore->trlEmuCoreInput(nPad);
				//trlEmuShellNetworkUpdateInput();
			}
			else if(nLastPad != nPad)
			{
				nLastPad = nPad;
				g_pEmuShellCore->trlEmuCoreInput(nPad);
			}
		}
		else if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_SWITCH)
		{
			if(trlEmuShellInputGetKey(TRL_INPUT_KEY_GBCOLORSWITCH))
			{
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_SWITCHING;
				if(g_pEmuShellCore->trlEmuCoreSwap)
				{
					g_pEmuShellCore->trlEmuCoreSwap(2);
					g_sEmuShellBuffer.nVCMState = 2;
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
						if(g_nTrlEmuMenuSwitchGBColorTime > g_nTrlEmuMenuSwitchGBColorDelay)
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
						++g_nTrlEmuMenuSwitchGBColorTime;
						if(g_nTrlEmuMenuSwitchGBColorTime > g_nTrlEmuMenuSwitchGBColorDelay)
							g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_OPEN;
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
}

inline void trlEmuShellUpdate()
{
#if TRL_DEBUGINFO
	trlTimeStart();
#endif
	trlEmuShellUpdateInput();
	if(g_bStepRun == 0 || g_bStepRun == 1)
	{
		if(g_bStepRun == 1)
			g_bStepRun = 2;
		g_pEmuShellCore->trlEmuCoreRunOneFrame();
	}

	// Switch GB Color
	if(g_nTrlEmuMenuSwitchGBColorState != MENU_SWITCHGBCOLOR_CLOSED)
		trlEmuShellMenuSwitchColor();

	// Patch
	trlEmuShellPatch();

	// CTR Render
	trlEmuShellVideoFrame();

	// Auto Save
	trlEmuShellDataUpdateAutoSave();

#if TRL_DEBUGINFO
	// Debug Info
	trlEmuShellDebugInfoUpdate();
#endif

#if !TRL_PRODUCTION
	if(trlEmuShellColorMenuOpened()!=0)
		trlEmuShellDebugMenuDraw();
#endif


#if TRL_DEBUGINFO
	g_nFrameTime = trlTimeStop();
#endif

	trlEmuShellAudioMain();
}

void trlEmuShellMain()
{
	switch(g_eTrlEmuShellState)
	{
	case eTrlEmuShellStateInitShell:
		trlEmuShellInit();
		g_eTrlEmuShellState = eTrlEmuShellStateSwitchRomCheck;
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
			g_eTrlEmuShellState = eTrlEmuShellStateGameRun;
		}
		break;		
	case eTrlEmuShellStateGameRun:
		trlEmuShellUpdate();
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
		g_sEmuShellBuffer.nVCMState = 1;
		g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuMain;
		break;
	case eTrlEmuShellStateDebugMenuMain:
		trlEmuShellInputUpdate();
		trlEmuShellDebugMenuUpdate(trlEmuShellInputGetButton(TRL_INPUT_BUTTON_TRIGGER), trlEmuShellInputGetButton(TRL_INPUT_BUTTON_HOLD));
		trlEmuShellDebugMenuDraw();
		if(trlEmuShellMenuOpened() != 1)
			g_eTrlEmuShellState = eTrlEmuShellStateDebugMenuClose;
		break;
	case eTrlEmuShellStateDebugMenuClose:
		trlEmuShellVideoMaskMode(false);
		trlEmuShellVideoFrame();
		#if TRL_DEBUGINFO
		trlTimeResume();
		#endif
		g_sEmuShellBuffer.nVCMState = 2;
		
		trlEmuShellAudioPlay();
		g_eTrlEmuShellState = eTrlEmuShellStateGameRun;			
		break;	
	case eTrlEmuShellStateExit:
		trlEmuShellsupendDisableSleep();
		trlEmuShellExit();
		if(g_bQuit == eTrlQuit_ReBoot)
		{
			g_bQuit = eTrlQuit_NONE;

			g_eTrlEmuShellState = eTrlEmuShellStateInitShell;

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

	if(g_bQuit != eTrlQuit_NONE && g_eTrlEmuShellState != eTrlEmuShellStateExit && g_eTrlEmuShellState != eTrlEmuShellStateExitSleep)
	{
		NN_LOG("g_bQuit = %d\n", g_bQuit);
		g_eTrlEmuShellState = eTrlEmuShellStateExit;
	}
}

