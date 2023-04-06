/**
 * @file agbCPUCompiler
 * @author zhfang
 * @date 2009.12.15
 * @brief AGB Emulate For CTR - Compiler for AGB CPU
 */
#pragma once
#include "..\agbGlobal.h"
/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}

/** @brief Initialize Compiler */
void agbCPUCmpilerInit();
/** @brief Compile the Instruction */
s32 agbCPUCmpilerCmpAll();
/** @brief Compile the Interrupt */
s32 agbCPUCmpilerCmpInterrupt();
/** @brief  */
s32 agbCPUCmpGetBlockID(u32 nOriAddress, u32 bThumb);
