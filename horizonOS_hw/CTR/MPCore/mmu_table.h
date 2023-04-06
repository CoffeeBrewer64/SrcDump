/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmu_table.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_MPCORE_MMU_TABLE_H_
#define NN_HW_CTR_MPCORE_MMU_TABLE_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


// MMUv6 Table Structure

#ifndef SDK_ASM

typedef struct
{
    u32 sb0_0:1;
    u32 sb1_1:1;
    u32 bafferable:1;
    u32 cacheable:1;
    u32 executeNever:1;
    u32 ignored:4;
    u32 notifyEcc:1;
    u32 permission:2;
    u32 memoryTypeEx:3;
    u32 permissionEx:1;
    u32 shared:1;
    u32 notGlobal:1;
    u32 sb1_18:1;
    u32 sb0_19_23:3;
    u32 base:8;
}
OSMMUv6SuperSection, OSMMUv6Section16MB;

typedef struct
{
    u32 sb0_0:1;
    u32 sb1_1:1;
    u32 bafferable:1;
    u32 cacheable:1;
    u32 executeNever:1;
    u32 domain:4;
    u32 notifyEcc:1;
    u32 permission:2;
    u32 memoryTypeEx:3;
    u32 permissionEx:1;
    u32 shared:1;
    u32 notGlobal:1;
    u32 sb0_18_19:2;
    u32 base:12;
}
OSMMUv6Section, OSMMUv6Section1MB;

typedef struct
{
    u32 sb1_0:1;
    u32 sb0_1_4:4;
    u32 domain:4;
    u32 notifyEcc:1;
    u32 base:12;
    u32 padding: 10;
}
OSMMUv6CoarsePage;

typedef struct
{
    u32 sb1_0:1;
    u32 sb0_1:1;
    u32 bafferable:1;
    u32 cacheable:1;
    u32 permission:2;
    u32 sb0_6_8:3;
    u32 permissionEx:1;
    u32 shared:1;
    u32 notGlobal:1;
    u32 memoryTypeEx:3;
    u32 executeNever:1;
    u32 base:16;
}
OSMMUv6LargePage, OSMMUv6Page64KB;

typedef struct
{
    u32 executeNever:1;
    u32 sb1_1:1;
    u32 bafferable:1;
    u32 cacheable:1;
    u32 permission:2;
    u32 memoryTypeEx:3;
    u32 permissionEx:1;
    u32 shared:1;
    u32 notGlobal:1;
    u32 base:20;
}
OSMMUv6SmallPage, OSMMUv6Page4KB;

#endif // SDK_ASM


// MMUv6 Table Formats

// Supersection

#ifndef SDK_ASM
#define HW_MMU6_T1_SUSEC_PACK_PADDR( paddr ) ((paddr) & HW_MMU6_T1_SUSEC_BASE_MASK)
#define HW_MMU6_T1_SUSEC_PACK_ATTR( apx, rgt, nglobal, sh, xn ) \
        ( ((apx)    << HW_MMU6_T1_APX_SFT) \
        | ((rgt)    << HW_MMU6_T1_RGT_SFT) \
        | ((nglobal) ? HW_MMU6_T1_NGLOBAL : 0) \
        | ((sh)      ? HW_MMU6_T1_SHARED : 0) \
        | ((xn)      ? HW_MMU6_T1_XN : 0) \
        | HW_MMU6_T1_SUSEC_SB1 )
#define HW_MMU6_T1_SUSEC_PACK2( paddr, attr ) ( HW_MMU6_T1_SUSEC_PACK_PADDR( paddr ) | attr)
#define HW_MMU6_T1_SUSEC_PACK( paddr, apx, rgt, nglobal, sh, xn ) HW_MMU6_T1_SUSEC_PACK2( paddr, HW_MMU6_T1_SUSEC_PACK_ATTR( apx, rgt, nglobal, sh, xn ) )
#endif

#define HW_MMU6_T1_SUSEC_SB1        0x00040002  // Should be 1

#define HW_MMU6_T1_SUSEC_BASE_MASK  0xff000000  // Base address (per 16MB)

#define HW_MMU6_T1_SUSEC_BASE_SFT   24

#define HW_MMU6_T1_SUSEC_SIZE       0x01000000
#define HW_MMU6_T1_SUSEC_ALIAS_SIZE 0x00100000

// Section

#ifndef SDK_ASM

