/**
 * @file agbCPUCompRunner.h
 * @author zhfang
 * @date 2009.12.27
 * @brief AGB Emulate For CTR - Run the compile version CPU
 */
#pragma once
#include "..\agbGlobal.h"
/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}
void agbCPUCmpRunnerInit();
s32 agbCPUCmpRun(u32 bThumb);
s32 agbCPUCmpRunBlock(u32 nBlockID, u32 offset, u32 bThumb);
