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
 *  Function: fseek
 *
 *  Description:
 *      Set the file position indicator for the file pointed
 *      to by 'fp'.
 *
 *  Inputs:
 *      fp - File descriptor
 *      offset - offset in bytes from whence
 *      whence - one of SEEK_SET, SEEK_CUR, or SEEK_END.  Currently
 *               only SEEK_SET is supported
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
fseek(FILE *fp, long offset, int whence)
{
    unsigned long args[2];

    args[0] = (unsigned long) fp;
    args[1] = offset;

    return __sys_seek(args);
}
