/**
 * @file trlTrace.cpp
 * @author Zhfang
 * @date 2011.02.12
 * @brief TRL Emulate For PC - Trace Module
 */
#include "..\trlTrace.h"
#include "..\trlDebug.h"
#include "..\CGB\cgbCard.h"
/** @name Macro Define */
//@{
#define TRL_TRACE_SOUND_MAIN 0
#define TRL_TRACE_SOUND_DETAL 1
#define TRL_TRACE_CPURUN 1
//@}

#if TRL_TRACETOOL

/** @name Global Variable */
//@{
u32 trlTrace_Ticks = 0;
u32 trlTrace_Ticks_Frame = 0;
u32 trlTrace_Ticks_Timer = 0;
u32 trlTrace_Ticks_Seg = 0;
//sound detail
u32 trlTraceSnd_Ct = 0;
u32 trlTraceSnd_CTFrame = 0;
u32 trlTraceSnd_CtTimer = 0;
u32 trlTraceSnd_CtSweep = 0;
u32 trlTraceSnd_CtSeg = 0;
u32 trlTraceSnd_CtSegSkip = 0;

u32 trlTrace_Tm_Ct = 0;

u32 trlTrace_Timer_Ct = 7;
///////
u32 trlTraceSndDetailFlag = 0;

u32 trlTraceSndCPUFlag = 0;
/////////////
u32 trlTrace_Flag_SegEnd = 0;

u32 trlTraceCPULogFlag = 0;
u32 trlTraceCPULogFlag1 = 0;
//@}

extern u8*	g_pCgbWRAM;

u32 writect = 0;
u32 readct = 0;

void trlTraceWRCt()
{
	NN_LOG("W %d R %d T %d\n", writect, readct, writect+readct);
}
//g_pCgbWRAM[0x1000*5 + 0xf19]

void trlTraceCPUReset();
void trlTraceReset()
{
	trlTraceTickReset();
	trlTraceCPUReset();
}

/** @brief Trace Tool init */
void trlTraceInit()
{
	trlTraceReset();
}

void trlTraceFrameBegin()
{
	writect = 0;
	readct = 0;
	//NN_LOG("Frame Begin: trlTraceSnd_CTFrame = %d trlTraceSnd_CtTimer = %d trlTrace_Ticks_Timer = %d trlTrace_Ticks_Frame = %d\n", trlTraceSnd_CTFrame, trlTraceSnd_CtTimer, trlTrace_Ticks_Timer, trlTrace_Ticks_Frame);
}

void trlTraceCPUFirstRunReset();
void trlTraceFrameEnd()
{	
	extern s32 g_nNesFrameLogCt;
	g_nNesFrameLogCt++;
	//NN_LOG("Frame End..: trlTrace_Ticks_Frame = %d  \n", trlTrace_Ticks_Frame);
	{
		//u8 cgbMemRead8(u16 nAddr);
		//NN_LOG("cgbMemRead8 0x9f19 = 0x%x\n", cgbMemRead8(0x9f19));
	}
	trlTraceSnd_CTFrame = 0;
	trlTrace_Ticks_Frame = 0;
	trlTraceCPUFirstRunReset();
}

void trlTraceTickReset()
{
	trlTrace_Ticks = 0;
}
void trlTraceTickAdd(u32 addticks)
{
	trlTrace_Ticks += addticks;
	trlTrace_Ticks_Frame += addticks;
	trlTrace_Ticks_Timer += addticks;
	trlTrace_Ticks_Seg += addticks;

	if(trlTrace_Flag_SegEnd == 1)
	{
		trlTrace_Flag_SegEnd = 0;
		trlTraceSnd_CtSeg = 0;
		trlTrace_Ticks_Seg = 0;
	}
}


void trlTraceSoundMainLog(char *str)
{
#if TRL_TRACE_SOUND_MAIN == 0
	return;
#endif
	NN_LOG(str);
}
void trlTraceSoundMainLogv2(char *str,u32 v1, u32 v2)
{
#if TRL_TRACE_SOUND_MAIN == 0
	return;
#endif
	NN_LOG(str, v1,v2);
}

void trlTraceSoundDetailLog(u32 cputicks)
{
	//NN_LOG("trlTraceSnd_Ct = %8d, trlTrace_Ticks = %8d, ", trlTraceSnd_Ct, trlTrace_Ticks + cputicks);
	NN_LOG("trlTraceSnd_CTFrame = %8d, trlTrace_Ticks_Frame = %8d, ", trlTraceSnd_CTFrame, trlTrace_Ticks_Frame + cputicks);
	NN_LOG("trlTraceSnd_CtTimer = %8d, trlTrace_Ticks_Timer = %8d, ", trlTraceSnd_CtTimer, trlTrace_Ticks_Timer + cputicks);
	NN_LOG("trlTraceSnd_CtSeg = %8d, trlTrace_Ticks_Seg = %8d, ", trlTraceSnd_CtSeg, trlTrace_Ticks_Seg + cputicks);
	NN_LOG("trlTraceSnd_CtSegSkip = %8d  total = %8d, ",trlTraceSnd_CtSegSkip, trlTraceSnd_CtSegSkip + trlTraceSnd_CtSeg );	
	//NN_LOG("trlTraceSnd_CtSweep = %8d", trlTraceSnd_CtSweep);
	NN_LOG("\n");
}

void trlTraceSoundDetailTryMakeSample()
{
}

