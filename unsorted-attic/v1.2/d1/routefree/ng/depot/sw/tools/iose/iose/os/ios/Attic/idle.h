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
#ifndef __IDLE_H__
#define __IDLE_H__
#include <iostypes.h>

#define IDLE_STACK_SIZE 16*1024
extern u32 __iosIdleStack[IDLE_STACK_SIZE];
void __idleThread(u32 arg);
#endif /* __IDLE_H__ */
