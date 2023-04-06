/**
 * @file agbCPU.cpp
 * @author zhfang
 * @date 2009.11.26
 * @brief AGB Emulate For CTR - CPU
 */
#include "agbGlobal.h"
#include "agbMemory.h"
#include "agbCPU.h"
#include "agbRegister.h"
#include "agbCPUData.h"
#include "CPUCompiler\agbCPUCmp.h"
#include "CPUCOmpiler\agbCPUCmpiler.h"
#include "CPUCompiler\agbCPUCmpRunner.h"

 //zhfang test
#ifdef TRL_PLATFORM_CTR
 #pragma diag_suppress 63, 550, 177,1517
#endif
 
/** @name some macro */
//@{

//@}


/** @name Local Function */
//@{
u32 agbCPUGetCondResult(u32 cond);  ///< computer the cond field of ARM instruction
inline void agbCPURunArm();		///< execute the current ARM instruction
inline void agbCPURunThumb();	///< execute the current Thumb instruction

void agbCPUUpdateCPSR();  ///< update the g_nAgbCPUReg[16](CPSR) by g_nAgbCPUReg[REG_ZFLAG], g_nAgbCPUReg[REG_CFLAG].....






void agbCPUSwap(u32 *a, u32 *b);	///< swap two  u32:  a<->b

s32 agbCPUEmptyLoogProc();

void agbCPUIntrCheck();
void agbCPUInterruptRun();

void agbCPUGetGameTitle();
//@}

void agbCPUGetGameTitle()
{
	u32 *pGameCode = (u32*)&g_pAgbROMHeader->nGameCode[0];
	if(*pGameCode == 0x4A414D41) //AMAJ
	{
		g_nAgbGameTitle = AGB_TITLE_MARIOA_AMAJ;
	}
	else if(*pGameCode == 0x4A424741) //AGBJ
	{
		if(g_pAgbROMHeader->nTitle[0] == 0x59)//YOSHI
		{
			g_nAgbGameTitle = AGB_TITLE_SIMPLE_YOSHI;
		}
		else if(g_pAgbROMHeader->nTitle[0] == 0x44)//YOSHI
		{
			g_nAgbGameTitle = AGB_TITLE_SIMPLE_DOPHI;
		}
	}
	else if(*pGameCode == 0x00000000) //test rom
	{
		g_nAgbGameTitle = AGB_TITLE_CHECK323;
	}
}

/** @brief Initialize CPU */
void agbCPUInit()
{
	TRL_INFO(0, "agbCPUInit");
	agbCPUReset();
}
 
/** @brief Reset CPU */
void agbCPUReset()
{
	//clear reg
	memset(&g_nAgbCPUReg[0],  0,  sizeof(g_nAgbCPUReg));
	//memset(&g_nAgbCPURegBank[0], 0, sizeof(g_nAgbCPURegBank));

	//clear clock
	g_nAgbCPUClock = 0;

	//set PC SP 
	g_nAgbCPUReg[13] = 0x03007f00;
	g_nAgbCPUReg[15] = 0x08000000;	
	g_nAgbCPUReg[R13_IRQ] = 0x03007fa0;
	g_nAgbCPUReg[R13_SVC] = 0x03007fe0;

	//set CPSR
	g_nAgbCPUReg[16] = 0x00000000;
	g_nAgbCPUReg[REG_NFLAG] = g_nAgbCPUReg[REG_ZFLAG] = g_nAgbCPUReg[REG_CFLAG] = g_nAgbCPUReg[REG_VFLAG] = 0;
	g_bAgbIrqDisable = 0;	
	g_nAgbCPUReg[REG_CPUMODE] = CPU_MODE_SYS;
	g_nAgbThumbState = 0;
	g_bFiqDisable = 1;
	g_nAgbCPUReg[16] |= 0x40;
	agbCPUUpdateCPSR();	

	//init instruction
	g_nAgbInsta = g_nAgbInsta = g_nAgbInstb = 0;
	ARM_FIRST_PREFETCH

	//init some statue
	g_nAgbCPUBeInterrupt = 0;
	//init the instruction compiler
	//zhfang test
	agbCPUGetGameTitle();
#if TRL_AGBCMP
	agbCPUCmpInit();
#endif
}

