#pragma once
#include "sounddefine.h"
#include "soundtype.h"

inline u8 __GetWave_PCM(s32 counter)
{
	if ( !(SoundP.datatop) )
	{
		return 0;
	}
	return (u8)(SoundP.datatop[counter]);
}


inline s16 __ProcessSoundP(void)
{
	s8 sample;
	s16 sample16;


	if (SoundP.number)
	{
		SoundP.fcounter.fc32=0;
		SoundP.number--;

		if ( PCMH2.mytop )
		{
			SoundP.datatop=(s8 *)(PCMH2.mytop+__ntohs(PCMH2.addr_table[SoundP.number]));
			SoundP.datalen=(s32)__ntohs(PCMH2.size_table[SoundP.number]);
			SoundP.pitch32=(u32)(0x10000*__ntohs(PCMH2.info_table[SoundP.number])/OUTPUT_RATE);
		}
		SoundP.number=0;
		SoundP.activity=1;
	}


	if (SoundP.fcounter.fc.high >= SoundP.datalen)
	{
		SoundP.activity=0;
	}

	if (SoundP.activity==0) 
		return (0);

	sample=(s8)(__GetWave_PCM(SoundP.fcounter.fc.high));
	sample16 = sample;
	sample16 = (s16)(sample16 << 6);

	SoundP.fcounter.fc32+=SoundP.pitch32;

	return(sample16);
}


void __Sound_Write_JALECO(u16 reg, u8 value)
{
#if TRL_SOUND_REG_LOG
	if(g_pNesSndRegWriteLog_Run == 0)
	{
		if(g_pNesSndRegWriteLog_Ct >= TRL_SOUND_REG_LOG_MAX)
		{
			NN_LOG("Error g_pNesSndRegWriteLog_Ct >= TRL_SOUND_REG_LOG_MAX\n");
			return;
		}
		g_pNesSndRegWriteLog_Addr[g_pNesSndRegWriteLog_Ct] = reg;
		g_pNesSndRegWriteLog_Value[g_pNesSndRegWriteLog_Ct] = value;
		g_pNesSndRegWriteLog_Ticks[g_pNesSndRegWriteLog_Ct] = g_nNesSndRegWriteLog_Ticks;
		g_pNesSndRegWriteLog_Type[g_pNesSndRegWriteLog_Ct] = 1;
		g_pNesSndRegWriteLog_Ct++;
		return;
	}	
#else
	((void)reg);
#endif
	u8 on=(value>>4)&0x3;
	if(on==2){
		u8 id=(value&0xF)+1;
		SoundP.number = id;
	}//else
	//	SoundP.number = 0;
}
