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
#ifndef __SK_H__
#define __SK_H__

#include <sktypes.h>

#define DEFAULT_SDK_LOC  "/opt/iop-sdk/"
#define DEFAULT_BIN_LOC  "/usr/bin/ske/"

#if defined(_LANGUAGE_C)


SKError skDestroyThread(SKThreadId id);
#define SK_ThreadExit(X)  skDestroyThread(0)

SKThreadId SK_Fork(SKEntryProc entry, void *arg, void *stack,
			   u32 stackSize, u32 priority);
SKThreadId SK_CreateThread(SKEntryProc entry, void *arg, void *stack,
			   u32 stackSize, u32 priority);
SKError SK_DestroyThread(SKThreadId id);
SKThreadId SK_GetThreadId(void);
SKProcessId SK_GetProcessId(void);
SKError SK_StartThread(SKThreadId id);
SKError SK_StopThread(SKThreadId id);
void SK_YieldThread(void);
u32 SK_GetThreadPriority(SKThreadId id);
SKError SK_SetThreadPriority(SKThreadId id, u32 priority);
SKMessageQueueId SK_CreateMessageQueue(SKMessage * msgarray, u32 count,
				       u32 pIdMask);
SKError SK_DestroyMessageQueue(SKMessageQueueId id);
SKError SK_SendMessage(SKMessageQueueId mq, SKMessage msg, u32 flag);
SKError SK_JamMessage(SKMessageQueueId mq, SKMessage msg, u32 flag);
SKError SK_ReceiveMessage(SKMessageQueueId mq, SKMessage * msg, u32 flag);
SKError SK_HandleEvent(SKEvent event, SKMessageQueueId mq, SKMessage mesg);
SKError SK_UnhandleEvent(SKEvent event);

SKTimerId skSetTimer(SKTime, SKMessageQueueId, SKMessage, u8);
#define SK_SetTimer(duration, mq, mesg) \
    skSetTimer((duration), (mq), (mesg), 0)
#define SK_SetPeriodicTimer(period, mq, mesg) \
    skSetTimer((period), (mq), (mesg), 1)
SKError SK_StopTimer(SKTimerId id);
SKError SK_ShareRegion(void *ptr, u32 size, u32 pIdMask);
SKError SK_UnshareRegion(void *ptr, u32 size, u32 pIdMask);
void *SK_Alloc(u32 size);
SKError SK_Free(void *ptr);
u32 SK_GetSdramPageSize(void);
SKError SK_RegisterRpc(SKInterfaceId id, SKMessageQueueId mq);
SKError SK_RegisterResourceManager(char *path, SKMessageQueueId mq);
SKCid SK_Open(const char *pathname, u32 flags);
SKError SK_Close(SKCid fd);
s32 SK_Read(SKCid fd, void *buf, u32 count);
s32 SK_Write(SKCid fd, void *buf, u32 count);
s32 SK_Seek(SKCid fd, s32 offset, u32 whence);
SKError SK_Ioctl(SKCid fd, s32 cmd, void *input, u32 input_bytes,
		 void *output, u32 output_bytes);

SKError  IUSB_FindDevice(u16 vendorId, u16 productId,
                            char *buf, int bufsize);
SKError IUSB_FindDeviceIds(u16 vendorId, u16 productId, int *maj, int *min);
void SK_DebugMemDump(void);
void SK_DebugTimerListDump(void);
void SK_EmuStartProg(const char *prog, u32 pri);
#endif /* _LANGUAGE_C */

#endif /*__SK_H__*/
