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

#include "estypes.h"
#include "csl.h"

/*
 * eTicket services library types
 * Common types for modules using security/DRM primitives
 */

#define ES_RSA_ROOT_KEY_SIZE    4096
#define ES_RSA_SIGNER_KEY_SIZE  2048
#define ES_RSA_EXPONENT         0x10001
#define ES_ROOT_NAME            "Root"
#define ES_CA_PREFIX            "CA"
#define ES_XS_PREFIX            "XS"
#define ES_MS_PREFIX            "MS"
#define ES_CP_PREFIX            "CP"
#ifdef NET_CARD
#define ES_DV_PREFIX            "NC"
#else
#define ES_DV_PREFIX            ""
#endif

#define ES_TMD_VERSION          (1)
#define ES_TICKET_VERSION       (1)

#define ES_SYS_DIR              "/sys"
#define ES_SYS_TITLE_DIR        "/sys/title"
#define ES_TITLE_DIR            "/title"
#define ES_TMP_DIR              "/tmp"
#define ES_TMP_IMP_DIR          "/tmp/import"
#define CERT_SYS_FILE           "/sys/cert.sys"

#define ES_TICKET_DIR           "/sys/title/00000000"
#define ES_TICKET_DEV_DIR       "/sys/title/00000000/00000000"
#define ES_TICKET_PATH          "/sys/title/00000000/00000000/00000000.tik"
#define ES_TMD_PATH             "/sys/title/00000000/00000000.tmd"
#define ES_APP_DIR              "/title/00000000/content"
#define ES_APP_PATH             "/title/00000000/content/00000000.app"
#define ES_TMP_APP_DIR          "/tmp/import/00000000/content"
#define ES_TMP_APP_PATH         "/tmp/import/00000000/content/00000000.app"

typedef u8   ESName[64];           /* cert chain name, used to describe 
                                    * ascii list heirarchy as: 
                                    *   string with xxxxxxxx representing 
                                    *   serial number in hex. (eg XS0000000f 
                                    *   is ticket server 15). pad with nulls.
                                    *   Root-CAxxxxxxxx-XSxxxxxxxx 
                                    *   Root-CAxxxxxxxx-CPxxxxxxxx
                                    *   Root-CAxxxxxxxx-MSxxxxxxxx
                                    *   Root-CAxxxxxxxx-MSxxxxxxxx-NCxxxxxxxx
                                    */
typedef u8   ESServerId[64];       /* holds only suffix name for ESServerName
                                    * (i.e., XSxxxxxxxx, where xxxxxxxx is
                                    * the serial number). */
typedef u8   ESDeviceId[64];       /* device ID in the form of NCxxxxxxxx */

typedef u8   ESReserved[64];       /* Nintendo reserved info */

/* various padding to make things 64 byte aligned */
typedef u8   ESSigDummy[60];
typedef u8   ESCertPad[48];
typedef u8   ESEccCertPad[8];

typedef struct {
    ESSigType       sigType;
    CSLOSRsaSig4096 sig;
    ESSigDummy      dummy;
    ESName          issuer; /* Root */
} ESSigRsa4096;

typedef struct {
    ESSigType        sigType;
    CSLOSRsaSig2048  sig;
    ESSigDummy       dummy;
    ESName           issuer;   /* Root-CAxxxxxxxx or 
                                  Root-CAxxxxxxxx-XSxxxxxxxx or 
                                  Root-CAxxxxxxxx-CPxxxxxxxx or 
                                  Root-CAxxxxxxxx-MSxxxxxxxx */
} ESSigRsa2048;

typedef struct {
    ESSigType    sigType;
    CSLOSEccSig  sig;
    ESSigDummy   dummy;
    ESName       issuer;  /* Root-CAxxxxxxxx-MSxxxxxxxx-NCxxxxxxxx */
} ESSigEcc;

typedef struct {
    ESPubKeyType pubKeyType;
    union {
        ESServerId serverId;
        ESDeviceId deviceId;
    } name;
    u32 date;
} ESCertHeader;

/* Root cert */
typedef struct {
    ESSigRsa4096           sig;
    ESCertHeader           head;
    CSLOSRsaPublicKey4096  pubKey;
    CSLOSRsaExponent       exponent;
    u32                    expSize;
    ESCertPad              pad;
} ESRootCert;

/* CA cert */
typedef struct {
    ESSigRsa4096           sig;
    ESCertHeader           head;
    CSLOSRsaPublicKey2048  pubKey;
    CSLOSRsaExponent       exponent;
    u32                    expSize;
    ESCertPad              pad;
} ESRsa4096RsaCert;

/* signer certs */
typedef struct {
    ESSigRsa2048           sig;
    ESCertHeader           head;
    CSLOSRsaPublicKey2048  pubKey;
    CSLOSRsaExponent       exponent;
    u32                    expSize;
    ESCertPad              pad;
} ESRsa2048RsaCert;

/* device certs */
typedef struct {
    ESSigRsa2048       sig;        /* 2048 bit RSA signature */
    ESCertHeader       head;
    CSLOSEccPublicKey  pubKey;     /* 512 bit ECC public key */
    ESCertPad          pad;
    ESEccCertPad       pad2;
} ESRsa2048EccCert;

/* devices signed certs */
typedef struct {
    ESSigEcc          sig;        /* 512 bit ECC signature */
    ESCertHeader      head;
    CSLOSEccPublicKey pubKey;     /* 512 bit ECC public key */
    ESCertPad         pad;
    ESEccCertPad      pad2;
} ESEccEccCert;

typedef ESServerId   ESCrlEntry;

typedef struct {
    ESSigRsa2048   sig;       /* RSA 2048bit sign of the ticket bundle */ 
    CSLOSEccPublicKey serverPubKey; /* ticketing server public key */
    CSLOSAesKey    titleKey;  /* published title key. encrypted using a 
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
    CSLOSSha1Hash hash;   /* 160-bit SHA1 hash of the content */
} ESContentMeta;

typedef struct {
    ESVersion     version;  /* TMD version number */
    ESVersion     osVersion;  /* OS version number */
    ESVersion     caCrlVersion;  /* CA CRL version number */ 
    ESVersion     signerCrlVersion; /* signer CRL version number */

    ESContentId   tmdCid;       /* cid of the TMD */
    ESTitleId     titleId;      /* 32 bit title id */
    ESReserved    reserved;     /* 64 bytes reserved info for Nintendo */
    u32           accessRights; /* title's access rights to use 
                                   system resources */
    u32           numContents;  /* number of contents per title */
    u16           bootIndex;    /* boot content index */
    u16           dummy;
} ESTitleMetaHeader;

typedef struct {
    ESSigRsa2048       sig;      /* RSA 2048bit sign of all the data in 
                                    the TMD file */
    ESTitleMetaHeader  head;
    ESContentMeta      contents[ES_MAX_CONTENT];
} ESTitleMeta;

#define ES_BLOCK_SIZE        (16*1024)
#define ES_APP_FILE_SUFFIX   "app"

#endif /*__ES_INT_H__*/