s32 agbCPUEmptyLoogProc()
{
//zhfang test
//empty loop hack
	if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
	{
		if((g_nAgbCPUReg[15]-2) == 0x0800028C)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}		
	}
	else if(g_nAgbGameTitle == AGB_TITLE_MARIOA_AMAJ)
	{
		if((g_nAgbCPUReg[15]-4) == 0x08001c6e)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}
	}
	else if(g_nAgbGameTitle == AGB_TITLE_CHECK323)
	{
		if((g_nAgbCPUReg[15]-2) == 0x08000E0C)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}
		if((g_nAgbCPUReg[15]-2) == 0x08000E12)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}

		if((g_nAgbCPUReg[15]-2) == 0x08000E1E)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}
		if((g_nAgbCPUReg[15]-2) == 0x08000E24)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}

		if((g_nAgbCPUReg[15]-2) == 0x08000E30)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}

		if((g_nAgbCPUReg[15]-2) == 0x08000E3C)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}
		if((g_nAgbCPUReg[15]-2) == 0x08000E42)
		{
			g_nAgbCPUClock += 100*1;
			return 1;
		}
	}
	return 0;
}

/** @brief Run CPU */
void agbCPURun()
{	
	if(g_pAgbHaltCnt->rHalt == 0)
	{
		if(g_nAgbCPUReg[15]  == 0x080002d8)
			g_nAgbCPUReg[15] = g_nAgbCPUReg[15];
		if(g_nAgbCPUReg[15] -4 == 0x000010bC)
			g_nAgbCPUReg[15] = g_nAgbCPUReg[15];	
#if TRL_AGBCMP
		if(agbCPUCmpRun() < 0)
#endif
		{
			if((g_nAgbCPUReg[15] -4) == 0x03000f3c)
			{
				g_nAgbCPUReg[15] = g_nAgbCPUReg[15];
			}
			agbCPUEmptyLoogProc();
			if(g_nAgbThumbState == 0)
				agbCPURunArm();
			else
				agbCPURunThumb();
		}
	}
	else
	{
		g_pAgbHaltCnt->rHalt = 1;
	}
	//agbCPUIntrCheck();
	agbCPUIntrCheckRun();
}

void agbCPUInterrupt()
{
	u32 pc = g_nAgbCPUReg[15];
	u32 saveState = g_nAgbThumbState;
	agbCPUSwitchMode(0x12, 1);
	g_nAgbCPUReg[14] = pc;
	if(saveState ==  1)
		g_nAgbCPUReg[14] += 2;
	g_nAgbCPUReg[15] = 0x18;
	g_nAgbThumbState = 0;
	g_bAgbIrqDisable = 1;
	ARM_FIRST_PREFETCH
}


void agbCPUInterruptRun()
{
	u32 pc = g_nAgbCPUReg[15];
	u32 saveState = g_nAgbThumbState;
	agbCPUSwitchMode(0x12, 1);
	g_nAgbCPUReg[14] = pc;
	if(saveState ==  1)
		g_nAgbCPUReg[14] += 2;
	g_nAgbCPUReg[15] = 0x18;
	g_nAgbThumbState = 0;
	g_bAgbIrqDisable = 1;
	ARM_FIRST_PREFETCH

	agbCPUCmpCmpInterrupt();
	while(1)
	{
		if(g_nAgbCPUReg[15] == pc)
		{
			break;
		}
		if(agbCPUCmpRun() < 0)
		{
			//agbCPUEmptyLoogProc();
 			if(g_nAgbThumbState == 0)
				agbCPURunArm();
			else
				agbCPURunThumb();
		}
	}
}

void agbCPUIntrCheckRun()
{
	u16 IF = *(u16*)g_pAgbIF;
	u16 IME = *(u16*)g_pAgbIME;
	u16 IE = *(u16*)g_pAgbIE;

	if(g_pAgbIF->rTMR == 2)
		g_pAgbIF->rTMR = 2;

	if(IF &&(g_pAgbIME->rEnable) && g_bAgbIrqDisable == 0)
	{
		u32 res = IF & IE;
		if(res != 0)
		{			
			g_pAgbHaltCnt->rHalt = 0;
			g_nAgbCPUBeInterrupt = 1;
			agbCPUInterruptRun();
			g_nAgbCPUBeInterrupt = 0;
		}
	}
}

void agbCPUIntrCheck()
{
	u16 IF = *(u16*)g_pAgbIF;
	u16 IME = *(u16*)g_pAgbIME;
	u16 IE = *(u16*)g_pAgbIE;

	if(IF &&(g_pAgbIME->rEnable) && g_bAgbIrqDisable == 0)
	{
		u32 res = IF & IE;
		if(res != 0)
		{
			g_pAgbHaltCnt->rHalt = 0;
			agbCPUInterrupt();			
		}
	}
}

