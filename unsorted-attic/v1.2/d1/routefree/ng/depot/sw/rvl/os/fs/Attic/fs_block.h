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
 *      This file declares the FS block level functionalities
 *
 */


#ifndef __FS_BLOCK_H__
#define __FS_BLOCK_H__


#ifdef NET_CARD
#include <sc/iostypes.h>
#include <sc/flash.h>
#include <sc/fs.h>
#else
#include <iostypes.h>
#include <flash.h>
#include <fs.h>
#endif


extern FLDevCap     __isfsFlashCap;


typedef u16         ISFSBlockEntry;

/*
 *  Description:
 *      Custom data used in the HMAC computation:
 *      1) Owner ID
 *      2) Relative file name
 *      3) Logical FS block index
 *      4) Inode array index 
 *      5) File version number
 *
 */
typedef struct {
    IOSUid          ownerId;
    u8              fname[ISFS_INODE_NAMELEN];
    u32             blockOffset;
    u32             inodeIndex;
    u32             fVersion;
    u8              pad[36];        /* Pad to 64 bytes */
} ISFSCustomData;

#define ISFS_IV_LEN             16
#define ISFS_MAC_LEN            20
#define ISFS_CUSTOM_DATA_LEN    64


/*
 *  Description:
 *      FS constants that depend on the flash capabilities
 *
 */
#define ISFS_BLOCK_ENTRIES                                                  \
        (1 << (__isfsFlashCap.totalSzShift - ISFS_BLOCK_SIZE_SHIFT))

#define ISFS_BLOCKS_IN_FL_BLOCK                                             \
        (1 << (__isfsFlashCap.erasableBlockSzShift - ISFS_BLOCK_SIZE_SHIFT))

#define ISFS_BLOCKS_IN_FL_BLOCK_SHIFT                                       \
        (__isfsFlashCap.erasableBlockSzShift - ISFS_BLOCK_SIZE_SHIFT)

/*
 *  Description:
 *      Block operation flags
 *
 */
#define ISFS_BLOCK_OP_ENCRYPTION        0x1
#define ISFS_BLOCK_OP_AUTH              0x2
#define ISFS_BLOCK_OP_CHAIN             0x4


/*
 *  Description:
 *      Operations to read/write/copy the flash based on
 *      FS block boundaries
 *
 */
ISFSError isfsInitFsBlocks(int);
ISFSError isfsReadFsBlocks(ISFSBlockEntry, u32, u32, ISFSCustomData *, u8 *, u8 *);
ISFSError isfsWriteFsBlocks(ISFSBlockEntry, u32, u32, ISFSCustomData *,
                        const u8 *, const u8 *);
ISFSError isfsCopyFsBlocks(ISFSBlockEntry, ISFSBlockEntry, u32);
ISFSError isfsStatusFsBlock(ISFSBlockEntry);


#endif /* __FS_BLOCK_H__ */
