/**
* @file trlEmuShellNetwork.cpp
* @author Chentian
* @date 2011.03.23
* @brief TRL Emulate For CTR - EmuShell Network
*/
#include "..\trlEmuShellSuspend.h"
#include "..\trlEmuShellNetwork.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellStruct.h"
#include "..\trlEmuShellVideo.h"
#include ".\EmuMenu\trlEmuMenuData.h"
#include "trlEmuShellDLP.h"

#if TRL_NETWORK_PIA

#include <pia/common.h>
#include <pia/local.h>
#include <pia/sync.h>
#include <pia/sync/sync_StationAddressTable.h>
#include <pia/sync/sync_Type.h>
#include <pia/local.h>
#include <nn/dlp.h>
#include "ErrorHandling.h"

u32 g_nTrlNetwork4PMsg = 0;
u32 g_nTrlNetworkClintNum = 0;
s32 g_nTrlNetworkDelay = -1;

u32 NETWORK_STATECHANGE_FRAMEDELAY = 4;
u32 NETWORK_STATECHANGE_CONFIRMDELAY = 4;
u32 g_nPlayerStateChangeDelay = 0;

u8* g_pTrlNetworkResumeBuf;


#define NETWORK_ADDTION_INFO_LENGTH 8


u32 g_nSelfState = PLAYER_STATE_NONE;
u32 g_pPlayerState[4] = {PLAYER_STATE_NONE, PLAYER_STATE_NONE, PLAYER_STATE_NONE, PLAYER_STATE_NONE};
u32 g_pPlayerCmd[4] = {PLAYER_COMMAND_NONE, PLAYER_COMMAND_NONE, PLAYER_COMMAND_NONE, PLAYER_COMMAND_NONE};
u32 g_pPlayerCmdFrameIndex[4] = {0, 0, 0, 0};
u32 g_nMenuCaller = 0;

s32 g_pPlayerSaveSeg[4] = {-1, -1, -1, -1};
s32 g_nWantCloseReceive = 0;
s32 g_nWantCloseNetwork = 0;
s32 g_bTrlNetworkScanAndJoin = 0;

u32 g_bTrlNetworkRole;
u32 g_bTrlNetworkIndex;
u32 g_nTrlNetworkInput = 0;

#if TRL_NETWORK_PIA_WITH_MIC
u32 g_nTrlNetworkInputMic = 0;
#endif

s32 g_nTrlNetworkPiaUdsInited = 0;
s32 g_nTrlNetworkPiaThreadInited = 0;
s32 g_nTrlNetworkPiaSaveSendTrheadInited = 0;

u16 g_pTrlNetworkPiaShareData[4*3];

const u8 SAMPLE_SUB_ID = 0x50;
const u8 SAMPLE_CHANNEL = 0;
const char SAMPLE_PASSPHRASE[] = "4+Nv9MFSpfDJIEvXSnU+4vxMAPlzhBicmoTiKCZEM";

const u8 SAMPLE_MAX_ENTRY = nn::pia::sync::PIA_SYNC_STATION_MAX;

const s32 PACKET_SIZE = nn::uds::UDS_PACKET_PAYLOAD_MAX_SIZE;
const s32 SCAN_MAX = 5;

const u32 UDS_RECEIVE_BUFFER_SIZE = 4096 * 20;
bit8 s_UdsReceiveBuffer[UDS_RECEIVE_BUFFER_SIZE] NN_ATTRIBUTE_ALIGN(4096);
const u32 UDS_SCAN_BUFFER_SIZE = 4 * 1024;
bit8 s_UdsScanBuffer[UDS_SCAN_BUFFER_SIZE];


#define UDS_SEND_OPTION (nn::uds::FORCE_DIRECT_BC | nn::uds::NO_WAIT)
const bit8 UDS_RECEIVE_OPTION = nn::uds::NO_WAIT;

const s32 SEND_THREAD_PRIORITY = nn::os::DEFAULT_THREAD_PRIORITY -1;
const s32 RECEIVE_THREAD_PRIORITY = SEND_THREAD_PRIORITY -1;
const s32 UDS_NODE_EVENTTHREAD_PRIORITY = RECEIVE_THREAD_PRIORITY -1;

//nn::pia::local::UdsSetting* s_pUdsSetting = NULL;
nn::os::Event s_DisconnectEvent;

nn::pia::common::Event s_SendEvent;
//nn::os::LightEvent s_SendEvent;
bool s_IsInitPiaSync = false;

s32 s_nHidSyncState = 0;
s32 s_nHidSyncFrameNo = 0;
u16 s_MyNodeId = 0;

nn::pia::sync::StationAddressTable s_AddressTable(nn::pia::common::UDS_LOCAL_NETWORK, 4);
nn::pia::StationId s_MyStationId = nn::pia::STATION_ID_INVALID;
s32 s_nPlayerNum = 0;
s32 s_nConnPlayerNum = 0;
u8 s_pTrlNetworkPlayerMap[4];
s32 g_nTrlNetworkPlayerMapInited = 0;

void UdsUpdateEventCallbackFunc(nn::pia::local::UdsUpdateEvent e, u16 nodeId, void* /* pParam */)
{
	nn::pia::local::UdsConnectionStatus connectionStatus;
	if(nn::pia::local::UdsNode::GetInstance()->GetConnectionStatus(&connectionStatus).IsFailure())
	{
		NN_LOG("GetConnectionStatus Failed.\n");
		s_DisconnectEvent.Signal();
	}

	s_MyNodeId = connectionStatus.myNodeId;
	s_AddressTable.UpdateForUdsNetwork(connectionStatus.nodeIdList);
	s_MyStationId = s_AddressTable.ToStationId( connectionStatus.myNodeId );


	if (e == nn::pia::local::UdsUpdateEventConnected)
	{
		NN_LOG("Connect! ID: %d MyNodeId: %d\n", nodeId, s_MyNodeId);
		s_nConnPlayerNum++;
		if(s_nConnPlayerNum == s_nPlayerNum)
		{	
			g_nSelfState = g_pPlayerState[0] = PLAYER_STATE_SENDSAVE_ING;
			g_pPlayerCmd[0] = PLAYER_COMMAND_SendShareData;
			NN_LOG("All Connect!\n");
		}
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_PARENT
		if(nodeId != s_MyNodeId)
		{
			nn::pia::local::UdsNodeInformation nodeinfo;
			nn::pia::local::UdsNode::GetInstance()->GetNodeInformation(&nodeinfo, nodeId);
			for(int j=0;j<3;j++)
			{
				s8 samename = 1;
				for(int k=0;k<4;k++)
				{
					if(g_pTrlNetworkPiaShareData[4*j + k] != nodeinfo.scrambledLocalFriendCode.value[k])
					{
						samename = 0;
						break;
					}
				}
				if(samename == 1)
				{
					NN_LOG("Node %d is Player %d\n", nodeId,j + 1);
					s_pTrlNetworkPlayerMap[nodeId-1] = j + 1;
					break;
				}
			}
		}
		else
			s_pTrlNetworkPlayerMap[0] = 0;
#endif
	}
	else if (e == nn::pia::local::UdsUpdateEventDisconnected)
	{
		NN_LOG("Disonnect! ID: %d MyNodeId: %d\n", nodeId, s_MyNodeId);
		if (nodeId == nn::pia::local::UDS_NODE_MASTER_NODE_ID)
		{
			NN_LOG("Leave Network (Reason:%d)\n", connectionStatus.disconnectReason);
			if ( connectionStatus.disconnectReason == nn::uds::REQUEST_FROM_SYSTEM )
			{
				NN_LOG("nn::uds::REQUEST_FROM_SYSTEM\n");
			}
			s_DisconnectEvent.Signal();
			trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		}
		else
		{
			g_pPlayerState[nodeId] = PLAYER_STATE_EXIT;
			trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		}
	}
}