/** @brief test cond field  return the result*/
u32 agbCPUGetCondResult(u32 cond)
{
	u32 result = 0;
	if(cond == 0x0e)
		return 1;
	switch(cond)
	{
		case 0:
			result = g_nAgbCPUReg[REG_ZFLAG];break;
		case 1:
			result = !g_nAgbCPUReg[REG_ZFLAG];break;
		case 2:
			result = g_nAgbCPUReg[REG_CFLAG];break;
		case 3:
			result = !g_nAgbCPUReg[REG_CFLAG];break;
		case 4:
			result = g_nAgbCPUReg[REG_NFLAG];break;
		case 5:
			result = !g_nAgbCPUReg[REG_NFLAG];break;
		case 6:
			result = g_nAgbCPUReg[REG_VFLAG];break;
		case 7:
			result = !g_nAgbCPUReg[REG_VFLAG];break;
		case 8:
			result = ((g_nAgbCPUReg[REG_CFLAG]) && (!g_nAgbCPUReg[REG_ZFLAG]));break;
		case 9:
			result = ((!g_nAgbCPUReg[REG_CFLAG]) || (g_nAgbCPUReg[REG_ZFLAG]));break;
		case 10:
			result = (g_nAgbCPUReg[REG_NFLAG] == g_nAgbCPUReg[REG_VFLAG]);break;
		case 11:
			result = (g_nAgbCPUReg[REG_NFLAG] != g_nAgbCPUReg[REG_VFLAG]);break;
		case 12:
			result = (!g_nAgbCPUReg[REG_ZFLAG] && (g_nAgbCPUReg[REG_NFLAG] == g_nAgbCPUReg[REG_VFLAG]));break;
		case 13:
			result = (g_nAgbCPUReg[REG_ZFLAG] || (g_nAgbCPUReg[REG_NFLAG] != g_nAgbCPUReg[REG_VFLAG]));break;
		default:
			TRL_WARN(1, "agbCPUGetCondResult unknown cond field\n");
			result = 0;
			break;
	}
	return result;
}

void agbCPUUpdateCPSR()
{
	u32 cpsr = g_nAgbCPUReg[16] & 0x40;
	if(g_nAgbCPUReg[REG_NFLAG])
		cpsr |= 0x80000000;
	if(g_nAgbCPUReg[REG_ZFLAG])
		cpsr |= 0x40000000;
	if(g_nAgbCPUReg[REG_CFLAG])
		cpsr |= 0x20000000;
	if(g_nAgbCPUReg[REG_VFLAG])
		cpsr |= 0x10000000;
	if(g_nAgbThumbState)
		cpsr |= 0x00000020;
	if(g_bAgbIrqDisable)
		cpsr |= 0x00000080;
	cpsr |= (g_nAgbCPUReg[REG_CPUMODE] & 0x1F);
	g_nAgbCPUReg[16] = cpsr;
}





/** @brief Run Arm Instruction */
inline void agbCPURunArm()
{
	//fetch
	g_nAgbInst = g_nAgbInsta;
	g_nAgbInsta = g_nAgbInstb;
	g_nAgbInstb = agbMemRead32(g_nAgbCPUReg[15]+4);
	g_nAgbCPUReg[15] +=4;

	u32 opcode1 = (g_nAgbInst >>16)&0xff0;
	u32 opcode2 = (g_nAgbInst >>4)&0xf;
	u32 opcode =g_nAgbInst;

	//decode
	u32 cond = g_nAgbInst>>28;
	u32 con_result = agbCPUGetCondResult(cond);
	
	//execute
	if(con_result)
	{
		#include "agbCPUArm.h"
#if 0		
		#ifdef TRL_PLATFORM_PC
		cpu_ct_arm[testcode]++;
		#endif
#endif			
	}
	//zhfnag test
	//becase the CPUClock can't yet been computer correctly
	//so, I do't add the time to CPUClock...
	//now synchronization is made by syscall "VBlankWait"	
	//.....
	g_nAgbCPUClock += 1;
}


#include "agbCPUThumbCFunc.h"
/** @brief Run thumb Instruction */
inline void agbCPURunThumb()
{
	//fetch
	g_nAgbInst = g_nAgbInsta;
	g_nAgbInsta = g_nAgbInstb;
	g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15]+2);
	g_nAgbCPUReg[15]+=2;

	//decode & execute
	u32 opcode = g_nAgbInst;	
#if 0 //old
	//#include "agbCPUThumb.h"
