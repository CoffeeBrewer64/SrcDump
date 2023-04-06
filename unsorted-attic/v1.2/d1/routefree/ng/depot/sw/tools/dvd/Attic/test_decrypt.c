#ident "$Id: test_decrypt.c,v 1.1 2006/03/21 22:47:50 craig Exp $"
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

int aes_SwDecryptWrapper(uint8_t *key, uint8_t *initVector, uint8_t *dataIn,
                         uint32_t bytes,uint8_t *dataOut);
uint32_t	blankIv[] = {0x0, 0x0, 0x0, 0x0};
uint8_t		cl_input[] = {0xb4, 0x6e, 0x06, 0x12, 0x61, 0x48, 0xbc};
uint8_t		en_input[] = {0x41, 0xff, 0xcf, 0x55, 0xac};

int
main(int argc, char *argv[])
{
    uint32_t    i;
    uint8_t     out_buf[1024];

    aes_SwEncryptWrapper((uint8_t *) &TitleKey, (uint8_t *) &blankIv,
                          cl_input, sizeof(cl_input), out_buf);

    printf ("Decrypted bytes: ");
    for (i = 0; i < 10; i++)
        printf ("0x%x, ", out_buf[i]);
    printf ("\n");
    exit(1);

    aes_SwDecryptWrapper((uint8_t *) &TitleKey, (uint8_t *) &blankIv,
                          en_input, sizeof(en_input), out_buf);

    printf ("Decrypted bytes: ");
    for (i = 0; i < 1024; i++)
        printf ("0x%x, ", out_buf[i]);
    printf ("\n");
}
