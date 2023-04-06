/**
 * @file trlEmuShellMenu.cpp
 * @author zhfang
 * @date 2011.03.30
 * @brief TRL Emulate For CTR - EmuShell Menu
 */
#include <nn\cfg.h>
#include "..\trlEmuShellMenu.h"
#include "..\trlEmuShellStruct.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellVideo.h"
#include "..\trlEmuShellAudio.h"
#include "..\trlEmuShellSuspend.h"
#include "..\trlEmuShellInput.h"
#include "trlEmuShellVCMLanguage.h"
#include "EmuMenu\trlEmuMenu.h"

/** @name Global Variable */
//@{
MENU_SWITCHGBCOLOR_STATE		g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_CLOSED;

CEmuMenuAlloctor g_MenuAlloctor;
CEmuMenuAlloctor g_MenuDevAlloctor;

CEmuMenu						g_hTrlEmuMenu;

u32								g_nTrlEmuMenuFade = 200;
u32								g_nTrlEmuMenuFadeCt = 0;

static const wchar_t			g_wzTrlEmuShellLayoutPath[] = L"rom:/VCM/CGBVCM/layout.arc";
static const wchar_t			g_wzTrlEmuShellLayoutErrPath[] = L"rom:/VCM/ERRVCM/layout.arc";
static const char				g_zTrlEmuShellLayoutPath[] ="rom:/VCM/SND/threeb.bcsar";

extern trlSEmuShellResumeInfo	g_sEmuShellResumeInfo;
extern GLuint					g_nTrlVideoFrameBufObj[2];
//@}

/** @brief EmuShell Menu Init */
void trlEmuShellMenuInit()
{
	g_nTrlEmuMenuFade = trlEmuShellDataGetConfigData("Menu", "MenuFade", 200) / 16.6666f;

	g_MenuAlloctor.SetAlloc(trlMemAlloc, trlMemFree);
	g_MenuDevAlloctor.SetAlloc(trlMemAllocDevice, trlMemFreeDevice);
	g_hTrlEmuMenu.Init((nw::os::IAllocator*)&g_MenuAlloctor, (nw::os::IAllocator*)&g_MenuDevAlloctor);
	g_hTrlEmuMenu.InitSound();
	g_hTrlEmuMenu.OpenSoundFile(g_zTrlEmuShellLayoutPath);
	g_hTrlEmuMenu.OpenVCMRes();

	g_hTrlEmuMenu.OpenFile(g_wzTrlEmuShellLayoutPath);


#ifdef REGION_EU
	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_NES)
	{
		g_hTrlEmuMenu.ChangeCtrlChangeTexutre();
	}
#else
#ifdef REGION_US
	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_NES)
	{
		g_hTrlEmuMenu.ChangeCtrlChangeTexutre();
	}
