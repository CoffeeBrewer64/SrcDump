/**
 * @file cgbGraphic.h
 * @author Chentian
 * @date 2009.11.24
 * @brief CGB Emulate For CTR - Graphic
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#define CGB_GRP_SAVEDATA	5										///< Graphic Save Data Count
#define CGB_RGB(r,g,b)		((b<<1) | (g<<6) | (r<<11) | 1)
#define CGB_BGRA2RGBA(v)	((((u16)(v&0x001F))<<11) | (((u16)(v&0x7C00))>>9) | ((v&0x03E0)<<1) | 1)
#define CGB_BGRA_R(v)		((v>>11)&0x001F)
#define CGB_BGRA_G(v)		((v>>6)&0x001F)
#define CGB_BGRA_B(v)		((v>>1)&0x001F)
//@}

/** @name Global Variable */
//@{
extern u16					g_nCgbGrpDMGColor[14];					///< DMG Color
extern u16					g_nCgbGrpBGPal[8][4];					///< BG Palette Data
extern u16					g_nCgbGrpOBJPal[8][4];					///< OBJ Palette Data
extern u16					g_nCgbGrpBGPalReal[8][4];				///< BG Real Palette Data
extern u16					g_nCgbGrpOBJPalReal[8][4];				///< OBJ Real Palette Data
extern u8*					g_pCgbGrpBGSrnDataBase;					///< BG Screen Data Base Address
extern u8*					g_pCgbGrpBGAtrDataBase;					///< BG Attribute Data Base Address
extern u8*					g_pCgbGrpWinSrnDataBase;				///< Window Screen Data Base Address
extern u8*					g_pCgbGrpWinAtrDataBase;				///< Window Attribute Data Base Address
extern u32					g_nCgbGrpBGWinTileDataBase;				///< BG & Window Tile Data Base Address
extern u8					g_nCgbGrpBGWinTileOffset;				///< BG & Window Tile Offset
extern u32					g_bCgbGrpOAMChange;						///< OAM Change Flag
extern u32					g_nCgbGrpLCDCInt;						///< LCDC Interrupt Stat
extern trlSEmuShellResume	g_sCgbGrpSaveData[CGB_GRP_SAVEDATA];	///< Graphic Save Data
//@}

/** @brief Initialize Graphic */
void cgbGrpInit();
/** @brief Reset Graphic */
void cgbGrpReset();
/** @brief Resume Graphic */
void cgbGrpResume();
/** @brief Exit Graphic */
void cgbGrpExit();
/** @brief Update Ticks */
void cgbGrpUpdateTicks();
/** @brief Render a White Screen */
void cgbGrpRenderWhite();
/** @brief Update LCD */
void cgbGrpUpdateLCD(u8 nRegLast);
