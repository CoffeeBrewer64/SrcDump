/**
 * @file nesCpu.cpp
 * @author chentian, zhfang
 * @date 2010.06.25
 * @brief NES Emulate For CTR - CPU
 */
#include "nesCPU.h"
#include "nesGraphic.h"
#include "nesMemory.h"
#include "nesCard.h"

#if TRL_CPU_OPCODE_REG_FAST
#define TRL_CPU_OPCODE_REG_FAST_TICK 1
#define TRL_CPU_OPCODE_REG_FAST_REGP 1
#define TRL_CPU_OPCODE_REG_FAST_REGPC 1
#define TRL_CPU_OPCODE_REG_FAST_REGA 0
#define TRL_CPU_OPCODE_REG_FAST_OPCODE 0
#else
#define TRL_CPU_OPCODE_REG_FAST_TICK 0
#define TRL_CPU_OPCODE_REG_FAST_REGP 0
#define TRL_CPU_OPCODE_REG_FAST_REGPC 0
#define TRL_CPU_OPCODE_REG_FAST_REGA 0
#define TRL_CPU_OPCODE_REG_FAST_OPCODE 0
#endif

/** @name Macro Define */
//@{
#define NES_CPU_CFLAG		0x01
#define NES_CPU_ZFLAG		0x02
#define NES_CPU_IFLAG		0x04
#define NES_CPU_DFLAG		0x08
#define NES_CPU_BFLAG		0x10
#define NES_CPU_UFLAG		0x20
#define NES_CPU_VFLAG		0x40
#define NES_CPU_NFLAG		0x80

#define A_G					g_nNesCpuRegA
#define X					g_nNesCpuRegX
#define Y					g_nNesCpuRegY
#define S					g_nNesCpuRegS
#define P_G					g_nNesCpuRegP
#define PC_G				g_nNesCpuRegPC

#if TRL_CPU_OPCODE_REG_FAST_REGP
#define P					nNesCpuRegP
#else
#define P					g_nNesCpuRegP
#endif

#if TRL_CPU_OPCODE_REG_FAST_REGPC
#define PC					nNesCpuRegPC
#else
#define PC					g_nNesCpuRegPC
#endif

#if TRL_CPU_OPCODE_REG_FAST_REGA
#define A					nNesCpuRegA
#else
#define A					g_nNesCpuRegA
#endif

#define	CHECK_Z(v)			((!v) << 1)
#define	CHECK_Z16(v)		((!(v&0xFF)) << 1)
#define	CHECK_N(v)			(v&0x80)

#define GET_CFLAG()			(P&NES_CPU_CFLAG)

#define SET_NZ(v)			(P = (P&0x7D) | CHECK_Z(v) | CHECK_N(v))
#define SET_NZC_CMP(v)		(P = (P&0x7C) | CHECK_Z16(v) | CHECK_N(v) | (v>=0))
#define SET_NZC_LEFT(v)		(P = (P&0x7C) | CHECK_Z16(v) | CHECK_N(v) | ((v&0x0100) >> 8))
#define SET_NZC_RIGHT(v)	(P = (P&0x7C) | CHECK_Z((v>>1)) | (v&0x01))
#define SET_NZC_RIGHTC(v)	(P = (P&0x7C) | CHECK_Z((v>>1)) | ((v&0x100)>>1) | (v&0x01))
#define SET_NVZC_ADD(w,v)	(P = (P&0x3C) | CHECK_Z16(v) | CHECK_N(v) | ((v>>8)&NES_CPU_CFLAG) | (((~(A^w))&(A^v)&0x80)>>1))
#define SET_NVZC_SUB(w,v)	(P = (P&0x3C) | CHECK_Z16(v) | CHECK_N(v) | (v>=0) | (((A^w)&(A^v)&0x80)>>1))

#define SET_PC_G(v)			(g_pNesCpuPC += v, PC += v)
#define SET_TICK_G(v)		(g_nNesCpuTicks += v)

#if TRL_CPU_OPCODE_REG_FAST

#if TRL_CPU_OPCODE_REG_FAST_REGPC
#define SET_PC(v)			(pNesCpuPC += v, PC += v)
#else
#define SET_PC(v)			(pNesCpuPC += v, PC += v)
#endif

