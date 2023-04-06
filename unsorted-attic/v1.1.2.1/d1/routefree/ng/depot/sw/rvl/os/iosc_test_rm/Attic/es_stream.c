a0 1520
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

#include <addr_map.h>
#include <ioslibc.h>
#include <iostypes.h>
#include <ios.h>
#include <fs.h>
#include <es.h>
#include <es_int.h>
#define APP_LOG(s, args...)     printf(s, ## args) 
#define APP_LOG2(s, args...)    printf(s, ## args) 
#define OSRoundUp32B(x)         (((u32)(x) + 32 - 1) & ~(32 - 1))


/* Define VERBOSE to dump out tmd and ticket views */
//#define VERBOSE           1

/* Defines to enable compilation of different tests */
//#define STAND_ALONE       1
//#define TEST_NO_STREAM    1
//#define TEST_STREAM       1
//#define TEST_STREAM_WFS   1
#define TEST_WFS            1

#define CERT_SIZE           3136
#define STREAM_TITLE_ID     0x1000012345678ULL
#define WFS_TITLE_ID        0x1000021234567ULL
#define STREAM_WFS_TITLE_ID 0x1000031234567ULL
#define NOSTREAM_TITLE_ID   0x1000041234567ULL

#include "cert_data.c"
#include "es_stream_data.c"
#include "es_stream_wfs_data.c"

/* 
 * Stream tmd:
 *  - stream_tmd: 
 *      - Title ID: 0x0001000012345678
 *      - Title type (0x5): ES_TITLE_TYPE_STREAM | ES_TITLE_TYPE_NG_TITLE
            Note: This title type is supported on PPC and IOP (WFS process)
 *      - 2 contents: data1 (rom3.rom), stream_data (stream_raw.bin)
 * 
 *  - wfs_tmd:
 *      - Title ID: 0x0001000021234567
 *      - Title type (0x21): ES_TITLE_TYPE_WFS | ES_TITLE_TYPE_NG_TITLE
            Note: This title type is supported ONLY on IOP (WFS process)
 *      - 2 contents: data1 (rom3.rom), stream_data (stream_raw.bin)
 * 
 *  - stream_wfs_tmd:
 *      - Title ID: 0x0001000032345678
 *      - Title type (0x25): ES_TITLE_TYPE_STREAM | ES_TITLE_TYPE_WFS | 
 *                           ES_TITLE_TYPE_NG_TITLE
            Note: This title type combination is NOT supported.
 *      - 2 contents: data1 (rom3.rom), stream_data (stream_raw.bin)
 * 
 * Stream tickets:
 *  - title ID: 0x0001000012345678
 *  - ticket1_1: common, ticketID 0x5000, access enabled for all titles
 *  - ticket1_2: common, ticketID 0x5001, access enabled for titleID 0x30303030
 *  - ticket1_3: common, ticketID 0x5002, access enabled for titleID 0x10101010
 * 
 *  - title ID: 0x0001000021234567
 *  - ticket2_1: common, ticketID 0x5010, access enabled for all titles
 *  - ticket2_2: common, ticketID 0x5011, access enabled for titleID 0x30303030
 *  - ticket2_3: common, ticketID 0x5012, access enabled for titleID 0x10101010
 * 
 *  - title ID: 0x0001000031234567
 *  - ticket3_1: common, ticketID 0x5020, access enabled for all titles
 *  - ticket3_2: common, ticketID 0x5021, access enabled for titleID 0x30303030
 *  - ticket3_3: common, ticketID 0x5022, access enabled for titleID 0x10101010
 */
#define TICKET_1_ID 0x5000ULL
#define TICKET_2_ID 0x5001ULL
#define TICKET_3_ID 0x5002ULL
#define TICKET_4_ID 0x5003ULL

#define TICKET_WFS_1_ID 0x5010ULL
#define TICKET_WFS_2_ID 0x5011ULL
#define TICKET_WFS_3_ID 0x5012ULL
#define TICKET_WFS_4_ID 0x5013ULL

#define TICKET_STR_WFS_1_ID 0x5020ULL
#define TICKET_STR_WFS_2_ID 0x5021ULL
#define TICKET_STR_WFS_3_ID 0x5022ULL

#define tidHi(t)    ((u32)((t)>>32))
#define tidLo(t)    ((u32)((t)&0xffffffffULL))

#define SHMEM_ALLOC(v, s, a) \
    v = IOS_AllocAligned(0, s, a); \
    if (v==NULL) { \
        APP_LOG2("ERROR: Alloc failed: %d bytes\n", s); \
        rc = ES_ERR_OUT_OF_MEMORY; \
        goto out; \
    }

//static ESTitleMeta  tmd __attribute__ ((aligned(32))); 
static ESTitleMeta  *tmd;

// ticketViewList must both be 32B aligned and 32B size multiple    
#if 0
static u8           ticketViewListRoundUp32B[OSRoundUp32B(5*sizeof(ESTicketView))] __attribute__ ((aligned(32)));
static ESTicketView *ticketViewList = (ESTicketView*)ticketViewListRoundUp32B;
#endif
static ESTicketView *ticketViewList = (ESTicketView*)(WFS_SP_START-0x10000+0x1000);

//static ESTicketView ticketView __attribute__ ((aligned(32)));
static ESTicketView *ticketView;

#if defined(TEST_STREAM)
static ESTicketId   ticketIdList1[4]  __attribute__ ((aligned(32))) = { 
       TICKET_1_ID, TICKET_2_ID, TICKET_3_ID, TICKET_4_ID
};
#endif

static ESTicketId   ticketIdList2[4]  __attribute__ ((aligned(32))) = { 
       TICKET_WFS_1_ID, TICKET_WFS_2_ID, TICKET_WFS_3_ID, TICKET_WFS_4_ID
};

#if defined(TEST_STREAM_WFS)
static ESTicketId   ticketIdList3[3] = { 
       TICKET_STR_WFS_1_ID, TICKET_STR_WFS_2_ID, TICKET_STR_WFS_3_ID
};
#endif

/* Key store handle should start from 12 since default handles use 0-11 */
// static IOSCSecretKeyHandle  hStreamKey  __attribute__ ((aligned(32)));
static IOSCSecretKeyHandle  *hStreamKey;

//static IOSCAesIv            iv __attribute__ ((aligned(32))); 
static IOSCAesIv            *iv;

//static u8 dataIv[16] __attribute__ ((aligned(32)));
#define DATA_IV_SZ      16
static u8 *dataIv;

