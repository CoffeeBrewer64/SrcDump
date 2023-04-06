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

#ident "$Id: test_util.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"

/*
 * System includes
 */
 
#ifdef LINUX
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <getopt.h>
	#include <string.h>
	#include <linux/ioctl.h>
	#include <iostypes.h>
#else
	#include <ios.h>
	#ifdef VERSA
		#include "ios_pci.h"
		#include <versaios.h>
	#endif
	#include <iostypes.h>
	#include <ioslibc.h>
	
	#include "sd.h"
	#include "sd_ioctl.h"
	#include "sdio_rm.h"
#endif

/*
 * Local includes
 */
//#include "./sd_test.h"
//#include "./sd_api.h"
#include <sd_ioctl.h>

/*
 * mem_dump
 */
void
mem_dump (char *buf, int len)
{
    int  i;
    char *p;
    
    for (i = 0, p = buf; i < len; i++, p++) {
        printf (" 0x%x", *p & 0xff);
        if (i && ((i % 15) == 0)) {
            printf ("\n");
        }
    }
    printf ("\n");
    
    return;
}

struct _slot_regsx {
    unsigned int addr;
    char *name;
} slot_regsx[] = {
    { 0x0, "sysaddrl" },
    { 0x2, "sysaddrh" },
    { 0x4, "blocksz" },
    { 0x6, "blockcnt" },
    { 0x8, "arglo" },
    { 0xa, "arghi" },
    { 0xc, "transmode" },
    { 0xe, "command" },
    { 0x10, "res" },
    { 0x12, "res" },
    { 0x14, "res" },
    { 0x16, "res" },
    { 0x18, "res" },
    { 0x1a, "res" },
    { 0x1c, "res" },
    { 0x1e, "res" },
    { 0x20, "buffdplo" },
    { 0x22, "buffdphi" },
    { 0x24, "pstate" },
    { 0x26, "pstate" },
    { 0x28, "host/pwrctrlreg" },
    { 0x2a, "blockgapreg" },
    { 0x2c, "clockctrl" },
    { 0x2e, "timeoutctrl" },
    { 0x30, "normintrstat" },
    { 0x32, "errintrstat" },
    { 0x34, "norintrsen" },
    { 0x36, "errintrsen" },
    { 0x38, "norintrsgen" },
    { 0x3a, "errintrsgen" },
    { 0x3c, "auto12" },
    { 0x3e, "none" },
    { 0x40, "capability" },
    { 0x42, "capability" },
    { 0x44, "capbilityr" },
    { 0x46, "capbilityr" },
    { 0x48, "maxcurr" },
};

/*
 * reg_name
 */
char *
reg_name(int reg)
{
    char *name = "unknown";
    int  index;

    for (index = 0; index < (sizeof(slot_regsx)/sizeof(struct _slot_regsx));
         index++) {
        if (slot_regsx[index].addr == reg) {
            return slot_regsx[index].name;
        }
    }

    return name;
};

struct _manuf_name {
    int  manuf_number;
    char *manuf_name;
} manuf_names[] = {
    { 0x02d0, "Broadcom" },
};

char *
manuf_name (int manuf)
{
    int i;

    for (i = 0; i < (sizeof(manuf_names)/sizeof(struct _manuf_name)); i++) {
        if (manuf_names[i].manuf_number == manuf) {
            return manuf_names[i].manuf_name;
        }
    }

    return "unknown";
}

struct _tuple_name {
    int  tuple_number;
    char *tuple_name;
} tuple_names[] = {
    { 0x20, "manufacturer id" },
    { 0x21, "function id" },
    { 0x22, "functions extensions" },
    { 0xff, "terminal" },
};

char *
tuple_name (int tuple)
{
    int i;

    for (i = 0; i < (sizeof(tuple_names)/sizeof(struct _tuple_name)); i++) {
        if (tuple_names[i].tuple_number == tuple) {
            return tuple_names[i].tuple_name;
        }
    }

    return "unknown";
}

struct _decode {
    int  shift;
    char *status_string;
} decode[] = {
    { 31, "OUT_OF_RANGE" },
    { 30, "ADDRESS_ERROR" },
    { 29, "BLOCK_LEN_ERROR" },
    { 28, "ERASE_SEQ_ERROR" },
    { 27, "ERASE_PARAM" },
    { 26, "WP_VIOLATION" },
    { 25, "CARD_IS_LOCKED" },
    { 24, "LOCK_UNLOCK_FAILED" },
    { 23, "COM_CRC_ERROR" },
    { 22, "ILLEGAL_COMMAND" },
    { 21, "CARD_ECC_FAILED" },
    { 20, "CC_ERROR" },
    { 19, "ERROR" },
    { 18, "reserved" },
    { 17, "reserved" },
    { 16, "SCD_OVERWRITE" },
    { 15, "WP_ERASE_SKIP" },
    { 14, "CARD_ECC_DISABLED" },
    { 13, "ERASE_RESET" },
    { 8, "READY_FOR_DATA" },
    { 7, "reserved" },
    { 6, "reserved" },
    { 5, "APP_CMD" },
    { 4, "SDIO" },
    { 3, "AKE_SEQ_ERROR" },
    { 2, "reserved" },
    { 1, "reserved" },
    { 0, "reserved" },
};

