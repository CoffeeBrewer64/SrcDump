/**
 * @file trlFile_CTR.cpp
 * @author Chentian
 * @date 2009.11.27
 * @brief TRL Emulate For CTR - File Module
 */
#include "..\trlFile.h"
#include "..\trlDebug.h"
#include "..\trlMemory.h"

#include <wchar.h>
#include <nn/os.h>
#include <nn/fs.h>
#include <nn/err.h>
using namespace nn::os;
using namespace nn::fs;

/** @name Global Variable */
//@{
DirectoryEntry		g_hTrlFileEntry[TRL_FILE_ENTRY];
void*				g_hTrlFileWorkingMemory = NULL;
//@}

/** @brief Init */
void trlFileInit()
{
	nn::fs::Initialize();

	s32 nSize = GetRomRequiredMemorySize(16, 16);
	NN_LOG("GetRomRequiredMemorySize %d\n", nSize);

	// Rom
	g_hTrlFileWorkingMemory = trlMemAllocDevice(nSize);
	nn::Result result = MountRom(16, 16, g_hTrlFileWorkingMemory, nSize);
	if(result.IsFailure())
	{
		NN_LOG("MountRom Fail.\n");
		NN_ERR_THROW_FATAL_ALL(result);
	}
	NN_LOG("MountRom Success\n");

#if !TRL_PRODUCTION
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_CHILD
	// Sdmc
	result = MountSdmc();
	if(result.IsFailure())
	{
		NN_LOG("MountSdmc Fail.\n");
		NN_ERR_THROW_FATAL_ALL(result);
	}
	NN_LOG("MountSdmc Success\n");
#endif
#endif
}

/** @brief Format Save Data */
s32 trlFileFormatSaveData()
{
	nn::Result result = FormatSaveData(4, 1, TRL_SAVE_DUPLICATE);
	if(result.IsFailure())
	{
		NN_LOG("FormatSaveData fail.\n");
		NN_ERR_THROW_FATAL_ALL(result);
	}
	NN_LOG("FormatSaveData Success.\n");

	result = MountSaveData();
	if(result.IsFailure())
	{
		NN_LOG("MountSaveData fail.\n");
		NN_ERR_THROW_FATAL_ALL(result);
	}
	NN_LOG("MountSaveData Success\n");
	return TRL_FILE_SUCCESS;
}

