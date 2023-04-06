/**
 * @file nesGlobal.cpp
 * @author Chentian
 * @date 2010.06.24
 * @brief NES Emulate For CTR - Global data
 */
#include "nesGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u8*				g_pNesPRGROM = NULL;							///< PRG Cartridge
u8*				g_pNesCHRROM = NULL;							///< CHR Cartridge
u8*				g_pNesWRAM = NULL;								///< Work RAM
u8*				g_pNesVRAM = NULL;								///< Video RAM
u8*				g_pNesSPRRAM = NULL;							///< Sprite Attribute Table
u8*				g_pNesPALRAM = NULL;							///< Palette RAM
u8*				g_pNesSRAM = NULL;								///< SRAM
u8*				g_pNesPRGBank[4] = {0,0,0,0};					///< PRG Banks
u8*				g_pNesCHRBank[12] = {0,0,0,0,0,0,0,0,0,0,0,0};	///< CHR Banks
u8*				g_pNesSRAMBank = NULL;							///< SRAM Bank

nesSROMHeader*	g_pNesROMHeader = NULL;							///< The Cartridge Header Data
u32				g_nNesBreakFlag = 0;							///< Break Flag
//@}
