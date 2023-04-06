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
#include <ios.h>
#include <ioslibc.h>
void
exit(int status)
{
    /* XXX horti: status is returned in the void * slot, used by
     *            join.
     */
    /* IOS_DestroyThread(0, (void *)status); */
    printf("exit(%d) called\n", status);
    while(1);
}
