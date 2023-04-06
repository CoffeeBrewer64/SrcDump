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


#ifndef __BSSTYPES_H__
#define __BSSTYPES_H__


#include <stdint.h>

/*
 * Basic Security Services types
 * Common types for modules using security/DRM primitives
 */

#define BSS_SIG_TYPE_RSA2048  0 /* RSA 2048 bit signature */
#define BSS_SIG_TYPE_RSA4096  1 /* RSA 4096 bit signature */
#define BSS_SIG_TYPE_ECC      2 /* ECC signature */

#define BSS_CONTENT_GAP  0  /* general purpose app */
#define BSS_CONTENT_SAP  1  /* secure app (runs on secure processor)*/

typedef uint32_t  BSSId;                 /* 32-bit Player identity */
typedef uint32_t  BSSHandle;             /* Handle to internal context */
typedef uint32_t  BSSContentId;          /* 32-bit content identity */
typedef uint32_t  BSSTitleId;            /* 32-bit title identity */

typedef uint32_t  BSSAesKey[4];          /* 128-bit AES key */
typedef uint32_t  BSSHmacKey[5];         /* 160-bit key used for HMAC */
typedef uint32_t  BSSAesIv[4];           /* 128-bit AES key */
typedef uint32_t  BSSEccPrivateKey[8];   /* 256-bit Elliptic key */
typedef uint32_t  BSSEccPublicKey[16];   /* X coord, Y coord of elliptic public key */
typedef uint32_t  BSSRsaPublicKey2048[64];   /* 2048-bit RSA public key */
typedef uint32_t  BSSRsaPublicKey4096[128];  /* 4096-bit RSA public key */
typedef uint32_t  BSSRsaExponent;

typedef uint32_t  BSSRsaSig2048[64];    /* 2048-bit RSA signature */
typedef uint32_t  BSSRsaSig4096[128];   /* 4096-bit RSA signature */
typedef uint32_t  BSSEccSig[16];        /* Signature from ECCSign() (X, Y) */
typedef uint32_t  BSSOwnerId;
typedef uint32_t  BSSRandomMix[8];      /* needed for signing along 
                                     with private key */

typedef int16_t  BSSTicketId;	  /* unique per-player ticket id */
/* union for signature field. contents determined by BSS_SIG_TYPE_*.  */
typedef union {                   
    BSSRsaSig2048 rsa2048;  /* BSS_SIG_TYPE_RSA2048 */
    BSSRsaSig4096 rsa4096;  /* BSS_SIG_TYPE_RSA4096 */
    BSSEccSig     ecc;      /* BSS_SIG_TYPE_ECC     */
} BSSGenericSig;

typedef uint32_t  BSSShaHash[5];         /* 160-bit SHA1 hash */

typedef uint8_t   BSSServerName[64];     /* server name, used to describe 
                                    * ascii list heirarchy as: 
                                    *   string with xxxxxxxx representing 
                                    *   serial number in hex. (eg XS0000000f 
                                    *   is ticket server 15). pad with nulls.
                                    *   Root-XSCAxxxxxxxx-XSxxxxxxxx 
                                    *   Root-CPCAxxxxxxxx-CPxxxxxxxx
                                    *   Root-MSCAxxxxxxxx-MSxxxxxxxx
                                    */
typedef uint8_t   BSSName[64];
typedef uint8_t   BSSServerSuffix[64];   /* holds only suffix name for BSSServerName
                                    * (i.e., XSxxxxxxxx, where xxxxxxxx is
                                    * the serial number).
                                    */
typedef BSSServerSuffix   BSSCrlEntry;
typedef uint8_t BSSVersion;

#endif /*__BSSTYPES_H__*/
