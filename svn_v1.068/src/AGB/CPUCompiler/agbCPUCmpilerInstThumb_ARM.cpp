/**
* @file agbCPUCompilerInstThumb.h
* @author zhfang
* @date 2009.12.27
* @brief AGB Emulate For CTR - Cmp Thumb Inst
*/
#include <assert.h>
#include "..\..\trlHeader.h"
#include "..\agbMemory.h"
#include "..\agbCPU.h"
#include "..\agbCPUData.h"
#include "agbCPUCmpData.h"
#include "agbCPUCmpilerGenArm.h"

static s32 agbCPUCompiler_PUSH(u16 inst)
{
	u32 rlist = inst&0xFF;
	u32 rflag = (inst>>8)&0x1;
	u32 rct = g_nAgbCpuBitsSet[rlist];

	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[13]);
	genARMN_SUB_REG_REG_U8(0, 0, rct*4+ rflag * 4);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);
	
	genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_CPUTEMP]);
	genARMN_BIC_REG_REG_U32(0, 0, 0x3);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);

	for(int i=0;i<8;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{
			//Write Reg To Stack(call agbMemWrite32)
			genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[i]);			
			genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_CPUADDRESS]);			
			genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");			

			//Modify the Stack Point
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genARMN_ADD_REG_REG_U8(0, 0, 0x4);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);
		}
	}
	if(rflag == 1)
	{
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[14]);			
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");		
	}

	genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_CPUTEMP]);	
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[13], 0, 1);
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_POP(u16 inst)
{
	u32 rlist = inst&0xFF;
	u32 rflag = (inst>>8)&0x1;
	u32 rct = g_nAgbCpuBitsSet[rlist];

	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[13]);
	genARMN_ADD_REG_REG_U8(0, 0, rct*4+ rflag * 4);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);
	
	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[13]);
	genARMN_BIC_REG_REG_U32(0, 0, 0x3);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);

	for(int i=0;i<8;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{
			//Read Reg from Stack(call agbMemRead32)
			genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genARMM_CALL((u32)agbMemRead32, "agbMemRead32");			
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[i], 0, 1);

			//Modify the Stack Point
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genARMN_ADD_REG_REG_U8(0, 0, 0x4);
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);
		}
	}
	if(rflag == 1)
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		genARMM_CALL((u32)agbMemRead32, "agbMemRead32");			
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[15], 0, 1);
	}
	
	genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[13], (u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);	
	if(rflag == 1)
	{
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_OUTERJUMP;
	}
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_MOV3(u16 inst, u32 pc)
{
	u32 rd = (inst&0x7);
	u32 rm = (inst>>3)&0x7;
	u32 h2 = (inst>>6)&0x1;
	u32 h1 = (inst>>7)&0x1;
	if(h1 == 1)
		rd += 8;
	if(h2 == 1)
		rm += 8;


	if(rm == 15)
		genARMM_MOV_REG_U32(0, pc+4);		
	else
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rm]);	
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	if(rd == 15)
	{
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_OUTERJUMP;
	}
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_OP_SP_IMM7x4(u16 inst)
{
	u32 flag = (inst>>7)&0x1;
	u32 imm7 = inst&0x7f;
	imm7<<=2;

	if(flag)
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[13]);
		genARMN_SUB_REG_REG_U32(0, 0, imm7);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[13], 0, 1);
	}
	else
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[13]);
		genARMN_ADD_REG_REG_U32(0, 0, imm7);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[13], 0, 1);
	}
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_OP_RD_PC_IMM8x4(u16 inst, u32 pc)
{
	u32 imm8 = (inst&0xff);
	imm8 <<=2;
	u32 rd = (inst>>8)&0x7;

	//zhfang test
	//if only complier the rom code, the PC at this time is knonw, so can be opt
	if(pc>=0x08000000)//fast but only in rom
	{
		u32 value = agbMemRead32(pc+4+imm8);
		genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[rd], value, 0, 1);
	}
	else
	{
		genARMM_MOV_REG_U32(0, pc + 4);
		genARMN_ADD_REG_REG_U32(0, 0, imm8);
		genARMM_CALL((u32)agbMemRead32, "agbMemRead32");
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	}
	return INST_CMPD_RESULT_NORMAL;
}
s32 agbCPUCompiler_OP_RD_RN_IMM3(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm3 = (inst>>6)&0x7;
	u32 flag = (inst>>9)&0x1;
	
	genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rn]);
	if(flag == 0)
		genARMN_ADDS_REG_REG_U8(0, 0, imm3);		
	else
		genARMN_SUBS_REG_REG_U8(0, 0, imm3);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);

	genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
	genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
	genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
	genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_OP_RD_RN_IMM5x2(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm5 = (inst>>6)&0x1f;
	u32 flag = (inst>>11)&0x1;

	imm5<<=1;
	if(flag == 0)//STRH
	{
		genARMM_MOV_REG_MEM16(1,(u32)&g_nAgbCPUReg[rd]);		
	}	
	genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rn]);
	genARMN_ADD_REG_REG_U8(0, 0, imm5);		
	if(flag == 1)//LDRH
	{
		genARMM_CALL((u32)agbMemRead16, "agbMemRead16");		
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	}
	else//STRH
	{
		genARMM_CALL((u32)agbMemWrite16, "agbMemWrite16");		
	}
	return INST_CMPD_RESULT_NORMAL;
}
s32 agbCPUCompiler_OP_RD_IMM8(u16 inst)
{
	u32 imm8 = (inst&0xff);
	u32 rd = (inst>>8)&0x7;
	u32 flag = (inst>>11)&0x3;


	
	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
	if(flag == 0) //MOV
		genARMN_MOVS_REG_U8(0, imm8);
	else if(flag == 1) //CMP
		genARMN_OP_REG_U32("CMP", 0, imm8);		
	else if(flag == 2)
		genARMN_ADDS_REG_REG_U8(0, 0, imm8);
	else
		genARMN_SUBS_REG_REG_U8(0, 0, imm8);
	if(flag != 1)
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	
	

	genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
	genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);	
	if(flag != 0)
	{
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);		
	}
	return INST_CMPD_RESULT_NORMAL;
}
s32 agbCPUCompiler_OP_RD_SP_IMM8(u16 inst)
{
	u32 imm8 = (inst&0xff);
	u32 rd = (inst>>8)&0x7;
	u32 flag = (inst>>11)&0x1;

	imm8<<=2;

	if(flag == 0)//STR
	{
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rd]);		
	}

	genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[13]);
	genARMN_ADD_REG_REG_U32(0, 0, imm8);
	if(flag == 0)//STR
	{
		genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");		
	}
	else
	{
		genARMM_CALL((u32)agbMemRead32, "agbMemRead32");
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	}
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_OP_RD_RN_IMM5_x4(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm5 = (inst>>6)&0x1f;
	u32 lflag = (inst>>11)&0x1;
	u32 bflag = (inst>>12)&0x1;

	if(bflag == 0)
		imm5<<=2;


	if(lflag == 0)//STR
	{
		if(bflag == 0)
			genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rd]);
		else
			genARMM_MOV_REG_MEM8(1, (u32)&g_nAgbCPUReg[rd]);		
	}

	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
	genARMN_ADD_REG_REG_U8(0, 0, imm5);	
	if(lflag == 0)//STR
	{
		if(bflag == 0)
			genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");
		else
			genARMM_CALL((u32)agbMemWrite8, "agbMemWrite8");		
	}
	else
	{
		if(bflag == 0)
		{
			genARMM_CALL((u32)agbMemRead32, "agbMemRead32");
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
		}
		else
		{
			genARMM_CALL((u32)agbMemRead8, "agbMemRead8");
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
		}		
	}
	return INST_CMPD_RESULT_NORMAL;
}
s32 agbCPUCompiler_OP_RD_RM_IMM5(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm5 = (inst>>6)&0x1f;
	u32 shift = (inst>>11)&0x3; //0b00:LSL 0b01:LSR 0b10:ASR


	//zhfang test.... simple shift,don't consider special condition
	genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rn]);
	if(shift == 0x0)//LSL
		genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 1, "LSL", imm5, 1);
	else if(shift == 0x1) //LSR
	{
		if(imm5 == 0)
			imm5 = 32;
		genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 1, "LSR", imm5, 1);
	}
	else if(shift == 0x2) //ASR
		genARMM_OP_RD_RM_SHIFT_VALUE("MOV", 0, 1, "ASR", imm5, 1);
	else
		assert(0);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);

	

	genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
	genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
	genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);	
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_OP_RD_RN_RM(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 rm = (inst>>6)&0x7;
	u32 flag = (inst>>9)&0x1;

	genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rn]);
	genARMM_MOV_REG_MEM32(2,(u32)&g_nAgbCPUReg[rm]);
	if(flag == 0) //ADD
		genARMN_ADD_REG_REG_REG(0, 1, 2);
	else
		genARMN_SUB_REG_REG_REG(0, 1, 2);
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);	
	
	genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
	genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
	genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
	genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_BL_BLH(u16 inst, u32 pc)
{
	u32 nextinst = agbMemRead16(pc+2);	
	assert( (nextinst&0xF800) == 0xF800);	
	u32 h = (nextinst>>11)&0x3;
	s32 offset1 = (inst&0x7ff);
	if( (inst&0x400) != 0)
		offset1 |= 0xFFFFF800;
	u32 offset2 = (nextinst&0x7ff);
	offset1<<=12;
	offset1 += (pc+4);
	offset1 += (offset2<<1);

	if(h == 0x1)
		offset1 &= 0xFFFFFFFC;
	g_nCmpdJmpAddress = offset1;

	//function call
	genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)offset1, 0, 1);
	genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[14], (pc+4)|1, 0, 1);
	if(h == 0x1)
		return INST_CMPD_RESULT_FUNCTIONX;
	else if(h == 0x3)
		return INST_CMPD_RESULT_FUNCTION;
	else
	{
		assert(0);
		return INST_CMPD_RESULT_UNKOWN_INST;
	}
}

