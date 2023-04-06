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
 *  Function: fopen
 *
 *  Description:
 *      Open the specified file
 *
 *  Inputs:
 *      fname - Name of the file
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      >= 0 - File descriptor
 *      < 0 - An error has occurred
 *
 */
FILE *
fopen(const char *fname, const char *mode)
{
    unsigned long args[3];
    int i;
    int rv;
#if 0
    static char *fileModes[] = {"r", "rb", "r+", "r+b", "w", "wb", "w+", "w+b", "a", "ab", "a+", "a+b"};

    for (i = 0; i < sizeof(fileModes)/sizeof(fileModes[0]); ++i) {
        if (!strncmp(fileModes[i], mode, 3)) {
            break;
        }
    }
    if (i == sizeof(fileModes)/sizeof(fileModes[0])) {
        return 0;
    }
#else
    i = 0;
    if (mode[0] == 'w') i+=4;
    if (mode[0] == 'a') i+=8;
    if (mode[1] == 'b') i+=1;
    if (mode[1] == '+') i+=2;
    if (mode[2] == 'b') i+=1;
#endif
    
    args[0] = (unsigned long) fname;
    args[1] = i;
    args[2] = 0;

    while (fname[args[2]] != '\0') {
        args[2]++;
    }

    rv = __sys_open(args);
    return rv != -1 ? (FILE *)rv : 0;
}
