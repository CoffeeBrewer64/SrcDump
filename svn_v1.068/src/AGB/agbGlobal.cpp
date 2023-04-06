/**
 * @file agbGlobal.cpp
 * @author Chentian
 * @date 2009.11.24
 * @brief AGB Emulate For CTR - Global data
 */
#include "agbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u8* g_pAgbSROM = NULL;						///< System ROM (16 Kbytes)
u8* g_pAgbEWRAM = NULL;						///< CPU External Working RAM (256 Kbytes)
u8* g_pAgbIWRAM = NULL;						///< CPU Internal Working RAM (32 Kbytes)
u8* g_pAgbREG = NULL;						///< I/O and Registers
u8* g_pAgbPRAM = NULL;						///< Palette RAM (1 Kbyte)
u8* g_pAgbVRAM = NULL;						///< VRAM (96 Kbyte)
u8* g_pAgbOAM = NULL;						///< OAM (1 Kbyte)
u8* g_pAgbGPROM = NULL;						///< Game Pak ROM
u8* g_pAgbGPRAM = NULL;						///< Game Pak RAM

agbSROMHeader* g_pAgbROMHeader = NULL;		///< The Cartridge Header Data
u32 g_nAgbBreakFlag = 0;					///< Break Flag
//@}
