/**
 * @file agbCPUCompilerGenArm.h
 * @author zhfang
 * @date 2010.01.05
 * @brief AGB Emulate For CTR - Generate the Arm Machine Code
 */
#pragma once
#include "..\agbGlobal.h"

void genARM_PUSH_EAX();
void genARM_NOT_EAX();
void genARM_ADD_ESP_U8(u8 value);
void genARM_ADD_EAX_S8(s8 value);
void genARM_SUB_EAX_S8(s8 value);
/*
void genARM_ADD_EAX_U8(u8 value);
void genARM_SUB_EAX_U8(u8 value);
*/


void genARM_ADD_EAX_U32(u32 value);
void genARM_SUB_EAX_U32(u32 value);
void genARM_ADD_EAX_MEM32(u32 memAddr);
void genARM_SUB_EAX_MEM32(u32 memAddr);
void genARM_ADC_EAX_MEM32(u32 memAddr);
void genARM_ADC_EDX_MEM32(u32 memAddr);
void genARM_SBC_EAX_MEM32(u32 memAddr);
void genARM_AND_EAX_MEM32(u32 memAddr);
void genARM_ORR_EAX_MEM32(u32 memAddr);
void genARM_EOR_EAX_MEM32(u32 memAddr);
void genARM_MUL_EAX_MEM32(u32 memAddr);
void genARM_NEG_MEM32(u32 memAddr);
void genARM_AND_EAX_S8(s8 value);
void genARM_AND_EAX_U32(u32 value);
void genARM_MOVZX_EAX_AL();
void genARM_MOVZX_EAX_AX();
void genARM_MOVSX_EAX_AL();
void genARM_MOVSX_EAX_AX();
void genARM_POP_EAX();
void genARM_SetNFlag(u32 memAddr);
void genARM_SetZFlag(u32 memAddr);
void genARM_SetCFlag(u32 memAddr);
void genARM_SetNCFlag(u32 memAddr);
void genARM_SetVFlag(u32 memAddr);
void genARM_MOV_EAX_U32(u32 value);
void genARM_MOV_ECX_U32(u32 value);
void genARM_MOV_EAX_MEM8(u32 memAddr);
void genARM_MOV_EAX_MEM16(u32 memAddr);
void genARM_MOV_EAX_MEM32(u32 memAddr);
void genARM_MOV_ECX_MEM32(u32 memAddr);
void genARM_MOV_MEM_EAX32(u32 memAddr);

void genARM_LSL_EAX(u8 value);
void genARM_LSR_EAX(u8 value);
void genARM_ASR_EAX(u8 value);
void genARM_ROR_EAX(u8 value);
void genARM_LSL_EAX_CL();
void genARM_LSR_EAX_CL();
void genARM_ASR_EAX_CL();
void genARM_ROR_EAX_CL();
void genARM_JEQ_S32(s32 value);
void genARM_JNE_S32(s32 value);
void genARM_JCS_S32(s32 value);
void genARM_JCC_S32(s32 value);
void genARM_JNS_S32(s32 value);
void genARM_JNC_S32(s32 value);
void genARM_JVS_S32(s32 value);
void genARM_JVC_S32(s32 value);
void genARM_JHI_S32(s32 value);
void genARM_JLS_S32(s32 value);
void genARM_JGE_S32(s32 value);
void genARM_JLT_S32(s32 value);
void genARM_JGT_S32(s32 value);
void genARM_JLE_S32(s32 value);


void genARM_CMP_MEM_U8(u32 memAddr, u8 value);
void genARM_CMP_MEM_U32(u32 memAddr, u32 value);
void genARM_CMP_EAX_MEM32(u32 memAddr);
void genARM_CMP_EAX_U8(u8 value);
void genARM_Return();
void genARM_CALL(u32 funcAddr);

void genARM_MOV_MEM_U32(u32 memAddr, u32 value);


void genARM_MOV_MEM_EDX32(u32 memAddr);
void genARM_MUL_EAX_MEM32(u32 memAddr);
void genARM_IMUL_EAX_MEM32(u32 memAddr);
void genARM_IMUL_EAX_U32(u32 value);
void genARM_JMP_S32(s32 value);
//////////////////////////////////////////////////////////////


void genARMN_JMP_S32(s32 value);
void genARMN_JCOND_S32(char *cond, s32 value);



void genARMN_MOV_REG_U8(u32 rd, u8 value);
void genARMN_MOV_COND_REG_U8(u32 rd, char * cond, u8 value);
void genARMN_CMP_REG_U8(u32 rd, u8 value);

void genARMN_MOVS_REG_U8(u32 rd, u8 value);
void genARMN_ADDS_REG_REG_U8(u32 rd, u32 rn, u8 value);
void genARMN_SUBS_REG_REG_U8(u32 rd, u32 rn, u8 value);

void genARMN_AND_REG_REG_U8(u32 rd, u32 rn, u8 value);

void genARMN_ADD_REG_REG_U8(u32 rd, u32 rn, u8 value);
void genARMN_SUB_REG_REG_U8(u32 rd, u32 rn, u8 value);

void genARMN_OP_REG_U32(char *op, u32 rn, u32 value, u8 s = 0);
void genARMN_OP_REG_REG_U32(char *op,u32 rd, u32 rn, u32 value, u8 s = 0);
void genARMN_OP_REG_REG(char *op,u32 rd, u32 rn, u8 s = 0);
void genARMN_OP_REG_REG_REG(char *op,u32 rd, u32 rn, u32 rm, u8 s = 0);
void genARMN_OP_REG_REG_REG_REG(char *op,u32 rdlo, u32 rdhi, u32 rn, u32 rm, u8 s = 0);

