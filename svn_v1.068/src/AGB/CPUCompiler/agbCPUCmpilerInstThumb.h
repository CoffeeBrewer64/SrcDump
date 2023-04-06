/**
* @file agbCPUCompilerInstThumb.h
* @author zhfang
* @date 2009.12.27
* @brief AGB Emulate For CTR - Cmp Thumb Inst
*/
#pragma once
#include "..\agbGlobal.h"
//return value
//0: normal
//1: inner jump
//2: function call
//3: outer jump

s32 agbCPUCompiler_Thumb(u16 inst, u32 pc);
