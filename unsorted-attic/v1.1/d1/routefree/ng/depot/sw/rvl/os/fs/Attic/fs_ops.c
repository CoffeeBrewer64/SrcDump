a21 1
#include "sc/fs_ops.h"
a29 1
#include "fs_ops.h"
d32 1
d36 1
a51 5
 * Maximum directory tree depth
 */
#define ISFS_MAX_DIRTREE_DEPTH      8

/*
d499 1
a499 1
 *      ISFS_ERROR_BADFD - Matching fd entry found
d516 1
a516 1
            rc = ISFS_ERROR_BADFD;
d810 1
a810 1
 *      ISFS_ERROR_BADFD - Open file descriptor exists
d835 1
a835 1
                        rc = ISFS_ERROR_BADFD;
d1672 2
a1673 2
 *      owner - ID for checking access control
 *      group - Group ID for checking access control
a1674 2
 *      ownerId - Owner ID of the directory
 *      groupId - Group ID of the directory
d1695 2
a1696 3
isfsCreateDir(IOSUid owner, IOSGid group, const u8 *dirname,
            IOSUid ownerId, IOSGid groupId, u32 dirAttr, u32 ownerAcc,
            u32 groupAcc, u32 othersAcc)
a1739 9
    /* Only root can create directories with non-self owner ID */
    if ((owner != IOS_ROOT_ID) && (owner != ownerId)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Non-root applications can not create"
                            " directories with non-self owner ID\n");

        rc = ISFS_ERROR_ACCESS;
        goto isfsCreateDir_out;
    }

d1811 2
a1812 2
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner = ownerId;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].group = groupId;
d1867 1
a1867 1
    u32         iNum, childINum, count, realNum;
d1911 1
a1911 14
    /* Count the number of files or directories */
    realNum = 0;
    childINum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.child;
    while (childINum != ISFS_INODENUM_INVALID) {
        realNum++;
        childINum = ISFS_FAT_INODE_ARRAY(fatp)[childINum].nextSibling;
    }

    if (nameList && (realNum > *num)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Read directory buffer not large enough,"
                            " real:%d, input:%d\n", realNum, *num);
        rc = ISFS_ERROR_INVALID;
        goto isfsReadDir_out;
    }
d1913 1
a1913 1
        *num = realNum;
d1917 6
a1922 2
    if (nameList) {
        childINum = ISFS_FAT_INODE_ARRAY(fatp)[iNum].addr.child;
d1924 1
a1924 1
        for (count = 0; count < *num; count++) {
d1933 1
d1935 1
a1935 2
            childINum = ISFS_FAT_INODE_ARRAY(fatp)[childINum].nextSibling;
        }
d1955 1
d1974 2
a1975 2
isfsSetAttr(IOSUid owner, const u8 *name, IOSGid groupId, u32 attr,
    u32 ownerAcc, u32 groupAcc, u32 othersAcc)
d2014 1
a2014 1
    /* Verify the access rights */
a2018 1

d2023 25
d2049 1
d2634 2
a2635 2
 *      owner - ID for checking access control
 *      group - ID for checking access control
a2636 2
 *      ownerId - Owner ID of the file
 *      groupId - Group ID of the file
d2656 3
a2658 4
isfsCreateFile(IOSUid owner, IOSGid group, const u8 *fname,
            IOSUid ownerId, IOSGid groupId, u32 fileAttr, u32 ownerAcc,
            u32 groupAcc, u32 othersAcc)
{
a2686 9
    /* Only root can create files with non-self owner ID */
    if ((owner != IOS_ROOT_ID) && (owner != ownerId)) {
        isfsPrint(ISFS_DEBUG_ERROR, "Non-root applications can not create files"
                            " with non-self owner ID\n");

        rc = ISFS_ERROR_ACCESS;
        goto isfsCreateFile_out;
    }

d2758 2
a2759 2
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].owner = ownerId;
    ISFS_FAT_INODE_ARRAY(fatp)[iNum].group = groupId;
