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
#ifndef __IOSTYPES_H__
#define __IOSTYPES_H__

#ifndef NULL
#define NULL 0
#endif 

#if defined(_LANGUAGE_C)
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
#endif


#define IOS_ERROR_OK              0
#define IOS_ERROR_ACCESS         -1
#define IOS_ERROR_EXISTS         -2
#define IOS_ERROR_INTR           -3
#define IOS_ERROR_INVALID        -4
#define IOS_ERROR_MAX            -5
#define IOS_ERROR_NOEXISTS       -6
#define IOS_ERROR_QEMPTY         -7
#define IOS_ERROR_QFULL          -8
#define IOS_ERROR_UNKNOWN        -9
#define IOS_ERROR_NOTREADY       -10
#define IOS_ERROR_ECC            -11
#define IOS_ERROR_ECC_CRIT       -12
#define IOS_ERROR_BADBLOCK       -13

#define IOS_THREAD_CREATE_JOINABLE 0
#define IOS_THREAD_CREATE_DETACHED 1

#define IOS_MESSAGE_BLOCK        0
#define IOS_MESSAGE_NOBLOCK      1

#define IOS_EVENT_WDOG             0
#define IOS_EVENT_SWI              1
#define IOS_EVENT_UNDEF2           2
#define IOS_EVENT_UNDEF3           3
#define IOS_EVENT_TIMER            4 
#define IOS_EVENT_TIMER23          5
#define IOS_EVENT_UNDEF6           6
#define IOS_EVENT_UNDEF7           7
#define IOS_EVENT_UNDEF8           8
#define IOS_EVENT_UNDEF9           9
#define IOS_EVENT_UNDEF10         10
#define IOS_EVENT_UNDEF11         11
#define IOS_EVENT_UART0           12
#define IOS_EVENT_UART1           13
#define IOS_EVENT_UART2           14
#define IOS_EVENT_UNDEF15         15
#define IOS_EVENT_UNDEF16         16
#define IOS_EVENT_UNDEF17         17
#define IOS_EVENT_PWRFAIL         18
#define IOS_EVENT_UNDEF19         19
#define IOS_EVENT_UNDEF20         20
#define IOS_EVENT_UNDEF21         21
#define IOS_EVENT_UNDEF22         22
#define IOS_EVENT_UNDEF23         23
#define IOS_EVENT_UNDEF24         24
#define IOS_EVENT_ETHERNET        25
#define IOS_EVENT_USB             26
#define IOS_EVENT_PCI0            27
#define IOS_EVENT_PCI1            28
#define IOS_EVENT_PCI2            29
#define IOS_EVENT_PCI3            30
#define IOS_EVENT_SIC             31
#define IOS_NUM_EVENTS 32

#define IOS_SEEK_SET     0
#define IOS_SEEK_CURRENT 1
#define IOS_SEEK_END     2

#define IOS_OPEN     1
#define IOS_CLOSE    2
#define IOS_READ     3
#define IOS_WRITE    4
#define IOS_SEEK     5
#define IOS_IOCTL    6
#define IOS_IOCTLV   7
#define IOS_REPLY    8

#if defined(_LANGUAGE_C)
typedef s32 IOSError;
typedef s32 IOSThreadId;
typedef s32 IOSProcessId;

typedef s32 IOSMessageQueueId;
typedef s32 IOSMessage;
typedef s32 IOSTimerId;

typedef s32 IOSInterfaceId;

typedef s32 IOSFd;

typedef u32 IOSUid;
typedef u16 IOSGid;

typedef u32 IOSTime;

typedef void (*IOSEntryProc)(u32);

typedef u32 IOSEvent;

typedef u32 IOSResourceHandle;

typedef struct {
    u8 *path;
    u32 flags;
    IOSUid uid;
    IOSGid gid;
} IOSResourceOpen;

typedef struct {
    u8 *outPtr;
    u32 outLen;
} IOSResourceRead;

typedef struct {
    u8 *inPtr;
    u32 inLen;
} IOSResourceWrite;

typedef struct {
    s32 offset;
    u32 whence;
} IOSResourceSeek;

typedef struct {
    u32 cmd;
    u8 *inPtr;
    u32 inLen;
    u8 *outPtr;
    u32 outLen;
} IOSResourceIoctl;

typedef struct {
        u8 *base;
            u32 length;
} IOSIoVector;

typedef struct {
    u32 cmd;
    u32 readCount;
    u32 writeCount;
    IOSIoVector *vector;
} IOSResourceIoctlv;

typedef struct {
    u32 cmd;
    IOSError status;
    IOSResourceHandle handle;
    union {
        IOSResourceOpen open;
        IOSResourceRead read;
        IOSResourceWrite write;
        IOSResourceSeek seek;
        IOSResourceIoctl ioctl;
        IOSResourceIoctlv ioctlv;
    } args;
} IOSResourceRequest;

#endif

#endif /*__IOSTYPES_H__*/
