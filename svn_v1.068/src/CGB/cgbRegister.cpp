/**
 * @file cgbRegister.cpp
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Register
 */
#include "cgbRegister.h"
#include "cgbCPU.h"
#include "cgbDMA.h"
#include "cgbTime.h"
#include "cgbInput.h"
#include "cgbSound.h"
#include "cgbMemory.h"
#include "cgbGraphic.h"
#include "cgbSerial.h"

/** @name Macro Define */
//@{
#define CGB_REG_SIZE		0x100			///< I/O and Registers Count
#define CGB_REG_VALID		0x58			///< I/O and Registers Valid Count
//@}

/** @name Global Variable */
//@{
u8*				g_pCgbRegMask	= NULL;		///< I/O and Registers Mask Code
u8*				g_pCgbRegWrite	= NULL;		///< I/O and Registers Write Only Code
u8*				g_pCgbRegRead	= NULL;		///< I/O and Registers Read Only Code
u8				g_nCgbRegLastVal= NULL;		///< Last Value
cgbSRegJOYP*	g_pCgbRegJOYP	= NULL;		///< FF00 - P1/JOYP - Joypad (R/W)
u8*				g_pCgbRegSB		= NULL;		///< FF01 - SB - Serial transfer data (R/W)
cgbSRegSC*		g_pCgbRegSC		= NULL;		///< FF02 - SC - Serial Transfer Control (R/W)
u8*				g_pCgbRegDIV	= NULL;		///< FF04 - DIV - Divider Register (R/W)
u8*				g_pCgbRegTIMA	= NULL;		///< FF05 - TIMA - Timer counter (R/W)
u8*				g_pCgbRegTMA	= NULL;		///< FF06 - TMA - Timer Modulo (R/W)
cgbSRegTAC*		g_pCgbRegTAC	= NULL;		///< FF07 - TAC - Timer Control (R/W)
cgbSRegINT*		g_pCgbRegIF		= NULL;		///< FF0F - IF - Interrupt Flag (R/W)
cgbSRegNR10*	g_pCgbRegNR10	= NULL;		///< FF10 - NR10 - Channel 1 Sweep register (R/W)
cgbSRegNRX1*	g_pCgbRegNR11	= NULL;		///< FF11 - NR11 - Channel 1 Sound length/Wave pattern duty (R/W)
cgbSRegNRX2*	g_pCgbRegNR12	= NULL;		///< FF12 - NR12 - Channel 1 Volume Envelope (R/W)
cgbSRegNRX34*	g_pCgbRegNR14	= NULL;		///< FF14 - NR14 - Channel 1 Frequency data (R/W)
cgbSRegNRX1*	g_pCgbRegNR21	= NULL;		///< FF16 - NR21 - Channel 2 Sound Length/Wave Pattern Duty (R/W)
cgbSRegNRX2*	g_pCgbRegNR22	= NULL;		///< FF17 - NR22 - Channel 2 Volume Envelope (R/W)
cgbSRegNRX34*	g_pCgbRegNR24	= NULL;		///< FF19 - NR24 - Channel 2 Frequency data (R/W)
cgbSRegNR30*	g_pCgbRegNR30	= NULL;		///< FF1A - NR30 - Channel 3 Sound on/off (R/W)
u8*				g_pCgbRegNR31	= NULL;		///< FF1B - NR31 - Channel 3 Sound Length (R/W)
cgbSRegNR32*	g_pCgbRegNR32	= NULL;		///< FF1C - NR32 - Channel 3 Select output level (R/W)
cgbSRegNRX34*	g_pCgbRegNR34	= NULL;		///< FF1E - NR34 - Channel 3 Frequency data (R/W)
cgbSRegNR41*	g_pCgbRegNR41	= NULL;		///< FF20 - NR41 - Channel 4 Sound Length (R/W)
cgbSRegNRX2*	g_pCgbRegNR42	= NULL;		///< FF21 - NR42 - Channel 4 Volume Envelope (R/W)
cgbSRegNR43*	g_pCgbRegNR43	= NULL;		///< FF22 - NR43 - Channel 4 Polynomial Counter (W)
cgbSRegNR44*	g_pCgbRegNR44	= NULL;		///< FF23 - NR44 - Channel 4 Counter/consecutive, Inital (R/W)
cgbSRegNR50*	g_pCgbRegNR50	= NULL;		///< FF24 - NR50 - Channel control / ON-OFF / Volume (R/W)
cgbSRegNR51*	g_pCgbRegNR51	= NULL;		///< FF25 - NR51 - Selection of Sound output terminal (R/W)
cgbSRegNR52*	g_pCgbRegNR52	= NULL;		///< FF26 - NR52 - Sound on/off (R/W)
cgbSRegLCDC*	g_pCgbRegLCDC	= NULL;		///< FF40 - LCDC - LCD Control (R/W)
cgbSRegSTAT*	g_pCgbRegSTAT	= NULL;		///< FF41 - STAT - LCDC Status (R/W)
u8*				g_pCgbRegSCY	= NULL;		///< FF42 - SCY - Scroll Y (R/W)
u8*				g_pCgbRegSCX	= NULL;		///< FF43 - SCX - Scroll X (R/W)
u8*				g_pCgbRegLY		= NULL;		///< FF44 - LY - LCDC Y-Coordinate (R)
u8*				g_pCgbRegLYC	= NULL;		///< FF45 - LYC - LY Compare (R/W)
u8*				g_pCgbRegDMA	= NULL;		///< FF46 - DMA - DMA Transfer and Start Address (W)
cgbSRegPAL*		g_pCgbRegBGP	= NULL;		///< FF47 - BGP - BG Palette Data (R/W) - Non CGB Mode Only
cgbSRegPAL*		g_pCgbRegOBP0	= NULL;		///< FF48 - OBP0 - Object Palette 0 Data (R/W) - Non CGB Mode Only
cgbSRegPAL*		g_pCgbRegOBP1	= NULL;		///< FF49 - OBP1 - Object Palette 1 Data (R/W) - Non CGB Mode Only
u8*				g_pCgbRegWY		= NULL;		///< FF4A - WY - Window Y Position (R/W)
u8*				g_pCgbRegWX		= NULL;		///< FF4B - WX - Window X Position minus 7 (R/W)
cgbSRegKEY1*	g_pCgbRegKEY1	= NULL;		///< FF4D - KEY1 - CGB Mode Only - Prepare Speed Switch (R/W)
cgbSRegVBK*		g_pCgbRegVBK	= NULL;		///< FF4F - VBK - CGB Mode Only - VRAM Bank (R/W)
cgbSRegHDMA5*	g_pCgbRegHDMA5	= NULL;		///< FF55 - HDMA5 - CGB Mode Only - New DMA Length/Mode/Start (W)
cgbSRegRP*		g_pCgbRegRP		= NULL;		///< FF56 - RP - CGB Mode Only - Infrared Communications Port (R/W)
cgbSRegCPS*		g_pCgbRegBCPS	= NULL;		///< FF68 - BCPS/BGPI - CGB Mode Only - Background Palette Index (R/W)
u8*				g_pCgbRegBCPD	= NULL;		///< FF69 - BCPD/BGPD - CGB Mode Only - Background Palette Data (R/W)
cgbSRegCPS*		g_pCgbRegOCPS	= NULL;		///< FF6A - OCPS/OBPI - CGB Mode Only - Sprite Palette Index (R/W)
u8*				g_pCgbRegOCPD	= NULL;		///< FF6B - OCPD/OBPD - CGB Mode Only - Sprite Palette Data (R/W)
cgbSRegSVBK*	g_pCgbRegSVBK	= NULL;		///< FF70 - SVBK - CGB Mode Only - WRAM Bank (R/W)
cgbSRegINT*		g_pCgbRegIE		= NULL;		///< FFFF - IE - Interrupt Enable (R/W)
const u8		g_nCgbRegMaskTable[CGB_REG_VALID] = {	///< I/O and Registers Mask Code Table
	0x3F, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 	// 00
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 	// 08
	0x7F, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 	// 10
	0xFF, 0xC7, 0x80, 0xFF, 0x60, 0xFF, 0xC7, 0xFF, 	// 18
	0x3F, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0x8F, 0xFF, 	// 20
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 28
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 30
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 38
	0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 40
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0xFF, 0x01, 	// 48
	0xFF, 0xFF, 0xF0, 0x1F, 0xF0, 0xFF, 0xC3, 0xFF, };	// 50
