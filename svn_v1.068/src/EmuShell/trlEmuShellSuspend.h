/**
 * @file trlEmuShellSuspend.h
 * @author zhfang
 * @date 2010.10.15
 * @brief TRL Emulate - EmuShell Suspend Module
 */
#pragma once
#include "..\trlHeader.h"

/** @name Global Variable */
//@{
extern u32					g_bQuit;
//@}

#ifdef TRL_PLATFORM_CTR
/** @brief EmuShell Suspend Init*/
void trlEmuShellSuspendInit0();
/** @brief EmuShell Suspend Init*/
void trlEmuShellSuspendInit1();
/** @brief EmuShell Suspend Main */
u32 trlEmuShellSuspendMain(u32 inMenu);
/** @brief EmuShell Exit */
void trlEmuShellSuspendExit0();
/** @brief EmuShell Exit */
void trlEmuShellSuspendExit1();
/** @brief EmuShell FS access wait*/
void trlEmuShellsuspendFSWait();
/** @brief EmuShell FS access release*/
void trlEmuShellsuspendFSRelease();
/** @brief EmuShell Enable Sleep*/
void trlEmuShellsupendEnableSleep();
/** @brief EmuShell Disable Sleep*/
void trlEmuShellsupendDisableSleep();
/** @brief EmuShell Disable HomeButton*/
void trlEmuShellSuspendEnableHomeButton();
/** @brief EmuShell Enable HomeButton*/
void trlEmuShellSuspendDisableHomeButton();
/** @brief EmuShell Proc HomeButton*/
u32 trlEmuShellSuspendProcHomeButton(u32 inMenu);
#endif

enum ETrlQuit
{
	eTrlQuit_NONE = 0,
	eTrlQuit_ReBoot,
	eTrlQuit_QuitApplication,
	eTrlQuit_AfterBoot,
	eTrlQuit_Close
};

enum ETrlSuspendMenuState
{
	eTrlSuspendMenuState_Normal = 0,
	eTrlSuspendMenuState_VCM,
	eTrlSuspendMenuState_VCM_ERROR,
	eTrlSuspendMenuState_Init
};

enum ETRLEMUSHELLHOMENIXSTATE
{
	eTrlEmuShell_HomeNixState_None = 0,
	eTrlEmuShell_HomeNixState_Open,
	eTrlEmuShell_HomeNixState_Anim,
	eTrlEmuShell_HomeNixState_Open_UP,
	eTrlEmuShell_HomeNixState_Anim_UP
};
extern u32								g_bTrlEmuMenuHomeNixState;

#ifdef TRL_PLATFORM_PC
#define trlEmuShellsuspendFSWait()  ((void)0)
#define trlEmuShellsuspendFSRelease()  ((void)0)
#define trlEmuShellsupendEnableSleep()  ((void)0)
#define trlEmuShellsupendDisableSleep()  ((void)0)

#define trlEmuShellSuspendInit0() ((void)0)
#define trlEmuShellSuspendInit1() ((void)0)
#define trlEmuShellSuspendMain(n) ((void)0)
#define trlEmuShellSuspendExit0() ((void)0)
#define trlEmuShellSuspendExit1() ((void)0)
#endif


