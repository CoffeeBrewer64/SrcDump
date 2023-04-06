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
#ifndef __NG_MALLOC_H__
#define __NG_MALLOC_H__
#include <ngtypes.h>
#define SK_DDR_PAGES_MAX 64
#define SK_DDR_PAGE_SIZE 4096 /* 1k words */

struct pg{
  void *page;  /* address of page controlled by this page struct */
  SKProcessId owner; /* pid of owner */
  u32 mask;  /* access control */
  u32 size;  /* chunk size in pages */
  unsigned used;   /* 0 - free 1 - used */
  unsigned start_pg; /* 0 - no 1 - yes */
};
typedef struct pg pg_t;

void __skFreeMem(u32 pid);
#endif /* __NG_MALLOC_H__ */
