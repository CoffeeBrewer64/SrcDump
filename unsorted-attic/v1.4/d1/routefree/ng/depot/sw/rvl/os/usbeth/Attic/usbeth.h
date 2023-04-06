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

#ifndef __USBETH_H__
#define __USBETH_H__

#define AX88772_VENDOR_ID 0b95
#define AX88772_PRODUCT_ID 7720
#define AX88772_LANGUAGE_ENGLISH   0x904

typedef struct
{
    u32   rx_packets;     /* total packets received   */
    u32   tx_packets;     /* total packets transmitted    */
    u32   rx_bytes;       /* total bytes received     */
    u32   tx_bytes;       /* total bytes transmitted  */
    u32   rx_errors;      /* bad packets received     */
    u32   tx_errors;      /* packet transmit problems */
    u32   rx_dropped;     /* no space in buffers    */
    u32   tx_dropped;     /* no space available */
    u32   multicast;      /* multicast packets received   */
    u32   collisions;

    u32   rx_missed_errors;   /* receiver missed packet   */
	u32   rx_length_errors;
    u32   rx_frame_errors;    /* recv'd frame alignment error */
} AX88772_Stats;

typedef struct 
{
    u8 wordCount4Preload;				//0
    u8 reserved00;
    u16 flag;							//1
    u8 offsetHSDeviceDescriptor;		//2
    u8 lengthHSDeviceDescriptor;
    u8 offsetHSConfigDescriptor;		//3
    u8 lengthHSConfigDescriptor;
    u8 NodeId[6];						//4
    u8 languageIdlow;					//7
    u8 languageIdhi;
    u8 offsetMfgStr;
    u8 lengthMfgStr;
    u8 offsetProductStr;
    u8 lengthProductStr;
    u8 offsetSerialNo;
    u8 lengthSerialNo;
    u8 offsetCfgStr;
    u8 lengthCfgStr;
    u8 offsetIF0Str;
    u8 lengthIF0Str;
    u8 offsetIF1_0Str;
    u8 lengthIF1_0Str;
    u8 offsetIF1_1Str;
    u8 lengthIF1_1Str;
    u16 phyRegOffsetInterruptEndPoint;
    u16 maxPktSize;
    u8 primaryPhyType; // 7:5 type 4:0 id	//0x11 low byte
    u8 secondaryPhyType; // 7:5 type 4:0 id
    u8 pauseFrameLowWatermark;
    u8 pauseFrameHighWaterMark;
    u8 offsetFullSpeedDevDesc;
    u8 lengthFullSpeedDevDesc;
    u8 offsetFullSpeedConfDesc;
    u8 lengthFullSpeedConfDesc;
} AX88772_EEProm_type;

#define AX88772_REGISTER_CLEAR			0
#define AX88772_REGISTER_SET			1

// Flag (01) EEPROM p13
#define AX88772_FLAG_SP 	1		//self-power 1=self 0=bus
#define AX88772_FLAG_RWU 	4		//remote wakeup =1
#define AX88772_FLAG_DCK 	16		//1=disabled chirp k
#define AX88772_FLAG_SCPR 	32		//1= PRL+PRTE of sw reset reg control phy
									//0=PRTE control phy
#define AX88772_FLAG_RDCE 	64		//1=CRC dropped before forwarding on RX
#define AX88772_FLAG_TACE 	128		//1=append CRC on TX
#define AX88772_FLAG_CEM 	256		//capture effective mode
#define AX88772_FLAG_TDPE 	512		//test debug port enable

// Serial Management Status reg (0x09, read-only)
#define AX88772_SERIAL_HOSTEN   0x01            //1=sw has access to PHY i/f, 0=hw

// Medium status/Mode reg (1a status/1b mode write)
#define AX88772_MEDIUM_FD 	0x0002	//1=full 0=half(full default)
#define AX88772_MEDIUM_RFC	0x0010	//1=enable rx pause frame, 0=no (1 default)
#define AX88772_MEDIUM_TFC	0x0020	//1=enable tx pause frame, 0=no (1 default)
#define AX88772_MEDIUM_PF   0x0080  //1=pause frame id'd on length/type
									//0=length/type+DA dest Addr(0 default)
#define AX88772_MEDIUM_RE   0x0100  //1=rx enable (0 default)
#define AX88772_MEDIUM_PS   0x0200  //1=port speed 100(default) 0 = 10Mbps
#define AX88772_MEDIUM_SBP  0x0800  //1 and TFC=1 continous back pressure
									//if rx buffer full in Half Duplex mode
									//0 only intermittent when rx full(default)

#define AX88772_MEDIUM_SM  	0x1000  //1 = super MAC support 
									// (shorten backoff time on retry) 0 default

// Monitor Mode Register 0x1d
#define AX88772_MONITOR_MOM     0x1     //1 = enable (all pkts checked on DA & grep CRC), 0 = disable
#define AX88772_MONITOR_RWLU    0x2     //1 = remote wakeup trigger by ethernet link-up
#define AX88772_MONITOR_RWMP    0x4     //1 = remote wakeup trigger by magic packet

// Software reset register 0x20 (default = 0x4c 01001100)
#define AX88772_RESET_REG_RR 		0x1 //clr frame length error bulk in(0)
#define AX88772_RESET_REG_RT 		0x2 //clr frame length error bulk out(0)
#define AX88772_RESET_REG_PRTE		0x4 //ext phy reset pin tri-state enab(1)
#define AX88772_RESET_REG_PRL		0x8 // ext phy reset pin lvl (1)
#define AX88772_RESET_REG_BZ		0x10// force bulk in to ret 0 len pkt(0) 
#define AX88772_RESET_REG_IPRL		0x20// int phy reset (0) make 1
#define AX88772_RESET_REG_IPPD		0x40// int phy power down (1) make 0