const u8		g_nCgbRegReadTable[CGB_REG_VALID] = {	///< I/O and Registers Write Only Code Table
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 00
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 08
	0xFF, 0xC0, 0xFF, 0x00, 0x78, 0xFF, 0xC0, 0xFF, 	// 10
	0x00, 0x78, 0xFF, 0xFF, 0xFF, 0x00, 0x78, 0xFF, 	// 18
	0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 	// 20
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 28
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 30
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 38
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 	// 40
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 48
	0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, };	// 50
const u8		g_nCgbRegWriteTable[CGB_REG_VALID] = {	///< I/O and Registers Read Only Code Table
	0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 00
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 08
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 10
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 18
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 	// 20
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 28
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 30
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	// 38
	0xFF, 0xF8, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 	// 40
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0x01, 	// 48
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, };	// 50
//@}

/** @brief Initialize Registers */
void cgbRegInit()
{
	// Initialize Mask Table
	g_pCgbRegMask = (u8*)trlMemAlloc(CGB_REG_SIZE);
	trlMemCopy(g_pCgbRegMask, g_nCgbRegMaskTable, CGB_REG_VALID);
	memset(&g_pCgbRegMask[CGB_REG_VALID], 0xFF, CGB_REG_SIZE-CGB_REG_VALID);
	g_pCgbRegMask[0x68] = 0xBF;
	g_pCgbRegMask[0x6A] = 0xBF;
	g_pCgbRegMask[0x70] = 0x07;
	g_pCgbRegMask[0xFF] = 0x1F;
	// Initialize Write Only Table
	g_pCgbRegWrite = (u8*)trlMemAlloc(CGB_REG_SIZE);
	trlMemCopy(g_pCgbRegWrite, g_nCgbRegReadTable, CGB_REG_VALID);
	memset(&g_pCgbRegWrite[CGB_REG_VALID], 0xFF, CGB_REG_SIZE-CGB_REG_VALID);
	// Initialize Read Only Table
	g_pCgbRegRead = (u8*)trlMemAlloc(CGB_REG_SIZE);
	trlMemCopy(g_pCgbRegRead, g_nCgbRegWriteTable, CGB_REG_VALID);
	memset(&g_pCgbRegRead[CGB_REG_VALID], 0xFF, CGB_REG_SIZE-CGB_REG_VALID);

	if(g_nCgbGameType == CGB_GAMETYPE_DMG)
	{
		for(u16 n=0x51; n<=0x54; ++n)
		{
			g_pCgbRegMask[n] = 0xFF;
			g_pCgbRegWrite[n] = 0xFF;
		}
		g_pCgbRegRead[0x4D] = 0xFF;
		g_pCgbRegRead[0x56] = 0xFF;
	}
	else
	{
		g_pCgbRegRead[0x4D] = 0x01;
		g_pCgbRegRead[0x4F] = 0x01;
		g_pCgbRegRead[0x70] = 0x07;
	}

	// Set Register Point
	g_pCgbRegJOYP	= (cgbSRegJOYP*)(&g_pCgbREG[0x00]);
	g_pCgbRegSB		= &g_pCgbREG[0x01];
	g_pCgbRegSC		= (cgbSRegSC*)(&g_pCgbREG[0x02]);
	g_pCgbRegDIV	= &g_pCgbREG[0x04];
	g_pCgbRegTIMA	= &g_pCgbREG[0x05];
	g_pCgbRegTMA	= &g_pCgbREG[0x06];
	g_pCgbRegTAC	= (cgbSRegTAC*)(&g_pCgbREG[0x07]);
	g_pCgbRegIF		= (cgbSRegINT*)(&g_pCgbREG[0x0F]);
	g_pCgbRegNR10	= (cgbSRegNR10*)(&g_pCgbREG[0x10]);
	g_pCgbRegNR11	= (cgbSRegNRX1*)(&g_pCgbREG[0x11]);
	g_pCgbRegNR12	= (cgbSRegNRX2*)(&g_pCgbREG[0x12]);
	g_pCgbRegNR14	= (cgbSRegNRX34*)(&g_pCgbREG[0x13]);
	g_pCgbRegNR21	= (cgbSRegNRX1*)(&g_pCgbREG[0x16]);
	g_pCgbRegNR22	= (cgbSRegNRX2*)(&g_pCgbREG[0x17]);
	g_pCgbRegNR24	= (cgbSRegNRX34*)(&g_pCgbREG[0x18]);
	g_pCgbRegNR30	= (cgbSRegNR30*)(&g_pCgbREG[0x1A]);
	g_pCgbRegNR31	= &g_pCgbREG[0x1B];
	g_pCgbRegNR32	= (cgbSRegNR32*)(&g_pCgbREG[0x1C]);
	g_pCgbRegNR34	= (cgbSRegNRX34*)(&g_pCgbREG[0x1D]);
	g_pCgbRegNR41	= (cgbSRegNR41*)(&g_pCgbREG[0x20]);
	g_pCgbRegNR42	= (cgbSRegNRX2*)(&g_pCgbREG[0x21]);
	g_pCgbRegNR43	= (cgbSRegNR43*)(&g_pCgbREG[0x22]);
	g_pCgbRegNR44	= (cgbSRegNR44*)(&g_pCgbREG[0x23]);
	g_pCgbRegNR50	= (cgbSRegNR50*)(&g_pCgbREG[0x24]);
	g_pCgbRegNR51	= (cgbSRegNR51*)(&g_pCgbREG[0x25]);
	g_pCgbRegNR52	= (cgbSRegNR52*)(&g_pCgbREG[0x26]);
	g_pCgbRegLCDC	= (cgbSRegLCDC*)(&g_pCgbREG[0x40]);
	g_pCgbRegSTAT	= (cgbSRegSTAT*)(&g_pCgbREG[0x41]);
	g_pCgbRegSCY	= &g_pCgbREG[0x42];
	g_pCgbRegSCX	= &g_pCgbREG[0x43];
	g_pCgbRegLY		= &g_pCgbREG[0x44];
	g_pCgbRegLYC	= &g_pCgbREG[0x45];
	g_pCgbRegDMA	= &g_pCgbREG[0x46];
	g_pCgbRegBGP	= (cgbSRegPAL*)(&g_pCgbREG[0x47]);
	g_pCgbRegOBP0	= (cgbSRegPAL*)(&g_pCgbREG[0x48]);
	g_pCgbRegOBP1	= (cgbSRegPAL*)(&g_pCgbREG[0x49]);
	g_pCgbRegWY		= &g_pCgbREG[0x4A];
	g_pCgbRegWX		= &g_pCgbREG[0x4B];
	g_pCgbRegKEY1	= (cgbSRegKEY1*)(&g_pCgbREG[0x4D]);
	g_pCgbRegVBK	= (cgbSRegVBK*)(&g_pCgbREG[0x4F]);
	g_pCgbRegHDMA5	= (cgbSRegHDMA5*)(&g_pCgbREG[0x55]);
	g_pCgbRegRP		= (cgbSRegRP*)(&g_pCgbREG[0x56]);
	g_pCgbRegBCPS	= (cgbSRegCPS*)(&g_pCgbREG[0x68]);
	g_pCgbRegBCPD	= &g_pCgbREG[0x69];
	g_pCgbRegOCPS	= (cgbSRegCPS*)(&g_pCgbREG[0x6A]);
	g_pCgbRegOCPD	= &g_pCgbREG[0x6B];
	g_pCgbRegSVBK	= (cgbSRegSVBK*)(&g_pCgbREG[0x70]);
	g_pCgbRegIE		= (cgbSRegINT*)(&g_pCgbREG[0xFF]);

	cgbRegReset();
}



