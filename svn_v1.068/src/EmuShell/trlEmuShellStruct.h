/**
 * @file trlEmuShellStruct.h
 * @author zhfang & chentian
 * @date 2009.11.24
 * @brief TRL Emulate - EmuShell Struct
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
#define TRL_EMUCORE_ROMTYPE_UNKNOW		0
#define TRL_EMUCORE_ROMTYPE_CGB			1
#define TRL_EMUCORE_ROMTYPE_AGB			2
#define TRL_EMUCORE_ROMTYPE_NES			3

#define TRL_EMUCORE_GBTYPE_DMG			1
#define TRL_EMUCORE_GBTYPE_CGB			2

#define TRL_EMUCORE_NETWORK_PASSLEN		12
#define TRL_EMUCORE_NETWORK_BUFSIZE		8

#define TRL_EMUCORE_TEX_X				512							///< TRL Texture Size - Y
#define TRL_EMUCORE_TEX_Y				256							///< TRL Texture Size - X

#define TRL_EMUCORE_SNDBUF				(512*4*4*4)					///< TRL Sound Buffer

#define TRL_EMUCORE_CONFIG_NAME			31							///< Config Name Length
#define TRL_EMUCORE_CONFIG_NAMEMAX		32							///< Config Name Max Length
#define TRL_EMUCORE_CONFIG_SECT			32							///< Config Section Max Count
#define TRL_EMUCORE_CONFIG_VALUE		48							///< Config Value Max Count

#define TRL_EMUCORE_PATCH_PALMAX		16							///< Patch Palette Max Count
#define TRL_EMUCORE_PATCH_ACTIVEMAX		8							///< Patch Active Max Count
#define TRL_EMUCORE_PATCH_DATAMAX		28							///< Patch Data Max Count
//@}

/**
 * @struct trlSEmuShellFileHeader
 * @brief Emulate Shell File Header Info
 */
struct trlSEmuShellFileHeader
{
	u32							nFlag;								///< File Flag
	u16							nVer;								///< File Version Number
	u16							nType;								///< File Emulator Type
	u32							nSize;								///< File Size
	u32							nCRC;								///< File Check Value
};

/**
 * @struct trlSEmuShellResumeHeader
 * @brief Emulate Shell Resume Header Struct
 */
struct trlSEmuShellResumeHeader
{
	u64							nTime;								///< Time
	u16							nType;								///< Type
	u16							nEnable;							///< Available Flag
	u16							nVCMMode;							///< VCM Mode
	u16							nPadding0;							///< Padding 0
	u64							nPadding1;							///< Padding 1
	u64							nPadding2;							///< Padding 2
};

/**
 * @struct trlSEmuShellVideoMask
 * @brief Emulate Shell Video Mask Data
 */
struct trlSEmuShellVideoMask
{
	u32							nMode;								///< Mode
	u32							bDarkEnable[2];						///< Dark Enable
	u32							bReduceEnable[2];					///< Reduce Color Enable
	u32							bMotionBEnable[2];					///< MotionBlur Enable
	u32							nDark[2];							///< Dark Value
	u32							nReduceColorR[2];					///< Reduce Red Color
	u32							nReduceColorG[2];					///< Reduce Green Color
	u32							nReduceColorB[2];					///< Reduce Blue Color
	u32							nMotionBlur[2];						///< MotionBlur Value

	u32*						pDarkEnable;						///< Dark Enable Current Pointer
	u32*						pReduceEnable;						///< Reduce Color Enable Current Pointer
	u32*						pMotionBEnable;						///< MotionBlur Enable Current Pointer
	u32*						pDark;								///< Dark Value Current Pointer
	u32*						pReduceColorR;						///< Reduce Red Color Current Pointer
	u32*						pReduceColorG;						///< Reduce Green Color Current Pointer
	u32*						pReduceColorB;						///< Reduce Blue Color Current Pointer
	u32*						pMotionBlur;						///< MotionBlur Value Current Pointer
};

/**
 * @struct trlSEmuShellPatchData
 * @brief Emulate Shell Patch Data
 */
union trlSEmuShellPatchData
{
	struct
	{
		u32							nMode;								///< Mode
		u32							nType;								///< Type
		u32							nIndex;								///< Index
		u32							nAddress;							///< ROM Address
		u32							nMemAddress;						///< RAM Address
		u32							nFixcode;							///< Patch Code
		u32							nDelayFrame;						///< Delay Frame
		u32							nFadeFrame;							///< Fade Frame
		u32							bDarkEnable[2];						///< Dark Enable
		u32							bReduceEnable[2];					///< Reduce Color Enable
		u32							bMotionBEnable[2];					///< MotionBlur Enable
		u32							nDark[2];							///< Dark Value
		u32							nReduceColorR[2];					///< Reduce Red Color
		u32							nReduceColorG[2];					///< Reduce Green Color
		u32							nReduceColorB[2];					///< Reduce Blue Color
		u32							nMotionBlur[2];						///< MotionBlur Value
		u32							nConditionType;
		u32							nConditionValueA;
		u32							nConditionValueB;
		u32							nConditionValueC;
	}							sA;