s32 agbCPUCompiler_OP_RD_RM(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rm = (inst>>3)&0x7;
	u32 opcode = (inst>>6)&0xF;



	if(opcode == 0x0 || opcode == 0x1 || opcode == 0xC || opcode == 0xD)//AND, EOR, ORR, MUL
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);
		if(opcode == 0x0)//AND
			genARMN_OP_REG_REG_REG("AND", 0, 0, 1, 1);			
		else if(opcode == 0x1)//EOR
			genARMN_OP_REG_REG_REG("EOR", 0, 0, 1, 1);			
		else if(opcode == 0xC)//ORR
			genARMN_OP_REG_REG_REG("ORR", 0, 0, 1, 1);			
		else if(opcode == 0xD)//MUL
		{
			genARMN_OP_REG_REG_REG("MUL", 2, 0, 1, 1);
			//genARMM_OP_RD_RM_SHIFT_VALUE("MUL", 0, 1, "LSL", 0);
		}
		if(opcode == 0xD)
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 2, 1);
		else
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);

		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);		
	}
	else if(opcode == 0x2 || opcode == 0x3 || opcode == 0x4 ||opcode == 0x7)//LSL, LSR, ASR, ROR
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);
		if(opcode == 0x2)//LSL
			genARMM_OP_RD_RM_SHIFT_RS("MOV", 0, 0, "LSL", 1, 1);
		else if(opcode == 0x3)//LSR
			genARMM_OP_RD_RM_SHIFT_RS("MOV", 0, 0, "LSR", 1, 1);
		else if(opcode == 0x4)//ASR
			genARMM_OP_RD_RM_SHIFT_RS("MOV", 0, 0, "ASL", 1, 1);
		else if(opcode == 0x7)//ROR
			genARMM_OP_RD_RM_SHIFT_RS("MOV", 0, 0, "ROR", 1, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);

		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
	}
	else if(opcode == 0x5 || opcode == 0x6)//ADC, SBC
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);
		genARMM_MOV_REG_MEM32(2, (u32)&g_nAgbCPUReg[REG_CFLAG]);
		if(opcode == 0x5)//ADC
		{
			genARMN_ADDS_REG_REG_REG(0, 0, 2);
			genARMN_ADDS_REG_REG_REG(0, 0, 1);
		}
		else if(opcode == 0x6)//SBC
		{
			genARMN_SUBS_REG_REG_REG(0, 0, 2);
			genARMN_SUBS_REG_REG_REG(0, 0, 1);
		}
		genARM_MOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
	}
	else if(opcode == 0x8)//TST
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);

		genARMN_OP_REG_REG("TST", 0, 1, 1);
		
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);		
	}
	else if(opcode == 0x9)//NEG
	{
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rm]);
		genARMN_OP_REG_REG_U32("RSB", 0, 1, 0, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);

		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
	}
	else if(opcode == 0xA || opcode == 0xB)//CMP, CMN
	{

		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);
		if(opcode == 0xA)
			genARMN_OP_REG_REG("CMP", 0, 1, 1);
		else if(opcode == 0xB)
			genARMN_OP_REG_REG("CMN", 0, 1, 1);
		
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
	}
	else if(opcode == 0xE)//BIC
	{
		genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);

		genARMM_OP_RD_RN_RM_SHIFT_VALUE("BIC", 0, 0, 1, "LSL", 0, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);

		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);		
	}
	else if(opcode == 0xF)//MVN
	{
		
		genARMM_MOV_REG_MEM32(1, (u32)&g_nAgbCPUReg[rm]);
		genARMN_OP_REG_REG("MVN", 0, 1, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
	}
	return INST_CMPD_RESULT_NORMAL;
}
s32 agbCPUCompiler_Bcond_IMM(u16 inst, u32 pc)
{
	s32 offset = (inst&0xFF);
	u32 cond = (inst>>8)&0xF;
	if( (offset&0x80) != 0)
		offset |= 0xFFFFFF00;
	offset<<=1;
	offset = pc+ 4 + offset;
	g_nCmpdJmpAddress = offset;
	s32 jmp_offset = g_nCmpdJmpAddress;	
	switch(cond)
	{
	case 0: //EQ
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 1://NE
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 2://CS
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 3://CC
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 4://NS
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 1, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 5://NC
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 6://VS
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 1, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 7://VC
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 8://HI
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1, 0);
		genARMN_JNE_S32_TEMP(g_nCmpdJmpTemp);
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		genARMM_TEMPLABEL(g_nCmpdJmpTemp++);
		break;
	case 9://LS
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ",jmp_offset);
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1, 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);		
		break;
	case 0xA://GE
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
		genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		break;
	case 0xB://LT
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
		genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);		
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("NE", jmp_offset);
		break;
	case 0xC://GT
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
		genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
		genARMN_JNE_S32_TEMP(g_nCmpdJmpTemp);
		
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 0);		
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);
		genARMM_TEMPLABEL(g_nCmpdJmpTemp++);
		break;
	case 0xD://LE
		genARMM_CMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1, 0);		
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("EQ", jmp_offset);

		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[REG_NFLAG]);
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[REG_VFLAG]);
		genARMM_OP_RN_RM_SHIFT_VALUE("CMP", 0, 1, "LSL", 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genARMN_JCOND_S32("NE", jmp_offset);
		break;
	}	
	return INST_CMPD_RESULT_INNERJUMP_COND;
}