#endif
	if(g_nAgbCPUReg[15] == 0x0800187A && g_nAgbCPUReg[6] == 8)
		g_nAgbCPUReg[6] = 8;
	g_pAgbCPUThumbFuncTable[opcode>>8]();
	g_nAgbCPUClock+=1;
}

/** @brief Update state flags */
extern "C" void agbCPUUpdateFlags( )
{
	u32 cpsr = g_nAgbCPUReg[16];

	g_nAgbCPUReg[REG_NFLAG] = (cpsr >>31)&0x1;
	g_nAgbCPUReg[REG_ZFLAG] = (cpsr >>30)&0x1;
	g_nAgbCPUReg[REG_CFLAG] = (cpsr >>29) & 0x1;
	g_nAgbCPUReg[REG_VFLAG] = (cpsr>>28)&0x1;

	g_nAgbThumbState = (cpsr>>5)&0x1;
	g_bFiqDisable = (cpsr>>6)&0x1;
	g_bAgbIrqDisable = (cpsr>>7)&0x1;
 }

/** @brief Switch the CPU Mode */
void agbCPUSwap(u32 *a, u32 *b)
{
	u32 c = *a;
	*a = *b;
	*b = c;	
}
extern "C" void agbCPUSwitchMode(u32 mode, u32 saveState)
{
	if(g_nAgbCPUReg[REG_CPUMODE] == mode)
		return;

	
	
	agbCPUUpdateCPSR();
	switch(g_nAgbCPUReg[REG_CPUMODE])
	{
	case CPU_MODE_USER:
	case CPU_MODE_SYS:
		g_nAgbCPUReg[R13_USER] = g_nAgbCPUReg[13];
		g_nAgbCPUReg[R14_USER] = g_nAgbCPUReg[14];
		g_nAgbCPUReg[17] = g_nAgbCPUReg[16];
		break;
	case CPU_MODE_FIQ:
		agbCPUSwap(&g_nAgbCPUReg[R8_FIQ], &g_nAgbCPUReg[8]);
		agbCPUSwap(&g_nAgbCPUReg[R9_FIQ], &g_nAgbCPUReg[9]);
		agbCPUSwap(&g_nAgbCPUReg[R10_FIQ], &g_nAgbCPUReg[10]);
		agbCPUSwap(&g_nAgbCPUReg[R11_FIQ], &g_nAgbCPUReg[11]);
		agbCPUSwap(&g_nAgbCPUReg[R12_FIQ], &g_nAgbCPUReg[12]);
		g_nAgbCPUReg[R13_FIQ] = g_nAgbCPUReg[13];
		g_nAgbCPUReg[R14_FIQ] = g_nAgbCPUReg[14];
		g_nAgbCPUReg[SPSR_FIQ] = g_nAgbCPUReg[17];
		break;
	case CPU_MODE_IRQ:
		g_nAgbCPUReg[R13_IRQ] = g_nAgbCPUReg[13];
		g_nAgbCPUReg[R14_IRQ] = g_nAgbCPUReg[14];
		g_nAgbCPUReg[SPSR_IRQ] = g_nAgbCPUReg[17];
		break;
	case CPU_MODE_SVC:
		g_nAgbCPUReg[R13_SVC] = g_nAgbCPUReg[13];
		g_nAgbCPUReg[R14_SVC] = g_nAgbCPUReg[14];
		g_nAgbCPUReg[SPSR_SVC] = g_nAgbCPUReg[17];
		break;
	case CPU_MODE_ABT:
		g_nAgbCPUReg[R13_ABT] = g_nAgbCPUReg[13];
		g_nAgbCPUReg[R14_ABT] = g_nAgbCPUReg[14];
		g_nAgbCPUReg[SPSR_ABT] = g_nAgbCPUReg[17];
		break;
	case CPU_MODE_UND:
		g_nAgbCPUReg[R13_UND] = g_nAgbCPUReg[13];
		g_nAgbCPUReg[R14_UND] = g_nAgbCPUReg[14];
		g_nAgbCPUReg[SPSR_UND] = g_nAgbCPUReg[17];
		break;
	}

	u32 CPSR = g_nAgbCPUReg[16];
	u32 SPSR = g_nAgbCPUReg[17];

	switch(mode)
	{
	case CPU_MODE_USER:
	case CPU_MODE_SYS:
		g_nAgbCPUReg[13] = g_nAgbCPUReg[R13_USER];
		g_nAgbCPUReg[14] = g_nAgbCPUReg[R14_USER];
		g_nAgbCPUReg[16] = SPSR;
		break;
	case CPU_MODE_FIQ:
		agbCPUSwap(&g_nAgbCPUReg[R8_FIQ], &g_nAgbCPUReg[8]);
		agbCPUSwap(&g_nAgbCPUReg[R9_FIQ], &g_nAgbCPUReg[9]);
		agbCPUSwap(&g_nAgbCPUReg[R10_FIQ], &g_nAgbCPUReg[10]);
		agbCPUSwap(&g_nAgbCPUReg[R11_FIQ], &g_nAgbCPUReg[11]);
		agbCPUSwap(&g_nAgbCPUReg[R12_FIQ], &g_nAgbCPUReg[12]);
		g_nAgbCPUReg[13] = g_nAgbCPUReg[R13_FIQ];
		g_nAgbCPUReg[14] = g_nAgbCPUReg[R14_FIQ];
		if(saveState)
			g_nAgbCPUReg[17] = CPSR;
		else
			g_nAgbCPUReg[17] = g_nAgbCPUReg[SPSR_FIQ];
		break;
	case CPU_MODE_IRQ:
		g_nAgbCPUReg[13] = g_nAgbCPUReg[R13_IRQ];
		g_nAgbCPUReg[14] = g_nAgbCPUReg[R14_IRQ];
		g_nAgbCPUReg[16] = SPSR;
		if(saveState)
			g_nAgbCPUReg[17] = CPSR;
		else
			g_nAgbCPUReg[17] = g_nAgbCPUReg[SPSR_IRQ];
		break;
	case CPU_MODE_SVC:
		g_nAgbCPUReg[13] = g_nAgbCPUReg[R13_SVC];
		g_nAgbCPUReg[14] = g_nAgbCPUReg[R14_SVC];
		g_nAgbCPUReg[16] = SPSR;
		if(saveState)
			g_nAgbCPUReg[17] = CPSR;
		else
			g_nAgbCPUReg[17] = g_nAgbCPUReg[SPSR_SVC];
		break;
	case CPU_MODE_ABT:
		g_nAgbCPUReg[13] = g_nAgbCPUReg[R13_ABT];
		g_nAgbCPUReg[14] = g_nAgbCPUReg[R14_ABT];
		g_nAgbCPUReg[16] = SPSR;
		if(saveState)
			g_nAgbCPUReg[17] = CPSR;
		else
			g_nAgbCPUReg[17] = g_nAgbCPUReg[SPSR_ABT];
		break;
	case CPU_MODE_UND:
		g_nAgbCPUReg[13] = g_nAgbCPUReg[R13_UND];
		g_nAgbCPUReg[14] = g_nAgbCPUReg[R14_UND];
		g_nAgbCPUReg[16] = SPSR;
		if(saveState)
			g_nAgbCPUReg[17] = CPSR;
		else
			g_nAgbCPUReg[17] = g_nAgbCPUReg[SPSR_UND];
		break;
	default:
		TRL_ERROR("Unsupported CPU mode\n");
		break;
	}
	g_nAgbCPUReg[REG_CPUMODE] = mode;
	agbCPUUpdateFlags();
	agbCPUUpdateCPSR();	
}

