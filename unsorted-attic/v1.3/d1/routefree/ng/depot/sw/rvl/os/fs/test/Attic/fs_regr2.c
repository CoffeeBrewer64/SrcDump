/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *      This file implements the software regression tests
 *
 */


#ifdef NET_CARD
#include <sc/arm.h>
#include <sc/libc.h>
#include <sc/iostypes.h>
#include <sc/sc.h>
#include <sc/ios.h>
#include <sc/flash.h>
#include <sc/fs.h>
#include <sc/fl_utils.h>
#include <sc/fl_ops.h>
#include <sc/fs_utils.h>
#include <sc/fs_ops.h>
#else
#include <arm.h>
#include <ioslibc.h>
#include <iostypes.h>
#include <iop.h>
#include <ios.h>
#include <flash.h>
#include <fs.h>
#include <fl_utils.h>
#include <fl_ops.h>
#include <fs_utils.h>
#include <fs_ops.h>

#define  IOS_Alloc(a, b)	IOS_Alloc(b)
#define  IOS_Free(a, b)		IOS_Free(b)

#endif


#define STACK_SIZE                  (2*1024)
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 11;


/* Number of logical blocks to be used in regression test */
// #define ISFS_STRESS_LOGIBLOCKS      16
#define ISFS_STRESS_LOGIBLOCKS      32

#define IOS_TITLE_0_ID              1
#define IOS_TITLE_1_ID              2
#define IOS_TITLE_GROUP             1

#define TEST_BLOCK		    1	/* Use block #1 to start testing */

/* Data buffers */
static u8                           *__isfsDataBuf;
static u8                           *__isfsSpareBuf;

#ifndef MEM_ALLOC
static u8       __dataBuf[FL_LOGI_BLOCK_SIZE * 4]  \
                    __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));
static u8       __spareBuf[FL_VIRT_SPARE_SIZE * 4] \
                    __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));
#endif

/* Global variable to avoid a large buffer on the stack */
static FLStats                      __flStats;


/*
 *  Function: fsRegrTestFlash
 *
 *  Description:
 *      Regression test for the flash device driver
 *
 *  Inputs:
 *      None
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Test passed
 *      < 0 - Error value of the test failed
 *
 */
IOSError
fsRegrTestFlash(void)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         count, logiBlkPerFlBlk, logiBlkCnt, logiBlkNum;
    FLDevCap    cap;

    ISFS_ENTRY();

#ifdef MEM_ALLOC
    __isfsDataBuf = IOS_Alloc(0, FL_LOGI_BLOCK_SIZE);
    if (__isfsDataBuf == NULL) {
        flPrint(FL_DEBUG_INFO, "Failed to allocate memory %d\n",
                            FL_LOGI_BLOCK_SIZE);

        rc = IOS_ERROR_MAX;
        goto fsRegrTestFlash_out;
    }

    __isfsSpareBuf = IOS_Alloc(0, FL_VIRT_SPARE_SIZE);
    if (__isfsSpareBuf == NULL) {
        flPrint(FL_DEBUG_INFO, "Failed to allocate memory %d\n",
                            FL_VIRT_SPARE_SIZE);

        rc = IOS_ERROR_MAX;
        goto fsRegrTestFlash_out;
    }
#else
    __isfsDataBuf = &__dataBuf[0];
    // __isfsSpareBuf = &__spareBuf[0];
    __isfsSpareBuf = (u8 *) (((u32)__spareBuf + FL_SPARE_ALIGN_SZ - 1) &
                             ~(FL_SPARE_ALIGN_SZ - 1));
