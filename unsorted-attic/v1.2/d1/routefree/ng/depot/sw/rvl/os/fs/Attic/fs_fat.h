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
 *      This file defines the basic FAT-related data structures
 *
 */


#ifndef __FS_FAT_H__
#define __FS_FAT_H__


#ifdef NET_CARD
#include <sc/libc.h>
#include <sc/iostypes.h>
#include <sc/fs.h>
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <fs.h>
#endif

#include "fs_block.h"


/*
 *  Description:
 *      Inode structure stored in the FAT
 *
 */
typedef struct {
    u8      name[ISFS_INODE_NAMELEN];   /* 7.3 file name or dir name */
    u8      typeAcc;                    /* 6-bit access; 2-bit inode type */
    u8      attr;                       /* 8-bit file attribute */
    union attr1 {
        ISFSBlockEntry  block;          /* Address of first block in file */
        u16             child;          /* Inode # of first file in dir */
    } __attribute__((packed)) addr;
    u16     nextSibling;                /* Next inode in the same directory */
    u32     size;                       /* Size of file in bytes */
    IOSUid  owner;                      /* Owner ID for this inode */
    IOSGid  group;                      /* Group ID for this inode */
    u32     version;                    /* File version */
} __attribute__((packed)) ISFSInodeEntry;

/* Top 4 bits of the type field is used for access or file attribute */ 
#define ISFS_INODE_TYPE_MASK    0x3
#define ISFS_INODE_TYPE_INVALID 0       /* Un-initialized */
#define ISFS_INODE_TYPE_FILE    1       /* Inode is a file */
#define ISFS_INODE_TYPE_DIR     2       /* Inode is a directory */

#define ISFS_INODE_TYPE_ISFILE(typeAcc)                                       \
    ((typeAcc & ISFS_INODE_TYPE_MASK) == ISFS_INODE_TYPE_FILE)
#define ISFS_INODE_TYPE_ISDIR(typeAcc)                                        \
    ((typeAcc & ISFS_INODE_TYPE_MASK) == ISFS_INODE_TYPE_DIR)
#define ISFS_INODE_TYPE_ISINVALID(typeAcc)                                    \
    ((typeAcc & ISFS_INODE_TYPE_MASK) == ISFS_INODE_TYPE_INVALID)

/* Mask and shift for access control field */
#define ISFS_INODE_OTHERS_ACCESS_SHIFT  2
#define ISFS_INODE_OTHERS_ACCESS_MASK   0x0c
#define ISFS_INODE_GROUP_ACCESS_SHIFT   4
#define ISFS_INODE_GROUP_ACCESS_MASK    0x30
#define ISFS_INODE_OWNER_ACCESS_SHIFT   6
#define ISFS_INODE_OWNER_ACCESS_MASK    0xc0


/*
 *  Description:
 *      FAT structures, constants, and macros
 *
 */
typedef struct {
    u32         saSz;       /* Size of System Area */
    u32         dataSz;     /* Size of Data region */
    u32         fatSzShift; /* Size of FAT region */
} ISFSFlashLayout;

typedef struct {
    u8          magic[4];   /* "SFFS" */
    u32         seq;        /* Highest number is current */
    u32         gVersion;   /* Global version number */
    u8          arrays[0];  /* FS block array, inode array, and padding */
} ISFSFat;

extern ISFSFlashLayout              __isfsFlashLayout;

/* The maximum FAT size affects the size of the BSS significantly */
#ifdef NET_CARD
#define ISFS_MAX_FAT_SIZE           (64 * 1024)
#else
#define ISFS_MAX_FAT_SIZE           (256 * 1024)
#endif

#define ISFS_FAT_COPIES             16
#define ISFS_FAT_COPIES_SHIFT       4
#define ISFS_FAT_BLOCK_SIZE                                             \
        (1 << (__isfsFlashLayout.fatSzShift - ISFS_FAT_COPIES_SHIFT))
#define ISFS_FAT_BLOCK_SIZE_SHIFT                                       \
        (__isfsFlashLayout.fatSzShift - ISFS_FAT_COPIES_SHIFT)
#define ISFS_FAT_SIZE_IN_BLOCKS                                         \
        (1 << (ISFS_FAT_BLOCK_SIZE_SHIFT - ISFS_BLOCK_SIZE_SHIFT))

#define ISFS_FAT_BLOCK_ARRAY(fatp)      ((ISFSBlockEntry *)&(fatp)->arrays[0])

#define ISFS_BLOCK_AVAIL_CLEAN 0xFFFF      /* Available clean FS block */
#define ISFS_BLOCK_AVAIL_DIRTY 0xFFFE      /* Available dirty FS block */
#define ISFS_BLOCK_BAD         0xFFFD      /* Flash block is bad */
#define ISFS_BLOCK_RESERVED    0xFFFC      /* Reserved for SA for FAT */
#define ISFS_BLOCK_LAST        0xFFFB      /* Last FS block in file */
#define ISFS_BLOCK_VALID(bl)   (bl <= ISFS_BLOCK_LAST)  /* Data blocks */

/*
 * X = FAT block size = ISFS_FAT_BLOCK_SIZE
 * Y = Total space occupied by FS block entries = 2 * ISFS_BLOCK_ENTRIES
 * Z = Space occupied by other fields in FAT = 8
 * N = Max # of inodes = (X - Y - Z)/sizeof(inode)
 */
#define ISFS_INODE_ENTRIES  ((ISFS_FAT_BLOCK_SIZE -                         \
                                (sizeof (ISFSBlockEntry) *                  \
                                                    ISFS_BLOCK_ENTRIES) -   \
                                sizeof (ISFSFat)) /                         \
                            sizeof (ISFSInodeEntry))

#define ISFS_FAT_INODE_ARRAY(fatp)                                          \
        ((ISFSInodeEntry *)&(fatp)->arrays[sizeof (ISFSBlockEntry) *        \
                                        ISFS_BLOCK_ENTRIES])

#define ISFS_INODENUM_ROOT      0       /* Inode index for root directory */
#define ISFS_INODENUM_INVALID   0xFFFF  /* Invalid inode index */


/*
 *  Description:
 *      Mark all the FS blocks in the same flash block as bad
 *
 */
#define ISFS_MARK_FLASH_BLOCK(fatp, fsBlock, state)                         \
    do {                                                                    \
        u32     __firstBlock, __count;                                      \
                                                                            \
        __firstBlock = fsBlock & ~(ISFS_BLOCKS_IN_FL_BLOCK - 1);            \
        for (__count = 0; __count < ISFS_BLOCKS_IN_FL_BLOCK; __count++) {   \
            ISFS_FAT_BLOCK_ARRAY(fatp)[__firstBlock + __count] = state;     \
        }                                                                   \
    } while (0)


/*
 *  Description:
 *      Functions for loading and commiting a FAT
 *
 */
ISFSError   isfsInitFat(u32);
ISFSFat     *isfsLoadFat(void);
ISFSFat     *isfsResetFat(void);
ISFSError   isfsCommitFat(void);
void        isfsPrintFat(const ISFSFat *);


#endif /* __FS_FAT_H__ */
