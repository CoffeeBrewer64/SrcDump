d16 1
a16 1
#include "types.h"
d19 8
d29 1
a29 1
typedef u32  ESTitleId;            /* 32-bit title identity */
d32 1
a32 13

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
d42 3
d47 1
d83 3
d107 9