	u32							nD[TRL_EMUCORE_PATCH_DATAMAX];			///< Data
};

/**
 * @struct trlSEmuShellPatch
 * @brief Emulate Shell Patch Data
 */
struct trlSEmuShellPatch
{
	u32							nOpcode;							///< Opcode
	trlSEmuShellPatchData		sData;								///< Data
	u32							nValue;								///< Value
	u8*							pFixcode;							///< Patch Code Array
	u8*							pConditionValueA;
	u8*							pConditionValueB;
	u8*							pConditionValueC;
	u32							nPalette[TRL_EMUCORE_PATCH_PALMAX];	///< Palette
};

/**
 * @class trlSEmuShellPatchActive
 * @brief Emulate Shell Active Patch Data
 */
struct trlSEmuShellPatchActive
{
	/** @brief Clear Data */
	inline void Clear() { nIndex = nDelay = nMode = nFade = nValue = 0; }

	u16							nIndex;								///< Index
	u16							nDelay;								///< Current Delay Frame
	u16							nMode;								///< Mode
	u16							nFade;								///< Current Fade Frame
	u32							nValue;								///< Value
};

/**
 * @struct trlSEmuShellConfigValue
 * @brief Emulate Shell Value Data
 */
struct trlSEmuShellConfigValue
{
	char						szName[TRL_EMUCORE_CONFIG_NAMEMAX];	///< Name
	u32							nValue;								///< Value
	u8*							pValue;								///< Value Array
};

/**
 * @struct trlSEmuShellConfigSection
 * @brief Emulate Shell Config Section Data
 */
struct trlSEmuShellConfigSection
{
	char						szName[TRL_EMUCORE_CONFIG_NAMEMAX];	///< Name
	u32							nCount;								///< Value Count
	trlSEmuShellConfigValue		sValue[TRL_EMUCORE_CONFIG_VALUE];	///< Value Data
};

/**
 * @struct trlSEmuShellConfig
 * @brief Emulate Shell Config Data
 */
struct trlSEmuShellConfig
{
	u32							nCount;								///< Section Count
	trlSEmuShellConfigSection	sSection[TRL_EMUCORE_CONFIG_SECT];	///< Section Data
};

/**
 * @struct trlSEmuShellResume
 * @brief Emulate Shell Resume Data Struct
 */
struct trlSEmuShellResume
{
	/** @brief Set Data */
	inline void SetData(void* _pValue, u32 _nSize, u32 _nVer, u32 _nDelVer)
	{
		pValue = _pValue;
		nSize = _nSize;
		nVer = _nVer;
		nDelVer = _nDelVer;
	}
	void*						pValue;								///< Value
	u32							nSize;								///< Value Size
	u32							nVer;								///< Create Version
	u32							nDelVer;							///< Delete Version
};

/**
 * @struct trlSEmuShellResumeInfo
 * @brief Emulate Shell Resume Info Struct
 */
struct trlSEmuShellResumeInfo
{
	u16*						pCapture;							///< Capture
	u32							nWidth;								///< Capture Width
	u32							nHeight;							///< Capture Height
	u32							nYear;								///< Year
	u32							nMonth;								///< Month
	u32							nDay;								///< Day
	u32							nHour;								///< Hour
	u32							nMinute;							///< Minute
	u32							nSecond;							///< Second
	u32							nType;								///< Resume Type
};

/**
 * @class trlSEmuShellTTPHeader
 * @brief Emulate Shell TTP File Header
 */
struct trlSEmuShellTTPHeader
{
	u32							nFlag;
	u32							nCount;
	u32							nPadding0;
	u32							nPadding1;
};

/**
 * @class trlSEmuShellTTPSegment
 * @brief Emulate Shell TTP File Segment
 */
struct trlSEmuShellTTPSegment
{
	u32							nFormatLength;
	u16							nWidth;
	u16							nHeight;
	u16							nOffsetX;
	u16							nOffsetY;
	u16							nSizeX;
	u16							nSizeY;
};

/**
 * @class trlSEmuShellTexData
 * @brief Emulate Shell Texture Data
 */
struct trlSEmuShellTexData
{
	u32							nFormat;
	u32							nLength;
	u16							nWidth;
	u16							nHeight;
	u16							nX0;
	u16							nY0;
	u16							nX1;
	u16							nY1;
	void*						pData;
};

/**
 * @struct trlSEmuShellNetworkBuffer
 * @brief Emulate Engine Network Buffer Data
 */
#define TRL_NETWORK_BUF_LENGTH 8
struct trlSEmuShellNetworkBuffer
{
	s32							nIndex;												///< Data Index
	u8							nInput[TRL_NETWORK_BUF_LENGTH];												///< Input Buffer Data
	u32							nCommand;											///< Command Type
	s32							nValue;												///< Command Value
};

