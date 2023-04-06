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
 *      This file implements the read and commit operations for the File
 *      Allocation Table (FAT)
 *
 */


#ifdef NET_CARD
#include <sc/libc.h>
#include <sc/iostypes.h>
#include <sc/sc.h>
#include <sc/ios.h>
#include <sc/iosc.h>
#include <sc/flash.h>
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <iop.h>
#include <ios.h>
#ifndef ISFS_DISABLE_SECURITY
#include <iosc.h>
#endif
#include <flash.h>
#endif

#include "fs_utils.h"
#include "fs_block.h"
#include "fs_fat.h"


/*
 * Global variable used for storing flash layout, which is
 * needed throughout the file system to determine the value
 * of certain macros
 */
ISFSFlashLayout     __isfsFlashLayout;


/*
 *  Description:
 *      Compute the physical FS block index given the FAT index
 *      from 0 to 15. In the case of the 128MB flash with a flash
 *      block size of 128KB and a FAT block size of 64KB, the
 *      first flash block contains FAT index 0 and 8, the next one
 *      contains FAT index 1 and 9, ...etc. The following formula
 *      computes the correct result for both the 64MB and the
 *      128MB flash devices. Basically, it is the FAT area offset
 *      + the flash block offset + offset within the flash block.
 *      It also computes the correct result for FAT that spans
 *      muliple flash blocks
 *
 */
#define ISFS_FATAREA_OFFSET                                                 \
    ((__isfsFlashLayout.saSz + __isfsFlashLayout.dataSz)                    \
        >> ISFS_BLOCK_SIZE_SHIFT)

#define ISFS_FATTOFL_BLOCK_SHIFT                                            \
    ((ISFS_FAT_BLOCK_SIZE_SHIFT > __isfsFlashCap.erasableBlockSzShift) ?    \
        (ISFS_FAT_BLOCK_SIZE_SHIFT - __isfsFlashCap.erasableBlockSzShift) : 0)

#define ISFS_HORIZONTAL_OFFSET(index)                                       \
    (((index &                                                              \
      ((1 <<                                                                \
        (__isfsFlashLayout.fatSzShift - __isfsFlashCap.erasableBlockSzShift)) \
        - 1)) <<                                                            \
      ISFS_FATTOFL_BLOCK_SHIFT) <<                                          \
      (__isfsFlashCap.erasableBlockSzShift - ISFS_BLOCK_SIZE_SHIFT))

#define ISFS_VERTICAL_OFFSET(index)                                         \
    ((index >>                                                              \
      (__isfsFlashLayout.fatSzShift - __isfsFlashCap.erasableBlockSzShift))   \
      * ISFS_FAT_SIZE_IN_BLOCKS)

#define ISFS_FAT_INDEX_TO_ISFS_BLOCK(index)                                 \
    ISFS_FATAREA_OFFSET + ISFS_HORIZONTAL_OFFSET(index) +                   \
        ISFS_VERTICAL_OFFSET(index)

#define ISFS_FAT_INDEX_NEXT(index)    ((index + 1) & (ISFS_FAT_COPIES - 1))


/*
 * __isfsFatp and __isfsFatNextIndex are valid only if (__isfsFatValid == 1)
 */
static u8       __isfsFat[ISFS_MAX_FAT_SIZE]
                    __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));
static ISFSFat  *__isfsFatp = NULL;     /* In-memory FAT structure */
static u32      __isfsFatNextIndex = 0; /* The next FAT index to be used */
static u32      __isfsFatValid = 0;     /* Validity of the in-memory FAT */

/* Custom data for signing a FAT */
static ISFSCustomData   __isfsFatCustomData
                            __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));


/*
 *  Function: isfsInitFat
 *
 *  Description:
 *      This functin allocates and initializes basic structures
 *      within the FAT module. The FS block module has to be
 *      initialized before calling this function
 *
 *  Inputs:
 *      init - 1 to initialize, 0 to de-initialize
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 *  Notes:
 *      The FS block module must be initialized before calling
 *      this function
 *
 */
