#include <PR/bcp.h>
#include <PR/R4300.h>
#include <PR/bbsim.h>
#include <PR/bbskapi.h>
#include <PR/os.h>
#include <PR/os_bbfs.h>
#include <PR/os_bbatb.h>
#include <PR/os_bbexec.h>
#include "launch.h"
#include "globals.h"

struct {
    s32 sfd;
    s32 dfd;
    BbTicketBundle ticketBundle;    
    BbAppLaunchCrls appRls;
    u32 recoveryBTgt;  /* target for recovery. 0 for no recovery */
    u32 destBProc;     /* dest bytes processed since saGamePrelaunch() */
    char launchAppName[16];
} gRecryptState;

/* bit flags for return */
#define SA_CID_EXT_NONE 0
#define SA_CID_EXT_APP  1 
#define SA_CID_EXT_REC  2
int getAppExtensionsPresent(BbContentId cid)
{
    char appName[16];
    s32 fd;
    int ret=0;

    cidToAppName(cid,gAppExt,appName);
    if( (fd = osBbFOpen(appName,"r")) >= 0){
        ret |= SA_CID_EXT_APP;
        osBbFClose(fd);
    }

    cidToAppName(cid,gRecExt,appName);
    if( (fd = osBbFOpen(appName,"r")) >= 0){
        ret |= SA_CID_EXT_REC;
        osBbFClose(fd);
    }
    
    return ret;
}

int readKeylist(u8 *keylist)
{
    s32 fd;

    int ret = SALAUNCH_OK;

    if( (fd = osBbFOpen(gRecryptKeyFname,"r")) < 0){
        return SALAUNCH_ERR_FILE_NOT_FOUND;
    }
    if(osBbFRead(fd, 0, keylist, KEYLIST_SIZE)<0){
        ret = SALAUNCH_ERR_FS;
    }
    osBbFClose(fd);
    return ret;
}

/* create if necessary */
int saveKeylist(u8 *keylist)
{
    s32 fd;
    int ret = SALAUNCH_OK;

    if( (fd = osBbFOpen(gRecryptKeyFname,"w")) < 0){
        if( (fd = osBbFCreate(gRecryptKeyFname,1,KEYLIST_SIZE)) < 0){
            return SALAUNCH_ERR_FS;
        }
    }
    if(osBbFWrite(fd, 0, keylist, 16*1024)<0){
        ret = SALAUNCH_ERR_FS;
    }
    osBbFClose(fd);
    return ret;
}


/*
 * NOTE: elements of the output, ticketBundle, will address memory
 *       in heap. so do not reclaim heap until after ticketBundle
 *       and appRls are no longer needed.
 */
