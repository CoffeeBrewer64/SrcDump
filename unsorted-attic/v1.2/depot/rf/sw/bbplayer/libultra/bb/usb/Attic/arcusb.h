#ifndef __arcusb_h__
#define __arcusb_h__

/*
 * Set appropriate ARC defines for BBPLAYER
 */
#define	__VUSB32__
#define __USB_OTG__
#undef __USB_OS_MQX__

/*HEADER******************************************************************
**************************************************************************
*** 
*** Copyright (c) 2001-2002 ARC International.
*** All rights reserved                                          
***                                                              
*** This software embodies materials and concepts which are      
*** confidential to ARC International and is made
*** available solely pursuant to the terms of a written license   
*** agreement with ARC International             
***
*** $Workfile:arc.h$
*** $Revision: 1.1 $
*** $Date: 2003/04/01 23:10:30 $
***
*** Description:      
***  This file contains ARC-specific defines.
***                                                               
**************************************************************************
*END*********************************************************************/

/*--------------------------------------------------------------------------*/
/*
**                            STANDARD TYPES
*/

/*
**  The following typedefs allow us to minimize portability problems
**  due to the various C compilers (even for the same processor) not
**  agreeing on the sizes of "int"s and "short int"s and "longs".
*/

#define _PTR_      *
#define _CODE_PTR_ *

typedef char _PTR_                    char_ptr;    /* signed character       */
typedef unsigned char  uchar, _PTR_   uchar_ptr;   /* unsigned character     */

typedef signed   char   int_8, _PTR_   int_8_ptr;   /* 8-bit signed integer   */
typedef unsigned char  uint_8, _PTR_   uint_8_ptr;  /* 8-bit signed integer   */

typedef          short int_16, _PTR_   int_16_ptr;  /* 16-bit signed integer  */
typedef unsigned short uint_16, _PTR_  uint_16_ptr; /* 16-bit unsigned integer*/

typedef          long  int_32, _PTR_   int_32_ptr;  /* 32-bit signed integer  */
typedef unsigned long  uint_32, _PTR_  uint_32_ptr; /* 32-bit unsigned integer*/

typedef unsigned long  boolean;  /* Machine representation of a boolean */

typedef void _PTR_     pointer;  /* Machine representation of a pointer */

/* IEEE single precision floating point number (32 bits, 8 exponent bits) */
typedef float          ieee_single;

/* IEEE double precision floating point number (64 bits, 11 exponent bits) */
typedef double         ieee_double;

typedef pointer        _usb_host_handle;

/*--------------------------------------------------------------------------*/
/*
**                          STANDARD CONSTANTS
**
**  Note that if standard 'C' library files are included after types.h,
**  the defines of TRUE, FALSE and NULL may sometimes conflict, as most
**  standard library files do not check for previous definitions.
*/

#ifdef  FALSE
   #undef  FALSE
#endif
#define FALSE ((boolean)0)

#ifdef  TRUE
   #undef  TRUE
#endif
#define TRUE ((boolean)1) 

#ifdef  NULL
   #undef  NULL
#endif

#ifdef __cplusplus
   #define NULL (0)
#else
   #define NULL ((pointer)0)
#endif

typedef  uint_32  VUSB_REGISTER;

/* The ARC is little-endian, just like USB */
#define USB_uint_16_low(x)                   ((x) & 0xFF)
#define USB_uint_16_high(x)                  (((x) >> 8) & 0xFF)

#ifndef __USB_OTG__
#if BSP_VUSB11_HOST_VECTOR0 < 6
   #define  HOST_INTERRUPT_ROUTINE_KEYWORD        _Interrupt1
#else
   #define  HOST_INTERRUPT_ROUTINE_KEYWORD        _Interrupt2
#endif

#if BSP_VUSB11_DEVICE_VECTOR0 < 6
	#define  DEVICE_INTERRUPT_ROUTINE_KEYWORD      _Interrupt1
#else
   #define  DEVICE_INTERRUPT_ROUTINE_KEYWORD      _Interrupt2
#endif
#endif /* !__USB_OTG__ */

#if BSP_VUSB11_OTG_VECTOR0 < 6
   #define  OTG_INTERRUPT_ROUTINE_KEYWORD         _Interrupt1
#else
   #define  OTG_INTERRUPT_ROUTINE_KEYWORD         _Interrupt2
#endif

#ifdef __USB_OTG__
#define DEVICE_INTERRUPT_ROUTINE_KEYWORD
#define HOST_INTERRUPT_ROUTINE_KEYWORD
#define  INTERRUPT_ROUTINE_KEYWORD OTG_INTERRUPT_ROUTINE_KEYWORD
#else
#define  INTERRUPT_ROUTINE_KEYWORD HOST_INTERRUPT_ROUTINE_KEYWORD
#endif /* __USB_OTG__ */

