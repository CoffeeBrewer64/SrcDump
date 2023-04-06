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
#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include <ng.h>

#include <ucontext.h>

typedef struct emu_ctx {
  ucontext_t uctx;
  sigset_t sigs;
  int sk_errno; 
} SKContext;
#endif /*__CONTEXT_H__*/