s32 agbCPUCompiler_BX_BLX(u16 inst, u32 pc)
{
	u32 rm = (inst>>3)&0x7;
	u32 h2 = (inst>>6)&0x1;
	u32 lflag = (inst>>7)&0x1;

	if(h2 == 1)
		rm += 8;
	if(lflag)
		genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[14], pc + 2, 0, 1);
	genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[15],(u32)&g_nAgbCPUReg[rm], 0, 1);
	g_nCmpdJmpAddress = -1;
	return INST_CMPD_RESULT_OUTERJUMPEX;
}
s32 agbCPUCompiler_OP_LS_RD_RN_RM(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 rm = (inst>>6)&0x7;
	u32 opcode = (inst>>9)&0x7;


	if(opcode < 3)//STR
	{
		if(opcode == 0) //STR
			genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rd]);
		else if(opcode == 1) //STRH
			genARMM_MOV_REG_MEM16(1,(u32)&g_nAgbCPUReg[rd]);
		else //STRB
			genARMM_MOV_REG_MEM8(1,(u32)&g_nAgbCPUReg[rd]);		
	}

	genARMM_MOV_REG_MEM32(2,(u32)&g_nAgbCPUReg[rn]);
	genARMM_MOV_REG_MEM32(3,(u32)&g_nAgbCPUReg[rm]);
	genARMN_OP_REG_REG_REG("ADD", 0, 2, 3);	
	if(opcode < 3)//STR
	{
		if(opcode == 0) //STR
			genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");
		else if(opcode == 1) //STRH
			genARMM_CALL((u32)agbMemWrite16, "agbMemWrite16");
		else //STRB
			genARMM_CALL((u32)agbMemWrite8, "agbMemWrite8");		
	}
	else
	{
		if(opcode == 3)//LDRSB
		{
			genARMM_CALL((u32)agbMemRead8, "agbMemRead8");
			genARMN_SXTB_REG_REG(0, 0);
		}
		else if(opcode == 4)//LDR
		{
			genARMM_CALL((u32)agbMemRead32, "agbMemRead32");
		}
		else if(opcode == 5)//LDRH
		{
			genARMM_CALL((u32)agbMemRead16, "agbMemRead16");			
		}
		else if(opcode == 6)//LDRB
		{
			genARMM_CALL((u32)agbMemRead8, "agbMemRead8");
		}
		else if(opcode == 7)//LDRSH
		{
			genARMM_CALL((u32)agbMemRead16, "agbMemRead16");
			genARMN_SXTH_REG_REG(0, 0);
		}		
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	}
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_B_IMM(u16 inst, u32 pc)
{
	s32 offset = (inst&0x7ff);
	if( (offset &0x400) != 0)
		offset |= 0xFFFFF800;
	offset<<=1;
	offset = pc + 4 +offset;

	
	
	genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)offset, 0, 1);
	
	g_nCmpdJmpAddress = offset;
	return INST_CMPD_RESULT_INNERJUMP;
}

