/**
* @file trlEmuShellSuspend.cpp
* @author zhfang
* @date 2010.10.15
* @brief TRL Emulate For CTR - EmuShell Suspend Module
*/
#include "trlEmuShellSleep.h"
#include "..\trlEmuShell.h"
#include "..\trlEmuShellSuspend.h"
#include "..\trlEmuShellAudio.h"
#include "..\trlEmuShellVideo.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellStruct.h"
#include "EmuMenu\trlEmuMenu.h"

/** @name Global Variable */
//@{

u32	g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_None;
nn::os::CriticalSection g_SleepCS;
nn::os::LightEvent g_TransitionEvent;
nn::os::LightEvent g_AwakeEvent;
nn::os::CriticalSection::ScopedLock *pLock = NULL;
u32 nTrlEmuShellSuspendDisableHomeButton;

void trlEmuShellsuspendFSWait()
{
	NN_LOG("trlEmuShellsuspendFSWait 0\n");
	g_AwakeEvent.Wait();
	NN_LOG("trlEmuShellsuspendFSWait 1\n");
	g_TransitionEvent.Wait();
	NN_LOG("trlEmuShellsuspendFSWait 2\n");
	pLock = new nn::os::CriticalSection::ScopedLock(g_SleepCS);
	NN_LOG("trlEmuShellsuspendFSWait 3\n");
}

void trlEmuShellsuspendFSRelease()
{
	if(pLock != NULL)
	{
		delete pLock;
		pLock = NULL;
		NN_LOG("trlEmuShellsuspendFSRelease 0\n");
	}
}

void trlEmuShellSuspendEnableHomeButton()
{
	NN_LOG("nTrlEmuShellSuspendDisableHomeButton = 0\n");
	nTrlEmuShellSuspendDisableHomeButton = 0;
}

void trlEmuShellSuspendDisableHomeButton()
{
	NN_LOG("nTrlEmuShellSuspendDisableHomeButton = 1\n");
	nTrlEmuShellSuspendDisableHomeButton = 1;
}

void trlEmuShellsupendEnableSleep()
{
	NN_LOG("trlEmuShellsupendEnableSleep\n");
	nn::applet::EnableSleep(true);
}

void trlEmuShellsupendDisableSleep()
{
	NN_LOG("trlEmuShellsupendDisableSleep\n");
	nn::applet::DisableSleep();
}
void restoreGraphicSetting()
{
	nngxUpdateState(NN_GX_STATE_ALL);
	nngxValidateState(NN_GX_STATE_ALL,GL_TRUE);
}

//@}
extern void trlEmuShellVideoSwapBuffer(const s32 display, const bool isWaitVSync);
extern CEmuMenu				g_hTrlEmuMenu;

/** @brief EmuShell Suspend Home Button CallBack*/
bool trlEmuShellSuspendHomeButtonCallBack(uptr arg, bool isActive, nn::applet::HomeButtonState state)
{
	NN_UNUSED_VAR(arg);
	NN_UNUSED_VAR(state);	
	if ( isActive )
	{		
		if(nTrlEmuShellSuspendDisableHomeButton == 1 || g_bTrlEmuMenuHomeNixState != eTrlEmuShell_HomeNixState_None)
		{
			if(g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_None)
			{
				if(g_eTrlEmuShellState == eTrlEmuShellStateGameRunNet || g_eTrlEmuShellState == eTrlEmuShellStateGameRun)
					g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_Open_UP;
				else
					g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_Open;
			}
			NN_LOG("nTrlEmuShellSuspendDisableHomeButton == 1\n");
			nn::applet::ClearHomeButtonState();
			return false;
		}
		else
		{
			NN_LOG("nTrlEmuShellSuspendDisableHomeButton == 0\n");
			return true;
		}
	}
	else
	{
		return false;
	}
}

