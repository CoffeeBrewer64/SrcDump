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
 *      This file implements the functions to encrypt, authenticate, and
 *      read/write/copy data aligned on FS block boundaries. A write to
 *      the first FS block in a flash block implies an erase operation
 *
 */


#ifdef NET_CARD
#include <sc/libc.h>
#include <sc/iostypes.h>
#include <sc/sc.h>
#include <sc/ios.h>
#include <sc/iosc.h>
#include <sc/fs.h>
#include <sc/flash.h>

#include "sc/fl_ops.h"
#else
#include <ioslibc.h>
#include <iostypes.h>
#include <iop.h>
#include <ios.h>
#ifndef ISFS_DISABLE_SECURITY
#include <iosc.h>
#endif
#include <fs.h>
#include <flash.h>

#include "fl_ops.h"
#endif

#include "fs_utils.h"
#include "fs_block.h"


/*
 * Global variable used for storing flash capabilities,
 * which is needed throughout the file system to determine
 * the value of certain FS block level macros
 */
FLDevCap        __isfsFlashCap;

/* Buffer used for encryption/decryption/authentication of data */
static u8       __isfsBlock[ISFS_BLOCK_SIZE]
                    __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));
static u8       *__isfsBlockp = NULL;
#ifndef ISFS_DISABLE_SECURITY
static u8       __isfsIV[ISFS_IV_LEN]
                    __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));
#endif


#ifndef ISFS_DISABLE_SECURITY
static void     __isfsComputeCustomIV(ISFSCustomData *, u8 *);
#endif


#ifndef ISFS_DISABLE_SECURITY
/*
 *  Function: __isfsComputeCustomIV
 *
 *  Description:
 *      Compute IV from custom data for encryption
 *
 *  Inputs:
 *      customData - Custom data
 *
 *  Outputs:
 *      iv - 16-byte IV computed from the custom data
 *
 *  Return values:
 *      None
 *
 */
static void
__isfsComputeCustomIV(ISFSCustomData *customData, u8 *iv)
{
    u32     count, sz, index;
    u8      *byteArray;

    sz = sizeof (ISFSCustomData);

    /* Generate IV based on custom data */
    byteArray = (u8 *) customData;
    for (count = 0; count < ISFS_IV_LEN; count++) {
        index = count;

        while (index < sz) {
            iv[count] = byteArray[index];
            index += ISFS_IV_LEN;
        }
    }
}
#endif


/*
 *  Function: isfsInitFsBlocks
 *
 *  Description:
 *      Initialize the FS block writing/reading module
 *
 *  Inputs:
 *      init - 1 to initialize, 0 to de-initialize
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 */
ISFSError
isfsInitFsBlocks(int init)
{
    ISFSError   rc = ISFS_ERROR_OK;
    IOSError    ret;

    ISFS_ENTRY();

    /* Get capabilities from the flash device driver */
    if (init) {
        ret = flGetCap(&__isfsFlashCap);
        if (ret != IOS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_ERROR, "Failed to get flash capabilities %d\n",
                                ret);

            rc = ISFS_ERROR_UNKNOWN;
            goto isfsInitFsBlocks_out;
        }

        __isfsBlockp = __isfsBlock;
    } else {
        __isfsBlockp = NULL;
    }

