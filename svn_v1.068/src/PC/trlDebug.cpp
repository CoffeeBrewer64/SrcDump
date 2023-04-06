/**
 * @file trlDebug.cpp
 * @author Chentian
 * @date 2009.11.16
 * @brief TRL Emulate For PC - Debug Module
 */
#include "..\trlDebug.h"
#include "..\trlTime.h"

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

#define TRL_DEBUG_STRINGBUF_MAX   256
char g_szString[TRL_DEBUG_STRINGBUF_MAX];
/** @brief Debug Error*/
void TRL_Debug_Error(char *szMessage, char *szFile, int nLine)
{	
	sprintf_s(g_szString, TRL_DEBUG_STRINGBUF_MAX, "%s at file: %s  line: %d\n", szMessage, szFile, nLine);	
	OutputDebugString(g_szString);
}

/** @brief Debug Warn*/
void TRL_Debug_Warn(int nLevel, char *szMessage, char *szFile, int nLine)
{
	if(nLevel <= TRL_DEBUG_LEVEL)
	{
		sprintf_s(g_szString, TRL_DEBUG_STRINGBUF_MAX, "%s at file: %s  line: %d\n", szMessage, szFile, nLine);
		OutputDebugString(g_szString);
	}
}

/** @brief Debug Info*/
void TRL_Debug_Info(int nLevel, char *szMessage, char *szFile, int nLine)
{
	if(nLevel <= TRL_DEBUG_LEVEL)
	{
		sprintf_s(g_szString, TRL_DEBUG_STRINGBUF_MAX, "%s at file: %s  line: %d\n", szMessage, szFile, nLine);
		OutputDebugString(g_szString);
	}
}

/** @brief Debug Log*/
void TRL_Debug_Log(const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 stringSize = vsnprintf_s(g_szString, TRL_DEBUG_STRINGBUF_MAX, _TRUNCATE, szFormat, va);
	va_end(va);

	OutputDebugString(g_szString);
}

/** @brief time test Output Log 32 bit */
void TRL_Debug_TimeLog(int nIndex)
{	
	u64 nCurTick = trlTimeGet_us();
	sprintf_s(g_szString, TRL_DEBUG_STRINGBUF_MAX, "DebugTime No.%d   time %d\n", nIndex, (u32)((nCurTick-trlDebugTimeTable[nIndex])/1000));	
	OutputDebugString(g_szString);
	trlDebugTimeTable[nIndex] = nCurTick;	
}

/** @brief time test Output Log 64 bit */
void TRL_Debug_TimeLog64(int nIndex)
{
	u64 nCurTick = trlTimeGet_us();
	sprintf_s(g_szString, TRL_DEBUG_STRINGBUF_MAX, "DebugTime No.%d   time %d\n", nIndex, nCurTick-trlDebugTimeTable[nIndex]);	
	OutputDebugString(g_szString);
	trlDebugTimeTable[nIndex] = nCurTick;	
}
