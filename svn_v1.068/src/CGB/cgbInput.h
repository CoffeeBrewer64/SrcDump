/**
 * @file cgbInput.h
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - Key Input
 */
#pragma once
#include "cgbCPU.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern u32		g_nCgbKeyBuffer;		///< Key Buffer
//@}

/** @brief Initialize Key Input */
void cgbKeyInit();
/** @brief Reset Key Input */
void cgbKeyReset();
/** @brief Resume Key Input */
void cgbKeyResume();
/** @brief Update Key Input */
void cgbKeyUpdate(u32 nKeyBuf);