isfsInitFsBlocks_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsReadFsBlocks
 *
 *  Description:
 *      Read a number of FS blocks from the flash. Options are provided
 *      to specify whether the FS blocks need to be decrypted or
 *      authenticated
 *
 *  Inputs:
 *      fsBlockIndex - Starting index to read from
 *      numBlocks - The number of FS blocks to read
 *      flags - Encryption and authentication
 *      customData - Custom data for authentication and IV for encryption
 *
 *  Outputs:
 *      buf - Read buffer, size is numBlocks * 16KB
 *      spare - Spare data, size is numBlocks * 64B, NULL if auth
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - FS block module not initialized
 *      ISFS_ERROR_ECC - Single-bit ECC error is detected and corrected
 *      ISFS_ERROR_ECC_CRIT - Multi-bit ECC error is detected
 *      ISFS_ERROR_AUTH_VIOL - Authentication failed
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 */
ISFSError
isfsReadFsBlocks(ISFSBlockEntry fsBlockIndex, u32 numBlocks, u32 flags,
            ISFSCustomData *customData, u8 *buf, u8 *spare)
{
    ISFSError       rc = ISFS_ERROR_OK;
    IOSError        ret;
    u32             count;
    u8              spareBuf[FL_VIRT_SPARE_SIZE];
#ifndef ISFS_DISABLE_SECURITY
    u8              mac[ISFS_MAC_LEN];
    IOSCHashContext hashCtx;
#endif

    ISFS_ENTRY();

    if (__isfsBlockp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "FS block module not initialized\n");
        rc = ISFS_ERROR_NOTREADY;
        goto isfsReadFsBlocks_out;
    }

    if (((fsBlockIndex + numBlocks) > ISFS_BLOCK_ENTRIES) ||
            (buf == NULL) ||
            (!(flags & ISFS_BLOCK_OP_AUTH) && (spare == NULL)) ||
            ((flags != 0) && (customData == NULL))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters %d, %d, 0x%x,"
                            " 0x%x, 0x%x, 0x%x\n", fsBlockIndex, numBlocks,
                            flags, (u32) customData, (u32) buf, (u32) spare);
        rc = ISFS_ERROR_INVALID;
        goto isfsReadFsBlocks_out;
    }

    for (count = 0; count < numBlocks; count++) {
        u8      *datap = NULL;

#ifndef ISFS_DISABLE_SECURITY
        if (flags & ISFS_BLOCK_OP_ENCRYPTION) {
            datap = __isfsBlockp;
        } else {
            datap = (buf + (count * ISFS_BLOCK_SIZE));
        }
#else
        datap = (buf + (count * ISFS_BLOCK_SIZE));
#endif

        /* Read one FS block at a time */
        ret = flRead(fsBlockIndex + count, datap, spareBuf);
        if (ret != IOS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_DEBUG, "An error occurred while reading"
                            " FS block %d, rc=%d\n", fsBlockIndex + count, ret);

            if ((ret == IOS_ERROR_ECC) && (rc != ISFS_ERROR_ECC_CRIT)) {
                rc = ISFS_ERROR_ECC;
            } else if (ret == IOS_ERROR_ECC_CRIT) {
                rc = ISFS_ERROR_ECC_CRIT;
                goto isfsReadFsBlocks_out;
            } else {
                rc = ISFS_ERROR_UNKNOWN;
                goto isfsReadFsBlocks_out;
            }
        }