// PHY registers
#define AX88772_PHY_REG_BMCR		0	//basic mode control reg
#define AX88772_PHY_REG_BMSR		1	//basic mode status reg
#define AX88772_PHY_REG_PHYIDR1		2	//phy identifier reg 1
#define AX88772_PHY_REG_PHYIDR2		3	//phy identifier reg 2
#define AX88772_PHY_REG_ANAR		4	//Auto neg advertisment reg
#define AX88772_PHY_REG_ANLPAR		5	//auto neg link partner ability
#define AX88772_PHY_REG_ANER  		6	//auto neg expansion reg

// phy reg BMCR reg 0 (default 001100010xxxxxxx but better to read first)
#define AX88772_PHY_REG_BMCR_COLL 		0x0080//collision test 1= collision(0)
#define AX88772_PHY_REG_BMCR_DUPLEX		0x0100//1=full 0=half(1)
#define AX88772_PHY_REG_BMCR_RST_AN		0x0200//1=restart auto neg(0)
#define AX88772_PHY_REG_BMCR_ISOLATE	0x0400//1=isolate 0=normal(0)
#define AX88772_PHY_REG_BMCR_POWER_DN	0x0800//1=power down 0 = normal(0)
#define AX88772_PHY_REG_BMCR_AN_ENABLE	0x1000//1=auto neg enable(1)
#define AX88772_PHY_REG_BMCR_SPEED		0x2000//1=100,0=10(def1) if(AN_ENABLE=0)
#define AX88772_PHY_REG_BMCR_LOOPBACK	0x4000//1=loop 0 =normal
#define AX88772_PHY_REG_BMCR_RESET		0x8000//1=sw reset(self clear)0=normal

// phy reg BMSR reg 1 status reg
#define AX88772_PHY_REG_BMSR_EXT_CAP	0x0001//extended capability
#define AX88772_PHY_REG_BMSR_JABBER		0x0002//jabber detect =1
#define AX88772_PHY_REG_BMSR_LINK_STAT	0x0004//valid link=1
#define AX88772_PHY_REG_BMSR_AN_CAPABLE	0x0008//1=auto neg capable
#define AX88772_PHY_REG_BMSR_REM_FAULT	0x0010//remote fault=1
#define AX88772_PHY_REG_BMSR_AN_COMPLETE 0x020//1=auto neg complete
#define AX88772_PHY_REG_BMSR_MF_PREAMBLE 0x040//can deal with pre amble
#define AX88772_PHY_REG_BMSR_10_HALF	0x0800//1=able to do 10 1/2
#define AX88772_PHY_REG_BMSR_10_FULL	0x1000//1=able to do 10 full
#define AX88772_PHY_REG_BMSR_100_HALF 	0x2000//1=able to do 100 1/2
#define AX88772_PHY_REG_BMSR_100_FULL	0x4000//1=able to do 100 full
#define AX88772_PHY_REG_BMSR_100_T4		0x8000//0=not able to do T4

// phy reg ANAR reg 4 AN advert FIXIT add other bits 15,14,13,10
#define AX88772_PHY_REG_ANAR_10_HD		0x0020//1=10 1/2 supported
#define AX88772_PHY_REG_ANAR_10_FD		0x0040//1=10 full
#define AX88772_PHY_REG_ANAR_100_HD		0x0080//1=100 1/2 supported
#define AX88772_PHY_REG_ANAR_100_FD		0x0100//1=100 full supported

//phy reg 05 ANLPAR reg 5
#define AX88772_PHY_REG_ANALPAR_10_HD		0x0020//1=10 1/2 supported
#define AX88772_PHY_REG_ANALPAR_10_FD		0x0040//1=10 full
#define AX88772_PHY_REG_ANALPAR_100_HD		0x0080//1=100 1/2 supported
#define AX88772_PHY_REG_ANALPAR_100_FD		0x0100//1=100 full supported

//phy reg 6 ANER only 2 bits FIXIT add the others
#define AX88772_PHY_REG_ANER_LP_AN_AB		0x0001//partner capable of AN
#define AX88772_PHY_REG_ANER_AN_PAGE_RX		0x0002//we just ANed

// Rx Control Reg
#define AX88772_RX_CONTROL_REG_PRO			0x01	// Promiscous mode=1
#define AX88772_RX_CONTROL_REG_AMALL		0x02	// all mcast mode=1
#define AX88772_RX_CONTROL_REG_SEP			0x04	// save err pkt =1
#define AX88772_RX_CONTROL_REG_AB			0x08	// bcast mode=1
#define AX88772_RX_CONTROL_REG_AM			0x10	// mcast match DA=1
#define AX88772_RX_CONTROL_REG_AP			0x20	// 
#define AX88772_RX_CONTROL_REG_SO			0x80	// start op=1
#define AX88772_RX_CONTROL_REG_MFB_MASK	       	0x0300	// 
#define AX88772_RX_CONTROL_REG_MFB_4K	       	0x0100	// 

#ifndef TRUE
// Any non zero value is considered TRUE
#define TRUE                1
#endif  // TRUE

#ifndef FALSE
#define FALSE               0
#endif  // FALSE

#ifndef BOOL
typedef int                 BOOL;
#endif  // BOOL

#define USBETH_MFB_SIZE     2048

// clean up definitions
#define USBETH_STACK_SIZE       (32 * 1024)
#define USBETH_PRIORITY         60
#define USBETH_MSGQ_SIZE        64

#endif /* __USBETH_H__ */
