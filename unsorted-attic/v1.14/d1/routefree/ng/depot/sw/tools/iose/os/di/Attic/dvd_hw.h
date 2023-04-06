d1 1
a1 1
#ident "$Id: dvd_hw.h,v 1.13 2006/02/02 00:34:05 craig Exp $"
a22 14
/*
 * The base address of the DI registers is 0x0C006000.
 * (IO Specification p. 14)
 */

extern volatile uint32_t        DIStatus;               /* Offset 0x00 */
extern volatile uint32_t        DICoverReg;             /* Offset 0x04 */
extern volatile uint32_t        DICmdBuf[3];            /* Offset 0x08 */
extern volatile uint32_t        DIDmaDestAddr;          /* Offset 0x14 */
extern volatile uint32_t        DILength;               /* Offset 0x18 */
extern volatile uint32_t        DIControl;              /* Offset 0x1C */
extern volatile uint32_t        DIImmData;              /* Offset 0x20 */
/* The DI Configuration Register is at offset 0x24.  It isn't used in the driver */

