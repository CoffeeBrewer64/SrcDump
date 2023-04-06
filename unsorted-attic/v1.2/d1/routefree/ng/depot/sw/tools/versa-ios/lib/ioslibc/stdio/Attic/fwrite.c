/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *      This file implements standard IO functions using semi-hosting
 *
 */


#include <stdarg.h>

#include "ioslibc.h"
#include "../vio.h"

/*
 *  Function: fwrite
 */
int
fwrite(void *ptr, int size, int nmemb, FILE *fp)
{
    unsigned long args[3];
    unsigned long len = size * nmemb;

    args[0] = (unsigned long) fp;
    args[1] = (unsigned long) ptr;
    args[2] = len;
    if (__sys_write(args) != 0) {
        return 0;
    }

    return nmemb;
}