ISFSError
isfsInitFat(u32 init)
{
    ISFSError   rc = ISFS_ERROR_OK;

    ISFS_ENTRY();

    if (init) {
        /* The system area size is a pre-defined constant */
        __isfsFlashLayout.saSz = ISFS_SYSAREA_SIZE;

        /* The FAT size depends on the total flash size */
        switch (__isfsFlashCap.totalSzShift) {
            case (30):  /* 1GB */
            case (29):  /* 512MB */
                __isfsFlashLayout.fatSzShift = 18 + ISFS_FAT_COPIES_SHIFT;
                break;

            case (28):  /* 256MB */
            case (27):  /* 128MB */
                __isfsFlashLayout.fatSzShift = 16 + ISFS_FAT_COPIES_SHIFT;
                break;

            case (26):  /* 64MB */
                __isfsFlashLayout.fatSzShift = 14 + ISFS_FAT_COPIES_SHIFT;
                break;

            default:
                isfsPrint(ISFS_DEBUG_ERROR, "Unsupported flash size %d\n",
                                        (1 << __isfsFlashCap.totalSzShift));
                rc = ISFS_ERROR_UNKNOWN;
                goto isfsInitFat_out;
        }

        /* The data area takes up the rest of the flash */   
        __isfsFlashLayout.dataSz = (1 << __isfsFlashCap.totalSzShift) -
                __isfsFlashLayout.saSz - (1 << __isfsFlashLayout.fatSzShift);

        __isfsFatp = (ISFSFat *) &__isfsFat;

        /* Zero the custom data used for signing a FAT */
        memset(&__isfsFatCustomData, 0, ISFS_CUSTOM_DATA_LEN);
    } else {
        __isfsFatp = NULL;
    }

isfsInitFat_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsLoadFat
 *
 *  Description:
 *      This function returns the most recent valid FAT. If necessary, it
 *      will load the FATs from the flash, compares to find the most recent
 *      one, and authenticates its content
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFSFat - The most recent and valid FAT
 *      NULL - No valid FAT found
 *
 */
ISFSFat *
isfsLoadFat(void)
{
    ISFSError   rc = ISFS_ERROR_OK;
    u32         fatIndex, fsBlockIndex, recommit = 0, version;
    u32         curSeqNum = 0, highSeqNum = 0xffffffff;
    s32         curFatIndex = -1;
    ISFSFat     *goodFatp = NULL;
    u8          spare[FL_VIRT_SPARE_SIZE];

    ISFS_ENTRY();

    if (__isfsFatp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "Fat module not initialized\n");
        goto isfsLoadFat_out;
    }

    if (__isfsFatValid) {
        goodFatp = __isfsFatp;
        goto isfsLoadFat_out;
    }

#ifndef ISFS_DISABLE_SECURITY
    rc = IOSC_GetData(IOSC_FSVER_HANDLE, &version);
    if (rc != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve global version number,"
                            " rc=%d\n", rc);
        goto isfsLoadFat_out;
    }
#else
    version = 0;
#endif

