#ifndef __BB_SYSAPP_LAUNCH_H_
#define __BB_SYSAPP_LAUNCH_H_

#include <PR/bbtypes.h>
#include <PR/bbcert.h>
#include <PR/bbcrl.h>
#include <PR/bbskapi.h>
#include "common.h"
#include "cert.h"
#include "rl.h"

#define CERT_CHAIN_MAX_LEN 5
#define KEYLIST_SIZE       16384
#define RECRYPT_CHUNK_SIZE (8*16*1024) /* NEVER CHANGE THIS AFTER FIRST
                                        * VIEWER RELEASE!!!
                                        */

/* informative success codes */
#define SALAUNCH_OK            0 /* may proceed with launch  */
#define SALAUNCH_PERSONALIZE   1 /* personalization required */

/* error codes */
#define SALAUNCH_ERR_FS             -1 /* error opening file on fs */
#define SALAUNCH_ERR_MEM            -2 /* not enough memory (heap) */
#define SALAUNCH_ERR_DATA           -3 /* data error               */
#define SALAUNCH_ERR_EXPIRED        -4 /* ticket expired           */
#define SALAUNCH_ERR_KEYLIST        -5 /* bad keylist              */
#define SALAUNCH_ERR_FILE_NOT_FOUND -6 /* bad keylist              */

int saBundleTicket(BbTicket *ticket,
                   BbTicketBundle *ticketBundle,
                   BbAppLaunchCrls *appRls,
                   u8 *heap,u32 heapSize);

int saGamePrelaunch(BbTicket *ticket,u8 *heap,u32 heapSize);
int saGamePersonalize(u8 *chunkBuffer,u8 *heap,u32 heapSize);
int saGameLaunch(u8 *heap,u32 heapSize, u32 binding[4]);

#endif