s32 trlEmuShellNetworkUdsInit()
{
	nn::pia::local::Initialize();
	nn::pia::local::BeginSetup();
	nn::pia::local::UdsNodeSetting udsNodeSetting =
	{
		s_UdsReceiveBuffer,
		UDS_RECEIVE_BUFFER_SIZE,
		s_UdsScanBuffer,
		UDS_SCAN_BUFFER_SIZE,
		UDS_SEND_OPTION,
		UDS_RECEIVE_OPTION,
		false
	};

	if(nn::pia::local::UdsNode::CreateInstance(udsNodeSetting).IsFailure())
	{
		nn::pia::local::EndSetup();
		nn::pia::local::Finalize();
		trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		NN_PANIC("nn::pia::local::UdsNode::CreateInstance() Error\n");
		return -1;
	}

	if( nn::pia::local::UdsNode::GetInstance()->Initialize(UDS_NODE_EVENTTHREAD_PRIORITY).IsFailure() )
	{
		if(nn::pia::local::UdsNode::GetInstance() != NULL)
		{
			nn::pia::local::UdsNode::GetInstance()->Finalize();
			nn::pia::local::UdsNode::DestroyInstance();
			NN_LOG("nn::pia::local::UdsNode::DestroyInstance()\n");
		}
		nn::pia::local::EndSetup();
		nn::pia::local::Finalize();
		trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		NN_LOG("UdsNode::GetInstance()->Initialize failed.\n");
		return -1;
	}
	s_DisconnectEvent.Initialize(false);
	nn::pia::local::UdsNode::GetInstance()->RegisterUpdateEventCallback(UdsUpdateEventCallbackFunc, NULL);
	NN_LOG("UdsNode::GetInstance()->Initialize Success.\n");

	nn::pia::local::EndSetup();

	g_nTrlNetworkPiaUdsInited = 1;
	return 0;
}

s32 trlEmuShellNetworkCreateServer()
{
	u32 communicationId = nn::pia::local::UdsNode::GetInstance()->CreateLocalCommunicationId(SAMPLE_TITLE_ID);
	NN_LOG("communicationId = %d\n", communicationId);
	if(nn::pia::local::UdsNode::GetInstance() == NULL)
	{
		NN_LOG("nn::pia::local::UdsNode::GetInstance() NULL\n");
		trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		return -1;
	}
	if(nn::pia::local::UdsNode::GetInstance()->RegisterGathering(
		SAMPLE_SUB_ID,
		SAMPLE_MAX_ENTRY,
		communicationId,
		g_sEmuShellBuffer.szNetworkPassPhrase,
		nn::dlp::MAX_CHILD_UDS_PASSPHRASE_LENGTH,
		SAMPLE_CHANNEL
		).IsFailure())
	{
		NN_LOG("CreateNetwork Error\n");
		trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		return -1;
	}
	NN_LOG("CreateNetwork Success\n");
	return 0;
}

nn::os::StackBuffer<4096> s_SendStackBuffer;
nn::os::StackBuffer<4096> s_ReceiveStackBuffer;

int s_FoundNetworkNum = 0;
nn::pia::local::UdsGatheringHolder s_GatheringList[SCAN_MAX];
nn::pia::local::UdsNodeInformation s_MasterInfo[SCAN_MAX];

s32 trlEmuShellNetworkScanAndJoin()
{
	nn::Result ret;
	g_bTrlNetworkScanAndJoin = 1;
	//scan
	u32 communicationId = nn::pia::local::UdsNode::GetInstance()->CreateLocalCommunicationId(SAMPLE_TITLE_ID);
	while(1)
	{
		ret = nn::pia::local::UdsNode::GetInstance()->FindById(SAMPLE_SUB_ID, communicationId);
		if(ret.IsSuccess())
		{
			NN_LOG("UdsNode::GetInstance()->FindById Success\n");
			size_t sz;
			if(nn::pia::local::UdsNode::GetInstance()->GetGatheringList(s_GatheringList, &sz, SCAN_MAX).IsFailure())
				s_FoundNetworkNum = 0;
			else
				s_FoundNetworkNum = sz;
			NN_LOG("UdsNode::GetInstance()->FindById Success s_FoundNetworkNum = %d\n", s_FoundNetworkNum);
			if ( s_FoundNetworkNum > 0 )
			{
				for (int i=0; i < s_FoundNetworkNum; i++)
				{
					if(!nn::pia::local::UdsNode::GetInstance()->Participate(
						&s_GatheringList[i],
						g_sEmuShellBuffer.szNetworkPassPhrase,
						nn::dlp::MAX_CHILD_UDS_PASSPHRASE_LENGTH
						).IsFailure())
					{
						NN_LOG("Participate %d Success\n", i);
						g_bTrlNetworkScanAndJoin = 0;
						return 0;
					}
				}
			}			
		}
		else
		{
			NN_LOG("UdsNode::GetInstance()->FindById failed.uds state = %d\n", nn::pia::local::UdsNode::GetInstance()->GetState());
			if(nn::pia::local::UdsNode::GetInstance()->GetState() == nn::uds::CTR::STATE_ERROR)
			{
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
				g_bTrlNetworkScanAndJoin = 0;
				return -1;
			}
			nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(1000));
		}
		if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
		{
			g_bTrlNetworkScanAndJoin = 0;
			return -1;
		}
		if(g_nWantCloseNetwork == 1)
		{
			g_bTrlNetworkScanAndJoin = 0;
			return -1;
		}
	}
}

nn::os::Thread s_SendThread;
nn::os::Thread s_RecvThread;

