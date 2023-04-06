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
 *  Function: tmpnam
 *
 *  Description:
 *      Create a unique temporary file name
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      s - Buffer where the file name is to be placed
 *
 *  Return values:
 *      s - Successful completion
 *      NULL - An error has occurred
 *
 */
char *
tmpnam(char *s)
{
    unsigned long args[3];

    args[0] = (unsigned long) s;
    args[1] = 0;
    args[2] = 255;

    return __sys_tmpnam(args) ? 0 : s;
}
