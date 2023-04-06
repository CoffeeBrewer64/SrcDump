d1 1
a1 1
#ident "$Id: dvd_hw_reg.h,v 1.1 2006/03/31 20:00:04 craig Exp $"
d16 6
d30 7
a36 7
extern volatile u32        DIStatus;               /* Offset 0x00 */
extern volatile u32        DICoverReg;             /* Offset 0x04 */
extern volatile u32        DICmdBuf[3];            /* Offset 0x08 */
extern volatile u32        DIDmaDestAddr;          /* Offset 0x14 */
extern volatile u32        DILength;               /* Offset 0x18 */
extern volatile u32        DIControl;              /* Offset 0x1C */
extern volatile u32        DIImmData;              /* Offset 0x20 */
