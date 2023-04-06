/*
 *               Copyright (C) 2006, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: sd_app.c,v 1.4 2006/07/11 03:15:38 achan Exp $
 */


#include <iostypes.h>
#include <addr_map.h>
#include <iop.h>
#include <ios.h>
#include <iosc.h>
#include <ioslibc.h>
#include <sys.h>
#include <es.h>
#include <es_int.h>

#include "sd_app.h"


#define STACK_SIZE (16*1024)
const u8 _initStack[STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

/* Start of DDR */
#define SD_LOAD_ADDR    0x10000000

/* Location of OS and APP on SD card */
#define SD_OS_OFFSET     0x100000
#define SD_PPCAPP_OFFSET 0x200000

/* Led delay */
#define LED_DELAY       1000000

/*
 * Output a value to the LEDs
 */
void
outputLed(u8 value)
{
    IOS_OutputLed(value);
}

/*
 * Boot failed for some reason.   Loop flashing the reason
 * on the Leds.
 */
void
sdBootFailure(u32 reason)
{
    sdBootReport("SD boot failed, reason is %d\n", reason);

    while (1) {
        outputLed (reason);
        busDelay (LED_DELAY);
        outputLed (0);
        busDelay (LED_DELAY);
    }
}

static s32
importTitle(u32 offset, ESTitleId *titleId)
{
    ESError rv = ES_ERR_OK;
    u16 numContents;
    ESWadHeader *wadHdr;
    void *certList, *ticket, *contentOffset;
    ESTitleMeta *tmd;
    u8 *certPtr = 0;
    u8 *ticketPtr = 0;
    ESTitleMeta *tmdPtr = 0;

    wadHdr = (ESWadHeader *) offset;
    certList = (void *) offset + wadHdr->hdrSize;
    ticket = (void *) offset + wadHdr->hdrSize + wadHdr->certSize;
    tmd = (ESTitleMeta *) (offset + wadHdr->hdrSize + wadHdr->certSize +
                    wadHdr->ticketSize);
    *titleId = tmd->head.titleId;

    certPtr = IOS_AllocAligned(0, wadHdr->certSize, 64);
    memcpy(certPtr, certList, wadHdr->certSize);
    ticketPtr = IOS_AllocAligned(0, wadHdr->ticketSize, 64);
    memcpy(ticketPtr, ticket, wadHdr->ticketSize);
    tmdPtr = IOS_AllocAligned(0, wadHdr->tmdSize, 64);
    memcpy(tmdPtr, tmd, wadHdr->tmdSize);

    rv = ES_ImportTicket(ticketPtr, certPtr, wadHdr->certSize, NULL, 0,
                         ES_TRANSFER_SERVER);

    if (rv != ES_ERR_OK) {
        sdBootReport("Unable to import ticket: %d\n", rv);
        goto out;
    }
    sdBootReport ("import ticket successful\n");

    rv = ES_ImportTitleInit(tmdPtr, wadHdr->tmdSize, certPtr, wadHdr->certSize, 0, 0, 
                            ES_TRANSFER_SERVER, 1);
    if (rv != ES_ERR_OK) {
        sdBootReport("Unable to import title init: %d\n", rv);
        goto out;
    }
    sdBootReport("imported TMD\n");

    numContents = tmdPtr->head.numContents;
    sdBootReport("Num contents %d\n", numContents);
    int i;
    contentOffset = (void *) offset + wadHdr->contentOffset;
    for (i = 0; i < numContents; ++i) {
        s32 clen;
        s32 cfd = ES_ImportContentBegin(tmdPtr->head.titleId, tmdPtr->contents[i].cid);
        if (cfd < 0) {
            sdBootReport("Unable to import content %d: %d\n", i, cfd);
            rv = cfd;
            goto out;
        }

        clen = (tmdPtr->contents[i].size+15) & ~15;
        sdBootReport("Importing %d bytes for content %d\n", clen, i);
        if ((rv = ES_ImportContentData(cfd, contentOffset, clen)) < 0) {
            sdBootReport("Error import content data: %d [%d]\n", rv, clen);
            goto out;
        }

        if ((rv = ES_ImportContentEnd(cfd)) != ES_ERR_OK) {
            sdBootReport("Unable to end content import: %d\n", rv);
            goto out;
        }
        contentOffset += clen;
    }

    if ((rv = ES_ImportTitleDone()) != ES_ERR_OK) {
        sdBootReport("Unable to finish import: %d\n", rv);
        goto out;
    }
    sdBootReport("Successfully imported title\n");

out:
    if (certPtr) IOS_Free(0, certPtr);
    if (ticketPtr) IOS_Free(0, ticketPtr);
    if (tmdPtr) IOS_Free(0, tmdPtr);

    return rv;
}

/*
 * main
 */
void
main(void)
{
    IOSError rc = IOS_ERROR_OK;
    ESTitleId titleId;
    ESTicketView *ticketView = NULL;
    u32 numTickets = 1;
    u32 loadedSize;

    /* Entry */
    outputLed(0x40);

    /* Initialize the SD card */
    rc = sdInit();
    if (rc != IOS_ERROR_OK) {
        sdBootReport("Failed to init SD card, rc=%d\n", rc);
        goto main_out;
    }
    rc = ES_InitLib();
    if (rc != ES_ERR_OK) {
        sdBootReport("Failed to init ES library, rc=%d\n", rc);
        goto main_out;
    }

    /* Before loading the OS */
    outputLed(0x41);

    rc = sdLoadWadFile(SD_LOAD_ADDR, SD_OS_OFFSET, &loadedSize);
    if (rc != IOS_ERROR_OK) {
        sdBootReport("Failed to load the OS wad from the SD card, rc=%d\n", rc);
        goto main_out;
    }

    /* Before importing the OS */
    outputLed(0x42);

    rc = importTitle(SD_LOAD_ADDR, &titleId);
    if (rc != IOS_ERROR_OK) {
        sdBootReport("Failed to import the OS wad from the SD card, rc=%d\n", rc);
        goto main_out;
    }
    /* XXX check that title ID is an OS! */
    sdBootReport("Title ID 0x%llx\n", titleId);

    /* Before loading the PPC app */
    outputLed(0x43);

    rc = sdLoadWadFile(SD_LOAD_ADDR, SD_PPCAPP_OFFSET, &loadedSize);
    if (rc != IOS_ERROR_OK) {
        sdBootReport("Failed to load the OS wad from the SD card, rc=%d\n", rc);
        goto main_out;
    }

    /* Before importing the PPC app */
    outputLed(0x44);

    rc = importTitle(SD_LOAD_ADDR, &titleId);
    if (rc != IOS_ERROR_OK) {
        sdBootReport("Failed to import the PPC Application wad from the SD card, rc=%d\n", rc);
        goto main_out;
    }
    /* XXX check that title ID is an System menu! */
    sdBootReport("Title ID 0x%llx\n", titleId);

    /* Before getting the ticket view */
    outputLed(0x45);

    ticketView = IOS_Alloc(0, sizeof(ESTicketView));
    rc = ES_GetTicketViews(titleId, ticketView, &numTickets);
    if (rc != ES_ERR_OK) {
        sdBootReport("Failed to get ticket view, rc=%d\n", rc);
        goto main_out;

    }

    /* Exit */
    outputLed(0x4f);

    rc = ES_LaunchTitle(titleId, ticketView);
    if (rc != ES_ERR_OK) {
        sdBootReport("Failed to launch, rc=%d\n", rc);
        goto main_out;

    }

main_out:
    if (ticketView) IOS_Free(0, ticketView);

    /* If we get to here, something went wrong */
    sdBootFailure(rc);
}