//static u8 dataBuf[65*1024] __attribute__ ((aligned(32)));
#define DATA_BUF_SZ     (65*1024)
static u8 *dataBuf;

static u8 *sh_cert = NULL;
#if defined(TEST_STREAM)
static u8 *sh_stream_tmd = NULL;
static u8 *sh_data1 = NULL;
static u8 *sh_stream_data = NULL; 
static u8 *sh_ticket1_1 = NULL;
static u8 *sh_ticket1_2 = NULL;
static u8 *sh_ticket1_3 = NULL;
static u8 *sh_ticket1_4 = NULL;
static u8 *sh_data1_raw = NULL;
#endif
#if defined(TEST_NO_STREAM)
static u8 *sh_nostream_tmd = NULL;
static u8 *sh_nostream_ticket = NULL;
#endif
static u8 *sh_wfs_tmd = NULL;
static u8 *sh_wfs_data1 = NULL;
static u8 *sh_wfs_stream_data =NULL; 
static u8 *sh_ticket2_1 = NULL;
static u8 *sh_ticket2_2 = NULL;
static u8 *sh_ticket2_3 = NULL;
static u8 *sh_ticket2_4 = NULL;
static u8 *sh_wfs_data1_raw = NULL;
#if defined(TEST_STREAM_WFS)
static u8 *sh_str_wfs_tmd = NULL;
static u8 *sh_str_wfs_data1 = NULL;
static u8 *sh_str_wfs_stream_data = NULL;
static u8 *sh_ticket3_1 = NULL;
#endif

#ifdef VERBOSE
static void dumpTmd(ESTitleMeta *tmdPtr);
static void dumpTicketView(ESTicketView *ticketViewPtr);
static void dumpIv(u8 *ivPtr);

static void
dumpTmd(ESTitleMeta *tmdPtr)
{
    int i;

    APP_LOG("\n");
    APP_LOG("*** TMD:\n");
    APP_LOG("  Version:       %d\n", tmdPtr->head.version);
    APP_LOG("  Sys Version:   0x%x\n", tmdPtr->head.sysVersion);
    APP_LOG("  Title ID:      0x%08x/0x%08x\n", 
            tidHi(tmdPtr->head.titleId),
            tidLo(tmdPtr->head.titleId));
    APP_LOG("  Title type:    0x%x\n", tmdPtr->head.type);
    APP_LOG("  Group ID:      %d\n", tmdPtr->head.groupId);
    APP_LOG("  Title version: %d\n", tmdPtr->head.titleVersion);
    APP_LOG("  Number of contents: %d\n", tmdPtr->head.numContents);
    APP_LOG("  Contents:\n");
    for (i=0; i<tmdPtr->head.numContents; i++) {
        APP_LOG("    Content ID:    0x%x\n", tmdPtr->contents[i].cid);
        APP_LOG("    Content index: %d\n", tmdPtr->contents[i].index);
        APP_LOG("    Content type:  %d\n", tmdPtr->contents[i].type);
        APP_LOG("    Size:          %lld\n", tmdPtr->contents[i].size);
    }
}

static void
dumpTicketView(ESTicketView *ticketViewPtr)
{
    int i;

    APP_LOG("\n");
    APP_LOG("*** TICKET VIEW:\n");
    APP_LOG("  Ticket ID: 0x%08x/0x%08x\n", 
            tidHi(ticketViewPtr->ticketId),
            tidLo(ticketViewPtr->ticketId));
    APP_LOG("  Device ID: 0x%08x\n", ticketViewPtr->deviceId);
    APP_LOG("  Title ID:  0x%08x/0x%08x\n", 
            tidHi(ticketViewPtr->titleId),
            tidLo(ticketViewPtr->titleId));
    APP_LOG("  Sys Access Mask:  ");
    for (i=0; i<sizeof(ESSysAccessMask); i++)
        APP_LOG2(" %02x", ticketViewPtr->sysAccessMask[i]);
    APP_LOG2("\n");
    APP_LOG("  Ticket Version:    0x%08x\n", ticketViewPtr->ticketVersion);
    APP_LOG("  Access Title ID:   0x%08x\n", ticketViewPtr->accessTitleId);
    APP_LOG("  Access Title Mask: 0x%08x\n", ticketViewPtr->accessTitleMask);
    /*
    APP_LOG("  Reserved:\n         ");
    for (i=0; i<sizeof(ESTicketReserved); i++)
        APP_LOG2(" %02x", ticketViewPtr->reserved[i]);
    APP_LOG2("\n");
    */
}

static void
dumpIv(u8 *ivPtr)
{

    int i;

    APP_LOG("Iv: ");
    for (i=0; i < sizeof(IOSCAesIv); i++) {
        APP_LOG2("%02x", ivPtr[i]);
    }
    APP_LOG2("\n");
}

#define DUMP_TMD(x)         {dumpTmd(x);}
#define DUMP_TICKETVIEW(x)  {dumpTicketView(x);}
#define DUMP_IV(x)          {dumpIv(x);}
#else   /* !VERBOSE */
#define DUMP_TMD(x)         {;}
#define DUMP_TICKETVIEW(x)  {;}
#define DUMP_IV(x)          {;}
#endif  /* !VERBOSE */

static void
dumpTmdAndTicketViews(ESTitleMeta *tmd, ESTicketView *tikViewList, u32 tikCnt)
{
    u32 i;

    DUMP_TMD(tmd);
    for (i=0; i < tikCnt; i++) {
        DUMP_TICKETVIEW(&tikViewList[i]);
    }
    APP_LOG("\n");
}

static u8 *
dupToSharedAligned(u8 *ptr, u32 size)
{
    u8 *sharedPtr;

    sharedPtr = IOS_AllocAligned(0, size, 64);
    if (sharedPtr == NULL) {
        APP_LOG("Failed to allocate buffer %d bytes\n", size);
        while (1) {};
    }
    memset(sharedPtr, 0, size);
    memcpy(sharedPtr, ptr, size);

    return(sharedPtr);
}

