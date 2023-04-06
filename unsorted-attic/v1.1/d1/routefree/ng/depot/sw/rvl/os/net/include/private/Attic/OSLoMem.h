d1 269
a269 265
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS Locore Map
  File:     OSLoMem.h

  Copyright 1998 - 2003 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/include/private/OSLoMem.h $
    
    26    04/02/23 11:03 Hashida
    Updated to support old apploader.
    
    25    04/02/19 0:41 Hashida
    Added OS_CURRENT_TGC_OFFSET.
    
    24    04/01/30 18:19 Hashida
    Deleted OS_IS_REBOOTED and OS_RESTART_CODE.
    Added OS_EXEC_PARAMS_ADDR.
    
    23    11/13/03 14:20 Shiki
    Added support for OSGetRestartCode().

    22    7/22/03 10:05 Shiki
    Defined OS_GAMECHOICE bit definitions.

    21    3/07/03 14:41 Shiki
    Added comment about Uji reserved area.

    20    03/03/04 13:09 Hashida
    Added OS_DOL_OFFSET_TO_BOOT (4 bytes).

    19    11/22/01 14:40 Shiki
    Added OS_GAMECHOICE2.

    18    9/15/01 3:33a Hashida
    Added OS_RESET_SHUTDOWN

    17    8/27/01 10:35 Shiki
    Added OS_GAMECHOICE.

    16    8/21/01 3:44p Hashida
    Added devicecode.

    15    7/16/01 13:51 Shiki
    Modified to define OS_*_CLOCK_SPEED for HW2 too.

    14    01/07/09 16:23 Shiki
    Added OS_PAD3_BUTTON.

    13    7/06/01 1:26p Hashida
    Added OS_IS_REBOOTED.

    12    01/03/21 14:50 Shiki
    Added OS_WIRELESS_PAD_FIX_MODE.

    11    2/21/01 4:49p Hashida
    Added system time base.

    10    1/15/01 6:52p Hashida
    Added BS2GetBytesLeft function support.

    9     10/31/00 4:41p Shiki
    Reserved DLL control block.

    8     9/12/00 10:43p Shiki
    Added OS_EXIn_PROBE_START_TIME.

    7     6/15/00 12:09a Shiki
    Added OS_*_CLOCK_SPEED.

    6     3/23/00 6:26p Hashida
    Added console simulated memory size, debug monitor size, debug monitor
    address and bootinfo2 address.

    5     3/21/00 6:47p Shiki
    Updated.

    4     3/21/00 6:25p Shiki
    Reserved thread control structures in low-mem.

    3     3/10/00 5:36p Eugene
    Added 4 bytes for storage of ARAM size. Located at 0xd0-0xd3.

    2     2/17/00 4:20p Hashida
    Added OS_TVTYPES_ADDR

    2     9/01/99 1:01p Tian
    Added field for OSDBIntegrator to save link register to.

    1     8/23/99 2:18p Tian
    Moved to include/private from include/dolphin/os.

    8     8/17/99 2:18a Shiki
    Added OS_UINTERRUPTMASK_ADDR.

    7     8/16/99 10:23p Shiki
    Added OS_INTERRUPTMASK_ADDR.

    6     7/20/99 5:14p Tian
    Fixed addition mistakes in comments.

    5     7/16/99 1:27p Tian
    Added a region for the code that performs the jump to the well known
    debugger breakpoint location.

    4     7/08/99 8:08p Tian
    mods for new debugger/kernel integration

    3     5/11/99 4:43p Shiki
    Refreshed include tree.

    1     4/30/99 12:49p Tianli01

    4     4/21/99 4:13p Tianli01
    updated comments, added console type information.

    3     3/31/99 6:07p Tianli01
    Added DBInterface field offsets.

    2     3/26/99 2:09p Tianli01
    Created.  PPC low memory map.

    1     3/26/99 2:08p Tianli01
    Broken up from previous OS.h.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __OSLOMEM_H__
