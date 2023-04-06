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
 *  Function: scanf
 *
 *  Description:
 *      Match inputs to a format string. Currently only one
 *      match can be specified and only the types %s and %d
 *      are supported. The maximum size of input is
 *      (BUF_SIZE - 1) characters
 *
 *  Inputs:
 *      fmt - Format string
 *      ... - Variable number of arguments
 *
 *  Outputs:
 *      The matched values are placed into the location
 *      specified
 *
 *  Return values:
 *      0 - Successful completion
 *
 */
int
scanf(const char *fmt, ...)
{
    int rc = 0, count = 0, *num_p;
    FILE *fp = 0;
    va_list ap;
    char c = '\0', in[BUF_SIZE], *str;

    /* Read string from console */
    fp = fopen(":tt", "r");
    fread(in, BUF_SIZE, 1, fp);
    fclose(fp);

    va_start(ap, fmt);

    /* Only the strings "%d" and "%s" are supported now */
    while ((c = *fmt++)) {
        if (c == '%') {
            switch ((c = *fmt++)) {
            case 's':
                str = va_arg(ap, char *);
                memcpy(str, in, count + 1);

                break;

            case 'd':
                num_p = va_arg(ap, int *);
                *num_p = 0;

                count = 0;
                while (in[count] && in[count] != '\n') {
                    if ((in[count] - '0') < 10) {
                        *num_p = (*num_p * 10) + (in[count] - '0');
                    }

                    count++;
                }

                break;

            default:
                rc = -1;
                goto scanf_out;
            }
        } else {
            rc = -1;
            goto scanf_out;
        }
    }

    va_end(ap);

scanf_out:

    return (rc);
}
