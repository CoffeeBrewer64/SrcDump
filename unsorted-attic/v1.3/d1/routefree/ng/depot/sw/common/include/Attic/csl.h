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
 *
 * csl.h
 * Crypto Services Library Header
 *
 */

#ifndef __CSL_H__
#define __CSL_H__

#include <types.h>

#include "poly_math.h"
#include "sha1.h"


#define CSL_SHA1_BLOCKSIZE		64
#define CSL_SHA1_DIGESTSIZE		20

#define CSL_AES_BLOCKSIZE_BYTES         16
#define CSL_AES_KEYSIZE_BYTES		16
#define CSL_AES_IVSIZE_BYTES 		16
#define CSL_KEY_STRING_LEN              30

/*errors */

typedef enum { CSL_OK = 0, 
               CSL_OVERFLOW, 
               CSL_DIVIDE_BY_ZERO, 
               CSL_SHA_ERROR,
	       CSL_AES_ERROR,
               CSL_BAD_KEY,
               CSL_NULL_POINTER,
	       CSL_VERIFY_ERROR
} CSL_error;

/* 
 * Data types for arguments (Octet Stream or byte stream format)
 */
typedef u8 CSLOSEccPrivateRand[CSL_KEY_STRING_LEN];
typedef u8 CSLOSEccPrivateKey[CSL_KEY_STRING_LEN];
typedef u8 CSLOSEccSharedKey[CSL_KEY_STRING_LEN];
typedef u8 CSLOSEccPublicKey[CSL_KEY_STRING_LEN*2];
typedef u8 CSLOSEccSigRand[CSL_KEY_STRING_LEN];
typedef u8 CSLOSEccSig[CSL_KEY_STRING_LEN*2];
typedef u8 CSLOSEccExpPublicKey[CSL_KEY_STRING_LEN*2*16];

typedef u8 CSLOSRsaPublicKey2048[256];
typedef u8 CSLOSRsaPublicKey4096[512];
typedef u8 CSLOSRsaExponent[4];
typedef u8 CSLOSRsaSig2048[256];
typedef u8 CSLOSRsaSig4096[512];

typedef u8 CSLOSRsaPublicKey[256];
typedef u8 CSLOSRsaSig[256];
typedef u8 CSLOSRsaMsg[256];
typedef u8 CSLOSRsaSecretExp[256];

typedef u8 CSLOSSha1Hash[20];
typedef u8 CSLOSAesKey[16];
typedef u8 CSLOSAesIv[16];
typedef u8 CSLOSHMACKey[20];


/* 
 * Highest Level calls for Elliptic Curve Operations
 */

CSL_error CSL_GenerateEccKeyPair(CSLOSEccPrivateRand rand, 
				 CSLOSEccPrivateKey privateKey,
				 CSLOSEccPublicKey publicKey);
CSL_error CSL_GenerateEccPublicKey(CSLOSEccPrivateKey privateKey,
                                   CSLOSEccPublicKey publicKey);
CSL_error CSL_GenerateEccSharedKey(CSLOSEccPrivateKey privateKey, 
                                   CSLOSEccPublicKey publicKey, 
                                   CSLOSEccSharedKey sharedKey, u32 numBytes);
CSL_error CSL_PrecomputeFour(CSLOSEccPublicKey  publicKey, 
                             CSLOSEccExpPublicKey prePublicKey);
CSL_error CSL_GenerateEccSharedKeyPre(CSLOSEccPrivateKey privateKey, 
                                      CSLOSEccExpPublicKey publicKey, 
                                      CSLOSEccSharedKey sharedKey, 
                                      u32 numBytes);
CSL_error CSL_ComputeEccSig(CSLOSSha1Hash digest, 
                            CSLOSEccPrivateKey private_key, 
                            CSLOSEccSig sign,
                            CSLOSEccSigRand random_data);
CSL_error CSL_VerifyEccSig(CSLOSSha1Hash digest, 
                           CSLOSEccPublicKey public_key, 
                           CSLOSEccSig sign);

/*
 * highest level calls for RSA functions
 */


CSL_error CSL_VerifyRsaSig2048(CSLOSSha1Hash hash, 
                           CSLOSRsaPublicKey2048 certpublickey, 
                           CSLOSRsaSig2048 certsign, 
                           CSLOSRsaExponent certexponent, 
                           u32 expsize);


CSL_error CSL_VerifyRsaSig4096(CSLOSSha1Hash hash, 
                           CSLOSRsaPublicKey4096 certpublickey, 
                           CSLOSRsaSig4096 certsign, 
                           CSLOSRsaExponent certexponent, 
                           u32 expsize);

/* this function can be used for any number of bits by allocating 
 * correct number of bits for public key, sign . Use the above two
 * for 2048, 4096
 * etc.
 */

CSL_error CSL_VerifyRsaSig(CSLOSSha1Hash hash, 
                           CSLOSRsaPublicKey certpublickey, 
                           CSLOSRsaSig certsign, 
                           CSLOSRsaExponent certexponent, 
                           u32 expsize, 
                           u32 keysize);

/* these functions below are for testing only */

void CSL_ComputeRsaSig(CSLOSRsaSig result, 
                       CSLOSRsaMsg paddedmessage, 
                       CSLOSRsaPublicKey certpublickey, 
                       CSLOSRsaSecretExp secretexponent,  
                       u32 keysize);
#if 0
void CSL_ComputeRsaSigFast(u8 *result, u32 *message, 
                           u32 *certpublickey, u32 *certp, 
                           u32 *certq, u32 *dmp, u32 *dmq, 
                           u32 *qinv,  int num_bits);
void CSL_ComputeHmac(u8 *text, u32 text_length, 
                     u8 *key, u32 key_length, 
                     u8 *hmac);
#endif

#endif /* __CSL_H__ */
