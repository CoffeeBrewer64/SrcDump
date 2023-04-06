#include <regdef.h>
#include <asm.h>
#include <PR/R4300.h>

#include <PR/bcp.h>
#include <PR/bbsim.h>
#include <PR/bbskapi.h>

#define SK_ENTRY_AND_RETURN               \
    li t0, PHYS_TO_K1(MI_SEC_MODE_REG);   \
    .set noreorder;                       \
    lw t1, (t0);                          \
    nop;                                  \
    .set reorder;                         \
    j ra

#define SK_API_APP_STUB(_funcname,_funcindx)  \
    .text;                                    \
    .align 2;                                 \
    .globl _funcname;                         \
    .type symbol,@function;                   \
    .ent _funcname;                           \
    _funcname:;                               \
      li   v0, _funcindx;                     \
      SK_ENTRY_AND_RETURN;                    \
    .end _funcname

SK_API_APP_STUB(skTest1,SK_API_CALL_TEST1)
SK_API_APP_STUB(skTest2,SK_API_CALL_TEST2)
SK_API_APP_STUB(skTest3,SK_API_CALL_TEST3)
