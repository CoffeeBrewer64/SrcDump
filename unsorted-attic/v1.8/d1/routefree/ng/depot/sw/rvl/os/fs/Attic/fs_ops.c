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
#include <sc/sc.h>
#include <sc/iosc.h>
#include <sc/fs.h>
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <iop.h>
#ifndef ISFS_DISABLE_SECURITY
#include <iosc.h>
#endif
#include <fs.h>
#endif


#include "fs_utils.h"
#include "fs_block.h"
#include "fs_fat.h"
#include "fs_ops.h"


/* Tree operations */
#define ISFS_TREE_OP_CHECK_FD       1
#define ISFS_TREE_OP_REM_INODE      2
#define ISFS_TREE_OP_CHECK_INODE    3

/*
 * Maximum number of flash blocks freed by each garbage collection
 * operation. This is needed to limit the amount of time that
 * each garbage collection would take
 */
#define ISFS_MAX_CLEANED_FLBLOCKS   8

/*
 * Valid ASCII character for file/directory name
 */
#define ISFS_NAME_MIN_ASCII         0x20
#define ISFS_NAME_MAX_ASCII         0x7e

/*
 * The file I/O library will hide the 16KB alignment restriction
 * from the file system layer. However, the size field still may
 * not be 16KB-aligned since it is persistent and therefore needs
 * to be stored in the FAT
 */
#define ISFS_ALIGN_SIZE(sz)                                                 \
    (((sz) + ISFS_BLOCK_SIZE - 1) & ~(ISFS_BLOCK_SIZE - 1))


/* File system statistics */
static ISFSStats        __isfsStats;

/* File descriptor table */
static ISFSFdEntry      __isfsFdTable[ISFS_FD_ENTRIES];

/* Custom data for encryption and signature */
static ISFSCustomData   __isfsCustomData
                            __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));

#ifdef NAPA_WORKAROUND
#define ISFS_MAXFILES_INDIR     256
static u8               __isfsNameListBuf[ISFS_MAXFILES_INDIR *             \
                                    (ISFS_INODE_NAMELEN + 4)];
#endif


static u32              __isfsVerifyFullPathName(const u8 *);
static u32              __isfsGetNextAvailInodeNum(const ISFSFat *);
static ISFSError        __isfsGetParentDir(const u8 *, u8 *, u8 *);
static u32              __isfsGetInodeNumInDir(const ISFSFat *, u32,
                                            const u8 *);
static u32              __isfsGetInodeNum(const ISFSFat *, const u8 *);
static ISFSError        __isfsRemoveInodeFromParent(ISFSFat *, u32, u32);
static ISFSError        __isfsVerifyAccess(const ISFSFat *, u32, IOSUid,
                                            IOSGid, u32);
static ISFSError        __isfsCheckFdEntryForInode(u32);
static void             __isfsMoveFsBlockEntries(ISFSFat *,
                                            ISFSBlockEntry [][2], u32);
static ISFSBlockEntry   __isfsGetNextAvailFsBlock(ISFSFat *, u32 *);
static ISFSBlockEntry   __isfsGetNextReservedBlock(const ISFSFat *);
static ISFSError        __isfsApplyOpToTree(ISFSFat *, u32, u32);
static ISFSError        __isfsGarbageCollect(ISFSFat *);
static ISFSError        __isfsBlockReplacement(ISFSFat *, ISFSBlockEntry);
static ISFSError        __isfsGatherStats(const ISFSFat *);
static ISFSError        __isfsReserveSpace(ISFSFat *);
static ISFSError        __isfsCheck(ISFSFat *, u32 *);


/*
 *  Function: __isfsVerifyFullPathName
 *
 *  Description:
 *      Verify that the full path name is valid, the path '/'
 *      is rejected as invalid
 *
 *  Inputs:
 *      The full path name to be verified
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      Length if the name is valid, 0 otherwise
 *
 */
static u32
__isfsVerifyFullPathName(const u8 *name)
{
    u32     len = 0;

    if ((name == NULL) || (name[0] != '/') ||
            ((len = strnlen(name, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN) ||
            (len < 2) || (name[len - 1] == '/')) {
        len = 0;
    }

    return (len);
}


/*
 *  Function: __isfsGetNextAvailInodeNum
 *
 *  Description:
 *      Search the FAT to find the next available inode #
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      0 to ISFS_INODE_ENTRIES - Free inode number
 *      ISFS_INODENUM_INVALID - Not found or an error has occurred
 *
 */
static u32
__isfsGetNextAvailInodeNum(const ISFSFat *fatp)
{
    u32     iNum;

    ISFS_ENTRY();

    for (iNum = 0; iNum < ISFS_INODE_ENTRIES; iNum++) {
        if (ISFS_INODE_TYPE_ISINVALID(
                ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc)) {
            goto __isfsGetNextAvailInodeNum_out;
        }
    }

    iNum = ISFS_INODENUM_INVALID;
    isfsPrint(ISFS_DEBUG_WARN, "Ran out of free inode entries\n");

__isfsGetNextAvailInodeNum_out:

    ISFS_EXIT();

    return (iNum);
}


/*
 *  Function: __isfsGetParentDir
 *
 *  Description:
 *      Given the full path name of a file or directory, find the full path
 *      name of its parent directory
 *
 *  Inputs:
 *      name - The full path name of a file or directory
 *
 *  Outputs:
 *      parentDir - The full path name of the parent directory
 *      child - The relative name of the file or directory
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *
 */
static ISFSError
__isfsGetParentDir(const u8 *name, u8 *parentDir, u8 *child)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         count, len;

    ISFS_ENTRY();

    if (((len = __isfsVerifyFullPathName(name)) == 0) || (parentDir == NULL) ||
            (child == NULL)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto __isfsGetParentDir_out;
    }

    for (count = (len - 1); count > 0; count--) {
        if (name[count] == '/') {
            break;
        }
    }

    /* Length of the child's relative name can not exceed ISFS_INODE_NAMELEN */
    if ((len - count - 1) > ISFS_INODE_NAMELEN) {
        isfsPrint(ISFS_DEBUG_ERROR, "Child's relative name is too long\n");

        rc = ISFS_ERROR_INVALID;
        goto __isfsGetParentDir_out;
    }

    if (count == 0) {
        parentDir[0] = '/';
        parentDir[1] = '\0';
    } else {
        strncpy(parentDir, name, count);
        parentDir[count] = '\0';
    }
    strncpy(child, name + count + 1, (len - count - 1));
    child[len - count - 1] = '\0';

__isfsGetParentDir_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *
 *  Function: __isfsGetInodeNumInDir
 *
 *  Description:
 *      Given name of a file or directory and the inode number of
 *      an "ancestor" directory, find its inode #
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      dirINum - The inode number of the parent directory
 *      name - The name of the file or directory
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      0 to ISFS_INODE_ENTRIES - Inode # of the directory or file
 *      ISFS_INODENUM_INVALID - Not found or an error has occurred
 *
 */
static u32
__isfsGetInodeNumInDir(const ISFSFat *fatp, u32 dirINum, const u8 *name)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         iNum = dirINum;
    u32         count, len;
    u8          simpleName[ISFS_INODE_NAMELEN+1];
    u8          *ptr = &simpleName[0];

    ISFS_ENTRY();

    len = strnlen(name, ISFS_PATH_MAXLEN);
    for (count = 0; count <= len; count++) {
        /* Find the next level of directory or file in the name */
        if ((name[count] != '/') && (name[count] != '\0')) {
            ptr[0] = name[count];
            ptr++;

            continue;
        } else {
            ptr[0] = '\0';
            ptr = &simpleName[0];
        }

        /* Search for the formatted name */
        iNum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.child;
        while (iNum != ISFS_INODENUM_INVALID) {
            if (strncmp(ISFS_FAT_INODE_ARRAY(fatp)[iNum].name, ptr,
                    ISFS_INODE_NAMELEN) == 0) {
                /* Found a match */
                break;
            }

            iNum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].nextSibling;
        }

        /* Not found */
        if (iNum == ISFS_INODENUM_INVALID) {
            rc = ISFS_ERROR_INVALID;
            goto __isfsGetInodeNumInDir_out;
        }
    }

__isfsGetInodeNumInDir_out:

    if (rc != ISFS_ERROR_OK) {
        iNum = ISFS_INODENUM_INVALID;
    }

    ISFS_EXIT();

    return (iNum);
}


/*
 *  Function: __isfsGetInodeNum
 *
 *  Description:
 *      Given the full path name of a file or directory, find its inode #
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      name - The full path name of a file or directory
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      0 to ISFS_INODE_ENTRIES - Inode # of the directory or file
 *      ISFS_INODENUM_INVALID - Not found or an error has occurred
 *
 */
