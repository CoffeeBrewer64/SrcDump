/**
 * @file trlEmuShellFont.h
 * @author zhfang, chentian
 * @date 2010.03.22
 * @brief TRL Emulate - EmuShell Font Module
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
#define TRL_FONT_WHITE		0
#define TRL_FONT_RED		1
#define TRL_FONT_YELLOW		2
#define TRL_FONT_MAX		3
//@}

/** @brief Init Font */
void trlEmuShellFontInit();
/** @brief Exit */
void trlEmuShellFontExit();
/** @brief Draw Text */
void trlEmuShellFontDraw(u32 nX, u32 nY, u32 nTileX, const char *szText, u32 nCount, u16* pBuffer, u32 nColor = TRL_FONT_WHITE);
