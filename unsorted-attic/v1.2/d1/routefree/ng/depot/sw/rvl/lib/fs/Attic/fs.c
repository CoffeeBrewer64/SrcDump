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
 *      This file implements the core file system operations for the SCFS
 *
 */


#ifdef NET_CARD
#include <sc/libc.h>
#include <sc/iostypes.h>
#include <sc/ios.h>
#include <sc/fs.h>
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <ios.h>
#include <fs.h>
#endif


#define ISFS_GETFD()                                                        \
    do {                                                                    \
        if (__isfsFd < 0) {                                                 \
            __isfsFd = IOS_Open("/dev/fs", 0);                              \
        }                                                                   \
    } while (0);

#define ISFS_RELFD()                                                        \
    do {                                                                    \
        if (__isfsFd >= 0) {                                                \
            IOS_Close(__isfsFd);                                            \
            __isfsFd = -1;                                                  \
        }                                                                   \
    } while (0);


/* FS library connection to the file system */
static IOSFd    __isfsFd = -1;

/* Buffer readable/writable by the FS, passed to the library through init */
static u8       __isfsInternalBuf[ISFS_INITLIB_BUFSIZE]
                    __attribute__ ((section(".data")));
void            *__isfsBuf = __isfsInternalBuf;


ISFSError
ISFS_Format(void)
{
    ISFS_GETFD();

    return (IOS_Ioctl(__isfsFd, ISFS_FORMAT, NULL, 0, NULL, 0));

    ISFS_RELFD();
}


ISFSError
ISFS_GetStats(ISFSStats *stats)
{
    ISFS_GETFD();

    return (IOS_Ioctl(__isfsFd, ISFS_STATS, NULL, 0, stats, sizeof(ISFSStats)));

    ISFS_RELFD();
}


