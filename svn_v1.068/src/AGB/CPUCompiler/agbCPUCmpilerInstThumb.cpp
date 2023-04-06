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
#include "agbCPUCmpilerGenX86.h"

static s32 agbCPUCompiler_PUSH(u16 inst)
{
	u32 rlist = inst&0xFF;
	u32 rflag = (inst>>8)&0x1;
	u32 rct = g_nAgbCpuBitsSet[rlist];

	

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
	genSUB_EAX_S8(rct*4+ rflag * 4);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
	genAND_EAX_S8(0xFC);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);

	for(int i=0;i<8;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{
			//Write Reg To Stack(call agbMemWrite32)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[i]);
			genPUSH_EAX();
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genPUSH_EAX();
			genCALL((u32)agbMemWrite32);
			genADD_ESP_U8(8);

			//Modify the Stack Point
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genADD_EAX_S8(0x4);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		}
	}
	if(rflag == 1)
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[14]);
		genPUSH_EAX();
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		genPUSH_EAX();
		genCALL((u32)agbMemWrite32);
		genADD_ESP_U8(8);
	}

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[13]);
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_POP(u16 inst)
{
	u32 rlist = inst&0xFF;
	u32 rflag = (inst>>8)&0x1;
	u32 rct = g_nAgbCpuBitsSet[rlist];



	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
	genADD_EAX_S8(rct*4+ rflag * 4);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
	genAND_EAX_S8(0xFC);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);

	for(int i=0;i<8;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{
			//Read Reg from Stack(call agbMemRead32)
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genPUSH_EAX();
			genCALL((u32)agbMemRead32);
			genADD_ESP_U8(4);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[i]);

			//Modify the Stack Point
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genADD_EAX_S8(0x4);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		}
	}
	if(rflag == 1)
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		genPUSH_EAX();
		genCALL((u32)agbMemRead32);
		genADD_ESP_U8(4);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[15]);
	}

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[13]);
	if(rflag == 1)
	{
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_OUTERJUMP;
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_MOV3(u16 inst, u32 pc)
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
		genMOV_EAX_U32(pc+4);
	else
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	if(rd == 15)
	{
		g_nCmpdJmpAddress = -1;
		return INST_CMPD_RESULT_OUTERJUMP;
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_OP_SP_IMM7x4(u16 inst)
{
	u32 flag = (inst>>7)&0x1;
	u32 imm7 = inst&0x7f;
	imm7<<=2;

	if(flag)
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
		genSUB_EAX_U32(imm7);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[13]);
	}
	else
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
		genADD_EAX_U32(imm7);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[13]);
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_OP_RD_PC_IMM8x4(u16 inst, u32 pc)
{
	u32 imm8 = (inst&0xff);
	imm8 <<=2;
	u32 rd = (inst>>8)&0x7;

	//zhfang test
	//if only complier the rom code, the PC at this time is knonw, so can be opt
	if(pc>=0x08000000)//fast but only in rom
	{
		u32 value = agbMemRead32(pc+4+imm8);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[rd], value);
	}
	else
	{
		genMOV_EAX_U32(pc+4+imm8);
		genPUSH_EAX();
		genCALL((u32)agbMemRead32);
		genADD_ESP_U8(4);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	return INST_CMPD_RESULT_NORMAL;
}
static s32 agbCPUCompiler_OP_RD_RN_IMM3(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm3 = (inst>>6)&0x7;
	u32 flag = (inst>>9)&0x1;

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	if(flag == 0)
		genADD_EAX_S8(imm3);
	else
		genSUB_EAX_S8(imm3);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
	genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
	genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	genSetZFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);

	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
	if(flag == 0) //ADD	
		genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
	else //SUB
		genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);

	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_OP_RD_RN_IMM5x2(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm5 = (inst>>6)&0x1f;
	u32 flag = (inst>>11)&0x1;

	imm5<<=1;
	if(flag == 0)//STR
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	genADD_EAX_S8(imm5);
	genPUSH_EAX();
	if(flag == 1)//LDR
	{
		genCALL((u32)agbMemRead16);
		genADD_ESP_U8(4);
		genMOVZX_EAX_AX();
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	else//STR
	{
		genCALL((u32)agbMemWrite16);
		genADD_ESP_U8(8);
	}
	return INST_CMPD_RESULT_NORMAL;
}
static s32 agbCPUCompiler_OP_RD_IMM8(u16 inst)
{
	u32 imm8 = (inst&0xff);
	u32 rd = (inst>>8)&0x7;
	u32 flag = (inst>>11)&0x3;


	if(flag == 0)//MOV
	{
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[rd], imm8);
	}
	else
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		if(flag == 2)
			genADD_EAX_U32(imm8);
		else //1 3 //CMP SUB
			genSUB_EAX_U32(imm8);
	}

	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
	genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
	genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	if(flag != 0)
	{
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		if(flag == 2)
			genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		else
			genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
	}
	if(flag>1) //ADD SUB
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	return INST_CMPD_RESULT_NORMAL;
}
static s32 agbCPUCompiler_OP_RD_SP_IMM8(u16 inst)
{
	u32 imm8 = (inst&0xff);
	u32 rd = (inst>>8)&0x7;
	u32 flag = (inst>>11)&0x1;

	imm8<<=2;

	if(flag == 0)//STR
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
	genADD_EAX_U32(imm8);
	genPUSH_EAX();
	if(flag == 0)//STR
	{
		genCALL((u32)agbMemWrite32);
		genADD_ESP_U8(8);
	}
	else
	{
		genCALL((u32)agbMemRead32);
		genADD_ESP_U8(4);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_OP_RD_RN_IMM5_x4(u16 inst)
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
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		else
			genMOV_EAX_MEM8((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	genADD_EAX_U32(imm5);
	genPUSH_EAX();
	if(lflag == 0)//STR
	{
		if(bflag == 0)
			genCALL((u32)agbMemWrite32);
		else
			genCALL((u32)agbMemWrite8);
		genADD_ESP_U8(8);
	}
	else
	{
		if(bflag == 0)
		{
			genCALL((u32)agbMemRead32);
		}
		else
		{
			genCALL((u32)agbMemRead8);
			genMOVZX_EAX_AL();
		}
		genADD_ESP_U8(4);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	return INST_CMPD_RESULT_NORMAL;
}
static s32 agbCPUCompiler_OP_RD_RM_IMM5(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 imm5 = (inst>>6)&0x1f;
	u32 shift = (inst>>11)&0x3; //0b00:LSL 0b01:LSR 0b10:ASR


	//zhfang test.... simple shift,don't consider special condition
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	if(shift == 0x0)//LSL
		genLSL_EAX(imm5);
	else if(shift == 0x1) //LSR
		genLSR_EAX(imm5);
	else if(shift == 0x2) //ASR
		genASR_EAX(imm5);
	else
		assert(0);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
	genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
	genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_OP_RD_RN_RM(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 rm = (inst>>6)&0x7;
	u32 flag = (inst>>9)&0x1;

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	if(flag == 0) //ADD
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	else
		genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
	genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
	genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	if(flag == 0) //ADD
		genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
	else
		genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
	genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_BL_BLH(u16 inst, u32 pc)
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
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)offset1);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[14], (pc+4)|1);	
	if(h == 0x1)
		return INST_CMPD_RESULT_FUNCTIONX;
	else if(h == 0x3)
		return INST_CMPD_RESULT_FUNCTION;
	else
		assert(0);
	return INST_CMPD_RESULT_UNKOWN_INST;
}

static s32 agbCPUCompiler_OP_RD_RM(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rm = (inst>>3)&0x7;
	u32 opcode = (inst>>6)&0xF;



	if(opcode == 0x0 || opcode == 0x1 || opcode == 0xC || opcode == 0xD)//AND, EOR, ORR, MUL
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		if(opcode == 0x0)//AND
			genAND_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		else if(opcode == 0x1)//EOR
			genEOR_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		else if(opcode == 0xC)//ORR
			genORR_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		else if(opcode == 0xD)//MUL
			genIMUL_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);

		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	}
	else if(opcode == 0x2 || opcode == 0x3 || opcode == 0x4 ||opcode == 0x7)//LSL, LSR, ASR, ROR
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		genMOV_ECX_MEM32((u32)&g_nAgbCPUReg[rm]);
		if(opcode == 0x2)//LSL
			genLSL_EAX_CL();
		else if(opcode == 0x3)//LSR
			genLSR_EAX_CL();
		else if(opcode == 0x4)//ASR
			genASR_EAX_CL();
		else if(opcode == 0x7)//ROR
			genROR_EAX_CL();
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
	}
	else if(opcode == 0x5 || opcode == 0x6)//ADC, SBC
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		if(opcode == 0x5)//ADC
		{
			genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
			genADD_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CFLAG]);
		}
		else if(opcode == 0x6)//SBC
		{
			genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
			genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CFLAG]);
		}
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		if(opcode == 0x5)//ADC
			genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		else if(opcode == 0x6)//SBC
			genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
	}
	else if(opcode == 0x8)//TST
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		if(opcode == 0x8)// TST-AND
			genAND_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		else if(opcode == 0x1)//EOR
			genEOR_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		else if(opcode == 0xC)//ORR
			genORR_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	}
	else if(opcode == 0x9)//NEG
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
		genNEG_MEM32((u32)&g_nAgbCPUReg[rd]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
	}
	else if(opcode == 0xA || opcode == 0xB)//CMP, CMN
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		if(opcode == 0xA)//CMP
			genSUB_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		else if(opcode == 0xB)//CMN
			genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		if(opcode == 0xA)//CMP
			genSetNCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		else if(opcode == 0xB)//CMN
			genSetCFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
	}
	else if(opcode == 0xE)//BIC
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		genNOT_EAX();
		genAND_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	}
	else if(opcode == 0xF)//MVN
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		genNOT_EAX();
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);

		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
	}
	return INST_CMPD_RESULT_NORMAL;
}
static s32 agbCPUCompiler_Bcond_IMM(u16 inst, u32 pc)
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
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 1://NE
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 2://CS
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 3://CC
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 4://NS
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 1);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 5://NC
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 6://VS
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 1);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 7://VC
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength;
		genJEQ_S32(jmp_offset);
		break;
	case 8://HI
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 1);
		genJNE_S32(13);
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 9://LS
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 0xA://GE
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 0xB://LT
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJNE_S32(jmp_offset);
		break;
	case 0xC://GT
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
		genJNE_S32(13);
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		break;
	case 0xD://LE
		genCMP_MEM_U8((u32)&g_nAgbCPUReg[REG_ZFLAG], 1);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJEQ_S32(jmp_offset);
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[REG_VFLAG]);
		g_pCmpdJmp[g_nCmpdJmpNum++] = g_nCmpdBufLength+2;
		genJNE_S32(jmp_offset);
		break;
	}	
	return INST_CMPD_RESULT_INNERJUMP_COND;
}

