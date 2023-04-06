/**
 * @file agbSound.cpp
 * @author Chentian
 * @date 2009.11.24
 * @brief AGB Emulate For CTR - Sound
 */
#include "agbSound.h"
#include "agbRegister.h"
#include "agbDMA.h"

/** @name Macro Define */
//@{
#define		AGB_SND_TICKS					380			///< Sound Interval Ticks
#define		AGB_SND_FIFOBUFFER				32			///< Sound FIFO Buffer Size
#define		AGB_SND_SOUND1					0			///< Sound 1
#define		AGB_SND_SOUND2					1			///< Sound 2
#define		AGB_SND_SOUND3					2			///< Sound 3
#define		AGB_SND_SOUND4					3			///< Sound 4
#define		AGB_SND_SOUNDA					4			///< Direct Sound A
#define		AGB_SND_SOUNDB					5			///< Direct Sound B
#define		AGB_SND_LENGTH1					172			///< The Length of The Output Sound (44100/256)
#define		AGB_SND_LENGTH2					344			///< The Length of The Output Sound (44100/128)
#define		AGB_SND_LENGTH3					689			///< The Length of The Output Sound (44100/64)
#define		AGB_SND_FREQ					0x30000000 	///< The Fixed Value Of The Output Frequency's Formula	//0x20000
#define		AGB_SND_NOISE					5
//@}

/** @name Global Variable */
//@{
u8			g_nAgbSndWavePattern[4][8] = {				///< Sound Wave Pattern Data
				0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
				0x01,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
				0x01,0x01,0x01,0x01,0xFF,0xFF,0xFF,0xFF,
				0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF };
const s32	g_nAgbSndFreqRatio[8] = 					///< Sound Frequency Ratio (4.194304 MHz / 8 / (0.5~7))
				{ 1048576, 524288, 262144, 174763, 131072, 104858, 87381, 74898 };
const s32	g_nAgbSndShiftClock[16]= 					///< Sound Shift Clock Frequency's Formula
				{ 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 1, 1 };

s32			g_nAgbSndTicks = 0;							///< Sound Ticks
s16*		g_pAgbSndBuf;								///< Sound Data Buffer Header
s32			g_nAgbSndBufSize = 0;						///< Sound Data Buffer Size
s32			g_nAgbSndBufPos = 0;						///< Sound Data Buffer Size
s32			g_nAgbSndBufOutput1 = 0;					///< Sound Data Output 1
s32			g_nAgbSndBufOutput2 = 0;					///< Sound Data Output 2

s8			g_nAgbSndFifoBuf[2][AGB_SND_FIFOBUFFER];	///< Sound FIFO Buffer
s32			g_nAgbSndFifoIdxW[2] = {0,0};				///< Sound FIFO Buffer Write Index
s32			g_nAgbSndFifoIdxR[2] = {0,0};				///< Sound FIFO Buffer Read Index
s32			g_nAgbSndFifoCount[2] = {0,0};				///< Sound FIFO Byte Count
s8			g_nAgbSndFifoValue[2] = {0,0};				///< Sound FIFO Value

s32			g_nAgbSnd1Index = 0;						///< Sound Data Index
s32			g_nAgbSnd1Length = 0;						///< Sound Length
s32			g_nAgbSnd1Frequency = 0;					///< Sound Output Frequency
s32			g_nAgbSnd1EnvelopeValue = 0;				///< Sound Envelope Value
s32			g_nAgbSnd1EnvelopeLength = 0;				///< Sound Envelope Length
s32			g_nAgbSnd1EnvelopeLengthInit = 0;			///< Sound Envelope Length Init Value

s32			g_nAgbSnd2Index = 0;						///< Sound Data Index
s32			g_nAgbSnd2Length = 0;						///< Sound Length
s32			g_nAgbSnd2Frequency = 0;					///< Sound Output Frequency
s32			g_nAgbSnd2EnvelopeValue = 0;				///< Sound Envelope Value
s32			g_nAgbSnd2EnvelopeLength = 0;				///< Sound Envelope Length
s32			g_nAgbSnd2EnvelopeLengthInit = 0;			///< Sound Envelope Length Init Value

s32			g_nAgbSnd3Index = 0;						///< Sound Data Index
s32			g_nAgbSnd3Length = 0;						///< Sound Length
s32			g_nAgbSnd3Frequency = 0;					///< Sound Output Frequency

