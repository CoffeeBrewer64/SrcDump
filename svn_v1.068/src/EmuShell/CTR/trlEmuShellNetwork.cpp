/**
 * @file trlEmuShellNetwork.cpp
 * @author Chentian
 * @date 2011.03.23
 * @brief TRL Emulate For CTR - EmuShell Network
 */

#include "..\trlEmuShellNetwork.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellStruct.h"
#include "..\trlEmuShellVideo.h"
#if TRL_NETWORK_IR
#include <nn/os.h>
#include <nn/ir.h>
#include <nn/ir/CTR/ir_IrnopAPI.h>

#define TRL_NETWORK_UNIQUE_ID			0x000F7FF0
#define TRL_NETWORK_SUB_ID				1
#define TRL_NETWORK_IR_WORKBUF			8192
#define TRL_NETWORK_PACKETBUF			1024
#define TRL_NETWORK_PLAYER_MAX			2
#define TRL_NETWORK_INPUT_BUF			2
#define TRL_NETWORK_PAUSE_DELAY			3
#define TRL_NETWORK_MIN(a,b)			((a) < (b) ? (a) : (b))

/** @name Global Variable */
//@{
static u8					g_nTrlNetworkIrBuf[TRL_NETWORK_IR_WORKBUF] NN_ATTRIBUTE_ALIGN(4096);

nn::os::Event				g_hTrlNetworkSendEvent;
nn::os::Event				g_hTrlNetworkRecvEvent;
nn::os::Event				g_hTrlNetworkViewEvent;
size_t						g_nTrlNetworkBufferSize;
size_t						g_nTrlNetworkDataSize;
u8*							g_pTrlNetworkSendBuf;
u8*							g_pTrlNetworkRecvBuf;
trlSEmuShellNetworkBuffer*	g_pTrlNetworkSendData;
trlSEmuShellNetworkBuffer*	g_pTrlNetworkRecvData;
u8*							g_pTrlNetworkResumeBuf;

u32							g_bTrlNetworkSendThread;
u32							g_bTrlNetworkRecvThread;
u32							g_bTrlNetworkViewThread;
nn::os::Thread				g_hTrlNetworkSendThread;
nn::os::Thread				g_hTrlNetworkRecvThread;
nn::os::Thread				g_hTrlNetworkViewThread;
nn::os::Thread				g_hTrlNetworkLoadThread;
nn::os::LightEvent			g_hTrlNetworkSyncEvent;
nn::os::LightEvent			g_hTrlNetworkLoadEvent;

nn::os::CriticalSection		g_hTrlNetworkLock;
u32							g_nTrlNetworkPlayer;
u32							g_bTrlNetworkSender;
s32							g_nTrlNetworkIndex;
u32							g_nTrlNetworkInput;
u32							g_bTrlNetworkRole;
u32							g_bTrlNetworkInit = 0;
//const wchar_t				g_szTrlNetworkNGUserName[] = L"********";
#if TRL_PRODUCTION==0	// For Test
const char					g_szTrlNetworkPathPhrase[] = "TRL_NETPP";
#endif
char						g_szCommand[0xA][16] = { "NONE", "START", "RESUME", "PAUSE", "CLOSE", "RESET", "LOAD", "FINISH", "DISCONNECT", "DESTROY" };
//@}

u8 g_pTrlNetworkIBuf[TRL_NETWORK_BUF_LENGTH];
u32 g_nTrlNetworkICount;

u8 g_pTrlNetworkOBuf[TRL_NETWORK_BUF_LENGTH];
u32 g_nTrlNetworkOCount;

u32 g_nTrlNetworkCount;

/** @brief EmuShell Network Process */
inline void trlEmuShellNetworkProcess();

/** @brief EmuShell Network Send Resume Data */
void trlEmuShellNetworkSendResume()
{
	NN_LOG("Send Resume: Start\n");

	trlEmuShellDataSaveResumeData(g_pTrlNetworkResumeBuf, TRL_DATA_RESUME_BACKUP);
	u32 nSent = 0;
	do{
		g_hTrlNetworkSendEvent.ClearSignal();
		size_t nDataSize = TRL_NETWORK_MIN(g_sEmuShellBuffer.nSaveFileSize - nSent, TRL_NETWORK_PACKETBUF);
		nn::Result result = nn::ir::Send(g_pTrlNetworkResumeBuf + nSent, nDataSize);
		if(result.IsFailure())
		{
			NN_LOG("Send Resume failed.\n");
			//if(result == nn::ir::ResultNotConnected())
			NN_ERR_THROW_FATAL(result);
		}
		else
			nSent += nDataSize;
		g_hTrlNetworkSendEvent.Wait();
	}while(nSent<g_sEmuShellBuffer.nSaveFileSize);

	NN_LOG("Send Resume: End\n");
}

