#include <PR/bcp.h>
#include <PR/R4300.h>
#include <PR/bbsim.h>
#include <PR/bbskapi.h>
#include <PR/os.h>
#include <PR/os_bbfs.h>
#include <PR/os_bbatb.h>
#include "meta.h"
#include "globals.h"

static u8 fbuf[4+SA_META_MAX_TICKETS*sizeof(BbTicket)] __attribute__ ((aligned(16)));

int getTicketStatus( BbTicket *pTick, u16 window, u16 *cc);
int updateLPWindow( SaTickets *tickets, u16 *window, u16 *cc);

int saMetaGetTickets(SaTickets *tickets)
{
    OSBbStatBuf fsStat;
    s32 fd;
    u32 ret = BB_SYSAPP_PASS;

    fd = osBbFOpen(gTicketFname,"r");
    if(fd<0){
        return SAMETA_ERR_FS;
    }
    if( osBbFStat(fd, &fsStat, NULL, 0) < 0){
        ret = SAMETA_ERR_FS;
        goto exit;
    }

    if(fsStat.size > sizeof(SaTickets)){
        ret = SAMETA_ERR_MEM;
        goto exit;
    }

    if(osBbFRead(fd, 0, (u8 *)tickets, fsStat.size)<0){
        ret = SAMETA_ERR_FS;
        goto exit;
    }

 exit:
    osBbFClose(fd);
    return ret;
}

int saMetaCleanTickets(SaTickets *tickets)
{
    int i, j, k, iorder, jorder;
    int istatus, jstatus, win;
    int size, block_size;
    char newFname[]="tmp.sys";
    s32 fd;
    BbTicket tmpTicket;
    u16 window, cc[BB_MAX_CC];
    u8 order[SA_META_MAX_TICKETS], valid[SA_META_MAX_TICKETS];
    u8 pgame[SA_META_MAX_TICKETS], pvalid[SA_META_MAX_TICKETS];
    u8 tgame[SA_META_MAX_TICKETS], tvalid[SA_META_MAX_TICKETS];
    u32 ret = BB_SYSAPP_PASS;

    // get raw tickets
    ret = saMetaGetTickets(tickets);
    if (ret != BB_SYSAPP_PASS) return ret;

    // get consumption window
    skGetConsumption(&window, cc);
    PRINTF("window=%d\n", window);

    // mark all as valid in counting order
    for(i=0; i<tickets->numTickets; i++) {
        order[i] = i;
        valid[i] = 1;
    }

    // Sort & mark as "invalid" any tickets to be deleted.
    win = -1;
    for(i=0; i<tickets->numTickets; i++){
        iorder = order[i];
        if( valid[iorder] ) {
            istatus = getTicketStatus( &(tickets->ticket[iorder]), window, cc );

            // compare with others
            for(j=i+1; (j<tickets->numTickets)&&(valid[iorder]); j++) {
                jorder = order[j];
                if( valid[jorder] ) {
                    jstatus = getTicketStatus( &(tickets->ticket[jorder]), window, cc );

                    // do i & j have the same cid? 
                    if( tickets->ticket[iorder].cmd.head.id == tickets->ticket[jorder].cmd.head.id ) {
                        if ( istatus==SAMETA_TICKET_PERM || (istatus==SAMETA_TICKET_LP_VALID && jstatus==SAMETA_TICKET_LP_EXPIRED) ) 
                            valid[jorder] = 0;
                        else if ( jstatus==SAMETA_TICKET_PERM || (jstatus==SAMETA_TICKET_LP_VALID && istatus==SAMETA_TICKET_LP_EXPIRED) ) 
                            valid[iorder] = 0;
                        else if ( istatus==SAMETA_TICKET_LP_EXPIRED && jstatus==SAMETA_TICKET_LP_EXPIRED) {
                            if (tickets->ticket[jorder].head.tid > tickets->ticket[iorder].head.tid ) 
                                valid[iorder] = 0;
                            else
                                valid[jorder] = 0;
                        }
                    } else if( tickets->ticket[iorder].cmd.head.id < tickets->ticket[jorder].cmd.head.id ) {
                        // switch games for sorting based on cid
                        order[j] = iorder;
                        order[i] = jorder;
                        iorder = order[i];

                        // update i index
                        istatus = jstatus; 
                    }
                }
            }
        }
    }

    // seperate ticket array into two: permanant and LP  
    for(i=j=k=0; i<tickets->numTickets; i++) {
        if( tickets->ticket[order[i]].head.tid < BB_TICKET_ID_LIMITED ) {
            pgame[j] = order[i];
            pvalid[j++] = valid[i];
        } else {
            tgame[k] = order[i];
            tvalid[k++] = valid[i];
        }
    }
    for( i = 0; i < j; i++ ) {
        order[i] = pgame[i];
    }
    for( i = j; i < tickets->numTickets; i++ ) {
        order[i] = tgame[i-j];
    }

    // compress and update ticket structure
    for(i=j=0; i<tickets->numTickets; i++){
        // only copy data if valid
        if( valid[ order[i] ] ) {
            // if we are copying to a valid ticket, we need to save it
            if( valid[j] ) bcopy( &tickets->ticket[j], &tmpTicket, sizeof(BbTicket) );
            bcopy( &tickets->ticket[ order[i] ], &tickets->ticket[j], sizeof(BbTicket) );
            if( valid[j] ) bcopy( &tmpTicket, &tickets->ticket[ order[i] ], sizeof(BbTicket) );

            // find where the replaced ticket goes
            for( k = j+1; k < tickets->numTickets; k++ ) 
                if( order[k] == j ) break;

            valid[ order[i] ] = valid[j];
            order[k] = order[j]; // flip orders

            order[j] = j;
            valid[j] = 1;
            j++;
        }
    }
    tickets->numTickets = j;

    // write out ticket.sys
    size = 4 + sizeof(BbTicket) * (tickets->numTickets);
    block_size = (size%BB_FL_BLOCK_SIZE == 0) ? size : (size/BB_FL_BLOCK_SIZE + 1) * BB_FL_BLOCK_SIZE; 
    PRINTF("size=%d block_size=%d\n", size, block_size);
    osBbFDelete(newFname);
    if ((fd = osBbFCreate(newFname, 1, block_size))<0) {
        PRINTF("tmp.sys creation failed %d\n", fd);
        ret = SAMETA_ERR_FS;
    } else {
        bzero(fbuf, sizeof(fbuf));
        bcopy(tickets, fbuf, size);
        if( osBbFWrite(fd, 0, fbuf, block_size)<0 ){
            PRINTF("failed to write tmp.sys\n");
            osBbFClose(fd);
            ret = SAMETA_ERR_FS;
        } 
        osBbFClose(fd);
    }

    // TODO: handle error
    osBbFRename(newFname, gTicketFname);

    return ret;
}