static u32
__isfsGetInodeNum(const ISFSFat *fatp, const u8 *name)
{
    u32     rc = ISFS_INODENUM_INVALID;

    ISFS_ENTRY();

    if (name[1] == '\0') {
        rc = ISFS_INODENUM_ROOT;
        goto __isfsGetInodeNum_out;
    }

    rc = __isfsGetInodeNumInDir(fatp, ISFS_INODENUM_ROOT, name + 1);

__isfsGetInodeNum_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsRemoveInodeFromParent
 *
 *  Description:
 *      Given the parent's inode number, search and delete the
 *      child inode specified
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      parentINum - The inode # of the parent directory
 *      iNum - The inode # of the child to be deleted
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful operation
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOEXISTS - Child inode not found
 *
 */
static ISFSError
__isfsRemoveInodeFromParent(ISFSFat *fatp, u32 parentINum, u32 iNum)
{
    ISFSError   rc = ISFS_ERROR_OK;

    ISFS_ENTRY();

    if (ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child == iNum) {
        ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child =
                                ISFS_FAT_INODE_ARRAY(fatp)[iNum].nextSibling;
    } else {
        u32     curInodeNum, found = 0;

        curInodeNum = ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child;
        while (curInodeNum != ISFS_INODENUM_INVALID) {
            if (iNum == ISFS_FAT_INODE_ARRAY(fatp)[curInodeNum].nextSibling) {
                ISFS_FAT_INODE_ARRAY(fatp)[curInodeNum].nextSibling =
                                ISFS_FAT_INODE_ARRAY(fatp)[iNum].nextSibling;

                found = 1;
                break;
            }

            curInodeNum = ISFS_FAT_INODE_ARRAY(fatp)[curInodeNum].nextSibling;
        }

        if (found == 0) {
            isfsPrint(ISFS_DEBUG_ERROR, "Can not find child %d in parent %d\n",
                                iNum, parentINum);

            rc = ISFS_ERROR_NOEXISTS;
            goto __isfsRemoveInodeFromParent_out;
        }
    }

    ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc = ISFS_INODE_TYPE_INVALID;

__isfsRemoveInodeFromParent_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsVerifyAccess
 *
 *  Description:
 *      Given the inode number of a directory, verify the specified
 *      caller ID has the requested access rights
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      inodeNum - Inode to be checked
 *      owner - Caller ID
 *      group - Group ID
 *      access - Requested access rights
 *      
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Access is granted
 *      ISFS_ERROR_ACCESS - Access violation
 *
 */
static ISFSError
__isfsVerifyAccess(const ISFSFat *fatp, u32 inodeNum, IOSUid owner,
            IOSGid group, u32 access)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         perm;

    ISFS_ENTRY();

    /* Root has all access */
    if (owner == IOS_ROOT_ID) {
        goto __isfsVerifyAccess_out;
    }

    perm = ISFS_FAT_INODE_ARRAY(fatp)[inodeNum].typeAcc;

    if (ISFS_FAT_INODE_ARRAY(fatp)[inodeNum].owner == owner) {
        perm = (perm & ISFS_INODE_OWNER_ACCESS_MASK) >>
                    ISFS_INODE_OWNER_ACCESS_SHIFT;
    } else if (ISFS_FAT_INODE_ARRAY(fatp)[inodeNum].group == group) {
        perm = (perm & ISFS_INODE_GROUP_ACCESS_MASK) >>
                    ISFS_INODE_GROUP_ACCESS_SHIFT;
    } else {
        perm = (perm & ISFS_INODE_OTHERS_ACCESS_MASK) >>
                    ISFS_INODE_OTHERS_ACCESS_SHIFT;
    }

    if ((access & perm) != access) {
        rc = ISFS_ERROR_ACCESS;
    }

__isfsVerifyAccess_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsCheckFdEntryForInode
 *
 *  Description:
 *      Search the file descriptor table to find entries that
 *      belong to the specified inode
 *
 *  Inputs:
 *      inodeNum - The inode number to be matched
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - No matching fd entry found
 *      ISFS_ERROR_OPENFD - Matching fd entry found
 *
 */
static ISFSError
__isfsCheckFdEntryForInode(u32 inodeNum)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         count;

    ISFS_ENTRY();

    for (count = 0; count < ISFS_FD_ENTRIES; count++) {
        if (__isfsFdTable[count].inUse == 0) {
            continue;
        }

        if (__isfsFdTable[count].inodeNum == inodeNum) {
            rc = ISFS_ERROR_OPENFD;
            goto __isfsCheckFdEntryForInode_out;
        }
    }

__isfsCheckFdEntryForInode_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsMoveFsBlockEntries
 *
 *  Description:
 *      Search for the old FS block entries and replace them
 *      with the new FS block entries
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      moved - A 2-dimensional array with the old and new entries
 *      num - Number of entries in the array
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      None
 *
 */
static void
__isfsMoveFsBlockEntries(ISFSFat *fatp, ISFSBlockEntry moved[][2], u32 num)
{
    u32     saInFsBlocks, dataInFsBlocks, count, movedCount;

    ISFS_ENTRY();

    saInFsBlocks = (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT);
    dataInFsBlocks = (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT);

    /* Check the FS block entries */
    for (count = saInFsBlocks; count < (saInFsBlocks + dataInFsBlocks);
            count++) {
        if (!ISFS_BLOCK_VALID(ISFS_FAT_BLOCK_ARRAY(fatp)[count])) {
            continue;
        }

        for (movedCount = 0; movedCount < num; movedCount++) {
            if (ISFS_FAT_BLOCK_ARRAY(fatp)[count] == moved[movedCount][0]) {
                ISFS_FAT_BLOCK_ARRAY(fatp)[count] = moved[movedCount][1];
                break;
            }
        }
    }

    /* Check the inode entries */
    for (count = 0; count < ISFS_INODE_ENTRIES; count++) {
        if (!ISFS_INODE_TYPE_ISFILE(
                ISFS_FAT_INODE_ARRAY(fatp)[count].typeAcc)) {
            continue;
        }

        for (movedCount = 0; movedCount < num; movedCount++) {
            if (ISFS_FAT_INODE_ARRAY(fatp)[count].addr.block ==
                                                        moved[movedCount][0]) {
                ISFS_FAT_INODE_ARRAY(fatp)[count].addr.block =
                                                        moved[movedCount][1];
                break;
            }
        }
    }

    ISFS_EXIT();
}


/*
 *  Function: __isfsGetNextAvailFsBlock
 *
 *  Description:
 *      Return the next available FS block. The algorithm
 *      will cycle through the entire flash. If a completely
 *      free but dirty flash block is available, the flash
 *      block will be cleaned and the first FS block will be
 *      returned
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      garbageCollected - 1 if garbage collection was triggered; 0 otherwise
 *
 *  Return values:
 *      ISFSBlockEntry - FS block number
 *      ISFS_BLOCK_BAD - No more free FS blocks
 *
 */
static ISFSBlockEntry
__isfsGetNextAvailFsBlock(ISFSFat *fatp, u32 *garbageCollected)
{
    static ISFSBlockEntry   offsetBlock;
    static u32              initialized = 0;
    ISFSError               rc = ISFS_ERROR_OK;
    u32                     count, tries = 1;
    u32                     saInFsBlocks, dataInFsBlocks;
    ISFSBlockEntry          fsBlock = ISFS_BLOCK_BAD;

    ISFS_ENTRY();

    *garbageCollected = 0;
    saInFsBlocks = (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT);
    dataInFsBlocks = (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT);

    /* Start the search from any block, and search the flash in loop */
    if (!initialized) {
        u32     offsetBlockInBytes = 0;

        /*
         * Use the FAT sequence number to determine where to
         * start. The purpose is to distribute the load to
         * different parts of the flash
         */
        offsetBlockInBytes = fatp->seq * ISFS_BLOCK_SIZE * 64;

        /* Should not exceed the size of flash */
        offsetBlockInBytes &= (__isfsFlashLayout.saSz +
                                __isfsFlashLayout.dataSz +
                                (1 << __isfsFlashLayout.fatSzShift) - 1);

        /* Should be in the data section */
        if (offsetBlockInBytes >=
                (__isfsFlashLayout.saSz + __isfsFlashLayout.dataSz)) {
            offsetBlockInBytes -= (1 << __isfsFlashLayout.fatSzShift);
        } else if (offsetBlockInBytes < __isfsFlashLayout.saSz) {
            offsetBlockInBytes += __isfsFlashLayout.saSz;
        }

        /* Change to FS block */
        offsetBlock = (offsetBlockInBytes >> ISFS_BLOCK_SIZE_SHIFT);

        /* Align on flash block boundary */
        offsetBlock &= (ISFS_BLOCKS_IN_FL_BLOCK - 1);

        initialized = 1;
    }

__isfsGetNextAvailFsBlock_tryagain:

    /* Examine one flash block at a time */
    for (count = 0; count < dataInFsBlocks; count += ISFS_BLOCKS_IN_FL_BLOCK) {
        u32             blCount = 0;
        ISFSBlockEntry  cleanBlock = ISFS_BLOCK_BAD, realBlock = ISFS_BLOCK_BAD;
        u32             usable = 1;

        realBlock = offsetBlock + count;
        if (realBlock >= (saInFsBlocks + dataInFsBlocks)) {
            realBlock -= dataInFsBlocks;
        }

        /* Can clean the flash block if all FS blocks are available */
        for (blCount = 0; blCount < ISFS_BLOCKS_IN_FL_BLOCK; blCount++) {
            if (ISFS_FAT_BLOCK_ARRAY(fatp)[realBlock + blCount] ==
                                                    ISFS_BLOCK_AVAIL_CLEAN) {
                /*
                 * In the case that this block can not be used, choose the
                 * next clean block
                 */
                if (cleanBlock == ISFS_BLOCK_BAD) {
                    cleanBlock = realBlock + blCount;
                }
            } else if (ISFS_FAT_BLOCK_ARRAY(fatp)[realBlock + blCount] !=
                                                    ISFS_BLOCK_AVAIL_DIRTY) {
                usable = 0;
            }
        }

        if (usable) {
            /*
             * Write to the first FS block will clean the whole
             * flash block. Furthermore, the whole flash block
             * being available dirty is logically the same as the
             * the flash block being available clean
             */
            for (blCount = 0; blCount < ISFS_BLOCKS_IN_FL_BLOCK; blCount++) {
                ISFS_FAT_BLOCK_ARRAY(fatp)[realBlock + blCount] =
                                                        ISFS_BLOCK_AVAIL_CLEAN;
            }

            offsetBlock = realBlock;
            fsBlock = realBlock;
            break;
        }
        if (cleanBlock != ISFS_BLOCK_BAD) {
            offsetBlock = realBlock;
            fsBlock = cleanBlock;
            break;
        }
    }

    if ((fsBlock == ISFS_BLOCK_BAD) && (tries-- > 0)) {
        rc = __isfsGarbageCollect(fatp);
        if (rc != ISFS_ERROR_OK) {
            if (rc != ISFS_ERROR_NOEXISTS) {
                isfsPrint(ISFS_DEBUG_ERROR, "Garbage collection failed,"
                                    " rc=%d\n", rc);

                *garbageCollected = 1;  /* Changes may have been made */
            }

            goto __isfsGetNextAvailFsBlock_out;
        }

        *garbageCollected = 1;
        goto __isfsGetNextAvailFsBlock_tryagain;
    }

__isfsGetNextAvailFsBlock_out:

    ISFS_EXIT();

    return (fsBlock);
}


/*
 *  Function: __isfsGetNextReservedBlock
 *
 *  Description:
 *      Return the next reserved block
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFSBlockEntry - FS block number
 *      ISFS_BLOCK_BAD - No more reserved FS blocks
 *
 */
static ISFSBlockEntry
__isfsGetNextReservedBlock(const ISFSFat *fatp)
{
    ISFSBlockEntry  reservedBlock = ISFS_BLOCK_BAD, count;
    u32             saInFsBlocks, dataInFsBlocks;

    ISFS_ENTRY();

    if (fatp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameter\n");
        goto __isfsGetNextReservedBlock_out;
    }

    saInFsBlocks = (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT);
    dataInFsBlocks = (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT);

    /* Look for reserved flash block */
    for (count = saInFsBlocks; count < (saInFsBlocks + dataInFsBlocks);
            count += ISFS_BLOCKS_IN_FL_BLOCK) {
        if (ISFS_FAT_BLOCK_ARRAY(fatp)[count] == ISFS_BLOCK_RESERVED) {
            reservedBlock = count;
            break;
        }
    }

__isfsGetNextReservedBlock_out:

    ISFS_EXIT();

    return (reservedBlock);
}


/*
 *  Function: __isfsApplyOpToTree
 *
 *  Description:
 *      This function applies an operation to every node in the
 *      tree specified. This is a recursive function
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      root - The root inode
 *      op - The operation to be applied
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_OPENFD - Open file descriptor exists
 *
 */
static ISFSError
__isfsApplyOpToTree(ISFSFat *fatp, u32 root, u32 op)
{
    ISFSError       rc = ISFS_ERROR_OK;
    u32             curNode, count, block, nextBlock;

    ISFS_ENTRY();

    curNode = ISFS_FAT_INODE_ARRAY(fatp)[root].addr.child;
    while (curNode != ISFS_INODENUM_INVALID) {
        /* Pre-ops */
        switch (op) {
            case (ISFS_TREE_OP_CHECK_FD):
                /* This operation only applies to files */
                if (!ISFS_INODE_TYPE_ISFILE(
                        ISFS_FAT_INODE_ARRAY(fatp)[curNode].typeAcc)) {
                    break;
                }

                for (count = 0; count < ISFS_FD_ENTRIES; count++) {
                    if ((__isfsFdTable[count].inUse == 1) &&
                            (__isfsFdTable[count].inodeNum == curNode)) {
                        rc = ISFS_ERROR_OPENFD;
                        goto __isfsApplyOpToTree_out;
                    }
                }

                break;

            case (ISFS_TREE_OP_REM_INODE):
                break;

            case (ISFS_TREE_OP_CHECK_INODE):
                /* Set the MSB of the size field */
                ISFS_FAT_INODE_ARRAY(fatp)[curNode].size |= 0x80000000;

                break;

            default:
                isfsPrint(ISFS_DEBUG_ERROR, "Invalid tree op %d\n", op);

                rc = ISFS_ERROR_INVALID;
                goto __isfsApplyOpToTree_out;
        }

        if (ISFS_INODE_TYPE_ISDIR(
                ISFS_FAT_INODE_ARRAY(fatp)[curNode].typeAcc)) {
            rc = __isfsApplyOpToTree(fatp, curNode, op);
            if (rc != ISFS_ERROR_OK) {
                goto __isfsApplyOpToTree_out;
            }
        }

        /* Post-ops */
        switch (op) {
            case (ISFS_TREE_OP_CHECK_FD):
                break;

            case (ISFS_TREE_OP_REM_INODE):
                if (ISFS_INODE_TYPE_ISFILE(
                        ISFS_FAT_INODE_ARRAY(fatp)[curNode].typeAcc)) {
                    /* Delete all of its FS blocks */
                    block = ISFS_FAT_INODE_ARRAY(fatp)[curNode].addr.block;
                    while (block != ISFS_BLOCK_LAST) {
                        nextBlock = ISFS_FAT_BLOCK_ARRAY(fatp)[block];
                        ISFS_FAT_BLOCK_ARRAY(fatp)[block] =
                                                    ISFS_BLOCK_AVAIL_DIRTY;
                        block = nextBlock;

                        __isfsStats.freeBlocks++;
                        __isfsStats.occupiedBlocks--;
                    }
                }

                /* Remove the inode, nextSibling is still valid */
                ISFS_FAT_INODE_ARRAY(fatp)[curNode].typeAcc =
                                                    ISFS_INODE_TYPE_INVALID;

                __isfsStats.freeInodes++;
                __isfsStats.occupiedInodes--;

                break;

            case (ISFS_TREE_OP_CHECK_INODE):
                break;

            default:
                isfsPrint(ISFS_DEBUG_ERROR, "Invalid tree op %d\n", op);

                rc = ISFS_ERROR_INVALID;
                goto __isfsApplyOpToTree_out;
        }

        curNode = ISFS_FAT_INODE_ARRAY(fatp)[curNode].nextSibling;
    }

__isfsApplyOpToTree_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsGarbageCollect
 *
 *  Description:
 *      This function groups individual FS blocks into physical flash
 *      blocks to free up more flash space that can be erased and
 *      re-used
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful and additional space is freed
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_NOEXISTS - No additional space is freed up
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
static ISFSError
__isfsGarbageCollect(ISFSFat *fatp)
{
    ISFSError       rc = ISFS_ERROR_OK;
    u32             saInFsBlocks, dataInFsBlocks;
    u32             count, blCount;
    u32             movedCount = 0, cleanedCount = 0;
    ISFSBlockEntry  state;
    ISFSBlockEntry  reservedBlock, replaceBlock;
    ISFSBlockEntry  moved[ISFS_BLOCKS_IN_FL_BLOCK][2];

    ISFS_ENTRY();

    /* Can not free anything if flash block size is same as FS block size */
    if (ISFS_BLOCKS_IN_FL_BLOCK == 1) {
        rc = ISFS_ERROR_NOEXISTS;
        goto __isfsGarbageCollect_out;
    }

    saInFsBlocks = (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT);
    dataInFsBlocks = (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT);

__isfsGarbageCollect_tryagain:

    /* Find a reserved block for garbage collection */
    reservedBlock = __isfsGetNextReservedBlock(fatp);
    if (!ISFS_BLOCK_VALID(reservedBlock)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to find reserved block, rc=%d\n",
                            reservedBlock);

        rc = ISFS_ERROR_NOEXISTS;
        goto __isfsGarbageCollect_out;
    }
    ISFS_MARK_FLASH_BLOCK(fatp, reservedBlock, ISFS_BLOCK_AVAIL_DIRTY);
    replaceBlock = ISFS_BLOCK_BAD;

    /* Examine one flash block at a time */
    for (count = 0; count < (saInFsBlocks + dataInFsBlocks);
            count += ISFS_BLOCKS_IN_FL_BLOCK) {
        u32     cleanable = 0, found_dirty = 0;

        /*
         * Do garbage collection if there are un-usable FS blocks
         * within a flash block. The algorithm is if there are
         * available FS blocks (must be dirty) before an occupied
         * FS block, then this flash block can be cleaned
         */
        for (blCount = 0; blCount < ISFS_BLOCKS_IN_FL_BLOCK; blCount++) {
            state = ISFS_FAT_BLOCK_ARRAY(fatp)[count + blCount];

            if (state == ISFS_BLOCK_RESERVED) {
                /* Not cleanable if the flash block is reserved */
                break;
            } else if (state == ISFS_BLOCK_BAD) {
                /* Not cleanable if the flash block is bad */
                break;
            } else if (state == ISFS_BLOCK_AVAIL_CLEAN) {
                /* All blocks after this one must also be clean */
                break;
            } else if (state == ISFS_BLOCK_AVAIL_DIRTY) {
                found_dirty = 1;
                continue;
            } else {    /* FS data block currently in use */
                if (found_dirty) {
                    cleanable = 1;
                    break;
                }
            }
        }

        if (!cleanable) {
            continue;
        }

        for (blCount = 0; blCount < ISFS_BLOCKS_IN_FL_BLOCK; blCount++) {
            state = ISFS_FAT_BLOCK_ARRAY(fatp)[count + blCount];

            /* The block needs to be copied if it's occupied */
            if (ISFS_BLOCK_VALID(state)) {
                if (movedCount == ISFS_BLOCKS_IN_FL_BLOCK) {
                    /*
                     * Commit the move by changing other FS blocks pointing
                     * to the moved blocks
                     */
                    __isfsMoveFsBlockEntries(fatp, moved, movedCount);

                    /* Use replacement block for copying */
                    reservedBlock = replaceBlock;
                    replaceBlock = ISFS_BLOCK_BAD;

                    movedCount = 0;
                }

                rc = isfsCopyFsBlocks(count + blCount,
                                reservedBlock + movedCount, 1);
                if (rc != ISFS_ERROR_OK) {
                    u32     recovCount;

                    if (rc != ISFS_ERROR_BADBLOCK) {
                        isfsPrint(ISFS_DEBUG_WARN, "Failed to copy FS blocks"
                                        " during garbage collection for"
                                        " block %d, rc=%d\n",
                                        count + blCount, rc);
                    }

                    /* Assume the reserved block is bad for some reason */
                    ISFS_MARK_FLASH_BLOCK(fatp, reservedBlock, ISFS_BLOCK_BAD);
                    __isfsStats.reservedBlocks -= ISFS_BLOCKS_IN_FL_BLOCK;
                    __isfsStats.badBlocks += ISFS_BLOCKS_IN_FL_BLOCK;

                    /* Revive FS blocks in the moved queue */
                    for (recovCount = 0; recovCount < movedCount;
                            recovCount++) {
                        ISFS_FAT_BLOCK_ARRAY(fatp)[moved[recovCount][0]] =
                            ISFS_FAT_BLOCK_ARRAY(fatp)[moved[recovCount][1]];
                    }

                    /* Recover from the error through reinit */
                    movedCount = 0;
                    rc = ISFS_ERROR_OK;
                    goto __isfsGarbageCollect_tryagain;
                }

                /* Copy the old block's link information */
                ISFS_FAT_BLOCK_ARRAY(fatp)[reservedBlock + movedCount] = state;
                moved[movedCount][0] = count + blCount;
                moved[movedCount][1] = reservedBlock + movedCount;

                movedCount++;
            }
        }

        /* The cleaned block is now marked as free-dirty */
        ISFS_MARK_FLASH_BLOCK(fatp, count, ISFS_BLOCK_AVAIL_DIRTY);

        /* The last completely cleaned block is used as reserve replacement */
        replaceBlock = count;

        if (++cleanedCount == ISFS_MAX_CLEANED_FLBLOCKS) {
            break;
        }
    }

    if (replaceBlock == ISFS_BLOCK_BAD) {
        /* This is only possible if nothing is cleaned */
        ISFS_MARK_FLASH_BLOCK(fatp, reservedBlock, ISFS_BLOCK_RESERVED);

        rc = ISFS_ERROR_NOEXISTS;
    } else {
        /* Commit the changes copied to the last block */
        if (movedCount > 0) {
            __isfsMoveFsBlockEntries(fatp, moved, movedCount);
        }

        ISFS_MARK_FLASH_BLOCK(fatp, replaceBlock, ISFS_BLOCK_RESERVED);
    }

__isfsGarbageCollect_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsBlockReplacement
 *
 *  Description:
 *      This function relocates the entire flash block where the specified
 *      FS block belongs
 *
 *  Inputs:
 *      fatp - The FAT structure
 *      fsBlockIndex - Index of the FS block to be relocated
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_MAXBLOCKS - Ran out of flash space
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
static ISFSError
__isfsBlockReplacement(ISFSFat *fatp, ISFSBlockEntry fsBlockIndex)
{
    ISFSError       rc = ISFS_ERROR_OK;
    ISFSBlockEntry  startBlock, newBlock;
    ISFSBlockEntry  replaced[ISFS_BLOCKS_IN_FL_BLOCK][2];
    u32             count, replacedCount = 0;

    ISFS_ENTRY();

    /* Get the first FS block in the flash block */
    startBlock = fsBlockIndex & ~(ISFS_BLOCKS_IN_FL_BLOCK - 1);

    /* Remember the blocks that need to be replaced */
    for (count = 0; count < ISFS_BLOCKS_IN_FL_BLOCK; count++) {
        if (ISFS_BLOCK_VALID(ISFS_FAT_BLOCK_ARRAY(fatp)[startBlock + count])) {
            replaced[replacedCount][0] = startBlock + count;
            replacedCount++;
        }
    }

__isfsBlockReplacement_tryagain:

    /* Find a reserved block for replacement */
    newBlock = __isfsGetNextReservedBlock(fatp);
    if (newBlock == ISFS_BLOCK_BAD) {
        isfsPrint(ISFS_DEBUG_WARN, "Failed to get free FS blocks\n");

        rc = ISFS_ERROR_MAXBLOCKS;
        goto __isfsBlockReplacement_out;
    }
    ISFS_MARK_FLASH_BLOCK(fatp, newBlock, ISFS_BLOCK_AVAIL_DIRTY);
    __isfsStats.reservedBlocks -= ISFS_BLOCKS_IN_FL_BLOCK;

    if (replacedCount == 0) {
        /* Do not need to replace any FS blocks */
        goto __isfsBlockReplacement_out;
    }

    /* Copy the replaced blocks */
    for (count = 0; count < replacedCount; count++) {
        rc = isfsCopyFsBlocks(replaced[count][0], newBlock + count, 1);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Double write error, rc=%d\n", rc);

            /* Assume this block is bad */
            ISFS_MARK_FLASH_BLOCK(fatp, newBlock, ISFS_BLOCK_BAD);
            __isfsStats.badBlocks += ISFS_BLOCKS_IN_FL_BLOCK;

            rc = ISFS_ERROR_OK;
            goto __isfsBlockReplacement_tryagain;
        }

        ISFS_FAT_BLOCK_ARRAY(fatp)[(newBlock + count)] =
                            ISFS_FAT_BLOCK_ARRAY(fatp)[replaced[count][0]];
        replaced[count][1] = newBlock + count;
    }

    /* Adjust the FS block entries to point to the new location */
    __isfsMoveFsBlockEntries(fatp, replaced, replacedCount);

__isfsBlockReplacement_out:

    if (rc == ISFS_ERROR_OK) {
        /* Mark the bad block if it's successfully replaced */
        ISFS_MARK_FLASH_BLOCK(fatp, startBlock, ISFS_BLOCK_BAD);
        __isfsStats.badBlocks += ISFS_BLOCKS_IN_FL_BLOCK;
    }

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: __isfsGatherStats
 *
 *  Description:
 *      Gather file system statistics
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful completion
 *      ISFS_ERROR_INVALID - Invalid parameters
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
static ISFSError
__isfsGatherStats(const ISFSFat *fatp)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         count, saInFsBlocks, dataInFsBlocks;

    __isfsStats.blockSize = ISFS_BLOCK_SIZE;
    __isfsStats.freeBlocks = 0;
    __isfsStats.occupiedBlocks = 0;
    __isfsStats.badBlocks = 0;
    __isfsStats.reservedBlocks = 0;
    __isfsStats.freeInodes = 0;
    __isfsStats.occupiedInodes = 0;

    saInFsBlocks = (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT);
    dataInFsBlocks = (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT);

    /* Count the FS blocks */
    for (count = saInFsBlocks; count < (saInFsBlocks + dataInFsBlocks);
            count++) {
        ISFSBlockEntry  state = ISFS_FAT_BLOCK_ARRAY(fatp)[count];

        switch (state) {
        case ISFS_BLOCK_AVAIL_CLEAN:
            __isfsStats.freeBlocks++;
            break;

        case ISFS_BLOCK_AVAIL_DIRTY:
            __isfsStats.freeBlocks++;
            break;

        case ISFS_BLOCK_BAD:
            __isfsStats.badBlocks++;
            break;

        case ISFS_BLOCK_RESERVED:
            __isfsStats.reservedBlocks++;
            break;

        default:    /* Data blocks */
            __isfsStats.occupiedBlocks++;
            break;
        }
    }

    /* Count the inodes */
    for (count = 0; count < ISFS_INODE_ENTRIES; count++) {
        if (ISFS_INODE_TYPE_ISINVALID(
                ISFS_FAT_INODE_ARRAY(fatp)[count].typeAcc)) {
            __isfsStats.freeInodes++;
        } else {
            __isfsStats.occupiedInodes++;
        }
    }

    return (rc);
}


/*
 *  Function: __isfsReserveSpace
 *
 *  Description:
 *      Set aside some flash space for bad block replacement. This
 *      function assumes that the file system is completely clean
 *      (i.e. other than bad blocks, all other blocks are free).
 *      It also assumes that the file system statistics is valid
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Successful completion
 *      ISFS_ERROR_INVALID - Invalid parameters
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
static ISFSError
__isfsReserveSpace(ISFSFat *fatp)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         count, saInFsBlocks, dataInFsBlocks, fatInFsBlocks;
    u32         reserved, maxReserve;

    saInFsBlocks = (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT);
    dataInFsBlocks = (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT);
    fatInFsBlocks = (1 << (__isfsFlashLayout.fatSzShift -
                            ISFS_BLOCK_SIZE_SHIFT));

    /* Reserve 1MB for every 64MB of flash space */
    maxReserve = (saInFsBlocks + dataInFsBlocks + fatInFsBlocks) >>
                (6 + ISFS_BLOCKS_IN_FL_BLOCK_SHIFT);

    reserved = __isfsStats.badBlocks >> ISFS_BLOCKS_IN_FL_BLOCK_SHIFT;
    if (reserved >= maxReserve) {
        isfsPrint(ISFS_DEBUG_ERROR, "Too many bad blocks\n");
        goto __isfsReserveSpace_out;
    }

    /* Reserve flash blocks */
    for (count = saInFsBlocks; count < (saInFsBlocks + dataInFsBlocks);
            count += (ISFS_BLOCKS_IN_FL_BLOCK)) {
        if (ISFS_FAT_BLOCK_ARRAY(fatp)[count] == ISFS_BLOCK_BAD) {
            continue;
        } else {
            /* All non-bad blocks can be reserved */
            ISFS_MARK_FLASH_BLOCK(fatp, count, ISFS_BLOCK_RESERVED);
            reserved++;
        }

        if (reserved >= maxReserve) {
            break;
        }
    }

    __isfsStats.reservedBlocks = reserved -
                    (__isfsStats.badBlocks >> ISFS_BLOCKS_IN_FL_BLOCK_SHIFT);

__isfsReserveSpace_out:

    return (rc);
}


/*
 *  Function: __isfsCheck
 *
 *  Description:
 *      This function checks the integrity of the FAT structure and repairs
 *      it if necessary
 *
 *  Inputs:
 *      fatp - The current valid FAT structure
 *
 *  Outputs:
 *      modified - 1 if the FAT structure is modified, 0 otherwise
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 */
static ISFSError
__isfsCheck(ISFSFat *fatp, u32 *modified)
{
    ISFSError       rc = ISFS_ERROR_OK;
    u32             count;
    ISFSBlockEntry  block;

    ISFS_ENTRY();

    *modified = 0;

    /*
     * More checks can be added, such as checking for FS blocks
     * "in use" but not linked to any file inodes, file inodes
     * with inconsistent block list, ...etc. However, it doesn't
     * seem like any of these scenarios, including the one
     * actually implemented below, can realistically happen since
     * the FAT should always be in a consistent state when
     * committed to the flash
     */

    /*
     * Delete "dangling" inodes that can not be reached by root. The
     * algorithm is to traverse through the whole tree and mark the
     * MSB of each inode's size field. Then iterate through the inode
     * array to check for any inodes without the bit marked
     */
    rc = __isfsApplyOpToTree(fatp, 0, ISFS_TREE_OP_CHECK_INODE);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to check inode for directory tree"
                            " rc=%d\n", rc);
        goto __isfsCheck_out;
    }

    /* Skip the root node */
    for (count = 1; count < ISFS_INODE_ENTRIES; count++) {
        if (ISFS_INODE_TYPE_ISINVALID(
                ISFS_FAT_INODE_ARRAY(fatp)[count].typeAcc)) {
            continue;
        }

        if ((ISFS_FAT_INODE_ARRAY(fatp)[count].size & 0x80000000) == 0) {
            isfsPrint(ISFS_DEBUG_WARN, "Detected dangling inode entry %d\n",
                                count);

            /* Remove the inode */
            continue;
            *modified = 1;
            if (ISFS_INODE_TYPE_ISFILE(
                    ISFS_FAT_INODE_ARRAY(fatp)[count].typeAcc)) {
                ISFSBlockEntry  nextBlock = ISFS_BLOCK_BAD;

                block = ISFS_FAT_INODE_ARRAY(fatp)[count].addr.block;
                while (block != ISFS_BLOCK_LAST) {
                    nextBlock = ISFS_FAT_BLOCK_ARRAY(fatp)[block];
                    ISFS_FAT_BLOCK_ARRAY(fatp)[block] = ISFS_BLOCK_AVAIL_DIRTY;
                    block = nextBlock;
                }
            }

            ISFS_FAT_INODE_ARRAY(fatp)[count].typeAcc = ISFS_INODE_TYPE_INVALID;
        } else {
            ISFS_FAT_INODE_ARRAY(fatp)[count].size &= 0x7fffffff;
        }
    }

