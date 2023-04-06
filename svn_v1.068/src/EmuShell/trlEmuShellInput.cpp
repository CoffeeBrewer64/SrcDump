/**
 * @file trlEmuShellInput.h
 * @author zhfang, chentian
 * @date 2011.03.31
 * @brief TRL Emulate - EmuShell Input Module
 */
#include "trlEmuShellInput.h"
#include "trlEmuShellData.h"
#include "trlEmuShellStruct.h"

/** @name Global Variable */
//@{
u32		g_nTrlInputButton[TRL_INPUT_BUTTON_MAX];
u32		g_nTrlInputTouch[TRL_INPUT_TOUCH_MAX];
u32		g_nTrlInputKey[TRL_INPUT_KEY_MAX];

u32		g_nTrlInputDebugMenuCt;
u32		g_nTrlInputColorMenuCt;
u32		g_nTrlInputGBColorMenuCt;
u32		g_nTrlInputMenuDelay;	
u32		g_nTrlInputGBColorDelay;

u32		g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_MAX];
u32		g_nTrlInputAutoFireState;
u32		g_nTrlInputAutoFireIndex;
//@}

void trlEmuShellInputInitDevice();
void trlEmuShellInputExitDevice();

/** @brief EmuShell Input Init */
void trlEmuShellInputInit()
{
	trlEmuShellInputInitDevice();

	// Init Data
	memset(g_nTrlInputButton, 0, TRL_INPUT_BUTTON_MAX*sizeof(u32));
	memset(g_nTrlInputTouch, 0, TRL_INPUT_TOUCH_MAX*sizeof(u32));
	memset(g_nTrlInputKey, 0, TRL_INPUT_KEY_MAX*sizeof(u32));

	g_nTrlInputDebugMenuCt = 0;
	g_nTrlInputColorMenuCt = 0;
	g_nTrlInputGBColorMenuCt = 0;

	g_nTrlInputMenuDelay = (u32)(trlEmuShellDataGetConfigData("Menu", "MenuDelay", 200) / 16.6666f);
	g_nTrlInputGBColorDelay = (u32)(trlEmuShellDataGetConfigData("Menu", "SwitchDelay", 200) / 16.6666f);
	g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_HOLD] = trlEmuShellDataGetConfigData("Input", "AutoFireHold", 0);
	g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_RELEASE] = trlEmuShellDataGetConfigData("Input", "AutoFireRelease", 1);
	g_nTrlInputAutoFireState = TRL_INPUT_AUTOFIRE_HOLD;
	g_nTrlInputAutoFireIndex = 0;
}

/** @brief EmuShell Input Exit */
void trlEmuShellInputExit()
{
	trlEmuShellInputExitDevice();
}