isfsLoadFat_tryagain:

    /*
     * Load the first FS block of each FAT from the flash. Check
     * the sequence numbers to find the most up-to-date FAT
     */
    for (fatIndex = 0; fatIndex < ISFS_FAT_COPIES; fatIndex++) {
        fsBlockIndex = ISFS_FAT_INDEX_TO_ISFS_BLOCK(fatIndex);

        rc = isfsReadFsBlocks(fsBlockIndex, 1, 0, NULL, (u8 *) __isfsFatp,
                            spare);
        if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_ECC)) {
            isfsPrint(ISFS_DEBUG_NOTIFY, "Failed to read FAT blocks from flash,"
                                " rc=%d\n", rc);
            continue;
        }

        /* Basic validity check */
        if ((__isfsFatp->magic[0] != 'S') || (__isfsFatp->magic[1] != 'F') ||
                (__isfsFatp->magic[2] != 'F') ||
                (__isfsFatp->magic[3] != 'S')) {
            continue;
        }

        /*
         * Allow version number to be off by at most one. It is
         * possible to be off by one when the latest FAT block
         * got corrupted and the next latest FAT block has an
         * earlier version number
         */
        if (version > (__isfsFatp->gVersion + 1)) {
            continue;
        } else if (version > __isfsFatp->gVersion) {
            /*
             * Catch up to the latest version number to avoid
             * re-using an old number
             */
            __isfsFatp->gVersion = version;
        }

        /* High sequence num rules out invalid FATs */
        if ((__isfsFatp->seq < highSeqNum) && (__isfsFatp->seq >= curSeqNum)) {
            curSeqNum = __isfsFatp->seq;
            curFatIndex = fatIndex;
        }
    }

    if (curFatIndex >= 0) {
        fsBlockIndex = ISFS_FAT_INDEX_TO_ISFS_BLOCK(curFatIndex);

        /* Read the entire FAT */
        __isfsFatCustomData.blockOffset = fsBlockIndex;
        rc = isfsReadFsBlocks(fsBlockIndex, ISFS_FAT_SIZE_IN_BLOCKS,
                    (ISFS_BLOCK_OP_AUTH | ISFS_BLOCK_OP_CHAIN),
                    &__isfsFatCustomData, (u8 *) __isfsFatp, spare);
        if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_ECC)) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to read FAT blocks from"
                                    " flash, rc=%d\n", rc);

            highSeqNum = curSeqNum;
            curSeqNum = 0;
            curFatIndex = -1;

            goto isfsLoadFat_tryagain;
        }

        /* If the FAT chosen has ECC errors, recommit the FAT */
        if (rc == ISFS_ERROR_ECC) {
            recommit = 1;
        }

        /* Found a good FAT */
        goodFatp = __isfsFatp;
        __isfsFatNextIndex = ISFS_FAT_INDEX_NEXT(curFatIndex);
    }

isfsLoadFat_out:

    if (goodFatp) {
        __isfsFatValid = 1;
    }

    if (recommit && __isfsFatValid) {
        rc = isfsCommitFat();
        if (rc != ISFS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to recommit FAT with ECC error,"
                                " rc=%d\n", rc);
        }
    }

    ISFS_EXIT();

    return (goodFatp);
}


/*
 *  Function: isfsResetFat
 *
 *  Description:
 *      This function resets the in-memory FAT and marks it as valid.
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFSFat - Pointer to the in-memory FAT
 *
 */