ISFSError
ISFS_CreateDir(const u8 *dname, u32 dirAttr, u32 ownerAcc, u32 groupAcc,
    u32 othersAcc)
{
    ISFSError           rc = ISFS_ERROR_OK;
    ISFSPathAttrArgs    *pathAttrArgs;
    u32 len;

    ISFS_GETFD();

    if ((dname == NULL) ||
            ((len = strnlen(dname, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_CreateDir_out;
    }

    /* Issue the create dir command */
    pathAttrArgs = (ISFSPathAttrArgs *) __isfsBuf;
    memcpy(pathAttrArgs->path, dname, len+1);
    pathAttrArgs->attr = dirAttr;
    pathAttrArgs->ownerAccess = ownerAcc;
    pathAttrArgs->groupAccess = groupAcc;
    pathAttrArgs->othersAccess = othersAcc;

    rc = IOS_Ioctl(__isfsFd,  ISFS_DCREATE, pathAttrArgs,
                sizeof (ISFSPathAttrArgs), NULL, 0);

ISFS_CreateDir_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_ReadDir(const u8 *dname, u8 *nameList, u32 *num)
{
    ISFSError   rc = ISFS_ERROR_OK;
    IOSIoVector *v = __isfsBuf;
    u32         len, numInputs, numOutputs, *numPtr;

    ISFS_GETFD();

    if ((dname == NULL) || (num == NULL) ||
            ((len = strnlen(dname, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_ReadDir_out;
    }


    /*
     * Issue the read dir command. There can be at most two inputs:
     *  1) The name of the directory
     *  2) The number of elements (only if nameList is not NULL)
     *
     * There can also be at most two outputs:
     *  1) The name list buffer (only if nameList is not NULL)
     *  2) The actual number of elements copied
     */

    /* Copy the directory name onto the global buffer */
    memcpy(&v[4], dname, len + 1);
    v[0].base = ((u8 *) &v[4]);
    v[0].length = ISFS_PATH_MAXLEN;

    /* Set the pointer for num input/output */
    numPtr = (u32 *) (((u32) &v[4]) + ISFS_PATH_MAXLEN);

    if (nameList) {
        numInputs = 2;
        numOutputs = 2;

        *numPtr = *num;
        v[1].base = (u8 *) numPtr;
        v[1].length = 4;
        v[2].base = nameList;
        v[2].length = *num * (ISFS_INODE_NAMELEN + 1);
        v[3].base = (u8 *) numPtr;
        v[3].length = 4;
    } else {
        numInputs = 1;
        numOutputs = 1;

        v[1].base = (u8 *) numPtr;
        v[1].length = 4;
    }

    rc = IOS_Ioctlv(__isfsFd,  ISFS_DREAD, numInputs, numOutputs, v);
    if (rc != ISFS_ERROR_OK) {
        goto ISFS_ReadDir_out;
    }

    *num = *numPtr;

ISFS_ReadDir_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_SetAttr(const u8 *name, IOSUid ownerId, IOSGid groupId, u32 attr,
    u32 ownerAcc, u32 groupAcc, u32 othersAcc)
{
    ISFSError           rc = ISFS_ERROR_OK;
    ISFSPathAttrArgs    *pathAttrArgs;
    u32 len;

    ISFS_GETFD();

    if ((name == NULL) ||
            ((len = strnlen(name, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_SetAttr_out;
    }

    /* Issue the set attr command */
    pathAttrArgs = (ISFSPathAttrArgs *) __isfsBuf;
    memcpy(pathAttrArgs->path, name, len+1);
    pathAttrArgs->ownerId = ownerId;
    pathAttrArgs->groupId = groupId;
    pathAttrArgs->attr = attr;
    pathAttrArgs->ownerAccess = ownerAcc;
    pathAttrArgs->groupAccess = groupAcc;
    pathAttrArgs->othersAccess = othersAcc;
    rc = IOS_Ioctl(__isfsFd, ISFS_SETATTR, (u8 *) pathAttrArgs,
                sizeof (ISFSPathAttrArgs), NULL, 0);

ISFS_SetAttr_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_GetAttr(const u8 *name, IOSUid *ownerId, IOSGid *groupId, u32 *attr,
    u32 *ownerAcc, u32 *groupAcc, u32 *othersAcc)
{
    ISFSError           rc = ISFS_ERROR_OK;
    ISFSPathAttrArgs    *pathAttrArgs;
    u8                  *ptr;
    u32                 len;

    ISFS_GETFD();

    if ((name == NULL) ||
            ((len = strnlen(name, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN) ||
            (ownerId == NULL) || (groupId == NULL) || (attr == NULL) ||
            (ownerAcc == NULL) || (groupAcc == NULL) || (othersAcc == NULL)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_GetAttr_out;
    }

    /* Issue the get attr command */
    ptr = (u8 *) __isfsBuf;
    memcpy(ptr, name, len+1);
    pathAttrArgs = (ISFSPathAttrArgs *) &ptr[ISFS_PATH_MAXLEN];

    rc = IOS_Ioctl(__isfsFd, ISFS_GETATTR, (u8 *) __isfsBuf, ISFS_PATH_MAXLEN,
                (u8 *) pathAttrArgs, sizeof (ISFSPathAttrArgs));
    if (rc == ISFS_ERROR_OK) {
        *ownerId = pathAttrArgs->ownerId;
        *groupId = pathAttrArgs->groupId;
        *attr = pathAttrArgs->attr; 
        *ownerAcc = pathAttrArgs->ownerAccess;
        *groupAcc = pathAttrArgs->groupAccess;
        *othersAcc = pathAttrArgs->othersAccess;
    }

ISFS_GetAttr_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_Delete(const u8 *name)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         len;

    ISFS_GETFD();

    if ((name == NULL) ||
            ((len = strnlen(name, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_Delete_out;
    }

    /* Issue the delete command */
    memcpy(__isfsBuf, name, len+1);
    rc = IOS_Ioctl(__isfsFd, ISFS_DEL, (u8 *) __isfsBuf, ISFS_PATH_MAXLEN, NULL, 0);

ISFS_Delete_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_Rename(const u8 *oldName, const u8 *newName)
{
    ISFSError       rc = ISFS_ERROR_OK;
    ISFSPathsArgs   *pathsArgs;
    u32             oldLen, newLen;

    ISFS_GETFD();

    if ((oldName == NULL) || (newName == NULL) ||
            ((oldLen = strnlen(oldName, ISFS_PATH_MAXLEN)) ==
                                                        ISFS_PATH_MAXLEN) ||
            ((newLen = strnlen(newName, ISFS_PATH_MAXLEN)) ==
                                                        ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_Rename_out;
    }

    /* Issue the rename command */
    pathsArgs = (ISFSPathsArgs *) __isfsBuf;
    memcpy(pathsArgs->path1, oldName, oldLen+1);
    memcpy(pathsArgs->path2, newName, newLen+1);

    rc = IOS_Ioctl(__isfsFd, ISFS_RENAME, (u8 *) pathsArgs,
                sizeof (ISFSPathsArgs), NULL, 0);

ISFS_Rename_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_CreateFile(const u8 *fname, u32 fileAttr, u32 ownerAcc, u32 groupAcc,
    u32 othersAcc)
{
    ISFSError           rc = ISFS_ERROR_OK;
    ISFSPathAttrArgs    *pathAttrArgs;
    u32 len;

    ISFS_GETFD();

    if ((fname == NULL) ||
            ((len = strnlen(fname, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_CreateFile_out;
    }

    /* Issue the file create command */
    pathAttrArgs = (ISFSPathAttrArgs *) __isfsBuf;
    memcpy(pathAttrArgs->path, fname, len+1);
    pathAttrArgs->attr = fileAttr;
    pathAttrArgs->ownerAccess = ownerAcc;
    pathAttrArgs->groupAccess = groupAcc;
    pathAttrArgs->othersAccess = othersAcc;

    rc = IOS_Ioctl(__isfsFd, ISFS_FCREATE, (u8 *) pathAttrArgs,
                sizeof (ISFSPathAttrArgs), NULL, 0);

ISFS_CreateFile_out:

    ISFS_RELFD();

    return (rc);
}


ISFSError
ISFS_SetFileVersionControl(const u8 *fname, u32 enable)
{
    ISFSError           rc = ISFS_ERROR_OK;
    ISFSPathAttrArgs    *pathAttrArgs;
    u32                 len;

    ISFS_GETFD();

    if ((fname == NULL) ||
            ((len = strnlen(fname, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN)) {
        rc = ISFS_ERROR_INVALID;
        goto ISFS_SetFileVersionControl_out;
    }

    /* Issue the set attr command */
    pathAttrArgs = (ISFSPathAttrArgs *) __isfsBuf;

    memcpy(pathAttrArgs->path, fname, len+1);
    pathAttrArgs->attr = enable;

    rc = IOS_Ioctl(__isfsFd, ISFS_FSETVCTRL, (u8 *) pathAttrArgs,
                sizeof (ISFSPathAttrArgs), NULL, 0);

ISFS_SetFileVersionControl_out:

    ISFS_RELFD();

    return (rc);
}


IOSFd
ISFS_Open(const u8 *fname, u32 access)
{
    return (IOS_Open(fname, access));
}


ISFSError
ISFS_GetFileStats(IOSFd fd, ISFSFileStats *stats)
{
    return (IOS_Ioctl(fd, ISFS_FSTATS, NULL, 0, stats, sizeof (ISFSFileStats)));
}


ISFSError
ISFS_Seek(IOSFd fd, s32 offset, u32 whence)
{
    return (IOS_Seek(fd, offset, whence));
}


ISFSError
ISFS_Read(IOSFd fd, u8 *buf, u32 size)
{
    return (IOS_Read(fd, buf, size));
}


ISFSError
ISFS_Write(IOSFd fd, const u8 *buf, u32 size)
{
    return (IOS_Write(fd, (u8 *) buf, size));
}


ISFSError
ISFS_Close(IOSFd fd)
{
    return (IOS_Close(fd));
}
