/**
* @file agbCPUThumbCFuncMacro.cpp
* @author zhfang
* @date 2009.12.16
* @brief AGB Emulate For CTR - Macro to create fucntion for Thumb instruction
*/

#define HEADFILE  #include "agbCPUThumbCFunc.h"

#define ENDFILE  \

HEADFILE


#define THUMB_FIRST_PREFETCH\
	g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]);\
	g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2);\
	g_nAgbCPUReg[15] += 2;

#define ARM_FIRST_PREFETCH\
	g_nAgbInsta = agbMemRead32(g_nAgbCPUReg[15]);\
	g_nAgbInstb = agbMemRead32(g_nAgbCPUReg[15] + 4);\
	g_nAgbCPUReg[15] += 4;


#define CASE_8(base) \
	case base:\
	case base+1:\
	case base+2:\
	case base+3:\
	case base+4:\
	case base+5:\
	case base+6:\
	case base+7:

#define NEG(i) ((i) >> 31)
#define POS(i) ((~(i)) >> 31)

#define ADDCARRY(a, b, c) \
	g_bAgbCFlag = ((NEG(a) & NEG(b)) |\
	(NEG(a) & POS(c)) |\
	(NEG(b) & POS(c))) ? true : false;

#define ADDOVERFLOW(a, b, c) \
	g_bAgbVFlag = ((NEG(a) & NEG(b) & POS(c)) |\
	(POS(a) & POS(b) & NEG(c))) ? true : false;

#define SUBCARRY(a, b, c) \
	g_bAgbCFlag = ((NEG(a) & POS(b)) |\
	(NEG(a) & POS(c)) |\
	(POS(b) & POS(c))) ? true : false;

#define SUBOVERFLOW(a, b, c)\
	g_bAgbVFlag = ((NEG(a) & POS(b) & POS(c)) |\
	(POS(a) & NEG(b) & NEG(c))) ? true : false;		

#define LSL_RD_RM_I5\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURm]>>(32-g_nAgbCPUImm5))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURm]<<g_nAgbCPUImm5);

#define LSL_RD_RS\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>(32-g_nAgbCPUReg[g_nAgbCPURs]))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd]<<g_nAgbCPUReg[g_nAgbCPURs];

#define LSR_RD_RM_I5\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURm]>>(g_nAgbCPUImm5-1))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURm]>>g_nAgbCPUImm5);

#define LSR_RD_RS\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>(g_nAgbCPUReg[g_nAgbCPURs]-1))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd]>>g_nAgbCPUReg[g_nAgbCPURs];

#define ASR_RD_RM_IMM5\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURm] >>(g_nAgbCPUImm5-1))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = ((s32)g_nAgbCPUReg[g_nAgbCPURm])>>g_nAgbCPUImm5;

#define ASR_RD_RS\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>(g_nAgbCPUReg[g_nAgbCPURs]-1))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = ((s32)g_nAgbCPUReg[g_nAgbCPURd])>>g_nAgbCPUReg[g_nAgbCPURs];

#define ROR_RD_VALUE\
	g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>(g_nAgbCPUValue-1))&0x1;\
	g_nAgbCPUReg[g_nAgbCPURd] = ((g_nAgbCPUReg[g_nAgbCPURd]<<(32-g_nAgbCPUValue)) | (g_nAgbCPUReg[g_nAgbCPURd]>>g_nAgbCPUValue));


#define THUMB_RD_RM_IMM5_DEFINE\
	g_nAgbCPURd = (g_nAgbInst &0x7);\
	g_nAgbCPURm = (g_nAgbInst>>3)&0x7;\
	g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;

#define THUMB_RD_RN_IMM5_DEFINE\
	g_nAgbCPURd = (g_nAgbInst &0x7);\
	g_nAgbCPURn = (g_nAgbInst>>3)&0x7;\
	g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;

#define THUMB_RD_RS_DEFINE\
	g_nAgbCPURd = (g_nAgbInst &0x7);\
	g_nAgbCPURs = (g_nAgbInst>>3)&0x7;

#define THUMB_RD_RM_DEFINE\
	g_nAgbCPURd = (g_nAgbInst &0x7);\
	g_nAgbCPURm = (g_nAgbInst>>3)&0x7;

#define THUMB_RN_RM_DEFINE\
	g_nAgbCPURn = (g_nAgbInst &0x7);\
	g_nAgbCPURm = (g_nAgbInst>>3)&0x7;

#define THUMB_RM_DEFINE\
	g_nAgbCPURm = (g_nAgbInst>>3)&0x7;

#define THUMB_RD_RN_RM_DEFINE\
	g_nAgbCPURd = (g_nAgbInst &0x7);\
	g_nAgbCPURn = (g_nAgbInst>>3)&0x7;\
	g_nAgbCPURm = (g_nAgbInst>>6)&0x7;