static void
initializeMemory()
{

    IOSError rc = IOS_ERROR_OK;
    static u8 initialized = 0;
    u32 sum;

    if (!initialized) {
#if defined(STAND_ALONE)
        /* Need to allocate buffers from shared heap to communicate with
           ISFS due to memory protection scheme */
        extern void *__isfsBuf;

        /* Overload ISFS internal buffer in library */
        SHMEM_ALLOC(__isfsBuf, ISFS_INITLIB_BUFSIZE, 32);
        APP_LOG("Allocated memory for ISFS buffer\n");

        /* Overload ES internal buffer in library */
        extern u8 *__esBuf;
        SHMEM_ALLOC(__esBuf, ES_BUF_SIZE, 32);
        APP_LOG("Allocated memory for ES buffers\n");
#endif  /* STAND_ALONE */

        SHMEM_ALLOC(ticketView, sizeof(ESTicketView), 32);
        SHMEM_ALLOC(tmd, sizeof(ESTitleMeta), 32);
        SHMEM_ALLOC(dataBuf, DATA_BUF_SZ, 32);

        SHMEM_ALLOC(hStreamKey, sizeof(IOSCSecretKeyHandle), 32);
        SHMEM_ALLOC(iv, sizeof(IOSCAesIv), 32);
        SHMEM_ALLOC(dataIv, 16, 32);

        sh_cert = dupToSharedAligned((u8 *)cert, CERT_SIZE);

        APP_LOG("Total size of cert: %d\n", CERT_SIZE);

        sum =sizeof(stream_tmd)+sizeof(stream_data)+sizeof(stream_data_raw);
        sum +=sizeof(ticket1_1)+sizeof(ticket1_2)+sizeof(ticket1_3)+sizeof(ticket1_4);
        sum +=sizeof(data1)+sizeof(data1_raw);
        sum +=sizeof(nostream_tmd)+sizeof(nostream_ticket)+sizeof(nostream_data1);
        APP_LOG("Total size of es_stream_data: %d\n", sum);

        sum =sizeof(wfs_tmd);
        sum +=sizeof(wfs_stream_data)+sizeof(wfs_stream_data_raw);
        sum +=sizeof(ticket2_1)+sizeof(ticket2_2)+sizeof(ticket2_3)+sizeof(ticket2_4);
        sum +=sizeof(wfs_data1)+sizeof(wfs_data1_raw);
        sum +=sizeof(str_wfs_tmd)+sizeof(str_wfs_data1)+sizeof(str_wfs_stream_data)+sizeof(ticket3_1);

        APP_LOG("Total size of es_stream_wfs_data: %d\n", sum);

        APP_LOG("Allocated memory for data buffers\n");

        initialized = 1;

    }

out:
    return;

}

static ESError
removeTitle(ESTitleId tid)
{
    ESError         rv = ES_ERR_OK;
    u32 ticketCnt;
    ESTicketView *tvp;
    u16 i;

    rv = ES_DeleteTitle(tid);
    if (rv != ES_ERR_OK && rv != ES_ERR_NOEXISTS) {
        APP_LOG("ERROR: Failed to delete title, rv=%d\n", rv);
        goto out;
    }

    /*
     * Delete the ticket(s) for the title, if it exists
     */
    if (rv != ES_ERR_NOEXISTS) {
        rv = ES_GetTicketViews(tid, NULL, &ticketCnt);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
            goto out;
        }
        APP_LOG("Found %d ticket(s) for title ID 0x%08x/0x%08x\n", ticketCnt, 
            tidHi(tid), tidLo(tid));

        rv = ES_GetTicketViews(tid, ticketViewList, &ticketCnt);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
            goto out;
        }

        APP_LOG("Deleting %d tickets for title = %08x/%08x\n",
            ticketCnt, tidHi(tid), tidLo(tid));
        for (i=0; i<ticketCnt; i++) {
            tvp = &(ticketViewList[i]);
            memcpy(ticketView, tvp, sizeof(ESTicketView));
            rv = ES_DeleteTicket(ticketView);
            if (rv != ES_ERR_OK) {
                APP_LOG("ERROR: Failed to delete ticket 0x%llx, rv=%d\n", 
                    ticketViewList[i].ticketId, rv);
                goto out;
            }
        }  /* for */
    }

out:
    return rv;
}


#if defined(TEST_NO_STREAM)
static ESError
testNoStream(ESTitleId titleId)
{
    ESError         rv = ES_ERR_OK;
    ESError         rvFinal = ES_ERR_OK;
    u32 tmdSize;
    u32 ticketCnt;

    APP_LOG("\n");
    APP_LOG("*** Testing non-stream title = %08x/%08x\n", 
        tidHi(titleId), tidLo(titleId));
    APP_LOG("Deleting title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    /* Import the ticket */
    sh_nostream_ticket = dupToSharedAligned((u8 *)nostream_ticket, sizeof(nostream_ticket));
    rv = ES_ImportTicket(sh_nostream_ticket, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import non-stream ticket %d\n", rv);
        goto out;
    }
    APP_LOG("Imported non-stream ticket\n");

    /* Import TMD */
    sh_nostream_tmd = dupToSharedAligned((u8 *)nostream_tmd, sizeof(nostream_tmd));
    rv = ES_ImportTitleInit(sh_nostream_tmd, sizeof(nostream_tmd), sh_cert, 
             CERT_SIZE, NULL, 0, ES_TRANSFER_SERVER, 1);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title init %d\n", rv);
        goto out;
    }
    rv = ES_ImportTitleDone();
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title done %d\n", rv);
        goto out;
    }
    APP_LOG("Imported non-stream tmd\n");

    rv = ES_GetTicketViews(titleId, NULL, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
        goto out;
    }
    APP_LOG("Found %d ticket(s) for title ID 0x%08x/0x%08x\n", ticketCnt, 
        tidHi(titleId), tidLo(titleId));

    rv = ES_GetTicketViews(titleId, ticketViewList, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, NULL, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, tmd, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }

    /* Setup stream key using ticket 1 */
    rv = ES_SetupStreamKey(&ticketViewList[0], tmd, tmdSize, hStreamKey);
    if (rv!=ES_ERR_OK && rv==ES_ERR_INVALID) {
        APP_LOG("SetupStreamKey failed for non-stream title, rv=%d -> OK "
            "(as expected)\n", rv);
        rvFinal = ES_ERR_OK;
    }
    else {
        APP_LOG("ERROR: SetupStreamKey should fail due to non-stream title, "
            "rv=%d -> FAIL\n", rv);
        rvFinal = ES_ERR_INVALID;
    }

    rv = rvFinal;

out:
    APP_LOG("Removing title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);
    
    if (sh_nostream_ticket) IOS_Free(0, sh_nostream_ticket);
    if (sh_nostream_tmd) IOS_Free(0, sh_nostream_tmd);

    return rv;
}
#endif  /* TEST_NO_STREAM */