#define HW_MMU6_T1_SEC_PACK_PADDR(paddr) ((paddr) & HW_MMU6_T1_SEC_BASE_MASK)
#define HW_MMU6_T1_SEC_PACK_ATTR(apx, rgt, nglobal, sh, xn, domain) \
        ( ((apx)    << HW_MMU6_T1_APX_SFT) \
        | ((rgt)    << HW_MMU6_T1_RGT_SFT) \
        | ((nglobal) ? HW_MMU6_T1_NGLOBAL : 0) \
        | ((sh)      ? HW_MMU6_T1_SHARED : 0) \
        | ((xn)      ? HW_MMU6_T1_XN : 0) \
        | ((domain) << HW_MMU6_T1_DOMAIN_SFT) \
        | HW_MMU6_T1_SEC_SB1 )
#define HW_MMU6_T1_SEC_PACK2( paddr, attr ) ( HW_MMU6_T1_SEC_PACK_PADDR(paddr) | attr )
#define HW_MMU6_T1_SEC_PACK( paddr, apx, rgt, nglobal, sh, xn, domain ) HW_MMU6_T1_SEC_PACK2(paddr, HW_MMU6_T1_SEC_PACK_ATTR(apx, rgt, nglobal, sh, xn, domain))
#endif

#define HW_MMU6_T1_SEC_SB1          0x00000002  // Should be 1

#define HW_MMU6_T1_SEC_BASE_MASK    0xfff00000  // Base address (per 1MB)

#define HW_MMU6_T1_SEC_BASE_SFT     20

#define HW_MMU6_T1_SEC_SIZE         0x00100000

// Coarse page table

#ifndef SDK_ASM
#define HW_MMU6_T1_COURSE_PACK( paddr, domain ) \
                                          \
        ( ((paddr) & HW_MMU6_T1_CORS_MASK) \
        | ((domain) << HW_MMU6_T1_DOMAIN_SFT) \
        | HW_MMU6_T1_CORS_SB1 )
#endif

#define HW_MMU6_T1_CORS_SB1         0x00000001  // Should be 1

#define HW_MMU6_T1_CORS_MASK        0xfffffc00  // Coarse page table address (per 1KB)

#define HW_MMU6_T1_CORS_SFT         12

#define HW_MMU6_T1_CORS_SIZE        0x00000400

// Supersection/Section/Coarse Common

#define HW_MMU6_T1_ECC_E            0x00000200  // ECC enable

// Section/Coarse Common

#define HW_MMU6_T1_DOMAIN_MASK      0x000001e0  // Domain

#define HW_MMU6_T1_DOMAIN_SFT       5

// Supersection/Section Common

#define HW_MMU6_T1_NGLOBAL          0x00020000  // Not Global (at subpages disabled)
#define HW_MMU6_T1_GLOBAL           0x00000000  // Global
#define HW_MMU6_T1_ASID_ENABLE      HW_MMU6_T1_NGLOBAL
#define HW_MMU6_T1_ASID_DISABLE     HW_MMU6_T1_GLOBAL
#define HW_MMU6_T1_SHARED           0x00010000  // Shared (Normal region only, at subpages disabled)
#define HW_MMU6_T1_APX_MASK         0x00008c00  // Access Permissions Extension (at subpages disabled)
#define HW_MMU6_T1_XN               0x00000010  // Execute Never (at subpages disabled)
#define HW_MMU6_T1_RGT_MASK         0x0000700c  // Region Type

#define HW_MMU6_T1_APX_SFT          10
#define HW_MMU6_T1_RGT_SFT          2

#define HW_MMU6_T1_APX_NA           HW_MMU6_APX_NA
#define HW_MMU6_T1_APX_S_RW_U_NA    HW_MMU6_APX_S_RW_U_NA
#define HW_MMU6_T1_APX_S_RW_U_RO    HW_MMU6_APX_S_RW_U_RO
#define HW_MMU6_T1_APX_ALL          HW_MMU6_APX_ALL
#define HW_MMU6_T1_APX_S_RO_U_NA    HW_MMU6_APX_S_RO_U_NA
#define HW_MMU6_T1_APX_S_RO_U_RO    HW_MMU6_APX_S_RO_U_RO