/** @brief EmuShell Network Recv Resume Data */
void trlEmuShellNetworkRecvResume()
{
	NN_LOG("Recv Resume: Start\n");

	u32 nRecv = 0;
	do{
		g_hTrlNetworkRecvEvent.Wait();
		g_hTrlNetworkRecvEvent.ClearSignal();
		s32 nUsedSize = -1;
		size_t nRecvSize = 0;
		nn::Result result = nn::ir::Receive(g_pTrlNetworkResumeBuf + nRecv, g_nTrlNetworkBufferSize, &nRecvSize, &nUsedSize);
		if(result.IsFailure())
		{
			nRecvSize = 0;
			if(result == nn::ir::ResultBufferInsufficient())
			{ 
				nn::ir::Communicator::DropNextReceiveData(&nUsedSize);
				NN_LOG("Recv Resume: BufferInsufficient.\n");
				break;
			}
			else if(result == nn::ir::ResultNoData())
			{
				NN_LOG("Recv Resume: NoData.\n");
				continue;
			}
			else if(result == nn::ir::ResultInvalidData())
				NN_LOG("Recv Resume: InvalidData.\n");
			else if(result == nn::ir::ResultNotConnected())
				NN_LOG("Recv Resume: NotConnected.\n");
			else if(result == nn::ir::ResultCannotConfirmId())
				NN_LOG("Recv Resume: CannotConfirm.\n");
			else if(result == nn::ir::ResultMachineSleep())
				NN_LOG("Recv Resume: MachineSleep.\n");
			else if(result == nn::ir::ResultFatalError())
				NN_LOG("Recv Resume: FatalError.\n");
			else
				NN_LOG("Recv Resume: Other.\n");
			NN_ERR_THROW_FATAL(result);
		}
		else
			nRecv += nRecvSize;
	}while(nRecv<g_sEmuShellBuffer.nSaveFileSize);

	trlEmuShellDataLoadResumeData(g_pTrlNetworkResumeBuf, TRL_DATA_RESUME_BACKUP);
	trlEmuShellDataResume();
	NN_LOG("Recv Resume: End\n");
}

//extern u32 g_pTrlNetworkIBuf[TRL_NETWORK_BUF_LENGTH];
//extern u32 g_nTrlNetworkICount;
//
//extern u32 g_pTrlNetworkOBuf[TRL_NETWORK_BUF_LENGTH];
//extern u32 g_nTrlNetworkOCount;
//
//extern u32 g_nTrlNetworkCount;

/** @brief EmuShell Network Send */
inline void trlEmuShellNetworkSend()
{
	if(g_pTrlNetworkSendData->nIndex < g_nTrlNetworkICount)
	{
		for(int i=0;i<TRL_NETWORK_BUF_LENGTH;i++)
			g_pTrlNetworkSendData->nInput[i] = g_pTrlNetworkIBuf[i];		
		g_pTrlNetworkSendData->nIndex = g_nTrlNetworkICount;
	}

	g_hTrlNetworkSendEvent.ClearSignal();
	g_hTrlNetworkLock.Enter();
	nn::Result result = nn::ir::Send(g_pTrlNetworkSendBuf, g_nTrlNetworkDataSize/*, g_nTrlNetworkBufferSize, false*/);
	g_hTrlNetworkLock.Leave();
	if(result.IsFailure())
	{
		NN_LOG("Send failed.\n");
		//if(result == nn::ir::ResultNotConnected())
		NN_ERR_THROW_FATAL(result);
	}
	g_hTrlNetworkSendEvent.Wait();
}

