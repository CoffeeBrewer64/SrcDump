/**
 * @file agbCPUCompiler_OffLine.h
 * @author zhfang
 * @date 2010.01.05
 * @brief AGB Emulate For CTR - Off Line Compiler for AGB CPU
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
void agbCPUCmpilerOffLineInit();
/** @brief Build the Cmpdata from LffLine data */
s32 agbCPUCmpilerCmpOffLineBuild();
/** @brief Compile the Instruction */
s32 agbCPUCmpilerCmpOne_OffLine(u32 nOriStartAddress, u32 nOriAddress, u32 bThumb);
/** @brief Compile the Instruction */
s32 agbCPUCmpilerCmpBlock_OffLine(u32 nOriStartAddress, u32 nOriAddress, u32 bThumb);