s32			g_nAgbSnd4Index = 0;						///< Sound Data Index
s32			g_nAgbSnd4Length = 0;						///< Sound Length
s32			g_nAgbSnd4Frequency = 0;					///< Sound Output Frequency
s32			g_nAgbSnd4EnvelopeValue = 0;				///< Sound Envelope Value
s32			g_nAgbSnd4EnvelopeLength = 0;				///< Sound Envelope Length
s32			g_nAgbSnd4EnvelopeLengthInit = 0;			///< Sound Envelope Length Init Value

u8*			g_pAgbSnd1Wave = g_nAgbSndWavePattern[2];	///< Sound 1 Wave
s32			g_nAgbSnd1SweepLength = 0;					///< Sound 1 Sweep Length
s32			g_nAgbSnd1SweepLengthInit = 0;				///< Sound 1 Sweep Length Init Value
u8*			g_pAgbSnd2Wave = g_nAgbSndWavePattern[2];	///< Sound 2 Wave
u8			g_nAgbSnd3WaveRam[32];						///< Sound 3 Waveform RAM Data
s32			g_nAgbSnd3Bank = 1;							///< Sound 3 I/O Bank
s32			g_nAgbSnd4Shift = 0x7F;						///< Sound 4 Shift
//@}

/** @brief Initialize Sound */
void agbSndInit()
{
	g_pAgbSndBuf = (s16*)g_pAgbEmuBuf->pSoundBuf;
	g_nAgbSndBufSize = g_pAgbEmuBuf->nSoundBufSize >> 1;
	g_nAgbSndBufPos = g_nAgbSndBufSize >> 1;

	agbSndReset();
}

/** @brief Reset Sound */
void agbSndReset()
{
}

/** @brief Update Sound Registers for 8 Bits */
void agbSndUpdateReg8(u32 nAddr)
{
	switch(nAddr)
	{
	case 0x060:		// NR10
		g_nAgbSnd1SweepLength = g_nAgbSnd1SweepLengthInit = AGB_SND_LENGTH2 * g_pAgbSound1CntL->rTime;
		break;
	case 0x062:		// NR11
		g_pAgbSnd1Wave = g_nAgbSndWavePattern[g_pAgbSound1CntH->rDuty];
		g_nAgbSnd1Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound1CntH->rLength);
		break;
	case 0x063:		// NR12
		g_nAgbSnd1EnvelopeLengthInit = AGB_SND_LENGTH3 * g_pAgbSound1CntH->rSteps;
		if(!g_pAgbSound1CntH->rDirection && !g_pAgbSound1CntH->rValue)
			g_nAgbSnd1EnvelopeValue = 0;
		break;
	case 0x064:		// NR13
		g_nAgbSnd1Frequency = (AGB_SND_FREQ<<1) / (2048 - g_pAgbSound1CntX->rFreq);
		g_nAgbSnd1Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound1CntH->rLength);
		break;
	case 0x065:		// NR14
		g_nAgbSnd1Frequency = (AGB_SND_FREQ<<1) / (2048 - g_pAgbSound1CntX->rFreq);
		g_nAgbSnd1Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound1CntH->rLength);
		if(g_pAgbSound1CntX->rInitial)
		{
			g_pAgbSoundCntX->rSound1 = 1;
			g_nAgbSnd1Index = 0;
			g_nAgbSnd1EnvelopeValue = g_pAgbSound1CntH->rValue;
			g_nAgbSnd1EnvelopeLength = g_nAgbSnd1EnvelopeLengthInit = AGB_SND_LENGTH3 * g_pAgbSound1CntH->rSteps;
			g_nAgbSnd1SweepLength = g_nAgbSnd1SweepLengthInit = AGB_SND_LENGTH2 * g_pAgbSound1CntL->rTime;
		}
		break;
	case 0x068:		// NR21
		g_pAgbSnd2Wave = g_nAgbSndWavePattern[g_pAgbSound2CntL->rDuty];
 		g_nAgbSnd2Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound2CntL->rLength);
		break;
	case 0x069:		// NR22
		g_nAgbSnd2EnvelopeLengthInit = AGB_SND_LENGTH3 * g_pAgbSound2CntL->rSteps;
		if(!g_pAgbSound2CntL->rDirection && !g_pAgbSound2CntL->rValue)
			g_nAgbSnd2EnvelopeValue = 0;
		break;
	case 0x06C:		// NR23
		g_nAgbSnd2Frequency = (AGB_SND_FREQ<<1) / (2048 - g_pAgbSound2CntH->rFreq);
		g_nAgbSnd2Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound2CntL->rLength); 
		break;
	case 0x06D:		// NR24
		g_nAgbSnd2Frequency = (AGB_SND_FREQ<<1) / (2048 - g_pAgbSound2CntH->rFreq);
		g_nAgbSnd2Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound2CntL->rLength); 
		if(g_pAgbSound2CntH->rInitial)
		{
			g_pAgbSoundCntX->rSound2 = 1;
			g_nAgbSnd2Index = 0;
			g_nAgbSnd2EnvelopeValue = g_pAgbSound2CntL->rValue;
			g_nAgbSnd2EnvelopeLength = g_nAgbSnd2EnvelopeLengthInit = AGB_SND_LENGTH3 * g_pAgbSound2CntL->rSteps;
		}
		break;
	case 0x070:		// NR30
		if(!g_pAgbSound3CntL->rOutput)
			g_pAgbSoundCntX->rSound3 = 0;
		if(g_pAgbSound3CntL->rBank == g_nAgbSnd3Bank)
		{
			g_nAgbSnd3Bank = g_pAgbSound3CntL->rBank ^ 1;
			trlMemCopy(&g_pAgbREG[0x90], &g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16], 16);
		}
		break;
	case 0x072:		// NR31
		g_nAgbSnd3Length = AGB_SND_LENGTH1 * (256 - g_pAgbSound3CntH->rLength);
		break;
	case 0x074:		// NR33
		g_nAgbSnd3Frequency = AGB_SND_FREQ / (2048 - g_pAgbSound3CntX->rFreq);
