#ifndef __BB_SYSAPP_CERT_H_
#define __BB_SYSAPP_CERT_H_

#include <PR/bbtypes.h>
#include <PR/bbcert.h>
#include "common.h"

#define SA_MAX_NUM_CERTS 64

#define SACERT_ERR -1

int saCertInit(u8 *certs,u32 bytes);
int saCertCreateChain(u8 *certs,const char *name,BbCertBase **chain);

#endif
