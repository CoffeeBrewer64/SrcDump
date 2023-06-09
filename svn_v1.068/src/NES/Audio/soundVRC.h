#pragma once
#include "sounddefine.h"
#include "soundtype.h"
#include "../nesSound.h"

void __Sound_Write_VRC(u16 reg, u8 value)
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
#endif
	if( (reg%4) != 0)
		reg += 1;
	sbuffer.buf[reg + 0xC0]=value; 

	Sound_HVCpulse_ *sd;
	VRCpulse_ *v;	
	s32 ch;

	if (reg <= 0x03)
	{
		ch=0; sd=&SoundX;  v=(VRCpulse_ *)&(sbuffer.buf[0xc0]);		
	}
	else if (reg <= 0x07)
	{
		ch=1; sd=&SoundY;  v=(VRCpulse_ *)&(sbuffer.buf[0xc4]);
	}
	else
	{ 			
		ch=2; sd=&SoundZ;  v=(VRCpulse_ *)&(sbuffer.buf[0xc8]);
	}

	/*if (reg==0x15)	
	{
		if ((value & 0x01 )==0)
			SoundX.activity=0;
		if ((value & 0x02 )==0) 
			SoundY.activity=0;
		if ((value & 0x04 )==0) 
			SoundZ.activity=0;
		return;
	}*/

	switch(reg & 0x03)
	{
	case 0:
		if (ch==2)
		{
			sd->envinterval=(u32)(value&0x1F);			
		}
		else
		{
			sd->dutytype= (value>>4);
			sd->volume = (value&0xF);
		}
		break;	
	case 2:
		sd->pitch_org = (u16)((v->R_4003.freq << 8) | (v->R_4002));
		if (ch == 2)
			sd->pitch=__PitchTo32_VRC_C(sd->pitch_org);
		else
			sd->pitch=__PitchTo32_VRC_PULSE(sd->pitch_org);
		break;
	case 3:
		sd->pitch_org = (u16)((v->R_4003.freq << 8) | (v->R_4002));
		if (ch==2)
			sd->pitch=__PitchTo32_VRC_C(sd->pitch_org);
		else
			sd->pitch=__PitchTo32_VRC_PULSE(sd->pitch_org);
	
		if(v->R_4003.enable)
			sd->activity=1;
		else
			sd->activity=0;
		break;
	}
}

inline u16 __ProcessSoundVRC(s32 ch)
{
	u16 sample;
	u32 sample32;
	Sound_HVCpulse_ *sd;



	switch(ch)
	{
	case 0:
		sd=&SoundX; break;
	case 1:
		sd=&SoundY; break;
	case 2:
		sd=&SoundZ; break;
	}
	if(sd->activity == 0)
		return 0;

	if (sd->activity==0)
	{
		if (sd->lastlevel==0) return(0);
		sd->lastlevel--;		
		sd->pitch=sd->lastpitch;
	}
	
	if(sd->fcounter.fc.high >=0x1000)
		sd->fcounter.fc.high = 0;


	if (ch <2)
	{
		sample32=__GetWave_Pulse2(sd->dutytype+VRC_DUTY_0, &(sd->fcounter.fc32), sd->pitch);
		#if TRL_HVC_SOUND_TEST
		if(ch == 0)
			sample32 *= g_bNesSnd5A;
		else
			sample32 *= g_bNesSnd5B;
		#endif
		return (sample32*sd->volume*0x60)>>12;
	}
	else if (ch==2)
	{
		u16 old = sd->fcounter.fc.high;
		sd->fcounter.fc32 += (sd->pitch/16);
		for(int i= old; i<sd->fcounter.fc.high;i++)
		{
			if(sd->fc32 == 0)
				sd->volume = 0;
			else
			{
				sd->volume += sd->envinterval;
			}
			sd->fc32++;
			if(sd->fc32 == 7)
				sd->fc32 = 0;
		}
		
		sample = (sd->volume>>3)* 0x60;
		#if TRL_HVC_SOUND_TEST		
		sample *= g_bNesSndZ;
		#endif
		return sample;
	}
	return 0;
}

