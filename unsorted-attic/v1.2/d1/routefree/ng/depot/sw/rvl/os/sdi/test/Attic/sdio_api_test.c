
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: sdio_api_test.c,v 1.1 2006/03/30 16:50:23 gbarnard Exp $
 */

char ident[] = "$Id: sdio_api_test.c,v 1.1 2006/03/30 16:50:23 gbarnard Exp $";

#ifdef LINUX
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>
	#include <iossdiotypes.h>
	#include <iosresource.h>
	#include <sys/types.h>
	
	#include <stdio.h>   /* for printf */
	#include <stdlib.h>  /* for getenv */
	#include <string.h>  /* for memcpy */
	#include <unistd.h>  /* for sleep */
#else
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>
	#include "sd.h"
	#include "sd_ioctl.h"
	#include "sdio_rm.h"
	#include "sd_debug.h"
	
	#define IOS_ThreadExit(X)  IOS_DestroyThread(0, NULL)
	//get_cmdline(char *buf, unsigned long bufLen)

#endif


#include "sdio_api.h"
#include "sdio_test.h"
#include "sdio_api_test.h"

SDDevHandle Handles[MAX_SLOTS][MAX_FUNCS];
bool interactive = false;

/* 
 * Parameters for message queue used to register driver. If there were
 * applications that used this driver, they would talk to it via this
 * queue.
 */
#define MSGQ_SIZE 8
#define PID_MASK 0xFFFFFFFF

tasks_t cmd52_data[] = {
    /* Round 1   */
    { SDIO_WR, SDIO_CMD52, 0, 1, 0x80c0, 1, 0x03, 0x03, 0, 0 },
    { SDIO_WR, SDIO_CMD52, 0, 1, 0x80c1, 1, 0x00, 0x00, 0, 0 },
    { SDIO_WR, SDIO_CMD52, 0, 1, 0x80c2, 1, 0x00, 0x00, 0, 0 },
    { SDIO_WR, SDIO_CMD52, 0, 1, 0x80c3, 1, 0x00, 0x00, 0, 0 },    
    { SDIO_RD, SDIO_CMD52, 0, 1, 0x80c0, 1, 0x0, 0x03, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 1, 0x80c1, 1, 0x0, 0x00, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 1, 0x80c2, 1, 0x0, 0x00, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 1, 0x80c3, 1, 0x0, 0x00, 0, 0 },
    /* Round 2   */
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
};

//    t_rw; t_cmd; t_slot; t_func; t_reg; t_width; t_data; t_exp; t_incr; t_dma;
    
tasks_t cmd53_data[] = {
    #if 1
    #if 0
    	{ SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x11223344, 0x0, 1, SDIO_PIO },
    #else
    	{ SDIO_WR, SDIO_CMD53, 0, 1, 0x80c4, 4, 0x03000000, 0x0, 1, SDIO_DMA },
    #endif
    #if 0
		{ SDIO_RD, SDIO_CMD53, 0, 1, 0x80c4, 4, 0x0, 0x11223344, 1, SDIO_PIO },    	  
    #else 
   	 	{ SDIO_RD, SDIO_CMD53, 0, 0, 0x80c4, 8, 0x0, 0x55667788, 1, SDIO_DMA },
    #endif
    #endif
    
    /* Round 1   */
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40003, 0x0, 1, SDIO_DMA }, 
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_PIO },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_DMA },
    /* Round 2   */
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x30004, 0x0, 1, SDIO_DMA },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x30004, 1, SDIO_PIO },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x30004, 1, SDIO_DMA },
    /* Round 3   */
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40003, 0x0, 1, SDIO_DMA },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_PIO },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_DMA },
    /* Round 4   */
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x30004, 0x0, 1, SDIO_DMA },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x30004, 1, SDIO_PIO },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x30004, 1, SDIO_DMA },
};

tasks_t cmd_52_53_data[] = {
    /* Round 1   */
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40003, 0x0, 1, SDIO_DMA },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_PIO },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_DMA },
    /* round 2   */
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    { SDIO_WR, SDIO_CMD52, 0, 0, 0x1000, 1, 0x20, 0x0, 0, 0 },
    { SDIO_RD, SDIO_CMD52, 0, 0, 0x1000, 1, 0x0, 0x20, 0, 0 },
    /* Round 3   */
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40003, 0x0, 1, SDIO_DMA },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_PIO },
    { SDIO_RD, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x0, 0x40003, 1, SDIO_DMA },
};

