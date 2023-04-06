d1 1
a1 1
#ident "$Id: dvd_hw_reg.i,v 1.2 2006/02/24 02:31:58 craig Exp $"
a18 6
#ifdef __ARMEB__
#include "stdint.h"
#else
#include <stdint.h>
#endif

a19 27
#include <stdio.h>
#include <stdlib.h>

/*
 * Declarations for the DVD hardware interface registers
 */

/*
 * The base address of the DI registers is 0x0C006000.
 * (IO Specification p. 14)
 */
#ifdef EMULATOR
extern volatile uint32_t        DIStatus;               /* Offset 0x00 */
extern volatile uint32_t        DICoverReg;             /* Offset 0x04 */
extern volatile uint32_t        DICmdBuf[3];            /* Offset 0x08 */
extern volatile uint32_t        DIDmaDestAddr;          /* Offset 0x14 */
extern volatile uint32_t        DILength;               /* Offset 0x18 */
extern volatile uint32_t        DIControl;              /* Offset 0x1C */
extern volatile uint32_t        DIImmData;              /* Offset 0x20 */
/*
 * The DI Configuration Register is at offset 0x24.
 * It isn't used in the driver
 */
#endif

#include <stdbool.h>
#include <stdio.h>
a21 2
#include "dvd_hw_reg.h"

d24 2
d27 1
d51 10
d71 1
a71 1
    return * ((uint32_t *) 0x0C006000);
d81 1
a81 1
    return * ((uint32_t *) 0x0C006004);
d90 2
a92 1
    return * ((uint32_t *) 0x0C006008);
d101 1
a101 1
    return * ((uint32_t *) 0x0C00600C);
d111 1
a111 1
    return * ((uint32_t *) 0x0C006010);
d121 1
a121 1
    return * ((uint32_t *) 0x0C006020);
a127 10
writeDIControl(const uint32_t value)
{
#ifdef EMULATOR
    DIControl = value;
#else
#endif
}

/* -------------------------------------------------------------------- */
static inline void
d133 1
d145 1
d156 1
d166 1
d177 12
d199 12
