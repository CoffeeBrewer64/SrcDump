/**
 * @file cgbRegister.h
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Register
 */
#pragma once
#include "cgbDataStruct.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u8*				g_pCgbRegWrite;		///< I/O and Registers Write Only Code
extern cgbSRegJOYP*		g_pCgbRegJOYP;		///< FF00 - P1/JOYP - Joypad (R/W)
extern u8*				g_pCgbRegSB;		///< FF01 - SB - Serial transfer data (R/W)
extern cgbSRegSC*		g_pCgbRegSC;		///< FF02 - SC - Serial Transfer Control (R/W)
extern u8*				g_pCgbRegDIV;		///< FF04 - DIV - Divider Register (R/W)
extern u8*				g_pCgbRegTIMA;		///< FF05 - TIMA - Timer counter (R/W)
extern u8*				g_pCgbRegTMA;		///< FF06 - TMA - Timer Modulo (R/W)
extern cgbSRegTAC*		g_pCgbRegTAC;		///< FF07 - TAC - Timer Control (R/W)
extern cgbSRegINT*		g_pCgbRegIF;		///< FF0F - IF - Interrupt Flag (R/W)
extern cgbSRegNR10*		g_pCgbRegNR10;		///< FF10 - NR10 - Channel 1 Sweep register (R/W)
extern cgbSRegNRX1*		g_pCgbRegNR11;		///< FF11 - NR11 - Channel 1 Sound length/Wave pattern duty (R/W)
extern cgbSRegNRX2*		g_pCgbRegNR12;		///< FF12 - NR12 - Channel 1 Volume Envelope (R/W)
extern cgbSRegNRX34*	g_pCgbRegNR14;		///< FF14 - NR14 - Channel 1 Frequency data (R/W)
extern cgbSRegNRX1*		g_pCgbRegNR21;		///< FF16 - NR21 - Channel 2 Sound Length/Wave Pattern Duty (R/W)
extern cgbSRegNRX2*		g_pCgbRegNR22;		///< FF17 - NR22 - Channel 2 Volume Envelope (R/W)
extern cgbSRegNRX34*	g_pCgbRegNR24;		///< FF19 - NR24 - Channel 2 Frequency data (R/W)
extern cgbSRegNR30*		g_pCgbRegNR30;		///< FF1A - NR30 - Channel 3 Sound on/off (R/W)
extern u8*				g_pCgbRegNR31;		///< FF1B - NR31 - Channel 3 Sound Length (R/W)
extern cgbSRegNR32*		g_pCgbRegNR32;		///< FF1C - NR32 - Channel 3 Select output level (R/W)
extern cgbSRegNRX34*	g_pCgbRegNR34;		///< FF1E - NR34 - Channel 3 Frequency data (R/W)
extern cgbSRegNR41*		g_pCgbRegNR41;		///< FF20 - NR41 - Channel 4 Sound Length (R/W)
extern cgbSRegNRX2*		g_pCgbRegNR42;		///< FF21 - NR42 - Channel 4 Volume Envelope (R/W)
extern cgbSRegNR43*		g_pCgbRegNR43;		///< FF22 - NR43 - Channel 4 Polynomial Counter (W)
extern cgbSRegNR44*		g_pCgbRegNR44;		///< FF23 - NR44 - Channel 4 Counter/consecutive, Inital (R/W)
extern cgbSRegNR50*		g_pCgbRegNR50;		///< FF24 - NR50 - Channel control / ON-OFF / Volume (R/W)
extern cgbSRegNR51*		g_pCgbRegNR51;		///< FF25 - NR51 - Selection of Sound output terminal (R/W)
extern cgbSRegNR52*		g_pCgbRegNR52;		///< FF26 - NR52 - Sound on/off (R/W)
extern cgbSRegLCDC*		g_pCgbRegLCDC;		///< FF40 - LCDC - LCD Control (R/W)
extern cgbSRegSTAT*		g_pCgbRegSTAT;		///< FF41 - STAT - LCDC Status (R/W)
extern u8*				g_pCgbRegSCY;		///< FF42 - SCY - Scroll Y (R/W)
extern u8*				g_pCgbRegSCX;		///< FF43 - SCX - Scroll X (R/W)
extern u8*				g_pCgbRegLY;		///< FF44 - LY - LCDC Y-Coordinate (R)
extern u8*				g_pCgbRegLYC;		///< FF45 - LYC - LY Compare (R/W)
extern u8*				g_pCgbRegDMA;		///< FF46 - DMA - DMA Transfer and Start Address (W)
extern cgbSRegPAL*		g_pCgbRegBGP;		///< FF47 - BGP - BG Palette Data (R/W) - Non CGB Mode Only
extern cgbSRegPAL*		g_pCgbRegOBP0;		///< FF48 - OBP0 - Object Palette 0 Data (R/W) - Non CGB Mode Only
extern cgbSRegPAL*		g_pCgbRegOBP1;		///< FF49 - OBP1 - Object Palette 1 Data (R/W) - Non CGB Mode Only
extern u8*				g_pCgbRegWY;		///< FF4A - WY - Window Y Position (R/W)
extern u8*				g_pCgbRegWX;		///< FF4B - WX - Window X Position minus 7 (R/W)
extern cgbSRegKEY1*		g_pCgbRegKEY1;		///< FF4D - KEY1 - CGB Mode Only - Prepare Speed Switch (R/W)
extern cgbSRegVBK*		g_pCgbRegVBK;		///< FF4F - VBK - CGB Mode Only - VRAM Bank (R/W)
extern cgbSRegHDMA5*	g_pCgbRegHDMA5;		///< FF55 - HDMA5 - CGB Mode Only - New DMA Length/Mode/Start (W)
extern cgbSRegRP*		g_pCgbRegRP;		///< FF56 - RP - CGB Mode Only - Infrared Communications Port (R/W)
extern cgbSRegCPS*		g_pCgbRegBCPS;		///< FF68 - BCPS/BGPI - CGB Mode Only - Background Palette Index (R/W)
extern u8*				g_pCgbRegBCPD;		///< FF69 - BCPD/BGPD - CGB Mode Only - Background Palette Data (R/W)
extern cgbSRegCPS*		g_pCgbRegOCPS;		///< FF6A - OCPS/OBPI - CGB Mode Only - Sprite Palette Index (R/W)
extern u8*				g_pCgbRegOCPD;		///< FF6B - OCPD/OBPD - CGB Mode Only - Sprite Palette Data (R/W)
extern cgbSRegSVBK*		g_pCgbRegSVBK;		///< FF70 - SVBK - CGB Mode Only - WRAM Bank (R/W)
extern cgbSRegINT*		g_pCgbRegIE;		///< FFFF - IE - Interrupt Enable (R/W)
//@}

/** @brief Initialize Registers */
void cgbRegInit();
/** @brief Reset Registers */
void cgbRegReset();
/** @brief Exit Registers */
void cgbRegExit();
/** @brief Data Write to Register */
void cgbRegWrite(u8 nAddr, u8 nData);
