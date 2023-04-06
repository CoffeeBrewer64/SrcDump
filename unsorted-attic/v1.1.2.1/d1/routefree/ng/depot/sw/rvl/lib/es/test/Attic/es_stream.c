a0 624
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

#if defined(NEXT_GEN)
#include <ioslibc.h>
#include <iostypes.h>
#include <ios.h>
#include <fs.h>
#include <es.h>
#include <es_int.h>
#define APP_LOG(s, args...)     printf(s, ## args) 
#define APP_LOG2(s, args...)    printf(s, ## args) 
#define OSRoundUp32B(x)         (((u32)(x) + 32 - 1) & ~(32 - 1))
#elif defined(BROADWAY_REV)
#include <revolution.h>
#include <demo.h>
#include <string.h>
#include <private/iostypes.h>
#include <private/fs.h>
#include <private/es.h>
#include <private/iosresclt.h>
#include <secure/iosccert.h>
#include <private/autotest.h>
#define APP_LOG(...) OSReport("APP: " __VA_ARGS__)
#define APP_LOG2(...) OSReport(__VA_ARGS__)
IOSError IPCCltInit(void);
#endif

#define STACK_SIZE                  2*1024
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 9;

#define CERT_SIZE           3136
#define STREAM_TITLE_ID     0x1000012345678ULL
#define NOSTREAM_TITLE_ID   0x1000023456789ULL
//#define APP_SIZE            656640

#include "cert_data.c"
#include "es_stream_data.c"

/* 
 * Stream tmd:
 *  - stream_tmd: 
 *      - title ID: 0x0001000012345678
 *      - title type (0x5): ES_TITLE_TYPE_STREAM | ES_TITLE_TYPE_NG_TITLE
 *      - 2 contents: data1 (rom3.rom), stream_data (stream_raw.bin)
 * 
 * Stream tickets:
 *  - title ID: 0x0001000012345678
 *  - ticket1: common, ticket ID 0x5000, access enabled for all titles
 *  - ticket2: common, ticket ID 0x5001, access enabled for title ID 0x30303030
 *  - ticket3: common, ticket ID 0x5002, access enabled for title ID 0x10101010
 */
#define TICKET1_ID 0x5000ULL
#define TICKET2_ID 0x5001ULL
#define TICKET3_ID 0x5002ULL
#define TICKET4_ID 0x5003ULL

#define tidHi(t)    ((u32)((t)>>32))
#define tidLo(t)    ((u32)((t)&0xffffffffULL))

static ESTitleMeta  tmd __attribute__ ((aligned(32))); 

static u8           ticketViewListRoundUp32B[OSRoundUp32B(5*sizeof(ESTicketView))] __attribute__ ((aligned(32)));
static ESTicketView *ticketViewList = (ESTicketView*)ticketViewListRoundUp32B;
static ESTicketView ticketView __attribute__ ((aligned(32)));

static ESTicketId   ticketIdList[4] = { 
                        TICKET1_ID, TICKET2_ID, TICKET3_ID, TICKET4_ID };

/* Key store handle should start from 12 since default handles use 0-11 */
static IOSCSecretKeyHandle  hStreamKey;
static IOSCAesIv            iv __attribute__ ((aligned(32))); 

static u8 dataIv[16] __attribute__ ((aligned(32)));
static u8 dataBuf[65*1024] __attribute__ ((aligned(32)));


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
            memcpy(&ticketView, tvp, sizeof(ESTicketView));
            rv = ES_DeleteTicket(&ticketView);
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


