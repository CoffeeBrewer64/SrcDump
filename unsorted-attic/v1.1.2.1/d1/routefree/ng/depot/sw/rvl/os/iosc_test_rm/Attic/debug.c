a0 179
#ident "$Id: debug.c,v 1.5 2008/01/23 20:59:05 cnguyen Exp $"
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*
 * Functions used only for debugging
 * 
 */

#include "iostypes.h"
#include "hw.h"
#include "ioslibc.h"
#include "ios.h"
// #include "stdbool.h"

#include "fs.h"
#include "debug.h"


extern  IOSMessageQueueId      dvdDriverSleepQueue;

/* ------------------------------------------------------------------------ */

/* This section is for routines to log to NAND */
// #ifdef WFS_LOG

#define MEM_BOUNDARY_TEST   1

#define DATA_BUF_SIZE   192     /* size of log buffer */

#define WFS_LOG_DIR      "/shared2/test2"
#define WFS_LOG_FILE     "/shared2/test2/wfslog.txt"

#if defined(MEM_BOUNDARY_TEST)
static u8 fsBuf[ISFS_INITLIB_BUFSIZE] __attribute__ ((aligned(32)));
static u8 dataBuf[DATA_BUF_SIZE] __attribute__ ((aligned(32)));
#else
static u8 *fsBuf = NULL;
static u8 *dataBuf = NULL;
#endif


ISFSError
wfsWriteLogFile(const u8* data, u32 size)
{
    ISFSError rc = ISFS_ERROR_OK;
    IOSFd fd = -1;
    int bytes;
    u32 num;

    printf("WFS: reading directory (%s)...\n", WFS_LOG_DIR);
    /* Create log directory if does not exist */
    rc = ISFS_ReadDir(WFS_LOG_DIR, NULL, &num);
    if (rc == ISFS_ERROR_NOEXISTS) {
        printf("WFS: creating log directory (%s)...\n", WFS_LOG_DIR);
        rc = ISFS_CreateDir(WFS_LOG_DIR, 0, ISFS_RW_ACCESS,
                         ISFS_RW_ACCESS, ISFS_RW_ACCESS);
        if (rc != ISFS_ERROR_OK) {
            printf("WFS: create log directory (%s) failed, rc=%d\n", 
                WFS_LOG_DIR, rc);
            goto out;
        }
    }

    printf("WFS: creating log file (%s)...\n", WFS_LOG_FILE);
    /* Create log file */
    rc = ISFS_CreateFile((const u8*)WFS_LOG_FILE, 0, ISFS_RW_ACCESS,
                         ISFS_RW_ACCESS, ISFS_RW_ACCESS);
    if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_EXISTS)) {
        printf("WFS: create log file (%s) failed, rc=%d\n", WFS_LOG_FILE, rc);
        goto out;
    }

    /* Open log file */
    fd = ISFS_Open((const u8*)WFS_LOG_FILE, ISFS_WRITE_ACCESS);
    if (fd < 0) {
        printf("WFS: open file (%s) failed, fd=%d\n", WFS_LOG_FILE, fd);
        rc = fd;
        goto out;
    }

    /* Seek to end of file */
    rc = ISFS_Seek(fd, 0, IOS_SEEK_END);
    if (rc < 0) {
        printf("WFS: seek to end of file (%s) failed, rc=%d\n", WFS_LOG_FILE, rc);
        goto out;
    }

    /* Write or append to file */
    bytes = ISFS_Write(fd, data, size);
    if (bytes != size) {
        printf("WFS: write file (%s) failed, bytes=%d size=%d\n", WFS_LOG_FILE, 
               bytes, size);
        rc = ISFS_ERROR_UNKNOWN;
        goto out;
    }

    /* Close */
    rc = ISFS_Close(fd);
    fd = -1;
    if (rc != ISFS_ERROR_OK) {
        printf("WFS: close file (%s) failed, rc=%d\n", WFS_LOG_FILE, rc);
        goto out;
    }

    printf("WFS: written file (%s) size=%d\n", WFS_LOG_FILE, bytes);

out:
    return(rc);

}


void
wfsLog(u8 *msg)
{

    static u8 initialized = 0;
    static u8 loggedOnce = 0;

    ISFSError rc = ISFS_ERROR_OK;

    if (!initialized) {
        /* Need to allocate buffers from shared heap to communicate with
           ISFS due to memory protection scheme */
        extern void *__isfsBuf;

#if !defined(MEM_BOUNDARY_TEST)
        fsBuf = IOS_Alloc(0, ISFS_INITLIB_BUFSIZE);
        if (fsBuf == NULL) {
            printf("WFS: alloc ISFS buffer failed!\n");
            goto out;
        }
        
        dataBuf = IOS_Alloc(0, DATA_BUF_SIZE);
        if (dataBuf == NULL) {
            printf("WFS: alloc data buffer failed!\n");
            goto out;
        }
#endif

        __isfsBuf = fsBuf;  /* Overload ISFS internal buffer in library */
        initialized = 1;

    }

    memset(dataBuf, 0, DATA_BUF_SIZE);
    strncpy(dataBuf, msg, DATA_BUF_SIZE-1);

    if (!loggedOnce) {
        printf("WFS: logging to NAND file (%s)\n", WFS_LOG_FILE);
        loggedOnce = 1;
    }

    /* If want to print out log message to JTAG */
    printf("WFS: Buffer = %s", dataBuf);

    rc = wfsWriteLogFile((const u8*)dataBuf, DATA_BUF_SIZE);
    if (rc != ISFS_ERROR_OK) {
        printf("WFS: write to log file failed, rc=%d\n", rc);
        goto out;
    }

out:
    return;

}

// #endif

/* ------------------------------------------------------------------------ */
