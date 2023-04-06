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
 *  Function: rename
 *
 *  Description:
 *      Rename a file from 'oldpath' to 'newpath'.
 *
 *  Inputs:
 *      oldpath - The name of the file to be renamed
 *      newpath - The new name for the file
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
rename(const char *oldpath, const char *newpath)
{
    unsigned long args[4];

    args[0] = (unsigned long) oldpath;
    args[1] = strnlen(oldpath, 255);
    args[2] = (unsigned long) newpath;
    args[3] = strnlen(newpath, 255);

    return __sys_rename(args) ? -1 : 0;
}