int saBundleTicket(BbTicket *ticket,
                   BbTicketBundle *ticketBundle,
                   BbAppLaunchCrls *appRls,
                   u8 *heap,u32 heapSize)
{
    BbContentMetaDataHead *pCmdh;
    u8 *rlHeap,*certHeap;
    OSBbStatBuf fsStat;
    s32 fsret,fd;
    int haveCrl=1;

    ticketBundle->ticket = ticket;
    pCmdh = &(ticketBundle->ticket->cmd.head);

    PRINTF("content size: %08x\n",pCmdh->size);

    /*
     * load certs
     */

    fd = osBbFOpen(gCertFname,"r");
    if(fd<0){
        return SALAUNCH_ERR_FS;
    }
    fsret = osBbFStat(fd, &fsStat, NULL, 0);
    PRINTF("%s contains %d bytes\n",gCertFname,fsStat.size);

    if(fsret !=0)
        return SALAUNCH_ERR_FS;
    if(fsStat.size >= heapSize)
        return SALAUNCH_ERR_MEM;

    certHeap = (u8 *)heap;

    /* read entire cert file into serialized heap */
    if(osBbFRead(fd, 0, certHeap, fsStat.size)<0){
        osBbFClose(fd);
        return SALAUNCH_ERR_FS;
    }

    if(osBbFClose(fd)<0){
        return SALAUNCH_ERR_FS;
    }

    /* initialize cert parser */
    if(saCertInit(certHeap,fsStat.size)!=BB_SYSAPP_PASS)
        return SALAUNCH_ERR_DATA;

    /* create ticket bundle */
    if(saCertCreateChain(certHeap,ticket->head.issuer,
                         ticketBundle->ticketChain)<0){
        PRINTF("saCertCreateChain() failure for ticket chain.\n");
        return SALAUNCH_ERR_DATA;
    }
    if(saCertCreateChain(certHeap,pCmdh->issuer,
                         ticketBundle->cmdChain)<0){
        PRINTF("saCertCreateChain() failure for cmd chain.\n");
        return SALAUNCH_ERR_DATA;
    }

    /*
     * load rls
     */

    fd = osBbFOpen(gRlFname,"r");
    if(fd<0){
        PRINTF("Failed to open rl file, proceeding without...\n");
        memset((void *)appRls,0,sizeof(BbAppLaunchCrls));
        haveCrl = 0;
    }
    if(haveCrl){
        /* NOTE: fsStat.size is prev heap usage to load cert.sys.
         *       it is 16KB aligned since fs doesn't support sizes
         *       of granularity < 16KB.
         */
        rlHeap = certHeap + fsStat.size;

        if((fd = osBbFOpen(gRlFname,"r")) < 0)
            return SALAUNCH_ERR_FS;
        fsret = osBbFStat(fd, &fsStat, NULL, 0);
        PRINTF("%s contains %d bytes\n",gRlFname,fsStat.size);
        
        if(fsret !=0)
            return SALAUNCH_ERR_FS;
        if(fsStat.size + (u32)(rlHeap-certHeap) >= heapSize)
            return SALAUNCH_ERR_MEM;

        /* read entire rl file into serialized heap */
        if(osBbFRead(fd, 0, rlHeap, fsStat.size)<0){
            osBbFClose(fd);
            return SALAUNCH_ERR_FS;
        }
        
        if(osBbFClose(fd)<0){
            return SALAUNCH_ERR_FS;
        }

        if(saRlBundle(rlHeap,certHeap,appRls)!=BB_SYSAPP_PASS)
            return SALAUNCH_ERR_DATA;
    }

    return BB_SYSAPP_PASS;
}

static int prelaunchRecryptNotReq(BbContentMetaDataHead *pCmdh, u8 *keylist)
{
    if(SK_API_SUCCESS != skLaunchSetup(&gRecryptState.ticketBundle, 
                                       &gRecryptState.appRls, 
                                       keylist)){
        PRINTF("skLaunch() failure!\n");
        return SALAUNCH_ERR_DATA;
    }
    cidToAppName(pCmdh->id,gAppExt,gRecryptState.launchAppName);
    return SALAUNCH_OK;
}


static int prelaunchFullRecrypt(BbContentMetaDataHead *pCmdh,u8 *keylist)
{
    OSBbStatBuf fsStat;
    char appName[16];

    /* save keylist */
    saveKeylist(keylist);
    
    /* setup state for chunked personalization calls */
    /* source fd */
    cidToAppName(pCmdh->id,gAppExt,appName);
    if( (gRecryptState.sfd = osBbFOpen(appName,"r")) < 0){
        PRINTF("Failed to open source app.\n");
        return SALAUNCH_ERR_FS;
    }
    
    /* destination fd */
    cidToAppName(pCmdh->id,gRecExt,appName);
    if((gRecryptState.dfd = osBbFCreate(appName, 1, 0)) < 0){
        PRINTF("Failed to open dest app.\n");
        return SALAUNCH_ERR_FS;
    }
    if((osBbFStat(gRecryptState.sfd, &fsStat, NULL, 0)) < 0){
        return SALAUNCH_ERR_FS;
    }
    if(fsStat.size<pCmdh->size){
        return SALAUNCH_ERR_FS;
    }

    gRecryptState.recoveryBTgt=0;
    gRecryptState.destBProc=0;
    return SALAUNCH_PERSONALIZE;
}

