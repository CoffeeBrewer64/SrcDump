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


#ifndef __ES_INT_H__
#define __ES_INT_H__

#include <iosctypes.h>
#include <iosccert.h>
#include <estypes.h>

/*
 * eTicket services library types
 * Common types for modules using security/DRM primitives
 */

#define ES_RSA_ROOT_KEY_SIZE    4096
#define ES_RSA_SIGNER_KEY_SIZE  2048

#define ES_TMD_VERSION          0
#define ES_TICKET_VERSION       0

#define ES_SYS_DIR              "/sys"
#define ES_TICKET_DIR           "/ticket"
#define ES_TITLE_DIR            "/title"
#define ES_TMP_DIR              "/tmp"
#define ES_TMP_IMP_DIR          "/tmp/import"
#define CERT_SYS_FILE           "/sys/cert.sys"
#define CRL_SYS_FILE            "/sys/crl.sys"

#define ES_TICKET_TITLE_DIR     "/ticket/00000000/00000000"
#define ES_TICKET_TITLE_DEV_DIR "/ticket/00000000/00000000/00000000"
#define ES_TICKET_PATH          "/ticket/00000000/00000000/00000000/00000000.tik"
#define ES_TITLE_ID_DIR         "/title/00000000/00000000"
#define ES_TMD_PATH             "/title/00000000/00000000/meta/00000000.tmd"
#define ES_APP_DIR              "/title/00000000/00000000/content"
#define ES_APP_PATH             "/title/00000000/00000000/content/00000000.app"
#define ES_LEGACY_STATE_PATH    "/title/00000000/00000000/data/legacy.sta"
#define ES_TMP_TITLE_DIR        "/tmp/import/00000000/00000000/"
#define ES_TMP_META_DIR         "/tmp/import/00000000/00000000/meta"
#define ES_TMP_DATA_DIR         "/tmp/import/00000000/00000000/data"
#define ES_TMP_APP_DIR          "/tmp/import/00000000/00000000/content"
#define ES_TMP_APP_PATH         "/tmp/import/00000000//00000000/content/00000000.app"

typedef u8             ESReserved[64];       /* Nintendo reserved info */

typedef IOSCName       ESCrlEntry;

#if defined(LINUX)
#pragma pack(push, 4)
#endif
typedef struct {
    IOSCSigRsa2048   sig;       /* RSA 2048bit sign of the ticket bundle */ 
    IOSCEccPublicKey serverPubKey; /* ticketing server public key */
    IOSCEccPublicPad pad;          /* padding for ecc public key */
    IOSCAesKey       titleKey;  /* published title key. encrypted using a 
                                   common AES key when published, then at 
                                   ticketing time, it's signed by the ticketing
                                   server and re-encrypted using the 
                                   shared key between the server and the 
                                   device */
    ESVersion      version;     /* ticket bundle version number */
    ESVersion      caCrlVersion; /* CA CRL version number */
    ESVersion      signerCrlVersion; /* signer CRL version number */
    u8             dummy; 
    ESTicketId     ticketId;  /* unique 32bit ticket id */
    ESId           deviceId;  /* unique 32bit device id */
    ESReserved     reserved;  /* 64 bytes reserved info for Nintendo */
    ESTitleId      titleId;   /* unique 32bit title id */
    ESCidxMask     cidxMask;  /* bit mask of the content index to 
                                 indicate which content is consumable */
    ESLpEntry      limits[ES_MAX_LIMIT_TYPE];  /* limited play entries */
} ESTicket;

typedef struct {
    ESContentId   cid;    /* 32 bit content id */
    u16           index;  /* content index, unique per title */
    u16           type;   /*  */
    u64           size;   /* unencrypted content size in bytes */
    IOSCSha1Hash hash;   /* 160-bit SHA1 hash of the content */
} ESContentMeta;

typedef struct {
    ESVersion     version;  /* TMD version number */
    ESVersion     titleVersion;  /* title version */
    ESVersion     caCrlVersion;  /* CA CRL version number */ 
    ESVersion     signerCrlVersion; /* signer CRL version number */
    ESSysVersion  sysVersion;  /* required system software version number */

    ESContentId   tmdCid;       /* cid of the TMD */
    ESTitleId     titleId;      /* 32 bit title id */
    ESReserved    reserved;     /* 64 bytes reserved info for Nintendo */
    u32           accessRights; /* title's access rights to use 
                                   system resources */
    u32           numContents;  /* number of contents per title */
    u16           bootIndex;    /* boot content index */
    u16           dummy;
} ESTitleMetaHeader;
#if defined(LINUX)
#pragma pack(pop)
#endif

typedef struct {
    IOSCSigRsa2048     sig;      /* RSA 2048bit sign of all the data in 
                                    the TMD file */
    ESTitleMetaHeader  head;
    ESContentMeta      contents[ES_MAX_CONTENT];
} ESTitleMeta;

#define ES_LEGACY_STATE_BIT_MASK  0x7
#define ES_RTC_BIT_MASK           0x8

#define ES_BLOCK_SIZE        (16*1024)
#define ES_APP_FILE_SUFFIX   "app"

#endif /*__ES_INT_H__*/
