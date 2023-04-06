/**
 * @file agbTime.h
 * @author Chentian
 * @date 2009.12.08
 * @brief AGB Emulate For CTR - Time
 */
#pragma once
#include "agbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u16		g_nAgbTimeCounter[4];		///< Timer Counter Backup
//@}

/** @brief Initialize Time */
void agbTimeInit();
/** @brief Reset Time */
void agbTimeReset();
/** @brief Update Time */
void agbTimeUpdate(u32 nTicks);
