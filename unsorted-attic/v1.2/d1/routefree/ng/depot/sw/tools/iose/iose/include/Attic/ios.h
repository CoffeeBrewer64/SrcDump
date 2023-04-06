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

#define DEFAULT_SDK_LOC  "/opt/iop-sdk/"
#define DEFAULT_BIN_LOC  "/usr/bin/iose/"

#if defined(_LANGUAGE_C)
#define IOS_ThreadExit(X)  iosDestroyThread(0)
#define IOS_SetTimer(duration, mq, mesg) \
    iosSetTimer((duration), (mq), (mesg), 0)
#define IOS_SetPeriodicTimer(period, mq, mesg) \
    iosSetTimer((period), (mq), (mesg), 1)
IOSError iosDestroyThread(IOSThreadId id);
IOSThreadId IOS_Fork(IOSEntryProc entry, void *arg, void *stack,
			   u32 stackSize, u32 priority);
IOSThreadId IOS_CreateThread(IOSEntryProc entry, void *arg, void *stack,
			   u32 stackSize, u32 priority);
IOSError IOS_DestroyThread(IOSThreadId id);
IOSThreadId IOS_GetThreadId(void);
IOSProcessId IOS_GetProcessId(void);
IOSError IOS_StartThread(IOSThreadId id);
IOSError IOS_StopThread(IOSThreadId id);
void IOS_YieldThread(void);
u32 IOS_GetThreadPriority(IOSThreadId id);
IOSError IOS_SetThreadPriority(IOSThreadId id, u32 priority);
IOSMessageQueueId IOS_CreateMessageQueue(IOSMessage * msgarray, u32 count,
				       u32 pIdMask);
IOSError IOS_DestroyMessageQueue(IOSMessageQueueId id);
IOSError IOS_SendMessage(IOSMessageQueueId mq, IOSMessage msg, u32 flag);
IOSError IOS_JamMessage(IOSMessageQueueId mq, IOSMessage msg, u32 flag);
IOSError IOS_ReceiveMessage(IOSMessageQueueId mq, IOSMessage * msg, u32 flag);
IOSError IOS_HandleEvent(IOSEvent event, IOSMessageQueueId mq, IOSMessage mesg);
IOSError IOS_UnhandleEvent(IOSEvent event);

IOSTimerId iosSetTimer(IOSTime, IOSMessageQueueId, IOSMessage, u8);
IOSError IOS_StopTimer(IOSTimerId id);
IOSError IOS_ShareRegion(void *ptr, u32 size, u32 pIdMask);
IOSError IOS_UnshareRegion(void *ptr, u32 size, u32 pIdMask);
void *IOS_Alloc(u32 size);
IOSError IOS_Free(void *ptr);
u32 IOS_GetSdramPageSize(void);
IOSError IOS_RegisterRpc(IOSInterfaceId id, IOSMessageQueueId mq);
IOSError IOS_RegisterResourceManager(char *path, IOSMessageQueueId mq);
IOSCid IOS_Open(const char *pathname, u32 flags);
IOSError IOS_Close(IOSCid fd);
s32 IOS_Read(IOSCid fd, void *buf, u32 count);
s32 IOS_Write(IOSCid fd, void *buf, u32 count);
s32 IOS_Seek(IOSCid fd, s32 offset, u32 whence);
IOSError IOS_Ioctl(IOSCid fd, s32 cmd, void *input, u32 input_bytes,
		 void *output, u32 output_bytes);
void IOS_EmuStartProg(const char *prog, u32 pri);
void IOS_DebugMemDump(void);
void IOS_DebugTimerListDump(void);
#endif /* _LANGUAGE_C */

#endif /*__IOS_H__*/