#define THUMB_RD_RN_IMM3_DEFINE\
	g_nAgbCPURd = (g_nAgbInst &0x7);\
	g_nAgbCPURn = (g_nAgbInst>>3)&0x7;\
	g_nAgbCPUImm3 = (g_nAgbInst>>6)&0x7;

#define THUMB_RD_IMM8\
	g_nAgbCPUImm8 = (g_nAgbInst &0xff);\
	g_nAgbCPURd = (g_nAgbInst>>8)&7;

#define NZFLAG_BY_RD\
	g_bAgbNFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;\
	g_bAgbZFlag = (g_nAgbCPUReg[g_nAgbCPURd] == 0);

#define NZFLAG_BY_VALUE\
	g_bAgbNFlag = (g_nAgbCPUValue>>31);\
	g_bAgbZFlag = (g_nAgbCPUValue == 0);

#define THUMB_PC_WRITE\
	if(g_nAgbCPURd == 7)\
{\
	g_nAgbCPUReg[15] &= 0xfffffffe;\
	THUMB_FIRST_PREFETCH\
}

#define PUSH_REG(val, r)\
	if(g_nAgbInst &(val))\
{\
	agbMemWrite32(g_nAgbCPUAddress, g_nAgbCPUReg[(r)]);\
	g_nAgbCPUAddress +=4;\
}

#define POP_REG(val, r)\
	if(g_nAgbInst &(val))\
{\
	g_nAgbCPUReg[(r)] = agbMemRead32(g_nAgbCPUAddress);\
	g_nAgbCPUAddress += 4;\
}

#define THUMB_STM_REG(val, r, b)\
	if(g_nAgbInst &(val))\
{\
	agbMemWrite32(g_nAgbCPUAddress, g_nAgbCPUReg[(r)]);\
	if(!g_nAgbCPUOffset)\
{\
	g_nAgbCPUReg[(b)] = g_nAgbCPUTemp;\
}\
	g_nAgbCPUOffset = 1;\
	g_nAgbCPUAddress +=4;\
}

#define THUMB_LDM_REG(val, r)\
	if(g_nAgbInst &(val))\
{\
	g_nAgbCPUReg[(r)] = agbMemRead32(g_nAgbCPUAddress);\
	g_nAgbCPUAddress+=4;\
}

#define THUMB_BCOND_SIMM8\
	g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1;\
	THUMB_FIRST_PREFETCH



#define AGBCPU_THUMB_FUNC_NAME_PRE\
	void
#define AGBCPU_THUMB_FUNC_NAME_NAME(n) agbCpuThumbCFunc_##n()
#define AGBCPU_THUMB_FUNC_NAME(n)\
	AGBCPU_THUMB_FUNC_NAME_PRE AGBCPU_THUMB_FUNC_NAME_NAME(n)


AGBCPU_THUMB_FUNC_NAME(0x00_0x07)
{
	// LSL Rd, Rm, #Imm5
	THUMB_RD_RM_IMM5_DEFINE
		if(g_nAgbCPUImm5 == 0)
		{
			g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURm];
		}
		else
		{
			LSL_RD_RM_I5
		}
		NZFLAG_BY_RD
}


AGBCPU_THUMB_FUNC_NAME(0x08_0x0f)
{
	// LSR Rd, Rm, #Imm5
	THUMB_RD_RM_IMM5_DEFINE
		if(g_nAgbCPUImm5 == 0)
		{
			g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
			g_nAgbCPUReg[g_nAgbCPURd] = 0;
		}
		else
		{
			LSR_RD_RM_I5
		}
		NZFLAG_BY_RD
}


AGBCPU_THUMB_FUNC_NAME(0x10_0x17)
{
	// ASR Rd, Rm, #Imm5
	THUMB_RD_RM_IMM5_DEFINE
		if(g_nAgbCPUImm5 == 0)
		{
			g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
			g_nAgbCPUReg[g_nAgbCPURd] = 0;
		}
		else
		{
			ASR_RD_RM_IMM5
		}
		NZFLAG_BY_RD
}

AGBCPU_THUMB_FUNC_NAME(0x18_0x19)
{
	// ADD Rd, Rn, Rm
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm];
	NZFLAG_BY_VALUE
		ADDCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue);
	ADDOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue);
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;
}	

AGBCPU_THUMB_FUNC_NAME(0x1a_0x1b)
{
	// SUB Rd, Rs, Rn
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm];
	NZFLAG_BY_VALUE
		SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue);
	SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue);
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;
}

