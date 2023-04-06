/**
 * @file cgbTime.cpp
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - Time
 */
#include "cgbTime.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
const u8			g_nCgbTimeMask[4] = {0xFF, 0x03, 0x0F, 0x3F};	///< Timer Mask
const u32			g_nCgbTimeTick[4] = {256, 4, 16, 64};			///< Time Interval Ticks
s32					g_nCgbTimeValue = 0;							///< Time Value
s32					g_nCgbTimeTicks = 0;							///< Time Ticks
s32					g_nCgbDivTicks = 0;								///< Div Ticks
trlSEmuShellResume	g_sCgbTimeSaveData[CGB_TIME_SAVEDATA];			///< Time Save Data
//@}

/** @brief Initialize Time */
void cgbTimeInit()
{
	// Save Data
	g_sCgbTimeSaveData[0].SetData(&g_nCgbTimeTicks, 4, 1, 0);
	g_sCgbTimeSaveData[1].SetData(&g_nCgbTimeValue, 4, 1, 0);
	g_sCgbTimeSaveData[2].SetData(&g_nCgbDivTicks, 4, 1, 0);

	cgbTimeReset();
}

/** @brief Reset Time */
void cgbTimeReset()
{
	g_nCgbTimeTicks = 0;
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		g_nCgbDivTicks = 0x19;
		g_nCgbTimeValue = 0x58;
	}
	else
	{
		g_nCgbDivTicks = 0x22;
		g_nCgbTimeValue = 0x61;
	}
}

/** @brief Resume Time */
void cgbTimeResume()
{
}
