/**
 * @file nesGlobal.h
 * @author Chentian
 * @date 2010.06.24
 * @brief NES Emulate For CTR - Global data
 */
#pragma once
#include "..\EmuShell\trlEmuShellStruct.h"

/** @name Macro Define */
//@{
//@}

/**
 * @class nesSROMHeader
 * @brief The Cartridge Header
 */
struct nesSROMHeader
{
	u32		nFlag;						///< Flag "TNES"
	u8		nMapper;					///< Mapper Number
	u8		nPRGBanks;					///< Number of 8K PRG-ROM Banks
	u8		nCHRBanks;					///< Number of 8K CHR-ROM Banks
	u8		nSRAMBanks;					///< Number of 8K SRAM Banks
	u8		nNameTabMapping;			///< Name Table Mapping Type
	u8		nBattery;					///< Support Battery
	u8		nSideNumber;				///< Number of Sides
	u8		nCRC;						///< CRC Enable Flag
	u32		nPadding;
};

/** @name Global Variable */
//@{
extern u8*					g_pNesPRGROM;		///< PRG Cartridge
extern u8*					g_pNesCHRROM;		///< CHR Cartridge
extern u8*					g_pNesWRAM;			///< Work RAM
extern u8*					g_pNesVRAM;			///< Video RAM
extern u8*					g_pNesSPRRAM;		///< Sprite Attribute Table
extern u8*					g_pNesPALRAM;		///< Palette RAM
extern u8*					g_pNesSRAM;			///< SRAM
extern u8*					g_pNesPRGBank[4];	///< PRG Banks
extern u8*					g_pNesCHRBank[12];	///< CHR Banks
extern u8*					g_pNesSRAMBank;		///< SRAM Bank

extern u8					g_nPPUCHRRAM;			///< PPU CHR RAM write enable flag

extern nesSROMHeader*		g_pNesROMHeader;	///< The Cartridge Header Data
extern trlSEmuShellBuffer*	g_pNesEmuBuf;		///< Emulate Shell Buffer
extern u32					g_nNesBreakFlag;	///< Break Flag

extern s32					g_nNesCpuEventTicks;///< Next Event Ticks
extern s32					g_nNesCpuTicks;		///< CPU Run Ticks
extern s32					g_nNesGrpTicks;		///< PPU Ticks
extern s32					g_nNesSndTicks;		///< APU Ticks
//@}