/** @brief Mount Save Data */
s32 trlFileMountSaveData()
{
	nn::Result result = MountSaveData();
	if(result.IsFailure())
	{
		if(result <= nn::fs::ResultNotFormatted())
		{
			NN_LOG("MountSaveData NotFormatted: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
			return TRL_FILE_NOTFORMATTED;
		}
		else if(result <= nn::fs::ResultBadFormat())
		{
			NN_LOG("MountSaveData BadFormat: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
			return TRL_FILE_BADFORMAT;
		}
		else if(result <= nn::fs::ResultVerificationFailed())
		{
			NN_LOG("MountSaveData VerificationFailed: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
			return TRL_FILE_VERIFICATIONFAILED;
		}
		else if(result <= nn::fs::ResultOperationDenied())
		{
			NN_LOG("MountSaveData OperationDenied: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
			return TRL_FILE_OPERATIONDENIED;
		}
		else
		{
			NN_LOG("MountSaveData OtherError: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
			NN_ERR_THROW_FATAL_ALL(result);
			return TRL_FILE_OTHERERROR;
		}
	}
	NN_LOG("MountSaveData Success\n");
	return TRL_FILE_SUCCESS;
}

/** @brief Unmount Save Data */
s32 trlFileUnmountSaveData()
{
	nn::Result result = Unmount("data:");
	if(result.IsFailure())
	{
		NN_LOG("Unmount SaveData fail: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
		NN_ERR_THROW_FATAL_ALL(result);
		return TRL_FILE_OTHERERROR;
	}
	NN_LOG("UnmountSaveData Success\n");
	return TRL_FILE_SUCCESS;
}

/** @brief Exit */
void trlFileExit()
{
	CommitSaveData();
	Unmount("data:");
#if !TRL_PRODUCTION
	Unmount("sdmc:");
#endif
	Unmount("rom:");
	trlMemFreeDevice(g_hTrlFileWorkingMemory);
	//remove at CTR_SDK 3.3.0
    //nn::fs::Finalize();
}

/** @brief Get TryXXX() Result */
inline s32 trlFileGetResult(nn::Result& ret)
{
	if(ret <= nn::fs::ResultNotFound())
		return TRL_FILE_NOTFOUND;
	else if(ret <= nn::fs::ResultAlreadyExists())
		return TRL_FILE_ALREADYEXISTS;
	else if(ret <= nn::fs::ResultBadFormat())
		return TRL_FILE_BADFORMAT;
	else if(ret <= nn::fs::ResultVerificationFailed())
		return TRL_FILE_VERIFICATIONFAILED;
	else if(ret <= nn::fs::ResultOperationDenied())
		return TRL_FILE_OPERATIONDENIED;
	else if(ret <= nn::fs::ResultNotEnoughSpace())
		return TRL_FILE_NOTENOUGHSPACE;

	NN_LOG("TryXXX() fail: Level %d, Summary %d, Module %d, Description %d\n", ret.GetLevel(), ret.GetSummary(), ret.GetModule(), ret.GetDescription());
	NN_ERR_THROW_FATAL_ALL(ret);
	return TRL_FILE_OTHERERROR;
}

/** @brief Delete File */
s32 trlFileDelete(const wchar_t* pPathName)
{
	nn::Result ret = TryDeleteFile(pPathName);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Delete File fail.");
		return trlFileGetResult(ret);
	}
	return TRL_FILE_SUCCESS;
}

/** @brief Delete File */
s32 trlFileDelete(const char* pPathName)
{
	nn::Result ret = TryDeleteFile(pPathName);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Delete File fail.");
		return trlFileGetResult(ret);
	}
	return TRL_FILE_SUCCESS;
}

/** @brief Create File */
s32 trlFileCreate(const wchar_t* pPathName, s32 nSize)
{
	nn::Result result = TryCreateFile(pPathName, nSize);
	if(result.IsFailure())
	{
		NN_LOG("Create File fail: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
		NN_ERR_THROW_FATAL_ALL(result);
		return trlFileGetResult(result);
	}
	return TRL_FILE_SUCCESS;
}

/** @brief Create File */
s32 trlFileCreate(const char* pPathName, s32 nSize)
{
	nn::Result result = TryCreateFile(pPathName, nSize);
	NN_LOG("TryCreateFile: Path:%s Size:%d\n", pPathName, nSize);
	if(result.IsFailure())
	{
		NN_LOG("Create File fail: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
		NN_ERR_THROW_FATAL_ALL(result);
		return trlFileGetResult(result);
	}
	return TRL_FILE_SUCCESS;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const wchar_t* pPathName, void* pBuf, s32 nSize, s32 nLimit)
{
	FileReader hFile;
	nn::Result ret = hFile.TryInitialize(pPathName);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	s64 nTrySize = 0;
	ret = hFile.TryGetSize(&nTrySize);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open file fail - TryGetSize.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}

	if(nSize > 0)
	{
		if(nLimit)
		{
			if((s32)nTrySize != nSize)
			{
				hFile.Finalize();
				return TRL_FILE_VERIFICATIONFAILED;
			}
		}
		else
		{
			if((s32)nTrySize > nSize)
				nTrySize = nSize;
		}
	}

	ret = hFile.TryRead(&nSize, pBuf, nTrySize);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open file fail - TryRead.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}
	hFile.Finalize();
	return nSize;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const char* pPathName, void* pBuf, s32 nSize, s32 nLimit)
{
	FileReader hFile;
	nn::Result ret = hFile.TryInitialize(pPathName);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	s64 nTrySize = 0;
	ret = hFile.TryGetSize(&nTrySize);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open file fail - TryGetSize.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}

	if(nSize > 0)
	{
		if(nLimit)
		{
			if((s32)nTrySize != nSize)
			{
				hFile.Finalize();
				return TRL_FILE_VERIFICATIONFAILED;
			}
		}
		else
		{
			if((s32)nTrySize > nSize)
				nTrySize = nSize;
		}
	}

	ret = hFile.TryRead(&nSize, pBuf, nTrySize);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open file fail - TryRead.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}
	hFile.Finalize();
	return nSize;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const wchar_t* pPathName, void** ppBuf)
{
	s32 nSize;
	FileReader hFile;
	nn::Result ret = hFile.TryInitialize(pPathName);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Read file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	s64 nTrySize = 0;
	ret = hFile.TryGetSize(&nTrySize);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Read file fail - TryGetSize.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}

	(*ppBuf) = trlMemAlloc(nTrySize);

	ret = hFile.TryRead(&nSize, *ppBuf, nTrySize);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Read file fail - TryRead.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}
	hFile.Finalize();
	return nSize;
}