#if TRL_CPU_OPCODE_REG_FAST_OPCODE
#define GET_PCCODE_8()		((nOpcode>>8)&0xFF)
#define GET_PCCODE_16()		((nOpcode>>8)&0xFFFF)
#else
#define GET_PCCODE_8()		(*(pNesCpuPC+1))
#define GET_PCCODE_16()		(*((u16*)(pNesCpuPC+1)))
#endif



#if TRL_CPU_OPCODE_REG_FAST_REGPC
#define NES_CPU_UPDATE_PC() (g_nNesCpuRegPC = nNesCpuRegPC,pNesCpuPC = nesCpuUpdatePC())
#else
#define NES_CPU_UPDATE_PC() (pNesCpuPC = nesCpuUpdatePC())
#endif

#if TRL_CPU_OPCODE_REG_FAST_TICK
#define SET_TICK(v)			(nNesCpuTicks += v)
#define CPU_TICKS			nNesCpuTicks
#else
#define SET_TICK(v)			(g_nNesCpuTicks += v)
#define CPU_TICKS			g_nNesCpuTicks
#endif

#else
#define SET_PC(v)			(g_pNesCpuPC += v, PC += v)
#define GET_PCCODE_8()		(*(g_pNesCpuPC+1))
#define GET_PCCODE_16()		(*((u16*)(g_pNesCpuPC+1)))
#define NES_CPU_UPDATE_PC() (nesCpuUpdatePC())
#define SET_TICK(v)			(g_nNesCpuTicks += v)
#define CPU_TICKS			g_nNesCpuTicks
#endif

#define GET_IMMEDIATE()		GET_PCCODE_8();SET_PC(2)
#define GET_ZEROPAGE()		g_pNesWRAM[GET_PCCODE_8()];SET_PC(2)
#define GET_ZEROPAGE_(r)	g_pNesWRAM[(u8)(GET_PCCODE_8() + r)];SET_PC(2)
#define GET_ABSOLUTE()		nesMemRead8(GET_PCCODE_16());SET_PC(3)
#define GET_ABSOLUTE_(r)	nesMemRead8(nesCpuCheckCross(GET_PCCODE_16(), r, CPU_TICKS));SET_PC(3)
#define GET_INDIRECT_X()	nesMemRead8(*((u16*)&g_pNesWRAM[(u8)(GET_PCCODE_8()+ X)]));SET_PC(2)
#define GET_INDIRECT_Y()	nesMemRead8(nesCpuCheckCross(*((u16*)&g_pNesWRAM[GET_PCCODE_8()]), Y, CPU_TICKS));SET_PC(2)

#define SET_ZEROPAGE(v)		trlTraceMemWrite(GET_PCCODE_8(), v);(g_pNesWRAM[GET_PCCODE_8()] = v);SET_PC(2)
#define SET_ZEROPAGE_(r,v)	trlTraceMemWrite(GET_PCCODE_8() + r, v);(g_pNesWRAM[(u8)(GET_PCCODE_8() + r)] = v);SET_PC(2)

#if TRL_CPU_OPCODE_REG_FAST_TICK 
#define SET_ABSOLUTE(v)		g_nNesCpuTicks=nNesCpuTicks;nesMemWrite8(GET_PCCODE_16(), v);nNesCpuTicks=g_nNesCpuTicks;SET_PC(3)
#define SET_ABSOLUTE_(r,v)	g_nNesCpuTicks=nNesCpuTicks;nesMemWrite8(GET_PCCODE_16() + r, v);nNesCpuTicks=g_nNesCpuTicks;SET_PC(3)
#else
#define SET_ABSOLUTE(v)		nesMemWrite8(GET_PCCODE_16(), v);SET_PC(3)
#define SET_ABSOLUTE_(r,v)	nesMemWrite8(GET_PCCODE_16() + r, v);SET_PC(3)
#endif

