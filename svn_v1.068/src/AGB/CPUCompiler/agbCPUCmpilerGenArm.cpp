/**
 * @file agbCPUCompilerGenArm.h
 * @author zhfang
 * @date 2010.01.05
 * @brief AGB Emulate For CTR - Generate the Arm Machine Code
 */
#include <assert.h>
#include "..\..\trlHeader.h"
#include "agbCPUCmpData.h"
#include "agbCPUCmpilerGenArm.h"
#include "..\agbCPUData.h"

void genARM_PUSH_EAX()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x50;	
}

void genARM_NOT_EAX()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD0;
}

void genARM_ADD_ESP_U8(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xc4;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genARM_ADD_EAX_S8(s8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
	g_pCmpdBuf[g_nCmpdBufLength++] = (u8)value;
}

void genARM_SUB_EAX_S8(s8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
	g_pCmpdBuf[g_nCmpdBufLength++] = (u8)value;
}
/*
void genARM_ADD_EAX_U8(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genARM_SUB_EAX_U8(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}
*/


void genARM_ADD_EAX_U32(u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}
void genARM_SUB_EAX_U32(u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x2D;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;	
}

void genARM_ADD_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x03;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_SUB_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x2B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_ADC_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x13;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_ADC_EDX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x13;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x15;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_SBC_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x1b;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_AND_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x23;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_ORR_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_EOR_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x33;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_NEG_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x1D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}


void genARM_AND_EAX_S8(s8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE0;
	g_pCmpdBuf[g_nCmpdBufLength++] = (u8)value;
}

void genARM_AND_EAX_U32(u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x25;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genARM_MOVZX_EAX_AL()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB6;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
}
void genARM_MOVZX_EAX_AX()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
}

void genARM_MOVSX_EAX_AL()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xBE;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
}
void genARM_MOVSX_EAX_AX()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x98;
}

void genARM_POP_EAX()
{assert(0);
}

void genARM_SetNFlag(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x98;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_SetZFlag(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x94;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_SetCFlag(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x92;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_SetNCFlag(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x93;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_SetVFlag(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x90;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_MOV_EAX_U32(u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB8;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genARM_MOV_ECX_U32(u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB9;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genARM_MOV_EAX_MEM8(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB6;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}



void genARM_MOV_EAX_MEM16(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xB7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_MOV_EAX_MEM32(u32 memAddr)
{assert(0);	
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xA1;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}

void genARM_MOV_ECX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}


void genARM_MOV_MEM_EAX32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xA3;	
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}


void genARM_LSL_EAX(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE0;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genARM_LSR_EAX(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genARM_ASR_EAX(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}
void genARM_ROR_EAX(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC1;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC8;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}


void genARM_LSL_EAX_CL()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE0;
}
void genARM_LSR_EAX_CL()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xE8;
}
void genARM_ASR_EAX_CL()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF8;
}
void genARM_ROR_EAX_CL()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xD3;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC8;
}

void genARM_JEQ_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x84;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JNE_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x85;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JCS_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x82;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JCC_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JNS_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x88;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JNC_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x89;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JVS_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x80;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JVC_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JHI_S32(s32 value)
{
	(void)value;
	assert(0);	
}
void genARM_JLS_S32(s32 value)
{
	(void)value;
	assert(0);
}

void genARM_JGE_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JLT_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8C;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JGT_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8F;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}
void genARM_JLE_S32(s32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x8E;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;	
	g_nCmpdBufLength+=4;
}



void genARM_CMP_MEM_U8(u32 memAddr, u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x3D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;	
	g_nCmpdBufLength+=4;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}
void genARM_CMP_MEM_U32(u32 memAddr, u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x81;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x3D;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}
void genARM_CMP_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x3B;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_CMP_EAX_U8(u8 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x83;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xFA;
	g_pCmpdBuf[g_nCmpdBufLength++] = value;
}

void genARM_Return()
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength] = 0xC3;
	g_nCmpdBufLength++;
}

void genARM_CALL(u32 funcAddr)
{assert(0);	
	assert(g_nCmpdFuncCallNum < INST_BLOCK_FUNCCALL_MAX);
	g_pCmpdFuncCall[g_nCmpdFuncCallNum++] = g_nCmpdBufLength + 1;
	g_pCmpdBuf[g_nCmpdBufLength] = 0xE8;
	g_nCmpdBufLength++;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = funcAddr;	
	g_nCmpdBufLength+=4;
}

void genARM_MOV_MEM_EDX32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x89;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x15;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_MUL_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xF7;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x25;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_IMUL_EAX_MEM32(u32 memAddr)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x0F;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xAF;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x05;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = memAddr;
	g_nCmpdBufLength+=4;
}
void genARM_IMUL_EAX_U32(u32 value)
{assert(0);
	g_pCmpdBuf[g_nCmpdBufLength++] = 0x69;
	g_pCmpdBuf[g_nCmpdBufLength++] = 0xC0;
	*(u32*)(g_pCmpdBuf + g_nCmpdBufLength) = value;
	g_nCmpdBufLength+=4;
}

