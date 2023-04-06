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
#ifndef __IOS_TIMER_H__
#define __IOS_TIMER_H__

#include "thread.h"
#include "message.h"
#include "emu_event.h"

#define IOS_TIMER_MAX 8

typedef struct {
    IOSEventState es;
    IOSTime expires;
    IOSTime period; /* only used for periodic timers */
    int nxt;
    int prev;
    u8 type; /* 0 = normal; 1 = periodic */
} IOSTimer_t;

int __iosInitTimers(void); /* 0 on success;  1 on error */
#endif  /* __IOS_TIMER_H__ */