#endif

    isfsPrint(ISFS_DEBUG_INFO,
            "\n*** Start flash driver regression test ***\n");

    /* Get flash capability */
    rc = flGetCap(&cap);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve flash capabilities,"
                            " rc=%d\n", rc);
        goto fsRegrTestFlash_out;
    }

    isfsPrint(ISFS_DEBUG_INFO, "Flash capabilities - totalSzShift:%d,"
        " erasableBlockSzShift:%d, pageSzShift:%d, spareSzShift:%d,"
        " userSpareSzShift:%d\n, numPlanes:%d, supportCopy:%d\n",
        cap.totalSzShift, cap.erasableBlockSzShift,
        cap.pageSzShift, cap.pageSpareSzShift, cap.userSpareSzShift,
        cap.numPlanes, cap.supportCopy);

    /* Number of logical blocks per flash block */
    logiBlkPerFlBlk = (1 <<
                (cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT));

    /* Number of logical blocks to test */
    logiBlkCnt = ISFS_STRESS_LOGIBLOCKS;

    /* Erase all flash blocks */
    logiBlkNum = TEST_BLOCK * logiBlkPerFlBlk;

    isfsPrint(ISFS_DEBUG_INFO, "Erasing all flash blocks...\n");

    // for (count = 0; count <
    for (count = logiBlkNum; count <
            (1 << (cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT));
            count++) {
        if ((count & (logiBlkPerFlBlk - 1)) == 0) {
            rc = flStatus(count);
            if (rc == IOS_ERROR_BADBLOCK) {
                continue;
            }

            rc = flErase(count);
            if ((rc != IOS_ERROR_OK)  && (rc != IOS_ERROR_BADBLOCK)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to erase logical block %d,"
                                    " rc=%d\n", count, rc);
                goto fsRegrTestFlash_out;
            }

            if (rc == IOS_ERROR_BADBLOCK) {
                isfsPrint(ISFS_DEBUG_INFO, "Bad block status detected during"
                                    " erase: %d\n", count);
            }
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Erased all flash blocks\n");

    /* Check the status of all flash blocks */
    // for (count = 0; count < logiBlkCnt; count++) {
    for (count = logiBlkNum; count < logiBlkCnt; count++) {
        if ((count & (logiBlkPerFlBlk - 1)) == 0) {

            isfsPrint(ISFS_DEBUG_INFO, "Checking status of logi block %d\n", 
                                        count);

            rc = flStatus(count);
            if ((rc != IOS_ERROR_OK) && (rc != IOS_ERROR_BADBLOCK)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to check status for logical"
                                    " block %d, rc=%d\n",count, rc);
                goto fsRegrTestFlash_out;
            }

            if (rc == IOS_ERROR_BADBLOCK) {
                isfsPrint(ISFS_DEBUG_INFO, "Bad block status detected during"
                                    " status check: %d\n", count);
            }
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Checked status for all logical blocks\n");

    /* Set up data and spare buffers for testing */
    for (count = 0; count < FL_LOGI_BLOCK_SIZE; count++) {
        /* Repeat "abcdefgh" */
        __isfsDataBuf[count] = 'a' + (count & 7);
    }
    for (count = 0; count < FL_VIRT_SPARE_SIZE; count++) {
        /* Repeat "rstuvwxy" */
        __isfsSpareBuf[count] = 'r' + (count & 7);
    }

    /* Write to the first half of the flash */
    // for (count = 0; count < (logiBlkCnt >> 1); count++) {
    for (count = logiBlkNum; count < (logiBlkCnt >> 1); count++) {
        rc = flStatus(count);
        if (rc == IOS_ERROR_BADBLOCK) {
            continue;
        }

        isfsPrint(ISFS_DEBUG_INFO, "Writing logi block %d\n", count);

        rc = flWrite(count, __isfsDataBuf, __isfsSpareBuf);
        if ((rc != IOS_ERROR_OK)  && (rc != IOS_ERROR_BADBLOCK)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to logical block %d,"
                                " rc=%d\n", count, rc);
            goto fsRegrTestFlash_out;
        }

        if (rc == IOS_ERROR_BADBLOCK) {
            isfsPrint(ISFS_DEBUG_INFO, "Bad block status detected during write:"
                                " %d\n", count);
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote to the first half of the flash\n");

    /* Copy the first half of the flash to the second half */
    if (cap.supportCopy) {
        // for (count = 0; count < (logiBlkCnt >> 1); count++) {
        for (count = logiBlkNum; count < (logiBlkCnt >> 1); count++) {
            rc = flStatus(count);
            if (rc == IOS_ERROR_BADBLOCK) {
                continue;
            }

            rc = flStatus(count + (logiBlkCnt >> 1));
            if (rc == IOS_ERROR_BADBLOCK) {
                continue;
            }

            isfsPrint(ISFS_DEBUG_INFO, "Copying from logi block %d to %d\n", 
                                        count, count + (logiBlkCnt >> 1));

            rc = flCopy(count, (count + (logiBlkCnt >> 1)));
            if ((rc != IOS_ERROR_OK)  && (rc != IOS_ERROR_BADBLOCK)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to copy to logical block"
                        " %d, rc=%d\n", count + (logiBlkCnt >> 1), rc);
                goto fsRegrTestFlash_out;
            }

            if (rc == IOS_ERROR_BADBLOCK) {
                isfsPrint(ISFS_DEBUG_INFO, "Bad block status detected during"
                            " copy: %d\n", count + (logiBlkCnt >> 1));
            }
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Copied to the second half of the flash\n");

    memset(__isfsDataBuf, 0, FL_LOGI_BLOCK_SIZE);
    memset(__isfsSpareBuf, 0, FL_VIRT_SPARE_SIZE);

    /* Check the content of all the blocks */
    // for (count = 0; count < logiBlkCnt; count++) {
    // for (count = logiBlkNum; count < logiBlkCnt; count++) {
    for (count = logiBlkNum; count < (logiBlkCnt >> 1); count++) {
        u32     charCount;

        if (!cap.supportCopy && (count >= (logiBlkCnt >> 1))) {
            break;
        }

        rc = flStatus(count);
        if (rc == IOS_ERROR_BADBLOCK) {
            continue;
        }

        isfsPrint(ISFS_DEBUG_INFO, "Reading from logi block %d\n", count);

        rc = flRead(count, __isfsDataBuf, __isfsSpareBuf);
        if ((rc != IOS_ERROR_OK) && (rc != IOS_ERROR_ECC)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to read from logical block %d,"
                                " rc=%d\n", count, rc);
            goto fsRegrTestFlash_out;
        }

        /* Check the content of both the data and spare areas */
        for (charCount = 0; charCount < FL_LOGI_BLOCK_SIZE; charCount++) {
            if (__isfsDataBuf[charCount] != 'a' + (charCount & 7)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Readback check failed for data of"
                                    " logical block: %d\n", rc);

                rc = IOS_ERROR_UNKNOWN;
                goto fsRegrTestFlash_out;
            }
        }

        for (charCount = 0; charCount < FL_VIRT_SPARE_SIZE; charCount++) {
            if (__isfsSpareBuf[charCount] != 'r' + (charCount & 7)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Readback failed for spare of"
                                    " logical block: %d\n", count);

                rc = IOS_ERROR_UNKNOWN;
                goto fsRegrTestFlash_out;
            }
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Read and verified all logical blocks\n");

    /* Erase all flash blocks */
    logiBlkNum = TEST_BLOCK * logiBlkPerFlBlk;

    // for (count = 0; count < logiBlkCnt; count++) {
    for (count = logiBlkNum; count < logiBlkCnt; count++) {
        if ((count & (logiBlkPerFlBlk - 1)) == 0) {
            rc = flStatus(count);
            if (rc == IOS_ERROR_BADBLOCK) {
                continue;
            }

            rc = flErase(count);
            if ((rc != IOS_ERROR_OK)  && (rc != IOS_ERROR_BADBLOCK)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to erase logical block %d,"
                                    " rc=%d\n", count, rc);
                goto fsRegrTestFlash_out;
            }

            if (rc == IOS_ERROR_BADBLOCK) {
                isfsPrint(ISFS_DEBUG_INFO, "Bad block status detected during"
                                    " erase: %d\n", count);
            }
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Erased all flash blocks\n");

    /* Issue invalid operations to test statistics */
    for (count = 0; count < (FL_FAILED_ENTRIES + 1); count++) {
        flWritePage(0, NULL, NULL, 0, 1);
    }

    rc = flGetStats(&__flStats);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve statistics,"
                                " rc=%d\n", rc);
        goto fsRegrTestFlash_out;
    }

    isfsPrint(ISFS_DEBUG_INFO, "Retrieved statistics - erases:%d, writes:%d,"
                    " reads:%d, copies:%d, start:%d, num:%d\n",
                    __flStats.numErasesSinceInit, __flStats.numWritesSinceInit,
                    __flStats.numReadsSinceInit, __flStats.numCopiesSinceInit,
                    __flStats.failRecordStart, __flStats.failRecordNum);

    /* Check failed records */
    for (count = 0; count < FL_FAILED_ENTRIES; count++) {
        if ((__flStats.failRecord[count].blockIndex != 0) ||
                (__flStats.failRecord[count].reason != IOS_ERROR_INVALID) ||
                (__flStats.failRecord[count].opType != FL_OP_WRITE)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Statistics check failed for record:%d,"
                                " index:%d, op:%d, reason:0x%x\n", count,
                                __flStats.failRecord[count].blockIndex,
                                __flStats.failRecord[count].opType,
                                __flStats.failRecord[count].reason);

            rc = IOS_ERROR_UNKNOWN;
            goto fsRegrTestFlash_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Checked flash statistics\n");

    isfsPrint(ISFS_DEBUG_INFO, "*** Successfully completed flash driver"
                        " regression test ***\n\n");

fsRegrTestFlash_out:

#ifdef MEM_ALLOC
    if (__isfsSpareBuf) {
        (void) IOS_Free(0, __isfsSpareBuf);
    }
    if (__isfsDataBuf) {
        (void) IOS_Free(0, __isfsDataBuf);
    }
#endif

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: fsRegrTestFs
 *
 *  Description:
 *      Regression test for the file system
 *
 *  Inputs:
 *      None
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Test passed
 *      < 0 - Error value of the test failed
 *
 */
IOSError
fsRegrTestFs(void)
{
    ISFSError       rc = ISFS_ERROR_OK;
    s32             count, num, attr, ownerAcc, groupAcc, othersAcc;
    s32             fd1, fd2, fd3, fdList[ISFS_FD_ENTRIES+1];
    u8              *nameList;
    ISFSFileStats   stats;
    ISFSStats       fsStats;
    IOSUid          ownerId;
    IOSGid          groupId;

    ISFS_ENTRY();

#ifdef MEM_ALLOC
    __isfsDataBuf = IOS_Alloc(0, FL_LOGI_BLOCK_SIZE * 3);
    if (__isfsDataBuf == NULL) {
        flPrint(FL_DEBUG_INFO, "Failed to allocate memory %d\n",
                            FL_LOGI_BLOCK_SIZE * 3);

        rc = IOS_ERROR_MAX;
        goto fsRegrTestFs_out;
    }

    __isfsSpareBuf = IOS_Alloc(0, FL_VIRT_SPARE_SIZE);
    if (__isfsSpareBuf == NULL) {
        flPrint(FL_DEBUG_INFO, "Failed to allocate memory %d\n",
                            FL_VIRT_SPARE_SIZE);

        rc = IOS_ERROR_MAX;
        goto fsRegrTestFs_out;
    }
#else
    __isfsDataBuf = &__dataBuf[0];
    // __isfsSpareBuf = &__spareBuf[0];
    __isfsSpareBuf = (u8 *) (((u32)__spareBuf + FL_SPARE_ALIGN_SZ - 1) &
                             ~(FL_SPARE_ALIGN_SZ - 1));
#endif

    isfsPrint(ISFS_DEBUG_INFO, "\n*** Start FS regression test ***\n");

    /* Re-format the file system */
    rc = isfsFormat(IOS_ROOT_ID);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to format file system, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Reformatted file system\n");

    /* Mount the file system */
    rc = isfsMount(1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to mount file system, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }

    /* Create directories */
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/sys", 0, 0, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /sys, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /sys\n");

    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/title",
                        0, 0, 0, ISFS_READ_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title\n");

    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/tmp",
                        0, 0, 0, ISFS_RW_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /tmp, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /tmp\n");

    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/title/0",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/0,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    rc = isfsSetAttr(IOS_ROOT_ID, "/title/0", IOS_TITLE_0_ID,
                IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to set attributes for /title/0,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/0\n");

    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/title/1",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/1,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    rc = isfsSetAttr(IOS_ROOT_ID, "/title/1", IOS_TITLE_1_ID,
                IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to set attributes for /title/1,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/1\n");

    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/test1",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/0/test1,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/0/test1\n");

    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/test2",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/0/test2,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/0/test2\n");

    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/test3",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/0/test3,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/0/test3\n");

    /* Create a duplicate directory */
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/sys", 0, 0, 0, 0);
    if (rc != ISFS_ERROR_EXISTS) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to detect duplicate directory,"
                            " rc=%d\n", rc);

        rc = ISFS_ERROR_UNKNOWN;      /* In case rc is ISFS_ERROR_OK */
        goto fsRegrTestFs_out;
    }
    rc = ISFS_ERROR_OK;

    /* Create a directory without write permission to the parent */
    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/1/test",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_ACCESS) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to detect access violation,"
                            " rc=%d\n", rc);
        rc = ISFS_ERROR_UNKNOWN;      /* In case rc is ISFS_ERROR_OK */
        goto fsRegrTestFs_out;
    }
    rc = ISFS_ERROR_OK;

    /* Create a file under root directory to test directory read */
    rc = isfsCreateFile(IOS_ROOT_ID, IOS_ROOT_GROUP, "/test.ab", 0, 0, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to created file, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created file /test.ab\n");

    /* Check the directories under root */
    rc = isfsReadDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/", NULL, &num);
    if ((rc != ISFS_ERROR_OK) || (num != 4)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to read directory, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    nameList = __isfsDataBuf;

    rc = isfsReadDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/", nameList, &num);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to read directory, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }

    if ((num != 4) || (strncmp(&nameList[0], "test.ab", 8)) ||
            (strncmp(&nameList[8], "tmp", 4)) ||
            (strncmp(&nameList[12], "title", 6)) ||
            (strncmp(&nameList[18], "sys", 4))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Verification failed for directory read,"
                            " num:%d, 1:%s, 2:%s, 3:%s, 4:%s\n", num,
                            &nameList[0], &nameList[8], &nameList[12],
                            &nameList[18]);

        rc = ISFS_ERROR_UNKNOWN;
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified directory read\n");

    /* Delete the test file */
    rc = isfsDelete(IOS_ROOT_ID, IOS_ROOT_GROUP, "/test.ab");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete file, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted file /test.ab\n");

    /* Create a file to test set and get attributes */
    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/testattr",
                        0, 0, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create file testattr,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created file /title/0/testattr\n");

    rc = isfsSetAttr(IOS_TITLE_0_ID, "/title/0/testattr", IOS_TITLE_0_ID,
                IOS_ROOT_GROUP, 0x3, ISFS_RW_ACCESS, ISFS_READ_ACCESS, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to set attributes for testattr,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Set attributes for /title/0/testattr\n");

    rc = isfsGetAttr(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/testattr",
                &ownerId, &groupId, &attr, &ownerAcc, &groupAcc, &othersAcc);
    if ((rc != ISFS_ERROR_OK) || (ownerId != IOS_TITLE_0_ID) ||
            (groupId != IOS_ROOT_GROUP) || (attr != 0x3) ||
            (ownerAcc != ISFS_RW_ACCESS) || (groupAcc != ISFS_READ_ACCESS) ||
            (othersAcc != 0)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to set attributes for testattr,"
                            " rc=%d, ownerId=0x%x, groupId=0x%x, attr=0x%x,"
                            " ownerAcc=0x%x, groupAcc=0x%x, othersAcc=0x%x\n",
                            rc, ownerId, groupId, attr, ownerAcc, groupAcc,
                            othersAcc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Checked attributes for /title/0/testattr\n");

    /* Enable and disable version control for test file */
    rc = isfsSetVersionControl(IOS_TITLE_0_ID, "/title/0/testattr", 1);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to enable version control for"
                            " testattr, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Enabled version control for"
                            " /title/0/testattr\n");

    rc = isfsSetVersionControl(IOS_TITLE_0_ID, "/title/0/testattr", 0);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to disable version control for"
                            " testattr, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Disabled version control for"
                            " /title/0/testattr\n");

    /* Delete some directories */
    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/test2");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete dir /title0/test2,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted directory /title/0/test2\n");

    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/test3");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete dir /title0/test3,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted directory /title/0/test3\n");

    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/test1");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete dir /title0/test1",
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted directory /title/0/test1\n");

    /* Only root can change the user ID of a directory or file */
    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/try",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /tmp/try, rc=%d\n",
                                    rc);
        goto fsRegrTestFs_out;
    }
    rc = isfsSetAttr(IOS_TITLE_0_ID, "/tmp/try", IOS_TITLE_1_ID,
                IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_ACCESS) {
        isfsPrint(ISFS_DEBUG_ERROR, "Directory set attr with non-self owner ID"
                            " should fail, rc=%d\n", rc);
        rc = ISFS_ERROR_ACCESS;
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified that only root can create a directory"
                        " with non-self owner ID\n");

    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/try.dat",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create file /tmp/try.dat,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    rc = isfsSetAttr(IOS_TITLE_0_ID, "/tmp/try.dat", IOS_TITLE_1_ID,
                IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_ACCESS) {
        isfsPrint(ISFS_DEBUG_ERROR, "File creation with non-self owner ID"
                            " should fail, rc=%d\n", rc);
        rc = ISFS_ERROR_ACCESS;
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified that only root can create a file with"
                        " non-self owner ID\n");

    /* Create a directory and some files under /tmp, then move it */
    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/exec",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /tmp/exec,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /tmp/exec\n");

    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/exec/map.dat",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create file /tmp/exec/map.dat,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created file /tmp/exec/map.dat\n");

    rc = isfsRename(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/exec",
                "/title/0/exec");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to move exec from /tmp to /title/0,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Moved exec from /tmp to /title/0\n");

    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/map.dat",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create file /tmp/map.dat,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created file /tmp/map.dat\n");

    /* Open the files, write something and read back to verify */
    fd1 = isfsOpen(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/map.dat",
            ISFS_RW_ACCESS);
    if (fd1 < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to open file /tmp/map.dat,"
                            " rc=%d\n", fd1);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Opened file /tmp/map.dat, fd=%d\n", fd1);

    fd2 = isfsOpen(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/exec/map.dat",
            ISFS_RW_ACCESS);
    if (fd2 < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to open file /title/0/exec/map.dat,"
                            " rc=%d\n", fd2);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Opened file /title/0/exec/map.dat,"
                            " fd=%d\n", fd2);

    /* Set up data buffer for testing */
    for (count = 0; count < (ISFS_BLOCK_SIZE * 2); count++) {
        /* Repeat "abcdefgh" */
        __isfsDataBuf[count] = 'a' + (count & 7);
    }

    /* Write two blocks first, then write one more block */
    rc = isfsWrite(fd1, __isfsDataBuf, ISFS_BLOCK_SIZE * 2);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to /tmp/map.dat,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote two FS blocks to /tmp/map.dat\n");

    rc = isfsWrite(fd1, __isfsDataBuf, ISFS_BLOCK_SIZE);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to /tmp/map.dat,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote one more FS block to /tmp/map.dat\n");

    /* Overwrite the content of the second block */
    rc = isfsSeek(fd1, -(ISFS_BLOCK_SIZE * 2), IOS_SEEK_CURRENT);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to seek to start of second block,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }

    rc = isfsWrite(fd1, __isfsDataBuf, ISFS_BLOCK_SIZE);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to /tmp/map.dat,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote again to the second block of"
                            " /tmp/map.dat\n");

    /* Read all three blocks and verify content */
    rc = isfsSeek(fd1, 0, IOS_SEEK_SET);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to seek to beginning of"
                            " /tmp/map.dat, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Seeked to beginning of /tmp/map.dat\n");

    memset(__isfsDataBuf, 0, ISFS_BLOCK_SIZE * 3);

    rc = isfsRead(fd1, __isfsDataBuf, ISFS_BLOCK_SIZE * 3);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to read from /tmp/map.dat, rc=%d\n",
                            rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Read three FS blocks from /tmp/map.dat\n");

    for (count = 0; count < (ISFS_BLOCK_SIZE * 3); count++) {
        if (__isfsDataBuf[count] != 'a' + (count & 7)) {
            isfsPrint(ISFS_DEBUG_INFO, "Readback check failed for"
                                " /tmp/map.dat\n");
            rc = ISFS_ERROR_UNKNOWN;
            goto fsRegrTestFs_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified the content of /tmp/map.dat\n");

    /* Write another block with non-aligned size */
    rc = isfsWrite(fd1, __isfsDataBuf, 1024);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to /tmp/map.dat,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote non-aligned block to /tmp/map.dat\n");

    rc = isfsSeek(fd1, -ISFS_BLOCK_SIZE, IOS_SEEK_CURRENT);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to go back one block for"
                            " /tmp/map.dat, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Seeked to the last block of /tmp/map.dat\n");

    memset(__isfsDataBuf, 0, ISFS_BLOCK_SIZE);

    rc = isfsRead(fd1, __isfsDataBuf, ISFS_BLOCK_SIZE);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to read from /tmp/map.dat, rc=%d\n",
                            rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Read one FS block from /tmp/map.dat\n");

    for (count = 0; count < 1024; count++) {
        if (__isfsDataBuf[count] != 'a' + (count & 7)) {
            isfsPrint(ISFS_DEBUG_INFO, "Readback check failed for"
                                " /tmp/map.dat\n");
            rc = ISFS_ERROR_UNKNOWN;
            goto fsRegrTestFs_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified the content of /tmp/map.dat\n");

    /* Check file statistics */
    rc = isfsGetFileStats(fd1, &stats);
    if ((rc != ISFS_ERROR_OK) ||
            (stats.size != ((ISFS_BLOCK_SIZE * 3) + 1024))||
            (stats.offset != (ISFS_BLOCK_SIZE * 4))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get statistics for /tmp/map.dat,"
                            " rc=%d, size=%d, offset=%d\n", rc, stats.size,
                            stats.offset);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified the size and offset of"
                            " /tmp/map.dat\n");

    rc = isfsWrite(fd2, __isfsDataBuf, ISFS_BLOCK_SIZE);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to map.dat, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote one FS block to /title/0/exec/map.dat\n");

    /* Close the file descriptors */
    rc = isfsClose(fd1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to close file descriptor: %d,"
                            " rc=%d\n", fd1, rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Closed /tmp/map.dat\n");

    rc = isfsClose(fd2);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to close file descriptor: %d,"
                            " rc=%d\n", fd2, rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Closed /title/0/exec/map.dat\n");

    /* File rename must keep the same relative file name */
    rc = isfsRename(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/map.dat",
                                "/title/0/exec/map.exe");
    if (rc != ISFS_ERROR_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Rename from /tmp/map.dat to map.exe should"
                            " fail, rc=%d\n", rc);
        rc = ISFS_ERROR_INVALID;
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified that file rename must keep the same"
                        " relative file name\n");
    rc = ISFS_ERROR_OK;

    /* Rename /tmp/map.dat to map.dat */
    rc = isfsRename(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/map.dat",
                                "/title/0/exec/map.dat");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to rename /tmp/map.dat to map.dat,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Renamed /tmp/map.dat to map.dat\n");

    /* Open more file descriptors than supported */
    count = ISFS_FD_ENTRIES + 1;
    for (count = 0; count < (ISFS_FD_ENTRIES + 1); count++) {
        fdList[count] = isfsOpen(IOS_TITLE_0_ID, IOS_TITLE_GROUP,
                            "/title/0/exec/map.dat", ISFS_RW_ACCESS);
        if ((count < ISFS_FD_ENTRIES) && (fdList[count] < 0)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to open file"
                                " /title/0/exec/game.exe, rc=%d\n", fd1);
            goto fsRegrTestFs_out;
        }
        if ((count == ISFS_FD_ENTRIES) && (fdList[count] >= 0)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to detect out of fd, rc=%d\n",
                                fd1);
            goto fsRegrTestFs_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Detected out of fd error\n");

    /* Delete map.dat */
    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/exec/map.dat");
    if (rc != ISFS_ERROR_OPENFD) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to detect open file descriptor,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Detected open file descriptor\n");

    for (count = 0; count < ISFS_FD_ENTRIES; count++) {
        rc = isfsClose(fdList[count]);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to close map.dat, rc=%d,"
                                " count=%d\n", rc, count);
            goto fsRegrTestFs_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Closed /title/0/exec/map.dat\n");

    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/exec/map.dat");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete map.dat, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted /title/0/exec/map.dat\n");

    /* Add a file with invalid name */
    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP,
                    "/title/0/exec/longfile.name", 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to recognize invalid file name,"
                            " rc=%d\n", rc);

        rc = ISFS_ERROR_INVALID;
        goto fsRegrTestFs_out;
    }
    rc = ISFS_ERROR_OK;
    isfsPrint(ISFS_DEBUG_INFO, "Recognized invalid file name\n");

    /*
     * Stress test: Create two files. Repeatedly write two blocks
     * to the first file and then the second file until the whole
     * flash is populated and ISFS_ERROR_MAX is returned. Now, free
     * the second file to trigger garbage collection for a certain
     * number of FS blocks. Create a third file and write 128 FS
     * blocks to it, garbage collection will be triggered again
     */
    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file1.tst",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create file /title/0/file1.tst,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created /title/0/file1.tst\n");

    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file2.tst",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create file /title/0/file2.tst,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created /title/0/file2.tst\n");

    fd1 = isfsOpen(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file1.tst",
            ISFS_RW_ACCESS);
    if (fd1 < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to open file /title/0/file1.tst,"
                            " rc=%d\n", fd1);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Opened /title/0/file1.tst, fd=%d\n", fd1);

    fd2 = isfsOpen(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file2.tst",
            ISFS_RW_ACCESS);
    if (fd2 < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to open file /title/0/file2.tst,"
                            " rc=%d\n", fd2);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Opened /title/0/file2.tst, fd=%d\n", fd2);

    count = 0;
    do {
        if ((count & 0xf) == 0) {
            isfsPrint(ISFS_DEBUG_INFO, "Wrote %d FS blocks\n", (count * 2));
        }

        rc = isfsWrite(((count & 0x1) == 0 ? fd1 : fd2), __isfsDataBuf,
                ISFS_BLOCK_SIZE * 2);
        if (rc == ISFS_ERROR_MAXBLOCKS) {
            isfsPrint(ISFS_DEBUG_INFO, "Reached flash max after writing %d"
                                " FS blocks\n", (count * 2));

            rc = ISFS_ERROR_OK;
            break;
        } else if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Stress test failed after writing %d"
                                " FS blocks\n", (count * 2));
            goto fsRegrTestFs_out;
        }

        count++;
    } while (rc == ISFS_ERROR_OK);

    rc = isfsClose(fd2);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to close file2.tst, rc=%d\n");
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Closed /title/0/file2.tst\n");

    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file2.tst");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete /title/0/file2.tst,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted /title/0/file2.tst\n");

    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file3.tst",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create /title/0/file3.tst,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created file /title/0/file3.tst\n");

    fd3 = isfsOpen(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file3.tst",
            ISFS_RW_ACCESS);
    if (fd3 < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to open /title/0/file3.tst,"
                            " rc=%d\n", fd3);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Opened /title/0/file3.tst, fd=%d\n", fd3);

    count = 64;
    while (count-- > 0) {
        isfsWrite(fd3, __isfsDataBuf, ISFS_BLOCK_SIZE * 2);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to write to /title/0/file3.tst,"
                                " rc=%d\n", rc);
            goto fsRegrTestFs_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Wrote 128 blocks to /title/0/file3.tst\n");

    /* Read the first two blocks of file1.tst and verify content */
    rc = isfsSeek(fd1, 0, IOS_SEEK_SET);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to seek to beginning of file1.tst,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Seeked to beginning of /title/0/file1.tst\n");

    memset(__isfsDataBuf, 0, ISFS_BLOCK_SIZE * 2);

    rc = isfsRead(fd1, __isfsDataBuf, ISFS_BLOCK_SIZE * 2);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to read from file1.tst,"
                                " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Read two FS blocks from /title/0/file1.tst\n");

    for (count = 0; count < (ISFS_BLOCK_SIZE * 2); count++) {
        if (__isfsDataBuf[count] != 'a' + (count & 7)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Readback check failed for"
                                    " file1.tst\n");
            rc = ISFS_ERROR_UNKNOWN;
            goto fsRegrTestFs_out;
        }
    }
    isfsPrint(ISFS_DEBUG_INFO, "Verified the content of /title/0/file1.tst\n");

    rc = isfsClose(fd1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to close file1.tst, rc=%d\n", rc);
    }
    isfsPrint(ISFS_DEBUG_INFO, "Closed /title/0/file1.tst\n");

    rc = isfsClose(fd3);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to close file3.tst, rc=%d\n", rc);
    }
    isfsPrint(ISFS_DEBUG_INFO, "Closed /title/0/file3.tst\n");

    /* Delete a directory with files and sub-directories */
    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/testdir",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/0/testdir,"
                            " rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/0/testdir\n");

    rc = isfsRename(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file1.tst",
                                "/title/0/testdir/file1.tst");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to move file1.tst to"
                            " /title/0/testdir, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Moved file3.tst to /title/0/testdir\n");

    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/testdir/test",
                        0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir"
                            " /title/0/testdir/test, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Created directory /title/0/testdir/test\n");

    rc = isfsRename(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/file3.tst",
                                "/title/0/testdir/file3.tst");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to move file3.tst to"
                            " /title/0/testdir, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Moved file3.tst to /title/0/testdir\n");

    rc = isfsDelete(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/title/0/testdir");
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete /title/0, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "Deleted /title/0/file1.tst\n");

    /* TODO: Add test for out-of-inode */

    /* Check file system statistics */
    rc = isfsGetStats(&fsStats);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get statistics, rc=%d\n", rc);
        goto fsRegrTestFs_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "File system block size: %d\n",
                            fsStats.blockSize);
    isfsPrint(ISFS_DEBUG_INFO, "Free FS blocks:         %d\n",
                            fsStats.freeBlocks);
    isfsPrint(ISFS_DEBUG_INFO, "Occupied FS blocks:     %d\n",
                            fsStats.occupiedBlocks);
    isfsPrint(ISFS_DEBUG_INFO, "Bad FS blocks:          %d\n",
                            fsStats.badBlocks);
    isfsPrint(ISFS_DEBUG_INFO, "Reserved FS blocks:     %d\n",
                            fsStats.reservedBlocks);
    isfsPrint(ISFS_DEBUG_INFO, "Free inodes:            %d\n",
                            fsStats.freeInodes);
    isfsPrint(ISFS_DEBUG_INFO, "Occupied inodes:        %d\n",
                            fsStats.occupiedInodes);

    isfsPrint(ISFS_DEBUG_INFO, "*** Successfully completed FS regression test"
                        " ***\n\n");