ISFSFat *
isfsResetFat(void)
{
    u32         count;
#ifndef ISFS_DISABLE_SECURITY
    IOSError    rc;
#endif

    ISFS_ENTRY();

    /* The FAT can be invalid, but it needs to be at least initialized */
    if (__isfsFatp == NULL) {
        goto isfsResetFat_out;
    }

    __isfsFatp->magic[0] = 'S';
    __isfsFatp->magic[1] = 'F';
    __isfsFatp->magic[2] = 'F';
    __isfsFatp->magic[3] = 'S';

    if (!__isfsFatValid) {
        /* Set the FAT sequence number */
        __isfsFatp->seq = 1;

#ifndef ISFS_DISABLE_SECURITY
        /* Set the global version number */
        rc = IOSC_GetData(IOSC_FSVER_HANDLE, &(__isfsFatp->gVersion));
        if (rc != IOS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to retrieve global version"
                                " number, rc=%d\n", rc);
            goto isfsResetFat_out;
        }
#else
        __isfsFatp->gVersion = 0;
#endif
    }

    for (count = 0; count < ISFS_BLOCK_ENTRIES; count++) {
        /* Default state for data region is free and dirty */
        ISFSBlockEntry      state;

        if (count < (__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT)) {
            /* Default system area state is reserved */
            state = ISFS_BLOCK_RESERVED;
        } else if (count < ((__isfsFlashLayout.saSz >> ISFS_BLOCK_SIZE_SHIFT) +
                    (__isfsFlashLayout.dataSz >> ISFS_BLOCK_SIZE_SHIFT))) {
            /* Default data region state is free dirty */
            state = ISFS_BLOCK_AVAIL_DIRTY;
        } else {
            /* Default FAT region state is reserved */
            state = ISFS_BLOCK_RESERVED;
        }

        if (__isfsFatValid) {
            /* Retain bad block status, otherwise set to default state */
            if (ISFS_FAT_BLOCK_ARRAY(__isfsFatp)[count] == ISFS_BLOCK_BAD) {
                state = ISFS_BLOCK_BAD;
            }
        } else {
            u32     remainder = 0;

            /* Scan for bad flash blocks */
            remainder = count & (ISFS_BLOCKS_IN_FL_BLOCK - 1);
            if (remainder == 0) {   /* 1st FS block in flash block */
                ISFSError   rc = ISFS_ERROR_OK;

                rc = isfsStatusFsBlock(count);
                if (rc != ISFS_ERROR_OK) {
                    state = ISFS_BLOCK_BAD;
                }
            } else {
                /* If a FS block is bad, the entire flash block is bad */
                state = ISFS_FAT_BLOCK_ARRAY(__isfsFatp)[count - remainder];
            }
        }

        ISFS_FAT_BLOCK_ARRAY(__isfsFatp)[count] = state;
    }

    memset(ISFS_FAT_INODE_ARRAY(__isfsFatp), 0,
            sizeof (ISFSInodeEntry) * ISFS_INODE_ENTRIES);
    for (count = 0; count < ISFS_INODE_ENTRIES; count++) {
        ISFS_FAT_INODE_ARRAY(__isfsFatp)[count].typeAcc =
                                                    ISFS_INODE_TYPE_INVALID;
    }

    __isfsFatNextIndex = 0;

    __isfsFatValid = 1;

isfsResetFat_out:

    ISFS_EXIT();

    return (__isfsFatp);
}


/*
 *  Function: isfsCommitFat
 *
 *  Description:
 *      This function commits the in-memory FAT if it's valid
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_NOEXISTS - In-memory FAT is not valid
 *      ISFS_ERROR_CORRUPT - The flash is corrupted beyond use
 *
 */
