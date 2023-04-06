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
 *  Function: flen
 *
 *  Description:
 *      Get the length of the specified file
 *
 *  Inputs:
 *      fp - File descriptor
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      >= 0 - Length of the file
 *      < 0 - An error has occurred
 *
 */
int
flen(FILE *fp)
{
    unsigned long args[1];

    args[0] = (unsigned long) fp;

    return __sys_flen(args);
}
