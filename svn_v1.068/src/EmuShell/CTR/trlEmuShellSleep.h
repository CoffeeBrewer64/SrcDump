/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     sleep.h

  Copyright (C)2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 25650 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SAMPLE_DEMOS_DEMO2_SLEEP_H_
#define NN_SAMPLE_DEMOS_DEMO2_SLEEP_H_

#include <nn/applet.h>

    class SleepHandler
    {
    public:
        SleepHandler() {}
        ~SleepHandler() {}

        static void Initialize( void );
        static void Finalize( void );
        static bool IsSleepRequested( void );
        static void SleepSystem( void );

        static nn::applet::AppletQueryReply SleepQueryCallback( uptr arg );
        static void             AwakeCallback( uptr arg );
        static void             CancelCallback( uptr arg );
        
        static volatile bool             s_IsAfterWakeUp;
        
    private:
        static nn::os::LightEvent   s_AwakeEvent;
        static bool                 s_IsInitialized;
    };


#endif // NN_SAMPLE_DEMOS_DEMO2_SLEEP_H_
