/**
 * @file agbCPU.h
 * @author zhfang
 * @date 2009.11.26
 * @brief AGB Emulate For CTR - CPU
 */
#pragma once
#include "agbCPUData.h"
/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}

/** @brief Initialize CPU */
 void agbCPUInit();
/** @brief Reset CPU */
void agbCPUReset();
/** @brief Run CPU */
void agbCPURun();
/** @brief Run CPU Intrerrupt*/
void agbCPUIntrCheckRun();
/** @brief Emu the swi call */
extern "C" void agbCPUSWI_NOPRE(u32 swi_no);
/** @brief call swi */
void agbCPUSWI(u32 swi_no);
/** @brief enter interrupt proc */
void agbCPUInterrupt();

/** @brief change the cpu mode  */
extern "C" void agbCPUSwitchMode(u32 mode, u32 saveState );
/** @brief some one wirte to g_nAgbCPUReg[16], so update the g_nAgbCPUReg[REG_ZFLAG], g_nAgbCPUReg[REG_CFLAG] and so on  */
extern "C" void agbCPUUpdateFlags(); ///< 
