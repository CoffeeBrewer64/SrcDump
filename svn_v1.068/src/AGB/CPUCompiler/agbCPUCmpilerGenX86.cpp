/**
 * @file agbCPUCompilerGenX86.h
 * @author zhfang
 * @date 2009.12.24
 * @brief AGB Emulate For CTR - Generate the X86 Machine Code
 */
#include <assert.h>
#include "..\..\trlHeader.h"
#include "agbCPUCmpData.h"

void genPUSH_EAX()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x50;	
}

void genNOT_EAX()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD0;
}

void genADD_ESP_U8(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xc4;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genADD_EAX_S8(s8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
	g_pCmpdBuf[g_nCmpdBufLength++] = (u8)value;
}

void genSUB_EAX_S8(s8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
	g_pCmpdBuf[g_nCmpdBufLength++] = (u8)value;
}
/*
void genADD_EAX_U8(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genSUB_EAX_U8(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}
*/


void genADD_EAX_U32(u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}
void genSUB_EAX_U32(u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x2D;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;	
}

void genADD_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x03;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genSUB_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x2B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genADC_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x13;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genADC_EDX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x13;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x15;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genSBC_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x1b;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genAND_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x23;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genORR_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genEOR_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x33;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genNEG_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x1D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}


void genAND_EAX_S8(s8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE0;
	g_pCmpdBuf[g_nCmpdBufLength++] = (u8)value;
}

void genAND_EAX_U32(u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x25;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genMOVZX_EAX_AL()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB6;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
}
void genMOVZX_EAX_AX()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
}

void genMOVSX_EAX_AL()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xBE;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
}
void genMOVSX_EAX_AX()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x98;
}

void genPOP_EAX()
{
}

void genSetNFlag(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x98;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genSetZFlag(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x94;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genSetCFlag(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x92;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genSetNCFlag(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x93;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genSetVFlag(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x90;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genMOV_EAX_U32(u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB8;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genMOV_ECX_U32(u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB9;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genMOV_EAX_MEM8(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB6;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}



void genMOV_EAX_MEM16(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genMOV_EAX_MEM32(u32 memAddr)
{	
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xA1;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genMOV_ECX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}


void genMOV_MEM_EAX32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xA3;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genMOV_MEM_U32(u32 memAddr, u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genLSL_EAX(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE0;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genLSR_EAX(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genASR_EAX(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}
void genROR_EAX(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}


void genLSL_EAX_CL()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE0;
}
void genLSR_EAX_CL()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
}
void genASR_EAX_CL()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF8;
}
void genROR_EAX_CL()
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC8;
}

void genJEQ_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x84;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJNE_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x85;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJCS_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x82;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJCC_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJNS_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x88;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJNC_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x89;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJVS_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x80;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJVC_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJHI_S32(s32 value)
{
	(void)value;
	assert(0);
}
void genJLS_S32(s32 value)
{	
	(void)value;
	assert(0);
}

void genJGE_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJLT_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8C;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJGT_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8F;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genJLE_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8E;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}

void genJMP_S32(s32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE9;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}

void genCMP_MEM_U8(u32 memAddr, u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x3D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;	
	g_nCmpdBufLength+=4;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}
void genCMP_MEM_U32(u32 memAddr, u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x3D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}
void genCMP_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x3B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genCMP_EAX_U8(u8 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xFA;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genReturn()
{
	g_pCmpdBuf[g_nCmpdBufLength] = 0xC3;
	g_nCmpdBufLength++;
}

void genCALL(u32 funcAddr)
{	
	assert(g_nCmpdFuncCallNum < INST_BLOCK_FUNCCALL_MAX);
	g_pCmpdFuncCall[g_nCmpdFuncCallNum++] = g_nCmpdBufLength + 1;
	g_pCmpdBuf[g_nCmpdBufLength] = 0xE8;
	g_nCmpdBufLength++;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = funcAddr;	
	g_nCmpdBufLength+=4;
}

void genMOV_MEM_EDX32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x89;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x15;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genMUL_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x25;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genIMUL_EAX_MEM32(u32 memAddr)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xAF;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genIMUL_EAX_U32(u32 value)
{
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x69;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