#define SET_INDIRECT_X(v)	nesMemWrite8(*((u16*)&g_pNesWRAM[(u8)(GET_PCCODE_8() + X)]), v);SET_PC(2)
#define SET_INDIRECT_Y(v)	nesMemWrite8(*((u16*)&g_pNesWRAM[GET_PCCODE_8()]) + Y, v);SET_PC(2)

#define STACK_PUSH(v)		(g_pNesWRAM[S+0x100] = v, --S)
#define STACK_PUSHPC(v)		(*(u16*)(g_pNesWRAM+S-1+0x100) = PC+v, S -= 2)
#define STACK_PUSHPC_G(v)	(*(u16*)(g_pNesWRAM+S-1+0x100) = PC_G+v, S -= 2)
#define STACK_PULL(v)		(++S, v = g_pNesWRAM[S+0x100])
#define STACK_PULLPC(v)		(S += 2, PC = *(u16*)(g_pNesWRAM+S-1+0x100) + v, NES_CPU_UPDATE_PC())
//@}

/** @name Global Variable */
//@{
s32							g_nNesCpuEventTicks;						///< Next Event Ticks
s32							g_nNesCpuTicks;								///< CPU Run Ticks
u16							g_nNesCpuRegPC;								///< CPU Registe PC
u8							g_nNesCpuRegA;								///< CPU Registe A
u8							g_nNesCpuRegX;								///< CPU Registe X
u8							g_nNesCpuRegY;								///< CPU Registe Y
u8							g_nNesCpuRegS;								///< CPU Registe S
u8							g_nNesCpuRegP;								///< CPU Registe P
u8							g_nNesCpuNMIFlag;							///< CPU NMI Flag
u8							g_nNesCpuIRQFlag;							///< CPU IRQ Flag
u8							g_nNesCpuRESETFlag;							///< CPU RESET Flag

u8*							g_pNesCpuPC;								///< CPU PC Pointer
u32							g_nNesCpuSaveData = 0;						///< CPU Save Data Count
trlSEmuShellResume			g_sNesCpuSaveData[NES_CPU_SAVEDATA_MAX];	///< CPU Save Data
//@}

#ifdef TRL_PLATFORM_PC
u32	g_bNesCPUDebug = 0;
FILE *g_hNesCPU = NULL;
#endif
/** @brief Initialize CPU */
void nesCpuInit()
{
#ifdef TRL_PLATFORM_PC
	if(!g_hNesCPU)
		fopen_s(&g_hNesCPU, "cpu_log_nes.log", "wb");
#endif
	// Save Data
	g_nNesCpuSaveData = 0;
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuEventTicks, 4, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuTicks, 4, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRegPC, 2, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRegA, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRegX, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRegY, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRegS, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRegP, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuNMIFlag, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuIRQFlag, 1, 1, 0);
	g_sNesCpuSaveData[g_nNesCpuSaveData++].SetData(&g_nNesCpuRESETFlag, 1, 3, 0);

	nesCpuReset();
}

/** @brief Update PC Pointer */
inline void nesCpuUpdatePC_G()
{
	switch(PC_G >> 13)
	{
	case 0x0:				// 0000h-07FFh   Internal 2K Work RAM (mirrored to 800h-1FFFh)
		g_pNesCpuPC = &g_pNesWRAM[PC_G&0x7FF];
		return;
	case 0x3:				// 6000h-7FFFh   Cartridge SRAM Area 8K
		if(g_pNesSRAMBank != NULL)
		{
			g_pNesCpuPC = &g_pNesSRAMBank[PC_G&0x1FFF];
			return;
		}
		break;
	case 0x4:				// 8000h-9FFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[0][PC_G&0x1FFF];
		return;
	case 0x5:				// A000h-BFFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[1][PC_G&0x1FFF];
		return;
	case 0x6:				// C000h-DFFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[2][PC_G&0x1FFF];
		return;
	case 0x7:				// E000h-FFFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[3][PC_G&0x1FFF];
		return;
	}
	g_pNesEmuBuf->bError = 1;
}

