/**
* @file agbCPUCompiler
* @author zhfang
* @date 2009.12.15
* @brief AGB Emulate For CTR - Compiler for AGB Cpu
*/
#include <assert.h>
#include "..\..\\trlHeader.h"
#include "..\agbMemory.h"
#include "..\agbCPUData.h"

#include "agbCPUCmpilerGenX86.h"
#include "agbCPUCmpilerGenArm.h"


#include "agbCPUCmpData.h"
#include "agbCPUCmpilerInstThumb.h"
#include "agbCPUCmpilerInstArm.h"
#include "agbCPUCmpiler_OffLine.h"

s32 agbCPUCmpilerCmpOne(u32 nOriAddress, u32 nInst, u32 bThumb); ///<< compile a block from nOriAddress, if be successed,return result block id, if failed, return -1
s32 agbCPUCmpilerCmpBlock(u32 nOriStartAddress,u32 nOriAddress, u32 bThumb);

/** @brief Initialize Compiler */
void agbCPUCmpilerInit()
{
	memset(g_sCPUCmpData.pInstBlock, 0, sizeof(CPU_INSTRUCT_BLOCK)*INST_BLOCK_NUM);
	memset(g_sCPUCmpData.pJmpBlock, 0, sizeof(CPU_JMP_BLOCK)*INST_JMP_NUM);
	g_sCPUCmpData.nInstBlockNum = 0;
	g_sCPUCmpData.nJmpBlockNum = 0;

	g_nCmpdDebugAddressNum = 0;
	g_nCmpdEmptyLoopAddressNum = 0;

	g_bCmpdInterruptChange = 1;

	g_nCmpdForceStopAddress = 0x00000000;

	g_bCmpdCmpAll = 1;
	
	g_nCmpdCmpBlockCt = 0;
	if(g_nAgbGameTitle == AGB_TITLE_MARIOA_AMAJ)
	{		
#ifdef TRL_PLATFORM_PC
		g_nCmpdCmpBlockMax = INST_BLOCK_NUM;//190;
#else
		g_nCmpdCmpBlockMax = 0;
#endif
		g_bCmpdRuntimeCmp = 1;
	}
	else if(g_nAgbGameTitle == AGB_TITLE_CHECK323)
	{
#ifdef TRL_PLATFORM_PC
		g_nCmpdCmpBlockMax = INST_BLOCK_NUM;
#else
		g_nCmpdCmpBlockMax = 0;
#endif
		g_bCmpdRuntimeCmp = 0;
	}
	else if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
	{
#ifdef TRL_PLATFORM_PC
		g_nCmpdCmpBlockMax = INST_BLOCK_NUM;
#else
		g_nCmpdCmpBlockMax = 0;
#endif
		//g_nCmpdCmpBlockMax = 0;
		g_bCmpdRuntimeCmp = 0;
	}
	else
	{
#ifdef TRL_PLATFORM_PC
		g_nCmpdCmpBlockMax = INST_BLOCK_NUM;
#else
		g_nCmpdCmpBlockMax = 0;
#endif
		g_bCmpdRuntimeCmp = 0;
	}

#ifdef TRL_PLATFORM_PC
	g_bCmpdOffLine = 1;
#endif

#ifdef TRL_PLATFORM_CTR
	g_bCmpdOffLine = 0;
#endif

	agbCPUCmpilerOffLineInit();
	
}

/** @brief */
s32 agbCPUCmpGetBlockID(u32 nOriAddress, u32 bThumb)
{
	for(s32 i=0;i<g_sCPUCmpData.nInstBlockNum;i++)
			if(g_sCPUCmpData.pInstBlock[i].nOriAddr == nOriAddress)
				return i;
	if(g_bCmpdRuntimeCmp)
	{	
		g_nCmpdForceStopAddress = 0x00000000;
		s32 rv = agbCPUCmpilerCmpOne(nOriAddress, 0x100, bThumb);
		if(rv >= 0)
			return rv;		
	}
	else
	{
		if(g_nAgbGameTitle == AGB_TITLE_MARIOA_AMAJ)
		{
			for(int i=0;i<nFuncTable_AAMAJ_size;i++)
			{
				if(nOriAddress == pFuncTable_AAMAJ[i*2])
				{
					g_nCmpdForceStopAddress = pFuncTable_AAMAJ[i*2+1];
					s32 rv = agbCPUCmpilerCmpOne(nOriAddress, 0x100, bThumb);
					if(rv >= 0)
						return rv;
				}
			}
		}
		else if(g_nAgbGameTitle == AGB_TITLE_CHECK323)
		{
			for(int i=0;i<nFuncTable_SIMPLE_size;i++)
			{
				if(nOriAddress == pFuncTable_SIMPLE[i*2])
				{
					g_nCmpdForceStopAddress = pFuncTable_SIMPLE[i*2+1];
					s32 rv = agbCPUCmpilerCmpOne(nOriAddress, 0x100, bThumb);
					if(rv >= 0)
						return rv;
				}
			}
		}
		else if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
		{
			for(int i=0;i<nFuncTable_DOPHI_size;i++)
			{
				if(nOriAddress == pFuncTable_DOPHI[i*2])
				{
					g_nCmpdForceStopAddress = pFuncTable_DOPHI[i*2+1];
					s32 rv = agbCPUCmpilerCmpOne(nOriAddress, 0x100, bThumb);
					if(rv >= 0)
						return rv;
				}
			}
		}
	}
	return -1;
}

