/**
 * @file agbCPUComp.cpp
 * @author zhfang
 * @date 2009.12.27
 * @brief AGB Emulate For CTR - AGB CPU Compiler version
 */
#include <assert.h>
#include "..\..\\trlHeader.h"
#include "..\agbMemory.h"
#include "..\agbRegister.h"
#include "..\agbCPUData.h"


#include "agbCPUCmpData.h"
#include "agbCPUCmp.h"
#include "agbCPUCmpiler.h"
#include "agbCPUCmpRunner.h"
#include "..\\..\\trlDebug.h"

/** @brief Initialize Compiler */
void agbCPUCmpInit()
{
	agbCPUCmpilerInit();
	agbCPUCmpCmpBegin();
	g_nCmpdFuncLevel = 0;
}
/** @brief Compile the Instruction */
void agbCPUCmpCmpBegin()
{
	agbCPUCmpilerCmpAll();
}
/** @brief Compile the Instruction at interrupt */
void agbCPUCmpCmpInterrupt()
{
	agbCPUCmpilerCmpInterrupt();
}

/** @brief Run the Instruction */
s32 agbCPUCmpRun()
{
	s32 rv;
	rv = agbCPUCmpRun(g_nAgbThumbState);
	if(rv >= 0)
	{
		if(rv == CMPD_JMPTYPE_FUNC || rv == CMPD_JMPTYPE_FUNCX)
		{
		}
		return rv;
	}
	else
		return -1;
}



