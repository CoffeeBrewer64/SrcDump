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
#include <ngtypes.h>
#include <sktypes.h>
#include <sk.h>
#include "alloc.h"
#include "thread.h"

#include <stdio.h>
#include <stdlib.h>

static void *__base = NULL;
static pg_t __pages[SK_DDR_PAGES_MAX];
static int initialized = 0;

void 
__skDumpPg(int i)
{
  fprintf(stderr, "------------------------------------ \n");
  fprintf(stderr, "page[%d].page = %p\n", i, __pages[i].page);
  if ( 1 == __pages[i].start_pg ) {
    fprintf(stderr, "page[%d].owner = %u\n", i, __pages[i].owner);
    fprintf(stderr, "page[%d].mask = %u\n", i, __pages[i].mask);
    fprintf(stderr, "page[%d].size = %u __pages\n", i, __pages[i].size);
    fprintf(stderr, "page[%d].start_pg= %u\n", i, __pages[i].start_pg);
  }
  fprintf(stderr, "page[%d].used = %u\n", i, __pages[i].used);
  fprintf(stderr, "page[%d].size = %p\n", i, (void *)__pages[i].size);
}

void 
__skDumpPgs(int start, int num)
{ 
  int i;
  for ( i = 0; i < num; ++i)
    __skDumpPg(start + i);
}

static int
__skMallocInit()
{
  int i;
  __base = malloc(SK_DDR_PAGES_MAX *SK_DDR_PAGE_SIZE);
  if ( NULL == __base ) {
    fprintf(stderr,"malloc_init failed\n");
    return -1;
  }
  for ( i = 0; i < SK_DDR_PAGES_MAX; ++i ) {
    __pages[i].page = __base + i*SK_DDR_PAGE_SIZE;
    __pages[i].used = 0;
  }
  return 0;
}

static void *
__skMarkInuse(int start_page, u32 siz)
{
  int i;
  __pages[start_page].used = 1;
  __pages[start_page].start_pg = 1;
  __pages[start_page].size = siz;
  __pages[start_page].owner = skGetProcessId();
  __pages[start_page].mask = skGetProcessId();

  for ( i = start_page + 1; i < start_page + siz; ++i ) {
   __pages[i].size = (u32)__pages[start_page].page; /* if start_pg == 0, size == start of block */
   __pages[i].used = 1;
   __pages[i].start_pg = 0;
  }
  return (void *) __pages[start_page].page;
}

/* size is # of __pages */
void *
skAlloc(u32 size)
{
  int sp = 0;
  int ep = 0;
  int i;
  if ( 0 == initialized ) {
    if ( -1 ==  __skMallocInit())
      return NULL;
    initialized = 1;
  }

  i = 0;
  while ( i < SK_DDR_PAGES_MAX) {
    if ( 1 == __pages[i].used && 1 == __pages[i].start_pg ) { 
      i += __pages[i].size; /* skip allocated __pages */
      sp = ep = i;
      continue;
    }
    if ( size == (ep - sp + 1) ) { /* done */ 
      __skMarkInuse(sp, size);
      return (void *) __pages[sp].page;
    }
    ++ep; ++i; /* continue */
  }
  return NULL;
}

static SKError 
__skFree(u32 offst)
{
  unsigned idx = offst;
  unsigned end = offst + __pages[offst].size;
  for ( idx = offst; idx < end; ++idx ) {
    __pages[idx].used = 0;
    __pages[idx].start_pg = 0;
    __pages[idx].size = 0;
  }
  return SK_ERROR_OK;
}

SKError
skFree(void *ptr)
{
  u32 offst;
  offst = (u32)  (ptr - __base)/SK_DDR_PAGE_SIZE;
  
//  DBG_PRINTF((dbg_fp,"skFreeMem: freeing ptr=%p __base= %p: ptr - __base = 0x%x page = %d page_size = 0x%x \n", ptr, __base, ptr - __base, offst, SK_DDR_PAGE_SIZE));
  
  if (   0 != ( (ptr - __base) & 0x1FF)
      || offst >= SK_DDR_PAGES_MAX 
      || 0 == __pages[offst].used 
     )
     goto err;

  if( 0 == __pages[offst].start_pg ) {
   u32 old_offst = offst;
   fprintf(stderr,"Given pointer %p [page %u] in the middle of an allocated chunk\n", ptr, offst);
   offst = ((void *)(__pages[offst].size) - __base ) / SK_DDR_PAGE_SIZE;
   fprintf(stderr,"Will free chunk: %p [page %u]\n", (void *)__pages[old_offst].size, offst);
  }
  return __skFree(offst);

err:
   fprintf(stderr,"Freeing invalid location\n");
    return SK_ERROR_INVALID;
}

void
__skFreeMem(u32 pid) 
{
  int idx;
//  DBG_PRINTF((dbg_fp,"__skFreeMem: freeing memory used by pid %u\n", pid));
  for ( idx = 0; idx < SK_DDR_PAGES_MAX; ++idx ) 
    if ( 1 == __pages[idx].start_pg && pid == __pages[idx].owner ) 
      __skFree(idx);
}

void
skDebugMemDump(void)
{
  int idx;
  int num_free = 0;
  int num_used = 0;
  fprintf(stderr,"*** Summary of memory usage: \n");
  for ( idx = 0; idx < SK_DDR_PAGES_MAX; ++idx )  {
    if ( 1 == __pages[idx].start_pg ) {
      num_used += __pages[idx].size;
      fprintf(stderr,"Pages [%d-%d]: in use by pid = %u\n", idx, idx + __pages[idx].size - 1, __pages[idx].owner);
    }
    else if ( 0 == __pages[idx].used ) num_free++;
  }
  fprintf(stderr,"Used __pages = %d; Free __pages = %d\n", num_used, num_free);
  fprintf(stderr,"****************************\n");
}
