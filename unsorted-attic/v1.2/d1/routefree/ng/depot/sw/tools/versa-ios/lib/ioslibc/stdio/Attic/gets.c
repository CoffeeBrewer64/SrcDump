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

#define BUF_SIZE 128

/*
 *  Function: gets
 *
 *  Description:
 *      Read a line from stdin into the buffer pointed to s
 *
 *  Inputs:
 *      s - A buffer to hold the line read from stdin
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      s - Successful completion
 *      NULL - An error has occurred
 *
 */
char *
gets(char *s)
{
    char buf[BUF_SIZE];
    char *dst = s;
    char *src = buf;
    FILE *fp = fopen(":tt", "r");
    fread(buf, BUF_SIZE, 1, fp);
    fclose(fp);

    while (*src && *src != '\n') {
        *dst++ = *src++;
    }
    *dst = 0;

    return s;
}
