/**
* @file agbCPUCompiler_OffLine
* @author zhfang
* @date 2010.01.05
* @brief AGB Emulate For CTR - Off Line Compiler for AGB Cpu
*/
#include <assert.h>
#include "..\..\\trlHeader.h"
#include "..\agbMemory.h"
#include "..\agbCPUData.h"
#ifdef TRL_PLATFORM_PC
#endif

#ifdef TRL_PLATFORM_CTR
#include "agbCPUCmpOffLine_JumpData.h"
#include "agbCPUCmpOffLine_BlockData.h"
#endif

#include "agbCPUCmpData.h"
#include "agbCPUCmpiler_OffLine.h"
#include "agbCPUCmpilerGenArm.h"
#include "agbCPUCmpilerInstArm_ARM.h"
#include "agbCPUCmpilerInstThumb_ARM.h"




/** @brief Initialize Compiler */
void agbCPUCmpilerOffLineInit()
{
	if(g_bCmpdOffLine == 0)
	{
		agbCPUCmpilerCmpOffLineBuild();
	}
	else
	{		
		memset(g_sCPUCmpDataOL.pInstBlock, 0, sizeof(CPU_INSTRUCT_BLOCK)*INST_BLOCK_NUM);
		memset(g_sCPUCmpDataOL.pJmpBlock, 0, sizeof(CPU_JMP_BLOCK)*INST_JMP_NUM);
		g_sCPUCmpDataOL.nInstBlockNum = 0;
		g_sCPUCmpDataOL.nJmpBlockNum = 0;

#ifdef TRL_PLATFORM_PC
		/*if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
		{
			g_pOLBlockData_fp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_BlockData_Dophi.cpp", "w");
			g_pOLBlockData_hfp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_BlockData_Dophi.h", "w");
			g_pOLJumpData_fp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_JumpData_Dophi.cpp", "w");
			g_pOLJumpData_hfp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_JumpData_Dophi.h", "w");
			g_pOLFunc_fp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLineFunc_Dophi.s", "w");

			fprintf(g_pOLBlockData_fp, "#include \"%s\"\n", "agbCPUCmpOffLine_BlockData_Dophi.h");
			fprintf(g_pOLJumpData_fp, "#include \"%s\"\n", "agbCPUCmpOffLine_BlockData_Dophi.h");
		}
		else*/
		{
			g_pOLBlockData_fp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_BlockData.cpp", "w");
			g_pOLBlockData_hfp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_BlockData.h", "w");
			g_pOLJumpData_fp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_JumpData.cpp", "w");
			g_pOLJumpData_hfp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLine_JumpData.h", "w");
			g_pOLFunc_fp = fopen("..\\src\\AGB\\CPUCompiler\\agbCPUCmpOffLineFunc.s", "w");

			fprintf(g_pOLBlockData_fp, "#include \"%s\"\n", "agbCPUCmpOffLine_BlockData.h");
			fprintf(g_pOLJumpData_fp, "#include \"%s\"\n", "agbCPUCmpOffLine_BlockData.h");
		}

		fprintf(g_pOLFunc_fp, "\tPRESERVE8\n");
		fprintf(g_pOLFunc_fp, "\tAREA OL_FUNC,CODE,READONLY\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbMemRead32\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbMemRead16\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbMemRead8\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbMemWrite32\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbMemWrite16\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbMemWrite8\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbCPUSwitchMode\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbCPUUpdateFlags\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT agbCPUSWI_NOPRE\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg\n");
		
		/*fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_CPUMODE]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_CPUVALUE]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_CPUTEMP]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_CPUADDRESS]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_NFLAG]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_ZFLAG]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_CFLAG]\n");
		fprintf(g_pOLFunc_fp, "\tIMPORT g_nAgbCPUReg[REG_VFLAG]\n");	*/
		

		fprintf(g_pOLFunc_fp, "\tEXPORT FUNC_JUMP\n");
		fprintf(g_pOLFunc_fp, "FUNC_JUMP\n");
		fprintf(g_pOLFunc_fp, "\tPUSH {r4,lr}\n");
		genARMN_LDR_REG_ADDR(4,(u32)&g_nAgbCPUReg[0]);
		fprintf(g_pOLFunc_fp, "\tBX r0\n");
		fprintf(g_pOLFunc_fp, "\tLTORG\n");
		fflush(g_pOLFunc_fp);

		g_nCmpdJmpTemp = 0;
		g_nCmpdCondJmpOL = 0;

		g_nCmpdCmpBlockCtOL = 0;
		g_nCmpdCmpBlockMaxOL = 0;
		g_nCmpdCmpBlockMaxOL = INST_BLOCK_NUM;
		
#endif
	}
}

