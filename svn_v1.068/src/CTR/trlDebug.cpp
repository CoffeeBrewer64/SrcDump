/**
 * @file trlDebug.cpp
 * @author zhfang
 * @date 2009.11.16
 * @brief TRL Emulate For CTR - Debug Module
 */
#include "..\trlDebug.h"
#include "..\trlTime.h"
#include <nn/os.h>
#include <nn/os/os_Tick.h>
using namespace nn::os;

#ifdef NN_LOG_LEVEL_DEFAULT
#undef NN_LOG_LEVEL_DEFAULT
#endif

#ifndef TRL_DEBUG_LEVEL
#define TRL_DEBUG_LEVEL 2  ///< the macro that control the debug message output level, '2' will output all '0' will output the importent
#endif

static u64 trlDebugTimeTable[256];
/** @brief time test begin*/
void TRL_Debug_TimeBegin(int nIndex)
{	
	trlDebugTimeTable[nIndex] = trlTimeGet_us();
}

/** @brief time test 32 bit */
u32 TRL_Debug_TimeGet(int nIndex)
{
	u64 nCurTick = trlTimeGet_us();
	u32 nTemp = (u32)((nCurTick-trlDebugTimeTable[nIndex]) / 1000);
	trlDebugTimeTable[nIndex] = nCurTick;
	return nTemp;
}

/** @brief time test 64 bit */
u64 TRL_Debug_TimeGet64(int nIndex)
{
	u64 nCurTick = trlTimeGet_us();
	u64 nTemp = nCurTick-trlDebugTimeTable[nIndex];
	trlDebugTimeTable[nIndex] = nCurTick;
	return nTemp;
}

/** @brief Debug Error*/
void TRL_Debug_Error(char *szMessage, char *szFile, int nLine)
{
	(void)szMessage;
	(void)szFile;
	(void)nLine;
	NN_LOG_FATAL("%s at file: %s  line: %d\n", szMessage, szFile, nLine);
	nn::dbg::Break(nn::dbg::BREAK_REASON_PANIC);
}
/** @brief Debug Warn*/
void TRL_Debug_Warn(int nLevel, char *szMessage, char *szFile, int nLine)
{
	(void)szMessage;
	(void)szFile;
	(void)nLine;
	if(nLevel <= TRL_DEBUG_LEVEL)
		NN_LOG_WARN("%s at file: %s  line: %d\n", szMessage, szFile, nLine);
}

/** @brief Debug Info*/
void TRL_Debug_Info(int nLevel, char *szMessage, char *szFile, int nLine)
{
	(void)szMessage;
	(void)szFile;
	(void)nLine;
	if(nLevel <= TRL_DEBUG_LEVEL)
		NN_LOG("%s at file: %s  line: %d\n", szMessage, szFile, nLine);
}

/** @brief time test Output Log 32 bit */
void TRL_Debug_TimeLog(int nIndex)
{
	u64 nCurTick = trlTimeGet_us();
	NN_LOG("DebugTime No.%d   time %d\n", nIndex, (nCurTick-trlDebugTimeTable[nIndex])/(Tick::TICKS_PER_SECOND/1000));
	trlDebugTimeTable[nIndex] = nCurTick;	
}

/** @brief time test Output Log 64 bit */
void TRL_Debug_TimeLog64(int nIndex)
{
	u64 nCurTick = trlTimeGet_us();
	NN_LOG("DebugTime No.%d   time %d\n", nIndex, (nCurTick-trlDebugTimeTable[nIndex])/(Tick::TICKS_PER_SECOND/1000000));
	trlDebugTimeTable[nIndex] = nCurTick;	
}
