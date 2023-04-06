/**
 * @file cgbInput.cpp
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - Key Input
 */
#include "cgbInput.h"
#include "cgbRegister.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u32				g_nCgbKeyBuffer;			///< Key Buffer
//@}

/** @brief Initialize Key Input */
void cgbKeyInit()
{
	cgbKeyReset();
}

/** @brief Reset Key Input */
void cgbKeyReset()
{
	g_nCgbKeyBuffer = 0xFFFF;
}

/** @brief Resume Key Input */
void cgbKeyResume()
{
	g_nCgbKeyBuffer = 0xFFFF;
}

/** @brief Update Key Input */
void cgbKeyUpdate(u32 nKeyBuf)
{
	g_nCgbKeyBuffer = ~nKeyBuf;
	if(!g_pCgbRegJOYP->rButton)
		g_pCgbRegJOYP->rKey = (g_nCgbKeyBuffer & 0x0F);
	else if(!g_pCgbRegJOYP->rDirection)
		g_pCgbRegJOYP->rKey = ((g_nCgbKeyBuffer>>4) & 0x0F);
	else
		g_pCgbRegJOYP->rKey = 0x0F;

	if(g_pCgbRegJOYP->rKey != 0x0F)
		g_pCgbRegIF->rJoypad = 1;
	if(g_nCgbKeyBuffer != 0xFF)
	{
		if(g_nCgbCpuState & CGB_CPU_STOP)
			g_nCgbCpuState &= ~CGB_CPU_STOP;
	}
}
