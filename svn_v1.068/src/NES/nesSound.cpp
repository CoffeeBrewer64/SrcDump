/**
 * @file nesSound.cpp
 * @author Chentian
 * @date 2010.06.25
 * @brief NES Emulate For CTR - Sound
 */
#include "nesSound.h"
#include "nesInput.h"
#include "nesCard.h"
#include "nesGraphic.h"


u16 __ntohs(u16 data)  
{  
	u8 high=(u8)(data>>8);  
	u8 lower=(u8)data;
	u16 ret=(lower<<8)+high;
	return ret;
} 

#include "Audio/soundA.h"
#include "Audio/soundB.h"
#include "Audio/soundC.h"
#include "Audio/soundD.h"
#include "Audio/soundE.h"
#include "Audio/soundF.h"
#include "Audio/soundP.h"
#include "Audio/soundQ.h"
#include "Audio/soundMMC5.h"
#include "Audio/soundVRC.h"
#include "Audio/moepro.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
s32						g_nNesSndTicks;									///< APU Ticks
s16*					g_pNesSndBuf = 0;								///< Sound Data Buffer Header
s32						g_nNesSndBufSize = 0;							///< Sound Data Buffer Size
s32						g_nNesSndBufPos = 0;							///< Sound Data Buffer Size
u32						g_nNesSndSaveData;								///< Sound Save Data Count
trlSEmuShellResume		g_sNesSndSaveData[NES_SND_SAVEDATA_MAX];		///< Sound Save Data
void					(*nesSndRegWriteCard)(u16 nAddr, u8 nValue) = NULL;
void					(*nesSndGetSample)() = NULL;

f32 g_fNesSndScaleA = 0.9f;
f32 g_fNesSndScaleB = 0.9f;
f32 g_fNesSndScaleC	= 0.9f;
f32 g_fNesSndScaleD = 1.70f;
f32 g_fNesSndScaleE = 0.7f;
f32 g_fNesSndScaleF = 1.2f;

f32 g_fNesSndScaleP = 1.2f;

f32 g_fNesSndScaleQ1 = 1.0f;
f32 g_fNesSndScaleQ2 = 1.0f;
f32 g_fNesSndScaleQ3 = 1.0f;

f32 g_fNesSndScale5A = 0.9f;
f32 g_fNesSndScale5B = 0.9f;
f32 g_fNesSndScaleZ = 1.0f;
//@}



#if TRL_HVC_SOUND_TEST
u32 g_bNesSndA = 1;
u32 g_bNesSndB = 1;
u32 g_bNesSndC = 1;
u32 g_bNesSndD = 1;
u32 g_bNesSndE = 1;
u32 g_bNesSndF = 1;
u32 g_bNesSnd5A = 1;
u32 g_bNesSnd5B = 1;
u32 g_bNesSndZ = 1;

u32 g_bNesSndQ1 = 1;
u32 g_bNesSndQ2 = 1;
u32 g_bNesSndQ3 = 1;
#endif

#if TRL_SOUND_REG_LOG
u16 g_pNesSndRegWriteLog_Addr[TRL_SOUND_REG_LOG_MAX];
u8  g_pNesSndRegWriteLog_Value[TRL_SOUND_REG_LOG_MAX];
u32 g_pNesSndRegWriteLog_Ticks[TRL_SOUND_REG_LOG_MAX];
u8  g_pNesSndRegWriteLog_Type[TRL_SOUND_REG_LOG_MAX];
u32 g_pNesSndRegWriteLog_Ct = 0;
u32 g_pNesSndRegWriteLog_Run = 0;
u32 g_nNesSndRegWriteLog_Ticks;

u32 nRegWriteLog_ticks = 0;
u32 nRegWriteLog_tickspersample = 0;
u32 nRegWriteLog_ct = 0;

inline void nesSndRegWriteLog_LogRunOneSample()
{
	if(nRegWriteLog_ct >= g_pNesSndRegWriteLog_Ct)
		return;
	nRegWriteLog_ticks += nRegWriteLog_tickspersample;
	while(nRegWriteLog_ticks >= g_pNesSndRegWriteLog_Ticks[nRegWriteLog_ct])
	{
		if(g_pNesSndRegWriteLog_Type[nRegWriteLog_ct]  == 0)
			nesSndRegWrite(g_pNesSndRegWriteLog_Addr[nRegWriteLog_ct], g_pNesSndRegWriteLog_Value[nRegWriteLog_ct]);
		else
			nesSndRegWriteCard(g_pNesSndRegWriteLog_Addr[nRegWriteLog_ct], g_pNesSndRegWriteLog_Value[nRegWriteLog_ct]);
		nRegWriteLog_ct++;
		if(nRegWriteLog_ct >= g_pNesSndRegWriteLog_Ct)
			return;
	}
}
#endif

