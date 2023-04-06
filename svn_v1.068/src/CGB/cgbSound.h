/**
 * @file cgbSound.h
 * @author Chentian
 * @date 2009.12.23
 * @brief CGB Emulate For CTR - Sound
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#if (TRL_SOUND_WAVE_TEST==1)
#define CGB_SND_STEP_SHIFT 3
#define CGB_SND_STEP (1<<CGB_SND_STEP_SHIFT)
#else
#define CGB_SND_STEP 1
#endif


#define		CGB_SND_SOUND1					0			///< Sound 1
#define		CGB_SND_SOUND2					1			///< Sound 2
#define		CGB_SND_SOUND3					2			///< Sound 3
#define		CGB_SND_SOUND4					3			///< Sound 4
#define		CGB_SND_SAMPLERATE				44100		///(16756991*16/(32*256))//44100
#define		CGB_SND_LENGTH1					(CGB_SND_SAMPLERATE/256)			///< The Length of The Output Sound (44100/256)
//CGB_SND_LENGTH2 is used for sound channel 1 sweep time
//CGB_SND_LENGTH2 = 4194304*737/128/17556/4 = 343.xxx
//in some time, the sweep time is at a xxxx time, 
//to make sure the sweep happen, to use 343
//to make sure the sweep not happen to use 344
#define		CGB_SND_LENGTH2					343//(4194304/128/4*737/17556)			///< The Length of The Output Sound

#define		CGB_SND_LENGTH3					(CGB_SND_SAMPLERATE/64)			///< The Length of The Output Sound (44100/64)
#define		CGB_SND_FREQ					0x30000000						///((u32)(0x2009E32D*2)) //0x2F8DF18E	///< The Fixed Value Of The Output Frequency's Formula (131072*8*0x2000000/44100)
#define		CGB_SND_NOISE					5					///4//CGB_SND_SAMPLERATE/(0x200000/256) //5			///< The Noise Value CGB_SND_SAMPLERATE/(0x200000/256)

#define		CGB_SND_VOLUMESCALE				60		///< Sound Volume Scale Value
#define		CGB_SND_SAVEDATA				23					///< Sound Save Data Count

#define		CGB_SND_FREQLIMIT				0x20000000
//@}

/** @name Global Variable */
//@{
extern s8					g_nCgbSndWavePattern[4][8];				///< Sound Wave Pattern Data
#if (TRL_SOUND_WAVE_TEST==1)
extern s8					g_nCgbSndWavePattern2[4][8*CGB_SND_STEP];
#endif
extern const s32			g_nCgbSndFreqRatio[8];					///< Sound Frequency Ratio (4.194304 MHz / 8 / (0.5~7))
extern const s32			g_nCgbSndShiftClock[16];				///< Sound Shift Clock Frequency's Formula
extern s32					g_nCgbSndVolume1;						///< Sound SO1 Volume
extern s32					g_nCgbSndVolume2;						///< Sound SO2 Volume

extern s32					g_nCgbSnd1Index;						///< Sound 1 Data Index
extern s32					g_nCgbSnd1Length;						///< Sound 1 Length
extern u32					g_nCgbSnd1Frequency;					///< Sound 1 Output Frequency
extern s32					g_nCgbSnd1EnvelopeValue;				///< Sound 1 Envelope Value
extern s32					g_nCgbSnd1EnvelopeLength;				///< Sound 1 Envelope Length
extern s32					g_nCgbSnd1EnvelopeLengthInit;			///< Sound 1 Envelope Length Init Value
extern s8*					g_pCgbSnd1Wave;							///< Sound 1 Wave
extern s32					g_nCgbSnd1SweepLimit;					///< Sound 1 Sweep Limit
extern s32					g_nCgbSnd1SweepLength;					///< Sound 1 Sweep Length
extern s32					g_nCgbSnd1SweepLengthInit;				///< Sound 1 Sweep Length Init Value
extern u32					g_nCgbSnd1SweepFreq;					///< Sound 1 Sweep Freq

extern s32					g_nCgbSnd2Index;						///< Sound 2 Data Index
extern s32					g_nCgbSnd2Length;						///< Sound 2 Length
extern u32					g_nCgbSnd2Frequency;					///< Sound 2 Output Frequency
extern s32					g_nCgbSnd2EnvelopeValue;				///< Sound 2 Envelope Value
extern s32					g_nCgbSnd2EnvelopeLength;				///< Sound 2 Envelope Length
extern s32					g_nCgbSnd2EnvelopeLengthInit;			///< Sound 2 Envelope Length Init Value
extern s8*					g_pCgbSnd2Wave;							///< Sound 2 Wave

extern s32					g_nCgbSnd3Index;						///< Sound 3 Data Index
extern s32					g_nCgbSnd3Length;						///< Sound 3 Length
extern u32					g_nCgbSnd3Frequency;					///< Sound 3 Output Frequency

extern s32					g_nCgbSnd4Index;						///< Sound 4 Data Index
extern s32					g_nCgbSnd4Length;						///< Sound 4 Length
extern u32					g_nCgbSnd4Frequency;					///< Sound 4 Output Frequency
extern s32					g_nCgbSnd4EnvelopeValue;				///< Sound 4 Envelope Value
extern s32					g_nCgbSnd4EnvelopeLength;				///< Sound 4 Envelope Length
extern s32					g_nCgbSnd4EnvelopeLengthInit;			///< Sound 4 Envelope Length Init Value
extern s32					g_nCgbSnd4Shift;						///< Sound 4 Shift
extern s32					g_nCgbSnd4TableIndex;

extern trlSEmuShellResume	g_sCgbSndSaveData[CGB_SND_SAVEDATA];	///< Sound Save Data
extern s32			g_nCgbSnd1Reset;
extern s32			g_nCgbSnd2Reset;
//@}

/** @brief Initialize Sound */
void cgbSndInit();
/** @brief Reset Sound */
void cgbSndReset();
/** @brief Resume Sound */
void cgbSndResume();
/** @brief Update Ticks */
void cgbSndUpdateTicks();
/** @brief Update Ticks */
void cgbSndUpdateTicksOneFrame();


#if TRL_SOUND_CGB_FAST
#define TRL_SOUND_REG_LOG_MAX 256
extern u16 g_pCGBSndRegWriteLog_Addr[];
extern u16 g_pCGBSndRegWriteLog_Value[];
extern u32 g_pCGBSndRegWriteLog_Ticks[];
extern u8  g_pCGBSndRegWriteLog_Type[];
extern u32 g_pCGBSndRegWriteLog_Ct;
extern u32 g_pCGBSndRegWriteLog_Run;
extern u32 g_nCGBSndRegWriteLog_Ticks;

void cgbSndRegWriteLog_LogBegin();
void cgbSndRegWriteLog_LogRun();
void cgbSndRegWriteLog_LogRunOneSample();
void cgbSndRegWriteLog_LogTicksAdd(u32 n);
#else
#define cgbSndRegWriteLog_LogBegin() ((void)0)
#define cgbSndRegWriteLog_LogRun() ((void)0)
#define cgbSndRegWriteLog_LogRunOneSample() ((void)0)
#define cgbSndRegWriteLog_LogTicksAdd(n)   ((void)0)
#endif

