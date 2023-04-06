#ifndef __AES_H__
#define __AES_H__

#include <stdint.h>

/*
  aes key expansion for use in setting PI_AES_EKEY for hardware decryption.
  
  arguments
    key: input, 128 bit key
    expkey: output, 44*4 byte expanded key
  returns >=0 on success, -1 on error
*/
int aes_HwKeyExpand(uint8_t *key,uint8_t *expkey);

/*
  aes encryption given the 128 bit key (NOT the expanded key).

  arguments
    key: input, 128 bit key
    initVector: input, 128 bit initialization vector
    dataIn: input, unencrypted data
    bytes: input, number of bytes to be encrypted, must be multiple of 16.
    dataOut: output, encrypted data

  returns >=0 on success, -1 on error
*/
int aes_SwEncrypt(uint8_t *key,uint8_t *initVector,uint8_t *dataIn,uint32_t bytes,uint8_t *dataOut);

int aes_SwEncryptWrapper(uint8_t *key,uint8_t *initVector,uint8_t *dataIn,uint32_t bytes,uint8_t *dataOut);
/*
  aes decryption given the 128 bit key (NOT the expanded key).

  arguments
    key: input, 128 bit key
    initVector: input, 128 bit initialization vector
    dataIn: input, encrypted data
    bytes: input, number of bytes to be decrypted, must be multiple of 16.
    dataOut: output, decrypted data

  returns >=0 on success, -1 on error
*/
int aes_SwDecrypt(uint8_t *key,uint8_t *initVector,uint8_t *dataIn,uint32_t bytes,uint8_t *dataOut);
int aes_SwDecryptWrapper(uint8_t *key,uint8_t *initVector,uint8_t *dataIn,uint32_t bytes,uint8_t *dataOut);

#endif	/* __AES_H__ */
