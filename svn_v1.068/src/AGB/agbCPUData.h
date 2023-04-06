/**
 * @file agbCPUData.h
 * @author zhfang
 * @date 2009.12.15
 * @brief AGB Emulate For CTR - CPU Data...register, clock and so on
 */
#pragma once
#include "agbGlobal.h"

#define THUMB_FIRST_PREFETCH\
	g_nAgbCPUReg[15] &= 0xFFFFFFFE;\
	g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]);\
	g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2);\
	g_nAgbCPUReg[15] += 2;

#define ARM_FIRST_PREFETCH\
	g_nAgbCPUReg[15] &= 0xFFFFFFFC;\
	g_nAgbInsta = agbMemRead32(g_nAgbCPUReg[15]);\
	g_nAgbInstb = agbMemRead32(g_nAgbCPUReg[15] + 4);\
	g_nAgbCPUReg[15] += 4;


  /** @name Global Variable */
//@{

typedef enum
{
	AGB_TITLE_SIMPLE_DOPHI = 0,
	AGB_TITLE_SIMPLE_YOSHI,
	AGB_TITLE_MARIOA_AMAJ,
	AGB_TITLE_CHECK323,
	AGB_TITLE_UNKOWN
}AGBGAMETITLE;


extern u32 g_nAgbGameTitle;

extern u32 g_nAgbCPUClock;

//instruction pretech
extern u32 g_nAgbInst; 		///< current instruction
extern u32 g_nAgbInsta;		///< instruction prefetch 1
extern u32 g_nAgbInstb;		///< instruction prefetch 1


//instruction decode
extern u32 g_nAgbCPURd;
extern u32 g_nAgbCPURm;
extern u32 g_nAgbCPURs;
extern u32 g_nAgbCPURn;

extern u32 g_nAgbCPUImm3;
extern u32 g_nAgbCPUImm5;
extern u32 g_nAgbCPUImm8;


extern u32 g_nAgbCPUBeInterrupt;

//register

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15
#define R16 16
#define R17 17

#define R13_USER 18
#define R14_USER 19
#define R8_FIQ 20
#define R9_FIQ 21
#define R10_FIQ 22
#define R11_FIQ 23
#define R12_FIQ 24
#define R13_FIQ 25
#define R14_FIQ 26
#define SPSR_FIQ 27
#define R13_SVC 28
#define R14_SVC 29
#define SPSR_SVC 30
#define R13_ABT 31
#define R14_ABT 32
#define SPSR_ABT 33
#define R13_IRQ 34
#define R14_IRQ 35
#define SPSR_IRQ 36
#define R13_UND 37
#define R14_UND 38
#define SPSR_UND 39


#define REG_NFLAG 40
#define REG_ZFLAG 41
#define REG_CFLAG 42
#define REG_VFLAG 43

#define REG_CPUVALUE 44
#define REG_CPUOFFSET 45
#define REG_CPUTEMP 46
#define REG_CPUSHIFT 47
#define REG_CPUCOUT 48
#define REG_CPUADDRESS 49

#define REG_CPUMODE 50

#define REG_NUM 51

extern u32 g_nAgbCPUReg[REG_NUM];	///<  reg0~reg15,  cpsr(16), spsr(17)   and   reg[13] == SP  reg[14] == LR




#define CPU_MODE_USER 0x10
#define CPU_MODE_FIQ 0x11
#define CPU_MODE_IRQ 0x12
#define CPU_MODE_SVC 0x13
#define CPU_MODE_ABT 0x17
#define CPU_MODE_UND 0x1B
#define CPU_MODE_SYS 0x1F

//cpsr 
extern u32 g_bAgbIrqDisable, g_bFiqDisable;
extern u32  g_nAgbThumbState;

extern u8 g_nAgbCpuBitsSet[256];
