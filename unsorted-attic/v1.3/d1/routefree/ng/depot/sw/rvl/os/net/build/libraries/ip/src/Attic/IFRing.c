/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IFRing.c -- ring buffer helper functions

  Copyright 2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IFRing.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    7     8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    6     7/30/03 18:38 Shiki
    Fixed IFRingInEx().

    5     8/05/02 11:02 Shiki
    Implemented IFRingInEx().

    4     4/23/02 9:41 Shiki
    Added detailed comments.

    3     4/10/02 18:34 Shiki
    Revised IFRingGet() interface.

    2     3/22/02 9:01 Shiki
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
#endif // IOP_OS

#define MIN(a, b)               (((a) < (b)) ? (a) : (b))
#define MAX(a, b)               (((a) > (b)) ? (a) : (b))
#define POS(head, ptr, size)    (((head) <= (ptr)) ? ((ptr) - (head)) : ((ptr) + (size) - (head)))

/*---------------------------------------------------------------------------*
  Name:         IFRingIn

  Description:  Moves data to the ring buffer.

  Arguments:    buf     Pointer to the ring buffer
                size    The size of the ring buffer in bytes
                head    Pointer to the head of data in the ring buffer
                used    The number of filled bytes in the ring buffer
                data    Pointer to data to be copied-in
                len     The length of the data in bytes

  Returns:      Pointer to the new head
 *---------------------------------------------------------------------------*/
u8* IFRingIn(u8* buf, s32 size, u8* head, s32 used,
             const u8* data, s32 len)
{
    u8* end;
    u8* tail;
    s32 free;

    ASSERT(used + len <= size);
    end = buf + size;
    ASSERT(buf <= head && head < end);
    tail = head + used;
    if (end <= tail)
    {
        tail -= size;
    }

    if (head <= tail)
    {
        //  buf      head         tail      end
        //  |        |            |         |
        //  +--------XXXXXXXXXXXXX----------+
        free = end - tail;
        if (len <= free)
        {
            memmove(tail, data, (u32) len);
            return head;
        }
        else
        {
            memmove(tail, data, (u32) free);
            data += free;
            len  -= free;
            memmove(buf, data, (u32) len);
            return head;
        }
    }
    else // (tail < head)
    {
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        memmove(tail, data, (u32) len);
        return head;
    }
}

/*---------------------------------------------------------------------------*
  Name:         IFRingOut

  Description:  Moves data from the ring buffer.

  Arguments:    buf     Pointer to the ring buffer
                size    The size of the ring buffer in bytes
                head    Pointer to the head of data in the ring buffer
                used    The number of filled bytes in the ring buffer
                data    Pointer to copy-out data buffer
                len     The size of the copy-out data buffer in bytes

  Returns:      Pointer to the new head
 *---------------------------------------------------------------------------*/
u8* IFRingOut(u8* buf, s32 size, u8* head, s32 used,
              u8* data, s32 len)
{
#ifdef IOP_OS
    TCPIP_UNUSED(used);
#else    
#ifdef NDEBUG
    #pragma unused(used)
#endif
#endif // IOP_OS
    u8* end;

    ASSERT(len <= used);
    end = buf + size;
    ASSERT(buf <= head && head < end);

    if (head + len < end)
    {
        //  buf      head         tail      end
        //  |        |            |         |
        //  +--------XXXXXXXXXXXXX----------+
        //  |        |<- len ->|            |
        memmove(data, head, (u32) len);
        head += len;
    }
    else    // (end <= head + len)
    {
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        //  +->|              |<--- len ----+
        //
        //                or
        //
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        //  |                 |<--- len --->|
        s32 front = end - head;

        ASSERT(front <= len);
        memmove(data, head, (u32) front);
        data += front;
        len  -= front;
        head = buf;
        memmove(data, head, (u32) len);
        head += len;
    }
    ASSERT(buf <= head && head < end);
    return head;
}

/*---------------------------------------------------------------------------*
  Name:         IFRingGet

  Description:  Sets up the first len bytes from the ring buffer to vec[2].

  Arguments:    buf     Pointer to the ring buffer
                size    The size of the ring buffer in bytes
                head    Pointer to the head of data in the ring buffer
                used    The number of filled bytes in the ring buffer
                vec     Pointer to IFVec{} array
                len     The number of elements in the vec array

  Returns:      The number of filled vec{}s (upto 2)
 *---------------------------------------------------------------------------*/
int IFRingGet(u8* buf, s32 size, u8* head, s32 used,
              IFVec* vec, s32 len)
{
#ifdef IOP_OS
    TCPIP_UNUSED(used);
#else
#ifdef NDEBUG
    #pragma unused(used)
#endif
#endif // IOP_OS
    u8* end;
    
    ASSERT(len <= used);
    end = buf + size;

    if (end <= head) // in case head is offset.
    {
        head -= size;
    }
    ASSERT(buf <= head && head < end);

    if (head + len <= end)
    {
        //  buf      head         tail      end
        //  |        |            |         |
        //  +--------XXXXXXXXXXXXX----------+
        //  |        |<- len ->|            |
        //
        //                or
        //
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        //  |                 |<--- len --->|
        vec->data = head;
        vec->len  = len;
        return 1;
    }
    else    // (end < head + len)
    {
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        //  +->|              |<--- len ----+
        s32 front = end - head;

        ASSERT(front < len);
        vec->data = head;
        vec->len  = front;
        ++vec;
        vec->data = buf;
        vec->len  = len - front;
        return 2;
    }
}

