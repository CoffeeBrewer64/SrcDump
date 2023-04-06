/**
 * @file cgbCpu.cpp
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - CPU
 */
#include "cgbCPU.h"
#include "cgbCPU_DAA.h"
#include "cgbDMA.h"
#include "cgbMemory.h"
#include "cgbRegister.h"
#include "cgbGraphic.h"
#include "cgbSound.h"

/** @name Macro Define */
//@{
#define		PC					g_nCgbCpuRegPC
#define		SP					g_nCgbCpuRegSP
#define		AF					(*(u16*)(&g_nCgbCpuReg8[0]))
#define		BC					(*(u16*)(&g_nCgbCpuReg8[2]))
#define		DE					(*(u16*)(&g_nCgbCpuReg8[4]))
#define		HL					(*(u16*)(&g_nCgbCpuReg8[6]))
#define		F					g_nCgbCpuReg8[0]
#define		A					g_nCgbCpuReg8[1]
#define		C					g_nCgbCpuReg8[2]
#define		B					g_nCgbCpuReg8[3]
#define		E					g_nCgbCpuReg8[4]
#define		D					g_nCgbCpuReg8[5]
#define		L					g_nCgbCpuReg8[6]
#define		H					g_nCgbCpuReg8[7]
#define		C_FLAG				0x10
#define		H_FLAG				0x20
#define		N_FLAG				0x40
#define		Z_FLAG				0x80
#define		Z_FLAG_CHECK(v)		((v) ? 0 : Z_FLAG)
//#define		ZN_FLAG_CHECK(v)	((v) ? N_FLAG : (Z_FLAG|N_FLAG))
//#define		ZH_FLAG_CHECK(v)	((v) ? H_FLAG : (Z_FLAG|H_FLAG))
#define		H_FLAG_INC(v)		((v)&0x0F ? 0 : H_FLAG)
//#define		H_FLAG_DEC(v)		(((v)&0x0F)==0x0F ? H_FLAG : 0)
//#define		H_FLAG_INC(v)		(((v)&0x10) << 1)
#define		H_FLAG_DEC(v)		((((v)&0x0F)==0x0F) << 5)
#define		H_FLAG_CHECK(v)		(((A^v^g_nCgbCpuTemp16)&0x10) << 1)
#define		C_FLAG_CHECK		((g_nCgbCpuTemp16&0x0100) >> 4)
//@}

#ifdef TRL_PLATFORM_PC
u32	g_bCgbCPUDebug = 0;
FILE *g_fCPU;
#endif

/** @name Global Variable */
//@{
s32					g_nCgbCpuEventTicks;					///< Next Event Ticks
s32					g_nCgbCpuTicks;							///< CPU Run Ticks
u8					g_nCgbCpuReg8[8];						///< CPU 8 Bit Registers
u16					g_nCgbCpuRegPC;							///< CPU PC Register
u16					g_nCgbCpuRegSP;							///< CPU SP Register
u8					g_nCgbCpuTemp8;							///< CPU 8 Bit Temp Value
u16					g_nCgbCpuTemp16;						///< CPU 16 Bit Temp Value
u32					g_nCgbCpuIME;							///< Interrupt Master Enable Flag (W)
u32					g_nCgbCpuState;							///< CPU State
u8*					g_pCgbCpuPC;							///< CPU PC Pointer
trlSEmuShellResume	g_sCgbCpuSaveData[CGB_CPU_SAVEDATA];	///< CPU Save Data
extern u32			g_nCgbROMBank;
//@}

/** @brief Initialize CPU */
void cgbCpuInit()
{
	// Save Data
	g_sCgbCpuSaveData[0].SetData(&g_nCgbCpuTicks, 4, 1, 0);
	g_sCgbCpuSaveData[1].SetData(g_nCgbCpuReg8, 8, 1, 0);
	g_sCgbCpuSaveData[2].SetData(&g_nCgbCpuRegPC, 2, 1, 0);
	g_sCgbCpuSaveData[3].SetData(&g_nCgbCpuRegSP, 2, 1, 0);
	g_sCgbCpuSaveData[4].SetData(&g_nCgbCpuIME, 4, 1, 0);
	g_sCgbCpuSaveData[5].SetData(&g_nCgbCpuState, 4, 1, 0);

	cgbCpuReset();
}

/** @brief Reset CPU */
void cgbCpuReset()
{
	PC = 0x0100;
	SP = 0xFFFE;
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		AF = 0x1180;
		BC = 0x0000;
		DE = 0xFF56;
		HL = 0x000D;
	}
	else
	{
		AF = 0x01B0;
		BC = 0x0013;
		DE = 0x00D8;
		HL = 0x014D;
	}

	g_nCgbCpuTicks = 0;
	g_nCgbCpuIME = 0;
	g_nCgbCpuState = 0;

	g_nCgbCpuEventTicks = 0;
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
}

/** @brief Resume CPU */
void cgbCpuResume()
{
	g_nCgbCpuEventTicks = 0;
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
}