__isfsCheck_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsGetNextAvailFdEntry
 *
 *  Description:
 *      Search the file descriptor table to find the next free
 *      file descriptor entry
 *
 *  Inputs:
 *      owner - Owner ID
 *      group - Group ID
 *      inodeNum - The inode number where this fd points to
 *      access - The access permission of the fd
 *      size - Size of the opened file
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      0 to (ISFS_FD_ENTRIES - 1) - Fd descriptor number
 *      -1 - No more free entries
 *
 */
s32
isfsGetNextAvailFdEntry(IOSUid owner, IOSGid group, u32 inodeNum, u32 access,
                u32 size)
{
    s32             newFd = -1;
    u32             count;

    ISFS_ENTRY();

    for (count = 0; count < ISFS_FD_ENTRIES; count++) {
        if (__isfsFdTable[count].inUse == 0) {    /* Entry is available */
            __isfsFdTable[count].inUse = 1;
            __isfsFdTable[count].uid = owner;
            __isfsFdTable[count].gid = group;
            __isfsFdTable[count].inodeNum = inodeNum;
            __isfsFdTable[count].access = access;
            __isfsFdTable[count].offset = 0;
            __isfsFdTable[count].nOffset = 0;
            __isfsFdTable[count].size = size;
            __isfsFdTable[count].changed = 0;
            __isfsFdTable[count].error = ISFS_ERROR_OK;

            break;
        }
    }

    if (count != ISFS_FD_ENTRIES) {
        newFd = (s32) &__isfsFdTable[count];
    }

    ISFS_EXIT();

    return (newFd);
}