/** @brief Emu the swi call */
extern "C" void agbCPUSWI_NOPRE(u32 swi_no)
{
	if(!g_nAgbThumbState)
		swi_no >>=16;

	u32 pc = g_nAgbCPUReg[15];
	u32 saveThumbState = g_nAgbThumbState;
	agbCPUSwitchMode(CPU_MODE_SVC, 1);
	if(saveThumbState)
		g_nAgbCPUReg[14] = pc - 2;
	else
		g_nAgbCPUReg[14] = pc - 4;
	g_nAgbCPUReg[15] = 0x08;
	g_nAgbThumbState = 0;
	g_bAgbIrqDisable = 1;	
}

/** @brief Emu the swi call */
void agbCPUSWI(u32 swi_no)
{
	if(!g_nAgbThumbState)
		swi_no >>=16;

	u32 pc = g_nAgbCPUReg[15];
	u32 saveThumbState = g_nAgbThumbState;
	agbCPUSwitchMode(CPU_MODE_SVC, 1);
	if(saveThumbState)
		g_nAgbCPUReg[14] = pc - 2;
	else
		g_nAgbCPUReg[14] = pc - 4;
	g_nAgbCPUReg[15] = 0x08;
	g_nAgbThumbState = 0;
	g_bAgbIrqDisable = 1;
	//agbCPUUpdateCPSR();
	ARM_FIRST_PREFETCH
}