void genARM_MOV_MEM_U32(u32 memAddr, u32 value)
{
	(void)memAddr, (void)value;
	assert(0);	
}

void genARM_JMP_S32(s32 value)
{	
	(void)value;
	assert(0);
}

///////////////////////////////////////////////////////////////////////
void genARMN_STR_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSTR r%d, [r%d]\n", rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif	
}

void genARMN_STRH_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSTRH r%d, [r%d]\n", rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif	
}

void genARMN_STRB_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSTRB r%d, [r%d]\n", rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif	
}

void genARMN_LDRB_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tLDRB r%d, [r%d]\n", rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif	
}

void genARMN_LDRH_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tLDRH r%d, [r%d]\n", rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif	
}


void genARMN_LDR_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tLDR r%d, [r%d]\n", rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif	
}



void genARMN_LDR_REG_U32(u32 r, u32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tLDR r%d, =0x%08x\n", r, value);
	fflush(g_pOLFunc_fp);
#else
	(void)r, (void)value;
	assert(0);
#endif
}
void genARMN_LDR_REG_ADDR(u32 r, u32 memAddr)
{
#ifdef TRL_PLATFORM_PC
	for(int i=0;i<REG_NUM;i++)
	{
		if(memAddr == (u32)&g_nAgbCPUReg[i])
		{
			//fprintf(g_pOLFunc_fp, "\tLDR r%d, =g_nAgbCPUReg + %d\n", r, i*4);
			if(r == 4)
				fprintf(g_pOLFunc_fp, "\tLDR r%d, =g_nAgbCPUReg + %d\n", r, i*4);
			else
				genARMN_ADD_REG_REG_U32(r, 4, i*4, 0);
			fflush(g_pOLFunc_fp);
			return;
		}		
	}	
	assert(0);
#else
	(void)r, (void)memAddr;
	assert(0);
#endif
}

void genARMN_JMP_S32(s32 value)
{	
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tB INST_0x%08x_IN_0x%08x\n", value, g_nCmpdCurFuncAddressOL);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif	
}

void genARMN_JCOND_S32(char *cond, s32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tB%s INST_0x%08x_IN_0x%08x\n", cond, value, g_nCmpdCurFuncAddressOL);
	fflush(g_pOLFunc_fp);
#else
	(void)cond, (void)value;
	assert(0);
#endif	
}




void genARMN_MOV_REG_U8(u32 rd, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tMOV r%d, #0x%02x\n", rd, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)value;
	assert(0);
#endif	
}

void genARMN_MOV_COND_REG_U8(u32 rd, char * cond, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tMOV%s r%d, #0x%02x\n", cond,rd, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)value, (void)cond;
	assert(0);
#endif
}

void genARMN_CMP_REG_U8(u32 rd, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tCMP r%d, #0x%02x\n", rd, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)value;
	assert(0);
#endif
}

void genARMN_MOVS_REG_U8(u32 rd, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tMOVS r%d, #0x%02x\n", rd, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)value;
	assert(0);
#endif	
}

void genARMN_ADDS_REG_REG_U8(u32 rd, u32 rn, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tADDS r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value;
	assert(0);
#endif	
}
void genARMN_SUBS_REG_REG_U8(u32 rd, u32 rn, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSUBS r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value;
	assert(0);
#endif	
}


void genARMN_ADD_REG_REG_U8(u32 rd, u32 rn, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tADD r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value;
	assert(0);
#endif	
}

void genARMN_SUB_REG_REG_U8(u32 rd, u32 rn, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSUB r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value;
	assert(0);
#endif	
}

