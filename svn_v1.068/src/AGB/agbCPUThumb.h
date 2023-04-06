
#define THUMB_NEG(i) ((i) >> 31)
#define THUMB_POS(i) ((~(i)) >> 31)

#define THUMB_ADDCARRY(a, b, c) \
	g_nAgbCPUReg[REG_CFLAG] = ((THUMB_NEG(a) & THUMB_NEG(b)) |\
	(THUMB_NEG(a) & THUMB_POS(c)) |\
	(THUMB_NEG(b) & THUMB_POS(c))) ? true : false;

#define THUMB_ADDOVERFLOW(a, b, c) \
	g_nAgbCPUReg[REG_VFLAG] = ((THUMB_NEG(a) & THUMB_NEG(b) & THUMB_POS(c)) |\
	(THUMB_POS(a) & THUMB_POS(b) & THUMB_NEG(c))) ? true : false;

#define THUMB_SUBCARRY(a, b, c) \
	g_nAgbCPUReg[REG_CFLAG] = ((THUMB_NEG(a) & THUMB_POS(b)) |\
	(THUMB_NEG(a) & THUMB_POS(c)) |\
	(THUMB_POS(b) & THUMB_POS(c))) ? true : false;

#define THUMB_SUBOVERFLOW(a, b, c)\
	g_nAgbCPUReg[REG_VFLAG] = ((THUMB_NEG(a) & THUMB_POS(b) & THUMB_POS(c)) |\
	(THUMB_POS(a) & THUMB_NEG(b) & THUMB_NEG(c))) ? true : false;

	
#define CASE_8(base) \
	case base:\
	case base+1:\
	case base+2:\
	case base+3:\
	case base+4:\
	case base+5:\
	case base+6:\
	case base+7:

#define THUMB_LSL_RD_RM_I5\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rm]>>(32-imm5))&0x1;\
	g_nAgbCPUReg[rd] = (g_nAgbCPUReg[rm]<<imm5);

#define THUMB_LSL_RD_RS\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>(32-rs))&0x1;\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rd]<<rs;

#define THUMB_LSR_RD_RM_I5\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rm]>>(imm5-1))&0x1;\
	g_nAgbCPUReg[rd] = (g_nAgbCPUReg[rm]>>imm5);

#define THUMB_LSR_RD_RS\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>(rs-1))&0x1;\
	g_nAgbCPUReg[rd] = g_nAgbCPUReg[rd]>>rs;

#define THUMB_ASR_RD_RM_IMM5\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rm] >>(imm5-1))&0x1;\
	g_nAgbCPUReg[rd] = ((s32)g_nAgbCPUReg[rm])>>imm5;

#define THUMB_ASR_RD_RS\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>(rs-1))&0x1;\
	g_nAgbCPUReg[rd] = ((s32)g_nAgbCPUReg[rd])>>rs;

#define THUMB_ROR_RD_RS\
	g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>(rs-1))&0x1;\
	g_nAgbCPUReg[rd] = ((g_nAgbCPUReg[rd]<<(32-rs)) | (g_nAgbCPUReg[rd]>>rs));
	

#define THUMB_RD_RM_IMM5_DEFINE\
	u32 rd = (opcode &0x7);\
	u32 rm = (opcode>>3)&0x7;\
	u32 imm5 = (opcode>>6)&0x1f;

#define THUMB_RD_RN_IMM5_DEFINE\
	u32 rd = (opcode &0x7);\
	u32 rn = (opcode>>3)&0x7;\
	u32 imm5 = (opcode>>6)&0x1f;

#define THUMB_RD_RS_DEFINE\
	u32 rd = (opcode &0x7);\
	u32 rs = (opcode>>3)&0x7;

#define THUMB_RD_RM_DEFINE\
	u32 rd = (opcode &0x7);\
	u32 rm = (opcode>>3)&0x7;

#define THUMB_RN_RM_DEFINE\
	u32 rn = (opcode &0x7);\
	u32 rm = (opcode>>3)&0x7;

#define THUMB_RM_DEFINE\
	u32 rm = (opcode>>3)&0x7;

#define THUMB_RD_RN_RM_DEFINE\
	u32 rd = (opcode &0x7);\
	u32 rn = (opcode>>3)&0x7;\
	u32 rm = (opcode>>6)&0x7;