fsRegrTestFs_out:

#ifdef MEM_ALLOC
    if (__isfsSpareBuf) {
        (void) IOS_Free(0, __isfsSpareBuf);
    }
    if (__isfsDataBuf) {
        (void) IOS_Free(0, __isfsDataBuf);
    }
#endif

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: main
 *
 *  Description:
 *      Entry function for CPU 0
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      0 - Successful completion
 *      < 0 - Error
 *
 */
s32
main(void)
{
    ISFSError   rc = ISFS_ERROR_OK;
    IOSError    ret = IOS_ERROR_OK;

    ISFS_ENTRY();

    /* Open flash device driver */
    ret = flOpen();
    if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to initialize device driver,"
                                " rc=%d\n", ret);
        rc = ret;
        goto main_out;
    }

    /* Software flash regression test */
    ret = fsRegrTestFlash();
    if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Flash regression test failed,"
                                " rc=%d\n", ret);
        rc = ret;
        goto main_out;
    }

    /* Software file system regression test */
    rc = fsRegrTestFs();
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "FS regression test failed, rc=%d\n", rc);
        goto main_out;
    }

    /* Close the flash device driver */
    ret = flClose();
    if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_WARN, "Failed to shut down flash device driver,"
                            " rc=%d\n", ret);

        rc = ret;
        goto main_out;
    }

main_out:

    ISFS_EXIT();

    exit(rc);
    return (rc);
}
