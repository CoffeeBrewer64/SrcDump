/**
 * @file agbCPUComp.h
 * @author zhfang
 * @date 2009.12.27
 * @brief AGB Emulate For CTR - AGB CPU Compiler version
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
void agbCPUCmpInit();
/** @brief Compile the Instruction */
void agbCPUCmpCmpBegin();
/** @brief Compile the Instruction */
void agbCPUCmpCmpInterrupt();
/** @brief Run the Instruction */
s32 agbCPUCmpRun();