#define THUMB_RD_RN_IMM3_DEFINE\
	u32 rd = (opcode &0x7);\
	u32 rn = (opcode>>3)&0x7;\
	u32 imm3 = (opcode>>6)&0x7;

#define THUMB_RD_IMM8\
	u32 imm8 = (opcode &0xff);\
	u32 rd = (opcode>>8)&7;

#define THUMB_NZFLAG_BY_RD\
	g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[rd]>>31)&0x1;\
	g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[rd] == 0);

#define THUMB_NZFLAG_BY_VALUE\
	g_nAgbCPUReg[REG_NFLAG] = (value>>31);\
	g_nAgbCPUReg[REG_ZFLAG] = (value == 0);

#define THUMB_PC_WRITE\
	if(rd == 7)\
	{\
		g_nAgbCPUReg[15] &= 0xfffffffe;\
		THUMB_FIRST_PREFETCH\
	}
	
#define THUMB_PUSH_REG(val, r)\
	if(opcode &(val))\
	{\
		agbMemWrite32(address, g_nAgbCPUReg[(r)]);\
		address +=4;\
	}

#define THUMB_POP_REG(val, r)\
	if(opcode &(val))\
	{\
		g_nAgbCPUReg[(r)] = agbMemRead32(address);\
		address += 4;\
	}

#define THUMB_STM_REG(val, r, b)\
	if(opcode &(val))\
	{\
		agbMemWrite32(address, g_nAgbCPUReg[(r)]);\
		if(!offset)\
		{\
			g_nAgbCPUReg[(b)] = temp;\
		}\
		offset = 1;\
		address +=4;\
	}

#define THUMB_LDM_REG(val, r)\
	if(opcode &(val))\
	{\
		g_nAgbCPUReg[(r)] = agbMemRead32(address);\
		address+=4;\
	}

#define THUMB_BCOND_SIMM8\
	g_nAgbCPUReg[15] += ((s8)(opcode &0xff))<<1;\
	THUMB_FIRST_PREFETCH

