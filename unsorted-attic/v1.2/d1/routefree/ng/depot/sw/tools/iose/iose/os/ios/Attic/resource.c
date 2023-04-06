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

#include <iostypes.h>

IOSError
iosRegisterResourceManager(char *path, IOSMessageQueueId mq)
{
    return IOS_ERROR_OK;
}

IOSError
iosUnregisterResourceManager(char *path)
{
    return IOS_ERROR_OK;
}

IOSCid
iosOpen(const char *pathname, u32 flags)
{
    return 0;
}

IOSError
iosClose(IOSCid fd)
{
    return IOS_ERROR_OK;
}

s32
iosRead(IOSCid fd, void *buf, u32 count)
{
    return IOS_ERROR_OK;
}

s32
iosWrite(IOSCid fd, void *buf, u32 count)
{
    return IOS_ERROR_OK;
}

s32
iosSeek(IOSCid fd, s32 offset, u32 whence)
{
    return IOS_ERROR_OK;
}

IOSError
iosIoctl(IOSCid fd, s32 cmd, void *input, u32 input_bytes, void *output, u32 output_bytes)
{
    return IOS_ERROR_OK;
}
