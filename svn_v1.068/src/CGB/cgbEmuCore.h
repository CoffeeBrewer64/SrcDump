/**
 * @file cgbEmuCore.h
 * @author zhfang & chentian
 * @date 2009.11.25
 * @brief TRL Emulate For CTR - Emu Core CGB
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @brief EmuCore Initialize */
void cgbEmuCoreInit(trlSEmuShellBuffer* pBuf);
/** @brief EmuCore Run One Frame */
void cgbEmuCoreRunOneFrame();
/** @brief EmuCore Reset */
void cgbEmuCoreReset();
/** @brief EmuCore Resume */
void cgbEmuCoreResume();
/** @brief EmuCore Exit */
void cgbEmuCoreExit();
/** @brief EmuCore Patch */
void cgbEmuCorePatch(trlSEmuShellPatch* pPatch);
/** @brief EmuCore Initialize */
void cgbEmuCoreConfig();
/** @brief Get Palette Color */
u16 cgbEmuCoreGetPalette(u32 nIndex);
/** @brief Set Palette Color */
void cgbEmuCoreSetPalette(u32 nIndex, u16 nColor, u32 bGray);
/** @brief Swap DMG Palette Mode */
u32 cgbEmuCoreSwapPalette(s32 nMode);
