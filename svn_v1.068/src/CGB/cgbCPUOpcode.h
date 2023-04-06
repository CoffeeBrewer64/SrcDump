/**
 * @file cgbCPUOpcode.h
 * @author Chentian
 * @date 2009.01.07
 * @brief CGB Emulate For CTR - CPU Opcode
 */

++PC;
u8 nOpcode = *g_pCgbCpuPC++;
LB_CGB_CPU_OPCODE:
switch(nOpcode)
{
// CPU Opcode - 00: NOP				[----]
case 0x00:
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 01: LD BC, NNNN		[----]
case 0x01:
	BC = *((u16*)g_pCgbCpuPC);
	PC += 2;
	g_pCgbCpuPC += 2;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 02: LD (BC), A		[----]
case 0x02:
	cgbMemWrite8(BC, A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 03: INC BC			[----]
case 0x03:
	++BC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 04: INC B			[Z0H-]
case 0x04:
	++B; 
	F = Z_FLAG_CHECK(B) | H_FLAG_INC(B) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 05: DEC B			[Z1H-]
case 0x05:
	--B;
	F = Z_FLAG_CHECK(B) | N_FLAG | H_FLAG_DEC(B) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 06: LD B, NN		[----]
case 0x06:
	B = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 07: RLCA			[000C]
case 0x07:
	F = (A & 0x80) ? C_FLAG : 0;
	A = (A<<1) | (A>>7);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 08: LD (NNNN), SP	[----]
case 0x08:
	cgbMemWrite16(*((u16*)g_pCgbCpuPC),SP);
	PC += 2;
	g_pCgbCpuPC += 2;
	g_nCgbCpuTicks += 5;
	break;
// CPU Opcode - 09: ADD HL, BC		[-0HC]
case 0x09:
	g_nCgbCpuTemp16 = HL + BC;
	F = (F & Z_FLAG) | ((HL^BC^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (((u32)HL+(u32)BC)&0x10000? C_FLAG : 0);
	HL = g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 0A: LD A, (BC)		[----]
case 0x0A:
	A = cgbMemRead8(BC);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 0B: DEC BC			[----]
case 0x0B:
	--BC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 0C: INC C			[Z0H-]
case 0x0C:
	++C;
	F = Z_FLAG_CHECK(C) | H_FLAG_INC(C) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 0D: DEC C			[Z1H-]
case 0x0D:
	--C;
	F = Z_FLAG_CHECK(C) | N_FLAG | H_FLAG_DEC(C) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 0E: LD C, NN		[----]
case 0x0E:
	C = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 0F: RRCA			[000C]
case 0x0F:
	F = (A & 0x01) ? C_FLAG : 0;
	A = (A>>1) | (A<<7);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 10: STOP			[----]
case 0x10:
	++PC;
	*g_pCgbCpuPC++;
	g_nCgbCpuTicks += 1;
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
		cgbCpuSpeed();
	//g_nCgbCpuState |= CGB_CPU_STOP;
	break;
// CPU Opcode - 11: LD DE, NNNN		[----]
case 0x11:
	DE = *((u16*)g_pCgbCpuPC);
	PC += 2;
	g_pCgbCpuPC += 2;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 12: LD (DE), A		[----]
case 0x12:
	cgbMemWrite8(DE, A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 13: INC DE			[----]
case 0x13:
	++DE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 14: INC D			[Z0H-]
case 0x14:
	++D;
	F = Z_FLAG_CHECK(D) | H_FLAG_INC(D) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 15: DEC D			[Z1H-]
case 0x15:
	--D;
	F = Z_FLAG_CHECK(D) | N_FLAG | H_FLAG_DEC(D) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 16: LD D, NN		[----]
case 0x16:
	D = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 17: RLA				[000C]
case 0x17:
	g_nCgbCpuTemp8 = A&0x80 ? C_FLAG : 0;
	A = (A<<1) | ((F & C_FLAG)>>4);
	F = g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 18: JR NN			[----]
case 0x18:
	PC += (s8)*g_pCgbCpuPC + 1;
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 19: ADD HL, DE		[-0HC]
case 0x19:
	g_nCgbCpuTemp16 = HL + DE;
	F = (F & Z_FLAG) | ((HL^DE^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (((u32)HL+(u32)DE)&0x10000 ? C_FLAG : 0);
	HL = g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 1A: LD A, (DE)		[----]
case 0x1A:
	A = cgbMemRead8(DE);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 1B: DEC DE			[----]
case 0x1B:
	--DE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 1C: INC E			[Z0H-]
case 0x1C:
	++E;
	F = Z_FLAG_CHECK(E) | H_FLAG_INC(E) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 1D: DEC E			[Z1H-]
case 0x1D:
	--E;
	F = Z_FLAG_CHECK(E) | N_FLAG | H_FLAG_DEC(E) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 1E: LD E, NN		[----]
case 0x1E:
	E = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 1F: RRA				[000C]
case 0x1F:
	g_nCgbCpuTemp8 = A&0x01;
	A = (A>>1) | ((F & C_FLAG)<<3);
	F = g_nCgbCpuTemp8<<4;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 20: JR NZ, NN		[----]
case 0x20:
	if(F & Z_FLAG)
	{
		++PC;
		++g_pCgbCpuPC;
		g_nCgbCpuTicks += 2;
	}
	else
	{
		PC += (s8)*g_pCgbCpuPC + 1;
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 3;
	}
	break;
// CPU Opcode - 21: LD HL, NNNN		[----]
case 0x21:
	HL = *((u16*)g_pCgbCpuPC);
	PC += 2;
	g_pCgbCpuPC += 2;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 22: LDI (HL), A		[----]
case 0x22:
	cgbMemWrite8(HL++, A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 23: INC HL			[----]
case 0x23:
	++HL;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 24: INC H			[Z0H-]
case 0x24:
	++H;
	F = Z_FLAG_CHECK(H) | H_FLAG_INC(H) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 25: DEC H			[Z1H-]
case 0x25:
	--H;
	F = Z_FLAG_CHECK(H) | N_FLAG | H_FLAG_DEC(H) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 26: LD H, NN		[----]
case 0x26:
	H = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 27: DAA				[Z-0X]
case 0x27:
	g_nCgbCpuTemp16 = A;
	if(F & C_FLAG)
		g_nCgbCpuTemp16 |= 0x0100;
	if(F & H_FLAG)
		g_nCgbCpuTemp16 |= 0x0200;
	if(F & N_FLAG)
		g_nCgbCpuTemp16 |= 0x0400;
	AF = g_nCgbDAATable[g_nCgbCpuTemp16];
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 28: JR Z, NN		[----]
case 0x28:
	if(F & Z_FLAG)
	{
		PC += (s8)*g_pCgbCpuPC + 1;
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 3;
	}
	else
	{
		++PC;
		++g_pCgbCpuPC;
		g_nCgbCpuTicks += 2;
	}
	break;
// CPU Opcode - 29: ADD HL, HL		[-0HC]
case 0x29:
	g_nCgbCpuTemp16 = HL + HL;
	F = (F & Z_FLAG) | (g_nCgbCpuTemp16&0x1000 ? H_FLAG : 0) | (((u32)HL+(u32)HL)&0x10000 ? C_FLAG : 0);
	HL = g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 2A: LDI A, (HL)		[----]
case 0x2A:
	A = cgbMemRead8(HL++);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 2B: DEC HL			[----]
case 0x2B:
	--HL;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 2C: INC L			[Z0H-]
case 0x2C:
	++L;
	F = Z_FLAG_CHECK(L) | H_FLAG_INC(L) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 2D: DEC L			[Z1H-]
case 0x2D:
	--L;
	F = Z_FLAG_CHECK(L) | N_FLAG | H_FLAG_DEC(L) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 2E: LD L, NN		[----]
case 0x2E:
	L = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 2F: CPL				[-11-]
case 0x2F:
	A ^= 0xFF;
	F |= N_FLAG | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 30: JR NC, NN		[----]
case 0x30:
	if(F & C_FLAG)
	{
		++PC;
		++g_pCgbCpuPC;
		g_nCgbCpuTicks += 2;
	}
	else
	{
		PC += (s8)*g_pCgbCpuPC + 1;
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 3;
	}
	break;
// CPU Opcode - 31: LD SP, NNNN		[----]
case 0x31:
	SP = *((u16*)g_pCgbCpuPC);
	g_pCgbCpuPC += 2;
	PC += 2;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 32: LDD (HL), A		[----]
case 0x32:
	cgbMemWrite8(HL--, A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 33: INC SP			[----]
case 0x33:
	++SP;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 34: INC (HL)		[Z0H-]
case 0x34:
	g_nCgbCpuTemp8 = cgbMemRead8(HL) + 1;
	F = Z_FLAG_CHECK(g_nCgbCpuTemp8) | H_FLAG_INC(g_nCgbCpuTemp8) | (F & C_FLAG);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 35: DEC (HL)		[Z1H-]
case 0x35:
	g_nCgbCpuTemp8 = cgbMemRead8(HL) - 1;
	F = Z_FLAG_CHECK(g_nCgbCpuTemp8) | N_FLAG | H_FLAG_DEC(g_nCgbCpuTemp8) | (F & C_FLAG);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 36: LD (HL), NN		[----]
case 0x36:
	cgbMemWrite8(HL, *g_pCgbCpuPC++);
	++PC;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - 37: SCF				[-001]
case 0x37:
	F = (F & Z_FLAG) | C_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 38: JR C, NN		[----]
case 0x38:
	if(F & C_FLAG)
	{
		PC += (s8)*g_pCgbCpuPC + 1;
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 3;
	}
	else
	{
		++PC;
		++g_pCgbCpuPC;
		g_nCgbCpuTicks += 2;
	}
	break;
// CPU Opcode - 39: ADD HL, SP		[-0HC]
case 0x39:
	g_nCgbCpuTemp16 = HL + SP;
	F = (F & Z_FLAG) | ((HL^SP^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (((u32)HL+(u32)SP)&0x10000 ? C_FLAG : 0);
	HL = g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 3A: LDD A, (HL)		[----]
case 0x3A:
	A = cgbMemRead8(HL--);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 3B: DEC SP			[----]
case 0x3B:
	--SP;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 3C: INC A			[Z0H-]
case 0x3C:
	++A;
	F = Z_FLAG_CHECK(A) | H_FLAG_INC(A) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 3D: DEC A			[Z1H-]
case 0x3D:
	--A;
	F = Z_FLAG_CHECK(A) | N_FLAG | H_FLAG_DEC(A) | (F & C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 3E: LD A, NN		[----]
case 0x3E:
	A = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 3F: CCF				[-00C]
case 0x3F:
	F = (F & Z_FLAG) | ((F & C_FLAG) ^ C_FLAG);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 40: LD B, B			[----]
case 0x40:
	//	B = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 41: LD B, C			[----]
case 0x41:
	B = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 42: LD B, D			[----]
case 0x42:
	B = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 43: LD B, E			[----]
case 0x43:
	B = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 44: LD B, H			[----]
case 0x44:
	B = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 45: LD B, L			[----]
case 0x45:
	B = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 46: LD B, (HL)		[----]
case 0x46:
	B = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 47: LD B, A			[----]
case 0x47:
	B = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 48: LD C, B			[----]
case 0x48:
	C = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 49: LD C, C			[----]
case 0x49:
	//	C = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 4A: LD C, D			[----]
case 0x4A:
	C = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 4B: LD C, E			[----]
case 0x4B:
	C = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 4C: LD C, H			[----]
case 0x4C:
	C = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 4D: LD C, L			[----]
case 0x4D:
	C = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 4E: LD C, (HL)		[----]
case 0x4E:
	C = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 4F: LD C, A			[----]
case 0x4F:
	C = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 50: LD D, B			[----]
case 0x50:
	D = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 51: LD D, C			[----]
case 0x51:
	D = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 52: LD D, D			[----]
case 0x52:
	//	D = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 53: LD D, E			[----]
case 0x53:
	D = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 54: LD D, H			[----]
case 0x54:
	D = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 55: LD D, L			[----]
case 0x55:
	D = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 56: LD D, (HL)		[----]
case 0x56:
	D = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 57: LD D, A			[----]
case 0x57:
	D = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 58: LD E, B			[----]
case 0x58:
	E = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 59: LD E, C			[----]
case 0x59:
	E = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 5A: LD E, D			[----]
case 0x5A:
	E = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 5B: LD E, E			[----]
case 0x5B:
	//	E = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 5C: LD E, H			[----]
case 0x5C:
	E = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 5D: LD E, L			[----]
case 0x5D:
	E = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 5E: LD E, (HL)		[----]
case 0x5E:
	E = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 5F: LD E, A			[----]
case 0x5F:
	E = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 60: LD H, B			[----]
case 0x60:
	H = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 61: LD H, C			[----]
case 0x61:
	H = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 62: LD H, D			[----]
case 0x62:
	H = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 63: LD H, E			[----]
case 0x63:
	H = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 64: LD H, H			[----]
case 0x64:
	//	H = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 65: LD H, L			[----]
case 0x65:
	H = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 66: LD H, (HL)		[----]
case 0x66:
	H = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 67: LD H, A			[----]
case 0x67:
	H = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 68: LD L, B			[----]
case 0x68:
	L = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 69: LD L, C			[----]
case 0x69:
	L = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 6A: LD L, D			[----]
case 0x6A:
	L = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 6B: LD L, E			[----]
case 0x6B:
	L = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 6C: LD L, H			[----]
case 0x6C:
	L = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 6D: LD L, L			[----]
case 0x6D:
	//	L = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 6E: LD L, (HL)		[----]
case 0x6E:
	L = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 6F: LD L, A			[----]
case 0x6F:
	L = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 70: LD (HL), B		[----]
case 0x70:
	cgbMemWrite8(HL, B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 71: LD (HL), C		[----]
case 0x71:
	cgbMemWrite8(HL, C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 72: LD (HL), D		[----]
case 0x72:
	cgbMemWrite8(HL, D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 73: LD (HL), E		[----]
case 0x73:
	cgbMemWrite8(HL, E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 74: LD (HL), H		[----]
case 0x74:
	cgbMemWrite8(HL, H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 75: LD (HL), L		[----]
case 0x75:
	cgbMemWrite8(HL, L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 76: HALT			[----]
case 0x76:
	if(g_nCgbCpuIME && g_pCgbREG[0xFF])
	{
		g_nCgbCpuState |= CGB_CPU_HALT;
		g_nCgbCpuTicks = g_nCgbCpuEventTicks;
	}
	else
		g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 77: LD (HL), A		[----]
case 0x77:
	cgbMemWrite8(HL, A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 78: LD A, B			[----]
case 0x78:
	A = B;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 79: LD A, C			[----]
case 0x79:
	A = C;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 7A: LD A, D			[----]
case 0x7A:
	A = D;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 7B: LD A, E			[----]
case 0x7B:
	A = E;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 7C: LD A, H			[----]
case 0x7C:
	A = H;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 7D: LD A, L			[----]
case 0x7D:
	A = L;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 7E: LD A, (HL)		[----]
case 0x7E:
	A = cgbMemRead8(HL);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 7F: LD A, A			[----]
case 0x7F:
	//	A = A;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 80: ADD B			[Z0HC]
case 0x80:
	g_nCgbCpuTemp16 = A + B;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(B) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 81: ADD C			[Z0HC]
case 0x81:
	g_nCgbCpuTemp16 = A + C;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(C) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 82: ADD D			[Z0HC]
case 0x82:
	g_nCgbCpuTemp16 = A + D;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(D) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 83: ADD E			[Z0HC]
case 0x83:
	g_nCgbCpuTemp16 = A + E;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(E) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 84: ADD H			[Z0HC]
case 0x84:
	g_nCgbCpuTemp16 = A + H;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(H) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 85: ADD L			[Z0HC]
case 0x85:
	g_nCgbCpuTemp16 = A + L;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(L) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 86: ADD (HL)		[Z0HC]
case 0x86:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = A + g_nCgbCpuTemp8;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 87: ADD A			[Z0HC]
case 0x87:
	g_nCgbCpuTemp16 = A + A;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(A) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 88: ADC B			[Z0HC]
case 0x88:
	g_nCgbCpuTemp16 = A + B + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(B) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 89: ADC C			[Z0HC]
case 0x89:
	g_nCgbCpuTemp16 = A + C + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(C) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 8A: ADC D			[Z0HC]
case 0x8A:
	g_nCgbCpuTemp16 = A + D + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(D) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 8B: ADC E			[Z0HC]
case 0x8B:
	g_nCgbCpuTemp16 = A + E + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(E) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 8C: ADC H			[Z0HC]
case 0x8C:
	g_nCgbCpuTemp16 = A + H + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(H) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 8D: ADC L			[Z0HC]
case 0x8D:
	g_nCgbCpuTemp16 = A + L + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(L) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 8E: ADC (HL)		[Z0HC]
case 0x8E:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = A + g_nCgbCpuTemp8 + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 8F: ADC A			[Z0HC]
case 0x8F:
	g_nCgbCpuTemp16 = A + A + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(A) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 90: SUB B			[Z1HC]
case 0x90:
	g_nCgbCpuTemp16 = A - B;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(B) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 91: SUB C			[Z1HC]
case 0x91:
	g_nCgbCpuTemp16 = A - C;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(C) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 92: SUB D			[Z1HC]
case 0x92:
	g_nCgbCpuTemp16 = A - D;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(D) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 93: SUB E			[Z1HC]
case 0x93:
	g_nCgbCpuTemp16 = A - E;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(E) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 94: SUB H			[Z1HC]
case 0x94:
	g_nCgbCpuTemp16 = A - H;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(H) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 95: SUB L			[Z1HC]
case 0x95:
	g_nCgbCpuTemp16 = A - L;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(L) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 96: SUB (HL)		[Z1HC]
case 0x96:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = A - g_nCgbCpuTemp8;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 97: SUB A			[Z1HC]
case 0x97:
	F = Z_FLAG | N_FLAG;
	A = 0;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 98: SBC B			[Z1HC]
case 0x98:
	g_nCgbCpuTemp16 = A - B - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(B) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 99: SBC C			[Z1HC]
case 0x99:
	g_nCgbCpuTemp16 = A - C - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(C) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 9A: SBC D			[Z1HC]
case 0x9A:
	g_nCgbCpuTemp16 = A - D - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(D) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 9B: SBC E			[Z1HC]
case 0x9B:
	g_nCgbCpuTemp16 = A - E - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(E) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 9C: SBC H			[Z1HC]
case 0x9C:
	g_nCgbCpuTemp16 = A - H - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(H) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 9D: SBC L			[Z1HC]
case 0x9D:
	g_nCgbCpuTemp16 = A - L - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(L) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - 9E: SBC (HL)		[Z1HC]
case 0x9E:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = A - g_nCgbCpuTemp8 - (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - 9F: SBC A			[Z1HC]
case 0x9F:
	g_nCgbCpuTemp16 = F&C_FLAG ? -1 : 0;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(A) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A0: AND B			[Z010]
case 0xA0:
	A &= B;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A1: AND C			[Z010]
case 0xA1:
	A &= C;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A2: AND D			[Z010]
case 0xA2:
	A &= D;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A3: AND E			[Z010]
case 0xA3:
	A &= E;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A4: AND H			[Z010]
case 0xA4:
	A &= H;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A5: AND L			[Z010]
case 0xA5:
	A &= L;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A6: AND (HL)		[Z010]
case 0xA6:
	A &= cgbMemRead8(HL);
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - A7: AND A			[Z010]
case 0xA7:
	//	A &= A;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A8: XOR B			[Z000]
case 0xA8:
	A ^= B;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - A9: XOR C			[Z000]
case 0xA9:
	A ^= C;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - AA: XOR D			[Z000]
case 0xAA:
	A ^= D;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - AB: XOR E			[Z000]
case 0xAB:
	A ^= E;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - AC: XOR H			[Z000]
case 0xAC:
	A ^= H;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - AD: XOR L			[Z000]
case 0xAD:
	A ^= L;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - AE: XOR (HL)		[Z000]
case 0xAE:
	A ^= cgbMemRead8(HL);
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - AF: XOR A			[Z000]
case 0xAF:
	A = 0;
	F = Z_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B0: OR B			[Z000]
case 0xB0:
	A |= B;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B1: OR C			[Z000]
case 0xB1:
	A |= C;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B2: OR D			[Z000]
case 0xB2:
	A |= D;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B3: OR E			[Z000]
case 0xB3:
	A |= E;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B4: OR H			[Z000]
case 0xB4:
	A |= H;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B5: OR L			[Z000]
case 0xB5:
	A |= L;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B6: OR (HL)			[Z000]
case 0xB6:
	A |= cgbMemRead8(HL);
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - B7: OR A			[Z000]
case 0xB7:
	//	A |= A;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B8: CP B			[Z1HC]
case 0xB8:
	g_nCgbCpuTemp16 = A - B;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(B) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - B9: CP C			[Z1HC]
case 0xB9:
	g_nCgbCpuTemp16 = A - C;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(C) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - BA: CP D			[Z1HC]
case 0xBA:
	g_nCgbCpuTemp16 = A - D;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(D) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - BB: CP E			[Z1HC]
case 0xBB:
	g_nCgbCpuTemp16 = A - E;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(E) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - BC: CP H			[Z1HC]
case 0xBC:
	g_nCgbCpuTemp16 = A - H;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(H) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - BD: CP L			[Z1HC]
case 0xBD:
	g_nCgbCpuTemp16 = A - L;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(L) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - BE: CP (HL)			[Z1HC]
case 0xBE:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = A - g_nCgbCpuTemp8;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - BF: CP A			[Z1HC]
case 0xBF:
	F = Z_FLAG | N_FLAG;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - C0: RET NZ			[----]
case 0xC0:
	if(!(F&Z_FLAG))
	{
		cgbCpuPopStack(PC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 5;
	}
	else
		g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - C1: POP BC			[----]
case 0xC1:
	cgbCpuPopStack(BC);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - C2: JP NZ, NNNN		[----]
case 0xC2:
	if(F&Z_FLAG)
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	else
	{
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 4;
	}
	break;
// CPU Opcode - C3: JP NNNN			[----]
case 0xC3:
	PC = *((u16*)g_pCgbCpuPC);
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - C4: CALL NZ, NNNN	[----]
case 0xC4:
	if(F&Z_FLAG)
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	else
	{
		cgbCpuPushStack(PC+2);
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 6;
	}
	break;
// CPU Opcode - C5: PUSH BC			[----]
case 0xC5:
	cgbCpuPushStack(BC);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - C6: ADD NN			[Z0HC]
case 0xC6:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = A + g_nCgbCpuTemp8;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - C7: RST 00			[----]
case 0xC7:
	cgbCpuPushStack(PC);
	PC = 0x0000;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - C8: RET Z			[----]
case 0xC8:
	if(F&Z_FLAG)
	{
		cgbCpuPopStack(PC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 5;
	}
	else
		g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - C9: RET				[----]
case 0xC9:
	cgbCpuPopStack(PC);
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CA: JP Z, NNNN		[----]
case 0xCA:
	if(F&Z_FLAG)
	{
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 4;
	}
	else
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	break;
// CPU Opcode - CB: CB Opcode
case 0xCB:
	#include "cgbCPUOpcodeCB.h"
//	cgbCpuOpcodeCB[*g_pCgbCpuPC++]();
	break;
// CPU Opcode - CC: CALL Z, NNNN	[----]
case 0xCC:
	if(F&Z_FLAG)
	{
		cgbCpuPushStack(PC+2);
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 6;
	}
	else
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	break;
// CPU Opcode - CD: CALL NNNN		[----]
case 0xCD:
	cgbCpuPushStack(PC+2);
	PC = *((u16*)g_pCgbCpuPC);
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
	g_nCgbCpuTicks += 6;
	break;
// CPU Opcode - CE: ADC NN			[Z0HC]
case 0xCE:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = A + g_nCgbCpuTemp8 + (F&C_FLAG ? 1 : 0);
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CF: RST 08			[----]
case 0xCF:
	cgbCpuPushStack(PC);
	PC = 0x0008;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - D0: RET NC			[----]
case 0xD0:
	if(!(F&C_FLAG))
	{
		cgbCpuPopStack(PC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 5;
	}
	else
		g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - D1: POP DE			[----]
case 0xD1:
	cgbCpuPopStack(DE);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - D2: JP NC, NNNN		[----]
case 0xD2:
	if(F&C_FLAG)
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	else
	{
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 4;
	}
	break;
// CPU Opcode - D3: Unused			[----]
case 0xD3:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - D4: CALL NC, NNNN	[----]
case 0xD4:
	if(F&C_FLAG)
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	else
	{
		cgbCpuPushStack(PC+2);
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 6;
	}
	break;
// CPU Opcode - D5: PUSH DE			[----]
case 0xD5:
	cgbCpuPushStack(DE);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - D6: SUB NN			[Z1HC]
case 0xD6:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = A - g_nCgbCpuTemp8;
	F= Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - D7: RST 10			[----]
case 0xD7:
	cgbCpuPushStack(PC);
	PC = 0x0010;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - D8: RET C			[----]
case 0xD8:
	if(F&C_FLAG)
	{
		cgbCpuPopStack(PC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 5;
	}
	else
		g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - D9: RETI			[----]
case 0xD9:
	cgbCpuPopStack(PC);
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
	g_nCgbCpuIME = 1;
	g_nCgbCpuTicks += 4;
	g_nCgbCpuEventTicks = g_nCgbCpuTicks;
	break;
// CPU Opcode - DA: JP C, NNNN		[----]
case 0xDA:
	if(F&C_FLAG)
	{
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 4;
	}
	else
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	break;
// CPU Opcode - DB: Unused			[----]
case 0xDB:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - DC: CALL C, NNNN	[----]
case 0xDC:
	if(F&C_FLAG)
	{
		cgbCpuPushStack(PC+2);
		PC = *((u16*)g_pCgbCpuPC);
		g_pCgbCpuPC = cgbMemReadOpcode(PC);
		g_nCgbCpuTicks += 6;
	}
	else
	{
		PC += 2;
		g_pCgbCpuPC += 2;
		g_nCgbCpuTicks += 3;
	}
	break;
// CPU Opcode - DD: Unused			[----]
case 0xDD:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - DE: SBC NN			[Z1HC]
case 0xDE:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = A - g_nCgbCpuTemp8 - (F&C_FLAG ? 1 : 0);
	F= Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	A = (u8)g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - DF: RST 18			[----]
case 0xDF:
	cgbCpuPushStack(PC);
	PC = 0x0018;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - E0: LD (FF00+NN), A	[----]
case 0xE0:
	cgbMemWrite8(0xFF00 + *g_pCgbCpuPC, A);
	++PC;
	++g_pCgbCpuPC;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - E1: POP HL			[----]
case 0xE1:
	cgbCpuPopStack(HL);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - E2: LD (FF00+C), A	[----]
case 0xE2:
	cgbMemWrite8(0xFF00 + C, A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - E3: Unused			[----]
case 0xE3:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - E4: Unused			[----]
case 0xE4:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - E5: PUSH HL			[----]
case 0xE5:
	cgbCpuPushStack(HL);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - E6: AND NN			[Z010]
case 0xE6:
	A &= *g_pCgbCpuPC++;
	++PC;
	F = Z_FLAG_CHECK(A) | H_FLAG;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - E7: RST 20			[----]
case 0xE7:
	cgbCpuPushStack(PC);
	PC = 0x0020;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - E8: ADD SP, NN		[00HC]
case 0xE8:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = SP + (s8)g_nCgbCpuTemp8;
	if(g_nCgbCpuTemp8 & 0x80)
		F = ((SP^g_nCgbCpuTemp8^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (SP<g_nCgbCpuTemp16 ? C_FLAG : 0);
	else
		F = ((SP^g_nCgbCpuTemp8^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (SP>g_nCgbCpuTemp16 ? C_FLAG : 0);
	SP = g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - E9: LD PC, HL		[----]
case 0xE9:
	PC = HL;
	g_pCgbCpuPC = cgbMemReadOpcode(PC);
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - EA: LD (NNNN), A	[----]
case 0xEA:
	cgbMemWrite8(*((u16*)g_pCgbCpuPC), A);
	PC += 2;
	g_pCgbCpuPC += 2;
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - EB: Unused			[----]
case 0xEB:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - EC: Unused			[----]
case 0xEC:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - ED: Unused			[----]
case 0xED:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - EE: XOR NN			[Z000]
case 0xEE:
	A ^= *g_pCgbCpuPC++;
	++PC;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - EF: RST 28			[----]
case 0xEF:
	cgbCpuPushStack(PC);
	PC = 0x0028;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - F0: LD A, (FF00+NN)	[----]
case 0xF0:
	A = cgbMemRead8(0xFF00 + *g_pCgbCpuPC);
	//if(*g_pCgbCpuPC == 0x41)
	//	g_nCgbCpuTicks = g_nCgbCpuEventTicks;
	//else
	//	g_nCgbCpuTicks += 3;
	++PC;
	++g_pCgbCpuPC;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - F1: POP AF			[----]
case 0xF1:
	cgbCpuPopStack(AF);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - F2: LD A, (FF00+C)	[----]
case 0xF2:
	A = cgbMemRead8(0xFF00 + C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - F3: DI				[----]
case 0xF3:
	g_nCgbCpuIME = 0;
	g_nCgbCpuTicks += 1;
	break;
// CPU Opcode - F4: Unused			[----]
case 0xF4:
//	g_nCgbCpuTicks += 0;
	break;
// CPU Opcode - F5: PUSH AF			[----]
case 0xF5:
	cgbCpuPushStack(AF);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - F6: OR NN			[Z000]
case 0xF6:
	A |= *g_pCgbCpuPC++;
	++PC;
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - F7: RST 30			[----]
case 0xF7:
	cgbCpuPushStack(PC);
	PC = 0x0030;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - F8: LD HL, SP+NN	[00HC]
case 0xF8:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = SP + (s8)g_nCgbCpuTemp8;
	if(g_nCgbCpuTemp8 & 0x80)
		F = ((SP^g_nCgbCpuTemp8^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (SP<g_nCgbCpuTemp16 ? C_FLAG : 0);
	else
		F = ((SP^g_nCgbCpuTemp8^g_nCgbCpuTemp16)&0x1000 ? H_FLAG : 0) | (SP>g_nCgbCpuTemp16 ? C_FLAG : 0);
	HL = g_nCgbCpuTemp16;
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - F9: LD SP, HL		[----]
case 0xF9:
	SP = HL;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - FA: LD A, (NNNN)	[----]
case 0xFA:
	A = cgbMemRead8(*((u16*)g_pCgbCpuPC));
	PC += 2;
	g_pCgbCpuPC += 2;
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - FB: EI				[----]
case 0xFB:
	g_nCgbCpuIME = 1;
	g_nCgbCpuTicks += 1;
	g_nCgbCpuEventTicks = g_nCgbCpuTicks;
	break;
// CPU Opcode - FC: Patch			[----]
case 0xFC:
	{
		
		u32 nAddress = g_pCgbCpuPC - (u8*)g_pCgbEmuBuf->pRomBuf - 1;
		trlSEmuShellPatch* pPatch = g_pCgbEmuBuf->pPatchData;
		for(u32 nID = 0; nID < g_pCgbEmuBuf->nPatchCount; ++nID, ++pPatch)
		{
			if(pPatch->sData.sA.nAddress == nAddress)
			{
				if(pPatch->sData.sA.nMode == 2) // Fixvalue
				{
					switch(pPatch->sData.sA.nType)
					{
					case 0:	// ZeldaYumeDX: Sound Delay Begin
						switch(g_pCgbEmuBuf->bFrameDelayEnable)
						{
						case 0:
							g_pCgbEmuBuf->bFrameDelayEnable = 1;
							g_pCgbEmuBuf->nFrameMark = g_pCgbEmuBuf->nFrames;
							g_pCgbEmuBuf->nFrameDelay = pPatch->sData.sA.nFixcode;
							break;
						case 1:
							g_pCgbEmuBuf->nFrameDelay += pPatch->sData.sA.nFixcode;
							break;
						}
						break;
					case 1:	// ZeldaYumeDX: Sound Delay End
						if(g_pCgbEmuBuf->bFrameDelayEnable == 1)
						{
							g_pCgbEmuBuf->bFrameDelayEnable = 2;
							g_pCgbEmuBuf->nFrameDelay -= g_pCgbEmuBuf->nFrames - g_pCgbEmuBuf->nFrameMark;
							if(g_pCgbEmuBuf->nFrameDelay <= 0)
								g_pCgbEmuBuf->bFrameDelayEnable = 0;
						}
						break;
					case 2: // Sweep Limit
						g_nCgbSnd1SweepLimit = pPatch->sData.sA.nFixcode;
						break;
					}
				}
				else if(pPatch->sData.sA.nMode == 6) // FixMemory rangelzhang
				{					
					for(int i=0;i<pPatch->sData.sA.nFixcode;i++)
						cgbMemWrite8(pPatch->sData.sA.nMemAddress + i, pPatch->pFixcode[i]);						
				}
				else
				{
					g_pCgbEmuBuf->sPatchActive[g_pCgbEmuBuf->nPatchActive].Clear();
					g_pCgbEmuBuf->sPatchActive[g_pCgbEmuBuf->nPatchActive].nIndex = nID;
					g_pCgbEmuBuf->sPatchActive[g_pCgbEmuBuf->nPatchActive].nMode = pPatch->sData.sA.nMode;
					g_pCgbEmuBuf->nPatchActive++;
				}
				NN_LOG("Patch %d 0x%x\n", nID, nAddress);
				nOpcode = (u8)pPatch->nOpcode;
				goto LB_CGB_CPU_OPCODE;
			}
		}
	}
	break;
// CPU Opcode - FD: Unused			[----]
case 0xFD:
	break;
// CPU Opcode - FE: CP NN			[Z1HC]
case 0xFE:
	g_nCgbCpuTemp8 = *g_pCgbCpuPC++;
	++PC;
	g_nCgbCpuTemp16 = A - g_nCgbCpuTemp8;
	F = Z_FLAG_CHECK((u8)g_nCgbCpuTemp16) | N_FLAG | H_FLAG_CHECK(g_nCgbCpuTemp8) | C_FLAG_CHECK;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - FF: RST 38			[----]
case 0xFF:
	cgbCpuPushStack(PC);
	PC = 0x0038;
	g_pCgbCpuPC = &g_pCgbROM[PC];
	g_nCgbCpuTicks += 4;
	break;
}
