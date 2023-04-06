d1 1
a1 1
#ident "$Id: dvd_hw_reg.i,v 1.3 2006/02/24 05:20:29 craig Exp $"
d22 1
a22 1
#ifdef __ARMEB__
d52 11
a62 9
#define         DI_STATUS_ADDR        0x0C006000
#define         DI_COVER_ADDR         0x0C006004
#define         DI_CMD_BUF_0_ADDR     0x0C006008
#define         DI_CMD_BUF_1_ADDR     0x0C00600C
#define         DI_CMD_BUF_2_ADDR     0x0C006010
#define         DI_DMA_DEST_ADDR      0x0C006014
#define         DI_LENGTH_ADDR        0x0C006018
#define         DI_CONTROL_ADDR       0x0C00601C
#define         DI_IMM_DATA_ADDR      0x0C006020
d71 1
d136 1