#define  VUSB_ARC_BDT_OUT_BIT                (0x10)
#define  VUSB_ARC_BDT_IN_BIT                 (0x00)
#define  VUSB_ARC_BDT_ODD_EVEN_BIT           (0x08)

#define  VUSB_BDT_OUT_BIT                    (VUSB_ARC_BDT_OUT_BIT)
#define  VUSB_BDT_IN_BIT                     (VUSB_ARC_BDT_IN_BIT)
#define  VUSB_BDT_ODD_EVEN_BIT               (VUSB_ARC_BDT_ODD_EVEN_BIT)

#define  VUSB_GET_STATUS(BDT_ptr)            (BDT_ptr->PID & VUSB_BD_PID_MASKS)
#define  VUSB_GET_BYTE_COUNT(BDT_ptr)        (BDT_ptr->BC)
#define  VUSB_ENDPT_REG_OFFSET               (0x40)

#define VUSB32_BDT_HACK	(TRUE)

/*
** VUSB Interrupt status register masks
*/

#define VUSB_INT_STAT_RESET               (0x01)
#define VUSB_INT_STAT_ERROR               (0x02)
#define VUSB_INT_STAT_SOF                 (0x04)
#define VUSB_INT_STAT_TOKEN_DONE          (0x08)
#define VUSB_INT_STAT_SLEEP               (0x10)
#define VUSB_INT_STAT_RESUME              (0x20)
#define VUSB_INT_STAT_ATTACH              (0x40)
#define VUSB_INT_STAT_STALL               (0x80)

/* Interrupt Enable Register Bit Masks */
#define  VUSB_INT_ENB_USB_RST             (0x01)
#define  VUSB_INT_ENB_ERROR               (0x02)
#define  VUSB_INT_ENB_SOF_TOK             (0x04)
#define  VUSB_INT_ENB_TOK_DNE             (0x08)
#define  VUSB_INT_ENB_SLEEP               (0x10)
#define  VUSB_INT_ENB_RESUME              (0x20)
#define  VUSB_INT_ENB_ATTACH              (0x40)
#define  VUSB_INT_ENB_STALL               (0x80)

/* Error Interrupt Status Register Bit Masks */
#define  VUSB_ERR_STAT_PID_ERR            (0x01)
#define  VUSB_ERR_STAT_CRC5_EOF           (0x02)
#define  VUSB_ERR_STAT_CRC16              (0x04)
#define  VUSB_ERR_STAT_DFN8               (0x08)
#define  VUSB_ERR_STAT_BTO_ERR            (0x10)
#define  VUSB_ERR_STAT_DMA_ERR            (0x20)
#define  VUSB_ERR_STAT_RSVD               (0x40)
#define  VUSB_ERR_STAT_BTS_ERR            (0x80)

/* Error Interrupt Enable Register Bit Masks */
#define  VUSB_ERR_ENB_PID_ERR             (0x01)
#define  VUSB_ERR_ENB_CRC5_EOF            (0x02)
#define  VUSB_ERR_ENB_CRC16               (0x04)
#define  VUSB_ERR_ENB_DFN8                (0x08)
#define  VUSB_ERR_ENB_BTO_ERR             (0x10)
#define  VUSB_ERR_ENB_DMA_ERR             (0x20)
#define  VUSB_ERR_ENB_RSVD                (0x40)
#define  VUSB_ERR_ENB_BTS_ERR             (0x80)

/* Status Register Bit Masks */
#define  VUSB_STATUS_ODD                  (0x04)
#define  VUSB_STATUS_IN                   (0x08)
#define  VUSB_STATUS_ENDP                 (0xF0)

/* Control Register Bit Masks */
#define  VUSB_CTRL_USB_EN                 (0x01)
#define  VUSB_CTRL_ODD_RST                (0x02)
#define  VUSB_CTRL_RESUME                 (0x04)
#define  VUSB_CTRL_HOST_MODE_EN           (0x08)
#define  VUSB_CTRL_RESET                  (0x10)
#define  VUSB_CTRL_TOKEN_BUSY             (0x20)
#define  VUSB_CTRL_TXD_SUSPEND            (0x20)
#define  VUSB_CTRL_SINGLE_ENDED_0         (0x40)
#define  VUSB_CTRL_JSTATE                 (0x80)

/* VUSB Control Register Masks */
#define VUSB_CTL_USB_EN                   (1 << 0)
#define VUSB_CTL_ODD_RST                  (1 << 1)
#define VUSB_CTL_TXD_SUSPEND              (1 << 5) /* overload bit 5 */

