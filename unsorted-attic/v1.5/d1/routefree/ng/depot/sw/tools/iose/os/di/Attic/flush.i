#ident "$Id: flush.i,v 1.4 2006/03/26 22:43:16 jprincen Exp $"
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

/*
 * Inlined functions to flush caches and buffers
 */


#ifdef RVL
#include "stdint.h"
#include "ios.h"
#include "iostypes.h"


/* ---------------------------------------------------------------------- */

/*
 * FIXME - This should be a function that does nothing,
 *         as writes to DI register shouldn't need flushing.
 */
static inline void
flushIOPtoDIregister(void* const ptr, const uint32_t num_bytes)
{
    IOS_FlushDCache(ptr, num_bytes);
    IOS_FlushMem(IOS_WB_IOD);
    IOS_InvalidateRdb(IOS_RB_AIM);
}
/* ---------------------------------------------------------------------- */

/*
 * The DI has written data that the IOP cpu needs to read.
 * Do all the necessary flushes to get the data from the drive
 * to the CPU.
 */
static inline void
flushDItoIOP(void* const ptr, const uint32_t numBytes)
{
    if ((numBytes & 0x1F) != 0) {
        printf ("!!! ERROR - flushDItoIOP given %u bytes - not a multiple of 32\n",
                numBytes);
        diFatalError("Non multiple of 32 bytes givn to flushDItoIOP\n");
    }
    // printf ("(flushDItoIOP) doing FlushMem IOS_WB_AIM\n");
    IOS_FlushMem(IOS_WB_AIM);
    // printf ("(flushDItoIOP) doing invalidateRdb IOS_RB_IOD\n");
    IOS_InvalidateRdb(IOS_RB_IOD);
    /*
    printf ("(flushDItoIOP) invalidate d-cache pointer is: 0x%x; num bytes: %u\n",
           ptr, numBytes);
    */
    IOS_InvalidateDCache(ptr, numBytes);
    // printf ("(flushDItoIOP) done\n");
}

/* ---------------------------------------------------------------------- */

/*
 * The DI has written data that the AES unit needs to read.
 * Do all the necessary flushes to get the data from the drive
 * to the AES.
 */
static inline void
flushDItoAES()
{
    IOS_FlushMem(IOS_WB_AIM);
    IOS_InvalidateRdb(IOS_RB_AES);
}

/* ---------------------------------------------------------------------- */

/*
 * The AES  has written data that the SHA unit needs to read.
 * Do all the necessary flushes to get the data from the AES uinit
 * to the SHA.
 */
static inline void
flushAEStoSHA()
{
    IOS_FlushMem(IOS_WB_AES);
    IOS_InvalidateRdb(IOS_RB_SHA);
}
#else

#define flushDItoIOP(x,y)       
#define flushDItoAES()
#endif // ifdef RVL
