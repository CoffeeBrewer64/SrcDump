/**
 * @file nesInput.cpp
 * @author Chentian
 * @date 2010.06.25
 * @brief NES Emulate For CTR - Input
 */
#include "nesGlobal.h"
#include "nesInput.h"
#include "..\EmuShell\trlEmuShellNetwork.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u32						g_nNesInputCount;								///< Input Count
u8						g_nNesInputReg;									///< Input Register
u8						g_nNesInputMic;									///< Input Mic
u8						g_nNesInputBit[2];								///< Bit Count
u8						g_nNesInputJoy[4];								///< Joypad Buffer
u8						g_nNesInputBuf[4];								///< Input Buffer
u32						g_nNesInputSaveData;							///< Input Save Data Count
trlSEmuShellResume		g_sNesInputSaveData[NES_INPUT_SAVEDATA_MAX];	///< Input Save Data
u32						g_nNesInputMask;								///< Input 2P Mask
extern u32				g_nNesEmuSwitchPlayer;							///< Switch Player
//@}

/** @brief Initialize */
void nesInputInit()
{
	g_nNesInputCount = g_pNesEmuBuf->funcConfigData("NES", "MultiPlayer", 2);
	g_nNesInputMask = g_pNesEmuBuf->funcConfigData("NES", "JoypadType", 1) ? 0xFF : 0xF3;

	// Save Data
	g_nNesInputSaveData = 0;
	g_sNesInputSaveData[g_nNesInputSaveData++].SetData(&g_nNesInputReg, 1, 1, 0);
	g_sNesInputSaveData[g_nNesInputSaveData++].SetData(g_nNesInputBit, 2, 1, 0);
	g_sNesInputSaveData[g_nNesInputSaveData++].SetData(g_nNesInputJoy, 4, 1, 0);

	nesInputReset();
}

/** @brief Reset */
void nesInputReset()
{
	g_nNesInputMic = 0;
	g_nNesInputBit[0] = 0;
	g_nNesInputBit[1] = 0;
	for(u32 n=0; n<4; ++n)
	{
		g_nNesInputJoy[n] = 0;
		g_nNesInputBuf[n] = 0;
	}
}

/** @brief Resume */
void nesInputResume()
{
	g_nNesInputMic = 0;
	for(u32 n=0; n<4; ++n)
		g_nNesInputBuf[n] = 0;
}

/** @brief Update */
void nesInputUpdate(u32 nKeyBuf)
{	
#if TRL_HVC_SWITCHPLAYER
	if(g_nNesEmuSwitchPlayer && g_pNesEmuBuf->nNetworkState == TRL_NETWORK_STATE_NONE)
	{
		nKeyBuf <<= 8;
	}
#endif

	for(u32 n=0; n<g_nNesInputCount; ++n)
	{
		g_nNesInputBuf[n] = nKeyBuf & 0xFF;
		nKeyBuf >>= 8;
	}
	g_nNesInputBuf[1] &= g_nNesInputMask;
	
	nesInputRegisterWrite();
}
