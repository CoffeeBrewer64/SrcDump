/**
 * @file trlTime_CTR.cpp
 * @author Chentian
 * @date 2009.12.25
 * @brief TRL Emulate For CTR - Time Module
 */
#include "..\trlTime.h"
#include <nn/os.h>
#include <nn/os/os_Tick.h>
using namespace nn::os;
using namespace nn::fnd;

/** @name Global Variable */
//@{
s64		g_nTrlTicksus	= 0;
s64		g_nTrlTicksms	= 0;
s64		g_nTrlTime0		= 0;
s64		g_nTrlTime1		= 0;
s64		g_nTrlTimeW[16];
u32		g_nTrlTimeC		= 0;
//@}

/** @brief Time Init */
void trlTimeInit()
{
	g_nTrlTicksus = Tick::TICKS_PER_SECOND / 1000000;
	g_nTrlTicksms = Tick::TICKS_PER_SECOND / 100000;
}

/** @brief Get Time - millisecond */
u64 trlTimeGet_us()
{
	return (u64)(Tick::GetSystemCurrent() / g_nTrlTicksus);
}

/** @brief Get Time - microsecond */
u64 trlTimeGet_ms()
{
	return (u64)(Tick::GetSystemCurrent() / g_nTrlTicksms);
}

/** @brief Get Time - second */
u64 trlTimeGet()
{
	return (u64)(Tick::GetSystemCurrent() / Tick::TICKS_PER_SECOND);
}

/** @brief Get Now Time */
u64 trlTimeGetNow()
{
	DateTime hTime = DateTime::GetNow();
	u64 nTime = ((u64)hTime.GetYear() << 26) | (hTime.GetMonth() << 22) | (hTime.GetDay() << 17) | (hTime.GetHour() << 12) | (hTime.GetMinute() << 6) | hTime.GetSecond();
	return nTime;
}

/** @brief Get Elapsed Time */
s32 trlTimeGetElapsedTime(u64 nOld, u64 nNow)
{
	s32 nDayOld = DateTime::DateToDays(TRL_TIME_GET_YEAR(nOld), TRL_TIME_GET_MONTH(nOld), TRL_TIME_GET_DAY(nOld));
	s32 nDayNow = DateTime::DateToDays(TRL_TIME_GET_YEAR(nNow), TRL_TIME_GET_MONTH(nNow), TRL_TIME_GET_DAY(nNow));
	s32 nSecDay = (nDayNow - nDayOld) * 86400;
	s32 nSecOld = (TRL_TIME_GET_HOUR(nOld) * 60 + TRL_TIME_GET_MINUTE(nOld)) * 60 + TRL_TIME_GET_SECOND(nOld);
	s32 nSecNow = (TRL_TIME_GET_HOUR(nNow) * 60 + TRL_TIME_GET_MINUTE(nNow)) * 60 + TRL_TIME_GET_SECOND(nNow);
	return nSecDay - nSecOld + nSecNow;
}

/** @brief Start Time */
void trlTimeStart()
{
	g_nTrlTimeC = 0;
	g_nTrlTime0 = (s64)(Tick::GetSystemCurrent() / g_nTrlTicksms);
}

/** @brief Get Current Time */
void trlTimeWatch()
{
	g_nTrlTimeW[g_nTrlTimeC++] = (s64)(Tick::GetSystemCurrent() / g_nTrlTicksms);
}

/** @brief Pause Time */
void trlTimePause()
{
	g_nTrlTime1 = (s64)(Tick::GetSystemCurrent() / g_nTrlTicksms);
}

/** @brief Resume Time */
void trlTimeResume()
{
	g_nTrlTime0 += (s64)(Tick::GetSystemCurrent() / g_nTrlTicksms) - g_nTrlTime1;
}

/** @brief Stop Time */
u32 trlTimeStop()
{
	return (u32)((Tick::GetSystemCurrent() / g_nTrlTicksms) - g_nTrlTime0);
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
	nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMicroSeconds(nMicrosec));
}
