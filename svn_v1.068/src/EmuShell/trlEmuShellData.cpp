/**
 * @file trlEmuShellData.cpp
 * @author Chentian
 * @date 2010.03.25
 * @brief TRL Emulate - EmuShell Data Module
 */
#include "trlEmuShellData.h"
#include "trlEmuShellAudio.h"
#include "trlEmuShellVideo.h"
#include "trlEmuShellPatch.h"
#include "trlEmuShellStruct.h"
#include "trlEmuShellNetWork.h"
#include "trlEmuShellSuspend.h"

/** @name Macro Define */
//@{
#define TRL_DATA_RESUME_VER_AGB		0x0000			// TRL Resume File Version Number For AGB
#define TRL_DATA_RESUME_VER_CGB		0x000F			// TRL Resume File Version Number For CGB
#define TRL_DATA_RESUME_VER_NES		0x0003			// TRL Resume File Version Number For NES
#define	TRL_DATA_BUILDTIME_MAX		0x20
//@}

/** @name Global Variable */
//@{
char						g_szEmuShellRom[TRL_DATA_FILENAMEMAX];
char						g_szEmuShellSave[TRL_DATA_FILENAMEMAX];
char						g_szEmuShellResume[2][TRL_DATA_FILENAMEMAX];
char						g_szEmuShellResumeDebug[TRL_DATA_FILENAMEMAX];
char						g_szEmuShellResumeTemp[260];
char						g_szEmuShellResumeList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
char						g_szEmuShellRomList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
char						g_szEmuShellTitleList[TRL_DATA_LISTMAX][TRL_DATA_LISTLEN];
trlSEmuShellResumeInfo		g_sEmuShellResumeInfo;
u32							g_nEmuShellResumeCount								= 0;
u32							g_nEmuShellRomCount									= 0;
u16							g_szEmuShellResumeVer								= 0;				///< TRL Resume File Version Number
u32							g_szEmuShellResumeFlag								= 0x53524354;		///< TRL Resume File Header Flag - "TCRS"
char						g_szEmuShellConfigName[TRL_DATA_PATHNAMEMAX]		= "config.ini";
char						g_szEmuShellPatchExtName[TRL_DATA_PATHNAMEMAX]		= ".patch";
char						g_szEmuShellResumeExtName[TRL_DATA_PATHNAMEMAX]		= ".rsm";
extern char					g_szEmuShellRootPath[TRL_DATA_PATHNAMEMAX];
extern char					g_szEmuShellRomPath[TRL_DATA_PATHNAMEMAX];
extern char					g_szEmuShellSdmcPath[TRL_DATA_PATHNAMEMAX];
extern char					g_szEmuShellDataPath[TRL_DATA_PATHNAMEMAX];
extern char					g_szEmushellBuildTimePath[TRL_DATA_PATHNAMEMAX];

#if TRL_PRODUCTION
const char					g_szEmuShellSaveExtName[TRL_DATA_PATHNAMEMAX]		= "sav.dat";
const char					g_szEmuShellResume1ExtName[TRL_DATA_PATHNAMEMAX]	= "rsm1.dat";
const char					g_szEmuShellResume2ExtName[TRL_DATA_PATHNAMEMAX]	= "rsm2.dat";
#else
const char					g_szEmuShellSaveExtName[TRL_DATA_PATHNAMEMAX]		= ".sav";
const char					g_szEmuShellResume1ExtName[TRL_DATA_PATHNAMEMAX]	= ".rs1";
const char					g_szEmuShellResume2ExtName[TRL_DATA_PATHNAMEMAX]	= ".rs2";
#endif

char						g_szEmuShellBuildTime[TRL_DATA_BUILDTIME_MAX];
//@}

/** @brief EmuShell Data List Rom */
void trlEmuShellDataListRom();
/** @brief EmuShell Data Load Rom */

//Public it for reload ROM.
char g_szPathName[256];

void trlEmuShellDataLoadRom(u32 nIndex)
{
	trlEmuShellDataListRom();
	if(nIndex >= g_nEmuShellRomCount)
	{
		TRL_ERROR("File's index overrange.");
		return;
	}
	sprintf(g_szEmuShellRom, "%s", g_szEmuShellRomList[nIndex]);
	memset(g_szPathName, 0, sizeof(g_szPathName));
	sprintf(g_szPathName, "%s/%s", g_szEmuShellRomPath, g_szEmuShellRom);
	g_sEmuShellBuffer.nRomBufSize = trlFileRead(g_szPathName, &g_sEmuShellBuffer.pRomBuf);
	if(g_sEmuShellBuffer.nRomBufSize==0)
		return;

	// Choice ROM Type
	g_sEmuShellBuffer.nRomType = TRL_EMUTYPE;
	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_UNKNOW:
		// Auto Recognise
		switch(*((u32*)g_sEmuShellBuffer.pRomBuf))
		{
		case 0xEA00002E:
			g_sEmuShellBuffer.nRomType = TRL_EMUCORE_ROMTYPE_AGB;
			g_sEmuShellBuffer.nRomSubType = 0;
			g_szEmuShellResumeVer = TRL_DATA_RESUME_VER_AGB;
			break;
		case 0x53454E54:
			g_sEmuShellBuffer.nRomType = TRL_EMUCORE_ROMTYPE_NES;
			g_sEmuShellBuffer.nRomSubType = 0;
			g_szEmuShellResumeVer = TRL_DATA_RESUME_VER_NES;
			break;
		default:
			g_sEmuShellBuffer.nRomType = TRL_EMUCORE_ROMTYPE_CGB;
			if(((u8*)g_sEmuShellBuffer.pRomBuf)[0x143] & 0x80)
				g_sEmuShellBuffer.nRomSubType = TRL_EMUCORE_GBTYPE_CGB;
			else
				g_sEmuShellBuffer.nRomSubType = TRL_EMUCORE_GBTYPE_DMG;
			g_szEmuShellResumeVer = TRL_DATA_RESUME_VER_CGB;
		}
		break;
	case TRL_EMUCORE_ROMTYPE_CGB:
		if(((u8*)g_sEmuShellBuffer.pRomBuf)[0x143] & 0x80)
			g_sEmuShellBuffer.nRomSubType = TRL_EMUCORE_GBTYPE_CGB;
		else
			g_sEmuShellBuffer.nRomSubType = TRL_EMUCORE_GBTYPE_DMG;
		g_szEmuShellResumeVer = TRL_DATA_RESUME_VER_CGB;
		break;
	case TRL_EMUCORE_ROMTYPE_AGB:
		g_sEmuShellBuffer.nRomSubType = 0;
		g_szEmuShellResumeVer = TRL_DATA_RESUME_VER_AGB;
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
		g_sEmuShellBuffer.nRomSubType = 0;
		g_szEmuShellResumeVer = TRL_DATA_RESUME_VER_NES;
		break;
	}

	// Get Save Name
