a1924 2
            u32 len = strnlen(ISFS_FAT_INODE_ARRAY(fatp)[childINum].name,
                              ISFS_INODE_NAMELEN);
d1926 7
a1932 3
                    ISFS_INODE_NAMELEN);
            nameList[len] = '\0';
            nameList += len + 1;
