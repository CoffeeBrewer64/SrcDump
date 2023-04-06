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
#include "agbCPUCmpilerGenArm.h"


static s32 agbCPUCompiler_ARM_OP_S_RN_RD_ROTATE_IMM8(u32 inst, u32 pc)
{
	u32 imm = (inst&0xFF);
	u32 rotate = (inst>>8)&0xF;
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 s = (inst>>20)&0x1;
	u32 opcode = (inst>>21)&0xF;
	
//	u32 c_out;
	u32 operand;
	rotate<<=1;
	if(rotate == 0)
	{
		operand = imm;
	}
	else
	{		
		operand = ((imm<<(32-rotate))|(imm>>rotate));
//		c_out = ((operand>>31)&0x1);
	}

	
	if(opcode == 0x0)//AND
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_REG_U32("AND", 1, 0, operand, s);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 1, 0);
	}
	else if(opcode == 0x2)//SUB
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_REG_U32("SUB", 1, 0, operand, s);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 1, 0);
	}
	else if(opcode == 0x4)//ADD
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_REG_U32("ADD", 0, 0, operand, s);
		//genARMM_ADD_REG_REG_U32(0, 0, operand, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	}
	else if(opcode == 0x5)//ADC
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMM_ADD_REG_REG_U32(0, 0, operand, 1);		
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_CFLAG]);
		genARMN_ADDS_REG_REG_REG(0, 0, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);		
	}	
	else if(opcode == 0xB)//CMN
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_REG_U32("CMN", 1, 0, operand);		
	}	
	else if(opcode == 0xD)//MOV
	{
		assert(rn == 0);		
		genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[rd], operand, 0, 1);
		if(s == 0)
			genARMN_ADDS_REG_REG_U8(0, 0, 0);		
	}
	else if(opcode == 0xE)//BIC
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_REG_U32("BIC", 1, 0, operand);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 1, 0);
	}	
	else if(opcode == 0xC) //ORR
	{
		if(rn != 15)
		{			
			genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rn]);
			genARMN_OP_REG_REG_U32("ORR", 1, 0, operand);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 1, 0);			
		}
		else
		{
			genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[rd], operand|(pc+8), 0, 1);			
		}
	}
	else if(opcode == 0xA)//CMP
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_U32("CMP", 0, operand, 0);
		//genARMN_SUB_REG_REG_U32(0, 0, operand);		
	}
	else if(opcode == 0x8) //TST
	{
		if(rn != 15)
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		else
			genARMM_MOV_REG_U32(0, pc + 8);
		genARMN_OP_REG_U32("TST", 0, operand);		
	}
	else if(opcode == 0x3) //RSB
	{
		if(rn != 15)
		{			
			genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rn]);
		}
		else
		{
			genARMM_MOV_REG_U32(0, pc+8);
		}
		genARMN_OP_REG_REG_U32("RSB", 1, 0, operand);
	}
	else
		assert(0);

	//1: EOR 0xF:MVN  0x3:RSB 0x7:RSC 0x6:SBC
	//8:TST 0x9:TEQ

	if(s == 1 && rd == 15)
	{
		genARMM_MOV_REG_U32(1, 0);
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[17]);
		genARMN_AND_REG_REG_U8(0, 0, 0x1F);
		genARMM_CALL((u32)agbCPUSwitchMode, "agbCPUSwitchMode");		
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else if(s == 1)
	{
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);		
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
	{		
		genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[14], pc+4, 0, 1);
	}
	genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], offset, 0, 1);
	

	
	if(l == 0)
	{		
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
	(void)pc, (void)offset;
	//static u32 jmpaddr_offset, jmpaddr_offset_special;
	//static u32 special_offset;
	u32 cond = (inst>>28)&0xF;
	if(cond == 0xe)
		return INST_CMPD_RESULT_NORMAL;
	else
	{
		if(first == 1)
		{
			//jmpaddr_offset = 0;
			//jmpaddr_offset_special = 0;
			//special_offset = 0;
			

//			u32 jmp_offset = 0;
			switch(cond)
			{
			case 0: //EQ
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 1://NE
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 2://CS
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 3://CC
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 4://NS
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 1, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 5://NC
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 6://VS
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 1, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 7://VC
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 8://HI
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1, 0);
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				genARM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 9://LS
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 0);
				genARMN_JEQ_S32_COND(g_nCmpdCondJmpOL);

				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL + 1);
				genARMM_LABEL_FOR_COND(g_nCmpdCondJmpOL++);
				break;
			case 0xA://GE
				genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
				genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
				genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 0xB://LT
				genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
				genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
				genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JEQ_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 0xC://GT
				genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
				genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
				genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);

				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JNE_S32_COND(g_nCmpdCondJmpOL);
				break;
			case 0xD://LE
				genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1, 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JEQ_S32_COND(g_nCmpdCondJmpOL);

				genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
				genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
				genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
				//jmpaddr_offset = g_nCmpdBufLength+2;
				genARMN_JEQ_S32_COND(g_nCmpdCondJmpOL+1);
				genARMM_LABEL_FOR_COND(g_nCmpdCondJmpOL++);
				break;
			}
		}
		else
		{
			/**(u32*)(g_pCmpdBuf + jmpaddr_offset) = offset;
			if(jmpaddr_offset_special != 0)
				*(u32*)(g_pCmpdBuf + jmpaddr_offset_special) = offset + special_offset;	*/
			genARMM_LABEL_FOR_COND(g_nCmpdCondJmpOL++);
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
		genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[rd],(u32)&g_nAgbCPUReg[16], 0, 1);
	}
	else
	{
		genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[rd],(u32)&g_nAgbCPUReg[17], 0, 1);
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
		//u32 c_out;
		//u32 operand;
		rotate<<=1;
		//if(rotate == 0)
		//{
		//	operand = imm;
		//}
		//else
		//{
		//	c_out = (imm>>(rotate-1))&1?1:0;
		//	operand = ((imm<<(32-rotate))|(imm>>rotate));
		//}
		//genARM_MOV_EAX_U32(operand);
	}
	else if(opcode == 0x2) //rn 
	{		
	}
	else
		assert(0);
	
	//rn ->field
	if(r == 0) //CPSR
	{
		genARMN_MOV_REG_U8(1, 0);

		if(opcode == 0x02)
		{			
			//zhfang test
			//cur work
			genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[imm]);			
			genARMM_MOV_REG_MEM32(2,(u32)&g_nAgbCPUReg[REG_CPUMODE]);

			genARMN_JEQ_S32_TEMP(g_nCmpdJmpTemp);
			
			if((rn&0x1) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF);
			if((rn&0x2) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF00);
			if((rn&0x3) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF0000);
			if((rn&0x4) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF000000);
			genARMM_TEMPLABEL(g_nCmpdJmpTemp++);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUVALUE], 0, 2);
		}
		else //IMM
			assert(0);

		genARMN_AND_REG_REG_U8(0,0,0x1F);
		genARMM_CALL((u32)agbCPUSwitchMode, "agbCPUSwitchMode");		
		
		genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[16], (u32)&g_nAgbCPUReg[REG_CPUVALUE], 0, 1);

		genARMM_CALL((u32)agbCPUUpdateFlags, "agbCPUUpdateFlags");
		g_nCmpdJmpAddress = -1;

		genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], pc+4, 0, 1);
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else  //SPSR
	{
		if(opcode == 0x2) //RM
		{
			
			genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CPUMODE], CPU_MODE_SYS, 2);
			genARMN_JEQ_S32_TEMP(g_nCmpdJmpTemp);
			genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CPUMODE], CPU_MODE_USER, 2);
			genARMN_JEQ_S32_TEMP(g_nCmpdJmpTemp);

			genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[imm]);
			
			if((rn&0x1) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF);
			if((rn&0x2) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF00);
			if((rn&0x3) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF0000);
			if((rn&0x4) == 0)
				genARMN_BIC_REG_REG_U32(0,0,0xFF000000);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[17], 0, 1);
			genARMM_TEMPLABEL(g_nCmpdJmpTemp++);
			return INST_CMPD_RESULT_NORMAL;
		}
		else
			assert(0);
	}
	return INST_CMPD_RESULT_UNKOWN_INST;
}
/*
static s32 agbCPUCompiler_ARM_OP_S_RN_RD_RS_SHIFT_RM(u32 inst ,u32 pc)
{
	u32 rm = (inst&0xF);
	u32 c1 = (inst>>4)&0x1;
	assert(c1 == 1);
	u32 shift = (inst>>5)&0x3;
	u32 rs = (inst>>8)&0xF;
	u32 rd = (inst>>12)&0xF;
	u32 rn = (inst>>16)&0xF;
	u32 s = (inst>>20)&0x1;
	u32 opcode = (inst>>21)&0xF;
	u32 rs = (shifta>>1)&0xF;
	
	assert(rm != 15);
	assert(rd != 15);
	assert(rs != 15);
	assert(rn != 15);
	//zhfang test
	//simple shift...
	
	genARM_MOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	genARM_MOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
	if(shift == 0x0)//LSL
	{
		genARM_LSL_EAX(shifta);		
	}
	else if(shift == 0x1) //LSL Rs
	{
		genARM_MOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
		genARM_LSL_EAX_CL();
	}
	else if(shift == 0x2) //LSR
	{
		genARM_LSR_EAX(shifta);
	}
	else if(shift == 0x3) //LSR Rs
	{
		genARM_MOV_ECX_MEM32((u32)&g_nAgbCPUReg[rs]);
		genARM_LSR_EAX_CL();		
	}
	else
		assert(0);
	
	//shift
	//0x4: ASR
	if(s == 1 && rd != 15)
	{
		genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CPUCOUT], 0);
		genARM_SetCFlag((u32)&g_nAgbCPUReg[REG_CPUCOUT]);
	}
	assert(rn != 15);
	

	if(opcode == 0xD)//MOV
		genARM_MOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	else if(opcode == 0x0) //AND
	{		
		genARM_AND_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genARM_MOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0x4) //ADD
	{
		genARM_ADD_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genARM_MOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else if(opcode == 0xA) //CMP
	{
		genARM_MOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		if(rm == 15)
			genARM_SUB_EAX_U32(pc+8);
		else
			genARM_SUB_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	}
	else if(opcode == 0x02)//SUB
	{
		genARM_MOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		genARM_MOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
		genARM_SUB_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUVALUE]);
		genARM_MOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else
		assert(0);

	//

	if(s == 1 && rd == 15)
	{
		genARM_MOV_EAX_U32(0);
		genARM_PUSH_EAX();
		genARM_MOV_EAX_MEM32((u32)&g_nAgbCPUReg[17]);
		genARM_AND_EAX_S8(0x1F);
		genARM_PUSH_EAX();
		genARM_CALL((u32)agbCPUSwitchMode);
		genARM_ADD_ESP_U8(8);
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else if(s == 1)
	{
		genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);		
		genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		genARM_SetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genARM_SetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		genARM_SetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
		
		if(opcode == 0x0D || opcode == 0x0) //MOV/AND
		{
			genARM_MOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUCOUT]);
			genARM_MOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CFLAG]);			
		}
		else if(opcode == 0x4) //ADD
		{
			genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
			genARM_SetCFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
		}
		else if(opcode == 0xA) //CMP
		{
			genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
			genARM_SetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		}
		else if(opcode == 0x2) //SUB
		{
			genARM_MOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
			genARM_SetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		}
		else
			assert(0);
	}
	return INST_CMPD_RESULT_NORMAL;
}
*/
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
	char *shiftname[4] = 
	{
		"LSL",
		"LSR",
		"ASR",
		"ROR"
	};

	char *opname[16] = 
	{
		"AND", //0
		"EOR", //1
		"SUB", //2
		"RSB", //3
		"ADD", //4
		"ADC", //5
		"SBC", //6
		"RSC", //7
		"TST", //8
		"TEQ", //9
		"CMP", //A
		"CMN", //B
		"ORR", //C
		"MOV", //D
		"BIC", //E
		"MVN", //F
	};
	//zhfang test
	//simple shift...

	if(c == 1)
		genARMM_MOV_REG_MEM32(3, (u32)&g_nAgbCPUReg[rs]);

	if(rm == 15)
		genARMM_MOV_REG_U32(2, pc+8);
	else
		genARMM_MOV_REG_MEM32(2,(u32)&g_nAgbCPUReg[rm]);
	genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rn]);

	
	if(c == 1) //Rm Shift Rs
	{
		if(opcode == 0x9 || opcode == 0xA)
		{
			genARMM_OP_RN_RM_SHIFT_RS(opname[opcode], 1, 2, shiftname[shift], 3, s);
		}
		else if(opcode == 0xD)
		{
			genARMM_OP_RN_RM_SHIFT_RS(opname[opcode], 0, 2, shiftname[shift], 3, s);
		}
		else
		{
			genARMM_OP_RD_RN_RM_SHIFT_RS(opname[opcode], 0, 1, 2, shiftname[shift], 3, s);
		}
	}
	else //Rm Shift Value
	{
		if(opcode == 0x9 || opcode == 0xA)
		{
			genARMM_OP_RN_RM_SHIFT_VALUE(opname[opcode], 1, 2, shiftname[shift], shifta, s);
		}
		else if(opcode == 0xD)
		{
			genARMM_OP_RN_RM_SHIFT_VALUE(opname[opcode], 0, 2, shiftname[shift], shifta, s);
		}
		else
		{
			if(shift == 2 && shifta == 0)
				shifta = 32;
			genARMM_OP_RD_RN_RM_SHIFT_VALUE(opname[opcode], 0, 1, 2, shiftname[shift], shifta, s);
		}
	}
	if(opcode == 0x9 || opcode == 0xA)
	{
	}
	else
	{
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	}

	if(s == 1 && rd == 15)
	{
		genARMM_MOV_REG_U32(1, 0);
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[17]);
		genARMN_AND_REG_REG_U8(0, 0, 0x1F);
		genARMM_CALL((u32)agbCPUSwitchMode, "agbCPUSwitchMode");		
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_SWITCHCMODE;
	}
	else if(s == 1 || opcode == 0x9 || opcode == 0xA) //TEQ/CMP
	{
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		
		if(!(opcode == 0x0 || opcode == 0x01 || opcode == 0x9 || opcode == 0x0D)) //MOV/EOR/TEQ/AND
		{
			genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
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
				genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);				
			}
		}
		else if(opcode == 0x4 || opcode == 0x5) //ADD/ADC
		{
			genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		}
		else if(opcode == 0x2 || opcode == 0xA) //SUB/CMP
		{
			genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
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
			genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rd]);
		else
			genARMM_MOV_REG_MEM8(1,(u32)&g_nAgbCPUReg[rd]);		
	}

	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rm]);
		if(shift == 0x0) //LSL
		{
			genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 0, "LSL", shift_imm);
		}
		else if(shift == 0x1) //LSR
		{
			if(shift_imm == 0)
				genARMM_MOV_REG_U32(0, 0);
			else
				genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 0, "LSR", shift_imm);				
		}
		else if(shift == 0x2) //ASR
		{
			if(shift_imm == 0)
			{
				genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 0, "ASR", 32);				
			}
			else
				genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 0, "ASR", shift_imm);
		}
		else if(shift == 0x3) //ROR
		{
			if(shift_imm == 0)
				assert(0);
			else
			{
				genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 0, "ROR", shift_imm);				
			}
		}
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);
	}
	
	if(rn != 15)
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		genARMM_MOV_REG_MEM32(2, (u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		if(u == 1)
		{
			genARMN_ADD_REG_REG_REG(0, 0, 2);			
		}
		else
		{
			genARMN_SUB_REG_REG_REG(0, 0, 2);
		}
	}
	else
	{
		genARMM_MOV_REG_U32(0, pc + 8);
		genARMM_MOV_REG_MEM32(2, (u32)&g_nAgbCPUReg[REG_CPUTEMP]);
		if(u == 1)
		{
			genARMN_ADD_REG_REG_REG(0, 0, 2);			
		}
		else
		{
			genARMN_SUB_REG_REG_REG(0, 0, 2);
		}
	}	
	
	if(l == 0)//STR
	{
		if(b == 0)
			genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");
		else
			genARMM_CALL((u32)agbMemWrite8, "agbMemWrite8");		
		return INST_CMPD_RESULT_NORMAL;
	}
	else if(l == 1)//LDR
	{		
		if(b == 0)
			genARMM_CALL((u32)agbMemRead32, "agbMemRead32");
		else
		{
			genARMM_CALL((u32)agbMemRead8, "agbMemRead8");
			genARMN_AND_REG_REG_U8(0, 0, 0xFF);
		}		

		if(rd == 15)
		{
			genARMN_BIC_REG_REG_U32(0, 0, 0x1);			
		}
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
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
			genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rd]);		
		else		
			genARMM_MOV_REG_MEM8(1, (u32)&g_nAgbCPUReg[rd]);
	}
	
	if(rn == 15)
		genARMM_MOV_REG_U32(0, pc + 8);		
	else		
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
	if(p == 1)
	{			
		genARMM_MOV_REG_U32(2, imm);
		if(u == 1)
			genARMN_ADD_REG_REG_REG(0, 0, 2);			
		else
			genARMN_SUB_REG_REG_REG(0, 0, 2);		
		if(w == 1)
		{
			assert(rn != 15);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rn], 0, 2);
		}
	}		
	else if(p == 0)
	{
		genARMM_MOV_REG_U32(2, imm);
		if(u == 1)
			genARMN_ADD_REG_REG_REG(2, 0, 2);
		else
			genARMN_SUB_REG_REG_REG(2, 0, 2);
		assert(rn != 15);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rn], 2, 3);		
	}	
	if(l == 0)//STR
	{
		if(b == 0)
			genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");
		else
			genARMM_CALL((u32)agbMemWrite8, "agbMemWrite8");		
		return INST_CMPD_RESULT_NORMAL;
	}
	else if(l == 1)//LDR
	{		
		if(b == 0)
			genARMM_CALL((u32)agbMemRead32, "agbMemRead32");
		else
		{
			genARMM_CALL((u32)agbMemRead8, "agbMemRead8");
			genARMN_AND_REG_REG_U8(0, 0, 0xFF);			
		}		

		if(rd == 15)
		{
			genARMN_BIC_REG_REG_U32(0, 0, 0x3);			
		}
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
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
	genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[15], (u32)&g_nAgbCPUReg[rm], 0, 1);
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
	
	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
	if(u == 0)
	{
		genARMN_SUB_REG_REG_U32(0, 0, rct*4);
	}
	else
	{
		genARMN_ADD_REG_REG_U32(0, 0, rct*4);
	}
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);
	
	if(u == 0)
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUTEMP]);		
		if(p == 0)
			genARMN_ADD_REG_REG_U8(0, 0, 4);
	}
	else
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
		if(p == 1)
			genARMN_ADD_REG_REG_U8(0, 0, 4);
	}
	
	genARMN_BIC_REG_REG_U32(0, 0, 0x3);	
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);
	
	for(int i=0;i<16;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{
			if(l == 0)  //STR
			{			
				genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[i]);				
			}
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUADDRESS]);			
			if(l == 0)//STR
			{
				genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");				
			}
			else //LDR
			{
				genARMM_CALL((u32)agbMemRead32, "agbMemRead32");				
				genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[i], 0, 1);
			}
			
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genARMN_ADD_REG_REG_U8(0, 0, 0x4);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);
		}
	}
	if(w == 1) //write to rn
	{
		genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[rn],(u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);		
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
		genARMM_MOV_REG_MEM16(1,(u32)&g_nAgbCPUReg[rd]);		
	}

	if(b == 1)//Imm offset
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rn]);
		if(p == 1)
		{
			offset = (hi<<4)|lo;		
			if(u == 1)
				genARMM_ADD_REG_REG_U32(0, 0, offset, 2);				
			else
				genARMM_SUB_REG_REG_U32(0, 0, offset, 2);			
			if(w == 1)
				genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rn], 0, 2);
		}
		else
		{
			offset = (hi<<4)|lo;		
			if(u == 1)
				genARMM_ADD_REG_REG_U32(2, 0, offset, 3);
			else
				genARMM_SUB_REG_REG_U32(2, 0, offset, 3);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rn], 2, 3);			
		}
	}
	else //reg offset
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rn]);
		genARMM_MOV_REG_MEM32(2,(u32)&g_nAgbCPUReg[rm]);
		if(p == 1)
		{			
			if(u == 1)
				genARMN_ADD_REG_REG_REG(0, 0, 2);
			else
				genARMN_SUB_REG_REG_REG(0, 0, 2);
			if(w == 1)
				genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rn], 0, 2);
		}		
		else if(p == 0)
		{
			if(u == 1)
				genARMN_ADD_REG_REG_REG(3, 0, 2);
			else
				genARMN_SUB_REG_REG_REG(3, 0, 2);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rn], 3, 2);
		}		
	}

	if(l== 0)//STR
	{
		assert(h == 1);
		assert(s == 0);
		genARMM_CALL((u32)agbMemWrite16, "agbMemWrite16");		
	}
	else //LDR
	{
		if(h == 1)
		{
			genARMM_CALL((u32)agbMemRead16, "agbMemRead16");
			if(s == 0)
			{
				//genARM_MOVZX_EAX_AX();
			}
			else
			{
				genARMN_SXTH_REG_REG(0, 0);				
			}
		}
		else
		{
			assert(s == 1);
			genARMM_CALL((u32)agbMemRead8, "agbMemRead8");
			genARMN_SXTB_REG_REG(0, 0);
		}
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
		if(rd == 15)
		{
			return INST_CMPD_RESULT_OUTERJUMP;
		}
	}	
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_MULL(u32 inst, u32 pc)
{
	(void)pc;
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
	
	assert(rm != 15);
	assert(rs != 15);
	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[lo]);
	genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[hi]);
	genARMM_MOV_REG_MEM32(2, (u32)&g_nAgbCPUReg[rm]);
	genARMM_MOV_REG_MEM32(3, (u32)&g_nAgbCPUReg[rs]);
	if(u == 0)
	{
		if(a == 1)
			genARMN_OP_REG_REG_REG_REG("UMLAL", lo, hi, rm, rs, s);
		else
			genARMN_OP_REG_REG_REG_REG("UMULL", lo, hi, rm, rs, s);
	}
	else
	{
		if(a == 1)
			genARMN_OP_REG_REG_REG_REG("SMLAL", lo, hi, rm, rs, s);
		else
			genARMN_OP_REG_REG_REG_REG("SMULL", lo, hi, rm, rs, s);
	}
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[lo], 0, 2);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[hi], 1, 2);

	if(s == 1)
	{
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);		
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_ARM_MUL(u32 inst, u32 pc)
{
	(void)pc;
	u32 rm = (inst&0xF);
	u32 c1001 = (inst>>4)&0xF;
	u32 rs = (inst>>8)&0xF;	
	u32 rd = (inst>>16)&0xF;
	u32 s = (inst>>20)&0x1;

	assert(c1001 == 0x9);
	assert(rd != 15);
	assert(rs != 15);
	assert(rm != 15);
	
	genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rm]);
	genARMM_MOV_REG_MEM32(2,(u32)&g_nAgbCPUReg[rs]);

	genARMN_OP_REG_REG_REG("MUL", 0, 1, 2, s);
	if(s == 1)
	{
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
	}
	
	return INST_CMPD_RESULT_NORMAL;
}

//volatile static void ArmFunc_0xB0FF()
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
//
//
//

s32 agbCPUCompiler_Arm_ARM(u32 inst, u32 pc)
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
			genARMM_MOV_REG_U32(0,g_sCPUCmpDataOL.nJmpBlockNum);
			genARMM_Return();
			genARMM_LTORG();
		}	
		else if(rv == INST_CMPD_RESULT_INNERJUMP)
		{
			g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+1;
			genARMN_JMP_S32(g_nCmpdJmpAddress);
			genARMM_LTORG();
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


