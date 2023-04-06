d44 3
d57 1
a57 2
    /* can only load heapSize/16KB blocks */
    fsret = osBbFStat(fd, &fsStat, blkList, heapSize>>14);
d155 2
a156 1

d161 1
a161 1
    fsret = osBbFStat(fd, &fsStat, blkList, heapSize>>14);
d166 3
d175 3
a177 1
        message("Calling skLaunchData.\n");
