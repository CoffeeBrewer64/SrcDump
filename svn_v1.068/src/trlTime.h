/**
 * @file trlTime.h
 * @author Chentian
 * @date 2009.12.25
 * @brief TRL Emulate - Time Module
 */
#pragma once
#include "trlType.h"

/** @name Macro Define */
//@{
#define TRL_TIME_GET_YEAR(t)		((t >> 26) & 0xFFF)
#define TRL_TIME_GET_MONTH(t)		((t >> 22) & 0xF)
#define TRL_TIME_GET_DAY(t)			((t >> 17) & 0x1F)
#define TRL_TIME_GET_HOUR(t)		((t >> 12) & 0x1F)
#define TRL_TIME_GET_MINUTE(t)		((t >> 6) & 0x3F)
#define TRL_TIME_GET_SECOND(t)		(t & 0x3F)
//@}

/** @brief Time Init */
void trlTimeInit();
/** @brief Get Time - millisecond */
u64 trlTimeGet_us();
/** @brief Get Time - microsecond */
u64 trlTimeGet_ms();
/** @brief Get Time - second */
u64 trlTimeGet();
/** @brief Start Time */
void trlTimeStart();
/** @brief Get Current Time */
void trlTimeWatch();
/** @brief Pause Time */
void trlTimePause();
/** @brief Resume Time */
void trlTimeResume();
/** @brief Stop Time */
u32 trlTimeStop();
/** @brief Get Watch Time */
u32 trlTimeGetWatch(u32 nIndex);
/** @brief Get Now Time */
u64 trlTimeGetNow();
/** @brief Get Elapsed Time */
s32 trlTimeGetElapsedTime(u64 nOld, u64 nNow);
/** @brief Sleep */
void trlTimeSleep(u64 nMicrosec);
/** @brief Start Limit FPS */
void trlTimeFPS_Start();
/** @brief End Limit FPS */
void trlTimeFPS_End();