/** @brief Get Sample for Normal */
void nesSndGetSampleNormal()
{
	for(int temp = g_pNesEmuBuf->nAudioSampleCurFrame;temp> 0;--temp)
	{
		nesSndRegWriteLog_LogRunOneSample();
#if 0
		s16 sampleA = 0;
		s16 sampleB = 0;
		s16 sampleC = 0;
		s16 sampleD = 0;
		s16 sampleE = 0;
		//sampleA = __ProcessSoundA();
		//sampleB = __ProcessSoundB();
		//sampleC = __ProcessSoundC();
		//sampleD = __ProcessSoundD();
		//sampleE = __ProcessSoundE();
#else
		s16 sampleA = __ProcessSoundA();
		s16 sampleB = __ProcessSoundB();
		s16 sampleC = __ProcessSoundC();
		s16 sampleD = __ProcessSoundD();
		s16 sampleE = __ProcessSoundE();
#endif

		s16 sample;
		#if ( USE_SOUNDSAMPLESCALING == 1)
			sample = (s16)(   g_fNesSndScaleA * sampleA
							+ g_fNesSndScaleB * sampleB
							- g_fNesSndScaleC * sampleC
							- g_fNesSndScaleD * sampleD
							+ g_fNesSndScaleE * sampleE);
			/*sample = (s16)(   SOUNDSAMPLESCALING_SOUNDA * sampleA
							+ SOUNDSAMPLESCALING_SOUNDB * sampleB
							- SOUNDSAMPLESCALING_SOUNDC * sampleC
							- SOUNDSAMPLESCALING_SOUNDD * sampleD
							+ SOUNDSAMPLESCALING_SOUNDE * sampleE);*/
		#else
			sample = sampleA + sampleB - sampleC - sampleD + sampleE;
		#endif
		g_pNesSndBuf[g_nNesSndBufPos] = sample;
		g_pNesSndBuf[g_nNesSndBufPos+1] = sample;
		g_nNesSndBufPos+= 2;

		if(g_nNesSndBufPos >= g_nNesSndBufSize)
		{
		#ifdef TRL_PLATFORM_PC
			g_pNesEmuBuf->funcAudioRecord((u8*)g_pNesSndBuf, g_nNesSndBufSize*2);
		#endif
			g_nNesSndBufPos = 0;
		}
	}
	g_pNesEmuBuf->nAudioSampleCurFrame = 0;
}

