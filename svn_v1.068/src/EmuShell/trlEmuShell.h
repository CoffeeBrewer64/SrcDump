/**
 * @file trlEmuShell.h
 * @author zhfang, chentian
 * @date 2009.11.24
 * @brief TRL Emulate - EmuShell Main
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
#define TRL_EMU_BOOTERROR 0
#define TRL_EMU_FSERROR 1
//@}

/** @name Global Variable */
//@{
extern s32 g_eTrlEmuShellState;
extern s32 g_bTrlEmuBootError;
extern s32 g_bTrlEmuNetRole;
//@}

enum ETrlEmuShellState
{
	eTrlEmuShellStateInitSleep,
	eTrlEmuShellStateEnableSleep,
	eTrlEmuShellStateInitShell,
	eTrlEmuShellStateSwitchRomCheck,
	eTrlEmuShellStateInitSave,
	eTrlEmuShellStateLoadBackup,
	eTrlEmuShellStateStartAutoSave,
	eTrlEmuShellStateCheckResume,
	eTrlEmuShellStateLoadResume,		
	eTrlEmuShellStateGameRun,
	eTrlEmuShellStateGameRunNet,
	eTrlEmuShellStateVCMOpen,
	eTrlEmuShellStateVCMMain,
	eTrlEmuShellStateVCMClose,
	eTrlEmuShellStateDebugMenuOpen,
	eTrlEmuShellStateDebugMenuMain,
	eTrlEmuShellStateDebugMenuClose,
	eTrlEmuShellStateNetStartFromDebugMenu,
	eTrlEmuShellStateNetStartGame,
	eTrlEmuShellStateNetStartGameSync,
	eTrlEmuShellStateNetSync,
	eTrlEmuShellStateBootDataErrorOpen,
	eTrlEmuShellStateBootDataErrorMain,
	eTrlEmuShellStateBootDataErrorClose,
	eTrlEmuShellStateFSDataErrorOpen,
	eTrlEmuShellStateFSDataErrorMain,
	eTrlEmuShellStateFSDataErrorClose,
	eTrlEmuShellStateNetChildInit,
	eTrlEmuShellStateExit,
	eTrlEmuShellStateExitSleep	
};

enum ETrlEmuNetRole
{
	eTrlEmuNetNone = -1,
	eTrlEmuNetMaster = 0,
	eTrlEmuNetSlave
};

/** @brief EmuShell Main */
void trlEmuShellMain();
/** @brief EmuShell Exit */
void trlEmuShellExit();
/** @brief EmuShell Input */
void trlEmuShellInput(u32 nKey, u32 nPush);
