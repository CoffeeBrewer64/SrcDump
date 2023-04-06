#ident "$Id: crypto_stub.c,v 1.3 2006/02/25 21:22:06 craig Exp $"
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*
 * Program comments here
 * 
 */

#ifdef RVL
#include "stdint.h"
#include "stdbool.h"
#include "ioslibc.h"
#else
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#include "ios.h"

#include "crypto_stub.h"
#include "sha1.h"

IOSError
IOS_GenerateHash(IOSHashContext *context, void* inputData,
                 uint32_t inputSize, uint32_t chainingFlag,
                 IOSHash *hashData,
                 IOSMessageQueueId mq, IOSMessage mesg)
{
    static SHA1Context   shaContext;

    if (inputSize > 64 * 1024) {
        printf ("Input size is too big - exit\n");
        exit(1);
    }
    if (chainingFlag == 0) {
        SHA1Reset(&shaContext);
    }
    if (inputData != NULL) {
        SHA1Input(&shaContext, inputData, inputSize);
    }

    if (chainingFlag == 2) {
        SHA1Result(&shaContext, (SHA1_BYTE *) hashData);
    }
    return (IOS_ERROR_OK);
}
