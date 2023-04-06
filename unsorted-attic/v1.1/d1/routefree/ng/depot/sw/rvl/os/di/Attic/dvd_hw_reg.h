d1 1
a1 1
#ident "$Id: dvd_hw_reg.h,v 1.1 2006/02/07 19:26:48 craig Exp $"
a15 6
#if defined(RVL)
#include "arm_stdint.h"
#else
#include <stdint.h>
#endif

d24 7
a30 7
extern volatile uint32_t        DIStatus;               /* Offset 0x00 */
extern volatile uint32_t        DICoverReg;             /* Offset 0x04 */
extern volatile uint32_t        DICmdBuf[3];            /* Offset 0x08 */
extern volatile uint32_t        DIDmaDestAddr;          /* Offset 0x14 */
extern volatile uint32_t        DILength;               /* Offset 0x18 */
extern volatile uint32_t        DIControl;              /* Offset 0x1C */
extern volatile uint32_t        DIImmData;              /* Offset 0x20 */