/** @brief Get Sample for MMC5 */
void nesSndGetSampleMMC5()
{
	for(int temp = g_pNesEmuBuf->nAudioSampleCurFrame;temp> 0;--temp)
	{
		nesSndRegWriteLog_LogRunOneSample();
#if 0
		s16 sampleA = 0;
		s16 sampleB = 0;
		s16 sampleC = 0;
		s16 sampleD = 0;
		s16 sampleE = 0;
		s16 sampleX = 0;
		s16 sampleY = 0;
		s16 sampleZ = 0;
		//sampleA = __ProcessSoundA();
		//sampleB = __ProcessSoundB();
		//sampleC = __ProcessSoundC();
		//sampleD = __ProcessSoundD();
		//sampleE = __ProcessSoundE();
		//sampleX = __ProcessSoundMMC5(&SoundX, true);
		//sampleY = __ProcessSoundMMC5(&SoundY, false);
		//sampleZ = SoundZ.lastlevel;
#else
		s16 sampleA = __ProcessSoundA();
		s16 sampleB = __ProcessSoundB();
		s16 sampleC = __ProcessSoundC();
		s16 sampleD = __ProcessSoundD();
		s16 sampleE = __ProcessSoundE();
		s16 sampleX = __ProcessSoundMMC5(&SoundX, true);
		s16 sampleY = __ProcessSoundMMC5(&SoundY, false);
		s16 sampleZ = SoundZ.lastlevel;
#endif
#if TRL_HVC_SOUND_TEST
		sampleZ *= g_bNesSndZ;
#endif		
		s16 sample;
		#if ( USE_SOUNDSAMPLESCALING == 1)
			/*sample = (s16)(   SOUNDSAMPLESCALING_SOUNDA * sampleA
							+ SOUNDSAMPLESCALING_SOUNDB * sampleB
							- SOUNDSAMPLESCALING_SOUNDC * sampleC
							- SOUNDSAMPLESCALING_SOUNDD * sampleD
							+ SOUNDSAMPLESCALING_SOUNDE * sampleE
							+ SOUNDSAMPLESCALING_SOUND5A * sampleX
							+ SOUNDSAMPLESCALING_SOUND5B * sampleY
							- SOUNDSAMPLESCALING_SOUNDZ * sampleZ);*/
			sample = (s16)(   g_fNesSndScaleA * sampleA
							+ g_fNesSndScaleB * sampleB
							- g_fNesSndScaleC * sampleC
							- g_fNesSndScaleD * sampleD
							+ g_fNesSndScaleE * sampleE
							+ g_fNesSndScale5A * sampleX
							+ g_fNesSndScale5B * sampleY
							- g_fNesSndScaleZ * sampleZ);
		#else
			sample = sampleA + sampleB - sampleC - sampleD + sampleE + sampleX + sampleY - sampleZ;
		#endif

		g_pNesSndBuf[g_nNesSndBufPos] = sample;
		g_pNesSndBuf[g_nNesSndBufPos+1] = sample;
		g_nNesSndBufPos+= 2;

		if(g_nNesSndBufPos >= g_nNesSndBufSize)
		{
#ifdef TRL_PLATFORM_PC
			g_pNesEmuBuf->funcAudioRecord((u8*)g_pNesSndBuf, g_nNesSndBufSize*2);
#endif
			g_nNesSndBufPos = 0;
		}
	}
	g_pNesEmuBuf->nAudioSampleCurFrame = 0;
}

/** @brief Get Sample for VRC */
void nesSndGetSampleVRC()
{
	for(int temp = g_pNesEmuBuf->nAudioSampleCurFrame;temp> 0;--temp)
	{
		nesSndRegWriteLog_LogRunOneSample();

#if 0		
		s16 sampleA = 0;
		s16 sampleB = 0;
		s16 sampleC = 0;
		s16 sampleD = 0;
		s16 sampleE = 0;
		s16 sampleX = 0;
		s16 sampleY = 0;
		u16 sampleZ = 0;
		//sampleA = __ProcessSoundA();
		//sampleB = __ProcessSoundB();
		//sampleC = __ProcessSoundC();
		//sampleD = __ProcessSoundD();
		//sampleE = __ProcessSoundE();
		//sampleX = __ProcessSoundVRC(0);
		//sampleY = __ProcessSoundVRC(1);
		//sampleZ = __ProcessSoundVRC(2);
#else
		s16 sampleA = __ProcessSoundA();
		s16 sampleB = __ProcessSoundB();
		s16 sampleC = __ProcessSoundC();
		s16 sampleD = __ProcessSoundD();
		s16 sampleE = __ProcessSoundE();
		s16 sampleX = __ProcessSoundVRC(0);
		s16 sampleY = __ProcessSoundVRC(1);
		u16 sampleZ = __ProcessSoundVRC(2);
#endif

		s16 sample;
		#if ( USE_SOUNDSAMPLESCALING == 1)
			/*sample = (s16)(   SOUNDSAMPLESCALING_SOUNDA * sampleA
							+ SOUNDSAMPLESCALING_SOUNDB * sampleB
							- SOUNDSAMPLESCALING_SOUNDC * sampleC
							- SOUNDSAMPLESCALING_SOUNDD * sampleD
							+ SOUNDSAMPLESCALING_SOUNDE * sampleE
							+ SOUNDSAMPLESCALING_SOUND5A * sampleX
							+ SOUNDSAMPLESCALING_SOUND5B * sampleY
							- SOUNDSAMPLESCALING_SOUNDZ * sampleZ);*/
			sample = (s16)(   g_fNesSndScaleA * sampleA
							+ g_fNesSndScaleB * sampleB
							- g_fNesSndScaleC * sampleC
							- g_fNesSndScaleD * sampleD
							+ g_fNesSndScaleE * sampleE
							+ g_fNesSndScale5A * sampleX
							+ g_fNesSndScale5B * sampleY
							- g_fNesSndScaleZ * sampleZ);
		#else
			sample = sampleA + sampleB - sampleC - sampleD + sampleE + sampleX + sampleY - sampleZ;
		#endif

		g_pNesSndBuf[g_nNesSndBufPos] = sample;
		g_pNesSndBuf[g_nNesSndBufPos+1] = sample;
		g_nNesSndBufPos+= 2;

		if(g_nNesSndBufPos >= g_nNesSndBufSize)
		{
#ifdef TRL_PLATFORM_PC
			g_pNesEmuBuf->funcAudioRecord((u8*)g_pNesSndBuf, g_nNesSndBufSize*2);
#endif
			g_nNesSndBufPos = 0;
		}
	}
	g_pNesEmuBuf->nAudioSampleCurFrame = 0;
}

