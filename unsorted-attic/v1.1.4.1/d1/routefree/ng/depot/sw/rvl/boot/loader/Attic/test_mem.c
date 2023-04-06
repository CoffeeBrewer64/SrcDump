a0 253
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

#include <iostypes.h>
#include <ioslibc.h>
#include <addr_map.h>
#include <sys.h>
#include <iop.h>

/*
 * primes between 0 and 255;
 * first three primes are repeated for u32 wrapping;
 */
#define	N_PRIMES	55
u8 test_mem_primes[] = {
	1, 2, 3, 5, 7, 11, 13, 17,
	19, 23, 29, 31, 37, 41, 43, 47,
	53, 59, 61, 67, 71, 73, 79, 83,
	89, 97, 101, 103, 107, 109, 113, 127,
	131, 137, 139, 149, 151, 157, 163, 167,
	173, 179, 181, 191, 193, 197, 199, 211,
	223, 227, 229, 233, 239, 241, 251,
	1, 2, 3,
};

// prime offset;
// use global, so that repeated tests use new sequence;
// set to 1 to avoid putting test_mem_poff in BSS

u32 test_mem_poff = 1;

// Test the entire DDR

#define TEST_SD_START		0x10000000
#define TEST_SD_END			IOP_GDDR3_END

// Test failure codes

#define REASON_MEMD			-1
#define REASON_MEM8			-2
#define REASON_MEM16		-3
#define REASON_MEM32		-4

/*
 * output a value to the LEDs
 */
void
output_led(u32 value)
{
	u32 reg;

	reg = busRd32(GPIIOPOUT_REG);
	reg = (reg & ~GPIIO_PIO_ENABLE) | ((value & 0xff) << GPIIO_PIO_SHIFT);
	busWrt32(GPIIOPOUT_REG, reg);
}

/*
 * test failed, output reason and spin
 */
static void
test_fail(u32 reason)
{
	output_led(reason);
	while (1);
}

/*
 * memory data bit test;
 * walking 1 through all data bits;
 * need three memory locations to flush bus/cache;
 */
void
test_memd(u32 *b, u32 *e)
{
	int bit;
	u32 exp, val;

	// store val into b, then inverse into *e;

	for(bit = 0; bit < 32; bit++) {
		exp = (1 << bit);
		busWrt32(b, exp);			// write b[0] with pattern;
		busWrt32(e, ~exp);			// flush the write buffer; 
		val = busRd32(e);			// invalidate the read buffer;
		val = busRd32(b);			// read b[0]
		if(val != exp) {
			test_fail(REASON_MEMD);
		}
	}
}

/*
 * memory byte test;
 */
u32
test_mem8(u8 *b, u8 *e, u32 poff)
{
	u32 roff, val, exp;
	u8 *p;

	// byte writes;
	// fill prime sequence;

	roff = poff;
	for(p = b; p < e; p+=4) {
		// write only one byte in each word;

		*(p + (poff & 0x3)) = test_mem_primes[poff];
		poff++;
		if(poff >= N_PRIMES)
			poff = 0;
	}

	// byte read test;

	for(p = b; p < e; p+=4) {
		val = (u32) *(p + (roff & 0x3));
		exp = (u32) test_mem_primes[roff++];
		if(val != exp) {
			test_fail(REASON_MEM8);
		}
		if(roff >= N_PRIMES)
			roff = 0;
	}
	return(poff);
}

/*
 * memory half test;
 */
u32
test_mem16(u16 *b, u16 *e, u32 poff)
{
	u32 roff, val, exp;
	u16 *p;

	// half writes;
	// fill prime sequence;

	roff = poff;
	for(p = b; p < e; p+=2) {
		// write only one half-word in each word;

		*(p + ((u32)poff & 0x1)) = (test_mem_primes[poff+0])
			| (test_mem_primes[poff+1] << 8);
		poff += 2;
		if(poff >= N_PRIMES)
			poff = 0;
	}

	// half read test;

	for(p = b; p < e; p+=2) {
		val = (u32) *(p + (roff & 0x1));
		exp = (u32) (test_mem_primes[roff+0])
			| (test_mem_primes[roff+1] << 8);
		if(val != exp) {
			test_fail(REASON_MEM16);
		}
		roff += 2;
		if(roff >= N_PRIMES)
			roff = 0;
	}
	return(poff);
}

/*
 * memory word test;
 */
u32
test_mem32(u32 *b, u32 *e, u32 poff)
{
	u32 roff, val, exp;
	u32 *p;

	// fill prime sequence;

	roff = poff;
	for(p = b; p < e; p++) {
		*p = (test_mem_primes[poff+0])
			| (test_mem_primes[poff+1] << 8)
			| (test_mem_primes[poff+2] << 16)
			| (test_mem_primes[poff+3] << 24);
		poff += 4;
		if(poff >= N_PRIMES)
			poff = 0;
	}

	// read test;

	for(p = b; p < e; p++) {
		val = *p;
		exp = (test_mem_primes[roff+0])
			| (test_mem_primes[roff+1] << 8)
			| (test_mem_primes[roff+2] << 16)
			| (test_mem_primes[roff+3] << 24);
		if(val != exp) {
			test_fail(REASON_MEM32);
		}
		roff += 4;
		if(roff >= N_PRIMES)
			roff = 0;
	}
	return(poff);
}

/*
 * dram data bit test;
 * alternative location must be larger than the write and read buffers
 */
void
test_sd_dbit(void)
{
	u32 *mem;

	mem = (u32 *) (TEST_SD_START + (64 * 1024));
	test_memd(mem, mem + 64*1024);
}

/*
 * dram byte test;
 */
void
test_sd_8(void)
{
	test_mem_poff = test_mem8((void *)TEST_SD_START, (void *)TEST_SD_END, test_mem_poff);
}

/*
 * dram half test;
 */
void
test_sd_16(void)
{
	test_mem_poff = test_mem16((void *)TEST_SD_START, (void *)TEST_SD_END, test_mem_poff);
}

/*
 * dram word test;
 */
void
test_sd_32(void)
{
	test_mem_poff = test_mem32((void *)TEST_SD_START, (void *)TEST_SD_END, test_mem_poff);
}