tasks_t cmd_bcm_data[] = {
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40003, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40003, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80b0, 4, 0x95, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80b4, 4, 0xc6, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x80c0, 4, 0x40013, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0xf0001, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0xf0000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0xd0000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x70000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x50000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9120, 4, 0x400, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9120, 4, 0x400, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9160, 4, 0x10000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9160, 4, 0x10000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9164, 4, 0xaa5555aa, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9160, 4, 0x10000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9160, 4, 0x10000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9164, 4, 0x55aaaa55, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9160, 4, 0x10000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9160, 4, 0x10000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9164, 4, 0xee94ba46, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x118c, 2, 0xaaaa, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x918c, 4, 0xccccbbbb, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x918c, 4, 0x0, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x50004, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f90, 4, 0x2000020, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x200f0005, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f90, 4, 0x20, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x200c0005, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x200f0001, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x200f0000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x200d0000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x20070000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x20050000, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9120, 4, 0x80000400, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9120, 4, 0x80000400, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13e6, 2, 0x0, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13f6, 2, 0x1, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13f6, 2, 0x1, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fc, 2, 0x811, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fe, 2, 0x5ff, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fc, 2, 0x812, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fe, 2, 0x20, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fc, 2, 0x449, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fc, 2, 0x811, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fe, 2, 0x5ff, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fc, 2, 0x812, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13fe, 2, 0x20, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x13e6, 2, 0xf4, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x20050004, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f90, 4, 0x2000020, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x30005, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f90, 4, 0x20, 0x0, 1, SDIO_DMA },
    { SDIO_WR, SDIO_CMD53, 0, 1, 0x9f98, 4, 0x5, 0x0, 1, SDIO_DMA },
};


int
getNextToken(char **next, char **rest)
{
    int valid = 0;
    char *p = *rest, *n;

    /* Strip leading white space */
    while (*p == ' ') {
        ++p;
    }
    *next = p;
    n = p;
    /* Find end of token */
    while (*n && *n != ' ') {
        valid = 1;
        ++n;
    }
    /* Strip trailing white space */
    while (*n == ' ') {
        *n++ = 0;
    }
    *rest = n;
    return valid;
}

#define LINE_SIZE 256
/*
 * interact
 *
 * Output a message and return true/false as the reply does/does not
 * match the expected response.
 */
bool
interact (char *question, char *resp)
{


    
    #ifdef LINUX
    {
	    char * line = NULL;
	    size_t len = 0;
	    ssize_t read;    	
	    extern FILE *stdin;
	    FILE * fp;
	 
	 	printf ("%s ", question);
	    fp = stdin;
	    if (fp == NULL)
        	exit(1);
        	if ((read = getline(&line, &len, fp)) != -1) {
	        if (!strncmp(line, resp, strlen(resp))) {
	            return true;
	        }
	    }
    }
    #else
    {
		char line[LINE_SIZE];
		char *cmd;
    	int cmdLen;	
    	char ch;
    		
    	printf ("%s ", question);
    	ch = getchar(); gets(line);
    	printf("Read line = %s %d\n",line,ch);
    	
	    getNextToken(&cmd, (char**)&line);
	    cmdLen = strnlen(cmd, LINE_SIZE);
	    if (0 == cmdLen) return false;
	    printf("cmd=%s, resp=%s\n",cmd,resp);
	    if (!strncmp(cmd, resp, cmdLen)) 
	    {
	    	printf("return\n");
	    	return true;
	    }
        
    }
    #endif

    return false;
}


// ======= IRQ TEST =======

#define FATAL_ONLY   0
#define DEBUG_ERR    1
#define DEBUG_CHATTY 2

int debug_level = FATAL_ONLY;

void
callback_interrupt (int arg)
{
    printf ("%s: mask 0x%x\n",
            __FUNCTION__, arg);

    return;
}

void
callback_removal (int arg)
{
    printf ("%s: mask 0x%x\n",
            __FUNCTION__, arg);

    return;
}

void
callback_error (int arg)
{
    printf ("%s: mask 0x%x\n",
            __FUNCTION__, arg);

    return;
}

/*
 * inst_callback()
 * 
 * inst [0,1] [ "intr" | "rem" | "err" ]
 */