/** @brief Get Sample for DiskSystem */
void nesSndGetSampleDisk()
{
	
	for(int temp = g_pNesEmuBuf->nAudioSampleCurFrame;temp> 0;--temp)
	{
		nesSndRegWriteLog_LogRunOneSample();

		s16 sampleA = 0;
		s16 sampleB = 0;
		s16 sampleC = 0;
		s16 sampleD = 0;
		s16 sampleE = 0;
		s16 sampleF = 0;

		sampleA = __ProcessSoundA();
		sampleB = __ProcessSoundB();
		sampleC = __ProcessSoundC();
		sampleD = __ProcessSoundD();
		sampleE = __ProcessSoundE();
		sampleF = __ProcessSoundF();

		s16 sample;
		#if ( USE_SOUNDSAMPLESCALING == 1)
			/*sample = (s16)(   SOUNDSAMPLESCALING_SOUNDA * sampleA
							+ SOUNDSAMPLESCALING_SOUNDB * sampleB
							- SOUNDSAMPLESCALING_SOUNDC * sampleC
							- SOUNDSAMPLESCALING_SOUNDD * sampleD
							+ SOUNDSAMPLESCALING_SOUNDE * sampleE
							- SOUNDSAMPLESCALING_SOUNDF * sampleF);*/
			sample = (s16)(   g_fNesSndScaleA * sampleA
							+ g_fNesSndScaleB * sampleB
							- g_fNesSndScaleC * sampleC
							- g_fNesSndScaleD * sampleD
							+ g_fNesSndScaleE * sampleE
							- g_fNesSndScaleF * sampleF);
		#else
			sample = sampleA + sampleB - sampleC - sampleD + sampleE - sampleF;
		#endif

		g_pNesSndBuf[g_nNesSndBufPos] = sample;
		g_pNesSndBuf[g_nNesSndBufPos+1] = sample;
		g_nNesSndBufPos+= 2;

		if(g_nNesSndBufPos >= g_nNesSndBufSize)
		{
#ifdef TRL_PLATFORM_PC
			g_pNesEmuBuf->funcAudioRecord((u8*)g_pNesSndBuf, g_nNesSndBufSize*2);
#endif
			g_nNesSndBufPos = 0;
		}
	}
	g_pNesEmuBuf->nAudioSampleCurFrame = 0;
}

void nesSndGetSampleJALECO()
{
	for(int temp = g_pNesEmuBuf->nAudioSampleCurFrame;temp> 0;--temp)
	{
		nesSndRegWriteLog_LogRunOneSample();
#if 0
		s16 sampleA = 0;
		s16 sampleB = 0;
		s16 sampleC = 0;
		s16 sampleD = 0;
		s16 sampleE = 0;
		//sampleA = __ProcessSoundA();
		//sampleB = __ProcessSoundB();
		//sampleC = __ProcessSoundC();
		//sampleD = __ProcessSoundD();
		//sampleE = __ProcessSoundE();
#else
		s16 sampleA = __ProcessSoundA();
		s16 sampleB = __ProcessSoundB();
		s16 sampleC = __ProcessSoundC();
		s16 sampleD = __ProcessSoundD();
		s16 sampleE = __ProcessSoundE();
#endif
		s16 sampleP = __ProcessSoundP();

		s16 sample;
		#if ( USE_SOUNDSAMPLESCALING == 1)
			sample = (s16)(   g_fNesSndScaleA * sampleA
							+ g_fNesSndScaleB * sampleB
							- g_fNesSndScaleC * sampleC
							- g_fNesSndScaleD * sampleD
							+ g_fNesSndScaleE * sampleE
							+ g_fNesSndScaleP * sampleP);
			/*sample = (s16)(   SOUNDSAMPLESCALING_SOUNDA * sampleA
							+ SOUNDSAMPLESCALING_SOUNDB * sampleB
							- SOUNDSAMPLESCALING_SOUNDC * sampleC
							- SOUNDSAMPLESCALING_SOUNDD * sampleD
							+ SOUNDSAMPLESCALING_SOUNDE * sampleE);*/
		#else
			sample = sampleA + sampleB - sampleC - sampleD + sampleE;
		#endif
		g_pNesSndBuf[g_nNesSndBufPos] = sample;
		g_pNesSndBuf[g_nNesSndBufPos+1] = sample;
		g_nNesSndBufPos+= 2;

		if(g_nNesSndBufPos >= g_nNesSndBufSize)
		{
		#ifdef TRL_PLATFORM_PC
			g_pNesEmuBuf->funcAudioRecord((u8*)g_pNesSndBuf, g_nNesSndBufSize*2);
		#endif
			g_nNesSndBufPos = 0;
		}
	}
	g_pNesEmuBuf->nAudioSampleCurFrame = 0;
}

