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
 *  Function: unlink
 *
 *  Description:
 *      Delete 'pathname' from the filesystem.
 *
 *  Inputs:
 *      pathname - The name of the file to be deleted
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      0 - Successful completion
 *      < 0 - An error has occurred
 *
 */
int
unlink(const char *pathname)
{
    unsigned long args[2];

    args[0] = (unsigned long) pathname;
    args[1] = strnlen(pathname, 255);

    return __sys_remove(args) ? -1 : 0;
}