AGBCPU_THUMB_FUNC_NAME(0x1c_0x1d)
{
	// ADD Rd, Rn, #g_nAgbCPUImm3
	THUMB_RD_RN_IMM3_DEFINE
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUImm3;
	NZFLAG_BY_VALUE
		ADDCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUImm3, g_nAgbCPUValue);
	ADDOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUImm3, g_nAgbCPUValue);
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;
}

AGBCPU_THUMB_FUNC_NAME(0x1e_0x1f)
{
	// SUB Rd, Rn, #g_nAgbCPUImm3
	THUMB_RD_RN_IMM3_DEFINE
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUImm3;
	NZFLAG_BY_VALUE
		SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUImm3, g_nAgbCPUValue);
	SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUImm3, g_nAgbCPUValue);
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;			
}	

AGBCPU_THUMB_FUNC_NAME(0x20_0x27)
{
	//MOV Rd, #g_nAgbCPUImm8
	THUMB_RD_IMM8
		g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUImm8;
	NZFLAG_BY_RD
}

AGBCPU_THUMB_FUNC_NAME(0x28_0x2f)
{
	// CMP Rd, #g_nAgbCPUImm8
	THUMB_RD_IMM8
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURd] - g_nAgbCPUImm8;
	NZFLAG_BY_VALUE
		SUBCARRY(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUImm8, g_nAgbCPUValue);
	SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUImm8, g_nAgbCPUValue);
}

AGBCPU_THUMB_FUNC_NAME(0x30_0x37)
{
	// ADD Rd, #g_nAgbCPUImm8
	THUMB_RD_IMM8
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURd] + g_nAgbCPUImm8;
	NZFLAG_BY_VALUE
		ADDCARRY(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUImm8, g_nAgbCPUValue);
	ADDOVERFLOW(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUImm8, g_nAgbCPUValue);
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;
}

AGBCPU_THUMB_FUNC_NAME(0x38_0x3f)
{
	// SUB Rd, #g_nAgbCPUImm8
	THUMB_RD_IMM8
		g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURd] - g_nAgbCPUImm8;			
	NZFLAG_BY_VALUE
		SUBCARRY(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUImm8, g_nAgbCPUValue);
	SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUImm8, g_nAgbCPUValue);
	g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;
}

AGBCPU_THUMB_FUNC_NAME(0x40)
{
	switch( (g_nAgbInst>>6)&3)
	{
	case 0x00:
		{
			// AND Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd] & g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_RD
		}
		break;
	case 0x01:
		{
			// EOR Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd]^g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_RD
		}
		break;				
	case 0x02:
		{
			// LSL Rd, Rs
			THUMB_RD_RS_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
			if(g_nAgbCPUValue == 0)
			{}
			else if(g_nAgbCPUValue > 0 && g_nAgbCPUValue<32)
			{
				LSL_RD_RS
			}
			else if(g_nAgbCPUValue == 32)
			{
				g_bAgbCFlag = g_nAgbCPUReg[g_nAgbCPURd]&0x1;
				g_nAgbCPUReg[g_nAgbCPURd] = 0;
			}
			else
			{
				g_bAgbCFlag = 0;
				g_nAgbCPUReg[g_nAgbCPURd] = 0;
			}
			NZFLAG_BY_RD
		}
		break;
	case 0x03:
		{
			// LSR Rd, Rs
			THUMB_RD_RS_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
			if(g_nAgbCPUValue == 0)
			{}
			else if(g_nAgbCPUValue > 0 && g_nAgbCPUValue<32)
			{
				LSR_RD_RS
			}
			else if(g_nAgbCPUValue == 32)
			{
				g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
				g_nAgbCPUReg[g_nAgbCPURd] = 0;
			}
			else
			{
				g_bAgbCFlag = 0;
				g_nAgbCPUReg[g_nAgbCPURd] = 0;
			}
			NZFLAG_BY_RD
		}
		break;
	}

}