#if TRL_SOUND_DEBUG
extern s32			g_bCgbSndResetCH1;
extern s32			g_bCgbSndResetCH2;
extern s32			g_bCgbSndResetCH3;
extern s32			g_bCgbSndResetCH4;
#endif
/** @brief Update Registers */
inline void cgbRegUpdate(u8 nAddr)
{
	switch(nAddr)
	{
	case 0x00:		// P1/JOYP
		if(!g_pCgbRegJOYP->rButton)
			g_pCgbRegJOYP->rKey = (g_nCgbKeyBuffer & 0x0F);
		else if(!g_pCgbRegJOYP->rDirection)
			g_pCgbRegJOYP->rKey = ((g_nCgbKeyBuffer>>4) & 0x0F);
		else
			g_pCgbRegJOYP->rKey = 0x0F;
		break;
	case 0x02:		// SC
		if(g_pCgbRegSC->rTransfer)
			g_nCgbSerialTicks = g_nCgbSerialTick0;
		g_nCgbSerialBits = 0;
		if(g_nCgbGameType == CGB_GAMETYPE_CGB)
		{
			if(g_pCgbRegSC->rClockSpeed)
				g_nCgbSerialTick0 = CGB_SERIAL_TICKS1;
			else
				g_nCgbSerialTick0 = CGB_SERIAL_TICKS0;
		}
		break;
	case 0x04:		// DIV
		*g_pCgbRegDIV = 0;
		g_nCgbDivTicks = CGB_DIV_TICKS;
		g_nCgbTimeValue = 0xFF;
		break;
	case 0x07:		// TAC
		if(g_pCgbRegTAC->rTimerStop)
		{
			g_nCgbTimeTicks = (g_nCgbTimeValue & g_nCgbTimeMask[g_pCgbRegTAC->rInputClock]) + 1;
			if(g_nCgbCpuEventTicks > g_nCgbTimeTicks)
				g_nCgbCpuEventTicks = g_nCgbTimeTicks;
		}
		break;
	case 0x10:		// NR10
		g_nCgbSnd1SweepLength = g_nCgbSnd1SweepLengthInit = CGB_SND_LENGTH2 * g_pCgbRegNR10->rTime;
		break;
	case 0x11:		// NR11
#if (TRL_SOUND_WAVE_TEST== 1)
		g_pCgbSnd1Wave = g_nCgbSndWavePattern2[g_pCgbRegNR11->rDuty];
#else
		g_pCgbSnd1Wave = g_nCgbSndWavePattern[g_pCgbRegNR11->rDuty];
#endif
		g_nCgbSnd1Length  = CGB_SND_LENGTH1 * (64 - g_pCgbRegNR11->rLength);
		break;
	case 0x12:		// NR12
		g_nCgbSnd1EnvelopeValue = g_pCgbRegNR12->rValue;
		g_nCgbSnd1EnvelopeLength = g_nCgbSnd1EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR12->rSteps;
		break;
	case 0x13:		// NR13
		g_nCgbSnd1Frequency = (CGB_SND_FREQ<<1) / (2048 - g_pCgbRegNR14->rFreq);
		break;
	case 0x14:		// NR14
		g_nCgbSnd1Frequency = (CGB_SND_FREQ<<1) / ((2048 - g_pCgbRegNR14->rFreq));
		trlTraceSoundDetallSweepFreq(g_pCgbRegNR14->rFreq);
		if(g_pCgbRegNR14->rInitial)
		{
			g_pCgbRegNR52->rSound1 = 1;
#if	TRL_SOUND_DEBUG
			if(g_bCgbSndResetCH1 == 1)
				g_nCgbSnd1Index = 0;
#endif
			if(g_nCgbSnd1Reset == 1)
				g_nCgbSnd1Index = 0;
			g_nCgbSnd1EnvelopeValue = g_pCgbRegNR12->rValue;
			g_nCgbSnd1EnvelopeLength = g_nCgbSnd1EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR12->rSteps;
			g_nCgbSnd1Length  = CGB_SND_LENGTH1 * (64 - g_pCgbRegNR11->rLength);

			g_nCgbSnd1SweepLength = g_nCgbSnd1SweepLengthInit = CGB_SND_LENGTH2 * g_pCgbRegNR10->rTime;
			g_nCgbSnd1SweepFreq = g_pCgbRegNR14->rFreq;
		}
		break;
	case 0x16:		// NR21
#if (TRL_SOUND_WAVE_TEST== 1)
		g_pCgbSnd2Wave = g_nCgbSndWavePattern2[g_pCgbRegNR21->rDuty];
#else
		g_pCgbSnd2Wave = g_nCgbSndWavePattern[g_pCgbRegNR21->rDuty];
#endif
 		g_nCgbSnd2Length = CGB_SND_LENGTH1 * (64 - g_pCgbRegNR21->rLength);
		break;
	case 0x17:		// NR22
		g_nCgbSnd2EnvelopeValue = g_pCgbRegNR22->rValue;
		g_nCgbSnd2EnvelopeLength = g_nCgbSnd2EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR22->rSteps;
		break;
	case 0x18:		// NR23
		g_nCgbSnd2Frequency = (CGB_SND_FREQ<<1) / ((2048 - g_pCgbRegNR24->rFreq));
		break;
	case 0x19:		// NR24
		g_nCgbSnd2Frequency = (CGB_SND_FREQ<<1) / ((2048 - g_pCgbRegNR24->rFreq));
		if(g_pCgbRegNR24->rInitial)
		{
			g_pCgbRegNR52->rSound2 = 1;
#if	TRL_SOUND_DEBUG
			if(g_bCgbSndResetCH2 == 1)
				g_nCgbSnd2Index = 0;
#endif
			if(g_nCgbSnd2Reset == 1)
				g_nCgbSnd2Index = 0;
			g_nCgbSnd2EnvelopeValue = g_pCgbRegNR22->rValue;
			g_nCgbSnd2EnvelopeLength = g_nCgbSnd2EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR22->rSteps;
			g_nCgbSnd2Length = CGB_SND_LENGTH1 * (64 - g_pCgbRegNR21->rLength); 
		}
		break;
	case 0x1A:		// NR30
		if(!g_pCgbRegNR30->rOutput)
			g_pCgbRegNR52->rSound3 = 0;
		else
			g_pCgbRegNR52->rSound3 = 1;
		break;
	case 0x1B:		// NR31
		g_nCgbSnd3Length = CGB_SND_LENGTH1 * (256 - *g_pCgbRegNR31);
		break;
	//case 0x1C:		// NR32
	//	break;
	case 0x1D:		// NR33
		g_nCgbSnd3Frequency = CGB_SND_FREQ / (2048 - g_pCgbRegNR34->rFreq);
		break;
	case 0x1E:		// NR34
		g_nCgbSnd3Frequency = CGB_SND_FREQ / (2048 - g_pCgbRegNR34->rFreq);
		if(g_pCgbRegNR34->rInitial && g_pCgbRegNR30->rOutput)
		{
			g_pCgbRegNR52->rSound3 = 1;
#if	TRL_SOUND_DEBUG
			if(g_bCgbSndResetCH3 == 1)
				g_nCgbSnd3Index = 0;
#endif
			g_nCgbSnd3Length = CGB_SND_LENGTH1 * (256 - *g_pCgbRegNR31);
		}
		break;
	case 0x20:		// NR41
		g_nCgbSnd4Length  = CGB_SND_LENGTH1 * (64 - g_pCgbRegNR41->rLength); 
		break;
	case 0x21:		// NR42
		g_nCgbSnd4EnvelopeValue = g_pCgbRegNR42->rValue;
		g_nCgbSnd4EnvelopeLength = g_nCgbSnd4EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR42->rSteps;
		break;
	case 0x22:		// NR43
		//	                        						4M *(2~ 1/7)
		//shiftcount_per_sample = shiftfreq/samplefreq = --------------------------  
		//							                     44100 * 2^3 * 2^(n+1)
		//
		//44100*420*shiftcount_per_sample = 4M *(2~ 1/7)~*420 /( 2^3 * 2^(n+1))
		//420 is 12*35 is the min xxxx of( 2,3,4,5,6,7)
		//44100*420 = 18522000 = 0x11A9F90
		{
			u32 g_nCgbSndFreqRatio_New[] = {420*2, 420, 420/2, 420/3, 420/4, 420/5, 420/6,420/7};
			g_nCgbSnd4Frequency = 4192304/8*g_nCgbSndFreqRatio_New[g_pCgbRegNR43->rDividingRatio]/g_nCgbSndShiftClock[g_pCgbRegNR43->rShiftClock];
		}
		//g_nCgbSnd4Frequency = ((g_nCgbSndFreqRatio[g_pCgbRegNR43->rDividingRatio] / g_nCgbSndShiftClock[g_pCgbRegNR43->rShiftClock]) << 8) / 7;//CGB_SND_NOISE;
		break;
	case 0x23:		// NR44
		if(g_pCgbRegNR44->rInitial)
		{
			g_pCgbRegNR52->rSound4 = 1;
#if	TRL_SOUND_DEBUG
			if(g_bCgbSndResetCH4 == 1)
			{
				g_nCgbSnd4Index = 0;
				g_nCgbSnd4TableIndex = 0;
			}
#endif

			g_nCgbSnd4Length  = CGB_SND_LENGTH1 * (64 - g_pCgbRegNR41->rLength); 
			g_nCgbSnd4Shift = g_pCgbRegNR43->rStepNumber ? 0x7F : 0x7FFF;

			g_nCgbSnd4EnvelopeValue = g_pCgbRegNR42->rValue;
			g_nCgbSnd4EnvelopeLength = g_nCgbSnd4EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR42->rSteps;
		}
		break;
	case 0x24:		// NR50
		g_nCgbSndVolume1 = g_pCgbRegNR50->rSO1Volume;
		g_nCgbSndVolume2 = g_pCgbRegNR50->rSO2Volume;
		break;
	//case 0x25:		// NR51
	//	break;
	case 0x26:		// NR52
		if(!g_pCgbRegNR52->rSoundAll)
		{
			g_pCgbRegNR52->rSound1 = 0;
			g_pCgbRegNR52->rSound2 = 0;
			g_pCgbRegNR52->rSound3 = 0;
			g_pCgbRegNR52->rSound4 = 0;
		}
		break;
	case 0x40:		// LCDC
		if(g_pCgbREG[0x40] != g_nCgbRegLastVal)
			cgbGrpUpdateLCD(g_nCgbRegLastVal);
		break;
	case 0x41:		// STAT
		g_pCgbRegSTAT->rCoincidence = 0;
		break;
	//case 0x42:		// SCY
	//	break;
	//case 0x43:		// SCX
	//	break;
	//case 0x44:		// LY
	//	g_pCgbREG[0x44] = 0;
	//	break;
	case 0x45:		// LYC
		if(g_pCgbREG[0x45] != g_nCgbRegLastVal)
		{
			if(g_pCgbRegLCDC->rLCDEnable)
			{
				if(*g_pCgbRegLY == *g_pCgbRegLYC)
				{
					g_pCgbRegSTAT->rCoincidence = 1;
					if(g_pCgbRegSTAT->rLYCEnable)
					{
						g_nCgbGrpLCDCInt = 1;
						g_pCgbRegIF->rLCD = 1;
					}
				}
				else
				{
					g_nCgbGrpLCDCInt = 0;
					g_pCgbRegSTAT->rCoincidence = 0;
				}
			}
		}
		break;
	case 0x46:		// DMA
		cgbDmaTransferDMA();
		break;
	case 0x47:		// BGP
		if(g_nCgbGameType == CGB_GAMETYPE_DMG)
		{
			g_nCgbGrpBGPal[0][0] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor0];
			g_nCgbGrpBGPal[0][1] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor1];
			g_nCgbGrpBGPal[0][2] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor2];
			g_nCgbGrpBGPal[0][3] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor3];
		}
		break;
	case 0x48:		// OBP0
		if(g_nCgbGameType == CGB_GAMETYPE_DMG)
		{
			g_nCgbGrpOBJPal[0][0] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor0+4];
			g_nCgbGrpOBJPal[0][1] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor1+4];
			g_nCgbGrpOBJPal[0][2] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor2+4];
			g_nCgbGrpOBJPal[0][3] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor3+4];
		}
		break;
	case 0x49:		// OBP1
		if(g_nCgbGameType == CGB_GAMETYPE_DMG)
		{
			g_nCgbGrpOBJPal[1][0] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor0+8];
			g_nCgbGrpOBJPal[1][1] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor1+8];
			g_nCgbGrpOBJPal[1][2] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor2+8];
			g_nCgbGrpOBJPal[1][3] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor3+8];
		}
		break;
	//case 0x4A:		// WY
	//	break;
	//case 0x4B:		// WX
	//	break;
	//case 0xFF:		// IE
	//	break;
	}

	if(g_nCgbGameType == CGB_GAMETYPE_DMG)
		return;

	switch(nAddr)
	{
	case 0x4D:		// KEY1
		cgbCpuSpeed();
		break;
	case 0x4F:		// VBK
		g_pCgbCurVRAM = &g_pCgbVRAM[g_pCgbRegVBK->rBank*0x2000];
		break;
	case 0x51:		// HDMA1
		if((g_pCgbREG[0x51] >= 0x80 && g_pCgbREG[0x51] < 0xA0) || (g_pCgbREG[0x51] > 0xE0))
			g_pCgbREG[0x51] = 0;
		break;
	//case 0x52:		// HDMA2
	//	break;
	//case 0x53:		// HDMA3
	//	break;
	//case 0x54:		// HDMA4
	//	break;
	case 0x55:		// HDMA5
		if(g_nCgbDmaHDMAFlag)
		{
			if(g_pCgbRegHDMA5->rMode)
				g_pCgbRegHDMA5->rMode = 0;
			else
			{
				g_pCgbREG[0x55] = 0xFF;
				g_nCgbDmaHDMAFlag = 0;
			}
		}
		else
		{
			if(g_pCgbRegHDMA5->rMode)
			{
				g_pCgbRegHDMA5->rMode = 0;
				g_nCgbDmaHDMAFlag = 1;
				if(g_pCgbRegSTAT->rMode == 0)
					cgbDmaTransferHDMA_HBlank();
			}
			else
				cgbDmaTransferHDMA_Normal();
		}
		break;
	//case 0x56:		// RP
	//	//g_pCgbRegRP
	//	break;
	case 0x68:		// BCPS
		*g_pCgbRegBCPD = (g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] >> (g_pCgbRegBCPS->rHL*8)) & 0xFF;
		break;
	case 0x69:		// BCPD
		if(g_pCgbRegSTAT->rMode != 3)
		{
			if(g_pCgbRegBCPS->rHL)
				g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] = ((*g_pCgbRegBCPD) << 8) | (g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] & 0x00FF);
			else
				g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] = (g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] & 0xFF00) | (*g_pCgbRegBCPD);
		}
		if(g_pCgbRegBCPS->rAutoInc)
		{
			if(!g_pCgbRegBCPS->rHL)
			{
				g_pCgbRegBCPS->rHL = 1;
				*g_pCgbRegBCPD = (g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] >> 8) & 0xFF;
			}
			else
			{
				g_pCgbRegBCPS->rHL = 0;
				g_nCgbGrpBGPal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] = CGB_BGRA2RGBA(g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo]);
				++g_pCgbRegBCPS->rPalDataNo;
				if(!g_pCgbRegBCPS->rPalDataNo)
					++g_pCgbRegBCPS->rPalNo;
				*g_pCgbRegBCPD = g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] & 0xFF;
			}
		}
		else
			g_nCgbGrpBGPal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo] = CGB_BGRA2RGBA(g_nCgbGrpBGPalReal[g_pCgbRegBCPS->rPalNo][g_pCgbRegBCPS->rPalDataNo]);
		break;
	case 0x6A:		// OCPS
		*g_pCgbRegOCPD = (g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] >> (g_pCgbRegOCPS->rHL*8)) & 0xFF;
		break;
	case 0x6B:		// OCPD
		if(g_pCgbRegSTAT->rMode != 3)
		{
			if(g_pCgbRegOCPS->rHL)
				g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] = ((*g_pCgbRegOCPD) << 8) | (g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] & 0x00FF);
			else
				g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] = (g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] & 0xFF00) | (*g_pCgbRegOCPD);
		}
		if(g_pCgbRegOCPS->rAutoInc)
		{
			if(!g_pCgbRegOCPS->rHL)
			{
				g_pCgbRegOCPS->rHL = 1;
				*g_pCgbRegOCPD = (g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] >> 8) & 0xFF;
			}
			else
			{
				g_pCgbRegOCPS->rHL = 0;
				g_nCgbGrpOBJPal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] = CGB_BGRA2RGBA(g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo]);
				++g_pCgbRegOCPS->rPalDataNo;
				if(!g_pCgbRegOCPS->rPalDataNo)
					++g_pCgbRegOCPS->rPalNo;
				*g_pCgbRegOCPD = g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] & 0xFF;
			}
		}
		else
			g_nCgbGrpOBJPal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo] = CGB_BGRA2RGBA(g_nCgbGrpOBJPalReal[g_pCgbRegOCPS->rPalNo][g_pCgbRegOCPS->rPalDataNo]);
		break;
	case 0x70:		// SVBK
		if(g_pCgbRegSVBK->rWRAMBank)
			g_pCgbCurWRAM = &g_pCgbWRAM[g_pCgbRegSVBK->rWRAMBank*0x1000];
		else
			g_pCgbCurWRAM = &g_pCgbWRAM[0x1000];
		if(g_nCgbCpuRegPC >= 0xD000 && g_nCgbCpuRegPC < 0xE000)
		{
			NN_LOG("CpuPC: SVBK\n");
			g_pCgbCpuPC = cgbMemReadOpcode(g_nCgbCpuRegPC);
		}
		break;
	}
}