/** @brief EmuShell Network Recv */
inline void trlEmuShellNetworkRecv()
{
	g_hTrlNetworkRecvEvent.Wait();
	g_hTrlNetworkRecvEvent.ClearSignal();
	if(g_bTrlNetworkRecvThread==0)
		return;
	s32 nUsedSize = -1;
	size_t nRecvSize = 0;
	nn::Result result = nn::ir::Receive(g_pTrlNetworkRecvBuf, g_nTrlNetworkDataSize/*g_nTrlNetworkBufferSize*/, &nRecvSize, &nUsedSize);
	if(result.IsFailure())
	{
		nRecvSize = 0; 
		if(result == nn::ir::ResultBufferInsufficient())
		{ 
			nn::ir::Communicator::DropNextReceiveData(&nUsedSize);
			NN_LOG("Recv: BufferInsufficient.\n");
			return;
		}
		else if(result == nn::ir::ResultNoData())
		{
			NN_LOG("Recv: NoData.\n");
			return;
		}
		else if(result == nn::ir::ResultInvalidData())
			NN_LOG("Recv: InvalidData.\n");
		else if(result == nn::ir::ResultNotConnected())
			NN_LOG("Recv: NotConnected.\n");
		else if(result == nn::ir::ResultCannotConfirmId())
			NN_LOG("Recv: CannotConfirm.\n");
		else if(result == nn::ir::ResultMachineSleep())
			NN_LOG("Recv: MachineSleep.\n");
		else if(result == nn::ir::ResultFatalError())
			NN_LOG("Recv: FatalError.\n");
		else
			NN_LOG("Recv: Other.\n");
		NN_ERR_THROW_FATAL(result);
	}
	trlEmuShellNetworkProcess();
	return;
}

/** @brief EmuShell Network Send Thread */
void trlEmuShellNetworkSendThread()
{
	while(g_bTrlNetworkSendThread)
	{
		g_hTrlNetworkSyncEvent.Wait();
		trlEmuShellNetworkSend();
	}
}

/** @brief EmuShell Network Recv Thread */
void trlEmuShellNetworkRecvThread()
{
	while(g_bTrlNetworkRecvThread)
	{
		g_hTrlNetworkLoadEvent.Wait();
		trlEmuShellNetworkRecv();
	}
}

/** @brief EmuShell Network View Thread */
void trlEmuShellNetworkViewThread()
{
	while(g_bTrlNetworkViewThread)
	{
		g_hTrlNetworkViewEvent.Wait();
		g_hTrlNetworkViewEvent.ClearSignal();
		switch(nn::ir::Communicator::GetConnectionStatus())
		{
		case nn::ir::CONNECTION_STATUS_STOPPED:
			break;
		case nn::ir::CONNECTION_STATUS_TRYING_TO_CONNECT:
			break;
		case nn::ir::CONNECTION_STATUS_CONNECTED:
			break;
		case nn::ir::CONNECTION_STATUS_DISCONNECTING:
		case nn::ir::CONNECTION_STATUS_FATAL_ERROR:
			if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_EXIT)
				g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_ERROR;
			break;
		}
	}
}

/** @brief EmuShell Network Load Thread */
void trlEmuShellNetworkLoadThread()
{
	if(g_sEmuShellBuffer.bNetworkMaster)	// Master
	{
		trlEmuShellNetworkSendResume();
	}
	else									// Client
	{
		trlEmuShellNetworkRecvResume();
		g_hTrlNetworkLoadEvent.Signal();
		trlEmuShellNetworkCommand(TRL_NETWORK_COMMAND_FINISH);
	}
}

/** @brief EmuShell Network Command */
void trlEmuShellNetworkCommand(u8 nCMD)
{
	g_bTrlNetworkSender = 1;
	g_pTrlNetworkSendData->nCommand = nCMD;

	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_RUN)
	{
		NN_LOG("Send: %s\n", g_szCommand[g_pTrlNetworkSendData->nCommand]);
		trlEmuShellNetworkSend();
	}
}

