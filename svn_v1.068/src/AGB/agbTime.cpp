/**
 * @file agbTime.cpp
 * @author Chentian
 * @date 2009.12.08
 * @brief AGB Emulate For CTR - Time
 */
#include "agbTime.h"
#include "agbRegister.h"
#include "agbSound.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
const u32		g_nAgbTimePrescalar[4]	= { 0, 6, 8, 10 };		///< Prescalar based on the system clock
s32				g_nAgbTimeTicks[4]		= { 0, 0, 0, 0 };		///< Timer Ticks Buffer
u16				g_nAgbTimeCounter[4]	= { 0, 0, 0, 0 };		///< Timer Counter Backup
//@}

/** @brief Initialize Time */
void agbTimeInit()
{
	agbTimeReset();
}

/** @brief Reset Time */
void agbTimeReset()
{
	for(s32 n=0; n<4; ++n)
		g_nAgbTimeTicks[n] = 0;
}

/** @brief Update Time */
void agbTimeUpdate(u32 nTicks)
{
	u32 nOverflow = 0;
	for(s32 n=0; n<4; ++n)
	{
		if(g_pAgbTMCntH[n]->rEnable == 0)
			continue;

		if(g_pAgbTMCntH[n]->rCount && n)	// Count-Up Timing
		{
			if(nOverflow & (1<<(n-1))) 
			{
				++(*g_pAgbTMCntL[n]);
				if((*g_pAgbTMCntL[n]) == 0)
				{
					*g_pAgbTMCntL[n] += g_nAgbTimeCounter[n];
					nOverflow |= (1<<n);
					if(n==1)
						agbSndTimerOverflow(n);
					if(g_pAgbTMCntH[n]->rInterrupt)
						g_pAgbIF->rTMR = 1<<n;
				}
			}
		}
		else
		{
			g_nAgbTimeTicks[n] -= nTicks;
			if(g_nAgbTimeTicks[n] <= 0) 
			{
				g_nAgbTimeTicks[n] += (0x10000 - g_nAgbTimeCounter[n]) << g_nAgbTimePrescalar[g_pAgbTMCntH[n]->rPrescalar];
				nOverflow |= (1<<n);
				if(n<2)
					agbSndTimerOverflow(n);
				if(g_pAgbTMCntH[n]->rInterrupt)
					g_pAgbIF->rTMR = 1<<n;
			}
			*g_pAgbTMCntL[n] = 0xFFFF - (g_nAgbTimeTicks[n] >> g_nAgbTimePrescalar[g_pAgbTMCntH[n]->rPrescalar]);
		}
	}
}
