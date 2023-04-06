#ifndef __BB_SYSAPP_META_H_
#define __BB_SYSAPP_META_H_

#include <PR/bbtypes.h>
#include <PR/bbcert.h>
#include <PR/bbcrl.h>
#include <PR/bbticket.h>
#include <PR/bbmetadata.h>
#include "common.h"

/* max tickets on fs */
#define SA_META_MAX_TICKETS 128

/* error codes */
#define SAMETA_ERR_FS          -1 /* error opening file on fs */
#define SAMETA_ERR_MEM         -2 /* not enough memory (heap) */
#define SAMETA_ERR_DATA        -3 /* data error               */
#define SAMETA_ERR_LP_ADVANCE  -4 /* skAdvanceWindow error    */

/* Game MetaData type flags */
#define  SA_META_TYPE_ONCARD  1  /* 1 if is on card */
#define  SA_META_TYPE_TRIAL   2  /* 1 if trial game */

#define SAMETA_TICKET_PERM        0
#define SAMETA_TICKET_LP_VALID    1
#define SAMETA_TICKET_LP_EXPIRED  2

typedef struct {
    u16 thumb_len;  /* gzipped thumbnail data length */
    u8 *thumb_data; /* pointer to gzipped 32x32 RGBA16 thumbnail*/
    u8 *title;      /* game title string */
    u32 size;  /* game size in bytes              */
    u32 type;  /* SA_META_TYPE_* flags        */
    u16 code;  /* limit algorithm type for LP games */
    u16 limit; /* limit for LP games */
    u16 cc;    /* consumption count for LP games */
} SaGameMetaData;

typedef struct {
    u32 numTickets;
    BbTicket ticket[SA_META_MAX_TICKETS];
} SaTickets;

/* as currently defined, the ticket.sys file will simply be read
 * into the tickets array since the formats are the same. if in the
 * future the tickey.sys layout changes, this api prevent the gui
 * from requiring change.
 */
int saMetaGetTickets(SaTickets *tickets);

/* reads ticket.sys file, deletes any "invalid" ticket, and groups 
 * the remaining tickets into permanant and LP group, both groups 
 * are sorted according to cids, writes out the cleaned up tickets 
 * back to ticket.sys file, returns the cleaned up tickets in 
 * "tickets" structure, updates the LP window base based on the 
 * cleaned up tickets. 
 *
 * A ticket is "invalid" and is deleted if:
 * 1. it is a LP ticket and there exists a permanant ticket for
 *    the same cid, or
 * 2. it is an expired LP ticket and there exists >=1 unexpired
 *    LP ticket for the same cid, or
 * 3. it is an expired LP ticket and there exists an expired LP
 *    ticket for the same cid and with a greater tid
 */
int saMetaCleanTickets(SaTickets *tickets);

/* metaData:
 *    assumed large enough to hold tickets.numTickets SaGameMetaData 
 *    entries.
 */
int saMetaGetData(SaTickets *tickets, SaGameMetaData *metaData);
                                 
#endif

