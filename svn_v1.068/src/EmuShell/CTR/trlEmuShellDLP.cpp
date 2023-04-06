/**
* @file trlEmuShellDLP.cpp
* @author zhfang
* @date 2011.07.06
* @brief TRL Emulate For CTR - Download Play Module
*/
#include "trlEmuShellDLP.h"
#include "../trlEmuShellSuspend.h"
#include "../trlEmuShellNetwork.h"
#include "../trlEmuShellStruct.h"
#include "EmuMenu/trlEmuMenu.h"
#include "EmuMenu/trlEmuMenuDataCallBack.h"
#include <nn/dlp.h>

/** @name Global Variable */
//@{
extern CEmuMenu g_hTrlEmuMenu;

u32 g_trlEmuDLPDLPError = TRL_EMU_DLPDLP_ERROR_NONE;

#define DLP_ROUNDUP(x, base)            (((x) + ((base)-1)) & ~((base)-1))
const u8 CHILD_INDEX    = 0x00;

static nn::os::Event s_DlpServerEvent;
static size_t s_DlpServerWorkBufferSize;
static void* s_pWorkBuffer = NULL;
static void* s_pAlignedWorkBuffer = NULL;
static u16 s_ClientNum;

u16 g_nTrlEmuDLPConnClientNum = 0;
u16 g_trlEmuDLPClientId[TRL_NETWORK_CLIENT_MAX];
nn::dlp::ClientState g_trlEmuDLPClientState[TRL_NETWORK_CLIENT_MAX];
nn::dlp::NodeInfo g_sTrlDLPNodeInfo[TRL_NETWORK_CLIENT_MAX];

bool g_bTrlEmuDLPNotice = false;
bool g_bTrlEmuDLPNoticeDraw = false;

wchar_t g_pTrlEmuDLPNoClientName[3][40] =
{	
	L"2P:Not Connected",
	L"3P:Not Connected",
	L"4P:Not Connected",
};
#define DLP_NAME_LENGTHMAX (nn::cfg::CTR::CFG_USER_NAME_LENGTH + 0x30)
wchar_t g_pTrlEmuDLPSelfNameBuf[DLP_NAME_LENGTHMAX] = L"1P:USERNAME";
wchar_t g_pTrlEmuDLPClineNameBuf[DLP_NAME_LENGTHMAX];

volatile s32 g_trlEmuDLPThreadFlag;
nn::dlp::CTR::RebootInfo g_sRebootInfo;

//@}

void trlEmuDLPSetDLPError(u32 error_no)
{
	if(g_trlEmuDLPDLPError == TRL_EMU_DLPDLP_ERROR_NONE)
	{
		g_trlEmuDLPDLPError = error_no;
		NN_LOG("trlEmuDLPSetDLPError %d\n", error_no);
	}
}

u32 trlEmuDLPGetConnPlayerNum()
{	
	return g_nTrlEmuDLPConnClientNum + 1;
}
u32 trlEmuDLPGetPlayerNum()
{
	return s_ClientNum + 1;
}

bool trlEmuDLPFlag()
{
	if(g_nTrlEmuDLPConnClientNum == 0)
		return false;
	return true;
}
void trlEmuDLPBootInfo()
{
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	memset(&g_sRebootInfo, 0, sizeof(g_sRebootInfo));
	nn::dlp::CTR::GetRebootInfo(&g_sRebootInfo);
	memcpy(g_sEmuShellBuffer.szNetworkPassPhrase,g_sRebootInfo.passphrase, nn::dlp::MAX_CHILD_UDS_PASSPHRASE_LENGTH);
	return; 
#endif

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_PARENT
	NN_LOG("s_ClientNum = %d\n", s_ClientNum);
	if(trlEmuDLPGetPlayerNum() == 1)
	{
		//begin net from debug menu
		extern u16 g_pTrlNetworkPiaShareData[4*3];
		memset(g_pTrlNetworkPiaShareData, 0, sizeof(g_pTrlNetworkPiaShareData));		
		memset(g_sEmuShellBuffer.szNetworkPassPhrase,0, nn::dlp::MAX_CHILD_UDS_PASSPHRASE_LENGTH);
	}
	NN_LOG("g_sEmuShellBuffer.szNetworkPassPhrase = %s\n", g_sEmuShellBuffer.szNetworkPassPhrase);
	return;
#endif

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_NONE
	return;
#endif
}

