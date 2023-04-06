a0 52
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

#include "hw.h"
#include "ios.h"
#include "ioslibc.h"

#define STACK_SIZE 1024
const u8 _initStack[STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

extern u32 timerIntrCnt;

void
main(u32 arg)
{
    IOSError rv;
    u32 count = 0;
    IOSMessageQueueId mq;
    IOSMessage array[4];

    mq = IOS_CreateMessageQueue(array, sizeof(array)/sizeof(IOSMessage));
    if ((rv = IOS_HandleEvent(IOS_EVENT_VIPIWR, mq, 0)) != IOS_ERROR_OK) {
        printf("Unable to register VIPIWR event handler: %d\n", rv);
        goto done;
    }
    printf("Event handler registered for VIPIWR event\n");

    rv = IOS_ClearAndEnableEvent(IOS_EVENT_VIPIWR);
    printf("Initial clearAndEnable returned: %d\n", rv);
    while (1) {
        printf("Waiting for VIPIWR event ...\n");
        if (IOS_ReceiveMessage(mq, NULL, IOS_MESSAGE_BLOCK) == IOS_ERROR_OK) {            
            printf("Received VIPIWR event %d\n", ++count);
            rv = IOS_ClearAndEnableEvent(IOS_EVENT_VIPIWR);
            printf("clearAndEnable returned: %d\n", rv);
        }
    }
done:
    IOS_DestroyThread(0, NULL);
    return;

}
