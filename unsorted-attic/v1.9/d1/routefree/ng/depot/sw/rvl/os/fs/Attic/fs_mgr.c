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
 *      This file implements the resource manager for the SCFS and the
 *      flash device driver
 *
 */


#ifdef NET_CARD
#include <sc/libc.h>
#include <sc/iostypes.h>
#include <sc/sc.h>
#include <sc/ios.h>
#include <sc/flash.h>
#include <sc/fs.h>

#include "sc/fl_ops.h"
#include "fs_utils.h"
#include "fs_fat.h"
#include "sc/fs_ops.h"
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <iop.h>
#include <ios.h>
#include <flash.h>
#include <fs.h>

#include "fl_ops.h"
#include "fs_utils.h"
#include "fs_fat.h"
#include "fs_ops.h"
#endif


#define STACK_SIZE                  (2*1024)
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 13;


/* FS cache buffer, the size must align on 16-byte boundary */
typedef struct {
    u8          buf[ISFS_BLOCK_SIZE]; /* FS Cache buffer */
    ISFSFdEntry *entry;             /* Pointer to the fd entry */
    u32         dirty;              /* Dirty bit */
    u32         offset;             /* Offset of the buffer */
    u32         size;               /* Size of valid data */
} ISFSCacheBuf;


/* Resource manager queue size and paths */
#define ISFS_RESRC_MGR_QSIZE        8       /* Few simultaneous requests */
#define ISFS_RESRC_MGR_FLASH_PATH   "/dev/flash"
#define ISFS_RESRC_MGR_FS_PATH      "/"

/* FS cache buffer pool size */
#define ISFS_CACHEBUF_POOLSIZE      1

/* FS cache buffer pool */
static ISFSCacheBuf   __isfsCachePool[ISFS_CACHEBUF_POOLSIZE]               \
                        __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));


/* Cache manipulation functions */
static ISFSCacheBuf *__isfsGetNewCacheBuf(ISFSFdEntry *);
static ISFSCacheBuf *__isfsFindCacheBuf(ISFSFdEntry *);
static ISFSError    __isfsFlushCacheBuf(ISFSCacheBuf *);

/* Command processing functions */
static IOSError     __isfsResrcMgrHandleFlashReq(IOSResourceRequest *);
static ISFSError    __isfsResrcMgrOpen(IOSResourceRequest *);
static s32          __isfsResrcMgrRead(IOSResourceRequest *);
static s32          __isfsResrcMgrWrite(IOSResourceRequest *);
static s32          __isfsResrcMgrSeek(IOSResourceRequest *);
static ISFSError    __isfsResrcMgrIoctl(IOSResourceRequest *);
static ISFSError    __isfsResrcMgrIoctlv(IOSResourceRequest *);
static ISFSError    __isfsResrcMgrClose(IOSResourceRequest *);


static ISFSCacheBuf *
__isfsGetNewCacheBuf(ISFSFdEntry *entry)
{
    u32     count, clean = ISFS_CACHEBUF_POOLSIZE;

    /* Search for available or clean entry */
    for (count = 0; count < ISFS_CACHEBUF_POOLSIZE; count++) {
        if (__isfsCachePool[count].entry == NULL) {
            break;
        } else if (__isfsCachePool[count].dirty == 0) {
            clean = count;
        }
    }

    if (count == ISFS_CACHEBUF_POOLSIZE) {
        /* Choose a buffer to be reclaimed */
        if (clean != ISFS_CACHEBUF_POOLSIZE) {
            count = clean;  /* Prefer a clean buffer */
        } else {
            count = 0;      /* Pick buf 0 if none available */

            /* Record flush error in old fd entry */
            __isfsCachePool[count].entry->error =
                                __isfsFlushCacheBuf(&__isfsCachePool[count]);
        }
    }

    __isfsCachePool[count].entry = entry;
    __isfsCachePool[count].dirty = 0;
    __isfsCachePool[count].offset = 0;
    __isfsCachePool[count].size = 0;

    return (&__isfsCachePool[count]);
}


static ISFSCacheBuf *
__isfsFindCacheBuf(ISFSFdEntry *entry)
{
    ISFSCacheBuf    *cbuf = NULL;
    u32             count;

    for (count = 0; count < ISFS_CACHEBUF_POOLSIZE; count++) {
        if (__isfsCachePool[count].entry == entry) {
            cbuf = &__isfsCachePool[count];
            break;
        }
    }

    return (cbuf);
}


static ISFSError
__isfsFlushCacheBuf(ISFSCacheBuf *cbuf)
{
    ISFSError rc    = ISFS_ERROR_OK;

    if ((cbuf->entry != NULL) && (cbuf->dirty)) {
        rc = isfsSeek((u32) cbuf->entry, cbuf->offset, IOS_SEEK_SET);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to seek\n");
            goto __isfsFlushCacheBuf_out;
        } 

        rc = isfsWrite((s32) cbuf->entry, cbuf->buf, cbuf->size);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to flush\n");
            goto __isfsFlushCacheBuf_out;
        }

        cbuf->dirty = 0;
    }

