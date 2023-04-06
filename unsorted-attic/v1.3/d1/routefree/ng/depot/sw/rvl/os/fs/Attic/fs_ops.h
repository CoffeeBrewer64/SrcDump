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
 *      This file declares the file system operations
 *
 */


#ifndef __FS_OPS_H__
#define __FS_OPS_H__


#ifdef NET_CARD
#include <sc/iostypes.h>
#include <sc/fs.h>
#else
#include <iostypes.h>
#include <fs.h>
#endif


/* File descriptor entry */
typedef struct {
    u16         inUse;      /* This entry is in-use */
    IOSGid      gid;        /* Group ID */
    IOSUid      uid;        /* User ID */
    u32         inodeNum;   /* Inode number */
    u32         access;     /* Read-write access granted to this fd */
    u32         offset;     /* File offset used by the fs_ops layer */
    u32         nOffset;    /* Non-aligned file offset used by caching */
    u32         size;       /* Current size of the file */
    u32         changed;    /* File has been changed since opened */
    ISFSError   error;      /* Cached error value */
} ISFSFdEntry;


/*
 *  Description:
 *      File system operations
 *
 */
ISFSError   isfsFormat(IOSUid);
ISFSError   isfsGetStats(ISFSStats *stats);
ISFSError   isfsCreateDir(IOSUid, IOSGid, const u8 *, u32, u32, u32, u32);
ISFSError   isfsReadDir(IOSUid, IOSGid, const u8 *, u8 *, u32 *);
ISFSError   isfsSetAttr(IOSUid, const u8 *, IOSUid, IOSGid, u32, u32, u32, u32);
ISFSError   isfsGetAttr(IOSUid, IOSGid, const u8 *, IOSUid *,
                    IOSGid *, u32 *, u32 *, u32 *, u32 *);
ISFSError   isfsDelete(IOSUid, IOSGid, const u8 *);
ISFSError   isfsRename(IOSUid, IOSGid, const u8 *, const u8 *);
ISFSError   isfsCreateFile(IOSUid, IOSGid, const u8 *, u32, u32, u32, u32);
ISFSError   isfsSetVersionControl(IOSUid, const u8 *, u32);
s32         isfsOpen(IOSUid, IOSGid, const u8 *, u32);
ISFSError   isfsGetFileStats(s32, ISFSFileStats *);
ISFSError   isfsSeek(s32, s32, u32);
ISFSError   isfsRead(s32, u8 *, u32);
ISFSError   isfsWrite(s32, const u8 *, u32);
ISFSError   isfsClose(s32);


/*
 *  Description:
 *      Operations only called by the resource manager
 */
s32         isfsGetNextAvailFdEntry(IOSUid, IOSGid, u32, u32, u32);
ISFSError   isfsMount(u32);


#endif /* __FS_OPS_H__ */