/* global state - no support for launching multiple games at a time.
 *   must be called from a single thread.
 *
 * heap 16B aligned and untouched by caller for saGamePrelaunch() and
 * saGamePersonalize(). must be large enough to hold:
 *   recrypt.sys (16KB)
 *   cert.sys    (probably 16KB)
 *   rl.sys      (probably 16KB, but max computable)
 *   inter-call state??? (may make this global in implementation file)
 */
int saGamePrelaunch(BbTicket *ticket,u8 *heap,u32 heapSize)
{
    BbTicketId tid; 
    BbContentMetaDataHead *pCmdh;
    u8 *keylist=heap;
    OSBbStatBuf fsStat;
    char appName[16];
    int i, ret, initKeylistGood=FALSE;
    u16 limit, window, cc[BB_MAX_CC];

    pCmdh = &(ticket->cmd.head);

    /* check limited play ticket*/
    tid = ticket->head.tid;
    limit = ticket->head.limit;
    if (tid >= BB_TICKET_ID_LIMITED) {
        skGetConsumption(&window, cc);
        for (i=0; i<BB_MAX_CC; i++) {
            if ( (tid & (BB_TICKET_ID_LIMITED-1)) == window+i ) { 
                if (cc[i]==limit) 
                    return SALAUNCH_ERR_EXPIRED;
                else
                    break;
            }
        }
    }

    /* check keylist */
    memset(keylist, 0, KEYLIST_SIZE);
    if((ret = readKeylist(keylist)) == SALAUNCH_ERR_FS)
        return ret;
    if((ret==SALAUNCH_OK) && (skRecryptListValid(keylist)!=SK_API_FAIL)){
        initKeylistGood = TRUE;
    }

    if(BB_SYSAPP_PASS != saBundleTicket(ticket, 
                                        &gRecryptState.ticketBundle,
                                        &gRecryptState.appRls,
                                        heap+KEYLIST_SIZE,
                                        heapSize-KEYLIST_SIZE)){
        PRINTF("saBundleTicket() failure!\n");
        return SALAUNCH_ERR_DATA;
    }

    /* default to recrypted app name for launch. change in code
     * to follow if necessary.
     */
    cidToAppName(pCmdh->id,gRecExt,gRecryptState.launchAppName);

    /* determine state of recryption by extension */
    i = getAppExtensionsPresent(pCmdh->id);

    switch(i){
    case SA_CID_EXT_NONE:
        return SALAUNCH_ERR_FS;
    case SA_CID_EXT_APP:
        /* original app directly from depot only */
        ret = skRecryptBegin(&gRecryptState.ticketBundle, 
                             &gRecryptState.appRls, 
                             keylist);
        switch(ret){
        case SK_API_RECRYPT_NOT_REQUIRED:
            return prelaunchRecryptNotReq(pCmdh, keylist);
        case SK_API_RECRYPT_INCOMPLETE:
            if(initKeylistGood==FALSE)
                return SALAUNCH_ERR_KEYLIST;
            /* crossover call for inside SK */
            if(skRecryptData(NULL, 0) != SK_API_SUCCESS)
                return SALAUNCH_ERR_DATA;
            return prelaunchFullRecrypt(pCmdh, keylist);
        case SK_API_RECRYPT_NEW:
        case SK_API_RECRYPT_COMPLETE:
            /* full recrypt */
            return prelaunchFullRecrypt(pCmdh, keylist);
        default:
            /* error case */
            return SALAUNCH_ERR_DATA;
        }
        break;
    case SA_CID_EXT_REC:
        /* personalized version only */
        if(initKeylistGood==FALSE)
            return SALAUNCH_ERR_KEYLIST;

        ret = skLaunchSetup(&gRecryptState.ticketBundle, 
                            &gRecryptState.appRls, 
                            keylist);
        switch(ret){
        case SK_API_SUCCESS:
            return SALAUNCH_OK;
        case SK_API_RECRYPT_INCOMPLETE:
            if(skRecryptBegin(&gRecryptState.ticketBundle, 
                                 &gRecryptState.appRls, 
                                 keylist)!=SK_API_RECRYPT_INCOMPLETE)
                return SALAUNCH_ERR_DATA;
            /* destination fd */
            cidToAppName(pCmdh->id,gRecExt,appName);
            if((gRecryptState.dfd = osBbFOpen(appName,"rw")) < 0){
                PRINTF("Failed to open dest app.\n");
                return SALAUNCH_ERR_FS;
            }
            if((osBbFStat(gRecryptState.dfd, &fsStat, NULL, 0)) < 0){
                return SALAUNCH_ERR_FS;
            }

            gRecryptState.recoveryBTgt=fsStat.size;
            gRecryptState.destBProc=0;

            return SALAUNCH_PERSONALIZE;
        case SK_API_RECRYPT_NEW:
        default:
            return SALAUNCH_ERR_DATA;
        }
    default:
        /* both original and personalized versions (most likely recovery
         * scenario) 
         */
        if(initKeylistGood==FALSE)
            return SALAUNCH_ERR_KEYLIST;

        ret = skRecryptBegin(&gRecryptState.ticketBundle, 
                             &gRecryptState.appRls, 
                             keylist);
        switch(ret){
        case SK_API_RECRYPT_NOT_REQUIRED:
            /* this case shouldn't occur */
            /* remove <cid>.rec, since shouldn't exist */
            osBbFDelete(gRecryptState.launchAppName);
            return prelaunchRecryptNotReq(pCmdh, keylist);
        case SK_API_RECRYPT_NEW:
        case SK_API_RECRYPT_COMPLETE:
            /* these cases shouldn't occur */
            /* remove <cid>.rec, since shouldn't exist */
            osBbFDelete(gRecryptState.launchAppName);
            return prelaunchFullRecrypt(pCmdh, keylist);
        case SK_API_RECRYPT_INCOMPLETE:
            /* the recovery expected case */

            /* setup state for chunked personalization calls */
            /* source fd */
            cidToAppName(pCmdh->id,gAppExt,appName);
            if( (gRecryptState.sfd = osBbFOpen(appName,"r")) < 0){
                PRINTF("Failed to open source app.\n");
                return SALAUNCH_ERR_FS;
            }

            /* destination fd */
            cidToAppName(pCmdh->id,gRecExt,appName);
            if((gRecryptState.dfd = osBbFOpen(appName,"rw")) < 0){
                PRINTF("Failed to open dest app.\n");
                return SALAUNCH_ERR_FS;
            }
            if((osBbFStat(gRecryptState.dfd, &fsStat, NULL, 0)) < 0){
                return SALAUNCH_ERR_FS;
            }

            gRecryptState.recoveryBTgt=fsStat.size;
            gRecryptState.destBProc=0;

            return SALAUNCH_PERSONALIZE;
            
        default:
            /* error case */
            return SALAUNCH_ERR_DATA;
        }
    }

    /* shouldn't come here */
    return SALAUNCH_ERR_DATA;
}


