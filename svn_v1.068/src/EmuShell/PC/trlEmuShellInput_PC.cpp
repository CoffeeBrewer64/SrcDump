/**
 * @file trlEmuShellInput_PC.h
 * @author zhfang, chentian
 * @date 2011.03.31
 * @brief TRL Emulate - EmuShell Input Module for PC
 */
#include "..\trlEmuShellInput.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u16	g_nKeyBuf;
//@}

/** @brief EmuShell Input Init */
void trlEmuShellInputInitDevice()
{
}

/** @brief EmuShell Input Exit */
void trlEmuShellInputExitDevice()
{
}

/** @brief EmuShell Input Update Button */
inline void trlEmuShellInputUpdateButton()
{
	u32 nPrev = g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE];
	g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] = (~g_nKeyBuf) & 0xFFFF;
	g_nTrlInputButton[TRL_INPUT_BUTTON_TRIGGER] = (g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] & ~nPrev);
	g_nTrlInputButton[TRL_INPUT_BUTTON_RELEASE] = (~g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] & nPrev);
	g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] = (g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] & nPrev);
}

/** @brief EmuShell Input Update */
u32 trlEmuShellInputUpdate()
{
	trlEmuShellInputUpdateButton();
	trlEmuShellInputAdvanceFunction();
	
	return trlEmuShellInputGetGameButton();
}
