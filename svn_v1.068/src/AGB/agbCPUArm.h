//case define
#define CASE_16(BASE)\
	case BASE:\
	case BASE+1:\
	case BASE+2:\
	case BASE+3:\
	case BASE+4:\
	case BASE+5:\
	case BASE+6:\
	case BASE+7:\
	case BASE+8:\
	case BASE+9:\
	case BASE+10:\
	case BASE+11:\
	case BASE+12:\
	case BASE+13:\
	case BASE+14:\
	case BASE+15:

#define CASE_256(BASE)\
	CASE_16(BASE)\
	CASE_16(BASE+0x10)\
	CASE_16(BASE+0x20)\
	CASE_16(BASE+0x30)\
	CASE_16(BASE+0x40)\
	CASE_16(BASE+0x50)\
	CASE_16(BASE+0x60)\
	CASE_16(BASE+0x70)\
	CASE_16(BASE+0x80)\
	CASE_16(BASE+0x90)\
	CASE_16(BASE+0xa0)\
	CASE_16(BASE+0xb0)\
	CASE_16(BASE+0xc0)\
	CASE_16(BASE+0xd0)\
	CASE_16(BASE+0xe0)\
	CASE_16(BASE+0xf0)

//ldrxxx to PC
#define LDR_TO_PC\
	if(rd == 15) \
	{\
		g_nAgbCPUReg[15] &= 0xfffffffc;\
		ARM_FIRST_PREFETCH\
	}


#define STM_REG(val, reg_num) \
	if(rlist & val)\
	{\
		agbMemWrite32(address, g_nAgbCPUReg[reg_num]);\
		address += 4;\
	}

#define STM_REG_BANK(val, reg_num) \
	if(rlist & val) \
	{\
		agbMemWrite32(address, g_nAgbCPUReg[reg_num]);\
		address += 4;\
	}
	
#define STM_REG_REG15\
	if(opcode & 0x8000)\
	{\
		agbMemWrite32(address, g_nAgbCPUReg[15] + 4);\
	}

#define STM_REG16\
	STM_REG(0x1, 0);\
	STM_REG(0x2, 1);\
	STM_REG(0x4, 2);\
	STM_REG(0x8, 3);\
	STM_REG(0x10, 4);\
	STM_REG(0x20, 5);\
	STM_REG(0x40, 6);\
	STM_REG(0x80, 7);\
	STM_REG(0x100, 8);\
	STM_REG(0x200, 9);\
	STM_REG(0x400, 10);\
	STM_REG(0x800, 11);\
	STM_REG(0x1000, 12);\
	STM_REG(0x2000, 13);\
	STM_REG(0x4000, 14);\
	STM_REG_REG15

#define STM_REG16_CPSR\
	STM_REG(0x1, 0);\
	STM_REG(0x2, 1);\
	STM_REG(0x4, 2);\
	STM_REG(0x8, 3);\
	STM_REG(0x10, 4);\
	STM_REG(0x20, 5);\
	STM_REG(0x40, 6);\
	STM_REG(0x80, 7);\
	if(g_nAgbCPUReg[REG_CPUMODE] == CPU_MODE_FIQ)\
	{\
		STM_REG(0x100, R8_FIQ);\
		STM_REG(0x200, R9_FIQ);\
		STM_REG(0x400, R10_FIQ);\
		STM_REG(0x800, R11_FIQ);\
		STM_REG(0x1000, R12_FIQ);\
	}\
	else\
	{\
		STM_REG(0x100, 8);\
		STM_REG(0x200, 9);\
		STM_REG(0x400, 10);\
		STM_REG(0x800, 11);\
		STM_REG(0x1000, 12);\
	}\
	if(g_nAgbCPUReg[REG_CPUMODE] != CPU_MODE_USER && g_nAgbCPUReg[REG_CPUMODE] != CPU_MODE_SYS)\
	{\
		STM_REG(0x2000, R13_USER);\
		STM_REG(0x4000, R14_USER);\
	}\
	else\
	{\
		STM_REG(0x2000, 13);\
		STM_REG(0x4000, 14);\
	}\
	STM_REG_REG15


#define LDM_REG(val, reg_num)\
	if(rlist & val)\
	{\
		g_nAgbCPUReg[reg_num] = agbMemRead32(address);\
		address += 4;\
	}

#define LDM_REG_BANK(val, reg_num)\
	if(rlist & val)\
	{\
		g_nAgbCPUReg[reg_num] = agbMemRead32(address);\
		address += 4;\
	}
	

#define LDM_REG_REG15\
	if(opcode & 0x8000)\
	{\
		g_nAgbCPUReg[15] = agbMemRead32(address);\
		ARM_FIRST_PREFETCH\
	}

#define LDM_REG16\
	LDM_REG(0x1, 0);\
	LDM_REG(0x2, 1);\
	LDM_REG(0x4, 2);\
	LDM_REG(0x8, 3);\
	LDM_REG(0x10, 4);\
	LDM_REG(0x20, 5);\
	LDM_REG(0x40, 6);\
	LDM_REG(0x80, 7);\
	LDM_REG(0x100, 8);\
	LDM_REG(0x200, 9);\
	LDM_REG(0x400, 10);\
	LDM_REG(0x800, 11);\
	LDM_REG(0x1000, 12);\
	LDM_REG(0x2000, 13);\
	LDM_REG(0x4000, 14);\
	LDM_REG_REG15
		
#define LDM_REG16_CPSR\
	if(rlist & 0x8000)\
	{\
		LDM_REG(0x1, 0);\
		LDM_REG(0x2, 1);\
		LDM_REG(0x4, 2);\
		LDM_REG(0x8, 3);\
		LDM_REG(0x10, 4);\
		LDM_REG(0x20, 5);\
		LDM_REG(0x40, 6);\
		LDM_REG(0x80, 7);\
		LDM_REG(0x100, 8);\
		LDM_REG(0x200, 9);\
		LDM_REG(0x400, 10);\
		LDM_REG(0x800, 11);\
		LDM_REG(0x1000, 12);\
		LDM_REG(0x2000, 13);\
		LDM_REG(0x4000, 14);\
		g_nAgbCPUReg[15] = agbMemRead32(address);\
		SWITCH_MODE_PREFETCH\
	}\
	else\
	{\
		LDM_REG(0x1, 0);\
		LDM_REG(0x2, 1);\
		LDM_REG(0x4, 2);\
		LDM_REG(0x8, 3);\
		LDM_REG(0x10, 4);\
		LDM_REG(0x20, 5);\
		LDM_REG(0x40, 6);\
		LDM_REG(0x80, 7);\
		if(g_nAgbCPUReg[REG_CPUMODE] == CPU_MODE_FIQ)\
		{\
			LDM_REG(0x100, R8_FIQ);\
			LDM_REG(0x200, R9_FIQ);\
			LDM_REG(0x400, R10_FIQ);\
			LDM_REG(0x800, R11_FIQ);\
			LDM_REG(0x1000, R12_FIQ);\
		}\
		else\
		{\
			LDM_REG(0x100, 8);\
			LDM_REG(0x200, 9);\
			LDM_REG(0x400, 10);\
			LDM_REG(0x800, 11);\
			LDM_REG(0x1000, 12);\
		}\
		if(g_nAgbCPUReg[REG_CPUMODE] != CPU_MODE_USER && g_nAgbCPUReg[REG_CPUMODE] != CPU_MODE_SYS)\
		{\
			LDM_REG(0x2000, R13_USER);\
			LDM_REG(0x4000, R14_USER);\
		}\
		else\
		{\
			LDM_REG(0x2000, 13);\
			LDM_REG(0x4000, 14);\
		}\
	}

