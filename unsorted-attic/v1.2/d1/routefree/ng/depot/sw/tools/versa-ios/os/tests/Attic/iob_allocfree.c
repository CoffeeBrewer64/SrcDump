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
#include <ios.h>
#include <versaios.h>
#include <iostypes.h>
#include <iosiobuf.h>
#include <ioslibc.h>
#include <arm.h>

IOSIobDebugInfo d;

void
iob_allocfree(void)
{
  IOSIobuf *p, *q;
  if (IOS_ERROR_OK != IOS_AccessIobPool(POOL_DEFAULT)) {
      printf("getting access to iobuf pool failed\n");
      goto done;
  }

  p = IOS_AllocIob(POOL_DEFAULT, 24, d);
  if ( NULL == p) {
      printf("allocating iobuf of size 24: FAILED\n");
  }
  else
      printf("allocating iobuf of size 24: PASSED\n");
  
  q = IOS_AllocIob(POOL_DEFAULT, 128, d);
  if ( NULL == q ) {
      printf("allocating iobuf of size 128: FAILED\n");
  }
  else
      printf("allocating iobuf of size 128: PASSED\n");
  
  
  IOS_FreeIob(p);
  IOS_FreeIob(q);
  printf("freed iobuf: %p, %p\n", p, q);

  IOS_DebugDumpIobFreeBufsList(0,0);
done:
  exit(0);
}

/* Thread created by idle process */
u8 testthrStack[1024]; /* 1024 is hardwired as stack size for this thread
                        * when the idle thread starts it. Please change
                        * it if you change this.
                        */
void
testthr(u32 arg)
{
  iob_allocfree();
}
