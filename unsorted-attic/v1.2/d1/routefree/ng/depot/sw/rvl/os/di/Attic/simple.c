#ident "$Id: simple.c,v 1.1 2006/02/24 00:59:48 craig Exp $"
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

/*
 * Program comments here
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stdint.h"
#include "dvd_hw_reg.i"

#define STACK_SIZE 1024
const uint8_t  _initStack[STACK_SIZE];
const uint32_t _initStackSize = sizeof(_initStack);



int
main(int argc, char *argv[])
{
    printf ("DI status reg is: 0x%x\n", readDIStatus());
    printf ("DI cover reg is: 0x%x\n",  readDICoverReg());
    exit(0);
}
