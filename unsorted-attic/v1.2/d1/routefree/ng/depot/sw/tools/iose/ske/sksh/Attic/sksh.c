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

#include <sk.h>
#include <sktypes.h>
#include "sksh.h"
#include "edit_line.h"
#include "cmd.h"
#define DEFAULT_PRIORITY 50


void
sksh(u32 id)
{
  SK_SetThreadPriority(0, DEFAULT_PRIORITY);
  printf("sksh version: %s starting...\n", SKSH_VER_STR);
  print_usage();
  setup_editline("sksh");
  while( NULL != (editline_inl = el_gets(el, &editline_count))) {
    int ac; const char **av; const LineInfo *li;
    li = el_line(el);
    tok_line(tok, li, &ac, &av, NULL, NULL); 
    history(hs, &ev, H_ENTER, editline_inl);
    if ( ac > 0) run_cmd(ac, av);
    tok_reset(tok);
    SK_YieldThread();
  }
  delete_editline();
  skDestroyThread(0);
}
