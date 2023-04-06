#ident "$Id: key.c,v 1.1 2005/12/23 21:52:52 craig Exp $"
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

#include <stdint.h>

uint32_t          TitleKey[] = {0xdeadbeef, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef};
uint32_t          TitleIv[]  = {0xcafebabe, 0xcafebabe, 0xcafebabe, 0xcafebabe};