void genARMN_ADD_REG_REG_U32(u32 rd, u32 rn, u32 value, u8 s = 0);
void genARMN_SUB_REG_REG_U32(u32 rd, u32 rn, u32 value, u8 s = 0);


void genARMN_ADD_REG_REG_REG(u32 rd, u32 rn, u32 rm);
void genARMN_SUB_REG_REG_REG(u32 rd, u32 rn, u32 rm);

void genARMN_ADDS_REG_REG_REG(u32 rd, u32 rn, u32 rm);
void genARMN_SUBS_REG_REG_REG(u32 rd, u32 rn, u32 rm);

void genARMN_OP_REG_REG_SHIFT_U8(char *op, u32 rd, u32 rm, char *shift, u8 value, u8 s = 0);
void genARMN_OP_REG_REG_SHIFT_REG(char *op, u32 rd, u32 rm, char *shift, u32 rs, u8 s = 0);

void genARMN_OP_REG_REG_REG_SHIFT_U8(char *op, u32 rd, u32 rn, u32 rm, char *shift, u8 value, u8 s = 0);
void genARMN_OP_REG_REG_REG_SHIFT_REG(char *op, u32 rd, u32 rn, u32 rm, char *shift, u32 rs, u8 s = 0);


void genARMN_STR_REG_REG(u32 rd, u32 rn);
void genARMN_STRB_REG_REG(u32 rd, u32 rn);
void genARMN_STRH_REG_REG(u32 rd, u32 rn);
void genARMN_LDR_REG_REG(u32 rd, u32 rn);
void genARMN_LDRB_REG_REG(u32 rd, u32 rn);
void genARMN_LDRH_REG_REG(u32 rd, u32 rn);

void genARMN_LDR_REG_U32(u32 r, u32 value);

void genARMN_BIC_REG_REG_U32(u32 rd, u32 rn, u32 value);
void genARMM_MOV_REG_U32(u32 rd, u32 value);



void genARMM_MOV_MEM_U32(u32 memAddr, u32 value, u32 rdtemp, u32 rntemp);

void genARMM_MOV_REG_MEM32(u32 rd,u32 memAddr);
void genARMM_MOV_REG_MEM16(u32 rd,u32 memAddr);
void genARMM_MOV_REG_MEM8(u32 rd,u32 memAddr);
void genARMM_MOV_MEM_REG32(u32 memAddr, u32 rd, u32 rtemp);
void genARMM_MOV_MEM_REG16(u32 memAddr, u32 rd, u32 rtemp);
void genARMM_MOV_MEM_REG8(u32 memAddr, u32 rd, u32 rtemp);

void genARMM_MOV_MEM_MEM32(u32 destAddr, u32 srcAddr, u32 rdtemp, u32 rntemp);
void genARMM_ADD_REG_REG_U32(u32 rd, u32 rn, u32 value, u32 rtemp);
void genARMM_SUB_REG_REG_U32(u32 rd, u32 rn, u32 value, u32 rtemp);

void genARMM_OP_RD_RN_RM_SHIFT_VALUE(char *op, u32 rd, u32 rn, u32 rm, char *shift, u32 value, u8 s = 0);
void genARMM_OP_RD_RN_RM_SHIFT_RS(char *op, u32 rd, u32 rn, u32 rm, char *shift, u32 rs, u8 s = 0);
void genARMM_OP_RN_RM_SHIFT_VALUE(char *op, u32 rn, u32 rm, char *shift, u32 value, u8 s = 0);
void genARMM_OP_RN_RM_SHIFT_RS(char *op, u32 rn, u32 rm, char *shift, u32 rs, u8 s = 0);
void genARMM_OP_RD_RM_SHIFT_VALUE(char *op, u32 rd, u32 rm, char *shift, u32 value, u8 s = 0);
void genARMM_OP_RD_RM_SHIFT_RS(char *op, u32 rd, u32 rm, char *shift, u32 rs, u8 s = 0);

void genARMM_MEM_SETN(u32 memAddr, u32 rdtemp, u32 rntemp);
void genARMM_MEM_SETZ(u32 memAddr, u32 rdtemp, u32 rntemp);
void genARMM_MEM_SETC(u32 memAddr, u32 rdtemp, u32 rntemp);
void genARMM_MEM_SETV(u32 memAddr, u32 rdtemp, u32 rntemp);

void genARMM_CMP_MEM_U8(u32 memAddr, u8 value, u32 rtemp);

void genARMM_CALL(u32 memAddr, char *funcname);


void genARMM_TEMPLABEL(s32 value);
void genARMN_JEQ_S32_TEMP(s32 value);
void genARMN_JNE_S32_TEMP(s32 value);

void genARMM_LABEL_FOR_COND(s32 value);
void genARMN_JEQ_S32_COND(s32 value);
void genARMN_JNE_S32_COND(s32 value);

void genARMN_SXTB_REG_REG(u32 rd, u32 rn);
void genARMN_SXTH_REG_REG(u32 rd, u32 rn);

void genARMM_Return();
void genARMM_LTORG();
void genARMN_LDR_REG_ADDR(u32 r, u32 memAddr);
