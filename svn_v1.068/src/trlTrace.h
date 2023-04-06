/**
 * @file trlTrace.h
 * @author Zhfang
 * @date 2011.02.12
 * @brief TRL Emulate - Trace Module
 */
#pragma once
#include "trlMacro.h"
#include "trlType.h"

#if TRL_PRODUCTION
#define TRL_TRACETOOL 0
#endif

#ifndef TRL_NOTRACETOOL
#define TRL_NOTRACETOOL 0
#endif

#if TRL_NOTRACETOOL
	#define TRL_TRACETOOL 0
#else
	#ifndef TRL_TRACETOOL
		#if TRL_PLATFORM_CTR
			#define TRL_TRACETOOL 0
		#else
			#define TRL_TRACETOOL 1
		#endif
	#endif
#endif

#if TRL_TRACETOOL

/** @name Macro Define */
//@{
//@}
void trlTraceWRCt();

void trlTraceInit();
void trlTraceReset();

void trlTraceFrameBegin();
void trlTraceFrameEnd();

void trlTraceTickReset();
void trlTraceTickAdd(u32 addticks);

void trlTraceWriteReg(u32 reg, u32 value);




/////////////////////////
//log the sound
void trlTraceSoundMainLog(char *str);
void trlTraceSoundMainLogv2(char *str,u32 v1, u32 v2);
/////////////////////////
//log the sound detail
void trlTraceSoundDetailMakeSample();
void trlTraceSoundDetailMakeSampleSkip(u32 n);
void trlTraceSoundDetailTryMakeSample();
void trlTraceSoundDetailWriteReg(u32 addr, u32 data);
void trlTraceSoundDetallSweepFreq(u32 freq);
//////////////////
//cpu run debug
void trlTraceCPURun();
void trlTraceCPURUN_NES();

void trlTraceMemRead(u32 addr, u32 value);
void trlTraceMemWrite(u32 addr, u32 value);
///////////////
void trlTraceTimer();
void trlTraceTimerDetail();

void trlTracePushStack(u32 value);
void trlTrackPopStack();
#else
#define trlTraceInit() ((void)0)
#define trlTraceReset()	((void)0)

#define trlTraceFrameBegin() ((void)0)
#define trlTraceFrameEnd() ((void)0)

#define trlTraceTickReset()	((void)0)
#define trlTraceTickAdd(n) ((void)0)

#define trlTraceWriteReg(m,n)  ((void)0)

#define trlTraceSoundMainLog(n) ((void)0)
#define trlTraceSoundMainLogv2(n, v1, v2) ((void)0)
#define trlTraceSoundDetallSweepFreq(n) ((void)0)

#define trlTraceSoundDetailMakeSample()  ((void)0)
#define trlTraceSoundDetailMakeSampleSkip(n) ((void)0)
#define trlTraceSoundDetailWriteReg(m,n)  ((void)0)

#define trlTraceCPURun()  ((void)0)
#define trlTraceCPURUN_NES()  ((void)0)

#define trlTraceMemRead(m,n) ((void)0)
#define trlTraceMemWrite(m,n) ((void)0)

#define trlTraceTimer()	((void)0)
#define trlTraceTimerDetail()	((void)0)

#define trlTracePushStack(n) ((void)0)
#define trlTrackPopStack() ((void)0)
#endif





#if TRL_PLATFORM_CTR
#define TRL_HIO 0
#else
#define TRL_HIO 0
#endif

#if TRL_HIO
void trlTraceHioInit();
void trlTraceHio(char *str);
void trlTraceHioRelease();
#else
#define trlTraceHioInit() ((void)0)
#define trlTraceHio(n) ((void)0)
#define trlTraceHioRelease() ((void)0)
#endif