#ifndef ISFS_DISABLE_SECURITY
        /* TODO: Test HW crypto and enable security */
        /* TODO: Change to use crypto async APIs */

        if (flags & ISFS_BLOCK_OP_ENCRYPTION) {
            /*
             * If the chain bit is set, only compute a new IV for
             * the first block
             */
            if (!(flags & ISFS_BLOCK_OP_CHAIN) || (count == 0)) {
                __isfsComputeCustomIV(customData, __isfsIV);
            }

            ret = IOSC_Decrypt(IOSC_FS_ENC_HANDLE, __isfsIV, datap,
                    ISFS_BLOCK_SIZE, buf + (count * ISFS_BLOCK_SIZE));
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while"
                   " decrypting block %d, rc=%d\n", fsBlockIndex + count, ret);
                rc = ret;
                goto isfsReadFsBlocks_out;
            }
        }

        if (flags & ISFS_BLOCK_OP_AUTH) {
            u32     chainFlag;

            if ((flags & ISFS_BLOCK_OP_CHAIN) && (count != 0)) {
                chainFlag = IOSC_MAC_MIDDLE;
            } else {
                chainFlag = IOSC_MAC_FIRST;
            }

            ret = IOSC_GenerateBlockMAC(hashCtx,
                        (u8 *) buf+(count*ISFS_BLOCK_SIZE), ISFS_BLOCK_SIZE,
                        (u8 *) customData, sizeof (ISFSCustomData),
                        IOSC_FS_MAC_HANDLE, chainFlag, mac);
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while signing"
                            " block %d, rc=%d\n", fsBlockIndex + count, ret);
                rc = ret;
                goto isfsReadFsBlocks_out;
            }

            if (!(flags & ISFS_BLOCK_OP_CHAIN) || (count == (numBlocks - 1))) {
                ret = IOSC_GenerateBlockMAC(hashCtx, NULL, 0, NULL, 0,
                        IOSC_FS_MAC_HANDLE, IOSC_MAC_LAST, mac);
                if (ret != IOS_ERROR_OK) {
                    isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while"
                                            " finishing block %d, rc=%d\n",
                                            fsBlockIndex + count, ret);
                    rc = ret;
                    goto isfsReadFsBlocks_out;
                }

                if (memcmp(mac, spareBuf, ISFS_MAC_LEN) != 0) {
                    /* Try again using the second copy of HMAC */
                    if (memcmp(mac, spareBuf + ISFS_MAC_LEN,
                            ISFS_MAC_LEN) != 0) {
                        isfsPrint(ISFS_DEBUG_ERROR, "Failed to verify HMAC"
                            " while reading block %d\n", fsBlockIndex + count);
                        rc = ISFS_ERROR_HMAC;
                        goto isfsReadFsBlocks_out;
                    } else {
                        /* Force this block to be re-written */
                        rc = ISFS_ERROR_ECC;
                    }
                }
            }
        } else {
            memcpy(spare + (count * FL_VIRT_SPARE_SIZE), spareBuf,
                FL_VIRT_SPARE_SIZE);
        }

        if (flags != 0) {
            /* Increment block offset by 1 for each block */
            customData->blockOffset++;
        }
#else
        if (!(flags & ISFS_BLOCK_OP_AUTH)) {
            memcpy(spare + (count * FL_VIRT_SPARE_SIZE), spareBuf,
                FL_VIRT_SPARE_SIZE);
        }
#endif
    }

isfsReadFsBlocks_out:

    if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_ECC)) {
        /*
         * Wipe out the read buffer to prevent caller from using
         * the invalid data
         */
        memset(buf, 0, numBlocks * ISFS_BLOCK_SIZE);
    }

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsWriteFsBlocks
 *
 *  Description:
 *      Write a number of FS blocks to the flash. Options are provided
 *      to specify whether the FS blocks need to be encrypted or
 *      authenticated. Since pages in the same physical flash block need
 *      to be programmed in sequential incrementing order, a write to
 *      the first page in a physical flash block implies an erase to
 *      the block
 *
 *  Inputs:
 *      fsBlockIndex - Starting index to write to 
 *      numBlocks - The number of FS blocks to be written
 *      flags - Encryption and authentication
 *      customData - Custom data for authentication, NULL if no authentication
 *      buf - Write buffer, size is numBlocks * 16KB
 *      spare - Spare data, size is numBlocks * 64B, NULL if auth
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - FS block module not initialized
 *      ISFS_ERROR_BADBLOCK - Bad block status is detected
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 *  Notes:
 *      It is recommended not to cross flash block boundaries when
 *      writing multiple FS blocks in one call, otherwise there is no
 *      no way to tell which flash block is bad when ISFS_ERROR_BADBLOCK
 *      is returned
 *
 */
