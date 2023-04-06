/**
* @file agbCPUCompilerInstArm.h
* @author zhfang
* @date 2009.12.27
* @brief AGB Emulate For CTR - Cmp Arm Inst
*/
#include <assert.h>
#include "..\..\trlHeader.h"
#include "..\agbMemory.h"
#include "..\agbCPU.h"
#include "..\agbCPUData.h"
#include "agbCPUCmpData.h"
#include "agbCPUCmpilerGenX86.h"

static s32 agbCPUCompiler_ARM_OP_S_RN_RD_ROTATE_IMM8(u32 inst, u32 pc)
{
	u32 imm = (inst&0xFF);
	u32 rotate = (inst>>8)&0xF;
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 s = (inst>>20)&0x1;
	u32 opcode = (inst>>21)&0xF;
	
	u32 c_out = 0;
	u32 operand;
	rotate<<=1;
	if(rotate == 0)
	{
		operand = imm;
	}
	else
	{		
		operand = ((imm<<(32-rotate))|(imm>>rotate));
		c_out = ((operand>>31)&0x1);
	}

	
	if(opcode == 0x0)//AND
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genAND_EAX_U32(operand);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x1)//EOR
	{
		if(rn != 15)
		{
			genMOV_EAX_U32(operand);
			genEOR_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);			
		}
		else
		{
			genMOV_EAX_U32(operand^(pc+8));			
		}		
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x2)//SUB
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genSUB_EAX_U32(operand);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x3) //RSB
	{
		genMOV_EAX_U32(operand);
		if(rn != 15)
		{			
			genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		}
		else
		{
			genSUB_EAX_U32(pc+8);			
		}		
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x4)//ADD
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genADD_EAX_U32(operand);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x5)//ADC
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genADD_EAX_U32(operand);
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}	
	else if(opcode == 0xB)//CMN
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genAND_EAX_U32(operand);		
	}	
	else if(opcode == 0xD)//MOV
	{
		assert(rn == 0);
		genMOV_EAX_U32(0);
		genADD_EAX_U32(operand);		
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0xE)//BIC
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genAND_EAX_U32(~operand);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}	
	else if(opcode == 0xC) //ORR
	{
		if(rn != 15)
		{
			genMOV_EAX_U32(operand);
			genORR_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);			
		}
		else
		{
			genMOV_EAX_U32(operand|(pc+8));			
		}
		
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0xA)//CMP
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genSUB_EAX_U32(operand);		
	}
	else if(opcode == 0x8) //TST
	{
		if(rn != 15)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		else
			genMOV_EAX_U32(pc + 8);
		genAND_EAX_U32(operand);		
	}	
	else
		assert(0);

	//1: EOR 0xF:MVN  0x3:RSB 0x7:RSC 0x6:SBC
	//8:TST 0x9:TEQ

	if(s == 1 && rd == 15)
	{
		genMOV_EAX_U32(0);
		genPUSH_EAX();
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[17]);
		genAND_EAX_S8(0x1F);
		genPUSH_EAX();
		genCALL((u32)agbCPUSwitchMode);
		genADD_ESP_U8(8);
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else if(s == 1)
	{
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		if(opcode == 0x0A) //CMP
			genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		else if(opcode == 0x0 || opcode == 0x0D || opcode == 0x0C )
			//AND/MOV/ORR
		{
			if(rotate != 0)
				genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], c_out);
		}
		else if(opcode == 0x2 || opcode == 0x3) //SUB RSB
		{
			genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);	
		}
		else
			genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);			
		genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_B_BL_SIMM24(u32 inst, u32 pc)
{
	s32 offset = (inst&0x00FFFFFF);
	if((offset&0x00800000)!= 0)
		offset |= 0xFF000000;
	offset<<=2;

	offset = pc+8+offset;

	u32 l = (inst>>24)&0x1;
	if(l==1)
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[14], pc+4);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], offset);
	

	
	if(l == 0)
	{	
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+1;
		genJMP_S32(offset);
		g_nCmpdJmpAddress = offset;
		return INST_CMPD_RESULT_INNERJUMP;		
	}
	else
	{
		return INST_CMPD_RESULT_FUNCTION;
	}
}