#define __OSLOMEM_H__

/*
    Low memory map

    0x0000 0000 - 0x0000 003F   BootInfo structure          (64 bytes, 64 used)
    0x0000 0040 - 0x0000 00BF   debugger related structures (128 bytes)
    0x0000 00C0 - 0x0000 00C3   __OSCurrentContextPA        (4 bytes)
    0x0000 00C4 - 0x0000 00C7   Global interrupt mask bits  (4 bytes)
    0x0000 00C8 - 0x0000 00CB   User interrupt mask bits    (4 bytes)
    0x0000 00CC - 0x0000 00CF   TV type                     (4 bytes)
    0x0000 00D0 - 0x0000 00D3   ARAM size                   (4 bytes)
    0x0000 00D4 - 0x0000 00E7   Thread control structures   (20 bytes)

    0x0000 00E8 - 0x0000 00EB   debug monitor size          (4 bytes)
    0x0000 00EC - 0x0000 00EF   free debug monitor addr     (4 bytes)
    0x0000 00F0 - 0x0000 00F3   simulated memory size       (4 bytes)
    0x0000 00F4 - 0x0000 00F7   boot info2 addr             (4 bytes)

    // for HW1, HW1_DRIP, HW2 and MINNOW
    0x0000 00F8 - 0x0000 00FB   bus clock speed (Hz)        (4 bytes)
    0x0000 00FC - 0x0000 00FF   core clock speed (Hz)       (4 bytes)

    0x0000 0100 - 0x0000 2FFF   Exception Table
    0x0000 2000 - 0x0000 20ff   Reserved by Uji             (256 bytes)

    0x0000 3000 - 0x0000 303F   OS Exception Handler Table  (64 bytes, 60 used)
    0x0000 3040 - 0x0000 30BF   OS Interrupt Handler Table  (128 bytes)

    0x0000 30C0 - 0x0000 30C3   EXI 0 probe start time      (4 bytes)
    0x0000 30C4 - 0x0000 30C7   EXI 1 probe start time      (4 bytes)
    0x0000 30C8 - 0x0000 30D3   DLL control block           (12 bytes)
    0x0000 30D4 - 0x0000 30D7   Information used by bootrom (4 bytes)
    0x0000 30D8 - 0x0000 30DF   System time base            (8 bytes)
    0x0000 30E0 - 0x0000 30E1   Wireless pad fix mode       (2 bytes - 0x3fff)
    0x0000 30E2                 Flag for reboot             (1 byte)
    0x0000 30E3                 multi game disk             (1 byte)
    0x0000 30E4 - 0x0000 30E5   pads[4].button              (2 bytes)
    0x0000 30E6 - 0x0000 30E7   dvd device code             (2 bytes)
    0x0000 30E8 - 0x0000 30E9   BI2 copy                    (2 bytes)
    0x0000 30EA - 0x0000 30EB   multi game disk             (2 bytes)
    0x0000 30EC - 0x0000 30EF   dol file execution          (4 bytes)
    0x0000 30F0 - 0x0000 30F3   parameters for exec         (4 bytes)
    0x0000 30F4 - 0x0000 30F7   tgc offset                  (4 bytes)
    0x0000 30F8 - 0x0000 30FF   RESERVED                    (8 bytes)

    0x0000 3100 -               Game

 */

#define OS_BOOTINFO_ADDR            0x0000  // 64 bytes, 64 used
#define OS_DBINTERFACE_ADDR         0x0040  // 32 bytes, 16 used
#define OS_DBJUMPPOINT_ADDR         0x0060  // 96 bytes, 36 used
#define OS_CURRENTCONTEXT_PADDR     0x00C0  // PA of __OSCurrentContext
#define OS_INTERRUPTMASK_ADDR       0x00C4  // Global interrupt mask bits
#define OS_UINTERRUPTMASK_ADDR      0x00C8  // User interrupt mask bits
#define OS_VITVTYPE_ADDR            0x00CC  // TV type
#define OS_ARAMSIZE_ADDR            0x00D0  // ARAM size (4 bytes)