/*
 *  Function: isfsFormat
 *
 *  Description:
 *      This function formats the SC file system onto the flash device
 *
 *  Inputs:
 *      owner - ID for checking access control
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful 
 *      ISFS_ERROR_ACCESS - The caller does not have root access
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *      ISFS_ERROR_UNKNOWN - An unknown error has occurred
 *
 */
ISFSError
isfsFormat(IOSUid owner)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         count;

    ISFS_ENTRY();

    /* Verify the current context has root access */
    if (owner != IOS_ROOT_ID) {
        isfsPrint(ISFS_DEBUG_WARN, "A non-root application tried to"
                            " format the file system, owner=%d\n", owner);

        rc = ISFS_ERROR_ACCESS;
        goto isfsFormat_out;
    }

    /* Initialize the FS block module */
    rc = isfsInitFsBlocks(1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to initialize the FS block module,"
                            "rc=%d\n", rc);
        goto isfsFormat_out;
    }

    /* Initialize the FAT module */
    rc = isfsInitFat(1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to initialize the FAT module,"
                            "rc=%d\n", rc);
        goto isfsFormat_initFat_out;
    }

    /* Reset the FAT structure */
    fatp = isfsResetFat();
    if (fatp == NULL) {
        /* The FAT pointer should always point to something */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to reset FAT\n");
        goto isfsFormat_resetFat_out;
    }

    /* Add root directory with read permission for non-owners */
    ISFS_FAT_INODE_ARRAY(fatp)[0].typeAcc = ISFS_INODE_TYPE_DIR |
                        (ISFS_READ_ACCESS << ISFS_INODE_OTHERS_ACCESS_SHIFT);
    ISFS_FAT_INODE_ARRAY(fatp)[0].name[0] = '/';
    ISFS_FAT_INODE_ARRAY(fatp)[0].name[1] = '\0';
    ISFS_FAT_INODE_ARRAY(fatp)[0].attr = 0x0;
    ISFS_FAT_INODE_ARRAY(fatp)[0].addr.child = ISFS_INODENUM_INVALID;
    ISFS_FAT_INODE_ARRAY(fatp)[0].nextSibling = ISFS_INODENUM_INVALID;
    ISFS_FAT_INODE_ARRAY(fatp)[0].size = 0;
    ISFS_FAT_INODE_ARRAY(fatp)[0].owner = IOS_ROOT_ID;
    ISFS_FAT_INODE_ARRAY(fatp)[0].group = IOS_ROOT_GROUP;
    ISFS_FAT_INODE_ARRAY(fatp)[0].version = 0;

    /* Reset the file descriptor table */
    for (count = 0; count < ISFS_FD_ENTRIES; count++) {
        __isfsFdTable[count].inUse = 0;
    }

    /* Set up file system statistics */
    rc = __isfsGatherStats(fatp);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to reserve space, rc=%d\n", rc);
        goto isfsFormat_resetFat_out;
    }

    /* Reserve file system space */
    rc = __isfsReserveSpace(fatp);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to reserve space, rc=%d\n", rc);
        goto isfsFormat_resetFat_out;
    }

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsFormat_resetFat_out;
    }

    goto isfsFormat_out;

isfsFormat_resetFat_out:

    (void) isfsInitFat(0);

isfsFormat_initFat_out:

    (void) isfsInitFsBlocks(0);

isfsFormat_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsGetStats
 *
 *  Description:
 *      This function returns the file system statistics
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      stats - The file system statistics
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_UNKNOWN - An unknown error has occurred
 *
 */
ISFSError
isfsGetStats(ISFSStats *stats)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;

    ISFS_ENTRY();

    if (stats == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsGetStats_out;
    }

    /* Check to make sure the file system is already mounted */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");
        rc = ISFS_ERROR_NOTREADY;
        goto isfsGetStats_out;
    }

    *stats = __isfsStats;

isfsGetStats_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsCreateDir
 *
 *  Description:
 *      This function creates a directory in the specified path
 *
 *  Inputs:
 *      owner - User ID of the caller
 *      group - Group ID of the caller
 *      dirname - Full path name of the new directory
 *      dirAttr - Directory attributes
 *      ownerAcc - Owner's access right to this directory
 *      groupAcc - Group's access right to this directory
 *      othersAcc - Others' access right to this directory
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_NOEXISTS - The parent directory does not exist
 *      ISFS_ERROR_ACCESS - The caller has no write access to the parent dir
 *      ISFS_ERROR_EXISTS - The file or directory already exists
 *      ISFS_ERROR_MAXFILES - Ran out of inode entries
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsCreateDir(IOSUid owner, IOSGid group, const u8 *dirname, u32 dirAttr,
            u32 ownerAcc, u32 groupAcc, u32 othersAcc)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum, parentINum, len, count, depth;
    u8          parentDir[ISFS_PATH_MAXLEN], child[ISFS_INODE_NAMELEN+1];

    ISFS_ENTRY();

    /* Check input parameters */
    if ((len = __isfsVerifyFullPathName(dirname)) == 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid directory name\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsCreateDir_out;
    }

    /*
     * Check that the name contains only valid characters and
     * that the maximum tree depth is not exceeded
     */
    depth = 0;
    for (count = 0; count < len; count++) {
        if ((dirname[count] < ISFS_NAME_MIN_ASCII) ||
                (dirname[count] > ISFS_NAME_MAX_ASCII)) {
            isfsPrint(ISFS_DEBUG_WARN, "Invalid character %c\n",
                                    dirname[count]);
            rc = ISFS_ERROR_INVALID;
            goto isfsCreateDir_out;
        }

        if (dirname[count] == '/') {
            if (depth == ISFS_MAX_DIRTREE_DEPTH) {
                isfsPrint(ISFS_DEBUG_WARN, "Reached maximum directory tree"
                                    " depth\n");

                rc = ISFS_ERROR_MAXDEPTH;
                goto isfsCreateDir_out;
            }

            depth++;
        }
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsCreateDir_out;
    }

    /* Locate the name of the parent directory */
    rc = __isfsGetParentDir(dirname, &parentDir[0], &child[0]);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get parent directory name for"
                            " %s\n", dirname);
        goto isfsCreateDir_out;
    }

    /* Find the inode number of the parent directory */
    parentINum = __isfsGetInodeNum(fatp, &parentDir[0]);
    if (parentINum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                            &parentDir[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsCreateDir_out;
    }

    /* Verify write access to the parent directory */
    rc = __isfsVerifyAccess(fatp, parentINum, owner, group, ISFS_WRITE_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "No write access to the parent directory"
                            " %s\n", &parentDir[0]);
        goto isfsCreateDir_out;
    }

    /* Make sure no file or directory with the same name already exists */
    iNum = __isfsGetInodeNumInDir(fatp, parentINum, &child[0]);
    if (iNum != ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "The directory %s already exists\n",
                            dirname);

        rc = ISFS_ERROR_EXISTS;
        goto isfsCreateDir_out;
    }

    /* Insert a new child inode at the beginning of the directory file list */
    iNum = __isfsGetNextAvailInodeNum(fatp);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "No more available inode\n");

        rc = ISFS_ERROR_MAXFILES;
        goto isfsCreateDir_out;
    }

    /* Format the name of the new directory */
    strncpy(ISFS_FAT_INODE_ARRAY(fatp)[iNum].name, child, ISFS_INODE_NAMELEN);

    ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc =
                (ownerAcc << ISFS_INODE_OWNER_ACCESS_SHIFT) |
                (groupAcc << ISFS_INODE_GROUP_ACCESS_SHIFT) |
                (othersAcc << ISFS_INODE_OTHERS_ACCESS_SHIFT) |
                ISFS_INODE_TYPE_DIR;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].attr = dirAttr;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.child = ISFS_INODENUM_INVALID;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].nextSibling =
                            ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].size = 0;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner = owner;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].group = group;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].version = 0;

    ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child = iNum;

    __isfsStats.freeInodes--;
    __isfsStats.occupiedInodes++;

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        /* FAT is corrupted */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsCreateDir_out;
    }