static s32 agbCPUCompiler_ARM_COND(u32 inst, u32 pc, u32 first, u32 offset)
{	
	(void)pc;
	static u32 jmpaddr_offset, jmpaddr_offset_special;
	static u32 special_offset;
	u32 cond = (inst>>28)&0xF;
	if(cond == 0xe)
		return INST_CMPD_RESULT_NORMAL;
	else
	{
		if(first == 1)
		{
			jmpaddr_offset = 0;
			jmpaddr_offset_special = 0;
			special_offset = 0;
			

			u32 jmp_offset = 0;
			switch(cond)
			{
			case 0: //EQ
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 1://NE
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 2://CS
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 3://CC
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 4://NS
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 1);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 5://NC
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 6://VS
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 1);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 7://VC
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
				jmpaddr_offset = g_nCmpdBufLength;
				genJNE_S32(jmp_offset);
				break;
			case 8://HI
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1);
				jmpaddr_offset_special = g_nCmpdBufLength+2;
				special_offset = 13;
				genJNE_S32(jmp_offset);				
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 9://LS
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0);				
				genJEQ_S32(13);
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 0xA://GE
				genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
				genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 0xB://LT
				genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
				genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJEQ_S32(jmp_offset);
				break;
			case 0xC://GT
				genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
				genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
				jmpaddr_offset_special = g_nCmpdBufLength+2;
				special_offset = 13;
				genJNE_S32(jmp_offset);
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJNE_S32(jmp_offset);
				break;
			case 0xD://LE
				genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1);				
				genJEQ_S32(17);
				genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
				genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
				jmpaddr_offset = g_nCmpdBufLength+2;
				genJEQ_S32(jmp_offset);
				break;
			}
		}
		else
		{
			*(u32*)(g_pCmpdBuf + jmpaddr_offset) = offset;
			if(jmpaddr_offset_special != 0)
				*(u32*)(g_pCmpdBuf + jmpaddr_offset_special) = offset + special_offset;			
		}
		return INST_CMPD_RESULT_CONDITION;
	}
}

static s32 agbCPUCompiler_ARM_MRS(u32 inst, u32 pc)
{
	(void)pc;
	u32 sbz = (inst&0xFFF);
	u32 rd = (inst>>12)&0xF;
	u32 sbo = (inst>>16)&0xF;
	u32 r = (inst>>22)&0x1;

	
	assert(sbz == 0x0);
	assert(sbo == 0xF);
	assert(rd != 15);

	if(r == 0) //CPSR
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[16]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[17]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	return INST_CMPD_RESULT_NORMAL;
}


