/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

        .text
        .code 32
        .align 0

_start: .global _start
    /* Set sp to point to top of stack */
    ldr r2, =_initStackSize
    ldr r2, [r2]
    ldr sp, =_initStack
    add sp, sp, r2

    /* Set initial priority */
    mov r5, r0
    mov r6, lr
    ldr r2, =_initPriority
    ldr r1, [r2]
    mov r0, #0
    bl  IOS_SetThreadPriority
    mov r0, r5
    mov lr, r6

    /* Jump to main */
    ldr r2, =main
    bx  r2

.end

