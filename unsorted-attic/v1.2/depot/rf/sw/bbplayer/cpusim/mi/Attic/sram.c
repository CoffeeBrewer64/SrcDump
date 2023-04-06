
#include <regdef.h>
#include <asm.h>
#include <R4300.h>
#include <PR/bcp.h>
#include <PR/bbdebug.h>
#include "test_vector.h"

static inline int do_virage_sram_test();
static inline int do_sram_test(unsigned int start, unsigned int end);

    /* Test all mi sram here */
int main()
{
    int err=0;

    err += do_virage_sram_test();
    err += do_sram_test(BOOT_RAM_LO_START, BOOT_RAM_LO_END);
    err += do_sram_test(INTERNAL_RAM_START, INTERNAL_RAM_END);

    if (err) { TEST_ERROR;}
    else {TEST_PASS;}

    for (;;) ;
    return 0;
}

static inline int do_sram_test(unsigned int start, unsigned int end)
{
    int err=0, data, addr, k;

    /* change to cache space */
    start |= K0BASE;
    end |= K0BASE;

         /* walk through address line */
    *((unsigned int *) start) = 0x12345678;
    for (addr=start, k=4; (addr+k)<end; k<<=1) {
        data = (k & 0xff) | ((~k & 0xff) << 8);
        data |= (~data << 16);

        *((unsigned int *) (addr + k)) = data;               
    }
    *((unsigned int *) (end -4)) = 0xbabecafe;

    if ( *((unsigned int *) start) != 0x12345678 )  err++;
    for (addr=start, k=4; (addr+k)<end; k<<=1) {
         data = (k & 0xff) | ((~k & 0xff) << 8);
         data |= (~data << 16);
         if (*((unsigned int *) (addr + k)) != data)  err++;
    }
    if ( *((unsigned int *) (end-4)) != 0xbabecafe )  err++;

                /* 1 Walk through data line */
    for (k=0; k<32; k++) {
        data = 1 << k;
        *((unsigned int *) start) = data;
        if ( *((unsigned int *) start) != data) err++;
    }

    return err;
}

static inline int  do_virage_sram_test()
{
    int err = 0;
    err += do_sram_test(VIRAGE0_RAM_START, VIRAGE0_RAM_END );
    err += do_sram_test(VIRAGE1_RAM_START, VIRAGE1_RAM_END );
    IO_WRITE(VIRAGE2_CTRL_REG, 0);
    err += do_sram_test(VIRAGE2_RAM_START, VIRAGE2_RAM_END );

    return err;
}
