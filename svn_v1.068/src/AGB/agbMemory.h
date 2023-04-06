/**
 * @file agbMemory.h
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Memory Map
 */
#pragma once
#include "agbGlobal.h"

/** @brief Initialize Memory */
void agbMemInit();
/** @brief Reset Memory */
void agbMemReset();

/** @brief Read 8 bits data from Memory Map */
extern "C" u8 agbMemRead8(u32 nAddr);
/** @brief Read 16 bits data from Memory Map */
extern "C" u16 agbMemRead16(u32 nAddr);
/** @brief Read 32 bits data from Memory Map */
extern "C" u32 agbMemRead32(u32 nAddr);

/** @brief Write 8 bits data to Memory Map */
extern "C" void agbMemWrite8(u32 nAddr, u8 nData);
/** @brief Write 16 bits data to Memory Map */
extern "C" void agbMemWrite16(u32 nAddr, u16 nData);
/** @brief Write 32 bits data to Memory Map */
extern "C" void agbMemWrite32(u32 nAddr, u32 nData);

/** @brief Copy 16 bits data */
u32 agbMemCopy16(u32 nAddrD, u32 nAddrS, u32 nCount);
/** @brief Copy 32 bits data */
u32 agbMemCopy32(u32 nAddrD, u32 nAddrS, u32 nCount);