/** @brief Data Write to Register */
void cgbRegWrite(u8 nAddr, u8 nData)
{
#if TRL_SOUND_CGB_FAST
	if(nAddr >= 0x10 && nAddr <=0x26)
		if(g_pCGBSndRegWriteLog_Run == 0)
		{
			if(g_pCGBSndRegWriteLog_Ct >= TRL_SOUND_REG_LOG_MAX)
			{
				NN_LOG("Error g_pNesSndRegWriteLog_Ct >= TRL_SOUND_REG_LOG_MAX\n");
				return;
			}
			g_pCGBSndRegWriteLog_Addr[g_pCGBSndRegWriteLog_Ct] = nAddr;
			g_pCGBSndRegWriteLog_Value[g_pCGBSndRegWriteLog_Ct] = nData;
			g_pCGBSndRegWriteLog_Ticks[g_pCGBSndRegWriteLog_Ct] = g_nCGBSndRegWriteLog_Ticks;
			g_pCGBSndRegWriteLog_Type[g_pCGBSndRegWriteLog_Ct] = 0;
			g_pCGBSndRegWriteLog_Ct++;

			g_nCgbRegLastVal = g_pCgbREG[nAddr];
			nData &= g_pCgbRegMask[nAddr];
			if(g_pCgbRegRead[nAddr] != 0xFF)
				g_pCgbREG[nAddr] = (nData & g_pCgbRegRead[nAddr]) | (g_pCgbREG[nAddr] & (~g_pCgbRegRead[nAddr]));
			else
				g_pCgbREG[nAddr] = nData;

			return;
		}	
#endif
	g_nCgbRegLastVal = g_pCgbREG[nAddr];
	nData &= g_pCgbRegMask[nAddr];
	if(g_pCgbRegRead[nAddr] != 0xFF)
		g_pCgbREG[nAddr] = (nData & g_pCgbRegRead[nAddr]) | (g_pCgbREG[nAddr] & (~g_pCgbRegRead[nAddr]));
	else
		g_pCgbREG[nAddr] = nData;

	trlTraceSoundDetailWriteReg(nAddr, nData);

	cgbRegUpdate(nAddr);
}