#define HW_MMU6_T1_RGT_STRONG_ORDER 0x0000  // Strongly Ordered, regardless of the S bit in the page table
#define HW_MMU6_T1_RGT_SHARED_DEV   0x0001  // Shared Device, regardless of the S bit in the page table
#define HW_MMU6_T1_RGT_NSHARED_DEV  0x0800  // Non-Shared Device, regardless of the S bit in the page table
#define HW_MMU6_T1_RGT_L1C_NC_NB    0x1000  // L1C Noncachable, Unbuffered
#define HW_MMU6_T1_RGT_L1C_WB_WA    0x1001  // L1C Write-back Write-allocate, Buffered
#define HW_MMU6_T1_RGT_L1L2C_NC     0x0400  // L1C and L2C Noncachable
#define HW_MMU6_T1_RGT_L1L2C_WB_WA  0x0403  // L1C and L2C Write-Back, Allocate on Write


// MMUv6 L2 Table Formats

// Large page

#ifndef SDK_ASM
#define HW_MMU6_T2_LP_PACK_PADDR( paddr ) ((paddr) & HW_MMU6_T2_LP_BASE_MASK)
#define HW_MMU6_T2_LP_PACK_ATTR( apx, rgt, nglobal, sh, xn ) \
        ( ((apx)    << HW_MMU6_T2_APX_SFT) \
        | ((rgt)    << HW_MMU6_T2_LP_RGT_SFT) \
        | ((nglobal) ? HW_MMU6_T2_NGLOBAL : 0) \
        | ((sh)      ? HW_MMU6_T2_SHARED : 0) \
        | ((xn)      ? HW_MMU6_T2_LP_XN : 0) \
        | HW_MMU6_T2_LP_SB1 )
#define HW_MMU6_T2_LP_PACK2( paddr, attr ) (HW_MMU6_T2_LP_PACK_PADDR( paddr ) | attr)
#define HW_MMU6_T2_LP_PACK( paddr, apx, rgt, nglobal, sh, xn ) HW_MMU6_T2_LP_PACK2( paddr, HW_MMU6_T2_LP_PACK_ATTR( apx, rgt, nglobal, sh, xn ) )
#endif

#define HW_MMU6_T2_LP_SB1           0x00000001  // Should be 1

#define HW_MMU6_T2_LP_BASE_MASK     0xffff0000  // Base address (per 64KB)
#define HW_MMU6_T2_LP_XN            0x00008000  // Execute Never (at subpages disabled)
#define HW_MMU6_T2_LP_RGT_MASK      0x0000700c  // Region Type

#define HW_MMU6_T2_LP_BASE_SFT      16
#define HW_MMU6_T2_LP_RGT_SFT       2

#define HW_MMU6_T2_LP_RGT_STRONG_ORDER  HW_MMU6_T1_RGT_STRONG_ORDER
#define HW_MMU6_T2_LP_RGT_SHARED_DEV    HW_MMU6_T1_RGT_SHARED_DEV
#define HW_MMU6_T2_LP_RGT_NSHARED_DEV   HW_MMU6_T1_RGT_NSHARED_DEV
#define HW_MMU6_T2_LP_RGT_L1C_NC_NB     HW_MMU6_T1_RGT_L1C_NC_NB
#define HW_MMU6_T2_LP_RGT_L1C_WB_WA     HW_MMU6_T1_RGT_L1C_WB_WA
#define HW_MMU6_T2_LP_RGT_L1L2C_NC      HW_MMU6_T1_RGT_L1L2C_NC
#define HW_MMU6_T2_LP_RGT_L1L2C_WB_WA   HW_MMU6_T1_RGT_L1L2C_WB_WA

#define HW_MMU6_T2_LP_SIZE          0x00010000
#define HW_MMU6_T2_LP_ALIAS_SIZE    0x00001000

// Small page

#ifndef SDK_ASM
#define HW_MMU6_T2_SP_PACK_PADDR( paddr ) ((paddr) & HW_MMU6_T2_SP_BASE_MASK)
#define HW_MMU6_T2_SP_PACK_ATTR( apx, rgt, nglobal, sh, xn ) \
        ( ((apx)    << HW_MMU6_T2_APX_SFT) \
        | ((rgt)    << HW_MMU6_T2_SP_RGT_SFT) \
        | ((nglobal) ? HW_MMU6_T2_NGLOBAL : 0) \
        | ((sh)      ? HW_MMU6_T2_SHARED : 0) \
        | ((xn)      ? HW_MMU6_T2_SP_XN : 0) \
        | HW_MMU6_T2_SP_SB1 )
