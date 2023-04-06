/**
 * @file trlFile.h
 * @author Chentian
 * @date 2009.11.27
 * @brief TRL Emulate - File Module
 */
#pragma once
#include "trlMacro.h"
#include "trlType.h"

/** @name Macro Define */
//@{
#define TRL_FILE_ENTRY				64

#define TRL_FILE_READ				0
#define TRL_FILE_WRITE				1
#define TRL_FILE_CREATE				2

#define TRL_FILE_SUCCESS			0
#define TRL_FILE_OTHERERROR			(-1)
#define TRL_FILE_NOTFORMATTED		(-2)
#define TRL_FILE_BADFORMAT			(-3)
#define TRL_FILE_VERIFICATIONFAILED	(-4)
#define TRL_FILE_OPERATIONDENIED	(-5)
#define TRL_FILE_NOTFOUND			(-6)
#define TRL_FILE_NOTENOUGHSPACE		(-7)
#define TRL_FILE_ALREADYEXISTS		(-8)
//@}

/** @brief Init */
void trlFileInit();
/** @brief Exit */
void trlFileExit();

/** @brief Create File */
s32 trlFileCreate(const wchar_t* pPathName, s32 nSize);
/** @brief Delete File */
s32 trlFileDelete(const wchar_t* pPathName);
/** @brief Read File to Buffer */
s32 trlFileRead(const wchar_t* pPathName, void* pBuf, s32 nSize = 0, s32 nLimit = 1);
/** @brief Read File to Buffer */
s32 trlFileRead(const wchar_t* pPathName, void** ppBuf);
/** @brief Write Buffer to File */
s32 trlFileWrite(const wchar_t* pPathName, void* pBuf, s32 nSize);
/** @brief Append Write Buffer to File */
s32 trlFileAppend(const wchar_t* pPathName, void* pBuf, s32 nSize);
/** @brief Create Directory */
s32 trlFileCreateDir(const wchar_t* pPathName);

/** @brief Create File */
s32 trlFileCreate(const char* pPathName, s32 nSize);
/** @brief Delete File */
s32 trlFileDelete(const char* pPathName);
/** @brief Read File to Buffer */
s32 trlFileRead(const char* pPathName, void* pBuf, s32 nSize = 0, s32 nLimit = 1);
/** @brief Read File to Buffer */
s32 trlFileRead(const char* pPathName, void** ppBuf);
/** @brief Write Buffer to File */
s32 trlFileWrite(const char* pPathName, void* pBuf, s32 nSize);
/** @brief Append Buffer to File */
s32 trlFileAppend(const char* pPathName, void* pBuf, s32 nSize);
/** @brief Create Directory */
s32 trlFileCreateDir(const char* pPathName);

/** @brief Mount Save Data */
s32 trlFileMountSaveData();
/** @brief Unmount Save Data */
s32 trlFileUnmountSaveData();
/** @brief Format Save Data */
s32 trlFileFormatSaveData();
