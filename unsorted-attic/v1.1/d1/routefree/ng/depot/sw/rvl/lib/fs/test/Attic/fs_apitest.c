d69 1
a69 1
    u32             count, num, attr, ownerAcc, groupAcc, othersAcc, iter;
d122 1
d182 2
a183 2
    for (count = 0; count < (1 << cap->pageSzShift); count++) {
        if (dataBuf[count] != ((count * 223) + 987) >> 2) {