AGBCPU_THUMB_FUNC_NAME(0x41)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			// ASR Rd, Rs
			THUMB_RD_RS_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
			if(g_nAgbCPUValue == 0)
			{}
			else if(g_nAgbCPUValue > 0 && g_nAgbCPUValue<32)
			{
				ASR_RD_RS
			}
			else if(g_nAgbCPUValue == 32)
			{
				g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
				if(g_bAgbCFlag)						
					g_nAgbCPUReg[g_nAgbCPURd] = 0xffffffff;
				else
					g_nAgbCPUReg[g_nAgbCPURd] = 0;
			}
			else
			{
				g_bAgbCFlag = 0;
				g_nAgbCPUReg[g_nAgbCPURd] = 0;
			}
			NZFLAG_BY_RD
		}
		break;
	case 0x01:
		{
			// ADC Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURd] + g_nAgbCPUReg[g_nAgbCPURm] + g_bAgbCFlag;
			NZFLAG_BY_VALUE
				ADDCARRY(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				ADDOVERFLOW(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
			g_nAgbCPUReg[rd]  = g_nAgbCPUValue;
		}
		break;
	case 0x02:
		{
			// SBC Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURd] - g_nAgbCPUReg[g_nAgbCPURm] - (!g_bAgbCFlag);
			NZFLAG_BY_VALUE
				SUBCARRY(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue);
			SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURd], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue);
			g_nAgbCPUReg[rd]  = g_nAgbCPUValue;
		}
		break;
	case 0x03:
		{
			// ROR Rd, Rs
			THUMB_RD_RS_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
			if(g_nAgbCPUValue == 0)
			{}
			else if((g_nAgbCPUValue&0xf) == 0)
			{
				g_bAgbCFlag = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
			}
			else
			{
				g_nAgbCPUValue = g_nAgbCPUValue&0xf;
				ROR_RD_VALUE
			}						
			NZFLAG_BY_RD
		}
		break;
	}

}

AGBCPU_THUMB_FUNC_NAME(0x42)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			// TST Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUValue = (g_nAgbCPUReg[g_nAgbCPURd] & g_nAgbCPUReg[g_nAgbCPURm]);
			NZFLAG_BY_VALUE
		}
		break;
	case 0x01:
		{
			// NEG Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUValue = (u32)0 - g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_VALUE
				SUBCARRY((u32)0, g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				SUBOVERFLOW((u32)0, g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUValue;
		}
		break;
	case 0x02:
		{
			//CMP Rn, Rm
			THUMB_RN_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_VALUE
				SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
		}
		break;
	case 0x03:
		{
			//CMN Rn, Rm
			THUMB_RN_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_VALUE
				ADDCARRY(g_nAgbCPUReg[g_nAgbCPURn],g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				ADDOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn],g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
		}
		break;
	}
}

AGBCPU_THUMB_FUNC_NAME(0x43)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			// ORR Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd] | g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_RD
		}
		break;
	case 0x01:
		{
			// MUL Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURm] * g_nAgbCPUReg[g_nAgbCPURd]);
			NZFLAG_BY_RD
		}
		break;
	case 0x02:
		{
			//Bic Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd] & (~g_nAgbCPUReg[g_nAgbCPURm]);
			NZFLAG_BY_RD
		}
		break;
	case 0x03:
		{
			//MVN Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = (~g_nAgbCPUReg[g_nAgbCPURm]);
			NZFLAG_BY_RD
		}
		break;
	}
}

AGBCPU_THUMB_FUNC_NAME(0x44)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			//zhfang test
			//unknown thumb
			TRL_ERROR("unknown thumb instruction");
		}
		break;
	case 0x01:
		{
			// ADD Rd, Hm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURd] + g_nAgbCPUReg[g_nAgbCPURm+8]);						
		}
		break;
	case 0x02:
		{
			// ADD Hd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd +8] = (g_nAgbCPUReg[g_nAgbCPURd + 8] + g_nAgbCPUReg[g_nAgbCPURm]);						
			THUMB_PC_WRITE
		}
		break;
	case 0x03:
		{
			// ADD Hd, Hm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd + 8] = (g_nAgbCPUReg[g_nAgbCPURd + 8] + g_nAgbCPUReg[g_nAgbCPURm +8]);						
			THUMB_PC_WRITE
		}
		break;				
	}
}

AGBCPU_THUMB_FUNC_NAME(0x45)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			//CMP Rn, Rm
			THUMB_RN_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_VALUE
				SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
		}
		break;
	case 0x01:
		{
			//CMP Rn, Hm
			THUMB_RN_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm +8];
			NZFLAG_BY_VALUE
				SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm+8], g_nAgbCPUValue)
				SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn], g_nAgbCPUReg[g_nAgbCPURm+8], g_nAgbCPUValue)
		}
		break;
	case 0x02:
		{
			//CMP Hn, Rm
			THUMB_RN_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn +8] - g_nAgbCPUReg[g_nAgbCPURm];
			NZFLAG_BY_VALUE
				SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn+8], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
				SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn+8], g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUValue)
		}
		break;
	case 0x03:
		{
			//CMP Hn, Hm
			THUMB_RN_RM_DEFINE
				g_nAgbCPUValue = g_nAgbCPUReg[g_nAgbCPURn +8] - g_nAgbCPUReg[g_nAgbCPURm +8];
			NZFLAG_BY_VALUE
				SUBCARRY(g_nAgbCPUReg[g_nAgbCPURn+8], g_nAgbCPUReg[g_nAgbCPURm+8], g_nAgbCPUValue)
				SUBOVERFLOW(g_nAgbCPUReg[g_nAgbCPURn+8], g_nAgbCPUReg[g_nAgbCPURm+8], g_nAgbCPUValue)
		}
		break;
	}
}

