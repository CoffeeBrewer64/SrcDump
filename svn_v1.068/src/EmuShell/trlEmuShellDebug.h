/**
 * @file trlEmuShellDebug.h
 * @author zhfang, Chentian
 * @date 2010.03.15
 * @brief TRL Emulate - EmuShell Debug Module
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u8	g_bMenuOpen;
extern s32	g_nFrameTime;
extern s32	g_nFrameTimeV;
extern s32	g_nMaxTime;
extern s32	g_nMaxTimeV;
extern s32  g_nTrlEmuSoundOn;
//@}

/** @brief EmuShell Debug Init */
void trlEmuShellDebugInit();
/** @brief EmuShell Debug Menu Update */
void trlEmuShellDebugMenuUpdate(u16 nInput, u16 nHold);
/** @brief EmuShell Debug Menu Draw*/
void trlEmuShellDebugMenuDraw();
/** @brief EmuShell Debug Info Update */
void trlEmuShellDebugInfoUpdate();

void trlEmuShellOpenDebugMenu();
void trlEmuShellOpenColorMenu();
void trlEmushellOpenSwitchRom();
inline int trlEmuShellMenuOpened()	{ return (g_bMenuOpen != 0); }
inline int trlEmuShellDebugMenuOpened()	{ return (g_bMenuOpen == 1); }
inline int trlEmuShellColorMenuOpened() { return (g_bMenuOpen == 2); }