/* VUSB Endpoint Control Register Mask */
#define VUSB_EP_CTRL_STALL                (0x2)
#define VUSB_INT_ENABLE_RESET             (0x01)

/* Token Register Masks */
#define  VUSB_TOKEN_ENDPT                 (0x0F)
#define  VUSB_TOKEN_PID                   (0xF0)
#define  VUSB_TOKEN_OUT                   (0x10)
#define  VUSB_TOKEN_IN                    (0x90)
#define  VUSB_TOKEN_SETUP                 (0xD0)

/* SOF Threshold Register Masks */
#define  VUSB_SOF_THLD_CNT0               (0x01)
#define  VUSB_SOF_THLD_CNT1               (0x02)
#define  VUSB_SOF_THLD_CNT2               (0x04)
#define  VUSB_SOF_THLD_CNT3               (0x08)
#define  VUSB_SOF_THLD_CNT4               (0x10)
#define  VUSB_SOF_THLD_CNT5               (0x20)
#define  VUSB_SOF_THLD_CNT6               (0x40)
#define  VUSB_SOF_THLD_CNT7               (0x80)

#define  VUSB_ADDR_LS_EN                  (0x80)

/* Status Register Bit Masks */
#define  VUSB_STAT_DIRECTION_BIT          (0x03)

/* Endpoint Control Register Masks */
#define  VUSB_ENDPT_CTL_EP_CTL_DIS        (0x10)
#define  VUSB_ENDPT_CTL_RETRY_DIS         (0x40)
#define  VUSB_ENDPT_CTL_HOST_WO_HUB       (0x80)

/* Buffer Descriptor Bit Masks */
#define  VUSB_BD_PID_MASKS                (0x3C)
#define  VUSB_BD_INVALID_PID1             (0x18)
#define  VUSB_BD_NAK_PID                  (0x28)
#define  VUSB_BD_PID_OWN                  (0x80)
#define  VUSB_BD_PID_DATA01               (0x40)
#define  VUSB_BD_DTS_ENABLE               (0x08)
#define  VUSB_BD_STALL_PID                (0x04)

/* Define the bits within the endpoint control register */
#define VUSB_ENDPT_HSHK_BIT               (0x01)
#define VUSB_ENDPT_STALL_BIT              (0x02)
#define VUSB_ENDPT_TX_EN_BIT              (0x04)
#define VUSB_ENDPT_RX_EN_BIT              (0x08)