void SaveSendThread(uptr /*param*/)
{
	static int donect = 0;
	extern trlSEmuShellBuffer g_sEmuShellBuffer;
	nn::Result ret;
	static u8 buf[1024*64];
	u32 buflength = 0;

	while(true)
	{
		if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
			return;
		//NN_LOG("SaveSendThread s_MyNodeId = %d  g_pPlayerCmd[s_MyNodeId - 1] = %d\n", s_MyNodeId, g_pPlayerCmd[s_MyNodeId - 1]);
		if(s_MyNodeId == 1)
		{
			if(g_pPlayerCmd[s_MyNodeId - 1] != PLAYER_COMMAND_NONE)
			{
				if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendShareData)
				{
					buflength = 3;
					buf[0] = g_pPlayerCmd[s_MyNodeId - 1];
					buf[1] = s_nPlayerNum;
					buf[2] = g_nTrlNetworkDelay;

					buflength += sizeof(s_pTrlNetworkPlayerMap);
					memcpy(&buf[3], s_pTrlNetworkPlayerMap, sizeof(s_pTrlNetworkPlayerMap));
					ret = nn::pia::local::UdsNode::GetInstance()->SendTo(
						reinterpret_cast<bit8*>(buf),
						buflength,
						nn::pia::local::UDS_NODE_BROADCAST_NODE_ID
						);
				}
				else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_A)
				{				
					buflength = 2;
					buf[0] = g_pPlayerCmd[s_MyNodeId - 1];
					buf[1] = g_pPlayerSaveSeg[0];

					buflength += 1024;
					//copy backup to buf 1024

					/*u8 *pTemp = (u8*)g_sEmuShellBuffer.pBackupData;
					pTemp += 1024*buf[1];
					if( (buf[1]+1) * 1024 <= g_sEmuShellBuffer.nBackupDataSize)
						memcpy(&buf[2], pTemp, 1024);
					else
						memcpy(&buf[2], pTemp, g_sEmuShellBuffer.nBackupDataSize&0x3FF);*/

					u8 *pTemp = g_pTrlNetworkResumeBuf;
					pTemp += 1024*buf[1];
					if( (buf[1]+1) * 1024 <= g_sEmuShellBuffer.nSaveFileSize)
						memcpy(&buf[2], pTemp, 1024);
					else
						memcpy(&buf[2], pTemp, g_sEmuShellBuffer.nSaveFileSize&0x3FF);



					ret = nn::pia::local::UdsNode::GetInstance()->SendTo(
						reinterpret_cast<bit8*>(buf),
						buflength,
						nn::pia::local::UDS_NODE_BROADCAST_NODE_ID
						);
				}
				else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_B)
				{
					buflength = 4;
					buf[0] = g_pPlayerCmd[0];
					buf[1] = g_pPlayerCmd[1];
					buf[2] = g_pPlayerCmd[2];
					buf[3] = g_pPlayerCmd[3];

					ret = nn::pia::local::UdsNode::GetInstance()->SendTo(
						reinterpret_cast<bit8*>(g_pPlayerCmd),
						buflength,
						nn::pia::local::UDS_NODE_BROADCAST_NODE_ID
						);
				}
				else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_C)
				{
					buflength = 4;
					buf[0] = g_pPlayerCmd[0];
					buf[1] = g_pPlayerCmd[1];
					buf[2] = g_pPlayerCmd[2];
					buf[3] = g_pPlayerCmd[3];

					ret = nn::pia::local::UdsNode::GetInstance()->SendTo(
						reinterpret_cast<bit8*>(g_pPlayerCmd),
						buflength,
						nn::pia::local::UDS_NODE_BROADCAST_NODE_ID
						);
					//if ( !ret && ErrorHandling::IsErrorDetected()
					//	&& ErrorHandling::GetResultCode() != nn::uds::ResultBufferIsFull() )
					if(ret.IsSuccess())
						donect++;
				}

				if ( ret.IsFailure() )
				{
					if ( ret == nn::pia::local::ResultInvalidConnection() )
					{
						if( nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_CLIENT &&
							nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_MASTER )
						{
							trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
							NN_LOG("UdsNode: ResultInvalidConnection\n");
							break;
						}
					}
					else if( ret == nn::uds::CTR::ResultBufferIsFull() )
					{
						// no care!
					}
					else if ( !nn::pia::common::ErrorHandler::IsPiaError(ret) )
					{
						trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
						NN_LOG("UdsNode::SendTo Failed.\n");
						ErrorHandling::PrintResult(ret);
						break;                
					}
					/*else// if ( nn::pia::common::ErrorHandler::GetSeverity(ret) != nn::pia::SEVERITY_IGNORABLE )
					{
						trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
						NN_LOG("UdsNode::SendTo Failed.[Pia Error]\n");
						ErrorHandling::PrintResult(ret);
						break;
					}*/
				}
			}
		}
		else
		{	
			if(g_pPlayerCmd[s_MyNodeId - 1] >= PLAYER_COMMAND_SendShareData)
			{
				buflength = 2;
				buf[0] = g_pPlayerCmd[s_MyNodeId - 1];
				buf[1] = g_pPlayerSaveSeg[s_MyNodeId - 1];

				ret = nn::pia::local::UdsNode::GetInstance()->SendTo(
					reinterpret_cast<bit8*>(buf),
					buflength,
					nn::pia::local::UDS_NODE_BROADCAST_NODE_ID
					);

				if ( ret.IsFailure() )
				{
					if ( ret == nn::pia::local::ResultInvalidConnection() )
					{				
						if( nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_CLIENT &&
							nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_MASTER )
						{
							trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
							NN_LOG("UdsNode: ResultInvalidConnection\n");
							break;
						}
					}
					else if ( !nn::pia::common::ErrorHandler::IsPiaError(ret) )
					{
						trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
						NN_LOG("UdsNode::SendTo Failed.\n");
						ErrorHandling::PrintResult(ret);
						break;                
					}
					/*else// if ( nn::pia::common::ErrorHandler::GetSeverity(ret) != nn::pia::SEVERITY_IGNORABLE )
					{
						trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
						NN_LOG("UdsNode::SendTo Failed.[Pia Error]\n");
						ErrorHandling::PrintResult(ret);
						break;
					}*/
				}
			}

			if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_C)
				donect++;
		}
		nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(20));
		if(g_nWantCloseNetwork)
			break;
		if(donect > 4)
			break;
	}
	donect = 0;
	g_nWantCloseReceive = 1;
	NN_LOG("SaveSendThread End\n");
}

