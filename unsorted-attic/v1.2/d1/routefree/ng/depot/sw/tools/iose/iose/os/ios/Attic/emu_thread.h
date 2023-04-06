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
#ifndef __EMU_THREAD__
#define __EMU_THREAD__
int emuInitContext( IOSContext *ctx, IOSEntryProc entry, void *arg, void *stack,
    u32 stackSize);
#endif /* _EMU_THREAD__ */
