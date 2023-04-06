/**
 * @file agbCPUCmpData.h
 * @author zhfang
 * @date 2009.12.27
 * @brief AGB Emulate For CTR - some data define for Compiler
 */
#pragma once
#include "..\agbGlobal.h"
#include "agbCPUCmpFuncTable.h"
/** @name Macro Define */
//@{
//@}

/** @name Global Variable Cmp DAta*/
//@{

//zhfang test, there have some bound error out of range...careful
//#define INST_BLOCK_NUM 0x500   ///< max compiled inst block num
//#define INST_BLOCK_MAXLENGTH 0x15000 ///< max length of a compiled block(result block)
//#define INST_BLOCK_FUNCCALL_MAX 0x300
//#define INST_BLOCK_JMP_MAX 100
//#define INST_BLOCK_EMPTYLOOP_MAX 10
//#define INST_BLOCK_DEBUG_MAX 100
//#define INST_JMP_NUM INST_BLOCK_NUM*3

#define INST_BLOCK_NUM 0x1000   ///< max compiled inst block num
#define INST_BLOCK_MAXLENGTH 0x20000 ///< max length of a compiled block(result block)
#define INST_BLOCK_FUNCCALL_MAX 0x600
#define INST_BLOCK_JMP_MAX 0x200
#define INST_BLOCK_EMPTYLOOP_MAX 0x10
#define INST_BLOCK_DEBUG_MAX 0x10
#define INST_JMP_NUM INST_BLOCK_NUM*3

#define INNER_JUMP_MAX 100

typedef struct
{
	u32 nOriAddr;  ///< this block's ori start address
	u8	*pBuf;		///< the buf store the cmped result(pc/(new arm) instuction)
	u32 nBufSize;	///< the buf size
	u32 nRunTimes;	///< this block runs times
	s32 nInstNum;	///< this block's origin instruction num ...this will be delete	
	u32 pJmpDataBuf;	///< in cmpling, 
}CPU_INSTRUCT_BLOCK;


typedef enum
{
	CMPD_JMPTYPE_FUNC = 0,
	CMPD_JMPTYPE_FUNCX,
	CMPD_JMPTYPE_JUMP,
	CMPD_JMPTYPE_JUMPX,
	CMPD_JMPTYPE_JUMPEX,
	CMPD_JMPTYPE_SWITCHMODE,
	CMPD_JMPTYPE_EMPTYLOOP,
	CMPD_JMPTYPE_DEBUG,
	CMPD_JMPTYPE_FORCESTOP
}CMPD_JMPTYPE;


typedef enum
{
	INST_CMPD_RESULT_NORMAL = 0,
	INST_CMPD_RESULT_INNERJUMP,
	INST_CMPD_RESULT_INNERJUMP_COND,
	INST_CMPD_RESULT_FUNCTION,
	INST_CMPD_RESULT_FUNCTION_COND,
	INST_CMPD_RESULT_FUNCTIONX,
	INST_CMPD_RESULT_SWI,
	INST_CMPD_RESULT_OUTERJUMP,
	INST_CMPD_RESULT_OUTERJUMPX,
	INST_CMPD_RESULT_OUTERJUMPEX,
	INST_CMPD_RESULT_EMPTYLOOP,
	INST_CMPD_RESULT_DEBUG,
	INST_CMPD_RESULT_SWITCHCMODE,
	INST_CMPD_RESULT_CONDITION,
	INST_CMPD_RESULT_UNKOWN_INST
}INST_CMPD_RESULT;

typedef struct
{
	CMPD_JMPTYPE nJmpType;
	CMPD_JMPTYPE nPadding1;
	CMPD_JMPTYPE nPadding2;
	CMPD_JMPTYPE nPadding3;
	s32 nOriJmpAddress;			///< the origin address at that the jump(or function call) occur
	s32 nOriRetAddress;			///< after the function call, the origin return address
	s32 nOriJmpedAddress;		///< if be func call, this is the origin address of the func. if  be jump, this is the dest address
	

	s32 nOriBlockID;
	s32 nCmpdJmpAddress;
	s32 nCmpdRetAddress;

	s32 nJmpedBlockID;
	s32 nCmpdJmpedAddress;
}CPU_JMP_BLOCK;

