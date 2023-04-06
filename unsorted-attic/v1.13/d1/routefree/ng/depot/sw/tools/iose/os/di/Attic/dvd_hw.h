d1 1
a1 1
#ident "$Id: dvd_hw.h,v 1.12 2006/01/28 03:38:11 craig Exp $"
d23 13
a35 7
extern volatile uint32_t        DIStatus;
extern volatile uint32_t        DICoverReg;
extern volatile uint32_t        DICmdBuf[3];
extern volatile uint32_t        DIDmaDestAddr;
extern volatile uint32_t        DILength;
extern volatile uint32_t        DIControl;
extern volatile uint32_t        DIImmData;