static s32 agbCPUCompiler_ARM_MSR(u32 inst, u32 pc)
{
	u32 imm = (inst&0xFF);
	u32 rotate = (inst>>8)&0xF;
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 c10 = (inst>>20)&0x3;
	u32 r = (inst>>22)&0x1;
	u32 opcode = (inst>>23)&0x1F;

	assert(rd == 0xF);
	assert(c10 == 0x2);
	if(opcode == 0x6) //imm
	{
		assert(0);
//		u32 c_out;
//		u32 operand;
		rotate<<=1;
//		if(rotate == 0)
//		{
//			operand = imm;
//		}
//		else
//		{
//			c_out = (imm>>(rotate-1))&1?1:0;
//			operand = ((imm<<(32-rotate))|(imm>>rotate));
//		}
		//genMOV_EAX_U32(operand);
	}
	else if(opcode == 0x2) //rn 
	{		
	}
	else
		assert(0);
	
	//rn ->field
	if(r == 0) //CPSR
	{
		genMOV_EAX_U32(0);
		genPUSH_EAX();

		if(opcode == 0x02)
		{
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[imm]);
			genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CPUMODE], CPU_MODE_USER);
			genJEQ_S32(5*g_nAgbCpuBitsSet[rn&0x7]);
			if((rn&0x1) == 0)	
				genAND_EAX_U32(0xFFFFFF00);
			if((rn&0x2) == 0)
				genAND_EAX_U32(0xFFFF00FF);
			if((rn&0x3) == 0)
				genAND_EAX_U32(0xFF00FFFF);
			if((rn&0x4) == 0)
				genAND_EAX_U32(0x00FFFFFF);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		}
		else //IMM
			assert(0);

		genAND_EAX_S8(0x1F);
		genPUSH_EAX();
		genCALL((u32)agbCPUSwitchMode);
		genADD_ESP_U8(8);

		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[16]);
		genCALL((u32)agbCPUUpdateFlags);
		g_nCmpdJmpAddress = -1;
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], pc+4);
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else  //SPSR
	{
		if(opcode == 0x2) //RM
		{
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[imm]);
			genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CPUMODE], CPU_MODE_SYS);
			genJEQ_S32(5*g_nAgbCpuBitsSet[rn] + 7 + 6 + 5);
			genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CPUMODE], CPU_MODE_USER);
			genJEQ_S32(5*g_nAgbCpuBitsSet[rn] + 5);
			if((rn&0x1) == 0)	
				genAND_EAX_U32(0xFFFFFF00);
			if((rn&0x2) == 0)
				genAND_EAX_U32(0xFFFF00FF);
			if((rn&0x3) == 0)
				genAND_EAX_U32(0xFF00FFFF);
			if((rn&0x4) == 0)
				genAND_EAX_U32(0x00FFFFFF);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[17]);
			return INST_CMPD_RESULT_NORMAL;
		}
		else
			assert(0);
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_OP_S_RN_RD_SHIFTA_SHIFT_0_RM(u32 inst, u32 pc)
{
	u32 rm = (inst&0xF);
	u32 c = (inst>>4)&0x1;	
	u32 shift = (inst>>5)&0x3;
	u32 shifta = (inst>>7)&0x1F;
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 s = (inst>>20)&0x1;
	u32 opcode = (inst>>21)&0xF;
	u32 rs = (shifta>>1)&0xF;
	
	
	//zhfang test
	//simple shift...
	if(rm == 15)
		genMOV_EAX_U32(pc+8);
	else
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	if(shift == 0x0)//LSL
	{
		if(c == 0)		
			genLSL_EAX(shifta);		
		else
		{
			genMOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
			genLSL_EAX_CL();
		}

	}
	else if(shift == 0x1) //LSR
	{
		if(c == 0)
		{			
			genLSR_EAX(shifta);
		}
		else
		{
			genMOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
			genLSR_EAX_CL();	
		}
	}
	else if(shift == 0x2) //ASR
	{
		if(c == 0)
		{		
			if(shifta == 0)
			{
				genASR_EAX(16);
				genASR_EAX(16);
			}
			else
				genASR_EAX(shifta);
		}
		else
		{
			genMOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
			genASR_EAX_CL();
		}
	}
	else if(shift == 0x3) //ROR
	{
		if(c == 0)
		{			
			genROR_EAX(shifta);
		}
		else
		{
			genMOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
			genROR_EAX_CL();
		}
	}
	else
		assert(0);	
	
	if(s == 1 && rd != 15)
	{
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CPUCOUT], 0);
		genSetCFlag((u32)&g_nAgbCPUReg[REG_CPUCOUT]);
	}
	
	

	
	if(opcode == 0x0) //AND
	{		
		genAND_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x1) //EOR
	{
		genEOR_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x02)//SUB
	{
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x4) //ADD
	{
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x5) //ADC
	{
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x9) //TEQ
	{
		genEOR_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);		
	}
	else if(opcode == 0xA) //CMP
	{
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);		
	}
	else if(opcode == 0xC)//ORR
	{
		genORR_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0xD)//MOV
	{
		genADD_EAX_U32(0);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}	
	else
		assert(0);
	//1 5 9

	//5:ADC E:BIC B:CMN 1:EOR F:MVN C:ORR 3:RSB 7:RSC 6:SBC 9:TEQ

	if(s == 1 && rd == 15)
	{
		genMOV_EAX_U32(0);
		genPUSH_EAX();
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[17]);
		genAND_EAX_S8(0x1F);
		genPUSH_EAX();
		genCALL((u32)agbCPUSwitchMode);
		genADD_ESP_U8(8);
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else if(s == 1 || opcode == 0x9 || opcode == 0xA)
	{
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);

		if(!(opcode == 0x0 || opcode == 0x01 || opcode == 0x9 || opcode == 0x0D)) //MOV/EOR/TEQ/AND
		{
			genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
			genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
		}
		
		if(opcode == 0x0 || opcode == 0x01 || opcode == 0x9 || opcode == 0x0D) //MOV/EOR/TEQ/AND
		{
			//set cflag == cout
			if(shift == 0 && shifta == 0)
			{
				//because cout == old cflag,so do nothing
			}
			else
			{
				genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUCOUT]);
				genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CFLAG]);
			}
		}
		else if(opcode == 0x4 || opcode == 0x5) //ADD/ADC
		{
			genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
			genSetCFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
		}
		else if(opcode == 0x2 || opcode == 0xA) //SUB/CMP
		{
			genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
			genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		}		
		else
			assert(0);
	}	
	return INST_CMPD_RESULT_NORMAL;

}

