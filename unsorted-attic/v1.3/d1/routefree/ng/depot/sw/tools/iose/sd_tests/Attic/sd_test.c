
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id$
 */

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <iossdiotypes.h>
#include <iosresource.h>
#include <sys/types.h>

#include <stdio.h>   /* for printf */
#include <stdlib.h>  /* for getenv */
#include <string.h>  /* for memcpy */

#include <sdio_api.h>
#include "sd_test.h"

SDDevHandle Handles[MAX_SLOTS][MAX_FUNCS];

#define FATAL_ONLY   0
#define DEBUG_ERR    1
#define DEBUG_CHATTY 2

int debug_level = FATAL_ONLY;

/* Parameters for message queue used to register driver. If there were 
 * applications that used this driver, they would talk to it via this queue.
 */
#define MSGQ_SIZE 8
#define PID_MASK 0xFFFFFFFF

#define DATA_LEN 256


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
 * inst_callback
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

    if (!strcmp (type, "intr")) {
        if (install) {
            ISD_RegisterDeviceIntrHandler(fd, callback_interrupt, 
                                          (void *)&data);
        } else {
            ISD_UnregisterDeviceIntrHandler(fd);
        }
    }

    if (!strcmp (type, "rem")) {
        if (install) {
            ISD_RegisterDeviceRemovalHandler(fd, callback_removal, 
                                             (void *)&data);
            status = sdio_thread_create (fd, SDDevRemove);
            if (status != IOS_ERROR_OK) {
                printf ("%s: thread creation failed status 0x%x\n",
                        __FUNCTION__, status);
                return false;
            }
        } else {
            ISD_UnregisterDeviceRemovalHandler(fd);
        }
    }

    if (!strcmp (type, "err")) {
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
 * read_cis
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

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: done\n",
                __FUNCTION__);

    return true;
}

struct _reg_addrs {
    char *reg_name;
    int   reg_addr;
} cccr_reg_addrs[] = {
    { "revision", 0x0 },
    { "spec_revision", 0x1 },
    { "enable", 0x2 },
    { "ready", 0x3 },
    { "intenable", 0x4 },
    { "intpending", 0x5 },
    { "abort", 0x6 },
    { "intf", 0x7 },
    { "cap", 0x8 },
    { "cis0", 0x9 },
    { "cis1", 0xa },
    { "cis2", 0xb },
    { "suspend", 0xc },
    { "select", 0xd },
    { "exec", 0xe },
    { "ready", 0xf },
    { "block0", 0x10 },
    { "block1", 0x11 },
};

struct _reg_addrs fbr_reg_addrs[] = {
    { "functioncode", 0x100 },
    { "extended func", 0x101 },
    { "power", 0x102 },
    { "cis0", 0x109 },
    { "cis1", 0x10a },
    { "cis2", 0x10b },
    { "csa0", 0x10c },
    { "csa1", 0x10d },
    { "csa2", 0x10e },
};

int
cccr_register_addr (char *name)
{
    int i;

    for (i = 0; i < (sizeof(cccr_reg_addrs)/sizeof(struct _reg_addrs)); 
         i++) {
        if (!strcmp (name, cccr_reg_addrs[i].reg_name)) {
            return cccr_reg_addrs[i].reg_addr;
        }
    }

    return -1;
}

int
fbr_register_addr (char *name)
{
    int i;

    for (i = 0; i < (sizeof(fbr_reg_addrs)/sizeof(struct _reg_addrs)); 
         i++) {
        if (!strcmp (name, fbr_reg_addrs[i].reg_name)) {
            return fbr_reg_addrs[i].reg_addr;
        }
    }

    return -1;
}

