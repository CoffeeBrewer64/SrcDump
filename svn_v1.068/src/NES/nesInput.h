/**
 * @file nesInput.h
 * @author Chentian
 * @date 2010.06.25
 * @brief NES Emulate For CTR - Input
 */
#pragma once
#include "nesGlobal.h"

/** @name Macro Define */
//@{
#define	NES_INPUT_SAVEDATA_MAX	5												///< Input Save Data Count
//@}

/** @name Global Variable */
//@{
extern u32						g_nNesInputCount;								///< Input Count
extern u8						g_nNesInputReg;									///< Input Register
extern u8						g_nNesInputMic;									///< Input Mic
extern u8						g_nNesInputBit[2];								///< Bit Count
extern u8						g_nNesInputJoy[4];								///< Joypad Buffer
extern u8						g_nNesInputBuf[4];								///< Input Buffer
extern u32						g_nNesInputSaveData;							///< Input Save Data Count
extern trlSEmuShellResume		g_sNesInputSaveData[NES_INPUT_SAVEDATA_MAX];	///< Input Save Data
//@}

/** @brief Initialize */
void nesInputInit();
/** @brief Reset */
void nesInputReset();
/** @brief Resume */
void nesInputResume();
/** @brief Update */
void nesInputUpdate(u32 nKeyBuf);

/** @brief Joypads Register Write */
inline void nesInputRegisterWrite()
{
	if(g_nNesInputReg & 0x1)
	{
		g_nNesInputBit[0] = 0;
		g_nNesInputBit[1] = 0;

		for(u32 n=0; n<g_nNesInputCount; ++n)
		{
			if(g_nNesInputBuf[n])
				g_nNesInputJoy[n] = (g_nNesInputBuf[n] & 0x0F) + ((g_nNesInputBuf[n]>>2) & 0x30) + ((g_nNesInputBuf[n]<<1) & 0x40) + ((g_nNesInputBuf[n]<<3) & 0x80);
			else
				g_nNesInputJoy[n] = 0;
		}
	}
}

/** @brief Joypads Register Read */
inline u8 nesInputRegisterRead(u32 nJoyID)
{
	if(g_nNesInputBit[nJoyID]>=8)
	{
		if(g_nNesInputCount > (nJoyID+2))
			return 3;
		if(g_nNesInputCount > nJoyID)
			return 1;
		return 0;
	}

	u8 nData = (g_nNesInputJoy[nJoyID] >> g_nNesInputBit[nJoyID]) & 0x1;
	if(g_nNesInputCount > (nJoyID+2))
		nData |= ((g_nNesInputJoy[nJoyID+2] >> g_nNesInputBit[nJoyID]) & 0x1) << 1;
	g_nNesInputBit[nJoyID]++;
	return nData;
}