int saMetaGetData(SaTickets *tickets, SaGameMetaData *metaData)
{
    int i;
    s32 fd;
    char appName[16];
    BbTicketId tid;
    u16 window, cc[BB_MAX_CC];

    skGetConsumption(&window, cc);

    for(i=0; i<tickets->numTickets; i++){
        metaData[i].thumb_len = *((u16*)(tickets->ticket[i].cmd.contentDesc));
        metaData[i].thumb_data = tickets->ticket[i].cmd.contentDesc+2;
        metaData[i].title = tickets->ticket[i].cmd.contentDesc+2+metaData[i].thumb_len;
        metaData[i].size  = tickets->ticket[i].cmd.head.size;
        metaData[i].type = 0;

        /* is present on card? */
        /* XXX: recrypt may impact this (multiple extensions to try) */
        cidToAppName(tickets->ticket[i].cmd.head.id,gAppExt,appName);
        if( (fd = osBbFOpen(appName,"r")) >= 0){
            metaData[i].type |= SA_META_TYPE_ONCARD;
            osBbFClose(fd);
        }

        metaData[i].limit = tickets->ticket[i].head.limit;
        /* trial games? */
        tid = tickets->ticket[i].head.tid;
        if (tid >= BB_TICKET_ID_LIMITED) {
            metaData[i].type |= SA_META_TYPE_TRIAL;
            metaData[i].code = tickets->ticket[i].head.code;
            
            tid = tid & (BB_TICKET_ID_LIMITED-1);
            if( tid < window ) // kicked out of window, expired
                metaData[i].cc = tickets->ticket[i].head.limit;
            else if( (tid - window) >= BB_MAX_CC ) // not yet played
                metaData[i].cc = 0;
            else 
                metaData[i].cc = cc[tid-window];
        }
    }

    return BB_SYSAPP_PASS;
}
                                 
int getTicketStatus(BbTicket* pTick, u16 window, u16* cc)
{
    u16 tid; 
    int status = SAMETA_TICKET_PERM;

    if ( pTick->head.tid >= BB_TICKET_ID_LIMITED ) {
        tid = (pTick->head.tid) & (BB_TICKET_ID_LIMITED-1);
        if( tid < window ) // kicked out of window, expired
            status = SAMETA_TICKET_LP_EXPIRED;
        else if( (tid - window) >= BB_MAX_CC ) // not yet played
            status = SAMETA_TICKET_LP_VALID;
        else {
            if ( pTick->head.limit <= cc[tid - window] ) 
                status = SAMETA_TICKET_LP_EXPIRED;
            else 
                status =  SAMETA_TICKET_LP_VALID;
        }
    }
    
    return status; 
}

int updateLPWindow(SaTickets *tickets, u16 *window, u16 *cc)
{
    int i, j, ret = BB_SYSAPP_PASS;  

    skGetConsumption(window, cc);
    PRINTF("window=%d\n", *window);

    for (i=0; i<BB_MAX_CC; i++) {
        for (j=0; j<tickets->numTickets; j++) {
            if (tickets->ticket[j].head.tid >= BB_TICKET_ID_LIMITED) {
                if ( (*window)+i == (tickets->ticket[j].head.tid & (BB_TICKET_ID_LIMITED-1)) ) {
                    if ( cc[i] == tickets->ticket[j].head.limit ) {
                        PRINTF("advancing window...\n"); 
                        if ((ret = skAdvanceTicketWindow()) < 0 ) {
                            ret = SAMETA_ERR_LP_ADVANCE;
                            goto exit;
                        }
                    } else 
                        goto exit; 
                    break;
                }
            }
        }
    }

    skGetConsumption(window, cc);
    PRINTF("window=%d\n", (*window));
    
exit:
    return ret;
}
