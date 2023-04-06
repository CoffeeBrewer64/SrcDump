/**
 * @file trlEmuShellMenu.h
 * @author zhfang
 * @date 2011.03.30
 * @brief TRL Emulate - EmuShell Menu Module
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
enum MENU_SWITCHGBCOLOR_STATE
{
	MENU_SWITCHGBCOLOR_CLOSED = 0,
	MENU_SWITCHGBCOLOR_OPEN,
	MENU_SWITCHGBCOLOR_SWITCH,
	MENU_SWITCHGBCOLOR_SWITCHING,
	MENU_SWITCHGBCOLOR_CLOSE
};
//@}

enum ETrlEmuShellMenuResult
{
	eTrlEmuShellMenuResult_End,
	eTrlEmuShellMenuResult_Continue
};
extern MENU_SWITCHGBCOLOR_STATE		g_nTrlEmuMenuSwitchGBColorState;

/** @brief EmuShell Menu Init */
void trlEmuShellMenuInit();

/** @brief EmuShell Menu Draw before game run*/
void trlEmuShellMenuDrawBeforeGameRun();
/** @brief EmuShell Menu Open*/
void trlEmuShellMenuOpen();
/** @brief EmuShell Menu Touch In Open*/
s32 trlEmuShellMenuTouchIn();
/** @brief EmuShell Menu Run*/
s32 trlEmuShellMenuRun(); //return 0: continue   1:  menu end

void trlEmuShellMenuSetParam(u32 SkipFadeIn, u32 HaveBreakSave);

/** @brief EmuShell Menu Switch Color Main run one per frame*/
void trlEmuShellMenuSwitchColor();

////////Error Menu
#ifdef TRL_PLATFORM_CTR
/** @brief EmuShell Boot Error Menu Open*/
void trlEmuShellBootErrorMenuOpen(s32 nResult);
s32 trlEmuShellBootErrorMenuMain();

/** @brief EmuShell FS Error Menu Open*/
void trlEmuShellFsErrorMenuOpen(s32 nResult);
s32 trlEmuShellFsErrorMenuMain();
s32 trlEmuShellMenuHomeNix();
#endif

#ifdef TRL_PLATFORM_PC
#define trlEmuShellMenuDrawBeforeGameRun() ((void)0)
#define trlEmuShellMenuSwitchColor() ((void)0)
#define trlEmuShellMenuTouchIn() ((s32)0)

#define trlEmuShellMenuSetParam(m,n) ((void)0)
#define trlEmuShellMenuOpen() ((void)0)
#define trlEmuShellMenuRun() ((s32)0)

#define trlEmuShellMenuHomeNix() ((s32)0)


#define trlEmuShellBootErrorMenuOpen(n) ((void)0)
#define trlEmuShellBootErrorMenuMain() ((s32)0)

#define trlEmuShellFsErrorMenuOpen(n) ((void)0)
#define trlEmuShellFsErrorMenuMain() ((s32)0)
#endif


