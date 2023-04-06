/**
 * @file trlEmuShellData_CTR.cpp
 * @author Chentian
 * @date 2010.08.26
 * @brief TRL Emulate For CTR - EmuShell Data Module
 */
#pragma diag_suppress 177
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellStruct.h"
#include <nn\os.h>
#include <nn\fs.h>
#include <nn\fnd.h>
#include <nn\snd.h>
#include <nn\ndm.h>
using namespace nn::os;
using namespace nn::fs;
using namespace nn::fnd;
using namespace nn::snd;

/** @name Global Variable */
//@{
char					g_szEmuShellRootPath[TRL_DATA_PATHNAMEMAX]			= "rom:";
char					g_szEmuShellRomPath[TRL_DATA_PATHNAMEMAX]			= "rom:/rom";
char					g_szEmuShellSdmcPath[TRL_DATA_PATHNAMEMAX]			= "sdmc:/save";
char					g_szEmuShellDataPath[TRL_DATA_PATHNAMEMAX]			= "data:";
char					g_szEmushellBuildTimePath[TRL_DATA_PATHNAMEMAX]		= "rom:/buildtime.txt";
extern char				g_szEmuShellResumeExtName[TRL_DATA_PATHNAMEMAX];
extern u32				g_nEmuShellResumeCount;
extern u32				g_nEmuShellRomCount;
extern char				g_szEmuShellRom[TRL_DATA_FILENAMEMAX];
extern char				g_szEmuShellResumeTemp[260];
extern char				g_szEmuShellResumeDebug[TRL_DATA_FILENAMEMAX];
extern char				g_szEmuShellResumeList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
extern char				g_szEmuShellRomList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
extern char				g_szEmuShellTitleList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
extern Thread			g_hTrlEmuShellSaveThread;
extern DirectoryEntry	g_hTrlFileEntry[TRL_FILE_ENTRY];
Thread					g_hEmuShellSaveThread;
Event					g_hEmuShellSaveEvent;
u32						g_bEmuShellSaveThread;
//@}

/** @brief EmuShell Save Thread Function */
void trlEmuShellDataSaveThreadFunc()
{
	while(g_bEmuShellSaveThread)
	{
		g_hEmuShellSaveEvent.Wait();
		if(!g_bEmuShellSaveThread)
			break;
		Thread::Sleep(nn::fnd::TimeSpan::FromSeconds(3));
		trlEmuShellDataSaveBackup();
		for(u32 n=0; n<g_sEmuShellBuffer.nSaveTime; ++n)
		{
			if(!g_bEmuShellSaveThread)
				break;
			Thread::Sleep(nn::fnd::TimeSpan::FromSeconds(1));
		}
	};
	trlEmuShellDataSaveBackup();
}

/** @brief EmuShell Data Init Auto Save */
void trlEmuShellDataInitAutoSave()
{
	nn::ndm::Initialize();
	if(g_sEmuShellBuffer.nBackupDataSize)
	{
		if(g_sEmuShellBuffer.nBackupDataSize > 0x8000)
			g_sEmuShellBuffer.nSaveTime = trlEmuShellDataGetConfigData("Save", "Interval1", 240);
		else
			g_sEmuShellBuffer.nSaveTime = trlEmuShellDataGetConfigData("Save", "Interval0", 60);

		g_bEmuShellSaveThread = 1;
		g_hEmuShellSaveEvent.Initialize(false);
		g_hEmuShellSaveThread.StartUsingAutoStack(trlEmuShellDataSaveThreadFunc, 4096, 20);
	}
	else
		nn::ndm::Resume(nn::ndm::CTR::DN_BOSS);
}

/** @brief EmuShell Data Update Auto Save */
void trlEmuShellDataUpdateAutoSave()
{
	if(g_sEmuShellBuffer.nSaveUpdate == 1)
	{
		g_sEmuShellBuffer.nSaveUpdate = 3;
		g_hEmuShellSaveEvent.Signal();
	}
}