isfsCreateDir_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsReadDir
 *
 *  Description:
 *      This function returns a list of files and directories.
 *      If "nameList" is NULL, then only the number of entries
 *      will be returned in "num"
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      group - Group ID for checking access control
 *      dirname - Full path name of the directory
 *
 *  Outputs:
 *      nameList - A list of the names
 *      num - Number of names
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The caller has no read access to the directory
 *      ISFS_ERROR_NOEXISTS - The directory does not exist
 *
 */
ISFSError
isfsReadDir(IOSUid owner, IOSGid group, const u8 *dirname, u8 *nameList,
        u32 *num)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum, childINum, count;
#ifdef NAPA_WORKAROUND
    u8          *ptr = __isfsNameListBuf;
#endif

    ISFS_ENTRY();

    /* Check input parameters */
    if ((dirname == NULL) || (dirname[0] != '/') || (num == NULL) ||
            (strnlen(dirname, ISFS_PATH_MAXLEN) == ISFS_PATH_MAXLEN)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");
        rc = ISFS_ERROR_INVALID;
        goto isfsReadDir_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");
        rc = ISFS_ERROR_NOTREADY;
        goto isfsReadDir_out;
    }

    /* Find the inode number of the directory */
    iNum = __isfsGetInodeNum(fatp, dirname);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                            dirname);
        rc = ISFS_ERROR_NOEXISTS;
        goto isfsReadDir_out;
    }

    /* Verify that the inode is a directory */
    if (!ISFS_INODE_TYPE_ISDIR(ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Specified name %s is not a dir", dirname);
        rc = ISFS_ERROR_INVALID;
        goto isfsReadDir_out;
    }

    /* Verify read access to the directory */
    rc = __isfsVerifyAccess(fatp, iNum, owner, group, ISFS_READ_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "No read access to the directory %s\n",
                            dirname);
        goto isfsReadDir_out;
    }

    /* Set num to the limit if nameList is NULL */
    if (nameList == NULL) {
        *num = ISFS_INODE_ENTRIES;
    }

    /* Copy the list of files or directories to nameList */
    childINum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.child;
    for (count = 0; count < *num; count++) {
        if (childINum == ISFS_INODENUM_INVALID) {
            *num = count;
            break;
        }

        if (nameList) {
#ifdef NAPA_WORKAROUND
            if (count > ISFS_MAXFILES_INDIR) {
                rc = ISFS_ERROR_INVALID;
                goto isfsReadDir_out;
            }

            strncpy(ptr, ISFS_FAT_INODE_ARRAY(fatp)[childINum].name,
                ISFS_INODE_NAMELEN);
            ptr[ISFS_INODE_NAMELEN] = '\0';

            while (ptr[0] != '\0') {
                ptr++;
            }
            ptr++;
#else
            strncpy(nameList, ISFS_FAT_INODE_ARRAY(fatp)[childINum].name,
                ISFS_INODE_NAMELEN);
            nameList[ISFS_INODE_NAMELEN] = '\0';

            while (nameList[0] != '\0') {
                nameList++;
            }
            nameList++;
#endif
        }

        childINum = ISFS_FAT_INODE_ARRAY(fatp)[childINum].nextSibling;
    }

#ifdef NAPA_WORKAROUND
    if (nameList) {
        u32     *srcPtr = (u32 *) __isfsNameListBuf;
        u32     *dstPtr = (u32 *) nameList, i;
        u32     num = (ISFS_MAXFILES_INDIR * (ISFS_INODE_NAMELEN + 4)) >> 2;

        for (i = 0; i < num; i++) {
            *dstPtr++ = *srcPtr++;
        }
    }
#endif

isfsReadDir_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsSetAttr
 *
 *  Description:
 *      This function sets the file or directory's attributes
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      name - Name of the file or directory
 *      ownerId - Owner ID of the file or directory
 *      groupId - Group ID of the file or directory
 *      attr - File or directory attributes
 *      ownerAcc - Owner's access right to this file or directory
 *      groupAcc - Group's access right to this file or directory
 *      othersAcc - Others' access right to this file or directory
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_NOEXISTS - The file or directory does not exist
 *      ISFS_ERROR_ACCESS - The caller is not the owner
 *
 */
ISFSError
isfsSetAttr(IOSUid owner, const u8 *name, IOSUid ownerId, IOSGid groupId,
        u32 attr, u32 ownerAcc, u32 groupAcc, u32 othersAcc)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum;

    ISFS_ENTRY();

    /* Check input parameters */
    if ((name == NULL) || (name[0] != '/') ||
            (strnlen(name, ISFS_PATH_MAXLEN) == ISFS_PATH_MAXLEN)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsSetAttr_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsSetAttr_out;
    }

    /* Find the inode number of the file or directory */
    iNum = __isfsGetInodeNum(fatp, name);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for"
                                " %s\n", name);
        rc = ISFS_ERROR_NOEXISTS;
        goto isfsSetAttr_out;
    }

    /* Only root or owner can change attributes */
    if ((owner != IOS_ROOT_ID) &&
            (owner != ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Caller ID 0x%x does not match the owner ID"
                    " 0x%x\n", owner, ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner);
        rc = ISFS_ERROR_ACCESS;
        goto isfsSetAttr_out;
    }

    if (ownerId != ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner) {
        /* Only root can change the owner ID */
        if (owner != IOS_ROOT_ID) {
            isfsPrint(ISFS_DEBUG_ERROR, "Only root can change the owner ID"
                                    " %x\n", owner);
            rc = ISFS_ERROR_ACCESS;
            goto isfsSetAttr_out;
        }

        /* Can not change the owner ID of a non-empty file */
        if (ISFS_INODE_TYPE_ISFILE(ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc) &&
                (ISFS_FAT_INODE_ARRAY(fatp)[iNum].size != 0)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Can not change the owner Id of a"
                                    " non-empty file\n",
                                    ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc,
                                    ISFS_FAT_INODE_ARRAY(fatp)[iNum].size);
            rc = ISFS_ERROR_NOTEMPTY;
            goto isfsSetAttr_out;
        }
    }

    /* Can not change the owner ID of a non-empty file */
    if (ownerId != ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner) {
    }

    /* Set the attributes in the inode */
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner = ownerId;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].group = groupId;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].attr = attr;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc =
            (ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc & ISFS_INODE_TYPE_MASK) |
            (ownerAcc << ISFS_INODE_OWNER_ACCESS_SHIFT) |
            (groupAcc << ISFS_INODE_GROUP_ACCESS_SHIFT) |
            (othersAcc << ISFS_INODE_OTHERS_ACCESS_SHIFT);

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        /* FAT is corrupted */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsSetAttr_out;
    }

isfsSetAttr_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsGetAttr
 *
 *  Description:
 *      This function retrieves the file or directory's attributes
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      group - ID for checking access control
 *      name - Name of the file or directory
 *
 *  Outputs:
 *      ownerId - Owner ID of the file or directory
 *      groupId - Group ID of the file or directory
 *      attr - File or directory attributes
 *      ownerAcc - Owner's access right to this file or directory
 *      groupAcc - Group's access right to this file or directory
 *      othersAcc - Others' access right to this file or directory
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_NOEXISTS - The file or directory does not exist
 *      ISFS_ERROR_ACCESS - No read access to the parent directory
 *
 */
ISFSError
isfsGetAttr(IOSUid owner, IOSGid group, const u8 *name, IOSUid *ownerId,
    IOSGid *groupId, u32 *attr, u32 *ownerAcc, u32 *groupAcc, u32 *othersAcc)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum, parentINum, len;
    u8          parentDir[ISFS_PATH_MAXLEN], child[ISFS_INODE_NAMELEN+1];

    ISFS_ENTRY();

    /* Check input parameters */
    if ((name == NULL) || (name[0] != '/') ||
            ((len = strnlen(name, ISFS_PATH_MAXLEN)) == ISFS_PATH_MAXLEN) ||
            (ownerId == NULL) || (groupId == NULL) || (attr == NULL) ||
            (ownerAcc == NULL) || (groupAcc == NULL) || (othersAcc == NULL)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsGetAttr_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsGetAttr_out;
    }

    if (len == 1) {
        /*
         * Allow everyone to get root's attributes
         */
        iNum = 0;
    } else {
        /* Locate the name of the parent directory */
        rc = __isfsGetParentDir(name, &parentDir[0], &child[0]);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to get parent directory name"
                                " for %s\n", name);
            goto isfsGetAttr_out;
        }

        /* Find the inode number of the parent directory */
        parentINum = __isfsGetInodeNum(fatp, &parentDir[0]);
        if (parentINum == ISFS_INODENUM_INVALID) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                                &parentDir[0]);

            rc = ISFS_ERROR_NOEXISTS;
            goto isfsGetAttr_out;
        }

        /* Verify read access to the parent directory */
        rc = __isfsVerifyAccess(fatp, parentINum, owner, group,
                            ISFS_READ_ACCESS);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "No read access to the parent directory"
                                " %s\n", &parentDir[0]);
            goto isfsGetAttr_out;
        }

        /* Find the inode number of the file or directory */
        iNum = __isfsGetInodeNumInDir(fatp, parentINum, &child[0]);
        if (iNum == ISFS_INODENUM_INVALID) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                                name);

            rc = ISFS_ERROR_NOEXISTS;
            goto isfsGetAttr_out;
        }
    }

    /* Retrieve the attributes from the inode */
    *ownerId = ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner;
#ifdef NAPA_WORKAROUND
    u32     word;

    word = ISFS_FAT_INODE_ARRAY(fatp)[iNum].group;
    word <<= 16;
    *((u32 *)groupId) = word;
#else
    *groupId = ISFS_FAT_INODE_ARRAY(fatp)[iNum].group;
#endif
    *attr = ISFS_FAT_INODE_ARRAY(fatp)[iNum].attr;
    *ownerAcc = (ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc &
            ISFS_INODE_OWNER_ACCESS_MASK) >> ISFS_INODE_OWNER_ACCESS_SHIFT;
    *groupAcc = (ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc &
            ISFS_INODE_GROUP_ACCESS_MASK) >> ISFS_INODE_GROUP_ACCESS_SHIFT;
    *othersAcc = (ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc &
            ISFS_INODE_OTHERS_ACCESS_MASK) >> ISFS_INODE_OTHERS_ACCESS_SHIFT;

isfsGetAttr_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsDelete
 *
 *  Description:
 *      This function deletes the specified file or directory
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      group - ID for checking access control
 *      name - Full path name of the file or directory
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The caller has no read access to the directory
 *      ISFS_ERROR_NOEXISTS - The file or directory does not exist
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsDelete(IOSUid owner, IOSGid group, const u8 *name)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum, parentINum, block, nextBlock;
    u32         garbageCollect = 0;
    u8          parentDir[ISFS_PATH_MAXLEN], child[ISFS_INODE_NAMELEN+1];

    ISFS_ENTRY();

    /* Check input parameters */
    if (!__isfsVerifyFullPathName(name)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid name\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsDelete_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsDelete_out;
    }

    /* Locate the name of the parent directory */
    rc = __isfsGetParentDir(name, &parentDir[0], &child[0]);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get parent directory name for"
                            " %s\n", name);

        rc = ISFS_ERROR_INVALID;
        goto isfsDelete_out;
    }

    /* Find the inode number of the parent directory */
    parentINum = __isfsGetInodeNum(fatp, &parentDir[0]);
    if (parentINum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                            &parentDir[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsDelete_out;
    }

    /* Verify write access to the parent directory */
    rc = __isfsVerifyAccess(fatp, parentINum, owner, group, ISFS_WRITE_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "No write access to the parent directory"
                            " %s\n", &parentDir[0]);
        goto isfsDelete_out;
    }

    /* Find the inode # of the file or directory to be deleted */
    iNum = __isfsGetInodeNumInDir(fatp, parentINum, &child[0]);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s"
                            " in directory %s\n", &child[0], &parentDir[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsDelete_out;
    }

    if (ISFS_INODE_TYPE_ISDIR(ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc)) {
        if (ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.child != ISFS_INODENUM_INVALID) {
            /* Check for open file descriptors */
            rc = __isfsApplyOpToTree(fatp, iNum, ISFS_TREE_OP_CHECK_FD);
            if (rc != ISFS_ERROR_OK) {
                goto isfsDelete_out;
            }

            /* Remove all inodes under this directory */
            rc = __isfsApplyOpToTree(fatp, iNum, ISFS_TREE_OP_REM_INODE);
            if (rc != ISFS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to apply tree operation to"
                                    " remove file descriptors, rc=%d\n", rc);
                goto isfsDelete_out;
            }

            /* Likely that garbage collection is needed */
            garbageCollect = 1;
        }
    } else {
        /* Check for open file descriptors */
        rc = __isfsCheckFdEntryForInode(iNum);
        if (rc != ISFS_ERROR_OK) {
            goto isfsDelete_out;
        }

        /* Delete all FS blocks that belong to this file */
        block = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block;
        while (block != ISFS_BLOCK_LAST) {
            nextBlock = ISFS_FAT_BLOCK_ARRAY(fatp)[block];
            ISFS_FAT_BLOCK_ARRAY(fatp)[block] = ISFS_BLOCK_AVAIL_DIRTY;
            block = nextBlock;

            __isfsStats.freeBlocks++;
            __isfsStats.occupiedBlocks--;

            garbageCollect = 1;
        }
    }

    /* Delete the inode from the parent directory's file list */
    rc = __isfsRemoveInodeFromParent(fatp, parentINum, iNum);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete inode %d\n", iNum);
        goto isfsDelete_out;
    }

    __isfsStats.freeInodes++;
    __isfsStats.occupiedInodes--;

    if (garbageCollect) {
        /* Do garbage collection */
        rc = __isfsGarbageCollect(fatp);
        if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_NOEXISTS)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to do garbage collection,"
                                " rc=%d\n", rc);
        }
        rc = ISFS_ERROR_OK;       /* Ignore error */
    }

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        /* FAT is corrupted */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsDelete_out;
    }

