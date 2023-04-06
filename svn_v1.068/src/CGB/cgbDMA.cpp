/**
 * @file cgbDMA.cpp
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - DMA Controller
 */
#include "cgbDMA.h"
#include "cgbRegister.h"
#include "cgbMemory.h"
#include "cgbCard.h"
#include "cgbGraphic.h"

/** @name Macro Define */
//@{
#define CGB_DMA_LEN					0x10				///< HDMA Transfer Length Once
//@}

/** @name Global Variable */
//@{
s32					g_nCgbDmaTicks;							///< DMA Ticks
s32					g_nCgbDmaTick0;							///< HDMA Ticks
u32					g_nCgbDmaHDMAFlag;						///< HDMA State Flag
trlSEmuShellResume	g_sCgbDmaSaveData[CGB_DMA_SAVEDATA];	///< DMA Save Data
//@}

/** @brief Initialize DMA */
void cgbDmaInit()
{
	// Save Data
	g_sCgbDmaSaveData[0].SetData(&g_nCgbDmaTicks, 4, 1, 0);
	g_sCgbDmaSaveData[1].SetData(&g_nCgbDmaHDMAFlag, 4, 1, 0);

	cgbDmaReset();
}

/** @brief Reset DMA */
void cgbDmaReset()
{
	g_nCgbDmaTicks = 0;
	g_nCgbDmaTick0 = CGB_DMA_TICKS;
	g_nCgbDmaHDMAFlag = 0;
}

/** @brief Resume DMA */
void cgbDmaResume()
{
	if(g_nCgbDmaTicks == -1)
		g_nCgbDmaTicks = 0;
	g_nCgbDmaTick0 = CGB_DMA_TICKS * (g_pCgbRegKEY1->rCurSpeed + 1);
}

/** @brief Start DMA Transfer */
void cgbDmaTransferDMA()
{
	// Get Address
	u8* pCgbDmaSrc = NULL;
	u32 nSrc = (*g_pCgbRegDMA) << 8;

	if(nSrc < 0x4000)
		pCgbDmaSrc = &g_pCgbROM[nSrc];
	else if(nSrc < 0x8000)
		pCgbDmaSrc = &g_pCgbCurROM[nSrc-0x4000];
	else if(nSrc < 0xA000)
		pCgbDmaSrc = &g_pCgbCurVRAM[nSrc-0x8000];
	else if(nSrc < 0xC000)
		pCgbDmaSrc = &g_pCgbCurERAM[nSrc-0xA000];
	else if(nSrc < 0xD000)
		pCgbDmaSrc = &g_pCgbWRAM[nSrc-0xC000];
	else
		pCgbDmaSrc = &g_pCgbCurWRAM[nSrc-0xD000];
	// Transfer
	trlMemCopy((void*)g_pCgbOAM, (void*)pCgbDmaSrc, 0xA0);
	g_bCgbGrpOAMChange = 1;
}

/** @brief Start HDMA Transfer */
inline void cgbDmaTransferHDMA(u32 nLength, u32 nSrc, u32 nDest)
{
	// Get Address
	u8* pCgbDmaSrc = NULL;
	u8* pCgbDmaDest = &g_pCgbCurVRAM[nDest];

	if(nSrc < 0x4000)
		pCgbDmaSrc = &g_pCgbROM[nSrc];
	else if(nSrc < 0x8000)
		pCgbDmaSrc = &g_pCgbCurROM[nSrc-0x4000];
	else if(nSrc < 0xC000)
		pCgbDmaSrc = &g_pCgbCurERAM[nSrc-0xA000];
	else if(nSrc < 0xD000)
		pCgbDmaSrc = &g_pCgbWRAM[nSrc-0xC000];
	else
		pCgbDmaSrc = &g_pCgbCurWRAM[nSrc-0xD000];

	// Transfer
	trlMemCopy((void*)pCgbDmaDest, (void*)pCgbDmaSrc, nLength);
}

/** @brief Start HDMA Transfer for Normal Mode */
void cgbDmaTransferHDMA_Normal()
{
	u32 nCgbDmaSrc = (g_pCgbREG[0x51] << 8) | g_pCgbREG[0x52];
	u32 nCgbDmaDest = (g_pCgbREG[0x53] << 8) | g_pCgbREG[0x54];
	u32 nLength = (g_pCgbRegHDMA5->rLength+1) << 4;
	cgbDmaTransferHDMA(nLength, nCgbDmaSrc, nCgbDmaDest);

	// Update Register
	g_nCgbDmaTicks = (g_pCgbRegHDMA5->rLength+1) * g_nCgbDmaTick0 + g_pCgbRegKEY1->rCurSpeed + 1;
	nCgbDmaSrc += nLength;
	nCgbDmaDest += nLength;
	if(nCgbDmaSrc == 0x8000)
		nCgbDmaSrc = 0xA000;
	if(nCgbDmaDest == 0x2000)
		nCgbDmaDest = 0x0000;

	g_pCgbREG[0x51] = nCgbDmaSrc >> 8;
	g_pCgbREG[0x52] = nCgbDmaSrc & 0xF0;
	g_pCgbREG[0x53] = (nCgbDmaDest >> 8) & 0x1F;
	g_pCgbREG[0x54] = nCgbDmaDest & 0xF0;
	g_pCgbREG[0x55] = 0xFF;
	g_nCgbDmaHDMAFlag = 0;
}

/** @brief Start HDMA Transfer for HBlank Mode */
void cgbDmaTransferHDMA_HBlank()
{
	u16 nCgbDmaSrc = (g_pCgbREG[0x51] << 8) | g_pCgbREG[0x52];
	u16 nCgbDmaDest = (g_pCgbREG[0x53] << 8) | g_pCgbREG[0x54];
	cgbDmaTransferHDMA(CGB_DMA_LEN, nCgbDmaSrc, nCgbDmaDest);

	// Update Register
	g_nCgbDmaTicks = g_nCgbDmaTick0 + g_pCgbRegKEY1->rCurSpeed + 1;

	// Finish
	if(!g_pCgbRegHDMA5->rLength)
	{
		g_pCgbREG[0x51] = 0xFF;
		g_pCgbREG[0x52] = 0xF0;
		g_pCgbREG[0x53] = 0x9F;
		g_pCgbREG[0x54] = 0xF0;
		g_pCgbREG[0x55] = 0xFF;
		g_nCgbDmaHDMAFlag = 0;
		return;
	}

	nCgbDmaSrc += 0x10;
	nCgbDmaDest += 0x10;
	if(nCgbDmaSrc == 0x8000)
		nCgbDmaSrc = 0xA000;
	if(nCgbDmaDest == 0x2000)
		nCgbDmaDest = 0x0000;

	g_pCgbREG[0x51] = nCgbDmaSrc >> 8;
	g_pCgbREG[0x52] = nCgbDmaSrc & 0xF0;
	g_pCgbREG[0x53] = (nCgbDmaDest >> 8) & 0x1F;
	g_pCgbREG[0x54] = nCgbDmaDest & 0xF0;
	--g_pCgbRegHDMA5->rLength;
}
