/*
#include "clibutil.h"
*/

#include <stdint.h>
#include <string.h>

#include "bsstypes.h"
#include "aes.h"
#include "aes_api.h"


#define BLOCK_SIZE 128
#define FILE_SIZE 512

/* aes lengths in bits as used by pi */
#define PI_AES_KEYLEN     (sizeof(BSSAesKey)*8)
#define PI_AES_BLOCKLEN   (sizeof(BSSAesKey)*8)


/*
  returns >=0 on success, -1 on error
  ***********************************
  use this only for HW
  for software encryption and decryption, the 
  key expansion is included
  if key is in ascii isAscii = 1, else 0
  ***********************************

*/
int aes_HwKeyExpand(uint8_t *key,uint8_t *expkey)
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
 * Wrapper to return the new IV needed for chained encryptions
 *************************************
 */
int aes_SwEncryptWrapper(uint8_t *key, uint8_t *initVector, uint8_t *dataIn,
                         uint32_t bytes,uint8_t *dataOut)
{
    int         numOldIvBytes;
    int         returnVal;

    returnVal = aes_SwEncrypt(key, initVector, dataIn, bytes, dataOut);
    if (bytes < 16) {
        numOldIvBytes = 16 - bytes;
        memmove(initVector, initVector + bytes, numOldIvBytes);
        memcpy(initVector + numOldIvBytes, dataOut, bytes);
    }
    else {
        memcpy(initVector, dataOut + (bytes - 16), 16);
    }
    return(returnVal);
}


/*************************************
 * Use this only for software (Key expansion included)
 * isAscii = 1 means initVector and key are in ascii
 *************************************
 */
int aes_SwEncrypt(uint8_t *key,uint8_t *initVector,uint8_t *dataIn,uint32_t bytes,uint8_t *dataOut)
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

int aes_SwDecrypt(uint8_t *key,uint8_t *initVector,uint8_t *dataIn,uint32_t bytes,uint8_t *dataOut)
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

/*************************************
 * Wrapper to return the new IV needed for chained decryptions
 *************************************
 */
int aes_SwDecryptWrapper(uint8_t *key, uint8_t *initVector, uint8_t *dataIn,
                         uint32_t bytes,uint8_t *dataOut)
{
    int         numOldIvBytes;
    int         returnVal;

    returnVal = aes_SwDecrypt(key, initVector, dataIn, bytes, dataOut);
    if (bytes < 16) {
        numOldIvBytes = 16 - bytes;
        memmove(initVector, initVector + bytes, numOldIvBytes);
        memcpy(initVector + numOldIvBytes, dataOut, bytes);
    }
    else {
        memcpy(initVector, dataOut + (bytes - 16), 16);
    }
    return(returnVal);
}
