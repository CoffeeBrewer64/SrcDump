d65 1
d68 1
a358 1
#ifdef MEM_ALLOC
a364 1
#endif
d444 1
a444 2
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/sys", IOS_ROOT_ID,
                IOS_ROOT_GROUP, 0, 0, 0, 0);
d451 2
a452 2
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/title", IOS_ROOT_ID,
                IOS_ROOT_GROUP, 0, 0, 0, ISFS_READ_ACCESS);
d459 2
a460 2
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/tmp", IOS_ROOT_ID,
                IOS_ROOT_GROUP, 0, 0, 0, ISFS_RW_ACCESS);
d467 8
a474 1
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/title/0", IOS_TITLE_0_ID,
d477 1
a477 1
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/0,"
d483 8
a490 1
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/title/1", IOS_TITLE_1_ID,
d493 1
a493 1
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to create dir /title/1,"
d500 1
a500 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d509 1
a509 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d518 1
a518 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d527 1
a527 2
    rc = isfsCreateDir(IOS_ROOT_ID, IOS_ROOT_GROUP, "/sys", IOS_ROOT_ID,
                IOS_ROOT_GROUP, 0, 0, 0, 0);
d539 1
a539 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d541 2
a542 3
        isfsPrint(ISFS_DEBUG_ERROR, "Failed to detect access violation, rc=%d\n",
                            rc);

d549 1
a549 2
    rc = isfsCreateFile(IOS_ROOT_ID, IOS_ROOT_GROUP, "/test.ab", IOS_ROOT_ID,
                IOS_ROOT_GROUP, 0, 0, 0, 0);
d594 1
a594 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, 0, 0, 0);
d602 2
a603 2
    rc = isfsSetAttr(IOS_TITLE_0_ID, "/title/0/testattr", IOS_ROOT_GROUP, 0x3,
                ISFS_RW_ACCESS, ISFS_READ_ACCESS, 0);
d670 10
a679 3
    /* Only root can create a file or directory with non-self owner ID */
    rc = isfsCreateDir(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/exec",
                IOS_TITLE_1_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d681 1
a681 1
        isfsPrint(ISFS_DEBUG_ERROR, "Directory creation with non-self owner ID"
a687 1
    rc = ISFS_ERROR_OK;
d689 9
a697 2
    rc = isfsCreateFile(IOS_TITLE_0_ID, IOS_TITLE_GROUP, "/tmp/map.dat",
                IOS_TITLE_1_ID, IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0, 0);
a705 1
    rc = ISFS_ERROR_OK;
d709 1
a709 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d718 1
a718 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0, 0);
d736 1
a736 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0, 0);
d950 1
a950 1
    if (rc != ISFS_ERROR_BADFD) {
d976 1
a976 2
                    "/title/0/exec/longfile.name", IOS_TITLE_0_ID,
                    IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0x0, 0x0);
d996 1
a996 1
                    IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0, 0);
d1005 1
a1005 1
                    IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0, 0);
d1070 1
a1070 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0x0, ISFS_RW_ACCESS, 0, 0);
d1141 1
a1141 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
d1159 1
a1159 1
                IOS_TITLE_0_ID, IOS_TITLE_GROUP, 0, ISFS_RW_ACCESS, 0, 0);
