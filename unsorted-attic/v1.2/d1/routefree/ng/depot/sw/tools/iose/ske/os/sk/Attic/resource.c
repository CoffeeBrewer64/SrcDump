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

#include <sktypes.h>

SKError
skRegisterResourceManager(char *path, SKMessageQueueId mq)
{
    return SK_ERROR_OK;
}

SKError
skUnregisterResourceManager(char *path)
{
    return SK_ERROR_OK;
}

SKCid
skOpen(const char *pathname, u32 flags)
{
    return 0;
}

SKError
skClose(SKCid fd)
{
    return SK_ERROR_OK;
}

s32
skRead(SKCid fd, void *buf, u32 count)
{
    return SK_ERROR_OK;
}

s32
skWrite(SKCid fd, void *buf, u32 count)
{
    return SK_ERROR_OK;
}

s32
skSeek(SKCid fd, s32 offset, u32 whence)
{
    return SK_ERROR_OK;
}

SKError
skIoctl(SKCid fd, s32 cmd, void *input, u32 input_bytes, void *output, u32 output_bytes)
{
    return SK_ERROR_OK;
}
