/**
 * @file cgbDMA.h
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - DMA Controller
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#define CGB_DMA_SAVEDATA			2					///< DMA Save Data Count
#define	CGB_DMA_TICKS				8					///< HDMA Ticks
//@}

/** @name Global Variable */
//@{
extern s32					g_nCgbDmaTicks;				///< DMA Ticks
extern s32					g_nCgbDmaTick0;				///< HDMA Ticks
extern u32					g_nCgbDmaHDMAFlag;			///< HDMA State Flag
extern trlSEmuShellResume	g_sCgbDmaSaveData[CGB_DMA_SAVEDATA];	///< DMA Save Data
//@}

/** @brief Initialize DMA */
void cgbDmaInit();
/** @brief Reset DMA */
void cgbDmaReset();
/** @brief Resume DMA */
void cgbDmaResume();
/** @brief Start DMA Transfer */
void cgbDmaTransferDMA();
/** @brief Start HDMA Transfer for Normal Mode */
void cgbDmaTransferHDMA_Normal();
/** @brief Start HDMA Transfer for HBlank Mode */
void cgbDmaTransferHDMA_HBlank();