AGBCPU_THUMB_FUNC_NAME(0x46)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			//Mov Rd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURm];
		}
		break;
	case 0x01:
		{
			//Mov Rd, Hm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURm + 8];
		}
		break;
	case 0x02:
		{
			//Mov Hd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd + 8] = g_nAgbCPUReg[g_nAgbCPURm];	
			THUMB_PC_WRITE
		}
		break;
	case 0x03:
		{
			//Mov Hd, Rm
			THUMB_RD_RM_DEFINE
				g_nAgbCPUReg[g_nAgbCPURd + 8] = g_nAgbCPUReg[g_nAgbCPURm + 8];
			THUMB_PC_WRITE
		}
		break;
	}
}

AGBCPU_THUMB_FUNC_NAME(0x47)
{
	switch((g_nAgbInst >> 6) & 3)
	{
	case 0x00:
		{
			//BX Rm
			THUMB_RM_DEFINE
				g_nAgbCPUReg[15] = g_nAgbCPUReg[g_nAgbCPURm]&0xfffffffe;
			if(g_nAgbCPUReg[g_nAgbCPURm]&0x1)
			{
				THUMB_FIRST_PREFETCH
			}
			else
			{
				g_nAgbThumbState = 0;
				g_nAgbCPUReg[15] &= 0xfffffffc;
				ARM_FIRST_PREFETCH
			}
		}
		break;
	case 0x01:
		{
			//BX Hm
			THUMB_RM_DEFINE
				g_nAgbCPUReg[15] = g_nAgbCPUReg[g_nAgbCPURm + 8]&0xfffffffe;
			if(g_nAgbCPUReg[g_nAgbCPURm + 8]&0x1)
			{
				THUMB_FIRST_PREFETCH
			}
			else
			{
				g_nAgbThumbState = 0;
				g_nAgbCPUReg[15] &= 0xfffffffc;
				ARM_FIRST_PREFETCH
			}
		}
		break;
	default:
		//zhfang test
		//unknown thumb
		TRL_ERROR("unknown thumb instruction");
		break;
	}
}

AGBCPU_THUMB_FUNC_NAME(0x48_0x4f)
{
	// LDR Rd, [PC, #g_nAgbCPUImm8*4]
	THUMB_RD_IMM8
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32((g_nAgbCPUReg[15]&0xfffffffc) + (g_nAgbCPUImm8<<2));
}

AGBCPU_THUMB_FUNC_NAME(0x50_0x51)
{
	// STR Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		agbMemWrite32(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUReg[g_nAgbCPURd]);
}

AGBCPU_THUMB_FUNC_NAME(0x52_0x53)
{
	// STRH Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		agbMemWrite16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUReg[g_nAgbCPURd]&0xffff);
}

AGBCPU_THUMB_FUNC_NAME(0x54_0x55)
{
	// STRB Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		agbMemWrite16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUReg[g_nAgbCPURd]&0xff);
}

AGBCPU_THUMB_FUNC_NAME(0x56_0x57)
{
	// LDRSB Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = (s8)agbMemRead8(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

AGBCPU_THUMB_FUNC_NAME(0x58_0x59)
{
	// LDR Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

AGBCPU_THUMB_FUNC_NAME(0x5a_0x5b)
{
	// LDRH Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

AGBCPU_THUMB_FUNC_NAME(0x5c_0x5d)
{
	// LDRB Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead8(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

AGBCPU_THUMB_FUNC_NAME(0x5e_0x5f)
{
	// LDRSH Rd, [Rn, Rm]
	THUMB_RD_RN_RM_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = (s16)agbMemRead16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

AGBCPU_THUMB_FUNC_NAME(0x60_0x67)
{
	// STR Rd, [Rn, IMM5*4]
	THUMB_RD_RN_IMM5_DEFINE
		agbMemWrite32(g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<2), g_nAgbCPUReg[g_nAgbCPURd]);
}

AGBCPU_THUMB_FUNC_NAME(0x68_0x6f)
{
	// LDR Rd, [Rn, IMM5*4]
	THUMB_RD_RN_IMM5_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32( g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<2));
}

AGBCPU_THUMB_FUNC_NAME(0x70_0x77)
{
	// STRB Rd, [Rn, IMM5]
	THUMB_RD_RN_IMM5_DEFINE
		agbMemWrite8(g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5), g_nAgbCPUReg[g_nAgbCPURd]);
}

AGBCPU_THUMB_FUNC_NAME(0x78_0x7f)
{
	// LDRB Rd, [Rn, IMM5]
	THUMB_RD_RN_IMM5_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead8( g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5));
}

AGBCPU_THUMB_FUNC_NAME(0x80_0x87)
{
	// STRH Rd, [Rn, IMM5*2]
	THUMB_RD_RN_IMM5_DEFINE
		agbMemWrite16(g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<1), g_nAgbCPUReg[g_nAgbCPURd]);
}