/** @brief Compile the Instruction */
s32 agbCPUCmpilerCmpOffLineBuild()
{
#ifdef TRL_PLATFORM_CTR
	assert(g_nAgbCmpDataOL_BlockNum < INST_BLOCK_NUM);
	for(int i=0;i<g_nAgbCmpDataOL_BlockNum;i++)
	{
		CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpData.pInstBlock[i]);
		g_sCPUCmpData.nInstBlockNum++;

		ptb->nInstNum = g_nAgbCmpDataOL_BlockData[i*3];
		ptb->nOriAddr = g_nAgbCmpDataOL_BlockData[i*3 + 1];
		ptb->nRunTimes = 0;
		ptb->pBuf = (u8*)(g_nAgbCmpDataOL_BlockData[i*3 + 2]);
	}
	g_nCmpdCmpBlockCt = g_nAgbCmpDataOL_BlockNum;
	
	for(int i=0;i<g_nAgbCmpDataOL_JumpBlockNum;i++)
	{
		CPU_JMP_BLOCK *pjumpdata = &g_sCPUCmpData.pJmpBlock[i];
		g_sCPUCmpData.nJmpBlockNum++;

		pjumpdata->nJmpType				= (CMPD_JMPTYPE)g_nAgbCmpDataOL_JumpBlock[i*9];
		pjumpdata->nOriBlockID			= g_nAgbCmpDataOL_JumpBlock[i*9+1];
		pjumpdata->nOriJmpAddress		= g_nAgbCmpDataOL_JumpBlock[i*9+2];
		pjumpdata->nOriJmpedAddress		= g_nAgbCmpDataOL_JumpBlock[i*9+3];
		pjumpdata->nOriRetAddress		= g_nAgbCmpDataOL_JumpBlock[i*9+4];
		pjumpdata->nCmpdJmpAddress		= g_nAgbCmpDataOL_JumpBlock[i*9+4];
		pjumpdata->nCmpdRetAddress		= g_nAgbCmpDataOL_JumpBlock[i*9+6];
		pjumpdata->nJmpedBlockID		= g_nAgbCmpDataOL_JumpBlock[i*9+7];
		pjumpdata->nCmpdJmpedAddress	 = g_nAgbCmpDataOL_JumpBlock[i*9+8];
	}

#endif
	return 0;
}


static s32 agbCPUCmpilerCmpClear()
{
	g_nCmpdBufLengthOL = 0;
	
	g_nCmpdFuncCallNum = 0;
	g_nCmpdJmpNum = 0;
	g_pCmpdFuncAddrStackPos = 0;
	memset(g_pCmpdAddrOL, 0, sizeof(g_pCmpdAddrOL));
	memset(g_pCmpdAddrReOL, 0, sizeof(g_pCmpdAddrReOL));

	return 0;
}


