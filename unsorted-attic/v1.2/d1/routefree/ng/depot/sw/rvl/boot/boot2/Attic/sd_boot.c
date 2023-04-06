/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: sd_boot.c,v 1.1 2006/05/05 21:46:55 jlivesey Exp $
 */

/*
 * This is a version of boot2 modified to do the following:
 *
 *  + Read boot3 off an SD card.
 *  + Decrypt, and hash.
 *  + Fit within one Flash block (128k)
 *
 * Components:
 *
 *  + Crypto version of IOS kernel.
 *  + SD card resource manager.
 *  + Driver thread (this file)
 *
 * Steps:
 *
 *  + Create an encryption object and load the common key.
 *  + Check that an SD card has been inserted.
 *  + Open the SD device.
 *  + Load a Wad header off the SD card that describes the rest 
 *    of boot3.
 *  + Parse and verify the eticket.
 *  + Read pages from the SD card into a staging area in DDR,
 *    decryptiong each page and accumulating a hash.
 *  + When all pages have been read, copy the image of boot3 down
 *    into sram, using its elf header for addresses and lengths.
 *
 * SD Card Layout:
 *
 *  Here is what we assume is the layout of the image on an SD
 *  card:
 *                                      Page
 *    _______________________________ 
 *    | esWadHdr  |  eTicket ---->  |    0
 *    | eTicket -> | loader.bin     |    1
 *    | elfhdr | phdr  | segment0 - |    2
 *    | ------------> segment1 .... |    3
 *    |                             |
 *    |                             |
 *
 */

#include <iostypes.h>
#include <iop.h>
#include <elf.h>
#include <ios.h>
#include <ioslibc.h>
#include <sys.h>
#include <es.h>

#include "boot2.h"

#define STACK_SIZE 4096
const u8 _initStack[STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 126;

ESWadHeader wadHdr;

/*
 * Output a value to the LEDs
 */
void
outputLed(u8 value)
{
    u32 reg;

    reg = busRd32(GPIIOPOUT_REG);
    reg = (reg & ~GPIIO_PIO_ENABLE) | ((value & 0xff) << GPIIO_PIO_SHIFT);
    busWrt32(GPIIOPOUT_REG, reg);
}


/*
 * debugLed
 */
void
debugLed(u8 value)
{
    outputLed(value);
    busDelay(LED_DELAY*2);
}

/*
 * bootFailure
 *
 * Boot failed for some reason.   Loop flashing the reason
 * on the Leds.
 */
void
bootFailure(u32 reason)
{

    printf ("%s: reason 0x%x\n",
            __FUNCTION__, reason);

    while (1) {
        outputLed (reason);
        busDelay (LED_DELAY);
        outputLed (0);
        busDelay (LED_DELAY);
    }
}

/*
 * loadWadHeader
 *
 * Load the wad header from the first page.
 */
IOSError
loadWadHeader(ESWadHeader *wadHdr, u32 *dataBuf)
{
    IOSError rc = IOS_ERROR_OK;
    u32 page = 0;

    printf ("%s: wadHdr 0x%08x dataBuf 0x%08x\n",
            __FUNCTION__, (u32)wadHdr, (u32)dataBuf);

    rc = sd_read(page, dataBuf, SD_PAGE_LEN);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: sd_read failed 0x%08x\n",
                __FUNCTION__, rc);
        bootFailure(BOOT_ERR_SD);
    }

     /* Handle the wad header endianness */
    memcpy(wadHdr, dataBuf, sizeof (ESWadHeader));
    wadHdr->hdrSize = ntohl(wadHdr->hdrSize);
    wadHdr->contentOffset = ntohl(wadHdr->contentOffset);
    wadHdr->certSize = ntohl(wadHdr->certSize);
    wadHdr->ticketSize = ntohl(wadHdr->ticketSize);
    wadHdr->tmdSize = ntohl(wadHdr->tmdSize);
    wadHdr->metaSize = ntohl(wadHdr->metaSize);
    wadHdr->metaCid = ntohl(wadHdr->metaCid);

    /*
     * Check the header:
     *
     *  - For simplicity, assert that the header size is smaller
     *    than one page, and that the content offset is smaller
     *    than one flash block
     *  - The offset to the start of content has to be aligned to
     *    64 byte boundary for SHA operations
     */
    if ((wadHdr->hdrSize != sizeof (ESWadHeader)) ||
            (wadHdr->hdrSize > (1 << SD_PAGE_SHIFT)) ||
            (wadHdr->contentOffset > (1 << SD_MAX_PAGE_SHIFT)) ||
            (wadHdr->contentOffset & (ALIGN_SZ - 1))) {
        rc = BOOT_ERR_WAD;
        return rc;
    }

    BOOT2_EXIT();

    return rc;
}

/*
 * verifyBundle
 *  - Verify the certs, tmd, and ticket
 *  - Output the decryption key, public key, and content hash
 *  - Check to make sure the content can fit into the load area
 *
 * XXX Since the SD content is under our control, is it necessary
 * to verify the eticket in the same detail as for a game?
 */
IOSError
verifyBundle(u32 blockOffset, ESWadHeader *wadHdr, u32 *contentSize,
    CSLOSAesKey *aesKey, CSLOSAesIv *iv, CSLOSSha1Hash *hash, u32 base)
{
    IOSError rc = IOS_ERROR_OK;

    /*
     * This routine should be replaced by the memory version
     * of launchOSFromMem()
     */

    return rc;
}