void SaveReceiveThread(uptr /*param*/)
{
	nn::Result ret;
	static u8 buf[1024*64];
	u32 buflength = 1024*64;

	g_nWantCloseReceive = 0;

	while(true)
	{
		u16 srcNodeId;
		size_t recvedSize;

		buf[0] = 0;
		buf[1] = 0;

		if(g_nWantCloseReceive)
			break;
		if(g_nWantCloseNetwork)
			break;

		if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
			return;

		ret = nn::pia::local::UdsNode::GetInstance()->ReceiveFrom(
			reinterpret_cast<bit8*>(buf),
			buflength,
			&recvedSize,
			&srcNodeId
			);
		//if ( !ret && ErrorHandling::IsErrorDetected() )
		if(ret.IsFailure())
		{
			if( ret == nn::pia::local::ResultInvalidConnection() )
			{
				if( nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_CLIENT &&
					nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_MASTER )
				{
					trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
					NN_LOG("UdsNode: ResultInvalidConnection\n");
					break;
				}
				nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(2));
			}
			else if ( !nn::pia::common::ErrorHandler::IsPiaError(ret) )
			{
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
				NN_LOG("UdsNode::ReceiveFrom Failed.\n");                
				break;
			}
			/*else// if ( nn::pia::common::ErrorHandler::GetSeverity(ret) != nn::pia::SEVERITY_IGNORABLE )
			{
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
				NN_LOG("UdsNode::ReceiveFrom Failed.[Pia Error]\n");
				break;

			}*/
			nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(2));
			continue;
		}

		if(recvedSize == 0)
		{
			nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(2));
			continue;
		}


		if(s_MyNodeId == 1) //master receive
		{
			g_pPlayerCmd[srcNodeId - 1] = buf[0];
			if(g_pPlayerCmd[srcNodeId - 1] == PLAYER_COMMAND_SendSave_A)
				g_pPlayerSaveSeg[srcNodeId - 1] = buf[1];

			if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendShareData)
			{
				bool alldone = true;
				for(int i=0;i<s_nPlayerNum;i++)
				{
					if(g_pPlayerCmd[i] != PLAYER_COMMAND_SendShareData)
					{	
						alldone = false;
						break;
					}
				}

				if(alldone == true)
				{
					NN_LOG("PLAYER_COMMAND_SendShareData All done\n");
					g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_A;
				}
			}
			else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_A)
			{
				bool alldone = true;
				for(int i=0;i<s_nPlayerNum;i++)
				{
					if(g_pPlayerCmd[i] != PLAYER_COMMAND_SendSave_A || g_pPlayerSaveSeg[i] != g_pPlayerSaveSeg[0])
					{
						//NN_LOG("all done false, i = %d g_pPlayerCmd[i] = %d g_pPlayerSaveSeg[i] = %d(%d)\n", i, g_pPlayerCmd[i],g_pPlayerSaveSeg[i], g_pPlayerSaveSeg[0]);
						alldone = false;
						break;
					}
				}

				if(alldone == true)
				{
					//if(g_pPlayerSaveSeg[0] * 1024 >= g_sEmuShellBuffer.nBackupDataSize)
					if(g_pPlayerSaveSeg[0] * 1024 >=g_sEmuShellBuffer.nSaveFileSize)
					{
						NN_LOG("SaveSeg All done  %d\n", g_sEmuShellBuffer.nSaveFileSize);
						g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_B;
					}
					else
					{
						if((g_pPlayerSaveSeg[0] %10) == 0)
							NN_LOG("SaveSeg %d done\n", g_pPlayerSaveSeg[0]);
						g_pPlayerSaveSeg[0]++;
					}
				}
			}
			else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_B)
			{
				if(buf[0] == PLAYER_COMMAND_SendSave_B)
				{
					if(g_pPlayerCmd[srcNodeId - 1] != PLAYER_COMMAND_SendSave_B)
					{
						NN_LOG("Find Client %d To PLAYER_COMMAND_SendSave_B\n", srcNodeId - 1);
						g_pPlayerCmd[srcNodeId - 1] = PLAYER_COMMAND_SendSave_B;
					}
				}
				else if(buf[0] == PLAYER_COMMAND_SendSave_C)
				{
					if(g_pPlayerCmd[srcNodeId - 1] != PLAYER_COMMAND_SendSave_C)
					{
						NN_LOG("Find Client %d To PLAYER_COMMAND_SendSave_B\n", srcNodeId - 1);
						g_pPlayerCmd[srcNodeId - 1] = PLAYER_COMMAND_SendSave_C;
					}
				}

				bool alldone = true;
				for(int i=0;i<s_nPlayerNum;i++)
					if(g_pPlayerCmd[i] != PLAYER_COMMAND_SendSave_B)
					{
						alldone = false;
						break;
					}
					if(alldone == true)
						g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_C;
			}
		}
		else //client receive
		{
			if(srcNodeId == 1)
			{
				if(buf[0] == PLAYER_COMMAND_SendShareData)
				{					
					g_nSelfState = PLAYER_STATE_SENDSAVE_ING;
					g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendShareData;
					memcpy(s_pTrlNetworkPlayerMap, &buf[3], sizeof(s_pTrlNetworkPlayerMap));
					s_nPlayerNum = buf[1];
					g_nTrlNetworkDelay = buf[2];
					NN_LOG("Client s_nPlayerNum = %d\n", s_nPlayerNum);
				}
				else if(buf[0] == PLAYER_COMMAND_SendSave_A)
				{
					g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_A;
					if(g_pPlayerSaveSeg[s_MyNodeId - 1] == (buf[1] - 1))
					{
						u8 *pTemp = g_pTrlNetworkResumeBuf;
						pTemp += 1024*buf[1];
						if((buf[1] %10) == 0)
							NN_LOG("Clinet %d receive Save Seg %d\n", s_MyNodeId - 1, buf[1]);
						if( (buf[1]+1) * 1024 <= g_sEmuShellBuffer.nSaveFileSize)
							memcpy(pTemp, &buf[2],1024);
						else
							memcpy(pTemp, &buf[2], g_sEmuShellBuffer.nSaveFileSize&0x3FF);
						g_pPlayerSaveSeg[s_MyNodeId - 1] = buf[1];
					}
				}
				else if(buf[0] == PLAYER_COMMAND_SendSave_B)
				{
					if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_A)
					{
						NN_LOG("Client %d To PLAYER_COMMAND_SendSave_B\n", s_MyNodeId - 1);
						g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_B;
					}
					else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_B)
					{
						if(buf[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_B)
						{
							NN_LOG("Client %d To PLAYER_COMMAND_SendSave_C\n", s_MyNodeId - 1);
							g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_C;
						}
					}
					else if(g_pPlayerCmd[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_C)
					{
						if(buf[s_MyNodeId - 1] == PLAYER_COMMAND_SendSave_C)
							break;
					}
				}
				else if(buf[0] == PLAYER_COMMAND_SendSave_C)
				{
					g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_COMMAND_SendSave_C;
					break;
				}
			}
		}
	}
	NN_LOG("SaveReceiveThread End\n");
}

void UdsSendThread(uptr /*param*/)
{
	nn::Result ret;
	static u32 counter[PACKET_SIZE/sizeof(u32) +1 + NETWORK_ADDTION_INFO_LENGTH/sizeof(u32)];

	while (true)
	{
		u32 writtenSize = 0;
		if(g_nWantCloseNetwork)
			break;
		if( s_IsInitPiaSync )
		{
			s_SendEvent.Wait();
			if(g_nWantCloseReceive)
				break;
			if(g_nWantCloseNetwork)
				break;
			if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
				return;
			if( !s_IsInitPiaSync )
			{
				continue;
			}
			nn::pia::sync::HidSync::GetInstance()->GeneratePacket(counter+NETWORK_ADDTION_INFO_LENGTH/sizeof(u32), &writtenSize, PACKET_SIZE);
			counter[0] = g_pPlayerCmd[s_MyNodeId - 1];
			counter[1] = g_pPlayerCmdFrameIndex[s_MyNodeId - 1];
			ret = nn::pia::local::UdsNode::GetInstance()->SendTo(
				reinterpret_cast<bit8*>(counter),
				writtenSize + NETWORK_ADDTION_INFO_LENGTH,
				nn::pia::local::UDS_NODE_BROADCAST_NODE_ID
				);
			if ( ret.IsFailure() )
			{
				if ( ret == nn::pia::local::ResultInvalidConnection() )
				{				
					if( nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_CLIENT &&
						nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_MASTER )
					{
						NN_LOG("UdsNode: ResultInvalidConnection\n");
						trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
						break;
					}
				}
				else if( ret == nn::uds::CTR::ResultBufferIsFull() )
				{
					// no care!
				}
				else if ( !nn::pia::common::ErrorHandler::IsPiaError(ret) )
				{
					NN_LOG("UdsNode::SendTo Failed.\n");
					ErrorHandling::PrintResult(ret);
					trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
					break;                
				}
				/*else// if ( nn::pia::common::ErrorHandler::GetSeverity(ret) != nn::pia::SEVERITY_IGNORABLE )
				{
					NN_LOG("UdsNode::SendTo Failed.[Pia Error]\n");
					ErrorHandling::PrintResult(ret);
					trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_OTHER);
					break;
				}*/
			}
		}
		else
		{
			nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(10) );
		}
	}
	NN_LOG("UdsSendThread is Finish!\n");
}

void UdsRecvThread(uptr /*param*/)
{
	nn::Result ret;
	g_nWantCloseReceive = 0;	
	while(true)
	{
		u16 srcNodeId;
		size_t recvedSize;
		static u32 counter[PACKET_SIZE/sizeof(u32)+1 + NETWORK_ADDTION_INFO_LENGTH/sizeof(u32)];

		if(g_nWantCloseReceive)
		{
			NN_LOG("UdsRecvThread g_nWantCloseReceive = 1\n");
			break;
		}
		if(g_nWantCloseNetwork)
			break;
		if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
			return;

		ret = nn::pia::local::UdsNode::GetInstance()->ReceiveFrom(
			reinterpret_cast<bit8*>(counter),
			PACKET_SIZE + NETWORK_ADDTION_INFO_LENGTH,
			&recvedSize,
			&srcNodeId
			);

		if(ret.IsFailure())
		{
			if( ret == nn::pia::local::ResultInvalidConnection() )
			{
				if( nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_CLIENT &&
					nn::pia::local::UdsNode::GetInstance()->GetState() != nn::uds::STATE_MASTER )
				{
					NN_LOG("UdsNode: ResultInvalidConnection\n");
					trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
					break;
				}
				nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(2));
			}
			else if ( !nn::pia::common::ErrorHandler::IsPiaError(ret) )
			{
				NN_LOG("UdsNode::ReceiveFrom Failed.\n");
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
				break;
			}
			/*else// if ( nn::pia::common::ErrorHandler::GetSeverity(ret) != nn::pia::SEVERITY_IGNORABLE )
			{
				NN_LOG("UdsNode::ReceiveFrom Failed.[Pia Error]\n");
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_OTHER);
				break;
			}*/
			nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(2));
			continue;
		}

		if(recvedSize == 0)
		{
			nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(2));
			continue;
		}

		if(s_IsInitPiaSync)
		{
			//if( (recvedSize -NETWORK_ADDTION_INFO_LENGTH) < 4)
			//	NN_LOG("UdsRecvThread %d\n", recvedSize);
			g_pPlayerCmd[srcNodeId-1] = counter[0];			
			g_pPlayerCmdFrameIndex[srcNodeId - 1] = counter[1];
			nn::pia::sync::HidSync::GetInstance()->AnalyzePacket(counter + NETWORK_ADDTION_INFO_LENGTH/sizeof(u32), recvedSize -NETWORK_ADDTION_INFO_LENGTH);
		}
	}
	NN_LOG("UdsRecvThread is Finish!\n");
}