void nesSndGetSampleFME7()
{
	for(int temp = g_pNesEmuBuf->nAudioSampleCurFrame;temp> 0;--temp)
	{
		nesSndRegWriteLog_LogRunOneSample();
#if 0
		s16 sampleA = 0;
		s16 sampleB = 0;
		s16 sampleC = 0;
		s16 sampleD = 0;
		s16 sampleE = 0;
		//sampleA = __ProcessSoundA();
		//sampleB = __ProcessSoundB();
		//sampleC = __ProcessSoundC();
		//sampleD = __ProcessSoundD();
		//sampleE = __ProcessSoundE();
#else
		s16 sampleA = __ProcessSoundA();
		s16 sampleB = __ProcessSoundB();
		s16 sampleC = __ProcessSoundC();
		s16 sampleD = __ProcessSoundD();
		s16 sampleE = __ProcessSoundE();
#endif
		__ProcessSoundQ_Env();	// Envelope & Noise
		s32	sampleQ0,sampleQ1,sampleQ2;

#if TRL_HVC_SOUND_TEST
		if(!g_bNesSndQ1)
			sampleQ0 = 0;
		else
#endif
			sampleQ0 = __ProcessSoundQ( 0 );

#if TRL_HVC_SOUND_TEST
		if(!g_bNesSndQ2)
			sampleQ1 = 0;
		else
#endif
			sampleQ1 = __ProcessSoundQ( 1 );

#if TRL_HVC_SOUND_TEST
		if(!g_bNesSndQ3)
			sampleQ2 = 0;
		else
#endif
			sampleQ2 = __ProcessSoundQ( 2 );

		s16 sample;
		#if ( USE_SOUNDSAMPLESCALING == 1)
			sample = (s16)(   g_fNesSndScaleA * sampleA
							+ g_fNesSndScaleB * sampleB
							- g_fNesSndScaleC * sampleC
							- g_fNesSndScaleD * sampleD
							+ g_fNesSndScaleE * sampleE
							+ g_fNesSndScaleQ1 * sampleQ0
							+ g_fNesSndScaleQ2 * sampleQ1
							+ g_fNesSndScaleQ3 * sampleQ2
							);
			/*sample = (s16)(   SOUNDSAMPLESCALING_SOUNDA * sampleA
							+ SOUNDSAMPLESCALING_SOUNDB * sampleB
							- SOUNDSAMPLESCALING_SOUNDC * sampleC
							- SOUNDSAMPLESCALING_SOUNDD * sampleD
							+ SOUNDSAMPLESCALING_SOUNDE * sampleE);*/
		#else
			sample = sampleA + sampleB - sampleC - sampleD + sampleE;
		#endif
		g_pNesSndBuf[g_nNesSndBufPos] = sample;
		g_pNesSndBuf[g_nNesSndBufPos+1] = sample;
		g_nNesSndBufPos+= 2;

		if(g_nNesSndBufPos >= g_nNesSndBufSize)
		{
		#ifdef TRL_PLATFORM_PC
			g_pNesEmuBuf->funcAudioRecord((u8*)g_pNesSndBuf, g_nNesSndBufSize*2);
		#endif
			g_nNesSndBufPos = 0;
		}
	}
	g_pNesEmuBuf->nAudioSampleCurFrame = 0;
}

