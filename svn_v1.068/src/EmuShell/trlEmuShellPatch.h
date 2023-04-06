/**
 * @file trlEmuShellPatch.h
 * @author zhfang, chentian
 * @date 2011.03.31
 * @brief TRL Emulate - EmuShell Patch Module
 */
#pragma once
#include "trlEmuShellStruct.h"

#if TRL_PATCH
/** @name Macro Define */
//@{
//@}

/** @brief EmuShell Patch Main*/
void trlEmuShellPatchMain();
/** @brief Change Mask Mode */
void trlEmuShellPatchMaskChangeMode(u32 nMode);
/** @brief Load Patch File */
void trlEmuShellPatchLoad();

/** @brief EmuShell Patch */
/** in one frame, if have some patch(s) is avtive, call this func to process this/these patch(s) */
inline void trlEmuShellPatch()
{
	if(g_sEmuShellBuffer.nPatchActive)
		trlEmuShellPatchMain();
}
#else
#define trlEmuShellPatch()						((void)0)
#define trlEmuShellPatchMaskChangeMode(m)		((void)0)
#define trlEmuShellPatchLoad()					((void)0)
#endif