void trlEmuShellNetworkStartSaveSendThread()
{
	NN_LOG("trlEmuShellNetworkStartSaveSendThread\n");
	g_nTrlNetworkPiaSaveSendTrheadInited = 1;
	g_pTrlNetworkResumeBuf = reinterpret_cast<u8*>(trlMemAlloc(g_sEmuShellBuffer.nSaveFileSize));	
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_PARENT
	trlEmuShellDataSaveResumeData(g_pTrlNetworkResumeBuf, TRL_DATA_RESUME_BACKUP, 0, 0);
#endif

	g_nSelfState = g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_SENDSAVE;

	g_pPlayerSaveSeg[0] = g_pPlayerSaveSeg[1] = g_pPlayerSaveSeg[2] = g_pPlayerSaveSeg[3] = -1;
	g_pPlayerSaveSeg[0] = 0;

	s_SendThread.Start( SaveSendThread, NULL, s_SendStackBuffer, SEND_THREAD_PRIORITY );
	s_RecvThread.Start( SaveReceiveThread, NULL, s_ReceiveStackBuffer, RECEIVE_THREAD_PRIORITY );
	s_SendThread.Join();
	s_SendThread.Finalize();
	s_RecvThread.Join();
	s_RecvThread.Finalize();
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	if(s_nPlayerNum > 2)
		g_nTrlNetwork4PMsg = 1;
	else
		g_nTrlNetwork4PMsg = 0;
	extern CEmuMenu g_hTrlEmuMenu;
	g_hTrlEmuMenu.Convert4PMessage();
#endif


	g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_SENDSAVE_DONE;
	if(g_nWantCloseNetwork || g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
	{
		g_nTrlNetworkPiaSaveSendTrheadInited = 0;
		trlMemFree(g_pTrlNetworkResumeBuf);
		return;
	}
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD

	{
		trlEmuShellDataLoadResumeData(g_pTrlNetworkResumeBuf, TRL_DATA_RESUME_BACKUP);
		trlEmuShellDataResume();
	}
#endif

	trlMemFree(g_pTrlNetworkResumeBuf);

	NETWORK_STATECHANGE_FRAMEDELAY = g_nTrlNetworkDelay;
	NETWORK_STATECHANGE_CONFIRMDELAY = g_nTrlNetworkDelay;

	g_nTrlNetworkPiaSaveSendTrheadInited = 0;
}

void trlEmuShellNetworkStartThread()
{
	g_nTrlNetworkPiaThreadInited = 1;
	s_SendThread.Start( UdsSendThread, NULL, s_SendStackBuffer, SEND_THREAD_PRIORITY );
	s_RecvThread.Start( UdsRecvThread, NULL, s_ReceiveStackBuffer, RECEIVE_THREAD_PRIORITY );
}


const u32 MEMORY_BLOCK_SIZE_PIA = 2 * 1024 * 1024;
//const u32 MEMORY_BLOCK_SIZE_PIA_LOCAL = 16 * 1024;
//const u32 MEMORY_BLOCK_SIZE_PIA_SYNC = 16 * 1024;
bit8 s_PiaMemoryBlock[MEMORY_BLOCK_SIZE_PIA] NN_ATTRIBUTE_ALIGN(4);

nn::os::LightEvent s_StatusUpdateEvent;
nn::Result result;

void triPiaCommonInit()
{
	nn::pia::common::Initialize(s_PiaMemoryBlock, MEMORY_BLOCK_SIZE_PIA);
	nn::pia::common::BeginSetup();
	ErrorHandling::Initialize();
	nn::pia::common::EndSetup();
}

/** @brief EmuShell Network Init */
void trlEmuShellNetworkInit(u32 bMaster)
{
	g_nWantCloseNetwork = 0;

	if(g_nTrlNetworkDelay == -1)
		g_nTrlNetworkDelay = g_sEmuShellBuffer.funcConfigData("NES", "NetDelay", 2);

	NETWORK_STATECHANGE_FRAMEDELAY = g_nTrlNetworkDelay;
	NETWORK_STATECHANGE_CONFIRMDELAY = g_nTrlNetworkDelay;

	trlEmuDLPBootInfo();

	g_nSelfState = g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_INIT;

	g_nTrlNetworkPlayerMapInited = 0;	


	if(trlEmuDLPGetPlayerNum() > 1)
		s_nPlayerNum = trlEmuDLPGetPlayerNum();
	else
		s_nPlayerNum = 2;

	if(s_nPlayerNum > 2)
		g_nTrlNetwork4PMsg = 1;
	else
		g_nTrlNetwork4PMsg = 0;

	s_nConnPlayerNum = 0;

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	s_nPlayerNum = 0;
#endif

	g_bTrlNetworkRole = bMaster;

	s_StatusUpdateEvent.Initialize(false);
	s_SendEvent.Initialize(false);

	if(trlEmuShellNetworkUdsInit() != 0)
		return;

	if(bMaster)
	{
		//create server
		if(trlEmuShellNetworkCreateServer() == -1)
			return;
	}
	else
	{
		//scan and join
		if(trlEmuShellNetworkScanAndJoin() == -1)
			return;
	}
	trlEmuShellNetworkStartSaveSendThread();

	if(g_nWantCloseNetwork || g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
		return;
	/*if(!bMaster)
	if(g_pEmuShellCore->trlEmuCoreSave)
	g_pEmuShellCore->trlEmuCoreSave(0);*/
	nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(100));

	trlEmuShellNetworkStartThread();

	nn::pia::sync::Initialize();
	nn::pia::sync::BeginSetup();



	nn::pia::sync::HidSync::Setting hidSyncSetting;
	hidSyncSetting.startDulation = 32;
	hidSyncSetting.inputDelay = g_nTrlNetworkDelay;
	hidSyncSetting.maxEntry = 4;
#if !TRL_NETWORK_PIA_WITH_MIC
	hidSyncSetting.deviceProfile.syncDeviceList = nn::pia::sync::CTR_PAD;
	hidSyncSetting.deviceProfile.pfsDeviceList = nn::pia::sync::CTR_PAD;
#else
	hidSyncSetting.deviceProfile.syncDeviceList = nn::pia::sync::CTR_PAD | nn::pia::sync::APP_SPECIFIC_DEVICE;
	hidSyncSetting.deviceProfile.pfsDeviceList = nn::pia::sync::CTR_PAD | nn::pia::sync::APP_SPECIFIC_DEVICE;
#endif

	nn::pia::sync::HidSync::CreateInstance( hidSyncSetting );
	//result = nn::pia::sync::HidSync::GetInstance()->Initialize( s_StatusUpdateEvent, s_SendEvent, s_MyConnectionId );
	result = nn::pia::sync::HidSync::GetInstance()->Initialize( s_SendEvent, s_MyStationId );
	if( result.IsFailure() )
	{
		trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
		NN_LOG("nn::pia::sync::HidSync::GetInstance()->Initialize Error\n");
		return;
	}
	NN_LOG("nn::pia::sync::HidSync::GetInstance()->Initialize Success\n");
	nn::pia::sync::EndSetup();
	s_IsInitPiaSync = true;

	NN_LOG("NetworkInit Done\n");
	g_bTrlNetworkIndex = 0;
	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_RUN;
	g_nSelfState = PLAYER_STATE_SYNC;
	trlEmuShellNetworkSetState(PLAYER_COMMAND_SYNCDONE);
	NN_LOG("trlEmuShellNetworkInit End\n");
}
/** @brief EmuShell Network Exit */
void trlEmuShellNetworkExit()
{
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_PARENT
	if(g_nSelfState >PLAYER_STATE_SYNC_DONE)
	{
		trlEmuShellDataReset();
	}
#endif
	g_nWantCloseReceive = 1;
	g_nWantCloseNetwork = 1;

	NN_LOG("trlEmuShellNetworkExit 0\n");	
	//nn::pia::sync::HidSync::GetInstance()->End("HidSync End", 12);
	while(g_bTrlNetworkScanAndJoin == 1)
	{
		g_nWantCloseReceive = 1;
		g_nWantCloseNetwork = 1;
		nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(100));
	}
	g_nWantCloseReceive = 1;
	g_nWantCloseNetwork = 1;
	
	while(g_nTrlNetworkPiaSaveSendTrheadInited == 1)
	{
		nn::os::Thread::Sleep( nn::fnd::TimeSpan::FromMilliSeconds(100));
	}


	void trlEmuNetworkWaitThreadEnd();
	trlEmuNetworkWaitThreadEnd();


	g_nSelfState = g_pPlayerCmd[0] = g_pPlayerCmd[1] = g_pPlayerCmd[2] = g_pPlayerCmd[3] = PLAYER_STATE_NONE;
	

	NN_LOG("trlEmuShellNetworkExit 1\n");
	if(g_nTrlNetworkPiaThreadInited == 1)
	{
		s_SendEvent.Signal();
		s_SendThread.Join();
		s_SendThread.Finalize();

		//s_SendEvent.ClearSignal();
		s_SendEvent.Finalize();
		NN_LOG("trlEmuShellNetworkExit s_SendThread End\n");

		s_RecvThread.Join();
		s_RecvThread.Finalize();
		NN_LOG("trlEmuShellNetworkExit s_RecvThread End\n");
		g_nTrlNetworkPiaThreadInited = 0;
	}

	if(nn::pia::sync::HidSync::GetInstance() != NULL)
	{
		nn::pia::sync::HidSync::GetInstance()->Finalize();
		nn::pia::sync::HidSync::DestroyInstance();
		NN_LOG("nn::pia::sync::HidSync::DestroyInstance()\n");
	}

	if(g_nTrlNetworkPiaUdsInited == 1)
	{
		if(nn::pia::local::UdsNode::GetInstance() != NULL)
		{
			nn::pia::local::UdsNode::GetInstance()->Finalize();
			nn::pia::local::UdsNode::DestroyInstance();
			NN_LOG("nn::pia::local::UdsNode::DestroyInstance()\n");
		}
		nn::pia::local::Finalize();
		g_nTrlNetworkPiaUdsInited = 0;

		s_DisconnectEvent.ClearSignal();
		s_DisconnectEvent.Finalize();
	}
	NN_LOG("trlEmuShellNetworkExit 3\n");



	ErrorHandling::Finalize();

	s_IsInitPiaSync = false;
	g_sEmuShellBuffer.nNetworkState = TRL_NETWORK_STATE_NONE;
	trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NONE);
	NN_LOG("trlEmuShellNetworkExit End\n");