ISFSError
isfsCommitFat(void)
{
    ISFSError   rc = ISFS_ERROR_OK;

    ISFS_ENTRY();

    if (__isfsFatValid) {
        u32         fsBlockIndex, tries;
        u8          spare[FL_VIRT_SPARE_SIZE];

        /* Increment FAT sequence number */
        __isfsFatp->seq++;

        /* Choose the right flash location */
        for (tries = 0; tries < ISFS_FAT_COPIES; tries++) {
            u32     written = 0;

            fsBlockIndex = ISFS_FAT_INDEX_TO_ISFS_BLOCK(__isfsFatNextIndex);

            if (ISFS_FAT_BLOCK_ARRAY(__isfsFatp)[fsBlockIndex] ==
                                                    ISFS_BLOCK_RESERVED) {
                __isfsFatCustomData.blockOffset = fsBlockIndex;

                /* Write the entire FAT */
                rc = isfsWriteFsBlocks(fsBlockIndex, ISFS_FAT_SIZE_IN_BLOCKS,
                            (ISFS_BLOCK_OP_AUTH | ISFS_BLOCK_OP_CHAIN),
                            &__isfsFatCustomData, (u8 *) __isfsFatp, spare);
                if (rc != ISFS_ERROR_OK) {
                    if (rc == ISFS_ERROR_BADBLOCK) {
                        isfsPrint(ISFS_DEBUG_INFO, "Detected bad logical"
                                    " block at %d\n", fsBlockIndex);
                        ISFS_MARK_FLASH_BLOCK(__isfsFatp, fsBlockIndex,
                                        ISFS_BLOCK_BAD);
                        __isfsFatp->seq++;  /* Trump the bad FAT */
                    } else {
                        isfsPrint(ISFS_DEBUG_ERROR, "Failed to write FAT"
                                            " blocks to flash, rc=%d\n", rc);
                    }

                    break;
                } else {
                    written = 1;
                }
            }

            __isfsFatNextIndex = ISFS_FAT_INDEX_NEXT(__isfsFatNextIndex);
            if (written) {
                break;
            }
        }

        if (tries == ISFS_FAT_COPIES) {
            isfsPrint(ISFS_DEBUG_CRIT, "The flash is corrupted beyond use\n");

            rc = ISFS_ERROR_CORRUPT;
            goto isfsCommitFat_out;
        }
    } else {
        return (ISFS_ERROR_NOEXISTS);
    }

isfsCommitFat_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isisfsPrintFat
 *
 *  Description:
 *      This function prints a FAT structure in a easy-to-read
 *      format
 *
 *  Inputs:
 *      fatp - The FAT structure
 *
 *  Outputs:
 *      The FAT is printed
 *
 *  Return values:
 *      None
 *
 */
void
isisfsPrintFat(const ISFSFat *fatp)
{
    u32     count;

    ISFS_ENTRY();

    if (fatp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "Input fatp is NULL\n");
        goto isisfsPrintFat_out;
    }

    isfsPrint(ISFS_DEBUG_INFO, "FAT structure at 0x%x\n", (u32) fatp);
    isfsPrint(ISFS_DEBUG_INFO, "Magic: %c%c%c%c\n", fatp->magic[0],
                            fatp->magic[1], fatp->magic[2], fatp->magic[3]);
    isfsPrint(ISFS_DEBUG_INFO, "Version: %d\n", fatp->gVersion);
    isfsPrint(ISFS_DEBUG_INFO, "Seq: %d\n", fatp->seq);

    for (count = 0; count < ISFS_INODE_ENTRIES; count++) {
        u32             charCount;
        ISFSInodeEntry  *inode_p = &(ISFS_FAT_INODE_ARRAY(fatp)[count]);

        if (ISFS_INODE_TYPE_ISINVALID(inode_p->typeAcc)) {
            continue;
        }

        isfsPrint(ISFS_DEBUG_INFO, "Inode entry %d\n", count);
        isfsPrint(ISFS_DEBUG_INFO, "Name: ");
        for (charCount = 0; charCount < ISFS_INODE_NAMELEN; charCount++) {
            if (inode_p->name[charCount] == '\0') {
                isfsPrint(ISFS_DEBUG_INFO, "@");
            } else {
                isfsPrint(ISFS_DEBUG_INFO, "%c", inode_p->name[charCount]);
            }
        }
        isfsPrint(ISFS_DEBUG_INFO, "\n");
        isfsPrint(ISFS_DEBUG_INFO, "Type: 0x%x\n", inode_p->typeAcc);
        isfsPrint(ISFS_DEBUG_INFO, "Addr: 0x%x\n", inode_p->addr.block);
        isfsPrint(ISFS_DEBUG_INFO, "Sibling: 0x%x\n", inode_p->nextSibling);
        isfsPrint(ISFS_DEBUG_INFO, "Size: %d KB\n", (inode_p->size / 1024));
        isfsPrint(ISFS_DEBUG_INFO, "Owner: %d\n", inode_p->owner);
        isfsPrint(ISFS_DEBUG_INFO, "Group: %d\n", inode_p->group);
        isfsPrint(ISFS_DEBUG_INFO, "Version: %d\n", inode_p->version);

        /* Print file block list */
        if (ISFS_INODE_TYPE_ISFILE(inode_p->typeAcc)) {
            u32     block = inode_p->addr.block;

            isfsPrint(ISFS_DEBUG_INFO, "File block list: %d ", block);
            while (block !=  ISFS_BLOCK_LAST) {
                block = ISFS_FAT_BLOCK_ARRAY(fatp)[block];
                isfsPrint(ISFS_DEBUG_INFO, "%d ", block);
            }
            isfsPrint(ISFS_DEBUG_INFO, "\n");
        }
    }

isisfsPrintFat_out:

    ISFS_EXIT();

    return;
}