//		g_nAgbSnd3Length = AGB_SND_LENGTH1 * (256 - g_pAgbSound3CntH->rLength);
		break;
	case 0x075:		// NR34
		g_nAgbSnd3Frequency = AGB_SND_FREQ / (2048 - g_pAgbSound3CntX->rFreq);
		g_nAgbSnd3Length = AGB_SND_LENGTH1 * (256 - g_pAgbSound3CntH->rLength);
		if(g_pAgbSound3CntX->rInitial && g_pAgbSound3CntL->rOutput)
		{
			g_pAgbSoundCntX->rSound3 = 1;
			g_nAgbSnd3Index = 0;
		}
		break;
	case 0x078:		// NR41
		g_nAgbSnd4Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound4CntL->rLength); 
		break;
	case 0x079:		// NR42
		g_nAgbSnd4EnvelopeLengthInit = AGB_SND_LENGTH3 * g_pAgbSound4CntL->rSteps;
		if(!g_pAgbSound4CntL->rDirection && !g_pAgbSound4CntL->rValue)
			g_nAgbSnd4EnvelopeValue = 0;
		break;
	case 0x07C:		// NR43
		g_nAgbSnd4Frequency = ((g_nAgbSndFreqRatio[g_pAgbSound4CntH->rDividingRatio] / g_nAgbSndShiftClock[g_pAgbSound4CntH->rShiftClock]) << 8) / AGB_SND_NOISE;
		break;
	case 0x07D:		// NR44
		if(g_pAgbSound4CntH->rInitial)
		{
			g_pAgbSoundCntX->rSound4 = 1;
			g_nAgbSnd4Index = 0;

			g_nAgbSnd4Length  = AGB_SND_LENGTH1 * (64 - g_pAgbSound4CntL->rLength); 
			g_nAgbSnd4Frequency = ((g_nAgbSndFreqRatio[g_pAgbSound4CntH->rDividingRatio] / g_nAgbSndShiftClock[g_pAgbSound4CntH->rShiftClock]) << 8) / AGB_SND_NOISE;
			g_nAgbSnd4Shift = g_pAgbSound4CntH->rStepNumber ? 0x7F : 0x7FFF;

			g_nAgbSnd4EnvelopeValue = g_pAgbSound4CntL->rValue;
			g_nAgbSnd4EnvelopeLength = g_nAgbSnd4EnvelopeLengthInit = AGB_SND_LENGTH3 * g_pAgbSound4CntL->rSteps;
		}
		break;
	case 0x084:		// NR52
		if(!g_pAgbSoundCntX->rSoundAll)
		{
			g_pAgbSoundCntX->rSound1 = 0;
			g_pAgbSoundCntX->rSound2 = 0;
			g_pAgbSoundCntX->rSound3 = 0;
			g_pAgbSoundCntX->rSound4 = 0;
		}
		break;
	case 0x090:		// WAVE_RAM0_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16] = g_pAgbWaveRam0L->rStep01;
		break;
	case 0x091:		// WAVE_RAM0_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+1] = g_pAgbWaveRam0L->rStep23;
		break;
	case 0x092:		// WAVE_RAM0_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+2] = g_pAgbWaveRam0H->rStep01;
		break;
	case 0x093:		// WAVE_RAM0_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+3] = g_pAgbWaveRam0H->rStep23;
		break;
	case 0x094:		// WAVE_RAM1_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+4] = g_pAgbWaveRam1L->rStep01;
		break;
	case 0x095:		// WAVE_RAM1_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+5] = g_pAgbWaveRam1L->rStep23;
		break;
	case 0x096:		// WAVE_RAM1_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+6] = g_pAgbWaveRam1H->rStep01;
		break;
	case 0x097:		// WAVE_RAM1_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+7] = g_pAgbWaveRam1H->rStep23;
		break;
	case 0x098:		// WAVE_RAM2_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+8] = g_pAgbWaveRam2L->rStep01;
		break;
	case 0x099:		// WAVE_RAM2_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+9] = g_pAgbWaveRam2L->rStep23;
		break;
	case 0x09A:		// WAVE_RAM2_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+10] = g_pAgbWaveRam2H->rStep01;
		break;
	case 0x09B:		// WAVE_RAM2_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+11] = g_pAgbWaveRam2H->rStep23;
		break;
	case 0x09C:		// WAVE_RAM3_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+12] = g_pAgbWaveRam3L->rStep01;
		break;
	case 0x09D:		// WAVE_RAM3_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+13] = g_pAgbWaveRam3L->rStep23;
		break;
	case 0x09E:		// WAVE_RAM3_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+14] = g_pAgbWaveRam3H->rStep01;
		break;
	case 0x09F:		// WAVE_RAM3_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+15] = g_pAgbWaveRam3H->rStep23;
		break;
	}
}

