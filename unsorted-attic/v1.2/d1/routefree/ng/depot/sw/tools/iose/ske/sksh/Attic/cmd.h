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
#ifndef __CMD_H__
#define  __CMD_H__

#define DEFAULT_PRIORITY 50
void print_usage(void);
void list_progs(void);
void start_prog(const char *prog, u32 pri);
void run_cmd(int ac, const char **av);
#endif /*__CMD_H__ */
