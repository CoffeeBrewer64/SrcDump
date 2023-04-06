/**
 * @file agbRegister.h
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Register
 */
#pragma once
#include "agbDataStruct.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u8*					g_pAgbRegWrite;		///< I/O and Registers Write Only Code
extern agbSRegDISPCNT*		g_pAgbDispCnt;		///< 0x000
extern agbSRegDISPSTAT*		g_pAgbDispStat;		///< 0x004
extern agbSRegVCOUNT*		g_pAgbVCount;		///< 0x006
extern agbSRegBGCNT*		g_pAgbBGCnt[4];		///< 0x008, 0x00A, 0x00C, 0x00E
extern agbSRegBGOFS*		g_pAgbBGHofs[4];	///< 0x010, 0x014, 0x018, 0x01C
extern agbSRegBGOFS*		g_pAgbBGVofs[4];	///< 0x012, 0x016, 0x01A, 0x01E
extern u16*					g_pAgbBGPA[2];		///< 0x020, 0x030
extern u16*					g_pAgbBGPB[2];		///< 0x022, 0x032
extern u16*					g_pAgbBGPC[2];		///< 0x024, 0x034
extern u16*					g_pAgbBGPD[2];		///< 0x026, 0x036
extern agbSRegBGSP*			g_pAgbBGX[2];		///< 0x028, 0x038
extern agbSRegBGSP*			g_pAgbBGY[2];		///< 0x02C, 0x03C
extern agbSRegWINCOORD*		g_pAgbWINH[2];		///< 0x040, 0x044
extern agbSRegWINCOORD*		g_pAgbWINV[2];		///< 0x042, 0x046
extern agbSRegWINCNT*		g_pAgbWININ;		///< 0x048
extern agbSRegWINCNT*		g_pAgbWINOUT;		///< 0x04A
extern agbSRegMOSAIC*		g_pAgbMosaic;		///< 0x04C
extern agbSRegBLDCNT*		g_pAgbBLDCnt;		///< 0x050
extern agbSRegBLDALPHA*		g_pAgbBLDAlpha;		///< 0x052
extern agbSRegBLDY*			g_pAgbBLDY;			///< 0x054
extern agbSRegSOUND1CNTL*	g_pAgbSound1CntL;	///< 0x060
extern agbSRegSOUNDXCNT12*	g_pAgbSound1CntH;	///< 0x062
extern agbSRegSOUNDXCNT34*	g_pAgbSound1CntX;	///< 0x064
extern agbSRegSOUNDXCNT12*	g_pAgbSound2CntL;	///< 0x068
extern agbSRegSOUNDXCNT34*	g_pAgbSound2CntH;	///< 0x06C
extern agbSRegSOUND3CNTL*	g_pAgbSound3CntL;	///< 0x070
extern agbSRegSOUND3CNTH*	g_pAgbSound3CntH;	///< 0x072
extern agbSRegSOUNDXCNT34*	g_pAgbSound3CntX;	///< 0x074
extern agbSRegSOUNDXCNT12*	g_pAgbSound4CntL;	///< 0x078
extern agbSRegSOUND4CNTH*	g_pAgbSound4CntH;	///< 0x07C
extern agbSRegSOUNDCNTL*	g_pAgbSoundCntL;	///< 0x080
extern agbSRegSOUNDCNTH*	g_pAgbSoundCntH;	///< 0x082
extern agbSRegSOUNDCNTX*	g_pAgbSoundCntX;	///< 0x084
extern agbSRegSOUNDBIAS*	g_pAgbSoundBias;	///< 0x088
extern agbSRegWAVERAM*		g_pAgbWaveRam0L;	///< 0x090
extern agbSRegWAVERAM*		g_pAgbWaveRam0H;	///< 0x092
extern agbSRegWAVERAM*		g_pAgbWaveRam1L;	///< 0x094
extern agbSRegWAVERAM*		g_pAgbWaveRam1H;	///< 0x096
extern agbSRegWAVERAM*		g_pAgbWaveRam2L;	///< 0x098
extern agbSRegWAVERAM*		g_pAgbWaveRam2H;	///< 0x09A
extern agbSRegWAVERAM*		g_pAgbWaveRam3L;	///< 0x09C
extern agbSRegWAVERAM*		g_pAgbWaveRam3H;	///< 0x09E
extern agbSRegFIFO*			g_pAgbFifoA;		///< 0x0A0
extern agbSRegFIFO*			g_pAgbFifoB;		///< 0x0A4
extern agbSRegDMAAddr27*	g_pAgbDMA0Sad;		///< 0x0B0
extern agbSRegDMAAddr27*	g_pAgbDMA0Dad;		///< 0x0B4
extern agbSRegDMACNTL*		g_pAgbDMA0Count;	///< 0x0B8
extern agbSRegDMACNTH*		g_pAgbDMACnt[4];	///< 0x0BA, 0x0C6, 0x0D2£¬0x0DE
extern agbSRegDMAAddr28*	g_pAgbDMA1Sad;		///< 0x0BC
extern agbSRegDMAAddr27*	g_pAgbDMA1Dad;		///< 0x0C0
extern agbSRegDMACNTL*		g_pAgbDMA1Count;	///< 0x0C4
extern agbSRegDMAAddr28*	g_pAgbDMA2Sad;		///< 0x0C8
extern agbSRegDMAAddr27*	g_pAgbDMA2Dad;		///< 0x0CC
extern agbSRegDMACNTL*		g_pAgbDMA2Count;	///< 0x0D0
extern agbSRegDMAAddr28*	g_pAgbDMA3Sad;		///< 0x0D4
extern agbSRegDMAAddr28*	g_pAgbDMA3Dad;		///< 0x0D8
extern u16*					g_pAgbDMA3Count;	///< 0x0DC
extern u16*					g_pAgbTMCntL[4];	///< 0x100, 0x104, 0x108, 0x10C
extern agbSRegTMCNT*		g_pAgbTMCntH[4];	///< 0x102, 0x106, 0x10A, 0x10E
extern agbSRegKEYINPUT*		g_pAgbKeyInput;		///< 0x130
extern agbSRegKEYCNT*		g_pAgbKeyCnt;		///< 0x132
extern agbSRegINT*			g_pAgbIE;			///< 0x200
extern agbSRegINT*			g_pAgbIF;			///< 0x202
extern agbSRegWAITCNT*		g_pAgbWaitCnt;		///< 0x204
extern agbSRegIME*			g_pAgbIME;			///< 0x208
extern agbSRegHALTCNT*		g_pAgbHaltCnt;		///< 0x300
//@}

/** @brief Initialize Registers */
void agbRegInit();
/** @brief Reset Registers */
void agbRegReset();

/** @brief Write 8 bits data to Registers */
void agbRegWrite8(u32 nAddr, u8 nData);
/** @brief Write 16 bits data to Registers */
void agbRegWrite16(u32 nAddr, u16 nData);
/** @brief Write 32 bits data to Registers */
void agbRegWrite32(u32 nAddr, u32 nData);
