#ident "$Id: crypto_stub.h,v 1.1 2005/12/16 01:07:42 craig Exp $"

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

#ifndef CRYPTO_STUB_H
#define CRYPTO_STUB_H

#include <stdint.h>

#include "sha1.h"

typedef uint32_t IOSHash[5];

typedef uint32_t IOSHashContext[5];

IOSError IOS_GenerateHash (IOSHashContext *context, 
                            void * inputData, 
                            uint32_t inputSize, 
                            uint32_t chainingFlag, 
                            IOSHash *hashData, 
                            IOSMessageQueueId mq, 
                            IOSMessage mesg);
#endif
