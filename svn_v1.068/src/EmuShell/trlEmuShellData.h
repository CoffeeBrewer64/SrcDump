/**
 * @file trlEmuShellData.h
 * @author Chentian
 * @date 2010.03.25
 * @brief TRL Emulate - EmuShell Data Module
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
#define TRL_DATA_LISTMAX			256
#define TRL_DATA_LISTLEN			128
#define TRL_DATA_FILENAMEMAX		128
#define TRL_DATA_PATHNAMEMAX		32

#define TRL_DATA_RESUME_BACKUP		0
#define TRL_DATA_RESUME_SUSPEND		1
#define TRL_DATA_RESUME_HOME		1
#define TRL_DATA_RESUME_SLEEP		2

enum EVCMMode
{
	eVCMMode_Normal = 0,
	eVCMMode_Advance,
	eVCMMode_Init
};
//@}

/** @brief EmuShell Data Initialize */
void trlEmuShellDataInit(u32 nIndex = 0);
/** @brief EmuShell Data Reset */
void trlEmuShellDataReset();
/** @brief EmuShell Data Resume */
void trlEmuShellDataResume();
/** @brief EmuShell Data Exit */
void trlEmuShellDataExit();
/** @brief EmuShell Data Init SaveData */
s32 trlEmuShellDataSaveDataInit(u32 nMount = 1);
/** @brief EmuShell Data Create SaveData */
s32 trlEmuShellDataSaveDataCreate();
/** @brief EmuShell Data Reset SaveData */
s32 trlEmuShellDataSaveDataReset();
/** @brief EmuShell Data Load Config File */
u32 trlEmuShellDataGetConfigData(const char* szSection, const char* szValue, u32 nDefault = 0);
/** @brief EmuShell Data Load Resume Data */
s32 trlEmuShellDataLoadResumeData(u8* pBuf, u32 nType);
/** @brief EmuShell Data Save Resume Data */
void trlEmuShellDataSaveResumeData(u8* pBuf, u32 nType, u32 bCreate = 0, u32 bCapture = 1);
/** @brief EmuShell Data Save Resume */
s32 trlEmuShellDataSaveResume(u32 nType);
/** @brief EmuShell Data Load Resume */
s32 trlEmuShellDataLoadResume(u32 nType);
/** @brief EmuShell Data Check Resume */
s32 trlEmuShellDataCheckResume(u32 nType, u32 bRead = 1);
/** @brief EmuShell Data Delete Resume */
s32 trlEmuShellDataDeleteResume(u32 nType);
/** @brief EmuShell Data Disable Resume */
s32 trlEmuShellDataDisableResume();
/** @brief EmuShell Data Update Resume */
s32 trlEmuShellDataUpdateResume();
/** @brief EmuShell Data Load Backup Data */
s32 trlEmuShellDataLoadBackup();
/** @brief EmuShell Data Save Backup Data */
s32 trlEmuShellDataSaveBackup();
/** @brief EmuShell Data Init Auto Save */
void trlEmuShellDataInitAutoSave();
/** @brief EmuShell Data Update Auto Save */
void trlEmuShellDataUpdateAutoSave();
/** @brief EmuShell Data Exit Auto Save */
void trlEmuShellDataExitAutoSave();

/** @brief EmuShell Data Save Resume for Debug */
u32 trlEmuShellDataSaveResumeDebug();
/** @brief EmuShell Data Load Resume for Debug */
u32 trlEmuShellDataLoadResumeDebug(s32 nIndex);
/** @brief EmuShell Data Delete Resume for Debug */
u32 trlEmuShellDataDeleteResumeDebug(s32 nIndex);

/** @brief EmuShell Data List Resume for Debug */
void trlEmuShellDataListResumeDebug();
/** @brief EmuShell Data Get Resume List Count for Debug */
s32 trlEmuShellDataGetResumeListCountDebug();
/** @brief EmuShell Data Get Resume List Filename for Debug */
char* trlEmuShellDataGetResumeListFileDebug(s32 nIndex);

/** @brief EmuShell Data Get Rom List Count for Debug */
s32 trlEmuShellDataGetRomListCountDebug();
/** @brief EmuShell Data Get Rom List Filename for Debug */
char* trlEmuShellDataGetRomListFileDebug(s32 nIndex);

//used for DiskSystem.
void trlEmuShellDataReloadRom(void);

