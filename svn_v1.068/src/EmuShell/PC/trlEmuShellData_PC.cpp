/**
 * @file trlEmuShellData_PC.cpp
 * @author Chentian
 * @date 2010.08.26
 * @brief TRL Emulate For PC - EmuShell Data Module
 */
#include "..\trlEmuShellData.h"

/** @name Global Variable */
//@{
char			g_szEmuShellRootPath[TRL_DATA_PATHNAMEMAX]			= "../files";
char			g_szEmuShellRomPath[TRL_DATA_PATHNAMEMAX]			= "../files/rom";
char			g_szEmuShellSdmcPath[TRL_DATA_PATHNAMEMAX]			= "../save";
char			g_szEmuShellDataPath[TRL_DATA_PATHNAMEMAX]			= "../save";
char			g_szEmushellBuildTimePath[TRL_DATA_PATHNAMEMAX]		= "../files/buildtime.txt";
extern char		g_szEmuShellResumeExtName[TRL_DATA_PATHNAMEMAX];
extern char		g_szEmuShellRom[TRL_DATA_FILENAMEMAX];
extern char		g_szEmuShellResumeDebug[TRL_DATA_FILENAMEMAX];
extern char		g_szEmuShellResumeList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
extern char		g_szEmuShellRomList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
extern char		g_szEmuShellTitleList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
extern u32		g_nEmuShellResumeCount;
extern u32		g_nEmuShellRomCount;
//@}

/** @brief EmuShell Data Update Auto Save */
void trlEmuShellDataUpdateAutoSave()
{
}

/** @brief EmuShell Data List Rom */
void trlEmuShellDataListRom()
{
	g_nEmuShellResumeCount = 0;
	g_nEmuShellRomCount = 0;
	char szPathName[MAX_PATH];
	sprintf(szPathName, "%s/*.*", g_szEmuShellRomPath);
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(szPathName, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
		return;

	char szTempName[256];
	u8 pBuf[512];
	do{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		strncpy(g_szEmuShellRomList[g_nEmuShellRomCount], ffd.cFileName, strlen(ffd.cFileName));
		sprintf(szTempName, "%s/%s", g_szEmuShellRomPath, g_szEmuShellRomList[g_nEmuShellRomCount]);
		trlFileRead(szTempName, pBuf, 512, 0);

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
			FindClose(hFind);
			return;
		}
	}while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
}

/** @brief EmuShell Data List Resume for Debug */
void trlEmuShellDataListResumeDebug()
{
	g_nEmuShellResumeCount = 0;
	char szPathName[MAX_PATH];
	sprintf(szPathName, "%s_*%s", g_szEmuShellResumeDebug, g_szEmuShellResumeExtName);
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(szPathName, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
		return;

	s32 nResumeLen = strlen(g_szEmuShellRom) + 1;
	do{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		u32 nLen = strlen(&ffd.cFileName[nResumeLen])-4;
		strncpy(g_szEmuShellResumeList[g_nEmuShellResumeCount], &ffd.cFileName[nResumeLen], nLen);
		g_szEmuShellResumeList[g_nEmuShellResumeCount][nLen] = 0;
		g_nEmuShellResumeCount++;
		if(g_nEmuShellResumeCount>=TRL_DATA_LISTMAX)
		{
			FindClose(hFind);
			return;
		}
	}while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
}
