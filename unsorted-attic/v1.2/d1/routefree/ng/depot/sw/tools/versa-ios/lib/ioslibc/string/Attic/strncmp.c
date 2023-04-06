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
strncmp(const char *a, const char *b, size_t n)
{
    if (n == 0) {
        return 0;
    }
    while (n-- && (*a == *b)) {
        if (n == 0 || *a == '\0') {
            break;
        }
        ++a;
        ++b;
    }
    return (*(u8 *)a - *(u8 *)b);
}
