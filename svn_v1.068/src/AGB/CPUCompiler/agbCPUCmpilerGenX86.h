/**
 * @file agbCPUCompilerGenX86.h
 * @author zhfang
 * @date 2009.12.24
 * @brief AGB Emulate For CTR - Generate the X86 Machine Code
 */
#pragma once
#include "..\agbGlobal.h"

void genPUSH_EAX();
void genNOT_EAX();
void genADD_ESP_U8(u8 value);
void genADD_EAX_S8(s8 value);
void genSUB_EAX_S8(s8 value);
/*
void genADD_EAX_U8(u8 value);
void genSUB_EAX_U8(u8 value);
*/


void genADD_EAX_U32(u32 value);
void genSUB_EAX_U32(u32 value);
void genADD_EAX_MEM32(u32 memAddr);
void genSUB_EAX_MEM32(u32 memAddr);
void genADC_EAX_MEM32(u32 memAddr);
void genADC_EDX_MEM32(u32 memAddr);
void genSBC_EAX_MEM32(u32 memAddr);
void genAND_EAX_MEM32(u32 memAddr);
void genORR_EAX_MEM32(u32 memAddr);
void genEOR_EAX_MEM32(u32 memAddr);
void genMUL_EAX_MEM32(u32 memAddr);
void genNEG_MEM32(u32 memAddr);
void genAND_EAX_S8(s8 value);
void genAND_EAX_U32(u32 value);
void genMOVZX_EAX_AL();
void genMOVZX_EAX_AX();
void genMOVSX_EAX_AL();
void genMOVSX_EAX_AX();
void genPOP_EAX();
void genSetNFlag(u32 memAddr);
void genSetZFlag(u32 memAddr);
void genSetCFlag(u32 memAddr);
void genSetNCFlag(u32 memAddr);
void genSetVFlag(u32 memAddr);
void genMOV_EAX_U32(u32 value);
void genMOV_ECX_U32(u32 value);
void genMOV_EAX_MEM8(u32 memAddr);
void genMOV_EAX_MEM16(u32 memAddr);
void genMOV_EAX_MEM32(u32 memAddr);
void genMOV_ECX_MEM32(u32 memAddr);
void genMOV_MEM_EAX32(u32 memAddr);
void genMOV_MEM_U32(u32 memAddr, u32 value);
void genLSL_EAX(u8 value);
void genLSR_EAX(u8 value);
void genASR_EAX(u8 value);
void genROR_EAX(u8 value);
void genLSL_EAX_CL();
void genLSR_EAX_CL();
void genASR_EAX_CL();
void genROR_EAX_CL();
void genJEQ_S32(s32 value);
void genJNE_S32(s32 value);
void genJCS_S32(s32 value);
void genJCC_S32(s32 value);
void genJNS_S32(s32 value);
void genJNC_S32(s32 value);
void genJVS_S32(s32 value);
void genJVC_S32(s32 value);
void genJHI_S32(s32 value);
void genJLS_S32(s32 value);
void genJGE_S32(s32 value);
void genJLT_S32(s32 value);
void genJGT_S32(s32 value);
void genJLE_S32(s32 value);
void genJMP_S32(s32 value);

void genCMP_MEM_U8(u32 memAddr, u8 value);
void genCMP_MEM_U32(u32 memAddr, u32 value);
void genCMP_EAX_MEM32(u32 memAddr);
void genCMP_EAX_U8(u8 value);
void genReturn();
void genCALL(u32 funcAddr);


void genMOV_MEM_EDX32(u32 memAddr);
void genMUL_EAX_MEM32(u32 memAddr);
void genIMUL_EAX_MEM32(u32 memAddr);
void genIMUL_EAX_U32(u32 value);