static s32 agbCPUCompiler_ARM_LDRSTR_REGOFFSET(u32 inst, u32 pc)
{
	u32 rm = (inst&0xF);
//	u32 c0 = (inst>>4)&0x1;
	u32 shift = (inst>>5)&0x3;
	u32 shift_imm = (inst>>7)&0x1F;	
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 l = (inst>>20)&0x1;
	u32 w = (inst>>21)&0x1;
	u32 b = (inst>>22)&0x1;
	u32 u = (inst>>23)&0x1;
	u32 p = (inst>>24)&0x1;
	
	assert(p == 1);
	assert(w == 0);

	if(l == 0)
	{
		if(b == 0)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		else
			genMOV_EAX_MEM8((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}

	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		if(shift == 0x0) //LSL
			genLSL_EAX(shift_imm);
		else if(shift == 0x1) //LSR
		{
			if(shift_imm == 0)
				genMOV_EAX_U32(0);
			else
				genLSR_EAX(shift_imm);
		}
		else if(shift == 0x2) //ASR
		{
			if(shift_imm == 0)
			{
				genASR_EAX(30);
				genASR_EAX(2);
			}
			else
				genASR_EAX(shift_imm);
		}
		else if(shift == 0x3) //ROR
		{
			if(shift_imm == 0)
				assert(0);
			else
			{
				genMOV_ECX_U32(shift_imm);
				genROR_EAX_CL();				
			}
		}
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
	}
	
	if(rn != 15)
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		if(u == 1)
		{
			genADD_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		}
		else
		{
			genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		}
	}
	else
	{
		genMOV_EAX_U32(pc + 8);
		if(u == 1)
		{
			genADD_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		}
		else
		{
			genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		}

	}
	genPUSH_EAX();
	
	if(l == 0)//STR
	{
		if(b == 0)
			genCALL((u32)agbMemWrite32);
		else
			genCALL((u32)agbMemWrite8);
		genADD_ESP_U8(8);
		return INST_CMPD_RESULT_NORMAL;
	}
	else if(l == 1)//LDR
	{		
		if(b == 0)
			genCALL((u32)agbMemRead32);
		else
		{
			genCALL((u32)agbMemRead8);
			genMOVZX_EAX_AL();
		}
		genADD_ESP_U8(4);

		if(rd == 15)
		{
			genAND_EAX_U32(0xFFFFFFFE);
		}
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
		if(rd == 15)
		{
			g_nCmpdJmpAddress = -1;
			return INST_CMPD_RESULT_OUTERJUMP;
		}
		return INST_CMPD_RESULT_NORMAL;

	}
	return INST_CMPD_RESULT_UNKOWN_INST;
}

