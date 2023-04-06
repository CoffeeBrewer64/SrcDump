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
 *  Function: puts
 *
 *  Description:
 *      Write a string and a trailing newline to stdout
 *
 *  Inputs:
 *      s - The string to be written
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      >= 0 - Successful completion
 *
 */
int
puts(const char *s)
{
    __sys_write0(s);
    __sys_write0("\n");
    return 0;
}