#ifndef LINUX
void sprintf(char* outs, char* fmt, char* srce1, char* srce2)
{
	outs = strchr(srce1,0);
	memcpy(outs, srce2, strnlen(srce2,20));
}
#endif

/*
 * decode_card_status
 */
char card_status_string[512];
char *
decode_card_status (int card_status)
{
    int i;
    char *state_string;

    card_status_string[0] = '\0';

    for (i = 0; i < (sizeof(decode)/sizeof(struct _decode)); i++) {
        if (card_status & (1 << decode[i].shift)) {
            sprintf (&card_status_string[0], "%s %s", 
                     &card_status_string[0], decode[i].status_string);
        }
    }

    switch ((card_status & 0x1e00) >> 9) {
    case 0:
        state_string = "idle";
        break;
    case 1:
        state_string = "ready";
        break;
    case 2:
        state_string = "ident";
        break;
    case 3:
        state_string = "stby";
        break;
    case 4:
        state_string = "tran";
        break;
    case 5:
        state_string = "data";
        break;
    case 6:
        state_string = "rcv";
        break;
    case 7:
        state_string = "prg";
        break;
    case 8:
        state_string = "dis";
        break;
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
        state_string = "reserved";
    case 0xf:
        state_string = "resvd for i/o mode";
    }
    sprintf (&card_status_string[0], "%s %s",
             &card_status_string[0], state_string);

    return &card_status_string[0];
}

struct _decode device_decode[] = {
    { 0, "inserted" },
    { 1, "removed" },
    { 2, "write protected" },
    { 3, "suspended" },
    { 16, "memory" },
    { 17, "sdio" },
    { 18, "combo" },
    { 19, "mmc" },
};

/*
 * decode_card_status
 */
char device_status_string[512];
char *
decode_device_status (int device_status)
{
    int i;

    device_status_string[0] = '\0';

    for (i = 0; i < (sizeof(device_decode)/sizeof(struct _decode)); i++) {
        if (device_status & (1 << device_decode[i].shift)) {
            sprintf (&device_status_string[0], "%s %s", 
                     &device_status_string[0], device_decode[i].status_string);
        }
    }

    return &device_status_string[0];
}

#define NUM_REGS 0x22

unsigned short saved_value[NUM_REGS];

#define BUF_LEN 512
char decode_buff[BUF_LEN];
char *
decode_reg_diff(int reg, unsigned int data)
{
    memset (&decode_buff[0], 0, BUF_LEN);

    switch (reg) {
    case 0x08:
        sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "command argument");
        break;
    case 0xc:
        if (data & 0x01) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "DMA enable");
        if (data & 0x02) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "block count enable");
        if (data & 0x04) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "auto CMD12");
        if (data & 0x10) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "data transfer direction");
        if (data & 0x20) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "multi/single block");
        break;
    case 0x0e:
        sprintf (&decode_buff[0], "%s %s %x,", 
                     &decode_buff[0], "command") ;//, (data & (0x3f << 8)) >> 8);
        sprintf (&decode_buff[0], "%s %s %x,", 
                     &decode_buff[0], "type"); //, (data & (0x3 << 6)) >> 6);
        sprintf (&decode_buff[0], "%s %s %x,", 
                     &decode_buff[0], "response"); //, (data & 0x3));
        if (data & 0x04) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "CRC check");
        if (data & 0x10) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "index check");
        if (data & 0x20) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "data present");
        break;
    case 0x24:
        if (data & 0x01) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "cmd inhibit CMD");
        if (data & 0x02) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "cmd inhibit DATA");
        if (data & 0x04) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "DAT line active");
        if (data & 0x0100) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "write transfer active");
        if (data & 0x0200) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "read transfer active");
        if (data & 0x0400) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "buffer write enable");
        if (data & 0x0800) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "buffer read enable");
        break;
    case 0x26:
        if (data & 0x01) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "inserted");
        if (data & 0x02) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "stable");
        if (data & 0x04) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "pin_level");
        if (data & 0x08) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "WP pin_level");
        if (data & 0x10) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "WP pin_level");
        if (data & 0xf0)
            sprintf (&decode_buff[0], "%s 0x%x", 
                     &decode_buff[0], "data...") ; //data & 0xf0);
        break;
    case 0x28:
        if (data & 0x01) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "LED_on");
        if (data & 0x02) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "data_width");
        if (data & 0x04) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "high_speed");
        if (data & 0x100)
            sprintf (&decode_buff[0], "%s %s, 0x%x", 
                     &decode_buff[0], "bus_power"); //, data & 0xe00);
        break;
    case 0x2c:
        if (data & 0x01) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "internal_clock_enable");
        if (data & 0x02) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "clock_stable");
        if (data & 0x04) 
            sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "SD_clock_enable");
        if (data & 0xff00)
            sprintf (&decode_buff[0], "%s %s, 0x%x", 
                     &decode_buff[0], "clock_divisor"); //, data & 0xff00);
        break;
    case 0x2e:
        sprintf (&decode_buff[0], "%s %s,", 
                     &decode_buff[0], "timeout value");
        break;
    default:
        break;
    }

    return (&decode_buff[0]);
}

/* eof */