/** @brief Switch CPU Speed */
void cgbCpuSpeed()
{
	if(!g_pCgbRegKEY1->rSpeed)
		return;
	g_pCgbRegKEY1->rSpeed = 0;
	if(g_pCgbRegKEY1->rCurSpeed)
	{
		g_pCgbRegKEY1->rCurSpeed = 0;
		g_nCgbGrpTicks >>= 1;
		g_nCgbGrpTick0 >>= 1;
		g_nCgbGrpTick1 >>= 1;
		g_nCgbGrpTick2 >>= 1;
		g_nCgbGrpTick3 >>= 1;
		g_nCgbSndTicks >>= 1;
		g_nCgbSndTick0 >>= 1;
		g_nCgbDmaTick0 >>= 1;
	}
	else
	{
		g_pCgbRegKEY1->rCurSpeed = 1;
		g_nCgbGrpTicks <<= 1;
		g_nCgbGrpTick0 <<= 1;
		g_nCgbGrpTick1 <<= 1;
		g_nCgbGrpTick2 <<= 1;
		g_nCgbGrpTick3 <<= 1;
		g_nCgbSndTicks <<= 1;
		g_nCgbSndTick0 <<= 1;
		g_nCgbDmaTick0 <<= 1;
	}
}

/** @brief Push Stack */
inline void	cgbCpuPushStack(u16 nReg)
{
	SP -= 2;
	trlTracePushStack(nReg);
	cgbMemWrite16(SP, nReg);
}

/** @brief Pop Stack */
inline void cgbCpuPopStack(u16 &nReg)
{
	nReg = cgbMemRead16(SP);
	SP += 2;
}

/** @brief Run CPU */
void cgbCpuRun()
{
#ifdef TRL_PLATFORM_PC
	//if(g_pCgbEmuBuf->nDebugKey & 1)
	//{
	//	if(*g_pCgbRegLY == 0)
	//	{
	//		if(g_bCgbCPUDebug == 0)
	//		{
	//			fopen_s(&g_fCPU, "cpu_log_cgb.log", "wb");
	//			g_bCgbCPUDebug = 1;
	//		}
	//	}
	//	else if(*g_pCgbRegLY == 153)
	//	{
	//		if(g_bCgbCPUDebug == 1)
	//		{
	//			fclose(g_fCPU);
	//			g_bCgbCPUDebug = 2;
	//		}
	//	}
	//}

	if(g_pCgbEmuBuf->nDebugKey & 1)
	{
		if(*g_pCgbRegLY == 0)
		{
			if(g_bCgbCPUDebug == 0)
			{
				fopen_s(&g_fCPU, "cpu_log_cgb.log", "wb");
				g_bCgbCPUDebug = 1;
			}
		}
	}
	if(g_pCgbEmuBuf->nDebugKey & 2)
	{
		if(*g_pCgbRegLY == 0)
		{
			if(g_bCgbCPUDebug == 1)
			{
				fclose(g_fCPU);
				g_bCgbCPUDebug = 2;
			}
		}
	}
#endif

	// Interrupt
	if(g_nCgbCpuIME)
	{
		u8 nRegInt = g_pCgbREG[0x0F] & g_pCgbREG[0xFF];
		if(nRegInt)
		{
			if(nRegInt & 0x01)
			{
				g_pCgbRegIF->rVBlank = 0;
				cgbCpuPushStack(PC);
				PC = 0x0040;
				g_pCgbCpuPC = &g_pCgbROM[0x0040];
			}
			else if(nRegInt & 0x02)
			{
				g_pCgbRegIF->rLCD = 0;
				cgbCpuPushStack(PC);
				PC = 0x0048;
				g_pCgbCpuPC = &g_pCgbROM[0x0048];
			}
			else if(nRegInt & 0x04)
			{
				g_pCgbRegIF->rTimer = 0;
				cgbCpuPushStack(PC);
				PC = 0x0050;
				g_pCgbCpuPC = &g_pCgbROM[0x0050];
			}
			else if(nRegInt & 0x08)
			{
				g_pCgbRegIF->rSerial = 0;
				cgbCpuPushStack(PC);
				PC = 0x0058;
				g_pCgbCpuPC = &g_pCgbROM[0x0058];
			}
			else if(nRegInt & 0x10)
			{
				g_pCgbRegIF->rJoypad = 0;
				cgbCpuPushStack(PC);
				PC = 0x0060;
				g_pCgbCpuPC = &g_pCgbROM[0x0060];
			}
			g_nCgbCpuState &= ~CGB_CPU_HALT;
			g_nCgbCpuIME = 0;
		}
	}

	// Opcode
	if(g_nCgbCpuState)
	{
		g_nCgbCpuTicks = g_nCgbCpuEventTicks;
		return;
	}
	g_nCgbCpuTicks = 0;
	do{
#ifdef TRL_PLATFORM_PC
		if(g_bCgbCPUDebug == 1)
		{
			if(g_pCgbCpuPC == NULL)
				fclose(g_fCPU);
			fprintf(g_fCPU, "PC:%02d-%04X=%02X %08X  LY:%03d AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", (PC<0x4000)?0:g_nCgbROMBank, PC, *g_pCgbCpuPC,(PC<0x4000)?PC:(g_nCgbROMBank-1)*0x4000+PC, *g_pCgbRegLY, AF, BC, DE, HL, SP);
		}
		trlTraceCPURun();
#endif
#if TRL_PROFILER
		g_pCgbEmuBuf->nProfiler3++;
#endif
		#include "cgbCPUOpcode.h"
	}while(g_nCgbCpuTicks<g_nCgbCpuEventTicks);
}