#endif
#endif

	nn::cfg::CfgLanguageCode lang = nn::cfg::GetLanguage();	

	//lang = (nn::cfg::CfgLanguageCode)trlEmuShellDataGetConfigData("Menu", "Language", 0);
	if(lang >= TRL_EMUSHELL_VCM_LANGUAGENUM)
	{
		NN_LOG("language selectd (%d) out of range (%d)\n", lang, TRL_EMUSHELL_VCM_LANGUAGENUM);
		lang = (nn::cfg::CfgLanguageCode)0;
	}	
	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_AGB:
	case TRL_EMUCORE_ROMTYPE_CGB:
		if(g_hTrlEmuMenu.OpenLanguageFile(g_wzTrlEmuShellLanguagePath[lang], g_wzTrlEmuShellLanguageScalePath[lang]) == 0)
			g_hTrlEmuMenu.OpenLanguageFile(g_wzTrlEmuShellLanguagePath[0], g_wzTrlEmuShellLanguageScalePath[0]);
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
		#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		if(g_hTrlEmuMenu.OpenLanguageFile(g_wzTrlEmuShellLanguagePathHVCNet[lang], g_wzTrlEmuShellLanguageScalePathHVCNet[lang]) == 0)
			g_hTrlEmuMenu.OpenLanguageFile(g_wzTrlEmuShellLanguagePathHVCNet[0], g_wzTrlEmuShellLanguageScalePathHVCNet[0]);
		#else
		if(g_hTrlEmuMenu.OpenLanguageFile(g_wzTrlEmuShellLanguagePathHVC[lang], g_wzTrlEmuShellLanguageScalePathHVC[lang]) == 0)
			g_hTrlEmuMenu.OpenLanguageFile(g_wzTrlEmuShellLanguagePathHVC[0], g_wzTrlEmuShellLanguageScalePathHVC[0]);
		#endif
		break;
	}

	if(g_hTrlEmuMenu.OpenErrLanguageFile(g_wzTrlEmuShellErrLanguagePath[lang], g_wzTrlEmuShellErrLanguageScalePath[lang]) == 0)
		g_hTrlEmuMenu.OpenErrLanguageFile(g_wzTrlEmuShellErrLanguagePath[0], g_wzTrlEmuShellErrLanguageScalePath[0]);

	if(g_hTrlEmuMenu.OpenMessageWindowLanguageFile(g_wzTrlEmuShellMessageWindowLanguagePath[lang], g_wzTrlEmuShellMessageWindowLanguageScalePath[lang]) == 0)
		g_hTrlEmuMenu.OpenMessageWindowLanguageFile(g_wzTrlEmuShellMessageWindowLanguagePath[0], g_wzTrlEmuShellMessageWindowLanguageScalePath[0]);

	g_hTrlEmuMenu.Convert4PMessage();
	
	g_hTrlEmuMenu.LoadShaderResource();
	g_hTrlEmuMenu.SetFrameBuffer0(g_nTrlVideoFrameBufObj[0]);
	g_hTrlEmuMenu.SetFrameBuffer1(g_nTrlVideoFrameBufObj[1]);
	g_hTrlEmuMenu.SetSaveFunc(trlEmuShellDataSaveResume);
	g_hTrlEmuMenu.SetLoadFunc(trlEmuShellDataLoadResume);	
	g_hTrlEmuMenu.SetResetFunc(trlEmuShellDataReset);
	g_hTrlEmuMenu.SetResumeFunc(trlEmuShellDataResume);
	g_hTrlEmuMenu.SetSavePicture(g_sEmuShellResumeInfo.pCapture);
	g_hTrlEmuMenu.SetSaveDate(&g_sEmuShellResumeInfo.nYear, &g_sEmuShellResumeInfo.nMonth, &g_sEmuShellResumeInfo.nDay);
	g_hTrlEmuMenu.SetPreviewSize(g_sEmuShellBuffer.nWidth, g_sEmuShellBuffer.nHeight);
	g_hTrlEmuMenu.SetSaveAnim(trlEmuShellDataGetConfigData("Menu", "SaveAnim", 1));
	g_hTrlEmuMenu.SetLoadAnim(trlEmuShellDataGetConfigData("Menu", "LoadAnim", 1));
	g_hTrlEmuMenu.SetResetAnim(trlEmuShellDataGetConfigData("Menu", "ResetAnim", 1));
	g_hTrlEmuMenu.SetLoadFadeParam(
		trlEmuShellDataGetConfigData("Menu", "FadeInTime1", 200)/16.6666f,
		trlEmuShellDataGetConfigData("Menu", "FadeInTime2", 200)/16.6666f,
		trlEmuShellDataGetConfigData("Menu", "FadeWaitTime", 2000)/16.6666f,
		trlEmuShellDataGetConfigData("Menu", "FadeOutTime", 200)/16.6666f);
	g_hTrlEmuMenu.SetWaitIconEnable(TRL_VCM_WAITICON);
}

/** @brief EmuShell Menu Draw before game run*/
void trlEmuShellMenuDrawBeforeGameRun()
{	
	g_hTrlEmuMenu.VCMForceMenuInit();
	g_hTrlEmuMenu.VCMForceGo();
	while(1)
	{
		if(g_hTrlEmuMenu.RunVCM() == eRunVCMReslut_End)
			break;
		nngxSplitDrawCmdlist();
		nngxRunCmdlist();
		nngxWaitCmdlistDone();
		nngxClearCmdlist();
	}
	trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY1, false);
	trlEmuShellVideoMaskMode(false);
}