/*---------------------------------------------------------------------------*
  Name:         IFRingPut

  Description:  Release the first len bytes from the ring buffer

  Arguments:    buf     Pointer to the ring buffer
                size    The size of the ring buffer in bytes
                head    Pointer to the head of data in the ring buffer
                used    The number of filled bytes in the ring buffer
                len     The size of the data to release

  Returns:      Pointer to the new head
 *---------------------------------------------------------------------------*/
u8* IFRingPut(u8* buf, s32 size, u8* head, s32 used,
              s32 len)
{
#ifdef IOP_OS
    TCPIP_UNUSED(used);
#else
#ifdef NDEBUG
    #pragma unused(used)
#endif
#endif // IOP_OS
    u8* end;

    ASSERT(len <= used);
    end = buf + size;
    ASSERT(buf <= head && head < end);

    if (head + len < end)
    {
        //  buf      head         tail      end
        //  |        |            |         |
        //  +--------XXXXXXXXXXXXX----------+
        //  |        |<- len ->|            |
        head += len;
    }
    else    // (end <= head + len)
    {
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        //  +->|              |<--- len ----+
        //
        //                or
        //
        //  buf      tail     head         end
        //  |        |        |             |
        //  XXXXXXXXX---------XXXXXXXXXXXXXXX
        //  |                 |<--- len --->|
        head = buf + len - (end - head);
    }
    ASSERT(buf <= head && head < end);
    return head;
}

/*---------------------------------------------------------------------------*
  Name:         IFRingInEx

  Description:  Moves data to the ring buffer with keeping above sequence
                data.

  Arguments:    buf         Pointer to the ring buffer
                size        The size of the ring buffer in bytes
                head        Pointer to the head of data in the ring buffer
                used        The number of filled bytes in the ring buffer
                offset      Offset from the tail of data in the ring buffer
                data        Pointer to data to be copied-in
                len         The length of the data in bytes
                blocks      Array of IFBlock{}s
                maxblock    # of IFBlock{}s

  Returns:      Pointer to the new head
 *---------------------------------------------------------------------------*/

static s32 MargeBlock(u8* ptr, s32 len,
                      IFBlock* blockTable, s32 maxblock,
                      s32 size, u8* tail)
{
    IFBlock* block;
    IFBlock* end;
    s32      pl;    // pos left
    s32      pr;    // pos right
    s32      pb;    // pos block

    ASSERT(1 < maxblock && blockTable);
    ASSERT(0 <= len);

    pl = POS(tail, ptr, size);
    pr = pl + len;

    end = &blockTable[maxblock];

    if (tail == ptr)
    {
        for (block = blockTable; block < end && block->ptr; )
        {
            pb = POS(tail, block->ptr, size);
            if (pb <= pr)
            {
                pr = MAX(pb + block->len, pr);
                len = pr - pl;
                // Delete block
                memmove(block, block + 1, (u32) ((u8*) end - (u8*) (block + 1)));
                memset(end - 1, 0, sizeof(IFBlock));
                continue;
            }
            ++block;
        }
        return len;
    }

    // tail != ptr
    for (block = blockTable; block < end && block->ptr; )
    {
        pb = POS(tail, block->ptr, size);
        if (pl <= pb + block->len && pb <= pr)
        {
            pr = MAX(pb + block->len, pr);
            if (pb < pl)
            {
                pl = pb;
                ptr = block->ptr;
            }
            len = pr - pl;
            // Delete block
            memmove(block, block + 1, (u32) ((u8*) end - (u8*) (block + 1)));
            memset(end - 1, 0, sizeof(IFBlock));
            continue;
        }
        ++block;
    }
    if (block < end)
    {
        ASSERT(block->ptr == NULL);
        block->ptr = ptr;
        block->len = len;
    }
    else
    {
        // Append new block after removing the oldest one
        memmove(blockTable, blockTable + 1, (u32) ((u8*) end - (u8*) (blockTable + 1)));
        block = end - 1;
        block->ptr = ptr;
        block->len = len;
    }
    return 0;
}

u8* IFRingInEx(u8* buf, s32 size, u8* head, s32 used,
               s32 offset, const u8* data, s32* adv,
               IFBlock* blockTable, s32 maxblock)
{
    u8* end;
    u8* tail;
    u8* ptr;
    s32 len = *adv;
    s32 free;

    if (len == 0)
    {
        return head;
    }

    ASSERT(0 <= offset);
    ASSERT(used + offset + len <= size);
    end = buf + size;
    ASSERT(buf <= head && head < end);
    tail = head + used;
    if (end <= tail)
    {
        tail -= size;
    }

    ASSERT(offset < size);
    ptr = tail + offset;
    if (end <= ptr)
    {
        ptr -= size;
    }

    if (head <= ptr)
    {
        //  buf      head    tail ptr      end
        //  |        |       |    |         |
        //  +--------XXXXXXXXOOOOO----------+
        free = end - ptr;
        if (len <= free)
        {
            memmove(ptr, data, (u32) len);
        }
        else
        {
            memmove(ptr, data, (u32) free);
            memmove(buf, data + free, (u32) len - free);
        }
    }
    else // (ptr < head)
    {
        //  buf tail ptr      head         end
        //  |   |    |        |             |
        //  XXXXOOOOO---------XXXXXXXXXXXXXXX
        memmove(ptr, data, (u32) len);
    }

    *adv = MargeBlock(ptr, len, blockTable, maxblock, size, tail);
    return head;
}
