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
#include "sk.h"
void
print_usage()
{
  printf("Commands: help\n"
      "\t  run<r>{program} [priority] - Run a program from $ROOT/bin\n"
      "\t                   Default location: %s%s\n"
      "\t  ls             - List available programs.\n" 
      "\t  exit<e>        - Exit current shell.\n" 
      "\t  shutdown<s, x> - Shutdown emulator\n",
      DEFAULT_SDK_LOC, DEFAULT_BIN_LOC
      );
  printf("You can use the letters in <> as abbreviations for the commands\n");
  return;
}
