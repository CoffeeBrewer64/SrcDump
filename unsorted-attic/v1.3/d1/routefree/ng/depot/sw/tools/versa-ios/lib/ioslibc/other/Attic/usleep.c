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
IOSError
usleep(u32 usec )
{
    IOSError rv = IOS_ERROR_OK;
    IOSMessageQueueId mq;
    IOSMessage array;
    IOSMessage m;
    
    if ((mq = IOS_CreateMessageQueue(&array, 1)) < 0) {
        rv = IOS_ERROR_MAX;
        goto done;
    }
    if ((rv = IOS_CreateTimer(usec, 0, mq, 0xbabecafe)) < 0)
            goto done;
    IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
    IOS_DestroyMessageQueue(mq);
done:
    return rv;
}
