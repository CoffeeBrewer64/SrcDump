#ident "$Id: test_aes.c,v 1.1 2006/01/12 19:58:46 craig Exp $"
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "aes.h"

extern uint32_t TitleKey[], TitleIv[];

int aes_SwEncryptWrapper(uint8_t *key, uint8_t *initVector, uint8_t *dataIn,
                         uint32_t bytes,uint8_t *dataOut);

int
main(int argc, char *argv[])
{
    uint32_t    i;
    uint32_t    in_buf[1024], out_buf[1024];

    printf ("Old Iv: ");
    for (i = 0; i < 4; i++)
        printf ("0x%x, ", TitleIv[i]);
    printf ("\n");

    for (i = 0; i < 1024;  i++) {
        in_buf[i] = i;
    }
    /*
    aes_SwEncryptWrapper((uint8_t *) &TitleKey, (uint8_t *) &TitleIv,
                   (uint8_t *) in_buf, 4096, (uint8_t *) out_buf);
    */
    aes_SwEncryptWrapper((uint8_t *) &TitleKey, (uint8_t *) &TitleIv,
                   (uint8_t *) in_buf, 2048, (uint8_t *) out_buf);
    aes_SwEncryptWrapper((uint8_t *) &TitleKey, (uint8_t *) &TitleIv,
                   (uint8_t *) (in_buf + 512), 2048, (uint8_t *) (out_buf + 512));
    printf ("New Iv: ");
    for (i = 0; i < 4; i++)
        printf ("0x%x, ", TitleIv[i]);
    printf ("\n");
}