#if TRL_PRODUCTION
	sprintf(g_szEmuShellSave, "%s/%s", g_szEmuShellDataPath, g_szEmuShellSaveExtName);
	sprintf(g_szEmuShellResume[0], "%s/%s", g_szEmuShellDataPath, g_szEmuShellResume1ExtName);
	sprintf(g_szEmuShellResume[1], "%s/%s", g_szEmuShellDataPath, g_szEmuShellResume2ExtName);
#else
	trlFileCreateDir(g_szEmuShellSdmcPath);
	sprintf(g_szEmuShellResumeDebug, "%s/%s", g_szEmuShellSdmcPath, g_szEmuShellRom);
	sprintf(g_szEmuShellSave, "%s/%.12s%s", g_szEmuShellDataPath, g_szEmuShellRom, g_szEmuShellSaveExtName);
	sprintf(g_szEmuShellResume[0], "%s/%.12s%s", g_szEmuShellDataPath, g_szEmuShellRom, g_szEmuShellResume1ExtName);
	sprintf(g_szEmuShellResume[1], "%s/%.12s%s", g_szEmuShellDataPath, g_szEmuShellRom, g_szEmuShellResume2ExtName);
#endif
}


//used for DiskSystem.
//yuans: reload rom need reload patch file...
void trlEmuShellDataLoadPatch();
void trlEmuShellDataReloadRom(void)
{
	trlMemFree(g_sEmuShellBuffer.pRomBuf);
	if(g_sEmuShellBuffer.nPatchCount)
		trlMemFree(g_sEmuShellBuffer.pPatchData);

	trlFileRead(g_szPathName, &g_sEmuShellBuffer.pRomBuf);
	trlEmuShellDataLoadPatch();
	//g_sEmuShellBuffer.nPatchMask = 0xFFFFFFFF;
	//g_sEmuShellBuffer.nPatchPalette = 0xFFFFFFFF;
	//g_sEmuShellBuffer.nPatchActive = 0;
	//memset(g_sEmuShellBuffer.sPatchActive, 0, sizeof(trlSEmuShellPatchActive)*TRL_EMUCORE_PATCH_ACTIVEMAX);
	return;
}

/** @brief EmuShell Data Load Backup Data */
s32 trlEmuShellDataLoadBackup()
{
//	g_sEmuShellBuffer.nBackupType = TRL_BACKUPTYPE;
	s32 nRet = trlFileRead(g_szEmuShellSave, g_sEmuShellBuffer.pBackupData, g_sEmuShellBuffer.nBackupDataSize);
	if(g_pEmuShellCore->trlEmuCoreSave)
		g_pEmuShellCore->trlEmuCoreSave(0);
	return nRet;
}

/** @brief EmuShell Data Save Backup Data */
s32 trlEmuShellDataSaveBackup()
{
	if(g_sEmuShellBuffer.nBackupDataSize && g_sEmuShellBuffer.bInitFlag)
	{
		if(g_pEmuShellCore->trlEmuCoreSave)
			g_pEmuShellCore->trlEmuCoreSave(1);
		s32 nRet = trlFileWrite(g_szEmuShellSave, g_sEmuShellBuffer.pBackupData, g_sEmuShellBuffer.nBackupDataSize);
		if(nRet<0)
		{
			g_sEmuShellBuffer.nSaveFlag = nRet;
			return nRet;
		}
		g_sEmuShellBuffer.nSaveFlag = 1;
		g_sEmuShellBuffer.nSaveUpdate = 0;
	}
	return TRL_FILE_SUCCESS;
}