/** @brief EmuShell Suspend Init */
void trlEmuShellSuspendInit0()
{	
	NN_LOG("trlEmuShellSuspendInit0 0\n");
	nn::fs::Initialize();	

#if TRL_DEMO == 0
	SleepHandler::Initialize();
#endif

	nn::applet::SetHomeButtonCallback( trlEmuShellSuspendHomeButtonCallBack, 0 );

	g_SleepCS.Initialize();
	g_AwakeEvent.Initialize(true);
	g_TransitionEvent.Initialize(true);

	g_AwakeEvent.Signal();
	g_TransitionEvent.Signal();

	nn::applet::Enable(false);
	if ( nn::applet::IsExpectedToCloseApplication() )
	{
#if TRL_DEMO == 0
		SleepHandler::Finalize();
#endif
		nn::Result result = nn::applet::PrepareToCloseApplication();
		NN_UTIL_PANIC_IF_FAILED( result );
		nn::applet::CloseApplication();
		g_bQuit = eTrlQuit_AfterBoot;
	}
}

/** @brief EmuShell Suspend Init */
void trlEmuShellSuspendInit1()
{
	trlEmuShellsupendEnableSleep();
}

/** @brief EmuShell Suspend Exit */
void trlEmuShellSuspendExit0()
{
	SleepHandler::Finalize();
	nngxWaitVSync(NN_GX_DISPLAY_BOTH);
}

/** @brief EmuShell Suspend Exit */
void trlEmuShellSuspendExit1()
{
	NN_LOG("trlEmuShellSuspendExit 0\n");
	g_SleepCS.Finalize();
	g_AwakeEvent.Finalize();
	g_TransitionEvent.Finalize();
	NN_LOG("trlEmuShellSuspendExit 1\n");
	nn::os::SetDeviceMemorySize(0);
	nn::os::SetHeapSize(0);

	NN_LOG("trlEmuShellSuspendExit 2\n");
	nn::applet::PrepareToCloseApplication();
	nn::applet::CloseApplication();
}

/** @brief EmuShell Suspend Proc Home Button */
u32 trlEmuShellSuspendProcHomeButton(u32 inMenu)
{
	if(g_bQuit != eTrlQuit_NONE)
		return 0;

	if ( nn::applet::IsExpectedToProcessHomeButton() )
	{
		NN_LOG("....have home request\n");

		g_TransitionEvent.ClearSignal();
		if ( g_SleepCS.TryEnter() )
		{
			NN_LOG("Want t oHome Menu\n");
			nn::applet::DisableSleep();

			//before home button
			if(inMenu == eTrlSuspendMenuState_Normal)
			{
				if(g_sEmuShellBuffer.nFrameDouble)
				{
					trlEmuShellVideoFrameBlend();
					trlEmuShellVideoFrame();
					trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, false);
				}
				trlEmuShellAudioPause();
			}
			if(inMenu == eTrlSuspendMenuState_Normal || inMenu == eTrlSuspendMenuState_VCM)
			{
				if(g_sEmuShellBuffer.nSaveUpdate)
					trlEmuShellDataSaveBackup();
				trlEmuShellDataSaveResume(TRL_DATA_RESUME_HOME);
			}

			//home button
			nn::applet::ProcessHomeButton();

			nn::applet::AppletWakeupState wState = nn::applet::WaitForStarting();
			NN_UNUSED_VAR(wState);

			g_SleepCS.Leave();
			g_TransitionEvent.Signal();
			nn::applet::EnableSleep(true);

			if ( nn::applet::IsExpectedToCloseApplication() )
			{
				NN_LOG("quit after home menu\n");
				trlTraceHio("quit after home menu\n");
				g_bQuit = eTrlQuit_QuitApplication;
				return 0;
			}

			restoreGraphicSetting();

			//after home button
			if(inMenu == eTrlSuspendMenuState_Normal || inMenu == eTrlSuspendMenuState_VCM)
				trlEmuShellDataDisableResume();

			if(inMenu == eTrlSuspendMenuState_Normal)
				trlEmuShellAudioPlay();
		}
	}
	return 1;
}
/** @brief EmuShell Suspend Main */
/** return 0: quit application	 */
/** return 1: normal			 */
/** inMenu 0: normal			 */
/** inMenu 1: VCM				 */
/** inMenu 2: VCM	error		 */

