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
 *  Function: time
 *
 *  Description:
 *      Return the sime since the Epoch (00:00:00 UTC, January 1, 1970),
 *      measured in seconds.
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      t - if 't' is non-NULL the return value is also stored in the memory
 *          pointed to by 't'
 *
 *  Return values:
 *      >= 0 - Time in seconds
 *      < 0 - An error has occurred
 *
 */
int
time(int *t)
{
    int rv = __sys_time();
    if (t) *t = rv;
    return rv;
}