/** @brief EmuShell Data Analyse INI File */
void trlEmuShellDataAnalyseINI(const char* pFilename, trlSEmuShellConfig* pConfigData)
{
	for(u32 n=0; n<pConfigData->nCount; ++n)
		for(u32 m=0; m<pConfigData->sSection[n].nCount; ++m)
			if(pConfigData->sSection[n].sValue[m].pValue)
				trlMemFree(pConfigData->sSection[n].sValue[m].pValue);

	memset(pConfigData, 0, sizeof(trlSEmuShellConfig));

	char* pConfig = NULL;
	s32 nSize = trlFileRead(pFilename, (void**)&pConfig);
	if(nSize <= 0)
		return;

	trlSEmuShellConfigSection* pSection = NULL;
	trlSEmuShellConfigValue* pValue = NULL;
	char* pName = NULL;
	u32 nName = 0;
	u32 bValue = 0;
	u32 nState = 0;
	u32 nPara = 0;
	u32 nValue = 0;
	for(s32 n=0; n<nSize; ++n)
	{
		switch(nState)
		{
		case 0:	// Start
			if((pConfig[n] == ' ') || (pConfig[n] == '\t') || (pConfig[n] == '\r') || (pConfig[n] == '\n'))
				continue;
			if((pConfig[n] == '=') || (pConfig[n] == ';'))
			{
				nState = 1;
				continue;
			}
			if(pConfig[n] == '[')
			{
				pSection = &pConfigData->sSection[pConfigData->nCount];
				pName = pSection->szName;
				nName = 0;
				nState = 2;
				continue;
			}
			if(pSection == NULL)
			{
				nState = 1;
				continue;
			}
			pValue = &pSection->sValue[pSection->nCount];
			pName = pValue->szName;
			pName[0] = pConfig[n];
			nName = 1;
			nState = 3;
			break;
		case 1:	// End
			if((pConfig[n] == '\r') || (pConfig[n] == '\n'))
			{
				nState = 0;
				continue;
			}
			break;
		case 2:	// Section
			if(pConfig[n] == ']')
			{
				pSection->nCount = 0;
				nState = 1;
				pConfigData->nCount++;
			}
			else
			{
				if(nName >= TRL_EMUCORE_CONFIG_NAME)
					nState = 1;
				else
				{
					pName[nName] = pConfig[n];
					nName++;
				}
			}
			break;
		case 3:	// Name
			if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
			{
				nState = 4;
				continue;
			}
			if(pConfig[n] == '=')
			{
				nState = 5;
				continue;
			}
			if((pConfig[n] == '\r') || (pConfig[n] == '\n') || (pConfig[n] == ';') || (nName >= TRL_EMUCORE_CONFIG_NAME))
			{
				nState = 1;
				continue;
			}
			pName[nName] = pConfig[n];
			nName++;
			break;
		case 4: // Equal
			if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
				continue;
			if(pConfig[n] == '=')
			{
				nState = 5;
				continue;
			}
			if((pConfig[n] == '\r') || (pConfig[n] == '\n') || (pConfig[n] == ';'))
			{
				nState = 1;
				continue;
			}
			break;
		case 5:	// Dec Value
			if(!bValue)
			{
				if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
					continue;
			}
			if((pConfig[n] == 'x') || (pConfig[n] == 'X'))
			{
				nState = 6;
				continue;
			}
			if((pConfig[n] == 'a') || (pConfig[n] == 'A'))
			{
				nState = 7;
				continue;
			}
			if((pConfig[n] == 'c') || (pConfig[n] == 'C'))
			{
				nState = 9;
				nPara = 0;
				nValue = 0;
				continue;
			}
			if(pConfig[n] >= '0' && pConfig[n] <= '9')
			{
				bValue = 1;
				pValue->nValue = pValue->nValue * 10 + pConfig[n] - 0x30;
				continue;
			}
			if(bValue)
			{
				bValue = 0;
				pSection->nCount++;
			}
			nState = 1;
			break;
		case 6:	// Hex Value
			if(!bValue)
			{
				if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
					continue;
			}
			if(pConfig[n] >= '0' && pConfig[n] <= '9')
			{
				bValue = 1;
				pValue->nValue = pValue->nValue * 16 + pConfig[n] - 0x30;
				continue;
			}
			if(pConfig[n] >= 'A' && pConfig[n] <= 'F')
			{
				bValue = 1;
				pValue->nValue = pValue->nValue * 16 + pConfig[n] - 0x37;
				continue;
			}
			if(pConfig[n] >= 'a' && pConfig[n] <= 'f')
			{
				bValue = 1;
				pValue->nValue = pValue->nValue * 16 + pConfig[n] - 0x57;
				continue;
			}
			if(bValue)
			{
				bValue = 0;
				pSection->nCount++;
			}
			nState = 1;
			break;
		case 7:	// Array Size
			if(!bValue)
			{
				if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
					continue;
			}
			if(pConfig[n] == ':')
			{
				nState = 8;
				nPara = 0;
				nValue = 0;
				bValue = 0;
				pValue->pValue = (u8*)trlMemAlloc(pValue->nValue);
				memset(pValue->pValue, 0, pValue->nValue);
				continue;
			}
			if(pConfig[n] >= '0' && pConfig[n] <= '9')
			{
				bValue = 1;
				pValue->nValue = pValue->nValue * 10 + pConfig[n] - 0x30;
				continue;
			}
			if(bValue)
			{
				bValue = 0;
				pSection->nCount++;
			}
			nState = 1;
			break;
		case 8:	// Array Value
			if(!bValue)
			{
				if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
					continue;
			}

			if(pConfig[n] >= '0' && pConfig[n] <= '9')
			{
				bValue = 2;
				nPara++;
				pValue->pValue[nValue] = pValue->pValue[nValue] * 16 + pConfig[n] - 0x30;
			}
			else if(pConfig[n] >= 'A' && pConfig[n] <= 'F')
			{
				bValue = 2;
				nPara++;
				pValue->pValue[nValue] = pValue->pValue[nValue] * 16 + pConfig[n] - 0x37;
			}
			else if(pConfig[n] >= 'a' && pConfig[n] <= 'f')
			{
				bValue = 2;
				nPara++;
				pValue->pValue[nValue] = pValue->pValue[nValue] * 16 + pConfig[n] - 0x57;
			}
			if(bValue == 2)
			{
				bValue = 1;
				if(nPara == 2)
				{
					bValue = 0;
					nPara = 0;
					nValue++;
					if(nValue >= pValue->nValue)
					{
						bValue = 0;
						pSection->nCount++;
						nState = 1;
					}
				}
				continue;
			}

			if(bValue)
			{
				bValue = 0;
				pSection->nCount++;
			}
			nState = 1;
			break;
		case 9:	// Palette Value
			if(!bValue)
			{
				if((pConfig[n] == ' ') || (pConfig[n] == '\t'))
					continue;
			}
			if(pConfig[n] == ',')
			{
				pValue->nValue |= (nValue & 0x1F) << (11 - nPara*5);
				nPara++;
				nValue = 0;
				continue;
			}
			if(pConfig[n] >= '0' && pConfig[n] <= '9')
			{
				bValue = 1;
				nValue = nValue * 10 + pConfig[n] - 0x30;
				continue;
			}
			if(bValue)
			{
				pValue->nValue |= nValue << (11 - nPara*5);
				pValue->nValue |= 1;
				bValue = 0;
				pSection->nCount++;
			}
			nState = 1;
			break;
		}
	}
	if(bValue)
		pSection->nCount++;

	trlMemFree(pConfig);
}

/** @brief EmuShell Data Load Config File */
void trlEmuShellDataLoadConfig()
{
	g_sEmuShellBuffer.funcConfigData = trlEmuShellDataGetConfigData;
	sprintf(g_szEmuShellResumeTemp, "%s/%s", g_szEmuShellRootPath, g_szEmuShellConfigName);
	trlEmuShellDataAnalyseINI(g_szEmuShellResumeTemp, &g_sEmuShellConfig);
}

/** @brief EmuShell Data Load Config File */
void trlEmuShellDataLoadPatch()
{
	g_sEmuShellBuffer.nPatchCount = 0;

	sprintf(g_szEmuShellResumeTemp, "%s/%s%s", g_szEmuShellRootPath, g_szEmuShellRom, g_szEmuShellPatchExtName);
	trlEmuShellDataAnalyseINI(g_szEmuShellResumeTemp, &g_sEmuShellPatch);
	if(g_sEmuShellPatch.nCount == 0)
		return;
	trlEmuShellPatchLoad();
}

/** @brief EmuShell Data Get Config Data */
u32 trlEmuShellDataGetConfigData(const char* szSection, const char* szValue, u32 nDefault)
{
	for(u32 n=0; n<g_sEmuShellConfig.nCount; ++n)
	{
		if(strcmp(szSection, g_sEmuShellConfig.sSection[n].szName))
			continue;
		for(u32 m=0; m<g_sEmuShellConfig.sSection[n].nCount; ++m)
		{
			if(strcmp(szValue, g_sEmuShellConfig.sSection[n].sValue[m].szName) == 0)
				return g_sEmuShellConfig.sSection[n].sValue[m].nValue;
		}
		break;
	}
	return nDefault;
}

/** @brief EmuShell Data Load BuildTime */
void trlEmuShellDataLoadBuildTime()
{	
	memset(g_szEmuShellBuildTime, 0, TRL_DATA_BUILDTIME_MAX);
	trlFileRead(g_szEmushellBuildTimePath, g_szEmuShellBuildTime);
}