/** @brief Update Sound Registers for 16 Bits */
void agbSndUpdateReg16(u32 nAddr)
{
	if(nAddr <= 0x84)
	{
		agbSndUpdateReg8(nAddr);
		agbSndUpdateReg8(nAddr+1);
		return;
	}
	switch(nAddr)
	{
	case 0x082:		// SOUNDCNT_H
		if(g_pAgbSoundCntH->rFIFOA)
		{
			g_pAgbSoundCntH->rFIFOA = 0;
			g_nAgbSndFifoIdxW[0] = 0;
			g_nAgbSndFifoIdxR[0] = 0;
			g_nAgbSndFifoCount[0] = 0;
			g_nAgbSndFifoValue[0] = 0;
			memset(g_nAgbSndFifoBuf[0], 0, AGB_SND_FIFOBUFFER);
		}
		if(g_pAgbSoundCntH->rFIFOB)
		{
			g_pAgbSoundCntH->rFIFOB = 0;
			g_nAgbSndFifoIdxW[1] = 0;
			g_nAgbSndFifoIdxR[1] = 0;
			g_nAgbSndFifoCount[1] = 0;
			g_nAgbSndFifoValue[1] = 0;
			memset(g_nAgbSndFifoBuf[1], 0, AGB_SND_FIFOBUFFER);
		}
		break;
	case 0x090:		// WAVE_RAM0_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16] = g_pAgbWaveRam0L->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+1] = g_pAgbWaveRam0L->rStep23;
		break;
	case 0x092:		// WAVE_RAM0_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+2] = g_pAgbWaveRam0H->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+3] = g_pAgbWaveRam0H->rStep23;
		break;
	case 0x094:		// WAVE_RAM1_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+4] = g_pAgbWaveRam1L->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+5] = g_pAgbWaveRam1L->rStep23;
		break;
	case 0x096:		// WAVE_RAM1_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+6] = g_pAgbWaveRam1H->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+7] = g_pAgbWaveRam1H->rStep23;
		break;
	case 0x098:		// WAVE_RAM2_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+8] = g_pAgbWaveRam2L->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+9] = g_pAgbWaveRam2L->rStep23;
		break;
	case 0x09A:		// WAVE_RAM2_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+10] = g_pAgbWaveRam2H->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+11] = g_pAgbWaveRam2H->rStep23;
		break;
	case 0x09C:		// WAVE_RAM3_L
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+12] = g_pAgbWaveRam3L->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+13] = g_pAgbWaveRam3L->rStep23;
		break;
	case 0x09E:		// WAVE_RAM3_H
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+14] = g_pAgbWaveRam3H->rStep01;
		g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+15] = g_pAgbWaveRam3H->rStep23;
		break;
	case 0x0A0:		// FIFO_A_L
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData0;
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData1;
		g_nAgbSndFifoIdxW[0] &= 0x1F;
		g_nAgbSndFifoCount[0] += 2;
		break;
	case 0x0A2:		// FIFO_A_H
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData2;
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData3;
		g_nAgbSndFifoIdxW[0] &= 0x1F;
		g_nAgbSndFifoCount[0] += 2;
		break;
	case 0x0A4:		// FIFO_B_L
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData0;
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData1;
		g_nAgbSndFifoIdxW[1] &= 0x1F;
		g_nAgbSndFifoCount[1] += 2;
		break;
	case 0x0A6:		// FIFO_B_H
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData2;
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData3;
		g_nAgbSndFifoIdxW[1] &= 0x1F;
		g_nAgbSndFifoCount[1] += 2;
		break;
	}
}