AGBCPU_THUMB_FUNC_NAME(0x88_0x8f)
{
	// LDRH Rd, [Rn, IMM5*2]
	THUMB_RD_RN_IMM5_DEFINE
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead16( g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<1));
}

AGBCPU_THUMB_FUNC_NAME(0x90_0x97)
{
	// STR Rd, [SP, IMM8*4]
	THUMB_RD_IMM8
		agbMemWrite32(g_nAgbCPUReg[13] + (g_nAgbCPUImm8<<2), g_nAgbCPUReg[g_nAgbCPURd]);
}

AGBCPU_THUMB_FUNC_NAME(0x98_0x9f)
{
	// LDR Rd, SP, IMM8*4]
	THUMB_RD_IMM8
		g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32( g_nAgbCPUReg[13] + (g_nAgbCPUImm8<<2));
}

AGBCPU_THUMB_FUNC_NAME(0xa0_0xa7)
{
	// ADD Rd, PC, IMM8
	THUMB_RD_IMM8
		g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[15]&0xfffffffc) + (g_nAgbCPUImm8<<2);
}

AGBCPU_THUMB_FUNC_NAME(0xa8_0xaf)
{
	// ADD Rd, SP, IMM8*4
	THUMB_RD_IMM8
		g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[13]) + (g_nAgbCPUImm8<<2);
}

AGBCPU_THUMB_FUNC_NAME(0xb0)
{
	// ADD SP, Imm7*4
	s32 imm7 = (g_nAgbInst&0x7f)<<2;
	if(g_nAgbInst &0x80)
		imm7 = - imm7;
	g_nAgbCPUReg[13] += (imm7);
}

AGBCPU_THUMB_FUNC_NAME(0xb4)
{
	//PUSH {Rlist}
	u32 g_nAgbCPUTemp =g_nAgbCPUReg[13] - g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4;
	u32 g_nAgbCPUAddress = g_nAgbCPUTemp &0xfffffffc;
	PUSH_REG(0x1, 0);
	PUSH_REG(0x2, 1);
	PUSH_REG(0x4, 2);
	PUSH_REG(0x8, 3);
	PUSH_REG(0x10, 4);
	PUSH_REG(0x20, 5);
	PUSH_REG(0x40, 6);
	PUSH_REG(0x80, 7);
	g_nAgbCPUReg[13] = g_nAgbCPUTemp;
}

AGBCPU_THUMB_FUNC_NAME(0xb5)
{
	//PUSH {Rlist, LR}
	u32 g_nAgbCPUTemp =g_nAgbCPUReg[13] - g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4 -4;
	u32 g_nAgbCPUAddress = g_nAgbCPUTemp & 0xfffffffc;
	PUSH_REG(0x1, 0);
	PUSH_REG(0x2, 1);
	PUSH_REG(0x4, 2);
	PUSH_REG(0x8, 3);
	PUSH_REG(0x10, 4);
	PUSH_REG(0x20, 5);
	PUSH_REG(0x40, 6);
	PUSH_REG(0x80, 7);
	PUSH_REG(0x100, 14);
	g_nAgbCPUReg[13] = g_nAgbCPUTemp;
}

AGBCPU_THUMB_FUNC_NAME(0xbc)
{
	//POP {Rlist}
	u32 g_nAgbCPUTemp =g_nAgbCPUReg[13] + g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4;
	u32 g_nAgbCPUAddress = g_nAgbCPUReg[13]&0xfffffffc;
	POP_REG(0x1, 0);
	POP_REG(0x2, 1);
	POP_REG(0x4, 2);
	POP_REG(0x8, 3);
	POP_REG(0x10, 4);
	POP_REG(0x20, 5);
	POP_REG(0x40, 6);
	POP_REG(0x80, 7);
	g_nAgbCPUReg[13] = g_nAgbCPUTemp;
}

AGBCPU_THUMB_FUNC_NAME(0xbd)
{
	//POP {Rlist, PC}
	u32 g_nAgbCPUTemp =g_nAgbCPUReg[13] + g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4 + 4;
	u32 g_nAgbCPUAddress = g_nAgbCPUReg[13]&0xfffffffc;
	POP_REG(0x1, 0);
	POP_REG(0x2, 1);
	POP_REG(0x4, 2);
	POP_REG(0x8, 3);
	POP_REG(0x10, 4);
	POP_REG(0x20, 5);
	POP_REG(0x40, 6);
	POP_REG(0x80, 7);
	g_nAgbCPUReg[15] = agbMemRead32(g_nAgbCPUAddress)&0xFFFFFFFE;
	THUMB_FIRST_PREFETCH
		g_nAgbCPUReg[13] = g_nAgbCPUTemp;
}

