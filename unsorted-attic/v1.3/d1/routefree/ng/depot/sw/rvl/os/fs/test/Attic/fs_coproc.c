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
#include <sc/libc.h>
#include <sc/sc.h>
#include <sc/iostypes.h>
#include <sc/ios.h>
#include <sc/fs.h>
#include <sc/fl_ops.h>
#include <sc/fs_utils.h>
#include <sc/fs_ops.h>
#else
#include <ioslibc.h>
#include <iop.h>
#include <iostypes.h>
#include <ios.h>
#include <fs.h>
#include <fl_ops.h>
#include <fs_utils.h>
#include <fs_ops.h>
#endif

#include "trylock.h"


#define STACK_SIZE                  (2*1024)
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 10;

u8              __childStack[STACK_SIZE];


/* Source and destination file names */
#define PARENT_SRC                  "/parent.src"
#define PARENT_DST                  "/parent.dst"
#define CHILD_SRC                   "/child.src"
#define CHILD_DST                   "/child.dst"

/* Macro to acquire mutext */
#define ISFS_LOCK()                                                         \
    do {                                                                    \
        u32     __gotLock = 0;                                              \
        while (!__gotLock) {                                                \
            __gotLock = __skTrylock(&__isfsLock);                           \
            if (!__gotLock) {                                               \
                IOS_YieldThread();                                          \
            }                                                               \
        }                                                                   \
    } while (0)

#define ISFS_UNLOCK()                                                       \
    do {                                                                    \
        __skUnlock(&__isfsLock);                                            \
    } while (0)

#define IOS_TITLE_0_ID              1
#define IOS_TITLE_1_ID              2
#define IOS_TITLE_GROUP             1


/* Mutex */
u32             __isfsLock;

/* Data buffers */
u8              *__parentSrcBuf;
u8              *__parentDstBuf;
u8              *__childDstBuf;
u8              *__childSrcBuf;

u8              __pSrcBuf[ISFS_BLOCK_SIZE];
u8              __pDstBuf[ISFS_BLOCK_SIZE];
u8              __cSrcBuf[ISFS_BLOCK_SIZE];
u8              __cDstBuf[ISFS_BLOCK_SIZE];

/* Thread priority */
IOSThreadId     __isfsPriority;


s32
fsCheck(u8 *srcName, u8 *dstName, u8 *srcBuf, u8 *dstBuf)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         count = 0, byteCount;
    s32         fdSrc, fdDst;

    while (count < 16) {
        /* Acquire file system lock */
        ISFS_LOCK();

        /* Delete the destination file */
        rc = isfsDelete(IOS_ROOT_ID, IOS_ROOT_GROUP, dstName);
        if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_NOEXISTS)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete destination file %s,"
                                " rc=%d\n", dstName, rc);
            goto fsCheck_out;
        }
        rc = ISFS_ERROR_OK;

        /* Open the source file */
        fdSrc = isfsOpen(IOS_ROOT_ID, IOS_ROOT_GROUP, srcName,
                    ISFS_READ_ACCESS);
        if (fdSrc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to open source file %s,"
                                " rc=%d\n", srcName, fdSrc);
            rc = fdSrc;
            goto fsCheck_out;
        }

        /* Read the content of the source file */
        rc = isfsRead(fdSrc, srcBuf, ISFS_BLOCK_SIZE);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to read source file %s,"
                                " rc=%d\n", srcName, rc);
            goto fsCheck_out;
        }

        /* Close the source file */
        rc = isfsClose(fdSrc);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to close source file %s,"
                                " rc=%d\n", srcName, rc);
            goto fsCheck_out;
        }

        /* Create the destination file */
        rc = isfsCreateFile(IOS_ROOT_ID, IOS_ROOT_GROUP, dstName,
                            0, ISFS_RW_ACCESS, 0, 0);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to create destination file %s,"
                                " rc=%d\n", dstName, rc);
            goto fsCheck_out;
        }

        /* Open the destination file */
        fdDst = isfsOpen(IOS_ROOT_ID, IOS_ROOT_GROUP, dstName, ISFS_RW_ACCESS);
        if (fdDst < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to open destination file %s,"
                                " rc=%d\n", dstName, fdDst);
            rc = fdDst;
            goto fsCheck_out;
        }

        /* Write to the destination file */
        rc = isfsWrite(fdDst, srcBuf, ISFS_BLOCK_SIZE);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to write destination file %s,"
                                " rc=%d\n", dstName, rc);
            goto fsCheck_out;
        }

        /* Seek to the beginning of the destination file */
        rc = isfsSeek(fdDst, 0, IOS_SEEK_SET);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to seek to the beginning of the"
                                " destination file %s, rc=%d\n", dstName, rc);
            goto fsCheck_out;
        }

        /* Read the content of the destination file */
        rc = isfsRead(fdDst, dstBuf, ISFS_BLOCK_SIZE);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to read destination file %s,"
                                " rc=%d\n", dstName, rc);
            goto fsCheck_out;
        }

        /* Release the file system lock */
        ISFS_UNLOCK();

        /* Increase concurrency by yielding control */
        IOS_YieldThread();

        /* Compare the content of the source against the destination */
        for (byteCount = 0; byteCount < ISFS_BLOCK_SIZE; byteCount++) {
            if (srcBuf[byteCount] != dstBuf[byteCount]) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to verify result for source"
                                    " %s, destination %s, count=%d\n",
                                    srcName, dstName, count);
                rc = ISFS_ERROR_UNKNOWN;
                goto fsCheck_out;
            }
        }

        /* Print a message every 4 times */
        if ((++count & 3) == 0) {
            isfsPrint(ISFS_DEBUG_INFO, "Checked %d times for copying %s to"
                                " %s\n", count, srcName, dstName);
        }
    }

