/**
 * @file cgbDMGPalette.h
 * @author zhfang
 * @date 2010.03.24
 * @brief CGB Emulate For CTR - DMG Palette
 */
#pragma once
#include "cgbGlobal.h"
#include "cgbMemory.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}

/** @brief Initialize DMG Palette */
void cgbDMGPaletteInit();
/** @brief Get DMG Color */
u16 cgbDMGPaletteGetColor(u32 index);