AGBCPU_THUMB_FUNC_NAME(0xc0_0xc7)
{
	// STMIA Rn, {Rlist}
	u32 g_nAgbCPURn =(g_nAgbInst>>8)&7;
	u32 g_nAgbCPUAddress = g_nAgbCPUReg[g_nAgbCPURn] & 0xfffffffc;
	u32 g_nAgbCPUTemp = g_nAgbCPUReg[g_nAgbCPURn] + 4*g_nAgbCpuBitsSet[g_nAgbInst &0xff];
	s32 g_nAgbCPUOffset = 0;
	THUMB_STM_REG(0x1, 0, g_nAgbCPURn);
	THUMB_STM_REG(0x2, 1, g_nAgbCPURn);
	THUMB_STM_REG(0x4, 2, g_nAgbCPURn);
	THUMB_STM_REG(0x8, 3, g_nAgbCPURn);
	THUMB_STM_REG(0x10, 4, g_nAgbCPURn);
	THUMB_STM_REG(0x20, 5, g_nAgbCPURn);
	THUMB_STM_REG(0x40, 6, g_nAgbCPURn);
	THUMB_STM_REG(0x80, 7, g_nAgbCPURn);
}

AGBCPU_THUMB_FUNC_NAME(0xc8_0xcf)
{
	// LDMIA Rn, {Rlist}
	u32 g_nAgbCPURn =(g_nAgbInst>>8)&7;
	u32 g_nAgbCPUAddress = g_nAgbCPUReg[g_nAgbCPURn] & 0xfffffffc;
	u32 g_nAgbCPUTemp = g_nAgbCPUReg[g_nAgbCPURn] + 4*g_nAgbCpuBitsSet[g_nAgbInst &0xff];
	THUMB_LDM_REG(0x1, 0);
	THUMB_LDM_REG(0x2, 1);
	THUMB_LDM_REG(0x4, 2);
	THUMB_LDM_REG(0x8, 3);
	THUMB_LDM_REG(0x10, 4);
	THUMB_LDM_REG(0x20, 5);
	THUMB_LDM_REG(0x40, 6);
	THUMB_LDM_REG(0x80, 7);
	if(!(g_nAgbInst &(1<<g_nAgbCPURn)))
		g_nAgbCPUReg[g_nAgbCPURn] = g_nAgbCPUTemp;
}