/** @brief Initialize Sound */
void nesSndInit()
{
	g_pNesSndBuf = (s16*)g_pNesEmuBuf->pSoundBuf;
	g_nNesSndBufSize = g_pNesEmuBuf->nSoundBufSize >> 1;
	g_nNesSndBufPos = (g_pNesEmuBuf->nAudioSampleOffset<<1);


	g_fNesSndScaleA  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_A",  9 )*0.1f;
	g_fNesSndScaleB  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_B",  9 )*0.1f;
	g_fNesSndScaleC  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_C",  9 )*0.1f;
	g_fNesSndScaleD  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_D",  17)*0.1f;
	g_fNesSndScaleE  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_E",  7 )*0.1f;
	g_fNesSndScaleF  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_F",  12)*0.1f;

	g_fNesSndScaleP  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_P",  12)*0.1f;

	g_fNesSndScaleQ1  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_Q1",  10)*0.1f;
	g_fNesSndScaleQ2  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_Q2",  10)*0.1f;
	g_fNesSndScaleQ3  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_Q3",  10)*0.1f;

	g_fNesSndScale5A = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_5A", 9 )*0.1f;
	g_fNesSndScale5B = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_5B", 9 )*0.1f;
	g_fNesSndScaleZ  = g_pNesEmuBuf->funcConfigData("NES", "SND_SCALE_Z",  10)*0.1f;

	// Save Data
	g_nNesSndSaveData = 0;
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&g_nNesSndTicks, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundA, sizeof(Sound_HVCpulse_), 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundB, sizeof(Sound_HVCpulse_), 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundC, sizeof(Sound_HVCpulse_), 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundD, sizeof(Sound_HVCpulse_), 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundE, sizeof(Sound_HVCdeltamod_), 1, 0);
	//g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundP, sizeof(Sound_Pcm_), 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&sbuffer, sizeof(Sound_buffer_), 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&NOISE_SHIFT_COUNTER, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&delta_counter, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&delta_sign, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&bias_move, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&bias, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&voltage, 4, 1, 0);
	g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&voltage_out, 4, 1, 0);

	switch(g_pNesROMHeader->nMapper)
	{
	case 5:		// MMC5 - BANKING, IRQ, SOUND, VIDEO, MULTIPLY, etc.
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundX, sizeof(Sound_HVCpulse_), 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundY, sizeof(Sound_HVCpulse_), 1, 0);

		nesSndRegWriteCard = __Sound_Write_MMC5;
		nesSndGetSample = nesSndGetSampleMMC5;
		break;

	case 14:	//SUNSOFT5 only for Gimmick!
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundQ, sizeof(Sound_FME7_), 1, 0);
		nesSndRegWriteCard = __Sound_Write_FME7;
		nesSndGetSample = nesSndGetSampleFME7;
		__Sound_Init_FME7();
		break;

	case 25:	// Konami VRC6A - PRG/16K/8K, VROM/1K, NT, IRQ, SOUND
	case 26:	// Konami VRC6B - PRG/16K/8K, VROM/1K, NT, IRQ, SOUND
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundX, sizeof(Sound_HVCpulse_), 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundY, sizeof(Sound_HVCpulse_), 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundZ, sizeof(Sound_HVCpulse_), 1, 0);

		nesSndRegWriteCard = __Sound_Write_VRC;
		nesSndGetSample = nesSndGetSampleVRC;
		break;
				 
	case 31:	//Mapper 31 - JALECO-4
		PCMH=(Pcmh_ *)&MOEPRO;
		PCMH2.mytop=(u8 *)PCMH;
		PCMH2.addr_table=(u16 *)(PCMH2.mytop+__ntohs(PCMH->addr_offset));
		PCMH2.size_table=(u16 *)(PCMH2.mytop+__ntohs(PCMH->size_offset));
		PCMH2.info_table=(u16 *)(PCMH2.mytop+__ntohs(PCMH->info_offset));

		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundP, sizeof(Sound_Pcm_), 1, 0);
		nesSndRegWriteCard = __Sound_Write_JALECO;
		nesSndGetSample = nesSndGetSampleJALECO;
		break;

	case 100:	// Disk System - PRG RAM, BIOS, DISK, IRQ, SOUND
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&SoundF, sizeof(Sound_HVCdiskfm_), 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(DISKFM_TABLE, 64, 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(DISKSUB_TABLE, 32, 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(disksubwave, 128, 1, 0);
		g_sNesSndSaveData[g_nNesSndSaveData++].SetData(&__sound_write_disk_shiftr, 4, 1, 0);

		nesSndRegWriteCard = __Sound_Write_Disk;
		nesSndGetSample = nesSndGetSampleDisk;
		break;
	default:
		nesSndGetSample = nesSndGetSampleNormal;
	}

	initNoise();
	nesSndReset();
}

