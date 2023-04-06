/**
 * @file cgbSerial.h
 * @author Chentian
 * @date 2010.01.18
 * @brief CGB Emulate For CTR - Serial
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#define	CGB_SERIAL_TICKS0	128						///< Serial Ticks - Normal
#define	CGB_SERIAL_TICKS1	4						///< Serial Ticks - Fast
#define CGB_SERIAL_SAVEDATA	2						///< Serial Save Data Count
//@}

/** @name Global Variable */
//@{
extern s32					g_nCgbSerialTick0;		///< Serial Interval Ticks
extern s32					g_nCgbSerialBits;		///< Serial Transfer Bit Count
extern trlSEmuShellResume	g_sCgbSerialSaveData[CGB_SERIAL_SAVEDATA];	///< Serial Save Data
//@}

/** @brief Initialize Serial */
void cgbSerialInit();
/** @brief Reset Serial */
void cgbSerialReset();
/** @brief Resume Serial */
void cgbSerialResume();
/** @brief Update Serial */
void cgbSerialUpdate();
