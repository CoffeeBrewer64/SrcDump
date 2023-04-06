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
 *  Function: putchar
 *
 *  Description:
 *      Write a character to the terminal
 *
 *  Inputs:
 *      c - The character to be written to the terminal
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      c - The character written to the terminal
 *
 */
int
putchar(int c)
{
    char a[] = "\0\0";
    a[0] = c;
    __sys_write0(a);
    return (unsigned char)c;
}