/** @brief EmuShell Data Initialize */
void trlEmuShellDataInit(u32 nIndex)
{
	memset(&g_sEmuShellBuffer, 0, sizeof(trlSEmuShellBuffer));
	memset(&g_sEmuShellConfig, 0, sizeof(trlSEmuShellConfig));
	memset(&g_sEmuShellPatch, 0, sizeof(trlSEmuShellConfig));
	

	trlEmuShellDataLoadRom(nIndex);
	trlEmuShellDataLoadPatch();
	trlEmuShellDataLoadConfig();
	trlEmuShellDataLoadBuildTime();

	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_CGB:
#if ((TRL_EMUTYPE==0) || (TRL_EMUTYPE==1))
		g_pEmuShellCore = &g_sEmuCoreCGB;
		g_sEmuShellBuffer.nWidth = 160;
		g_sEmuShellBuffer.nHeight = 144;
		g_sEmuShellBuffer.nSaveDataSize = 9;
		g_sEmuShellBuffer.nKeyMask = 0xFF;
#endif
		break;
	case TRL_EMUCORE_ROMTYPE_AGB:
#if ((TRL_EMUTYPE==0) || (TRL_EMUTYPE==2))
		g_pEmuShellCore = &g_sEmuCoreAGB;
		g_sEmuShellBuffer.nWidth = 240;
		g_sEmuShellBuffer.nHeight = 160;
		g_sEmuShellBuffer.nSaveDataSize = 0;
		g_sEmuShellBuffer.pSaveData = NULL;
		g_sEmuShellBuffer.nKeyMask = 0xFFFF;
#endif
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
#if ((TRL_EMUTYPE==0) || (TRL_EMUTYPE==3))
		g_pEmuShellCore = &g_sEmuCoreNES;
		g_sEmuShellBuffer.nWidth = 256;
		g_sEmuShellBuffer.nHeight = 240;
		g_sEmuShellBuffer.nSaveDataSize = 7;
	#if TRL_MIC
		g_sEmuShellBuffer.nKeyMask = 0x100000FF;
	#else
		g_sEmuShellBuffer.nKeyMask = 0x000000FF;
	#endif
#endif
		break;
	}
	if(g_sEmuShellBuffer.nSaveDataSize)
		g_sEmuShellBuffer.pSaveData = (trlSEmuShellResume*)trlMemAlloc(sizeof(trlSEmuShellResume)*g_sEmuShellBuffer.nSaveDataSize);
	g_sEmuShellResumeInfo.pCapture = (u16*)trlMemAlloc(TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);
	memset(g_sEmuShellResumeInfo.pCapture, 0, TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);

	g_sEmuShellBuffer.nSaveUpdate = 0;
	g_sEmuShellBuffer.nSaveFlag = 0;

	g_sEmuShellBuffer.nFrames = 0;
	g_sEmuShellBuffer.bFrameDelayEnable = 0;
	g_sEmuShellBuffer.nFrameMark = 0;
	g_sEmuShellBuffer.nFrameDelay = 0;
	g_sEmuShellBuffer.nFrameDouble = 0;
	g_sEmuShellBuffer.nPatchMask = 0xFFFFFFFF;
	g_sEmuShellBuffer.nPatchPalette = 0xFFFFFFFF;
	g_sEmuShellBuffer.nPatchActive = 0;
	memset(g_sEmuShellBuffer.sPatchActive, 0, sizeof(trlSEmuShellPatchActive)*TRL_EMUCORE_PATCH_ACTIVEMAX);

	g_sEmuShellBuffer.nVSyncEnable = TRL_VSYNC;
	g_sEmuShellBuffer.funcSaveBackup = trlEmuShellDataSaveBackup;
	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_NONE;
	g_sEmuShellBuffer.nNetworkErrorState = TRL_NETWORK_ERROR_STATE_NONE;

	g_sEmuShellBuffer.nMotion2Frames = 0;
}

/** @brief EmuShell Data Reset */
void trlEmuShellDataReset()
{
	trlEmuShellAudioStop();

	g_sEmuShellBuffer.nMotion2Frames = 0;

	g_sEmuShellBuffer.bError = 0;
	g_sEmuShellBuffer.nFrames = 0;
	g_sEmuShellBuffer.bFrameDelayEnable = 0;
	g_sEmuShellBuffer.nFrameMark = 0;
	g_sEmuShellBuffer.nFrameDelay = 0;
	g_sEmuShellBuffer.nFrameDouble = 0;
	g_sEmuShellBuffer.nPatchMask = 0xFFFFFFFF;
	g_sEmuShellBuffer.nPatchPalette = 0xFFFFFFFF;
	g_sEmuShellBuffer.nPatchActive = 0;
	g_sEmuShellBuffer.nVCMState = 0;
	memset(g_sEmuShellBuffer.sPatchActive, 0, sizeof(trlSEmuShellPatchActive)*TRL_EMUCORE_PATCH_ACTIVEMAX);

	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_CGB:
	case TRL_EMUCORE_ROMTYPE_AGB:
		{
			g_sEmuShellBuffer.nSaveUpdate = 0;
			g_sEmuShellBuffer.nSaveFlag = 0;
		}
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
		trlEmuShellVideoMaskChangeMode(0);
		break;
	}
	g_pEmuShellCore->trlEmuCoreReset();
	trlEmuShellAudioReset();
}

/** @brief EmuShell Data Resume */
void trlEmuShellDataResume()
{
	trlEmuShellAudioStop();

	g_sEmuShellBuffer.bError = 0;
	g_sEmuShellBuffer.nSaveUpdate = 0;
	g_sEmuShellBuffer.nSaveFlag = 0;
	g_sEmuShellBuffer.nFrames = 0;
	g_sEmuShellBuffer.bFrameDelayEnable = 0;
	g_sEmuShellBuffer.nFrameMark = 0;
	g_sEmuShellBuffer.nFrameDelay = 0;

	g_sEmuShellBuffer.nMotion2Frames = 0;

	g_pEmuShellCore->trlEmuCoreResume();

	trlEmuShellAudioReset();
}

/** @brief EmuShell Data Exit */
void trlEmuShellDataExit()
{
	for(u32 n=0; n<g_sEmuShellConfig.nCount; ++n)
		for(u32 m=0; m<g_sEmuShellConfig.sSection[n].nCount; ++m)
			if(g_sEmuShellConfig.sSection[n].sValue[m].pValue)
				trlMemFree(g_sEmuShellConfig.sSection[n].sValue[m].pValue);
	for(u32 n=0; n<g_sEmuShellPatch.nCount; ++n)
		for(u32 m=0; m<g_sEmuShellPatch.sSection[n].nCount; ++m)
			if(g_sEmuShellPatch.sSection[n].sValue[m].pValue)
				trlMemFree(g_sEmuShellPatch.sSection[n].sValue[m].pValue);

	
	if(g_sEmuShellBuffer.nSaveUpdate)
		trlEmuShellDataSaveBackup();
	trlMemFree(g_sEmuShellBuffer.pRomBuf);
	if(g_sEmuShellBuffer.nPatchCount)
		trlMemFree(g_sEmuShellBuffer.pPatchData);
	if(g_sEmuShellBuffer.nSaveDataSize)
		trlMemFree(g_sEmuShellBuffer.pSaveData);
	trlMemFree(g_sEmuShellResumeInfo.pCapture);
}

