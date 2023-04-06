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
#include <nglibc.h>
#ifndef __SK_EMULATOR__
extern void _exit (int __status) __attribute__ ((__noreturn__));
void
exit(int status)
{
  _exit(status);
}
#endif /* ! __SK_EMULATOR__ */
