/*
 *               Copyright (C) 2006, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */
#ifndef __IOS_RESOURCE_H__
#define __IOS_RESOURCE_H__

/* Non-blocking internal API 
 */
IOSError iosOpenAsync(
        const char         *path,
        u32                 flags,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);
IOSError iosCloseAsync(
        IOSFd               fd,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);
IOSError iosReadAsync(
        IOSFd               fd,
        void               *buf,
        u32                 count,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);
IOSError iosWriteAsync(
        IOSFd               fd,
        void               *buf,
        u32                 count,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);
IOSError iosSeekAsync(
        IOSFd               fd,
        s32                 offset,
        u32                 whence,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);
IOSError iosIoctlAsync(
        IOSFd               fd,
        s32                 cmd,
        void               *input,
        u32                 inputLen,
        void               *output,
        u32                 outputLen,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);
IOSError iosIoctlvAsync(
        IOSFd               fd,
        s32                 cmd,
        u32                 readCount,
        u32                 writeCount,
        IOSIoVector        *vect,
        IOSMessageQueueId   replyQId,
        IOSResourceRequest *reply);


#endif /* __IOS_RESOURCE_H__ */