static s32 agbCPUCompiler_BX_BLX(u16 inst, u32 pc)
{
//	u32 sbz = (inst&0x7);
	u32 rm = (inst>>3)&0x7;
	u32 h2 = (inst>>6)&0x1;
	u32 lflag = (inst>>7)&0x1;

	if(h2 == 1)
		rm += 8;
	if(lflag)
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[14], pc + 2);
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[15]);

	g_nCmpdJmpAddress = -1;
	return INST_CMPD_RESULT_OUTERJUMPEX;
}
static s32 agbCPUCompiler_OP_LS_RD_RN_RM(u16 inst)
{
	u32 rd = (inst&0x7);
	u32 rn = (inst>>3)&0x7;
	u32 rm = (inst>>6)&0x7;
	u32 opcode = (inst>>9)&0x7;


	if(opcode < 3)//STR
	{
		if(opcode == 0) //STR
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		else if(opcode == 1) //STRH
			genMOV_EAX_MEM16((u32)&g_nAgbCPUReg[rd]);
		else //STRB
			genMOV_EAX_MEM8((u32)&g_nAgbCPUReg[rd]);
		genPUSH_EAX();
	}

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
	genPUSH_EAX();
	if(opcode < 3)//STR
	{
		if(opcode == 0) //STR
			genCALL((u32)agbMemWrite32);
		else if(opcode == 1) //STRH
			genCALL((u32)agbMemWrite16);
		else //STRB
			genCALL((u32)agbMemWrite8);
		genADD_ESP_U8(8);
	}
	else
	{
		if(opcode == 3)//LDRSB
		{
			genCALL((u32)agbMemRead8);
			genMOVSX_EAX_AL();
		}
		else if(opcode == 4)//LDR
		{
			genCALL((u32)agbMemRead32);
		}
		else if(opcode == 5)//LDRH
		{
			genCALL((u32)agbMemRead16);
			genMOVZX_EAX_AX();
		}
		else if(opcode == 6)//LDRB
		{
			genCALL((u32)agbMemRead8);
			genMOVZX_EAX_AL();
		}
		else if(opcode == 7)//LDRSH
		{
			genCALL((u32)agbMemRead16);
			genMOVSX_EAX_AX();
		}
		genADD_ESP_U8(4);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	}
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_B_IMM(u16 inst, u32 pc)
{
	s32 offset = (inst&0x7ff);
	if( (offset &0x400) != 0)
		offset |= 0xFFFFF800;
	offset<<=1;
	offset = pc + 4 +offset;
	
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], (u32)offset);

	
	g_nCmpdJmpAddress = offset;
	return INST_CMPD_RESULT_INNERJUMP;
}

