a76 6
#ifdef NAPA_WORKAROUND
#define ISFS_MAXFILES_INDIR     256
static u8               __isfsNameListBuf[ISFS_MAXFILES_INDIR *             \
                                    (ISFS_INODE_NAMELEN + 4)];
#endif

a1867 3
#ifdef NAPA_WORKAROUND
    u8          *ptr = __isfsNameListBuf;
#endif
a1924 15
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
a1932 1
#endif
a1937 12
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

a2181 7
#ifdef NAPA_WORKAROUND
    u32     word;

    word = ISFS_FAT_INODE_ARRAY(fatp)[iNum].group;
    word <<= 16;
    *((u32 *)groupId) = word;
#else
a2182 1
#endif
