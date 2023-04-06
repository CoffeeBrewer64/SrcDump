/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by Federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

#ifdef NET_CARD
#include <sc/asm.h>
#else
#include <asm.h>
#endif

/*
 * ASM routines for managing locks
 */

    .text
    .code 32
    .balign 0

/*
 * void __skInitlock(lock_t lck)
 *
 * Initialize a lock, must be called before other primitives
 */
BEGIN_PROC(__skInitlock)
        ldr     r1, =0
        str     r1, [r0]
        bx      lr
END_PROC(__skInitlock)

/*
 * void __skTrylock(lock_t lck)
 *
 * Acquire a lock
 */
BEGIN_PROC(__skTrylock)
        ldr     r2, =0
        ldr     r1, =1
        swp     r1, r1, [r0]
        ldr     r0, =0
        cmp     r1, r2
        bne     done        /* Failed */
        ldr     r0, =1      /* Succeeded */
done:
        bx      lr
END_PROC(__skTrylock)

/*
 * void __skUnlock(lock_t lck)
 *
 * Release a lock
 */
BEGIN_PROC(__skUnlock)
        ldr     r1, =0
        str     r1, [r0]        @ release the lock
        bx      lr
END_PROC(__skUnlock)