/** @brief Compile the Instruction */
s32 agbCPUCmpilerCmpAll()
{
	if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
	{		
		//g_pCmpdDebugAddress[g_nCmpdDebugAddressNum++] = 0x0800028E;
		
		g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x08000288;
		g_pCmpdArmFuncAddrStackPos = g_pCmpdThumbFuncAddrStackPos = 0;
		g_nCmpdForceStopAddress = 0x00000000;		
	}
	else if(g_nAgbGameTitle == AGB_TITLE_MARIOA_AMAJ)
	{
		g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x080B5556;
		g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x080B555E;
		g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x08001c72;
		g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x08001D0E;

		g_pCmpdArmFuncAddrStackPos = g_pCmpdThumbFuncAddrStackPos = 0;		
		
	}
	else if(g_nAgbGameTitle == AGB_TITLE_CHECK323)
	{
		g_pCmpdArmFuncAddrStackPos = g_pCmpdThumbFuncAddrStackPos = 0;
		//g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x080B5E3C;
		//g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x080B5E42;
		//g_pCmpdEmptyLoopAddress[g_nCmpdEmptyLoopAddressNum++] = 0x080B5E42;
	}
	return 0;
}

/** @brief Compile the Interrupt */
s32 agbCPUCmpilerCmpInterrupt()
{
	if(g_bCmpdInterruptChange == 1)
	{
		
		
		if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
		{
			//g_nCmpdForceStopAddress = 0x0000134;
			agbCPUCmpilerCmpOne(0x00000018, 0x100, 0);
			//g_nCmpdForceStopAddress = 0x0000134;
			agbCPUCmpilerCmpOne(0x030005A0, 0x100, 0);
			agbCPUCmpilerCmpOne(0x08000374, 0x100, 1);
		}
		else if(g_nAgbGameTitle == AGB_TITLE_MARIOA_AMAJ)
		{
			//intr_main 0x03001140
			//intr_table
			//0x08000BED	V_BLANK_INTR_FLAG
			//0x08002AED	SIO_INTR_FLAG
			//0x08002AED	TIMER3_INTR_FLAG
			//0x080011A5	H_BLANK_INTR_FLAG
			//0x0800111E	V_COUNT_INTR_FLAG
			//0x08001211	TIMER0_INTR_FLAG
			//0x08001211	TIMER1_INTR_FLAG
			//0x080B64C5	TIMER2_INTR_FLAG
			//0x08001211	DMA0_INTR_FLAG
			//0x08001211	DMA1_INTR_FLAG
			//0x08001211	DMA2_INTR_FLAG
			//0x08001211	DMA3_INTR_FLAG
			//0x08001211	KEY_INTR_FLAG
			//0x08001211	CASSETTE_INTR_FLAG
			//agbCPUCmpilerCmpOne(0x00000018, 0x100, 0);
			//agbCPUCmpilerCmpOne(0x03001140, 0x100, 0);

			//agbCPUCmpilerCmpOne(0x08000BEC, 0x100, 1);
			//agbCPUCmpilerCmpOne(0x08002AED, 0x100, 1);
			//agbCPUCmpilerCmpOne(0x080011A5, 0x100, 1);
			

		}
		g_bCmpdInterruptChange = 0;
	}
	return 0;
}