/** @brief EmuShell Data Init SaveData */
s32 trlEmuShellDataSaveDataInit(u32 nMount)
{
	g_sEmuShellBuffer.nSaveFileSize = sizeof(trlSEmuShellFileHeader) + sizeof(trlSEmuShellResumeHeader) + g_sEmuShellBuffer.nWidth*g_sEmuShellBuffer.nHeight*2;
	for(u32 m=0; m<g_sEmuShellBuffer.nSaveDataSize; ++m)
	{
		trlSEmuShellResume* pSaveModule = (trlSEmuShellResume*)g_sEmuShellBuffer.pSaveData[m].pValue;
		u32 nSaveModuleSize = g_sEmuShellBuffer.pSaveData[m].nSize;
		for(u32 n=0; n<nSaveModuleSize; ++n)
		{
			if(pSaveModule[n].nSize == 0)
				continue;
			if(pSaveModule[n].nDelVer > 0)
				continue;
			g_sEmuShellBuffer.nSaveFileSize += pSaveModule[n].nSize;
		}
	}
	if(nMount)
		return trlFileMountSaveData();
	return 0;
}

/** @brief EmuShell Data Create SaveData */
s32 trlEmuShellDataSaveDataCreate()
{
	trlEmuShellsuspendFSWait();
	trlFileFormatSaveData();
	s32 nResult = 0;
	if(g_sEmuShellBuffer.nBackupDataSize)
	{
		trlFileCreate(g_szEmuShellSave, g_sEmuShellBuffer.nBackupDataSize);
		nResult = trlFileWrite(g_szEmuShellSave, g_sEmuShellBuffer.pBackupData, g_sEmuShellBuffer.nBackupDataSize);
		if(nResult < 0)
		{
			trlEmuShellsuspendFSRelease();
			return nResult;
		}
	}

	g_sEmuShellBuffer.nVCMMode = eVCMMode_Init;

	u8* pBuffer = (u8*)trlMemAlloc(g_sEmuShellBuffer.nSaveFileSize);
	memset(pBuffer, 0, g_sEmuShellBuffer.nSaveFileSize);
	trlSEmuShellFileHeader* pHeader = (trlSEmuShellFileHeader*)pBuffer;
	pHeader->nFlag = g_szEmuShellResumeFlag;
	pHeader->nVer = g_szEmuShellResumeVer;
	pHeader->nType = g_sEmuShellBuffer.nRomType;
	pHeader->nSize = g_sEmuShellBuffer.nSaveFileSize - sizeof(trlSEmuShellFileHeader);
	pHeader->nCRC = 0;
	
	trlSEmuShellResumeHeader* pResumeHeader = (trlSEmuShellResumeHeader*)(pBuffer + sizeof(trlSEmuShellFileHeader));
	pResumeHeader->nTime = trlTimeGetNow();
	pResumeHeader->nType = TRL_DATA_RESUME_BACKUP;
	pResumeHeader->nEnable = 0;
	pResumeHeader->nVCMMode = g_sEmuShellBuffer.nVCMMode;

	trlFileCreate(g_szEmuShellResume[0], g_sEmuShellBuffer.nSaveFileSize);
	nResult = trlFileWrite(g_szEmuShellResume[0], pBuffer, g_sEmuShellBuffer.nSaveFileSize);
	if(nResult < 0)
	{
		trlMemFree(pBuffer);
		trlEmuShellsuspendFSRelease();
		return nResult;
	}

	pResumeHeader->nType = TRL_DATA_RESUME_SUSPEND;
	trlFileCreate(g_szEmuShellResume[1], g_sEmuShellBuffer.nSaveFileSize);
	nResult = trlFileWrite(g_szEmuShellResume[1], pBuffer, g_sEmuShellBuffer.nSaveFileSize);
	if(nResult < 0)
	{
		trlMemFree(pBuffer);
		trlEmuShellsuspendFSRelease();
		return nResult;
	}

	trlMemFree(pBuffer);
	trlEmuShellsuspendFSRelease();
	return TRL_FILE_SUCCESS;
}

/** @brief EmuShell Data Reset SaveData */
s32 trlEmuShellDataSaveDataReset()
{
	trlFileUnmountSaveData();
	trlEmuShellDataSaveDataCreate();
	return TRL_FILE_SUCCESS;
}

/** @brief EmuShell Data Block Format Convert to Line Format */
void trlEmuShellDataB2LConvert(u32* pBlock, u32* pLine, u32 nWidth, u32 nHeight)
{
	nWidth >>= 1;
	u32* pBlockCur = pBlock;
	for(u32 h=0; h<nHeight; h+=8)
	{
		for(u32 w=0; w<nWidth; w+=4, pBlockCur += 4)
		{
			u32* pBlockCur2 = pBlockCur;
			for(u32 h1=0; h1<2; ++h1)
			{
				for(u32 w1=0; w1<2; ++w1, pBlockCur2 += 2)
				{
					u32* pBlockCur3 = pBlockCur2;
					for(u32 h2=0; h2<2; ++h2)
					{
						for(u32 w2=0; w2<2; ++w2, ++pBlockCur3, pLine+=2)
						{
							pBlockCur3[0] = pLine[0];
							pBlockCur3[nWidth] = pLine[1];
						}
						pBlockCur3 = pBlockCur2 + nWidth*2;
					}
				}
				pBlockCur2 = pBlockCur + nWidth*4;
			}
		}
		pBlockCur = pBlock + nWidth*(h+8);
	}
}