// Thread control structure addresses (20 bytes, 20 used)
#define OS_CURRENTCONTEXT_ADDR      0x00D4  // 4 bytes
#define OS_FPUCONTEXT_ADDR          0x00D8  // 4 bytes
#define OS_ACTIVETHREADQUEUE_ADDR   0x00DC  // 8 bytes
#define OS_CURRENTTHREAD_ADDR       0x00E4  // 4 bytes

#define OS_DEBUGMONITOR_SIZE        0x00E8  // 4 bytes
#define OS_FREEDEBUGMONITOR_ADDR    0x00EC  // 4 bytes
#define OS_SIMULATEDMEM_SIZE        0x00F0  // 4 bytes
#define OS_BOOTINFO2_ADDR           0x00F4  // 4 bytes

#if     defined(HW1) || defined(HW1_DRIP) || defined(MINNOW) || defined(HW2)
#define OS_BUS_CLOCK_SPEED          0x00F8  // 4 bytes
#define OS_CORE_CLOCK_SPEED         0x00FC  // 4 bytes
#endif  defined(HW1) || defined(HW1_DRIP) || defined(MINNOW) || defined(HW2)

#define OS_EXCEPTIONTABLE_ADDR      0x3000  // 64 bytes, 60 used
#define OS_INTERRUPTTABLE_ADDR      0x3040  // 128 bytes

#define OS_EXI0_PROBE_START_TIME    0x30C0  // 4 bytes
#define OS_EXI1_PROBE_START_TIME    0x30C4  // 4 bytes

// DLL control block (12 bytes)
#define OS_MODULE_LIST_ADDR         0x30C8  // 8 bytes
#define OS_STRING_TABLE_ADDR        0x30D0  // 4 bytes

// Information used by bootrom
#define OS_BOOT_TOTAL_BYTES         0x30D4  // 4 bytes

// System time base
#define OS_SYSTEMTIME_BASE          0x30D8  // 8 bytes

// Wireless pad fix mode
#define OS_WIRELESS_PAD_FIX_MODE    0x30E0  // 2 bytes

#define OS_IS_REBOOTED              0x30E2  // 1 bytes

#define OS_GAMECHOICE               0x30E3  // 1 bytes
#define   OS_GAMECHOICE_TIMER           0x1f    // Set to fake reset button timer in min.
#define   OS_GAMECHOICE_PAD_RUMBLE      0x20    // Set to disable rumble.
#define   OS_GAMECHOICE_PAD_ORIGIN      0x40    // Set to disable recalibration.
#define   OS_GAMECHOICE_CARD_MOUNT      0x80    // Set to disable mount operation.

#define OS_PAD3_BUTTON              0x30E4  // 2 bytes

#define OS_DVD_DEVICECODE           0x30E6  // 2 bytes

// Copy of BI2
#define OS_DEBUG_FLAG               0x30E8  // 1 byte
#define OS_PAD_SPEC                 0x30E9  // 1 byte

// Game Choice
#define OS_GAMECHOICE2              0x30EA  // 2 bytes

// Dol Exec
#define OS_DOL_OFFSET_TO_BOOT       0x30EC  // 4 bytes (for backward comp.)

#define OS_EXEC_PARAMS_ADDR         0x30F0  // 4 bytes

#define OS_CURRENT_TGC_OFFSET       0x30F4  // 4 bytes

/*
    These macros should represent the offsets of the DBInterface structure
    members.  These members are fairly stable and should not change.  If
    there are additions to the DBInterface structure definition, they
    should come after these fields.
 */
#define DB_BPRESENT_OFFSET          0x0000
#define DB_EXCEPTIONMASK_OFFSET     0x0004
#define DB_EXCEPTIONDEST_OFFSET     0x0008
#define DB_EXCEPTIONRET_OFFSET      0x000C

#endif  // __OSLOMEM_H__