bool
inst_callback (int dev, char *type, int install)
{
    SDDevHandle fd;
    IOSError status;
    int data;

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: dev 0x%x type %s %s\n",
                __FUNCTION__, dev, type, install ? "install" : "uninstall");

    fd = Handles[dev][0];

    if (!strncmp (type, "intr",4)) {
        if (install) {
            ISD_RegisterDeviceIntrHandler(fd, callback_interrupt, 
                                          (void *)&data);
        } else {
            ISD_UnregisterDeviceIntrHandler(fd);
        }
    }

    if (!strncmp (type, "rem",3)) {
        if (install) {
            ISD_RegisterDeviceRemovalHandler(fd, callback_removal, 
                                             (void *)&data);
            //status = sdio_thread_create (fd, SDDevRemove);
            if (status != IOS_ERROR_OK) {
                printf ("%s: thread creation failed status 0x%x\n",
                        __FUNCTION__, status);
                return false;
            }
        } else {
            ISD_UnregisterDeviceRemovalHandler(fd);
        }
    }

    if (!strncmp (type, "err",3)) {
        if (install) {
            ISD_RegisterDeviceErrorHandler(fd, callback_error, 
                                           (void *)&data);
        } else {
            ISD_UnregisterDeviceErrorHandler(fd);
        }
    }


    return true;
}

/*
 * slot_crack_cis
 */
bool
slot_crack_cis (unsigned char *tuple_data)
{
    int i, j, next;
    unsigned int code, offset;

    i = 0;
    do {
        code = *tuple_data;
        i++;
        tuple_data++;
        offset = *tuple_data;
        printf ("%s: code 0x%x (%s) length 0x%x\n",
                __FUNCTION__, code, tuple_name(code), offset);
        if ((code == 0xff) || (code == 0x0)) {
            break;
        }
        i++;
        tuple_data++;
        next = i + offset;
        printf ("%s: tuple data: ",
                __FUNCTION__);
        for (j = i; j < next; j++) {
            printf ("0x%x ", *tuple_data & 0xff);
            tuple_data++;
        }
        printf ("\n");
    } while (code != 0xff);

    printf ("%s: done\n",
             __FUNCTION__);

    return true;
}

#define CIS_BUFF_LEN 64
/*
 * sdio_cis_test
 */
void
sdio_cis_test (int slot)
{
    SDDevHandle fd;
    IOSError status;
    int function = 1;
    unsigned char* cis_buffer; //[CIS_BUFF_LEN];

    fd = Handles[slot][0];

    cis_buffer = (unsigned char *) malloc (CIS_BUFF_LEN);
    if (!cis_buffer) {
        perror ("malloc");
        return;
    }
   
    memset (cis_buffer, 0, CIS_BUFF_LEN);
    status = ISD_ReadCIS(fd, function, cis_buffer, CIS_BUFF_LEN);
    if (status != IOS_ERROR_OK) {
        printf ("Bad ReadCIS\n");
        return;
    }
    slot_crack_cis(cis_buffer);

    return;
}

/*
 * sdio_cccr_test
 */
void
sdio_cccr_test (void)
{

    return;
}

/*
 * sdio_cmd52_test
 *
 * Cmd52 allows you to transfer data to or from a single register
 * on a card.
 */
