d1 182
a182 182
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dolphin/os.h>
#include <private/eth.h>

#ifdef WIN32
#include <windows.h>

u32 __OSCoreClock;

void OSPanic ( const char* file, int line, const char* msg, ... )
{
    va_list marker;

    OSDisableInterrupts();
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    exit(0);
}

void OSReport( const char* msg, ... )
{
    va_list marker;

    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
}

void OSSetAlarm( OSAlarm* alarm, OSTime tick, OSAlarmHandler handler )
{

}

void OSSetPeriodicAlarm ( OSAlarm* alarm, OSTime start, OSTime period,
                          OSAlarmHandler handler )
{

}

void OSCreateAlarm( OSAlarm* alarm )
{

}

void OSCancelAlarm( OSAlarm* alarm )
{

}

BOOL    OSDisableInterrupts ( void )
{
    return TRUE;
}

BOOL    OSEnableInterrupts  ( void )
{
    return TRUE;
}

BOOL    OSRestoreInterrupts ( BOOL level )
{
    return FALSE;
}

OSTime  OSGetTime( void )
{
    LARGE_INTEGER ll;

    QueryPerformanceCounter(&ll);
    return ll.QuadPart;
}

OSTick  OSGetTick( void )
{
    LARGE_INTEGER ll;

    QueryPerformanceCounter(&ll);
    return ll.LowPart;
}

OSTime __OSGetSystemTime( void )
{
    return 0;
}

void       OSInitThreadQueue   ( OSThreadQueue* queue )
{

}

void       OSSleepThread       ( OSThreadQueue* queue )
{

}

void       OSWakeupThread      ( OSThreadQueue* queue )
{

}

void OSInitMutex   ( OSMutex* mutex )
{
    mutex->count = 0;
}

void OSLockMutex   ( OSMutex* mutex )
{
    ++mutex->count;
}

void OSUnlockMutex ( OSMutex* mutex )
{
    --mutex->count;
}

void OSRegisterResetFunction  ( OSResetFunctionInfo* info )
{

}

void ETHSetRecvCallback(ETHCallback0 callback0, ETHCallback1 callback1)
{

}

void ETHSetProtoType(u16 *array, s32 num)
{

}

void ETHGetMACAddr(u8 *macaddr)
{

}

s32  ETHInit(s32 mode)
{
    return ETH_OK;
}

void ETHSendAsync(void *addr, s32 length, ETHCallback2 callback2)
{
#if 0
    static int count;

    if (0 < count++)
        return;
#endif
    callback2(0);
}

BOOL ETHGetLinkStateAsync(BOOL* status)
{
    return TRUE;
}

void ETHAddMulticastAddress( const u8* macaddr )
{

}

void ETHClearMulticastAddresses( void )
{

}

void OSProcessAlarm(void)
{

}

void OSRegisterVersion(const char* id)
{
    OSReport("%s\n", id);
}

#endif