#define LDM_REG16W_CPSR\
	if(rlist & 0x8000)\
	{\
		LDM_REG(0x1, 0);\
		LDM_REG(0x2, 1);\
		LDM_REG(0x4, 2);\
		LDM_REG(0x8, 3);\
		LDM_REG(0x10, 4);\
		LDM_REG(0x20, 5);\
		LDM_REG(0x40, 6);\
		LDM_REG(0x80, 7);\
		LDM_REG(0x100, 8);\
		LDM_REG(0x200, 9);\
		LDM_REG(0x400, 10);\
		LDM_REG(0x800, 11);\
		LDM_REG(0x1000, 12);\
		LDM_REG(0x2000, 13);\
		LDM_REG(0x4000, 14);\
		g_nAgbCPUReg[15] = agbMemRead32(address);\
		if(!(opcode &(1<<rn)))\
			g_nAgbCPUReg[rn] = temp;\
		SWITCH_MODE_PREFETCH\
	}\
	else\
	{\
		LDM_REG(0x1, 0);\
		LDM_REG(0x2, 1);\
		LDM_REG(0x4, 2);\
		LDM_REG(0x8, 3);\
		LDM_REG(0x10, 4);\
		LDM_REG(0x20, 5);\
		LDM_REG(0x40, 6);\
		LDM_REG(0x80, 7);\
		if(g_nAgbCPUReg[REG_CPUMODE] == CPU_MODE_FIQ)\
		{\
			LDM_REG(0x100, R8_FIQ);\
			LDM_REG(0x200, R9_FIQ);\
			LDM_REG(0x400, R10_FIQ);\
			LDM_REG(0x800, R11_FIQ);\
			LDM_REG(0x1000, R12_FIQ);\
		}\
		else\
		{\
			LDM_REG(0x100, 8);\
			LDM_REG(0x200, 9);\
			LDM_REG(0x400, 10);\
			LDM_REG(0x800, 11);\
			LDM_REG(0x1000, 12);\
		}\
		if(g_nAgbCPUReg[REG_CPUMODE] != CPU_MODE_USER && g_nAgbCPUReg[REG_CPUMODE] != CPU_MODE_SYS)\
		{\
			LDM_REG(0x2000, R13_USER);\
			LDM_REG(0x4000, R14_USER);\
		}\
		else\
		{\
			LDM_REG(0x2000, 13);\
			LDM_REG(0x4000, 14);\
		}\
		if(!(opcode &(1<<rn)))\
			g_nAgbCPUReg[rn] = temp;\
	}


#define LOGICAL_LSL_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		C_OUT = (v >> (32 - shift)) & 1 ? true : false;\
		operand = v << shift;\
	}
#define LOGICAL_LSR_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		C_OUT = (v >> (shift - 1)) & 1 ? true : false;\
		operand = v >> shift;\
	}
#define LOGICAL_ASR_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		C_OUT = ((s32)v >> (int)(shift - 1)) & 1 ? true : false;\
		operand = (s32)v >> (int)shift;\
	}

#define LOGICAL_ROR_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		C_OUT = (v >> (shift - 1)) & 1 ? true : false;\
		operand = ((v << (32 - shift)) |(v >> shift));\
	}
#define LOGICAL_RRX_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		shift = (int)g_nAgbCPUReg[REG_CFLAG];\
		C_OUT = (v  & 1) ? true : false;\
		operand = ((v >> 1) |\
		(shift << 31));\
	}
#define LOGICAL_ROR_IMM\
	{\
		u32 v = opcode & 0xff;\
		C_OUT = (v >> (shift - 1)) & 1 ? true : false; \
		operand = ((v << (32 - shift)) | \
		(v >> shift));\
	}

#define ARITHMETIC_LSL_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		operand = v << shift;\
	}
#define ARITHMETIC_LSR_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		operand = v >> shift;\
	}
#define ARITHMETIC_ASR_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		operand = (s32)v >> (int)shift;\
	}
#define ARITHMETIC_ROR_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		operand = ((v << (32 - shift)) |(v >> shift));\
	}
#define ARITHMETIC_RRX_REG\
	{\
		u32 v = g_nAgbCPUReg[opcode & 0x0f];\
		shift = (int)g_nAgbCPUReg[REG_CFLAG];\
		operand = ((v >> 1) |\
		(shift << 31));\
	}
#define ARITHMETIC_ROR_IMM\
	{\
		u32 v = opcode & 0xff;\
		operand = ((v << (32 - shift)) |(v >> shift));\
	}

#define ROR_IMM_MSR\
	{\
		u32 v = opcode & 0xff;\
		operand = ((v << (32 - shift)) | (v >> shift));\
	}
#define ROR_VALUE\
	{\
		operand = ((value << (32 - shift)) | (value >> shift));\
	}
#define RCR_VALUE\
	{\
	     shift = (int)g_nAgbCPUReg[REG_CFLAG];\
	     operand = ((value >> 1) | (shift << 31));\
	}

#define ROR_OFFSET_SHIFT_IMM\
	{\
		offset = ((offset << (32 - shift_imm)) | (offset >> shift_imm));\
	}
#define RCR_OFFSET_SHIFT_IMM\
	{\
	     shift_imm = (int)g_nAgbCPUReg[REG_CFLAG];\
	     offset = ((shift_imm >> 1) | (shift_imm << 31));\
	}

#define OPERAND_LSL_IMM\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else\
		LOGICAL_LSL_REG
#define OPERAND_LSR_IMM\
	if(shift == 0)\
	{\
		operand = 0;\
		C_OUT = ((g_nAgbCPUReg[rm]>>0x31)&0x1);\
	}\
	else\
		LOGICAL_LSR_REG
#define OPERAND_ASR_IMM\
	if(shift == 0)\
	{\
		if(g_nAgbCPUReg[rm] &0x80000000)\
		{\
			operand = 0xffffffff;\
			C_OUT = 1;\
		}\
		else\
		{\
			operand = 0;\
			C_OUT = 0;\
		}\
	}\
	else\
		LOGICAL_ASR_REG

#define OPERAND_ROR_IMM\
	if(shift == 0)\
		LOGICAL_RRX_REG \
	else\
		LOGICAL_ROR_REG
#define OPERAND_IMMED\
	if(shift == 0)\
	{\
		operand = (opcode &0xff);\
	}\
	else\
		LOGICAL_ROR_IMM



#define OPERAND_LSL_REG\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else if(shift < 32)\
		LOGICAL_LSL_REG \
	else if(shift == 32)\
	{\
		operand = 0;\
		C_OUT = (g_nAgbCPUReg[rm] & 0x1);\
	}\
	else\
	{\
		operand = 0;\
		C_OUT = 0;\
	}
#define OPERAND_LSR_REG\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else if(shift < 32)\
		LOGICAL_LSR_REG \
	else if(shift == 32)\
	{\
		operand = 0;\
		C_OUT = ((g_nAgbCPUReg[rm]>>0x31)&0x1);\
	}\
	else\
	{\
		operand = 0;\
		C_OUT = 0;\
	}
#define OPERAND_ASR_REG\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else if(shift < 32)\
		LOGICAL_ASR_REG \
	else\
	{\
		if(g_nAgbCPUReg[rm] &0x80000000)\
		{\
			operand = 0xffffffff;\
			C_OUT = 1;\
		}\
		else\
		{\
			operand = 0;\
			C_OUT = 0;\
		}\
	}
#define OPERAND_ROR_REG\
	if(shift&0x1f)\
	{\
		LOGICAL_ROR_REG\
	}\
	else\
	{\
		operand = g_nAgbCPUReg[rm];\
		C_OUT = (operand>>31)&0x1;\
	}

#define OPERAND_LSL_IMM_A\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else\
		ARITHMETIC_LSL_REG
#define OPERAND_LSR_IMM_A\
	if(shift == 0)\
	{\
		operand = 0;\
	}\
	else\
		ARITHMETIC_LSR_REG
#define OPERAND_ASR_IMM_A\
	if(shift == 0)\
	{\
		if(g_nAgbCPUReg[rm] &0x80000000)\
		{\
			operand = 0xffffffff;\
		}\
		else\
		{\
			operand = 0;\
		}\
	}\
	else\
		ARITHMETIC_ASR_REG

#define OPERAND_ROR_IMM_A\
	if(shift == 0)\
		ARITHMETIC_RRX_REG \
	else\
		ARITHMETIC_ROR_REG
#define OPERAND_IMMED_A\
	ARITHMETIC_ROR_IMM



#define OPERAND_LSL_REG_A\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else if(shift < 32)\
		ARITHMETIC_LSL_REG \
	else\
	{\
		operand = 0;\
	}
#define OPERAND_LSR_REG_A\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else if(shift < 32)\
		ARITHMETIC_LSR_REG \
	else\
	{\
		operand = 0;\
	}
#define OPERAND_ASR_REG_A\
	if(shift == 0)\
	{\
		operand = g_nAgbCPUReg[rm];\
	}\
	else if(shift < 32)\
		ARITHMETIC_ASR_REG \
	else\
	{\
		if(g_nAgbCPUReg[rm] &0x80000000)\
			operand = 0xffffffff;\
		else\
			operand = 0;\
	}
#define OPERAND_ROR_REG_A\
	if(shift&0x1f)\
	{\
		LOGICAL_ROR_REG\
	}\
	else\
	{\
		operand = g_nAgbCPUReg[rm];\
	}

	
#define DATA_PROC_RD_RN_RM_DEFINE\
	u32 rd = (opcode >> 12) & 0xf;\
	u32 rn = (opcode >> 16) &0xf;\
	u32 rm = (opcode&0xf);

#define DATA_PROC_SHIFTIMM_DEFINE\
	u32 shift = (opcode>>7)&0x1f;
#define DATA_PROC_SHIFTREG_DEFINE\
	u32 shift = g_nAgbCPUReg[(opcode>>8)&15]&0xFF;

#define DATA_PROC_COUT_OPERAND_DEFINE\
	u32 C_OUT = g_nAgbCPUReg[REG_CFLAG];\
	u32 operand;