#define HW_MMU6_T2_SP_PACK2( paddr, attr ) (HW_MMU6_T2_SP_PACK_PADDR( paddr ) | attr)
#define HW_MMU6_T2_SP_PACK( paddr, apx, rgt, nglobal, sh, xn ) HW_MMU6_T2_SP_PACK2( paddr, HW_MMU6_T2_SP_PACK_ATTR( apx, rgt, nglobal, sh, xn ) )
#endif

#define HW_MMU6_T2_SP_SB1           0x00000002  // Should be 1

#define HW_MMU6_T2_SP_BASE_MASK     0xfffff000  // Base address (per 4KB)
#define HW_MMU6_T2_SP_XN            0x00000001  // Execute Never (at subpages disabled)
#define HW_MMU6_T2_SP_RGT_MASK      0x000001cc  // Region Type

#define HW_MMU6_T2_SP_BASE_SFT      12
#define HW_MMU6_T2_SP_RGT_SFT       2

#define HW_MMU6_T2_SP_RGT_STRONG_ORDER    0x00  // Strongly Ordered, regardless of the S bit in the page table
#define HW_MMU6_T2_SP_RGT_SHARED_DEV      0x01  // Shared Device, regardless of the S bit in the page table
#define HW_MMU6_T2_SP_RGT_NSHARED_DEV     0x20  // Non-Shared Device, regardless of the S bit in the page table
#define HW_MMU6_T2_SP_RGT_L1C_NC_NB       0x40  // L1C Noncachable, Unbuffered
#define HW_MMU6_T2_SP_RGT_L1C_WB_WA       0x41  // L1C Write-back Write-allocate, Buffered
#define HW_MMU6_T2_SP_RGT_L1L2C_NC        0x10  // L1C and L2C Noncachable
#define HW_MMU6_T2_SP_RGT_L1L2C_WB_WA     0x13  // L1C and L2C Write-Back, Allocate on Write

#define HW_MMU6_T2_SP_SIZE          0x00001000

// LargePage/SmallPage Common

#define HW_MMU6_T2_NGLOBAL          0x00000800  // Not Global (at subpages disabled)
#define HW_MMU6_T2_GLOBAL           0x00000000  // Global
#define HW_MMU6_T2_ASID_ENABLE      HW_MMU6_T2_NGLOBAL
#define HW_MMU6_T2_ASID_DISABLE     HW_MMU6_T2_GLOBAL
#define HW_MMU6_T2_SHARED           0x00000400  // Shared (Normal region only, at subpages disabled)
#define HW_MMU6_T2_APX_MASK         0x00000230  // Access Permissions Extension (at subpages disabled)

#define HW_MMU6_T2_APX_SFT          4

#define HW_MMU6_T2_APX_NA           HW_MMU6_APX_NA
#define HW_MMU6_T2_APX_S_RW_U_NA    HW_MMU6_APX_S_RW_U_NA
#define HW_MMU6_T2_APX_S_RW_U_RO    HW_MMU6_APX_S_RW_U_RO
#define HW_MMU6_T2_APX_ALL          HW_MMU6_APX_ALL
#define HW_MMU6_T2_APX_S_RO_U_NA    HW_MMU6_APX_S_RO_U_NA
#define HW_MMU6_T2_APX_S_RO_U_RO    HW_MMU6_APX_S_RO_U_RO


// Supersection/Section/Coarse/LargePage/SmallPage Common

#define HW_MMU6_APX_NA              0x00    // Access denied
#define HW_MMU6_APX_S_RW_U_NA       0x01    // Supervisor access only
#define HW_MMU6_APX_S_RW_U_RO       0x02    // Supervisor full access, User read only
#define HW_MMU6_APX_ALL             0x03    // Full access
#define HW_MMU6_APX_S_RO_U_NA       0x21    // Supervisor read only
#define HW_MMU6_APX_S_RO_U_RO       0x23    // Supervisor/User read only

#define HW_MMU6_CBA_NC_NB           0   // Noncachable, Unbuffered
#define HW_MMU6_CBA_WB_WA           1   // Write-back Write-allocate, Buffered


#ifdef __cplusplus
} // extern "C"
#endif

// NN_HW_CTR_MPCORE_MMU_TABLE_H_
#endif