char *help_msg[] = {
    "quit - end session\n",
    "open [ \"all\" | 0-4 ]\n",
    "close [ \"all\" | 0-4 ]\n",
    "reset [0,1]\n",
    "debug 0xN\n",
    "Ddebug 0xN\n",
    "rcreg 0-4 function 0xreg width [expected_data]\n",
    "wcreg 0-4 function 0xreg width 0xdata\n",
    "readcis [0,1] function\n",
    "mread [0,1] function reg blk_size blk_count [\"pio\"|\"dma\"] [expected_value]\n",
    "mwrite [0,1] function reg blk_size blk_count data [\"pio\"|\"dma\"]\n",
    "funcon [0,1] [1,2,....]\n",
    "funcoff [0,1] [1,2,....]\n",
    "readcccr [0,1] name\n",
    "writecccr [0,1] name data\n",
    "cccr revision\n",
    "cccr spec_revision\n",
    "cccr enable\n",
    "cccr ready\n",
    "cccr intenable\n",
    "cccr intpending\n",
    "cccr abort\n",
    "cccr intf\n",
    "cccr cap\n",
    "cccr cis0\n",
    "cccr cis1\n",
    "cccr cis2\n",
    "cccr suspend\n",
    "cccr select\n",
    "cccr exec\n",
    "cccr ready\n",
    "cccr block0\n",
    "cccr block1\n",
    "readfbr [0,1] name\n",
    "inst [0,1] [ \"intr\" | \"rem\" | \"err\" ]\n",
    "deinst [0,1] [ \"intr\" | \"rem\" | \"err\" ]\n",
    "status [0,1]\n",
};

/*
 * help
 */
void
help (char *cmd)
{
    int i, len;

    len = strlen (cmd);

    for (i = 0; i < (sizeof(help_msg)/sizeof(char *)); i++) {
        if (!strncmp(help_msg[i], cmd, len)) {
            fprintf (stderr, "%s", help_msg[i]);
            return;
        }
    }

    fprintf (stderr, "No help for %s\n", cmd);

    return;
}

/*
 * usage
 */
void
usage (void)
{
    int i;

    for (i = 0; i < (sizeof(help_msg)/sizeof(char *)); i++) {
        fprintf (stderr, "%s", help_msg[i]);
    }

}


struct _actions {
    char *action_string;
    action_t action;
} actions[] = {
    { "help", ACTION_HELP },
    { "usage", ACTION_USAGE },
    { "quit", ACTION_QUIT },
    { "open", ACTION_OPEN },
    { "close", ACTION_CLOSE },
    { "reset", ACTION_RESET },
    { "debug", ACTION_TEST_DEBUG },
    { "Ddebug", ACTION_DRIVER_DEBUG },
    { "rcreg", ACTION_READCREG },
    { "wcreg", ACTION_WRITECREG },
    { "funcon", ACTION_FUNCON },
    { "funcoff", ACTION_FUNCOFF },
    { "readcis", ACTION_READCIS },
    { "mread", ACTION_MULTREAD },
    { "mwrite", ACTION_MULTWRITE },
    { "readcccr", ACTION_READCCCR },
    { "writecccr", ACTION_WRITECCCR },
    { "readfbr", ACTION_READFBR },
    { "inst", ACTION_INST_CALLBACK },
    { "deinst", ACTION_DEINST_CALLBACK },
    { "status", ACTION_STATUS },
};

/*
 * string_action
 */
action_t
string_action(char *token)
{
    int i;

    for (i = 0; i < (sizeof (actions) / sizeof (struct _actions)); i++) {
        if (!strcmp (token, actions[i].action_string)) {
            return actions[i].action;
        }
    }

    return ACTION_ILLEGAL;
}


#define MAX_BUF 256
/*
 * execute_line
 */
