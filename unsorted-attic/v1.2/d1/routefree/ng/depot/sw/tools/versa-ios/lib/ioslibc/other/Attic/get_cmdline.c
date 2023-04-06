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

#include "../vio.h"

void
get_cmdline(char *buf, unsigned long bufLen)
{
    unsigned long args[] = {(unsigned long)buf, bufLen};
    __sys_get_cmdline(args);
}
