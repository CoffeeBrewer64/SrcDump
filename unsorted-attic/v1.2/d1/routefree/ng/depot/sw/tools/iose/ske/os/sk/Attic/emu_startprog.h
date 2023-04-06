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
#ifndef __EMU_STARTPROG_H__
#define __EMU_STARTPROG_H__
#define EMU_DEFAULT_PRIORITY 50
#define EMU_SHELL_PRIORITY 10
#define EMU_STACK_SIZE 32*1024
#define SKSH_PROG_NAME "sksh"
void skEmuStartProg(const char *prog, u32 pri);
#endif /* __EMU_STARTPROG_H__ */
