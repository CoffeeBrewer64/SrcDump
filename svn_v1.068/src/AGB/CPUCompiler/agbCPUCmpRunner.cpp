/**
 * @file agbCPUCompRunner.cpp
 * @author zhfang
 * @date 2009.12.27
 * @brief AGB Emulate For CTR - Run the compile version CPU
 */
#include <assert.h>
#include "..\..\trlHeader.h"
#include "..\..\trlTime.h"
#include "..\agbMemory.h"
#include "..\agbRegister.h"
#include "..\agbCPUData.h"
#include "agbCPUCmpData.h"
#include "agbCPUCmpiler.h"
#include "agbCPUCmpRunner.h"

#ifdef TRL_PLATFORM_CTR
//#include "agbCPUCmpOffLine_JumpData.h"
#include "agbCPUCmpOffLine_BlockData.h"
#endif


void agbCPUCmpRunnerInit()
{
	g_sCPUCmpRunData.nJmpStackPos = 0;
}

s32 agbCPUCmpRun(u32 bThumb)
{
	//u64 cputime;
	s32 rv;
	u32 curpc;

	//cputime = trlTimeGet_us();

	if(bThumb == 0)
		curpc = g_nAgbCPUReg[15] - 4;
	else
		curpc = g_nAgbCPUReg[15] - 2;

	if(g_sCPUCmpRunData.nJmpStackPos > 0)
	{
		u32 jmpindex = g_sCPUCmpRunData.pJmpStack[g_sCPUCmpRunData.nJmpStackPos-1];
		CPU_JMP_BLOCK *pjumdata = &g_sCPUCmpData.pJmpBlock[jmpindex];
		if(pjumdata->nOriRetAddress == curpc)
		{			
			g_sCPUCmpRunData.nJmpStackPos--;
			rv = agbCPUCmpRunBlock(pjumdata->nOriBlockID, pjumdata->nCmpdRetAddress, bThumb);

			//g_nAgbCPUTime += (trlTimeGet_us() - cputime);
			return rv;
		}
	}	
	{
		s32 blockid = agbCPUCmpGetBlockID(curpc, bThumb);
		if(blockid >=0)
		{
			rv = agbCPUCmpRunBlock(blockid, 0, bThumb);
			//g_nAgbCPUTime += (trlTimeGet_us() - cputime);
			return rv;
		}
	}
	//g_nAgbCPUTime += (trlTimeGet_us() - cputime);
	return -1;
}

/** @brief  */
s32 agbCPUCmpRunBlock(u32 nBlockID, u32 offset, u32 bThumb)
{
	
	s32 (*pfunc)();
	CPU_INSTRUCT_BLOCK *ptb = &(g_sCPUCmpData.pInstBlock[nBlockID]);	
	if(ptb->nOriAddr == 0x080b4dAC)// && ptb->nRunTimes >= 0x10000)
		nBlockID = nBlockID;
#ifdef TRL_PLATFORM_PC
	pfunc = (*(s32(*)(void))(ptb->pBuf + offset));
#endif
#ifdef TRL_PLATFORM_CTR
	if(offset != 0)
		pfunc = (*(s32(*)(void))(offset));
	else
		pfunc = (*(s32(*)(void))(ptb->pBuf + offset));
#endif

	
#ifdef TRL_PLATFORM_PC
	s32 rv = pfunc();
#endif
#ifdef TRL_PLATFORM_CTR
	s32 rv = FUNC_JUMP((u32)pfunc);
#endif
	

	if(offset == 0)
		ptb->nRunTimes++;

	if(ptb->nOriAddr == 0x080b6a58)// && ptb->nRunTimes >= 0x10000)
	{
		if(g_nAgbCPUReg[15] == 0x08046301)
			nBlockID = nBlockID;
	}
	
	CPU_JMP_BLOCK *jb = &g_sCPUCmpData.pJmpBlock[rv];

	if(jb->nJmpType == CMPD_JMPTYPE_FUNC)
	{
		g_sCPUCmpRunData.pJmpStack[g_sCPUCmpRunData.nJmpStackPos++] = rv;
		if(bThumb == 0)
		{
			ARM_FIRST_PREFETCH
		}
		else
		{
			THUMB_FIRST_PREFETCH
		}
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_FUNCX)
	{
		g_sCPUCmpRunData.pJmpStack[g_sCPUCmpRunData.nJmpStackPos++] = rv;
		if(bThumb == 0)
		{
			g_nAgbThumbState = 1;			
			THUMB_FIRST_PREFETCH
		}
		else
		{
			g_nAgbThumbState = 0;			
			ARM_FIRST_PREFETCH
		}
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_JUMP)
	{
		if(bThumb == 0)
		{
			ARM_FIRST_PREFETCH
		}
		else
		{
			THUMB_FIRST_PREFETCH
		}
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_JUMPX)
	{
		if(bThumb == 0)
		{
			g_nAgbThumbState = 1;			
			THUMB_FIRST_PREFETCH
		}
		else
		{
			g_nAgbThumbState = 0;			
			ARM_FIRST_PREFETCH
		}
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_JUMPEX)
	{
		if((g_nAgbCPUReg[15]&0x1) == 1)
		{
			g_nAgbThumbState = 1;
			g_nAgbCPUReg[15] &= 0xFFFFFFFE;
			THUMB_FIRST_PREFETCH
		}
		else
		{
			g_nAgbThumbState = 0;
			g_nAgbCPUReg[15] &= 0xFFFFFFFC;
			ARM_FIRST_PREFETCH
		}
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_EMPTYLOOP)
	{
		g_sCPUCmpRunData.pJmpStack[g_sCPUCmpRunData.nJmpStackPos++] = rv;
		g_nAgbCPUClock += 400;
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_DEBUG)
	{
		g_sCPUCmpRunData.pJmpStack[g_sCPUCmpRunData.nJmpStackPos++] = rv;
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_FORCESTOP)
	{
		//assert(g_nAgbThumbState == 0);
		if(bThumb == 0)
		{
			ARM_FIRST_PREFETCH
		}
		else
		{
			THUMB_FIRST_PREFETCH
		}
	}
	else if(jb->nJmpType == CMPD_JMPTYPE_SWITCHMODE)
	{
		if(g_nAgbThumbState)
		{			
			THUMB_FIRST_PREFETCH
		}
		else
		{
			ARM_FIRST_PREFETCH
		}
	}
	else
		assert(0);

	g_nAgbCPUClock += 10;
	return jb->nJmpType;
}


