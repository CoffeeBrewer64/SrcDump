d74 1
a74 1
static FLStats              flStats;
d77 1
a77 1
FLDev                       flDev;
d506 1
a506 1
            flStats.numErasesSinceInit++;
d508 1
a508 1
            flStats.numWritesSinceInit++;
d510 1
a510 1
            flStats.numReadsSinceInit++;
d512 1
a512 1
            flStats.numCopiesSinceInit++;
d517 1
a517 1
        if (flStats.failRecordNum == FL_FAILED_ENTRIES) {
d523 3
a525 3
            nextFailRecordIndex = flStats.failRecordStart;
            flStats.failRecordStart =
                    (flStats.failRecordStart + 1) &
d528 2
a529 2
            nextFailRecordIndex = flStats.failRecordStart +
                                        flStats.failRecordNum;
d531 1
a531 1
            flStats.failRecordNum++;
d534 3
a536 3
        flStats.failRecord[nextFailRecordIndex].blockIndex = blockIndex;
        flStats.failRecord[nextFailRecordIndex].opType = opType;
        flStats.failRecord[nextFailRecordIndex].reason = reason;
d577 1
a577 1
    rc = flExecCmd(flDev.cmdSet.readOpStatus, 0x0, FL_CTRL_RDP,
d832 1
a832 1
            flDev = *dev_p;
d835 5
a839 5
            flConfReg = (flDev.cfg.eoc << FL_CONF_EOC_SHIFT) | FL_CONF_DEV |
                    (flDev.cfg.rsa << FL_CONF_RSA_SHIFT) |
                    (flDev.cfg.rea << FL_CONF_REA_SHIFT) |
                    (flDev.cfg.wea << FL_CONF_WEA_SHIFT) |
                    (flDev.cfg.caa << FL_CONF_CAA_SHIFT);
d854 5
a858 5
    flStats.numErasesSinceInit = 0;
    flStats.numWritesSinceInit = 0;
    flStats.numReadsSinceInit = 0;
    flStats.failRecordStart = 0;
    flStats.failRecordNum = 0;
d932 1
a932 1
    memcpy(cap, &flDev.cap, sizeof (FLDevCap));
d980 1
a980 1
    memcpy(id, &flDev.flashID, sizeof(FLIdentifier));
d1024 1
a1024 1
        (1 << (flDev.cap.totalSzShift - flDev.cap.pageSzShift))) ||
d1040 1
a1040 1
    if ((cache) && (flDev.cmdSet.cache == FL_CMD_INVALID)) {
d1044 1
a1044 1
        program_cmd = flDev.cmdSet.cache;
d1046 1
a1046 1
        program_cmd = flDev.cmdSet.program;
d1057 1
a1057 1
        memcpy(spareBuf, spare, (1 << flDev.cap.pageSpareSzShift));
d1059 1
a1059 1
        memset(spareBuf, 0, (1 << flDev.cap.pageSpareSzShift));
d1061 1
a1061 1
    spareBuf[flDev.cap.statusByteOffset] = FL_STATUS_GOOD;
d1070 1
a1070 1
    rc = flExecCmd(flDev.cmdSet.programSetup, flDev.cmdSet.addrBytePhase,
d1072 1
a1072 1
                (1 << flDev.cap.pageSzShift));
d1082 2
a1083 2
                    (flDev.cap.pageSzShift - FL_ECC_UNIT_SHIFT);
        memcpy(&spareBuf[(1 << flDev.cap.pageSpareSzShift) - totalEccSize],
d1088 1
a1088 1
        if (flDev.cmdSet.randomInput == FL_CMD_INVALID) {
d1113 1
a1113 1
            if (flDev.cmdSet.readSpare != FL_CMD_INVALID) {
d1119 1
a1119 1
                rc = flExecCmd(flDev.cmdSet.readSpare, 0, 0, 0);
d1126 1
a1126 1
                ad0 = 1 << flDev.cap.pageSzShift;
d1136 2
a1137 2
            rc = flExecCmd(flDev.cmdSet.programSetup, 
                        flDev.cmdSet.addrBytePhase,
d1139 1
a1139 1
                        (1 << flDev.cap.pageSpareSzShift));
d1151 1
a1151 1
            flSetDevAddr((1 << flDev.cap.pageSzShift), FL_REG_ADDR_INVALID);
d1153 2
a1154 2
            rc = flExecCmd(flDev.cmdSet.randomInput,
                        flDev.cmdSet.addrBytePhase & 0x3,
d1156 1
a1156 1
                        (1 << flDev.cap.pageSpareSzShift));
d1186 2
a1187 2
    if ((spare || ecc) && (flDev.cmdSet.randomInput == FL_CMD_INVALID) &&
            (flDev.cmdSet.readSpare != FL_CMD_INVALID)) {
d1193 1
a1193 1
        rc = flExecCmd(flDev.cmdSet.read, 0, 0, 0);
d1205 1
a1205 1
                (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift)),
d1247 1
a1247 1
                (1 << (flDev.cap.totalSzShift - flDev.cap.pageSzShift))) ||
d1266 1
a1266 1
    if (flDev.cmdSet.readSetup != FL_CMD_INVALID) {
d1272 1
a1272 1
        rc = flExecCmd(flDev.cmdSet.readSetup, flDev.cmdSet.addrBytePhase,
d1281 1
a1281 1
        adp = flDev.cmdSet.addrBytePhase;
d1290 1
a1290 1
    rc = flExecCmd(flDev.cmdSet.read, adp,
d1292 2
a1293 2
                (1 << flDev.cap.pageSzShift) +
                    (1 << flDev.cap.pageSpareSzShift));
d1304 1
a1304 1
        memcpy(spare, spareBuf, (1 << flDev.cap.pageSpareSzShift));
d1313 1
a1313 1
                (flDev.cap.pageSzShift - FL_ECC_UNIT_SHIFT);
d1315 1
a1315 1
            &spareBuf[(1 << flDev.cap.pageSpareSzShift) - totalEccSize],
d1323 1
a1323 1
            (1 << (flDev.cap.pageSzShift - FL_ECC_UNIT_SHIFT));
d1331 1
a1331 1
            &spareBuf[(1 << flDev.cap.pageSpareSzShift) - totalEccSize +
d1371 1
a1371 1
                (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift)),
d1411 1
a1411 1
    maxPage = (1 << (flDev.cap.totalSzShift - flDev.cap.pageSzShift));
d1428 1
a1428 1
    if (flDev.cmdSet.readSetup != FL_CMD_INVALID) {
d1435 1
a1435 1
        rc = flExecCmd(flDev.cmdSet.readSetup, flDev.cmdSet.addrBytePhase,
d1444 1
a1444 1
        adp = flDev.cmdSet.addrBytePhase;
d1448 1
a1448 1
    read_cmd = flDev.cmdSet.readForCopy;
d1450 1
a1450 1
        read_cmd = flDev.cmdSet.read;
d1471 1
a1471 1
    rc = flExecCmd(flDev.cmdSet.copyBack, flDev.cmdSet.addrBytePhase,
d1478 1
a1478 1
    if (flDev.cmdSet.programForCopy != FL_CMD_INVALID) {
d1484 1
a1484 1
        rc = flExecCmd(flDev.cmdSet.program, 0,
d1504 1
a1504 1
                (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift)),
d1542 1
a1542 1
            (1 << (flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) {
d1563 3
a1565 3
        (blockIndex << (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift)));
    rc = flExecCmd(flDev.cmdSet.eraseSetup,
            (flDev.cmdSet.addrBytePhase & 0x1c), 0x0, 0);
d1577 1
a1577 1
    rc = flExecCmd(flDev.cmdSet.erase, 0x0, (FL_CTRL_MASK | FL_CTRL_RDY), 0);
d1635 1
a1635 1
        (1 << (flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) ||
d1656 1
a1656 1
    pages = (1 << (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift));
d1658 1
a1658 1
                (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift);
d1661 1
a1661 1
                (FL_VIRT_SPARE_SIZE_SHIFT - flDev.cap.userSpareSzShift));
d1666 1
a1666 1
        memset(spareBuf, 0, (1 << flDev.cap.pageSpareSzShift));
d1670 1
a1670 1
                        flDev.cap.userSpareSzShift);
d1673 2
a1674 2
            memcpy(&spareBuf[flDev.cap.statusByteOffset + 1], sparePtr,
                (1 << flDev.cap.userSpareSzShift));
d1679 1
a1679 1
                    buf + (pageCount << flDev.cap.pageSzShift),
d1730 1
a1730 1
        (1 << (flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) ||
d1751 1
a1751 1
    pages = (1 << (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift));
d1753 1
a1753 1
                (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift);
d1756 1
a1756 1
                (FL_VIRT_SPARE_SIZE_SHIFT - flDev.cap.userSpareSzShift));
d1763 1
a1763 1
                            buf + (pageCount << flDev.cap.pageSzShift),
d1775 1
a1775 1
                        flDev.cap.userSpareSzShift);
d1778 2
a1779 2
            memcpy(sparePtr, &spareBuf[flDev.cap.statusByteOffset + 1],
                    (1 << flDev.cap.userSpareSzShift));
d1831 1
a1831 1
    maxBlock = (1 << (flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT));
d1834 2
a1835 2
            (flDev.cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT)) &
            (flDev.cap.numPlanes - 1);
d1837 3
a1839 3
            (flDev.cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT)) &
            (flDev.cap.numPlanes - 1);
    if (!flDev.cap.supportCopy || (srcPlane != dstPlane) ||
d1855 1
a1855 1
    pages = (1 << (FL_LOGI_BLOCK_SIZE_SHIFT - flDev.cap.pageSzShift));
d1917 1
a1917 1
    memcpy(stats, &flStats, sizeof (FLStats));
d1957 1
a1957 1
            (1 << (flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) {
d1980 1
a1980 1
            (flDev.cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT);
d1982 1
a1982 1
            (flDev.cap.erasableBlockSzShift - flDev.cap.pageSzShift);
d1985 1
a1985 1
        if (flDev.cmdSet.readSpare != FL_CMD_INVALID) {
d1993 2
a1994 2
            rc = flExecCmd(flDev.cmdSet.readSpare, 
                        flDev.cmdSet.addrBytePhase,
d1996 1
a1996 1
                        (1 << flDev.cap.pageSpareSzShift));
d2008 1
a2008 1
            rc = flExecCmd(flDev.cmdSet.read, 0, 0, 0);
d2020 1
a2020 1
            flSetDevAddr((1 << flDev.cap.pageSzShift),
d2022 2
a2023 2
            rc = flExecCmd(flDev.cmdSet.readSetup,
                        flDev.cmdSet.addrBytePhase, 0x0, 0);
d2036 1
a2036 1
            rc = flExecCmd(flDev.cmdSet.read,
d2038 1
a2038 1
                        (1 << flDev.cap.pageSpareSzShift));
d2050 1
a2050 1
        if (spareBuf[flDev.cap.statusByteOffset] != FL_STATUS_GOOD) {