s32
main(int argc, char *argv[])
{
    ESError         rv = ES_ERR_OK;
    u32 tmdSize;
    u32 ticketCnt;
    ESTitleId titleId;
    u32 i;

#ifdef USB_PRINT
    extern void *__usbPrintfBuf;
    __usbPrintfBuf = IOS_AllocAligned(0, 16, 16);
#endif

#if defined(BROADWAY_REV)
    IPCCltInit();
    VIInit();
    DVDInit();
    APP_LOG("ES Stream Test start\n");
    ATSTInit(&argc, argv, ATST_INFO);
#endif

#ifdef ESTESTS
    rv = ISFS_OpenLib();
    if (rv!=ISFS_ERROR_OK) {
        goto out1;
    }
#endif
    rv = ES_InitLib();
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Failed to initialize ES library, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Initialized ES library\n");

    /* Start with a clean slate by delete the test title */
    hStreamKey = 0;
    titleId = NOSTREAM_TITLE_ID;
    APP_LOG("\n");
    APP_LOG("*** Testing non-stream title = %08x/%08x\n", 
        tidHi(titleId), tidLo(titleId));
    APP_LOG("Deleting title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    /* Import the ticket */
    rv = ES_ImportTicket(nostream_ticket, cert, CERT_SIZE, NULL, 0, ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import non-stream ticket %d\n", rv);
        goto out;
    }
    APP_LOG("Imported non-stream ticket\n");

    /* Import TMD */
    rv = ES_ImportTitleInit(nostream_tmd, sizeof(nostream_tmd), cert, CERT_SIZE, 
             NULL, 0, ES_TRANSFER_SERVER, 1);
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

    // JohnC: ticketViewList must both be 32B aligned and 32B size multiple    
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
    rv = ES_GetTmd(titleId, &tmd, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }

    /* Setup stream key using ticket 1 */
    rv = ES_SetupStreamKey(&ticketViewList[0], &tmd, tmdSize, &hStreamKey);
    if (rv!=ES_ERR_OK && rv==ES_ERR_INVALID) {
        APP_LOG("Setup stream key failed for non-stream title type, rv=%d (OK)\n",
            rv);
    }
    else {
        APP_LOG("ERROR: SetupStreamKey should fail due to non-stream title type, rv=%d\n", rv);
        rv = -1;
        goto out;
    }
    APP_LOG("Removing non-stream title = %08x/%08x\n", tidHi(titleId), 
        tidLo(titleId));
    removeTitle(titleId);

    /* Start with a clean slate by delete the test title */
    titleId = STREAM_TITLE_ID;
    APP_LOG("\n");
    APP_LOG("*** Testing stream title = %08x/%08x\n", 
        tidHi(titleId), tidLo(titleId));
    APP_LOG("Deleting title = %08x/%08x\n", tidHi(titleId), tidLo(titleId));
    removeTitle(titleId);

    /* Import the tickets */
    rv = ES_ImportTicket(ticket1, cert, CERT_SIZE, NULL, 0, ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket1, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket1\n");

    rv = ES_ImportTicket(ticket2, cert, CERT_SIZE, NULL, 0, ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket2, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket2\n");

    rv = ES_ImportTicket(ticket3, cert, CERT_SIZE, NULL, 0, ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket3, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket3\n");

    rv = ES_ImportTicket(ticket4, cert, CERT_SIZE, NULL, 0, ES_TRANSFER_SERVER);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: Failed to import stream ticket4, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Imported ticket4\n");

    /* Import TMD */
    rv = ES_ImportTitleInit(stream_tmd, sizeof(stream_tmd), cert, CERT_SIZE, 
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

    // JohnC: ticketViewList must both be 32B aligned and 32B size multiple    
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
    rv = ES_GetTmd(titleId, &tmd, &tmdSize);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: GetTmd failed, rv=%d\n", rv);
        goto out;
    }

//#ifdef VERBOSE
    dumpTmd(&tmd);
    for (i=0; i < ticketCnt; i++) {
        dumpTicketView(&ticketViewList[i]);
    }
    APP_LOG("\n");
//#endif

    /* Verify ticket ID */
    for (i=0; i < ticketCnt; i++) {
        if (ticketViewList[i].ticketId != ticketIdList[i]) {
            APP_LOG("ERRO: Incorrect ticket ID %d: exp=0x%llx actual=0x%llx\n",
                i, ticketIdList[i], ticketViewList[i].ticketId);
            goto out;
        }
    }
    APP_LOG("Verified ticket ID in %d ticket views\n", ticketCnt);

    /* Setup stream key using ticket 4 (no access title info) - should fail */
    APP_LOG("Setting up stream key using ticket 4 -> should fail\n");
    memset((u8 *)&ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)&ticketView, (u8 *)&(ticketViewList[3]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(&ticketView, &tmd, tmdSize, &hStreamKey);
    if (rv!=ES_ERR_OK && rv==ES_ERR_NO_RIGHT) {
        APP_LOG("Setup stream key failed for empty access title info, rv=%d (OK)\n",
            rv);
    }
    else {
        APP_LOG("ERROR: SetupStreamKey should fail due to empty accessed title info, rv=%d\n", rv);
        dumpTicketView(&ticketView);
        rv = -1;
        goto out;
    }

#if defined(BROADWAY_REV)
    APP_LOG("Setting up stream key using ticket 3 -> should fail\n");
    /* Setup stream key using ticket 3 - only for title ID 0x10101010 */
    memset((u8 *)&ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)&ticketView, (u8 *)&(ticketViewList[2]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(&ticketView, &tmd, tmdSize, &hStreamKey);
    if (rv!=ES_ERR_OK && rv==ES_ERR_NO_RIGHT) {
        APP_LOG("Setup stream key failed for wrong accessed title ID, rv=%d (OK)\n",
            rv);
    }
    else {
        APP_LOG("ERROR: SetupStreamKey should fail due to incorrect accessed title ID, rv=%d\n", rv);
        dumpTicketView(&ticketView);
        rv = -1;
        goto out;
    }

    /* Setup stream key using ticket 2 - only for title ID 0x30303030 */
    APP_LOG("Setting up stream key using ticket 2 -> should pass\n");
    memset((u8 *)&ticketView, 0, sizeof(ESTicketView));
    memcpy((u8 *)&ticketView, (u8 *)&(ticketViewList[1]), sizeof(ESTicketView));
    rv = ES_SetupStreamKey(&ticketView, &tmd, tmdSize, &hStreamKey);
    if (rv !=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamKey failed for ticket 2, rv=%d\n", rv);
        dumpTicketView(&ticketView);
        goto out;
    }
    APP_LOG("Setup stream key successfully, got handle %d\n", hStreamKey);

    rv = ES_DeleteStreamKey(hStreamKey);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Deleted stream key handle %d\n", hStreamKey);
    hStreamKey = 0;
#endif  /* BROADWAY_REV */

    /* Setup stream key using ticket 1 - accessible to all titles */
    APP_LOG("Setting up stream key using ticket 1 -> should pass\n");
    rv = ES_SetupStreamKey(&ticketViewList[0], &tmd, tmdSize, &hStreamKey);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamKey failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream key successfully, got handle %d\n", hStreamKey);

    /* 
     * Decrypt test of data content index 1 - large stream data
     */

    /* Setup stream key for content index 1 */
    rv = ES_SetupStreamIv(1, iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 1\n");
    dumpIv((u8 *)iv);

    APP_LOG("Decrypting stream data...\n", i);
    for (i=0; i< (sizeof(stream_data)/(64*1024)); i++) {
        APP_LOG("[%3d] Decrypting 64K chunk of data...\n", i);
        rv = ES_Decrypt(hStreamKey, iv, ((u8*)stream_data)+i*64*1024, 64*1024,
                 dataBuf);
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
    rv = ES_SetupStreamIv(0, iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    dumpIv((u8 *)iv);

    /* Data In: data1, Data Out: dataBuf */
    memset(dataBuf, 0, sizeof(dataBuf));
    rv = ES_Decrypt(hStreamKey, iv, (u8*)data1, sizeof(data1), dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted data1 successfully\n");
    for (i=0; i < sizeof(data1); i++) {
        if (dataBuf[i] != data1_raw[i]) {
            APP_LOG("ERROR: Decrypt of data1 mismatch byte %d: 0x%x:0x%x\n", i, 
                dataBuf[i], data1_raw[i]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared decrypted data1 successfully\n");

    /* Data In: data1_raw, Data Out: dataBuf */
    memset(dataBuf, 0, sizeof(dataBuf));
    /* Setup stream key for content index 0 */
    rv = ES_SetupStreamIv(0, iv);
    if (rv!=ES_ERR_OK) {
        APP_LOG("ERROR: SetupStreamIv for content index 0 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Setup stream iv for content index 0\n");
    dumpIv((u8 *)iv);
    rv = ES_Encrypt(hStreamKey, iv, (u8*)data1_raw, sizeof(data1), dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Encrypt of data1 failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Encrypted data1 successfully\n");
    for (i=0; i < sizeof(data1); i++) {
        if (dataBuf[i] != data1[i]) {
            APP_LOG("ERROR: Encrypt of data1 mismatch byte %d: 0x%x:0x%x\n", i, 
                dataBuf[i], data1[i]);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared encrypted data1 successfully\n");

    /* 
     * Encrypt/decrypt test of 64K data 
     */

    /* Data In: dataBuf, Data Out: dataBuf */
    memset(dataIv, 0x0, sizeof(dataIv));
    memset(dataBuf, 0xff, sizeof(dataBuf));
    rv = ES_Encrypt(hStreamKey, dataIv, dataBuf, (u32) 64*1024, dataBuf);
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

    memset(dataIv, 0x0, sizeof(dataIv));
    rv = ES_Decrypt(hStreamKey, dataIv, dataBuf, (u32) 64*1024, dataBuf);
    if (rv != ES_ERR_OK) {
        APP_LOG("ERROR: Decrypt of 64K failed, rv=%d\n", rv);
        goto out;
    }
    APP_LOG("Decrypted 64K successfully\n");
    for (i=0; i<64*1024; i++) {
        if (dataBuf[i] != 0xff) {
            APP_LOG("ERROR: 64K Encrypt/Decrypt data mismatch byte %d\n", i);
            rv = -1;
            goto out;
        }
    }
    APP_LOG("Compared 64K successfully\n");

out:
    if (hStreamKey > 0) {
        ESError rv2 = ES_ERR_OK;
        rv2 = ES_DeleteStreamKey(hStreamKey);
        if (rv2!=ES_ERR_OK) {
            APP_LOG("ERROR: DeleteStreamKey failed, rv=%d\n", rv2);
        }
        else {
            APP_LOG("Deleted stream key handle %d\n", hStreamKey);
        }
    }

    if (rv == ES_ERR_OK) {
        APP_LOG("Test PASSED.\n");
    }
    else {
        APP_LOG("Test FAILED.\n");
    }
#if defined(BROADWAY_REV)
    ATSTExit(rv);
#endif

    return (rv);
}