/** @brief Compile the Instruction */
s32 agbCPUCmpilerCmpOne(u32 nOriAddress, u32 nInst, u32 bThumb)
{
	(void)nInst;
	if(g_nCmpdCmpBlockCt >= g_nCmpdCmpBlockMax)
		return -1;
	u32 blocknum;

	blocknum = g_sCPUCmpData.nInstBlockNum;
	if(blocknum >= INST_BLOCK_NUM)
		return -1;

	s32 cmpinstnum;
	s32 nOriStartAddress = nOriAddress;
	
	cmpinstnum= agbCPUCmpilerCmpBlock(nOriStartAddress, nOriAddress, bThumb);
	if(cmpinstnum >= 0)
	{
		CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpData.pInstBlock[blocknum]);
		g_sCPUCmpData.nInstBlockNum++;
		assert(g_sCPUCmpData.nInstBlockNum < INST_BLOCK_NUM);
		
		ptb->nInstNum = cmpinstnum;
		ptb->nOriAddr = nOriStartAddress;
		ptb->nRunTimes = 0;
		ptb->pBuf = (u8*)trlMemAlloc(g_nCmpdBufLength);
		trlMemCopy(ptb->pBuf, g_pCmpdBuf, g_nCmpdBufLength);

		///re-address the function call
		//the function is like agbMemRead...and so on
		for(int i=0;i<g_nCmpdFuncCallNum;i++)
		{
			s32 oriAddr = *(s32*)(ptb->pBuf + g_pCmpdFuncCall[i]);
			s32 newAddr = ((s32)(ptb->pBuf) + g_pCmpdFuncCall[i]);
			*(s32*)(ptb->pBuf + g_pCmpdFuncCall[i]) = (oriAddr - 4 - newAddr);			
		}
		//re-address the function-inner jmp			
		for(int i=0;i<g_nCmpdJmpNum;i++)
		{
			s32 offsetjmp = g_pCmpdJmp[i];
			s32 destaddr = *(u32*)(g_pCmpdBuf + offsetjmp);
			s32 newdestaddr;
			if(bThumb == 1)
			{
				if( (destaddr - nOriAddress) >= 0)
					newdestaddr = g_pCmpdAddr[(destaddr - nOriAddress)/2];
				else
					newdestaddr = g_pCmpdAddrRe[(destaddr - nOriAddress)/2];
			}
			else
			{
				if( (destaddr - nOriAddress) >= 0)
					newdestaddr = g_pCmpdAddr[(destaddr - nOriAddress)/4];
				else
					newdestaddr = g_pCmpdAddrRe[(destaddr - nOriAddress)/4];
			}
			*(s32*)(ptb->pBuf + offsetjmp) = newdestaddr - (offsetjmp+4);
		}		
	}
	else
	{
		return -1;
	}
	agbCPUCmpilerCmpOne_OffLine(nOriStartAddress, nOriAddress, bThumb);
	NN_LOG("agbCPUCmpilerCmpOne success: Address =  %08x Thumb = %d, BlockCt = %d  blokcid = 0x%x cmpinstnum = %d\n",nOriStartAddress, bThumb, g_nCmpdCmpBlockCt, blocknum, cmpinstnum);
	g_nCmpdCmpBlockCt++;
	return blocknum;
}

static s32 agbCPUCmpilerCmpClear()
{
	g_nCmpdBufLength = 0;
	g_nCmpdFuncCallNum = 0;
	g_nCmpdJmpNum = 0;
	g_pCmpdFuncAddrStackPos = 0;
	memset(g_pCmpdAddr, 0, sizeof(g_pCmpdAddr));
	memset(g_pCmpdAddrRe, 0, sizeof(g_pCmpdAddrRe));
	return 0;
}




s32 agbCPUCmpilerMakeJmpData(u32 pc,u32 instpos, CMPD_JMPTYPE jmptype)
{
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc));
	genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
	genReturn();

	s32 oriaddr;//, oriretaddr;
		
	oriaddr = pc;
//	oriretaddr = pc;
		
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = jmptype;					
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = oriaddr;
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = -1;
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = -1;
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
	g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
	g_sCPUCmpData.nJmpBlockNum++;
	return 0;
}