ISFSError
isfsWriteFsBlocks(ISFSBlockEntry fsBlockIndex, u32 numBlocks, u32 flags,
            ISFSCustomData *customData, const u8 *buf, const u8 *spare)
{
    ISFSError       rc = ISFS_ERROR_OK;
    IOSError        ret;
    u32             count;
    u8              spareBuf[FL_VIRT_SPARE_SIZE];
#ifndef ISFS_DISABLE_SECURITY
    IOSCHashContext hashCtx;
#endif

    ISFS_ENTRY();

    if (__isfsBlockp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "FS block module not initialized\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsWriteFsBlocks_out;
    }

    if (((fsBlockIndex + numBlocks) > ISFS_BLOCK_ENTRIES) ||
            (buf == NULL) ||
            (!(flags & ISFS_BLOCK_OP_AUTH) && (spare == NULL)) ||
            ((flags != 0) && (customData == NULL))) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters %d, %d, 0x%x, %d,"
                            " %d, 0x%x, 0x%x\n", fsBlockIndex, numBlocks,
                            flags, (u32) customData, (u32) buf, (u32) spare);
        rc = ISFS_ERROR_INVALID;
        goto isfsWriteFsBlocks_out;
    }

    for (count = 0; count < numBlocks; count++) {
        const u8        *datap = NULL;

#ifndef ISFS_DISABLE_SECURITY
        if (flags & ISFS_BLOCK_OP_AUTH) {
            u32     chainFlag;

            if ((flags & ISFS_BLOCK_OP_CHAIN) && (count != 0)) {
                chainFlag = IOSC_MAC_MIDDLE;
            } else {
                chainFlag = IOSC_MAC_FIRST;
            }

            ret = IOSC_GenerateBlockMAC(hashCtx,
                        (u8 *) (buf+(count*ISFS_BLOCK_SIZE)), ISFS_BLOCK_SIZE,
                        (u8 *) customData, sizeof (ISFSCustomData),
                        IOSC_FS_MAC_HANDLE, chainFlag, spareBuf);
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while signing"
                            " block %d, rc=%d\n", fsBlockIndex + count, ret);
                rc = ret;
                goto isfsWriteFsBlocks_out;
            }

            if (!(flags & ISFS_BLOCK_OP_CHAIN) || (count == (numBlocks - 1))) {
                ret = IOSC_GenerateBlockMAC(hashCtx, NULL, 0, NULL, 0,
                        IOSC_FS_MAC_HANDLE, IOSC_MAC_LAST, spareBuf);
                if (ret != IOS_ERROR_OK) {
                    isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while"
                                            " finishing block %d, rc=%d\n",
                                            fsBlockIndex + count, ret);
                    rc = ret;
                    goto isfsWriteFsBlocks_out;
                }

                /* Make another copy of the HMAC */
                memcpy(spareBuf + ISFS_MAC_LEN, spareBuf, ISFS_MAC_LEN);
            }
        } else {
            memcpy(spareBuf, spare + (count * FL_VIRT_SPARE_SIZE),
                FL_VIRT_SPARE_SIZE);
        }

        if (flags & ISFS_BLOCK_OP_ENCRYPTION) {
            /*
             * If the chain bit is set, only compute a new IV for
             * the first block
             */
            if (!(flags & ISFS_BLOCK_OP_CHAIN) || (count == 0)) {
                __isfsComputeCustomIV(customData, __isfsIV);
            }

            ret = IOSC_Encrypt(IOSC_FS_ENC_HANDLE, __isfsIV,
                            (u8 *) buf + (count * ISFS_BLOCK_SIZE),
                            ISFS_BLOCK_SIZE, __isfsBlockp);
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while"
                    " encrypting block %d, rc=%d\n", fsBlockIndex + count, ret);
                rc = ret;
                goto isfsWriteFsBlocks_out;
            }

            datap = __isfsBlockp;
        } else {
            datap = (buf + (count * ISFS_BLOCK_SIZE));
        }

        if (flags != 0) {
            /* Increment block offset by 1 for each block */
            customData->blockOffset++;
        }
#else
        if (!(flags & ISFS_BLOCK_OP_AUTH)) {
            memcpy(spareBuf, spare + (count * FL_VIRT_SPARE_SIZE),
                FL_VIRT_SPARE_SIZE);
        }

        datap = (buf + (count * ISFS_BLOCK_SIZE));