void trlTraceSoundDetailMakeSample()
{
	trlTraceSnd_Ct++;
	trlTraceSnd_CTFrame++;
	trlTraceSnd_CtTimer++;
	trlTraceSnd_CtSweep++;
	trlTraceSnd_CtSeg++;
#if TRL_TRACE_SOUND_DETAL
	if(trlTraceSndDetailFlag)
	{
		//if((trlTraceSnd_CTFrame%64) == 0 || trlTraceSnd_CTFrame > 720)
		if(trlTraceSnd_CtTimer < 20 || trlTraceSnd_CtTimer > 650)
		{
			//NN_LOG("Sound Sample: trlTraceSnd_CTFrame = %d trlTraceSnd_CtTimer = %d trlTraceSnd_CtSeg = %d trlTrace_Ticks_Seg = %d trlTrace_Ticks_Timer = %d trlTrace_Ticks_Frame = %d\n", trlTraceSnd_CTFrame, trlTraceSnd_CtTimer, trlTraceSnd_CtSeg, trlTrace_Ticks_Seg, trlTrace_Ticks_Timer, trlTrace_Ticks_Frame);			
		}

	}
#endif
}

void trlTraceSoundDetailMakeSampleSkip(u32 n)
{
	trlTraceSnd_CtSegSkip += n;
	NN_LOG("Sound Skip.: trlTraceSnd_CtSegSkip = %d\n",trlTraceSnd_CtSegSkip);
}

void trlTraceSoundDetailWriteReg(u32 addr, u32 data)
{
	//nes
	if(0)
	{
		if(addr == 0x4015)
		{
			extern u32 pc32;			
			NN_LOG("Sound Write: pc32 =%08lx %08lx %02x\n", pc32, addr, data);
		}
		if(addr >= 0x4004 && addr <= 0x4007)
		{
			extern u32 pc32;			
			NN_LOG("Sound Write: pc32 =%08lx %08lx %02x\n", pc32, addr, data);
		}
		if(addr >= 0 && addr <= 3)
		{
			extern u32 pc32;
			NN_LOG("Pallte Write: pc32 =%08lx %08lx %02x\n", pc32, addr, data);
		}
		
	}
	if(0)
	{
		if(addr >= 0x47 && addr <= 0x49)
		{
			extern u32 pc32;
			NN_LOG("Pallte Write: pc32 =%08lx %08lx %02x\n", pc32, addr, data);
		}
		if(addr >= 0x4A && addr <= 0x4B)
		{
			extern u32 pc32;
			NN_LOG("Display Write: pc32 =%08lx %08lx %02x\n", pc32, addr, data);
		}
	}
#if TRL_TRACE_SOUND_DETAL
	//if((addr >=0x10 && addr <=0x14))	
	if((addr >=0x16 && addr <=0x19))
	//if((addr >=0x1A && addr <=0x1E))
	//if((addr >=0x20 && addr <=0x23))
	//if(addr == 0x26 || addr == 0x25)
	if(0)
	{
		extern s32 g_nCgbCpuEventTicks;
		extern s32 g_nCgbCpuTicks;
		extern u32 pc32;
		void trlTraceCPULOG();
		NN_LOG("Sound Write: pc32 =%08lx %08lx %02x ", pc32, addr, data);
		//trlTraceCPULOG();
		trlTraceSoundDetailLog(g_nCgbCpuTicks);
		g_nCgbCpuEventTicks = g_nCgbCpuTicks;		
	}
	if((addr >=0x4000 && addr <=0x4003))
	{
		extern u32 pc32;
		//NN_LOG("Sound Write: pc32 =%08lx %08lx %02x  trlTrace_Ticks_Frame = %d\n", pc32, addr, data, trlTrace_Ticks_Frame);
	}
#endif
}

void trlTraceSoundDetallSweepFreq(u32 freq)
{
#if TRL_TRACE_SOUND_DETAL
	//NN_LOG("Sound Event: freq = %d -(%d)trlTraceSnd_CtSweep = %d\n", freq, 4194304/32/(2048-freq), trlTraceSnd_CtSweep);
	trlTraceSnd_CtSweep = 0;
#endif
}
//////////////
//timer
void trlTraceTimer()
{
#if TRL_TRACE_SOUND_DETAL
	//if(trlTraceSndDetailFlag)
	{
		//NN_LOG("Timer Event: ");
		//trlTraceSoundDetailLog(0);
	}
	trlTrace_Ticks_Timer = 0;
	trlTraceSnd_CtTimer = 0;
	trlTrace_Tm_Ct = 0;

	trlTrace_Timer_Ct++;
	if(trlTrace_Timer_Ct == 6)
	{
		//trlTraceSndCPUFlag = 1;
	}
#endif
}

void trlTraceTimerDetail()
{
	trlTrace_Tm_Ct++;
	if(trlTrace_Tm_Ct < 2 || trlTrace_Tm_Ct> 255)
	{
		//NN_LOG("Timer Event: trlTrace_Tm_Ct = %4d,", trlTrace_Tm_Ct);
		//trlTraceSoundDetailLog(0);
	}
}

/////////////////
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
//@}

/** @name Global Variable */
//@{
extern s32					g_nCgbCpuEventTicks;					///< Next Event Ticks
extern s32					g_nCgbCpuTicks;							///< CPU Run Ticks
extern u8					g_nCgbCpuReg8[8];						///< CPU 8 Bit Registers
extern u16					g_nCgbCpuRegPC;							///< CPU PC Register
extern u16					g_nCgbCpuRegSP;							///< CPU SP Register
extern u8					g_nCgbCpuTemp8;							///< CPU 8 Bit Temp Value
extern u16					g_nCgbCpuTemp16;						///< CPU 16 Bit Temp Vajlue
extern u32					g_nCgbCpuIME;							///< Interrupt Master Enable Flag (W)
extern u32					g_nCgbCpuState;							///< CPU State
extern u8*					g_pCgbCpuPC;							///< CPU PC Pointer
extern u32					g_nCgbROMBank;
//@}
#define LASTINST_NUM 0x1000
u32 lastinst[LASTINST_NUM];
u32 lastinstct = 0;
u8  valuetable[LASTINST_NUM];
u32 pc32;
u32 logdelay = 0;

