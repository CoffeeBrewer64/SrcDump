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
 * $Id: sdio_api_test.h,v 1.1 2006/03/30 16:50:23 gbarnard Exp $
 */
#ifndef _SDIO_API_TEST_H_
#define _SDIO_API_TEST_H_

typedef enum {
    SDIO_RD,
    SDIO_WR
} wr_t;

typedef enum {
    SDIO_CMD52,
    SDIO_CMD53
} sdio_cmd_t;

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
    /*
     * These two fields are for cmd53 only
     */
    unsigned int t_incr;
    trans_t      t_dma;
} tasks_t;

/*
 * Prototypes.
 */
extern bool interact (char *question, char *resp);
extern void sdio_test1 (void);

#endif /* _SDIO_API_TEST_H_ */

/* eof */
