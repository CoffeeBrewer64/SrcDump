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
#include <ng.h>
#include <sk.h>
#include <sktypes.h>
#include "thread.h"
#include "emu_startprog.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdlib.h>
#define SDIR_MAX 256

static void 
run_prog(SKEntryProc prog_sym, u32 pri)
{
    u32 *progStack = (void *) malloc(EMU_STACK_SIZE);
    u32 id = skCreateThread(prog_sym, 0, progStack, EMU_STACK_SIZE, pri);
    skStartThread(id);
    return;
}

void 
skEmuStartProg(const char *prog, u32 pri)
{
  char slib[SDIR_MAX];
  char *sdkroot = NULL;
  SKEntryProc prog_sym;
  void *handle = NULL;
  char *error;
  int shell = -1;

  if ( 0 != (shell = strcmp(prog, SKSH_PROG_NAME) ))
      sdkroot = getenv("ROOT");
  if ( NULL == sdkroot ) sdkroot = DEFAULT_SDK_LOC; 
  sprintf(slib,"%s%s%s.so", sdkroot, DEFAULT_BIN_LOC, prog);
 
  handle = dlopen(slib, RTLD_NOW|RTLD_GLOBAL);
  error = dlerror();
  if ( NULL == handle ) {
    fprintf(stderr, "%s\n", error);
    goto err;
  }
  prog_sym = dlsym(handle, prog);
  if ((error = dlerror()) != NULL)  {
    fprintf (stderr, "%s\n", error);
    goto err;
  }
  run_prog(prog_sym, pri);
  goto out;

err:
  printf("Starting program: %s failed\n", prog);
  if ( 0 == shell ) 
      exit(1);
out:
  return;
}
