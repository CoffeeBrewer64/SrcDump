#include <regdef.h>
#include <asm.h>
#include <PR/R4300.h>

#include <PR/bcp.h>
#include <PR/bbsim.h>
#include <PR/bbskapi.h>

#define APP_STACK_SIZE 256 

.set mips3

.global __timer_test

#define CHECK_REG(_r,val)   \
        li      a2, val; \
        beq     a2, _r, 1f; \
        la      a2, PHYS_TO_K1(PI_BASE_REG); \
        sw      _r, (a2); \
        li      _r, val; \
        sw      _r, (a2); \
    1:

/* reserve space for the stack pointer */
.bss
.align 4
.comm __stack, APP_STACK_SIZE

.text
.align 2
.set   reorder 
.ent __start
.globl __start
__start:
        la      sp, __stack + APP_STACK_SIZE

        .set noreorder
        la      t0, __bss_start
        la      t1, _end - 4
zero_bss:
        sw      zero, (t0)
        bge     t1, t0, zero_bss
        add     t0, 4
        .set reorder

#ifdef BIG_APP
        /* make app big for testing */
        .set noreorder
        .rept (1024*16)/4
        nop
        .endr
        .set reorder
#endif

        jal     boot


        /* for timer testing */
__timer_test:
        /* set all regs to known values */
        li      a0, 1
        li      a1, 2
        li      a2, 3
        li      a3, 4
        li      t0, 5
        li      t1, 6
        li      t2, 7
        li      t3, 8
        li      t4, 9
        li      t5, 10
        li      t6, 11
        li      t7, 12
        li      t8, 13
        li      t9, 14
        li      s0, 15
        li      s1, 16
        li      s2, 17
        li      s3, 18
        li      s4, 19
        li      s5, 20
        li      s6, 21
        li      s7, 22
        li      v0, 23
        li      v1, 24
        li      ra, 25
        li      sp, 26
        li      gp, 27

forever:
        CHECK_REG(a0,1)
        CHECK_REG(a1,2)
        CHECK_REG(a3,4)
        CHECK_REG(t0,5)
        CHECK_REG(t1,6)
        CHECK_REG(t2,7)
        CHECK_REG(t3,8)
        CHECK_REG(t4,9)
        CHECK_REG(t5,10)
        CHECK_REG(t6,11)
        CHECK_REG(t7,12)
        CHECK_REG(t8,13)
        CHECK_REG(t9,14)
        CHECK_REG(s0,15)
        CHECK_REG(s1,16)
        CHECK_REG(s2,17)
        CHECK_REG(s3,18)
        CHECK_REG(s4,19)
        CHECK_REG(s5,20)
        CHECK_REG(s6,21)
        CHECK_REG(s7,22)
        CHECK_REG(v0,23)
        CHECK_REG(v1,24)
        CHECK_REG(ra,25)
        CHECK_REG(sp,26)
        CHECK_REG(gp,27)
        j       forever

        /* simulator off */
        sh      zero, PHYS_TO_K1(PI_IDE3_SIM_HALT)
        lw      t0, PHYS_TO_K1(PI_IDE_FC_BASE_REG)
power_down_loop:
        beq     zero, zero, power_down_loop

.end __start
