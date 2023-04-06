/**
 * @file agbGlobal.h
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Global data
 */
#pragma once
#include "..\EmuShell\trlEmuShellStruct.h"

/** @name Macro Define */
//@{
//@}

/**
 * @class agbSROMHeader
 * @brief The Cartridge Header (0x0000-0x00C0)
 */
struct agbSROMHeader
{
	u8		nEntry[4];					///< Start Address (0000-0003)
	u8		nLogo[156];					///< Nintendo Logo Character Data (0004-009F)
	u8		nTitle[12];					///< Game Title (00A0-00AB)
	u8		nGameCode[4];				///< Game Code (00AC-00AF)
	u8		nMakerCode[2];				///< Maker Code (00B0-00B1)
	u8		nFixedCode;					///< Store the fixed code '96h' (00B2)
	u8		nMainUnitCode;				///< Main Unit Code (00B3)
	u8		nDeviceType;				///< Device Type (00B4)
	u8		nReservedArea1[7];			///< Reserved Area 1 (00B5-00BB)
	u8		nVersion;					///< Mask ROM Version No. (00BC)
	u8		nCheck;						///< Complement Check (00BD)
	u8		nReservedArea2[2];			///< Reserved Area 2 (00BE-00BF)
};

/** @name Global Variable */
//@{
extern u8* g_pAgbSROM;					///< System ROM (16 Kbytes)
extern u8* g_pAgbEWRAM;					///< CPU External Working RAM (256 Kbytes)
extern u8* g_pAgbIWRAM;					///< CPU Internal Working RAM (32 Kbytes)
extern u8* g_pAgbREG;					///< I/O and Registers
extern u8* g_pAgbPRAM;					///< Palette RAM (1 Kbyte)
extern u8* g_pAgbVRAM;					///< VRAM (96 Kbyte)
extern u8* g_pAgbOAM;					///< OAM (1 Kbyte)
extern u8* g_pAgbGPROM;					///< Game Pak ROM
extern u8* g_pAgbGPRAM;					///< Game Pak RAM

extern agbSROMHeader* g_pAgbROMHeader;	///< The Cartridge Header Data
extern trlSEmuShellBuffer *g_pAgbEmuBuf;///< Emulate Shell Buffer
extern u32 g_nAgbBreakFlag;				///< Break Flag
//@}