#define DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE\
	DATA_PROC_RD_RN_RM_DEFINE\
	DATA_PROC_SHIFTIMM_DEFINE\
	DATA_PROC_COUT_OPERAND_DEFINE

#define DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE\
	DATA_PROC_RD_RN_RM_DEFINE\
	DATA_PROC_SHIFTREG_DEFINE\
	DATA_PROC_COUT_OPERAND_DEFINE
	

#define LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2)\
	if(rd == 15) \
	{ \
		OPCODE2 \
		if(opcode &0x00100000)\
		{\
			agbCPUSwitchMode(g_nAgbCPUReg[17]&0x1f, 0);\
		}\
		if(g_nAgbThumbState)\
		{\
			g_nAgbCPUReg[15] &= 0xfffffffe;\
			THUMB_FIRST_PREFETCH\
		}\
		else\
		{\
			g_nAgbCPUReg[15] &= 0xfffffffc;\
			ARM_FIRST_PREFETCH\
		}\
	} \
	else \
	{ \
		OPCODE \
	}


#define LOGICAL_DATA_OPCODE( OPCODE, OPCODE2,  BASE )\
	case BASE:\
	case BASE +8:\
		{\
			/* OP Rd, Rn, Rm LSL # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE\
			OPERAND_LSL_IMM\
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2)\
		}\
		break;\
	case BASE+2: \
	case BASE +10: \
		{\
			/* OP Rd, Rn, Rm LSR # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE \
			OPERAND_LSR_IMM \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2)\
		}\
		break;\
	case BASE+4: \
	case BASE +12: \
		{\
			/* OP Rd, Rn, Rm ASR # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE \
			OPERAND_ASR_IMM \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+6: \
	case BASE +14: \
		{\
			/* OP Rd, Rn, Rm ROR # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE \
			OPERAND_ROR_IMM \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+1: \
		{\
			/* OP Rd, Rn, Rm LSL Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_LSL_REG \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+3: \
		{\
			/* OP Rd, Rn, Rm LSR Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_LSR_REG \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+5: \
		{\
			/* OP Rd, Rn, Rm ASR Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_ASR_REG \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+7: \
		{\
			/* OP Rd, Rn, Rm ROR Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_ROR_REG \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	CASE_16(BASE+0x200) \
		{\
			/* OP Rd, Rn, Rm ROR Imm*/\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			shift = (opcode &0xf00)>>7;\
			OPERAND_IMMED \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;

#define ARITHMETIC_DATA_OPCODE(OPCODE, OPCODE2, BASE) \
	case BASE:\
	case BASE +8:\
		{\
			/* OP Rd, Rn, Rm LSL # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE\
			OPERAND_LSL_IMM_A\
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2)\
		}\
		break;\
	case BASE+2: \
	case BASE +10: \
		{\
			/* OP Rd, Rn, Rm LSR # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE \
			OPERAND_LSR_IMM_A \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2)\
		}\
		break;\
	case BASE+4: \
	case BASE +12: \
		{\
			/* OP Rd, Rn, Rm ASR # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE \
			OPERAND_ASR_IMM \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+6: \
	case BASE +14: \
		{\
			/* OP Rd, Rn, Rm ROR # */\
			DATA_PROC_RD_RN_RM_SHIFT_COUT_OPERAND_DEFINE \
			OPERAND_ROR_IMM_A \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+1: \
		{\
			/* OP Rd, Rn, Rm LSL Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_ROR_REG_A \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+3: \
		{\
			/* OP Rd, Rn, Rm LSR Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_ROR_REG \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+5: \
		{\
			/* OP Rd, Rn, Rm ASR Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_ASR_REG_A\
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	case BASE+7: \
		{\
			/* OP Rd, Rn, Rm ROR Rs */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			OPERAND_ROR_REG \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;\
	CASE_16(BASE+0x200) \
		{\
			/* OP Rd, Rn, Rm ROR Imm */\
			DATA_PROC_RD_RN_RM_SHIFTREG_COUT_OPERAND_DEFINE \
			shift = (opcode &0xf00)>>7;\
			OPERAND_IMMED_A \
			LOGICAL_DATA_OPCODE_PROC(OPCODE, OPCODE2) \
		}\
		break;


#define LHS_RHS_DEFINE\
	u32 lhs = g_nAgbCPUReg[rn];\
	u32 rhs = operand;

#define NZFLAG_BY_RD\
	g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[rd] >>31)&0x1;\
	g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[rd] == 0);

#define NZFLAG_BY_RES\
	g_nAgbCPUReg[REG_NFLAG] = (res >>31)&0x1;\
	g_nAgbCPUReg[REG_ZFLAG] = (res == 0);

#define RD_RES_NZFLAG\
	g_nAgbCPUReg[rd] = res;\
	NZFLAG_BY_RES

#define NZFLAG_RES_C_COUT\
	NZFLAG_BY_RES\
	g_nAgbCPUReg[REG_CFLAG]=C_OUT;

#define NZ_RD_C_COUT\
	NZFLAG_BY_RD\
	g_nAgbCPUReg[REG_CFLAG]=C_OUT;

#define NEG(i) ((i) >> 31)
#define POS(i) ((~(i)) >> 31)

#define ADDCARRY(a, b, c) \
	g_nAgbCPUReg[REG_CFLAG] = ((NEG(a) & NEG(b)) |\
	(NEG(a) & POS(c)) |\
	(NEG(b) & POS(c))) ? true : false;

#define ADDOVERFLOW(a, b, c) \
	g_nAgbCPUReg[REG_VFLAG] = ((NEG(a) & NEG(b) & POS(c)) |\
	(POS(a) & POS(b) & NEG(c))) ? true : false;

#define SUBCARRY(a, b, c) \
	g_nAgbCPUReg[REG_CFLAG] = ((NEG(a) & POS(b)) |\
	(NEG(a) & POS(c)) |\
	(POS(b) & POS(c))) ? true : false;

#define SUBOVERFLOW(a, b, c)\
	g_nAgbCPUReg[REG_VFLAG] = ((NEG(a) & POS(b) & POS(c)) |\
	(POS(a) & NEG(b) & NEG(c))) ? true : false;


#define OP_AND\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] & operand;
#define OP_ANDS\
	{\
		OP_AND\
		NZ_RD_C_COUT\
	}

#define OP_ORR\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] | operand;\

#define OP_ORRS\
	{\
		OP_ORR\
		NZ_RD_C_COUT\
	}

#define OP_EOR\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] ^ operand;\

#define OP_EORS\
	{\
		OP_EOR\
		NZ_RD_C_COUT \
	}

#define OP_MOV\
	{\
		g_nAgbCPUReg[rd] = operand;\
	}
#define OP_MOVS\
	{\
		OP_MOV\
		NZ_RD_C_COUT\
	}
#define OP_MVN\
	g_nAgbCPUReg[rd] = ~operand;
#define OP_MVNS\
	{\
		OP_MVN\
		NZ_RD_C_COUT\
	}
#define OP_BIC\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] &(~operand);
#define OP_BICS\
	{\
		OP_BIC\
		NZ_RD_C_COUT\
	}
#define OP_SUB\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] - operand;
#define OP_SUBS\
	{\
		LHS_RHS_DEFINE\
		u32 res = lhs - rhs;\
		RD_RES_NZFLAG\
		SUBCARRY(lhs, rhs, res)\
		SUBOVERFLOW(lhs, rhs, res)\
	}
#define OP_RSB\
	g_nAgbCPUReg[rd] = operand - g_nAgbCPUReg[rn];
#define OP_RSBS\
	{\
		LHS_RHS_DEFINE\
		u32 res = rhs - lhs;\
		RD_RES_NZFLAG\
		SUBCARRY(rhs, lhs, res)\
		SUBOVERFLOW(rhs, lhs, res)\
	}
#define OP_ADD\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] + operand;
#define OP_ADDS\
	{\
		LHS_RHS_DEFINE\
		u32 res = lhs + rhs;\
		RD_RES_NZFLAG\
		ADDCARRY(lhs, rhs, res)\
		ADDOVERFLOW(lhs, rhs, res);\
	}
#define OP_ADC\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] + operand + g_nAgbCPUReg[REG_CFLAG];
#define OP_ADCS\
	{\
		LHS_RHS_DEFINE\
		u32 res = lhs + rhs + g_nAgbCPUReg[REG_CFLAG];\
		RD_RES_NZFLAG\
		ADDCARRY(lhs, rhs, res)\
		ADDOVERFLOW(lhs, rhs, res)\
	}
#define OP_SBC\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rn] - operand - !g_nAgbCPUReg[REG_CFLAG];
#define OP_SBCS\
	{\
		LHS_RHS_DEFINE\
		u32 res = lhs - rhs - !g_nAgbCPUReg[REG_CFLAG];\
		RD_RES_NZFLAG\
		SUBCARRY(lhs, rhs, res)\
		SUBOVERFLOW(lhs, rhs, res)\
	}
#define OP_RSC\
	g_nAgbCPUReg[rd] = operand - g_nAgbCPUReg[rn] - !g_nAgbCPUReg[REG_CFLAG];
#define OP_RSCS\
	{\
		LHS_RHS_DEFINE\
		u32 res = rhs - lhs - !g_nAgbCPUReg[REG_CFLAG];\
		RD_RES_NZFLAG\
		SUBCARRY(lhs, rhs, res)\
		SUBOVERFLOW(lhs, rhs, res)\
	}
#define OP_CMP\
	{\
		LHS_RHS_DEFINE\
		u32 res = lhs - rhs;\
		NZFLAG_BY_RES\
		SUBCARRY(lhs, rhs, res);\
		SUBOVERFLOW(lhs, rhs, res);\
	}
#define OP_CMN\
	{\
		LHS_RHS_DEFINE\
		u32 res = lhs + rhs;\
		NZFLAG_BY_RES\
		ADDCARRY(lhs, rhs, res);\
		ADDOVERFLOW(lhs, rhs, res);\
	}
#define OP_TST\
	{\
		u32 res = g_nAgbCPUReg[rn] & operand;\
		NZFLAG_RES_C_COUT\
	}
#define OP_TEQ\
	{\
		u32 res = g_nAgbCPUReg[rn] ^ operand;\
		NZFLAG_RES_C_COUT\
	}
	
#define SWITCH_MODE_PREFETCH\
	{\
		agbCPUSwitchMode(g_nAgbCPUReg[17] & 0x1f, 0);\
		if(g_nAgbThumbState)\
		{\
			g_nAgbCPUReg[15] &= 0xfffffffe;\
			THUMB_FIRST_PREFETCH\
		}\
		else\
		{\
			g_nAgbCPUReg[15] &= 0xfffffffc;\
			ARM_FIRST_PREFETCH\
		}\
	}

#define ARM_RM_RS_RD_DEFINE\
	u32 rm = (opcode & 0x0f);\
	u32 rs = (opcode >> 8) & 0x0f;\
	u32 rd = (opcode >>16) & 0x0f;
#define ARM_RM_RD_RN_DEFINE\
	u32 rm = (opcode & 0x0f);\
	u32 rd = (opcode >> 12) & 0x0f;\
	u32 rn = (opcode >>16) & 0x0f;
#define ARM_RMIMM_RD_RN_DEFINE\
	u32 rm = (opcode & 0xfff);\
	u32 rd = (opcode >> 12) & 0x0f;\
	u32 rn = (opcode >>16) & 0x0f;
#define ARM_RM_RD_RN_ADDRESS_DEFINE\
	u32 rm = (opcode & 0x0f);\
	u32 rd = (opcode >> 12) & 0x0f;\
	u32 rn = (opcode >>16) & 0x0f;\
	u32 address;	
#define ARM_RM_RS_RN_RD_DEFINE\
	u32 rm = (opcode & 0x0f);\
	u32 rs = (opcode >> 8) & 0x0f;\
	u32 rn = (opcode >> 12) & 0x0f;\
	u32 rd = (opcode >>16) & 0x0f;
#define ARM_RM_RS_RDL_RDH_DEFINE\
	u32 rm = (opcode & 0x0f);\
	u32 rs = (opcode >> 8) & 0x0f;\
	u32 rdlo = (opcode >> 12) & 0x0f;\
	u32 rdhi = (opcode >>16) & 0x0f;
#define ARM_RM_IMM_RD_RN_DEFINE\
	u32 rm = opcode&0xf;\
	u32 shift_imm = (opcode >>7) & 0x1f;\
	u32 rd = (opcode >> 12) & 15;\
	u32 rn = (opcode >> 16) & 15;
#define ARM_RM_IMM_RD_RN_ADD_DEFINE\
	ARM_RM_IMM_RD_RN_DEFINE\
	u32 address = g_nAgbCPUReg[rn];

#define ARM_ROR_SHIFT_OFFSET\
	if(shift_imm == 0)\
		RCR_OFFSET_SHIFT_IMM\
	else\
		ROR_OFFSET_SHIFT_IMM

#define ARM_RN_RLIST_DEFINE\
	u32 rn = (opcode >> 16) & 15;\
	u32 rlist = (opcode & 0xffff);

 switch(opcode1|opcode2)
{
case 0x009:
	{
		// MUL Rd, Rm, Rs
		ARM_RM_RS_RD_DEFINE
		g_nAgbCPUReg[rd] = g_nAgbCPUReg[rm] *  g_nAgbCPUReg[rs];
	}
	break;
case 0x019:
	{
		// MULS Rd, Rm, Rs
		ARM_RM_RS_RD_DEFINE
		g_nAgbCPUReg[rd] = g_nAgbCPUReg[rm] *  g_nAgbCPUReg[rs];
		NZFLAG_BY_RD
	}
	break;
case 0x029:
	{
		// MLA Rd, Rm, Rs, Rn
		ARM_RM_RS_RN_RD_DEFINE
		g_nAgbCPUReg[rd] = (g_nAgbCPUReg[rm]*g_nAgbCPUReg[rs] + g_nAgbCPUReg[rn]);
	}
	break;
case 0x039:
	{
		// MLAS Rd, Rm, Rs, Rn
		ARM_RM_RS_RN_RD_DEFINE
		g_nAgbCPUReg[rd] = (g_nAgbCPUReg[rm]*g_nAgbCPUReg[rs] + g_nAgbCPUReg[rn]);
		g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[rd]>>31)&0x01;
		g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[rd] == 0);
	}
	break;