/** @brief EmuShell Network Process */
inline void trlEmuShellNetworkProcess()
{
	// Update Input Data
	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_RUN)
	{
		if(g_pTrlNetworkRecvData->nIndex > g_nTrlNetworkOCount)
		{
			for(int i=0;i<TRL_NETWORK_BUF_LENGTH;i++)
				g_pTrlNetworkOBuf[i] = g_pTrlNetworkRecvData->nInput[i];
			g_nTrlNetworkOCount = g_pTrlNetworkRecvData->nIndex;
		}
		if(!g_bTrlNetworkRole)
		{
			if(g_pTrlNetworkRecvData->nCommand == TRL_NETWORK_COMMAND_NONE)
				g_hTrlNetworkSyncEvent.Signal();
		}
	}

	// Process Command
	if(g_pTrlNetworkRecvData->nCommand != TRL_NETWORK_COMMAND_NONE)
	{
		if(g_bTrlNetworkSender)
			g_bTrlNetworkSender = 0;
		else
		{
			g_pTrlNetworkSendData->nCommand = g_pTrlNetworkRecvData->nCommand;
			NN_LOG("Recv: %s\n", g_szCommand[g_pTrlNetworkRecvData->nCommand]);
			trlEmuShellNetworkSend();
		}
		g_pTrlNetworkSendData->nCommand = TRL_NETWORK_COMMAND_NONE;

		switch(g_pTrlNetworkRecvData->nCommand)
		{
		case TRL_NETWORK_COMMAND_START:
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_READY;
			break;
		case TRL_NETWORK_COMMAND_RESUME:
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_RUN;
			break;
		case TRL_NETWORK_COMMAND_PAUSE:
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_PAUSE;
			break;
		case TRL_NETWORK_COMMAND_CLOSE:
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_CLOSE;
			break;
		case TRL_NETWORK_COMMAND_RESET:
			trlEmuShellDataReset();
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_RESET;
			break;
		case TRL_NETWORK_COMMAND_LOAD:
			if(!g_sEmuShellBuffer.bNetworkMaster)
			{
				g_hTrlNetworkLoadEvent.ClearSignal();
				g_hTrlNetworkRecvEvent.Signal();
			}
			g_hTrlNetworkLoadThread.StartUsingAutoStack( trlEmuShellNetworkLoadThread, 8192, nn::os::DEFAULT_THREAD_PRIORITY+1 );
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_LOAD;
			break;
		case TRL_NETWORK_COMMAND_FINISH:
			g_hTrlNetworkLoadThread.Join();
			g_hTrlNetworkLoadThread.Finalize();
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_PAUSE;
			break;
		case TRL_NETWORK_COMMAND_DISCONNECT:
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_EXIT;
			break;
		case TRL_NETWORK_COMMAND_DESTROY:
			g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_ERROR;
			break;
		}
	}
}

