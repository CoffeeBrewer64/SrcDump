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

#include "ioslibc.h"
#include "aes.h"
#include "aes_api.h"


#define BLOCK_SIZE 128
#define FILE_SIZE 512

/* aes lengths in bits as used by pi */
#define PI_AES_KEYLEN     (sizeof(BbAesKey)*8)
#define PI_AES_BLOCKLEN   (sizeof(BbAesKey)*8)

typedef u32 BbAesKey[4];	/* 128-bit AES Key */

/*
  returns >=0 on success, -1 on error
  ***********************************
  use this only for HW
  for software encryption and decryption, the 
  key expansion is included
  if key is in ascii isAscii = 1, else 0
  ***********************************

*/
int aes_HwKeyExpand(u8 *key,u8 *expkey)
{
    AesKeyInstance keyI;

    if(aesMakeKey(&keyI, AES_DIR_DECRYPT, PI_AES_KEYLEN, key) != AES_TRUE){
        return -1;
    }

    /* scan for creating expanded key in form used by pi */
    memcpy(expkey, keyI.rk, 44*4);
    return 0;
}

/*************************************
 * Use this only for software (Key expansion included)
 * isAscii = 1 means initVector and key are in ascii
 *************************************
 */
int aes_SwEncrypt(u8 *key,u8 *initVector,u8 *dataIn,u32 bytes,u8 *dataOut)
{
    AesKeyInstance keyI;
    AesCipherInstance cipher;
    int error;

    /* make key */
    if(aesMakeKey(&keyI, AES_DIR_ENCRYPT, PI_AES_KEYLEN, key) != AES_TRUE){
        return -1;
    }

    /* initialise parameters */
    error = aesCipherInit(&cipher, AES_MODE_CBC, initVector);
    if (error != AES_TRUE) {
        /*
        fprintf(stderr,"cipherInit error %d \n", error);
        */
        return -1;
    }

    /*encrypt */
    if(aesBlockEncrypt(&cipher, &keyI, dataIn, bytes*8, dataOut)
       != bytes*8){
/*
        fprintf(stderr, "cipher encryption error \n");
*/
        return -1;
    }

    return 0;
}


/*************************************
 * Use this only for software (Key expansion included)
 * isAscii = 1 means key and IV are in ascii
 *************************************
 */

int aes_SwDecrypt(u8 *key,u8 *initVector,u8 *dataIn,u32 bytes,u8 *dataOut)
{
    AesKeyInstance keyI;
    AesCipherInstance cipher;
    int error;

    /* make key */
    if(aesMakeKey(&keyI, AES_DIR_DECRYPT, PI_AES_KEYLEN, key) != AES_TRUE){
        return -1;
    }

    /* initialise parameters */
    error = aesCipherInit(&cipher, AES_MODE_CBC, initVector);
    if (error != AES_TRUE) {
/*
        fprintf(stderr,"cipherInit error %d \n", error);
*/
        return -1;
    }

    /*encrypt */
    if(aesBlockDecrypt(&cipher, &keyI, dataIn, bytes*8, dataOut) != bytes*8){
/*
        fprintf(stderr, "cipher encryption error \n");
*/
        return -1;
    }

    return 0;
}