void
sdio_cmd52_test (int slot)
{
    int i;
    tasks_t *tp;
    SDDevHandle fd;
    IOSError status;
    unsigned int data;

    //for (i = 0; i < 8; i++) { 
   	for (i = 0; i < (sizeof(cmd52_data)/sizeof(tasks_t)); i++) {
        tp = &cmd52_data[i];
        fd = Handles[slot][tp->t_func];
        switch (tp->t_rw) {
        case SDIO_RD:
            data = 0;
            status = ISD_ReadReg(fd, tp->t_reg, &data);
            if (data == tp->t_exp) {
                printf ("Good data: read reg 0x%x data 0x%x %s\n",
                        tp->t_reg, data,
                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
            } else {
                printf ("Bad data: read reg 0x%x data 0x%x != 0x%x %s\n",
                        tp->t_reg, data, tp->t_exp,
                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
            }
            break;
        case SDIO_WR:
            status = ISD_WriteReg(fd, tp->t_reg, tp->t_data);
            break;
        default:
            printf ("Bad direction %d\n", tp->t_rw);
        }
    }

    return;
}

/*
 * sdio_cmd53_test
 *
 * Test of cmd53 data transfer.  Cmd 53 allows you to read or write
 * multiple registers, with either PIO or DMA operations, and it
 * allows the target address to be either fixed or incrementing.
 * Fixed addresses are useful for transferring data to or from fifos
 * and incrementing addresses for transferring data to or from
 * incrementing locations.
 */
void
sdio_cmd53_test (int slot)
{
    int i;
    tasks_t *tp;
    SDDevHandle fd;
    IOSError status;
    u32* data;
    
    /// --- debug ---
    u32 data1;
	data = &data1;
	//set_driver_debug(Handles[slot][0],0x10000801); //0x2401
	
	///ISD_ReadReg(Handles[slot][0], 0x1000, &data1);
	///ISD_ReadReg(Handles[slot][0], 0x1001, &data1);
	///ISD_ReadReg(Handles[slot][0], 0x1002, &data1);
	//ISD_WriteReg(Handles[0][0], 2, 2);	
	//ISD_WriteReg(Handles[0][0], 6, 1); // io abort fn1
	//ISD_WriteReg(Handles[0][0], 2, 2); // io enable fn1
//	sleep(1);
//	ISD_ReadReg(Handles[0][0], 3, data);	// io ready fn1...
//	printf("IO_Ready     :0x%02x\n",*data);		
	
//	ISD_ReadReg(Handles[0][0], 8, data);	// capabilities
//	printf("IO_Capability:0x%02x\n",*data);
	
	/// --- debug end ---
	
    for (i = 0; i < 2; i++) 
    {
    	printf("   *** TEST53 %d\n",i);
        tp = &cmd53_data[i];
        fd = Handles[slot][tp->t_func];
        switch (tp->t_rw) 
        {
        case SDIO_RD:
            data = (unsigned int *) malloc (tp->t_width);
            memset (data, 0x0, tp->t_width);
            status = ISD_ReadMultiReg(fd, tp->t_reg, tp->t_width, 
                                      tp->t_incr, data, tp->t_dma);
            if (*data == tp->t_exp) 
            {
                printf ("-Good data: read reg 0x%x data 0x%x %s\n",
                        tp->t_reg, *data,
                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
            } 
            else 
            {
                printf ("-Error[0x%04X] wr 0x%08X != 0x%08X %s\n",
                        tp->t_reg, *data, tp->t_exp,
                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
            }
            free (data);
            break;
        case SDIO_WR:
        {
        	unsigned int* dp = (unsigned int*)&tp->t_data; //{0x12345678,0x55667788,0x99AABBCC,0xDDEEFF11};
            //printf ("CMD53> Write data: reg 0x%x data 0x%x %s\n",
            //        tp->t_reg, tp->t_data, 
            //        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");        
            status = ISD_WriteMultiReg(fd, tp->t_reg, tp->t_width, 
                                       tp->t_incr, dp, tp->t_dma);
        }
            break;
        default:
            printf ("Bad direction %d\n", tp->t_rw);
        }
    }

    return;
}

/*
 * sdio_cmd53_test
 *
 * Test of cmd53 data transfer.  Cmd 53 allows you to read or write
 * multiple registers, with either PIO or DMA operations, and it
 * allows the target address to be either fixed or incrementing.
 * Fixed addresses are useful for transferring data to or from fifos
 * and incrementing addresses for transferring data to or from
 * incrementing locations.
 */
void
sdio_bcm_test (int slot)
{
    int i;
    tasks_t *tp;
    SDDevHandle fd;
    IOSError status;
    u32* data;
    
    /// --- debug ---
    u32 data1;
	data = &data1;

//	sleep(1);
//	ISD_ReadReg(Handles[0][0], 3, data);	// io ready fn1...
//	printf("IO_Ready     :0x%02x\n",*data);		
	
//	ISD_ReadReg(Handles[0][0], 8, data);	// capabilities
//	printf("IO_Capability:0x%02x\n",*data);
	
	/// --- debug end ---
	
    for (i = 0; i < (sizeof(cmd52_data)/sizeof(tasks_t)); i++) 
    {
    	printf("   *** BCM INIT %d\n",i);
        tp = &cmd53_data[i];
        fd = Handles[slot][tp->t_func];
        switch (tp->t_rw) 
        {
        case SDIO_RD:
            data = (unsigned int *) malloc (tp->t_width);
            memset (data, 0x0, tp->t_width);
            status = ISD_ReadMultiReg(fd, tp->t_reg, tp->t_width, 
                                      tp->t_incr, data, tp->t_dma);
            free (data);
            break;
        case SDIO_WR:
        {
        	unsigned int* dp = (unsigned int*)&tp->t_data; 
            printf ("CMD53> Write data: reg 0x%x data 0x%x %s\n",
                    tp->t_reg, tp->t_data, 
                    (tp->t_dma == SDIO_DMA) ? "dma" : "pio");        
            status = ISD_WriteMultiReg(fd, tp->t_reg, tp->t_width, 
                                       tp->t_incr, dp, tp->t_dma);
        }
            break;
        default:
            printf ("Bad direction %d\n", tp->t_rw);
        }
    }

    return;
}
/*
 * sdio_cmd_52_53_test
 *
 * A mixture of cmd52 and cmd53 operations.  This is not pointless,
 * because they can interfere with one another if the timing is not
 * right.
 */
void
sdio_cmd_52_53_test (tasks_t *tasks, int size)
{
    int i;
    tasks_t *tp;
    SDDevHandle fd;
    IOSError status;
    unsigned int data52, *data53;

    for (i = 0, tp = tasks; i < (size/sizeof(tasks_t)); i++, tp++) {
        fd = Handles[tp->t_slot][tp->t_func];
        switch (tp->t_cmd) {
        case SDIO_CMD52:
	        switch (tp->t_rw) {
	        case SDIO_RD:
                data52 = 0;
	            status = ISD_ReadReg(fd, tp->t_reg, &data52);
	            if (data52 == tp->t_exp) {
	                printf ("Good data: read reg 0x%x data 0x%x %s\n",
	                        tp->t_reg, data52,
	                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
	            } else {
	                printf ("Bad data: read reg 0x%x data 0x%x != 0x%x %s\n",
	                        tp->t_reg, data52, tp->t_exp,
	                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
	            }
	            break;
	        case SDIO_WR:
	            status = ISD_WriteReg(fd, tp->t_reg, tp->t_data);
	            break;
	        default:
	            printf ("Bad direction %d command %d\n", 
                        tp->t_rw, tp->t_cmd);
	        }
            break;
        case SDIO_CMD53:
            switch (tp->t_rw) {
	        case SDIO_RD:
	            data53 = (unsigned int *) malloc (tp->t_width);
                memset (data53, 0, tp->t_width);
	            status = ISD_ReadMultiReg(fd, tp->t_reg, tp->t_width, 
	                                      tp->t_incr, data53, tp->t_dma);
	            if (*data53 == tp->t_exp) {
	                printf ("Good data: read reg 0x%x data 0x%x %s\n",
	                        tp->t_reg, *data53,
	                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
	            } else {
	                printf ("Bad data: read reg 0x%x data 0x%x != 0x%x %s\n",
	                        tp->t_reg, *data53, tp->t_exp,
	                        (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
	            }
	            free (data53);
	            break;
	        case SDIO_WR:
	        {
	        	unsigned int* dp = (unsigned int*)&tp->t_data;
	            status = ISD_WriteMultiReg(fd, tp->t_reg, tp->t_width, 
	                                       tp->t_incr, dp, 
                                           tp->t_dma);
	            printf ("Write data: reg 0x%x data 0x%x %s\n",
	                    tp->t_reg, tp->t_data, 
	                    (tp->t_dma == SDIO_DMA) ? "dma" : "pio");
	        }
	            break;
	        default:
	            printf ("Bad direction %d commannd %d\n", 
                        tp->t_rw, tp->t_cmd);
	        }
            break;
        default:
            printf ("Bad command %d\n", tp->t_cmd);
        }
    }

    return;
}

/*
 * sdio_test1
 *
 * Test driver for the sdio_api_test program.
 */
void
sdio_test1 (void)
{
    SDDevConfig config;
    IOSError status;
    int function = 1;
/*
    if (interact ("Interactives? (y/n) ", "y")) {
        interactive = true;
        printf("--- Interactive Starting ---\n");
    }
*/
    memset (&config, 0, sizeof (config));
    config.SDDevSlot = 0;
    config.SDDevFunc = 0;
	
    printf ("*** ISD_AttachDevice slot %d function %d handle %x ***\n",
            config.SDDevSlot, config.SDDevFunc, Handles[config.SDDevSlot][config.SDDevFunc]);

    status = ISD_AttachDevice(&config, 
                              &Handles[config.SDDevSlot][config.SDDevFunc]);
    if (status != IOS_ERROR_OK) {
        printf ("Bad open\n");
        return;
    }
    else
    {
    	//printf(">>>>>>> Handle %X\n",Handles[config.SDDevSlot][config.SDDevFunc]);
    }
    
    // --- Set Debug Level, also doubles as a check to see if host driver can be accessed ---
    // 		Should succeed even without a card insterd in slot.
    set_driver_debug(Handles[config.SDDevSlot][0],1); //0x2401
  
  	printf("*** Install Interrupt Handler ***\n");
  	inst_callback(0,"inst",1);
  	
    printf ("*** Reset SDIO ***\n");
    status = ISD_ResetDevice(Handles[config.SDDevSlot][0]);
    if (status != IOS_ERROR_OK) {
        printf ("Bad reset\n");
        return;
    }
    printf ("Good reset\n");

	#if 0
    if (interactive && (!interact ("Next step? (y/n) ", "y"))) {
        return;
    }
    #endif

    printf ("*** Testing Function 1 ***\n");
	config.SDDevFunc = function;
	
	
    status = ISD_EnableDevice(Handles[config.SDDevSlot][0], config.SDDevFunc);
    if (status != IOS_ERROR_OK) {
        printf ("Bad enable\n");
        return;
    }
    printf ("Good enable\n");
    
    
    status = ISD_AttachDevice(&config, 
                              &Handles[config.SDDevSlot][config.SDDevFunc]);
    if (status != IOS_ERROR_OK) {
        printf ("Bad open\n");
        return;
    }
    printf ("Good Function Open\n");

	// - set debug level -
	//set_driver_debug(Handles[config.SDDevSlot][0],0x00000021); //0x2401
	
	#if 0
	    if (interactive && (!interact ("cis tests? (y/n) ", "y"))) {
	        return;
	    }
	#endif
		
	// - set debug level -
	//set_driver_debug(Handles[config.SDDevSlot][0],0x2001); //0x2401
	  
	#if 1
	    printf ("*** Run CIS tests on slot 0 function 1 *** \n");
	    sdio_cis_test (config.SDDevSlot);
	#endif

	#if 0
	    if (interactive && (!interact ("cmd52 tests? (y/n) ", "y"))) {
	        return;
	    }   
	#endif	
	
	#if 0     
	    printf ("*** Run cmd 52 tests on slot 0 function 1 ***\n");
	    sdio_cmd52_test (config.SDDevSlot);
	#endif

	#if 0
	    if (interactive && (!interact ("cmd53 tests? (y/n) ", "y"))) {
	        return;
	    }
	#endif	   
	
	#if 1 
		//set_driver_debug(Handles[config.SDDevSlot][0],1|DEBUG_SER_REG_MREAD|0x10002401);
	    printf ("*** Run cmd 53 tests on slot %d function 1 ***\n",config.SDDevSlot);
	    sdio_bcm_test(config.SDDevSlot);
	    sdio_cmd53_test (config.SDDevSlot);
	#endif

/*
    if (interactive && (!interact ("cmd52_53 tests? (y/n) ", "y"))) {
        return;
    }

    printf ("Run cmd 52_53 tests on slot 0 function 1\n");

    sdio_cmd_52_53_test (&cmd_52_53_data[0], sizeof(cmd_52_53_data));
*/
	// set_driver_debug(Handles[config.SDDevSlot][0],0x01); //0x2401

    ISD_DetachDevice(Handles[config.SDDevSlot][config.SDDevFunc]);
	
    return;
}

/*
 * sdio_api_test
 *
 * This is the 'mainline' of the sdio_api_test program.
 */
int
sdio_api_test (void)
{
    IOSCid devId;
    #if 0
    IOSMessageQueueId qid;
    IOSMessage msgQ[MSGQ_SIZE];
	#endif
    printf("*** SDIO API test program ***\n");

    //printf ("%s\n", ident);

    ISDIO_FindDevice(&devId);

	#if 0
    //printf("%s: devId %d\n",
    //       __FUNCTION__, devId);

    /* Create a message queue that clients use to communicate with this
     * driver
     */
    if ( (qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK )) < 0 ) {
        printf("Creating message queue failed\n");
        IOS_ThreadExit(0);
    }

    /* Register device */
    if ( IOS_ERROR_OK != ISDIO_RegisterResourceManager(devId, qid) ) {
        printf("Registering SDIO failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
   // else
   //     printf("SDIO registered successfully...\n");
	#endif
	
    sdio_test1();

    return 0; //IOS_ThreadExit(0);
}