fsCheck_out:

    return (rc);
}


s32
child(u32 arg)
{
    ISFSError   rc = ISFS_ERROR_OK;

    /* Test concurrent FS operations */
    rc = fsCheck(CHILD_SRC, CHILD_DST, __childSrcBuf, __childDstBuf);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "CHILD: FS check failed, rc=%d\n", rc);
        goto child_out;
    }

    isfsPrint(ISFS_DEBUG_INFO, "CHILD: FS check succeeded\n");

child_out:

    return (rc);
}


/*
 *  Function: main
 *
 *  Description:
 *      Entry function for test
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
    u32         childId, parentId;

    ISFS_ENTRY();

    /* Get default thread priority */
    parentId = IOS_GetThreadId();
    __isfsPriority = IOS_GetThreadPriority(parentId);

    /* Initialize mutex */
    __skInitlock(&__isfsLock);

    /* Initialize buffers */
#ifdef MEM_ALLOC
    __parentSrcBuf = IOS_Alloc(0, ISFS_BLOCK_SIZE);
    __parentDstBuf = IOS_Alloc(0, ISFS_BLOCK_SIZE);
    __childSrcBuf = IOS_Alloc(0, ISFS_BLOCK_SIZE);
    __childDstBuf = IOS_Alloc(0, ISFS_BLOCK_SIZE);
    if ((__parentSrcBuf == NULL) || (__parentDstBuf == NULL) ||
            (__childSrcBuf == NULL) || (__childDstBuf == NULL)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to allocate buffers: "
                            " 0x%x:0x%x:0x%x:0x%x\n",
                            __parentSrcBuf, __parentDstBuf,
                            __childSrcBuf, __childDstBuf);
        rc = IOS_ERROR_INVALID;
        goto main_out;
    }
#else
    __parentSrcBuf = &__pSrcBuf[0];
    __parentDstBuf = &__pDstBuf[0];
    __childSrcBuf = &__cSrcBuf[0];
    __childDstBuf = &__cDstBuf[0];
#endif

    /* Open flash device driver */
    ret = flOpen();
    if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to initialize device driver, rc=%d\n",
                            ret);
        rc = ret;
        goto main_out;
    }

    /* Mount file system */
    rc = isfsMount(1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to mount file system, rc=%d\n", rc);
        goto main_out;
    }

    /* Create concurrent child thread */
    childId = IOS_CreateThread((IOSEntryProc) child, (void *)0,
                            __childStack+STACK_SIZE, STACK_SIZE,
                            __isfsPriority, IOS_THREAD_CREATE_JOINABLE);
    if (childId < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create child thread, rc=%d\n",
                            childId);
        rc = childId;
        goto main_out;
    }

    /* Start child thread */
    ret = IOS_StartThread(childId);
    if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to start child thread, rc=%d\n",
                                ret);
        rc = ret;
        goto main_out;
    }

    /* Test concurrent FS operations */
    rc = fsCheck(PARENT_SRC, PARENT_DST, __parentSrcBuf, __parentDstBuf);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "PARENT: FS check failed, rc=%d\n", rc);
        goto main_out;
    }
    isfsPrint(ISFS_DEBUG_INFO, "PARENT: FS check succeeded\n");

    /* Wait for child thread to join */
    ret = IOS_JoinThread(childId, (void **)&rc);
    if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Child thread failed to join, rc=%d\n",
                                ret);
        rc = ret;
        goto main_out;
    }

    /* Check child's error message */
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Child reported error, rc=%d\n", rc);
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

    isfsPrint(ISFS_DEBUG_INFO, "Successfully completed FS coproc test\n");

main_out:

    ISFS_EXIT();

    exit(rc);
    return (rc);
}
