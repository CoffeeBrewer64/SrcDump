/**
 * @file trlTime_PC.cpp
 * @author Chentian
 * @date 2009.12.25
 * @brief TRL Emulate For PC - Time Module
 */
#include "..\trlTime.h"

/** @name Global Variable */
//@{
typedef BOOLEAN		(WINAPI *trlTimeSince1970)(PLARGE_INTEGER, PULONG);
LARGE_INTEGER		g_nTrlFrequency;
LARGE_INTEGER		g_nTrlCountStart;
LARGE_INTEGER		g_nTrlCountEnd;
LARGE_INTEGER		g_nTrlFPSStart;
LARGE_INTEGER		g_nTrlFPSEnd;
u64					g_nTrlTicksus = 0;
u64					g_nTrlTicksms = 0;
u64					g_nTrlTime0	= 0;
u64					g_nTrlTime1	= 0;
u64					g_nTrlTimeW[16];
u32					g_nTrlTimeC	= 0;
u64					g_nTrlFPS = 0;
trlTimeSince1970	trlTimeDateToDays = NULL;
//@}

/** @brief Time Init */
void trlTimeInit()
{
	trlTimeDateToDays = (trlTimeSince1970)GetProcAddress(LoadLibrary("Ntdll.dll"), "RtlTimeToSecondsSince1970");
	QueryPerformanceFrequency(&g_nTrlFrequency);
	g_nTrlTicksus = g_nTrlFrequency.QuadPart / 1000000;
	g_nTrlTicksms = g_nTrlFrequency.QuadPart / 1000;
	//CTR is    268868100 / 268111856 =1.00282s/60frames
	//CTR sound avg sample/per frame at 44100 is 737.1	
	g_nTrlFPS = 100282*g_nTrlFrequency.QuadPart / 6000000;
}

/** @brief Get Time - millisecond */
u64 trlTimeGet_us()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	return g_nTrlCountStart.QuadPart / g_nTrlTicksus;
}

/** @brief Get Time -  microsecond */
u64 trlTimeGet_ms()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	return g_nTrlCountStart.QuadPart / g_nTrlTicksms;
}

/** @brief Get Time - second */
u64 trlTimeGet()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	return g_nTrlCountStart.QuadPart / g_nTrlFrequency.QuadPart;
}

/** @brief Get Now Time */
u64 trlTimeGetNow()
{
	SYSTEMTIME hTime;
    GetLocalTime(&hTime);
	u64 nTime = ((u64)hTime.wYear << 26) | (hTime.wMonth << 22) | (hTime.wDay << 17) | (hTime.wHour << 12) | (hTime.wMinute << 6) | hTime.wSecond;
	return nTime;
}

/** @brief Get Elapsed Time */
s32 trlTimeGetElapsedTime(u64 nOld, u64 nNow)
{
    FILETIME ft;
    SYSTEMTIME st;
	st.wDayOfWeek = 0;
	st.wMilliseconds = 0;
	st.wYear = TRL_TIME_GET_YEAR(nOld);
	st.wMonth = TRL_TIME_GET_MONTH(nOld);
	st.wDay = TRL_TIME_GET_DAY(nOld);
	st.wHour = TRL_TIME_GET_HOUR(nOld);
	st.wMinute = TRL_TIME_GET_MINUTE(nOld);
	st.wSecond = TRL_TIME_GET_SECOND(nOld);
    SystemTimeToFileTime(&st, &ft);
	ULONG nSecOld;
	trlTimeDateToDays((LARGE_INTEGER*)&ft, &nSecOld);

	st.wYear = TRL_TIME_GET_YEAR(nNow);
	st.wMonth = TRL_TIME_GET_MONTH(nNow);
	st.wDay = TRL_TIME_GET_DAY(nNow);
	st.wHour = TRL_TIME_GET_HOUR(nNow);
	st.wMinute = TRL_TIME_GET_MINUTE(nNow);
	st.wSecond = TRL_TIME_GET_SECOND(nNow);
    SystemTimeToFileTime(&st, &ft);
	ULONG nSecNow;
	trlTimeDateToDays((LARGE_INTEGER*)&ft, &nSecNow);
	return (s32)(nSecNow - nSecOld);
}

/** @brief Start Time */
void trlTimeStart()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	g_nTrlTime0 = g_nTrlCountStart.QuadPart / g_nTrlTicksms;
	g_nTrlTimeC = 0;
}

/** @brief Get Current Time */
void trlTimeWatch()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	g_nTrlTimeW[g_nTrlTimeC++] = g_nTrlCountStart.QuadPart / g_nTrlTicksms;
}

/** @brief Pause Time */
void trlTimePause()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	g_nTrlTime1 = g_nTrlCountStart.QuadPart / g_nTrlTicksms;
}

/** @brief Resume Time */
void trlTimeResume()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	g_nTrlTime0 += g_nTrlCountStart.QuadPart / g_nTrlTicksms - g_nTrlTime1;
}

/** @brief Stop Time */
u32 trlTimeStop()
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	return (u32)(g_nTrlCountStart.QuadPart / g_nTrlTicksms - g_nTrlTime0);
}

/** @brief Get Watch Time */
u32 trlTimeGetWatch(u32 nIndex)
{
	if(nIndex==0)
		return (u32)(g_nTrlTimeW[nIndex] - g_nTrlTime0);
	else
		return (u32)(g_nTrlTimeW[nIndex] - g_nTrlTimeW[nIndex-1]);
}

/** @brief Sleep */
void trlTimeSleep(u64 nMicrosec)
{
	QueryPerformanceCounter(&g_nTrlCountStart);
	g_nTrlCountStart.QuadPart += g_nTrlTicksms * nMicrosec;
	do{
		QueryPerformanceCounter(&g_nTrlCountEnd);
	}while(g_nTrlCountEnd.QuadPart < g_nTrlCountStart.QuadPart);
}

/** @brief Start Limit FPS */
void trlTimeFPS_Start()
{
	QueryPerformanceCounter(&g_nTrlFPSStart);
	g_nTrlFPSStart.QuadPart += g_nTrlFPS;
}

u32 bTrlTimeEmuFast = 0;
/** @brief End Limit FPS */
void trlTimeFPS_End()
{
	if(bTrlTimeEmuFast == 0)
	{
		do{
			QueryPerformanceCounter(&g_nTrlFPSEnd);
		}while(g_nTrlFPSEnd.QuadPart < g_nTrlFPSStart.QuadPart);
	}
}
