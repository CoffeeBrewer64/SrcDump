d36 1
a36 1
// changed to 1 to avoid using the BSS
d40 1
a40 1
// Test part of the SRAM, DDR, and Napa
d42 2
a43 6
#define TEST_SRAM_START		0xffff0000
#define TEST_SRAM_END       0xffff8000
#define TEST_DDR_START		0x10000000
#define TEST_DDR_END        0x10010000
#define TEST_NAPA_START		0x00000000
#define TEST_NAPA_END       0x00010000
d58 1
a58 1
    u32 reg;
d60 3
a62 3
    reg = busRd32(GPIIOPOUT_REG);
    reg = (reg & ~GPIIO_PIO_ENABLE) | ((value & 0xff) << GPIIO_PIO_SHIFT);
    busWrt32(GPIIOPOUT_REG, reg);
d71 2
a72 2
    output_led(reason);
    while (1);
d215 6
a220 2
s32
doMemTest(void)
d222 1
a222 2
    s32 rc = 0;
    u32 *mem;
d224 3
a226 1
    output_led(0x23);
d228 8
a235 18
    /* Test the SRAM */
    mem = (u32 *) (TEST_SRAM_START + (8 * 1024));
    test_memd(mem, mem + (8 * 1024));
	test_mem_poff = test_mem8((void *)TEST_SRAM_START, (void *)TEST_SRAM_END, test_mem_poff);
	test_mem_poff = test_mem16((void *)TEST_SRAM_START, (void *)TEST_SRAM_END, test_mem_poff);
	test_mem_poff = test_mem32((void *)TEST_SRAM_START, (void *)TEST_SRAM_END, test_mem_poff);

    /* Test the DDR */
    mem = (u32 *) (TEST_DDR_START + (16 * 1024));
    test_memd(mem, mem + (16 * 1024));
	test_mem_poff = test_mem8((void *)TEST_DDR_START, (void *)TEST_DDR_END, test_mem_poff);
	test_mem_poff = test_mem16((void *)TEST_DDR_START, (void *)TEST_DDR_END, test_mem_poff);
	test_mem_poff = test_mem32((void *)TEST_DDR_START, (void *)TEST_DDR_END, test_mem_poff);

    /* Test the Napa */
    mem = (u32 *) (TEST_NAPA_START + (16 * 1024));
    test_memd(mem, mem + (16 * 1024));
	test_mem_poff = test_mem32((void *)TEST_NAPA_START, (void *)TEST_NAPA_END, test_mem_poff);
d237 8
a244 1
    output_led(0x24);
d246 7
a252 1
    return (rc);
