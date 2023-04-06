d60 1
a60 1
#define ISFS_ERROR_BADFD            -111    /* Invalid file descriptor */
d87 3
d127 1
a127 1
/* ISFS_InitLib buffer size */
a131 3
ISFSError ISFS_InitLib(void *buf);
ISFSError ISFS_CloseLib(void);

d136 2
a137 2
ISFSError ISFS_CreateDir(const u8 *dname, IOSUid ownerId, IOSGid groupId,
    u32 dirAttr, u32 ownerAcc, u32 groupAcc, u32 othersAcc);
d141 2
a142 2
ISFSError ISFS_SetAttr(const u8 *name, IOSGid groupId, u32 attr, u32 ownerAcc,
    u32 groupAcc, u32 othersAcc);
d151 2
a152 2
ISFSError ISFS_CreateFile(const u8 *fname, IOSUid ownerId, IOSGid groupId,
    u32 fileAttr, u32 ownerAcc, u32 groupAcc, u32 othersAcc);