u32 trlEmuShellSuspendMain(u32 inMenu)
{
	if(g_bQuit != eTrlQuit_NONE)
		return 0;
#if TRL_DEMO
	NN_UNUSED_VAR(inMenu);
	return 1;
#else
	if ( SleepHandler::s_IsAfterWakeUp ) 
	{
		nn::gx::StartLcdDisplay();
		SleepHandler::s_IsAfterWakeUp = false;
	}

	if ( SleepHandler::IsSleepRequested() )
	{
		NN_LOG("....have sleep request\n");
		if ( g_SleepCS.TryEnter() )
		{
			trlTraceHio("Want totrlEmuShellSleep\n");
			NN_LOG("Want totrlEmuShellSleep\n");
			/*if(nw::snd::SoundSystem::IsInitialized())
			{
				NN_LOG("LockSoundThread\n");
				nw::snd::SoundSystem::LockSoundThread();
			}*/
			//before sleep
			if(inMenu == eTrlSuspendMenuState_Normal)
			{
				if(g_sEmuShellBuffer.nFrameDouble)
				{
					trlEmuShellVideoFrameBlend();
					trlEmuShellVideoFrame();
					trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, false);
				}
				trlEmuShellAudioPause();
			}
			if(inMenu == eTrlSuspendMenuState_Normal || inMenu == eTrlSuspendMenuState_VCM)
			{
				NN_LOG("sleep inMenu = %d\n", inMenu);
				if(g_sEmuShellBuffer.nSaveUpdate)
					trlEmuShellDataSaveBackup();
				trlEmuShellDataSaveResume(TRL_DATA_RESUME_SLEEP);
			}

			//sleep 
			NN_LOG("trlEmuShellSleep\n");
			SleepHandler::SleepSystem();

			//after sleep
			if(inMenu == eTrlSuspendMenuState_Normal || inMenu == eTrlSuspendMenuState_VCM)
			{
				NN_LOG("sleep inMenu = %d\n", inMenu);
				trlEmuShellDataDisableResume();
			}
			if(inMenu == eTrlSuspendMenuState_Normal)
				trlEmuShellAudioPlay();
			/*if(nw::snd::SoundSystem::IsInitialized())
			{
				NN_LOG("UnlockSoundThread\n");
				nw::snd::SoundSystem::UnlockSoundThread();
			}*/
		}
	}

	if ( nn::applet::IsExpectedToCloseApplication() )
	{
		g_bQuit = eTrlQuit_QuitApplication;		
		return 0;		
	}

	if ( nn::applet::IsExpectedToProcessPowerButton() )
	{
		NN_LOG("....have power request\n");
		g_TransitionEvent.ClearSignal();
		if ( g_SleepCS.TryEnter() )
		{
			NN_LOG("Want to Power\n");
			nn::applet::DisableSleep();

			if(g_sEmuShellBuffer.nFrameDouble)
			{
				trlEmuShellVideoFrameBlend();
				trlEmuShellVideoFrame();
				trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, false);
			}
			if(inMenu != eTrlSuspendMenuState_VCM_ERROR)
			{
				if(g_sEmuShellBuffer.nSaveUpdate)
					trlEmuShellDataSaveBackup();
				//trlEmuShellDataSaveResume(TRL_DATA_RESUME_HOME);
			}


			nn::applet::ProcessPowerButton();
			nn::applet::AppletWakeupState wState = nn::applet::WaitForStarting();

			NN_UNUSED_VAR(wState);

			g_SleepCS.Leave();
			g_TransitionEvent.Signal();
			nn::applet::EnableSleep(true);

			if ( nn::applet::IsExpectedToCloseApplication() )
			{
				NN_LOG("Power IsExpectedToCloseApplication\n");
				g_bQuit = eTrlQuit_QuitApplication;
				return 0;
			}            
			restoreGraphicSetting();
		}
	}
	return 1;
#endif
}