static s32 agbCPUCmpiler_OffLine_WriteFile()
{
#ifdef TRL_PLATFORM_PC
	//asm file
	for(int i=0;i<g_sCPUCmpDataOL.nInstBlockNum;i++)
	{
		CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[i]);
		fprintf(g_pOLFunc_fp, "\tEXPORT INST_0x%08x\n", ptb->nOriAddr);
	}
	for(int i=0;i<g_sCPUCmpDataOL.nJmpBlockNum;i++)
	{
		CPU_JMP_BLOCK *pjumpdata = &g_sCPUCmpDataOL.pJmpBlock[i];
		if(pjumpdata->nOriRetAddress != -1)
		{
			CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[pjumpdata->nOriBlockID]);
			if(pjumpdata->nJmpType == CMPD_JMPTYPE_FUNC || pjumpdata->nJmpType == CMPD_JMPTYPE_FUNCX ||
				pjumpdata->nJmpType == CMPD_JMPTYPE_EMPTYLOOP)
			{
				fprintf(g_pOLFunc_fp, "\tEXPORT INST_0x%08x_IN_0x%08x\n", pjumpdata->nOriRetAddress, ptb->nOriAddr);
			}
			else
				fprintf(g_pOLFunc_fp, "\tEXPORT INST_0x%08x\n", pjumpdata->nOriRetAddress);
		}
	}
	fprintf(g_pOLFunc_fp, "\tEND\n");
	fclose(g_pOLFunc_fp);
	
	//block data h
	fprintf(g_pOLBlockData_hfp, "#include \"..\\..\\trlHeader.h\"\n\n");
	fprintf(g_pOLBlockData_hfp, "extern \"C\" s32 FUNC_JUMP(u32 func_addr);\n");
	for(int i=0;i<g_sCPUCmpDataOL.nInstBlockNum;i++)
	{
		CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[i]);
		fprintf(g_pOLBlockData_hfp, "extern \"C\" s32 INST_0x%08x();\n", ptb->nOriAddr);
	}
	for(int i=0;i<g_sCPUCmpDataOL.nJmpBlockNum;i++)
	{
		CPU_JMP_BLOCK *pjumpdata = &g_sCPUCmpDataOL.pJmpBlock[i];
		CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[pjumpdata->nOriBlockID]);
		if(pjumpdata->nOriRetAddress != -1)
		{
			if(pjumpdata->nJmpType == CMPD_JMPTYPE_FUNC || pjumpdata->nJmpType == CMPD_JMPTYPE_FUNCX ||
				pjumpdata->nJmpType == CMPD_JMPTYPE_EMPTYLOOP)
			{
				fprintf(g_pOLBlockData_hfp, "\extern \"C\" s32 INST_0x%08x_IN_0x%08x();\n", pjumpdata->nOriRetAddress, ptb->nOriAddr);
			}
			else
				fprintf(g_pOLBlockData_hfp, "\extern \"C\" s32 INST_0x%08x();\n", pjumpdata->nOriRetAddress);
		}		
	}
	fprintf(g_pOLBlockData_hfp, "\n");
	fprintf(g_pOLBlockData_hfp, "extern u32 g_nAgbCmpDataOL_BlockNum;\n");
	fprintf(g_pOLBlockData_hfp, "extern u32 g_nAgbCmpDataOL_BlockData[3*%d];\n", g_sCPUCmpDataOL.nInstBlockNum);
	fclose(g_pOLBlockData_hfp);

	//block data cpp
	fprintf(g_pOLBlockData_fp, "\n");
	fprintf(g_pOLBlockData_fp, "u32 g_nAgbCmpDataOL_BlockNum = %d;\n", g_sCPUCmpDataOL.nInstBlockNum);
	fprintf(g_pOLBlockData_fp, "u32 g_nAgbCmpDataOL_BlockData[3*%d] = \n{\n", g_sCPUCmpDataOL.nInstBlockNum);
	for(int i=0;i<g_sCPUCmpDataOL.nInstBlockNum;i++)
	{
		CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[i]);
		if(i < g_sCPUCmpDataOL.nInstBlockNum-1)
			fprintf(g_pOLBlockData_fp, "\t%d,\t0x%08x,\t(u32)INST_0x%08x,\n", ptb->nInstNum, ptb->nOriAddr, ptb->nOriAddr);
		else
			fprintf(g_pOLBlockData_fp, "\t%d,\t0x%08x,\t(u32)INST_0x%08x\n", ptb->nInstNum, ptb->nOriAddr, ptb->nOriAddr);		
	}
	fprintf(g_pOLBlockData_fp, "};\n");
	fclose(g_pOLBlockData_fp);
	
	//jmp data h
	fprintf(g_pOLJumpData_hfp, "#include \"..\\..\\trlHeader.h\"\n\n");
	fprintf(g_pOLJumpData_hfp, "extern u32 g_nAgbCmpDataOL_JumpBlockNum;\n", g_sCPUCmpDataOL.nJmpBlockNum);
	fprintf(g_pOLJumpData_hfp, "extern s32 g_nAgbCmpDataOL_JumpBlock[9*%d];\n", g_sCPUCmpDataOL.nJmpBlockNum);
	fclose(g_pOLJumpData_hfp);
	
	//jmp data cpp
	fprintf(g_pOLJumpData_fp, "#include \"..\\..\\trlHeader.h\"\n\n");	
	fprintf(g_pOLJumpData_fp, "u32 g_nAgbCmpDataOL_JumpBlockNum = %d;\n", g_sCPUCmpDataOL.nJmpBlockNum);
	fprintf(g_pOLJumpData_fp, "s32 g_nAgbCmpDataOL_JumpBlock[9*%d] =\n{\n", g_sCPUCmpDataOL.nJmpBlockNum);
	for(int i=0;i<g_sCPUCmpDataOL.nJmpBlockNum;i++)
	{
		CPU_JMP_BLOCK *pjumpdata = &g_sCPUCmpDataOL.pJmpBlock[i];
		if(pjumpdata->nOriRetAddress != 0xFFFFFFFF)
		{
			CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[pjumpdata->nOriBlockID]);

			pjumpdata->nCmpdRetAddress = pjumpdata->nOriRetAddress;
			if(i < g_sCPUCmpDataOL.nJmpBlockNum-1)
				fprintf(g_pOLJumpData_fp, "\t%d,\t%d,\t0x%08x,\t0x%08x,\t0x%08x,\t0x%08x,\t(u32)INST_0x%08x_IN_0x%08x,\t%d,\t0x%08x,\n", pjumpdata->nJmpType,
					pjumpdata->nOriBlockID, pjumpdata->nOriJmpAddress, pjumpdata->nOriJmpedAddress, pjumpdata->nOriRetAddress,
					pjumpdata->nCmpdJmpAddress, pjumpdata->nCmpdRetAddress, ptb->nOriAddr,
					pjumpdata->nJmpedBlockID, pjumpdata->nCmpdJmpedAddress);
			else
				fprintf(g_pOLJumpData_fp, "\t%d,\t%d,\t0x%08x,\t0x%08x,\t0x%08x,\t0x%08x,\t(u32)INST_0x%08x_IN_0x%08x,\t%d,\t0x%08x\n", pjumpdata->nJmpType,
					pjumpdata->nOriBlockID, pjumpdata->nOriJmpAddress, pjumpdata->nOriJmpedAddress, pjumpdata->nOriRetAddress,
					pjumpdata->nCmpdJmpAddress, pjumpdata->nCmpdRetAddress, ptb->nOriAddr,
					pjumpdata->nJmpedBlockID, pjumpdata->nCmpdJmpedAddress);
		}
		else
		{
			if(i < g_sCPUCmpDataOL.nJmpBlockNum-1)
				fprintf(g_pOLJumpData_fp, "\t%d,\t%d,\t0x%08x,\t0x%08x,\t0x%08x,\t0x%08x,\t0x%08x,                        \t%d,\t0x%08x,\n", pjumpdata->nJmpType,
					pjumpdata->nOriBlockID, pjumpdata->nOriJmpAddress, pjumpdata->nOriJmpedAddress, pjumpdata->nOriRetAddress,
					pjumpdata->nCmpdJmpAddress, pjumpdata->nCmpdRetAddress,
					pjumpdata->nJmpedBlockID, pjumpdata->nCmpdJmpedAddress);
			else
				fprintf(g_pOLJumpData_fp, "\t%d,\t%d,\t0x%08x,\t0x%08x,\t0x%08x,\t0x%08x,\t0x%08x,                        \t%d,\t0x%08x\n", pjumpdata->nJmpType,
					pjumpdata->nOriBlockID, pjumpdata->nOriJmpAddress, pjumpdata->nOriJmpedAddress, pjumpdata->nOriRetAddress,
					pjumpdata->nCmpdJmpAddress, pjumpdata->nCmpdRetAddress,
					pjumpdata->nJmpedBlockID, pjumpdata->nCmpdJmpedAddress);
		}
	}
	fprintf(g_pOLJumpData_fp, "};\n", g_sCPUCmpDataOL.nJmpBlockNum);
	fclose(g_pOLJumpData_fp);
