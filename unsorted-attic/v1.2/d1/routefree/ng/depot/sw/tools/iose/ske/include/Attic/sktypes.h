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
#ifndef __SKTYPES_H__
#define __SKTYPES_H__

#include <ngtypes.h>
#include <skerrno.h>

#define SK_MESSAGE_BLOCK        0
#define SK_MESSAGE_NOBLOCK      1

#define SK_EVENT_AES    0
#define SK_EVENT_SHA    1
#define SK_EVENT_USB    2
#define SK_EVENT_FLASH  3
#define SK_EVENT_IPC    4
#define SK_EVENT_ADC    5
#define SK_EVENT_DAC    6
#define SK_NUM_EVENTS   64 

/* Emulation only signal definitions */
#define SK_EVENT_MIN   SIGRTMIN
#define SK_EVENT_MAX   SIGRTMAX

#define SK_SEEK_SET     0
#define SK_SEEK_CURRENT 1
#define SK_SEEK_END     2

#if defined(_LANGUAGE_C)
typedef s32 SKError;
typedef s32 SKThreadId;
typedef s32 SKProcessId;

typedef s32 SKMessageQueueId;
typedef s32 SKMessage;
typedef s32 SKTimerId;

typedef s32 SKInterfaceId;

typedef s32 SKCid;

typedef u32 SKTime;

typedef void (*SKEntryProc)(u32);

typedef u32 SKEvent;
#endif

#endif /*__SKTYPES_H__*/
