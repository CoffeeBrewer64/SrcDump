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
#ifndef __IOS_H__
#define __IOS_H__

#include <iostypes.h>

#if defined(_LANGUAGE_C)
#include <iosiobuf.h>
IOSThreadId IOS_CreateThread(IOSEntryProc entry, void *arg, void *stack, u32 stackSize, u32 priority, u32 attributes);
IOSError IOS_JoinThread(IOSThreadId id, void **val);
IOSError IOS_DestroyThread(IOSThreadId id, void *val);
IOSThreadId IOS_GetThreadId(void);
IOSProcessId IOS_GetProcessId(void);
IOSError IOS_StartThread(IOSThreadId id);
IOSError IOS_StopThread(IOSThreadId id);
void IOS_YieldThread(void);
u32 IOS_GetThreadPriority(IOSThreadId id);
IOSError IOS_SetThreadPriority(IOSThreadId id, u32 priority);
IOSMessageQueueId IOS_CreateMessageQueue(IOSMessage *msgarray, u32 count, u32 pIdMask);
IOSError IOS_DestroyMessageQueue(IOSMessageQueueId id);
IOSError IOS_SendMessage(IOSMessageQueueId mq, IOSMessage msg, u32 flag);
IOSError IOS_JamMessage(IOSMessageQueueId mq, IOSMessage msg, u32 flag);
IOSError IOS_ReceiveMessage(IOSMessageQueueId mq, IOSMessage *msg, u32 flag);
IOSError IOS_HandleEvent(IOSEvent event, IOSMessageQueueId mq, IOSMessage mesg);
IOSError IOS_UnhandleEvent(IOSEvent event);
IOSTimerId IOS_CreateTimer(IOSTime value, IOSTime interval, IOSMessageQueueId mq, IOSMessage mesg);
IOSError IOS_DestroyTimer(IOSTimerId id);
IOSTime IOS_GetTimer(void);
IOSHeapId IOS_CreateHeap(void *ptr, u32 size);
IOSError IOS_DestroyHeap(IOSHeapId id);
void *IOS_Alloc(IOSHeapId id, u32 size);
IOSError IOS_Free(IOSHeapId id, void *ptr);
IOSError IOS_RegisterResourceManager(char *path, IOSMessageQueueId mq);
IOSFd IOS_Open(const char *pathname, u32 flags);
IOSError IOS_Close(IOSFd fd);
s32 IOS_Read(IOSFd fd, void *buf, u32 count);
s32 IOS_Write(IOSFd fd, void *buf, u32 count);
s32 IOS_Seek(IOSFd fd, s32 offset, u32 whence);
IOSError IOS_Ioctl(IOSFd fd, s32 cmd, void *input, u32 input_bytes, void *output, u32 output_bytes);
IOSError IOS_ResourceReply(IOSResourceRequest *response, IOSError status);
IOSError IOS_SetUid(IOSProcessId id, IOSUid uid);
IOSUid IOS_GetUid(void);
IOSError IOS_SetGid(IOSProcessId id, IOSGid gid);
IOSGid IOS_GetGid(void);

#endif /* _LANGUAGE_C */

#endif /*__IOS_H__*/
