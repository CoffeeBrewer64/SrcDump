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
#include <sc/addr_map.h>
#include <sc/iostypes.h>
#include <sc/ios.h>
#include <sc/flash.h>
#include <sc/fs.h>
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <ios.h>
#include <flash.h>
#include <fs.h>
#endif


#define STACK_SIZE                  1024
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 11;


u8              *dataBuf = NULL;
extern void     *__isfsBuf;


#ifndef MEM_ALLOC
static u8       __dataBuf[ISFS_BLOCK_SIZE * 2]  \
                    __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));
#endif


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
    ISFSError       rc = ISFS_ERROR_OK;
    u32             count, num, attr, ownerAcc, groupAcc, othersAcc, iter;
    IOSProcessId    pid;
    IOSUid          uid;
    IOSGid          gid;
    IOSFd           fd, fdFlash;
    FLDevCap        *cap, capBuf;
    FLStats         *flStats;
    ISFSStats       *stats;
    ISFSFileStats   *fstats;
    u8              *nameList, *buf;
    u32             totalPageSz, firstDataPage;

    pid = IOS_GetProcessId();
    printf("PID=0x%x\n", pid);

    IOS_SetUid(pid, 0);
    IOS_SetGid(pid, 0);

    uid = IOS_GetUid();
    gid = IOS_GetGid();
    printf("UID=0x%x, GID=0x%x\n", uid, gid);

#ifdef MEM_ALLOC
    dataBuf = IOS_Alloc(0, 2 * ISFS_BLOCK_SIZE);
    if (dataBuf == NULL) {
        printf("Failed to allocate memory %d\n", 2 * ISFS_BLOCK_SIZE);
        rc = IOS_ERROR_MAX;
        goto main_out;
    }
#else
    dataBuf = __dataBuf;
