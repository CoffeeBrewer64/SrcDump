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

char *
strncpy(char *dst, const char *src, size_t n)
{
    char *d = dst;
    const char *s = src;
    while (n > 0) {
        --n;
        if ((*d++ = *s++) == '\0') {
            break;
        }
    }
    while (n-- > 0)
        *d++ = '\0';
    return dst;
}