#endif
	return 0;
}

s32 agbCPUCmpilerCmpOne_OffLine(u32 nOriStartAddress, u32 nOriAddress, u32 bThumb)
{
	if(g_nCmpdCmpBlockCtOL >= g_nCmpdCmpBlockMaxOL)
		return -1;

	u32 blocknum;
	blocknum = g_sCPUCmpDataOL.nInstBlockNum;

	u32 nFuncTable_size;
	u32 *pFuncTable;

	if(g_nAgbGameTitle == AGB_TITLE_CHECK323)
	{
		nFuncTable_size = nFuncTable_SIMPLE_size;
		pFuncTable = pFuncTable_SIMPLE;
	}
	else if(g_nAgbGameTitle == AGB_TITLE_SIMPLE_DOPHI)
	{
		nFuncTable_size = nFuncTable_DOPHI_size;
		pFuncTable = pFuncTable_DOPHI;
	}
	else if(g_nAgbGameTitle == AGB_TITLE_MARIOA_AMAJ)
	{
		nFuncTable_size = nFuncTable_AAMAJ_size;
		pFuncTable = pFuncTable_AAMAJ;
	}
	else
		assert(0);


	for(int i=0;i<nFuncTable_size;i++)
	{
		if(nOriAddress == 0x080238c4)
			nOriAddress = 0x080238c4;
		if(nOriAddress == pFuncTable[i*2])
		{
			g_nCmpdForceStopAddress = pFuncTable[i*2+1];
			s32 rv = agbCPUCmpilerCmpBlock_OffLine(nOriStartAddress, nOriAddress, bThumb);
			if(rv >= 0)
			{
				CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpDataOL.pInstBlock[blocknum]);
				g_sCPUCmpDataOL.nInstBlockNum++;
				assert(g_sCPUCmpDataOL.nInstBlockNum < INST_BLOCK_NUM);

				ptb->nInstNum = rv;
				ptb->nOriAddr = nOriStartAddress;
				ptb->nRunTimes = 0;
			}
			else
			{
				return -1;
			}
			g_nCmpdCmpBlockCtOL++;			
			if(g_nCmpdCmpBlockCtOL >= g_nCmpdCmpBlockMaxOL)
			{
				agbCPUCmpiler_OffLine_WriteFile();
			}
			else if(g_nCmpdCmpBlockCtOL == nFuncTable_size)
			{
				agbCPUCmpiler_OffLine_WriteFile();
			}
			return rv;
		}
	}
	return -1;
}