enum EShellMenuState
{
	eShellMenuStateOpen,
	eShellMenuStateFadeIn,
	eShellMenuStateMenuOpen,
	eShellMenuStateMain,
	eShellMenuStateFadeOut,
	eShellMenuStateClose
};
EShellMenuState g_eShellMenuState = eShellMenuStateOpen;

void trlEmuShellMenuOpen()
{
	g_eShellMenuState = eShellMenuStateOpen;	
}

s32 trlEmuShellMenuTouchIn()
{
	return g_hTrlEmuMenu.beInOpenTouchArea(trlEmuShellInputGetTouch(TRL_INPUT_TOUCH_X), trlEmuShellInputGetTouch(TRL_INPUT_TOUCH_Y));
}

u32 g_bVCMSkipFadeIn = 0;
u32 g_bVCMHaveBreakSave = 0;
u32 g_bVCMHaveSave = 0;
void trlEmuShellMenuSetParam(u32 SkipFadeIn, u32 HaveBreakSave)
{
	g_bVCMSkipFadeIn = SkipFadeIn;
	g_bVCMHaveBreakSave = HaveBreakSave;
}

/** @brief EmuShell Boot Error Menu Open*/
void trlEmuShellBootErrorMenuOpen(s32 nResult)
{
	NN_UNUSED_VAR(nResult)
	g_hTrlEmuMenu.VCMForceError();
}

s32 trlEmuShellBootErrorMenuMain()
{
	if(g_hTrlEmuMenu.RunVCM() == eRunVCMReslut_End)
		return 1;
	trlEmuShellVideoFrame();
	trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY1, true);
	return 0;
}

/** @brief EmuShell Boot Error Menu Open*/
void trlEmuShellFsErrorMenuOpen(s32 nResult)
{
	NN_UNUSED_VAR(nResult)
	g_hTrlEmuMenu.VCMForceError();
}

s32 trlEmuShellFsErrorMenuMain()
{
	if(g_hTrlEmuMenu.RunVCM() == eRunVCMReslut_End)
		return 1;
	trlEmuShellVideoFrame();
	trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY1, true);
	return 0;
}

s32 trlEmuShellMenuHomeNix()
{
	if(g_bTrlEmuMenuHomeNixState != eTrlEmuShell_HomeNixState_None)
	{
		if(g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_Open)
			g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_Open_UP;
		g_hTrlEmuMenu.UpdateHomeNix();
		return 1;
	}
	return 0;
};