struct trlSEmuShellBuffer
{
	u32							nRomType;											///< Cartridge Type
	u32							nRomSubType;										///< Cartridge Sub Type
	u32							nBackupType;										///< Backup Type
	s32							nWidth;												///< Screen Width
	s32							nHeight;											///< Screen Height
	s32							nTexWidth;											///< Texture Width
	s32							nTexHeight;											///< Texture Height
	u32							nRomBufSize;										///< Cartridge Buffer Size
	void*						pRomBuf;											///< Cartridge Buffer Data
	u32							nSoundBufSize;										///< Sound Buffer Size
	void*						pSoundBuf;											///< Sound Buffer Data
	void*						pTextureBuf[2];										///< Texture Buffer Data
	void*						pScreenBuf;											///< Screen Buffer Data
	u32							nTexID;												///< Current Texture Buffer ID
	u32							nScreenBufOffset;									///< Screen Buffer Data Offset
	u32							nBackupDataSize;									///< Backup Buffer Size
	void*						pBackupData;										///< Backup Buffer Data
	u32							nKeyMask;											///< Input Key Mask
	u32							bInitFlag;											///< Init Flag
	u32							bError;												///< Error Flag

	u32							nSaveDataSize;										///< Save Data Size
	trlSEmuShellResume*			pSaveData;											///< Save Data
	s32							nSaveFlag;											///< Save Flag
	u32							nSaveFileSize;										///< Save File Size
	u32							nSaveTime;											///< Save Time Interval
	u32							nSaveUpdate;										///< Save Update Flag

	u32							nDebugKey;											///< Debug Key Data
	u32							nVSyncEnable;										///< VSync Enable Flag

	u32							nSwitchDisk;										///< NES Switch Disk

	u32							bNetworkMaster;										///< Network Master Flag
	u32							bNetworkAsync;										///< Network Async Flag
	u32							nNetworkState;										///< Network State
	u32							nNetworkErrorState;									///< Network Error State
	char						szNetworkPassPhrase[TRL_EMUCORE_NETWORK_PASSLEN];	///< Network Pass Phrase

	u32							nPatchMask;											///< Patch Mask Index
	u32							nPatchPalette;										///< Patch Palette Index
	u32							nPatchCount;										///< Patch Count
	trlSEmuShellPatch*			pPatchData;											///< Patch Data
	u32							nPatchActive;										///< Patch Active Count
	trlSEmuShellPatchActive		sPatchActive[TRL_EMUCORE_PATCH_ACTIVEMAX];			///< Patch Active Data

	u32							nFrames;											///< Frame Count
	u32							bFrameDelayEnable;									///< Frame Delay Enable Flag
	u32							nFrameMark;											///< Frame Mark
	s32							nFrameDelay;										///< Frame Delay Count
	u32							nFrameDouble;										///< Frame Double Mode Flag

	s32							nAudioSampleCurFrame;								///< Audio Sample Current Frame
	s32							nAudioSampleSkip;									///< Audio Sample Skip Frame
	u32							nAudioSampleOffset;									///< Audio Sample Offset Frame

	u32							nVCMMode;											///< VCM Mode
	u32							nVCMState;											///< VCM State: 0-Close, 1-Open, 2-Closing

	s32							(*funcSaveBackup)();								///< TRL Save Backup Func Pointer
	s32							(*funcSoundPlaySize)();								///< TRL Get Sound Play Size Func Pointer
	void						(*funcChangeMaskMode)(u32);							///< TRL Change Mask Mode Func Pointer
	void						(*funcChangeFilterMode)(u32);						///< TRL Change Mono Filter Func Pointer
	u32							(*funcConfigData)(const char*, const char*, u32);	///< TRL Get Config Data Func Pointer
	void						(*funcAudioRecord)(u8*, u32);						///< TRL Audio Record Func Pointer
#ifdef TRL_PLATFORM_PC
	void*						pWaveBuf;											///< Wave Buffer Data (for PC)
#endif
	u32							nMotion2Frames;
#if TRL_PROFILER
	u32							nProfiler1;
	u32							nProfiler2;
	u32							nProfiler3;
	u32							nProfiler4;
#endif
};

/**
 * @struct trlSEmuShellCore
 * @brief EmuCore Function Struct
 */
struct trlSEmuShellCore
{
	void (*trlEmuCoreInit)(trlSEmuShellBuffer*);
	void (*trlEmuCoreRunOneFrame)();
	void (*trlEmuCoreReset)();
	void (*trlEmuCoreInput)(u32);
	void (*trlEmuCoreResume)();
	void (*trlEmuCoreExit)();
	void (*trlEmuCorePatch)(trlSEmuShellPatch*);
	u16 (*trlEmuCoreGetPalette)(u32);
	void (*trlEmuCoreSetPalette)(u32, u16, u32);
	u32 (*trlEmuCoreSwap)(s32);
	void (*trlEmuCoreSave)(u32);
};

extern trlSEmuShellCore		g_sEmuCoreAGB;
extern trlSEmuShellCore		g_sEmuCoreCGB;
extern trlSEmuShellCore		g_sEmuCoreNES;
extern trlSEmuShellBuffer	g_sEmuShellBuffer;
extern trlSEmuShellCore*	g_pEmuShellCore;
extern trlSEmuShellConfig	g_sEmuShellConfig;
extern trlSEmuShellConfig	g_sEmuShellPatch;