s32 agbCPUCmpilerCmpBlock_OffLine(u32 nOriStartAddress, u32 nOriAddress, u32 bThumb)
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
	if(nOriAddress == 0x010af0f4)
		nOriAddress = nOriAddress;
	g_nCmpdCurFuncAddressOL = nOriAddress;
#ifdef TRL_PLATFORM_PC
			fprintf(g_pOLFunc_fp, "INST_0x%08x\n", pc);
			fflush(g_pOLFunc_fp);
#endif

	while(innerjumpnum > 0)
	{
		pc = innerjump[innerjumpnum-1];
		innerjumpnum--;
		while(1)
		{			
			assert(pc >= nOriAddress);
			assert(g_nCmpdBufLengthOL < INST_BLOCK_MAXLENGTH);
			
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

			if(instpos >=0)
			{
				if(g_pCmpdAddrOL[instpos] != 0)
					break;
			}
			else
			{
				if(g_pCmpdAddrReOL[-instpos] != 0)
					break;
			}

			if(pc == g_nCmpdForceStopAddress)
			{
				genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc), 0, 1);
				genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
				genARMM_Return();
				genARMM_LTORG();
				
				s32 oriaddr;//, oriretaddr;
					
				oriaddr = pc;
				//oriretaddr = pc;
					
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FORCESTOP;					
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpDataOL.nJmpBlockNum++;
				return instct;
			}
			//zhfang test
			g_pCmpdAddrOL[instpos] = 0x2244;//g_nCmpdBufLengthOL;

			for(int i=0;i<g_nCmpdDebugAddressNum;i++)
			{
				if(pc == g_pCmpdDebugAddress[i])
				{
					if(bThumb == 1)
						genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+4), 0, 1);
					else
						genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+8), 0, 1);
					genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
					genARMM_Return();

					s32 oriaddr, oriretaddr;
					
					oriaddr = pc;
					oriretaddr = pc;
					
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_DEBUG;					
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = -1;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
					g_sCPUCmpDataOL.nJmpBlockNum++;
				}
			}

			for(int i=0;i<g_nCmpdEmptyLoopAddressNum;i++)
			{
				if(pc == g_pCmpdEmptyLoopAddress[i])
				{
					if(bThumb == 1)
						genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+2), 0, 1);
					else
						genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)(pc+4), 0, 1);
					genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
					genARMM_Return();

					s32 oriaddr, oriretaddr;
					
					oriaddr = pc;
					oriretaddr = pc;
					
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_EMPTYLOOP;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = -1;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
					g_sCPUCmpDataOL.nJmpBlockNum++;
				}
			}
			if(pc == 0x0300115c)
				pc = pc;

			if( (instpos%50) == 0 && (instpos/50)>0)
			{
				genARMN_JMP_S32(pc);
				genARMM_LTORG();
			}
			
