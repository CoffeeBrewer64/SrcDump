#include "cpusim.h"
#include "test_vector.h"

#define TEST_JUMP_ADDR  (K0BASE | 0x201000)
#define TEST_JUMP_STACK (K0BASE | 0x2f8000)

int main() 
{
    int x;
    void (*f0)(void);
    static void run(void);
    vu32 *p0, *p1;

    test_preamble();
    initICache();
    initDCache();
    init_ddr();

    setcp0reg(C0_SR, SR_CU0|SR_CU1|SR_BEV);
    setcp0reg(C0_CONFIG, CONFIG_BE|CONFIG_NONCOHRNT);

    p0 = (vu32*)run;
    p1 = (vu32*)PHYS_TO_K1(INTERNAL_RAM_START);
    f0 = (void(*))K1_TO_K0(p1);
    for(x = 0; x < 128; x++) *p1++ = *p0++;
    (*f0)();

       /* swicth stack to ddr and jump to other test */
       /* Please make sure code is already loaded to ddr */ 
    __asm__ __volatile__ ("li   $29, %0\n" : : "M"(TEST_JUMP_STACK)); 
    f0 = (void(*))K1_TO_K0(TEST_JUMP_ADDR);
    (*f0)();

    test_postamble();
    return 0;
}

#define DDR_X64_START  (K0BASE | 0x01000000)
#define DDR_X64_END    (K0BASE | 0x02000000)
#define DDR_ADDR_LINE  24
#define DDR_MASK       (((1<<DDR_ADDR_LINE) - 1) & 0xFFFFFFFC) 

static void run(void) 
{
    int i, addr[(DDR_ADDR_LINE-2)*2], *paddr;
    unsigned int *p, *e;

    for (i=2, paddr=addr; i < DDR_ADDR_LINE; i++) {
        *paddr++ =  (1<<i) | DDR_X64_START;
        *paddr++ = ((~(1<<i)) & DDR_MASK) | DDR_X64_START;
    } 

       /* Output */
    p=(unsigned int *) addr;
    e=p + (DDR_ADDR_LINE-2)*2;
    while (p < e) {
        *((unsigned int *) p[0]) = p[0];
        p++;
    }

      /* Input and compare*/ 
    p=(unsigned int *) addr;
    e=p + (DDR_ADDR_LINE-2)*2;
    while (p < e) {
        if (*((unsigned int *) p[0]) != p[0])  {
            TEST_ERROR;
        }
        p++;
    }

      /* Output and input */
    p=(unsigned int *) addr;
    e=p + (DDR_ADDR_LINE-2)*2;
    while (p < e) {
        * ((unsigned int *) p[0]) = p[0];
        if (*((unsigned int *) p[0]) != p[0]) {
            TEST_ERROR;
        }
        p++;
    }

    return ;
}