char* trlEmuDLPGetPassPhrase()
{
	return g_sRebootInfo.passphrase;
};

void trlEmuDLPStateInit()
{
	g_trlEmuDLPDLPError = TRL_EMU_DLPDLP_ERROR_NONE;
}

/** @brief Init DLP*/
s32 trlEmuDLPInit()
{
	g_nTrlNetworkClintNum = g_sEmuShellBuffer.funcConfigData("NES", "MultiPlayer", 2) - 1;
	if(g_nTrlNetworkClintNum > 1)
	{
		g_nTrlNetwork4PMsg = 1;
	}
	else
	{
		g_nTrlNetwork4PMsg = 0;
	}
	g_hTrlEmuMenu.Convert4PMessage();
	{
		u32 no_conn_msg_id = HVC_VCM_07;
		if(g_nTrlNetwork4PMsg == 1)
			no_conn_msg_id = HVC_VCM_4P_07;
		for(int i=0;i<3;i++)
		{
			int j;
			for(j=0;j<g_hTrlEmuMenu.pMainMessageLength[no_conn_msg_id];j++)
			{
				g_pTrlEmuDLPNoClientName[i][j] = g_hTrlEmuMenu.pMainMessage[no_conn_msg_id][j];
			}
			g_pTrlEmuDLPNoClientName[i][j] = 0;
		}
	}

	nn::Result result;
	s_DlpServerEvent.Initialize(false);
	s_DlpServerWorkBufferSize = nn::dlp::Server::GetBufferSize(g_nTrlNetworkClintNum);
	NN_LOG("dlpServerWorkBufferSize %d\n", s_DlpServerWorkBufferSize);
	s_pWorkBuffer = trlMemAlloc(s_DlpServerWorkBufferSize + 4096);	
	NN_LOG("s_pWorkBuffer = 0x%x\n", s_pWorkBuffer);
	s_pAlignedWorkBuffer
            = reinterpret_cast<void*> (DLP_ROUNDUP(reinterpret_cast<u32>(s_pWorkBuffer), 4096UL));
	NN_LOG("s_pWorkBuffer = 0x%x\n", s_pAlignedWorkBuffer);

	trlEmuShellSuspendDisableHomeButton();
	trlEmuShellsupendDisableSleep();

	
	NN_LOG("trlEmuDLPInit go to Server::Initialize\n");
	result = nn::dlp::Server::Initialize(
		&g_bTrlEmuDLPNotice,
		s_DlpServerEvent.GetHandle(),
        g_nTrlNetworkClintNum,
        CHILD_INDEX,
		s_pAlignedWorkBuffer,
        s_DlpServerWorkBufferSize);
	NN_LOG("trlEmuDLPInit go to Server::Initialize end\n");
	if(result.IsFailure())
	{	
		trlEmuDLPRelease();
		trlEmuShellSuspendEnableHomeButton();
		trlEmuShellsupendEnableSleep();
		NN_LOG("EmuDLP fail: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
		if(result == nn::dlp::ResultWirelessOff())
			return eEmuDLPResult_WireLessOff;
		return eEmuDLPResult_Fail;
	}
	NN_LOG("trlEmuDLPInit go to Server::Initialize success\n");

	g_nTrlEmuDLPConnClientNum = 0;
//	g_bTrlEmuDLPNotice = true;
	return eEmuDLPResult_Success;
}

/** @brief Release DLP, run after dlp success or dlp was canceled*/
s32 trlEmuDLPRelease()
{
	NN_LOG("trlEmuDLPRelease\n");	
	nn::dlp::Server::Finalize();
    s_DlpServerEvent.Finalize();
	if(s_pWorkBuffer != NULL)
	{
		trlMemFree(s_pWorkBuffer);
		s_pWorkBuffer = NULL;
	}
	g_nTrlEmuDLPConnClientNum = 0;	
	return eEmuDLPResult_Success;
}

/** @brief Proc DLP, run in a thread to proc dlp*/
s32 trlEmuDLPProc()
{
	nn::dlp::ServerState serverState;
	nn::dlp::Server::GetState(&serverState);

	switch (serverState)
    {
    case nn::dlp::SERVER_STATE_INITIALIZED:
		NN_LOG("Inited,so open seccsion\n");
		nn::dlp::Server::OpenSessions(true, 0);
		return eEmuDLPResult_Wait;        
    case nn::dlp::SERVER_STATE_OPENED_SESSIONS:
        trlEmuDLPWaitChild();
        return eEmuDLPResult_Wait;
    case nn::dlp::SERVER_STATE_DISTRIBUTING:
		{
			u16 clientNum = 0;
			u16 clientId[TRL_NETWORK_CLIENT_MAX];
			nn::dlp::Server::GetConnectingClients(&clientNum, clientId, g_nTrlNetworkClintNum);
			if(clientNum == 0)
			{
				trlEmuShellSuspendEnableHomeButton();
				trlEmuShellsupendEnableSleep();
				trlEmuDLPSetDLPError(TRL_EMU_DLPDLP_ERROR_NETWORK);
				g_trlEmuDLPThreadFlag = TLL_EMU_DLPTHREAD_FAIL;
				NN_LOG("......dlp server error\n");
				return eEmuDLPResult_Fail;
			}
		}
		return eEmuDLPResult_Wait;
    case nn::dlp::SERVER_STATE_COMPLETE_DISTRIBUTION:
		{
			NN_LOG("trans done, so reboot child\n");

			u32 random;
			::std::srand(static_cast<s32>(nn::os::Tick::GetSystemCurrent() >> 1));
			random = static_cast<u32>(::std::rand());
			nn::nstd::TSNPrintf(g_sEmuShellBuffer.szNetworkPassPhrase, nn::dlp::MAX_CHILD_UDS_PASSPHRASE_LENGTH, "%08x", random);
			nn::dlp::Server::RebootAllClients(g_sEmuShellBuffer.szNetworkPassPhrase);
		}
        return eEmuDLPResult_Wait;
    case nn::dlp::SERVER_STATE_REBOOTING_CLIENTS:
		{
			u16 clientNum = 0;
			u16 clientId[TRL_NETWORK_CLIENT_MAX];
			if (nn::dlp::Server::GetConnectingClients(&clientNum, clientId, g_nTrlNetworkClintNum).IsSuccess())
			{	
				if (clientNum == 0)
				{
					NN_LOG("all child have been reboot\n");
					g_trlEmuDLPThreadFlag = TLL_EMU_DLPTHREAD_SUCCESS;
					return eEmuDLPResult_Success;
				}
				else
				{
					NN_LOG("have %d childs  not reboot\n", clientNum);
					return eEmuDLPResult_Wait;
				}
			}
			else
				return eEmuDLPResult_Fail;            
		}
    case nn::dlp::SERVER_STATE_ERROR:		
    case nn::dlp::SERVER_STATE_INVALID:
		trlEmuShellSuspendEnableHomeButton();
		trlEmuShellsupendEnableSleep();
		trlEmuDLPSetDLPError(TRL_EMU_DLPDLP_ERROR_NETWORK);
		g_trlEmuDLPThreadFlag = TLL_EMU_DLPTHREAD_FAIL;
		NN_LOG("......dlp server error\n");
		return eEmuDLPResult_Fail;

		//trlEmuDLPReset();
		//return eEmuDLPResult_Wait;        
    }
	return eEmuDLPResult_Wait;
}

/** @brief reset DLP if there have some error*/
s32 trlEmuDLPReset()
{
	nn::Result result;
	nn::dlp::Server::Finalize();
	result = nn::dlp::Server::Initialize(
		s_DlpServerEvent.GetHandle(),
        g_nTrlNetworkClintNum,
        CHILD_INDEX,
		s_pAlignedWorkBuffer,
        s_DlpServerWorkBufferSize);
	if(result.IsFailure())
	{
		if(result == nn::dlp::ResultInvalidPointer())
		{
			NN_LOG("nn::dlp::Server::Initialize failed ResultInvalidPointer\n");
		}
		else if(result == nn::dlp::ResultInvalidPointer())
		{
			NN_LOG("nn::dlp::Server::Initialize failed ResultInvalidPointer\n");
		}
		
		NN_LOG("EmuDLP fail: Level %d, Summary %d, Module %d, Description %d\n", result.GetLevel(), result.GetSummary(), result.GetModule(), result.GetDescription());
		return eEmuDLPResult_Fail;
	}
	g_nTrlEmuDLPConnClientNum = 0;

	//zhfang test
	//g_bTrlEmuDLPNotice = true;
	return eEmuDLPResult_Success;
}


/** @brief DLP wait child to join in and accept it*/
s32 trlEmuDLPWaitChild()
{
	nn::dlp::Server::GetConnectingClients(&g_nTrlEmuDLPConnClientNum, g_trlEmuDLPClientId, g_nTrlNetworkClintNum);	
	for(int i=0;i<g_nTrlEmuDLPConnClientNum;i++)
	{		
		nn::dlp::Server::GetClientState(&g_trlEmuDLPClientState[i], g_trlEmuDLPClientId[i]);
		if (g_trlEmuDLPClientState[i] == nn::dlp::CLIENT_STATE_WAITING_ACCEPT)
		{
			//NN_LOG("AcceptClinet g_nTrlEmuDLPConnClientNum = %d\n", g_nTrlEmuDLPConnClientNum);
			nn::dlp::Server::AcceptClient(g_trlEmuDLPClientId[i]);
		}
		nn::dlp::Server::GetClientInfo(&g_sTrlDLPNodeInfo[i], g_trlEmuDLPClientId[i]);
	}
	return eEmuDLPResult_Success;	
}

/** @brief DLP begin trans child program to child machine*/
s32 trlEmuDLPBeginTrans()
{
	trlEmuShellSuspendDisableHomeButton();
	trlEmuShellsupendDisableSleep();

	u16 clientNum = 0;
    u16 clientId[TRL_NETWORK_CLIENT_MAX];
	nn::dlp::Server::GetConnectingClients(&clientNum, clientId, g_nTrlNetworkClintNum);
	NN_LOG("Begin trans..clientNum = %d\n", clientNum);
	for(int i=0;i<clientNum;i++)
	{
		nn::dlp::Server::GetClientState(&g_trlEmuDLPClientState[i], clientId[i]);
		if (g_trlEmuDLPClientState[i] == nn::dlp::CLIENT_STATE_JOINED_SESSION)
		{	
			nn::dlp::Server::GetClientInfo(&g_sTrlDLPNodeInfo[i], clientId[i]);
			extern u16 g_pTrlNetworkPiaShareData[4*3];
			memcpy(&g_pTrlNetworkPiaShareData[4*i], g_sTrlDLPNodeInfo[i].scrambledLocalFriendCode.value, 4*sizeof(u16));
		}
	}

	
	NN_LOG("...begin to trans\n");
	nn::dlp::Server::StartDistribute();
    nn::dlp::Server::GetConnectingClients(&s_ClientNum, clientId, g_nTrlNetworkClintNum);
	if(clientNum == 0)
	{
		trlEmuShellSuspendEnableHomeButton();
		trlEmuShellsupendEnableSleep();
		trlEmuDLPSetDLPError(TRL_EMU_DLPDLP_ERROR_NETWORK);
		g_trlEmuDLPThreadFlag = TLL_EMU_DLPTHREAD_FAIL;
	}
	return eEmuDLPResult_Success;
}


/** @brief Cancel the DLP*/
void trlEmuDLPThreadStop()
{
	g_trlEmuDLPThreadFlag = TLL_EMU_DLPTHREAD_STOP;
}

/** @brief DLP Proc thread */
void trlEmuDLPThreadFunc()
{
	NN_LOG("trlEmuDLPThreadFunc begin\n");
	g_trlEmuDLPThreadFlag = TLL_EMU_DLPTHREAD_RUN;

	if(g_bTrlEmuDLPNotice == true)
		g_bTrlEmuDLPNoticeDraw = true;

	while(g_trlEmuDLPThreadFlag == TLL_EMU_DLPTHREAD_RUN)
	{
		trlEmuDLPProc();
		nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(16));
	}
	trlEmuDLPRelease();
	if(g_trlEmuDLPThreadFlag == TLL_EMU_DLPTHREAD_FAIL)
	{
		NN_LOG("trlEmuDLPThreadFunc was failed\n");
		return;
	}
	if(g_trlEmuDLPThreadFlag == TLL_EMU_DLPTHREAD_STOP)
	{
		NN_LOG("trlEmuDLPThreadFunc was canceled\n");
		return;
	}


	if(trlEmuDLPGetPlayerNum() > 2)
		g_nTrlNetwork4PMsg = 1;
	else
		g_nTrlNetwork4PMsg = 0;
	g_hTrlEmuMenu.Convert4PMessage();

	trlEmuShellSuspendDisableHomeButton();
	trlEmuShellsupendDisableSleep();
	g_trlEmuDLPThreadFlag = TRL_EMU_DLPTHREAD_RECON_SUCCESS;
	NN_LOG("trlEmuDLPThreadFunc end\n");
}