/** @brief EmuShell Network Init */
void trlEmuShellNetworkInit(u32 bMaster)
{
	if(g_bTrlNetworkInit)
		return;

	g_nTrlNetworkIndex = 0;
	g_nTrlNetworkInput = 0;
	g_bTrlNetworkSender = 0;
	g_nTrlNetworkDataSize = sizeof(trlSEmuShellNetworkBuffer);
	g_sEmuShellBuffer.bNetworkAsync = 0;
	g_sEmuShellBuffer.bNetworkMaster = bMaster;
	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_NONE;

	size_t nBufferSize     = nn::ir::Communicator::GetPacketSize(TRL_NETWORK_PACKETBUF)*2;
    size_t nManagementSize = nn::ir::Communicator::GetManagementSize(1)*2;
    NN_ASSERT(nn::ir::Communicator::GetReservedSize() + (nBufferSize + nManagementSize)*2 <= TRL_NETWORK_IR_WORKBUF);
    NN_UTIL_PANIC_IF_FAILED(nn::ir::Communicator::Initialize(g_nTrlNetworkIrBuf, TRL_NETWORK_IR_WORKBUF, nBufferSize, nManagementSize, nBufferSize, nManagementSize));

    nn::ir::Communicator::GetSendEvent(&g_hTrlNetworkSendEvent);
    nn::ir::Communicator::GetReceiveEvent(&g_hTrlNetworkRecvEvent);
    nn::ir::Communicator::GetConnectionStatusEvent(&g_hTrlNetworkViewEvent);

    g_nTrlNetworkBufferSize = nn::ir::Communicator::CalculateBufferSizeToCommunicate(TRL_NETWORK_PACKETBUF);
	g_pTrlNetworkResumeBuf = reinterpret_cast<u8*>(trlMemAlloc(g_sEmuShellBuffer.nSaveFileSize));
	g_pTrlNetworkSendBuf = reinterpret_cast<u8*>(trlMemAllocDevice(g_nTrlNetworkBufferSize,4));
	g_pTrlNetworkRecvBuf = reinterpret_cast<u8*>(trlMemAllocDevice(g_nTrlNetworkBufferSize,4));
	g_pTrlNetworkSendData = reinterpret_cast<trlSEmuShellNetworkBuffer*>(g_pTrlNetworkSendBuf);
	g_pTrlNetworkRecvData = reinterpret_cast<trlSEmuShellNetworkBuffer*>(g_pTrlNetworkRecvBuf);
	memset(g_pTrlNetworkSendBuf,0,g_nTrlNetworkBufferSize);
	memset(g_pTrlNetworkRecvBuf,0,g_nTrlNetworkBufferSize);

	memset(g_pTrlNetworkIBuf, 0, sizeof(g_pTrlNetworkIBuf));
	memset(g_pTrlNetworkOBuf, 0, sizeof(g_pTrlNetworkOBuf));	
	g_nTrlNetworkICount = 0;
	g_nTrlNetworkOCount = 0;

	g_nTrlNetworkCount = 0;

	nn::ir::Communicator::AutoConnection();
	while(1)
	{
		nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(1));
		if( nn::ir::Communicator::GetConnectionStatus() == nn::ir::CONNECTION_STATUS_CONNECTED)
		{
			//nn::Result result;
			//bit32 nCMID = nn::ir::Communicator::CreateCommunicationId(TRL_NETWORK_UNIQUE_ID);

			#if !TRL_PRODUCTION	// For Test
			memcpy(g_sEmuShellBuffer.szNetworkPassPhrase, g_szTrlNetworkPathPhrase, sizeof(g_szTrlNetworkPathPhrase));
			#endif	

			/*switch(nn::ir::Communicator::GetConnectionRole())
			{
			case nn::ir::CONNECTION_ROLE_TO_REQUIRE:
				NN_LOG("CONNECTION_ROLE_TO_REQUIRE\n");
				nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(500));
				g_bTrlNetworkRole = 0;
				result = nn::ir::Communicator::RequireToConfirmId(TRL_NETWORK_SUB_ID, nCMID, g_sEmuShellBuffer.szNetworkPassPhrase, TRL_EMUCORE_NETWORK_PASSLEN);
				break;
			case nn::ir::CONNECTION_ROLE_TO_WAIT:
				NN_LOG("CONNECTION_ROLE_TO_WAIT\n");
				g_bTrlNetworkRole = 1;
				result = nn::ir::Communicator::WaitToConfirmId(TRL_NETWORK_SUB_ID, nCMID, g_sEmuShellBuffer.szNetworkPassPhrase, TRL_EMUCORE_NETWORK_PASSLEN, nn::fnd::TimeSpan::FromMilliSeconds(1000));
				break;
			}*/
			g_bTrlNetworkRole = bMaster;
			break;
		}
	}

	// Transfer SaveData
	if(g_sEmuShellBuffer.bNetworkMaster)
	{
		trlEmuShellNetworkSendResume();
		g_nTrlNetworkPlayer = g_pEmuShellCore->trlEmuCoreSwap(-1) ? 1 : 0;
	}
	else
	{
		trlEmuShellNetworkRecvResume();
		g_nTrlNetworkPlayer = g_pEmuShellCore->trlEmuCoreSwap(-1) ? 0 : 1;
	}

	// Init Thread
	g_hTrlNetworkLock.Initialize();
	g_hTrlNetworkSyncEvent.Initialize(false);
	g_hTrlNetworkLoadEvent.Initialize(true);
	g_hTrlNetworkLoadEvent.Signal();
	g_bTrlNetworkViewThread = 1;
	g_hTrlNetworkViewThread.StartUsingAutoStack( trlEmuShellNetworkViewThread, 4096, nn::os::DEFAULT_THREAD_PRIORITY-1 );
	g_bTrlNetworkRecvThread = 1;
	g_hTrlNetworkRecvThread.StartUsingAutoStack( trlEmuShellNetworkRecvThread, 4096, nn::os::DEFAULT_THREAD_PRIORITY-2 );
	g_bTrlNetworkSendThread = 1;
	g_hTrlNetworkSendThread.StartUsingAutoStack( trlEmuShellNetworkSendThread, 4096, nn::os::DEFAULT_THREAD_PRIORITY-1 );

	g_bTrlNetworkInit = 1;
	NN_LOG("Network Init OK!\n");
	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_INIT;
}