/** @brief EmuShell Data Save Resume Data */
void trlEmuShellDataSaveResumeData(u8* pBuf, u32 nType, u32 bCreate, u32 bCapture)
{
	u8* pCur = pBuf + sizeof(trlSEmuShellFileHeader);

	//add by yuans: for BUG 373. flush the SRAM data before create a instant save file, otherwise the SRAM data isn't saved.
	if(g_pEmuShellCore->trlEmuCoreSave)
			g_pEmuShellCore->trlEmuCoreSave(1);
	//end of add.

	// Write Info
	trlSEmuShellResumeHeader sResumeHeader;
	memset(&sResumeHeader, 0, sizeof(sResumeHeader));
	sResumeHeader.nTime = trlTimeGetNow();
	sResumeHeader.nType = nType;
	sResumeHeader.nEnable = !bCreate;
	sResumeHeader.nVCMMode = g_sEmuShellBuffer.nVCMMode;
	if(TRL_DATA_RESUME_BACKUP == nType)
	{
		g_sEmuShellResumeInfo.nYear = TRL_TIME_GET_YEAR(sResumeHeader.nTime);
		g_sEmuShellResumeInfo.nMonth = TRL_TIME_GET_MONTH(sResumeHeader.nTime);
		g_sEmuShellResumeInfo.nDay = TRL_TIME_GET_DAY(sResumeHeader.nTime);
		g_sEmuShellResumeInfo.nHour = TRL_TIME_GET_HOUR(sResumeHeader.nTime);
		g_sEmuShellResumeInfo.nMinute = TRL_TIME_GET_MINUTE(sResumeHeader.nTime);
		g_sEmuShellResumeInfo.nSecond = TRL_TIME_GET_SECOND(sResumeHeader.nTime);
	}

	trlMemCopy(pCur, &sResumeHeader, sizeof(sResumeHeader));
	pCur += sizeof(sResumeHeader);

	if(bCreate == 0)
	{
		// Write Capture
		u8* pScreenBuf = (u8*)g_sEmuShellBuffer.pScreenBuf;
		u8* pCapture = (u8*)g_sEmuShellResumeInfo.pCapture;
		for(s32 y=0; y<g_sEmuShellBuffer.nHeight; ++y)
		{
			if(bCapture == 1)
			{
				trlMemCopy(pCapture, pScreenBuf+16, g_sEmuShellBuffer.nWidth*2);
				trlMemCopy(pCur, pScreenBuf+16, g_sEmuShellBuffer.nWidth*2);
			}
			else
			{
				memset(pCapture, 0, g_sEmuShellBuffer.nWidth*2);
				memset(pCur, 0, g_sEmuShellBuffer.nWidth*2);
			}
			pScreenBuf += g_sEmuShellBuffer.nTexWidth*2;
			pCapture += g_sEmuShellBuffer.nWidth*2;
			pCur += g_sEmuShellBuffer.nWidth*2;
		}

		// Write Data
		for(u32 m=0; m<g_sEmuShellBuffer.nSaveDataSize; ++m)
		{
			trlSEmuShellResume* pSaveModule = (trlSEmuShellResume*)g_sEmuShellBuffer.pSaveData[m].pValue;
			u32 nSaveModuleSize = g_sEmuShellBuffer.pSaveData[m].nSize;
			for(u32 n=0; n<nSaveModuleSize; ++n)
			{
				if(pSaveModule[n].nSize == 0)
					continue;
				if(pSaveModule[n].nDelVer > 0)
					continue;
				trlMemCopy(pCur, pSaveModule[n].pValue, pSaveModule[n].nSize);
				pCur += pSaveModule[n].nSize;
			}
		}
	}

	// Write Header
	trlSEmuShellFileHeader hHeader;
	hHeader.nFlag = g_szEmuShellResumeFlag;
	hHeader.nVer = g_szEmuShellResumeVer;
	hHeader.nType = g_sEmuShellBuffer.nRomType;
	hHeader.nSize = g_sEmuShellBuffer.nSaveFileSize - sizeof(trlSEmuShellFileHeader);

	// Compress
	// ...

	// CRC
	// ...
	hHeader.nCRC = 0;
	trlMemCopy(pBuf, &hHeader, sizeof(trlSEmuShellFileHeader));
}

/** @brief EmuShell Data Save Resume File */
inline s32 trlEmuShellDataSaveResumeFile(const char* pFileName, u32 nType, u32 bCreate = 0)
{
	if(g_sEmuShellBuffer.nSaveFileSize==0)
		return TRL_FILE_SUCCESS;
	u8* pBuf = (u8*)trlMemAlloc(g_sEmuShellBuffer.nSaveFileSize);
	memset(pBuf, 0, g_sEmuShellBuffer.nSaveFileSize);

	trlEmuShellDataSaveResumeData(pBuf, nType, bCreate);

	s32 nSize = trlFileWrite(pFileName, pBuf, g_sEmuShellBuffer.nSaveFileSize);
	trlMemFree(pBuf);
	return nSize;
}

/** @brief EmuShell Data Load Resume Data */
s32 trlEmuShellDataLoadResumeData(u8* pBuf, u32 nType)
{
	// Read Header
	u32 nVer = 1;
	trlSEmuShellFileHeader* pHeader = (trlSEmuShellFileHeader*)pBuf;
	if(pHeader->nFlag == g_szEmuShellResumeFlag)
	{
		nVer = pHeader->nVer;
		if((pHeader->nType != 0) && (pHeader->nType != g_sEmuShellBuffer.nRomType))
		{
			TRL_WARN(0, "This Resume file emu type error.");
			return 0;
		}
		pBuf += sizeof(trlSEmuShellFileHeader);
	}
	//else
	//{
	//	TRL_DATA_FILE_CLOSE(hFile);
	//	TRL_WARN(0, "This file isn't the TRL Resume file.");
	//	return 0;
	//}

	// CRC
	// ...

	// Decompress
	// ...

	// Skip Info
	u32 nCaptureSize = 0;
	trlSEmuShellResumeHeader* pResumeHeader = NULL;
	if((g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_CGB) && (nVer <= 11))
	{
		if(nVer >= 5)
		{
			if(nVer == 5)
				pBuf += g_sEmuShellBuffer.nWidth*g_sEmuShellBuffer.nHeight*2 + 4;
			else
			{
				pBuf += 4;
				nCaptureSize = g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2;
			}
		}
	}
	else
	{
		pResumeHeader = (trlSEmuShellResumeHeader*)pBuf;
		pBuf += sizeof(trlSEmuShellResumeHeader);
		// Check Type
		if(pResumeHeader->nType != nType)
		{
			TRL_WARN(0, "This Resume file type error.");
			return 0;
		}
		// Check Available
		if(pResumeHeader->nEnable == 0)
		{
			TRL_WARN(0, "This Resume file disable.");
			return 0;
		}
		g_sEmuShellBuffer.nVCMMode = pResumeHeader->nVCMMode;
		if((g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_CGB) && (nVer <= 0xC))
			nCaptureSize = g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2;
		else
			nCaptureSize = g_sEmuShellBuffer.nWidth*g_sEmuShellBuffer.nHeight*2;
	}

	// Load Capture
	if(nCaptureSize)
	{
		if((g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_CGB) && (nVer <= 0xC))
		{
			u8* pDataBuf;
			u32* pTempBuf = NULL;
			if(nVer == 0xC)
				pDataBuf = pBuf;
			else
			{
				pTempBuf = (u32*)trlMemAlloc(g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2);
				trlEmuShellDataB2LConvert(pTempBuf, (u32*)pBuf, 256, 256);
				pDataBuf = (u8*)pTempBuf;
			}

			u8* pScreenBuf = (u8*)g_sEmuShellBuffer.pScreenBuf;
			for(s32 y=0; y<g_sEmuShellBuffer.nHeight; ++y)
			{
				trlMemCopy(pScreenBuf, pDataBuf, g_sEmuShellBuffer.nWidth*2);
				pScreenBuf += g_sEmuShellBuffer.nTexWidth*2;
				pDataBuf += g_sEmuShellBuffer.nTexWidth*2;
			}

			trlMemFree(pTempBuf);

			pBuf += nCaptureSize;
		}
		else
		{
			u8* pScreenBuf = (u8*)g_sEmuShellBuffer.pScreenBuf;
			for(s32 y=0; y<g_sEmuShellBuffer.nHeight; ++y)
			{
				trlMemCopy(pScreenBuf+16, pBuf, g_sEmuShellBuffer.nWidth*2);
				pScreenBuf += g_sEmuShellBuffer.nTexWidth*2;
				pBuf += g_sEmuShellBuffer.nWidth*2;
			}
		}
	}

	// Read Data
	g_sEmuShellBuffer.nPatchMask = 0xFFFFFFFF;
	g_sEmuShellBuffer.nPatchPalette = 0xFFFFFFFF;
	g_sEmuShellBuffer.nPatchActive = 0;
	g_sEmuShellBuffer.nFrameDouble = 0;
	for(u32 m=0; m<g_sEmuShellBuffer.nSaveDataSize; ++m)
	{
		trlSEmuShellResume* pSaveModule = (trlSEmuShellResume*)g_sEmuShellBuffer.pSaveData[m].pValue;
		if(g_sEmuShellBuffer.pSaveData[m].nVer > nVer)
			continue;
		if(g_sEmuShellBuffer.pSaveData[m].nDelVer && (g_sEmuShellBuffer.pSaveData[m].nDelVer <= nVer))
			continue;
		u32 nSaveModuleSize = g_sEmuShellBuffer.pSaveData[m].nSize;
		for(u32 n=0; n<nSaveModuleSize; ++n)
		{
			if(pSaveModule[n].nSize==0)
				continue;
			if(pSaveModule[n].nVer > nVer)
				continue;
			if(pSaveModule[n].nDelVer && (pSaveModule[n].nDelVer <= nVer))
				continue;
			if(pSaveModule[n].pValue)
				trlMemCopy(pSaveModule[n].pValue, pBuf, pSaveModule[n].nSize);
			pBuf += pSaveModule[n].nSize;
		}
	}

	// Set Available Flag
	if(pResumeHeader)
	{
		if(pResumeHeader->nType != TRL_DATA_RESUME_BACKUP)
		{
			pResumeHeader->nEnable = 0;
			return 2;
		}
	}
	return 1;
}

