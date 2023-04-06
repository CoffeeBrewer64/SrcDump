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

size_t
strnlen(const char *str, size_t n)
{
    const char *s = str;
    while (*s && n-- > 0)
        ++s;
    return s - str;
}