void genARMN_OP_REG_U32(char *op, u32 rn, u32 value, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, #0x%02x\n", op, rn, value);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, #0x%02x\n", op, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rn, (void)value, (void)s;
	assert(0);
#endif
}

void genARMN_OP_REG_REG_U32(char *op,u32 rd, u32 rn, u32 value, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, #0x%02x\n", op, rd, rn, value);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, #0x%02x\n", op, rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rn, (void)value, (void)s;
	assert(0);
#endif
}

void genARMN_OP_REG_REG(char *op,u32 rd, u32 rn, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d\n", op, rd, rn);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d\n", op, rd, rn);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rn, (void)s;
	assert(0);
#endif
}


void genARMN_OP_REG_REG_REG(char *op,u32 rd, u32 rn, u32 rm, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, r%d\n", op, rd, rn, rm);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, r%d\n", op, rd, rn, rm);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rn, (void)rm, (void)s;
	assert(0);
#endif
}

void genARMN_OP_REG_REG_REG_REG(char *op,u32 rdlo, u32 rdhi, u32 rn, u32 rm, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, r%d, r%d\n", op, rdlo, rdhi, rn, rm);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, r%d, r%d\n", op, rdlo, rdhi, rn, rm);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rdlo, (void)rdhi, (void)rn, (void)rm, (void)s;
	assert(0);
#endif
}

void genARMN_ADD_REG_REG_U32(u32 rd, u32 rn, u32 value, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\tADD r%d, r%d, #0x%02x\n", rd, rn, value);
	else
		fprintf(g_pOLFunc_fp, "\tADDS r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value, (void)s;
	assert(0);
#endif	
}

void genARMN_SUB_REG_REG_U32(u32 rd, u32 rn, u32 value, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\tSUB r%d, r%d, #0x%02x\n", rd, rn, value);
	else
		fprintf(g_pOLFunc_fp, "\tSUBS r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value, (void)s;
	assert(0);
#endif	
}

void genARMN_ADD_REG_REG_REG(u32 rd, u32 rn, u32 rm)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tADD r%d, r%d, r%d\n", rd, rn, rm);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)rm;
	assert(0);
#endif	
}

void genARMN_SUB_REG_REG_REG(u32 rd, u32 rn, u32 rm)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSUB r%d, r%d, r%d\n", rd, rn, rm);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)rm;
	assert(0);
#endif	
}

void genARMN_ADDS_REG_REG_REG(u32 rd, u32 rn, u32 rm)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tADDS r%d, r%d, r%d\n", rd, rn, rm);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)rm;
	assert(0);
#endif	
}

void genARMN_SUBS_REG_REG_REG(u32 rd, u32 rn, u32 rm)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSUBS r%d, r%d, r%d\n", rd, rn, rm);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)rm;
	assert(0);
#endif	
}

void genARMN_OP_REG_REG_SHIFT_U8(char *op, u32 rd, u32 rm, char *shift, u8 value, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, %s #0x%02x\n", op, rd, rm, shift, value);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, %s #0x%02x\n", op, rd, rm, shift, value);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rm, (void)shift, (void)value, (void)s;
	assert(0);
#endif
}
void genARMN_OP_REG_REG_SHIFT_REG(char *op, u32 rd, u32 rm, char *shift, u32 rs, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, %s r%d\n", op, rd, rm, shift, rs);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, %s r%d\n", op, rd, rm, shift, rs);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rm, (void)shift, (void)rs, (void)s;
	assert(0);
#endif
}


void genARMN_OP_REG_REG_REG_SHIFT_U8(char *op, u32 rd, u32 rn, u32 rm, char *shift, u8 value, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, r%d, %s #0x%02x\n", op, rd, rn, rm, shift, value);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, r%d, %s #0x%02x\n", op, rd, rn, rm, shift, value);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rn, (void)rm, (void)shift, (void)value, (void)s;
	assert(0);
#endif
}
void genARMN_OP_REG_REG_REG_SHIFT_REG(char *op, u32 rd, u32 rn, u32 rm, char *shift, u32 rs, u8 s)
{
#ifdef TRL_PLATFORM_PC
	if(s == 0)
		fprintf(g_pOLFunc_fp, "\t%s r%d, r%d, r%d, %s r%d\n", op, rd, rn, rm, shift, rs);
	else
		fprintf(g_pOLFunc_fp, "\t%sS r%d, r%d, r%d, %s r%d\n", op, rd, rn, rm, shift, rs);
	fflush(g_pOLFunc_fp);
#else
	(void)op, (void)rd, (void)rn, (void)rm, (void)shift, (void)rs, (void)s;
	assert(0);
#endif
}

