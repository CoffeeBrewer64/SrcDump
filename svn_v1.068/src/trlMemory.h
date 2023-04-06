/**
 * @file trlMemory.h
 * @author zhfang
 * @date 2009.11.16
 * @brief TRL Emulate - Memory Module
 */
#pragma once
#include "trlMacro.h"
#include "trlType.h"

/** @brief init the trl system memory */
u32 trlMemInit(u32 nMaxSize = 0);
/** @brief reset the trl system memory */
u32 trlMemReset();
/** @brief Alloc memory */
void* trlMemAlloc(size_t nSize, u8 nAlign = 4);
/** @brief Free Memory */
void trlMemFree(void* pBuf);
/** @brief Alloc device memory */
void* trlMemAllocDevice(size_t nSize, u8 nAlign = 32);
/** @brief Alloc device memory */
void trlMemFreeDevice(void* pBuf);
/** @brief get total size of system memory */
u32 trlMemGetTotalSize();
/** @brief get current free system memory */
u32 trlMemGetFree();
/** @brief output the state of system memory usage */
void trlMemPrint();
/** @brief Delete Memory */
void trlMemExit();
#ifdef TRL_PLATFORM_CTR
/** @brief Alloc Vram Memory */
void* trlMemAllocVram(GLenum area, GLenum aim, GLuint id, GLsizei size);
/** @brief Free Vram Memory */
void trlMemFreeVram(GLenum area, GLenum aim, GLuint id, void* addr);
#define trlMemCopy(d,s,z)		nn::nstd::ARMv6::MemCpy(d,s,z)
#define trlMemMove(d,s,z)		nn::nstd::ARMv6::MemMove(d,s,z)
#endif
#ifdef TRL_PLATFORM_PC
#define trlMemCopy(d,s,z)		memcpy(d,s,z)
#define trlMemMove(d,s,z)		memmove(d,s,z)
#endif