/** @brief Update Sound Registers for 32 Bits */
void agbSndUpdateReg32(u32 nAddr)
{
	switch(nAddr)
	{
	case 0x090:		// WAVE_RAM0
		trlMemCopy(&g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16], &g_pAgbREG[nAddr], 4);
		break;
	case 0x094:		// WAVE_RAM1
		trlMemCopy(&g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+4], &g_pAgbREG[nAddr], 4);
		break;
	case 0x098:		// WAVE_RAM2
		trlMemCopy(&g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+8], &g_pAgbREG[nAddr], 4);
		break;
	case 0x09C:		// WAVE_RAM3
		trlMemCopy(&g_nAgbSnd3WaveRam[g_nAgbSnd3Bank*16+12], &g_pAgbREG[nAddr], 4);
		break;
	case 0x0A0:		// FIFO_A_L
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData0;
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData1;
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData2;
		g_nAgbSndFifoBuf[0][g_nAgbSndFifoIdxW[0]++] = g_pAgbFifoA->rSoundData3;
		g_nAgbSndFifoIdxW[0] &= 0x1F;
		g_nAgbSndFifoCount[0] += 4;
		break;
	case 0x0A4:		// FIFO_B_L
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData0;
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData1;
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData2;
		g_nAgbSndFifoBuf[1][g_nAgbSndFifoIdxW[1]++] = g_pAgbFifoB->rSoundData3;
		g_nAgbSndFifoIdxW[1] &= 0x1F;
		g_nAgbSndFifoCount[1] += 4;
		break;
	}
}

