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
 *  Function: fread
 *
 *  Description:
 *      Read the specified number of elements from the file.
 *      This function returns an error if the number of
 *      bytes left since the last read is less than the
 *      number of bytes requested
 *
 *  Inputs:
 *      fp - File descriptor
 *      nmemb - Number of members to read
 *      size - Size of member
 *
 *  Outputs:
 *      ptr - Buffer where the content is to be placed
 *
 *  Return values:
 *      0 - Successful completion
 *      < 0 - An error has occurred
 *
 */
int
fread(void *ptr, int size, int nmemb, FILE *fp)
{
    unsigned long args[3];
    unsigned long len = size * nmemb;

    args[0] = (unsigned long) fp;
    args[1] = (unsigned long) ptr;
    args[2] = len;
    if (__sys_read(args) != 0) {
        return 0;
    }

    return nmemb;
}
