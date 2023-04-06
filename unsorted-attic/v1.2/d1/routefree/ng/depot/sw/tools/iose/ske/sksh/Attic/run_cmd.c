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
/* Parse and run commands */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sk.h>
#include <sktypes.h>
#include "cmd.h"
#include "sksh.h"

void
run_cmd(int ac, const char **av)
{
  /* exit */
  if ( 0 == strncmp(av[0], "exit", 1) || 0 == strncmp(av[0],"quit", 1)) {
      printf("%s version: %s exiting ...\n", SKSH_PROG_NAME, SKSH_VER_STR);
      SK_ThreadExit(0);
  }
  /* shutdown */
  if ( 0 == strncmp(av[0], "shutdown", 1) || 0 == strcmp(av[0],"reboot")
       || 0 == strncmp(av[0],"x", 1) 
      )
    _exit(0);
  /* run */
  if ( 0 == strncmp(av[0],"run", 1)) {
    u32 pri = 0;
    if ( ac < 2 ) goto usg;
    if ( ac > 2 )
      pri = (u32) atoi(av[2]);
    if ( pri <= 0 || pri > 127 ) {
      pri = DEFAULT_PRIORITY;
      fprintf(stderr, "sksh: will run with default priority: %u\n",pri);
    }
    start_prog(av[1], pri);
    goto out;
  }
  /* ls */
  if ( 0 == strncmp(av[0],"ls", 1)) {
      list_progs(); 
      goto out;
  }
  /* default: fall thru to usage */
usg:
  print_usage();
out:
  return;
}
