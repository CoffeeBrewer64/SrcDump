/**
 * @file cgbCPUOpcodeCB.h
 * @author Chentian
 * @date 2009.01.07
 * @brief CGB Emulate For CTR - CPU Opcode - CB-prefixed instructions
 */

++PC;
switch(*g_pCgbCpuPC++)
{
// CPU Opcode - CB00: RLC B			[Z00C]
case 0x00:
	F = (B & 0x80) >> 3;
	B = (B<<1) | (B>>7);
	F |= Z_FLAG_CHECK(B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB01: RLC C			[Z00C]
case 0x01:
	F = (C & 0x80) >> 3;
	C = (C<<1) | (C>>7);
	F |= Z_FLAG_CHECK(C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB02: RLC D			[Z00C]
case 0x02:
	F = (D & 0x80) >> 3;
	D = (D<<1) | (D>>7);
	F |= Z_FLAG_CHECK(D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB03: RLC E			[Z00C]
case 0x03:
	F = (E & 0x80) >> 3;
	E = (E<<1) | (E>>7);
	F |= Z_FLAG_CHECK(E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB04: RLC H			[Z00C]
case 0x04:
	F = (H & 0x80) >> 3;
	H = (H<<1) | (H>>7);
	F |= Z_FLAG_CHECK(H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB05: RLC L			[Z00C]
case 0x05:
	F = (L & 0x80) >> 3;
	L = (L<<1) | (L>>7);
	F |= Z_FLAG_CHECK(L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB06: RLC (HL)		[Z00C]
case 0x06:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	F = (g_nCgbCpuTemp8 & 0x80) >> 3;
	g_nCgbCpuTemp8 = (g_nCgbCpuTemp8<<1) | (g_nCgbCpuTemp8>>7);
	F |= Z_FLAG_CHECK(g_nCgbCpuTemp8);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB07: RLC A			[Z00C]
case 0x07:
	F = (A & 0x80) >> 3;
	A = (A<<1) | (A>>7);
	F |= Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB08: RRC B			[Z00C]
case 0x08:
	F = (B & 0x01) << 4;
	B = (B>>1) | (B<<7);
	F |= Z_FLAG_CHECK(B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB09: RRC C			[Z00C]
case 0x09:
	F = (C & 0x01) << 4;
	C = (C>>1) | (C<<7);
	F |= Z_FLAG_CHECK(C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB0A: RRC D			[Z00C]
case 0x0A:
	F = (D & 0x01) << 4;
	D = (D>>1) | (D<<7);
	F |= Z_FLAG_CHECK(D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB0B: RRC E			[Z00C]
case 0x0B:
	F = (E & 0x01) << 4;
	E = (E>>1) | (E<<7);
	F |= Z_FLAG_CHECK(E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB0C: RRC H			[Z00C]
case 0x0C:
	F = (H & 0x01) << 4;
	H = (H>>1) | (H<<7);
	F |= Z_FLAG_CHECK(H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB0D: RRC L			[Z00C]
case 0x0D:
	F = (L & 0x01) << 4;
	L = (L>>1) | (L<<7);
	F |= Z_FLAG_CHECK(L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB0E: RRC (HL)		[Z00C]
case 0x0E:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	F = (g_nCgbCpuTemp8 & 0x01) << 4;
	g_nCgbCpuTemp8 = (g_nCgbCpuTemp8>>1) | (g_nCgbCpuTemp8<<7);
	F |= Z_FLAG_CHECK(g_nCgbCpuTemp8);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB0F: RRC A			[Z00C]
case 0x0F:
	F = (A & 0x01) << 4;
	A = (A>>1) | (A<<7);
	F |= Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB10: RL B			[Z00C]
case 0x10:
	g_nCgbCpuTemp8 = (B & 0x80) >> 3;
	B = (B<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(B) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB11: RL C			[Z00C]
case 0x11:
	g_nCgbCpuTemp8 = (C & 0x80) >> 3;
	C = (C<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(C) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB12: RL D			[Z00C]
case 0x12:
	g_nCgbCpuTemp8 = (D & 0x80) >> 3;
	D = (D<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(D) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB13: RL E			[Z00C]
case 0x13:
	g_nCgbCpuTemp8 = (E & 0x80) >> 3;
	E = (E<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(E) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB14: RL H			[Z00C]
case 0x14:
	g_nCgbCpuTemp8 = (H & 0x80) >> 3;
	H = (H<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(H) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB15: RL L			[Z00C]
case 0x15:
	g_nCgbCpuTemp8 = (L & 0x80) >> 3;
	L = (L<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(L) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB16: RL (HL)		[Z00C]
case 0x16:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = (g_nCgbCpuTemp8 & 0x80) >> 3;
	g_nCgbCpuTemp8 = (g_nCgbCpuTemp8<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(g_nCgbCpuTemp8) | g_nCgbCpuTemp16;
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB17: RL A			[Z00C]
case 0x17:
	g_nCgbCpuTemp8 = (A & 0x80) >> 3;
	A = (A<<1) | ((F & C_FLAG) >> 4);
	F = Z_FLAG_CHECK(A) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB18: RR B			[Z00C]
case 0x18:
	g_nCgbCpuTemp8 = (B & 0x01) << 4;
	B = (B>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(B) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB19: RR C			[Z00C]
case 0x19:
	g_nCgbCpuTemp8 = (C & 0x01) << 4;
	C = (C>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(C) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB1A: RR D			[Z00C]
case 0x1A:
	g_nCgbCpuTemp8 = (D & 0x01) << 4;
	D = (D>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(D) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB1B: RR E			[Z00C]
case 0x1B:
	g_nCgbCpuTemp8 = (E & 0x01) << 4;
	E = (E>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(E) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB1C: RR H			[Z00C]
case 0x1C:
	g_nCgbCpuTemp8 = (H & 0x01) << 4;
	H = (H>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(H) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB1D: RR L			[Z00C]
case 0x1D:
	g_nCgbCpuTemp8 = (L & 0x01) << 4;
	L = (L>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(L) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB1E: RR (HL)		[Z00C]
case 0x1E:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp16 = (g_nCgbCpuTemp8 & 0x01) << 4;
	g_nCgbCpuTemp8 = (g_nCgbCpuTemp8>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(g_nCgbCpuTemp8) | g_nCgbCpuTemp16;
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB1F: RR A			[Z00C]
case 0x1F:
	g_nCgbCpuTemp8 = (A & 0x01) << 4;
	A = (A>>1) | ((F & C_FLAG) << 3);
	F = Z_FLAG_CHECK(A) | g_nCgbCpuTemp8;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB20: SLA B			[Z00C]
case 0x20:
	F = (B & 0x80) >> 3;
	B <<= 1;
	F |= Z_FLAG_CHECK(B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB21: SLA C			[Z00C]
case 0x21:
	F = (C & 0x80) >> 3;
	C <<= 1;
	F |= Z_FLAG_CHECK(C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB22: SLA D			[Z00C]
case 0x22:
	F = (D & 0x80) >> 3;
	D <<= 1;
	F |= Z_FLAG_CHECK(D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB23: SLA E			[Z00C]
case 0x23:
	F = (E & 0x80) >> 3;
	E <<= 1;
	F |= Z_FLAG_CHECK(E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB24: SLA H			[Z00C]
case 0x24:
	F = (H & 0x80) >> 3;
	H <<= 1;
	F |= Z_FLAG_CHECK(H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB25: SLA L			[Z00C]
case 0x25:
	F = (L & 0x80) >> 3;
	L <<= 1;
	F |= Z_FLAG_CHECK(L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB26: SLA (HL)		[Z00C]
case 0x26:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	F = (g_nCgbCpuTemp8 & 0x80) >> 3;
	g_nCgbCpuTemp8 <<= 1;
	F |= Z_FLAG_CHECK(g_nCgbCpuTemp8);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB27: SLA A			[Z00C]
case 0x27:
	F = (A & 0x80) >> 3;
	A <<= 1;
	F |= Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB28: SRA B			[Z00C]
case 0x28:
	F = (B & 0x01) << 4;
	B = (B >> 1) | (B & 0x80);
	F |= Z_FLAG_CHECK(B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB29: SRA C			[Z00C]
case 0x29:
	F = (C & 0x01) << 4;
	C = (C >> 1) | (C & 0x80);
	F |= Z_FLAG_CHECK(C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB2A: SRA D			[Z00C]
case 0x2A:
	F = (D & 0x01) << 4;
	D = (D >> 1) | (D & 0x80);
	F |= Z_FLAG_CHECK(D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB2B: SRA E			[Z00C]
case 0x2B:
	F = (E & 0x01) << 4;
	E = (E >> 1) | (E & 0x80);
	F |= Z_FLAG_CHECK(E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB2C: SRA H			[Z00C]
case 0x2C:
	F = (H & 0x01) << 4;
	H = (H >> 1) | (H & 0x80);
	F |= Z_FLAG_CHECK(H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB2D: SRA L			[Z00C]
case 0x2D:
	F = (L & 0x01) << 4;
	L = (L >> 1) | (L & 0x80);
	F |= Z_FLAG_CHECK(L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB2E: SRA (HL)		[Z00C]
case 0x2E:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	F = (g_nCgbCpuTemp8 & 0x01) << 4;
	g_nCgbCpuTemp8 = (g_nCgbCpuTemp8 >> 1) | (g_nCgbCpuTemp8 & 0x80);
	F |= Z_FLAG_CHECK(g_nCgbCpuTemp8);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB2F: SRA A			[Z00C]
case 0x2F:
	F = (A & 0x01) << 4;
	A = (A >> 1) | (A & 0x80);
	F |= Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB30: SWAP B		[Z000]
case 0x30:
	B = (B >> 4) | (B << 4);
	F = Z_FLAG_CHECK(B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB31: SWAP C		[Z000]
case 0x31:
	C = (C >> 4) | (C << 4);
	F = Z_FLAG_CHECK(C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB32: SWAP D		[Z000]
case 0x32:
	D = (D >> 4) | (D << 4);
	F = Z_FLAG_CHECK(D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB33: SWAP E		[Z000]
case 0x33:
	E = (E >> 4) | (E << 4);
	F = Z_FLAG_CHECK(E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB34: SWAP H		[Z000]
case 0x34:
	H = (H >> 4) | (H << 4);
	F = Z_FLAG_CHECK(H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB35: SWAP L		[Z000]
case 0x35:
	L = (L >> 4) | (L << 4);
	F = Z_FLAG_CHECK(L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB36: SWAP (HL)		[Z000]
case 0x36:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	g_nCgbCpuTemp8 = (g_nCgbCpuTemp8 >> 4) | (g_nCgbCpuTemp8 << 4);
	F = Z_FLAG_CHECK(g_nCgbCpuTemp8);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB37: SWAP A		[Z000]
case 0x37:
	A = (A >> 4) | (A << 4);
	F = Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB38: SRL B			[Z00C]
case 0x38:
	F = (B & 0x01) << 4;
	B >>= 1;
	F |= Z_FLAG_CHECK(B);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB39: SRL C			[Z00C]
case 0x39:
	F = (C & 0x01) << 4;
	C >>= 1;
	F |= Z_FLAG_CHECK(C);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB3A: SRL D			[Z00C]
case 0x3A:
	F = (D & 0x01) << 4;
	D >>= 1;
	F |= Z_FLAG_CHECK(D);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB3B: SRL E			[Z00C]
case 0x3B:
	F = (E & 0x01) << 4;
	E >>= 1;
	F |= Z_FLAG_CHECK(E);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB3C: SRL H			[Z00C]
case 0x3C:
	F = (H & 0x01) << 4;
	H >>= 1;
	F |= Z_FLAG_CHECK(H);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB3D: SRL L			[Z00C]
case 0x3D:
	F = (L & 0x01) << 4;
	L >>= 1;
	F |= Z_FLAG_CHECK(L);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB3E: SRL (HL)		[Z00C]
case 0x3E:
	g_nCgbCpuTemp8 = cgbMemRead8(HL);
	F = (g_nCgbCpuTemp8 & 0x01) << 4;
	g_nCgbCpuTemp8 >>= 1;
	F |= Z_FLAG_CHECK(g_nCgbCpuTemp8);
	cgbMemWrite8(HL, g_nCgbCpuTemp8);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB3F: SRL A			[Z00C]
case 0x3F:
	F = (A & 0x01) << 4;
	A >>= 1;
	F |= Z_FLAG_CHECK(A);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB40: BIT 0, B		[Z01-]
case 0x40:
	F = (B & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB41: BIT 0, C		[Z01-]
case 0x41:
	F = (C & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB42: BIT 0, D		[Z01-]
case 0x42:
	F = (D & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB43: BIT 0, E		[Z01-]
case 0x43:
	F = (E & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB44: BIT 0, H		[Z01-]
case 0x44:
	F = (H & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB45: BIT 0, L		[Z01-]
case 0x45:
	F = (L & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB46: BIT 0, (HL)	[Z01-]
case 0x46:
	F = (cgbMemRead8(HL) & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB47: BIT 0, A		[Z01-]
case 0x47:
	F = (A & 0x01 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB48: BIT 1, B		[Z01-]
case 0x48:
	F = (B & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB49: BIT 1, C		[Z01-]
case 0x49:
	F = (C & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB4A: BIT 1, D		[Z01-]
case 0x4A:
	F = (D & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB4B: BIT 1, E		[Z01-]
case 0x4B:
	F = (E & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB4C: BIT 1, H		[Z01-]
case 0x4C:
	F = (H & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB4D: BIT 1, L		[Z01-]
case 0x4D:
	F = (L & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB4E: BIT 1, (HL)	[Z01-]
case 0x4E:
	F = (cgbMemRead8(HL) & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB4F: BIT 1, A		[Z01-]
case 0x4F:
	F = (A & 0x02 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB50: BIT 2, B		[Z01-]
case 0x50:
	F = (B & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB51: BIT 2, C		[Z01-]
case 0x51:
	F = (C & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB52: BIT 2, D		[Z01-]
case 0x52:
	F = (D & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB53: BIT 2, E		[Z01-]
case 0x53:
	F = (E & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB54: BIT 2, H		[Z01-]
case 0x54:
	F = (H & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB55: BIT 2, L		[Z01-]
case 0x55:
	F = (L & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB56: BIT 2, (HL)	[Z01-]
case 0x56:
	F = (cgbMemRead8(HL) & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB57: BIT 2, A		[Z01-]
case 0x57:
	F = (A & 0x04 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB58: BIT 3, B		[Z01-]
case 0x58:
	F = (B & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB59: BIT 3, C		[Z01-]
case 0x59:
	F = (C & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB5A: BIT 3, D		[Z01-]
case 0x5A:
	F = (D & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB5B: BIT 3, E		[Z01-]
case 0x5B:
	F = (E & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB5C: BIT 3, H		[Z01-]
case 0x5C:
	F = (H & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB5D: BIT 3, L		[Z01-]
case 0x5D:
	F = (L & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB5E: BIT 3, (HL)	[Z01-]
case 0x5E:
	F = (cgbMemRead8(HL) & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB5F: BIT 3, A		[Z01-]
case 0x5F:
	F = (A & 0x08 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB60: BIT 4, B		[Z01-]
case 0x60:
	F = (B & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB61: BIT 4, C		[Z01-]
case 0x61:
	F = (C & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB62: BIT 4, D		[Z01-]
case 0x62:
	F = (D & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB63: BIT 4, E		[Z01-]
case 0x63:
	F = (E & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB64: BIT 4, H		[Z01-]
case 0x64:
	F = (H & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB65: BIT 4, L		[Z01-]
case 0x65:
	F = (L & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB66: BIT 4, (HL)	[Z01-]
case 0x66:
	F = (cgbMemRead8(HL) & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB67: BIT 4, A		[Z01-]
case 0x67:
	F = (A & 0x10 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB68: BIT 5, B		[Z01-]
case 0x68:
	F = (B & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB69: BIT 5, C		[Z01-]
case 0x69:
	F = (C & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB6A: BIT 5, D		[Z01-]
case 0x6A:
	F = (D & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB6B: BIT 5, E		[Z01-]
case 0x6B:
	F = (E & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB6C: BIT 5, H		[Z01-]
case 0x6C:
	F = (H & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB6D: BIT 5, L		[Z01-]
case 0x6D:
	F = (L & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB6E: BIT 5, (HL)	[Z01-]
case 0x6E:
	F = (cgbMemRead8(HL) & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB6F: BIT 5, A		[Z01-]
case 0x6F:
	F = (A & 0x20 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB70: BIT 6, B		[Z01-]
case 0x70:
	F = (B & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB71: BIT 6, C		[Z01-]
case 0x71:
	F = (C & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB72: BIT 6, D		[Z01-]
case 0x72:
	F = (D & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB73: BIT 6, E		[Z01-]
case 0x73:
	F = (E & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB74: BIT 6, H		[Z01-]
case 0x74:
	F = (H & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB75: BIT 6, L		[Z01-]
case 0x75:
	F = (L & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB76: BIT 6, (HL)	[Z01-]
case 0x76:
	F = (cgbMemRead8(HL) & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB77: BIT 6, A		[Z01-]
case 0x77:
	F = (A & 0x40 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB78: BIT 7, B		[Z01-]
case 0x78:
	F = (B & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB79: BIT 7, C		[Z01-]
case 0x79:
	F = (C & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB7A: BIT 7, D		[Z01-]
case 0x7A:
	F = (D & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB7B: BIT 7, E		[Z01-]
case 0x7B:
	F = (E & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB7C: BIT 7, H		[Z01-]
case 0x7C:
	F = (H & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB7D: BIT 7, L		[Z01-]
case 0x7D:
	F = (L & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB7E: BIT 7, (HL)	[Z01-]
case 0x7E:
	F = (cgbMemRead8(HL) & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 3;
	break;
// CPU Opcode - CB7F: BIT 7, A		[Z01-]
case 0x7F:
	F = (A & 0x80 ? H_FLAG : (Z_FLAG|H_FLAG)) | (F & C_FLAG);
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB80: RES 0, B		[----]
case 0x80:
	B &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB81: RES 0, C		[----]
case 0x81:
	C &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB82: RES 0, D		[----]
case 0x82:
	D &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB83: RES 0, E		[----]
case 0x83:
	E &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB84: RES 0, H		[----]
case 0x84:
	H &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB85: RES 0, L		[----]
case 0x85:
	L &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB86: RES 0, (HL)	[----]
case 0x86:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xFE);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB87: RES 0, A		[----]
case 0x87:
	A &= 0xFE;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB88: RES 1, B		[----]
case 0x88:
	B &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB89: RES 1, C		[----]
case 0x89:
	C &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB8A: RES 1, D		[----]
case 0x8A:
	D &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB8B: RES 1, E		[----]
case 0x8B:
	E &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB8C: RES 1, H		[----]
case 0x8C:
	H &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB8D: RES 1, L		[----]
case 0x8D:
	L &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB8E: RES 1, (HL)	[----]
case 0x8E:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xFD);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB8F: RES 1, A		[----]
case 0x8F:
	A &= 0xFD;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB90: RES 2, B		[----]
case 0x90:
	B &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB91: RES 2, C		[----]
case 0x91:
	C &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB92: RES 2, D		[----]
case 0x92:
	D &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB93: RES 2, E		[----]
case 0x93:
	E &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB94: RES 2, H		[----]
case 0x94:
	H &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB95: RES 2, L		[----]
case 0x95:
	L &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB96: RES 2, (HL)	[----]
case 0x96:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xFB);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB97: RES 2, A		[----]
case 0x97:
	A &= 0xFB;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB98: RES 3, B		[----]
case 0x98:
	B &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB99: RES 3, C		[----]
case 0x99:
	C &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB9A: RES 3, D		[----]
case 0x9A:
	D &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB9B: RES 3, E		[----]
case 0x9B:
	E &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB9C: RES 3, H		[----]
case 0x9C:
	H &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB9D: RES 3, L		[----]
case 0x9D:
	L &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CB9E: RES 3, (HL)	[----]
case 0x9E:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xF7);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CB9F: RES 3, A		[----]
case 0x9F:
	A &= 0xF7;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA0: RES 4, B		[----]
case 0xA0:
	B &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA1: RES 4, C		[----]
case 0xA1:
	C &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA2: RES 4, D		[----]
case 0xA2:
	D &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA3: RES 4, E		[----]
case 0xA3:
	E &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA4: RES 4, H		[----]
case 0xA4:
	H &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA5: RES 4, L		[----]
case 0xA5:
	L &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA6: RES 4, (HL)	[----]
case 0xA6:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xEF);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBA7: RES 4, A		[----]
case 0xA7:
	A &= 0xEF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA8: RES 5, B		[----]
case 0xA8:
	B &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBA9: RES 5, C		[----]
case 0xA9:
	C &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBAA: RES 5, D		[----]
case 0xAA:
	D &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBAB: RES 5, E		[----]
case 0xAB:
	E &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBAC: RES 5, H		[----]
case 0xAC:
	H &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBAD: RES 5, L		[----]
case 0xAD:
	L &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBAE: RES 5, (HL)	[----]
case 0xAE:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xDF);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBAF: RES 5, A		[----]
case 0xAF:
	A &= 0xDF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB0: RES 6, B		[----]
case 0xB0:
	B &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB1: RES 6, C		[----]
case 0xB1:
	C &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB2: RES 6, D		[----]
case 0xB2:
	D &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB3: RES 6, E		[----]
case 0xB3:
	E &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB4: RES 6, H		[----]
case 0xB4:
	H &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB5: RES 6, L		[----]
case 0xB5:
	L &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB6: RES 6, (HL)	[----]
case 0xB6:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0xBF);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBB7: RES 6, A		[----]
case 0xB7:
	A &= 0xBF;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB8: RES 7, B		[----]
case 0xB8:
	B &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBB9: RES 7, C		[----]
case 0xB9:
	C &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBBA: RES 7, D		[----]
case 0xBA:
	D &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBBB: RES 7, E		[----]
case 0xBB:
	E &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBBC: RES 7, H		[----]
case 0xBC:
	H &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBBD: RES 7, L		[----]
case 0xBD:
	L &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBBE: RES 7, (HL)	[----]
case 0xBE:
	cgbMemWrite8(HL, cgbMemRead8(HL) & 0x7F);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBBF: RES 7, A		[----]
case 0xBF:
	A &= 0x7F;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC0: SET 0, B		[----]
case 0xC0:
	B |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC1: SET 0, C		[----]
case 0xC1:
	C |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC2: SET 0, D		[----]
case 0xC2:
	D |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC3: SET 0, E		[----]
case 0xC3:
	E |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC4: SET 0, H		[----]
case 0xC4:
	H |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC5: SET 0, L		[----]
case 0xC5:
	L |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC6: SET 0, (HL)	[----]
case 0xC6:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x01);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBC7: SET 0, A		[----]
case 0xC7:
	A |= 0x01;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC8: SET 1, B		[----]
case 0xC8:
	B |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBC9: SET 1, C		[----]
case 0xC9:
	C |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBCA: SET 1, D		[----]
case 0xCA:
	D |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBCB: SET 1, E		[----]
case 0xCB:
	E |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBCC: SET 1, H		[----]
case 0xCC:
	H |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBCD: SET 1, L		[----]
case 0xCD:
	L |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBCE: SET 1, (HL)	[----]
case 0xCE:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x02);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBCF: SET 1, A		[----]
case 0xCF:
	A |= 0x02;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD0: SET 2, B		[----]
case 0xD0:
	B |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD1: SET 2, C		[----]
case 0xD1:
	C |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD2: SET 2, D		[----]
case 0xD2:
	D |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD3: SET 2, E		[----]
case 0xD3:
	E |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD4: SET 2, H		[----]
case 0xD4:
	H |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD5: SET 2, L		[----]
case 0xD5:
	L |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD6: SET 2, (HL)	[----]
case 0xD6:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x04);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBD7: SET 2, A		[----]
case 0xD7:
	A |= 0x04;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD8: SET 3, B		[----]
case 0xD8:
	B |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBD9: SET 3, C		[----]
case 0xD9:
	C |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBDA: SET 3, D		[----]
case 0xDA:
	D |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBDB: SET 3, E		[----]
case 0xDB:
	E |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBDC: SET 3, H		[----]
case 0xDC:
	H |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBDD: SET 3, L		[----]
case 0xDD:
	L |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBDE: SET 3, (HL)	[----]
case 0xDE:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x08);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBDF: SET 3, A		[----]
case 0xDF:
	A |= 0x08;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE0: SET 4, B		[----]
case 0xE0:
	B |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE1: SET 4, C		[----]
case 0xE1:
	C |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE2: SET 4, D		[----]
case 0xE2:
	D |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE3: SET 4, E		[----]
case 0xE3:
	E |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE4: SET 4, H		[----]
case 0xE4:
	H |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE5: SET 4, L		[----]
case 0xE5:
	L |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE6: SET 4, (HL)	[----]
case 0xE6:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x10);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBE7: SET 4, A		[----]
case 0xE7:
	A |= 0x10;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE8: SET 5, B		[----]
case 0xE8:
	B |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBE9: SET 5, C		[----]
case 0xE9:
	C |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBEA: SET 5, D		[----]
case 0xEA:
	D |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBEB: SET 5, E		[----]
case 0xEB:
	E |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBEC: SET 5, H		[----]
case 0xEC:
	H |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBED: SET 5, L		[----]
case 0xED:
	L |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBEE: SET 5, (HL)	[----]
case 0xEE:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x20);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBEF: SET 5, A		[----]
case 0xEF:
	A |= 0x20;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF0: SET 6, B		[----]
case 0xF0:
	B |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF1: SET 6, C		[----]
case 0xF1:
	C |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF2: SET 6, D		[----]
case 0xF2:
	D |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF3: SET 6, E		[----]
case 0xF3:
	E |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF4: SET 6, H		[----]
case 0xF4:
	H |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF5: SET 6, L		[----]
case 0xF5:
	L |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF6: SET 6, (HL)	[----]
case 0xF6:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x40);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBF7: SET 6, A		[----]
case 0xF7:
	A |= 0x40;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF8: SET 7, B		[----]
case 0xF8:
	B |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBF9: SET 7, C		[----]
case 0xF9:
	C |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBFA: SET 7, D		[----]
case 0xFA:
	D |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBFB: SET 7, E		[----]
case 0xFB:
	E |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBFC: SET 7, H		[----]
case 0xFC:
	H |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBFD: SET 7, L		[----]
case 0xFD:
	L |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
// CPU Opcode - CBFE: SET 7, (HL)	[----]
case 0xFE:
	cgbMemWrite8(HL, cgbMemRead8(HL) | 0x80);
	g_nCgbCpuTicks += 4;
	break;
// CPU Opcode - CBFF: SET 7, A		[----]
case 0xFF:
	A |= 0x80;
	g_nCgbCpuTicks += 2;
	break;
}
