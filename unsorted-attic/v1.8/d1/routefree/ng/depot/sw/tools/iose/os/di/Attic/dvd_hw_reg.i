d1 1
a1 1
#ident "$Id: dvd_hw_reg.i,v 1.7 2006/02/28 04:03:46 craig Exp $"
d63 32
d97 1
d99 1
d107 1
a107 1
    return (busRd32(DI_STATUS_ADDR));
d117 1
a117 1
    return (busRd32(DI_COVER_ADDR));
d127 1
a127 1
    return (busRd32(DI_CMD_BUF_0_ADDR));
d137 1
a137 1
    return (busRd32(DI_CMD_BUF_1_ADDR));
d147 1
a147 1
    return (busRd32(DI_CMD_BUF_2_ADDR));
d157 1
a157 1
    return (busRd32(DI_IMM_DATA_ADDR));
d191 1
a191 1
    regValue = busRd32(address);