u32 runtimes[1024*1024*4];
u32 firstrun[1024*1024];
u32 firstrunct = 0;

void trlTraceCPULOG()
{
	//if(trlTraceCPULogFlag && trlTraceCPULogFlag1)
	{
		NN_LOG("pc32 = 0x%x AF:0x%-4x BC:0x%-4x DE:0x%-4x HL:0x%-4x\n",
			pc32, AF, BC, DE, HL);
	}
}


void trlTraceMemRead(u32 addr, u32 value)
{
	readct = 0;
	u32 realaddr = (&g_pCgbCurROM[addr-0x4000] - g_pCgbROM);
	if(realaddr == 0xfe894)
	{
		//NN_LOG("Mem Read: pc32 = 0x%x\n", pc32);
	}
	if(addr == 0xced2)
	{
		//if(pc32 != 0x407 && pc32 != 0x236 && pc32 != 0x1b480 && pc32 != 0x1b48e)
		//	NN_LOG("Mem Read: pc32 = 0x%x\n", pc32);
	}
	if(addr == 0x4016)
	{		
		NN_LOG("Mem Read: pc32 = 0x%x\n", pc32);
	}
	if(addr == 0x4017)
	{		
		NN_LOG("Mem Read: pc32 = 0x%x\n", pc32);
	}
	if(addr == 0xc701)
	{		
		//NN_LOG("0xc701 Mem ____Read___: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	}
}

void trlTraceMemWrite(u32 addr, u32 value)
{
	writect++;
	
	
	if(addr == 0xFFA6)
	{
		//trlTraceCPULOG();
		NN_LOG("0xFFA6--##############- Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	}
	
	if(addr == 0xFF47)
	{
		//trlTraceCPULOG();
		NN_LOG("0xC504 Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	
	if(addr == 0x0130)
	{
		//trlTraceCPULOG();
		NN_LOG("0x0130 Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	if(addr == 0x0131)
	{
		//trlTraceCPULOG();
		NN_LOG("0x0131 Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	if(addr == 0x003e)
	{
		//trlTraceCPULOG();
		NN_LOG("0x003e Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	if(addr == 0x06d0)
	{
		//trlTraceCPULOG();
		NN_LOG("0x06d0 Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	if(addr == 0x2006&&value==0x62)
	{
		//trlTraceCPULOG();
	//	NN_LOG("0x2006 Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	if(addr == 0x2007&&value==0x00)
	{
		//trlTraceCPULOG();
	//	NN_LOG("0x2007 00 Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	if(addr == 0x2007&&value==0xBB)
	{
		//trlTraceCPULOG();
	//	NN_LOG("0x2007 bb Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x   AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\r\n", pc32, addr, value,AF,BC,DE,HL,SP);
	}
	
	//if(addr == 0x58)
	//{
	//	//trlTraceCPULOG();
	//	NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	//}
	//if(addr == 0xB)
	//{
	//	//trlTraceCPULOG();
	//	NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	//}
	//if(addr == 0x2001)
	//{
	//	//trlTraceCPULOG();
	//	//NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	//}
	//if(addr == 0x711)
	//{
	//	//trlTraceCPULOG();
	//	//NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	//}
	//if(addr == 0x0089)
	//{
	//	extern u16					g_nNesGrpPalTable[0x40];
	//	//NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
	//	if(pc32 == 0x37625)
	//	{
	//		//g_nNesGrpPalTable[0x16] = 0x0000;
	//		//g_nNesGrpPalTable[0x0F] = 0xD941;
	//	}
	//}
	/*if(addr == 0xC280)
		NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	*/
	//if(addr >=0xC280 && addr <=0xC28F)
	//	NN_LOG("Mem Write: pc32 = 0x%x addr = 0x%x value = 0x%x\n", pc32, addr, value);	
}

void trlTraceCPUReset()
{
	for(int i=0;i<1024*1024*4;i++)
		runtimes[i] = 0;
	firstrunct = 0;
}

void trlTraceCPUFirstRunReset()
{
	firstrunct = 0;
}

u8 cgbMemRead8(u16 nAddr);
u16 cgbMemRead16(u16 nAddr);
extern u8							g_nNesCpuRegA;								///< CPU Registe A
extern u8							g_nNesCpuRegX;								///< CPU Registe X
extern u8							g_nNesCpuRegY;								///< CPU Registe Y
extern u8							g_nNesCpuRegS;								///< CPU Registe S
extern u8							g_nNesCpuRegP;								///< CPU Registe P
extern u16							g_nNesCpuRegPC;								///< CPU Registe PC
extern u8*							g_pNesCpuPC;								///< CPU PC Pointer
extern u8*							g_pNesPRGROM;								///< PRG Cartridge

void trlTraceCPULOGNES()
{
	//if(trlTraceCPULogFlag && trlTraceCPULogFlag1)
	{
		NN_LOG("pc32 = 0x%x(0x%x) A:0x%-4x X:0x%-4x Y:0x%-4x S:0x%-4x\n",
			pc32, g_nNesCpuRegPC, g_nNesCpuRegA, g_nNesCpuRegX, g_nNesCpuRegY, g_nNesCpuRegS);
	}
}

void trlTraceCPURUN_NES()
{	
	pc32 = (g_pNesCpuPC - g_pNesPRGROM);

	lastinst[lastinstct] = (pc32);		
	lastinstct++;
	if(lastinstct >= LASTINST_NUM)
		lastinstct = 0;
	if(pc32 == 0x715F)
	{		
		//trlTraceCPULOGNES();
	}
	if(pc32 == 0x154bb)
	{	
		//trlTraceCPULOGNES();
	}
	if(pc32 == 0x36005)
	{
		//NN_LOG("Begin\n");
		//trlTraceCPULOGNES();
	}

}

void trlTracePushStack(u32 value)
{
	//if(value == 0x6894)
	//	trlTraceCPULOG();
}
void trlTrackPopStack()
{
}
void trlTraceCPURun()
{
#if TRL_TRACE_CPURUN == 0
	return;
#endif
	
	//if(g_pCgbCpuPC == 0)
	//	g_pCgbCpuPC = g_pCgbCpuPC;


	
	if(PC<0x8000)
		pc32 = (PC<0x4000)?PC:g_nCgbROMBank*0x4000+PC-0x4000;
	else
		pc32 = PC;
	lastinst[lastinstct] = (pc32);		
	lastinstct++;
	if(lastinstct >= LASTINST_NUM)
		lastinstct = 0;

	if(runtimes[pc32] == 0)
	{
		firstrun[firstrunct] = pc32;
		firstrunct++;
	}
	runtimes[pc32] ++;	
	if(pc32 == 0x154c0)// && pc32 <= 0x191A)
	{
		//trlTraceCPULOG();
		NN_LOG("set e4 -----------------PC32 = 0x%x\n", pc32);	
		//logdelay = 20;
	}
	if(pc32 == 0x154BB)// && pc32 <= 0x191A)
	{
		//trlTraceCPULOG();
		NN_LOG("set 00 #################PC32 = 0x%x\n", pc32);	
		//logdelay = 20;
	}
	if(trlTraceSndCPUFlag == 1)
	{
		/*if(pc32 >= 0xE8E7 && pc32 <= 0xE8EF)
		{
			NN_LOG("CPU.. EVENT:  pc32 =%08lx", pc32);
			extern s32 g_nCgbCpuTicks;
			trlTraceSoundDetailLog(g_nCgbCpuTicks);
		}*/
		if(pc32 == 0x50 || pc32 == 0x5F)
		{
			NN_LOG("CPU.. EVENT:  pc32 =%08lx", pc32);
			extern s32 g_nCgbCpuTicks;
			trlTraceSoundDetailLog(g_nCgbCpuTicks);
		}
	}
	if(cgbMemRead16(SP) == 0x656)
	{
		pc32 = pc32;
	}
	if(cgbMemRead16(SP+2) == 0x656)
	{
		pc32 = pc32;
	}
	if(pc32 == 0x90)
	{
		//A = 0x36;
	}

	if(pc32 == 0x1021B)// && pc32 <= 0x191A)
	{
		//trlTraceCPULOG();
		//NN_LOG("PC32 = 0x%x\n", pc32);	
		//logdelay = 20;
	}
	if(pc32 == 0x1022E)// && pc32 <= 0x191A)
	{
		//trlTraceCPULOG();
		//NN_LOG("PC32 = 0x%x\n", pc32);	
		//logdelay = 20;
	}
	
	if(pc32 == 0x10214)// && pc32 <= 0x191A)
	{
		//NN_LOG("---%x %x %x\n", cgbMemRead8(0xc392),cgbMemRead8(0xc3A4),cgbMemRead8(0xc3A2));
		//trlTraceCPULOG();
		//NN_LOG("PC32 = 0x%x\n", pc32);	
		//logdelay = 20;
	}
	if(pc32 == 0x154A8)
	{
		trlTraceCPULOG();
		//NN_LOG("PC32 = 0x%x\n", pc32);	
		//logdelay = 5;
	}
	if(pc32 == 0x14012)
	{
		//trlTraceCPULOG();
		//NN_LOG("PC32 = 0x%x\n", pc32);	
		//logdelay = 5;
	}
	if(pc32 == 0x675)
	{
		//trlTraceCPULOG();
		//NN_LOG("PC32 = 0x%x\n", pc32);	
		//hlogdelay = 20;
	}
	if(pc32 >= 0x272d && pc32 <= 0x2771)
	{
		//trlTraceCPULOG();
		//logdelay = 20;
	}
	if(pc32 == 0x3AA5)
	{
		//trlTraceCPULOG();
		//logdelay = 5;
	}
	if(pc32 == 0x150)
	{
		//trlTraceCPULOG();
		//logdelay = 20;
	}


	if(logdelay > 0)
	{
		logdelay--;
		NN_LOG("PC32 = 0x%x  PC = 0x%x HL = 0x%x  DE = 0x%x\n", pc32, PC, HL, DE);
	}	
}
#endif


#if TRL_HIO
#include <nn/assert.h>
#include <nn/hio.h>
#include <cstring>
#include <string.h>

const char sampleFileName[] =  "d:/hio.txt";

void trlTraceHio(char *str)
{
	nn::Result result;
    nn::hio::CTR::HostFile file;
	
	result = file.Open(sampleFileName,
        nn::hio::CTR::HostFile::ACCESS_MODE_READ_WRITE,
        nn::hio::HostFile::OPEN_DISP_OPEN_EXISTING);
    if ( result.IsFailure() )
    {
        NN_LOG(" -> Failed to create file.\n");
    }
    else
	{
		file.Seek(0, nn::hio::CTR::HostFile::SEEK_TYPE_END);
		file.Write(str, strlen(str) + 1);
		file.Close();
	}
}

void trlTraceHioInit()
{
	nn::hio::CTR::Initialize(trlMemAllocDevice(80 * 1024 + 32));
}
void trlTraceHioRelease()
{
	nn::hio::CTR::Finalize();
}
#endif

#include "../NES/nesGlobal.h"
#include "../NES/nesGraphic.h"
#include "../NES/nesSound.h"
#include "../NES/nesCard.h"
#include "../NES/nesInput.h"
u8 GetMem(u16 nAddr)
{
	switch(nAddr >> 13)
	{
	case 0x0:				// 0000h-07FFh   Internal 2K Work RAM (mirrored to 800h-1FFFh)
		return g_pNesWRAM[nAddr&0x7FF];
	case 0x1:				// 2000h-2007h   Internal PPU Registers (mirrored to 2008h-3FFFh)
		return 0;
		//return nesGrpRegRead(nAddr&0x7);
	case 0x2:		
		if(nAddr<0x4018)	// 4000h-4017h   Internal APU Registers
		{
			return 0;
			//switch(nAddr)
			//{
			//case 0x4015:		// 4015h - DMC/IRQ/length counter status
			//	return ((( SoundE.interrupt ) << 7) | (( SoundE.activity ) << 4) | (( SoundD.activity ) << 3) | (( SoundC.activity ) << 2) | (( SoundB.activity ) << 1) | (( SoundA.activity ) << 0));
			//case 0x4016:		// 4016h - Joypad #1/3
			//	return nesInputRegisterRead(0) | 0x40 | g_nNesInputMic;
			//case 0x4017:		// 4017h - Joypad #2/4
			//	return nesInputRegisterRead(1);
			//default:
			//	return 0x00;
			//}
		}
		else if(nesCardRegisterRead)	// 4018h-5FFFh   Cartridge Expansion Area almost 8K
			return nesCardRegisterRead(nAddr);
		return 0xFF;
	case 0x3:				// 6000h-7FFFh   Cartridge SRAM Area 8K
		if(g_nNesCardSRAMEnable==1)
			return g_pNesSRAMBank[nAddr&0x1FFF];
		else
			return 0xFF;
	case 0x4:				// 8000h-9FFFh   Cartridge PRG-ROM Area 8K
		return g_pNesPRGBank[0][nAddr&0x1FFF];
	case 0x5:				// A000h-BFFFh   Cartridge PRG-ROM Area 8K
		return g_pNesPRGBank[1][nAddr&0x1FFF];
	case 0x6:				// C000h-DFFFh   Cartridge PRG-ROM Area 8K
		return g_pNesPRGBank[2][nAddr&0x1FFF];
	case 0x7:				// E000h-FFFFh   Cartridge PRG-ROM Area 8K
		return g_pNesPRGBank[3][nAddr&0x1FFF];
	}
	return 0xFF;

}


#define uint8 u8
#define uint16 u16

const uint8 opsize[256] = {
/*0x00*/	1,2,0,0,0,2,2,0,1,2,1,0,0,3,3,0,
/*0x10*/	2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0,
/*0x20*/	3,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0,
/*0x30*/	2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0,
/*0x40*/	1,2,0,0,0,2,2,0,1,2,1,0,3,3,3,0,
/*0x50*/	2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0,
/*0x60*/	1,2,0,0,0,2,2,0,1,2,1,0,3,3,3,0,
/*0x70*/	2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0,
/*0x80*/	0,2,0,0,2,2,2,0,1,0,1,0,3,3,3,0,
/*0x90*/	2,2,0,0,2,2,2,0,1,3,1,0,0,3,0,0,
/*0xA0*/	2,2,2,0,2,2,2,0,1,2,1,0,3,3,3,0,
/*0xB0*/	2,2,0,0,2,2,2,0,1,3,1,0,3,3,3,0,
/*0xC0*/	2,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0,
/*0xD0*/	2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0,
/*0xE0*/	2,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0,
/*0xF0*/	2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0
};

s32 g_nNesFrameLogCt = 0;
#define NES_A					g_nNesCpuRegA
#define NES_X					g_nNesCpuRegX
#define NES_Y					g_nNesCpuRegY
#define NES_S					g_nNesCpuRegS
char *DisassembleData(int addr, u8 *opcode);
void WriteDisassembleFile(FILE *fp)
{
	static FILE *sfp = NULL;
	static s32 g_nNesFrameLogCtLast = -1;
	if(g_nNesFrameLogCtLast != g_nNesFrameLogCt)
	{
		g_nNesFrameLogCtLast = g_nNesFrameLogCt;

		if(sfp != NULL)
		{
			fclose(sfp);
		}
		char filename[50];
		sprintf(filename, "log/fame_%05d.txt", g_nNesFrameLogCt);
		sfp = fopen(filename, "w");
	}


	fprintf(fp, "%-43sA:%02X X:%02X Y:%02X S:%02X Frame:%5d(%5d) g_nNesGrpLines:%5d g_nNesGrpTicks:%5d  g_nNesCpuTicks:%5d g_nNesCpuEventTicks = %5d\n", DisassembleData(g_nNesCpuRegPC, g_pNesCpuPC), NES_A, NES_X, NES_Y, NES_S, g_nNesFrameLogCt, g_sEmuShellBuffer.nFrames, g_nNesGrpLines, g_nNesGrpTicks, g_nNesCpuTicks, g_nNesCpuEventTicks);
	fprintf(sfp, "%-43sA:%02X X:%02X Y:%02X S:%02X\n", DisassembleData(g_nNesCpuRegPC, g_pNesCpuPC), NES_A, NES_X, NES_Y, NES_S);
}
char *Disassemble(int addr, uint8 *opcode);
char *DisassembleData(int addr, uint8 *opcode) {
	static char str[64]={0},chr[25]={0};
	char *c;
	int size,j;

	sprintf(str, "$%04X:", addr);
	if ((size = opsize[opcode[0]]) == 0) {
		sprintf(chr, "%02X        UNDEFINED", opcode[0]);
		strcat(str,chr);
	}
	else {
		if ((addr+size) > 0x10000) {
			sprintf(chr, "%02X        OVERFLOW", opcode[0]);
			strcat(str,chr);
		}
		else {
			for (j = 0; j < size; j++) {
				sprintf(chr, "%02X ", opcode[j]);
				addr++;
				strcat(str,chr);
			}
			while (size < 3) {
				strcat(str,"   "); //pad output to align ASM
				size++;
			}
			strcat(strcat(str," "),Disassemble(addr,opcode));
		}
	}
	//if ((c=strchr(str,'='))) *(c-1) = 0;
	//if ((c=strchr(str,'@'))) *(c-1) = 0;
	return str;
}


#define relative(a) { \
			if (((a)=opcode[1])&0x80) (a) = addr-(((a)-1)^0xFF); \
			else (a)+=addr; \
		}
		#define absolute(a) { \
			(a) = opcode[1] | opcode[2]<<8; \
		}
		#define zpIndex(a,i) { \
			(a) = opcode[1]+(i); \
		}
		#define indirectX(a) { \
			(a) = (opcode[1]+RX)&0xFF; \
			(a) = GetMem((a)) | (GetMem((a)+1))<<8; \
		}
		#define indirectY(a) { \
			(a) = GetMem(opcode[1]) | (GetMem(opcode[1]+1))<<8; \
			(a) += RY; \
		}

char *Disassemble(int addr, uint8 *opcode) {
	static char str[64]={0},chr[5]={0};
	uint16 tmp,tmp2;

	//these may be replaced later with passed-in values to make a lighter-weight disassembly mode that may not query the referenced values
	#define RX (g_nNesCpuRegX)
	#define RY (g_nNesCpuRegY)

	switch (opcode[0]) {
		#define relative(a) { \
			if (((a)=opcode[1])&0x80) (a) = addr-(((a)-1)^0xFF); \
			else (a)+=addr; \
		}
		#define absolute(a) { \
			(a) = opcode[1] | opcode[2]<<8; \
		}
		#define zpIndex(a,i) { \
			(a) = opcode[1]+(i); \
		}
		#define indirectX(a) { \
			(a) = (opcode[1]+RX)&0xFF; \
			(a) = GetMem((a)) | (GetMem((a)+1))<<8; \
		}
		#define indirectY(a) { \
			(a) = GetMem(opcode[1]) | (GetMem(opcode[1]+1))<<8; \
			(a) += RY; \
		}


		//odd, 1-byte opcodes
		case 0x00: strcpy(str,"BRK"); break;
		case 0x08: strcpy(str,"PHP"); break;
		case 0x0A: strcpy(str,"ASL"); break;
		case 0x18: strcpy(str,"CLC"); break;
		case 0x28: strcpy(str,"PLP"); break;
		case 0x2A: strcpy(str,"ROL"); break;
		case 0x38: strcpy(str,"SEC"); break;
		case 0x40: strcpy(str,"RTI"); break;
		case 0x48: strcpy(str,"PHA"); break;
		case 0x4A: strcpy(str,"LSR"); break;
		case 0x58: strcpy(str,"CLI"); break;
		case 0x60: strcpy(str,"RTS"); break;
		case 0x68: strcpy(str,"PLA"); break;
		case 0x6A: strcpy(str,"ROR"); break;
		case 0x78: strcpy(str,"SEI"); break;
		case 0x88: strcpy(str,"DEY"); break;
		case 0x8A: strcpy(str,"TXA"); break;
		case 0x98: strcpy(str,"TYA"); break;
		case 0x9A: strcpy(str,"TXS"); break;
		case 0xA8: strcpy(str,"TAY"); break;
		case 0xAA: strcpy(str,"TAX"); break;
		case 0xB8: strcpy(str,"CLV"); break;
		case 0xBA: strcpy(str,"TSX"); break;
		case 0xC8: strcpy(str,"INY"); break;
		case 0xCA: strcpy(str,"DEX"); break;
		case 0xD8: strcpy(str,"CLD"); break;
		case 0xE8: strcpy(str,"INX"); break;
		case 0xEA: strcpy(str,"NOP"); break;
		case 0xF8: strcpy(str,"SED"); break;

		//(Indirect,X)
		case 0x01: strcpy(chr,"ORA"); goto _indirectx;
		case 0x21: strcpy(chr,"AND"); goto _indirectx;
		case 0x41: strcpy(chr,"EOR"); goto _indirectx;
		case 0x61: strcpy(chr,"ADC"); goto _indirectx;
		case 0x81: strcpy(chr,"STA"); goto _indirectx;
		case 0xA1: strcpy(chr,"LDA"); goto _indirectx;
		case 0xC1: strcpy(chr,"CMP"); goto _indirectx;
		case 0xE1: strcpy(chr,"SBC"); goto _indirectx;
		_indirectx:
			indirectX(tmp);
			sprintf(str,"%s ($%02X,X) @ $%04X = #$%02X", chr,opcode[1],tmp,GetMem(tmp));
			break;

		//Zero Page
		case 0x05: strcpy(chr,"ORA"); goto _zeropage;
		case 0x06: strcpy(chr,"ASL"); goto _zeropage;
		case 0x24: strcpy(chr,"BIT"); goto _zeropage;
		case 0x25: strcpy(chr,"AND"); goto _zeropage;
		case 0x26: strcpy(chr,"ROL"); goto _zeropage;
		case 0x45: strcpy(chr,"EOR"); goto _zeropage;
		case 0x46: strcpy(chr,"LSR"); goto _zeropage;
		case 0x65: strcpy(chr,"ADC"); goto _zeropage;
		case 0x66: strcpy(chr,"ROR"); goto _zeropage;
		case 0x84: strcpy(chr,"STY"); goto _zeropage;
		case 0x85: strcpy(chr,"STA"); goto _zeropage;
		case 0x86: strcpy(chr,"STX"); goto _zeropage;
		case 0xA4: strcpy(chr,"LDY"); goto _zeropage;
		case 0xA5: strcpy(chr,"LDA"); goto _zeropage;
		case 0xA6: strcpy(chr,"LDX"); goto _zeropage;
		case 0xC4: strcpy(chr,"CPY"); goto _zeropage;
		case 0xC5: strcpy(chr,"CMP"); goto _zeropage;
		case 0xC6: strcpy(chr,"DEC"); goto _zeropage;
		case 0xE4: strcpy(chr,"CPX"); goto _zeropage;
		case 0xE5: strcpy(chr,"SBC"); goto _zeropage;
		case 0xE6: strcpy(chr,"INC"); goto _zeropage;
		_zeropage:
		// ################################## Start of SP CODE ###########################
		// Change width to %04X
			sprintf(str,"%s $%04X = #$%02X", chr,opcode[1],GetMem(opcode[1]));
		// ################################## End of SP CODE ###########################
			break;

		//#Immediate
		case 0x09: strcpy(chr,"ORA"); goto _immediate;
		case 0x29: strcpy(chr,"AND"); goto _immediate;
		case 0x49: strcpy(chr,"EOR"); goto _immediate;
		case 0x69: strcpy(chr,"ADC"); goto _immediate;
		//case 0x89: strcpy(chr,"STA"); goto _immediate;  //baka, no STA #imm!!
		case 0xA0: strcpy(chr,"LDY"); goto _immediate;
		case 0xA2: strcpy(chr,"LDX"); goto _immediate;
		case 0xA9: strcpy(chr,"LDA"); goto _immediate;
		case 0xC0: strcpy(chr,"CPY"); goto _immediate;
		case 0xC9: strcpy(chr,"CMP"); goto _immediate;
		case 0xE0: strcpy(chr,"CPX"); goto _immediate;
		case 0xE9: strcpy(chr,"SBC"); goto _immediate;
		_immediate:
			sprintf(str,"%s #$%02X", chr,opcode[1]);
			break;

		//Absolute
		case 0x0D: strcpy(chr,"ORA"); goto _absolute;
		case 0x0E: strcpy(chr,"ASL"); goto _absolute;
		case 0x2C: strcpy(chr,"BIT"); goto _absolute;
		case 0x2D: strcpy(chr,"AND"); goto _absolute;
		case 0x2E: strcpy(chr,"ROL"); goto _absolute;
		case 0x4D: strcpy(chr,"EOR"); goto _absolute;
		case 0x4E: strcpy(chr,"LSR"); goto _absolute;
		case 0x6D: strcpy(chr,"ADC"); goto _absolute;
		case 0x6E: strcpy(chr,"ROR"); goto _absolute;
		case 0x8C: strcpy(chr,"STY"); goto _absolute;
		case 0x8D: strcpy(chr,"STA"); goto _absolute;
		case 0x8E: strcpy(chr,"STX"); goto _absolute;
		case 0xAC: strcpy(chr,"LDY"); goto _absolute;
		case 0xAD: strcpy(chr,"LDA"); goto _absolute;
		case 0xAE: strcpy(chr,"LDX"); goto _absolute;
		case 0xCC: strcpy(chr,"CPY"); goto _absolute;
		case 0xCD: strcpy(chr,"CMP"); goto _absolute;
		case 0xCE: strcpy(chr,"DEC"); goto _absolute;
		case 0xEC: strcpy(chr,"CPX"); goto _absolute;
		case 0xED: strcpy(chr,"SBC"); goto _absolute;
		case 0xEE: strcpy(chr,"INC"); goto _absolute;
		_absolute:
			absolute(tmp);
			sprintf(str,"%s $%04X = #$%02X", chr,tmp,GetMem(tmp));
			break;

		//branches
		case 0x10: strcpy(chr,"BPL"); goto _branch;
		case 0x30: strcpy(chr,"BMI"); goto _branch;
		case 0x50: strcpy(chr,"BVC"); goto _branch;
		case 0x70: strcpy(chr,"BVS"); goto _branch;
		case 0x90: strcpy(chr,"BCC"); goto _branch;
		case 0xB0: strcpy(chr,"BCS"); goto _branch;
		case 0xD0: strcpy(chr,"BNE"); goto _branch;
		case 0xF0: strcpy(chr,"BEQ"); goto _branch;
		_branch:
			relative(tmp);
			sprintf(str,"%s $%04X", chr,tmp);
			break;

		//(Indirect),Y
		case 0x11: strcpy(chr,"ORA"); goto _indirecty;
		case 0x31: strcpy(chr,"AND"); goto _indirecty;
		case 0x51: strcpy(chr,"EOR"); goto _indirecty;
		case 0x71: strcpy(chr,"ADC"); goto _indirecty;
		case 0x91: strcpy(chr,"STA"); goto _indirecty;
		case 0xB1: strcpy(chr,"LDA"); goto _indirecty;
		case 0xD1: strcpy(chr,"CMP"); goto _indirecty;
		case 0xF1: strcpy(chr,"SBC"); goto _indirecty;
		_indirecty:
			indirectY(tmp);
			sprintf(str,"%s ($%02X),Y @ $%04X = #$%02X", chr,opcode[1],tmp,GetMem(tmp));
			break;

		//Zero Page,X
		case 0x15: strcpy(chr,"ORA"); goto _zeropagex;
		case 0x16: strcpy(chr,"ASL"); goto _zeropagex;
		case 0x35: strcpy(chr,"AND"); goto _zeropagex;
		case 0x36: strcpy(chr,"ROL"); goto _zeropagex;
		case 0x55: strcpy(chr,"EOR"); goto _zeropagex;
		case 0x56: strcpy(chr,"LSR"); goto _zeropagex;
		case 0x75: strcpy(chr,"ADC"); goto _zeropagex;
		case 0x76: strcpy(chr,"ROR"); goto _zeropagex;
		case 0x94: strcpy(chr,"STY"); goto _zeropagex;
		case 0x95: strcpy(chr,"STA"); goto _zeropagex;
		case 0xB4: strcpy(chr,"LDY"); goto _zeropagex;
		case 0xB5: strcpy(chr,"LDA"); goto _zeropagex;
		case 0xD5: strcpy(chr,"CMP"); goto _zeropagex;
		case 0xD6: strcpy(chr,"DEC"); goto _zeropagex;
		case 0xF5: strcpy(chr,"SBC"); goto _zeropagex;
		case 0xF6: strcpy(chr,"INC"); goto _zeropagex;
		_zeropagex:
			zpIndex(tmp,RX);
		// ################################## Start of SP CODE ###########################
		// Change width to %04X
			sprintf(str,"%s $%02X,X @ $%04X = #$%02X", chr,opcode[1],tmp,GetMem(tmp));
		// ################################## End of SP CODE ###########################
			break;

		//Absolute,Y
		case 0x19: strcpy(chr,"ORA"); goto _absolutey;
		case 0x39: strcpy(chr,"AND"); goto _absolutey;
		case 0x59: strcpy(chr,"EOR"); goto _absolutey;
		case 0x79: strcpy(chr,"ADC"); goto _absolutey;
		case 0x99: strcpy(chr,"STA"); goto _absolutey;
		case 0xB9: strcpy(chr,"LDA"); goto _absolutey;
		case 0xBE: strcpy(chr,"LDX"); goto _absolutey;
		case 0xD9: strcpy(chr,"CMP"); goto _absolutey;
		case 0xF9: strcpy(chr,"SBC"); goto _absolutey;
		_absolutey:
			absolute(tmp);
			tmp2=(tmp+RY);
			sprintf(str,"%s $%04X,Y @ $%04X = #$%02X", chr,tmp,tmp2,GetMem(tmp2));
			break;

		//Absolute,X
		case 0x1D: strcpy(chr,"ORA"); goto _absolutex;
		case 0x1E: strcpy(chr,"ASL"); goto _absolutex;
		case 0x3D: strcpy(chr,"AND"); goto _absolutex;
		case 0x3E: strcpy(chr,"ROL"); goto _absolutex;
		case 0x5D: strcpy(chr,"EOR"); goto _absolutex;
		case 0x5E: strcpy(chr,"LSR"); goto _absolutex;
		case 0x7D: strcpy(chr,"ADC"); goto _absolutex;
		case 0x7E: strcpy(chr,"ROR"); goto _absolutex;
		case 0x9D: strcpy(chr,"STA"); goto _absolutex;
		case 0xBC: strcpy(chr,"LDY"); goto _absolutex;
		case 0xBD: strcpy(chr,"LDA"); goto _absolutex;
		case 0xDD: strcpy(chr,"CMP"); goto _absolutex;
		case 0xDE: strcpy(chr,"DEC"); goto _absolutex;
		case 0xFD: strcpy(chr,"SBC"); goto _absolutex;
		case 0xFE: strcpy(chr,"INC"); goto _absolutex;
		_absolutex:
			absolute(tmp);
			tmp2=(tmp+RX);
			sprintf(str,"%s $%04X,X @ $%04X = #$%02X", chr,tmp,tmp2,GetMem(tmp2));
			break;

		//jumps
		case 0x20: strcpy(chr,"JSR"); goto _jump;
		case 0x4C: strcpy(chr,"JMP"); goto _jump;
		case 0x6C: absolute(tmp); sprintf(str,"JMP ($%04X) = $%04X", tmp,GetMem(tmp)|GetMem(tmp+1)<<8); break;
		_jump:
			absolute(tmp);
			sprintf(str,"%s $%04X", chr,tmp);
			break;

		//Zero Page,Y
		case 0x96: strcpy(chr,"STX"); goto _zeropagey;
		case 0xB6: strcpy(chr,"LDX"); goto _zeropagey;
		_zeropagey:
			zpIndex(tmp,RY);
		// ################################## Start of SP CODE ###########################
		// Change width to %04X
			sprintf(str,"%s $%04X,Y @ $%04X = #$%02X", chr,opcode[1],tmp,GetMem(tmp));
		// ################################## End of SP CODE ###########################
			break;

		//UNDEFINED
		default: strcpy(str,"ERROR"); break;

	}
	
	return str;
}