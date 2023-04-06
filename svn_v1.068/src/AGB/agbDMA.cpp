/**
 * @file agbDMA.cpp
 * @author Chentian
 * @date 2009.12.04
 * @brief AGB Emulate For CTR - DMA Controller
 */
#include "agbDMA.h"
#include "agbRegister.h"
#include "agbMemory.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
void	(*agbDmaTransfer[4])(u32);					///< Dma Transfer Function Pointer
u32		g_nAgbDmaSad[4] = {0,0,0,0};				///< Dma Source Address
u32		g_nAgbDmaDad[4] = {0,0,0,0};				///< Dma Destination Address
u16		g_nAgbDmaEnable[4] = {0,0,0,0};				///< Dma Enable Flag
//@}

static s32 t_nSInc, t_nDInc, t_bCopy;
/** @brief Do DMA Transfer */
inline void agbDmaDoTranster(u32 nDMA, u32 nCount)
{
	switch(g_pAgbDMACnt[nDMA]->rSrcAddr)
	{
	case 0:	// Increment
		t_nSInc = 2 * (g_pAgbDMACnt[nDMA]->rTransfer + 1);
		break;
	case 1:	// Decrement
		t_nSInc = -2 * (g_pAgbDMACnt[nDMA]->rTransfer + 1);
		break;
	case 2:	// Fixed
		t_nSInc = 0;
		break;
	case 3:	// Prohibied Code
		return;
	}
	switch(g_pAgbDMACnt[nDMA]->rDestAddr)
	{
	case 0:	// Increment
	case 3:	// Increment/Reload
		t_nDInc = 2 * (g_pAgbDMACnt[nDMA]->rTransfer + 1);
		break;
	case 1:	// Decrement
		t_nDInc = -2 * (g_pAgbDMACnt[nDMA]->rTransfer + 1);
		break;
	case 2:	// Fixed
		t_nDInc = 0;
		break;
	}

	t_bCopy = 0;
	if(g_pAgbDMACnt[nDMA]->rTransfer)	// 32-bit transfer
	{
		if(t_nSInc>0 && t_nDInc>0)
			t_bCopy = agbMemCopy32(g_nAgbDmaDad[nDMA], g_nAgbDmaSad[nDMA], nCount*4);

		if(!t_bCopy)
		{
			do{
				agbMemWrite32(g_nAgbDmaDad[nDMA], agbMemRead32(g_nAgbDmaSad[nDMA]));
				g_nAgbDmaSad[nDMA] += t_nSInc;
				g_nAgbDmaDad[nDMA] += t_nDInc;
				--nCount;
			}while(nCount);
		}
	}
	else							// 16-bit transfer
	{
		if(t_nSInc>0 && t_nDInc>0)
			t_bCopy = agbMemCopy16(g_nAgbDmaDad[nDMA], g_nAgbDmaSad[nDMA], nCount*2);

		if(!t_bCopy)
		{
			do{
				agbMemWrite16(g_nAgbDmaDad[nDMA], agbMemRead16(g_nAgbDmaSad[nDMA]));
				g_nAgbDmaSad[nDMA] += t_nSInc;
				g_nAgbDmaDad[nDMA] += t_nDInc;
				--nCount;
			}while(nCount);
		}
	}

	if(g_pAgbDMACnt[nDMA]->rInterrupt)
		g_pAgbIF->rDMA = 1<<nDMA;
	if(!g_pAgbDMACnt[nDMA]->rRepeat)
	{
		g_pAgbDMACnt[nDMA]->rEnable = 0;
		g_nAgbDmaEnable[nDMA] = 0;
	}
}

/** @brief Start DMA0 Transfer */
inline void agbDmaTransfer0(u32 nStart)
{
	if(nStart)
	{
		g_nAgbDmaSad[0] = g_pAgbDMA0Sad->rAddress;
		g_nAgbDmaDad[0] = g_pAgbDMA0Dad->rAddress;
	}
	u32 nCount = g_pAgbDMA0Count->rCount;
	if(!nCount)
		nCount = 0x4000;
	agbDmaDoTranster(0, nCount);
	if(g_pAgbDMACnt[0]->rDestAddr == 3)	// Reload
		g_nAgbDmaDad[0] = g_pAgbDMA0Dad->rAddress;
}

