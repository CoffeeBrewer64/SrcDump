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

//#include <stdio.h>
//#include <string.h>
//#include <unistd.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <iostypes.h>
#include <aes_api.h>
#include <aes.h>
#include <sha1.h>


#define DATA_BLK_SIZE	16384
#define AES_BLOCK_SIZE  128
#define AES_BLOCK_SIZE_BYTES 16
#define HASH_SIZE_BYTES 20
#define CHUNK_SIZE 1024

void aes_sw_encrypt(u8 *key, u8 *iv, u8 *data, int size, u8 * cipherTextBytes){
  
    AesKeyInstance expkey;
    AesCipherInstance cipher;
    aesMakeKey(&expkey, AES_DIR_ENCRYPT, AES_BLOCK_SIZE, key);
    aesCipherInit (&cipher, AES_MODE_CBC, iv);
    aesBlockEncrypt(&cipher, &expkey, data, size, cipherTextBytes);
}

void  aes_sw_decrypt(u8 *key, u8 *iv, u8 *cipherTextBytes, int size, u8 *tempblock){

    AesKeyInstance expkey;
    AesCipherInstance cipher;
    aesMakeKey(&expkey, AES_DIR_DECRYPT, AES_BLOCK_SIZE, key);
    aesCipherInit (&cipher, AES_MODE_CBC, iv);
    aesBlockDecrypt(&cipher, &expkey, cipherTextBytes, size, tempblock);
}


void sha_sw(SHA1Context *sha, unsigned char *input, int numblocks, unsigned char *swhash){

  SHA1Reset(sha);
  SHA1SetNoPadding(sha);
  SHA1Input(sha, input, 64 *numblocks);
  SHA1Result(sha, swhash);

}