#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	trlEmuShellSuspendEnableHomeButton();
	trlEmuShellsupendEnableSleep();
#endif
}
/** @brief EmuShell Network Command */
void trlEmuShellNetworkCommand(u8 nCMD)
{
	NN_UNUSED_VAR(nCMD);
}

/** @brief EmuShell Network Command */
void trlEmuShellNetworkCommandNew(u8 nCMD)
{
	NN_LOG("trlEmuShellNetworkCommandNew %d g_bTrlNetworkIndex = %d\n", nCMD, g_bTrlNetworkIndex);
	switch(nCMD)
	{
	case TRL_NETWORK_COMMAND_START:
		//g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_STATE_INIT_DONE;			
		//g_pPlayerCmdFrameIndex[s_MyNodeId - 1] = g_bTrlNetworkIndex + NETWORK_COMMAND_FRAMEDELAY;
		break;
	case TRL_NETWORK_COMMAND_READY:
		//g_pPlayerCmd[s_MyNodeId - 1] = PLAYER_STATE_WAIT_TO_PLAY;			
		//g_pPlayerCmdFrameIndex[s_MyNodeId - 1] = g_bTrlNetworkIndex + NETWORK_COMMAND_FRAMEDELAY;
		break;
	}
}

/** @brief EmuShell Network SetState */
void trlEmuShellNetworkSetState(u32 nState)
{
	NN_LOG("Player  %d Say at Frame %d to State %d\n", s_MyNodeId - 1, g_bTrlNetworkIndex + NETWORK_STATECHANGE_FRAMEDELAY, nState);
	g_pPlayerCmd[s_MyNodeId - 1] = nState;			
	g_pPlayerCmdFrameIndex[s_MyNodeId - 1] = g_bTrlNetworkIndex + NETWORK_STATECHANGE_FRAMEDELAY;
}

#define TRL_NETWORK_PIA_PADBUF_NUM 60*60*1
u32 g_pTrlNetworkPIAPadBuf[TRL_NETWORK_PIA_PADBUF_NUM];

