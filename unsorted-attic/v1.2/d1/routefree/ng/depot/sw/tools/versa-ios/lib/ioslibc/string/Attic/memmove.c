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

#include <iostypes.h>
#include "ioslibc.h"

void *
memmove(void *dst, const void *src, size_t n)
{
    char *d = dst;
    const char *s = src;
    if (src < dst && dst < (src + n)) {
        /* Copy overlapping regions backwards */
        d += n;
        s += n;
        while (n--) {
            *--d = *--s;
        }
    } else {
        /* Copy non-overlapping regions just like memcpy */
        while (n--) {
            *d++ = *s++;
        }
    }
    return dst;
}