/** @brief Start DMA1 Transfer */
inline void agbDmaTransfer1(u32 nStart)
{
	if(nStart)
	{
		g_nAgbDmaSad[1] = g_pAgbDMA1Sad->rAddress;
		g_nAgbDmaDad[1] = g_pAgbDMA1Dad->rAddress;
	}
	if(g_pAgbDMACnt[1]->rStartup == 0x03)
	{
		g_pAgbDMACnt[1]->rDestAddr = 2;
		agbDmaDoTranster(1, 4);
		return;
	}
	u32 nCount = g_pAgbDMA1Count->rCount;
	if(!nCount)
		nCount = 0x4000;
	agbDmaDoTranster(1, nCount);
	if(g_pAgbDMACnt[1]->rDestAddr == 3)	// Reload
		g_nAgbDmaDad[1] = g_pAgbDMA1Dad->rAddress;
}

/** @brief Start DMA2 Transfer */
inline void agbDmaTransfer2(u32 nStart)
{
	if(nStart)
	{
		g_nAgbDmaSad[2] = g_pAgbDMA2Sad->rAddress;
		g_nAgbDmaDad[2] = g_pAgbDMA2Dad->rAddress;
	}
	if(g_pAgbDMACnt[2]->rStartup == 0x03)
	{
		g_pAgbDMACnt[2]->rDestAddr = 2;
		agbDmaDoTranster(2, 4);
		return;
	}
	u32 nCount = g_pAgbDMA2Count->rCount;
	if(!nCount)
		nCount = 0x4000;
	agbDmaDoTranster(2, nCount);
	if(g_pAgbDMACnt[2]->rDestAddr == 3)	// Reload
		g_nAgbDmaDad[2] = g_pAgbDMA2Dad->rAddress;
}

/** @brief Start DMA3 Transfer */
inline void agbDmaTransfer3(u32 nStart)
{
	if(nStart)
	{
		g_nAgbDmaSad[3] = g_pAgbDMA3Sad->rAddress;
		g_nAgbDmaDad[3] = g_pAgbDMA3Dad->rAddress;
	}
	u32 nCount = *g_pAgbDMA3Count;
	if(!nCount)
		nCount = 0x10000;
	agbDmaDoTranster(3, nCount);
	if(g_pAgbDMACnt[3]->rDestAddr == 3)	// Reload
		g_nAgbDmaDad[3] = g_pAgbDMA3Dad->rAddress;
}

/** @brief Start VBlank DMA Transfer */
void agbDmaTransferVBlank()
{
	for(s32 n=0; n<4; ++n)
	{
		if(!g_pAgbDMACnt[n]->rEnable)
			continue;
		if(g_pAgbDMACnt[n]->rStartup == 0x01)
			agbDmaTransfer[n](0);
	}
}

/** @brief Start HBlank DMA Transfer */
void agbDmaTransferHBlank()
{
	for(s32 n=0; n<4; ++n)
	{
		if(!g_pAgbDMACnt[n]->rEnable)
			continue;
		if(g_pAgbDMACnt[n]->rStartup == 0x02)
			agbDmaTransfer[n](0);
	}
}

/** @brief Start Synchronize DMA Transfer */
void agbDmaTransferSynchronize()
{
	if(!g_pAgbDMACnt[3]->rEnable)
		return;
	if((g_pAgbVCount->rVCountVal >= 1) && (g_pAgbVCount->rVCountVal < 161))
		agbDmaTransfer[3](0);
	else if(g_pAgbVCount->rVCountVal == 162)
	{
		g_pAgbDMACnt[3]->rEnable = 0;
		g_nAgbDmaEnable[3] = 0;
	}
}

/** @brief Start Direct Sound FIFO DMA Transfer */
void agbDmaTransferDirectSoundFIFO(u32 nDMA)
{
	if(!g_pAgbDMACnt[nDMA]->rEnable)
		return;
	if(g_pAgbDMACnt[nDMA]->rStartup != 0x03)
		return;
	agbDmaDoTranster(nDMA, 4);
}

/** @brief Reset DMA */
void agbDmaReset()
{
	for(s32 n=0; n<4; ++n)
	{
		g_nAgbDmaSad[n] = g_nAgbDmaDad[n] = 0;
		g_nAgbDmaEnable[n] = 0;
	}
}

/** @brief Initialize DMA */
void agbDmaInit()
{
	agbDmaTransfer[0] = agbDmaTransfer0;
	agbDmaTransfer[1] = agbDmaTransfer1;
	agbDmaTransfer[2] = agbDmaTransfer2;
	agbDmaTransfer[3] = agbDmaTransfer3;
	agbDmaReset();
}