#if defined(TEST_STREAM)
static ESError
initStreamTest(ESTitleId titleId, ESTitleMeta *tmd, u32 *tmdSize)
{
    ESError         rv = ES_ERR_OK;
    //u32 tmdSize;
    u32 i, ticketCnt;

    APP_LOG("Deleting title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    /* Import the tickets */
    sh_ticket1_1 = dupToSharedAligned((u8 *)ticket1_1, sizeof(ticket1_1));
    rv = ES_ImportTicket(sh_ticket1_1, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket1_1, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket1_1\n");

    sh_ticket1_2 = dupToSharedAligned((u8 *)ticket1_2, sizeof(ticket1_2));
    rv = ES_ImportTicket(sh_ticket1_2, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket1_2, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket1_2\n");

    sh_ticket1_3 = dupToSharedAligned((u8 *)ticket1_3, sizeof(ticket1_3));
    rv = ES_ImportTicket(sh_ticket1_3, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket1_3, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket1_3\n");

    sh_ticket1_4 = dupToSharedAligned((u8 *)ticket1_4, sizeof(ticket1_4));
    rv = ES_ImportTicket(sh_ticket1_4, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket1_4, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket1_4\n");

    /* Import TMD */
    sh_stream_tmd = dupToSharedAligned((u8 *)stream_tmd, sizeof(stream_tmd));
    rv = ES_ImportTitleInit(sh_stream_tmd, sizeof(stream_tmd), sh_cert, CERT_SIZE, 
             NULL, 0, ES_TRANSFER_SERVER, 1);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title init, rv=%d\n", rv);
        goto out;
    }
    rv = ES_ImportTitleDone();
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title done, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported tmd\n");

    rv = ES_GetTicketViews(titleId, NULL, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
        goto out;
    }
    APP_LOG("Found %d ticket(s) for title ID 0x%08x/0x%08x\n", ticketCnt, 
        tidHi(titleId), tidLo(titleId));

    // ticketViewList must both be 32B aligned and 32B size multiple    
    rv = ES_GetTicketViews(titleId, ticketViewList, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, NULL, tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, tmd, tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }

    dumpTmdAndTicketViews(tmd, ticketViewList, ticketCnt);

    /* Verify ticket ID */
    for (i=0; i < ticketCnt; i++) {
        if (ticketViewList[i].ticketId != ticketIdList1[i]) {
            APP_LOG("ERROR: Incorrect ticket ID %d: exp=0x%llx actual=0x%llx\n",
                i, ticketIdList1[i], ticketViewList[i].ticketId);
            rv = ES_ERR_INVALID;
            goto out;
        }
    }
    APP_LOG("Verified ticket ID in %d ticket views\n", ticketCnt);

out:
    if (sh_stream_tmd) IOS_Free(0, sh_stream_tmd);
    if (sh_ticket1_1) IOS_Free(0, sh_ticket1_1);
    if (sh_ticket1_2) IOS_Free(0, sh_ticket1_2);
    if (sh_ticket1_3) IOS_Free(0, sh_ticket1_3);
    if (sh_ticket1_4) IOS_Free(0, sh_ticket1_4);

    return rv;

}

static ESError
testStream1(ESTitleId titleId)
{
    ESError         rv = ES_ERR_OK;
    ESError         rvFinal = ES_ERR_OK;
    u32 i=0, tmdSize=0;


    /* Start with a clean slate by delete the test title */
    APP_LOG("\n");
    APP_LOG("*** Testing stream title = %08x/%08x\n", 
        tidHi(titleId), tidLo(titleId));

    rv = initStreamTest(titleId, tmd, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("Test initialization failed, rv=%d\n", rv);
        goto out;
    }

    /* Setup stream key using ticket 4 (no access title info) - should fail */
    APP_LOG("Setting up stream key using ticket 4 -> should fail\n");
    memset((u8 *)ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)ticketView, (u8 *)&(ticketViewList[3]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(ticketView, tmd, tmdSize, hStreamKey);
    if (rv!=ES_ERR_OK) {
        if (rv==ES_ERR_NO_RIGHT) {
            APP_LOG("SetupStreamKey failed for empty access title info, rv=%d "
                "-> OK (as expected)\n", rv);
            rv=ES_ERR_OK;
        }
        else {
            APP_LOG("SetupStreamKey failed, rv=%d -> FAIL\n", rv);
            rvFinal = rv;
            goto out;
        }
    }
    else {
        APP_LOG("ERROR: SetupStreamKey succeeded, should fail for empty access "
            "title info -> FAIL\n");
        DUMP_TICKETVIEW(ticketView);
        rvFinal = ES_ERR_INVALID;
    
        rv = ES_DeleteStreamKey(*hStreamKey);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv);
            goto out;
        }
        APP_LOG("Deleted stream key handle %d\n", *hStreamKey);
        *hStreamKey = 0;
    }

    /* Setup stream key using ticket 1 - accessible to all titles */
    APP_LOG("Setting up stream key using ticket 1 -> should pass\n");
    memset((u8 *)ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)ticketView, (u8 *)&(ticketViewList[0]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(ticketView, tmd, tmdSize, hStreamKey);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamKey failed for ticket 1, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream key successfully, got handle %d\n", *hStreamKey);

    /* 
     * Decrypt test of data content index 1 - large stream data
     */

    /* Setup stream key for content index 1 */
    rv = ES_SetupStreamIv(1, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 1\n");
    DUMP_IV((u8 *)iv);

    memset(dataBuf, 0, DATA_BUF_SZ);
    sh_stream_data = dupToSharedAligned((u8 *)stream_data, sizeof(stream_data));
    APP_LOG("Decrypting stream data...\n", i);
    for (i=0; i< (sizeof(stream_data)/(64*1024)); i++) {
        APP_LOG("[%3d] Decrypting 64K chunk of data...\n", i);
        rv = ES_Decrypt(*hStreamKey, *iv, ((u8*)sh_stream_data)+i*64*1024, 
                 64*1024, dataBuf);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: Decrypt of stream data failed, rv=%d\n", rv);
            goto out;
        }
        rv = memcmp(stream_data_raw+i*64*1024, dataBuf, 64*1024);
        if (rv!=0) {
            APP_LOG("ERROR: Decrypt of data mismatch byte %d: 0x%x:0x%x\n", i, 
                dataBuf[i], stream_data_raw[i*64*1024]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Decrypted stream data successfully\n");

    /* 
     * Decrypt/encrypt test of data content index 0
     */

    /* Setup stream key for content index 0 */
    rv = ES_SetupStreamIv(0, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    DUMP_IV((u8 *)iv);

    /* Data In: data1, Data Out: dataBuf */
    memset(dataBuf, 0, DATA_BUF_SZ);
    sh_data1 = dupToSharedAligned((u8 *)data1, sizeof(data1));
    rv = ES_Decrypt(*hStreamKey, *iv, (u8*)sh_data1, sizeof(data1), dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted data1 successfully\n");
    for (i=0; i < sizeof(data1_raw); i++) {
        if (dataBuf[i] != data1_raw[i]) {
            APP_LOG("ERROR: Decrypt of data1(%d) mismatch byte %d: 0x%x:0x%x\n", 
                sizeof(data1), i, dataBuf[i], data1_raw[i]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared decrypted data1 successfully\n");

    /* Data In: data1_raw, Data Out: dataBuf */
    memset(dataBuf, 0, DATA_BUF_SZ);
    /* Setup stream key for content index 0 */
    rv = ES_SetupStreamIv(0, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    DUMP_IV((u8 *)iv);
    APP_LOG("Encrypting data1, size: data1=%d data1_raw=%d\n",
        sizeof(data1), sizeof(data1_raw));
    sh_data1_raw = dupToSharedAligned((u8 *)data1_raw, sizeof(data1));
    rv = ES_Encrypt(*hStreamKey, *iv, (u8*)sh_data1_raw, sizeof(data1), dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Encrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Encrypted data1 successfully\n");
    for (i=0; i < sizeof(data1); i++) {
        if (dataBuf[i] != data1[i]) {
            APP_LOG("ERROR: Encrypt of data1(%d) mismatch byte %d: 0x%x:0x%x\n",
                sizeof(data1), i, dataBuf[i], data1[i]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared encrypted data1 successfully\n");

    /* 
     * Encrypt/decrypt test of 64K data 
     */

    /* Data In: dataBuf, Data Out: dataBuf */
    memset(dataIv, 0x0, DATA_IV_SZ);
    memset(dataBuf, 0xff, DATA_BUF_SZ);
    rv = ES_Encrypt(*hStreamKey, dataIv, dataBuf, (u32) 64*1024, dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Encrypt of 64K failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Encrypted 64K successfully\n");

    /* Check the first 10 bytes to make sure that data buffer is modified */
    for (i=0; i<10; i++) {
        if (dataBuf[i] == 0xff) {
            APP_LOG("ERROR: 64K Encrypt incorrect byte %d\n", i);
            rv = -1;
            goto out;
        }
    }

    memset(dataIv, 0x0, DATA_IV_SZ);
    rv = ES_Decrypt(*hStreamKey, dataIv, dataBuf, (u32) 64*1024, dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of 64K failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted 64K successfully\n");
    for (i=0; i<64*1024; i++) {
        if (dataBuf[i] != 0xff) {
            APP_LOG("ERROR: 64K Encrypt/Decrypt data mismatch byte %d: 0x%x\n",
                i, dataBuf[i]);
            rv = ES_ERR_INVALID;
            goto out;
        }
    }
    APP_LOG("Compared 64K successfully\n");

    rv = rvFinal;

out:
    APP_LOG("Removing title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    if (sh_data1) IOS_Free(0, sh_data1);
    if (sh_data1_raw) IOS_Free(0, sh_data1_raw);

    if (*hStreamKey > 0) {
        ESError rv2 = ES_ERR_OK;
        rv2 = ES_DeleteStreamKey(*hStreamKey);
        if (rv2!=ES_ERR_OK) {
            APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv2);
        }
        else {
            APP_LOG("Deleted stream key handle %d\n", *hStreamKey);
        }
    }

    return rv;
}
#endif  /* TEST_STREAM */


#if defined(TEST_WFS)
static ESError
initWfsTest(ESTitleId titleId, ESTitleMeta *tmd, u32 *tmdSize)
{
    ESError         rv = ES_ERR_OK;
    //u32 tmdSize;
    u32 i, ticketCnt;

    APP_LOG("Deleting title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    /* Import the tickets */
    sh_ticket2_1 = dupToSharedAligned((u8 *)ticket2_1, sizeof(ticket2_1));
    rv = ES_ImportTicket(sh_ticket2_1, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import wfs ticket2_1, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket2_1\n");

    sh_ticket2_2 = dupToSharedAligned((u8 *)ticket2_2, sizeof(ticket2_2));
    rv = ES_ImportTicket(sh_ticket2_2, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import wfs ticket2_2, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket2_2\n");

    sh_ticket2_3 = dupToSharedAligned((u8 *)ticket2_3, sizeof(ticket2_3));
    rv = ES_ImportTicket(sh_ticket2_3, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import wfs ticket2_3, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket2_3\n");

    sh_ticket2_4 = dupToSharedAligned((u8 *)ticket2_4, sizeof(ticket2_4));
    rv = ES_ImportTicket(sh_ticket2_4, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import wfs ticket2_4, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket2_4\n");

    /* Import TMD */
    sh_wfs_tmd = dupToSharedAligned((u8 *)wfs_tmd, sizeof(wfs_tmd));
    rv = ES_ImportTitleInit(sh_wfs_tmd, sizeof(wfs_tmd), sh_cert, CERT_SIZE, 
             NULL, 0, ES_TRANSFER_SERVER, 1);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title init, rv=%d\n", rv);
        goto out;
    }
    rv = ES_ImportTitleDone();
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title done, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported tmd\n");

    rv = ES_GetTicketViews(titleId, NULL, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
        goto out;
    }
    APP_LOG("Found %d ticket(s) for title ID 0x%08x/0x%08x\n", ticketCnt, 
        tidHi(titleId), tidLo(titleId));

    // ticketViewList must both be 32B aligned and 32B size multiple    
    rv = ES_GetTicketViews(titleId, ticketViewList, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, NULL, tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, tmd, tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }

    dumpTmdAndTicketViews(tmd, ticketViewList, ticketCnt);

    /* Verify ticket ID */
    for (i=0; i < ticketCnt; i++) {
        if (ticketViewList[i].ticketId != ticketIdList2[i]) {
            APP_LOG("ERROR: Incorrect ticket ID %d: exp=0x%llx actual=0x%llx\n",
                i, ticketIdList2[i], ticketViewList[i].ticketId);
            rv = ES_ERR_INVALID;
            goto out;
        }
    }
    APP_LOG("Verified ticket ID in %d ticket views\n", ticketCnt);

out:
    if (sh_wfs_tmd) IOS_Free(0, sh_wfs_tmd);
    if (sh_ticket2_1) IOS_Free(0, sh_ticket2_1);
    if (sh_ticket2_2) IOS_Free(0, sh_ticket2_2);
    if (sh_ticket2_3) IOS_Free(0, sh_ticket2_3);
    if (sh_ticket2_4) IOS_Free(0, sh_ticket2_4);

    return rv;

}

static ESError testWfs1(ESTitleId titleId)
{
    ESError         rv = ES_ERR_OK;
    ESError         rvFinal = ES_ERR_OK;
    u32 i=0, tmdSize=0;


    /* Start with a clean slate by delete the test title */
    APP_LOG("\n");
    APP_LOG("*** Testing WFS title = %08x/%08x\n", 
        tidHi(titleId), tidLo(titleId));

    rv = initWfsTest(titleId, tmd, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("Test initialization failed, rv=%d\n", rv);
        goto out;
    }

    /* Setup stream key using ticket 4 (no access title info) - should fail */
    APP_LOG("Setting up stream key using ticket 4 -> should fail\n");
    memset((u8 *)ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)ticketView, (u8 *)&(ticketViewList[3]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(ticketView, tmd, tmdSize, hStreamKey);
    if (rv!=ES_ERR_OK) {
        if (rv==ES_ERR_NO_RIGHT) {
            APP_LOG("SetupStreamKey failed for empty access title info, rv=%d "
                "-> OK (as expected)\n", rv);
        }
        else {
            APP_LOG("ERROR: SetupStreamKey failed for empty access title info,"
                " rv=%d -> FAIL\n", rv);
            rvFinal = rv;
        }
    }
    else {
        APP_LOG("ERROR: SetupStreamKey succeeded, should fail due to empty "
            "accessed title info -> FAIL\n");
        DUMP_TICKETVIEW(ticketView);
        rvFinal = ES_ERR_INVALID;

        APP_LOG("Setup stream key successfully, got handle %d\n", *hStreamKey);

        rv = ES_DeleteStreamKey(*hStreamKey);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv);
            goto out;
        }
        APP_LOG("Deleted stream key handle %d\n", *hStreamKey);
        *hStreamKey = 0;
    }

    /* Setup stream key using ticket 1 - accessible to all titles */
    APP_LOG("Setting up stream key using ticket 1 -> should pass\n");
    memset((u8 *)ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)ticketView, (u8 *)&(ticketViewList[0]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(ticketView, tmd, tmdSize, hStreamKey);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamKey failed for ticket 1, rv=%d -> FAIL\n", 
            rv);
        goto out;
    }
    APP_LOG("Setup stream key successfully, got handle %d\n", *hStreamKey);

    /* 
     * Decrypt test of data content index 1 - large stream data
     */

    /* Setup stream key for content index 1 */
    rv = ES_SetupStreamIv(1, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 1\n");
    DUMP_IV((u8 *)iv);

    APP_LOG("Decrypting stream data...\n", i);
    sh_wfs_stream_data = dupToSharedAligned((u8 *)wfs_stream_data, sizeof(wfs_stream_data));
    for (i=0; i< (sizeof(wfs_stream_data)/(64*1024)); i++) {
        APP_LOG("[%3d] Decrypting 64K chunk of data...\n", i);
        rv = ES_Decrypt(*hStreamKey, *iv, ((u8*)sh_wfs_stream_data)+i*64*1024, 
                 64*1024, dataBuf);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: Decrypt of stream data failed, rv=%d\n", rv);
            goto out;
        }
        rv = memcmp(wfs_stream_data_raw+i*64*1024, dataBuf, 64*1024);
        if (rv!=0) {
            APP_LOG("ERROR: Decrypt of data mismatch byte %d: 0x%x:0x%x\n", i, 
                dataBuf[i], wfs_stream_data_raw[i*64*1024]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Decrypted stream data successfully\n");

    /* 
     * Decrypt/encrypt test of data content index 0
     */

    /* Setup stream key for content index 0 */
    rv = ES_SetupStreamIv(0, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    DUMP_IV((u8 *)iv);

    /* Data In: wfs_data1, Data Out: dataBuf */
    memset(dataBuf, 0, DATA_BUF_SZ);
    sh_wfs_data1 = dupToSharedAligned((u8 *)wfs_data1, sizeof(wfs_data1));
    rv = ES_Decrypt(*hStreamKey, *iv, (u8*)sh_wfs_data1, sizeof(wfs_data1), dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted data1 successfully\n");
    for (i=0; i < sizeof(wfs_data1); i++) {
        if (dataBuf[i] != wfs_data1_raw[i]) {
            APP_LOG("ERROR: Decrypt of data1 mismatch byte %d: 0x%x:0x%x\n", i, 
                dataBuf[i], wfs_data1_raw[i]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared decrypted data1 successfully\n");

    /* Data In: data1_raw, Data Out: dataBuf */
    memset(dataBuf, 0, DATA_BUF_SZ);
    /* Setup stream key for content index 0 */
    rv = ES_SetupStreamIv(0, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    DUMP_IV((u8 *)iv);
    sh_wfs_data1_raw = dupToSharedAligned((u8 *)wfs_data1_raw, sizeof(wfs_data1));
    rv = ES_Encrypt(*hStreamKey, *iv, (u8*)sh_wfs_data1_raw, sizeof(wfs_data1), 
             dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Encrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Encrypted data1 successfully\n");
    for (i=0; i < sizeof(wfs_data1); i++) {
        if (dataBuf[i] != wfs_data1[i]) {
            APP_LOG("ERROR: Encrypt of data1 mismatch byte %d: 0x%x:0x%x\n", i, 
                dataBuf[i], wfs_data1[i]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared encrypted data1 successfully\n");

    /* 
     * Encrypt/decrypt test of 64K data 
     */

    /* Data In: dataBuf, Data Out: dataBuf */
    memset(dataIv, 0x0, DATA_IV_SZ);
    memset(dataBuf, 0xff, DATA_BUF_SZ);
    rv = ES_Encrypt(*hStreamKey, dataIv, dataBuf, (u32) 64*1024, dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Encrypt of 64K failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Encrypted 64K successfully\n");

    /* Check the first 10 bytes to make sure that data buffer is modified */
    for (i=0; i<10; i++) {
        if (dataBuf[i] == 0xff) {
            APP_LOG("ERROR: 64K Encrypt incorrect byte %d\n", i);
            rv = -1;
            goto out;
        }
    }

    memset(dataIv, 0x0, DATA_IV_SZ);
    rv = ES_Decrypt(*hStreamKey, dataIv, dataBuf, (u32) 64*1024, dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of 64K failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted 64K successfully\n");
    for (i=0; i<64*1024; i++) {
        if (dataBuf[i] != 0xff) {
            APP_LOG("ERROR: 64K Encrypt/Decrypt data mismatch byte %d: 0x%x\n",
                i, dataBuf[i]);
            rv = ES_ERR_INVALID;
            goto out;
        }
    }
    APP_LOG("Compared 64K successfully\n");

    rv = rvFinal;

out:
    APP_LOG("Removing title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    if (sh_wfs_stream_data) IOS_Free(0, sh_wfs_stream_data);
    if (sh_wfs_data1) IOS_Free(0, sh_wfs_data1);
    if (sh_wfs_data1_raw) IOS_Free(0, sh_wfs_data1_raw);

    if (*hStreamKey > 0) {
        ESError rv2 = ES_ERR_OK;
        rv2 = ES_DeleteStreamKey(*hStreamKey);
        if (rv2!=ES_ERR_OK) {
            APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv2);
        }
        else {
            APP_LOG("Deleted stream key handle %d\n", *hStreamKey);
        }
    }

    return rv;

}  /* testWfs1 */


ESError
TestWfsStream() 
{
    /* Initialize various global memory structures */
    initializeMemory();

    return(testWfs1(WFS_TITLE_ID));
}


#endif  /* TEST_WFS */


#if defined(TEST_STREAM_WFS)
static ESError
initStreamWfsTest(ESTitleId titleId, ESTitleMeta *tmd, u32 *tmdSize)
{
    ESError         rv = ES_ERR_OK;
    u32 i, ticketCnt;

    APP_LOG("Deleting title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    /* Import the tickets */
    sh_ticket3_1 = dupToSharedAligned((u8 *)ticket3_1, sizeof(ticket3_1));
    rv = ES_ImportTicket(sh_ticket3_1, sh_cert, CERT_SIZE, NULL, 0, 
             ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import wfs ticket3_1, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket3_1\n");

    /* Import TMD */
    sh_str_wfs_tmd = dupToSharedAligned((u8 *)str_wfs_tmd, sizeof(str_wfs_tmd));
    rv = ES_ImportTitleInit(sh_str_wfs_tmd, sizeof(str_wfs_tmd), sh_cert, CERT_SIZE, 
             NULL, 0, ES_TRANSFER_SERVER, 1);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title init, rv=%d\n", rv);
        goto out;
    }
    rv = ES_ImportTitleDone();
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import title done, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported tmd\n");

    rv = ES_GetTicketViews(titleId, NULL, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d \n", rv);
        goto out;
    }
    APP_LOG("Found %d ticket(s) for title ID 0x%08x/0x%08x\n", ticketCnt, 
        tidHi(titleId), tidLo(titleId));

    // ticketViewList must both be 32B aligned and 32B size multiple    
    rv = ES_GetTicketViews(titleId, ticketViewList, &ticketCnt);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTicketViews failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, NULL, tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }
    rv = ES_GetTmd(titleId, tmd, tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }

    dumpTmdAndTicketViews(tmd, ticketViewList, ticketCnt);

    /* Verify ticket ID */
    for (i=0; i < ticketCnt; i++) {
        if (ticketViewList[i].ticketId != ticketIdList3[i]) {
            APP_LOG("ERROR: Incorrect ticket ID %d: exp=0x%llx actual=0x%llx\n",
                i, ticketIdList3[i], ticketViewList[i].ticketId);
            rv = ES_ERR_INVALID;
            goto out;
        }
    }
    APP_LOG("Verified ticket ID in %d ticket views\n", ticketCnt);

out:
    if (sh_str_wfs_tmd) IOS_Free(0, sh_str_wfs_tmd);
    if (sh_ticket3_1) IOS_Free(0, sh_ticket3_1);

    return rv;

}  /* initStreamWfsTest */


static ESError
testStreamWfs1(ESTitleId titleId)
{
    ESError         rv = ES_ERR_OK;
    ESError         rvFinal = ES_ERR_OK;
    u32 i=0, tmdSize=0;


    /* Start with a clean slate by delete the test title */
    APP_LOG("\n");
    APP_LOG("*** Testing Stream+WFS title = %08x/%08x\n", 
        tidHi(titleId), tidLo(titleId));

    rv = initStreamWfsTest(titleId, tmd, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("Test initialization failed, rv=%d\n", rv);
        goto out;
    }

    *hStreamKey = 0;

    /* Setup stream key using ticket 1 - accessible to all titles */
    APP_LOG("Setting up stream key using ticket 1 -> should fail\n");
    memset((u8 *)ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)ticketView, (u8 *)&(ticketViewList[0]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(ticketView, tmd, tmdSize, hStreamKey);
    if (rv!=ES_ERR_OK) {
        if (rv==ES_ERR_INVALID) {
            APP_LOG("SetupStreamKey failed for ticket 1, rv=%d -> OK "
                "(as expected)\n", rv);
            rv = ES_ERR_OK;
        }
        else {
            APP_LOG("ERROR: SetupStreamKey failed for ticket 1, rv=%d "
                "-> FAIL\n", rv);
        }
        goto out;
    }
    else {
        APP_LOG("ERROR: SetupStreamKey succeeded, handle %d -> FAIL\n", 
            *hStreamKey);
        rvFinal = ES_ERR_INVALID;
    }

    /* 
     * Decrypt test of data content index 1 - large stream data
     */

    /* Setup stream key for content index 1 */
    rv = ES_SetupStreamIv(1, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 1\n");
    DUMP_IV((u8 *)iv);

    APP_LOG("Decrypting stream data...\n", i);
    sh_str_wfs_stream_data = dupToSharedAligned((u8 *)str_wfs_stream_data, sizeof(str_wfs_stream_data));
    for (i=0; i< (sizeof(str_wfs_stream_data)/(64*1024)); i++) {
        APP_LOG("[%3d] Decrypting 64K chunk of data...\n", i);
        rv = ES_Decrypt(*hStreamKey, *iv, ((u8*)sh_str_wfs_stream_data)+i*64*1024, 
                 64*1024, dataBuf);
        if (rv!=ES_ERR_OK) {
            APP_LOG("ERROR: Decrypt of stream data failed, rv=%d\n", rv);
            goto out;
        }
    }
    APP_LOG("Decrypted stream data successfully\n");

    /* 
     * Decrypt/encrypt test of data content index 0
     */

    /* Setup stream key for content index 0 */
    rv = ES_SetupStreamIv(0, *iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    DUMP_IV((u8 *)iv);

    /* Data In: wfs_data1, Data Out: dataBuf */
    memset(dataBuf, 0, DATA_BUF_SZ);
    sh_str_wfs_data1 = dupToSharedAligned((u8 *)str_wfs_data1, sizeof(str_wfs_data1));
    rv = ES_Decrypt(*hStreamKey, *iv, (u8*)sh_str_wfs_data1, sizeof(str_wfs_data1), 
             dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted data1 successfully\n");

    rv = rvFinal;

out:
    APP_LOG("Removing title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    if (sh_str_wfs_data1) IOS_Free(0, sh_str_wfs_data1);
    if (sh_str_wfs_stream_data) IOS_Free(0, sh_str_wfs_stream_data);

    if (*hStreamKey > 0) {
        ESError rv2 = ES_ERR_OK;
        rv2 = ES_DeleteStreamKey(*hStreamKey);
        if (rv2!=ES_ERR_OK) {
            APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv2);
        }
        else {
            APP_LOG("Deleted stream key handle %d\n", *hStreamKey);
        }
    }

    return rv;

}  /* testStreamWfs1 */

#endif  /* TEST_STREAM_WFS */


#if defined(STAND_ALONE)
s32
main(int argc, char *argv[])
{
    ESError         rv = ES_ERR_OK;
    ESTitleId titleId;
    u32 testNum = 0;
    u32 totalErrCnt = 0;

    IOSProcessId    pid;
    IOSUid          uid;
    IOSGid          gid;
    u8 testDir[64];

#define WFS_DIR         "/wfs"
#define WFS_TEST_DIR    "wfstest"


    rv = ES_InitLib();
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Failed to initialize ES library, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Initialized ES library\n");

    pid = IOS_GetProcessId();
    APP_LOG("*** PID=0x%x\n", pid);

    uid = IOS_GetUid();
    gid = IOS_GetGid();
    APP_LOG("*** UID=0x%x, GID=0x%x\n", uid, gid);

    IOS_SetUid(pid, 0);
    IOS_SetGid(pid, 0);

    uid = IOS_GetUid();
    gid = IOS_GetGid();
    APP_LOG("*** UID=0x%x, GID=0x%x\n", uid, gid);

    /* Initialize various global memory structures */
    initializeMemory();

    /* Create test dir */
    snprintf(testDir, 64, "%s/%s", WFS_DIR, WFS_TEST_DIR);
    rv = ISFS_CreateDir(testDir, 0, ISFS_RW_ACCESS, 0, 0);
    if (rv != ISFS_ERROR_OK) {
        APP_LOG("ERROR: Failed create directory (%s), rv=%d\n", testDir, rv);
    }
    else {
        APP_LOG("Created directory (%s)\n", testDir);
    }
    rv = ISFS_SetAttr(testDir, uid, gid, 0, ISFS_RW_ACCESS, 0, 0);
    if (rv != ISFS_ERROR_OK) {
        APP_LOG("ERROR: Failed to set attr on (%s), rv=%d\n", testDir, rv);
    }
    else {
        APP_LOG("Set attributes to (%s)\n", testDir);
    }

    /* Start with a clean slate by delete the test title */
    *hStreamKey = 0;
    testNum = 0;
    totalErrCnt = 0;

    /*********************************************************************
     * Test #1:
     *   - Test against ticket that does NOT have stream title type
     */
    testNum++;
    titleId = NOSTREAM_TITLE_ID;
    APP_LOG("*******************************************************\n");
    APP_LOG("Test #%d\n", testNum);
    rv = testNoStream(titleId);
    if (rv==ES_ERR_OK) {
        APP_LOG("Test #%d -> PASS\n\n", testNum);
    }
    else {
        APP_LOG("Test #%d -> FAIL\n\n", testNum);
        totalErrCnt++;
    }

    /*********************************************************************
     * Test #2:
     *   - Test against ticket that has stream title type
     */
    testNum++;
    titleId = STREAM_TITLE_ID;
    APP_LOG("*******************************************************\n");
    APP_LOG("Test #%d\n", testNum);
    rv = testStream1(titleId);
    if (rv==ES_ERR_OK) {
        APP_LOG("Test #%d -> PASS\n\n", testNum);
    }
    else {
        APP_LOG("Test #%d -> FAIL\n\n", testNum);
        totalErrCnt++;
    }

    /*********************************************************************
     * Test #3:
     *   - Test against ticket that has WFS title type
     */
    testNum++;
    titleId = WFS_TITLE_ID;
    APP_LOG("*******************************************************\n");
    APP_LOG("Test #%d\n", testNum);
    rv = testWfs1(titleId);
    if (rv==ES_ERR_OK) {
        APP_LOG("Test #%d -> PASS\n\n", testNum);
    }
    else {
        APP_LOG("Test #%d -> FAIL\n\n", testNum);
        totalErrCnt++;
    }

    /*********************************************************************
     * Test #4:
     *   - Test against ticket that has both STREAM and WFS title type
     */
    testNum++;
    titleId = STREAM_WFS_TITLE_ID;
    APP_LOG("*******************************************************\n");
    APP_LOG("Test #%d\n", testNum);
    rv = testStreamWfs1(titleId);
    if (rv==ES_ERR_OK) {
        APP_LOG("Test #%d -> PASS\n\n", testNum);
    }
    else {
        APP_LOG("Test #%d -> FAIL\n\n", testNum);
        totalErrCnt++;
    }

out:
    (void) ES_CloseLib();
    APP_LOG("Closed ES library\n\n");

    APP_LOG("*******************************************************\n");
    APP_LOG("ES Stream Tests Completed: %d errors\n", totalErrCnt);
    APP_LOG("*******************************************************\n");

    return (rv);
}

#endif  /* STAND_ALONE */