static s32 agbCPUCompiler_ARM_LDRSTR_IMMOFFSET(u32 inst, u32 pc)
{
	u32 imm = (inst&0xFFF);
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 l = (inst>>20)&0x1;
	u32 w = (inst>>21)&0x1;
	u32 b = (inst>>22)&0x1;
	u32 u = (inst>>23)&0x1;
	u32 p = (inst>>24)&0x1;
	


	if(l == 0)
	{
		if(b == 0)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		else
			genMOV_EAX_MEM8((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}
	
	if(rn == 15)
		genMOV_EAX_U32(pc + 8);
	else
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	if(p == 1)
	{			
		if(u == 1)
			genADD_EAX_U32(imm);
		else
			genSUB_EAX_U32(imm);
		genPUSH_EAX();
		if(w == 1)
		{
			assert(rn != 15);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
		}
	}		
	else if(p == 0)
	{
		genPUSH_EAX();
		if(u == 1)
			genADD_EAX_U32(imm);
		else
			genSUB_EAX_U32(imm);
		assert(rn != 15);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
	}	
	if(l == 0)//STR
	{
		if(b == 0)
			genCALL((u32)agbMemWrite32);
		else
			genCALL((u32)agbMemWrite8);
		genADD_ESP_U8(8);
		return INST_CMPD_RESULT_NORMAL;
	}
	else if(l == 1)//LDR
	{		
		if(b == 0)
			genCALL((u32)agbMemRead32);
		else
		{
			genCALL((u32)agbMemRead8);
			genMOVZX_EAX_AL();
		}
		genADD_ESP_U8(4);

		if(rd == 15)
		{
			genAND_EAX_U32(0xFFFFFFFE);
		}
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
		if(rd == 15)
		{
			g_nCmpdJmpAddress = -1;
			return INST_CMPD_RESULT_OUTERJUMP;
		}
		return INST_CMPD_RESULT_NORMAL;

	}
	return INST_CMPD_RESULT_UNKOWN_INST;
}

static s32 agbCPUCompiler_ARM_B_BX_1(u32 inst)
{
	u32 rm = (inst&0xF);
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[15]);
	g_nCmpdJmpAddress = -1;
	return INST_CMPD_RESULT_OUTERJUMPEX;
}

static s32 agbCPUCompiler_ARM_RN_RLIST(u32 inst) //Load/Store multiple
{
	u32 rlist = (inst&0xFFFF);
	u32 rn = (inst>>16)&0xF;
	u32 l = (inst>>20)&0x1;
	u32 w = (inst>>21)&0x1;
	u32 s = (inst>>22)&0x1;
	u32 u = (inst>>23)&0x1;
	u32 p = (inst>>24)&0x1;

	u32 rct = g_nAgbCpuBitsSet[rlist&0xFF] + g_nAgbCpuBitsSet[rlist>>8];


	assert(s == 0);	

	//assert(p == 1);
	
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	if(u == 0)
	{	
		genSUB_EAX_U32(rct*4);	
	}
	else
	{
		genADD_EAX_U32(rct*4);
	}
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
	
	if(u == 0)
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		if(p == 0)
			genADD_EAX_S8(0x4);
	}
	else
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		if(p == 1)
			genADD_EAX_S8(0x4);
	}

	genAND_EAX_S8(0xFC);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
	
	for(int i=0;i<16;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{
			if(l == 0)  //STR
			{			
				genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[i]);
				genPUSH_EAX();
			}
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genPUSH_EAX();
			if(l == 0)//STR
			{
				genCALL((u32)agbMemWrite32);
				genADD_ESP_U8(8);
			}
			else //LDR
			{
				genCALL((u32)agbMemRead32);
				genADD_ESP_U8(4);
				genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[i]);
			}
			
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genADD_EAX_S8(0x4);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		}
	}
	if(w == 1) //write to rn
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);			
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_LDRSTRH_RN_RD_HI_LO(u32 inst, u32 pc) //LDRSTRH  LDRSTRSHB
{
	(void)pc;
	u32 lo = (inst&0xF);
//	u32 flag = (inst>>4)&0xF;
	u32 hi = (inst>>8)&0xF;
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 l = (inst>>20)&0x1;
	u32 w = (inst>>21)&0x1;
	u32 b = (inst>>22)&0x1;
	u32 u = (inst>>23)&0x1;
	u32 p = (inst>>24)&0x1;
	u32 rm = lo;
	u32 s = (inst>>6)&0x1;
	u32 h = (inst>>5)&0x1;
	
	u32 offset;

	if(l==0)//STR
	{
		genMOV_EAX_MEM16((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}

	if(b == 1)//Imm offset
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		if(p == 1)
		{
			offset = (hi<<4)|lo;		
			if(u == 1)
				genADD_EAX_U32(offset);
			else
				genSUB_EAX_U32(offset);
			genPUSH_EAX();
			if(w == 1)
				genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
		}
		else
		{
			genPUSH_EAX();
			offset = (hi<<4)|lo;		
			if(u == 1)
				genADD_EAX_U32(offset);
			else
				genSUB_EAX_U32(offset);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
		}
	}
	else //reg offset
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);		
		if(p == 1)
		{			
			if(u == 1)			
				genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);			
			else
				genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
			genPUSH_EAX();
			if(w == 1)
				genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
		}		
		else if(p == 0)
		{
			genPUSH_EAX();
			if(u == 1)			
				genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);			
			else
				genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
		}		
	}

	if(l== 0)//STR
	{
		assert(h == 1);
		assert(s == 0);
		genCALL((u32)agbMemWrite16);
		genADD_ESP_U8(8);
	}
	else //LDR
	{
		if(h == 1)
		{
			genCALL((u32)agbMemRead16);
			if(s == 0)
				genMOVZX_EAX_AX();
			else
				genMOVSX_EAX_AX();
		}
		else
		{
			assert(s == 1);
			genCALL((u32)agbMemRead8);
			genMOVSX_EAX_AL();
		}
		genADD_ESP_U8(4);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
		if(rd == 15)
		{
			return INST_CMPD_RESULT_OUTERJUMP;
		}
	}	
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_MULL(u32 inst, u32 pc)
{
	u32 rm = (inst&0xF);
//	u32 c1001 = (inst>>4)&0xF;
	u32 rs = (inst>>8)&0xF;
	u32 lo = (inst>>12)&0xF;
	u32 hi = (inst>>16)&0xF;
	u32 s = (inst>>20)&0x1;
	u32 a = (inst>>21)&0x1;
	u32 u = (inst>>22)&0x1;

	assert(lo != 15);
	assert(hi != 15);

	if(rm == 15 && rs == 15)
	{
		assert(0);
	}
	if(rs == 15)
	{
		genMOV_EAX_U32(pc+8);
	}
	else if(rm == 15)
		genMOV_EAX_U32(pc+8);
	else
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);

	if(u == 0) //UMULL/UMLAL
	{
		if(rs != 15)
			genMUL_EAX_MEM32((u32)&g_nAgbCPUReg[rs]);
		else
			genMUL_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	}
	else //SMULL/SMLAL
	{
		if(rs != 15)
			genIMUL_EAX_MEM32((u32)&g_nAgbCPUReg[rs]);
		else
			genIMUL_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	}

	if(a == 1) //Accumulate
	{		
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[lo]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[lo]);
		genADC_EDX_MEM32((u32)&g_nAgbCPUReg[hi]);
		genMOV_MEM_EDX32((u32)&g_nAgbCPUReg[hi]);
	}
	else
	{
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[lo]);
		genMOV_MEM_EDX32((u32)&g_nAgbCPUReg[hi]);

	}
	if(s == 1)
	{
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);				
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);		
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_MUL(u32 inst, u32 pc)
{
	u32 rm = (inst&0xF);
	u32 c1001 = (inst>>4)&0xF;
	u32 rs = (inst>>8)&0xF;	
	u32 rd = (inst>>16)&0xF;
//	u32 s = (inst>>20)&0x1;

	assert(c1001 == 0x9);
	assert(rd != 15);
	assert(rs != 15);
	assert(rm != 15);
	
	
	if(rm == 15)
		genMOV_EAX_U32(pc+8);
	else
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);

	if(rs == 15)
		genIMUL_EAX_U32(pc +8);
	else
		genIMUL_EAX_MEM32((u32)&g_nAgbCPUReg[rs]);

	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	return INST_CMPD_RESULT_NORMAL;
}