/*
 * load_from_sd
 *
 * Read each page from SD card to DDR staging area, decrypt,
 * accumulate hash.
 *
 * XXX ToDo: hash accumulation and checking.
 */
IOSError
load_from_sd(u32 base, u32 start_page)
{
    IOSError rc = IOS_ERROR_OK;
    u32 page;
    u8 *addr = (u8 *)base, *src;
    u32 *decode_buffer = (u32 *)BOOT3_DECODE_BUFFER;
    u32 max_pages = SD_MAX_PAGES, offset, len;
    u32 blockOffset = 0, contentSize;

    printf ("%s: base 0x%08x start page %d\n",
            __FUNCTION__, base, start_page);

    debugLed (0xc1);

    rc = sd_init();
    if (rc != IOS_ERROR_OK) {
        printf ("%s: sd_init failed %d\n",
                __FUNCTION__, rc);
        bootFailure(BOOT_ERR_SD);
    }

    /*
     * I am assuming here that the first page or two loaded are not
     * encrypted and contain the wad header that describes the rest of
     * the data, plus the start of the data.
     */
    rc = loadWadHeader(&wadHdr, decode_buffer);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: loadWadHeader failed %d\n",
                __FUNCTION__, rc);
        bootFailure(BOOT_ERR_WAD);
    }

    /* 
     * Verify certs, tmd, and ticket.   We don't have to worry about
     * bad blocks, so blockOffset is set to 0.
     */
    rc = verifyBundle(blockOffset, &wadHdr, &contentSize,
                      NULL, 0, NULL, 0 /* &aesKey, ivPtr, &hash, base */ );
    if (rc != IOS_ERROR_OK) {
        printf ("%s: verifyBundle failed %d\n",
                __FUNCTION__, rc);
        bootFailure(BOOT_ERR_ETICKET);
    }


    /*
     * After the wad header has been loaded, the content begins
     * at an offset into some page.
     */
    start_page = wadHdr.contentOffset >> SD_PAGE_SHIFT;
    offset = wadHdr.contentOffset & (SD_PAGE_LEN - 1);
    src = (u8 *)(decode_buffer + offset);
    len = SD_PAGE_LEN - offset;

    for (page = start_page; page < max_pages; 
         page++, addr += len) {

        rc = sd_read(page, decode_buffer, SD_PAGE_LEN);
        if (rc != IOS_ERROR_OK) {
            printf ("%s: sd_read failed %d\n",
                    __FUNCTION__, rc);
            bootFailure(BOOT_ERR_SD);
        }

        rc = aes_decode(src, len, addr);
        if (rc != IOS_ERROR_OK) {
            printf ("%s: aes_decode failed %d\n",
                    __FUNCTION__, rc);
            bootFailure(BOOT_ERR_AES);
        }

        /*
         * In subsequent pages, the offset is zero.
         */
        src = (u8 *)decode_buffer;
        len = SD_PAGE_LEN;
        
    }

    BOOT2_EXIT();

    return rc;
}

/*
 * copy_to_dest
 *
 * On entry, the data from the SD card has been decrypted and is
 * in the staging area.
 *
 * Copy the segments from the DDR staging area to the destination
 * given in the elf header, usually to sram.   Then jump to the
 * entry address.
 *
 * XXX There is a problem here in that IOS currently creates the
 * normal and the exception stack in sram, and we can't risk
 * over-writing our auto data.  Perhaps we can have a different 
 * init.s for IOS to put the stacks into a different memory.
 */
void
copy_to_dest(u32 base)
{
#if 0
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
    u32 count;

    /* Elf and program headers */
    ehdr = (Elf32_Ehdr *)base;
    phdr = (Elf32_Phdr *)(base + sizeof (Elf32_Ehdr));

    /* quick check of phdr */
    if (ehdr->e_phnum <= 0) {
        printf ("%s: corrupt phdr?\n",
                __FUNCTION__);
        return;
    }

    /* Copy the data down from the staging area into sram */
    for (count = 0; count < ehdr->e_phnum; count++) {
        if (phdr[count].p_type != PT_LOAD) {
            continue;
        }
        memcpy((u8 *)phdr[count].p_vaddr, 
               (u8 *)(base + phdr[count].p_offset), phdr[count].p_filesz);
    }
#else

    /*
     * Don't interpret the elf headers ourselves.   Instead jump
     * to the entry point of loader.bin, which is the first thing
     * in the loaded code.
     */

#endif  /* 0 */

    /* XXX need to get the entry address */

    /* Jump to the entry point */
    asm ("    nop");
}

/*
 * main
 */
void
main(void)
{
    IOSError rc = IOS_ERROR_OK;

    BOOT2_ENTRY();

    debugLed (0xa1);

    debugLed (0xa2);

    rc = init_aes();
    if (rc != IOS_ERROR_OK) {
        printf ("%s: init_aes failed %d\n",
                __FUNCTION__, rc);
        bootFailure(BOOT_ERR_AES);
    }

    debugLed (0xa3);

    rc = load_from_sd(BOOT3_STAGE_ADDR, BOOT3_START_PAGE);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: load_from_sd failed %d\n",
                __FUNCTION__, rc);
        bootFailure(BOOT_ERR_SD);
    }

    debugLed (0xa4);

    /*
     * This call should not return.
     */
    copy_to_dest(BOOT3_STAGE_ADDR);

    /*
     * If we get to here, something went wrong with loading.
     */
    bootFailure(BOOT_ERR_ELF);
}

/* eof */
