#include "asm.h"
#include "mmu.h"
.text
.code 32
.align 0

.global enableAFaults
.global disableAFaults

/*
 * Turn on Alignment Faults in the MMU.
 *
 * + set A bit in PC register c1
 *
 * This routine obeys normal procecure calling
 * conventions meaning that it trashes r0
 * and does not restore it.
 */
BEGIN_PROC(enableAFaults)
    mrc     p15, 0, r0, c1, c0, 0
    orr     r0, r0, #ENABLE_ALIGNMENT_CHECK
    mcr     p15, 0, r0, c1, c0, 0
    bx      lr
END_PROC(enableAFaults)

/*
 * Turn off Alignment Faults in the MMU.
 *
 * + clear A bit in PC register c1
 */
BEGIN_PROC(disableAFaults)
    mrc     p15, 0, r0, c1, c0, 0
    bic     r0, r0, #ENABLE_ALIGNMENT_CHECK
    mcr     p15, 0, r0, c1, c0, 0
    bx      lr
END_PROC(disableAFaults)

.end