/** @brief Reset Sound */
void nesSndReset()
{
	memset(&SoundA, 0, sizeof(Sound_HVCpulse_));
	memset(&SoundB, 0, sizeof(Sound_HVCpulse_));
	memset(&SoundC, 0, sizeof(Sound_HVCpulse_));
	memset(&SoundD, 0, sizeof(Sound_HVCpulse_));

	memset(&SoundE, 0, sizeof(Sound_HVCdeltamod_));

	memset(&SoundX, 0, sizeof(Sound_HVCpulse_));
	memset(&SoundY, 0, sizeof(Sound_HVCpulse_));
	memset(&SoundZ, 0, sizeof(Sound_HVCpulse_));

	memset(&SoundF, 0, sizeof(Sound_HVCdiskfm_));
	memset(&SoundP, 0, sizeof(Sound_Pcm_));
	memset(&SoundQ, 0, sizeof(Sound_FME7_));

	memset(&sbuffer, 0, sizeof(Sound_buffer_));

	g_nNesSndBufPos = (g_pNesEmuBuf->nAudioSampleOffset<<1);
	__ClearSoundEVoltage();

	WriteBias(0);
}

/** @brief Resume Sound */
void nesSndResume()
{
	g_nNesSndBufPos = (g_pNesEmuBuf->nAudioSampleOffset<<1);
}

/** @brief Update Ticks */
void nesSndUpdate()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuSoundOn;
	if(g_nTrlEmuSoundOn == 0)
		return;
#endif

	if(g_pNesEmuBuf->nAudioSampleSkip != 0)
	{
		for(s32 n=0;n<g_pNesEmuBuf->nAudioSampleSkip;++n)
		{
			g_pNesSndBuf[g_nNesSndBufPos] = 0;
			g_pNesSndBuf[g_nNesSndBufPos + 1] = 0;
			g_nNesSndBufPos+= 2;
			if(g_nNesSndBufPos >= g_nNesSndBufSize)
				g_nNesSndBufPos = 0;
		}
		g_pNesEmuBuf->nAudioSampleSkip = 0;
	}
	nesSndGetSample();
}

#if 0
static void nesSndRegUpdateRealTime(u16 nAddr, u8 nValue)
{
	//sbuffer.buf[nAddr]=nValue;
	switch(nAddr)
	{
	case 0x03:		// 4003h - APU Channel 1 (Rectangle) Length
		sbuffer.buf[nAddr]=nValue;
		if (sbuffer.sr.R_4015.soundA)
			SoundA.activity=1;
		break;
	case 0x07:		// 4007h - APU Channel 2 (Rectangle) Length
		sbuffer.buf[nAddr]=nValue;
		if (sbuffer.sr.R_4015.soundB)
			SoundB.activity=1;
		break;
	case 0x0B:		// 400Bh - APU Channel 3 (Triangle) Length		
		sbuffer.buf[nAddr]=nValue;
		if ( (sbuffer.sr.R_4015.soundC) && (sbuffer.sr.R_4008.length2) )
			SoundC.activity=1;
		else
			SoundC.activity= 0;
		break;
	case 0x0F:		// 400Fh - APU Channel 4 (Noise) Length
		sbuffer.buf[nAddr]=nValue;
		if (sbuffer.sr.R_4015.soundD)
			SoundD.activity = 1;
		break;
	case 0x15:		// 4015h - APU Channel enable register
		sbuffer.buf[nAddr]=nValue;
		if ((nValue & 0x01 )==0) SoundA.activity=0;
		if ((nValue & 0x02 )==0) SoundB.activity=0;
		if ((nValue & 0x04 )==0) SoundC.activity=0;
		if ((nValue & 0x08 )==0) SoundD.activity=0;
		if ((nValue & 0x10 )==0) SoundE.activity=0;
		if ( ((nValue & 0x10 )!=0) && (SoundE.activity==0) ){
			SoundE.activity=1;
			SoundE.interrupt=0;
		}
		break;	
	}
}
#endif

