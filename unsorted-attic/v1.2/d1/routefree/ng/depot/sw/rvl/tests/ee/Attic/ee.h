/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */


#ifndef __EE_H__
#define __EE_H__


// Define GPIO address.
#define EE_GPIO_ENABLE 			(ACR_PROT_REGS_BASE+GPIIOPEN_OFFSET)
#define EE_GPIO_OUTOE			(ACR_PROT_REGS_BASE+GPIIOPOE_OFFSET)
#define EE_GPIO_OUT 			(ACR_PROT_REGS_BASE+GPIIOPOUT_OFFSET)
#define EE_GPIO_IN 			(ACR_PROT_REGS_BASE+GPIIOPIN_OFFSET)
#define EE_GPIO_INTERRUPT_ENABLE 	(ACR_PROT_REGS_BASE+GPIIOPINTEN_OFFSET)

// GPIO[13:11]
#define EE_CS_GPIO_10_BIT_POS	10
#define EE_CK_GPIO_11_BIT_POS	11
#define EE_DI_GPIO_12_BIT_POS	12
#define EE_DO_GPIO_13_BIT_POS	13

#define EE_CS_GPIO_10_MASK	(0x1 << EE_CS_GPIO_10_BIT_POS)
#define EE_CK_GPIO_11_MASK	(0x1 << EE_CK_GPIO_11_BIT_POS)
#define EE_DI_GPIO_12_MASK	(0x1 << EE_DI_GPIO_12_BIT_POS)
#define EE_DO_GPIO_13_MASK	(0x1 << EE_DO_GPIO_13_BIT_POS)
#define EE_GPIO_13_10_MASK	(EE_DO_GPIO_13_MASK | EE_DI_GPIO_12_MASK | EE_CK_GPIO_11_MASK | EE_CS_GPIO_10_MASK)

// Timing in terms of nanosecond.
#define tCDS		2
#define SYS_CLK_PERIOD	4
#define EE_CLK_LOW	500
#define EE_CLK_HIGH	500

// Master bit time period in terms of number of system clocks.
#define EE_BIT_TIME_HIGH	(EE_CLK_HIGH / SYS_CLK_PERIOD)

// Slave bit time period in terms of number of system clocks.
#define EE_BIT_TIME_LOW		(EE_CLK_LOW / SYS_CLK_PERIOD)

// EE status.
#define EE_OK	0x0
#define EE_ERR	0x1

// EE cmd string. Only support S-93C56B part. 128w x 16b
// 1 start bit + 2 op code + 8 addr bit where the 8th address bit is a 0.
#define EE_START_BIT (0x1 << 10)
#define EE_OP_00    (0x0 << 8)
#define EE_OP_01    (0x1 << 8)
#define EE_OP_10    (0x2 << 8)
#define EE_OP_11    (0x3 << 8)
#define EE_CMD_WRAL  0x40
#define EE_CMD_ERAL  0x80
#define EE_CMD_EWEN  0xC0
#define EE_CMD_EWDS  0x00

// EE functions

void	eeClkHigh(void);
void	eeClkLow(void);
void	eeCSHigh(void);
void	eeCSLow(void);
void	eeDataOut(u32);
void	eeBitTimeIdle(u32);
void	eeBitTimeWr(u32);
void	eeBitTimeRead(void);
u32	eeWrNbits(u32, u32);
u32	eeRdNbits(u32, u32 *);
u32	eeChkStatus();
u32	eeRdCmd(u32, u32 *);
u32	eeWrCmd(u32, u32);
u32	eeEraseCmd(u32);
u32	eeWralCmd(u32);
u32	eeEralCmd(void);
u32	eeWenCmd(void);
u32	eeWenCmd(void);
void	eeGPIOSetup(void);
u32	eeBasicTest(u32);

void	__setACRGPIOResetVals(void);
void	__restoreACRGPIORegs(void);

#endif /* __EE_H__ */