/** @brief Reset Registers */
void cgbRegReset()
{
	for(s16 n=0; n<0x80; ++n)
		g_pCgbREG[n] = 0xFF;
	for(u8 n=0x30; n<0x40; n+=2)
		g_pCgbREG[n] = 0x00;

	g_pCgbREG[0x05] = 0x00;
	g_pCgbREG[0x06] = 0x00;
	g_pCgbREG[0x07] = 0x00;
	g_pCgbREG[0x0F] = 0x01;
	g_pCgbREG[0x10] = 0x80;
	g_pCgbREG[0x11] = 0xBF;
	g_pCgbREG[0x12] = 0xF3;
	g_pCgbREG[0x14] = 0xBF;
	g_pCgbREG[0x16] = 0x3F;
	g_pCgbREG[0x17] = 0x00;
	g_pCgbREG[0x19] = 0xBF;
	g_pCgbREG[0x1A] = 0x7F;
	g_pCgbREG[0x1C] = 0x9F;
	g_pCgbREG[0x1E] = 0xBF;
	g_pCgbREG[0x21] = 0x00;
	g_pCgbREG[0x22] = 0x00;
	g_pCgbREG[0x23] = 0xBF;
	g_pCgbREG[0x24] = 0x77;
	g_pCgbREG[0x25] = 0xF3;
	g_pCgbREG[0x26] = 0xF1;
	g_pCgbREG[0x40] = 0x91;
	g_pCgbREG[0x42] = 0x00;
	g_pCgbREG[0x43] = 0x00;
	g_pCgbREG[0x45] = 0x00;
	g_pCgbREG[0x47] = 0xFC;
	g_pCgbREG[0x4D] = 0x7E;
	g_pCgbREG[0x72] = 0x00;
	g_pCgbREG[0x73] = 0x00;
	g_pCgbREG[0x75] = 0x8F;
	g_pCgbREG[0x76] = 0x00;
	g_pCgbREG[0x77] = 0x00;
	g_pCgbREG[0xFF] = 0x00;
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		g_pCgbREG[0x02] = 0x7C;
		g_pCgbREG[0x04] = 0x1E;
		g_pCgbREG[0x41] = 0x81;
		g_pCgbREG[0x44] = 0x90;
		g_pCgbREG[0x4A] = 0x00;
		g_pCgbREG[0x4B] = 0x00;
		g_pCgbREG[0x4F] = 0xFE;
		g_pCgbREG[0x52] = 0xF0;
		g_pCgbREG[0x53] = 0x9F;
		g_pCgbREG[0x54] = 0xF0;
		g_pCgbREG[0x56] = 0x3E;
		g_pCgbREG[0x68] = 0xC0;
		g_pCgbREG[0x6A] = 0xC0;
		g_pCgbREG[0x6C] = 0xFE;
		g_pCgbREG[0x70] = 0xF8;
		g_pCgbREG[0x74] = 0x00;
	}
	else
	{
		g_pCgbREG[0x02] = 0x7E;
		g_pCgbREG[0x04] = 0x26;
		g_pCgbREG[0x41] = 0x01;
		g_pCgbREG[0x44] = 0x94;
	}

	for(u8 n=0x10; n<=0x26; ++n)
		cgbRegUpdate(n);
} 

/** @brief Exit Registers */
void cgbRegExit()
{
	trlMemFree(g_pCgbRegMask);
	trlMemFree(g_pCgbRegWrite);
	trlMemFree(g_pCgbRegRead);
}