bool
execute_line (char *line)
{
    IOSError status;
    char *token, *keyword = NULL;
    action_t action;
    SDDevConfig devCfg;
    int dev, function, arg, reg, width, data;
    char *buffer;
    unsigned int device_status;
    unsigned int blk_size, blk_cnt, i;
    unsigned int expected_data;
    char *cccr_name, *fbr_name;
    unsigned char cis_buffer[64];

    token = strtok (line, " \n");
    if (!token) {
        fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
        return false;
    }
    keyword = strdup(token);

    switch (action = string_action(token)) {
    /*
     * quit - end session
     */
    case ACTION_QUIT:
        exit (0);
    /*
     * help command_name
     */
    case ACTION_HELP:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        help (token);
        break;
    /*
     * usage
     */
    case ACTION_USAGE:
        usage ();
        break;
    /*
     * open [ \"all\" | 0-4 ]
     */
    case ACTION_OPEN:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        if (debug_level >= DEBUG_CHATTY)
            fprintf (stderr, "%s: token %s\n",
                     __FUNCTION__, token);
        devCfg.SDDevSlot = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        devCfg.SDDevFunc = strtol(token, (char **)NULL, 10);
        status = ISD_AttachDevice (&devCfg, 
                                   &Handles[devCfg.SDDevSlot][devCfg.SDDevFunc]);
        if (status != IOS_ERROR_OK) {
            fprintf (stderr, "%s: bad status %d\n",
                     __FUNCTION__, status);
        }
        break;
    /*
     * close [ \"all\" | 0-4 ]
     */
    case ACTION_CLOSE:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        if (debug_level >= DEBUG_CHATTY)
            fprintf (stderr, "%s: token %s\n",
                     __FUNCTION__, token);
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        status = ISD_DetachDevice (Handles[dev][function]);
        if (status != IOS_ERROR_OK) {
            fprintf (stderr, "%s: bad status %d\n",
                     __FUNCTION__, status);
        }
        break;
    /*
     * funcon [0,1] [1,2,....]
     */
    case ACTION_FUNCON:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        ISD_EnableDevice(Handles[dev][0], function);
        break;
    /*
     * funcoff [0,1] [1,2,....]
     */
    case ACTION_FUNCOFF:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        ISD_DisableDevice(Handles[dev][0], function);
        break;
    /*
     * rcreg 0-4 function 0xreg width
     */
    case ACTION_READCREG:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        reg = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        width = strtol(token, (char **)NULL, 10);
        status = ISD_ReadReg(Handles[dev][function], reg, 1, &data);
        if (status != IOS_ERROR_OK) {
            fprintf (stderr, "%s: bad status %d\n",
                     __FUNCTION__, status);
        }
        /*
         * Read the optional expected value token.  If it is missing,
         * then we are done.  If it is present, compare the first four
         * bytes of the data read with the data expected.
         */
        token = strtok (NULL, " \n");
        if (token) {
            expected_data = strtoul(token, (char **)NULL, 16);
            if (expected_data == data) {
                printf ("Good data: reg 0x%x 0x%x\n", 
                        reg, data);
            } else {
                printf ("Bad data: reg 0x%x 0x%x 0x%x\n", 
                        reg, expected_data, data);
            }
        } else {
            printf ("No data comparison\n");
        }
        printf ("%s: read reg card 0x%x data 0x%x\n",
                 __FUNCTION__, reg, data);
        break;
    /*
     * wcreg 0-4 function 0xreg width 0xdata
     */
    case ACTION_WRITECREG:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        reg = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        width = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        data = strtol(token, (char **)NULL, 16);
        status = ISD_WriteReg(Handles[dev][function], reg, 1, data);
        if (status != IOS_ERROR_OK) {
            fprintf (stderr, "%s: bad status %d\n",
                     __FUNCTION__, status);
        }
        break;
    /*
     * mread [0,1] function reg blk_size blk_count ["pio"|"dma"]
     */
    case ACTION_MULTREAD:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        buffer = malloc (MAX_BUF);
        if (!buffer) {
            fprintf (stderr, "%s: null buffer\n",
                 __FUNCTION__);
            return false;
        }
        if (debug_level >= DEBUG_CHATTY)
            printf ("%s: buffer 0x%x\n",
                    __FUNCTION__, (u32)buffer);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        reg = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        blk_size = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        blk_cnt = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        if (!strcmp(token, "pio")) {
            ISD_ReadMultiReg(Handles[dev][function], reg, 
                             blk_size * blk_cnt, 0, 
                             (unsigned int *)buffer, 0);
        } else {
            if (!strcmp(token, "dma")) {
                ISD_ReadMultiReg(Handles[dev][function], reg, 
                                 blk_size * blk_cnt, 0, 
                                 (unsigned int *)buffer, 1);
            } else {
                help ("mread");
            }
        }
        mem_dump (buffer, blk_size * blk_cnt);
        /*
         * Read the optional expected value token.  If it is missing,
         * then we are done.  If it is present, compare the first four
         * bytes of the data read with the data expected.
         */
        token = strtok (NULL, " \n");
        if (token) {
            expected_data = strtoul(token, (char **)NULL, 16);
            if (expected_data == *(unsigned int *)buffer) {
                printf ("Good data: reg 0x%x 0x%x\n",
                        reg, *(unsigned int *)buffer);
            } else {
                printf ("Bad data: reg 0x%x 0x%x 0x%x\n",
                        reg, expected_data,
                        *(unsigned int *)buffer);
            }
        } else {
            printf ("No data comparison\n");
        }
        break;
    /*
     * mwrite [0,1] function reg blk_size blk_count ["pio"|"dma"]
     */
    case ACTION_MULTWRITE:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        buffer = malloc (MAX_BUF);
        if (!buffer) {
            fprintf (stderr, "%s: null buffer\n",
                 __FUNCTION__);
            return false;
        }
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        reg = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        blk_size = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        blk_cnt = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        *(unsigned int *)&buffer[0] = strtol(token, (char **)NULL, 16);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        if (!strcmp(token, "pio")) {
            ISD_WriteMultiReg(Handles[dev][function], reg, 
                              blk_size * blk_cnt, 0, 
                              (unsigned int *)buffer, 0);
        } else {
            if (!strcmp(token, "dma")) {
                ISD_WriteMultiReg(Handles[dev][function], reg, 
                                  blk_size * blk_cnt, 0, 
                                  (unsigned int *)buffer, 1);
            } else {
                help ("mwrite");
            }
        }
        break;
        /*
         * readcccr [0,1] name
         */
    case ACTION_READCCCR:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        cccr_name = token;
        if (!strcmp(cccr_name, "all")) {
            for (i = 0; i < (sizeof(cccr_reg_addrs)/sizeof(struct _reg_addrs)); 
                 i++) {
                reg = cccr_reg_addrs[i].reg_addr;
                ISD_ReadCCCR(Handles[dev][0], reg, 
                             (unsigned char *)&data);
                printf ("%s: name %s reg addr 0x%x data 0x%x\n", 
                        __FUNCTION__, 
                        cccr_reg_addrs[i].reg_name, reg, data & 0xff);

            }
        } else {
            reg = cccr_register_addr (cccr_name);
            ISD_ReadCCCR(Handles[dev][0], reg, (unsigned char *)&data);
            printf ("%s: %s = 0x%x\n",
                    __FUNCTION__, token, data & 0xff);
        }
        break;
        /*
         * writecccr [0,1] name
         */
    case ACTION_WRITECCCR:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        cccr_name = token;
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        data = strtol(token, (char **)NULL, 16);
        reg = cccr_register_addr (cccr_name);
        ISD_WriteCCCR(Handles[dev][0], reg, data);
        printf ("%s: %s = 0x%x\n",
                __FUNCTION__, token, data);
        break;
        /*
         * readfbr [0,1] name
         */
    case ACTION_READFBR:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        fbr_name = token;
        if (!strcmp (fbr_name, "all")) {
            for (i = 0; i < (sizeof(fbr_reg_addrs)/sizeof(struct _reg_addrs)); 
                 i++) {
                reg = fbr_reg_addrs[i].reg_addr;
                ISD_ReadFBR(Handles[dev][0], 0, reg, 
                            (unsigned char *)&data);
                
                printf ("%s: name %s reg addr 0x%x data 0x%x\n", 
                        __FUNCTION__, 
                        fbr_reg_addrs[i].reg_name, reg, data & 0xff);
            }
        } else {
            reg = fbr_register_addr (fbr_name);
            ISD_ReadFBR(Handles[dev][0], 0, reg, 
                        (unsigned char *)&data);
            printf ("%s: %s = 0x%x\n",
                    __FUNCTION__, token, data & 0xff);
        }
        break;
        /*
         * inst [0,1] [ "intr" | "rem" | "err" ]
         */
    case ACTION_INST_CALLBACK:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        inst_callback (dev, token, 1);
        break;
        /*
         * deinst [0,1] [ "intr" | "rem" | "err" ]
         */
    case ACTION_DEINST_CALLBACK:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        inst_callback (dev, token, 0);
        break;
        /*
         * status [0,1]
         */
    case ACTION_STATUS:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        device_status = 0;
        ISD_GetDeviceStatus(Handles[dev][0], &device_status);
        printf ("%s: device status 0x%x %s\n",
                __FUNCTION__, device_status,
                decode_device_status(device_status));
        break;
    /*
     * reset [0,1]
     */
    case ACTION_RESET:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        status = ISD_ResetDevice(Handles[dev][0]);
        if (status != IOS_ERROR_OK) {
            fprintf (stderr, "%s: bad status %d\n",
                     __FUNCTION__, status);
        }
        break;
    /*
     * readcis [0,1] function
     */
    case ACTION_READCIS:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        dev = strtol(token, (char **)NULL, 10);
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        function = strtol(token, (char **)NULL, 10);
        ISD_ReadCIS(Handles[dev][0], function, &cis_buffer[0], 64);
        slot_crack_cis(&cis_buffer[0]);
        break;
    case ACTION_TEST_DEBUG:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        debug_level = strtol(token, (char **)NULL, 10);
        break;
    case ACTION_DRIVER_DEBUG:
        token = strtok (NULL, " \n");
        if (!token) {
            fprintf (stderr, "%s: null token\n",
                 __FUNCTION__);
            return false;
        }
        arg = strtol(token, (char **)NULL, 10);
        set_driver_debug (Handles[0][0], arg);
        break;
    /*
     * No command recognized.
     */
    default:
        fprintf (stderr, "%s bad keyword %s action %d\n",
                 __FUNCTION__, keyword, action);
        return false;
    }
    if (keyword) {
        free(keyword);
        keyword = NULL;
    }
    
    return true;
}

