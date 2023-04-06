/**
 * @file agbDMA.h
 * @author Chentian
 * @date 2009.12.04
 * @brief AGB Emulate For CTR - DMA Controller
 */
#pragma once
#include "agbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u16		g_nAgbDmaEnable[4];				///< Dma Enable Flag
//@}

/** @brief Initialize DMA */
void agbDmaInit();
/** @brief Reset DMA */
void agbDmaReset();
/** @brief Start VBlank DMA Transfer */
void agbDmaTransferVBlank();
/** @brief Start HBlank DMA Transfer */
void agbDmaTransferHBlank();
/** @brief Start Synchronize DMA Transfer */
void agbDmaTransferSynchronize();
/** @brief Start Direct Sound FIFO DMA Transfer */
void agbDmaTransferDirectSoundFIFO(u32 nDMA);
/** @brief Start Dma Transfer */
extern void (*agbDmaTransfer[4])(u32 nStart);