//extern u32 g_pTrlNetworkIBuf[TRL_NETWORK_BUF_LENGTH];
//extern u32 g_nTrlNetworkICount;
//
//extern u32 g_pTrlNetworkOBuf[TRL_NETWORK_BUF_LENGTH];
//extern u32 g_nTrlNetworkOCount;
//
//extern u32 g_nTrlNetworkCount;
#define TRL_NETWORK_DELAY 2
/** @brief EmuShell Network Update Input */
void trlEmuShellNetworkUpdateInput(u32 nInput)
{
	if( (g_nTrlNetworkOCount + TRL_NETWORK_DELAY) > g_nTrlNetworkIndex)
	{
		if(g_nTrlNetworkIndex > TRL_NETWORK_DELAY)
			g_nTrlNetworkInput = (g_pTrlNetworkOBuf[(g_nTrlNetworkIndex - TRL_NETWORK_DELAY)%TRL_NETWORK_BUF_LENGTH]<<((1-g_nTrlNetworkPlayer)*8))
				| (g_pTrlNetworkIBuf[(g_nTrlNetworkIndex - TRL_NETWORK_DELAY)%TRL_NETWORK_BUF_LENGTH]<<(g_nTrlNetworkPlayer*8));
		else
			g_nTrlNetworkInput = 0;
		g_pEmuShellCore->trlEmuCoreInput(g_nTrlNetworkInput);

		g_nTrlNetworkIndex++;
		g_nTrlNetworkICount++;
		g_pTrlNetworkIBuf[g_nTrlNetworkICount%TRL_NETWORK_BUF_LENGTH] = (nInput & 0xFF);// << (g_nTrlNetworkPlayer*8);

		g_sEmuShellBuffer.bNetworkAsync = 0;
	}
	else
		g_sEmuShellBuffer.bNetworkAsync = 1;


	if(g_bTrlNetworkRole)
	{		
		g_hTrlNetworkSyncEvent.Signal();
	}

	//g_hTrlNetworkLock.Leave();
}

/** @brief EmuShell Network Get Player Name */
const wchar_t* trlEmuShellNetworkGetPlayerName(u32 nID)
{
	(void)nID;
	//if(nID < TRL_NETWORK_MAX_ENTRY)
	//{
	//	if((g_nTrlNetworkPlayerMap>>nID) & 0x01)
	//	{
	//		if(g_sTrlNetworkNodeInfo[nID].userName.isNgUserName)
	//			return g_szTrlNetworkNGUserName;
	//		return g_sTrlNetworkNodeInfo[nID].userName.userName;
	//	}
	//}
	return 0;
}

/** @brief EmuShell Network Exit */
void trlEmuShellNetworkExit()
{
	if(g_bTrlNetworkInit)
	{
		if(g_hTrlNetworkLoadThread.IsAlive())
		{
			g_hTrlNetworkLoadThread.Join();
			g_hTrlNetworkLoadThread.Finalize();
		}
		trlMemFree(g_pTrlNetworkResumeBuf);

		g_bTrlNetworkViewThread = 0;
		g_hTrlNetworkViewEvent.Signal();
		g_hTrlNetworkViewThread.Join();
		g_hTrlNetworkViewThread.Finalize();

		g_bTrlNetworkSendThread = 0;
		g_bTrlNetworkRecvThread = 0;
		g_hTrlNetworkLoadEvent.Signal();
		g_hTrlNetworkRecvEvent.Signal();
		g_hTrlNetworkRecvThread.Join();
		g_hTrlNetworkRecvThread.Finalize();
		g_hTrlNetworkSyncEvent.Signal();
		g_hTrlNetworkSendThread.Join();
		g_hTrlNetworkSendThread.Finalize();
		g_hTrlNetworkSyncEvent.Finalize();
		g_hTrlNetworkLoadEvent.Finalize();

		trlMemFreeDevice(g_pTrlNetworkSendBuf);
		trlMemFreeDevice(g_pTrlNetworkRecvBuf);

		g_hTrlNetworkLock.Finalize();
		nn::ir::Communicator::Finalize();
	}

	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_NONE;
	g_bTrlNetworkInit = 0;
	NN_LOG("Network End!\n");
}
#endif
