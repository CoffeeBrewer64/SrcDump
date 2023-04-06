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
 *      This file defines internal utility functions used by the SCFS
 *
 */


#ifndef __FS_UTILS_H__
#define __FS_UTILS_H__


/*
 *  Description:
 *      Error logging primitives
 *
 */
#define ISFS_DEBUG_CRIT             1
#define ISFS_DEBUG_ERROR            2
#define ISFS_DEBUG_WARN             4
#define ISFS_DEBUG_INFO             8
#define ISFS_DEBUG_NOTIFY           16
#define ISFS_DEBUG_DEBUG            32
#define ISFS_DEBUG_TRACE            64

#define ISFS_DEBUG_LEVEL            0x1f


#ifdef ISFS_DEBUG_LOG
#ifdef NET_CARD
#include <sc/libc.h>
#else
#include <ioslibc.h>
#endif

#define isfsPrint(l, s, args...)                                \
    do {                                                        \
        if (l & ISFS_DEBUG_LEVEL) {                             \
            /* The ## remove the ',' when there's no args */    \
            printf(s, ## args);                                 \
        }                                                       \
    } while (0)
#define ISFS_ENTRY()                                            \
    do {                                                        \
        if (ISFS_DEBUG_LEVEL & ISFS_DEBUG_TRACE) {              \
            printf("%s: Entering function %s(), line %d\n",     \
                    __FILE__, __FUNCTION__, __LINE__);          \
        }                                                       \
    } while (0)
#define ISFS_EXIT()                                             \
    do {                                                        \
        if (ISFS_DEBUG_LEVEL & ISFS_DEBUG_TRACE) {              \
            printf("%s: Exiting function %s(), line %d\n",      \
                    __FILE__, __FUNCTION__, __LINE__);          \
        }                                                       \
    } while (0)

#else

#define isfsPrint(l, s, ...)        (void)(0)
#define ISFS_ENTRY()                (void)(0)
#define ISFS_EXIT()                 (void)(0)

#endif                  /*  Enable file system logging */


#endif /* __FS_UTILS_H__ */
