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
 *  Function: getchar
 *
 *  Description:
 *      Read a character of input from the terminal
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      The character read from the terminal
 *
 */
int
getchar(void)
{
    return __sys_readc(0);
}