/** @brief EmuShell Network Update Input */
void trlEmuShellNetworkUpdateInput()
{
	g_sEmuShellBuffer.bNetworkAsync = 1;
	if(g_sEmuShellBuffer.nNetworkErrorState != TRL_NETWORK_ERROR_STATE_NONE)
		return;
	if( s_IsInitPiaSync )
	{

#if !TRL_NETWORK_PIA_WITH_MIC
		result = nn::pia::sync::HidSync::GetInstance()->Dispatch();
#else
		extern u8 g_nNesInputMic;

		u8	deviceMic = g_nNesInputMic;
		result = nn::pia::sync::HidSync::GetInstance()->Dispatch(reinterpret_cast<bit8*>(&deviceMic), sizeof(deviceMic));
		//if(deviceMic)
		//	NN_LOG("sending mic=%d\n", deviceMic);
#endif
		nn::pia::sync::State state= nn::pia::sync::HidSync::GetInstance()->GetState();
		if( result.IsFailure() && state != nn::pia::sync::STATE_ERROR )
		{
			static int ct = 0;
			ct++;
			if((ct%60) == 0)
			{	
				NN_LOG("nn::pia::sync::HidSync::GetInstance()->Dispatch Error  %d\n", state);
			}
			return;
		}

		// for DebugPrint
		s_nHidSyncState = state;
		s_nHidSyncFrameNo = nn::pia::sync::HidSync::GetInstance()->GetFrameNo();

		static int execCounter = 0;
		switch(state)
		{
		case nn::pia::sync::STATE_NOT_SYNCHRONIZED:
			{
				if(g_bTrlNetworkRole)
				{
					result = nn::pia::sync::HidSync::GetInstance()->WaitEntry(g_pTrlNetworkPiaShareData, sizeof(g_pTrlNetworkPiaShareData));
				}
				else
				{
					result = nn::pia::sync::HidSync::GetInstance()->TryEntry();
				}
				NN_LOG("%s %s s_nHidSyncFrameNo = %d\n", g_bTrlNetworkRole?"WaitEntry":"TryEntry", result.IsSuccess()?"Success":"Failure", s_nHidSyncFrameNo);

			}
			break;
		case nn::pia::sync::STATE_CLIENT_SYNCHRONIZED:
		case nn::pia::sync::STATE_MASTER_SYNCHRONIZED:
			{
				s32 readNum;
				nn::hid::PadStatus synchronizedPadStatus[4];
				g_nTrlNetworkInput = 0;
				for(u8 i=0;i<s_nPlayerNum;i++)
				{
					if(g_pPlayerState[i] == PLAYER_STATE_EXIT)
						continue;
					if(nn::pia::sync::HidSync::GetInstance() == NULL)
						return;
					if(nn::pia::sync::HidSync::GetInstance()->GetState() == nn::pia::sync::STATE_ERROR)
						return;
					result = nn::pia::sync::HidSync::GetInstance()->ReadCtrPad(s_AddressTable.ToStationId( i + 1), &synchronizedPadStatus[i], &readNum, 1 );
					if( result.IsFailure())// && result != nn::pia::sync::ResultSyncDataIsNotArrivedYet())
					{
						NN_LOG("ReadCtrPad %d fail s_nHidSyncFrameNo = %d\n", i, s_nHidSyncFrameNo);
						return;
					}
					else if(readNum != 0)
					{
						// copy & mod from trlEmuShellInputUpdate()
						synchronizedPadStatus[i].hold |= synchronizedPadStatus[i].trigger;
						synchronizedPadStatus[i].hold |= ((synchronizedPadStatus[i].hold & (nn::hid::CTR::BUTTON_X | nn::hid::CTR::BUTTON_Y))>>9);
						synchronizedPadStatus[i].hold |= ((synchronizedPadStatus[i].hold & nn::hid::CTR::PLUS_BUTTON_EMULATION_MASK)>>24);
						if((synchronizedPadStatus[i].hold & (nn::hid::CTR::BUTTON_RIGHT|nn::hid::CTR::BUTTON_LEFT)) == (nn::hid::CTR::BUTTON_RIGHT|nn::hid::CTR::BUTTON_LEFT))
						{
							synchronizedPadStatus[i].hold &= ~nn::hid::CTR::BUTTON_RIGHT;
						}
						if((synchronizedPadStatus[i].hold & (nn::hid::CTR::BUTTON_UP|nn::hid::CTR::BUTTON_DOWN)) == (nn::hid::CTR::BUTTON_UP|nn::hid::CTR::BUTTON_DOWN))
						{
							synchronizedPadStatus[i].hold &= ~nn::hid::CTR::BUTTON_DOWN;
						}

						u32 nPad = synchronizedPadStatus[i].hold & g_sEmuShellBuffer.nKeyMask;
						g_nTrlNetworkInput |= (nPad & 0x000000FF) << (s_pTrlNetworkPlayerMap[i]*8);
					}
				}
#if TRL_NETWORK_PIA_WITH_MIC
					//read only from 2P with MIC
					//if(i==1)
				g_nTrlNetworkInputMic = 0;
					{
						u8 mic_data_2P[64];

						result = nn::pia::sync::HidSync::GetInstance()->ReadAppSpecificDevice( s_AddressTable.ToStationId(2), mic_data_2P );
						if( result.IsFailure())// && result != nn::pia::sync::ResultDataIsNotArrivedYet)
						{
							state= nn::pia::sync::HidSync::GetInstance()->GetState();
							NN_LOG("ReadAppSpecificDevice 2 fail s_nHidSyncFrameNo = %d state=%d\n", s_nHidSyncFrameNo, state);
							return;
						}
						else
						{
							extern u8 g_nNesInputMic;
							g_nTrlNetworkInputMic = mic_data_2P[0];
							g_nNesInputMic = g_nTrlNetworkInputMic;
						}
					}
#endif
				/*{	
					static int ct = 0;					
					if( (ct%60) == 0)
					{						
						NN_LOG("%d(%d) %d(%d) %d(%d) %d(%d):State %d %d %d %d   %d %d-%d\n",
						g_pPlayerCmd[0], g_pPlayerCmdFrameIndex[0],
						g_pPlayerCmd[1], g_pPlayerCmdFrameIndex[1],
						g_pPlayerCmd[2], g_pPlayerCmdFrameIndex[2],
						g_pPlayerCmd[3], g_pPlayerCmdFrameIndex[3],
						g_pPlayerState[0],
						g_pPlayerState[1],
						g_pPlayerState[2],
						g_pPlayerState[3],
						g_nSelfState, s_nHidSyncFrameNo,g_bTrlNetworkIndex);
						NN_LOG(" Map: %d %d %d %d Input 0x%x\n",
						s_pTrlNetworkPlayerMap[0],
						s_pTrlNetworkPlayerMap[1],
						s_pTrlNetworkPlayerMap[2],
						s_pTrlNetworkPlayerMap[3],
						g_nTrlNetworkInput);
						
					}
					ct++;					
				}*/

				g_sEmuShellBuffer.bNetworkAsync = 0;
				for(u8 i=0;i<s_nPlayerNum;i++)
				{
					if(g_pPlayerCmdFrameIndex[i] == g_bTrlNetworkIndex)
					{	
						//if (i != (s_MyNodeId - 1))
						{
							//g_nSelfState = g_pPlayerCmd[i];
							switch(g_pPlayerCmd[i])
							{
							case PLAYER_COMMAND_SYNCDONE:
								g_pPlayerState[i] = PLAYER_STATE_SYNC_DONE;
								break;
							case PLAYER_COMMAND_CLOSEMENU:
								g_pPlayerState[i] = PLAYER_STATE_WAIT_TO_PLAY;
								break;
							case PLAYER_COMMAND_RESET:
								{
									//void nesEmuCoreReset();
									//nesEmuCoreReset();
									trlEmuShellDataReset();
								}
								g_pPlayerState[i] = PLAYER_STATE_WAIT_TO_PLAY;
								break;
							case PLAYER_COMMAND_PLAYGAME:
								g_pPlayerState[i] = PLAYER_STATE_PLAYGAME;
								break;
							case PLAYER_COMMAND_OPENMENU:
								g_pPlayerState[i] = PLAYER_STATE_MENU;
								break;
							case PLAYER_COMMAND_QUIT:
								g_pPlayerState[i] = PLAYER_STATE_WAIT_TO_QUIT;
								break;

							}
						}
						NN_LOG("at Frame %d Player %d PlayerState Confirm to %d\n",g_bTrlNetworkIndex, i, g_pPlayerState[i]);
					}
				}
				if(g_nPlayerStateChangeDelay > 0)
					g_nPlayerStateChangeDelay--;

				switch(g_nSelfState)
				{
				case PLAYER_STATE_SYNC:
					{
						u32 alldone = 1;
						for(u8 i=0;i<s_nPlayerNum;i++)
						{							
							if(g_pPlayerState[i] != PLAYER_STATE_SYNC_DONE || g_pPlayerCmdFrameIndex[i] > g_bTrlNetworkIndex)
							{
								alldone = 0;
								break;
							}
						}
						if(alldone == 1)
						{
							g_nPlayerStateChangeDelay = NETWORK_STATECHANGE_CONFIRMDELAY;
							g_nSelfState = PLAYER_STATE_SYNC_DONE;							
							NN_LOG("At Frame %d, to PLAYER_STATE_SYNC_DONE\n", g_bTrlNetworkIndex);							
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
							extern u32 g_nTrlEmuVideoPause;
							g_nTrlEmuVideoPause = 10;
#endif

						}
					}
					break;
				case PLAYER_STATE_SYNC_DONE:
					{
						if(g_pPlayerState[0] == PLAYER_STATE_WAIT_TO_PLAY)
						{
							g_nPlayerStateChangeDelay = NETWORK_STATECHANGE_CONFIRMDELAY;
							g_nSelfState = PLAYER_STATE_WAIT_TO_PLAY;
							g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_WAIT_TO_PLAY;
							NN_LOG("At Frame %d, to PLAYER_STATE_WAIT_TO_PLAY\n", g_bTrlNetworkIndex);
							trlEmuShellDataReset();
						}
					}
					break;				
				case PLAYER_STATE_WAIT_TO_PLAY:
					{
						u32 alldone = 1;
						for(u8 i=0;i<s_nPlayerNum;i++)
						{
							if(g_pPlayerState[i] != PLAYER_STATE_PLAYGAME || g_pPlayerCmdFrameIndex[i] > g_bTrlNetworkIndex)
							{
								alldone = 0;
								break;
							}
						}
						if(alldone == 1)
						{
							g_nPlayerStateChangeDelay = NETWORK_STATECHANGE_CONFIRMDELAY;
							g_nSelfState = PLAYER_STATE_PLAYGAME;	
							NN_LOG("At Frame %d, to PLAYER_STATE_PLAYGAME\n", g_bTrlNetworkIndex);
						}
					}
					break;
				case PLAYER_STATE_WAIT_TO_QUIT:
					break;
				case PLAYER_STATE_PLAYGAME:
					{						
						for(u8 i=0;i<s_nPlayerNum;i++)
						{
							if(g_pPlayerState[i] == PLAYER_STATE_MENU)
							{
								g_nPlayerStateChangeDelay = NETWORK_STATECHANGE_CONFIRMDELAY;
								g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_OTHER_MENU;
								g_pPlayerState[i] = PLAYER_STATE_MENU;
								if (i == (s_MyNodeId - 1))
								{	
									g_nMenuCaller = i;
									g_nSelfState = PLAYER_STATE_MENU;
									NN_LOG("At Frame %d, to PLAYER_STATE_MENU\n", g_bTrlNetworkIndex);
								}
								else
								{
									g_nMenuCaller = i;
									g_nSelfState = PLAYER_STATE_OTHER_MENU;
									NN_LOG("At Frame %d, to PLAYER_STATE_OTHER_MENU\n", g_bTrlNetworkIndex);
								}
								g_vcm_specialplayer = s_pTrlNetworkPlayerMap[i];
							}
						}					
					}
					break;
				case PLAYER_STATE_MENU:
				case PLAYER_STATE_OTHER_MENU:
					{
						if(g_pPlayerState[g_nMenuCaller] == PLAYER_STATE_WAIT_TO_PLAY)
						{
							g_nPlayerStateChangeDelay = NETWORK_STATECHANGE_CONFIRMDELAY;
							g_nSelfState = PLAYER_STATE_WAIT_TO_PLAY;
							g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_WAIT_TO_PLAY;
							NN_LOG("At Frame %d, to PLAYER_STATE_WAIT_TO_PLAY\n", g_bTrlNetworkIndex);
						}
						else if(g_pPlayerState[g_nMenuCaller] == PLAYER_STATE_WAIT_TO_QUIT)
						{
							if(g_nMenuCaller == 0)
								trlEmuShellNetworkSetErrorState(TRL_NETWORK_EEEOR_STATE_MASTERLEAVE);
							else
								trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_LEAVE);
							g_vcm_specialplayer = s_pTrlNetworkPlayerMap[g_nMenuCaller];

							g_nPlayerStateChangeDelay = NETWORK_STATECHANGE_CONFIRMDELAY;
							g_nSelfState = PLAYER_STATE_WAIT_TO_QUIT;
							g_pPlayerState[0] = g_pPlayerState[1] = g_pPlayerState[2] = g_pPlayerState[3] = PLAYER_STATE_WAIT_TO_QUIT;
							NN_LOG("At Frame %d, to PLAYER_STATE_WAIT_TO_QUIT\n", g_bTrlNetworkIndex);
						}
					}
					break;
				}
				g_bTrlNetworkIndex++;
				//Workaroud: HidSync will be implemented TouchPanel-Read API...
				//trlEmuShellInputUpdateTouch();
				//g_pEmuShellCore->trlEmuCoreInput(g_nTrlNetworkInput);
			}
			break;
		case nn::pia::sync::STATE_MASTER_WAIT_ENTRY:
			{
				int allready = 1;
				for(int i=0;i<s_nPlayerNum;i++)
					if( nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(i)) != nn::pia::sync::READY_TO_START)
						allready = 0;

				if(allready == 1)
				{
					result = nn::pia::sync::HidSync::GetInstance()->Start();
					if( result.IsFailure() )
					{
						NN_LOG("nn::pia::sync::HidSync::GetInstance()->Start Error\n");
					}
				}
				else
				{
					execCounter++;
					if( (execCounter%60) == 0)
					{
						NN_LOG("WaitEntry... EntryState:%d, %d, %d, %d\n",
							nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(0)),
							nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(1)),
							nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(2)),
							nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(3)) );
					}
				}
			}
			break;
		case nn::pia::sync::STATE_CLIENT_WAIT_SYNCHRONIZATION:
			{
				//new function of Pia 1.1.2: execute just 1time.
				static bool isExecReadyToStart = false;
				if( !isExecReadyToStart )
				{
					result = nn::pia::sync::HidSync::GetInstance()->ReadyToStart();
					if( result.IsFailure() )
					{
						NN_LOG("nn::pia::sync::HidSync::GetInstance()->ReadyToStart Error\n");
					}
					isExecReadyToStart =true;
				}
				execCounter++;
				if( (execCounter%60) == 0)
				{
					NN_LOG("WaitSync... EntryState:%d, %d, %d, %d\n",
						nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(0)),
						nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(1)),
						nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(2)),
						nn::pia::sync::HidSync::GetInstance()->CheckEntry(static_cast<nn::pia::StationId>(3)) );



				}
			}
			break;
		case nn::pia::sync::STATE_ERROR:
			{
				trlEmuShellNetworkSetErrorState(TRL_NETWORK_ERROR_STATE_NETWORK);
				//NN_LOG("nn::pia::sync::HidSync::GetInstance()->GetState() == ERROR\n");
			}
			break;
		default:
			{
				//NN_LOG("UnknownState: %d s_nHidSyncFrameNo = %d\n", state, s_nHidSyncFrameNo);
			}
		}
	}
	else
	{
		NN_LOG("s_IsInitPiaSync = false\n");
	}
}
/** @brief EmuShell Network Get Player Name */
const wchar_t* trlEmuShellNetworkGetPlayerName(u32 nID)
{
	NN_UNUSED_VAR(nID);
	return NULL;
}

