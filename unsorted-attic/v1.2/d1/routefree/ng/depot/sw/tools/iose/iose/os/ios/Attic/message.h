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
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#define IOS_MESSAGE_QUEUE_MAX   32

#define IOS_MESSAGE_QUEUE_EMPTYQ 0
#define IOS_MESSAGE_QUEUE_FULLQ  4
#define IOS_MESSAGE_QUEUE_OWNER  8
#define IOS_MESSAGE_QUEUE_MASK   12
#define IOS_MESSAGE_QUEUE_COUNT  16
#define IOS_MESSAGE_QUEUE_RPTR   20
#define IOS_MESSAGE_QUEUE_SIZE   24
#define IOS_MESSAGE_QUEUE_BUFFER 28

#define IOS_EVENT_STATE_MQ       0
#define IOS_EVENT_STATE_MSG      4
#define IOS_EVENT_STATE_OWNER    8
#define IOS_EVENT_STATE_SIZE     16

#if defined(_LANGUAGE_C)
typedef struct {
    IOSThread *emptyQ;
    IOSThread *fullQ;
    u32 owner;
    u32 maios;
    s32 count;
    s32 rptr;
    s32 size;
    IOSMessage *buffer;
} IOSMessageQueue;

typedef struct {
    IOSMessageQueue *messageQueue;
    IOSMessage message;
    u32 owner;
    u32 pad;
} IOSEventState;

#define CHECK_EVENT(event) \
    if ((event) < IOS_EVENT_MIN || (event) > IOS_EVENT_MAX) { \
        rv = IOS_ERROR_INVALID; \
        goto end; \
    } 

extern void iosSendEvent(IOSEventState es);
extern IOSMessageQueue __queues[];
#endif /* _LANGUAGE_C */

#endif /*__MESSAGE_H__*/
