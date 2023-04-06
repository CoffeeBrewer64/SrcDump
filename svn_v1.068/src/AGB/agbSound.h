/**
 * @file agbSound.h
 * @author Chentian
 * @date 2009.11.24
 * @brief AGB Emulate For CTR - Sound
 */
#pragma once
#include "agbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}

/** @brief Initialize Sound */
void agbSndInit();
/** @brief Reset Sound */
void agbSndReset();
/** @brief Update Ticks */
void agbSndUpdateTicks(u32 nTicks);
/** @brief Update Sound Registers for 8 Bits */
void agbSndUpdateReg8(u32 nAddr);
/** @brief Update Sound Registers for 16 Bits */
void agbSndUpdateReg16(u32 nAddr);
/** @brief Update Sound Registers for 32 Bits */
void agbSndUpdateReg32(u32 nAddr);
/** @brief Process Direct Sound Timer Overflow */
void agbSndTimerOverflow(u32 nTimer);
