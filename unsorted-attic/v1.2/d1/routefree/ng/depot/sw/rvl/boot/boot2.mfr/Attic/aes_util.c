/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: aes_util.c,v 1.1 2006/05/05 23:43:06 cnguyen Exp $
 */

#include <iostypes.h>
#include <iop.h>
#include <ios.h>
#include <ioslibc.h>
#include <iosc.h>

#include "boot2.h"

extern unsigned char bootKey[];
extern unsigned char bootIv[];

IOSCSecretKeyHandle Handle;

/*
 * init_aes
 *
 * Create and initialise an encryption object.
 */
IOSError
init_aes(void)
{
    IOSError rc = IOS_ERROR_OK;
    u32 type = IOSC_SECRETKEY_TYPE;
    u32 subtype = IOSC_ENC_SUBTYPE;
    u32 keysize;

    printf ("%s: 0x%08x %d %d\n",
            __FUNCTION__, (u32)&Handle, type, subtype);

    rc = IOSC_CreateObject(&Handle, type, subtype);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: bad IOSC_CreateObject %d\n",
                __FUNCTION__, rc);
    }
    IOSC_GetKeySize(&keysize, Handle);
    printf ("%s: Handle 0x%08x key size %d\n",
            __FUNCTION__, (u32)Handle, keysize);

    rc = IOSC_ImportSecretKey(Handle, 0, 0, 
                              IOSC_NOSIGN_NOENC, 0, 0, &bootKey[0]);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: bad IOSC_ImportSecretKey %d\n",
                __FUNCTION__, rc);
        return rc;
    }

    BOOT2_EXIT();

    return rc;
}

/*
 * aes_decode
 *
 * Decrypt a block of data in memory.
 */
IOSError
aes_decode(u8 *inputData, u32 inputSize, u8 *outputData)
{
    IOSError rc = IOS_ERROR_OK;

    BOOT2_ENTRY();

    rc = IOSC_Decrypt(Handle, &bootIv[0], inputData, inputSize, outputData);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: bad IOSC_Decrypt %d\n",
                __FUNCTION__, rc);
        return rc;
    }

    BOOT2_EXIT();

    return rc;
}

/* eof */
