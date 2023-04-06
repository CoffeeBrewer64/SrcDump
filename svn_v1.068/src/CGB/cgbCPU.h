/**
 * @file cgbCPU.h
 * @author Chentian
 * @date 2009.12.25
 * @brief CGB Emulate For CTR - CPU
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
#define	CGB_CPU_HALT		0x01									///< CPU Halt Flag
#define	CGB_CPU_STOP		0x02									///< CPU Stop Flag
#define	CGB_CPU_SAVEDATA	6										///< CPU Save Data Count
//@}

/** @name Global Variable */
//@{
extern u32					g_nCgbCpuState;							///< CPU State
extern u32					g_nCgbCpuIME;							///< Interrupt Master Enable Flag (W)
extern u8*					g_pCgbCpuPC;							///< CPU PC Pointer
extern u16					g_nCgbCpuRegPC;							///< CPU PC Registers
extern trlSEmuShellResume	g_sCgbCpuSaveData[CGB_CPU_SAVEDATA];	///< CPU Save Data
//@}

/** @brief Initialize CPU */
void cgbCpuInit();
/** @brief Reset CPU */
void cgbCpuReset();
/** @brief Resume CPU */
void cgbCpuResume();
/** @brief Run CPU */
void cgbCpuRun();
/** @brief Switch CPU Speed */
void cgbCpuSpeed();