isfsDelete_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsRename
 *
 *  Description:
 *      This function renames the file or directory to the new name
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      group - ID for checking access control
 *      oldName - Old full path name
 *      newName - New full path name
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The caller has no write access to either parent dir
 *      ISFS_ERROR_NOEXISTS - The old file or directory does not exist
 *      ISFS_ERROR_EXISTS - New name already exists but has different inode type
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsRename(IOSUid owner, IOSGid group, const u8 *oldName,
        const u8 *newName)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         oldNum, oldPrtNum, newNum, newPrtNum;
    u32         garbageCollect = 0;
    u8          oldParent[ISFS_PATH_MAXLEN], oldChild[ISFS_INODE_NAMELEN+1];
    u8          newParent[ISFS_PATH_MAXLEN], newChild[ISFS_INODE_NAMELEN+1];
    u8          oldType, newType, typeAcc;

    ISFS_ENTRY();

    /* Check input parameters */
    if ((!__isfsVerifyFullPathName(oldName)) ||
            (!__isfsVerifyFullPathName(newName))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid file or directory names\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsRename_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsRename_out;
    }

    /* Locate the name of the parent directories */
    rc = __isfsGetParentDir(oldName, &oldParent[0], &oldChild[0]);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get parent directory name for"
                            " %s\n", oldName);

        rc = ISFS_ERROR_INVALID;
        goto isfsRename_out;
    }

    rc = __isfsGetParentDir(newName, &newParent[0], &newChild[0]);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get parent directory name for"
                            " %s\n", newName);

        rc = ISFS_ERROR_INVALID;
        goto isfsRename_out;
    }

    /* Find the inode number of the parent directories */
    oldPrtNum = __isfsGetInodeNum(fatp, &oldParent[0]);
    if (oldPrtNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                            &oldParent[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsRename_out;
    }

    newPrtNum = __isfsGetInodeNum(fatp, &newParent[0]);
    if (newPrtNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                            &newParent[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsRename_out;
    }

    /* Verify write access to the parent directories */
    rc = __isfsVerifyAccess(fatp, oldPrtNum, owner, group, ISFS_WRITE_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "No write access to the parent directory"
                            " %s\n", &oldParent[0]);
        goto isfsRename_out;
    }

    rc = __isfsVerifyAccess(fatp, newPrtNum, owner, group, ISFS_WRITE_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "No write access to the parent directory"
                            " %s\n", &newParent[0]);
        goto isfsRename_out;
    }

    /* Find the inode # of the files or directories */
    oldNum = __isfsGetInodeNumInDir(fatp, oldPrtNum, &oldChild[0]);
    if (oldNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s in"
                            " directory %s\n", &oldChild[0], &oldParent[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsRename_out;
    }
    oldType = ISFS_FAT_INODE_ARRAY(fatp)[oldNum].typeAcc & ISFS_INODE_TYPE_MASK;

    /* File rename must keep the same relative file name */
    if (ISFS_INODE_TYPE_ISFILE(oldType) &&
            (strncmp(oldChild, newChild, ISFS_INODE_NAMELEN) != 0)) {
        isfsPrint(ISFS_DEBUG_ERROR, "File rename must keep the same relative"
                            " file name - %s:%s\n", oldChild, newChild);

        rc = ISFS_ERROR_INVALID;
        goto isfsRename_out;
    }

    /* Only allow deletion if there are no open file descriptors */
    if (ISFS_INODE_TYPE_ISDIR(oldType)) {
        rc = __isfsApplyOpToTree(fatp, oldNum, ISFS_TREE_OP_CHECK_FD);
        if (rc != ISFS_ERROR_OK) {
            goto isfsRename_out;
        }
    } else {
        rc = __isfsCheckFdEntryForInode(oldNum);
        if (rc != ISFS_ERROR_OK) {
            goto isfsRename_out;
        }
    }

    newNum = __isfsGetInodeNumInDir(fatp, newPrtNum, &newChild[0]);
    if (newNum != ISFS_INODENUM_INVALID) {
        newType = ISFS_FAT_INODE_ARRAY(fatp)[newNum].typeAcc &
                                                    ISFS_INODE_TYPE_MASK;

        /* Verify the new inode is of the same type */
        if (oldType != newType) {
            isfsPrint(ISFS_DEBUG_ERROR, "Old inode and new inode are not of the"
                                " same type, old=%d, new=%d\n",
                                oldType, newType);

            rc = ISFS_ERROR_EXISTS;
        }

        if (ISFS_INODE_TYPE_ISDIR(newType)) {
            if (ISFS_FAT_INODE_ARRAY(fatp)[newNum].addr.child !=
                                                        ISFS_INODENUM_INVALID) {
                rc = __isfsApplyOpToTree(fatp, oldNum, ISFS_TREE_OP_CHECK_FD);
                if (rc != ISFS_ERROR_OK) {
                    goto isfsRename_out;
                }

                /* Remove all inodes under this directory */
                rc = __isfsApplyOpToTree(fatp, newNum, ISFS_TREE_OP_REM_INODE);
                if (rc != ISFS_ERROR_OK) {
                    isfsPrint(ISFS_DEBUG_ERROR, "Failed to apply tree operation "
                                        " to remove file descriptors, rc=%d\n",
                                        rc);
                    goto isfsRename_out;
                }

                /* Likely that garbage collection is needed */
                garbageCollect = 1;
            }
        } else {
            u32     block, nextBlock;

            rc = __isfsCheckFdEntryForInode(newNum);
            if (rc != ISFS_ERROR_OK) {
                goto isfsRename_out;
            }

            /* Delete all FS blocks that belong to this file */
            block = ISFS_FAT_INODE_ARRAY(fatp)[newNum].addr.block;
            while (block != ISFS_BLOCK_LAST) {
                nextBlock = ISFS_FAT_BLOCK_ARRAY(fatp)[block];
                ISFS_FAT_BLOCK_ARRAY(fatp)[block] = ISFS_BLOCK_AVAIL_DIRTY;
                block = nextBlock;

                __isfsStats.freeBlocks++;
                __isfsStats.occupiedBlocks--;

                garbageCollect = 1;
            }
        }

        /* Delete the inode from the parent directory's file list */
        rc = __isfsRemoveInodeFromParent(fatp, newPrtNum, newNum);
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete inode %d\n", newNum);
            goto isfsRename_out;
        }

        __isfsStats.freeInodes++;
        __isfsStats.occupiedInodes--;

        if (garbageCollect) {
            /* Do garbage collection */
            rc = __isfsGarbageCollect(fatp);
            if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_NOEXISTS)) {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to do garbage collection,"
                                    " rc=%d\n", rc);
            }
            rc = ISFS_ERROR_OK;       /* Ignore error */
        }
    }

    /* Delete the old inode from the parent directory's file list */
    typeAcc = ISFS_FAT_INODE_ARRAY(fatp)[oldNum].typeAcc;
    rc = __isfsRemoveInodeFromParent(fatp, oldPrtNum, oldNum);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to delete inode %d\n", oldNum);
        goto isfsRename_out;
    }

    /* Change the old inode's name to the new name */
    strncpy(ISFS_FAT_INODE_ARRAY(fatp)[oldNum].name, newChild,
        ISFS_INODE_NAMELEN);

    /* Insert this inode into the new parent directory */
    ISFS_FAT_INODE_ARRAY(fatp)[oldNum].typeAcc = typeAcc;
    ISFS_FAT_INODE_ARRAY(fatp)[oldNum].nextSibling =
                            ISFS_FAT_INODE_ARRAY(fatp)[newPrtNum].addr.child;
    ISFS_FAT_INODE_ARRAY(fatp)[newPrtNum].addr.child = oldNum;

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        /* FAT is corrupted */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsRename_out;
    }

isfsRename_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsCreateFile
 *
 *  Description:
 *      This function creates a new file with the specified attributes
 *
 *  Inputs:
 *      owner - User ID of the caller
 *      group - Group ID of the caller
 *      fname - Full path name of the file
 *      fileAttr - 4-bit file attribute
 *      ownerAcc - Permission bits for the owner
 *      groupAcc - Permission bits for the group
 *      others - Permission bits for the others
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The caller has no write access to the parent dir
 *      ISFS_ERROR_EXISTS - The file or directory already exists
 *      ISFS_ERROR_MAXFILES - Ran out of inode entries
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsCreateFile(IOSUid owner, IOSGid group, const u8 *fname, u32 fileAttr,
            u32 ownerAcc, u32 groupAcc, u32 othersAcc)
{ 
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum, parentINum, len, count;
    u8          parentDir[ISFS_PATH_MAXLEN], child[ISFS_INODE_NAMELEN+1];

    ISFS_ENTRY();

    /* Check input parameters */
    if ((len = __isfsVerifyFullPathName(fname)) == 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid file name\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsCreateFile_out;
    }

    /*
     * Check that the name contains only valid characters
     */
    for (count = 0; count < len; count++) {
        if ((fname[count] < ISFS_NAME_MIN_ASCII) ||
                (fname[count] > ISFS_NAME_MAX_ASCII)) {
            isfsPrint(ISFS_DEBUG_WARN, "Invalid character %c\n", fname[count]);

            rc = ISFS_ERROR_INVALID;
            goto isfsCreateFile_out;
        }
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsCreateFile_out;
    }

    /* Locate the name of the parent directory */
    rc = __isfsGetParentDir(fname, &parentDir[0], &child[0]);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get parent directory name for"
                            " %s\n", fname);

        rc = ISFS_ERROR_INVALID;
        goto isfsCreateFile_out;
    }

    /* Find the inode number of the parent directory */
    parentINum = __isfsGetInodeNum(fatp, &parentDir[0]);
    if (parentINum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for %s\n",
                            &parentDir[0]);

        rc = ISFS_ERROR_NOEXISTS;
        goto isfsCreateFile_out;
    }

    /* Verify write access to the parent directory */
    rc = __isfsVerifyAccess(fatp, parentINum, owner, group, ISFS_WRITE_ACCESS);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "No write access to the parent directory"
                            " %s\n", &parentDir[0]);
        goto isfsCreateFile_out;
    }

    /* Make sure no file or directory with the same name already exists */
    iNum = __isfsGetInodeNumInDir(fatp, parentINum, &child[0]);
    if (iNum != ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "The file %s already exists\n", fname);

        rc = ISFS_ERROR_EXISTS;
        goto isfsCreateFile_out;
    }

    /* Insert a new child inode at the beginning of the directory file list */
    iNum = __isfsGetNextAvailInodeNum(fatp);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "No more available inode\n");

        rc = ISFS_ERROR_MAXFILES;
        goto isfsCreateFile_out;
    }

    /* Set the new inode */
    strncpy(ISFS_FAT_INODE_ARRAY(fatp)[iNum].name, child, ISFS_INODE_NAMELEN);
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc =
                (ownerAcc << ISFS_INODE_OWNER_ACCESS_SHIFT) |
                (groupAcc << ISFS_INODE_GROUP_ACCESS_SHIFT) |
                (othersAcc << ISFS_INODE_OTHERS_ACCESS_SHIFT) |
                ISFS_INODE_TYPE_FILE;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].attr = fileAttr;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block = ISFS_BLOCK_LAST;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].nextSibling =
                            ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].size = 0;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner = owner;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].group = group;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].version = 0;

    ISFS_FAT_INODE_ARRAY(fatp)[parentINum].addr.child = iNum;

    __isfsStats.freeInodes--;
    __isfsStats.occupiedInodes++;

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        /* FAT is corrupted */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsCreateFile_out;
    }