s32 agbCPUCompiler_OP_H1H2_RM_RD(u16 inst, u32 pc)
{
	(void)pc;
	u32 rd = (inst&0x7);
	u32 rm = (inst>>3)&0x7;
	u32 h2 = (inst>>6)&01;
	u32 h1 = (inst>>7)&0x1;
	u32 opcode = (inst>>8)&0x3;

	if(h1 == 1)
		rd += 8;
	if(h2 == 1)
		rm += 8;

	if(opcode == 0x0) //ADD
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rm]);
		genARMN_OP_REG_REG_REG("ADD", 0, 0, 1);
		genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
		if(rd != 15)
			return INST_CMPD_RESULT_NORMAL;
		else
		{
			g_nCmpdJmpAddress = -1;
			return INST_CMPD_RESULT_OUTERJUMP;
		}
	}	
	else if(opcode == 0x1) //CMP
	{
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[rd]);
		genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[rm]);
		genARMN_OP_REG_REG("CMP", 0, 1);

		genARMM_MEM_SETN((u32)&g_nAgbCPUReg[REG_NFLAG], 0, 1);
		genARMM_MEM_SETZ((u32)&g_nAgbCPUReg[REG_ZFLAG], 0, 1);
		genARMM_MEM_SETC((u32)&g_nAgbCPUReg[REG_CFLAG], 0, 1);
		genARMM_MEM_SETV((u32)&g_nAgbCPUReg[REG_VFLAG], 0, 1);
		return INST_CMPD_RESULT_NORMAL;

	}
	else if(opcode == 0x2) //MOV
	{
		genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[rd], (u32)&g_nAgbCPUReg[rm], 0, 1);
		if(rd != 15)
			return INST_CMPD_RESULT_NORMAL;
		else
		{
			g_nCmpdJmpAddress = -1;
			return INST_CMPD_RESULT_OUTERJUMP;
		}
	}
	else
	{
		assert(0);
		return INST_CMPD_RESULT_UNKOWN_INST;
	}
}