#endif

        if (((fsBlockIndex + count) & (ISFS_BLOCKS_IN_FL_BLOCK - 1)) == 0) {
            ret = flErase(fsBlockIndex + count);
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_WARN, "An error occurred while erasing"
                    " FS block %d, rc=%d\n", fsBlockIndex + count, ret);

                if (ret == IOS_ERROR_BADBLOCK) {
                    rc = ISFS_ERROR_BADBLOCK;
                } else {
                    rc = ret;
                }

                goto isfsWriteFsBlocks_out;
            }
        }

        /* Write FS block one at a time */
        ret = flWrite(fsBlockIndex + count, datap, spareBuf);
        if (ret != IOS_ERROR_OK) {
            isfsPrint(ISFS_DEBUG_WARN, "An error occurred while writing"
                " FS block %d, rc=%d\n", fsBlockIndex + count, ret);

            if (ret == IOS_ERROR_BADBLOCK) {
                rc = ISFS_ERROR_BADBLOCK;
            } else {
                rc = ret;
            }

            goto isfsWriteFsBlocks_out;
        }
    }

isfsWriteFsBlocks_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsCopyFsBlocks
 *
 *  Description:
 *      Copy a number of FS blocks within the flash. Since pages in
 *      the same physical flash block need to be programmed in
 *      sequential incrementing order, a write to the first page in
 *      physical flash block implies an erase to the block
 *      the block
 *
 *  Inputs:
 *      src - Starting index of the source blocks
 *      dst - Starting index of the destination blocks
 *      numBlocks - Number of blocks to copy
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - Operation is successful
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - FS block module not initialized
 *      ISFS_ERROR_BADBLOCK - Bad block status is detected
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 *  Notes:
 *      It is recommended not to cross flash block boundaries when
 *      copying multiple FS blocks in one call, otherwise there is no
 *      no way to tell which flash block is bad when ISFS_ERROR_BADBLOCK
 *      is returned
 *
 */
ISFSError
isfsCopyFsBlocks(ISFSBlockEntry src, ISFSBlockEntry dst, u32 numBlocks)
{
    ISFSError   rc = ISFS_ERROR_OK;
    IOSError    ret;
    u32         count, srcPlane, dstPlane;
    u8          spareBuf[FL_VIRT_SPARE_SIZE];

    ISFS_ENTRY();

    if (__isfsBlockp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "FS block module not initialized\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsCopyFsBlocks_out;
    }

    if (((src + numBlocks) > ISFS_BLOCK_ENTRIES) ||
            ((dst + numBlocks) > ISFS_BLOCK_ENTRIES)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameters %d, %d, %d\n",
                            src, dst, numBlocks);

        rc = ISFS_ERROR_INVALID;
        goto isfsCopyFsBlocks_out;
    }

    /*
     * If the flash does not support copy, or if the blocks to be copied
     * are not in the same plane, use read and then write instead
     */
    srcPlane = (src >> ISFS_BLOCKS_IN_FL_BLOCK_SHIFT) &
                            (__isfsFlashCap.numPlanes - 1);
    dstPlane = (dst >> ISFS_BLOCKS_IN_FL_BLOCK_SHIFT) &
                            (__isfsFlashCap.numPlanes - 1);
    if (!__isfsFlashCap.supportCopy || (srcPlane != dstPlane)) {
        for (count = 0; count < numBlocks; count++) {
            /*
             * Ignore ECC errors while copying since single-bit error
             * has already been corrected and nothing can be done for
             * multi-bit errors anyways
             */
            ret = flRead(src + count, __isfsBlockp, spareBuf);
            if ((ret != IOS_ERROR_OK) && (ret != IOS_ERROR_ECC) &&
                    (ret != IOS_ERROR_ECC_CRIT)) {
                isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while reading"
                                " FS block %d, rc=%d\n", (src + count), ret);

                rc = ISFS_ERROR_UNKNOWN;
                goto isfsCopyFsBlocks_out;
            }

            if (((dst + count) & (ISFS_BLOCKS_IN_FL_BLOCK - 1)) == 0) {
                ret = flErase(dst + count);
                if (ret != IOS_ERROR_OK) {
                    isfsPrint(ISFS_DEBUG_WARN, "An error occurred while erasing"
                                " FS block %d, rc=%d\n", (dst + count), ret);

                    if (ret == IOS_ERROR_BADBLOCK) {
                        rc = ISFS_ERROR_BADBLOCK;
                    } else {
                        rc = ISFS_ERROR_UNKNOWN;
                    }

                    goto isfsCopyFsBlocks_out;
                }
            }

            ret = flWrite(dst + count, __isfsBlockp, spareBuf);
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_WARN, "An error occurred while writing"
                                " FS block %d, rc=%d\n", (dst + count), ret);

                if (ret == IOS_ERROR_BADBLOCK) {
                    rc = ISFS_ERROR_BADBLOCK;
                } else {
                    rc = ISFS_ERROR_UNKNOWN;
                }

                goto isfsCopyFsBlocks_out;
            }
        }
    } else {
        for (count = 0; count < numBlocks; count++) {
            if (((dst + count) & (ISFS_BLOCKS_IN_FL_BLOCK - 1)) == 0) {
                ret = flErase(dst + count);
                if (ret != IOS_ERROR_OK) {
                    isfsPrint(ISFS_DEBUG_WARN, "An error occurred while erasing"
                                " FS block %d, rc=%d\n", (dst + count), ret);

                    if (ret == IOS_ERROR_BADBLOCK) {
                        rc = ISFS_ERROR_BADBLOCK;
                    } else {
                        rc = ISFS_ERROR_UNKNOWN;
                    }

                    goto isfsCopyFsBlocks_out;
                }
            }

            /* Copy FS block one at a time */
            ret = flCopy(src + count, dst + count);
            if (ret != IOS_ERROR_OK) {
                isfsPrint(ISFS_DEBUG_WARN, "An error occurred while copying FS"
                            " block %d to FS block %d, rc=%d\n", (src + count),
                            (dst + count), ret);

                if (ret == IOS_ERROR_BADBLOCK) {
                    rc = ISFS_ERROR_BADBLOCK;
                } else {
                    rc = ISFS_ERROR_UNKNOWN;
                }

                goto isfsCopyFsBlocks_out;
            }
        }
    }