/** @brief EmuShell Network Input Valid */
bool trlEmuShellNetworkInputValid()
{
	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE)
		return true;
	else
	{
		if(g_sEmuShellBuffer.bNetworkAsync == 0)
		{
			if(g_nSelfState == PLAYER_STATE_PLAYGAME)
				return true;
		}
		return false;
	}
}

/** @brief EmuShell Network Get Self Player State */
u32 trlEmuShellNetworkGetSelfPlayerState()
{
	if(g_nPlayerStateChangeDelay == 0)
		return g_nSelfState;
	else
		return PLAYER_STATE_NONE;
}
/** @brief EmuShell Network SetErrorState */
void trlEmuShellNetworkSetErrorState(u32 error)
{	
	if(error == TRL_NETWORK_ERROR_STATE_NONE)
	{
		NN_LOG("TRL_NETWORK_ERROR_STATE_NONE\n"); 
		g_sEmuShellBuffer.nNetworkErrorState = TRL_NETWORK_ERROR_STATE_NONE;
	}
	else
	{
		if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_NONE)
		{
			NN_LOG("TRL_NETWORK_ERROR  %d\n", error);
			g_sEmuShellBuffer.nNetworkErrorState = error;
		}
		else if(g_sEmuShellBuffer.nNetworkErrorState == TRL_NETWORK_ERROR_STATE_OTHER)
		{
			NN_LOG("TRL_NETWORK_ERROR  %d\n", error);
			g_sEmuShellBuffer.nNetworkErrorState = error;
		}
	}
}
#endif
