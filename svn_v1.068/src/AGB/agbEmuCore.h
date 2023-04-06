/**
 * @file agbEmuCore.h
 * @author zhfang
 * @date 2009.11.25
 * @brief TRL Emulate For CTR - Emu Core AGB
 */
#pragma once
#include "agbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @brief EmuCore Initialize */
void agbEmuCoreInit(trlSEmuShellBuffer* pBuf);
/** @brief EmuCore Run One Frame */
void agbEmuCoreRunOneFrame();
/** @brief EmuCore Reset */
void agbEmuCoreReset();
/** @brief EmuCore Input */
void agbEmuCoreInput(u32 nKeyBuf);
/** @brief EmuCore Resume */
void agbEmuCoreResume();
/** @brief EmuCore Exit */
void agbEmuCoreExit();
