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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdlib.h>

#include <ios.h>
#include <iostypes.h>
#include "iossh.h"
#define SDIR_MAX 256
void 
list_progs(void)
{
  char buf[SDIR_MAX + 3];
  char *sdkroot = getenv("ROOT");
  if ( NULL == sdkroot ) sdkroot = DEFAULT_SDK_LOC; 
  sprintf(buf,"ls %s%s", sdkroot, DEFAULT_BIN_LOC);
  system(buf);
  return;
}

void 
start_prog(const char *prog, u32 pri)
{
  IOS_EmuStartProg(prog, pri);
}