isfsCreateFile_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsSetVersionControl
 *
 *  Description:
 *      This function enables or disables version control
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      fname - Name of the file
 *      enable - 0 to disable, otherwise enable version control
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_NOEXISTS - The file or directory does not exist
 *      ISFS_ERROR_ACCESS - The caller is not the owner
 *      ISFS_ERROR_NOTEMPTY - The file is not empty
 *
 */
ISFSError
isfsSetVersionControl(IOSUid owner, const u8 *fname, u32 enable)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum;

    ISFS_ENTRY();

    /* Check input parameters */
    if (!__isfsVerifyFullPathName(fname)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsSetVersionControl_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsSetVersionControl_out;
    }

    /* Find the inode number of the file */
    iNum = __isfsGetInodeNum(fatp, fname);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for"
                                " %s\n", fname);
        rc = ISFS_ERROR_NOEXISTS;
        goto isfsSetVersionControl_out;
    }

    /* Verify the access rights */
    if ((owner != IOS_ROOT_ID) &&
            (owner != ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Caller ID 0x%x does not match the owner ID"
                    " 0x%x\n", owner, ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner);

        rc = ISFS_ERROR_ACCESS;
        goto isfsSetVersionControl_out;
    }

    /* The inode must be a file */
    if (!ISFS_INODE_TYPE_ISFILE(ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Attempt to enable/disable version control"
                            " for a directory\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsSetVersionControl_out;
    }

    /* The file must be empty */
    if (ISFS_FAT_INODE_ARRAY(fatp)[iNum].size != 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Attempt to enable/disable version control"
                            " for a non-empty file of size %d\n",
                            ISFS_FAT_INODE_ARRAY(fatp)[iNum].size);

        rc = ISFS_ERROR_NOTEMPTY;
        goto isfsSetVersionControl_out;
    }

    /* Sanity check */
    if (((ISFS_FAT_INODE_ARRAY(fatp)[iNum].version == 0) && (!enable)) ||
            ((ISFS_FAT_INODE_ARRAY(fatp)[iNum].version != 0) && (enable))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Version enable sanity check failed,"
                            " version=%d, enable=%d\n",
                            ISFS_FAT_INODE_ARRAY(fatp)[iNum].version, enable);
        rc = ISFS_ERROR_INVALID;
        goto isfsSetVersionControl_out;
    }

    if (enable) {
        fatp->gVersion++;
        ISFS_FAT_INODE_ARRAY(fatp)[iNum].version = fatp->gVersion;
    } else {
        ISFS_FAT_INODE_ARRAY(fatp)[iNum].version = 0;
    }

    /* Commit FAT */
    rc = isfsCommitFat();
    if (rc != ISFS_ERROR_OK) {
        /* FAT is corrupted */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        goto isfsSetVersionControl_out;
    }

#ifndef ISFS_DISABLE_SECURITY
    if (enable) {
        /* Write back the new global version number */
        rc = IOSC_SetData(IOSC_FSVER_HANDLE, fatp->gVersion);
        if (rc != IOS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to write back global version"
                                " number, rc=%d\n", rc);
            goto isfsSetVersionControl_out;
        }
    }
#endif

isfsSetVersionControl_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsOpen
 *
 *  Description:
 *      This function opens the file with the requested permission
 *
 *  Inputs:
 *      owner - ID for checking access control
 *      group - ID for checking access control
 *      fname - Full path name of the file
 *      access - Requested access permission
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      > 0 - File descriptor
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The caller does not have the requested permission
 *      ISFS_ERROR_NOEXISTS - The file does not exist
 *      ISFS_ERROR_MAXFD - Runs out of file descriptor entries
 *
 */
s32
isfsOpen(IOSUid owner, IOSGid group, const u8 *fname, u32 access)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum;
    s32         fd;

    ISFS_ENTRY();

    /* Check input parameters */
    if (!__isfsVerifyFullPathName(fname)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid file name\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsOpen_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsOpen_out;
    }

    /* Find the inode number of the file */
    iNum = __isfsGetInodeNum(fatp, fname);
    if (iNum == ISFS_INODENUM_INVALID) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get inode number for"
                                " %s\n", fname);
        rc = ISFS_ERROR_NOEXISTS;
        goto isfsOpen_out;
    }

    /* Verify that the inode is a file */
    if (!ISFS_INODE_TYPE_ISFILE(ISFS_FAT_INODE_ARRAY(fatp)[iNum].typeAcc)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Specified name %s is not a file", fname);

        rc = ISFS_ERROR_INVALID;
        goto isfsOpen_out;
    }

    /* Verify requested access to the file */
    rc = __isfsVerifyAccess(fatp, iNum, owner, group, access);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Access violation to file %s\n", &fname[0]);
        goto isfsOpen_out;
    }

    /* Get new file descriptor */
    fd = isfsGetNextAvailFdEntry(owner, group, iNum, access,
                            ISFS_FAT_INODE_ARRAY(fatp)[iNum].size);
    if (fd < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to get new fd entry, rc=%d\n", fd);

        rc = ISFS_ERROR_MAXFD;
        goto isfsOpen_out;
    }

    rc = fd;

isfsOpen_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsGetFileStats
 *
 *  Description:
 *      This function retrieves the file's statistics information
 *
 *  Inputs:
 *      fd - File descriptor
 *
 *  Outputs:
 *      stat - Statistics info
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The file descriptor does not have read access
 *      ISFS_ERROR_NOEXISTS - The file descriptor is invalid
 *
 */
ISFSError
isfsGetFileStats(s32 fd, ISFSFileStats *stats)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         iNum;
    ISFSFdEntry *fd_entry_p = (ISFSFdEntry *) fd;

    ISFS_ENTRY();

    /* Check input parameters */
    if ((fd < 0) || (stats == NULL)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");
        rc = ISFS_ERROR_INVALID;
        goto isfsGetFileStats_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");
        rc = ISFS_ERROR_NOTREADY;
        goto isfsGetFileStats_out;
    }

    if ((fd_entry_p->access & ISFS_READ_ACCESS) == 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Access not granted\n");
        rc = ISFS_ERROR_ACCESS;
        goto isfsGetFileStats_out;
    }
    iNum = fd_entry_p->inodeNum;

    stats->size = ISFS_FAT_INODE_ARRAY(fatp)[iNum].size;
    stats->offset = fd_entry_p->offset;

isfsGetFileStats_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsSeek
 *
 *  Description:
 *      This function reads FS blocks from the flash
 *
 *  Inputs:
 *      fd - File descriptor
 *      offset - Offset into the file, must be FS block aligned
 *      whence - Base offset from beginning, end, or current
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The file descriptor does not have read/write access
 *      ISFS_ERROR_NOEXISTS - The file descriptor is invalid
 *
 */
ISFSError
isfsSeek(s32 fd, s32 offset, u32 whence)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    ISFSFdEntry *fd_entry_p = (ISFSFdEntry *) fd;
    u32         iNum;
    s32         offsetTmp;

    ISFS_ENTRY();

    if (fd < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid fd %d\n", fd);

        rc = ISFS_ERROR_INVALID;
        goto isfsSeek_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsSeek_out;
    }

    iNum = fd_entry_p->inodeNum;

    if (whence == IOS_SEEK_SET) {            /* Relative to file beginning */
        offsetTmp = 0;
    } else if (whence == IOS_SEEK_CURRENT) { /* Relative to current offset */
        offsetTmp = fd_entry_p->offset;
    } else if (whence == IOS_SEEK_END) {     /* Relative to file end */
        offsetTmp = ISFS_ALIGN_SIZE(ISFS_FAT_INODE_ARRAY(fatp)[iNum].size);
    } else {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid whence %d\n", whence);

        rc = ISFS_ERROR_INVALID;
        goto isfsSeek_out;
    }

    offsetTmp += offset;

    if ((offsetTmp < 0) ||
            (offsetTmp > ISFS_ALIGN_SIZE(
                                    ISFS_FAT_INODE_ARRAY(fatp)[iNum].size)) ||
            ((offsetTmp & (ISFS_BLOCK_SIZE - 1)) != 0)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid offset %d, whence %d with file"
                            " size %d\n", offset, whence,
                            ISFS_FAT_INODE_ARRAY(fatp)[iNum].size);

        rc = ISFS_ERROR_INVALID;
        goto isfsSeek_out;
    }

    fd_entry_p->offset = offsetTmp;

isfsSeek_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsRead
 *
 *  Description:
 *      This function reads FS blocks from the flash
 *
 *  Inputs:
 *      fd - File descriptor
 *      size - Number of bytes to read, must be FS block aligned
 *
 *  Outputs:
 *      buf - Output buffer for the data
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The file descriptor does not have read access
 *      ISFS_ERROR_NOEXISTS - The file descriptor is invalid
 *      ISFS_ERROR_ECC_CRIT - Multi-bit ECC error
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsRead(s32 fd, u8 *buf, u32 size)
{
    ISFSError       rc = ISFS_ERROR_OK;
    ISFSFat         *fatp = NULL;
    u32             iNum, blockNum, offset, bufOffset = 0;
    u32             blockOffset, ver, commit = 0;
    ISFSFdEntry     *fd_entry_p = (ISFSFdEntry *) fd;

    ISFS_ENTRY();

    /* Check input parameters */
    if ((fd < 0) || (buf == NULL) || ((size & (ISFS_BLOCK_SIZE - 1)) != 0) ||
            (size == 0)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsRead_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsRead_out;
    }

    if ((fd_entry_p->access & ISFS_READ_ACCESS) == 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Read access not granted\n");

        rc = ISFS_ERROR_ACCESS;
        goto isfsRead_out;
    }
    iNum = fd_entry_p->inodeNum;
    offset = fd_entry_p->offset;

    /* Check to make sure the file is large enough */
    if (ISFS_ALIGN_SIZE(ISFS_FAT_INODE_ARRAY(fatp)[iNum].size) <
            (offset + size)) {
        isfsPrint(ISFS_DEBUG_ERROR, "The file size %d is smaller than"
                            " the requested size %d\n",
                            ISFS_FAT_INODE_ARRAY(fatp)[iNum].size,
                            (offset + size));

        rc = ISFS_ERROR_INVALID;
        goto isfsRead_out;
    }

    blockOffset = offset >> ISFS_BLOCK_SIZE_SHIFT;
    ver = ISFS_FAT_INODE_ARRAY(fatp)[iNum].version;

    blockNum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block;
    while (offset > 0) {
        blockNum = ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum];
        offset -= ISFS_BLOCK_SIZE;
    }

    __isfsCustomData.ownerId = ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner;
    memcpy(__isfsCustomData.fname, ISFS_FAT_INODE_ARRAY(fatp)[iNum].name,
        ISFS_INODE_NAMELEN);
    __isfsCustomData.inodeIndex = iNum;
    __isfsCustomData.fVersion = ver;
    memset(__isfsCustomData.pad, 0, sizeof (__isfsCustomData.pad));

    /* Read data from flash */
    while (bufOffset < size) {
        __isfsCustomData.blockOffset = blockOffset;
        rc = isfsReadFsBlocks(blockNum, 1,
                        ISFS_BLOCK_OP_ENCRYPTION | ISFS_BLOCK_OP_AUTH,
                        &__isfsCustomData, (buf + bufOffset), NULL);
        if (rc != ISFS_ERROR_OK) {
            if (rc == ISFS_ERROR_ECC) {
                ISFSBlockEntry  newBlock = 0, moved[1][2];
                u32             garbageCollected = 0;

                /* Re-write the content to correct the ECC error */
                commit = 1;
                newBlock = __isfsGetNextAvailFsBlock(fatp, &garbageCollected);
                if (newBlock == ISFS_BLOCK_BAD) {
                    isfsPrint(ISFS_DEBUG_WARN, "Failed to get free FS block\n");

                    rc = ISFS_ERROR_MAXBLOCKS;
                    goto isfsRead_out;
                }
                moved[0][0] = blockNum;
                moved[0][1] = newBlock;

                __isfsCustomData.blockOffset = blockOffset;
                rc = isfsWriteFsBlocks(newBlock, 1,
                                ISFS_BLOCK_OP_ENCRYPTION | ISFS_BLOCK_OP_AUTH,
                                &__isfsCustomData, (buf + bufOffset), NULL);
                if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_BADBLOCK)) {
                    isfsPrint(ISFS_DEBUG_ERROR, "Failed to re-write FS block,"
                                        " rc=%d\n", rc);
                    goto isfsRead_out;
                }
                if (rc == ISFS_ERROR_BADBLOCK) {
                    u32     totalBlockOffset = 0;

                    rc = __isfsBlockReplacement(fatp, newBlock);
                    if (rc != ISFS_ERROR_OK) {
                        isfsPrint(ISFS_DEBUG_ERROR, "Failed to replace FS block"
                                            " %d, rc=%d\n", newBlock, rc);
                        goto isfsRead_out;
                    }

                    /*
                     * Read the next block. Note that the block
                     * numbers may have been changed by the block
                     * replacement, so it is necessary to traverse
                     * the file list again to find the block number
                     */
                    totalBlockOffset = fd_entry_p->offset + bufOffset;
                    blockNum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block;
                    while (totalBlockOffset > 0) {
                        blockNum = ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum];
                        totalBlockOffset -= ISFS_BLOCK_SIZE;
                    }
                } else {
                    /* Set the file block list links appropriately */
                    __isfsMoveFsBlockEntries(fatp, moved, 1);
                    ISFS_FAT_BLOCK_ARRAY(fatp)[newBlock] =
                                        ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum];
                    ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum] =
                                        ISFS_BLOCK_AVAIL_DIRTY;

                    blockNum = newBlock;
                }

                rc = ISFS_ERROR_OK;
            } else {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to read file system block"
                            " with block number: %d, rc=%d\n", blockNum, rc);
                goto isfsRead_out;
            }
        }

        blockOffset++;
        blockNum = ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum];
        bufOffset += ISFS_BLOCK_SIZE;
    }

    /* Increment fd offset by read size */
    fd_entry_p->offset += size;