__isfsFlushCacheBuf_out:

    return (rc);
}


/*
 * Handle flash requests
 */
static IOSError
__isfsResrcMgrHandleFlashReq(IOSResourceRequest *req)
{
    IOSError            rc = ISFS_ERROR_OK;
    FLContext           *ctx = (FLContext *) req->handle;
    FLDevCap            cap;
    u32                 size, totalPageSz, pageOffset;
    u8                  *spare;
    IOSResourceRead     *argsRead;
    IOSResourceWrite    *argsWrite;
    IOSResourceSeek     *argsSeek;
    IOSResourceIoctl    *argsIoctl;

    ISFS_ENTRY();

    rc = flGetCap(&cap);
    if (rc != IOS_ERROR_OK) {
        goto __isfsResrcMgrHandleFlashReq_out;
    }
    totalPageSz = (1 << cap.pageSzShift) + (1 << cap.pageSpareSzShift);

    switch (req->cmd) {
        case (IOS_READ):
            argsRead = (IOSResourceRead *) &(req->args.read);

            size = argsRead->outLen;
            if (size == totalPageSz) {
                spare = argsRead->outPtr + (1 << cap.pageSzShift);
            } else if (size == (1 << cap.pageSzShift)) {
                spare = NULL;
            } else {
                rc = IOS_ERROR_INVALID;
                goto __isfsResrcMgrHandleFlashReq_out;
            }

            rc = flReadPage(ctx->pageOffset, argsRead->outPtr, spare);
            if (rc == IOS_ERROR_OK) {
                ctx->pageOffset++;
                rc = size;
            }

            break;

        case (IOS_WRITE):
            argsWrite = (IOSResourceWrite *) &(req->args.write);

            size = argsWrite->inLen;
            if (size == totalPageSz) {
                spare = argsWrite->inPtr + (1 << cap.pageSzShift);
            } else if (size == (1 << cap.pageSzShift)) {
                spare = NULL;
            } else {
                rc = IOS_ERROR_INVALID;
                goto __isfsResrcMgrHandleFlashReq_out;
            }

            rc = flWritePage(ctx->pageOffset, argsWrite->inPtr, spare, 0, 1);
            if (rc == IOS_ERROR_OK) {
                ctx->pageOffset++;
                rc = size;
            }

            break;

        case (IOS_SEEK):
            argsSeek = (IOSResourceSeek *) &(req->args.seek);

            switch (argsSeek->whence) {
                case (IOS_SEEK_SET):
                    pageOffset = argsSeek->offset;
                    break;

                case (IOS_SEEK_CURRENT):
                    pageOffset = ctx->pageOffset;
                    pageOffset += argsSeek->offset;
                    break;

                case (IOS_SEEK_END):
                    pageOffset = (1 << (cap.totalSzShift - cap.pageSzShift)) +
                                    argsSeek->offset;
                    break;

                default:
                    isfsPrint(ISFS_DEBUG_ERROR, "Unknown seek offset,"
                                            " whence=%d\n", argsSeek->whence);
                    rc = IOS_ERROR_INVALID;
                    goto __isfsResrcMgrHandleFlashReq_out;
            }

            if (pageOffset > (1 << (cap.totalSzShift - cap.pageSzShift))) {
                rc = IOS_ERROR_INVALID;
            } else {
                rc = ctx->pageOffset = pageOffset;
            }

            break;

        case (IOS_IOCTL):
            argsIoctl = (IOSResourceIoctl *) &(req->args.ioctl);

            size = argsIoctl->outLen;
            switch (argsIoctl->cmd) {
                case (FL_GETCAP):
                    if (size < sizeof (FLDevCap)) {
                        rc = IOS_ERROR_INVALID;
                        goto __isfsResrcMgrHandleFlashReq_out;
                    }
                    memcpy(argsIoctl->outPtr, &cap, sizeof (FLDevCap));

                    break;

                case (FL_GETSTATS):
                    if (size < sizeof (FLStats)) {
                        rc = IOS_ERROR_INVALID;
                        goto __isfsResrcMgrHandleFlashReq_out;
                    }
                    rc = flGetStats((FLStats *) argsIoctl->outPtr);

                    break;

                case (FL_ERASE):
                    rc = flErase(ctx->pageOffset >>
                                (FL_LOGI_BLOCK_SIZE_SHIFT - cap.pageSzShift));
                    break;

                case (FL_STATUS):
                    rc = flStatus(ctx->pageOffset >>
                                (FL_LOGI_BLOCK_SIZE_SHIFT - cap.pageSzShift));
                    break;

                default:
                    isfsPrint(ISFS_DEBUG_ERROR, "Invalid Ioctl command, %d\n",
                                            argsIoctl->cmd);
                    rc = IOS_ERROR_INVALID;
                    goto __isfsResrcMgrHandleFlashReq_out;
            }

            break;

        case (IOS_CLOSE):
            ctx->inUse = 0;
            break;

        default:
            isfsPrint(ISFS_DEBUG_ERROR, "Unknown message command,"
                                    " cmd=%d\n", req->cmd);
            rc = IOS_ERROR_INVALID;
            break;
    }

__isfsResrcMgrHandleFlashReq_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrOpen
 *
 *  Description:
 *      This function assigns a context to the caller. If
 *      the path references a real file, isfsOpen() is called.
 *      If the path references a device driver, then the
 *      command is dropped
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful completion
 *      ISFS_ERROR_MAXFD - Ran out of available context
 *      ISFS_ERROR_DEV - Request is for an unrelated device driver
 *      Other error values from isfsOpen()
 *
 */
static ISFSError
__isfsResrcMgrOpen(IOSResourceRequest *req)
{
    ISFSError       rc = ISFS_ERROR_OK;
    IOSResourceOpen *args = (IOSResourceOpen *) &(req->args.open);
    s32             fsReq = 0, flashReq = 0;

    ISFS_ENTRY();

    isfsPrint(ISFS_DEBUG_INFO, "Path is %s, flags=0x%x, UID=0x%x, GID=0x%x\n",
                        args->path, args->flags, args->uid, args->gid);

    /* Check for requests destined to other device drivers */
    if (!strncmp(args->path, "/dev/", 5)) {
        if (!strncmp(&args->path[5], "fs", 3)) {
            fsReq = 1;
        } else if (!strncmp(&args->path[5], "flash", 6)) {
            flashReq = 1;
        } else {
            rc = IOS_ERROR_NOEXISTS;
            goto __isfsResrcMgrOpen_out;
        }
    }

    if (flashReq == 1) {
        if (args->uid != IOS_ROOT_ID) {
            rc = IOS_ERROR_ACCESS;
            goto __isfsResrcMgrOpen_out;
        } else {
            rc = flGetNextAvailCtx();
        }
    } else if (fsReq == 1) {
        /* Open a general connection to the file system */
        rc = isfsGetNextAvailFdEntry(args->uid, args->gid,
                                ISFS_INODENUM_INVALID, 0, 0);
    } else {
        /* Open a specific file */
        rc = isfsOpen(args->uid, args->gid, args->path, args->flags);
        if (rc < 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to open file, rc=%d\n", rc);
        }
    }

__isfsResrcMgrOpen_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrRead
 *
 *  Description:
 *      This function calls isfsRead()
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      >= 0 - Number of bytes read
 *      ISFS_ERROR_INVALID - Invalid context
 *      Other error values from isfsRead()
 *
 */
static s32
__isfsResrcMgrRead(IOSResourceRequest *req)
{
    ISFSError       rc = ISFS_ERROR_OK;
    IOSResourceRead *args = (IOSResourceRead *) &(req->args.read);
    ISFSFdEntry     *entry = (ISFSFdEntry *) req->handle;
    ISFSCacheBuf    *cbuf;
    u32             bytesRead = 0, size = args->outLen;

    ISFS_ENTRY();

    /* Return existing error */
    if (entry->error != ISFS_ERROR_OK) {
        rc = entry->error;
        goto __isfsResrcMgrRead_out;
    }

    /* Make sure the entry points to a normal file */
    if (entry->inodeNum == ISFS_INODENUM_INVALID) {
        rc = ISFS_ERROR_INVALID;
        goto __isfsResrcMgrRead_out;
    }

    /* Only read up to the file size */
    if ((entry->nOffset + size) > entry->size) {
        size = entry->size - entry->nOffset;
    }

    while (size > 0) {
        u32     destOffset;
        u8      *ptr;

        /* Check the cache buffer */
        cbuf = __isfsFindCacheBuf(entry);
        if (cbuf && (cbuf->offset ==
                (entry->nOffset & ~(ISFS_BLOCK_SIZE - 1)))) {
            u32     offsetInBlock, readSize;

            /* Offset to requested data in block */
            offsetInBlock = entry->nOffset - cbuf->offset;

            /* Size of requested data within this block */
            readSize = ISFS_BLOCK_SIZE - offsetInBlock;
            readSize = (readSize < size) ? readSize : size;

            /* Copy over the data */
            memcpy(args->outPtr + bytesRead, &(cbuf->buf[offsetInBlock]),
                readSize);
            size -= readSize;
            bytesRead += readSize;

            /* Increment the file descriptor's offset */
            entry->nOffset += readSize;
            continue;
        }

        destOffset = entry->nOffset & ~(ISFS_BLOCK_SIZE - 1);

        /* Read either into the cache buffer or the user buffer directly */
        if (((entry->nOffset & (ISFS_BLOCK_SIZE - 1)) == 0) &&
                (size >= ISFS_BLOCK_SIZE) &&
                ((((u32)args->outPtr + bytesRead) &
                    (FL_BASE_ALIGN_SZ - 1)) == 0)) {
            ptr = args->outPtr + bytesRead;
            size -= ISFS_BLOCK_SIZE;
            bytesRead += ISFS_BLOCK_SIZE;

            rc = isfsSeek((s32) entry, destOffset, IOS_SEEK_SET);
            if (rc != ISFS_ERROR_OK) {
                goto __isfsResrcMgrRead_out;
            }
            entry->nOffset += ISFS_BLOCK_SIZE;
        } else {
            if (cbuf == NULL) {
                cbuf = __isfsGetNewCacheBuf(entry);
            } else {
                rc = __isfsFlushCacheBuf(cbuf);
                if (rc != ISFS_ERROR_OK) {
                    goto __isfsResrcMgrRead_out;
                }
            }
            ptr = cbuf->buf;

            /* Set the cache buf state */
            cbuf->offset = destOffset;
            cbuf->size = entry->size - destOffset;
            if (cbuf->size > ISFS_BLOCK_SIZE) {
                cbuf->size = ISFS_BLOCK_SIZE;
            }

            rc = isfsSeek((s32) entry, destOffset, IOS_SEEK_SET);
            if (rc != ISFS_ERROR_OK) {
                goto __isfsResrcMgrRead_out;
            }
        }

        rc = isfsRead((s32) entry, ptr, ISFS_BLOCK_SIZE);
        if (rc != ISFS_ERROR_OK) {
            goto __isfsResrcMgrRead_out;
        }
    }
    rc = bytesRead;

__isfsResrcMgrRead_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrWrite
 *
 *  Description:
 *      This function calls isfsWrite()
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      >= 0 - Number of bytes written
 *      ISFS_ERROR_INVALID - Invalid context
 *      Other error values from isfsRead()
 *
 */
static s32
__isfsResrcMgrWrite(IOSResourceRequest *req)
{
    ISFSError           rc = ISFS_ERROR_OK;
    IOSResourceWrite    *args = (IOSResourceWrite *) &(req->args.write);
    ISFSFdEntry         *entry = (ISFSFdEntry *) req->handle;
    ISFSCacheBuf        *cbuf;
    u32                 bytesWritten = 0, size = args->inLen;

    ISFS_ENTRY();

    /* Return existing error */
    if (entry->error != ISFS_ERROR_OK) {
        rc = entry->error;
        goto __isfsResrcMgrWrite_out;
    }

    /* Make sure the entry points to a normal file */
    if (entry->inodeNum == ISFS_INODENUM_INVALID) {
        rc = ISFS_ERROR_INVALID;
        goto __isfsResrcMgrWrite_out;
    }

    /* Check here is necessary since the write may not be committed */
    if ((entry->access & ISFS_WRITE_ACCESS) == 0) {
        rc = ISFS_ERROR_ACCESS;
        goto __isfsResrcMgrWrite_out;
    }

    while (size > 0) {
        u32     destOffset;

        /* Check the cache buffer */
        cbuf = __isfsFindCacheBuf(entry);
        if (cbuf && (cbuf->offset ==
                (entry->nOffset & ~(ISFS_BLOCK_SIZE - 1)))) {
            u32     offsetInBlock, writeSize;

            /* Offset to requested data in block */
            offsetInBlock = entry->nOffset - cbuf->offset;

            /* Size of requested data within this block */
            writeSize = ISFS_BLOCK_SIZE - offsetInBlock;
            writeSize = (writeSize < size) ? writeSize : size;

            /* Copy over the data */
            memcpy(&(cbuf->buf[offsetInBlock]), args->inPtr + bytesWritten,
                writeSize);
            size -= writeSize;
            bytesWritten += writeSize;

            /* Mark the cache buffer as dirty */
            cbuf->dirty = 1;

            /* Increment the file descriptor's offset */
            entry->nOffset += writeSize;

            /* Adjust the size both for the fd entry and for the cache */
            if (entry->size < entry->nOffset) {
                entry->size = entry->nOffset;
            }
            if (entry->nOffset > (cbuf->offset + cbuf->size)) {
                cbuf->size = entry->nOffset - cbuf->offset;
            }

            /* Flush the buffer when the end of the block is reached */
            if ((entry->nOffset & (ISFS_BLOCK_SIZE - 1)) == 0) {
                rc = __isfsFlushCacheBuf(cbuf);
                if (rc != ISFS_ERROR_OK) {
                    goto __isfsResrcMgrWrite_out;
                }
            }

            continue;
        }

        destOffset = entry->nOffset & ~(ISFS_BLOCK_SIZE - 1);

        /* Write either to the cache buffer or the flash directly */
        if (((entry->nOffset & (ISFS_BLOCK_SIZE - 1)) == 0) &&
                (size >= ISFS_BLOCK_SIZE) &&
                ((((u32)args->inPtr + bytesWritten) &
                    (FL_BASE_ALIGN_SZ - 1)) == 0)) {
            rc = isfsSeek((s32) entry, destOffset, IOS_SEEK_SET);
            if (rc != ISFS_ERROR_OK) {
                goto __isfsResrcMgrWrite_out;
            }

            rc = isfsWrite((s32) entry, args->inPtr + bytesWritten,
                    ISFS_BLOCK_SIZE);
            if (rc != ISFS_ERROR_OK) {
                goto __isfsResrcMgrWrite_out;
            }

            size -= ISFS_BLOCK_SIZE;
            bytesWritten += ISFS_BLOCK_SIZE;
            entry->nOffset += ISFS_BLOCK_SIZE;

            /* Adjust the size for the fd entry */
            if (entry->size < entry->nOffset) {
                entry->size = entry->nOffset;
            }
        } else {
            if (cbuf == NULL) {
                cbuf = __isfsGetNewCacheBuf(entry);
            } else {
                rc = __isfsFlushCacheBuf(cbuf);
                if (rc != ISFS_ERROR_OK) {
                    goto __isfsResrcMgrWrite_out;
                }
            }

            cbuf->offset = destOffset;
            cbuf->size = entry->size - destOffset;
            if (cbuf->size > ISFS_BLOCK_SIZE) {
                cbuf->size = ISFS_BLOCK_SIZE;
            }

            if (cbuf->size != 0) {
                u32     grantReadAccess = 0;

                rc = isfsSeek((s32) entry, destOffset, IOS_SEEK_SET);
                if (rc != ISFS_ERROR_OK) {
                    goto __isfsResrcMgrWrite_out;
                }

                /* Grant temporary read access */
                if ((entry->access & ISFS_READ_ACCESS) == 0) {
                    entry->access |= ISFS_READ_ACCESS;
                    grantReadAccess = 1;
                }

                rc = isfsRead((s32) entry, cbuf->buf, ISFS_BLOCK_SIZE);
                if (grantReadAccess) {
                    entry->access &= ~ISFS_READ_ACCESS;
                }
                if (rc != ISFS_ERROR_OK) {
                    goto __isfsResrcMgrWrite_out;
                }
            }
        }
    }
    rc = bytesWritten;

__isfsResrcMgrWrite_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrSeek
 *
 *  Description:
 *      This function calls isfsSeek()
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      >= 0 - Current offset
 *      ISFS_ERROR_INVALID - Invalid context
 *      Other error values from isfsRead()
 *
 */
static s32
__isfsResrcMgrSeek(IOSResourceRequest *req)
{
    ISFSError       rc = ISFS_ERROR_OK;
    IOSResourceSeek *args = (IOSResourceSeek *) &(req->args.seek);
    ISFSFdEntry     *entry = (ISFSFdEntry *) req->handle;
    u32             offset;

    ISFS_ENTRY();

    /* Return existing error */
    if (entry->error != ISFS_ERROR_OK) {
        rc = entry->error;
        goto __isfsResrcMgrSeek_out;
    }

    /* Make sure the entry points to a normal file */
    if (entry->inodeNum == ISFS_INODENUM_INVALID) {
        rc = ISFS_ERROR_INVALID;
        goto __isfsResrcMgrSeek_out;
    }

    /* Calculate the desired offset */
    switch (args->whence) {
        case (IOS_SEEK_SET):
            offset = 0;
            break;

        case (IOS_SEEK_CURRENT):
            offset = entry->nOffset;
            break;

        case (IOS_SEEK_END):
            offset = entry->size;
            break;

        default:
            rc = ISFS_ERROR_INVALID;
            goto __isfsResrcMgrSeek_out;
    }
    offset += args->offset;

    if ((offset < 0) || (offset > entry->size)) {
        rc = ISFS_ERROR_INVALID;
        goto __isfsResrcMgrSeek_out;
    }

    /* Delay the actual seek in read/write, just set the values here */
    rc = entry->nOffset = offset;

__isfsResrcMgrSeek_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrIoctl
 *
 *  Description:
 *      This function calls the other FS commands
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful completion
 *      Other error values from the FS commands
 *
 */
static ISFSError
__isfsResrcMgrIoctl(IOSResourceRequest *req)
{
    ISFSError           rc = ISFS_ERROR_OK;
    IOSResourceIoctl    *args = (IOSResourceIoctl *) &(req->args.ioctl);
    ISFSFdEntry         *entry = (ISFSFdEntry *) req->handle;
    ISFSPathsArgs       *pathsArgs;
    ISFSPathAttrArgs    *pathAttrArgs;
    u32                 ownerAcc, groupAcc, othersAcc, attr;

    ISFS_ENTRY();

    isfsPrint(ISFS_DEBUG_INFO, "Ioctl command %d\n", args->cmd);

    /* Process the various ioctl commands */
    switch (args->cmd) {
        case (ISFS_FORMAT):
            rc = isfsFormat(entry->uid);
            break;

        case (ISFS_STATS):
            if (args->outLen < sizeof (ISFSStats)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            rc = isfsGetStats((ISFSStats *) args->outPtr);
            break;

        case (ISFS_DCREATE):
            if (args->inLen < sizeof (ISFSPathAttrArgs)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            pathAttrArgs = (ISFSPathAttrArgs *) args->inPtr;
            rc = isfsCreateDir(entry->uid, entry->gid,
                    (const u8 *) pathAttrArgs->path, pathAttrArgs->attr,
                    pathAttrArgs->ownerAccess, pathAttrArgs->groupAccess,
                    pathAttrArgs->othersAccess);

            break;

        case (ISFS_SETATTR):
            if (args->inLen < sizeof (ISFSPathAttrArgs)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            pathAttrArgs = (ISFSPathAttrArgs *) args->inPtr;
            rc = isfsSetAttr(entry->uid, (const u8 *) pathAttrArgs->path,
                        pathAttrArgs->ownerId, pathAttrArgs->groupId,
                        pathAttrArgs->attr, pathAttrArgs->ownerAccess,
                        pathAttrArgs->groupAccess, pathAttrArgs->othersAccess);

            break;

        case (ISFS_GETATTR):
            if ((args->inLen < ISFS_PATH_MAXLEN) ||
                    (args->outLen < sizeof (ISFSPathAttrArgs))) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            pathAttrArgs = (ISFSPathAttrArgs *) args->outPtr;
            rc = isfsGetAttr(entry->uid, entry->gid, args->inPtr,
                        &(pathAttrArgs->ownerId), &(pathAttrArgs->groupId),
                        &attr, &ownerAcc, &groupAcc, &othersAcc);

#ifdef NAPA_WORKAROUND      /* TODO: Temporary workaround */
            u32     word, *wordPtr;

            word = (groupAcc & 0xff) | ((ownerAcc & 0xff) << 8);
            wordPtr = (u32 *) (&(pathAttrArgs->ownerAccess) - 2);
            *wordPtr = word;

            word = ((attr & 0xff) << 16) | ((othersAcc & 0xff) << 24);
            wordPtr = (u32 *) &(pathAttrArgs->othersAccess);
            *wordPtr = word;
#else
            pathAttrArgs->attr = attr;
            pathAttrArgs->ownerAccess = ownerAcc;
            pathAttrArgs->groupAccess = groupAcc;
            pathAttrArgs->othersAccess = othersAcc;
#endif

            break;

        case (ISFS_DEL):
            if (args->inLen < ISFS_PATH_MAXLEN) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            rc = isfsDelete(entry->uid, entry->gid, args->inPtr);

            break;

        case (ISFS_RENAME):
            if (args->inLen < sizeof (ISFSPathsArgs)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            pathsArgs = (ISFSPathsArgs *) args->inPtr;
            rc = isfsRename(entry->uid, entry->gid, pathsArgs->path1,
                        pathsArgs->path2);

            break;

        case (ISFS_FCREATE):
            if (args->inLen < sizeof (ISFSPathAttrArgs)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            pathAttrArgs = (ISFSPathAttrArgs *) args->inPtr;
            rc = isfsCreateFile(entry->uid, entry->gid,
                            (const u8 *) pathAttrArgs->path, pathAttrArgs->attr,
                            pathAttrArgs->ownerAccess,
                            pathAttrArgs->groupAccess,
                            pathAttrArgs->othersAccess);

            break;

        case (ISFS_FSETVCTRL):
            if (args->inLen < sizeof (ISFSPathAttrArgs)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            pathAttrArgs = (ISFSPathAttrArgs *) args->inPtr;
            rc = isfsSetVersionControl(entry->uid, 
                                (const u8 *) pathAttrArgs->path,
                                pathAttrArgs->attr);

            break;

        case (ISFS_FSTATS):
            if (args->outLen < sizeof (ISFSFileStats)) {
                rc = ISFS_ERROR_INVALID;
                break;
            }

            if (entry->error != ISFS_ERROR_OK) {
                rc = entry->error;
            } else if ((entry->access & ISFS_READ_ACCESS) == 0) {
                rc = ISFS_ERROR_ACCESS;
            } else if (entry->inodeNum == ISFS_INODENUM_INVALID) {
                rc = ISFS_ERROR_INVALID;
            } else {
                ((ISFSFileStats *) args->outPtr)->size = entry->size;
                ((ISFSFileStats *) args->outPtr)->offset = entry->nOffset;
            }

            break;

        default:
            isfsPrint(ISFS_DEBUG_ERROR, "Unknown ioctl command, cmd=%d\n",
                                args->cmd);
            rc = ISFS_ERROR_INVALID;
            break;
    }

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrIoctlv
 *
 *  Description:
 *      This function calls the other FS commands
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful completion
 *      Other error values from the FS commands
 *
 */
static ISFSError
__isfsResrcMgrIoctlv(IOSResourceRequest *req)
{
    ISFSError           rc = ISFS_ERROR_OK;
    IOSResourceIoctlv   *args = (IOSResourceIoctlv *) &(req->args.ioctlv);
    ISFSFdEntry         *entry = (ISFSFdEntry *) req->handle;
    u8                  *dname, *nameList;
    u32                 *num;

    ISFS_ENTRY();

    isfsPrint(ISFS_DEBUG_INFO, "Ioctl command %d\n", args->cmd);

    /* Process the various ioctl commands */
    switch (args->cmd) {
        case (ISFS_DREAD):
            if (args->vector[0].length != ISFS_PATH_MAXLEN) {
                rc = ISFS_ERROR_INVALID;
                break;
            }
            dname = args->vector[0].base;

            if (args->readCount == 2) {     /* nameList != NULL */
                if ((args->vector[1].length != 4) ||
                        (args->vector[3].length != 4)) {
                    rc = ISFS_ERROR_INVALID;
                    break;
                }
                num = (u32 *) args->vector[1].base;

                if (args->vector[2].length !=
                        (*num * (ISFS_INODE_NAMELEN + 1))) {
                    rc = ISFS_ERROR_INVALID;
                    break;
                }
                nameList = args->vector[2].base;
            } else {                        /* nameList == NULL */
                if (args->vector[1].length != 4) {
                    rc = ISFS_ERROR_INVALID;
                    break;
                }
                num = (u32 *) args->vector[1].base;

                nameList = NULL;
            }

            rc = isfsReadDir(entry->uid, entry->gid, dname, nameList, num);

            break;

        default:
            isfsPrint(ISFS_DEBUG_ERROR, "Unknown ioctlv command, cmd=%d\n",
                                args->cmd);
            rc = ISFS_ERROR_INVALID;
            break;
    }

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsResrcMgrClose
 *
 *  Description:
 *      This function calls isfsClose()
 *
 *  Inputs:
 *      req - Resource manager request
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful completion
 *      ISFS_ERROR_INVALID - Invalid context
 *      Other error values from isfsRead()
 *
 */
static ISFSError
__isfsResrcMgrClose(IOSResourceRequest *req)
{
    ISFSError       rc, final_rc = ISFS_ERROR_OK;
    ISFSFdEntry     *entry = (ISFSFdEntry *) req->handle;
    ISFSCacheBuf    *cbuf;

    ISFS_ENTRY();

    /* Return existing error */
    if (entry->error != ISFS_ERROR_OK) {
        final_rc = entry->error;
    }

    /* Flush pending write data */
    cbuf = __isfsFindCacheBuf(entry);
    if (cbuf) {
        rc = __isfsFlushCacheBuf(cbuf);
        if (rc != ISFS_ERROR_OK ) {
            final_rc = rc;
        }
        cbuf->entry = NULL;
    }

    /* Close the file */
    if (entry->inodeNum != ISFS_INODENUM_INVALID) {
        rc = isfsClose((s32) entry);
        if (rc != ISFS_ERROR_OK) {
            final_rc = rc;
            goto __isfsResrcMgrClose_out;
        }
    } else {
        entry->inUse = 0;
    }

__isfsResrcMgrClose_out:

    ISFS_EXIT();

    return (final_rc);
}


/*
 *  Function: main
 *
 *  Description:
 *      This is the entry point of the FS and flash device driver
 *      process (i.e. the resource manager).
 *
 *  Inputs:
 *      None
 *
 *  Ouputs:
 *      None
 *
 *  Return values:
 *      0 - Successful completion
 *      < 0 - Error values for regression tests
 *
 */
int
main(void)
{
    ISFSError           rc = ISFS_ERROR_OK, error = ISFS_ERROR_OK;
    IOSMessage          resrcMgrQ[ISFS_RESRC_MGR_QSIZE];
    IOSMessageQueueId   resrcMgrQId;
    IOSMessage          msg;
    IOSResourceRequest  *req;
    u32                 count;
    struct {
        u8              *dirName;
        IOSUid          uid;
        IOSGid          gid;
        u32             ownerAcc;
        u32             grpAcc;
        u32             othersAcc;
    } defDirs[] = {
        {"/sys", IOS_ROOT_ID, IOS_ROOT_GROUP,
            ISFS_RW_ACCESS, 0, 0},
        {"/title", IOS_ROOT_ID, IOS_ROOT_GROUP,
            ISFS_RW_ACCESS, ISFS_READ_ACCESS, ISFS_READ_ACCESS},
        {"/tmp", IOS_ROOT_ID, IOS_ROOT_GROUP,
            ISFS_RW_ACCESS, ISFS_RW_ACCESS, ISFS_RW_ACCESS},
        {"/share1", IOS_ROOT_ID, IOS_ROOT_GROUP,
            ISFS_RW_ACCESS, ISFS_READ_ACCESS, ISFS_READ_ACCESS},
        {"/share2", IOS_ROOT_ID, IOS_ROOT_GROUP,
            ISFS_RW_ACCESS, ISFS_RW_ACCESS, ISFS_RW_ACCESS},
    };

#ifdef USB_PRINTF
    /* Initialize the printf buffer */
    extern void  *__usbPrintfBuf;
    if ((__usbPrintfBuf = IOS_Alloc(0, PRINTF_BUF_SIZE)) == NULL) {
        rc = IOS_ERROR_MAX;
        goto main_out;
    }
#endif

    /* Create message queue for flash and FS resource managers */
    resrcMgrQId = IOS_CreateMessageQueue(resrcMgrQ,
                                    ISFS_RESRC_MGR_QSIZE);
    if (resrcMgrQId < 0) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to create resource manager queue,"
                            " rc=%d\n", rc);
        rc = resrcMgrQId;
        goto main_out;
    }

    /* Flash resource manager */
    rc = IOS_RegisterResourceManager(ISFS_RESRC_MGR_FLASH_PATH, resrcMgrQId);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to register flash resource manager,"
                            " rc=%d\n", rc);
        goto main_out;
    }

    /* FS resource manager */
    rc = IOS_RegisterResourceManager(ISFS_RESRC_MGR_FS_PATH, resrcMgrQId);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to register SCFS resource manager,"
                            " rc=%d\n", rc);
        goto main_out;
    }

    /* Open flash device driver */
    rc = flOpen();
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_CRIT, "Failed to initialize device driver,"
                            " rc=%d\n", rc);
        error = rc;
        goto main_loop;
    }

    /* Mount file system */
    rc = isfsMount(1);
    if (rc != ISFS_ERROR_OK) {
        if (rc == ISFS_ERROR_NOTREADY) {
            isfsPrint(ISFS_DEBUG_WARN, "File system needs to be"
                                    " re-formatted\n");
        } else {
            isfsPrint(ISFS_DEBUG_CRIT, "Failed to mount file system,"
                                    " rc=%d\n", rc);
            error = rc;
            goto main_loop;
        }
    }

    if (rc == ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_INFO, "Mounted file system\n");

        rc = isfsDelete(IOS_ROOT_ID, IOS_ROOT_GROUP, "/tmp");
        if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_NOEXISTS)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete /tmp, rc=%d\n", rc);
            error = rc;
            goto main_loop;
        }

        for (count = 0; count < (sizeof(defDirs)/sizeof(defDirs[0])); count++) {
            rc = isfsCreateDir(defDirs[count].uid, defDirs[count].gid,
                        defDirs[count].dirName, 0, defDirs[count].ownerAcc,
                        defDirs[count].grpAcc, defDirs[count].othersAcc);
            if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_MAXFILES) &&
                    (rc != ISFS_ERROR_EXISTS)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to create %s, rc=%d\n",
                                        defDirs[count].dirName, rc);
                error = rc;
                goto main_loop;
            }
        }
    }

    for (count = 0; count < ISFS_CACHEBUF_POOLSIZE; count++) {
        __isfsCachePool[count].entry = NULL;
    }

    isfsPrint(ISFS_DEBUG_INFO, "Enter into infinite loop\n");

