/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *      This file defines internal utility functions used by the flash
 *      device driver
 *
 */


#ifndef __FL_UTILS_H__
#define __FL_UTILS_H__


/*
 *  Description:
 *      Error logging primitives
 *
 */
#define FL_DEBUG_CRIT           1
#define FL_DEBUG_ERROR          2
#define FL_DEBUG_WARN           4
#define FL_DEBUG_INFO           8
#define FL_DEBUG_NOTIFY         16
#define FL_DEBUG_DEBUG          32
#define FL_DEBUG_TRACE          64

#define FL_DEBUG_LEVEL          0x1f


#ifdef FL_DEBUG_LOG
#ifdef NET_CARD
#include <sc/libc.h>
#else
#include <ioslibc.h>
#endif

#define flPrint(l, s, args...)                                  \
    do {                                                        \
        if (l & FL_DEBUG_LEVEL) {                               \
            /* The ## remove the ',' when there's no args */    \
            printf(s, ## args);                                 \
        }                                                       \
    } while (0)
#define FL_ENTRY()                                              \
    do {                                                        \
        if (FL_DEBUG_LEVEL & FL_DEBUG_TRACE) {                  \
            printf("%s: Entering function %s(), line %d\n",     \
                    __FILE__, __FUNCTION__, __LINE__);          \
        }                                                       \
    } while (0)
#define FL_EXIT()                                               \
    do {                                                        \
        if (FL_DEBUG_LEVEL & FL_DEBUG_TRACE) {                  \
            printf("%s: Exiting function %s(), line %d\n",      \
                    __FILE__, __FUNCTION__, __LINE__);          \
        }                                                       \
    } while (0)

#else

#define flPrint(l, s, ...)      (void)(0)
#define FL_ENTRY()              (void)(0)
#define FL_EXIT()               (void)(0)

#endif                  /*  Enable flash device driver logging */


#endif /* __FL_UTILS_H__ */
