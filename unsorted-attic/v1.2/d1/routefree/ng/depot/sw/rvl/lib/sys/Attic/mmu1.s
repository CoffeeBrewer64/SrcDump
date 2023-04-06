	/*
        * $Id: mmu1.s,v 1.1 2006/02/04 03:07:54 gzhang Exp $
        */
	
#include "asm.h"
#include "mmu.h"
	
        /*
	 * Utility routines to do with turning on the MMU and
	 * caches.
	 */
        .text
        .code 32
        .align 0

#define	TTB_ADDR	0xfff08000 


	.global setupMmu

	/*
	 * Do all the steps to set up the MMU, finally calling
	 * the mmuEnable routine.
	 */
BEGIN_PROC(setupMmu)
	/*
	 * Save registers.
	 */
	sub	sp, sp, #4
	str	lr, [sp]
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	/* 
	 * Write the aligned address to CP TTB register c2.
	 */
	ldr	r0, =TTB_ADDR
	bl	mmuSetTTB
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Now program the Domain Access Control Register C3.
	 *
	 * No longer called here.   The global routine mmuSetDACR
	 * must be called before setup_mmu is called.
	 */
	/*
	 * Enable MMU.
	 */
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #ENABLE_MMU
	ldr	r1, =save_r0
	str	r0, [r1]
	mcr	p15, 0, r0, c1, c0, 0
	/*
	 * Restore registers.
	 */
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	ldr	lr, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(setupMmu)

	.global setupMmuNoAccess

	/*
	 * Do all the steps to set up the MMU, finally calling
	 * the mmuEnable routine.
	 */
BEGIN_PROC(setupMmuNoAccess)
	/*
	 * Save registers.
	 */
	sub	sp, sp, #4
	str	lr, [sp]
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	/* 
	 * Write the aligned address to CP TTB register c2.
	 */
	ldr	r0, =TTB_ADDR
	bl	mmuSetTTB
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Now program the Domain Access Control Register C3.
	 */
	ldr	r0, =DOMAIN_NO_ACCESS
	mcr	p15, 0, r0, c3, c0, 0
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Enable MMU.
	 */
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #ENABLE_MMU
	mcr	p15, 0, r0, c1, c0, 0
	/*
	 * Restore registers.
	 */
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	ldr	lr, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(setupMmuNoAccess)

	.global setupMmuCltAccess

	/*
	 * Do all the steps to set up the MMU, finally calling
	 * the mmuEnable routine. Setup for Domain Client Access
	 */
BEGIN_PROC(setupMmuCltAccess)
	/*
	 * Save registers.
	 */
	sub	sp, sp, #4
	str	lr, [sp]
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	/* 
	 * Write the aligned address to CP TTB register c2.
	 */
	ldr	r0, =TTB_ADDR
	bl	mmuSetTTB
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Now program the Domain Access Control Register C3.
	 */
	ldr	r0, =DOMAIN_CLIENT_ACCESS
	mcr	p15, 0, r0, c3, c0, 0
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Enable MMU.
	 */
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #ENABLE_MMU
	mcr	p15, 0, r0, c1, c0, 0
	/*
	 * Restore registers.
	 */
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	ldr	lr, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(setupMmuCltAccess)

	/*
	 * Enable MMU
	 */
BEGIN_PROC(mmuEnable)
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #ENABLE_MMU
	mcr	p15, 0, r0, c1, c0, 0
	ldr	r1, =save_r0
	str	r0, [r1]
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(mmuEnable)

	/*
	 * Set the translation table base in CP register c2.
	 *
	 * Assumes that the TTB base is in r0
	 */
BEGIN_PROC(mmuSetTTB)
	mcr	p15, 0, r0, c2, c0, 0
	mov	pc, lr
END_PROC(mmuSetTTB)

	/*
	 * Flush the two TLBs.
	 *
	 * This routine is only called from within this source file, so
	 * there is no global declaration for it.   Also, we assume that 
	 * the caller will save and restore r0.
	 *
	 * Call with 'bl mmuFlushTLB'.
	 */
BEGIN_PROC(mmuFlushTLB)
	mov	r0, #0
	mcr	p15, 0, r0, c8, c7, 0
	mov	pc, lr
END_PROC(mmuFlushTLB)

	/*
	 * Do all the steps to set up the MMU, finally calling
	 * the mmuEnable routine.
	 */