/** @brief Process Sound Channel 1 */
inline void agbSndChannel1()
{
	// Process Data
	if(g_nAgbSnd1Length || !g_pAgbSound1CntX->rCounter)
	{
		g_nAgbSnd1Index += g_nAgbSnd1Frequency;
		g_nAgbSnd1Index &= 0x1FFFFFFF;

		s8 nData = ((s8)g_pAgbSnd1Wave[g_nAgbSnd1Index>>26]) * g_nAgbSnd1EnvelopeValue;
		if(g_pAgbSoundCntL->rSoundL & 1)
			g_nAgbSndBufOutput1 += nData;
		if(g_pAgbSoundCntL->rSoundR & 1)
			g_nAgbSndBufOutput2 += nData;
	}

	// Calculate Length
	if(g_nAgbSnd1Length)
	{
		--g_nAgbSnd1Length;
		if(g_nAgbSnd1Length <=0 && g_pAgbSound1CntX->rCounter)
			g_pAgbSoundCntX->rSound1 = 0;
	}

	// Process Envelope
	if(g_nAgbSnd1EnvelopeLength)
	{
		--g_nAgbSnd1EnvelopeLength;
		if(g_nAgbSnd1EnvelopeLength <= 0)
		{
			if(g_pAgbSound1CntH->rDirection)
			{
				if(g_nAgbSnd1EnvelopeValue < 15)
					++g_nAgbSnd1EnvelopeValue;
			}
			else
			{
				if(g_nAgbSnd1EnvelopeValue)
					--g_nAgbSnd1EnvelopeValue;
			}
			g_nAgbSnd1EnvelopeLength += g_nAgbSnd1EnvelopeLengthInit;
		}
	}

	if(g_nAgbSnd1SweepLength)
	{
		--g_nAgbSnd1SweepLength;
		if(g_nAgbSnd1SweepLength<=0)
		{
			s32 nFreq = g_pAgbSound1CntX->rFreq;
			if(g_pAgbSound1CntL->rShift)
			{
				nFreq = (g_pAgbSound1CntL->rAS ? -1 : 1) * g_pAgbSound1CntX->rFreq / (1 << g_pAgbSound1CntL->rShift);
				if(nFreq == g_pAgbSound1CntX->rFreq)
					nFreq = 0;
			}

			if(nFreq < 0)
				g_nAgbSnd1SweepLength += g_nAgbSnd1SweepLengthInit;
			else if(nFreq > 2047)
			{
				g_nAgbSnd1SweepLength = 0;
				g_pAgbSoundCntX->rSound1 = 0;
			}
			else
			{
				g_nAgbSnd1SweepLength += g_nAgbSnd1SweepLengthInit;
				g_nAgbSnd1Frequency = (AGB_SND_FREQ<<1)/(2048 - nFreq);
				g_pAgbSound1CntX->rFreq = nFreq;
			}
		}
	}
}

/** @brief Process Sound Channel 2 */
inline void agbSndChannel2()
{
	// Process Data
	if(g_nAgbSnd2Length || !g_pAgbSound2CntH->rCounter)
	{
		g_nAgbSnd2Index += g_nAgbSnd2Frequency;
		g_nAgbSnd2Index &= 0x1FFFFFFF;
		s8 nData = ((s8)g_pAgbSnd2Wave[g_nAgbSnd2Index>>26]) * g_nAgbSnd2EnvelopeValue;
		if(g_pAgbSoundCntL->rSoundL & 2)
			g_nAgbSndBufOutput1 += nData;
		if(g_pAgbSoundCntL->rSoundR & 2)
			g_nAgbSndBufOutput2 += nData;
	}

	// Calculate Length
	if(g_nAgbSnd2Length)
	{
		--g_nAgbSnd2Length;
		if(g_nAgbSnd2Length <= 0 && g_pAgbSound2CntH->rCounter)
			g_pAgbSoundCntX->rSound2 = 0;
	}

	// Process Envelope
	if(g_nAgbSnd2EnvelopeLength)
	{
		--g_nAgbSnd2EnvelopeLength;
		if(g_nAgbSnd2EnvelopeLength <= 0)
		{
			if(g_pAgbSound2CntL->rDirection)
			{
				if(g_nAgbSnd2EnvelopeValue < 15)
					++g_nAgbSnd2EnvelopeValue;
			}
			else
			{
				if(g_nAgbSnd2EnvelopeValue)
					--g_nAgbSnd2EnvelopeValue;
			}
			g_nAgbSnd2EnvelopeLength += g_nAgbSnd2EnvelopeLengthInit;
		}
	}
}

/** @brief Process Sound Channel 3 */
inline void agbSndChannel3()
{
	s32 nData = 0;
	// Process Data
	if(g_nAgbSnd3Length || !g_pAgbSound3CntX->rCounter)
	{
		g_nAgbSnd3Index += g_nAgbSnd3Frequency;
		if(g_pAgbSound3CntL->rData)	// 64 Steps
		{
			g_nAgbSnd3Index &= 0x3FFFFFFF;
			nData = g_nAgbSnd3WaveRam[g_nAgbSnd3Index>>25];
		}
		else						// 32 Steps
		{
			g_nAgbSnd3Index &= 0x1FFFFFFF;
			nData = g_nAgbSnd3WaveRam[g_pAgbSound3CntL->rBank*16 + (g_nAgbSnd3Index>>25)];
		}

		if(g_nAgbSnd3Index & 0x01000000)
			nData &= 0x0F;
		else
			nData >>= 4;

		nData -= 8;
		nData *= 2;

		if(g_pAgbSound3CntH->rForcedLevel)
			nData = (nData >> 2) + (nData >> 1);
		else
		{
			switch(g_pAgbSound3CntH->rLevel)
			{
			case 0:
				nData = 0;
				break;
			case 2:
				nData >>= 1;
				break;
			case 3:
				nData >>= 2;
				break;
			}
		}
	}
	// Calculate Length
	if(g_nAgbSnd3Length)
	{
		--g_nAgbSnd3Length;
		if(g_nAgbSnd3Length <= 0 && g_pAgbSound3CntX->rCounter)
			g_pAgbSoundCntX->rSound3 = 0;
	}
	if(g_pAgbSoundCntL->rSoundL & 4)
		g_nAgbSndBufOutput1 += (s8)nData;
	if(g_pAgbSoundCntL->rSoundR & 4)
		g_nAgbSndBufOutput2 += (s8)nData;
}