#define VUSB_ENDPT_DISABLE                (0x00)
#define VUSB_ENDPT_CONTROL      (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_TX_EN_BIT | \
   VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_BULK_RX      (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_RX_EN_BIT | \
   VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_BULK_TX      (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_TX_EN_BIT | \
   VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_BULK_BIDIR   (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_TX_EN_BIT | \
   VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_ISO_RX       (VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_CTL_EP_CTL_DIS | \
   VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_ISO_TX       (VUSB_ENDPT_TX_EN_BIT | VUSB_ENDPT_CTL_EP_CTL_DIS | \
   VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_ISO_BIDIR    (VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_TX_EN_BIT \
   | VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)

#define  VUSB_ENDPT_INT_RX                (0x49)
#define  VUSB_ENDPT_INT_TX                (0x45)
#define  VUSB_ENDPT_INT_BIDIR             (0x4d)   

#define  VUSB_ENDPT_HOST_RETRY_DIS        (0x40)
#define  VUSB_ENDPT_HOST_WO_HUB           (0x80)
   
/*
** BDT Structure Macros
*/

#define VUSB_COPY_OWN_DATA_PID(BDT_to, BDT_from) \
   { \
      (BDT_to)->REGISTER.BITMAP.DATA01 = (BDT_from)->REGISTER.BITMAP.DATA01; \
      (BDT_to)->REGISTER.BITMAP.PID  = (BDT_from)->REGISTER.BITMAP.PID;  \
      (BDT_to)->REGISTER.BITMAP.OWNS = (BDT_from)->REGISTER.BITMAP.OWNS; \
   }
#define VUSB_SET_ADDRESS(pBDT, a)  ((pBDT)->ADDRESS = (a))

#define VUSB_CLEAR_CURRENT_BDT(pBDT,pxd) \
   { \
      (pBDT)->REGISTER.BDTCTL= 0; \
      VUSB_SET_BC((pBDT), 0); \
      VUSB_SET_ADDRESS((pBDT), 0); \
      pxd->PACKETPENDING--; \
   }
   
#define VUSB_CLEAR_OTHER_BDT(pBDT,pxd) \
   { \
      if ((VUSB_TOGGLE_BDT(pBDT))->REGISTER.BITMAP.OWNS) { \
         pxd->NEXTODDEVEN = VUSB_TOGGLE_BIT(pxd->NEXTODDEVEN); \
         pxd->NEXTDATA01 = VUSB_TOGGLE_BIT(pxd->NEXTDATA01); \
         pxd->PACKETPENDING--; \
      } /* Endif */ \
      (VUSB_TOGGLE_BDT(pBDT))->REGISTER.BDTCTL = 0; \
      VUSB_SET_BC(VUSB_TOGGLE_BDT(pBDT), 0); \
      VUSB_SET_ADDRESS(VUSB_TOGGLE_BDT(pBDT), 0); \
   }

typedef  uint_32  USB_REGISTER, _PTR_ USB_REGISTER_PTR;

typedef union bdt_reg {
   /*
   ** The BDT register is layed out on ARC as follows:
   ** Bits 0-1: Zero
   ** Bits 2-5: [IN] PID of token sent by host (PID)
   ** Bit 2: [OUT] BDT Stall (BDT-STALL)
   ** Bit 3: [OUT] Data Toggle Synch (DTS)
   ** Bit 4: [OUT] Disable DMA address increment (NINC)
   ** Bit 5: [OUT] Disables the VUSB from disowning the BDT and writing the PID
   **    (KEEP)
   ** Bit 6: DATA0/1 select
   ** Bit 7: OWNS==1 if the VUSB owns the BDT
   */
   struct {
      uint_16  :2,
               PID:4,
               DATA01:1,
               OWNS:1,
               :8;
   } BITMAP;
   uint_16     BDTCTL;
} BDT_REG, _PTR_ BDT_REG_PTR;

typedef struct bdt_struct {
   BDT_REG     REGISTER;
   uint_16     BC;
   uint_8_ptr  ADDRESS;
} BDT_STRUCT, _PTR_ BDT_STRUCT_PTR;

/* Multipurpose (MP) structure */
typedef union
{
   uint_32 W;
   struct {uint_16 L; uint_16 H;} B;
   uchar_ptr PB;
   struct BD _PTR_ BDT_PTR;
} MP_STRUCT, _PTR_ MP_STRUCT_PTR;

typedef union
{
   uint_16  W;
   struct {uint_8 L; uint_8 H;} B;
   uchar    PB[2];
} MP_STRUCT16, _PTR_ MP_STRUCT16_PTR;

/* VUSB Buffer Descriptor Format */
typedef struct BD
{
   uint_16     PID;   /* 7:own 6:data0/1 5-2:pid 1-0:bch bits */
   uint_16     BC;    /* Byte Count Low bits */
   MP_STRUCT   ADDR;  /* ZERO:2, ODD:1, EP:4, BDT_PAGE_REG: 8 */
} HOST_BDT_STRUCT, _PTR_ HOST_BDT_STRUCT_PTR;

#define VUSB_BDT_OWNS_BIT         (1 << 7)
#define VUSB_BDT_DATA01_BIT       (1 << 6)
#define VUSB_BDT_KEEP_BIT         (1 << 5)
#define VUSB_BDT_NINC_BIT         (1 << 4)
#define VUSB_BDT_DTS_BIT          (1 << 3)
#define VUSB_BDT_STALL_BIT        (1 << 2)
#define VUSB_BDT_DEQUEUED         (~VUSB_BDT_OWNS_BIT)

#define VUSB_GET_BC(pBdt)         ((uint_16)((pBdt)->BC))
#define VUSB_SET_BC(pBdt,bytes)   ((pBdt)->BC = (bytes))
#define VUSB_TOGGLE_BDT(pBdt)     ((BDT_STRUCT_PTR)(((uint_32)(pBdt)) ^ 0x08))

/* Macro for aligning the BDT page head to the appropriate byte boundary */
#define USB_BDT_ALIGN(n)      ((n) + (-(n) & 511))

#define USB_SET_BDT_PAGE(devptr, bdtpage) \
   { \
      (devptr)->USB->BDTPAGE1 = (((uint_32)(bdtpage)) >> 8) & 0xFF; \
      (devptr)->USB->BDTPAGE2 = (((uint_32)(bdtpage)) >> 16) & 0xFF; \
      (devptr)->USB->BDTPAGE3 = (((uint_32)(bdtpage)) >> 24) & 0xFF; \
   }

#define VUSB_TOGGLE_BIT(x)        ((x) ^ 1)
   
/* The ARC is little-endian, just like USB */
#define USB_uint_16_low(x)          ((x) & 0xFF)
#define USB_uint_16_high(x)         (((x) >> 8) & 0xFF)

#define  PIPE_RESERVED_FOR_ALIGNMENT         (2)
#define  XD_RESERVED_FOR_ALIGNMENT           (18)

#define  VUSB_ARC_BDT_OUT_BIT                (0x10)
#define  VUSB_ARC_BDT_IN_BIT                 (0x00)
#define  VUSB_ARC_BDT_ODD_EVEN_BIT           (0x08)

#define  VUSB_GET_STATUS(BDT_ptr)            (BDT_ptr->PID & VUSB_BD_PID_MASKS)
#define  VUSB_GET_BYTE_COUNT(BDT_ptr)        (BDT_ptr->BC)
#define  VUSB_ENDPT_REG_OFFSET               (0x40)

/* VUSB Register Structure */   
typedef volatile struct usb_struct {
   USB_REGISTER   INTSTATUS;
   USB_REGISTER   INTENABLE;
   USB_REGISTER   ERRORSTATUS;
   USB_REGISTER   ERRORENABLE;
   USB_REGISTER   STATUS;
   USB_REGISTER   CONTROL;
   USB_REGISTER   ADDRESS;
   USB_REGISTER   BDTPAGE1;
   USB_REGISTER   FRAMENUMLO;
   USB_REGISTER   FRAMENUMHI;
   USB_REGISTER   TOKEN;
   USB_REGISTER   SOFTHRESHOLDLO;
   USB_REGISTER   BDTPAGE2;
   USB_REGISTER   BDTPAGE3;
   USB_REGISTER   SOFTHRESHOLDHI;
   USB_REGISTER   RESERVED;
} USB_STRUCT, _PTR_ USB_STRUCT_PTR;

/*
** The USB STATUS register contains:
** Bits 7-4:   Endpoint
** Bit 3:      Tx(1)/Rx(0)
** Bit 2:      Odd(1)/Even(0)
** Bits 1-0:   Zero
*/
#define USB_REGISTER_STATUS_ENDPOINT(usbptr) (((usbptr)->STATUS >> 4) & 0x0F)
#define USB_REGISTER_STATUS_TXRX(usbptr)     (((usbptr)->STATUS >> 3) & 0x01)
#define USB_REGISTER_STATUS_ODDEVEN(usbptr)  (((usbptr)->STATUS >> 2) & 0x01)

#define TA_WAIT_BCON_TMR_FOR_EVER

/* Enable this for debug */
/* #define OTG_LOG_STATE */           

/*
**  A-DEVICE timing  constants
*/
/* Wait for VBUS Rise  */
#define TA_WAIT_VRISE 		(100) 	/* a_wait_vrise 100 ms, section: 6.6.5.1 */

/* Wait for B-Connect */
#define TA_WAIT_BCON  		(200) 	/* a_wait_bcon 200 ms, section: 6.6.5.2 */

/* A-Idle to B-Disconnect */
#define TA_AIDL_BDIS  		(300) 	/* a_suspend 150 ms, section: 6.6.5.3 */

/*
**  B-DEVICE timing constants.
*/

/* SE0 Time Before SRP */
#define TB_SE0_SRP 			(3) 		/* b_idle 2 ms 5.3.2 */

/* Data-Line Pulse Time*/
#define TB_DATA_PLS  		(7)      /* b_srp_init 5 to 10 ms, section: 5.3.3 */

#define TB_DATA_PLS_MIN		(5) 		/* b_srp_init 5 to 10 ms, section: 5.3.3 */

/* SRP Initiate Time  */
#define TB_SRP_INIT  		(100) 	/* b_srp_init 100 ms, section: 5.3.8 */

/* SRP Fail Time  */
#define TB_SRP_FAIL  		(20000) 	/* b_srp_init 5 to 30 sec,section: 6.8.2.2*/

/* A-SE0 to B-Reset  */
#define TB_ASE0_BRST  		(4) 		/* b_wait_acon 3.125, section: 6.8.2.4 */

#define TB_BUS_RESUME		(10)

/* Timer Macros */
#define TB_SRP_FAIL_TMR_ON(s,t)    		((s)->TB_SRP_FAIL_TMR = t)
#define TB_SRP_FAIL_TMR_OFF(s)     		((s)->TB_SRP_FAIL_TMR = -1)
#define TB_SRP_FAIL_TMR_EXPIRED(s)  	((s)->TB_SRP_FAIL_TMR ==  0)

#define TB_SRP_INIT_TMR_ON(s,t)   		((s)->TB_SRP_INIT_TMR = t)
#define TB_SRP_INIT_TMR_OFF(s)    		((s)->TB_SRP_INIT_TMR = -1)
#define TB_SRP_INIT_TMR_EXPIRED(s)    	((s)->TB_SRP_INIT_TMR == 0)

#define TB_DATA_PLS_TMR_ON(s,t) 			((s)->TB_DATA_PLS_TMR = t)
#define TB_DATA_PLS_TMR_OFF(s) 			((s)->TB_DATA_PLS_TMR = -1)
#define TB_DATA_PLS_TMR_EXPIRED(s) 		((s)->TB_DATA_PLS_TMR == 0)

#define TB_ASE0_BRST_TMR_ON(s,t)  		((s)->TB_ASE0_BRST_TMR = t)
#define TB_ASE0_BRST_TMR_OFF(s)    		((s)->TB_ASE0_BRST_TMR = -1)
#define TB_ASE0_BRST_TMR_EXPIRED(s) 	((s)->TB_ASE0_BRST_TMR == 0)

#define TA_WAIT_VRISE_TMR_ON(s,t)  		((s)->TA_WAIT_VRISE_TMR = t)
#define TA_WAIT_VRISE_TMR_OFF(s)    	((s)->TA_WAIT_VRISE_TMR = -1)
#define TA_WAIT_VRISE_TMR_EXPIRED(s) 	((s)->TA_WAIT_VRISE_TMR == 0)

#define TA_WAIT_BCON_TMR_ON(s,t)  		((s)->TA_WAIT_BCON_TMR = t)
#define TA_WAIT_BCON_TMR_OFF(s)    		((s)->TA_WAIT_BCON_TMR = -1)
#define TA_WAIT_BCON_TMR_EXPIRED(s) 	((s)->TA_WAIT_BCON_TMR == 0)

#define TA_AIDL_BDIS_TMR_ON(s,t)  		((s)->TA_AIDL_BDIS_TMR = t)
#define TA_AIDL_BDIS_TMR_OFF(s)    		((s)->TA_AIDL_BDIS_TMR = -1)
#define TA_AIDL_BDIS_TMR_EXPIRED(s) 	((s)->TA_AIDL_BDIS_TMR == 0)

#define TB_SE0_SRP_TMR_ON(s,t)  			((s)->TB_SE0_SRP_TMR = t)
#define TB_SE0_SRP_TMR_OFF(s)    		((s)->TB_SE0_SRP_TMR = -1)
#define CHECK_TB_SE0_SRP_TMR_OFF(s) 	((s)->TB_SE0_SRP_TMR == -1)
#define TB_SE0_SRP_TMR_EXPIRED(s) 		((s)->TB_SE0_SRP_TMR == 0)

#define A_SRP_TMR_ON(s,t)  				((s)->A_SRP_TMR = t)
#define A_SRP_TMR_OFF(s)    				((s)->A_SRP_TMR = -1)
#define A_SRP_TMR_EXPIRED(s) 				((s)->A_SRP_TMR == 0)

typedef struct otg_state_machine_struct {
   uint_8               STATE;
   boolean           	A_BUS_DROP;
   boolean           	A_BUS_REQ;
   boolean           	B_BUS_REQ;
   boolean              HOST_UP;
	boolean              DEVICE_UP;
   boolean           	A_SRP_DET;
   int_32               A_SRP_TMR;
	boolean 					A_DATA_PULSE_DET;
   int_32				   TB_SE0_SRP_TMR;
   boolean           	B_SE0_SRP;
	uint_32              OTG_INT_STATUS;
	boolean           	A_BUS_RESUME;
	boolean           	A_BUS_SUSPEND;
	boolean           	A_BUS_SUSPEND_REQ;
	boolean           	A_CONN;
	boolean           	B_BUS_RESUME;
	boolean           	B_BUS_SUSPEND;
	boolean           	B_CONN;
	boolean           	A_SET_B_HNP_EN;
	boolean           	B_SESS_REQ;
	boolean           	B_SRP_DONE;
	boolean           	B_HNP_ENABLE;
   boolean              JSTATE;
   uint_32              JSTATE_COUNT;
	/* A device specific timers */
	int_32				   TA_WAIT_VRISE_TMR;
	int_32				   TA_WAIT_BCON_TMR;
	int_32				   TA_AIDL_BDIS_TMR;
	/* B device specific timers */
	int_32				   TB_DATA_PLS_TMR;
	int_32				   TB_SRP_INIT_TMR;
	int_32				   TB_SRP_FAIL_TMR;
	int_32               TB_ASE0_BRST_TMR;
} OTG_STATE_MACHINE_STRUCT, _PTR_ OTG_STATE_MACHINE_STRUCT_PTR;

/* define the hardware specific registers */
#ifdef __VUSB32__
/* OTG Interrupt Status Register Bit Masks */
#define  OTG_INT_STATUS_A_VBUS                	(0x01)
#define  OTG_INT_STATUS_B_SESS                	(0x04)
#define  OTG_INT_STATUS_SESS_VLD              	(0x08)
#define  OTG_INT_STATUS_LINE_STATE_CHANGE       (0x20)
#define  OTG_INT_STATUS_1_MSEC                  (0x40)
#define  OTG_INT_STATUS_ID                   	(0x80)

/* OTG Interrupt Enable Register Bit Masks */
#define  OTG_INT_ENABLE_A_VBUS                	(0x01)
#define  OTG_INT_ENABLE_B_SESS                 	(0x04)
#define  OTG_INT_ENABLE_SESS_VLD              	(0x08)
#define  OTG_INT_ENABLE_1_MSEC                 	(0x40)
#define  OTG_INT_ENABLE_ID                     	(0x80)

/* OTG   Status Register Bit Masks */
#define  OTG_STAT_A_VBUS_VLD			(0x01)
#define  OTG_STAT_B_SESS_END               	(0x04)
#define  OTG_STAT_SESS_VLD                 	(0x08)
#define  OTG_STAT_LINE_STATE_CHANGE             (0x20)
#define  OTG_STAT_1_MSEC_VLD               	(0x40)
#define  OTG_STAT_ID_VLD                   	(0x80)

/* OTG  Control Register Bit Masks */
#define  OTG_CTL_VBUS_DSCHG             	(0x01)
#define  OTG_CTL_VBUS_CHG             	      	(0x02)
#define  OTG_CTL_OTG_ENABLE           	      	(0x04)
#define  OTG_CTL_VBUS_ON              	      	(0x08)
#define  OTG_CTL_DM_LOW             	        (0x10)
#define  OTG_CTL_DP_LOW             	        (0x20)
#define  OTG_CTL_DM_HIGH                    	(0x40)
#define  OTG_CTL_DP_HIGH                    	(0x80)

#define START_TIMER(x)   ((x)->OTG_INT_ENABLE |= OTG_INT_ENABLE_1_MSEC)
#define STOP_TIMER(x)  ((x)->OTG_INT_ENABLE &= ~OTG_INT_ENABLE_1_MSEC)

/*
** Interrupt status register signals
*/
#define ID_CHG(mask)          ((mask & OTG_INT_STATUS_ID))
#define SESS_VLD_CHG(mask)    ((mask & OTG_INT_STATUS_SESS_VLD))
#define A_VBUS_CHG(mask)      ((mask & OTG_INT_STATUS_A_VBUS))

/*
** status register signals
*/
#define SESS_VLD_FALSE(x)     (!((x)->OTG_STAT & OTG_STAT_SESS_VLD))
#define SESS_VLD(x)           (((x)->OTG_STAT & OTG_STAT_SESS_VLD))
#define B_SESS_END(x)         (((x)->OTG_STAT & OTG_STAT_B_SESS_END))

#define ID(x)                 (((x)->OTG_STAT & OTG_STAT_ID_VLD))
#define ID_FALSE(x)           (!((x)->OTG_STAT & OTG_STAT_ID_VLD))
#define A_VBUS_VLD(x)         (((x)->OTG_STAT & OTG_STAT_A_VBUS_VLD))
#define A_VBUS_VLD_FALSE(x)   (!((x)->OTG_STAT & OTG_STAT_A_VBUS_VLD))
#define STABLE_J_SE0_LINE_STATE(x) (((x)->OTG_STAT) & OTG_STAT_LINE_STATE_CHANGE)

/*
** OTG control register signals
*/
/* discharge the VBUS */
#define VBUS_DSCHG_ON(x)      ((x)->OTG_CTL |= OTG_CTL_VBUS_DSCHG)
#define VBUS_DSCHG_OFF(x)     ((x)->OTG_CTL &= ~OTG_CTL_VBUS_DSCHG)

/* TURN OFF VBUS charging. */
#define VBUS_CHG_ON(x)        ((x)->OTG_CTL |= OTG_CTL_VBUS_CHG)
#define VBUS_CHG_OFF(x)       ((x)->OTG_CTL &= ~OTG_CTL_VBUS_CHG)

#define VBUS_ON(x)            ((x)->OTG_CTL |= OTG_CTL_VBUS_ON)
#define VBUS_OFF(x)           ((x)->OTG_CTL &= ~OTG_CTL_VBUS_ON)

#define VBUS_DM_LOW_ON(x)     ((x)->OTG_CTL |= OTG_CTL_DM_LOW)
#define VBUS_DM_LOW_OFF(x)    ((x)->OTG_CTL &= ~OTG_CTL_DM_LOW)

#define VBUS_DP_LOW_ON(x)     ((x)->OTG_CTL |= OTG_CTL_DP_LOW)
#define VBUS_DP_LOW_OFF(x)    ((x)->OTG_CTL &= ~OTG_CTL_DP_LOW)

#define DM_HIGH_ON(x)         ((x)->OTG_CTL |= OTG_CTL_DM_HIGH )
#define DM_HIGH_OFF(x)        ((x)->OTG_CTL &= ~OTG_CTL_DM_HIGH )
#define DP_HIGH_ON(x)         ((x)->OTG_CTL |= OTG_CTL_DP_HIGH )
#define DP_HIGH_OFF(x)        ((x)->OTG_CTL &= ~OTG_CTL_DP_HIGH )

#define PULL_UP_PULL_DOWN_HOST_CTRL(x)	   (x)->OTG_CTL |= (OTG_CTL_DP_LOW | OTG_CTL_DM_LOW); \
                                          (x)->OTG_CTL &= ~(OTG_CTL_DP_HIGH | OTG_CTL_DM_HIGH); 

#define PULL_UP_PULL_DOWN_DEVICE_CTRL(x)  (x)->OTG_CTL |= (OTG_CTL_DP_HIGH); \
                                          (x)->OTG_CTL &= ~(OTG_CTL_DM_LOW | OTG_CTL_DM_HIGH | OTG_CTL_DP_LOW )

#define PULL_UP_PULL_DOWN_IDLE(x) (x)->OTG_CTL &= ~(OTG_CTL_DM_LOW | OTG_CTL_DM_HIGH | OTG_CTL_DP_LOW | OTG_CTL_DP_HIGH)

/* clear D + */
#define PULL_UP_PULL_DOWN_LOW_SPEED(x)    (x)->OTG_CTL &= ~OTG_CTL_DM_LOW; 

/* clear D - */
#define PULL_UP_PULL_DOWN_FULL_SPEED(x)   (x)->OTG_CTL &= ~OTG_CTL_DP_LOW;

/*
** USB core signals
*/

#define SE0(x)  ((x)->CONTROL & VUSB_CTRL_SINGLE_ENDED_0 )
#define JSTATE(x)  ((x)->CONTROL & VUSB_CTRL_JSTATE)
#define SPEED(x)  ((x)->ADDRESS & VUSB_ADDR_LS_EN)

typedef volatile struct otg_struct
{
   USB_REGISTER  OTG_INT_STAT;         /* OTG Interrupt Status Register */
   USB_REGISTER  OTG_INT_ENABLE;       /* OTG Interrupt Enable Register */
   USB_REGISTER  OTG_STAT;             /* OTG status Register */
   USB_REGISTER  OTG_CTL;              /* OTG Control Register */
} OTG_STRUCT, _PTR_ OTG_STRUCT_PTR;

#endif /* __VUSB32__ */

typedef struct usb_otg_state_structure {
   OTG_STRUCT_PTR                      OTG_REG_PTR;
   USB_STRUCT_PTR                      USB_REG_PTR;
	OTG_STATE_MACHINE_STRUCT      		STATE_STRUCT;
   void (_CODE_PTR_                    SERVICE)(pointer, uint_32);
	uint_8       		  						DEV_NUM;
   pointer             						CALLBACK_STRUCT_PTR;
#ifdef OTG_LOG_STATE
	uchar                               LOG_STATE[100];
	uchar                               LOG_STATE_COUNT;
#endif
} USB_OTG_STATE_STRUCT, _PTR_ USB_OTG_STATE_STRUCT_PTR;

/* Prototypes */

#ifdef __cplusplus
extern "C" {
#endif
#if 0
extern void _usb_otg_state_machine(_usb_otg_handle);
extern void _usb_otg_process_b_idle(_usb_otg_handle);
extern void _usb_otg_process_a_idle(_usb_otg_handle);
extern void _usb_otg_process_a_wait_vrise(_usb_otg_handle);
extern void _usb_otg_process_a_wait_vfall(_usb_otg_handle);
extern void _usb_otg_process_b_device_session_valid(_usb_otg_handle);
extern void _usb_otg_process_b_srp_init(_usb_otg_handle);
extern boolean _usb_otg_process_timers(_usb_otg_handle);
extern boolean _usb_otg_process_exceptions(_usb_otg_handle);
extern void  _usb_otg_reset_state_machine(_usb_otg_handle);
extern void _usb_host_bus_control(pointer, uint_8); 

#ifdef __VUSB32__
   extern void OTG_INTERRUPT_ROUTINE_KEYWORD _usb_otg_vusb11_isr(void);
   extern void HOST_INTERRUPT_ROUTINE_KEYWORD _usb_hci_vusb11_isr(void);
   extern void DEVICE_INTERRUPT_ROUTINE_KEYWORD _usb_dci_vusb11_isr(void);
   uint_8 _usb_otg_vusb11_init(_usb_otg_handle);
   extern void _usb_otg_vusb11_shutdown(_usb_otg_handle);
#endif /* __VUSB32__ */

#endif /* 0 */

#ifdef __cplusplus
}
#endif
#endif /* __arcusb_h__ */
