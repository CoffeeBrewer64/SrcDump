/**
 * @file trlEmuShellAudio.cpp
 * @author Chentian
 * @date 2009.12.17
 * @brief TRL Emulate - EmuShell Audio Module
 */
#include "trlEmuShellAudio.h"
#include "trlEmuShellStruct.h"

/** @name Macro Define */
//@{
#define FRAME_DELAY				4
#define SAMPLES_PER_FRAME		738
#define SAMPLES_PER_FRAME_SMALL	(SAMPLES_PER_FRAME-1)
#define SAMPLE_DIFF_MIN_LIMIT	(SAMPLES_PER_FRAME*(FRAME_DELAY-1))
#define SAMPLE_DIFF_ORIGIN		(SAMPLES_PER_FRAME*(FRAME_DELAY+0))
#define SAMPLE_DIFF_MAX_LIMIT	(SAMPLES_PER_FRAME*(FRAME_DELAY+1))
//@}

/** @name Global Variable */
//@{
u32 g_nTrlAudioSamplePlayed = 0;
u32 g_nTrlAudioSampleMaked = 0;
u32 g_bTrlAudioPaused = 0;
s32 g_nTrlAudioLastPos =0;
s32 g_nTrlAudioCurPos = 0;
u32 g_bTrlAudioRecord = 0;
//@}

/** @brief EmuShell Audio Main */
void trlEmuShellAudioMain()
{	
	g_nTrlAudioCurPos = trlEmuShellAudioGetPlayPosition();
	s32 played = (g_nTrlAudioCurPos - g_nTrlAudioLastPos);
	g_nTrlAudioSamplePlayed += (g_nTrlAudioCurPos - g_nTrlAudioLastPos);
	if(g_nTrlAudioCurPos < g_nTrlAudioLastPos)
	{
		g_nTrlAudioSamplePlayed += TRL_EMUCORE_SNDBUF/4;
		played += TRL_EMUCORE_SNDBUF/4;
	}
	g_sEmuShellBuffer.nAudioSampleSkip = 0;

	s32 diff = g_nTrlAudioSampleMaked -g_nTrlAudioSamplePlayed;

	//if(g_sEmuShellBuffer.nAudioSampleCurFrame != 0)	
	//	NN_LOG("ERROR:g_sEmuShellBuffer.nAudioSampleCurFrame isn't 0 at end of frame  %d\n", g_sEmuShellBuffer.nAudioSampleCurFrame);

	g_nTrlAudioSampleMaked -= g_sEmuShellBuffer.nAudioSampleCurFrame;

	if(diff < SAMPLE_DIFF_MIN_LIMIT)
	{
		g_sEmuShellBuffer.nAudioSampleCurFrame = SAMPLES_PER_FRAME;
		g_sEmuShellBuffer.nAudioSampleSkip += (SAMPLE_DIFF_ORIGIN-diff);		
	}
	else if(diff < SAMPLE_DIFF_ORIGIN)
	{
		g_sEmuShellBuffer.nAudioSampleCurFrame = SAMPLES_PER_FRAME;		
	}
	else if(diff < SAMPLE_DIFF_MAX_LIMIT)
	{
		g_sEmuShellBuffer.nAudioSampleCurFrame = SAMPLES_PER_FRAME_SMALL;
	}	
	else
	{
		g_sEmuShellBuffer.nAudioSampleCurFrame = 0;		
	}

	trlTraceSoundMainLogv2("trlEmuShellAudioMain frame = %d skip = %d\n", g_sEmuShellBuffer.nAudioSampleCurFrame, g_sEmuShellBuffer.nAudioSampleSkip);
	
	/*{
		static u32 ct = 0;
		ct++;
		if((ct%60)== 0)
		{
			extern s32 g_nTrlAudioCurPos;
			extern s32 g_nCgbSndBufPos;
			NN_LOG("nPos = %8d, makepos = %8d lastpos = %8d played = %8d  avg = %8f  diff = %8d make = %8d\n", g_nTrlAudioCurPos, g_nCgbSndBufPos/2, g_nTrlAudioLastPos, played, 1.0*cta/ctb,diff,g_sEmuShellBuffer.nAudioSampleCurFrame);
		}
	}*/

	g_nTrlAudioSampleMaked += g_sEmuShellBuffer.nAudioSampleCurFrame + g_sEmuShellBuffer.nAudioSampleSkip;
	if(g_nTrlAudioSampleMaked > 0x10000000 && g_nTrlAudioSamplePlayed > 0x10000000)
	{
		g_nTrlAudioSampleMaked -= 0x10000000;
		g_nTrlAudioSamplePlayed -= 0x10000000;
	}
	g_nTrlAudioLastPos = g_nTrlAudioCurPos;
	
#if TRL_PROFILER
	g_sEmuShellBuffer.nProfiler4 = g_sEmuShellBuffer.nAudioSampleCurFrame;
#endif
}

/** @brief EmuShell Audio Resume */
void trlEmuShellAudioResume()
{
	memset(g_sEmuShellBuffer.pSoundBuf, 0, TRL_EMUCORE_SNDBUF);
	g_nTrlAudioSamplePlayed = 0;
	g_nTrlAudioSampleMaked = SAMPLE_DIFF_ORIGIN;
	g_sEmuShellBuffer.nAudioSampleCurFrame = 0;
	g_sEmuShellBuffer.nAudioSampleSkip = 0;
	g_sEmuShellBuffer.nAudioSampleOffset = SAMPLE_DIFF_ORIGIN;
	g_bTrlAudioPaused = 0;
	g_nTrlAudioLastPos =0;
	g_nTrlAudioCurPos = 0;
}