s32 trlEmuShellMenuRun() //return 0: continue   1:  menu end
{
	switch(g_eShellMenuState)
	{
	case eShellMenuStateOpen:
		trlTimePause();
		trlEmuShellAudioPause();
		if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
			if(g_sEmuShellBuffer.nSaveUpdate)
				trlEmuShellDataSaveBackup();
		if(g_sEmuShellBuffer.nFrameDouble)
			trlEmuShellVideoFrameBlend();

		if(g_bVCMSkipFadeIn)
			g_eShellMenuState = eShellMenuStateMenuOpen;
		else
		{
			g_eShellMenuState = eShellMenuStateFadeIn;
			g_nTrlEmuMenuFadeCt = 0;
		}
		break;
	case eShellMenuStateFadeIn:
		trlEmuShellVideoMaskMode(1, (g_nTrlEmuMenuFade-g_nTrlEmuMenuFadeCt-1)/(g_nTrlEmuMenuFade*1.0f));
		trlEmuShellVideoFrame();
		trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, true);			
		g_nTrlEmuMenuFadeCt++;
		if(g_nTrlEmuMenuFadeCt >= g_nTrlEmuMenuFade)
			g_eShellMenuState = eShellMenuStateMenuOpen;
		g_hTrlEmuMenu.UpdatePad();
		break;
	case eShellMenuStateMenuOpen:
		{
			
			s32 nRet = trlEmuShellDataCheckResume(TRL_DATA_RESUME_BACKUP);
			g_bVCMHaveSave = (nRet == 0);			
			{				
				g_hTrlEmuMenu.PlaySoundMenuOpen();
				g_hTrlEmuMenu.VCMForceGo();
			}
			g_eShellMenuState = eShellMenuStateMain;
			g_hTrlEmuMenu.UpdatePad();
			
		}
		break;
	case eShellMenuStateMain:
		{
			if(g_hTrlEmuMenu.RunVCM() == eRunVCMReslut_End)
			{
				g_nTrlEmuMenuFadeCt = 0;
				g_eShellMenuState = eShellMenuStateFadeOut;
				if(g_bQuit != eTrlQuit_NONE)
				{
					trlTraceHio("trlEmuShellMenuRun eShellMenuStateMain Quit\n");
					return eTrlEmuShellMenuResult_End;
				}
			}
			if(g_bQuit != eTrlQuit_NONE)
			{
				trlTraceHio("trlEmuShellMenuRun eShellMenuStateMain Quit\n");
				return eTrlEmuShellMenuResult_End;
			}
			extern u32 g_nTrlVideoMenuDark;
			if(g_hTrlEmuMenu.GetLoadFadeFlag() == 1)
			{
				trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY1, true);
			}
			else
			{
				trlEmuShellVideoMaskMode(2, g_hTrlEmuMenu.GetLoadFadeParam(g_nTrlVideoMenuDark));
				trlEmuShellVideoFrame();
				trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH, true);
			}			
		}
		break;
	case eShellMenuStateFadeOut:
		trlEmuShellVideoMaskMode(1, g_nTrlEmuMenuFadeCt/(g_nTrlEmuMenuFade*1.0f));
		trlEmuShellVideoFrame();
		trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, true);
		g_nTrlEmuMenuFadeCt++;
		if(g_nTrlEmuMenuFadeCt >= g_nTrlEmuMenuFade)
			g_eShellMenuState = eShellMenuStateClose;
		break;
	case eShellMenuStateClose:
		trlEmuShellVideoMaskMode(false);		
		trlTimeResume();
		trlEmuShellMenuSetParam(0,0);
		return eTrlEmuShellMenuResult_End;
	}	
	return eTrlEmuShellMenuResult_Continue;
}

/** @brief EmuShell Menu Switch Color Main run one per frame*/
void trlEmuShellMenuSwitchColor()
{
	if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_OPEN)
	{
		extern u32 g_bTrlVideoFaceEnable;
		g_hTrlEmuMenu.UpdateSwitchIconBG(g_bTrlVideoFaceEnable);
		if(g_pEmuShellCore->trlEmuCoreSwap(-1) == 0)
		{
			if(g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateBOpen, TRL_SWITCHICON) == 1)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_SWITCH;			
		}
		else
		{
			if(g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateGOpen, TRL_SWITCHICON) == 1)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_SWITCH;
		}
	}
	else if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_SWITCH)
	{
		if(g_pEmuShellCore->trlEmuCoreSwap(-1) == 0)
			g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateBLoop, TRL_SWITCHICON);
		else
			g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateGLoop, TRL_SWITCHICON);
	}
	else if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_SWITCHING)
	{
		if(g_pEmuShellCore->trlEmuCoreSwap(-1) == 2)
		{
			if(g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateBTOG, TRL_SWITCHICON) == 1)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_SWITCH;
		}
		else
		{
			if(g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateGTOB, TRL_SWITCHICON) == 1)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_SWITCH;
		}
	}
	else if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_CLOSE)
	{
		if(g_pEmuShellCore->trlEmuCoreSwap(-1) == 0)
		{
			if(g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateBClose, TRL_SWITCHICON) == 1)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_CLOSED;
		}
		else
		{
			if(g_hTrlEmuMenu.UpdateSwitchIcon1(CEmuMenu::eModeChangeStateGClose, TRL_SWITCHICON) == 1)
				g_nTrlEmuMenuSwitchGBColorState = MENU_SWITCHGBCOLOR_CLOSED;
		}
	}
}