main_loop:

    /* Loop for file system or flash device driver requests */
    while (1) {
        /* Receive incoming message */
        rc = IOS_ReceiveMessage(resrcMgrQId, &msg, IOS_MESSAGE_BLOCK);
        if (rc != IOS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to receive proper message,"
                                " rc=%d\n", rc);
            continue;
        }

        /* Received a new request */
        req = (IOSResourceRequest *) msg;
        isfsPrint(ISFS_DEBUG_INFO, "Received messages 0x%x, cmd=%d\n",
                            msg, req->cmd);

        /* File system init failed, can not accept requests */
        if (error != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Can not accept new requests due to"
                                    " initialization failure, rc=%d\n", error);
            rc = error;
        } else if ((req->cmd != IOS_OPEN) &&
                (flCtxCheck((void *) req->handle) == IOS_ERROR_OK)) {
            /* Handle flash requests */
            rc = __isfsResrcMgrHandleFlashReq(req);
        } else {
            /* Process file system commands */
            switch (req->cmd) {
                case (IOS_OPEN):
                    rc = __isfsResrcMgrOpen(req);
                    break;

                case (IOS_READ):
                    rc = __isfsResrcMgrRead(req);
                    break;

                case (IOS_WRITE):
                    rc = __isfsResrcMgrWrite(req);
                    break;

                case (IOS_SEEK):
                    rc = __isfsResrcMgrSeek(req);
                    break;

                case (IOS_IOCTL):
                    rc = __isfsResrcMgrIoctl(req);
                    break;

                case (IOS_IOCTLV):
                    rc = __isfsResrcMgrIoctlv(req);
                    break;

                case (IOS_CLOSE):
                    rc = __isfsResrcMgrClose(req);
                    break;

                default:
                    isfsPrint(ISFS_DEBUG_ERROR, "Unknown message command,"
                                    " cmd=%d\n", req->cmd);
                    rc = IOS_ERROR_INVALID;
                    break;
            }
        }

        /* Respond to the sender */
        IOS_ResourceReply(req, rc);
    }

    rc = isfsMount(0);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_WARN, "Failed to unmount file system,"
                                " rc=%d\n", rc);
        goto main_out;
    }

    rc = flClose();
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_WARN, "Failed to shut down flash device driver,"
                            " rc=%d\n", rc);
        goto main_out;
    }

main_out:

    return (rc);
}
