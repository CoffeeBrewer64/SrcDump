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

int
memcmp(const void *s1, const void *s2, size_t n)
{
    const u8 *a = s1;
    const u8 *b = s2;

    if (n == 0) {
        return 0;
    }
    while (--n && (*a == *b)) {
        ++a;
        ++b;
    }
    return (*a - *b);
}
