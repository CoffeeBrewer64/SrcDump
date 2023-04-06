#ident "$Id: key.c,v 1.3 2006/03/31 20:00:04 craig Exp $"
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

#if defined(RVL)
#include "arm_stdint.h"
#else
#include <stdint.h>
#endif

uint8_t          TitleKey[] = {0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef,
                               0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef};
uint8_t          TitleIv[]  = {0xca, 0xfe, 0xba, 0xbe, 0xca, 0xfe, 0xba, 0xbe,
                               0xca, 0xfe, 0xba, 0xbe, 0xca, 0xfe, 0xba, 0xbe};
