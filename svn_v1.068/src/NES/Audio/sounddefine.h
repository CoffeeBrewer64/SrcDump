#pragma once
#include "../nesGlobal.h"

#define	USE_SOUNDSAMPLESCALING (1)

#define	__GETWAVE_DISK_20080112 (0)

#define SOUND_FADE_IN_OUT (1)
#define SOUND_INT_SHIFT	16
#define SOUND_INT_ONE	0x00010000 //(0x1<<SOUND_INT_SHIFT) 
//////////////////////////////////////////////////////////

#define OUTPUT_RATE (44100)
#define OUTPUT_RATE_PER_FRAME OUTPUT_RATE/60

#define PITCH_CONST ((f32)((f32)OUTPUT_RATE/32.0f))
#define PITCH_CONST_DISK ((f32)((f32)OUTPUT_RATE/64.0f))
#define LEN_SCALE (1)


#define CPUCLOCK_NTSC		(1789882.8f)	//		 = 21.48MHz/12
#define CPUCLOCK_PAL		(1662500.0f)	//		 = 26.6 MHz/16
#define CPUCLOCK			CPUCLOCK_NTSC

#define SOUND_SWEEP_RREQ_NTSC	120
#define SOUND_SWEEP_RREQ_PAL	90
#define SOUND_SWEEP_FREQ		SOUND_SWEEP_RREQ_NTSC

#define SOUND_ENVELOPE_FREQ_NTSC	240
#define SOUND_ENVELOPE_FREQ_PAL		192
#if TRL_NES_SOUND_ENVELOPE_FREQ_NTSC
#define SOUND_ENVELOPE_FREQ			SOUND_ENVELOPE_FREQ_NTSC
#else
#define SOUND_ENVELOPE_FREQ			SOUND_ENVELOPE_FREQ_PAL
#endif


#if ( USE_SOUNDSAMPLESCALING == 1)
#define		SOUNDSAMPLESCALING_SOUNDA		(0.9)
#define		SOUNDSAMPLESCALING_SOUNDB		(0.9)
#define		SOUNDSAMPLESCALING_SOUNDC		(0.9)
#define		SOUNDSAMPLESCALING_SOUNDD		(1.70)
#define		SOUNDSAMPLESCALING_SOUNDE		(0.7)
#define		SOUNDSAMPLESCALING_SOUNDF		(1.2)
#define		SOUNDSAMPLESCALING_SOUND5A		(0.9)
#define		SOUNDSAMPLESCALING_SOUND5B		(0.9)
#define		SOUNDSAMPLESCALING_SOUNDZ		(1.0)
#endif

#define SOUNDE_DOWNCOEF  (0.9994586f)

#define SOUNDE_OUTPUT_GAIN (216)		// 1:1 Filtered