switch(opcode>>8)
{
	CASE_8(0x00)
		{
			// LSL Rd, Rm, #Imm5
			THUMB_RD_RM_IMM5_DEFINE
			if(imm5 == 0)
			{
				g_nAgbCPUReg[rd] = g_nAgbCPUReg[rm];
			}
			else
			{
				THUMB_LSL_RD_RM_I5
			}
			THUMB_NZFLAG_BY_RD
		}
		break;
	CASE_8(0x08)
		{
			// LSR Rd, Rm, #Imm5
			THUMB_RD_RM_IMM5_DEFINE
			if(imm5 == 0)
			{
				g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>31)&0x1;
				g_nAgbCPUReg[rd] = 0;
			}
			else
			{
				THUMB_LSR_RD_RM_I5
			}
			THUMB_NZFLAG_BY_RD
		}
		break;
	CASE_8(0x10)
		{
			// ASR Rd, Rm, #Imm5
			THUMB_RD_RM_IMM5_DEFINE
			if(imm5 == 0)
			{
				g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>31)&0x1;
				g_nAgbCPUReg[rd] = 0;
			}
			else
			{
				THUMB_ASR_RD_RM_IMM5
			}
			THUMB_NZFLAG_BY_RD
		}
		break;
	case 0x18:
	case 0x19:
		{
			// ADD Rd, Rn, Rm
			THUMB_RD_RN_RM_DEFINE
			u32 value = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
			THUMB_NZFLAG_BY_VALUE
			THUMB_ADDCARRY(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value);
			THUMB_ADDOVERFLOW(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value);
			g_nAgbCPUReg[rd] = value;
		}	
		break;
	case 0x1a:
	case 0x1b:
		{
			// SUB Rd, Rs, Rn
			THUMB_RD_RN_RM_DEFINE
			u32 value = g_nAgbCPUReg[rn] - g_nAgbCPUReg[rm];
			THUMB_NZFLAG_BY_VALUE
			THUMB_SUBCARRY(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value);
			THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value);
			g_nAgbCPUReg[rd] = value;
		}
		break;
	case 0x1c:
	case 0x1d:
		{
			// ADD Rd, Rn, #imm3
			THUMB_RD_RN_IMM3_DEFINE
			u32 value = g_nAgbCPUReg[rn] + imm3;
			THUMB_NZFLAG_BY_VALUE
			THUMB_ADDCARRY(g_nAgbCPUReg[rn], imm3, value);
			THUMB_ADDOVERFLOW(g_nAgbCPUReg[rn], imm3, value);
			g_nAgbCPUReg[rd] = value;
		}
		break;
	case 0x1e:
	case 0x1f:
		{
			// SUB Rd, Rn, #imm3
			THUMB_RD_RN_IMM3_DEFINE
			u32 value = g_nAgbCPUReg[rn] - imm3;
			THUMB_NZFLAG_BY_VALUE
			THUMB_SUBCARRY(g_nAgbCPUReg[rn], imm3, value);
			THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn], imm3, value);
			g_nAgbCPUReg[rd] = value;			
		}
		break;
	CASE_8(0x20)
		{
			//MOV Rd, #imm8
			THUMB_RD_IMM8
			g_nAgbCPUReg[rd] = imm8;
			THUMB_NZFLAG_BY_RD
		}
		break;
	CASE_8(0x28)
		{
			// CMP Rd, #imm8
			THUMB_RD_IMM8
			u32 value = g_nAgbCPUReg[rd] - imm8;
			THUMB_NZFLAG_BY_VALUE
			THUMB_SUBCARRY(g_nAgbCPUReg[rd], imm8, value);
			THUMB_SUBOVERFLOW(g_nAgbCPUReg[rd], imm8, value);
		}
		break;
	CASE_8(0x30)
		{
			// ADD Rd, #imm8
			THUMB_RD_IMM8
			u32 value = g_nAgbCPUReg[rd] + imm8;
			THUMB_NZFLAG_BY_VALUE
			THUMB_ADDCARRY(g_nAgbCPUReg[rd], imm8, value);
			THUMB_ADDOVERFLOW(g_nAgbCPUReg[rd], imm8, value);
			g_nAgbCPUReg[rd] = value;
		}
		break;
	CASE_8(0x38)
		{
			// SUB Rd, #imm8
			THUMB_RD_IMM8
			u32 value = g_nAgbCPUReg[rd] - imm8;			
			THUMB_NZFLAG_BY_VALUE
			THUMB_SUBCARRY(g_nAgbCPUReg[rd], imm8, value);
			THUMB_SUBOVERFLOW(g_nAgbCPUReg[rd], imm8, value);
			g_nAgbCPUReg[rd] = value;
		}
		break;
	case 0x40:
		{
			switch( (opcode>>6)&3)
			{
				case 0x00:
					{
						// AND Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = g_nAgbCPUReg[rd] & g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_RD
					}
					break;
				case 0x01:
					{
						// EOR Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = g_nAgbCPUReg[rd]^g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_RD
					}
					break;				
				case 0x02:
				{
					// LSL Rd, Rs
					THUMB_RD_RS_DEFINE
					rs = g_nAgbCPUReg[rs]&0xff;
					if(rs == 0)
					{}
					else if(rs > 0 && rs<32)
					{
						THUMB_LSL_RD_RS
					}
					else if(rs == 32)
					{
						g_nAgbCPUReg[REG_CFLAG] = g_nAgbCPUReg[rd]&0x1;
						g_nAgbCPUReg[rd] = 0;
					}
					else
					{
						g_nAgbCPUReg[REG_CFLAG] = 0;
						g_nAgbCPUReg[rd] = 0;
					}
					THUMB_NZFLAG_BY_RD
				}
				break;
				case 0x03:
				{
					// LSR Rd, Rs
					THUMB_RD_RS_DEFINE
					rs = g_nAgbCPUReg[rs]&0xff;
					if(rs == 0)
					{}
					else if(rs > 0 && rs<32)
					{
						THUMB_LSR_RD_RS
					}
					else if(rs == 32)
					{
						g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>31)&0x1;
						g_nAgbCPUReg[rd] = 0;
					}
					else
					{
						g_nAgbCPUReg[REG_CFLAG] = 0;
						g_nAgbCPUReg[rd] = 0;
					}
					THUMB_NZFLAG_BY_RD
				}
				break;
			}

		}
		break;
	case 0x41:
		{
			switch((opcode >> 6) & 3)
			{
				case 0x00:
					{
						// ASR Rd, Rs
						THUMB_RD_RS_DEFINE
						rs = g_nAgbCPUReg[rs]&0xff;
						if(rs == 0)
						{}
						else if(rs > 0 && rs<32)
						{
							THUMB_ASR_RD_RS
						}
						else if(rs == 32)
						{
								g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>31)&0x1;
								if(g_nAgbCPUReg[REG_CFLAG])						
									g_nAgbCPUReg[rd] = 0xffffffff;
								else
									g_nAgbCPUReg[rd] = 0;
						}
						else
						{
							g_nAgbCPUReg[REG_CFLAG] = 0;
							g_nAgbCPUReg[rd] = 0;
						}
						THUMB_NZFLAG_BY_RD
					}
					break;
				case 0x01:
					{
						// ADC Rd, Rm
						THUMB_RD_RM_DEFINE
						u32 value = g_nAgbCPUReg[rd] + g_nAgbCPUReg[rm] + g_nAgbCPUReg[REG_CFLAG];
						THUMB_NZFLAG_BY_VALUE
						THUMB_ADDCARRY(g_nAgbCPUReg[rd], g_nAgbCPUReg[rm], value)
						THUMB_ADDOVERFLOW(g_nAgbCPUReg[rd], g_nAgbCPUReg[rm], value)
						g_nAgbCPUReg[rd]  = value;
					}
					break;
				case 0x02:
					{
						// SBC Rd, Rm
						THUMB_RD_RM_DEFINE
						u32 value = g_nAgbCPUReg[rd] - g_nAgbCPUReg[rm] - (!g_nAgbCPUReg[REG_CFLAG]);
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY(g_nAgbCPUReg[rd], g_nAgbCPUReg[rm], value);
						THUMB_SUBOVERFLOW(g_nAgbCPUReg[rd], g_nAgbCPUReg[rm], value);
						g_nAgbCPUReg[rd]  = value;
					}
					break;
				case 0x03:
					{
						// ROR Rd, Rs
						THUMB_RD_RS_DEFINE
						rs = g_nAgbCPUReg[rs]&0xff;
						if(rs == 0)
						{}
						else if((rs&0xf) == 0)
						{
							g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[rd]>>31)&0x1;
						}
						else
						{
							rs = rs&0xf;
							THUMB_ROR_RD_RS
						}						
						THUMB_NZFLAG_BY_RD
					}
					break;
			}
			
		}
		break;
	case 0x42:
		{
			switch((opcode >> 6) & 3)
			{
				case 0x00:
					{
						// TST Rd, Rm
						THUMB_RD_RM_DEFINE
						u32 value = (g_nAgbCPUReg[rd] & g_nAgbCPUReg[rm]);
						THUMB_NZFLAG_BY_VALUE
					}
					break;
				case 0x01:
					{
						// NEG Rd, Rm
						THUMB_RD_RM_DEFINE
						u32 value = (u32)0 - g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY((u32)0, g_nAgbCPUReg[rm], value)
						THUMB_SUBOVERFLOW((u32)0, g_nAgbCPUReg[rm], value)
						g_nAgbCPUReg[rd] = value;
					}
					break;
				case 0x02:
					{
						//CMP Rn, Rm
						THUMB_RN_RM_DEFINE
						u32 value = g_nAgbCPUReg[rn] - g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value)
						THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value)
					}
					break;
				case 0x03:
					{
						//CMN Rn, Rm
						THUMB_RN_RM_DEFINE
						u32 value = g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_VALUE
						THUMB_ADDCARRY(g_nAgbCPUReg[rn],g_nAgbCPUReg[rm], value)
						THUMB_ADDOVERFLOW(g_nAgbCPUReg[rn],g_nAgbCPUReg[rm], value)
					}
					break;
			}
		}
		break;
	case 0x43:
		{
			switch((opcode >> 6) & 3)
			{
				case 0x00:
					{
						// ORR Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = g_nAgbCPUReg[rd] | g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_RD
					}
					break;
				case 0x01:
					{
						// MUL Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = (g_nAgbCPUReg[rm] * g_nAgbCPUReg[rd]);
						THUMB_NZFLAG_BY_RD
					}
					break;
				case 0x02:
					{
						//Bic Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = g_nAgbCPUReg[rd] & (~g_nAgbCPUReg[rm]);
						THUMB_NZFLAG_BY_RD
					}
					break;
				case 0x03:
					{
						//MVN Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = (~g_nAgbCPUReg[rm]);
						THUMB_NZFLAG_BY_RD
					}
					break;
			}
		}
		break;
	case 0x44:
		{
			switch((opcode >> 6) & 3)
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
						g_nAgbCPUReg[rd] = (g_nAgbCPUReg[rd] + g_nAgbCPUReg[rm+8]);						
					}
					break;
				case 0x02:
					{
						// ADD Hd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd +8] = (g_nAgbCPUReg[rd + 8] + g_nAgbCPUReg[rm]);						
						THUMB_PC_WRITE
					}
					break;
				case 0x03:
					{
						// ADD Hd, Hm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd + 8] = (g_nAgbCPUReg[rd + 8] + g_nAgbCPUReg[rm +8]);						
						THUMB_PC_WRITE
					}
					break;				
			}
		}
		break;
	case 0x45:
		{
			switch((opcode >> 6) & 3)
			{
				case 0x00:
					{
						//CMP Rn, Rm
						THUMB_RN_RM_DEFINE
						u32 value = g_nAgbCPUReg[rn] - g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value)
						THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm], value)
					}
					break;
				case 0x01:
					{
						//CMP Rn, Hm
						THUMB_RN_RM_DEFINE
						u32 value = g_nAgbCPUReg[rn] - g_nAgbCPUReg[rm +8];
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm+8], value)
						THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn], g_nAgbCPUReg[rm+8], value)
					}
					break;
				case 0x02:
					{
						//CMP Hn, Rm
						THUMB_RN_RM_DEFINE
						u32 value = g_nAgbCPUReg[rn +8] - g_nAgbCPUReg[rm];
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY(g_nAgbCPUReg[rn+8], g_nAgbCPUReg[rm], value)
						THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn+8], g_nAgbCPUReg[rm], value)
					}
					break;
				case 0x03:
					{
						//CMP Hn, Hm
						THUMB_RN_RM_DEFINE
						u32 value = g_nAgbCPUReg[rn +8] - g_nAgbCPUReg[rm +8];
						THUMB_NZFLAG_BY_VALUE
						THUMB_SUBCARRY(g_nAgbCPUReg[rn+8], g_nAgbCPUReg[rm+8], value)
						THUMB_SUBOVERFLOW(g_nAgbCPUReg[rn+8], g_nAgbCPUReg[rm+8], value)
					}
					break;
			}
		}
		break;
	case 0x46:
		{
			switch((opcode >> 6) & 3)
			{
				case 0x00:
					{
						//MOV Rd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = g_nAgbCPUReg[rm];
					}
					break;
				case 0x01:
					{
						//MOV Rd, Hm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd] = g_nAgbCPUReg[rm + 8];
					}
					break;
				case 0x02:
					{
						//MOV Hd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd + 8] = g_nAgbCPUReg[rm];	
						THUMB_PC_WRITE
					}
					break;
				case 0x03:
					{
						//MOV Hd, Rm
						THUMB_RD_RM_DEFINE
						g_nAgbCPUReg[rd + 8] = g_nAgbCPUReg[rm + 8];
						THUMB_PC_WRITE
					}
					break;
			}
		}
		break;
	case 0x47:
		{
			switch((opcode >> 6) & 3)
			{
				case 0x00:
					{
						//BX Rm
						THUMB_RM_DEFINE
						g_nAgbCPUReg[15] = g_nAgbCPUReg[rm]&0xfffffffe;
						if(g_nAgbCPUReg[rm]&0x1)
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
						g_nAgbCPUReg[15] = g_nAgbCPUReg[rm + 8]&0xfffffffe;
						if(g_nAgbCPUReg[rm + 8]&0x1)
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
		break;
	CASE_8(0x48)
		{
			// LDR Rd, [PC, #imm8*4]
			THUMB_RD_IMM8
			g_nAgbCPUReg[rd] = agbMemRead32((g_nAgbCPUReg[15]&0xfffffffc) + (imm8<<2));
		}
		break;
	case 0x50:
	case 0x51:
		{
			// STR Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			agbMemWrite32(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm], g_nAgbCPUReg[rd]);
		}
		break;
	case 0x52:
	case 0x53:
		{
			// STRH Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			agbMemWrite16(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm], g_nAgbCPUReg[rd]&0xffff);
		}
		break;
	case 0x54:
	case 0x55:
		{
			// STRB Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			agbMemWrite16(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm], g_nAgbCPUReg[rd]&0xff);
		}
		break;
	case 0x56:
	case 0x57:
		{
			// LDRSB Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			g_nAgbCPUReg[rd] = (s8)agbMemRead8(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm]);
		}
		break;
	case 0x58:
	case 0x59:
		{
			// LDR Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			g_nAgbCPUReg[rd] = agbMemRead32(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm]);
		}
		break;
	case 0x5a:
	case 0x5b:
		{
			// LDRH Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			g_nAgbCPUReg[rd] = agbMemRead16(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm]);
		}
		break;
	case 0x5c:
	case 0x5d:
		{
			// LDRB Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			g_nAgbCPUReg[rd] = agbMemRead8(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm]);
		}
		break;
	case 0x5e:
	case 0x5f:
		{
			// LDRSH Rd, [Rn, Rm]
			THUMB_RD_RN_RM_DEFINE
			g_nAgbCPUReg[rd] = (s16)agbMemRead16(g_nAgbCPUReg[rn] + g_nAgbCPUReg[rm]);
		}
		break;
	CASE_8(0x60)
		{
			// STR Rd, [Rn, IMM5*4]
			THUMB_RD_RN_IMM5_DEFINE
			agbMemWrite32(g_nAgbCPUReg[rn] + (imm5<<2), g_nAgbCPUReg[rd]);
		}
		break;
	CASE_8(0x68)
		{
			// LDR Rd, [Rn, IMM5*4]
			THUMB_RD_RN_IMM5_DEFINE
			g_nAgbCPUReg[rd] = agbMemRead32( g_nAgbCPUReg[rn] + (imm5<<2));
		}
		break;
	CASE_8(0x70)
		{
			// STRB Rd, [Rn, IMM5]
			THUMB_RD_RN_IMM5_DEFINE
			agbMemWrite8(g_nAgbCPUReg[rn] + (imm5), g_nAgbCPUReg[rd]);
		}
		break;
	CASE_8(0x78)
		{
			// LDRB Rd, [Rn, IMM5]
			THUMB_RD_RN_IMM5_DEFINE
			g_nAgbCPUReg[rd] = agbMemRead8( g_nAgbCPUReg[rn] + (imm5));
		}
		break;
	CASE_8(0x80)
		{
			// STRH Rd, [Rn, IMM5*2]
			THUMB_RD_RN_IMM5_DEFINE
			agbMemWrite16(g_nAgbCPUReg[rn] + (imm5<<1), g_nAgbCPUReg[rd]);
		}
		break;
	CASE_8(0x88)
		{
			// LDRH Rd, [Rn, IMM5*2]
			THUMB_RD_RN_IMM5_DEFINE
			g_nAgbCPUReg[rd] = agbMemRead16( g_nAgbCPUReg[rn] + (imm5<<1));
		}
		break;
	CASE_8(0x90)
		{
			// STR Rd, [SP, IMM8*4]
			THUMB_RD_IMM8
			agbMemWrite32(g_nAgbCPUReg[13] + (imm8<<2), g_nAgbCPUReg[rd]);
		}
		break;
	CASE_8(0x98)
		{
			// LDR Rd, SP, IMM8*4]
			THUMB_RD_IMM8
			g_nAgbCPUReg[rd] = agbMemRead32( g_nAgbCPUReg[13] + (imm8<<2));
		}
		break;
	CASE_8(0xa0)
		{
			// ADD Rd, PC, IMM8
			THUMB_RD_IMM8
			g_nAgbCPUReg[rd] = (g_nAgbCPUReg[15]&0xfffffffc) + (imm8<<2);
		}
		break;
	CASE_8(0xa8)
		{
			// ADD Rd, SP, IMM8
			THUMB_RD_IMM8
			g_nAgbCPUReg[rd] = (g_nAgbCPUReg[13]) + (imm8<<2);
		}
		break;
	case 0xb0:
		{
			// ADD SP, Imm7*4
			s32 imm7 = (opcode&0x7f)<<2;
			if(opcode &0x80)
				imm7 = - imm7;
			g_nAgbCPUReg[13] += (imm7);
		}
		break;
	case 0xb4:
		{
			//PUSH {Rlist}
			u32 temp =g_nAgbCPUReg[13] - g_nAgbCpuBitsSet[opcode &0xff]*4;
			u32 address = temp &0xfffffffc;
			THUMB_PUSH_REG(0x1, 0);
			THUMB_PUSH_REG(0x2, 1);
			THUMB_PUSH_REG(0x4, 2);
			THUMB_PUSH_REG(0x8, 3);
			THUMB_PUSH_REG(0x10, 4);
			THUMB_PUSH_REG(0x20, 5);
			THUMB_PUSH_REG(0x40, 6);
			THUMB_PUSH_REG(0x80, 7);
			g_nAgbCPUReg[13] = temp;
		}
		break;
	case 0xb5:
		{
			//PUSH {Rlist, LR}
			u32 temp =g_nAgbCPUReg[13] - g_nAgbCpuBitsSet[opcode &0xff]*4 -4;
			u32 address = temp & 0xfffffffc;
			THUMB_PUSH_REG(0x1, 0);
			THUMB_PUSH_REG(0x2, 1);
			THUMB_PUSH_REG(0x4, 2);
			THUMB_PUSH_REG(0x8, 3);
			THUMB_PUSH_REG(0x10, 4);
			THUMB_PUSH_REG(0x20, 5);
			THUMB_PUSH_REG(0x40, 6);
			THUMB_PUSH_REG(0x80, 7);
			THUMB_PUSH_REG(0x100, 14);
			g_nAgbCPUReg[13] = temp;
		}
		break;
	case 0xbc:
		{
			//POP {Rlist}
			u32 temp =g_nAgbCPUReg[13] + g_nAgbCpuBitsSet[opcode &0xff]*4;
			u32 address = g_nAgbCPUReg[13]&0xfffffffc;
			THUMB_POP_REG(0x1, 0);
			THUMB_POP_REG(0x2, 1);
			THUMB_POP_REG(0x4, 2);
			THUMB_POP_REG(0x8, 3);
			THUMB_POP_REG(0x10, 4);
			THUMB_POP_REG(0x20, 5);
			THUMB_POP_REG(0x40, 6);
			THUMB_POP_REG(0x80, 7);
			g_nAgbCPUReg[13] = temp;
		}
		break;
	case 0xbd:
		{
			//POP {Rlist, PC}
			u32 temp =g_nAgbCPUReg[13] + g_nAgbCpuBitsSet[opcode &0xff]*4 + 4;
			u32 address = g_nAgbCPUReg[13]&0xfffffffc;
			THUMB_POP_REG(0x1, 0);
			THUMB_POP_REG(0x2, 1);
			THUMB_POP_REG(0x4, 2);
			THUMB_POP_REG(0x8, 3);
			THUMB_POP_REG(0x10, 4);
			THUMB_POP_REG(0x20, 5);
			THUMB_POP_REG(0x40, 6);
			THUMB_POP_REG(0x80, 7);
			g_nAgbCPUReg[15] = agbMemRead32(address)&0xFFFFFFFE;
			THUMB_FIRST_PREFETCH
			g_nAgbCPUReg[13] = temp;
		}
		break;
	CASE_8(0xc0)
		{
			// STMIA Rn, {Rlist}
			u32 rn =(opcode>>8)&7;
			u32 address = g_nAgbCPUReg[rn] & 0xfffffffc;
			u32 temp = g_nAgbCPUReg[rn] + 4*g_nAgbCpuBitsSet[opcode &0xff];
			s32 offset = 0;
			THUMB_STM_REG(0x1, 0, rn);
			THUMB_STM_REG(0x2, 1, rn);
			THUMB_STM_REG(0x4, 2, rn);
			THUMB_STM_REG(0x8, 3, rn);
			THUMB_STM_REG(0x10, 4, rn);
			THUMB_STM_REG(0x20, 5, rn);
			THUMB_STM_REG(0x40, 6, rn);
			THUMB_STM_REG(0x80, 7, rn);
		}
		break;
	CASE_8(0xc8)
		{
			// LDMIA Rn, {Rlist}
			u32 rn =(opcode>>8)&7;
			u32 address = g_nAgbCPUReg[rn] & 0xfffffffc;
			u32 temp = g_nAgbCPUReg[rn] + 4*g_nAgbCpuBitsSet[opcode &0xff];
			THUMB_LDM_REG(0x1, 0);
			THUMB_LDM_REG(0x2, 1);
			THUMB_LDM_REG(0x4, 2);
			THUMB_LDM_REG(0x8, 3);
			THUMB_LDM_REG(0x10, 4);
			THUMB_LDM_REG(0x20, 5);
			THUMB_LDM_REG(0x40, 6);
			THUMB_LDM_REG(0x80, 7);
			if(!(opcode &(1<<rn)))
				g_nAgbCPUReg[rn] = temp;
		}
		break;
	case 0xd0:
		{
			//BEQ SImm8
			if(g_nAgbCPUReg[REG_ZFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd1:
		{
			//BNE SImm8
			if(g_nAgbCPUReg[REG_ZFLAG] == 0)
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd2:
		{
			//BCS SImm8
			if(g_nAgbCPUReg[REG_CFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd3:
		{
			//BCC SImm8
			if(g_nAgbCPUReg[REG_CFLAG] == 0)
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd4:
		{
			//BMI SImm8
			if(g_nAgbCPUReg[REG_NFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd5:
		{
			//BPL SImm8
			if(g_nAgbCPUReg[REG_NFLAG] == 0)
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd6:
		{
			//BVS SImm8
			if(g_nAgbCPUReg[REG_VFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd7:
		{
			//BVC SImm8
			if(g_nAgbCPUReg[REG_VFLAG] == 0)
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd8:
		{
			//BHI SImm8
			if(g_nAgbCPUReg[REG_CFLAG] && g_nAgbCPUReg[REG_ZFLAG] == 0)
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xd9:
		{
			//BLS SImm8
			if(g_nAgbCPUReg[REG_CFLAG] == 0  || g_nAgbCPUReg[REG_ZFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xda:
		{
			//BGE SImm8
			if(g_nAgbCPUReg[REG_NFLAG] == g_nAgbCPUReg[REG_VFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xdb:
		{
			//BLT SImm8
			if(g_nAgbCPUReg[REG_NFLAG] != g_nAgbCPUReg[REG_VFLAG])
			{
				THUMB_BCOND_SIMM8	
			}
		}
		break;
	case 0xdc:
		{
			//BGT SImm8
			if(g_nAgbCPUReg[REG_ZFLAG] == 0 && (g_nAgbCPUReg[REG_NFLAG] == g_nAgbCPUReg[REG_VFLAG]))
			{
				THUMB_BCOND_SIMM8
			}
		}
		break;
	case 0xdd:
		{
			//BLE SImm8
			if(g_nAgbCPUReg[REG_ZFLAG]  || (g_nAgbCPUReg[REG_NFLAG] != g_nAgbCPUReg[REG_VFLAG]))
			{
				THUMB_BCOND_SIMM8
			}
		}
		break;
	case 0xdf:
		{
			// SWI
			agbCPUSWI(opcode &0xff);
		}
		break;
	CASE_8(0xe0)
		{
			//B Imm11
			s32 offset = (s32)(opcode & 0x3ff)<<1;
			if(opcode &0x0400)
				offset |= 0xfffff800;
			g_nAgbCPUReg[15] += offset;
			THUMB_FIRST_PREFETCH
		}
		break;
	case 0xf0:
	case 0xf1:
	case 0xf2:
	case 0xf3:
		{
			// BLL #offset
			s32 offset = (opcode & 0x7ff);
			g_nAgbCPUReg[14] = g_nAgbCPUReg[15] + (offset << 12);
		}
   		break;      
	case 0xf4:
	case 0xf5:
	case 0xf6:
	case 0xf7:
		{
			// BLL #offset
			s32 offset = (opcode & 0x7ff);
			g_nAgbCPUReg[14] = g_nAgbCPUReg[15] + ((offset << 12) | 0xff800000);
		}
		break;
	CASE_8(0xf8)
		{
			// BLH
			s32 offset = (opcode &0x7ff);
			u32 temp = g_nAgbCPUReg[15] -2;
			g_nAgbCPUReg[15] = (g_nAgbCPUReg[14] + (offset<<1))&0xfffffffe;
			g_nAgbCPUReg[14]= temp|1;
			THUMB_FIRST_PREFETCH
		}
		break;
	default:
		{
			//unknown thumb
			TRL_ERROR("unknown thumb instruction");
		}
		break;
}


		
