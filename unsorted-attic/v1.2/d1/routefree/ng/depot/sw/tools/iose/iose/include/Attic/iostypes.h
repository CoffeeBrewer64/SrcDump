/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */
#ifndef __IOSTYPES_H__
#define __IOSTYPES_H__
#include <ioserrno.h>

#define IOS_MESSAGE_BLOCK        0
#define IOS_MESSAGE_NOBLOCK      1

#define IOS_EVENT_AES    0
#define IOS_EVENT_SHA    1
#define IOS_EVENT_USB    2
#define IOS_EVENT_FLASH  3
#define IOS_EVENT_IPC    4
#define IOS_EVENT_ADC    5
#define IOS_EVENT_DAC    6
#define IOS_NUM_EVENTS   64 

/* Emulation only signal definitions */
#define IOS_EVENT_MIN   SIGRTMIN
#define IOS_EVENT_MAX   SIGRTMAX

#define IOS_SEEK_SET     0
#define IOS_SEEK_CURRENT 1
#define IOS_SEEK_END     2

#if defined(_LANGUAGE_C)
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef s32 IOSError;
typedef s32 IOSThreadId;
typedef s32 IOSProcessId;

typedef s32 IOSMessageQueueId;
typedef s32 IOSMessage;
typedef s32 IOSTimerId;

typedef s32 IOSInterfaceId;

typedef s32 IOSCid;

typedef u32 IOSTime;

typedef void (*IOSEntryProc)(u32);

typedef u32 IOSEvent;
#endif

#ifndef NULL
#define NULL 0
#endif 

#endif /*__IOSTYPES_H__*/