static s32 agbCPUCompiler_OP_H1H2_RM_RD(u16 inst, u32 pc)
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
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		genADD_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
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
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rd]);
		genCMP_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_NFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_ZFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_CFLAG], 0);
		genMOV_MEM_U32((u32)&g_nAgbCPUReg[REG_VFLAG], 0);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_NFLAG]);
		genSetZFlag((u32)&g_nAgbCPUReg[REG_ZFLAG]);
		genSetNFlag((u32)&g_nAgbCPUReg[REG_CFLAG]);
		genSetVFlag((u32)&g_nAgbCPUReg[REG_VFLAG]);
		return INST_CMPD_RESULT_NORMAL;

	}
	else if(opcode == 0x2)
	{
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rm]);		
		genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
		if(rd != 15)
			return INST_CMPD_RESULT_NORMAL;
		else
		{
			g_nCmpdJmpAddress = -1;
			return INST_CMPD_RESULT_OUTERJUMP;
		}
	}
	return INST_CMPD_RESULT_UNKOWN_INST;
}

static s32 agbCPUCompiler_LDRSTR_RN_RLIST(u16 inst, u32 pc)
{
	(void)pc;
	u32 rlist = (inst&0xFF);
	u32 rn = (inst>>8)&0x7;
	u32 l = (inst>>11)&0x1;
	
	u32 rct = g_nAgbCpuBitsSet[rlist];
	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);
	genADD_EAX_U32(rct*4);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);

	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[rn]);	
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);

	
	for(int i=0;i<8;i++)
	{
		if( ((rlist>>i)&0x1) == 1)
		{			
			if(l == 0)//STR
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
			else
			{
				genCALL((u32)agbMemRead32);
				genADD_ESP_U8(4);
				genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[i]);

			}

			//Modify the Stack Point
			genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
			genADD_EAX_S8(0x4);
			genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[REG_CPUADDRESS]);
		}
	}


	genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[REG_CPUTEMP]);	
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rn]);
	return INST_CMPD_RESULT_NORMAL;
}

static s32 agbCPUCompiler_SWI(u16 inst, u32 pc)
{
	u32 swino = (inst&0xF);
	genMOV_MEM_U32((u32)&g_nAgbCPUReg[15], pc+4);
	genMOV_EAX_U32(swino);
	genPUSH_EAX();		
	genCALL((u32)agbCPUSWI_NOPRE);
	genADD_ESP_U8(4);
	g_nCmpdJmpAddress = -1;
	return INST_CMPD_RESULT_SWI;
}
static s32 agbCPUCompiler_ADDSUB_SPPC_IMM8x4(u16 inst, u32 pc)
{
	u32 imm = (inst&0xFF);
	u32 rd = (inst>>8)&0x7;
	u32 flag = (inst>>11)&0x1;
	imm*=4;

	if(flag == 0) //PC
		genMOV_EAX_U32(pc+4);
	else //SP
		genMOV_EAX_MEM32((u32)&g_nAgbCPUReg[13]);
	genADD_EAX_U32(imm);
	genMOV_MEM_EAX32((u32)&g_nAgbCPUReg[rd]);
	return INST_CMPD_RESULT_NORMAL;
}

s32 agbCPUCompiler_Thumb(u16 inst, u32 pc)
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