BEGIN_PROC(setupMmuMgrAccess)
	/*
	 * Save registers.
	 */
	sub	sp, sp, #4
	str	lr, [sp]
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	/* 
	 * Write the aligned address to CP TTB register c2.
	 */
	ldr	r0, =TTB_ADDR
	bl	mmuSetTTB
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Now program the Domain Access Control Register C3.
	 */
	ldr	r0, =DOMAIN_MANAGER_ACCESS
	mcr	p15, 0, r0, c3, c0, 0
	ldr	r1, =save_r0
	str	r0, [r1]
	/*
	 * Drain write buffer
	 */
	mcr     p15, 0, r0, c7, c10, 4
	/*
	 * Enable MMU.
	 */
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #(ENABLE_MMU|ENABLE_D_CACHE)
	mcr	p15, 0, r0, c1, c0, 0
	/*
	 * Restore registers.
	 */
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	ldr	lr, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(setupMmuMgrAccess)


	.global	flushDCache
	/*
	 * This is a routine to flush the D cache.
	 *
	 * + Save used registers
	 * + flush D cache bits in PC register c1
	 * + restore used registers.
	 *
	 */
BEGIN_PROC(flushDCache)
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
tci_loop:		mrc	p15, 0, r15, c7, c10, 3
	bne	tci_loop
	ldr	r1, =save_r0
	str	r0, [r1]
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(flushDCache)

	.global	flushInvalidDCache
	/*
	 * This is a routine to flush and invalidate the D cache.
	 *
	 * + Save used registers
	 * + flush and invalidate D cache bits in PC register c1
	 * + restore used registers.
	 *
	 */
BEGIN_PROC(flushInvalidDCache)
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
tci_loop2:		mrc	p15, 0, r15, c7, c14, 3
	bne	tci_loop2
	ldr	r1, =save_r0
	str	r0, [r1]
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(flushInvalidDCache)

	.global drainWriteBuffer	
	/*
	 * This is a routine to drain write buffer
	 *
	 * + Save used registers
	 * + drain write buffer in PC register c1
	 * + restore used registers.
	 *
	 */
BEGIN_PROC(drainWriteBuffer)
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	mov	r0, #0
	mcr	p15, 0, r0, c7, c10, 4
	ldr	r1, =save_r0
	str	r0, [r1]
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(drainWriteBuffer)

	.global	enableDCache
	/*
	 * This is a routine to enable the D cache.
	 *
	 * + Save used registers
	 * + enable D cache bits in PC register c1
	 * + restore used registers.
	 *
	 */
BEGIN_PROC(enableDCache)
	sub	sp, sp, #4
	str	r0, [sp]
	sub	sp, sp, #4
	str	r1, [sp]
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #ENABLE_D_CACHE
	mcr	p15, 0, r0, c1, c0, 0
	ldr	r1, =save_r0
	str	r0, [r1]
	ldr	r1, [sp]
	add	sp, sp, #4
	ldr	r0, [sp]
	add	sp, sp, #4
	mov	pc, lr
END_PROC(enableDCache)

        .global enableICache
        /*
         * This is a routine to enable the I cache.
         *
         * + Save used registers
         * + enable I cache bits in PC register c1
         * + restore used registers.
         *
         */
BEGIN_PROC(enableICache)
        sub     sp, sp, #4
        str     r0, [sp]
        sub     sp, sp, #4
        str     r1, [sp]
        mrc     p15, 0, r0, c1, c0, 0
        orr     r0, r0, #ENABLE_I_CACHE
        mcr     p15, 0, r0, c1, c0, 0
        ldr     r1, =save_r0
        str     r0, [r1]
        ldr     r1, [sp]
        add     sp, sp, #4
        ldr     r0, [sp]
        add     sp, sp, #4
        mov     pc, lr
END_PROC(enableICache)

        .global invalICache
        /*
         * This is a routine to invalidate the I cache.
         *
         * + Save used registers
         * + invalidate I cache bits in PC register c5
         * + restore used registers.
         *
         */
BEGIN_PROC(invalICache)
        sub     sp, sp, #4
        str     r0, [sp]
        sub     sp, sp, #4
        str     r1, [sp]
        mcr     p15, 0, r0, c7, c5, 0
        ldr     r1, =save_r0
        str     r0, [r1]
        ldr     r1, [sp]
        add     sp, sp, #4
        ldr     r0, [sp]
        add     sp, sp, #4
        mov     pc, lr
END_PROC(invaliICache)

        .global mmuSetDACR
        /*
         * Program the Domain Access Control Register C3.
         */
BEGIN_PROC(mmuSetDACR)
        mcr     p15, 0, r0, c3, c0, 0
        ldr     r1, =save_r0
        str     r0, [r1]
        mov     pc, lr
END_PROC(mmuSetDACR)

save_r0:
	.word	0

	.end