/** @brief Process Sound Channel 4 */
inline void agbSndChannel4()
{
	// Process Data
	if((g_nAgbSnd4Length || !g_pAgbSound4CntH->rCounter) && (g_pAgbSound4CntH->rShiftClock < 0x0D))
	{
		g_nAgbSnd4Index += g_nAgbSnd4Frequency;
		if(g_pAgbSound4CntH->rStepNumber)	// 7 Steps
		{
			while(g_nAgbSnd4Index >= 0x200000)
			{
				g_nAgbSnd4Shift = (((g_nAgbSnd4Shift << 6) ^ (g_nAgbSnd4Shift << 5)) & 0x40) | (g_nAgbSnd4Shift >> 1);
				g_nAgbSnd4Index -= 0x200000;
			}
		}
		else								// 15 Steps
		{
			while(g_nAgbSnd4Index >= 0x200000)
			{
				g_nAgbSnd4Shift = (((g_nAgbSnd4Shift << 14) ^ (g_nAgbSnd4Shift << 13)) & 0x4000) | (g_nAgbSnd4Shift >> 1);
				g_nAgbSnd4Index -= 0x200000;
			}
		}
		s8 nData = ((g_nAgbSnd4Shift & 1) ? 1 : -1) * g_nAgbSnd4EnvelopeValue;
		if(g_pAgbSoundCntL->rSoundL & 8)
			g_nAgbSndBufOutput1 += nData;
		if(g_pAgbSoundCntL->rSoundR & 8)
			g_nAgbSndBufOutput2 += nData;
	}

	// Calculate Length
	if(g_nAgbSnd4Length)
	{
		--g_nAgbSnd4Length;
		if(g_nAgbSnd4Length <= 0 && g_pAgbSound4CntH->rCounter)
			g_pAgbSoundCntX->rSound4 = 0;
	}

	// Process Envelope
	if(g_nAgbSnd4EnvelopeLength)
	{
		--g_nAgbSnd4EnvelopeLength;
		if(g_nAgbSnd4EnvelopeLength <= 0)
		{
			if(g_pAgbSound4CntL->rDirection)
			{
				if(g_nAgbSnd4EnvelopeValue < 15)
					++g_nAgbSnd4EnvelopeValue;
			}
			else
			{
				if(g_nAgbSnd4EnvelopeValue)
					--g_nAgbSnd4EnvelopeValue;
			}
			g_nAgbSnd4EnvelopeLength += g_nAgbSnd4EnvelopeLengthInit;
		}
	}
}

/** @brief Process Direct Sound Timer */
inline void agbSndDirectSoundTimer(u32 nDSound)
{
	if(g_nAgbSndFifoCount[nDSound] <= 16)
	{
		agbDmaTransferDirectSoundFIFO(1+nDSound);
		if(g_nAgbSndFifoCount[nDSound] <= 16)
		{
			do{
				g_nAgbSndFifoBuf[nDSound][g_nAgbSndFifoIdxW[nDSound]++] = 0;
				g_nAgbSndFifoBuf[nDSound][g_nAgbSndFifoIdxW[nDSound]++] = 0;
				g_nAgbSndFifoIdxW[nDSound] &= 0x1F;
				g_nAgbSndFifoCount[nDSound] += 2;
			}while(g_nAgbSndFifoCount[nDSound] < AGB_SND_FIFOBUFFER);
		}
	}

	g_nAgbSndFifoValue[nDSound] = g_nAgbSndFifoBuf[nDSound][g_nAgbSndFifoIdxR[nDSound]++];
	g_nAgbSndFifoIdxR[nDSound] &= 0x1F;
	--g_nAgbSndFifoCount[nDSound];
}