s32 agbCPUCmpilerCmpBlock(u32 nOriStartAddress, u32 nOriAddress, u32 bThumb)
{
	u32 innerjump[INNER_JUMP_MAX];
	u32 innerjumpnum = 0;
	s32 rv = 0;
	u32 instct = 0;
	u32 instpos;
	u32 pc = nOriStartAddress;
	u32 inst;

	agbCPUCmpilerCmpClear();

	innerjump[0] = nOriStartAddress;
	innerjumpnum = 1;

	if(nOriStartAddress == 0xaac)
		nOriStartAddress = nOriStartAddress;
	
	while(innerjumpnum > 0)
	{
		pc = innerjump[innerjumpnum-1];
		innerjumpnum--;
		while(1)
		{
			//if(bThumb == 1)
			//	NN_LOG("agbCPUCmpilerCmpBlock Thumb 0x%x, 0x%x  0x%x   0x%x == 0x%x\n", pc, g_nCmpdBufLength, g_pCmpdAddr[(pc-nOriAddress)/2], instct, (pc-nOriAddress)/2);
			//else
			//	NN_LOG("agbCPUCmpilerCmpBlock Arm   0x%x, 0x%x  0x%x   0x%x == 0x%x\n", pc, g_nCmpdBufLength, g_pCmpdAddr[(pc-nOriAddress)/2], instct, (pc-nOriAddress)/2);
			
			assert(pc >= nOriAddress);

			assert(g_nCmpdBufLength < INST_BLOCK_MAXLENGTH);
			
			if(bThumb == 1)
			{
				assert( (pc&0x1) == 0);
				inst = agbMemRead16(pc);
				instpos = (pc - nOriAddress)/2;
			}
			else
			{
				assert( (pc&0x3) == 0);
				inst = agbMemRead32(pc);
				instpos = (pc - nOriAddress)/4;
			}

			//zhfang test 0x080009BE in dophi should be debug more careful
			//if(pc == 0x080009BE)
			//	pc = pc;
			if(pc == 0x08027e2c)
				pc = pc;
			
			if(instpos >=0)
			{
				if(g_pCmpdAddr[instpos] != 0)
					break;
			}
			else
			{
				if(g_pCmpdAddrRe[-instpos] != 0)
					break;
			}

			if(pc == g_nCmpdForceStopAddress)
			{
				genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc));
				genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
				genReturn();

				s32 oriaddr;//, oriretaddr;
					
				oriaddr = pc;
				//oriretaddr = pc;
					
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FORCESTOP;					
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpData.nJmpBlockNum++;
				return instct;
			}
			
			g_pCmpdAddr[instpos] = g_nCmpdBufLength;

			for(int i=0;i<g_nCmpdDebugAddressNum;i++)
			{
				if(pc == g_pCmpdDebugAddress[i])
				{
					if(bThumb == 1)
						genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+4));
					else
						genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+8));
					genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
					genReturn();

					s32 oriaddr, oriretaddr;
					
					oriaddr = pc;
					oriretaddr = pc;
					
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_DEBUG;					
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = -1;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
					g_sCPUCmpData.nJmpBlockNum++;
				}
			}

			for(int i=0;i<g_nCmpdEmptyLoopAddressNum;i++)
			{
				if(pc == g_pCmpdEmptyLoopAddress[i])
				{
					if(bThumb == 1)
						genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+2));
					else
						genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+4));
					genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
					genReturn();

					s32 oriaddr, oriretaddr;
					
					oriaddr = pc;
					oriretaddr = pc;
					
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_EMPTYLOOP;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = -1;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
					g_sCPUCmpData.nJmpBlockNum++;
				}
			}
			if(pc == 0x08026D2A)
				pc = pc;
			
			
			if(bThumb == 1)
				rv = agbCPUCompiler_Thumb(inst, pc);
			else
				rv = agbCPUCompiler_Arm(inst, pc);
			instct++;
			

			if(rv == INST_CMPD_RESULT_NORMAL)
			{
			}
			else if(rv == INST_CMPD_RESULT_INNERJUMP)
			{
				if(g_nCmpdJmpAddress >= nOriAddress)
				{
					g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+1;
					genJMP_S32(g_nCmpdJmpAddress);
					pc = g_nCmpdJmpAddress;
				}
				else
				{
					genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
					genReturn();

					s32 oriaddr, oriretaddr;
					oriaddr = pc;
					oriretaddr = -1;
					
					
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMP;					
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
					g_sCPUCmpData.nJmpBlockNum++;
					break;
				}
			}
			else if(rv == INST_CMPD_RESULT_INNERJUMP_COND)
			{
				assert(g_nCmpdJmpAddress >= nOriAddress);
				innerjump[innerjumpnum++] = g_nCmpdJmpAddress;
			}
			else if(rv == INST_CMPD_RESULT_FUNCTION_COND)
			{
				s32 oriaddr, oriretaddr;
				if(bThumb == 1)
				{
					g_pCmpdFuncAddrStack[g_pCmpdFuncAddrStackPos++] = g_nCmpdJmpAddress;
					oriaddr = pc;
					oriretaddr = pc+4;
					pc+=2;
				}
				else
				{
					g_pCmpdFuncAddrStack[g_pCmpdFuncAddrStackPos++] = g_nCmpdJmpAddress;
					oriaddr = pc;
					oriretaddr = pc+4;					
				}

				if(rv == INST_CMPD_RESULT_FUNCTION)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNC;
				else if(rv == INST_CMPD_RESULT_FUNCTIONX)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNCX;				

				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpData.nJmpBlockNum++;
			}
			else if(rv == INST_CMPD_RESULT_OUTERJUMP || rv == INST_CMPD_RESULT_OUTERJUMPX || rv == INST_CMPD_RESULT_OUTERJUMPEX)
			{	
				genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
				genReturn();

				s32 oriaddr, oriretaddr;
				oriaddr = pc;
				oriretaddr = -1;
				
				if(rv == INST_CMPD_RESULT_OUTERJUMP)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMP;
				else if(rv == INST_CMPD_RESULT_OUTERJUMPX)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMPX;
				else if(rv == INST_CMPD_RESULT_OUTERJUMPEX)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMPEX;

				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpData.nJmpBlockNum++;
				break;
			}
			else if(rv == INST_CMPD_RESULT_SWI)
			{
				//zhfang test
				genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
				genReturn();

				s32 oriaddr, oriretaddr;
				if(bThumb == 1)
				{
					g_pCmpdFuncAddrStack[g_pCmpdFuncAddrStackPos++] = g_nCmpdJmpAddress;
					oriaddr = pc;
					oriretaddr = pc+2;					
				}
				else
					assert(0);

				
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNCX;				

				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpData.nJmpBlockNum++;
			}
			else if(rv == INST_CMPD_RESULT_FUNCTION || rv == INST_CMPD_RESULT_FUNCTIONX)
			{
				//zhfang test
				genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
				genReturn();

				s32 oriaddr, oriretaddr;
				if(bThumb == 1)
				{
					g_pCmpdFuncAddrStack[g_pCmpdFuncAddrStackPos++] = g_nCmpdJmpAddress;
					oriaddr = pc;
					oriretaddr = pc+4;
					pc+=2;
				}
				else
				{
					g_pCmpdFuncAddrStack[g_pCmpdFuncAddrStackPos++] = g_nCmpdJmpAddress;
					oriaddr = pc;
					oriretaddr = pc+4;					
				}

				if(rv == INST_CMPD_RESULT_FUNCTION)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNC;
				else if(rv == INST_CMPD_RESULT_FUNCTIONX)
					g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNCX;				

				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLength;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpData.nJmpBlockNum++;			
			}
			else if(rv == INST_CMPD_RESULT_SWITCHCMODE)
			{
				genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
				genReturn();

				s32 oriaddr;
				oriaddr = pc;				
				
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_SWITCHMODE;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriBlockID = g_sCPUCmpData.nInstBlockNum;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nOriRetAddress = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddr[instpos];			
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdRetAddress = -1;

				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpData.pJmpBlock[g_sCPUCmpData.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpData.nJmpBlockNum++;

				break;
			}
			else if(rv == INST_CMPD_RESULT_UNKOWN_INST)
			{
				//unkown inst
				assert(0);
			}
			else
			{
				//unkown rv
				assert(0);
			}

			if(rv != INST_CMPD_RESULT_INNERJUMP)
			{
				if(bThumb == 1)
					pc+=2;
				else
					pc+=4;
			}
			if(bThumb == 1)
				instpos = (pc - nOriAddress)/2;
			else
				instpos = (pc - nOriAddress)/4;
			
			if(g_pCmpdAddr[instpos] != 0)
			{
				//if(rv == INST_CMPD_RESULT_NORMAL || rv == INST_CMPD_RESULT_FUNCTION || INST_CMPD_RESULT_FUNCTIONX
				if(rv != INST_CMPD_RESULT_INNERJUMP)
				{
					genJMP_S32(g_pCmpdAddr[instpos] - (g_nCmpdBufLength + 5));
					break;
				}
			}
		}
	}
	return instct;
}
