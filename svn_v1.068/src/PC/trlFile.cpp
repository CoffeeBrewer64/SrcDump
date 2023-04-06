/**
 * @file trlFile_PC.cpp
 * @author Chentian
 * @date 2009.11.27
 * @brief TRL Emulate For PC - File Module
 */
#include "..\trlFile.h"
#include "..\trlDebug.h"
#include "..\trlMemory.h"
#include <stdio.h>
#include <stdlib.h>

/** @brief Init */
void trlFileInit()
{
}

/** @brief Format Save Data */
s32 trlFileFormatSaveData()
{
	return TRL_FILE_SUCCESS;
}

/** @brief Mount Save Data */
s32 trlFileMountSaveData()
{
	return TRL_FILE_SUCCESS;
}

/** @brief Unmount Save Data */
s32 trlFileUnmountSaveData()
{
	return TRL_FILE_SUCCESS;
}

/** @brief Exit */
void trlFileExit()
{
}

/** @brief Delete File */
s32 trlFileDelete(const wchar_t* pPathName)
{
	if(!DeleteFileW(pPathName))
	{
		TRL_WARN(0, "Delete File fail.");
		return TRL_FILE_OTHERERROR;
	}
	return TRL_FILE_SUCCESS;
}

/** @brief Delete File */
s32 trlFileDelete(const char* pPathName)
{
	if(!DeleteFileA(pPathName))
	{
		TRL_WARN(0, "Delete File fail.");
		return TRL_FILE_OTHERERROR;
	}
	return TRL_FILE_SUCCESS;
}

/** @brief Create File */
s32 trlFileCreate(const wchar_t* pPathName, s32 nSize)
{
	return TRL_FILE_SUCCESS;
}

/** @brief Create File */
s32 trlFileCreate(const char* pPathName, s32 nSize)
{
	return TRL_FILE_SUCCESS;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const wchar_t* pPathName, void* pBuf, s32 nSize, s32 nLimit)
{
	FILE *fp;
	_wfopen_s(&fp, pPathName, L"rb");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	fseek(fp, 0, SEEK_END);
	s32 nLen = ftell(fp);
	if(nSize > 0)
	{
		if(nLimit)
		{
			if(nLen != nSize)
				return TRL_FILE_VERIFICATIONFAILED;
		}
		else
		{
			if(nLen > nSize)
				nLen = nSize;
		}
	}
	fseek(fp, 0, SEEK_SET);
	nSize = fread(pBuf, 1, nLen, fp);
	fclose(fp);
	return nSize;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const char* pPathName, void* pBuf, s32 nSize, s32 nLimit)
{
	FILE *fp;
	fopen_s(&fp, pPathName, "rb");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	fseek(fp, 0, SEEK_END);
	s32 nLen = ftell(fp);
	if(nSize > 0)
	{
		if(nLimit)
		{
			if(nLen != nSize)
				return TRL_FILE_VERIFICATIONFAILED;
		}
		else
		{
			if(nLen > nSize)
				nLen = nSize;
		}
	}
	fseek(fp, 0, SEEK_SET);
	nSize = fread(pBuf, 1, nLen, fp);
	fclose(fp);
	return nSize;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const wchar_t* pPathName, void** ppBuf)
{
	s32 nSize;
	FILE *fp;
	_wfopen_s(&fp, pPathName, L"rb");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	fseek(fp, 0, SEEK_END);
	nSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	(*ppBuf) = trlMemAlloc(nSize);
	nSize = fread(*ppBuf, 1, nSize, fp);
	fclose(fp);
	return nSize;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const char* pPathName, void** ppBuf)
{
	s32 nSize;
	FILE *fp;
	fopen_s(&fp, pPathName, "rb");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	fseek(fp, 0, SEEK_END);
	nSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	(*ppBuf) = trlMemAlloc(nSize);
	nSize = fread(*ppBuf, 1, nSize, fp);
	fclose(fp);
	return nSize;
}

/** @brief Write Buffer to File */
s32 trlFileWrite(const wchar_t* pPathName, void* pBuf, s32 nSize)
{
	s32 nLen;
	FILE *fp;
	_wfopen_s(&fp, pPathName, L"wb");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	nLen = fwrite(pBuf, 1, nSize, fp);
	fclose(fp);
	return nLen;
}

/** @brief Write Buffer to File */
s32 trlFileWrite(const char* pPathName, void* pBuf, s32 nSize)
{
	s32 nLen;
	FILE *fp;
	fopen_s(&fp, pPathName, "wb");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	nLen = fwrite(pBuf, 1, nSize, fp);
	fclose(fp);
	return nLen;
}

/** @brief Append Buffer to File */
s32 trlFileAppend(const wchar_t* pPathName, void* pBuf, s32 nSize)
{
	s32 nLen;
	FILE *fp;
	_wfopen_s(&fp, pPathName, L"ab");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	nLen = fwrite(pBuf, 1, nSize, fp);
	fclose(fp);
	return nLen;
}

/** @brief Append Buffer to File */
s32 trlFileAppend(const char* pPathName, void* pBuf, int nSize)
{
	s32 nLen;
	FILE *fp;
	fopen_s(&fp, pPathName, "ab");
	if(!fp)
		return TRL_FILE_OTHERERROR;
	nLen = fwrite(pBuf, 1, nSize, fp);
	fclose(fp);
	return nLen;
}

/** @brief Create Directory */
s32 trlFileCreateDir(const wchar_t* pPathName)
{
	return TRL_FILE_SUCCESS;
}

/** @brief Create Directory */
s32 trlFileCreateDir(const char* pPathName)
{
	return TRL_FILE_SUCCESS;
}
