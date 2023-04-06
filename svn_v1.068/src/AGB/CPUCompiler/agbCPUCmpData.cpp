/**
 * @file agbCPUCmpData.h
 * @author zhfang
 * @date 2009.12.27
 * @brief AGB Emulate For CTR - some data define for Compiler
 */
#include "..\..\trlHeader.h"
#include "agbCPUCmpData.h"

CPU_COMPILER_DATA g_sCPUCmpData;
CPU_COMPILER_DATA g_sCPUCmpDataOL;

u8 g_pCmpdBuf[INST_BLOCK_MAXLENGTH];	///< compiled result
u32  g_nCmpdBufLength;

u32 g_pCmpdAddr[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address
u32 g_pCmpdAddrRe[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address

u32 g_pCmpdFuncCall[INST_BLOCK_FUNCCALL_MAX];  ///< this record the function called position in g_pCmpdBuf,by this position, can get the function address 
u32 g_nCmpdFuncCallNum;

u32 g_pCmpdJmp[INST_BLOCK_JMP_MAX];
u32 g_nCmpdJmpNum;

s32 g_nCmpdJmpAddress;

u32 g_pCmpdFuncCallAddrStack[INST_BLOCK_FUNCCALL_MAX];
u32 g_pCmpdFuncAddrStack[INST_BLOCK_FUNCCALL_MAX];
u32 g_pCmpdFuncAddrStackPos;

u32 g_pCmpdThumbFuncAddrStack[INST_BLOCK_FUNCCALL_MAX];
u32 g_pCmpdThumbFuncAddrStackPos;

u32 g_pCmpdArmFuncAddrStack[INST_BLOCK_FUNCCALL_MAX];
u32 g_pCmpdArmFuncAddrStackPos;

CPU_CMP_RUNDATA g_sCPUCmpRunData;

u32 g_pCmpdDebugAddress[INST_BLOCK_DEBUG_MAX];
u32 g_nCmpdDebugAddressNum;

u32 g_pCmpdEmptyLoopAddress[INST_BLOCK_EMPTYLOOP_MAX];
u32 g_nCmpdEmptyLoopAddressNum;

u32 g_nCmpdForceStopAddress;

u32 g_bCmpdInterruptChange;

u32 g_bCmpdCmpAll;

u32 g_nCmpdCmpBlockCt;
u32 g_nCmpdCmpBlockMax;
u32 g_nCmpdCmpBlockCtOL;
u32 g_nCmpdCmpBlockMaxOL;

u32 g_nCmpdCurFuncAddressOL;


u32 g_pCmpdAddrOL[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address
u32 g_pCmpdAddrReOL[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address

u32 g_nCmpdBufLengthOL;

u32 g_nCmpdFuncLevel;

u32 g_bCmpdRuntimeCmp;

u32 g_bCmpdOffLine = 0;

u32 g_nCmpdJmpTemp;
u32 g_nCmpdCondJmpOL;

#ifdef TRL_PLATFORM_PC
FILE* g_pOLBlockData_fp;
FILE* g_pOLBlockData_hfp;
FILE* g_pOLJumpData_fp;
FILE* g_pOLJumpData_hfp;
FILE* g_pOLFunc_fp;
#endif
