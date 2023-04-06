/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IFFifo.c -- contiguous FIFO memory allocation manager

  Copyright 2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IFFifo.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    9     11/15/02 9:44 Shiki
    Fixed not to use macro version of isprint() for SN.

    8     02/07/01 13:21 Shiki
    Modified IFFifoFree() so that it can release the tail part separately
    (to cancel the previous allocation).

    7     4/23/02 9:15 Shiki
    Revised figures in comments.

    6     4/12/02 12:48 Shiki
    Revised IFFifoFree() to check error more strictly.

    5     4/10/02 18:21 Shiki
    Modified IFFifoFree() to fill the released block with ~GARBAGE.

    4     4/10/02 14:11 Shiki
    Revised debug version to fill allocated/released blocks with garbage
    data.

    3     3/22/02 9:00 Shiki
    Modified and now IFFifo can be used with zero-length buffer.

    2     3/18/02 14:12 Shiki
    Clean up.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#endif // IOP_OS

#include <dolphin/os.h>
#include <dolphin/ip.h>
#ifndef IOP_OS
#include <string.h>
#include <ctype.h>
#endif // IOP_OS

#ifdef _DEBUG
#define GARBAGE 0xA3
#endif  // _DEBUG

void IFFifoInit(IFFifo* fifo, void* buff, s32 size)
{
    ASSERT(size == 0 || (buff && 0 < size));
    fifo->size = size;
    fifo->head = fifo->buff = buff;
    fifo->used = 0;
#ifdef GARBAGE
    if (buff && 0 < size)
    {
        memset(buff, 0xff, (u32) size);
    }
#endif
}

static void* FifoAlloc(IFFifo* fifo, s32 len)
{
    s32 free;
    u8* tail;
    u8* end = &fifo->buff[fifo->size];

    ASSERT(0 < len);
    ASSERT(0 <= fifo->used && fifo->used <= fifo->size);
    ASSERT(fifo->buff <= fifo->head && fifo->head <= end);

    if (fifo->size - fifo->used < len)
    {
        return NULL;
    }

    tail = fifo->head + fifo->used;
    if (end <= tail)
    {
        tail -= fifo->size;
    }

    if (fifo->head == tail)
    {
        fifo->head = fifo->buff;
        fifo->used = len;
        return fifo->buff;
    }
    else if (fifo->head < tail)
    {
        //  buff     head    tail     end
        //  |        |       |        |
        //  +--------XXXXXXXX---------+
        free = end - tail;
        if (len <= free)
        {
            fifo->used += len;
            return tail;
        }
        if (len <= fifo->head - fifo->buff)
        {
            fifo->used += free + len;
            return fifo->buff;
        }
    }
    else // (tail < fifo->head)
    {
        //  buff     tail     head    end
        //  |        |        |       |
        //  XXXXXXXXX---------XXXXXXXXX
        ASSERT(fifo->head - tail == fifo->size - fifo->used);
        fifo->used += len;
        return tail;
    }

    return NULL;
}

void* IFFifoAlloc(IFFifo* fifo, s32 len)
{
    void* ptr;

    ptr = FifoAlloc(fifo, len);
#ifdef GARBAGE
    if (ptr)
    {
        memset(ptr, GARBAGE, (u32) len);
    }
#endif
    ASSERT(fifo->used <= fifo->size);
    return ptr;
}

BOOL IFFifoFree(IFFifo* fifo, void* ptr, s32 len)
{
    u8* p = ptr;
    u8* end = &fifo->buff[fifo->size];
    u8* head;
    u8* tail;

    ASSERT(0 <= fifo->used && fifo->used <= fifo->size);
    ASSERT(fifo->buff <= fifo->head && fifo->head < end);

    if (len <= 0 || fifo->used < len ||
        p == NULL || p < fifo->buff || end <= p)
    {
        return FALSE;
    }

    tail = fifo->head + fifo->used;
    if (end <= tail)
    {
        tail -= fifo->size;
    }

    // new head position
    head = p + len;
    if (end <= head)
    {
        head -= fifo->size;
    }
    if (head < fifo->buff || end <= head)
    {
        return FALSE;
    }

    if (fifo->head == tail)
    {
        //           tail
        //  buff     head             end
        //  |        |                |
        //  XXXXXXXXXXXXXXXXXXXXXXXXXXX
        if (fifo->head < head)
        {
            if (head <= p || p < fifo->head)
            {
                return FALSE;
            }
#ifdef GARBAGE
            memset(fifo->head, ~GARBAGE, (u32) (head - fifo->head));
#endif
        }
        else if (head <= p && p < fifo->head)
        {
            return FALSE;
        }
        else
        {
            if (head == tail)
            {
#ifdef GARBAGE
                memset(p, ~GARBAGE, (u32) len);
#endif
                fifo->used -= len;
                return TRUE;
                // NOT REACHED HERE
            }

#ifdef GARBAGE
            memset(fifo->head, ~GARBAGE, (u32) (end - fifo->head));
            memset(fifo->buff, ~GARBAGE, (u32) (head - fifo->buff));
#endif
        }
    }
    else if (fifo->head < tail)
    {
        //  buff     head    tail     end
        //  |        |       |        |
        //  +--------XXXXXXXX---------+
        if (head <= p || p < fifo->head || tail < head)
        {
            return FALSE;
        }

        if (head == tail)
        {
#ifdef GARBAGE
            memset(p, ~GARBAGE, (u32) len);
#endif
            fifo->used -= len;
            return TRUE;
            // NOT REACHED HERE
        }

#ifdef GARBAGE
        memset(fifo->head, ~GARBAGE, (u32) (head - fifo->head));
#endif
    }
    else
    {
        //  buff     tail     head    end
        //  |        |        |       |
        //  XXXXXXXXX---------XXXXXXXXX
        if (fifo->head < head)
        {
            if (head <= p || p < fifo->head)
            {
                return FALSE;
            }
#ifdef GARBAGE
            memset(fifo->head, ~GARBAGE, (u32) (head - fifo->head));
#endif
        }
        else if (tail < head)
        {
            return FALSE;
        }
        else if (head <= p && p < fifo->head)
        {
            return FALSE;
        }
        else
        {
            if (head == tail)
            {
#ifdef GARBAGE
                memset(p, ~GARBAGE, (u32) len);
#endif
                fifo->used -= len;
                return TRUE;
                // NOT REACHED HERE
            }
#ifdef GARBAGE
            memset(fifo->head, ~GARBAGE, (u32) (end - fifo->head));
            memset(fifo->buff, ~GARBAGE, (u32) (head - fifo->buff));
#endif
        }
    }

    if (head <= tail)
    {
        fifo->used = tail - head;
    }
    else
    {
        fifo->used = (end - head) + (tail - fifo->buff);
    }
    ASSERT(fifo->used < fifo->size);
    fifo->head = head;

    return TRUE;
}

// For debugging
void IFDump(void* ptr, s32 len)
{
    int j;
    int i;
    int n;

    for (j = 0; j < len; j += 16)
    {
        n = len - j;
        if (16 < n)
        {
            n = 16;
        }

        OSReport("%08x: ", j);
        for (i = 0; i < n; i++)
        {
            OSReport("%02x ", ((u8*) ptr)[j + i]);
        }

        for (; i < 16; i++)
        {
            OSReport("   ");
        }

#ifndef IOP_OS
        OSReport("  ");
        for (i = 0; i < n; i++)
        {
            OSReport("%c", (isprint)(((u8*) ptr)[j + i]) ? ((u8*) ptr)[j + i] : '.');
        }
#endif // IOP_OS
        
        OSReport("\n");
    }
}
