/**
 * @file cgbTime.h
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - Time
 */
#pragma once
#include "cgbGlobal.h"
#include "cgbRegister.h"

/** @name Macro Define */
//@{
#define			CGB_DIV_TICKS		64					///< Div Interval Ticks
#define			CGB_TIME_SAVEDATA	3					///< Time Save Data Count
//@}

/** @name Global Variable */
//@{
extern const u8				g_nCgbTimeMask[4];					///< Timer Mask
extern const u32			g_nCgbTimeTick[4];					///< Time Interval Ticks
extern s32					g_nCgbTimeValue;					///< Time Value
extern s32					g_nCgbTimeTicks;					///< Time Ticks
extern s32					g_nCgbDivTicks;						///< Div Ticks
extern trlSEmuShellResume	g_sCgbTimeSaveData[];				///< Time Save Data
//@}

/** @brief Initialize Time */
void cgbTimeInit();
/** @brief Reset Time */
void cgbTimeReset();
/** @brief Resume Time */
void cgbTimeResume();
/** @brief Update Time */
inline void cgbTimeUpdate()
{
	g_nCgbTimeTicks = (g_nCgbTimeValue & g_nCgbTimeMask[g_pCgbRegTAC->rInputClock]) + 1 - g_nCgbCpuTicks;
	while(g_nCgbTimeTicks <= 0)
	{
		if(*g_pCgbRegTIMA == 0xFF)
		{
			*g_pCgbRegTIMA = (*g_pCgbRegTMA);
			g_pCgbRegIF->rTimer = 1;
		}
		else
			++(*g_pCgbRegTIMA);
		g_nCgbTimeTicks += g_nCgbTimeTick[g_pCgbRegTAC->rInputClock];
	};
}
