/**
 * @file cgbGlobal.cpp
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Global data
 */
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u8*				g_pCgbROM = NULL;					///< Cartridge
u8*				g_pCgbWRAM = NULL;					///< Work RAM: GB-8K CGB-32K
u8*				g_pCgbVRAM = NULL;					///< Video RAM: GB-8K CGB-16K
u8*				g_pCgbERAM = NULL;					///< External RAM: In Cartridge
u8*				g_pCgbOAM = NULL;					///< Sprite Attribute Table (OAM)
u8*				g_pCgbHRAM = NULL;					///< High RAM
u8*				g_pCgbREG = NULL;					///< I/O Ports

u32				g_nCgbGameType = CGB_GAMETYPE_DMG;	///< Game Type: 0-DMG 1-CGB
cgbSROMHeader*	g_pCgbROMHeader;					///< The Cartridge Header Data
u32				g_nCgbBreakFlag = 0;				///< Break Flag
cgbSConfigData	g_sCgbConfigData;					///< Config Data
//@}
