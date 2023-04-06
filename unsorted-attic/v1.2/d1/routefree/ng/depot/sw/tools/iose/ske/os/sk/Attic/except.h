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
#ifndef __EXCEPT_H__ 
#define __EXCEPT_H__
u32 __skDisableInt(void);
void __skRestoreInt(u32 mask);
void __skEnqueueAndYield(SKThread **queue);
void __skDispatchThread();
#endif /*__EXCEPT_H__*/
