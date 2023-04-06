d140 2
a141 2
        rc = isfsCreateFile(IOS_ROOT_ID, IOS_ROOT_GROUP, dstName, IOS_ROOT_ID,
                        IOS_ROOT_GROUP, 0x0, ISFS_RW_ACCESS, 0x0, 0x0);
a357 7
#ifdef MEM_ALLOC
    IOS_Free(__parentSrcBuff);
    IOS_Free(__parentDstBuff);
    IOS_Free(__childSrcBuff);
    IOS_Free(__childDstBuff);
#endif

