/**
 * @file cgbGlobal.h
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Global data
 */
#pragma once
#include "..\EmuShell\trlEmuShellStruct.h"

/** @name Macro Define */
//@{
#define CGB_GAMETYPE_DMG			0
#define CGB_GAMETYPE_CGB			1
//@}

/**
 * @class cgbSROMHeader
 * @brief The Cartridge Header (0x0100-0x014F)
 */
struct cgbSROMHeader
{
	u8		nEntry[4];					///< Entry Point (0100-0103)
	u8		nLogo[48];					///< Nintendo Logo (0104-0133)
	u8		nTitle[11];					///< Title (0134-013E)
	u8		nManCode[4];				///< Manufacturer Code (013F-0142)
	u8		nCGBFlag;					///< CGB Flag (0143)
	u8		nNewCompany[2];				///< New Licensee Code (0144-0145)
	u8		nSGBFlag;					///< SGB Flag (0146)
	u8		nCartType;					///< Cartridge Type (0147)
	u8		nROMSize;					///< ROM Size (0148)
	u8		nRAMSize;					///< RAM Size (0149)
	u8		nRegion;					///< Region Code (014A)
	u8		nCompany;					///< Old Licensee Code (014B)
	u8		nVersion;					///< Mask ROM Version number (014C)
	u8		nHeaderCRC;					///< Header Checksum (014D)
	u8		nROMCRC[2];					///< Global Checksum (014E-014F)
};

/**
 * @class cgbSConfigData
 * @brief Config Data
 */
struct cgbSConfigData
{
	u16		nGrayPal[5];				///< Gray DMG Palette
	u16		nGreenPal[5];				///< Green DMG Palette
	u16		nColorPal[14];				///< Color DMG Palette
	s32		nSoundSwapLR;				///< Swap Sound L/R
	s32		nDMGColor;					///< Color DMG Mode Flag
};

/** @name Global Variable */
//@{
extern u8*					g_pCgbROM;			///< Cartridge
extern u8*					g_pCgbWRAM;			///< Work RAM: GB-8K CGB-32K
extern u8*					g_pCgbVRAM;			///< Video RAM: GB-8K CGB-16K
extern u8*					g_pCgbERAM;			///< External RAM: In Cartridge
extern u8*					g_pCgbOAM;			///< Sprite Attribute Table (OAM)
extern u8*					g_pCgbHRAM;			///< High RAM
extern u8*					g_pCgbREG;			///< I/O Ports

extern u32					g_nCgbGameType;		///< Game Type: 0-DMG 1-CGB
extern cgbSROMHeader*		g_pCgbROMHeader;	///< The Cartridge Header Data
extern trlSEmuShellBuffer*	g_pCgbEmuBuf;		///< Emulate Shell Buffer
extern u32					g_nCgbBreakFlag;	///< Break Flag
extern cgbSConfigData		g_sCgbConfigData;	///< Config Data

extern s32					g_nCgbCpuEventTicks;///< Next Event Ticks
extern s32					g_nCgbCpuTicks;		///< CPU Run Ticks
extern s32					g_nCgbGrpTicks;		///< LCD Ticks
extern s32					g_nCgbSndTicks;		///< Sound Ticks
extern s32					g_nCgbDmaTicks;		///< DMA Ticks
extern s32					g_nCgbTimeTicks;	///< Time Ticks
extern s32					g_nCgbDivTicks;		///< Div Ticks
extern s32					g_nCgbSerialTicks;	///< Serial Ticks
extern s32					g_nCgbSndTick0;		///< Sound Interval Ticks
extern s32					g_nCgbGrpTick0;		///< H-Blank Ticks
extern s32					g_nCgbGrpTick1;		///< One Line Ticks
extern s32					g_nCgbGrpTick2;		///< Searching OAM-RAM Ticks
extern s32					g_nCgbGrpTick3;		///< Transfering Data to LCD Driver Ticks
//@}
