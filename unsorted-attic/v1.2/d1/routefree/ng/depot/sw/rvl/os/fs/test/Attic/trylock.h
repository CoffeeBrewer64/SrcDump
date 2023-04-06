/*
 *              Copyright (C) 2005, BroadOn Communications Corp.
 *
 * These coded instructions, statements, and computer programs contain
 * unpublished  proprietary information of BroadOn Communications Corp.,
 * and  are protected by Federal copyright law. They may not be disclosed
 * to  third  parties or copied or duplicated in any form, in whole or in
 * part, without the prior written consent of BroadOn Communications Corp.
 *
 */

#ifndef __TRYLOCK_H__
#define __TRYLOCK_H__

#if !defined(ASSEMBLER)

/*
 * Spinlock routines
 */
typedef u32 *lock_t;
extern void __skInitlock(lock_t lck);
extern u32 __skTrylock(lock_t lck);
extern void __skUnlock(lock_t lck);

#endif /* ASSEMBLER */
#endif /* __TRYLOCK_H__ */