/** @brief Process Direct Sound Timer Overflow */
void agbSndTimerOverflow(u32 nTimer)
{
	if((g_pAgbSoundCntH->rLOutputA | g_pAgbSoundCntH->rROutputA) && (g_pAgbSoundCntH->rTimerA == nTimer))
		agbSndDirectSoundTimer(0);
	else
		g_nAgbSndFifoValue[0] = 0;


	if((g_pAgbSoundCntH->rLOutputB | g_pAgbSoundCntH->rROutputB) && (g_pAgbSoundCntH->rTimerB == nTimer))
		agbSndDirectSoundTimer(1);
	else
		g_nAgbSndFifoValue[1] = 0;
}

/** @brief Update Ticks */
void agbSndUpdateTicks(u32 nTicks)
{
	g_nAgbSndTicks -= nTicks;
	if(g_nAgbSndTicks > 0)
		return;
	g_nAgbSndTicks += AGB_SND_TICKS;

	s32 nSize = g_pAgbEmuBuf->funcSoundPlaySize();
	if(g_pAgbSoundCntX->rSoundAll && (!g_pAgbHaltCnt->rPowerDown))
	{
		for(s32 n=0; n<nSize; ++n)
		{
			g_nAgbSndBufOutput1 = 0;
			g_nAgbSndBufOutput2 = 0;

			if(g_pAgbSoundCntX->rSound1)
				agbSndChannel1();
			if(g_pAgbSoundCntX->rSound2)
				agbSndChannel2();
			if(g_pAgbSoundCntX->rSound3)
				agbSndChannel3();
			if(g_pAgbSoundCntX->rSound4)
				agbSndChannel4();

			g_nAgbSndBufOutput1 *= g_pAgbSoundCntL->rLVolume * 52;
			g_nAgbSndBufOutput2 *= g_pAgbSoundCntL->rRVolume * 52;
			switch(g_pAgbSoundCntH->rSynthesis)
			{
			case 0:
				g_nAgbSndBufOutput1 >>= 2;
				g_nAgbSndBufOutput2 >>= 2;
				break;
			case 1:
				g_nAgbSndBufOutput1 >>= 1;
				g_nAgbSndBufOutput2 >>= 1;
				break;
			}

			if(g_pAgbSoundCntH->rLOutputA)
				g_nAgbSndBufOutput1 += (g_nAgbSndFifoValue[0] >> (1 - g_pAgbSoundCntH->rRatioA))*170;
			if(g_pAgbSoundCntH->rLOutputB)
				g_nAgbSndBufOutput1 += (g_nAgbSndFifoValue[1] >> (1 - g_pAgbSoundCntH->rRatioB))*170;
			if(g_pAgbSoundCntH->rROutputA)
				g_nAgbSndBufOutput2 += (g_nAgbSndFifoValue[0] >> (1 - g_pAgbSoundCntH->rRatioA))*170;
			if(g_pAgbSoundCntH->rROutputB)
				g_nAgbSndBufOutput2 += (g_nAgbSndFifoValue[1] >> (1 - g_pAgbSoundCntH->rRatioB))*170;

			if(g_nAgbSndBufOutput1 >= 32768)
				g_nAgbSndBufOutput1 = 32767;
			else if(g_nAgbSndBufOutput1 < -32768)
				g_nAgbSndBufOutput1 = -32768;
			g_pAgbSndBuf[g_nAgbSndBufPos++] = (s16)g_nAgbSndBufOutput1;
			if(g_nAgbSndBufOutput2 >= 32768)
				g_nAgbSndBufOutput2 = 32767;
			else if(g_nAgbSndBufOutput2 < -32768)
				g_nAgbSndBufOutput2 = -32768;
			g_pAgbSndBuf[g_nAgbSndBufPos++] = (s16)g_nAgbSndBufOutput2;

			if(g_nAgbSndBufPos >= g_nAgbSndBufSize)
				g_nAgbSndBufPos = 0;
		}
	}
	else
	{
		for(s32 n=0; n<nSize; ++n)
		{
			g_pAgbSndBuf[g_nAgbSndBufPos++] = 0;
			g_pAgbSndBuf[g_nAgbSndBufPos++] = 0;
			if(g_nAgbSndBufPos >= g_nAgbSndBufSize)
				g_nAgbSndBufPos = 0;
		}
	}
}
