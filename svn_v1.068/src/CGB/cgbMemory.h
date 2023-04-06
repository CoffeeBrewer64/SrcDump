/**
 * @file cgbMemory.h
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Memory Map
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#define CGB_MEM_SAVEDATA	4										///< Memory Save Data Count
//@}

/** @name Global Variable */
//@{
extern u8*					g_pCgbCurVRAM;							///< Current Video RAM Bank
extern u8*					g_pCgbCurWRAM;							///< Current Work RAM Bank
extern trlSEmuShellResume	g_sCgbMemSaveData[CGB_MEM_SAVEDATA];	///< Memory Save Data
//@}

/** @brief Initialize Memory */
void cgbMemInit();
/** @brief Reset Memory */
void cgbMemReset();
/** @brief Resume Memory */
void cgbMemResume();
/** @brief Exit Memory */
void cgbMemExit();

/** @brief Read Data From Memory Map - 8 Bit */
u8 cgbMemRead8(u16 nAddr);
/** @brief Write Data to Memory Map - 8 Bit */
void cgbMemWrite8(u16 nAddr, u8 nValue);
/** @brief Read Data From Memory Map - 16 Bit */
u16 cgbMemRead16(u16 nAddr);
/** @brief Write Data to Memory Map - 16 Bit */
void cgbMemWrite16(u16 nAddr, u16 nValue);
/** @brief Read Opcode From Memory Map */
u8* cgbMemReadOpcode(u16 nAddr);