#endif
    printf("Allocated memory for data buffer\n");

    /* Open a connection to the flash directly */
    fdFlash = IOS_Open("/dev/flash", 0);
    if (fdFlash < 0) {
        printf("Failed to open a connection to the flash driver, rc=%d\n",
            fdFlash);
        rc = fdFlash;
        goto main_out;
    }
    printf("Opened a connection to the flash driver, fd=%d\n", fdFlash);

    cap = (FLDevCap *) dataBuf;
    rc = IOS_Ioctl(fdFlash, FL_GETCAP, NULL, 0, cap, sizeof (FLDevCap));
    if (rc != IOS_ERROR_OK) {
        printf("Failed to get flash capabilities, rc=%d\n", rc);
        goto main_out;
    }
    memcpy(&capBuf, cap, sizeof (FLDevCap));
    cap = &capBuf;
    printf("Total size %d, erasable block size %d, page size %d\n",
        (1 << cap->totalSzShift), (1 << cap->erasableBlockSzShift),
        (1 << cap->pageSzShift));

    firstDataPage = ISFS_SYSAREA_SIZE >> cap->pageSzShift;
    rc = IOS_Seek(fdFlash, firstDataPage, IOS_SEEK_SET);
    if (rc != firstDataPage) {
        printf("Failed to seek to the first page, rc=%d\n", rc);
        goto main_out;
    }
    printf("Seeked to the first page\n");

    rc = IOS_Ioctl(fdFlash, FL_STATUS, NULL, 0, NULL, 0);
    if (rc != IOS_ERROR_OK) {
        if (rc == IOS_ERROR_BADBLOCK) {
            rc = 0;
            printf("Detected bad block, skipping the rest of the tests\n");
            goto main_out;    
        } else {
            printf("Failed to check the status of the page, rc=%d\n", rc);
            goto main_out;
        }
    }
    printf("Checked the status of the first page\n");

    rc = IOS_Ioctl(fdFlash, FL_ERASE, NULL, 0, NULL, 0);
    if (rc != IOS_ERROR_OK) {
        printf("Failed to erase block, rc=%d\n", rc);
        goto main_out;
    }
    printf("Erased block\n");

    totalPageSz = (1 << cap->pageSzShift) + (1 << cap->pageSpareSzShift);
    for (count = 0; count < totalPageSz; count++) {
        dataBuf[count] = ((count * 223) + 987) >> 2;
    }
    printf("Initialized buffer - 0:%d, 1:%d, 128:%d, 129:%d\n",
        dataBuf[0], dataBuf[1], dataBuf[128], dataBuf[129]);

    rc = IOS_Write(fdFlash, dataBuf, totalPageSz);
    if (rc != totalPageSz) {
        printf("Failed to write page %d, rc=%d\n", firstDataPage, rc);
        goto main_out;
    }
    printf("Wrote to page %d\n", firstDataPage);

    rc = IOS_Seek(fdFlash, -1, IOS_SEEK_CURRENT);
    if (rc != firstDataPage) {
        printf("Failed to seek to the first page, rc=%d\n", rc);
        goto main_out;
    }
    printf("Seeked to the first page\n");

    memset(dataBuf, 0, totalPageSz);

    rc = IOS_Read(fdFlash, dataBuf, totalPageSz);
    if (rc != totalPageSz) {
        printf("Failed to read page %d, rc=%d\n", firstDataPage, rc);
        goto main_out;
    }
    printf("Read from page %d\n", firstDataPage);

    for (count = 0; count < (1 << cap->pageSzShift); count++) {
        if (dataBuf[count] != ((u8) (((count * 223) + 987) >> 2))) {
            printf("Readback check failed, count=%d\n", count);
            rc = IOS_ERROR_INVALID;
            goto main_out;
        }
    }
    printf("Verified buffer - 0:%d, 1:%d, 128:%d, 129:%d\n",
        dataBuf[0], dataBuf[1], dataBuf[128], dataBuf[129]);

    flStats = (FLStats *) dataBuf;
    rc = IOS_Ioctl(fdFlash, FL_GETSTATS, NULL, 0, flStats, sizeof (FLStats));
    if (rc != IOS_ERROR_OK) {
        printf("Failed to get flash statistics, rc=%d\n", rc);
        goto main_out;
    }
    printf("Flash erases %d, flash writes %d, flash reads %d\n",
        flStats->numErasesSinceInit, flStats->numWritesSinceInit,
        flStats->numReadsSinceInit);

    rc = IOS_Close(fdFlash);
    if (rc != IOS_ERROR_OK) {
        printf("Failed to close flash driver, rc=%d\n", rc);
        goto main_out;
    }
    printf("Closed the flash driver\n");

    __isfsBuf = dataBuf;
    printf("Set the FS library internal buffer\n");

    rc = ISFS_Format();
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to format file system, rc=%d\n", rc);
        goto main_out;
    }
    printf("Formatted file system\n");

    rc = ISFS_CreateDir("/tmp", 0, ISFS_RW_ACCESS, ISFS_RW_ACCESS,
                    ISFS_RW_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to create new directory, rc=%d\n", rc);
        goto main_out;
    }
    printf("Created new directory\n");

    stats = (ISFSStats *) dataBuf + ISFS_INITLIB_BUFSIZE;
    rc = ISFS_GetStats(stats);
    if ((rc != ISFS_ERROR_OK) || (stats->blockSize != ISFS_BLOCK_SIZE)) {
        printf("Failed to get file system statistics, rc=%d, size=%d\n",
            rc, stats->blockSize);
        goto main_out;
    }
    printf("Block size: %d, Free: %d, Occupied: %d, Bad: %d, Reserved: %d,"
        " Free Inodes: %d, Occupied Inodes: %d\n", stats->blockSize,
        stats->freeBlocks, stats->occupiedBlocks, stats->badBlocks,
        stats->reservedBlocks, stats->freeInodes, stats->occupiedInodes);

    rc = ISFS_CreateFile("/tmp/apitests.tst", 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to create new file, rc=%d\n", rc);
        goto main_out;
    }
    printf("Created new file\n");

    rc = ISFS_SetFileVersionControl("/tmp/apitests.tst", 1);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to enable file version control, rc=%d\n", rc);
        goto main_out;
    }
    printf("Enabled file version control\n");

    fd = ISFS_Open("/tmp/apitests.tst", ISFS_RW_ACCESS);
    if (fd < 0) {
        printf("Failed to open file, rc=%d\n", fd);
        rc = fd;
        goto main_out;
    }
    printf("Opened file\n");

    buf = dataBuf + ISFS_INITLIB_BUFSIZE;
    for (count = 0; count < ISFS_BLOCK_SIZE; count++) {
        buf[count] = ((count * 362) + 118) >> 3;
    }
    printf("Initialized buffer - 0:%d, 1:%d, 8000:%d, 8001:%d\n",
        buf[0], buf[1], buf[8000], buf[8001]);

    rc = ISFS_Write(fd, buf, ISFS_BLOCK_SIZE);
    if (rc != ISFS_BLOCK_SIZE) {
        printf("Failed to write a full FS block, rc=%d\n");
        goto main_out;
    }
    printf("Wrote a full FS block, bytes=%d\n", rc);

    rc = ISFS_Seek(fd, 0, IOS_SEEK_SET);
    if (rc != 0) {
        printf("Failed to seek to the beginning, rc=%d\n", rc);
        goto main_out;
    }
    printf("Seeked to the beginning, offset=%d\n", rc);

    memset(buf, 0, ISFS_BLOCK_SIZE);

    rc = ISFS_Read(fd, buf, ISFS_BLOCK_SIZE);
    if (rc != ISFS_BLOCK_SIZE) {
        printf("Failed to read a full FS block, rc=%d\n");
        goto main_out;
    }
    printf("Read a full FS block, bytes=%d\n", rc);

    for (count = 0; count < ISFS_BLOCK_SIZE; count++) {
        if (buf[count] != ((u8) (((count * 362) + 118) >> 3))) {
            printf("Read-back check failed, count=%d:%d\n", count, buf[count]);
            rc = ISFS_ERROR_UNKNOWN;
            goto main_out;
        }
    }
    printf("Verified buffer - 0:%d, 1:%d, 8000:%d, 8001:%d\n",
        buf[0], buf[1], buf[8000], buf[8001]);

    rc = ISFS_Seek(fd, 0, IOS_SEEK_SET);
    if (rc != 0) {
        printf("Failed to seek to the beginning, rc=%d\n", rc);
        goto main_out;
    }
    printf("Seeked to the beginning, offset=%d\n", rc);

    for (count = 0; count < ISFS_BLOCK_SIZE; count++) {
        buf[count] = ((count * 236) + 764) >> 2;
    }
    printf("Initialized buffer - 0:%d, 1:%d, 8000:%d, 8001:%d\n",
        buf[0], buf[1], buf[8000], buf[8001]);

    for (iter = 0; iter < 3; iter++) {
        rc = ISFS_Write(fd, buf + ((iter & 1) * 8000), 8000);
        if (rc != 8000) {
            printf("Failed to write to the file, rc=%d, iter=%d\n", rc, iter);
            goto main_out;
        }
        printf("Wrote to the file, iter=%d, bytes=%d\n", iter, rc);
    }

    rc = ISFS_Seek(fd, 0, IOS_SEEK_SET);
    if (rc != 0) {
        printf("Failed to seek to the beginning, rc=%d\n", rc);
        goto main_out;
    }
    printf("Seeked to the beginning, offset=%d\n", rc);

    memset(buf, 0, ISFS_BLOCK_SIZE);

    for (iter = 0; iter < 3; iter++) {
        rc = ISFS_Read(fd, buf, 8000);
        if (rc != 8000) {
            printf("Failed to read from the file, rc=%d, iter=%d\n", rc, iter);
            goto main_out;
        }
        printf("Read from the file, iter=%d, bytes=%d\n", iter, rc);

        for (count = 0; count < 8000; count++) {
            if (buf[count] !=
                    (u8) ((((count + ((iter&1) * 8000)) * 236) + 764) >> 2)) {
                printf("Read-back check failed, count=%d:%d\n",
                    count, buf[count]);
                rc = ISFS_ERROR_UNKNOWN;
                goto main_out;
            }
        }
        printf("Verified read-back - 0:%d, 1:%d\n", buf[0], buf[1]);
    }

    fstats = (ISFSFileStats *) (dataBuf + ISFS_INITLIB_BUFSIZE);
    rc = ISFS_GetFileStats(fd, fstats);
    if ((rc != ISFS_ERROR_OK) || (fstats->size != (8000 * 3)) ||
            (fstats->offset != fstats->size)) {
        printf("Failed to get file stats, rc=%d, size=%d, offset=%d\n",
            rc, fstats->size, fstats->offset);
        goto main_out;
    }
    printf("Size:%d, Offset:%d\n", fstats->size, fstats->offset);

    rc = ISFS_Close(fd);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to close file, rc=%d\n", rc);
        goto main_out;
    }
    printf("Closed file\n");

    rc = ISFS_CreateDir("/tmp/apitest", 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to create new directory, rc=%d\n", rc);
        goto main_out;
    }
    printf("Created new directory\n");

    rc = ISFS_SetAttr("/tmp/apitest", uid, gid, 0xf, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to set attribute for directory\n");
        goto main_out;
    }
    printf("Set attributes for directory\n");

    rc = ISFS_GetAttr("/tmp/apitest", &uid, &gid, &attr, &ownerAcc, &groupAcc,
                &othersAcc);
    if ((rc != ISFS_ERROR_OK) || (attr != 0xf)) {
        printf("Failed to get attributes for directory\n");
        goto main_out;
    }
    printf("UID:0x%x, GID:0x%x, attr:0x%x, own:0x%x, grp:0x%x, other:0x%x\n",
        uid, gid, attr, ownerAcc, groupAcc, othersAcc);

    rc = ISFS_Rename("/tmp/apitests.tst", "/tmp/apitest/apitests.tst");
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to rename file, rc=%d\n", rc);
        goto main_out;
    }
    printf("Renamed file\n");

    rc = ISFS_Delete("/tmp/apitest/apitests.tst");
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to delete file, rc=%d\n", rc);
        goto main_out;
    }
    printf("Deleted file\n");

    rc = ISFS_CreateFile("/tmp/goodfile.txt", 0, ISFS_RW_ACCESS, 0, 0);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to create new file, rc=%d\n", rc);
        goto main_out;
    }
    printf("Created new file\n");

    rc = ISFS_ReadDir("/tmp", NULL, &num);
    if ((rc != ISFS_ERROR_OK) || (num != 2)) {
        printf("Failed to get number of directory elements, rc=%d, num=%d\n",
            rc, num);
        goto main_out;
    }
    printf("Number of directory elements is %d\n", num);

    num = 3;
    nameList = dataBuf + ISFS_INITLIB_BUFSIZE;
    rc = ISFS_ReadDir("/tmp", nameList, &num);
    if ((rc != ISFS_ERROR_OK) || (num != 2) ||
            (strncmp(nameList, "goodfile.txt", ISFS_INODE_NAMELEN)) ||
            (strncmp(&nameList[13], "apitest", ISFS_INODE_NAMELEN))) {
        printf("Failed to read directory, rc=%d, num=%d, name1:%s, name2:%s\n",
            rc, num, nameList, &nameList[13]);
        goto main_out;
    }
    printf("Num:%d, name1:%s, name2:%s\n", num, nameList, &nameList[13]);

    /* Create two files of the same name */
    rc = ISFS_CreateFile("/abc.txt", 0, ISFS_RW_ACCESS, ISFS_RW_ACCESS,
                    ISFS_RW_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        printf("Failed to create new file, rc=%d\n", rc);
        goto main_out;
    }
    printf("Created new file /abc.txt\n");

    rc = ISFS_CreateFile("/abc.txt", 0, ISFS_RW_ACCESS, ISFS_RW_ACCESS,
                    ISFS_RW_ACCESS);
    if (rc != ISFS_ERROR_EXISTS) {
        printf("Failed to detect duplicate file, rc=%d\n", rc);
        goto main_out;
    }
    rc = ISFS_ERROR_OK;
    printf("Detected duplicate file creation\n");

main_out:

    exit (rc);
    return (rc);
}