void genARMN_AND_REG_REG_U8(u32 rd, u32 rn, u8 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tAND r%d, r%d, #0x%02x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value;
	assert(0);
#endif
}

void genARMN_BIC_REG_REG_U32(u32 rd, u32 rn, u32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBIC r%d, r%d,#0x%08x\n", rd, rn, value);
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn, (void)value;
	assert(0);
#endif
}

void genARMN_BL(u32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBL FUNC_0x%08x\n", value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif
}

void genARMM_MOV_REG_U32(u32 rd, u32 value)
{
	genARMN_LDR_REG_U32(rd, value);
}

void genARMM_MOV_MEM_U32(u32 memAddr, u32 value, u32 rdtemp, u32 rntemp)
{
	genARMN_LDR_REG_U32(rdtemp, value);
	genARMN_LDR_REG_ADDR(rntemp, memAddr);
	genARMN_STR_REG_REG(rdtemp, rntemp);
}

void genARMM_MOV_REG_MEM8(u32 rd,u32 memAddr)
{
	genARMN_LDR_REG_ADDR(rd, memAddr);
	genARMN_LDRB_REG_REG(rd,rd);
}

void genARMM_MOV_REG_MEM16(u32 rd,u32 memAddr)
{
	genARMN_LDR_REG_ADDR(rd, memAddr);
	genARMN_LDRH_REG_REG(rd,rd);
}


void genARMM_MOV_REG_MEM32(u32 rd,u32 memAddr)
{
	genARMN_LDR_REG_ADDR(rd, memAddr);
	genARMN_LDR_REG_REG(rd,rd);
}

void genARMM_MOV_MEM_REG32(u32 memAddr, u32 rd, u32 rtemp)
{
	genARMN_LDR_REG_ADDR(rtemp, memAddr);
	genARMN_STR_REG_REG(rd, rtemp);
}

void genARMM_MOV_MEM_REG16(u32 memAddr, u32 rd, u32 rtemp)
{
	genARMN_LDR_REG_ADDR(rtemp, memAddr);
	genARMN_STRH_REG_REG(rd, rtemp);
}

void genARMM_MOV_MEM_REG8(u32 memAddr, u32 rd, u32 rtemp)
{
	genARMN_LDR_REG_ADDR(rtemp, memAddr);
	genARMN_STRB_REG_REG(rd, rtemp);
}

void genARMM_MOV_MEM_MEM32(u32 destAddr, u32 srcAddr, u32 rdtemp, u32 rntemp)
{
	assert(rdtemp != rntemp);
	genARMM_MOV_REG_MEM32(rdtemp, srcAddr);
	genARMM_MOV_MEM_REG32(destAddr, rdtemp, rntemp);

}

void genARMM_ADD_REG_REG_U32(u32 rd, u32 rn, u32 value, u32 rtemp)
{
	genARMM_MOV_REG_U32(rtemp, value);
	genARMN_ADD_REG_REG_REG(rd, rn, rtemp);
}

void genARMM_SUB_REG_REG_U32(u32 rd, u32 rn, u32 value, u32 rtemp)
{
	genARMM_MOV_REG_U32(rtemp, value);
	genARMN_SUB_REG_REG_REG(rd, rn, rtemp);

}
void genARMM_OP_RD_RN_RM_SHIFT_VALUE(char *op, u32 rd, u32 rn, u32 rm, char *shift, u32 value, u8 s)
{
	genARMN_OP_REG_REG_REG_SHIFT_U8(op, rd, rn, rm, shift, value, s);
}
void genARMM_OP_RD_RN_RM_SHIFT_RS(char *op, u32 rd, u32 rn, u32 rm, char *shift, u32 rs, u8 s)
{
	genARMN_OP_REG_REG_REG_SHIFT_REG(op, rd, rn, rm, shift, rs, s);
}
void genARMM_OP_RN_RM_SHIFT_VALUE(char *op, u32 rn, u32 rm, char *shift, u32 value, u8 s)
{
	genARMN_OP_REG_REG_SHIFT_U8(op, rn, rm, shift, value, s);
}
void genARMM_OP_RN_RM_SHIFT_RS(char *op, u32 rn, u32 rm, char *shift, u32 rs, u8 s)
{
	genARMN_OP_REG_REG_SHIFT_REG(op, rn, rm, shift, rs, s);
}
void genARMM_OP_RD_RM_SHIFT_VALUE(char *op, u32 rd, u32 rm, char *shift, u32 value, u8 s)
{
	genARMN_OP_REG_REG_SHIFT_U8(op, rd, rm, shift, value, s);
}
void genARMM_OP_RD_RM_SHIFT_RS(char *op, u32 rd, u32 rm, char *shift, u32 rs, u8 s)
{
	genARMN_OP_REG_REG_SHIFT_REG(op, rd, rm, shift, rs, s);
}


