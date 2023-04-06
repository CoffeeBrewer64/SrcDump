/**
 * @file cgbSerial.cpp
 * @author Chentian
 * @date 2010.01.18
 * @brief CGB Emulate For CTR - Serial
 */
#include "cgbSerial.h"
#include "cgbRegister.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
s32					g_nCgbSerialTicks = 0;						///< Serial Ticks
s32					g_nCgbSerialTick0 = CGB_SERIAL_TICKS0;		///< Serial Interval Ticks
s32					g_nCgbSerialBits = 0;						///< Serial Transfer Bit Count
trlSEmuShellResume	g_sCgbSerialSaveData[CGB_SERIAL_SAVEDATA];	///< Serial Save Data
//@}

/** @brief Initialize Serial */
void cgbSerialInit()
{
	// Save Data
	g_sCgbSerialSaveData[0].SetData(&g_nCgbSerialTicks, 4, 1, 0);
	g_sCgbSerialSaveData[1].SetData(&g_nCgbSerialBits, 4, 1, 0);

	cgbSerialReset();
}

/** @brief Reset Serial */
void cgbSerialReset()
{
	g_nCgbSerialBits = 0;
}

/** @brief Resume Serial */
void cgbSerialResume()
{
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		if(g_pCgbRegSC->rClockSpeed)
			g_nCgbSerialTick0 = CGB_SERIAL_TICKS1;
		else
			g_nCgbSerialTick0 = CGB_SERIAL_TICKS0;
	}
	else
		g_nCgbSerialTick0 = CGB_SERIAL_TICKS0;
}

/** @brief Update Serial */
void cgbSerialUpdate()
{
	++g_nCgbSerialBits;
	if(g_nCgbSerialBits == 8)
	{
		*g_pCgbRegSB = 0xFF;
		g_nCgbSerialTicks = 0;
		g_pCgbRegSC->rTransfer = 0;
		g_pCgbRegIF->rSerial = 1;
		g_nCgbSerialBits  = 0;
	}
}
