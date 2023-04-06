#ident "$Id: dvd_mem.c,v 1.4 2006/01/30 22:14:43 craig Exp $"
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
 * Memory allocater for the DI driver.
 * NOTE: memory can only be allocated and not freed,
 * except if all memory is freed.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "iostypes.h"
#include "ios.h"

static  uint8_t         *current_free_ptr, *current_end_ptr;

/* ----------------------------------------------------------------- */

void
initDvdMemAlloc(void)
{
    current_free_ptr = IOS_Alloc(1);
    if (current_free_ptr == NULL) {
        fprintf(stderr, "Error: can't allocate space for dvd mem allocated - exit\n");
        exit(1);
    }
    current_end_ptr = current_free_ptr + IOS_DDR_PAGE_SIZE;
}

/* ----------------------------------------------------------------- */

/*
 * Allocate memory of size 'size'.
 * RETURNS: a pointer to the allocated memory, or
 *          NULL if the request could not be fulfilled
 */
void *
dvdMemAlloc(uint32_t size)
{
    void        *return_val;

    /* Round up allocations to a multiple of 8 for alignment purposes */
    if (size % 8 != 0) {
        size += 8;
        size &= ~0x7;
    }

    /*
     * Check to see if the size of the memory requested fits in
     * the unallocated space.  If so, take the memory from the
     * current unallocated space.  If not, allocate more memory.
     */
    if ((uint32_t) current_free_ptr + size > (uint32_t) current_end_ptr) {
        int numPages2Alloc;

        if (size > IOS_DDR_PAGE_SIZE) {
            numPages2Alloc = size / IOS_DDR_PAGE_SIZE;
            if (size % IOS_DDR_PAGE_SIZE != 0) {
                numPages2Alloc++;
            }
        }
        else {
            numPages2Alloc = 1;
        }
        return_val = IOS_Alloc(numPages2Alloc);
        if (return_val == NULL) {
            return(NULL);
        }
        current_end_ptr = return_val + (numPages2Alloc * IOS_DDR_PAGE_SIZE);
        current_free_ptr = return_val + size;
    } else {
        return_val = current_free_ptr;
        current_free_ptr += size;
    }
    return ( (void *) return_val);
}

/* ----------------------------------------------------------------- */