void trlEmuNetThreadChildFunc()
{
	trlEmuShellNetworkInit(0);
}


/** @brief Get Self Name*/
wchar_t* trlEmuDLPGetSelfName()
{
	return g_pTrlEmuDLPSelfNameBuf;
}

/** @brief Get Child Name*/
wchar_t* trlEmuDLPGetChildName(int index)
{
	u16 clientnum = g_nTrlEmuDLPConnClientNum;
	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
		clientnum = 1;
	if(clientnum > g_nTrlNetworkClintNum)
		return NULL;

	if(index >= 0 && index < g_nTrlNetworkClintNum)
	{
		if(index >= clientnum)
		{
			for(int i=0;i<DLP_NAME_LENGTHMAX;i++)
			{
				g_pTrlEmuDLPClineNameBuf[i] = g_pTrlEmuDLPNoClientName[index][i];
				if(g_pTrlEmuDLPNoClientName[index][i] == 0)	
					break;
			}
			g_pTrlEmuDLPClineNameBuf[DLP_NAME_LENGTHMAX - 1] = 0;
			return g_pTrlEmuDLPClineNameBuf;
		}
		{
			int i;
			for(i=0;i<3;i++)
				g_pTrlEmuDLPClineNameBuf[i] = g_pTrlEmuDLPNoClientName[index][i];
			if(g_sTrlDLPNodeInfo[index].userName.isNgUserName)
			{
				g_pTrlEmuDLPClineNameBuf[0] = '?';
				g_pTrlEmuDLPClineNameBuf[1] = '?';
				g_pTrlEmuDLPClineNameBuf[2] = '?';
				g_pTrlEmuDLPClineNameBuf[3] = 0;
			}
			else
			{
				for(i=0;i<nn::cfg::CTR::CFG_USER_NAME_LENGTH;i++)
				{
					g_pTrlEmuDLPClineNameBuf[i] = g_sTrlDLPNodeInfo[index].userName.userName[i];
					if(g_sTrlDLPNodeInfo[index].userName.userName[i] == 0)
						break;
				}
				g_pTrlEmuDLPClineNameBuf[DLP_NAME_LENGTHMAX - 1] = 0;
			}
			return g_pTrlEmuDLPClineNameBuf;
		}
	}
	return NULL;
}
