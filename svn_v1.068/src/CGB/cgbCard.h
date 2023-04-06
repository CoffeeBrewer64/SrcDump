/**
 * @file cgbCard.h
 * @author Chentian
 * @date 2009.11.19
 * @brief CGB Emulate For CTR - Cartridge
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#define CGB_CARD_SAVEDATA	19										///< Card Save Data Count
//@}

/** @name Global Variable */
//@{
extern u8*					g_pCgbCurROM;							///< Current ROM Bank
extern u8*					g_pCgbCurERAM;							///< Current External RAM Bank
extern void					(*cgbCardRegister)(u16, u8);			///< Game Card RAM Register Function Pointer
extern void					(*cgbCardWriteRAM)(u16, u8);			///< Game Card RAM Write Function Pointer
extern u8					(*cgbCardReadRAM)(u16);					///< Game Card RAM Read Function Pointer
extern trlSEmuShellResume	g_sCgbCardSaveData[CGB_CARD_SAVEDATA];	///< Card Save Data
//@}

/** @brief Initialize Card */
void cgbCardInit();
/** @brief Reset Card */
void cgbCardReset();
/** @brief Resume Card */
void cgbCardResume();
/** @brief Exit Card */
void cgbCardExit();