/** @brief Write Data to APU Register */
void nesSndRegWrite(u16 nAddr, u8 nValue)
{	
#if TRL_SOUND_REG_LOG
	if(g_pNesSndRegWriteLog_Run == 0)
	{
		trlTraceSoundDetailWriteReg(nAddr + 0x4000, nValue);
		if(g_pNesSndRegWriteLog_Ct >= TRL_SOUND_REG_LOG_MAX)
		{
			NN_LOG("Error g_pNesSndRegWriteLog_Ct >= TRL_SOUND_REG_LOG_MAX\n");
			return;
		}
		g_pNesSndRegWriteLog_Addr[g_pNesSndRegWriteLog_Ct] = nAddr;
		g_pNesSndRegWriteLog_Value[g_pNesSndRegWriteLog_Ct] = nValue;
		g_pNesSndRegWriteLog_Ticks[g_pNesSndRegWriteLog_Ct] = g_nNesSndRegWriteLog_Ticks;
		g_pNesSndRegWriteLog_Type[g_pNesSndRegWriteLog_Ct] = 0;
		g_pNesSndRegWriteLog_Ct++;
		//nesSndRegUpdateRealTime(nAddr, nValue);
		return;
	}	
#else
	trlTraceSoundDetailWriteReg(nAddr + 0x4000, nValue);
#endif
	sbuffer.buf[nAddr]=nValue; 
	switch(nAddr)
	{
	case 0x00:		// 4000h - APU Channel 1 (Rectangle) Volume/Decay				
	case 0x01:		// 4001h - APU Channel 1 (Rectangle) Sweep				
	case 0x02:		// 4002h - APU Channel 1 (Rectangle) Frequency		
	case 0x03:		// 4003h - APU Channel 1 (Rectangle) Length
		__Sound_Write_A(nAddr, nValue);
		break;
	case 0x04:		// 4004h - APU Channel 2 (Rectangle) Volume/Decay		
	case 0x05:		// 4005h - APU Channel 2 (Rectangle) Sweep		
	case 0x06:		// 4006h - APU Channel 2 (Rectangle) Frequency		
	case 0x07:		// 4007h - APU Channel 2 (Rectangle) Length
		__Sound_Write_B(nAddr, nValue);
		break;
	case 0x08:		// 4008h - APU Channel 3 (Triangle) Linear Counter		
	case 0x0A:		// 400Ah - APU Channel 3 (Triangle) Frequency		
	case 0x0B:		// 400Bh - APU Channel 3 (Triangle) Length		
		__Sound_Write_C(nAddr, nValue);
		break;
	case 0x0C:		// 400Ch - APU Channel 4 (Noise) Volume/Decay		
	case 0x0E:		// 400Eh - APU Channel 4 (Noise) Frequency		
	case 0x0F:		// 400Fh - APU Channel 4 (Noise) Length
		__Sound_Write_D(nAddr, nValue);
		break;
	case 0x10:		// 4010h - APU Channel 5 (DMC) Play mode and DMA frequency		
	case 0x11:		// 4011h - APU Channel 5 (DMC) Delta counter load register		
	case 0x12:		// 4012h - APU Channel 5 (DMC) Address load register		
	case 0x13:		// 4013h - APU Channel 5 (DMC) Length register
		__Sound_Write_E(nAddr, nValue);
		break;
	case 0x15:		// 4015h - APU Channel enable register
		if ((nValue & 0x01 )==0) SoundA.activity=0;
		if ((nValue & 0x02 )==0) SoundB.activity=0;
		if ((nValue & 0x04 )==0) SoundC.activity=0;
		if ((nValue & 0x08 )==0) SoundD.activity=0;
		if ((nValue & 0x10 )==0) SoundE.activity=0;
		if ( ((nValue & 0x10 )!=0) && (SoundE.activity==0) )
			StartE();
		break;
	case 0x17:		// 4017h - APU SOFTCLK
		if (nValue & 0x80)	//	60Frame Mode.
		{
			FRAME_SAMPLE = OUTPUT_RATE/50;
			PHASE_SAMPLE = FRAME_SAMPLE/4;
		}
		else				//	48Frame mode.
		{			
			FRAME_SAMPLE = OUTPUT_RATE/FRAME_DIVIDER;
			PHASE_SAMPLE = FRAME_SAMPLE/4;
		}
		break;		
	}
}
