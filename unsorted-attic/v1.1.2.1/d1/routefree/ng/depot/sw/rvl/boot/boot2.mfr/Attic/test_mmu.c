a0 268
/*
 *               Copyright (C) 2006, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and are protected by Federal copyright law. They may not be disclosed
 *  to third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: mmu.c,v 1.32 2006/06/30 20:23:53 achan Exp $
 */


#include <types.h>
#include <ioslibc.h>
#include <iop.h>
#include <ios.h>
#include <sys.h>
#include <mmu.h>
#include <diag/proto.h>
#include <diag/aes_sw.h>
#include <addr_map.h>


#define DCACHE_SIZE         (16 * 1024)
#define MEMCPY_SIZE         (64 * 1024)
#define AES_SIZE            (64 * 1024)
#define BUF_SIZE            (64 * 1024)

/* Tests to run */
#define VALUE_00            1
#define VALUE_FF            2
#define VALUE_MEM           3
static u32  tests[] = {VALUE_00, VALUE_FF, VALUE_MEM};

/* Buffer for testing */
static u8   testBuf[BUF_SIZE];
static u8   dstBuf[BUF_SIZE];
static u8   dstBuf2[BUF_SIZE];


void
testFail()
{
    IOS_OutputLed(0x3e);
    while (1);
}


void
writeToMem32(u32 test)
{
    u32     count = 0;
    u32     value, *ptr;

    for (count = 0; count < (DCACHE_SIZE / 4); count++) {
        if (test == VALUE_00) {
            value = 0;
        } else if (test == VALUE_FF) {
            value = 0xffffffff;
        } else {
            value = ((u32) testBuf) + (count * 4);
        }

        ptr = (u32 *) (((u32) testBuf) + (count * 4));
        *ptr = value;
    }   
}

void
writeToMem16(u32 test)
{
    u32     count = 0;
    u16     value, *ptr;

    for (count = 0; count < (DCACHE_SIZE / 2); count++) {
        if (test == VALUE_00) {
            value = 0;
        } else if (test == VALUE_FF) {
            value = 0xffff;
        } else {
            value = ((u16) testBuf) + (count * 2);
        }

        ptr = (u16 *) (((u32) testBuf) + (count * 2));
        *ptr = value;
    }   
}

void
writeToMem8(u32 test)
{
    u32     count = 0;
    u8      value, *ptr;

    for (count = 0; count < DCACHE_SIZE; count++) {
        if (test == VALUE_00) {
            value = 0;
        } else if (test == VALUE_FF) {
            value = 0xff;
        } else {
            value = ((u8) testBuf) + count;
        }

        ptr = (u8 *) (((u32) testBuf) + count);
        *ptr = value;
    }   
}


void
readFromMem32(u32 test)
{
    u32     count = 0;
    u32     *ptr, check, value;

    for (count = 0; count < (DCACHE_SIZE / 4); count++) {
        if (test == VALUE_00) {
            value = 0;
        } else if (test == VALUE_FF) {
            value = 0xffffffff;
        } else {
            value = ((u32) testBuf) + (count * 4);
        }

        ptr = (u32 *) (((u32) testBuf) + (count * 4));
        check = *ptr;
        if (check != value) {
            testFail();
        }
    }   
}

void
readFromMem16(u32 test)
{
    u32     count = 0;
    u16     *ptr, check, value;

    for (count = 0; count < (DCACHE_SIZE / 2); count++) {
        if (test == VALUE_00) {
            value = 0;
        } else if (test == VALUE_FF) {
            value = 0xffff;
        } else {
            value = ((u16) testBuf) + (count * 2);
        }

        ptr = (u16 *) (((u32) testBuf) + (count * 2));
        check = *ptr;
        if (check != value) {
            testFail();
        }
    }   
}

void
readFromMem8(u32 test)
{
    u32     count = 0;
    u8      *ptr, check, value;

    for (count = 0; count < DCACHE_SIZE; count++) {
        if (test == VALUE_00) {
            value = 0;
        } else if (test == VALUE_FF) {
            value = 0xff;
        } else {
            value = ((u8) testBuf) + count;
        }

        ptr = (u8 *) (((u32) testBuf) + count);
        check = *ptr;
        if (check != value) {
            testFail();
        }
    }   
}

void
doMemcpyTest(void)
{
    u8      *src = testBuf;
    u8      *dst = dstBuf;
    u32     count;

    /* Assign some random data to the buffer */
    for (count = 0; count < MEMCPY_SIZE; count++) {
        *src++ = (u8) ((count * 3372) + 198);
    }
    src = (u8 *) testBuf;

    /* Perform the memcpy */
    memcpy(dst, src, MEMCPY_SIZE);

    /* Compare the source and destination data */
    for (count = 0; count < MEMCPY_SIZE; count++) {
        if (src[count] != dst[count]) {
            testFail();
        }
    }
}

void
doAesTest(void)
{
    u8      *data = testBuf;
    u8      *enc = dstBuf;
    u8      *dec = dstBuf2;
    u32     swKey[4], swIv[4];
    u32     count;

    /* Assign some random data to the buffer */
    for (count = 0; count < AES_SIZE; count++) {
        *data++ = (u8) ((count * 2193) + 442);
    }
    data = (u8 *) testBuf;

    /* Perform encryption using the software AES engine */
    memset(swKey, 0, sizeof (swKey));
    memset(swIv, 0, sizeof (swIv));
    aes_sw_encrypt((u8 *) swKey, (u8 *) swIv, data, AES_SIZE * 8, enc);

    /* Perform decryption using the software AES engine */
    memset(swKey, 0, sizeof (swKey));
    memset(swIv, 0, sizeof (swIv));
    aes_sw_decrypt((u8 *) swKey, (u8 *) swIv, enc, AES_SIZE * 8, dec);

    /* Compare the original data and decrypted text */
    for (count = 0; count < AES_SIZE; count++) {
        if (data[count] != dec[count]) {
            testFail();
        }
    }
}


void
mmuTest(void)
{
    u32     cycles = 5, count;

    while (cycles-- > 0) {
        /* Simple memory test */
        for (count = 0; count < (sizeof(tests) / sizeof(tests[0])); count++) {
            /* 32-bit test */
            writeToMem32(tests[count]);
            readFromMem32(tests[count]);

            /* 16-bit test */
            writeToMem16(tests[count]);
            readFromMem16(tests[count]);

            /* 8-bit test */
            writeToMem8(tests[count]);
            readFromMem8(tests[count]);
        }

        /* Memory test with memcpy */
        doMemcpyTest();

        /* Memory test with AES software engine */
        doAesTest();
    }

    /* Test passed */
    IOS_OutputLed(0x34);
}