s32 agbCPUCompiler_LDRSTR_RN_RLIST(u16 inst, u32 pc)
{
	(void)pc;
	u32 rlist = (inst&0xFF);
	u32 rn = (inst>>8)&0x7;
	u32 l = (inst>>11)&0x1;
	
	u32 rct = g_nAgbCpuBitsSet[rlist];

	genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[rn]);
	genARMM_ADD_REG_REG_U32(0, 0, rct*4, 1);	
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);
	
	genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS],(u32)&g_nAgbCPUReg[rn], 0, 1);
	
	for(int i=0;i<8;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{			
			if(l == 0)//STR
			{				
				genARMM_MOV_REG_MEM32(1,(u32)&g_nAgbCPUReg[i]);				
			}
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUADDRESS]);			
			if(l == 0)//STR
			{
				genARMM_CALL((u32)agbMemWrite32, "agbMemWrite32");				
			}
			else
			{
				genARMM_CALL((u32)agbMemRead32, "agbMemRead32");				
				genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[i], 0, 1);

			}

			//Modify the Stack Point
			genARMM_MOV_REG_MEM32(0, (u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genARMM_ADD_REG_REG_U32(0, 0, 0x4, 1);			
			genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[REG_CPUADDRESS], 0, 1);
		}
	}
	
	genARMM_MOV_MEM_MEM32((u32)&g_nAgbCPUReg[rn],(u32)&g_nAgbCPUReg[REG_CPUTEMP], 0, 1);
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_SWI(u16 inst, u32 pc)
{
	u32 swino = (inst&0xF);
	genARMM_MOV_MEM_U32((u32)&g_nAgbCPUReg[15], pc+4, 0, 1);
	genARMM_MOV_REG_U32(0, swino);	
	genARMM_CALL((u32)agbCPUSWI_NOPRE, "agbCPUSWI_NOPRE");	
	g_nCmpdJmpAddress = -1;
	return INST_CMPD_RESULT_SWI;
}
s32 agbCPUCompiler_ADDSUB_SPPC_IMM8x4(u16 inst, u32 pc)
{
	u32 imm = (inst&0xFF);
	u32 rd = (inst>>8)&0x7;
	u32 flag = (inst>>11)&0x1;
	imm*=4;

	if(flag == 0) //PC
		genARMM_MOV_REG_U32(0, pc+4);		
	else //SP
		genARMM_MOV_REG_MEM32(0,(u32)&g_nAgbCPUReg[13]);
	genARMM_ADD_REG_REG_U32(0, 0, imm, 1);	
	genARMM_MOV_MEM_REG32((u32)&g_nAgbCPUReg[rd], 0, 1);
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_Thumb_ARM(u16 inst, u32 pc)
{
	s32 rv;

	if( (inst & 0xFE00) == 0xB400)//PUSH
	{
		rv = agbCPUCompiler_PUSH(inst);
	}
	else if( (inst & 0xFE00) == 0xBC00)//POP
	{
		//zhfang test
		//POP to reg[15],this will break out
		rv = agbCPUCompiler_POP(inst);
	}
	else if( (inst & 0xFF00) == 0x4600)//MOV3 Rd Rm
	{
		rv = agbCPUCompiler_MOV3(inst, pc);
	}
	else if( (inst & 0xFF00) == 0xB000)//ADD7 /SUB4 ADD/SUB SP IMM7*4
	{
		rv = agbCPUCompiler_OP_SP_IMM7x4(inst);
	}
	else if( (inst & 0xF800) == 0x4800)//LDR Rd, [PC, #imm8*4]
	{
		rv = agbCPUCompiler_OP_RD_PC_IMM8x4(inst, pc);
	}
	else if((inst&0xFC00) == 0x1C00)//ADD/SUB Rd, Rn, #imm3
	{
		rv = agbCPUCompiler_OP_RD_RN_IMM3(inst);
	}
	else if((inst&0xF000) == 0x8000)//LDRH/STRH Rd, [Rn, #imm5*2]
	{
		rv = agbCPUCompiler_OP_RD_RN_IMM5x2(inst);

	}
	else if((inst&0xE000) == 0x2000)//MOV/CMP/ADD/SUB Rd, #imm8
	{
		rv = agbCPUCompiler_OP_RD_IMM8(inst);

	}
	else if((inst&0xF000) == 0x9000)//LDR/STR Rd, [SP, #imm8]
	{
		rv = agbCPUCompiler_OP_RD_SP_IMM8(inst);

	}
	else if((inst&0xE000) == 0x6000)// LDR/STR Rd, [Rn,#imm5*4] LDRB/STRB Rd, [Rn,#imm5]
	{
		rv = agbCPUCompiler_OP_RD_RN_IMM5_x4(inst);
	}
	else if((inst&0xE000) == 0x0000 && ((inst&0x1800) != 0x1800))//SHIFT Rd, Rm, #imm5
	{
		rv = agbCPUCompiler_OP_RD_RM_IMM5(inst);
	}
	else if((inst&0xFC00) == 0x1800)//ADD/SUB Rd, Rn, Rm
	{
		rv = agbCPUCompiler_OP_RD_RN_RM(inst);
	}
	else if((inst&0xF800)== 0xF000)// BL BLH
	{
		rv = agbCPUCompiler_BL_BLH(inst, pc);
	}
	else if( (inst&0xFC00) == 0x4000)//OPCODE Rd, Rm
	{
		rv = agbCPUCompiler_OP_RD_RM(inst);
	}
	else if((inst&0xF000) == 0xD000 && (inst&0x0F00)<0x0E00)//B <cond> imm
	{
		rv = agbCPUCompiler_Bcond_IMM(inst, pc);
	}
	else if((inst&0xFF00)== 0x4700)//BLX BX
	{
		rv = agbCPUCompiler_BX_BLX(inst, pc);
	}
	else if((inst&0xF000) == 0x5000)//LDR/STR (S)(B/H) Rd, [Rn, Rm]
	{
		rv = agbCPUCompiler_OP_LS_RD_RN_RM(inst);
	}
	else if((inst&0xF800) == 0xE000)//B offset
	{
		rv = agbCPUCompiler_B_IMM(inst, pc);
	}
	else if((inst&0xFC00) == 0x4400 && (inst&0x300)!= 0x0300) //OP H1 H2 RM RD
	{
		rv = agbCPUCompiler_OP_H1H2_RM_RD(inst, pc);
	}
	else if((inst&0xF000) == 0xC000) //Load/Store multiple
	{
		rv = agbCPUCompiler_LDRSTR_RN_RLIST(inst, pc);
	}
	else if((inst&0xFF00) == 0xDF00) //SWI
	{
		rv = agbCPUCompiler_SWI(inst, pc);
	}
	else if((inst&0xF000) == 0xA000) //ADD/SUB Rd, SP/PC, imm8*4
	{
		rv = agbCPUCompiler_ADDSUB_SPPC_IMM8x4(inst, pc);
	}
	else
	{
		rv = INST_CMPD_RESULT_UNKOWN_INST;//unkown inst
	}
	return rv;
}

