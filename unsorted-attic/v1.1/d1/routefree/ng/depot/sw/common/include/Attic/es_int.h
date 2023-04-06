d16 3
a18 2
#include "estypes.h"
#include "csl.h"
a26 11
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
d28 2
a29 2
#define ES_TMD_VERSION          (1)
#define ES_TICKET_VERSION       (1)
d32 1
a32 1
#define ES_SYS_TITLE_DIR        "/sys/title"
d37 1
d39 13
a51 37
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
d53 1
a53 9
typedef struct {
    ESSigType        sigType;
    CSLOSRsaSig2048  sig;
    ESSigDummy       dummy;
    ESName           issuer;   /* Root-CAxxxxxxxx or 
                                  Root-CAxxxxxxxx-XSxxxxxxxx or 
                                  Root-CAxxxxxxxx-CPxxxxxxxx or 
                                  Root-CAxxxxxxxx-MSxxxxxxxx */
} ESSigRsa2048;
d55 1
a55 6
typedef struct {
    ESSigType    sigType;
    CSLOSEccSig  sig;
    ESSigDummy   dummy;
    ESName       issuer;  /* Root-CAxxxxxxxx-MSxxxxxxxx-NCxxxxxxxx */
} ESSigEcc;
d57 3
d61 9
a69 67
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
d88 1
a88 1
    CSLOSSha1Hash hash;   /* 160-bit SHA1 hash of the content */
d93 1
a93 1
    ESVersion     osVersion;  /* OS version number */
d96 1
d107 3
d112 1
a112 1
    ESSigRsa2048       sig;      /* RSA 2048bit sign of all the data in 
d118 3
