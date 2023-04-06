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

#ifndef __ES_TYPES_H__
#define __ES_TYPES_H__

#if !defined(NEXT_GEN)
#include "types.h"
#endif

typedef u32  ESId;                 /* 32-bit device identity */
typedef u32  ESContentId;          /* 32-bit content identity */
typedef u32  ESTitleId;            /* 32-bit title identity */
typedef u32  ESTicketId;	       /* unique per-device ticket id */
typedef u8   ESVersion;

/* sig and pubKey types */
typedef enum {
    ES_SIG_RSA4096 = 0x00010000,  /* RSA 4096 bit signature */
    ES_SIG_RSA2048,  /* RSA 2048 bit signature */
    ES_SIG_ECC       /* ECC signature 512 bits*/
} ESSigType;

typedef enum {
    ES_PUBKEY_RSA4096,  /* RSA 4096 bit key */
    ES_PUBKEY_RSA2048,  /* RSA 2048 bit key */
    ES_PUBKEY_ECC       /* ECC pub key 512 bits*/
} ESPubKeyType;

/* TMD View */
#define ES_MAX_CONTENT             512
#define ES_ALIGN_CONTENT_SIZE      64

#define ES_CONTENT_RD   1          /* read only content */
#define ES_CONTENT_EX   2          /* executable content */
#define ES_CONTENT_SH   4          /* shared content */

typedef struct {
    ESVersion   version;           /* TMD version */
    ESContentId tmdCid;            /* content id for TMD */
    ESTitleId   titleId;           /* title id */
    u32         numContents;       /* number of contents in the title */
} ESTmdViewHeader;

typedef struct {
    ESContentId cid;               /* content id */
    u16         index;             /* content index */
    u16         type;              /* content type */
    u64         size;              /* content size */
} ESCmdView;

typedef struct {
    ESTmdViewHeader head;
    ESCmdView       contents[ES_MAX_CONTENT];
} ESTmdView;

/* eTicket View */
#define ES_MAX_LIMIT_TYPE   8

typedef u8   ESCidxMask[64];

typedef struct {
    u32        code;               /* limited play algorithm */
    u32        limit;              /* limited play limit */
} ESLpEntry;

typedef struct {
    ESVersion  version;            /* eTicket version */
    ESTicketId ticketId;           /* eTicket ID */
    ESId       deviceId;           /* device ID */
    ESTitleId  titleId;            /* title ID */
    ESCidxMask cidxMask;           /* 512 bits of cidx mask */
    ESLpEntry  limits[ES_MAX_LIMIT_TYPE];  /* limit algorithm and limit */
} ESTicketView;

/* Consumption Counter */
typedef struct {
    u32        revision;
    u32        numCcs; 
} ESCcHeader;

typedef struct {
    ESId       deviceId;
    ESTicketId ticketId;
    u32        limitCode;
    u32        consumption;
} ESCc;

typedef s32 ESError;
typedef enum {
    ES_TRANSFER_SERVER,
    ES_TRANSFER_PEER_DEVICE,
    ES_TRANSFER_BACKUP
} ESTransferType;

#define ES_ERR_OK                                   0
#define ES_ERR_INCORRECT_CERT_TYPE                  -1001
#define ES_ERR_GENKEY_FAILED                        -1002
#define ES_ERR_VERIFY_SIG_FAILED                    -1003
#define ES_ERR_CANNOT_OPEN_FILE                     -1004
#define ES_ERR_INCORRECT_PUBKEY_TYPE                -1005
#define ES_ERR_CERT_ISSUER_MISMATCH                 -1006
#define ES_ERR_ENCRYPTION_FAILED                    -1007
#define ES_ERR_FILE_OPEN_FAILED                     -1008
#define ES_ERR_FILE_READ_FAILED                     -1009
#define ES_ERR_FILE_WRITE_FAILED                    -1010
#define ES_ERR_TMD_NUM_CONTENTS                     -1011
#define ES_ERR_INCORRECT_SIG_TYPE                   -1012
#define ES_ERR_INCORRECT_SIG_LENGTH                 -1013
#define ES_ERR_INCORRECT_CERT_LENGTH                -1014
#define ES_ERR_DEV                                  -1015
#define ES_ERR_MAXFD                                -1016
#define ES_ERR_INVALID                              -1017
#define ES_ERR_FS_CONNECTION_FAILED                 -1018
#define ES_ERR_UNSUPPORTED_TRANSFER_SOURCE          -1019
#define ES_ERR_DEVICE_ID_MISMATCH                   -1020
#define ES_ERR_INCORRECT_CONTENT_SIZE               -1021
#define ES_ERR_HASH_MISMATCH                        -1022
#define ES_ERR_INCORRECT_CONTENT_COUNT              -1023
#define ES_ERR_OUT_OF_MEMORY                        -1024
#define ES_ERR_NO_TMD_FILE                          -1025
#define ES_ERR_NO_RIGHT                             -1026
#define ES_ERR_UNKNOWN                              -1027

#endif /*__ES_TYPES_H__*/