/** @brief Update PC Pointer */
inline u8* nesCpuUpdatePC()
{
	switch(PC_G >> 13)
	{
	case 0x0:				// 0000h-07FFh   Internal 2K Work RAM (mirrored to 800h-1FFFh)
		g_pNesCpuPC = &g_pNesWRAM[PC_G&0x7FF];
		return g_pNesCpuPC;
	case 0x3:				// 6000h-7FFFh   Cartridge SRAM Area 8K
		if(g_pNesSRAMBank != NULL)
		{
			g_pNesCpuPC = &g_pNesSRAMBank[PC_G&0x1FFF];
			return g_pNesCpuPC;
		}
		break;
	case 0x4:				// 8000h-9FFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[0][PC_G&0x1FFF];
		return g_pNesCpuPC;
	case 0x5:				// A000h-BFFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[1][PC_G&0x1FFF];
		return g_pNesCpuPC;
	case 0x6:				// C000h-DFFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[2][PC_G&0x1FFF];
		return g_pNesCpuPC;
	case 0x7:				// E000h-FFFFh   Cartridge PRG-ROM Area 8K
		g_pNesCpuPC = &g_pNesPRGBank[3][PC_G&0x1FFF];
		return g_pNesCpuPC;
	}
	g_pNesEmuBuf->bError = 1;
	return g_pNesCpuPC;
}

/** @brief Reset CPU */
void nesCpuReset()
{
	A_G = 0x00;
	X = 0x00;
	Y = 0x00;
	S = 0xFF;
	P_G = NES_CPU_UFLAG | NES_CPU_ZFLAG | NES_CPU_IFLAG;
	PC_G = *((u16*)&g_pNesPRGBank[3][0x1FFC]);
	nesCpuUpdatePC_G();

	g_nNesCpuIRQFlag = 0;
	g_nNesCpuNMIFlag = 0;
	g_nNesCpuRESETFlag = 0;
	g_nNesCpuTicks = 0;
	g_nNesCpuEventTicks = 0;
}

/** @brief Resume CPU */
void nesCpuResume()
{
	nesCpuUpdatePC_G();
}

/** @brief Check Indexing Crosses a Page Boundary */
inline u16 nesCpuCheckCross(u16 nValue, u8 nReg, s32 &tick)
{
	u16 nAddr = nReg + nValue;
	if((nAddr^nValue)&0x100)
		tick++;
	return nAddr;
}


/** @brief CPU Patch */
//return 0, normal  LB_NES_CPU_OPCODE
//return 1, go to  LB_NES_CPU_GETOPCODE
u8 nesCpuPatch()
{
	u8 nopcode = 0xEA;
	u32 nAddress = g_pNesCpuPC - (u8*)g_pNesEmuBuf->pRomBuf;
		trlSEmuShellPatch* pPatch = g_pNesEmuBuf->pPatchData;
		for(u32 nID = 0; nID < g_pNesEmuBuf->nPatchCount; ++nID, ++pPatch)
		{
			u32 nFind = 0;
			if(pPatch->sData.sA.nMemAddress != 0xFFFFFFFF)
			{
				if(pPatch->sData.sA.nMemAddress == PC_G)
					nFind = 1;
			}
			else
			{
				if(pPatch->sData.sA.nAddress == nAddress)
					nFind = 1;
			}
			if(nFind && pPatch->sData.sA.nConditionType != 0xFFFFFFFF)
			{
				if(pPatch->sData.sA.nConditionType == 0) //MemCheck
				{
					for(int i=0;i<pPatch->sData.sA.nConditionValueA/2;i++)
					{
						u16 addr  = pPatch->pConditionValueA[i*2] + (pPatch->pConditionValueA[i*2 + 1]<<8);
						u16 cond  = pPatch->pConditionValueB[i*2] + (pPatch->pConditionValueB[i*2 + 1]<<8);
						u16 value = pPatch->pConditionValueC[i*2] + (pPatch->pConditionValueC[i*2 + 1]<<8);
						if( 
							(cond == 0x0000 && !(nesMemRead8(addr) == value)) ||
							(cond == 0x0001 && !(nesMemRead8(addr) >  value)) ||
							(cond == 0x0002 && !(nesMemRead8(addr) <  value)) ||
							(cond == 0x0003 && !(nesMemRead8(addr) >= value)) ||
							(cond == 0x0004 && !(nesMemRead8(addr) <= value)) ||
							(cond == 0x0005 && !(nesMemRead8(addr) != value))
						)
						{
							nFind = 0;
							nopcode = (u8)pPatch->nOpcode;
							break;						
						}
					}
				}
				if(pPatch->sData.sA.nConditionType == 1) //VRAM Check rangelzhang add 2012/7/20
				{
					u16 begin_addr  = pPatch->pConditionValueA[0] + (pPatch->pConditionValueA[1]<<8);
					for(int i=0;i<pPatch->sData.sA.nConditionValueC;i++)
					{
						if(pPatch->pConditionValueC[i]!=g_pNesVRAM[(begin_addr + i)&0x3FFF])
						{
							nFind = 0;
							nopcode = (u8)pPatch->nOpcode;
							break;						
						}
					}
				}
			}

			if(nFind)
			{
				NN_LOG("Patch %d 0x%x\n", nID, nAddress);
				nopcode = (u8)pPatch->nOpcode;
				#include "nesPatch.h"				
				return nopcode;
			}
		}
		return nopcode;
}