/** @brief EmuShell Data Load Resume File */
inline s32 trlEmuShellDataLoadResumeFile(const char* pFileName, u32 nType)
{
	u8* pBufHeader = NULL;
	s32 nFileSize = trlFileRead(pFileName, (void**)(&pBufHeader));
	if(nFileSize < 0)
		return nFileSize;

	switch(trlEmuShellDataLoadResumeData(pBufHeader, nType))
	{
	case 0:
		nFileSize = 0;
		break;
	case 1:
		break;
	case 2:
		nFileSize = trlFileWrite(pFileName, pBufHeader, nFileSize);
		break;
	}

	trlMemFree(pBufHeader);
	return nFileSize;
}

/** @brief EmuShell Data Check Resume Data */
s32 trlEmuShellDataCheckResumeData(const char* pFileName, u16 nType, u32 bRead)
{
	u8* pBufHeader = NULL;
	s32 nFileSize = trlFileRead(pFileName, (void**)(&pBufHeader));
	if(nFileSize < 0)
		return nFileSize;
	u8* pBuf = pBufHeader;

	// Read Header
	trlSEmuShellFileHeader* pHeader = (trlSEmuShellFileHeader*)pBuf;
	if(pHeader->nFlag != g_szEmuShellResumeFlag)
	{
		trlMemFree(pBufHeader);
		TRL_WARN(0, "This file isn't the TRL Resume file.");
		return 1;
	}
	if((pHeader->nType != 0) && (pHeader->nType != g_sEmuShellBuffer.nRomType))
	{
		trlMemFree(pBufHeader);
		TRL_WARN(0, "This Resume file emu type error.");
		return 1;
	}

	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_CGB)
	{
		if(pHeader->nVer < 5)
		{
			trlMemFree(pBufHeader);
			return TRL_FILE_SUCCESS;
		}
	}
	pBuf += sizeof(trlSEmuShellFileHeader);

	// CRC
	// ...

	// Decompress
	// ...

	// Load Info
	u64 nTime = 0;
	if(pHeader->nVer <= 11 && g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_CGB)
	{
		nTime = (*(u32*)pBuf) << 17;
		pBuf += 4;
	}
	else
	{
		trlSEmuShellResumeHeader* pResumeHeader = (trlSEmuShellResumeHeader*)pBuf;
		pBuf += sizeof(trlSEmuShellResumeHeader);
		nTime = pResumeHeader->nTime;
		// Check Type
		switch(nType)
		{
		case TRL_DATA_RESUME_BACKUP:
			if(pResumeHeader->nType != TRL_DATA_RESUME_BACKUP)
			{
				trlMemFree(pBufHeader);
				TRL_WARN(0, "This file isn't the TRL Backup Resume file.");
				return 1;
			}
			break;
		case TRL_DATA_RESUME_SUSPEND:
			if(pResumeHeader->nType == TRL_DATA_RESUME_BACKUP)
			{
				trlMemFree(pBufHeader);
				TRL_WARN(0, "This file isn't the TRL Suspend Resume file.");
				return 1;
			}
			g_sEmuShellBuffer.nVCMMode = pResumeHeader->nVCMMode;
			break;
		}
		nType = pResumeHeader->nType;
		// Check Available
		if(pResumeHeader->nEnable == 0)
		{
			trlMemFree(pBufHeader);
			TRL_WARN(0, "This Resume file disable.");
			return 1;
		}
	}

	if(bRead)
	{
		memset(g_sEmuShellResumeInfo.pCapture, 0, g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2);
		g_sEmuShellResumeInfo.nWidth = g_sEmuShellBuffer.nWidth;
		g_sEmuShellResumeInfo.nHeight = g_sEmuShellBuffer.nHeight;
		g_sEmuShellResumeInfo.nYear = TRL_TIME_GET_YEAR(nTime);
		g_sEmuShellResumeInfo.nMonth = TRL_TIME_GET_MONTH(nTime);
		g_sEmuShellResumeInfo.nDay = TRL_TIME_GET_DAY(nTime);
		g_sEmuShellResumeInfo.nHour = TRL_TIME_GET_HOUR(nTime);
		g_sEmuShellResumeInfo.nMinute = TRL_TIME_GET_MINUTE(nTime);
		g_sEmuShellResumeInfo.nSecond = TRL_TIME_GET_SECOND(nTime);
		g_sEmuShellResumeInfo.nType = nType;

		// Load Capture
		u32 nCapture;
		if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_CGB)
		{
			if((pHeader->nVer == 5) || (pHeader->nVer >= 0xD))
				nCapture = g_sEmuShellBuffer.nWidth*g_sEmuShellBuffer.nHeight*2;
			else
				nCapture = g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2;

			if(pHeader->nVer == 0xC)
				trlMemCopy(g_sEmuShellResumeInfo.pCapture, pBuf, nCapture);
			else
			{
				u32* pBuffer = (u32*)trlMemAlloc(nCapture);
				trlMemCopy(pBuffer, pBuf, nCapture);
				if(pHeader->nVer < 0xB)
					trlEmuShellDataB2LConvert((u32*)g_sEmuShellResumeInfo.pCapture, pBuffer, 256, 256);
				else
				{
					u8* pCapture = (u8*)g_sEmuShellResumeInfo.pCapture;
					u8* pDataBuf = (u8*)pBuffer;
					for(s32 y=0; y<g_sEmuShellBuffer.nHeight; ++y)
					{
						trlMemCopy(pCapture, pDataBuf, g_sEmuShellBuffer.nWidth*2);
						pCapture += g_sEmuShellBuffer.nTexWidth*2;
						pDataBuf += g_sEmuShellBuffer.nWidth*2;
					}
				}
				trlMemFree(pBuffer);
			}
		}
		else
		{
			nCapture = g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2;
			trlMemCopy(g_sEmuShellResumeInfo.pCapture, pBuf, nCapture);
		}
	}
	trlMemFree(pBufHeader);
	return TRL_FILE_SUCCESS;
}