AGBCPU_THUMB_FUNC_NAME(0xd0)
{
	//BEQ SImm8
	if(g_bAgbZFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd1)
{
	//BNE SImm8
	if(g_bAgbZFlag == 0)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd2)
{
	//BCS SImm8
	if(g_bAgbCFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd3)
{
	//BCC SImm8
	if(g_bAgbCFlag == 0)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd4)
{
	//BMI SImm8
	if(g_bAgbNFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd5)
{
	//BPL SImm8
	if(g_bAgbNFlag == 0)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd6)
{
	//BVS SImm8
	if(g_bAgbVFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd7)
{
	//BVC SImm8
	if(g_bAgbVFlag == 0)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd8)
{
	//BHI SImm8
	if(g_bAgbCFlag && g_bAgbZFlag == 0)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xd9)
{
	//BLS SImm8
	if(g_bAgbCFlag == 0  || g_bAgbZFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xda)
{
	//BGE SImm8
	if(g_bAgbNFlag == g_bAgbVFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xdb)
{
	//BLT SImm8
	if(g_bAgbNFlag != g_bAgbVFlag)
	{
		THUMB_BCOND_SIMM8	
	}
}

AGBCPU_THUMB_FUNC_NAME(0xdc)
{
	//BGT SImm8
	if(g_bAgbZFlag == 0 && (g_bAgbNFlag == g_bAgbVFlag))
	{
		THUMB_BCOND_SIMM8
	}
}

AGBCPU_THUMB_FUNC_NAME(0xdd)
{
	//BLE SImm8
	if(g_bAgbZFlag  || (g_bAgbNFlag != g_bAgbVFlag))
	{
		THUMB_BCOND_SIMM8
	}
}

AGBCPU_THUMB_FUNC_NAME(0xdf)
{
	// SWI
	agbCPUSWI(g_nAgbInst &0xff);
}

AGBCPU_THUMB_FUNC_NAME(0xe0_0xe7)
{
	//B Imm11
	s32 g_nAgbCPUOffset = (s32)(g_nAgbInst & 0x3ff)<<1;
	if(g_nAgbInst &0x0400)
		g_nAgbCPUOffset |= 0xfffff800;
	g_nAgbCPUReg[15] += g_nAgbCPUOffset;
	THUMB_FIRST_PREFETCH
}

AGBCPU_THUMB_FUNC_NAME(0xf0_0xf3)
{
	// BLL #g_nAgbCPUOffset
	s32 g_nAgbCPUOffset = (g_nAgbInst & 0x7ff);
	g_nAgbCPUReg[14] = g_nAgbCPUReg[15] + (g_nAgbCPUOffset << 12);
}

AGBCPU_THUMB_FUNC_NAME(0xf4_0xf7)
{
	// BLL #g_nAgbCPUOffset
	s32 g_nAgbCPUOffset = (g_nAgbInst & 0x7ff);
	g_nAgbCPUReg[14] = g_nAgbCPUReg[15] + ((g_nAgbCPUOffset << 12) | 0xff800000);
}

AGBCPU_THUMB_FUNC_NAME(0xf8_0xff)
{
	// BLH
	s32 g_nAgbCPUOffset = (g_nAgbInst &0x7ff);
	u32 g_nAgbCPUTemp = g_nAgbCPUReg[15] -2;
	g_nAgbCPUReg[15] = (g_nAgbCPUReg[14] + (g_nAgbCPUOffset<<1))&0xfffffffe;
	g_nAgbCPUReg[14]= g_nAgbCPUTemp|1;
	THUMB_FIRST_PREFETCH
}

AGBCPU_THUMB_FUNC_NAME(und)
{
	//unknown thumb
	TRL_ERROR("unknown thumb instruction");
}


//========================this is a line ^_^============================

#define 	AGBCPU_THUMB_FUNC_TABLE_ITME1(n, index)\
	agbCpuThumbCFunc_##n,
#define 	AGBCPU_THUMB_FUNC_TABLE_ITME2(n, index)\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,
#define 	AGBCPU_THUMB_FUNC_TABLE_ITME4(n, index)\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,
#define 	AGBCPU_THUMB_FUNC_TABLE_ITME8(n, index)\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,\
	agbCpuThumbCFunc_##n,


void (*g_pAgbCPUThumbFuncTable[])() =
{
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x00_0x07, 0x00)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x08_0x0f, 0x08)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x10_0x17, 0x10)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x18_0x19, 0x18)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x1a_0x1b, 0x1a)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x1c_0x1d, 0x1c)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x1e_0x1f, 0x1e)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x20_0x27, 0x20)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x28_0x2f, 0x28)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x30_0x37, 0x30)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x38_0x3f,0x38)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x40, 0x40)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x41, 0x41)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x42, 0x42)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x43, 0x43)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x44, 0x44)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x45, 0x45)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x46, 0x46)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0x47, 0x47)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x48_0x4f, 0x48)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x50_0x51, 0x50)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x52_0x53, 0x52)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x54_0x55, 0x54)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x56_0x57, 0x56)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x58_0x59, 0x58)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x5a_0x5b, 0x5a)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x5c_0x5d, 0x5c)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(0x5e_0x5f, 0x5e)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x60_0x67, 0x60)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x68_0x6f, 0x68)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x70_0x77, 0x70)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x78_0x7f, 0x78)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x80_0x87, 0x80)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x88_0x8f, 0x88)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x90_0x97, 0x90)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0x98_0x9f, 0x98)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0xa0_0xa7, 0xa0)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0xa8_0xaf, 0xa8)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xb0, 0xb0)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(und, 0xb1)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(und, 0xb2)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xb4, 0xb4)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xb5, 0xb5)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(und, 0xb6)
	AGBCPU_THUMB_FUNC_TABLE_ITME4(und, 0xb8)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xbc, 0xbc)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xbd, 0xbd)
	AGBCPU_THUMB_FUNC_TABLE_ITME2(und, 0xbe)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0xc0_0xc7, 0xc0)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0xc8_0xcf, 0xc8)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd0, 0xd0)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd1, 0xd1)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd2, 0xd2)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd3, 0xd3)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd4, 0xd4)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd5, 0xd5)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd6, 0xd6)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd7, 0xd7)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd8, 0xd8)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xd9, 0xd9)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xda, 0xda)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xdb, 0xdb)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xdc, 0xdc)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xdd, 0xdd)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(und, 0xde)
	AGBCPU_THUMB_FUNC_TABLE_ITME1(0xdf, 0xdf)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0xe0_0xe7, 0xe0)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(und, 0xe8)
	AGBCPU_THUMB_FUNC_TABLE_ITME4(0xf0_0xf3, 0xf0)
	AGBCPU_THUMB_FUNC_TABLE_ITME4(0xf4_0xf7, 0xf4)
	AGBCPU_THUMB_FUNC_TABLE_ITME8(0xf8_0xff, 0xf8)
};

ENDFILE