void genARMN_JEQ_S32_TEMP(s32 value)
{	
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBEQ TEMP_0x%08x\n", value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif	
}

void genARMN_JNE_S32_TEMP(s32 value)
{	
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBNE TEMP_0x%08x\n", value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif	
}

void genARMM_TEMPLABEL(s32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "TEMP_0x%08x\n",value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif
}

void genARMM_LABEL_FOR_COND(s32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "COND_0x%08x\n",value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif
}
void genARMN_JEQ_S32_COND(s32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBEQ COND_0x%08x\n", value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif	
}

void genARMN_JNE_S32_COND(s32 value)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBNE COND_0x%08x\n", value);
	fflush(g_pOLFunc_fp);
#else
	(void)value;
	assert(0);
#endif	
}

void genARMM_CALL(u32 memAddr, char *funcname)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tBL %s\n",funcname);
	fflush(g_pOLFunc_fp);
#else
	(void)memAddr;
	(void)funcname;
	assert(0);
#endif
}

void genARMN_SXTB_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSXTB r%d,r%d\n", rd, rn);	
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif
}
void genARMN_SXTH_REG_REG(u32 rd, u32 rn)
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tSXTH r%d,r%d\n", rd, rn);	
	fflush(g_pOLFunc_fp);
#else
	(void)rd, (void)rn;
	assert(0);
#endif
}

void genARMM_Return()
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tPOP {r4}\n");
	fprintf(g_pOLFunc_fp, "\tPOP {lr}\n");
	fprintf(g_pOLFunc_fp, "\tBX lr\n");
	fflush(g_pOLFunc_fp);
#else
	assert(0);
#endif
}

void genARMM_LTORG()
{
#ifdef TRL_PLATFORM_PC
	fprintf(g_pOLFunc_fp, "\tLTORG\n");	
	fflush(g_pOLFunc_fp);
#else
	assert(0);
#endif
}

void genARMM_MEM_SETN(u32 memAddr, u32 rdtemp, u32 rntemp)
{	
	genARMN_MOV_COND_REG_U8(rdtemp, "MI", 1);
	genARMN_MOV_COND_REG_U8(rdtemp, "PL", 0);
	genARMM_MOV_MEM_REG32(memAddr, rdtemp, rntemp);
}
void genARMM_MEM_SETZ(u32 memAddr, u32 rdtemp, u32 rntemp)
{
	genARMN_MOV_COND_REG_U8(rdtemp, "EQ", 1);
	genARMN_MOV_COND_REG_U8(rdtemp, "NE", 0);
	genARMM_MOV_MEM_REG32(memAddr, rdtemp, rntemp);
}
void genARMM_MEM_SETC(u32 memAddr, u32 rdtemp, u32 rntemp)
{
	genARMN_MOV_COND_REG_U8(rdtemp, "CS", 1);
	genARMN_MOV_COND_REG_U8(rdtemp, "CC", 0);
	genARMM_MOV_MEM_REG32(memAddr, rdtemp, rntemp);
}
void genARMM_MEM_SETV(u32 memAddr, u32 rdtemp, u32 rntemp)
{
	genARMN_MOV_COND_REG_U8(rdtemp, "VS", 1);
	genARMN_MOV_COND_REG_U8(rdtemp, "VC", 0);
	genARMM_MOV_MEM_REG32(memAddr, rdtemp, rntemp);
}

void genARMM_CMP_MEM_U8(u32 memAddr, u8 value, u32 rtemp)
{
	genARMM_MOV_REG_MEM32(rtemp, memAddr);
	genARMN_CMP_REG_U8(rtemp, value);
}