isfsRead_out:

    /* Commit FAT */
    if (commit) {
        rc = isfsCommitFat();
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        }
    }

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsWrite
 *
 *  Description:
 *      This function writes FS blocks to the flash
 *
 *  Inputs:
 *      fd - File descriptor
 *      buf - Data to be written to the flash, padded to FS block size
 *      size - Number of ACTUAL data bytes may NOT be FS block aligned
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The file descriptor does not have read access
 *      ISFS_ERROR_NOEXISTS - The file descriptor is invalid
 *      ISFS_ERROR_MAXBLOCKS - Ran out of FS blocks
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 */
ISFSError
isfsWrite(s32 fd, const u8 *buf, u32 size)
{
    ISFSError       rc = ISFS_ERROR_OK;
    ISFSFat         *fatp;
    u32             iNum, alignedSz;
    ISFSBlockEntry  blockNum, firstBlock = ISFS_BLOCK_LAST;
    ISFSBlockEntry  lastBlock = ISFS_BLOCK_BAD, nextBlock;
    u32             offset, bufOffset = 0, numBlocks = 0;
    u32             blockOffset, ver, commit = 0;
    ISFSFdEntry     *fd_entry_p = (ISFSFdEntry *) fd;

    ISFS_ENTRY();

    /* Check input parameters */
    if ((fd < 0) || (buf == NULL) || (size == 0)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters\n");

        rc = ISFS_ERROR_INVALID;
        goto isfsWrite_out;
    }
    alignedSz = ISFS_ALIGN_SIZE(size);

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted that
         * it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsWrite_out;
    }

    if ((fd_entry_p->access & ISFS_WRITE_ACCESS) == 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Write access not granted\n");

        rc = ISFS_ERROR_ACCESS;
        goto isfsWrite_out;
    }
    iNum = fd_entry_p->inodeNum;
    offset = fd_entry_p->offset;

    /* Size must align on FS block unless the write involves the last block */
    if ((size != alignedSz) && ((offset + size) <
            (ISFS_FAT_INODE_ARRAY(fatp)[iNum].size & ~(ISFS_BLOCK_SIZE - 1)))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Size must align on FS block boundary unless"
                            " the last block is involved, size=%d,"
                            " offset=%d, file=%d\n", size, offset,
                            ISFS_FAT_INODE_ARRAY(fatp)[iNum].size);

        rc = ISFS_ERROR_INVALID;
        goto isfsWrite_out;
    }

    blockOffset = offset >> ISFS_BLOCK_SIZE_SHIFT;
    ver = ISFS_FAT_INODE_ARRAY(fatp)[iNum].version;

    /* Write data to flash */
    while (bufOffset < alignedSz) {
        u32     garbageCollected = 0;

        blockNum = __isfsGetNextAvailFsBlock(fatp, &garbageCollected);
        if (garbageCollected) {
            commit = 1;
        }
        if (blockNum == ISFS_BLOCK_BAD) {
            isfsPrint(ISFS_DEBUG_WARN, "Failed to get free FS block\n");

            rc = ISFS_ERROR_MAXBLOCKS;
            goto isfsWrite_out;
        }

        __isfsCustomData.ownerId = ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner;
        memcpy(__isfsCustomData.fname, ISFS_FAT_INODE_ARRAY(fatp)[iNum].name,
            ISFS_INODE_NAMELEN);
        __isfsCustomData.blockOffset = blockOffset;
        __isfsCustomData.inodeIndex = iNum;
        __isfsCustomData.fVersion = ver;
        memset(__isfsCustomData.pad, 0, sizeof (__isfsCustomData.pad));

        rc = isfsWriteFsBlocks(blockNum, 1,
                        ISFS_BLOCK_OP_ENCRYPTION | ISFS_BLOCK_OP_AUTH,
                        &__isfsCustomData, (buf + bufOffset), NULL);
        if (rc != ISFS_ERROR_OK) {
            if (rc == ISFS_ERROR_BADBLOCK) {
                commit = 1;

                /* Replace the entire flash block */
                rc =  __isfsBlockReplacement(fatp, blockNum);
                if (rc == ISFS_ERROR_OK) {
                    /* Re-try writing this data block */
                    continue;
                }

                isfsPrint(ISFS_DEBUG_ERROR, "Failed to replace FS block %d,"
                                    " rc=%d\n", blockNum, rc);
            } else {
                isfsPrint(ISFS_DEBUG_ERROR, "Failed to write file system block"
                                    " with block number: %d, rc=%d\n",
                                    blockNum, rc);
            }

            /* Free the blocks allocated */
            while (firstBlock != ISFS_BLOCK_LAST) {
                ISFSBlockEntry  temp;

                temp = ISFS_FAT_BLOCK_ARRAY(fatp)[firstBlock];
                ISFS_FAT_BLOCK_ARRAY(fatp)[firstBlock] = ISFS_BLOCK_AVAIL_DIRTY;
                firstBlock = temp;
        
                __isfsStats.freeBlocks++;
                __isfsStats.occupiedBlocks--;
            }

            goto isfsWrite_out;
        }

        __isfsStats.freeBlocks--;
        __isfsStats.occupiedBlocks++;

        /* The first data block will be linked to the file */
        if (bufOffset == 0) {
            firstBlock = blockNum;
        }

        /* Link up the new data blocks */
        ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum] = ISFS_BLOCK_LAST;
        if (lastBlock != ISFS_BLOCK_BAD) {
            ISFS_FAT_BLOCK_ARRAY(fatp)[lastBlock] = blockNum;
        }
        lastBlock = blockNum;

        blockOffset++;
        bufOffset += ISFS_BLOCK_SIZE;
        numBlocks++;
    }

    /* Link the new data blocks to the file block list */
    if (offset == 0) {
        nextBlock = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block;
        ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block = firstBlock;
    } else {
        blockNum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.block;

        while (1) {
            offset -= ISFS_BLOCK_SIZE;
            if (offset == 0) {
                nextBlock = ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum];
                ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum] = firstBlock;

                break;
            }

            blockNum = ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum];
        }
    }

    /* Some old data blocks may get over-written, mark them as free-dirty */
    while ((nextBlock != ISFS_BLOCK_LAST) && (numBlocks > 0)) {
        blockNum = nextBlock;
        nextBlock = ISFS_FAT_BLOCK_ARRAY(fatp)[nextBlock];

        ISFS_FAT_BLOCK_ARRAY(fatp)[blockNum] = ISFS_BLOCK_AVAIL_DIRTY;
        numBlocks--;
        
        __isfsStats.freeBlocks++;
        __isfsStats.occupiedBlocks--;
    }
    ISFS_FAT_BLOCK_ARRAY(fatp)[lastBlock] = nextBlock;

    /* Increment fd offset to new position */
    fd_entry_p->offset += alignedSz;

    /* Set new file size */
    if (ISFS_FAT_INODE_ARRAY(fatp)[iNum].size < fd_entry_p->offset) {
        ISFS_FAT_INODE_ARRAY(fatp)[iNum].size =
                                    fd_entry_p->offset - (alignedSz - size);
    }

    /* Mark the file descriptor as changed */
    fd_entry_p->changed = 1;

isfsWrite_out:

    /* Commit FAT */
    if (commit) {
        rc = isfsCommitFat();
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        }
    }

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsClose
 *
 *  Description:
 *      This function closes the file and commits all file writes to
 *      the flash
 *
 *  Inputs:
 *      fd - File descriptor
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - The file system needs to be (re)formatted
 *      ISFS_ERROR_ACCESS - The file descriptor does not have access
 *      ISFS_ERROR_NOEXISTS - The file descriptor is invalid
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsClose(s32 fd)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    ISFSFdEntry *fd_entry_p = (ISFSFdEntry *) fd;

    ISFS_ENTRY();

    /* Check input parameters */
    if (fd < 0) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid fd %d\n", fd);

        rc = ISFS_ERROR_INVALID;
        goto isfsClose_out;
    }

    /* Get a pointer to the cached FAT */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsClose_out;
    }

    /* Commit FAT if changes were made */
    if (fd_entry_p->changed) {
        rc = isfsCommitFat();
        if (rc != ISFS_ERROR_OK) {
            /* FAT is corrupted */
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
            goto isfsClose_out;
        }
    }

    /* Reset the file descriptor entry */
    fd_entry_p->inUse = 0;

isfsClose_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsMount
 *
 *  Description:
 *      This is an internal operation triggered during file system
 *      initialization. It loads the FAT from the flash, verifies its
 *      integrity, and initializes some data structures
 *
 *  Inputs:
 *      mount - 1 to mount, 0 to unmount
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_NOTREADY - File system needs to be (re)formatted
 *      ISFS_ERROR_UNKNOWN - An unknown error has occurred
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond repair
 *
 */
ISFSError
isfsMount(u32 mount)
{
    ISFSError   rc = ISFS_ERROR_OK;
    ISFSFat     *fatp;
    u32         count, modified = 0;

    ISFS_ENTRY();

    if (!mount) {
        isfsPrint(ISFS_DEBUG_INFO, "File system unmounted\n");
        (void) isfsInitFat(0);
        (void) isfsInitFsBlocks(0);
        goto isfsMount_out;
    }

    /* Initialize the FS block module */
    rc = isfsInitFsBlocks(1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to initialize the FS block module,"
                            "rc=%d\n", rc);
        goto isfsMount_out;
    }

    /* Initialize the FAT module */
    rc = isfsInitFat(1);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to initialize the FAT module,"
                            "rc=%d\n", rc);
        goto isfsMount_initFat_out;
    }

    /* Load the most recent FAT from the flash */
    fatp = isfsLoadFat();
    if (fatp == NULL) {
        /*
         * File system not formatted yet or so corrupted
         * that it needs to be reformatted
         */
        isfsPrint(ISFS_DEBUG_WARN, "Failed to retrieve FAT\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsMount_load_out;
    }

    /* Perform integrity checks on the file system and repairs if necessary */
    rc = __isfsCheck(fatp, &modified);
    if (rc != ISFS_ERROR_OK) {
        /* File system repair should not return an error */
        isfsPrint(ISFS_DEBUG_ERROR, "Failed system check failed, rc=%d\n", rc);
        goto isfsMount_load_out;
    }

    /*
     * Since the FAT is committed after the FS blocks are written, it
     * can not be trusted to provide the clean/dirty status of a free
     * FS block at bootup. Mark all FS free blocks as dirty
     */
    for (count = 0; count < ISFS_BLOCK_ENTRIES; count++) {
        if (ISFS_FAT_BLOCK_ARRAY(fatp)[count] == ISFS_BLOCK_AVAIL_CLEAN) {
            ISFS_FAT_BLOCK_ARRAY(fatp)[count] = ISFS_BLOCK_AVAIL_DIRTY;
        }
    }

    /* Set up the file descriptor table */
    for (count = 0; count < ISFS_FD_ENTRIES; count++) {
        __isfsFdTable[count].inUse = 0;
    }

    /* Set up file system statistics */
    rc = __isfsGatherStats(fatp);
    if (rc != ISFS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to reserve space, rc=%d\n", rc);
        goto isfsMount_load_out;
    }

    goto isfsMount_out;

isfsMount_load_out:

    (void) isfsInitFat(0);

isfsMount_initFat_out:

    (void) isfsInitFsBlocks(0);

isfsMount_out:

    /* Commit FAT */
    if (modified) {
        rc = isfsCommitFat();
        if (rc != ISFS_ERROR_OK) {
            /* FAT is corrupted */
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to commit FAT, rc=%d\n", rc);
        }
    }

    ISFS_EXIT();

    return (rc);
}
