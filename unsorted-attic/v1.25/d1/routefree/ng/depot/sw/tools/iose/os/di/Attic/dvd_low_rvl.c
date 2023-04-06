d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.24 2006/03/22 01:09:34 craig Exp $"
d657 1
d661 1
a662 1
        flushDItoIOP(&diskInfo, sizeof(diskInfo));
a719 2
    flushDItoIOP(&globalTOC, sizeof(globalTOC_t));

a730 1
    flushDItoIOP(&gameTOC, sizeof(gameTOC_t));
a739 1
    flushDItoIOP(&partitionOffset, sizeof(uint32_t));
a781 1
    flushDItoIOP(&gamePartition, sizeof(gamePartition_t));
d843 1
d870 1
d876 1