//volatile void ArmFunc_0xB0FF()
//{
//	u64 a;
//	u32 b;
//	u32 c;
//
//	b = (u32)0xFFFFFFFF;
//	c = (u32)20;
//	a = 0xFFFFFFFF;
//	a = a + g_nAgbCPUReg[0]*g_nAgbCPUReg[1];
//}

s32 agbCPUCompiler_Arm(u32 inst, u32 pc)
{
	s32 rv = INST_CMPD_RESULT_UNKOWN_INST;
	s32 cond_rv;

	u32 start_offset;
	cond_rv = agbCPUCompiler_ARM_COND(inst, pc, 1, 0);
	start_offset = g_nCmpdBufLength;

	int mct = 0;
	
	if((inst&0x0E000010) == 0x00000000 && (inst&0x01900000)!= 0x01000000) //op immedaite shift
	{
		mct++;
	}
	if((inst&0x0FB000F0) == 0x01000000) //move reg to status reg
	{
		mct++;
	}
	if((inst&0x0FB000F0) == 0x01200000) //move reg to status reg
	{
		mct++;
	}	
	if((inst&0x0E000090) == 0x00000010 && (inst&0x01900000) != 0x01000000) //op rm shift
	{
		mct++;
	}
	if((inst&0x0FFFFFF0) == 0x012FFF10) //B/BX(1)
	{
		mct++;
	}
	if((inst&0xFC000F0) == 0x00000090) //MUL
	{
		mct++;
	}
	if((inst&0x0F8000F0) == 0x00800090) //MULL
	{
		mct++;
	}
	if((inst&0x0E0000F0) == 0x000000B0) //Load/Store HalfWord
	{
		mct++;
	}
	if((inst&0x0E1000D0) == 0x001000D0) //Load signed HalfWord
	{
		mct++;
	}
	if((inst&0x0E000000) == 0x02000000) //OP {s} RD,RN,ROR Imm
	{
		mct++;
	}
	if((inst&0x0E000000) == 0x04000000)// load/store immediate offset
	{
		mct++;
	}
	if((inst&0x0E000000) == 0x06000000)// load/store immedregiate offset
	{
		mct++;
	}
	if((inst&0x0E000000) == 0x08000000) //Load/Store multiple
	{
		mct++;
	}
	if((inst&0x0E000000) == 0x0A000000)//B/BL simm24
	{
		mct++;
	}
	assert(mct == 1);

	if((inst&0x0E000010) == 0x00000000 && (inst&0x01900000)!= 0x01000000) //op immedaite shift
	{
		rv = agbCPUCompiler_ARM_OP_S_RN_RD_SHIFTA_SHIFT_0_RM(inst, pc);
	}
	else if((inst&0x0FB000F0) == 0x01000000) //move reg to status reg
	{
		rv = agbCPUCompiler_ARM_MRS(inst, pc);
	}
	else if((inst&0x0FB000F0) == 0x01200000) //move reg to status reg
	{
		rv = agbCPUCompiler_ARM_MSR(inst, pc);
	}	
	else if((inst&0x0E000090) == 0x00000010 && (inst&0x01900000) != 0x01000000) //op rm shift
	{
		rv = agbCPUCompiler_ARM_OP_S_RN_RD_SHIFTA_SHIFT_0_RM(inst, pc);
	}
	else if((inst&0x0FFFFFF0) == 0x012FFF10) //B/BX(1)
	{
		rv = agbCPUCompiler_ARM_B_BX_1(inst);
	}
	else if((inst&0xFC000F0) == 0x00000090) //MUL
	{
		rv = agbCPUCompiler_ARM_MUL(inst, pc);
	}
	else if((inst&0x0F8000F0) == 0x00800090) //MULL
	{
		rv = agbCPUCompiler_ARM_MULL(inst, pc);
	}
	else if((inst&0x0E0000F0) == 0x000000B0) //Load/Store HalfWord
	{
		rv = agbCPUCompiler_ARM_LDRSTRH_RN_RD_HI_LO(inst, pc);
	}
	else if((inst&0x0E1000D0) == 0x001000D0) //Load signed HalfWord
	{
		rv = agbCPUCompiler_ARM_LDRSTRH_RN_RD_HI_LO(inst, pc);
	}
	else if((inst&0x0E000000) == 0x02000000) //OP {s} RD,RN,ROR Imm
	{
		rv = agbCPUCompiler_ARM_OP_S_RN_RD_ROTATE_IMM8(inst, pc);
	}
	else if((inst&0x0E000000) == 0x04000000)// load/store immediate offset
	{
		rv = agbCPUCompiler_ARM_LDRSTR_IMMOFFSET(inst, pc);
	}
	else if((inst&0x0E000000) == 0x06000000)// load/store immedregiate offset
	{
		rv = agbCPUCompiler_ARM_LDRSTR_REGOFFSET(inst, pc);
	}
	else if((inst&0x0E000000) == 0x08000000) //Load/Store multiple
	{
		rv = agbCPUCompiler_ARM_RN_RLIST(inst);
	}
	else if((inst&0x0E000000) == 0x0A000000)//B/BL simm24
	{
		rv = agbCPUCompiler_ARM_B_BL_SIMM24(inst, pc);
	}
	else
		assert(0);

	if(rv != INST_CMPD_RESULT_UNKOWN_INST)
	{
		if(rv == INST_CMPD_RESULT_FUNCTION && cond_rv == INST_CMPD_RESULT_CONDITION)
		{
			genMOV_EAX_U32(g_sCPUCmpData.nJmpBlockNum);
			genReturn();
		}		
		cond_rv = agbCPUCompiler_ARM_COND(inst, pc, 0, g_nCmpdBufLength - start_offset);
	}
	if(rv == INST_CMPD_RESULT_INNERJUMP && cond_rv == INST_CMPD_RESULT_CONDITION)
		rv = INST_CMPD_RESULT_INNERJUMP_COND;
	else if(rv == INST_CMPD_RESULT_FUNCTION && cond_rv == INST_CMPD_RESULT_CONDITION)
		rv = INST_CMPD_RESULT_FUNCTION_COND;
	else if(rv != INST_CMPD_RESULT_NORMAL && cond_rv == INST_CMPD_RESULT_CONDITION)
		assert(0);
	return rv;
}