/** @brief Read File to Buffer */
s32 trlFileRead(const char* pPathName, void** ppBuf)
{
	s32 nSize;
	FileReader hFile;
	NN_LOG("trlFileRead %s  0x%x  0x%x\n", pPathName, ppBuf, *ppBuf);
	nn::Result ret = hFile.TryInitialize(pPathName);
	if(ret.IsFailure())
	{
		NN_LOG("Read file fail - TryInitialize.");
		TRL_WARN(0, "Read file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	s64 nTrySize = 0;
	ret = hFile.TryGetSize(&nTrySize);
	if(ret.IsFailure())
	{
		NN_LOG("Read file fail - TryGetSize.");
		TRL_WARN(0, "Read file fail - TryGetSize.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}

	NN_LOG("Read file TryRead. nTrySize 0x%x nSize 0x%x,, buf 0x%x", (s32)nTrySize, nSize, ppBuf);
	(*ppBuf) = trlMemAlloc(nTrySize);

	ret = hFile.TryRead(&nSize, *ppBuf, nTrySize);
	NN_LOG("Read file TryRead. nTrySize 0x%x nSize 0x%x,, buf 0x%x", (s32)nTrySize, nSize, ppBuf);
	if(ret.IsFailure())
	{
		NN_LOG("Read file fail - TryRead. nTrySize 0x%x nSize 0x%x,, buf 0x%x", nTrySize, nSize, ppBuf);
		TRL_WARN(0, "Read file fail - TryRead.");
		hFile.Finalize();
		return trlFileGetResult(ret);
	}
	hFile.Finalize();
	return nSize;
}

/** @brief Write Buffer to File */
s32 trlFileWrite(const wchar_t* pPathName, void* pBuf, s32 nSize)
{
	s32 nLen;
	FileWriter hFile;
	nn::Result ret = hFile.TryInitialize(pPathName, true);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Write file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	ret = hFile.TryWrite(&nLen, pBuf, nSize, true);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Write file fail - TryWrite.");
		return trlFileGetResult(ret);
	}

	hFile.Finalize();

	if(wcsncmp(pPathName, L"data:", 5)==0)
		CommitSaveData();
	return nLen;
}

/** @brief Write Buffer to File */
s32 trlFileWrite(const char* pPathName, void* pBuf, s32 nSize)
{
	s32 nLen;
	FileWriter hFile;
	nn::Result ret = hFile.TryInitialize(pPathName, true);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Write file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	ret = hFile.TryWrite(&nLen, pBuf, nSize, true);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Write file fail - TryWrite.");
		return trlFileGetResult(ret);
	}

	hFile.Finalize();

	if(strncmp(pPathName, "data:", 5)==0)
		CommitSaveData();
	return nLen;
}

/** @brief Append Buffer to File */
s32 trlFileAppend(const wchar_t* pPathName, void* pBuf, s32 nSize)
{
	s32 nLen;
	FileWriter hFile;
	nn::Result ret = hFile.TryInitialize(pPathName, true);
	if(ret.IsFailure())
	{		
		TRL_WARN(0, "Append file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	ret = hFile.TrySeek(0, POSITION_BASE_END);
	if(ret.IsFailure())
	{		
		TRL_WARN(0, "Append file fail - TrySeek.");
		return trlFileGetResult(ret);
	}

	ret = hFile.TryWrite(&nLen, pBuf, nSize, true);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Append file fail - TryWrite.");
		return trlFileGetResult(ret);
	}
	hFile.Finalize();
	return nLen;
}

/** @brief Append Buffer to File */
s32 trlFileAppend(const char* pPathName, void* pBuf, int nSize)
{
	s32 nLen;
	FileWriter hFile;
	nn::Result ret = hFile.TryInitialize(pPathName, true);
	if(ret.IsFailure())
	{		
		TRL_WARN(0, "Append file fail - TryInitialize.");
		return trlFileGetResult(ret);
	}

	ret = hFile.TrySeek(0, POSITION_BASE_END);
	if(ret.IsFailure())
	{		
		TRL_WARN(0, "Append file fail - TrySeek.");
		return trlFileGetResult(ret);
	}

	ret = hFile.TryWrite(&nLen, pBuf, nSize, true);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Append file fail - TryWrite.");
		return trlFileGetResult(ret);
	}
	hFile.Finalize();
	return nLen;
}

/** @brief Create Directory */
s32 trlFileCreateDir(const wchar_t* pPathName)
{
	Directory hDir;
	nn::Result ret = hDir.TryInitialize(pPathName);
	if(ret.IsFailure())
	{
		ret = TryCreateDirectory(pPathName);
		if(ret.IsFailure())
			return trlFileGetResult(ret);
	}
	else
		hDir.Finalize();
	return TRL_FILE_SUCCESS;
}

/** @brief Create Directory */
s32 trlFileCreateDir(const char* pPathName)
{
	Directory hDir;
	nn::Result ret = hDir.TryInitialize(pPathName);
	if(ret.IsFailure())
	{
		ret = TryCreateDirectory(pPathName);
		if(ret.IsFailure())
			return trlFileGetResult(ret);
	}
	else
		hDir.Finalize();
	return TRL_FILE_SUCCESS;
}
