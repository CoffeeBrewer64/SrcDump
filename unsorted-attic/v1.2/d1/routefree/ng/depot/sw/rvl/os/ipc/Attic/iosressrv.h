#ident "$Id: iosressrv.h,v 1.1 2006/03/02 07:10:22 orest Exp $"
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
#ifndef __IOS_RESSRV_H__
#define __IOS_RESSRV_H__


/* Non-blocking API 
 * XXX - There will be minor naming and other changes to the following.
 *       No real change in functionality.
 */

IOSFd IOS_OpenAsync(
        const char         *path, 
        u32                 flags, 
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

IOSError IOS_CloseAsync(
        IOSFd               fd, 
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

IOSError IOS_ReadAsync(
        IOSFd               fd, 
        void               *buf, 
        u32                 count,
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

IOSError IOS_WriteAsync(
        IOSFd               fd, 
        void               *buf, 
        u32                 count,
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

IOSError IOS_SeekAsync(
        IOSFd               fd, 
        s32                 offset, 
        u32                 whence,
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

IOSError IOS_IoctlAsync(
        IOSFd               fd, 
        s32                 cmd,
        void               *input, 
        u32                 inputLen,
        void               *output, 
        u32                 outputLen,
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

IOSError IOS_IoctlvAsync(
        IOSFd               fd,
        s32                 cmd,
        u32                 readCount,
        u32                 writeCount,
        IOSIoVector        *vect,
        IOSMessageQueueId   replyQId, 
        IOSResourceRequest *reply);

#endif /* __IOS_RESSRV_H__ */
