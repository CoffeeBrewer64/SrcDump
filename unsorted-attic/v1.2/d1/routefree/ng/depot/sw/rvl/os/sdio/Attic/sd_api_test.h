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

/*
 * $Id: sd_api_test.h,v 1.1 2006/03/02 19:02:05 gbarnard Exp $
 */
#ifndef _SD_API_TEST_H_
#define _SD_API_TEST_H_

/*
typedef enum {
    SDIO_READ,
    SDIO_WRITE
} wr_t;

typedef enum {
    SDIO_PIO,
    SDIO_DMA
} trans_t;


typedef struct _tasks {
    wr_t         t_rw;
    sdio_cmd_t   t_cmd;
    unsigned int t_slot;
    unsigned int t_func;
    unsigned int t_reg;
    unsigned int t_width;
    unsigned int t_data;
    unsigned int t_exp;
    unsigned int t_incr;
    trans_t      t_dma;
} tasks_t;
*/

/*
 * Prototypes.
 */
 
extern bool interact (char *question, char *resp);

extern void sd_test (void);

#endif /* _SD_API_TEST_H_ */

/* eof */