/*
 * interactive_mode
 */
void
interactive_mode (void)
{
    extern FILE *stdin;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    bool status;

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s:\n", __FUNCTION__);

    fp = stdin;
    if (fp == NULL)
        exit(1);

    printf (">> ");
    while ((read = getline(&line, &len, fp)) != -1) {
        if (debug_level >= DEBUG_CHATTY)
            fprintf (stderr, ">> %s", line);
        status = execute_line (line);
        if (!status) {
            fprintf (stderr, "Bad cmd %s\n", line);
        }
        printf (">> ");
    }
    if (line) {
        free(line);
        line = NULL;
    }
}

int
sdio_test()
{   
    IOSCid devId;
    IOSMessageQueueId qid;
    IOSMessage msgQ[MSGQ_SIZE];
    IOSResourceRequest *req;

    
    printf("*** SDIO API test program ***\n");

    ISDIO_FindDevice(&devId);

    printf("%s: devId %d\n",
           __FUNCTION__, devId);

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
    else
        printf("SDIO registered successfully...\n");

    interactive_mode ();

    /* Sit in a loop processing requests */
    while(1) {
        printf("*** SDIO API test waiting for requests...\n");
        IOS_ReceiveMessage(qid, (IOSMessage *)&req, IOS_MESSAGE_BLOCK);
        switch(req->cmd) {
        default:
            printf("%s: bad request: %d\n",
                   __FUNCTION__, req->cmd);
        }
    }

    return IOS_ThreadExit(0);
}

/* eof */


