/**
* @file trlEmuShellDLP.h
* @author zhfang
* @date 2011.07.06
* @brief TRL Emulate For CTR - Download Play Module
*/
#pragma once
#include "../../trlHeader.h"

enum EEmuDLPResult
{
	eEmuDLPResult_Success = 0,
	eEmuDLPResult_WireLessOff,
	eEmuDLPResult_Fail,
	eEmuDLPResult_Wait
};

#define TLL_EMU_DLPTHREAD_STOP 0
#define TLL_EMU_DLPTHREAD_RUN 1
#define TLL_EMU_DLPTHREAD_SUCCESS 2
#define TRL_EMU_DLPTHREAD_RECON_SUCCESS 3
#define TLL_EMU_DLPTHREAD_FAIL 4
extern volatile s32 g_trlEmuDLPThreadFlag;

#define TRL_EMU_DLPDLP_ERROR_NONE 0
#define TRL_EMU_DLPDLP_ERROR_NETWORK 1
extern u32 g_trlEmuDLPDLPError;


void trlEmuDLPThreadStop();
void trlEmuDLPThreadFunc();
void trlEmuNetThreadChildFunc();
s32 trlEmuDLPBeginTrans();
s32 trlEmuDLPRelease();
///////////////////
s32 trlEmuDLPReset();
s32 trlEmuDLPWaitChild();

void trlEmuDLPStateInit();
s32 trlEmuDLPInit();

u32 trlEmuDLPGetConnPlayerNum();
u32 trlEmuDLPGetPlayerNum();
bool trlEmuDLPFlag();
void trlEmuDLPBootInfo();
char* trlEmuDLPGetPassPhrase();


wchar_t* trlEmuDLPGetSelfName();
wchar_t* trlEmuDLPGetChildName(int index);

extern wchar_t g_pTrlEmuDLPSelfNameBuf[];

extern void trlEmuNetThreadChildFunc();

extern u16 g_nTrlEmuDLPConnClientNum;

extern bool g_bTrlEmuDLPNotice;
extern bool g_bTrlEmuDLPNoticeDraw;
