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
 * Memory allocater for the tcp/ip stack
 * 
 *---------------------------------------------------------------------------*/

#include <types.h>
#include <iostypes.h>
#include <ios.h>
#include <ioslibc.h>

#include "dolphin/os.h"

static u8 __heapArea[16 * 1024] ATTRIBUTE_ALIGN(32);
static IOSHeapId  __heapId;

BOOL
initNetMem(void)
{
    __heapId = IOS_CreateHeap(__heapArea, sizeof(__heapArea));
    if (__heapId < 0) {
        printf("%s: cant create heap\n", __FUNCTION__);
        return FALSE;
    }
    return TRUE;
}

void
cleanupNetMem(void)
{
    IOSError ret = IOS_DestroyHeap(__heapId);
    if (ret < 0)
        printf("%s: cant cleanup heap\n", __FUNCTION__);        
}

void * 
OSAlloc(int size)
{
    return IOS_Alloc(__heapId, size);
}

void
OSFree(void *ptr)
{
    IOS_Free(__heapId, ptr);
}

