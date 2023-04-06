/**
 * @file agbInput.h
 * @author Chentian
 * @date 2009.12.08
 * @brief AGB Emulate For CTR - Key Input
 */
#pragma once
#include "agbRegister.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}

/** @brief Initialize Key Input */
void agbKeyInit();
/** @brief Reset Key Input */
void agbKeyReset();

/** @brief Update Key Input */
inline void agbKeyUpdate(u32 nKeyBuf)
{
	nKeyBuf = (~nKeyBuf) & 0x03FF;
	if(g_pAgbKeyInput->rButtons == nKeyBuf)
		return;
	g_pAgbKeyInput->rButtons = nKeyBuf;
	if(g_pAgbKeyCnt->rIntEnable)
	{
		nKeyBuf = ~nKeyBuf;
		if(g_pAgbKeyCnt->rIntConditions)	// Logical Multiplication (AND) Operation
		{
			if((nKeyBuf & g_pAgbKeyCnt->rButtons) == g_pAgbKeyCnt->rButtons)
				g_pAgbIF->rKey = 1;
		}
		else								// Logical Addition (OR) Operation
		{
			if(nKeyBuf & g_pAgbKeyCnt->rButtons)
				g_pAgbIF->rKey = 1;
		}
	}
}
