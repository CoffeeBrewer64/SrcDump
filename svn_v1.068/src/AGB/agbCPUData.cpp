/**
 * @file agbCPUData.cpp
 * @author zhfang
 * @date 2009.12.15
 * @brief AGB Emulate For CTR - CPU Data...register, clock and so on
 */

 /** @name Global Variable */
//@{
#include "..\trlHeader.h"
#include "agbCPUData.h"


u32 g_nAgbGameTitle = AGB_TITLE_UNKOWN;
u32 g_nAgbCPUClock = 0;

//instruction pretech
u32 g_nAgbInst; 		///< current instruction
u32 g_nAgbInsta;		///< instruction prefetch 1
u32 g_nAgbInstb;		///< instruction prefetch 1


//instruction decode
u32 g_nAgbCPURd;
u32 g_nAgbCPURm;
u32 g_nAgbCPURs;
u32 g_nAgbCPURn;

u32 g_nAgbCPUImm3;
u32 g_nAgbCPUImm5;
u32 g_nAgbCPUImm8;


u32 g_nAgbCPUBeInterrupt;

//register
u32 g_nAgbCPUReg[REG_NUM];	///<  reg0~reg15,  cpsr(16), spsr(17)   and   reg[13] == SP  reg[14] == LR
//u32 g_nAgbCPURegBank[22];

//cpsr 

u32 g_bAgbIrqDisable, g_bFiqDisable;
u32  g_nAgbThumbState;

#define bit4(m) m, m+1, m+1, m+2
#define bit16(m) bit4(m),bit4(m+1)	,bit4(m+1),bit4(m+2)

u8 g_nAgbCpuBitsSet[256] = 
{
	bit16(0),
	bit16(1),
	bit16(1),
	bit16(2),
	bit16(1),
	bit16(2),
	bit16(2),
	bit16(3),
	bit16(1),
	bit16(2),
	bit16(2),
	bit16(3),
	bit16(2),
	bit16(3),
	bit16(3),
	bit16(4)
};
//@}