case 0x089:
	{
		// UMULL RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		u64 temp = ((u64)g_nAgbCPUReg[rm])*((u64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);				
	}
	break;
case 0x099:
	{
		// UMULLS RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		u64 temp = ((u64)g_nAgbCPUReg[rm])*((u64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);				
		g_nAgbCPUReg[REG_ZFLAG] = (temp == 0);
		g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[rdhi] >>31) &0x1;
	}
	break;
case 0x0a9:
	{
		// UMLAL RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		u64 temp;
		temp = (u64)g_nAgbCPUReg[rdhi];
		temp<<=32;
		temp |= (u64)g_nAgbCPUReg[rdlo];
		temp += ((u64)g_nAgbCPUReg[rm])*((u64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);				
	}
	break;
case 0x0b9:
	{
		// UMLALS RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		u64 temp;
		temp = (u64)g_nAgbCPUReg[rdhi];
		temp<<=32;
		temp |= (u64)g_nAgbCPUReg[rdlo];
		temp += ((u64)g_nAgbCPUReg[rm])*((u64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);				
		g_nAgbCPUReg[REG_ZFLAG] = (temp == 0);
		g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[rdhi] >>31) &0x1;
	}
	break;
case 0x0c9:
	{
		// SMULL RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		s64 temp = ((s64)g_nAgbCPUReg[rm])*((s64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);
	}
	break;
case 0x0d9:
	{
		// SMULLS RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		s64 temp = ((s64)g_nAgbCPUReg[rm])*((s64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);	
		g_nAgbCPUReg[REG_ZFLAG] = (temp == 0);
		g_nAgbCPUReg[REG_NFLAG] = (temp < 0);
	}
	break;
case 0x0e9:
	{
		// SMLAL RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		s64 temp;
		temp = (u64)g_nAgbCPUReg[rdhi];
		temp<<=32;
		temp |= (u64)g_nAgbCPUReg[rdlo];
		temp += ((s64)g_nAgbCPUReg[rm])*((s64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);				
	}
	break;
case 0x0f9:
	{
		// SMLALS RdLo, RdHi, Rm, Rs
		ARM_RM_RS_RDL_RDH_DEFINE
		s64 temp;
		temp = (u64)g_nAgbCPUReg[rdhi];
		temp<<=32;
		temp |= (u64)g_nAgbCPUReg[rdlo];
		temp += ((s64)g_nAgbCPUReg[rm])*((s64)g_nAgbCPUReg[rs]);
		g_nAgbCPUReg[rdlo] = (u32)temp;
		g_nAgbCPUReg[rdhi] = (u32)(temp>>32);		
		g_nAgbCPUReg[REG_ZFLAG] = (temp == 0);
		g_nAgbCPUReg[REG_NFLAG] = (temp<0);
	}
	break;
case 0x00b:
case 0x02b:
	{
		// STRH Rd, [Rn], -Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address - g_nAgbCPUReg[rm];
	}
	break;
case 0x04b:
case 0x06b:
	{
		//STRH Rd, [Rn], -#offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address - rm;
	}
	break;
case 0x08b:
case 0x0ab:
	{
		// STRH Rd, [Rn], +Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address + g_nAgbCPUReg[rm];
	}
	break;
case 0x0cb:
case 0x0eb:
	{
		//STRH Rd, [Rn], #+offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address + rm;
	}
	break;
case 0x10b:
	{
		// STRH Rd, [Rn, -Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x12b:
	{
		// STRH Rd, [Rn, -Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address;
	}
	break;
case 0x14b:
	{
		//STRH Rd, [Rn, -#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x16b:
	{
		//STRH Rd, [Rn, -#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address;
	}
	break;
case 0x18b:
	{
		// STRH Rd, [Rn, +Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x1ab:
	{
		// STRH Rd, [Rn, +Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address;
	}
	break;
case 0x1cb:
	{
		//STRH Rd, [Rn, +#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x1eb:
	{
		//STRH Rd, [Rn, + #offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		agbMemWrite16(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address;
	}
	break;			
case 0x01b:
case 0x03b:
	{
		// LDRH Rd, [Rn], -Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		rm = g_nAgbCPUReg[rm];
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x05b:
case 0x07b:
	{
		//LDRH Rd, [Rn], -#offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x09b:
case 0x0bb:
	{
		// LDRH Rd, [Rn], +Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		rm =g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x0db:
case 0x0fb:	
	{
		//LDRH Rd, [Rn], #+offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x11b:
	{
		// LDRH Rd, [Rn, -Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC			
	}
	break;
case 0x13b:
	{
		// LDRH Rd, [Rn, -Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC

	}
	break;
case 0x15b:
	{
		//LDRH Rd, [Rn, -#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x17b:
	{
		//LDRH Rd, [Rn, -#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;	
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x19b:
	{
		// LDRH Rd, [Rn +Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x1bb:
	{
		// LDRH Rd, [Rn +Rm]!
		u32 rm = (opcode & 0xf);
		u32 rd = (opcode >> 12) & 0x0f;
		u32 rn = (opcode >>16) & 0x0f;
		u32 address;				
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x1db:
	{
		//LDRH Rd, [Rn, +#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x1fb:
	{
		//LDRH Rd, [Rn, +#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x01d:
case 0x03d:
	{
		// LDRSB Rd, [Rn], -Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		rm = g_nAgbCPUReg[rm];
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x05d:
case 0x07d:	
	{
		//LDRSB Rd, [Rn], -#offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x09d:
case 0x0bd:	
	{
		// LDRSB Rd, [Rn], +Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		rm =g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x0dd:
case 0x0fd:
	{
		//LDRSB Rd, [Rn], +#offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x11d:
	{
		// LDRSB Rd, [Rn, -Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE		
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC		
	}
	break;
case 0x13d:
	{
		// LDRSB Rd, [Rn, -Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC

	}
	break;
case 0x15d:
	{
		//LDRSB Rd, [Rn, -#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x17d:
	{
		//LDRSB Rd, [Rn, -#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;	
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x19d:
	{
		// LDRSB Rd, [Rn, +Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x1bd:
	{
		// LDRSB Rd, [Rn, +Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x1dd:
	{
		//LDRSB Rd, [Rn, +#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x1fd:
	{
		//LDRSB Rd, [Rn, +#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s8)agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x01f:
case 0x03f:
	{
		// LDRSH Rd, [Rn], -Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		rm = g_nAgbCPUReg[rm];
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x05f:
case 0x07f:
	{
		//LDRSH Rd, [Rn], -#offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x09f:
case 0x0bf:	
	{
		// LDRSH Rd, [Rn], +Rm
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		rm =g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x0df:
case 0x0ff:	
	{
		//LDRSH Rd, [Rn], +#offset
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x11f:
	{
		// LDRSH Rd, [Rn, -Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC			
	}
	break;
case 0x13f:
	{
		// LDRSH Rd, [Rn, -Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] -g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC

	}
	break;
case 0x15f:
	{
		//LDRSH Rd, [Rn, -#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE		
		address = g_nAgbCPUReg[rn] - rm;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x17f:
	{
		//LDRSH Rd, [Rn, -#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] - rm;	
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x19f:
	{
		// LDRSH Rd, [Rn, +Rm]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x1bf:
	{
		// LDRSH Rd, [Rn, +Rm]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x1df:
	{
		//LDRSH Rd, [Rn, +#offset]
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;		
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
case 0x1ff:
	{
		// LDRSH Rd, [Rn, +#offset]!
		ARM_RM_RD_RN_ADDRESS_DEFINE
		address = g_nAgbCPUReg[rn] + rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = (s16)agbMemRead16(address);
		LDR_TO_PC
	}
	break;
CASE_16(0x400)
CASE_16(0x420)
	{
		// STRT Rd, [Rn], -#offset
		// STR   Rd, [Rn], -#offset
		ARM_RMIMM_RD_RN_DEFINE		
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		
	}
	break;
CASE_16(0x480)
CASE_16(0x4a0)
	{
		// STRT Rd, [Rn], +#offset
		// STR   Rd, [Rn], +#offset
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x500)
	{
		// STR Rd, [Rn, -#offset]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x520)
	{
		// STR Rd, [Rn, -#offset]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x580)
	{
		// STR Rd, [Rn, +#offset]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x5a0)
	{
		// STR Rd, [Rn, +#offset]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x410)
CASE_16(0x430)
	{
		// LDR   Rd, [Rn], -#offset
		// LDRT Rd, [Rn], -#offset
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x490)
CASE_16(0x4b0)
	{
		// LDR   Rd, [Rn], #offset
		// LDRT Rd, [Rn], #offset
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x510)
	{
		// LDR Rd, [Rn, -#Rm]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x530)
	{
		// LDR Rd, [Rn, -#Rm]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x590)
	{
		// LDR Rd, [Rn, +#Rm]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x5b0)
	{
		// LDR Rd, [Rn, +#Rm]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x440)
CASE_16(0x460)
	{
		// STRBT Rd, [Rn], -#offset
		// STRB   Rd, [Rn], -#offset
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);

	}
	break;
CASE_16(0x4c0)
CASE_16(0x4e0)
	{
		// STRBT Rd, [Rn], +#offset
		// STRB   Rd, [Rn], +#offset
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);

	}
	break;
CASE_16(0x540)
	{
		// STRB Rd, [Rn, -#offset]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x560)
	{
		// STRB Rd, [Rn, -#offset]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x5c0)
	{
		// STRB Rd, [Rn, +#offset]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x5e0)
	{
		// STRB Rd, [Rn, +#offset]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
CASE_16(0x450)
CASE_16(0x470)
	{
		// LDRBT Rd, [Rn], -#offset
		// LDRB   Rd, [Rn], -#offset				
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address - rm;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x4d0)
CASE_16(0x4f0)
	{
		// LDRB   Rd, [Rn], #offset
		// LDRBT Rd, [Rn], #offset
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + rm;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x550)
	{
		// LDRB Rd, [Rn, -#Rm]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x570)
	{
		// LDRB Rd, [Rn, -#Rm]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address -= rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x5d0)
	{
		// LDRB Rd, [Rn, +#offset]
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC;
	}
	break;
CASE_16(0x5f0)
	{
		// LDRB Rd, [Rn, +#offset]!
		ARM_RMIMM_RD_RN_DEFINE
		u32 address = g_nAgbCPUReg[rn];
		address += rm;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC;
	}
	break;
case 0x600:
case 0x608:
case 0x620:
case 0x628:
	{
		//STRT Rd, [Rn], -Rm, LSL #imm
		//STR   Rd, [Rn], -Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE		
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] << shift_imm);
	}
	break;
case 0x602:
case 0x60a:
case 0x622:
case 0x62a:
	{
		//STRT Rd, [Rn], -Rm, LSR #imm
		//STR   Rd, [Rn], -Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE		
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] >> shift_imm);
		
	}
	break;
case 0x604:
case 0x60c:
case 0x624:
case 0x62c:
	{
		//STRT Rd, [Rn], -Rm, ASR #imm
		//STR   Rd, [Rn], -Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address - ((s32)g_nAgbCPUReg[rm] >> shift_imm);
	}
	break;
case 0x606:
case 0x60e:
case 0x626:
case 0x62e:
	{
		//STRT Rd, [Rn], -Rm, ROR #imm
		//STR   Rd, [Rn], -Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address - offset;
	}
	break;
case 0x680:
case 0x688:
case 0x6a0:
case 0x6a8:
	{
		//STRT Rd, [Rn], Rm, LSL #imm
		//STR   Rd, [Rn], Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE		
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] << shift_imm);
	}
	break;
case 0x682:
case 0x68a:
case 0x6a2:
case 0x6aa:
	{
		//STRT Rd, [Rn], Rm, LSR #imm
		//STR   Rd, [Rn], Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x684:
case 0x68c:
case 0x6a4:
case 0x6ac:
	{
		//STRT Rd, [Rn], Rm, ASR #imm
		//STR   Rd, [Rn], Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x686:
case 0x68e:
case 0x6a6:
case 0x6ae:
	{
		//STRT Rd, [Rn], Rm, ROR #imm
		//STR   Rd, [Rn], Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address + offset;
	}
	break;
case 0x700:
case 0x708:
	{
		//STR Rd, [Rn, -Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x702:
case 0x70a:
	{
		//STR Rd, [Rn, -Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x704:
case 0x70c:
	{
		//STR Rd, [Rn, -Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x706:
case 0x70e:
	{
		//STR Rd, [Rn, -Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x720:
case 0x728:
	{
		//STR Rd, [Rn, -Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x722:
case 0x72a:
	{
		//STR Rd, [Rn, -Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x724:
case 0x72c:
	{
		//STR Rd, [Rn, -Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x726:
case 0x72e:
	{
		//STR Rd, [Rn, -Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x780:
case 0x788:
	{
		//STR Rd, [Rn, Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x782:
case 0x78a:
	{
		//STR Rd, [Rn, Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x784:
case 0x78c:
	{
		//STR Rd, [Rn, Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x786:
case 0x78e:
	{
		//STR Rd, [Rn, Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address += offset;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7a0:
case 0x7a8:
	{
		//STR Rd, [Rn, Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7a2:
case 0x7aa:
	{
		//STR Rd, [Rn, Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7a4:
case 0x7ac:
	{
		//STR Rd, [Rn, Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7a6:
case 0x7ae:
	{
		//STR Rd, [Rn, Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite32(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x610:
case 0x618:
case 0x630:
case 0x638:
	{
		//LDRT Rd, [Rn], -Rm, LSL #imm
		//LDR   Rd, [Rn], -Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x612:
case 0x61a:
case 0x632:
case 0x63a:
	{
		//LDRT Rd, [Rn], -Rm, LSR #imm
		//LDR   Rd, [Rn], -Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;		
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC	
	}
	break;
case 0x614:
case 0x61c:
case 0x634:
case 0x63c:
	{
		//LDRT Rd, [Rn], -Rm, ASR #imm
		//LDR   Rd, [Rn], -Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address - ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x616:
case 0x61e:
case 0x636:
case 0x63e:
	{
		//LDRT Rd, [Rn], -Rm, ROR #imm
		//LDR   Rd, [Rn], -Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address - offset;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x690:
case 0x698:
case 0x6b0:
case 0x6b8:
	{
		//LDRT Rd, [Rn], Rm, LSL #imm
		//LDR   Rd, [Rn], Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x692:
case 0x69a:
case 0x6b2:
case 0x6ba:
	{
		//LDRT Rd, [Rn], Rm, LSR #imm
		//LDR   Rd, [Rn], Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC	
	}
	break;
case 0x694:
case 0x69c:
case 0x6b4:
case 0x6bc:
	{
		//LDRT Rd, [Rn], Rm, ASR #imm
		//LDR   Rd, [Rn], Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x696:
case 0x69e:
case 0x6b6:
case 0x6be:
	{
		//LDRT Rd, [Rn], Rm, ROR #imm
		//LDR   Rd, [Rn], Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address + offset;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x710:
case 0x718:
	{
		//LDR Rd, [Rn, -Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE		
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x712:
case 0x71a:
	{
		//LDR Rd, [Rn, -Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x714:
case 0x71c:
	{
		//LDR Rd, [Rn, -Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x716:
case 0x71e:
	{
		//LDR Rd, [Rn, -Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x730:
case 0x738:
	{
		//LDR Rd, [Rn, -Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x732:
case 0x73a:
	{
		//LDR Rd, [Rn, -Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x734:
case 0x73c:
	{
		//LDR Rd, [Rn, -Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x736:
case 0x73e:
	{
		//LDR Rd, [Rn, -Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x790:
case 0x798:
	{
		//LDR Rd, [Rn, Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x792:
case 0x79a:
	{
		//LDR Rd, [Rn, Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x794:
case 0x79c:
	{
		//LDR Rd, [Rn, Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x796:
case 0x79e:
	{
		//LDR Rd, [Rn, Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address += offset;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x7b0:
case 0x7b8:
	{
		//LDR Rd, [Rn, Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x7b2:
case 0x7ba:
	{
		//LDR Rd, [Rn, Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x7b4:
case 0x7bc:
	{
		//LDR Rd, [Rn, Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x7b6:
case 0x7be:
	{
		//LDR Rd, [Rn, Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address += offset;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead32(address);
		LDR_TO_PC
	}
	break;
case 0x640:
case 0x648:
case 0x660:
case 0x668:
	{
		//STRBT Rd, [Rn], -Rm, LSL #imm
		//STRB   Rd, [Rn], -Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] << shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);				
	}
	break;
case 0x642:
case 0x64a:
case 0x662:
case 0x66a:
	{
		//STRBT Rd, [Rn], -Rm, LSR #imm
		//STRB   Rd, [Rn], -Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);				
	}
	break;
case 0x644:
case 0x64c:
case 0x664:
case 0x66c:
	{
		//STRBT Rd, [Rn], -Rm, ASR #imm
		//STRB   Rd, [Rn], -Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address - ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x646:
case 0x64e:
case 0x666:
case 0x66e:
	{
		//STRBT Rd, [Rn], -Rm, ROR #imm
		//STRB   Rd, [Rn], -Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address - offset;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x6c0:
case 0x6c8:
case 0x6e0:
case 0x6e8:
	{
		//STRBT Rd, [Rn], Rm, LSL #imm
		//STRB   Rd, [Rn], Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] << shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);				
	}
	break;
case 0x6c2:
case 0x6ca:
case 0x6e2:
case 0x6ea:
	{
		//STRBT Rd, [Rn], Rm, LSR #imm
		//STRB   Rd, [Rn], Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);				
	}
	break;
case 0x6c4:
case 0x6cc:
case 0x6e4:
case 0x6ec:
	{
		//STRBT Rd, [Rn], Rm, ASR #imm
		//STRB   Rd, [Rn], Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x6c6:
case 0x6ce:
case 0x6e6:
case 0x6ee:
	{
		//STRBT Rd, [Rn], Rm, ROR #imm
		//STRB   Rd, [Rn], Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address + offset;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x740:
case 0x748:
	{
		//STRB Rd, [Rn, -Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x742:
case 0x74a:
	{
		//STRB Rd, [Rn, -Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x744:
case 0x74c:
	{
		//STRB Rd, [Rn, -Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x746:
case 0x74e:
	{
		//STRB Rd, [Rn, -Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x760:
case 0x768:
	{
		//STRB Rd, [Rn, -Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x762:
case 0x76a:
	{
		//STRB Rd, [Rn, -Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x764:
case 0x76c:
	{
		//STRB Rd, [Rn, -Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x766:
case 0x76e:
	{
		//STRB Rd, [Rn, -Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7c0:
case 0x7c8:
	{
		//STRB Rd, [Rn, Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7c2:
case 0x7ca:
	{
		//STRB Rd, [Rn, Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7c4:
case 0x7cc:
	{
		//STRB Rd, [Rn, Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7c6:
case 0x7ce:
	{
		//STRB Rd, [Rn, Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address += offset;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7e0:
case 0x7e8:
	{
		//STRB Rd, [Rn, Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7e2:
case 0x7ea:
	{
		//STRB Rd, [Rn, Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7e4:
case 0x7ec:
	{
		//STRB Rd, [Rn, Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x7e6:
case 0x7ee:
	{
		//STRB Rd, [Rn, Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rn] = address;
		agbMemWrite8(address, g_nAgbCPUReg[rd]);
	}
	break;
case 0x650:
case 0x658:
case 0x670:
case 0x678:
	{
		//LDRBT Rd, [Rn], -Rm, LSL #imm
		//LDRB   Rd, [Rn], -Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x652:
case 0x65a:
case 0x672:
case 0x67a:
	{
		//LDRBT Rd, [Rn], -Rm, LSR #imm
		//LDRB   Rd, [Rn], -Rm, LSR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;		
		g_nAgbCPUReg[rn] = address - (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC	
	}
	break;
case 0x654:
case 0x65c:
case 0x674:
case 0x67c:
	{
		//LDRBT Rd, [Rn], -Rm, ASR #imm
		//LDRB   Rd, [Rn], -Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address - ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x656:
case 0x65e:
case 0x676:
case 0x67e:
	{
		//LDRBT Rd, [Rn], -Rm, ROR #imm
		//LDRB   Rd, [Rn], -Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address - offset;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x6d0:
case 0x6d8:
case 0x6f0:
case 0x6f8:
	{
		//LDRBT Rd, [Rn], Rm, LSL #imm
		//LDRB   Rd, [Rn], Rm, LSL #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x6d2:
case 0x6da:
case 0x6f2:
case 0x6fa:
	{
		//LDRBT Rd, [Rn], Rm, LSR #imm
		//LDRB   Rd, [Rn], Rm, LSR #imm
		u32 rm = opcode&0xf;
		u32 shift_imm = (opcode >>7) & 0x1f;
		u32 rd = (opcode >> 12) & 15;
		u32 rn = (opcode >> 16) & 15;
		if(shift_imm == 0)
			shift_imm = 32;
		u32 address = g_nAgbCPUReg[rn];
		g_nAgbCPUReg[rn] = address + (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC	
	}
	break;
case 0x6d4:
case 0x6dc:
case 0x6f4:
case 0x6fc:
	{
		//LDRBT Rd, [Rn], Rm, ASR #imm
		//LDRB   Rd, [Rn], Rm, ASR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		g_nAgbCPUReg[rn] = address + ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x6d6:
case 0x6de:
case 0x6f6:
case 0x6fe:
	{
		//LDRBT Rd, [Rn], Rm, ROR #imm
		//LDRB   Rd, [Rn], Rm, ROR #imm
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		g_nAgbCPUReg[rn] = address + offset;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x750:
case 0x758:
	{
		//LDRB Rd, [Rn, -Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x752:
case 0x75a:
	{
		//LDRB Rd, [Rn, -Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x754:
case 0x75c:
	{
		//LDRB Rd, [Rn, -Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x756:
case 0x75e:
	{
		//LDRB Rd, [Rn, -Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x770:
case 0x778:
	{
		//LDRB Rd, [Rn, -Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address -= (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x772:
case 0x77a:
	{
		//LDRB Rd, [Rn, -Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x774:
case 0x77c:
	{
		//LDRB Rd, [Rn, -Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address -= ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x776:
case 0x77e:
	{
		//LDRB Rd, [Rn, -Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address -= offset;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7d0:
case 0x7d8:
	{
		//LDRB Rd, [Rn, Rm, LSL #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7d2:
case 0x7da:
	{
		//LDRB Rd, [Rn, Rm, LSR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7d4:
case 0x7dc:
	{
		//LDRB Rd, [Rn, Rm, ASR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7d6:
case 0x7de:
	{
		//LDRB Rd, [Rn, Rm, ROR #imm]
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address += offset;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7f0:
case 0x7f8:
	{
		//LDRB Rd, [Rn, Rm, LSL #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		address += (g_nAgbCPUReg[rm] << shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7f2:
case 0x7fa:
	{
		//LDRB Rd, [Rn, Rm, LSR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += (g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7f4:
case 0x7fc:
	{
		//LDRB Rd, [Rn, Rm, ASR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		if(shift_imm == 0)
			shift_imm = 32;
		address += ((s32)g_nAgbCPUReg[rm] >> shift_imm);
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
case 0x7f6:
case 0x7fe:
	{
		//LDRB Rd, [Rn, Rm, ROR #imm]!
		ARM_RM_IMM_RD_RN_ADD_DEFINE
		u32 offset = g_nAgbCPUReg[rm];
		ARM_ROR_SHIFT_OFFSET
		address += offset;
		g_nAgbCPUReg[rn] = address;
		g_nAgbCPUReg[rd] = agbMemRead8(address);
		LDR_TO_PC
	}
	break;
CASE_16(0x800)
	{
		// STMDA Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		STM_REG16
	}
	break;
CASE_16(0x820)
	{
		// STMDA Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		STM_REG16
		g_nAgbCPUReg[rn] = startaddress - 4;
	}
	break;
CASE_16(0x840)
	{
		// STMDA Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		STM_REG16_CPSR
	}
	break;
CASE_16(0x860)
	{
		// STMDA Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		STM_REG16_CPSR
		g_nAgbCPUReg[rn] = startaddress - 4;
	}
	break;
CASE_16(0x880)
	{
		// STMIA Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		STM_REG16
	}
	break;
CASE_16(0x8a0)
	{
		// STMIA Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		STM_REG16
			g_nAgbCPUReg[rn] = endaddress + 4;
	}
	break;
CASE_16(0x8c0)
	{
		// STMIA Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		STM_REG16_CPSR
	}
	break;
CASE_16(0x8e0)
	{
		// STMIA Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		STM_REG16_CPSR
		g_nAgbCPUReg[rn] = endaddress + 4;
	}
	break;
CASE_16(0x810)
	{
		// LDMDA Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		LDM_REG16
	}
	break;
CASE_16(0x830)
	{
		// LDMDA Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		LDM_REG16
		g_nAgbCPUReg[rn] = startaddress - 4;
	}
	break;
CASE_16(0x850)
	{
		// LDMDA Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		LDM_REG16_CPSR
	}
	break;
CASE_16(0x870)
	{
		// LDMDA Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) + 4;
		u32 endaddress = g_nAgbCPUReg[rn];
		u32 address = startaddress;
		u32 temp = startaddress - 4;
		LDM_REG16W_CPSR
	}
	break;
CASE_16(0x890)
	{
		// LDMIA Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		LDM_REG16
	}
	break;
CASE_16(0x8b0)
	{
		// LDMIA Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		LDM_REG16
			g_nAgbCPUReg[rn] = endaddress + 4;
	}
	break;
CASE_16(0x8d0)
	{
		// LDMIA Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		LDM_REG16_CPSR
	}
	break;
CASE_16(0x8f0)
	{
		// LDMIA Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn];
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]) - 4;
		u32 address = startaddress;
		u32 temp = endaddress + 4;
		LDM_REG16W_CPSR
	}
	break;
CASE_16(0x900)
	{
		// STMDB Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		STM_REG16
	}
	break;
CASE_16(0x920)
	{
		// STMDB Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		STM_REG16
			g_nAgbCPUReg[rn] = startaddress;
	}
	break;
CASE_16(0x940)
	{
		// STMDB Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		STM_REG16_CPSR
	}
	break;
CASE_16(0x960)
	{
		// STMDB Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		STM_REG16_CPSR
		g_nAgbCPUReg[rn] = startaddress;
	}
	break;
CASE_16(0x980)
	{
		// STMIB Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		STM_REG16
	}
	break;
CASE_16(0x9a0)
	{
		// STMIB Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		STM_REG16
		g_nAgbCPUReg[rn] = endaddress;
	}
	break;
CASE_16(0x9c0)
	{
		// STMIB Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		STM_REG16_CPSR
	}
	break;
CASE_16(0x9e0)
	{
		// STMIB Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		STM_REG16_CPSR
		g_nAgbCPUReg[rn] = endaddress;
	}
	break;
CASE_16(0x910)
	{
		// LDMDB Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		LDM_REG16
	}
	break;
CASE_16(0x930)
	{
		// LDMDB Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		LDM_REG16
		g_nAgbCPUReg[rn] = startaddress;
	}
	break;
CASE_16(0x950)
	{
		// LDMDB Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		LDM_REG16_CPSR
	}
	break;
CASE_16(0x970)
	{
		// LDMDB Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] - 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 endaddress = g_nAgbCPUReg[rn] - 4;
		u32 address = startaddress;
		u32 temp = startaddress;
		LDM_REG16W_CPSR
	}
	break;
CASE_16(0x990)
	{
		// LDMIB Rn, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		STM_REG16
	}
	break;
CASE_16(0x9b0)
	{
		// LDMIB Rn!, {Rlist}
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		LDM_REG16
			g_nAgbCPUReg[rn] = endaddress;
	}
	break;
CASE_16(0x9d0)
	{
		// LDMIB Rn, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		LDM_REG16_CPSR
	}
	break;
CASE_16(0x9f0)
	{
		// LDMIB Rn!, {Rlist}^
		ARM_RN_RLIST_DEFINE
		u32 startaddress = g_nAgbCPUReg[rn] + 4;
		u32 endaddress = g_nAgbCPUReg[rn] + 4*(g_nAgbCpuBitsSet[rlist &0xff] + g_nAgbCpuBitsSet[rlist >>8]);
		u32 address = startaddress;
		u32 temp = endaddress;
		LDM_REG16W_CPSR
		g_nAgbCPUReg[rn] = endaddress;
	}
	break;
CASE_256(0xa00)
	{
		// B offset
		s32 offset = opcode &0x00ffffff;
		if(offset &0x00800000)
			offset |= 0xff000000;
		offset <<=2;
		g_nAgbCPUReg[15] += offset;
		g_nAgbCPUReg[15] &= 0xfffffffc;
		ARM_FIRST_PREFETCH
	}
	break;
CASE_256(0xb00)
	{
		// BL offset
		s32 offset = opcode &0x00ffffff;
		if(offset &0x00800000)
			offset |= 0xff000000;
		offset <<=2;
		g_nAgbCPUReg[14] = g_nAgbCPUReg[15] - 4;
		g_nAgbCPUReg[15] += offset;
		g_nAgbCPUReg[15] &= 0xfffffffc;
		ARM_FIRST_PREFETCH
	}
	break;
CASE_256(0xf00)
	{
		// SWI
		agbCPUSWI(opcode &0x00ffffff);
	}
	break;
case 0x100:
	{
		// MRS Rd, CPSR
		agbCPUUpdateCPSR();
		u32 rd = (opcode >> 12) & 15;		
		g_nAgbCPUReg[rd] = g_nAgbCPUReg[16];
	}
	break;
case 0x140:
	{
		//MRS Rd, SPSR
		g_nAgbCPUReg[(opcode >>12)&0xf] = g_nAgbCPUReg[17];
	}
	break;
case 0x109:
	{
		// SWP Rd, Rm, [Rn]
		ARM_RM_RD_RN_DEFINE
		u32 temp = agbMemRead32(g_nAgbCPUReg[rn]);
		agbMemWrite32(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm]);
		g_nAgbCPUReg[rd] = temp;				
	}
	break;
case 0x149:
	{
		// SWPB Rd, Rm, [Rn]
		ARM_RM_RD_RN_DEFINE
		u32 temp = agbMemRead8(g_nAgbCPUReg[rn]);
		agbMemWrite8(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm]);
		g_nAgbCPUReg[rd] = temp;				
	}
	break;
case 0x120:
	{
		// MSR CPSR_fields, Rm
		agbCPUUpdateCPSR();
		u32 rm = (opcode & 0xf);
		u32 field = (opcode >>16) & 0x0f;
		u32 newvalue = g_nAgbCPUReg[16];
		rm =g_nAgbCPUReg[rm];		
		if(g_nAgbCPUReg[REG_CPUMODE] > CPU_MODE_USER)
		{
			if(field & 0x0001)
				newvalue = (newvalue &0xffffff00) | (rm &0x000000ff);
			if(field & 0x0002)
				newvalue = (newvalue &0xffff00ff) | (rm &0x0000ff00);
			if(field & 0x0004)
				newvalue = (newvalue &0xff00ffff) | (rm &0x00ff0000);
		}
		if(field & 0x0008)
			newvalue = (newvalue &0x00ffffff) | (rm &0xff000000);
		newvalue |= 0x10;
		agbCPUSwitchMode(newvalue & 0x1f, 0);
		g_nAgbCPUReg[16] = newvalue;
		agbCPUUpdateFlags();
		if(g_nAgbThumbState)
		{			
			THUMB_FIRST_PREFETCH
		}
	}
	break;
case 0x160:
	{
		// MSR SPSR_fields, Rm
		if(g_nAgbCPUReg[REG_CPUMODE] > CPU_MODE_USER && g_nAgbCPUReg[REG_CPUMODE] < CPU_MODE_SYS)
		{
			u32 rm = (opcode & 0xf);
			u32 field = (opcode >>16) & 0x0f;
			u32 newvalue = g_nAgbCPUReg[17];
			rm =g_nAgbCPUReg[rm];
			if(field & 0x0001)
				newvalue = (newvalue &0xffffff00) | (rm &0x000000ff);
			if(field & 0x0002)
				newvalue = (newvalue &0xffff00ff) | (rm &0x0000ff00);
			if(field & 0x0004)
				newvalue = (newvalue &0xff00ffff) | (rm &0x00ff0000);
			if(field & 0x0008)
				newvalue = (newvalue &0x00ffffff) | (rm &0xff000000);
			g_nAgbCPUReg[17] = newvalue;
		}
	}
	break;
CASE_16(0x320)
	{
		// MSR CPSR_fields, #
		agbCPUUpdateCPSR();
		u32 operand = (opcode & 0xff);
		s32 shift = (opcode & 0xf00) >>7;
		if(shift)
		{
			ROR_IMM_MSR;
		}
		u32 field = (opcode >>16) & 0x0f;		
		u32 newvalue = g_nAgbCPUReg[16];
		if(g_nAgbCPUReg[REG_CPUMODE] > CPU_MODE_USER)
		{
			if(field & 0x0001)
				newvalue = (newvalue &0xffffff00) | (operand &0x000000ff);
			if(field & 0x0002)
				newvalue = (newvalue &0xffff00ff) | (operand &0x0000ff00);
			if(field & 0x0004)
				newvalue = (newvalue &0xff00ffff) | (operand &0x00ff0000);
		}
		if(field & 0x0008)
			newvalue = (newvalue &0x00ffffff) | (operand &0xff000000);
		newvalue |= 0x10;
		agbCPUSwitchMode(newvalue & 0x1f, 0);
		g_nAgbCPUReg[16] = newvalue;
		agbCPUUpdateFlags();
		if(g_nAgbThumbState)
		{
			THUMB_FIRST_PREFETCH
		}
	}
	break;
CASE_16(0x360)
	{
		// MSR SPSR_fields, #
		//zhfang test
		if(g_nAgbCPUReg[REG_CPUMODE] > CPU_MODE_USER && g_nAgbCPUReg[REG_CPUMODE] < CPU_MODE_SYS)
		{
			u32 operand = (opcode & 0xff);
			s32 shift = (opcode & 0xf00) >>7;
			if(shift)
			{
				ROR_IMM_MSR;
			}
			u32 field = (opcode >>16) & 0x0f;
			u32 newvalue = g_nAgbCPUReg[17];
			if(field & 0x0001)
				newvalue = (newvalue &0xffffff00) | (operand &0x000000ff);
			if(field & 0x0002)
				newvalue = (newvalue &0xffff00ff) | (operand &0x0000ff00);
			if(field & 0x0004)
				newvalue = (newvalue &0xff00ffff) | (operand &0x00ff0000);
			if(field & 0x0008)
				newvalue = (newvalue &0x00ffffff) | (operand &0xff000000);
			g_nAgbCPUReg[17] = newvalue;
		}
	}
	break;
case  0x121:
	{
		// BX Rm
		u32 rm = (opcode & 0xf);
		g_nAgbThumbState = (g_nAgbCPUReg[rm]&0x1);		
		if(g_nAgbThumbState)
		{
			g_nAgbCPUReg[15] = (g_nAgbCPUReg[rm] & 0xfffffffe);
			THUMB_FIRST_PREFETCH
		}
		else
		{
			g_nAgbCPUReg[15] = (g_nAgbCPUReg[rm] & 0xfffffffc);
			ARM_FIRST_PREFETCH
		}		
	}
	break;
	LOGICAL_DATA_OPCODE(OP_AND, OP_AND, 0x000);
	LOGICAL_DATA_OPCODE(OP_ANDS, OP_ANDS, 0x010);
	LOGICAL_DATA_OPCODE(OP_EOR,  OP_EOR, 0x020);
	LOGICAL_DATA_OPCODE(OP_EORS, OP_EOR, 0x030);
	LOGICAL_DATA_OPCODE(OP_TST, OP_TST, 0x110);
	LOGICAL_DATA_OPCODE(OP_TEQ, OP_TEQ, 0x130);
	LOGICAL_DATA_OPCODE(OP_ORR,  OP_ORR, 0x180);
	LOGICAL_DATA_OPCODE(OP_ORRS, OP_ORR, 0x190);
	LOGICAL_DATA_OPCODE(OP_MOV,  OP_MOV, 0x1a0);
	LOGICAL_DATA_OPCODE(OP_MOVS, OP_MOV, 0x1b0);
	LOGICAL_DATA_OPCODE(OP_BIC,  OP_BIC, 0x1c0);
	LOGICAL_DATA_OPCODE(OP_BICS, OP_BIC, 0x1d0);
	LOGICAL_DATA_OPCODE(OP_MVN,  OP_MVN, 0x1e0);
	LOGICAL_DATA_OPCODE(OP_MVNS, OP_MVN, 0x1f0);
	
	ARITHMETIC_DATA_OPCODE(OP_SUB,  OP_SUB, 0x040);
	ARITHMETIC_DATA_OPCODE(OP_SUBS, OP_SUB, 0x050);
	ARITHMETIC_DATA_OPCODE(OP_RSB,  OP_RSB, 0x060);
	ARITHMETIC_DATA_OPCODE(OP_RSBS, OP_RSB, 0x070);		
	ARITHMETIC_DATA_OPCODE(OP_ADD,  OP_ADD, 0x080);
	ARITHMETIC_DATA_OPCODE(OP_ADDS, OP_ADD, 0x090);
	ARITHMETIC_DATA_OPCODE(OP_ADC,  OP_ADC, 0x0a0);
	ARITHMETIC_DATA_OPCODE(OP_ADCS, OP_ADC, 0x0b0);

	ARITHMETIC_DATA_OPCODE(OP_SBC,  OP_SBC, 0x0c0);
	ARITHMETIC_DATA_OPCODE(OP_SBCS, OP_SBC, 0x0d0);
	ARITHMETIC_DATA_OPCODE(OP_RSC,  OP_RSC, 0x0e0);
	ARITHMETIC_DATA_OPCODE(OP_RSCS, OP_RSC, 0x0f0);
	ARITHMETIC_DATA_OPCODE(OP_CMP, OP_CMP, 0x150);
	ARITHMETIC_DATA_OPCODE(OP_CMN, OP_CMN, 0x170);
default:
	TRL_ERROR("unknown arm instruction");
	break;
}

