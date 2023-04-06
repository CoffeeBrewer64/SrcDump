#ident "$Id: assert.h,v 1.2 2006/06/12 23:34:54 craig Exp $"
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

/* Cheesy implementation of real assert.h */

#ifndef ASSERT_H
#define ASSERT_H


#if !defined(assert)
#if defined(_NDEBUG)
#define assert(x)       (0)
#else

#include <stdio.h>
#include <stdlib.h>

static inline void
assert_failed(const char *expression)
{
    printf ("Assert failed: Expression is '%s'", expression);
    exit(1);
}

#define assert(x)       ( (x) ? 0 : assert_failed(("x")), 0)
#endif


#endif // if !defined(assert)
#endif // ifndef ASSERT_H