isfsCopyFsBlocks_out:

    ISFS_EXIT();

    return (rc);
}


/*
 *  Function: isfsStatusFsBlock
 *
 *  Description:
 *      Retrieves the status of the flash block where the specified
 *      FS block belongs
 *
 *  Inputs:
 *      fsBlockIndex - Index of the FS block
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      ISFS_ERROR_OK - The flash block is good
 *      ISFS_ERROR_INVALID - Invalid input parameters
 *      ISFS_ERROR_NOTREADY - FS block module not initialized
 *      ISFS_ERROR_BADBLOCK - The flash block is bad
 *      ISFS_ERROR_UNKNOWN - Unknown error
 *
 */
ISFSError
isfsStatusFsBlock(ISFSBlockEntry fsBlockIndex)
{
    ISFSError   rc = ISFS_ERROR_OK;
    IOSError    ret;

    ISFS_ENTRY();

    if (__isfsBlockp == NULL) {
        isfsPrint(ISFS_DEBUG_ERROR, "FS block module not initialized\n");

        rc = ISFS_ERROR_NOTREADY;
        goto isfsStatusFsBlocks_out;
    }

    if (fsBlockIndex >= ISFS_BLOCK_ENTRIES) {
        isfsPrint(ISFS_DEBUG_ERROR, "Invalid input parameter %d\n",
                                fsBlockIndex);

        rc = ISFS_ERROR_INVALID;
        goto isfsStatusFsBlocks_out;
    }

    ret = flStatus(fsBlockIndex);
    if (ret == IOS_ERROR_BADBLOCK) {
        rc = ISFS_ERROR_BADBLOCK;
    } else if (ret != IOS_ERROR_OK) {
        isfsPrint(ISFS_DEBUG_ERROR, "An error occurred while retrieving"
                            " status, rc=%d\n", ret);

        rc = ISFS_ERROR_UNKNOWN;
    }

isfsStatusFsBlocks_out:

    ISFS_EXIT();

    return (rc);
}
