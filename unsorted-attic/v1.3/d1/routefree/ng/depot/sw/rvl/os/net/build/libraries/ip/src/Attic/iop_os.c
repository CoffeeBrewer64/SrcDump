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

/*---------------------------------------------------------------------------*
 * 
 * OS layer on IOP OS
 * 
 *---------------------------------------------------------------------------*/

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#include <stdarg.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <private/eth.h>

#define NET_THREAD_MAX      (SO_SOCKET_MAX + 2)
static OSThread __threads[NET_THREAD_MAX];

void 
OSReport(const char* msg, ...)
{
    va_list marker;

    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
}

void 
OSPanic(const char* file, int line, const char* msg, ...)
{
    va_list marker;

    OSDisableInterrupts();
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    exit(0);
}

OSTime
OSGetTime(void)
{
    return IOS_GetTimer();
}

OSTick  
OSGetTick(void)
{
    return IOS_GetTimer();
}

OSTime __OSGetSystemTime(void)
{
    return IOS_GetTimer();
}

void       
OSInitThreadQueue(OSThreadQueue* queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

void
OSSleepThread(OSThreadQueue* queue)
{
    IOSThreadId threadId = IOS_GetThreadId();
    OSThread *thread = &__threads[threadId];

    thread->threadId = threadId;
    
    if (queue->head == NULL)
    {
        queue->head = thread;
        thread->next = NULL;
        thread->prev = NULL;
    }
    else if (queue->head == queue->tail)
    {
        queue->tail->next = thread;
        queue->tail->prev = thread;
        thread->prev = queue->tail;
        thread->next = queue->tail;
    }
    else
    {
        OSThread *head = queue->head;
        OSThread *tail = queue->tail;

        tail->next = thread;
        thread->prev = tail;

        head->prev = thread;
        thread->next = head;
    }

    queue->tail = thread;
    IOS_StopThread(threadId);
}

void
OSWakeupThread(OSThreadQueue* queue)
{
    OSThread *thread = NULL;

    if (queue->head == NULL)
    {
        return;
    }
    else if (queue->head == queue->tail)
    {
        thread = queue->head;
        
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
    {
        thread = queue->head;

        thread->next->prev = queue->tail;
        queue->tail->next = thread->next;
        
        queue->head = thread->next;
    }

    thread->next = NULL;
    thread->prev = NULL;

    IOS_StartThread(thread->threadId);
}

s32
OSDisableScheduler(void)
{
    return TRUE;
}

s32
OSEnableScheduler(void)
{
    return TRUE;
}

void
OSYieldThread(void)
{
}

void
OSRegisterResetFunction(OSResetFunctionInfo* info)
{
}

void
ETHSetRecvCallback(ETHCallback0 callback0, ETHCallback1 callback1)
{
}

void
ETHSetProtoType(u16 *array, s32 num)
{
}

void
ETHGetMACAddr(u8 *macaddr)
{
    // TODO: the hardcode will be removed after integrating with driver
    u8 MAC_ADDR[] = { 0x00,0x0e,0xc6,0x00,0x00,0x66 };
    memmove(macaddr, MAC_ADDR, 6);
}

void
ETHSetMACAddr( u8* macaddr )
{
}
    
s32
ETHInit(s32 mode)
{
    return ETH_OK;
}

void
ETHSendAsync(void *addr, s32 length, ETHCallback2 callback2)
{
    // TODO: for now, just dumping the packet
    int len     = length;
    u32 *ptr    = (u32*)addr;

    while (len)
    {
        if ( len >= 4 ) len -= 4;
        else len = 0;
        OSDbgReport(("%08X\n",*ptr++));
    }
    OSDbgReport(("\n"));

    if (callback2)
        callback2(0);
}

BOOL
ETHGetLinkStateAsync(BOOL* status)
{
    return FALSE;
}

void
ETHAddMulticastAddress(const u8* macaddr)
{
}

void
ETHClearMulticastAddresses(void)
{
}

void
MD5Final(void)
{
}

void
MD5Init(void)
{
}

void
MD5Update(void)
{
}

s32
EXIGetType ( s32 chan, u32 dev, u32* type )
{
   *type = EXI_ETHER;
   return EXI_ETHER;
}

