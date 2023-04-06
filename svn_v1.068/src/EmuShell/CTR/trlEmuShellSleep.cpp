/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     sleep.cpp

  Copyright (C)2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 33028 $
 *---------------------------------------------------------------------------*/

#include "trlEmuShellSleep.h"

extern nn::os::CriticalSection g_SleepCS;
extern nn::os::LightEvent g_TransitionEvent;
extern nn::os::LightEvent g_AwakeEvent;

volatile bool SleepHandler::s_IsAfterWakeUp = false;

/*------------------------------------------------------------------------*/
void SleepHandler::Initialize( void )
{
    nn::applet::SetSleepQueryCallback(SleepQueryCallback, 0);
    nn::applet::SetAwakeCallback(AwakeCallback, 0);
//    nn::applet::SetSleepCancelCallback(NULL, 0);
}

/*------------------------------------------------------------------------*/
void SleepHandler::Finalize( void )
{
    nn::applet::SetSleepQueryCallback(NULL, 0);
    nn::applet::SetAwakeCallback(NULL, 0);

    nn::applet::DisableSleep();
}

bool SleepHandler::IsSleepRequested( void )
{
    if ( nn::applet::IsExpectedToReplySleepQuery() )
        return true;

    return false;
}

void SleepHandler::SleepSystem( void )
{
    //if ( g_SleepCS.TryEnter() )
    {

        nn::applet::ReplySleepQuery(nn::applet::REPLY_ACCEPT);

        g_AwakeEvent.Wait();
                
        g_SleepCS.Leave();
    }
}

nn::applet::AppletQueryReply SleepHandler::SleepQueryCallback( uptr arg )
{
    NN_UNUSED_VAR(arg);

    g_AwakeEvent.ClearSignal();

    if ( !nn::applet::IsActive() )
    {
        return nn::applet::REPLY_ACCEPT;
    }
    else
    {
        return nn::applet::REPLY_LATER;
    }
}

void SleepHandler::AwakeCallback( uptr arg )
{
    NN_UNUSED_VAR(arg);
    g_AwakeEvent.Signal();
    
    s_IsAfterWakeUp = true;
}