/** @brief EmuShell Data Exit Auto Save */
void trlEmuShellDataExitAutoSave()
{
	if(g_hEmuShellSaveThread.IsAlive())
	{
		if(g_sEmuShellBuffer.nBackupDataSize)
		{
			g_bEmuShellSaveThread = 0;
			g_hEmuShellSaveEvent.Signal();
			g_hEmuShellSaveThread.Join();
			g_hEmuShellSaveThread.Finalize();
			g_hEmuShellSaveEvent.Finalize();
		}
	}
	nn::ndm::Finalize();
}

/** @brief EmuShell Data List Rom */
void trlEmuShellDataListRom()
{
	g_nEmuShellRomCount = 0;
	Directory hDir;
	nn::Result ret = hDir.TryInitialize(g_szEmuShellRomPath);
	if(ret.IsFailure())
	{
		TRL_WARN(0, "Open path fail.");
		return;
	}

	s32 nEntry = 0;
	char szTempName[256];
	u8 pBuf[512];
	do{
		nEntry = hDir.Read(g_hTrlFileEntry, TRL_FILE_ENTRY);
		for(s32 n=0; n<nEntry; ++n)
		{
			if(g_hTrlFileEntry[n].attributes.isDirectory)
				continue;
			wcstombs(szTempName, g_hTrlFileEntry[n].entryName, g_hTrlFileEntry[n].entrySize);
			strncpy(g_szEmuShellRomList[g_nEmuShellRomCount], szTempName, strlen(szTempName));
			sprintf(szTempName, "%s/%s", g_szEmuShellRomPath, g_szEmuShellRomList[g_nEmuShellRomCount]);

			if(trlFileRead(szTempName, pBuf, 512, 0)<0)
				continue;

			// Auto Recognise
			switch(*((u32*)pBuf))
			{
			case 0xEA00002E:	// AGB
				sprintf(g_szEmuShellTitleList[g_nEmuShellRomCount], "%s-AGB", g_szEmuShellRomList[g_nEmuShellRomCount]);
				break;
			case 0x53454E54:	// NES
				sprintf(g_szEmuShellTitleList[g_nEmuShellRomCount], "%s-HVC", g_szEmuShellRomList[g_nEmuShellRomCount]);
				break;
			default:			// CGB
				strncpy(szTempName, (const char*)&pBuf[0x134], 0x11);
				szTempName[0x11] = 0;
				sprintf(g_szEmuShellTitleList[g_nEmuShellRomCount], "%s-%s", g_szEmuShellRomList[g_nEmuShellRomCount], szTempName);
			}

			g_nEmuShellRomCount++;
			if(g_nEmuShellRomCount>=TRL_DATA_LISTMAX)
			{
				hDir.Finalize();
				return;
			}
		}
	}while(nEntry);
	hDir.Finalize();
}

/** @brief EmuShell Data List Resume for Debug */
void trlEmuShellDataListResumeDebug()
{
	g_nEmuShellResumeCount = 0;
	Directory hDir;
	nn::Result ret = hDir.TryInitialize(g_szEmuShellSdmcPath);
	if(!ret.IsSuccess())
	{
		TRL_WARN(0, "Open path fail.");
		return;
	}

	sprintf(g_szEmuShellResumeTemp, "%s_", g_szEmuShellRom);
	s32 nResumeLen = strlen(g_szEmuShellResumeTemp);

	s32 nEntry = 0;
	char szTempName[128];

	do{
		nEntry = hDir.Read(g_hTrlFileEntry, TRL_FILE_ENTRY);
		for(s32 n=0; n<nEntry; ++n)
		{
			if(g_hTrlFileEntry[n].attributes.isDirectory)
				continue;
			wcstombs(szTempName, g_hTrlFileEntry[n].entryName, g_hTrlFileEntry[n].entrySize);
			if(strncmp(szTempName, g_szEmuShellResumeTemp, nResumeLen))
				continue;
			u32 nLen = strlen(&szTempName[nResumeLen])-4;
			strncpy(g_szEmuShellResumeList[g_nEmuShellResumeCount], &szTempName[nResumeLen], nLen);
			g_szEmuShellResumeList[g_nEmuShellResumeCount][nLen] = 0;
			g_nEmuShellResumeCount++;
			if(g_nEmuShellResumeCount>=TRL_DATA_LISTMAX)
			{
				hDir.Finalize();
				return;
			}
		}
	}while(nEntry);
	hDir.Finalize();
}
