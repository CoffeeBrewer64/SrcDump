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
strstr (const char *haystack, const char *needle)
{
    if (*haystack == 0) {
        if (*needle == 0) {
            return (char *)haystack;
        } else {
            return 0;
        }
    }
    while (*haystack) {
        int i = 0;
        while (1) {
            if (needle[i] == 0) {
                return (char *)haystack;
            }
            if (needle[i] != haystack[i]) {
                break;
            }
            ++i;
        }
        ++haystack;
    }
    return 0;
}
