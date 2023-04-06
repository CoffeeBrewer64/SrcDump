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
#include <iosdebug.h>
#include <iostypes.h>
#include <ioserrno.h>
#include "thread.h"
#include "emu_event.h"

#include <stdio.h>

extern void initc(void);

#ifdef __IOS_EMU_DBG__
FILE *dbg_fp;

void 
init_debug()
{
  if ( NULL == (dbg_fp = fopen("/tmp/iose.log", "a")) ) {
    printf("Opening file failed\n");
    dbg_fp = stderr;
  }
  /* XXXhorti: get rid of this later */  
  dbg_fp = stderr;
  return; 
}
#else 
#define init_debug() /* Debug is not defined */
#endif 

int
main(int argc, char *argv[])
{
  init_debug();
  __iosRegisterHandlers();
  initc();
  return 0;
}
