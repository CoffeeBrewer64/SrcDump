d69 1
a69 1
    u32             count, num, attr, ownerAcc, groupAcc, othersAcc, iter, pgSz;
d74 1
a74 1
    FLDevCap        *cap;
d119 2
a123 1
    pgSz = (1 << cap->pageSzShift);
d183 2
a184 2
    for (count = 0; count < pgSz; count++) {
        if (dataBuf[count] != (u8) (((count * 223) + 987) >> 2)) {
d293 1
a293 1
        if (buf[count] != (u8) (((count * 362) + 118) >> 3)) {