/* return SALAUNCH_OK when done, SALAUNCH_PERSONALIZE indicates call again.
 *
 * chunkBuffer must always be of size RECRYPT_CHUNK_SIZE.
 */
int saGamePersonalize(u8 *chunkBuffer,u8 *heap,u32 heapSize)
{
    u32 chunkSize=RECRYPT_CHUNK_SIZE;
    u32 contentSize=gRecryptState.ticketBundle.ticket->cmd.head.size;
    int ret;

    if(contentSize<(gRecryptState.destBProc+chunkSize)) 
        chunkSize = contentSize-gRecryptState.destBProc;
        
    if(gRecryptState.recoveryBTgt){

        if(osBbFRead(gRecryptState.dfd, 
                     gRecryptState.destBProc, 
                     chunkBuffer, chunkSize) < 0) {
            ret = SALAUNCH_ERR_FS;
            goto chunkerr;
        }
        if(skRecryptComputeState(chunkBuffer,chunkSize)!=SK_API_SUCCESS){
            ret = SALAUNCH_ERR_DATA;
            goto chunkerr;
        }
        gRecryptState.destBProc += chunkSize;

        /* need to crossover? */
        if(gRecryptState.destBProc < contentSize && 
           gRecryptState.destBProc == gRecryptState.recoveryBTgt){

            gRecryptState.recoveryBTgt = 0;
            if(osBbFRead(gRecryptState.sfd, 0, chunkBuffer, chunkSize) < 0){
                ret = SALAUNCH_ERR_FS;
                goto chunkerr;
            }
            if(skRecryptData(chunkBuffer,chunkSize)!=SK_API_SUCCESS){
                ret = SALAUNCH_ERR_DATA;
                goto chunkerr;
            }
        }
    }
    else{
        if(osBbFRead(gRecryptState.sfd, 
                     gRecryptState.destBProc ? RECRYPT_CHUNK_SIZE : 0, 
                     chunkBuffer, chunkSize) < 0) {
            ret = SALAUNCH_ERR_FS;
            goto chunkerr;
        }
        if(skRecryptData(chunkBuffer, chunkSize)!=SK_API_SUCCESS){
            ret = SALAUNCH_ERR_DATA;
            goto chunkerr;
        }
        if(osBbFShuffle(gRecryptState.sfd, gRecryptState.dfd, 
                        gRecryptState.destBProc!=0, 
                        chunkBuffer, chunkSize) < 0) {
            ret = SALAUNCH_ERR_FS;
            goto chunkerr;
        }        
        gRecryptState.destBProc += chunkSize;
    }

    /* finished? */
    if(gRecryptState.destBProc>=contentSize){
        /* done, prepare for launch */
        char appName[16];
        u8 *keylist = heap; /* keylist at beginning of heap from 
                             * saGamePrelaunch() 
                             */
        cidToAppName(gRecryptState.ticketBundle.ticket->cmd.head.id,
                     gAppExt,appName);
        osBbFClose(gRecryptState.sfd);
        osBbFClose(gRecryptState.dfd);
        osBbFDelete(appName);
        if(skRecryptEnd(keylist)!=SK_API_SUCCESS){
            cidToAppName(gRecryptState.ticketBundle.ticket->cmd.head.id,
                         gRecExt,appName);
            osBbFDelete(appName);
            return SALAUNCH_ERR_DATA;
        }
        saveKeylist(keylist);
        PRINTF("skLaunchSetup()\n");
        if(skLaunchSetup(&gRecryptState.ticketBundle, 
                         &gRecryptState.appRls, keylist)!=SK_API_SUCCESS){
            return SALAUNCH_ERR_DATA;
        }
        return SALAUNCH_OK;
    }

    return SALAUNCH_PERSONALIZE;

 chunkerr:
    osBbFClose(gRecryptState.sfd);
    osBbFClose(gRecryptState.dfd);
    return ret;
}


int saGameLaunch(u8 *heap,u32 heapSize, u32 binding[4])
{
    u16 *blkList;
    OSBbStatBuf fsStat;
    OSBbMetaData md;
    s32 fsret,fd,listSize;
    u32 addr;

    if( (fd = osBbFOpen(gRecryptState.launchAppName,"r")) < 0){
        return SALAUNCH_ERR_FS;
    }

    memset(heap,0,heapSize);
    blkList = (u16 *)heap;

    fsret = osBbFStat(fd, &fsStat, blkList, heapSize/2);
    if(fsret !=0)
        return SALAUNCH_ERR_FS;
    
    listSize = fsStat.size/BB_FL_BLOCK_SIZE;

    PRINTF("Calling osBbGetMetaData()\n");
    if (osBbGetMetaData(&md, blkList, listSize) >= 0) {
        PRINTF("Calling osBbLoadState()\n");
        osBbLoadState(gRecryptState.launchAppName, &md.state, binding);
    }
    PRINTF("Calling osBbLoadApp()\n");
    if ((addr = osBbLoadApp(&md, blkList, listSize)) != NULL) {
        skLaunch(addr);
    }

    return SALAUNCH_ERR_DATA;
}