/** @brief EmuShell Data Save Resume */
s32 trlEmuShellDataSaveResume(u32 nType)
{
	switch(nType)
	{
	case TRL_DATA_RESUME_BACKUP:
		return trlEmuShellDataSaveResumeFile(g_szEmuShellResume[0], nType);
	case TRL_DATA_RESUME_HOME:
	case TRL_DATA_RESUME_SLEEP:
		return trlEmuShellDataSaveResumeFile(g_szEmuShellResume[1], nType);
	}
	return TRL_FILE_OTHERERROR;
}

/** @brief EmuShell Data Load Resume */
s32 trlEmuShellDataLoadResume(u32 nType)
{
	switch(nType)
	{
	case TRL_DATA_RESUME_BACKUP:
		return trlEmuShellDataLoadResumeFile(g_szEmuShellResume[0], nType);
	case TRL_DATA_RESUME_HOME:
	case TRL_DATA_RESUME_SLEEP:
		return trlEmuShellDataLoadResumeFile(g_szEmuShellResume[1], nType);
	}
	return TRL_FILE_OTHERERROR;
}

/** @brief EmuShell Data Check Resume */
s32 trlEmuShellDataCheckResume(u32 nType, u32 bRead)
{
	return trlEmuShellDataCheckResumeData(g_szEmuShellResume[nType], nType, bRead);
}

/** @brief EmuShell Data Delete Resume */
s32 trlEmuShellDataDeleteResume(u32 nType)
{
	if(trlFileDelete(g_szEmuShellResume[nType])==0)
		return 0;

	memset(g_sEmuShellResumeInfo.pCapture, 0, g_sEmuShellBuffer.nTexWidth*g_sEmuShellBuffer.nTexHeight*2);
	g_sEmuShellResumeInfo.nYear = 0;
	g_sEmuShellResumeInfo.nMonth = 0;
	g_sEmuShellResumeInfo.nDay = 0;
	g_sEmuShellResumeInfo.nHour = 0;
	g_sEmuShellResumeInfo.nMinute = 0;
	g_sEmuShellResumeInfo.nSecond = 0;
	g_sEmuShellResumeInfo.nType = 0;
	return 1;
}

/** @brief EmuShell Data Disable Resume */
s32 trlEmuShellDataDisableResume()
{
	u8* pBufHeader = NULL;
	s32 nFileSize = trlFileRead(g_szEmuShellResume[1], (void**)(&pBufHeader));
	if(nFileSize < 0)
		return nFileSize;
	u16* pFlag = (u16*)(pBufHeader + sizeof(trlSEmuShellFileHeader) + 10);
	*pFlag = 0;
	nFileSize = trlFileWrite(g_szEmuShellResume[1], pBufHeader, nFileSize);
	trlMemFree(pBufHeader);
	return nFileSize;
}

/** @brief EmuShell Data Update Resume */
s32 trlEmuShellDataUpdateResume()
{
	u8* pBufHeader = NULL;
	s32 nFileSize = trlFileRead(g_szEmuShellResume[1], (void**)(&pBufHeader));
	if(nFileSize < 0)
		return nFileSize;
	u16* pFlag = (u16*)(pBufHeader + sizeof(trlSEmuShellFileHeader) + 12);
	*pFlag = g_sEmuShellBuffer.nVCMMode;
	nFileSize = trlFileWrite(g_szEmuShellResume[1], pBufHeader, nFileSize);
	trlMemFree(pBufHeader);
	return nFileSize;
}

/** @brief EmuShell Data Load Resume for Debug */
u32 trlEmuShellDataLoadResumeDebug(s32 nIndex)
{
	nIndex = g_nEmuShellResumeCount - nIndex - 1;
	sprintf(g_szEmuShellResumeTemp, "%s_%s%s", g_szEmuShellResumeDebug, g_szEmuShellResumeList[nIndex], g_szEmuShellResumeExtName);
	return trlEmuShellDataLoadResumeFile(g_szEmuShellResumeTemp, 0);
}

/** @brief EmuShell Data Save Resume for Debug */
u32 trlEmuShellDataSaveResumeDebug()
{
	u64 nTime = trlTimeGetNow();
	s32 nYear = TRL_TIME_GET_YEAR(nTime);
	s32 nMonth = TRL_TIME_GET_MONTH(nTime);
	s32 nDay = TRL_TIME_GET_DAY(nTime);
	s32 nHour = TRL_TIME_GET_HOUR(nTime);
	s32 nMin = TRL_TIME_GET_MINUTE(nTime);
	s32 nSec = TRL_TIME_GET_SECOND(nTime);
	sprintf(g_szEmuShellResumeTemp, "%s_%04d%02d%02d-%02d'%02d'%02d%s", g_szEmuShellResumeDebug, nYear, nMonth, nDay, nHour, nMin, nSec, g_szEmuShellResumeExtName);
	return trlEmuShellDataSaveResumeFile(g_szEmuShellResumeTemp, 0);
}

/** @brief EmuShell Data Delete Resume for Debug */
u32 trlEmuShellDataDeleteResumeDebug(s32 nIndex)
{
	nIndex = g_nEmuShellResumeCount - nIndex - 1;
	sprintf(g_szEmuShellResumeTemp, "%s_%s%s", g_szEmuShellResumeDebug, g_szEmuShellResumeList[nIndex], g_szEmuShellResumeExtName);
	return trlFileDelete(g_szEmuShellResumeTemp);
}

/** @brief EmuShell Data Get Resume List Count for Debug */
s32 trlEmuShellDataGetResumeListCountDebug()
{
	return g_nEmuShellResumeCount;
}

/** @brief EmuShell Data Get Resume List Filename for Debug */
char* trlEmuShellDataGetResumeListFileDebug(s32 nIndex)
{
	return g_szEmuShellResumeList[g_nEmuShellResumeCount - nIndex - 1];
}

/** @brief EmuShell Data Get Rom List Count for Debug */
s32 trlEmuShellDataGetRomListCountDebug()
{
	return g_nEmuShellRomCount;
}

/** @brief EmuShell Data Get Rom List Filename for Debug */
char* trlEmuShellDataGetRomListFileDebug(s32 nIndex)
{
	return g_szEmuShellTitleList[g_nEmuShellRomCount - nIndex - 1];
}