typedef struct
{
	CPU_INSTRUCT_BLOCK pInstBlock[INST_BLOCK_NUM];			///< cmped block for both instruction
	CPU_JMP_BLOCK pJmpBlock[INST_JMP_NUM];					///< in cmpling, build the jmpdata	
	u32 nInstBlockNum;
	u32 nJmpBlockNum;
}CPU_COMPILER_DATA;

extern CPU_COMPILER_DATA g_sCPUCmpData;		///< final compilied result
extern CPU_COMPILER_DATA g_sCPUCmpDataOL;	///< final off line compilied result


///////////////////
//comping temp buf
extern u8 g_pCmpdBuf[INST_BLOCK_MAXLENGTH];	///< compiled result
extern u32  g_nCmpdBufLength;
extern u32 g_pCmpdFuncCall[INST_BLOCK_FUNCCALL_MAX];
extern u32 g_nCmpdFuncCallNum;
extern u32 g_pCmpdAddr[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address
extern u32 g_pCmpdAddrRe[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address
extern u32 g_pCmpdJmp[INST_BLOCK_JMP_MAX];
extern u32 g_nCmpdJmpNum;

extern u32 g_pCmpdFuncCallAddrStack[INST_BLOCK_FUNCCALL_MAX];
extern u32 g_pCmpdFuncAddrStack[INST_BLOCK_FUNCCALL_MAX];
extern u32 g_pCmpdFuncAddrStackPos;

extern u32 g_pCmpdThumbFuncAddrStack[INST_BLOCK_FUNCCALL_MAX];
extern u32 g_pCmpdThumbFuncAddrStackPos;

extern u32 g_pCmpdArmFuncAddrStack[INST_BLOCK_FUNCCALL_MAX];
extern u32 g_pCmpdArmFuncAddrStackPos;


extern s32 g_nCmpdJmpAddress;

extern u32 g_pCmpdDebugAddress[INST_BLOCK_DEBUG_MAX];
extern u32 g_nCmpdDebugAddressNum;

extern u32 g_pCmpdEmptyLoopAddress[INST_BLOCK_EMPTYLOOP_MAX];
extern u32 g_nCmpdEmptyLoopAddressNum;

extern u32 g_nCmpdForceStopAddress;

extern u32 g_bCmpdInterruptChange;

extern u32 g_bCmpdCmpAll;

extern u32 g_nCmpdCmpBlockCt;
extern u32 g_nCmpdCmpBlockMax;
extern u32 g_nCmpdCmpBlockCtOL;
extern u32 g_nCmpdCmpBlockMaxOL;
extern u32 g_nCmpdBufLengthOL;

extern u32 g_pCmpdAddrOL[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address
extern u32 g_pCmpdAddrReOL[INST_BLOCK_MAXLENGTH];  ///<  origin instuction compiled address

extern u32 g_nCmpdFuncLevel;

extern u32 g_bCmpdRuntimeCmp;

extern u32 g_bCmpdOffLine;

extern u32 g_nCmpdJmpTemp;
extern u32 g_nCmpdCondJmpOL;

extern u32 g_nCmpdCurFuncAddressOL;

//comping temp buf
//////////////////////

//@}

#ifdef TRL_PLATFORM_PC
extern FILE* g_pOLBlockData_fp;
extern FILE* g_pOLBlockData_hfp;
extern FILE* g_pOLJumpData_fp;
extern FILE* g_pOLJumpData_hfp;
extern FILE* g_pOLFunc_fp;
#endif


/** @name Global Variable Run DAta*/
//@{
#define INST_RUNNER_JMP_MAX 100



typedef struct
{
	u32 pJmpStack[INST_RUNNER_JMP_MAX];
	u32 nJmpStackPos;
}CPU_CMP_RUNDATA;

extern CPU_CMP_RUNDATA g_sCPUCmpRunData;
//@}