/** @brief Run CPU */
void nesCpuRun()
{
	if(g_nNesCpuRESETFlag)
	{
		g_nNesCpuRESETFlag = 0;
		g_nNesCpuIRQFlag = 0;
		g_nNesCpuNMIFlag = 0;
		A_G = 0x00;
		X = 0x00;
		Y = 0x00;
		S = 0xFF;
		P_G = NES_CPU_UFLAG | NES_CPU_ZFLAG | NES_CPU_IFLAG;
		PC_G = *((u16*)&g_pNesPRGBank[3][0x1FFC]);
		nesCpuUpdatePC_G();
		SET_TICK_G(6);
#if TRL_HVC_NMI_LINE240
//		g_pNesGrpReg2000->rNMI = 0;
#endif
	}
	else if(g_nNesCpuNMIFlag)
	{
		g_nNesCpuNMIFlag = 0;
		P_G &= ~NES_CPU_BFLAG;
		STACK_PUSHPC_G(0);
		STACK_PUSH(P_G);
		P_G |= NES_CPU_IFLAG;
		PC_G = *((u16*)&g_pNesPRGBank[3][0x1FFA]);
		nesCpuUpdatePC_G();
		SET_TICK_G(7);
#ifdef TRL_PLATFORM_PC
	if(g_bNesCPUDebug==1)
		fprintf(g_hNesCPU, "NMI\r\n");
#endif
	}
	else if(g_nNesCpuIRQFlag)
	{
		if( (P_G&NES_CPU_IFLAG) == 0)
		{
			P_G &= ~NES_CPU_BFLAG;
			STACK_PUSHPC_G(0);
			STACK_PUSH(P_G);
			P_G |= NES_CPU_IFLAG;
			PC_G = *((u16*)&g_pNesPRGBank[3][0x1FFE]);
			nesCpuUpdatePC_G();
			SET_TICK_G(7);
#ifdef TRL_PLATFORM_PC
	if(g_bNesCPUDebug==1)
		fprintf(g_hNesCPU, "IRQ_%d\r\n", g_nNesCpuIRQFlag);
#endif
		}
	}

#ifdef TRL_PLATFORM_PC
	if((g_pNesEmuBuf->nDebugKey & 1) && (g_bNesCPUDebug == 0))
		g_bNesCPUDebug = 1;
	if((g_pNesEmuBuf->nDebugKey & 2) && (g_bNesCPUDebug == 1))
	{
		fclose(g_hNesCPU);
		g_hNesCPU = NULL;
		g_bNesCPUDebug = 2;
	}
#endif

#if TRL_CPU_OPCODE_REG_FAST
	register u8* pNesCpuPC = g_pNesCpuPC;
#if TRL_CPU_OPCODE_REG_FAST_TICK
	register s32 nNesCpuTicks = g_nNesCpuTicks;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGP
	register u8  nNesCpuRegP = g_nNesCpuRegP;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGPC
	register u16  nNesCpuRegPC = g_nNesCpuRegPC;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGA
	register u8  nNesCpuRegA = g_nNesCpuRegA;
#endif
#endif

#if TRL_CPU_OPCODE_REG_FAST
	while(nNesCpuTicks<g_nNesCpuEventTicks)
#else
	while(g_nNesCpuTicks<g_nNesCpuEventTicks)
#endif
	{
#ifdef TRL_PLATFORM_PC
		if(g_pNesROMHeader->nMapper == 100)
		{
			switch(PC)
			{
			case 0xE1F8:
				NN_LOG("Load Files\n");
				break;
			case 0xE237:
				NN_LOG("Append File\n");
				break;
			case 0xE239:
				NN_LOG("Write File\n");
				break;
			case 0xE2B7:
				NN_LOG("Check File count\n");
				break;
			case 0xE2BB:
				NN_LOG("Adjust File count\n");
				break;
			case 0xE301:
				NN_LOG("Set File count (alt. 2)\n");
				break;
			case 0xE305:
				NN_LOG("Set File count (alt. 1)\n");
				break;
			case 0xE32A:
				NN_LOG("Get Disk Information\n");
				break;
			}
		}
		if(g_bNesCPUDebug==1)
		{	
			//fprintf(g_hNesCPU, "$%04X:%02X(%02X) L:%d A:%02X X:%02X Y:%02X S:%02X P:%s%sU%s%s%s%s%s\r\n", PC, nesMemRead8(PC), *g_pNesCpuPC, g_nNesGrpLines, A, X, Y, S, (P&0x80)?"N":"n", (P&0x40)?"V":"v", (P&0x10)?"B":"b", (P&0x08)?"D":"d", (P&0x04)?"I":"i", (P&0x02)?"Z":"z", (P&0x01)?"C":"c");
			//NN_LOG("$%04X:%02X(%02X) L:%d A:%02X X:%02X Y:%02X S:%02X P:%s%sU%s%s%s%s%s\r\n", PC, nesMemRead8(PC), *g_pNesCpuPC, g_nNesGrpLines, A, X, Y, S, (P&0x80)?"N":"n", (P&0x40)?"V":"v", (P&0x10)?"B":"b", (P&0x08)?"D":"d", (P&0x04)?"I":"i", (P&0x02)?"Z":"z", (P&0x01)?"C":"c");
			//fprintf(g_hNesCPU,"$%04x:",PC);
#if TRL_CPU_OPCODE_REG_FAST
#if TRL_CPU_OPCODE_REG_FAST_REGP
	g_nNesCpuRegP = nNesCpuRegP;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGPC
	g_nNesCpuRegPC = nNesCpuRegPC;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGA
	g_nNesCpuRegA = nNesCpuRegA;
#endif
	g_pNesCpuPC = pNesCpuPC;
#if TRL_CPU_OPCODE_REG_FAST_TICK
	g_nNesCpuTicks = nNesCpuTicks;
#endif
#endif
			void WriteDisassembleFile(FILE *fp);
			WriteDisassembleFile(g_hNesCPU);
		}
#endif
		trlTraceCPURUN_NES();
		#include "nesCPUOpcode.h"
#ifdef TRL_PLATFORM_PC
		{
			static int ct = 0;
			ct++;
			//if(ct == 0x4259)
			//	ct = ct;
#if TRL_CPU_OPCODE_REG_FAST_TICK
			if(g_nNesCpuTicks != nNesCpuTicks)
				g_nNesCpuTicks = nNesCpuTicks;
#endif
			//NN_LOG("%d %d\n", ct, PC);

		}
#endif
	}
#if TRL_CPU_OPCODE_REG_FAST
#if TRL_CPU_OPCODE_REG_FAST_REGP
	g_nNesCpuRegP = nNesCpuRegP;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGPC
	g_nNesCpuRegPC = nNesCpuRegPC;
#endif
#if TRL_CPU_OPCODE_REG_FAST_REGA
	g_nNesCpuRegA = nNesCpuRegA;
#endif
	g_pNesCpuPC = pNesCpuPC;
#if TRL_CPU_OPCODE_REG_FAST_TICK
	g_nNesCpuTicks = nNesCpuTicks;
#endif
#endif

	g_nNesCpuTicks -= g_nNesCpuEventTicks;
}
