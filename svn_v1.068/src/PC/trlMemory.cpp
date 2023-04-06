/**
 * @file trlMemory_PC.cpp
 * @author Chentian
 * @date 2009.11.16
 * @brief TRL Emulate For PC - Memory Module
 */
#include "..\trlMemory.h"
#include "..\trlDebug.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u32		g_nTrlMemSize = 0x01000000;		///< System Memory Size
u8*		g_pTrlMemPoint = NULL;			///< System Memory Point
u32		g_nTrlMemSizeUsed = 0;			///< System Memory Used Size
//@}

/** @brief init the trl system memory*/
u32 trlMemInit(u32 nMaxSize )
{
	g_nTrlMemSize = nMaxSize;
	g_pTrlMemPoint = new u8[g_nTrlMemSize];
	return g_nTrlMemSize;
}

/** @brief reset the trl system memory */ 
u32 trlMemReset()
{
	return 0;
}

/** @brief Alloc memory */
void* trlMemAlloc(size_t nSize, u8 nAlign)
{
	nSize += nSize % nAlign;
	if(g_nTrlMemSizeUsed + nSize > g_nTrlMemSize)
	{
		TRL_ERROR("trlMemAlloc Fail.");
		return NULL;
	}
	void* pNew = (void*)&g_pTrlMemPoint[g_nTrlMemSizeUsed];
	g_nTrlMemSizeUsed += nSize;
	return pNew;
}

/** @brief Free Memory*/
void trlMemFree(void* pBuf)
{
}

/** @brief get total size of system memory */
u32 trlMemGetTotalSize()
{
	return g_nTrlMemSize;
}

/** @brief get current free system memory */
u32 trlMemGetFree()
{
	return g_nTrlMemSize-g_nTrlMemSizeUsed;
}

/** @brief output the state of system memory usage */
void trlMemPrint()
{
}

/** @brief Alloc device memory*/
void* trlMemAllocDevice(size_t nSize, u8 nAlign)
{
	return trlMemAlloc(nSize, nAlign);
}

/** @brief Delete Memory */
void trlMemExit()
{
	delete []g_pTrlMemPoint;
}
