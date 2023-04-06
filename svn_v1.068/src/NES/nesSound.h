/**
 * @file nesSound.h
 * @author Chentian
 * @date 2010.06.25
 * @brief NES Emulate For CTR - Sound
 */
#pragma once
#include "nesGlobal.h"
#include "Audio/sound.h"

/** @name Macro Define */
//@{
#define	NES_SND_SAVEDATA_MAX	20										///< Sound Save Data Max Count
#define	NES_SND_COUNT			8										///< Sound Count
#define	NES_SND_TICKS			300										///< Sound Interval Ticks	//NES_SND_COUNT*(1789772/32728)
//@}

/** @name Global Variable */
//@{
extern u32						g_nNesSndSaveData;							///< Sound Save Data Count
extern trlSEmuShellResume		g_sNesSndSaveData[NES_SND_SAVEDATA_MAX];	///< Sound Save Data
extern u8						(*nesSndRegReadCard)(u16 nAddr);			///< Read Data From Card Register
extern void						(*nesSndRegWriteCard)(u16 nAddr, u8 nValue);///< Write Data to Card Register

extern f32 g_fNesSndScaleA;
extern f32 g_fNesSndScaleB;
extern f32 g_fNesSndScaleC;
extern f32 g_fNesSndScaleD;
extern f32 g_fNesSndScaleE;
extern f32 g_fNesSndScaleF;
extern f32 g_fNesSndScale5A;
extern f32 g_fNesSndScale5B;
extern f32 g_fNesSndScaleZ;

#if TRL_HVC_SOUND_TEST
extern u32 g_bNesSndA;
extern u32 g_bNesSndB;
extern u32 g_bNesSndC;
extern u32 g_bNesSndD;
extern u32 g_bNesSndE;
extern u32 g_bNesSndF;
extern u32 g_bNesSnd5A;
extern u32 g_bNesSnd5B;
extern u32 g_bNesSndZ;
#endif
//@}

/** @brief Initialize Sound */
void nesSndInit();
/** @brief Reset Sound */
void nesSndReset();
/** @brief Resume Sound */
void nesSndResume();
/** @brief Update Ticks */
void nesSndUpdate();
/** @brief Write Data to APU Register */
void nesSndRegWrite(u16 nAddr, u8 nValue);

#if TRL_SOUND_REG_LOG
#define TRL_SOUND_REG_LOG_MAX 512
extern u16 g_pNesSndRegWriteLog_Addr[];
extern u8  g_pNesSndRegWriteLog_Value[];
extern u32 g_pNesSndRegWriteLog_Ticks[];
extern u8  g_pNesSndRegWriteLog_Type[];
extern u32 g_pNesSndRegWriteLog_Ct;
extern u32 g_pNesSndRegWriteLog_Run;
extern u32 g_nNesSndRegWriteLog_Ticks;

extern u32 nRegWriteLog_ticks;
extern u32 nRegWriteLog_tickspersample;
extern u32 nRegWriteLog_ct;

void nesSndRegWriteLog_LogRunOneSample();

inline void nesSndRegWriteLog_LogRun()
{	
	g_pNesSndRegWriteLog_Run = 1;

	nRegWriteLog_ticks = 0;
	nRegWriteLog_ct = 0;
	if(g_pNesEmuBuf->nAudioSampleCurFrame != 0)
	{		
		nRegWriteLog_tickspersample = g_nNesSndRegWriteLog_Ticks/g_pNesEmuBuf->nAudioSampleCurFrame + 1;	
		//NN_LOG("nesSndRegWriteLog_LogRun g_pNesSndRegWriteLog_Ct = %d\n", g_pNesSndRegWriteLog_Ct);
	}
	else
	{
		//g_sEmuShellBuffer.nAudioSampleCurFrame == 0
		//so just write reg and no sound sample is output
		for(u32 i=0;i<g_pNesSndRegWriteLog_Ct;i++)
		{
			if(g_pNesSndRegWriteLog_Type[i]  == 0)
				nesSndRegWrite(g_pNesSndRegWriteLog_Addr[i], g_pNesSndRegWriteLog_Value[i]);
			else
				nesSndRegWriteCard(g_pNesSndRegWriteLog_Addr[i], g_pNesSndRegWriteLog_Value[i]);
		}
	}
}

//call this at frame begin
inline void nesSndRegWriteLog_LogBegin()
{
	g_pNesSndRegWriteLog_Ct = 0;
	g_pNesSndRegWriteLog_Run = 0;
	g_nNesSndRegWriteLog_Ticks = 0;
}

//ticks add 
inline void nesSndRegWriteLog_LogTicksAdd(u32 n)
{
	g_nNesSndRegWriteLog_Ticks += n;
}
#else
#define nesSndRegWriteLog_LogBegin() ((void)0)
#define nesSndRegWriteLog_LogRun() ((void)0)
#define nesSndRegWriteLog_LogRunOneSample() ((void)0)
#define nesSndRegWriteLog_LogTicksAdd(n)   ((void)0)
#endif
