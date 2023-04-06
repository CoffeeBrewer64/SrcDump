/**
 * @file trlDebug.h
 * @author zhfang
 * @date 2009.11.16
 * @brief TRL Emulate - Debug Module
 */
#pragma once
#include "trlMacro.h"
#include "trlType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @name debug macro output to debugwindow */
//@{
#if !TRL_PRODUCTION
#define TRL_ERROR(m)	TRL_Debug_Error(m, __FILE__,__LINE__)
#define TRL_WARN(l, m) TRL_Debug_Warn(l, m, __FILE__,__LINE__)
#define TRL_INFO(l, m) TRL_Debug_Info(l, m, __FILE__,__LINE__)
#else
#define TRL_ERROR(m)	((void)0)
#define TRL_WARN(l, m) ((void)0)
#define TRL_INFO(l, m) ((void)0)
#endif
//@}

/** @brief Debug Error*/
void TRL_Debug_Error(char *szMessage, char *szFile, int nLine);
/** @brief Debug Warn*/
void TRL_Debug_Warn(int nLevel, char *szMessage, char *szFile, int nLine);
/** @brief Debug Info*/
void TRL_Debug_Info(int nLevel, char *szMessage, char *szFile, int nLine);
/** @brief Debug Log*/
void TRL_Debug_Log(const char *szFormat, ...);

/** @name time debug macro*/
//@{
#if !TRL_PRODUCTION
#define TRL_TIME_BEGIN(n) TRL_Debug_TimeBegin(n)
#define TRL_TIME_LOG(n)  TRL_Debug_TimeLog(n)
#define TRL_TIME_LOG64(n)  TRL_Debug_TimeLog64(n)
#define TRL_TIME_GET(n) TRL_Debug_TimeGet(n)
#define TRL_TIME_GET64(n) TRL_Debug_TimeGet64(n)
#else
#define TRL_TIME_BEGIN(n)  ((void)0)
#define TRL_TIME_LOG(n)  ((void)0)
#define TRL_TIME_LOG64(n)  ((void)0)
#define TRL_TIME_GET(n)  ((void)0)
#define TRL_TIME_GET64(n) ((void)0)
#endif
//@}

/** @brief time test Begin */
void TRL_Debug_TimeBegin(int nIndex);
/** @brief time test Output Log 32 bit */
void TRL_Debug_TimeLog(int nIndex);
/** @brief time test Output Log 64 bit */
void TRL_Debug_TimeLog64(int nIndex);
/** @brief time test 32 bit */
u32 TRL_Debug_TimeGet(int nIndex);
/** @brief time test 64 bit */
u64 TRL_Debug_TimeGet64(int nIndex);

#ifdef TRL_PLATFORM_PC
#define NN_LOG	TRL_Debug_Log
#endif
