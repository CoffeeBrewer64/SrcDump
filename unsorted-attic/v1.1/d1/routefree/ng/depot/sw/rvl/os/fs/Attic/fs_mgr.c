a43 1

d86 1
d180 1
d199 5
a203 1
            if (size != totalPageSz) {
d208 1
a208 2
            rc = flReadPage(ctx->pageOffset, argsRead->outPtr,
                        argsRead->outPtr + (1 << cap.pageSzShift));
d211 1
a211 1
                rc = totalPageSz;
d220 5
a224 1
            if (size != totalPageSz) {
d229 1
a229 2
            rc = flWritePage(ctx->pageOffset, argsWrite->inPtr,
                        argsWrite->inPtr + (1 << cap.pageSzShift), 0, 1);
d232 1
a232 1
                rc = totalPageSz;
d274 17
a290 3
            if (argsIoctl->cmd == FL_GETCAP) {
                if (size < sizeof (FLDevCap)) {
                    rc = IOS_ERROR_INVALID;
a291 1
                }
d293 3
a295 4
                memcpy(argsIoctl->outPtr, &cap, sizeof (FLDevCap));
            } else if (argsIoctl->cmd == FL_GETSTATS) {
                if (size < sizeof (FLStats)) {
                    rc = IOS_ERROR_INVALID;
a296 1
                }
d298 2
a299 3
                rc = flGetStats((FLStats *) argsIoctl->outPtr);
            } else if (argsIoctl->cmd == FL_ERASE) {
                rc = flErase(ctx->pageOffset >>
d301 7
a307 2
            } else {
                rc = IOS_ERROR_INVALID;
d482 3
a484 1
                (size >= ISFS_BLOCK_SIZE)) {
d631 3
a633 1
                (size >= ISFS_BLOCK_SIZE)) {
d822 1
a822 2
                    pathAttrArgs->path, pathAttrArgs->ownerId,
                    pathAttrArgs->groupId, pathAttrArgs->attr,
a827 26
        case (ISFS_DREAD):
            if (args->outLen < 4) {
                rc = ISFS_ERROR_INVALID;
            } else if (args->outLen == 4) {
                if (args->inLen < ISFS_PATH_MAXLEN) {
                    rc = ISFS_ERROR_INVALID;
                    break;
                }

                rc = isfsReadDir(entry->uid, entry->gid, args->inPtr,
                            NULL, (u32 *) args->outPtr);
            } else {
                u32 *num = (u32 *) (args->inPtr + ISFS_PATH_MAXLEN);

                if ((args->inLen < (ISFS_PATH_MAXLEN + 4)) ||
                        (args->outLen < (*num * (ISFS_INODE_NAMELEN + 1)))) {
                    rc = ISFS_ERROR_INVALID;
                    break;
                }

                rc = isfsReadDir(entry->uid, entry->gid, args->inPtr,
                            args->outPtr, num);
            }

            break;

d836 3
a838 3
                        pathAttrArgs->groupId, pathAttrArgs->attr,
                        pathAttrArgs->ownerAccess, pathAttrArgs->groupAccess,
                        pathAttrArgs->othersAccess);
d891 1
a891 2
                            pathAttrArgs->path, pathAttrArgs->ownerId,
                            pathAttrArgs->groupId, pathAttrArgs->attr,
d943 80
d1192 2
a1193 3
            rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP,
                        defDirs[count].dirName, defDirs[count].uid,
                        defDirs[count].gid, 0, defDirs[count].ownerAcc,
d1260 4
