/**
 * @file trlEmuShellInput.h
 * @author zhfang, chentian
 * @date 2011.03.31
 * @brief TRL Emulate - EmuShell Input Module
 */
#pragma once
#include "..\trlHeader.h"
#include "trlEmuShellStruct.h"

/** @name Macro Define */
//@{
#define TRL_INPUT_BUTTON_VALUE				0
#define TRL_INPUT_BUTTON_TRIGGER			1
#define TRL_INPUT_BUTTON_RELEASE			2
#define TRL_INPUT_BUTTON_HOLD				3
#define TRL_INPUT_BUTTON_MAX				4

#define TRL_INPUT_TOUCH_VALUE				0
#define TRL_INPUT_TOUCH_TRIGGER				1
#define TRL_INPUT_TOUCH_RELEASE				2
#define TRL_INPUT_TOUCH_X					3
#define TRL_INPUT_TOUCH_Y					4
#define TRL_INPUT_TOUCH_MAX					5

#define TRL_INPUT_KEY_CLEARTIME				0
#define TRL_INPUT_KEY_SWITCHDISK			1
#define TRL_INPUT_KEY_SWITCHICON			2
#define TRL_INPUT_KEY_GBCOLORSWITCH			3
#define TRL_INPUT_KEY_GBCOLORMENU			4
#define TRL_INPUT_KEY_DEBUGMENU				5
#define TRL_INPUT_KEY_COLORMENU				6
#define TRL_INPUT_KEY_MAX					7

#define TRL_INPUT_AUTOFIRE_HOLD				0
#define TRL_INPUT_AUTOFIRE_RELEASE			1
#define TRL_INPUT_AUTOFIRE_MAX				2

#define TRL_INPUT_BUTTON_A					0x00000001
#define TRL_INPUT_BUTTON_B					0x00000002
#define TRL_INPUT_BUTTON_SELECT				0x00000004
#define TRL_INPUT_BUTTON_START				0x00000008
#define TRL_INPUT_BUTTON_RIGHT				0x00000010
#define TRL_INPUT_BUTTON_LEFT				0x00000020
#define TRL_INPUT_BUTTON_UP					0x00000040
#define TRL_INPUT_BUTTON_DOWN				0x00000080
#define TRL_INPUT_BUTTON_R					0x00000100
#define TRL_INPUT_BUTTON_L					0x00000200
#define TRL_INPUT_BUTTON_X					0x00000400
#define TRL_INPUT_BUTTON_Y					0x00000800
//@}

/** @name Global Variable */
//@{
extern u32		g_nTrlInputButton[TRL_INPUT_BUTTON_MAX];
extern u32		g_nTrlInputTouch[TRL_INPUT_TOUCH_MAX];
extern u32		g_nTrlInputKey[TRL_INPUT_KEY_MAX];

extern u32		g_nTrlInputDebugMenuCt;
extern u32		g_nTrlInputColorMenuCt;
extern u32		g_nTrlInputGBColorMenuCt;
extern u32		g_nTrlInputMenuDelay;	
extern u32		g_nTrlInputGBColorDelay;

extern u32		g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_MAX];
extern u32		g_nTrlInputAutoFireState;
extern u32		g_nTrlInputAutoFireIndex;
//@}


/** @brief EmuShell Input Init */
void trlEmuShellInputInit();
/** @brief EmuShell Input Exit */
void trlEmuShellInputExit();
/** @brief EmuShell Input Update */
u32 trlEmuShellInputUpdate();

#if TRL_NETWORK_PIA_WITH_MIC
void trlEmuShellInputUpdateMicrophone();
#endif

/** @brief EmuShell Input Advance Function */
inline void trlEmuShellInputAdvanceFunction()
{
	g_nTrlInputKey[TRL_INPUT_KEY_CLEARTIME] = g_nTrlInputButton[TRL_INPUT_BUTTON_TRIGGER] & TRL_INPUT_BUTTON_L;
	g_nTrlInputKey[TRL_INPUT_KEY_SWITCHDISK] = g_nTrlInputButton[TRL_INPUT_BUTTON_TRIGGER] & TRL_INPUT_BUTTON_R;
	g_nTrlInputKey[TRL_INPUT_KEY_GBCOLORSWITCH] = g_nTrlInputButton[TRL_INPUT_BUTTON_TRIGGER] & TRL_INPUT_BUTTON_Y;
	
	g_nTrlInputKey[TRL_INPUT_KEY_DEBUGMENU] = 0;
	if(g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] == TRL_INPUT_BUTTON_L)
	{
		if(g_nTrlInputDebugMenuCt >= g_nTrlInputMenuDelay)
			g_nTrlInputKey[TRL_INPUT_KEY_DEBUGMENU] = 1;
		else
			g_nTrlInputDebugMenuCt++;
	}
	else
		g_nTrlInputDebugMenuCt = 0;

	g_nTrlInputKey[TRL_INPUT_KEY_COLORMENU] = 0;
	if(g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] == TRL_INPUT_BUTTON_R)
	{
		if(g_nTrlInputColorMenuCt >= g_nTrlInputMenuDelay)
			g_nTrlInputKey[TRL_INPUT_KEY_COLORMENU] = 1;
		else
			g_nTrlInputColorMenuCt++;		
	}
	else
		g_nTrlInputColorMenuCt = 0;	

	g_nTrlInputKey[TRL_INPUT_KEY_GBCOLORMENU] = 0;
	if ((g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] & TRL_INPUT_BUTTON_L) && (g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] & TRL_INPUT_BUTTON_R))
	{
		g_nTrlInputKey[TRL_INPUT_KEY_SWITCHICON] = 1;
		if(g_nTrlInputGBColorMenuCt >= g_nTrlInputGBColorDelay)
			g_nTrlInputKey[TRL_INPUT_KEY_GBCOLORMENU] = 1;
		else
			g_nTrlInputGBColorMenuCt++;
	}
	else
	{
		g_nTrlInputKey[TRL_INPUT_KEY_SWITCHICON] = 0;
		g_nTrlInputGBColorMenuCt = 0;
	}
}

/** @brief EmuShell Input Get Game Button */
inline u32 trlEmuShellInputGetGameButton()
{
	u32 nPad = g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] & g_sEmuShellBuffer.nKeyMask;
	if(g_nTrlInputAutoFireFrame[TRL_INPUT_AUTOFIRE_HOLD])
	{
		if(nPad)
		{
			g_nTrlInputAutoFireIndex++;
			if(g_nTrlInputAutoFireIndex >= g_nTrlInputAutoFireFrame[g_nTrlInputAutoFireState])
			{
				g_nTrlInputAutoFireState = 1 - g_nTrlInputAutoFireState;
				g_nTrlInputAutoFireIndex = 0;
			}
			if(g_nTrlInputAutoFireState == TRL_INPUT_AUTOFIRE_RELEASE)
				nPad = 0;
		}
		else
		{
			g_nTrlInputAutoFireState = TRL_INPUT_AUTOFIRE_HOLD;
			g_nTrlInputAutoFireIndex = 0;
		}
	}

	return nPad&0xFF;
}

inline u32 trlEmuShellInputGetButton(u32 nIndex)	{return g_nTrlInputButton[nIndex];}
inline u32 trlEmuShellInputGetTouch(u32 nIndex)		{return g_nTrlInputTouch[nIndex];}
inline u32 trlEmuShellInputGetKey(u32 nIndex)		{return g_nTrlInputKey[nIndex];}
