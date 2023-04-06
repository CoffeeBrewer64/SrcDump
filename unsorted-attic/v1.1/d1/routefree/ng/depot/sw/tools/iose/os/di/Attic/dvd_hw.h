d1 1
a1 1
#ident "$Id$"
d23 7
a29 6
extern volatile uint32_t        DI_Status;
extern volatile uint32_t        DI_Cover_Reg;
extern volatile uint32_t        DI_DMA_Dest_Addr;
extern volatile uint32_t        DI_Length;
extern volatile uint32_t        DI_Control;
extern volatile uint32_t        DI_Imm_Data;
d44 1
d50 42
a91 1
#define DI_START_TRANSFER               DI_Control |= DI_TRANSFER