#ifdef TRL_PLATFORM_PC
			fprintf(g_pOLFunc_fp, "INST_0x%08x_IN_0x%08x\n", pc, nOriAddress);
			fflush(g_pOLFunc_fp);
#endif			
			if(bThumb == 1)
				rv = agbCPUCompiler_Thumb_ARM(inst, pc);
			else
				rv = agbCPUCompiler_Arm_ARM(inst, pc);
			instct++;
			

			if(rv == INST_CMPD_RESULT_NORMAL)
			{
			}
			else if(rv == INST_CMPD_RESULT_INNERJUMP)
			{
				if(g_nCmpdJmpAddress >= nOriAddress)
				{
					g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+1;
					genARMN_JMP_S32(g_nCmpdJmpAddress);
					genARMM_LTORG();
					pc = g_nCmpdJmpAddress;
				}
				else
				{
					genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
					genARMM_Return();
					genARMM_LTORG();

					s32 oriaddr, oriretaddr;
					oriaddr = pc;
					oriretaddr = -1;
					
					
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMP;					
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
					g_sCPUCmpDataOL.nJmpBlockNum++;
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
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNC;
				else if(rv == INST_CMPD_RESULT_FUNCTIONX)
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNCX;				

				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpDataOL.nJmpBlockNum++;
			}
			else if(rv == INST_CMPD_RESULT_OUTERJUMP || rv == INST_CMPD_RESULT_OUTERJUMPX || rv == INST_CMPD_RESULT_OUTERJUMPEX)
			{	
				genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
				genARMM_Return();
				genARMM_LTORG();

				s32 oriaddr, oriretaddr;
				oriaddr = pc;
				oriretaddr = -1;
				
				if(rv == INST_CMPD_RESULT_OUTERJUMP)
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMP;
				else if(rv == INST_CMPD_RESULT_OUTERJUMPX)
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMPX;
				else if(rv == INST_CMPD_RESULT_OUTERJUMPEX)
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_JUMPEX;

				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpDataOL.nJmpBlockNum++;
				break;
			}
			else if(rv == INST_CMPD_RESULT_SWI)
			{
				//zhfang test
				genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
				genARMM_Return();

				s32 oriaddr, oriretaddr;
				if(bThumb == 1)
				{
					g_pCmpdFuncAddrStack[g_pCmpdFuncAddrStackPos++] = g_nCmpdJmpAddress;
					oriaddr = pc;
					oriretaddr = pc+2;					
				}
				else
					assert(0);

				
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNCX;				

				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpDataOL.nJmpBlockNum++;
			}
			else if(rv == INST_CMPD_RESULT_FUNCTION || rv == INST_CMPD_RESULT_FUNCTIONX)
			{
				//zhfang test
				genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
				genARMM_Return();
				genARMM_LTORG();


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
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNC;
				else if(rv == INST_CMPD_RESULT_FUNCTIONX)
					g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_FUNCX;				

				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = oriretaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = g_nCmpdBufLengthOL;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpDataOL.nJmpBlockNum++;			
			}
			else if(rv == INST_CMPD_RESULT_SWITCHCMODE)
			{
				genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
				genARMM_Return();

				s32 oriaddr;
				oriaddr = pc;				
				
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpType = CMPD_JMPTYPE_SWITCHMODE;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriBlockID = g_sCPUCmpDataOL.nInstBlockNum;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpAddress = oriaddr;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriJmpedAddress = g_nCmpdJmpAddress;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nOriRetAddress = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpAddress = g_pCmpdAddrOL[instpos];			
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdRetAddress = -1;

				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nJmpedBlockID = -1;
				g_sCPUCmpDataOL.pJmpBlock[g_sCPUCmpDataOL.nJmpBlockNum].nCmpdJmpedAddress = -1;
				g_sCPUCmpDataOL.nJmpBlockNum++;

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
			
			if(g_pCmpdAddrOL[instpos] != 0)
			{
				//if(rv == INST_CMPD_RESULT_NORMAL || rv == INST_CMPD_RESULT_FUNCTION || INST_CMPD_RESULT_FUNCTIONX
				if(rv != INST_CMPD_RESULT_INNERJUMP)
				{
					genARMN_JMP_S32(pc);
					genARMM_LTORG();
					//genARM_JMP_S32(g_pCmpdAddrOL[instpos] - (g_nCmpdBufLengthOL + 5));
					break;
				}
			}
		}
	}
	genARMM_LTORG();
	return instct;
}
