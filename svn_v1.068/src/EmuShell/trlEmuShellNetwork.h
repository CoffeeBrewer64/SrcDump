/**
 * @file trlEmuShellNetwork.h
 * @author Chentian
 * @date 2011.03.23
 * @brief TRL Emulate - EmuShell Network Module
 */
#pragma once
#include "trlEmuShellStruct.h"

/** @name Macro Define */
//@{
#define TRL_NETWORK_CLIENT_MAX				3

extern u32 g_nTrlNetwork4PMsg;
extern u32 g_nTrlNetworkClintNum;
enum PLAYER_COMMAND
{
	PLAYER_COMMAND_NONE = 0,
	PLAYER_COMMAND_SendShareData,
	PLAYER_COMMAND_SendSave_A,
	PLAYER_COMMAND_SendSave_B,
	PLAYER_COMMAND_SendSave_C,
	PLAYER_COMMAND_SendSave_D,
	PLAYER_COMMAND_SYNCDONE,
	PLAYER_COMMAND_CLOSEMENU,
	PLAYER_COMMAND_QUIT,
	PLAYER_COMMAND_RESET,
	PLAYER_COMMAND_PLAYGAME,
	PLAYER_COMMAND_OPENMENU,
	PLAYER_COMMAND_TONORMAL
};

enum PLAYER_STATE
{
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_INIT,	
	PLAYER_STATE_SENDSAVE,
	PLAYER_STATE_SENDSAVE_ING,
	PLAYER_STATE_SENDSAVE_DONE,
	PLAYER_STATE_SYNC,
	PLAYER_STATE_SYNC_DONE,
	PLAYER_STATE_WAIT_TO_PLAY,
	PLAYER_STATE_WAIT_TO_QUIT,
	PLAYER_STATE_PLAYGAME,
	PLAYER_STATE_MENU,
	PLAYER_STATE_OTHER_MENU,
	PLAYER_STATE_CLOSEMENU,
	PLAYER_STATE_EXIT
};

#define TRL_NETWORK_BUF_ALL					TRL_EMUCORE_NETWORK_BUFSIZE
#define TRL_NETWORK_BUF_HALF				(TRL_NETWORK_BUF_ALL>>1)
#define TRL_NETWORK_BUF_AVAIL				(TRL_NETWORK_BUF_HALF+1)

#define TRL_NETWORK_ERROR_STATE_NONE		0x00
#define TRL_NETWORK_EEEOR_STATE_MASTERLEAVE 0x01
#define TRL_NETWORK_ERROR_STATE_LEAVE		0x02
#define TRL_NETWORK_ERROR_STATE_NETWORK		0x03
#define TRL_NETWORK_ERROR_STATE_OTHER		0x04

#define TRL_NETWORK_STATE_NONE				0x00
#define TRL_NETWORK_STATE_INIT				0x01
#define TRL_NETWORK_STATE_RUN				0x02
#define TRL_NETWORK_STATE_PAUSE				0x03
#define TRL_NETWORK_STATE_CLOSE				0x04
#define TRL_NETWORK_STATE_READY				0x05
#define TRL_NETWORK_STATE_ERROR				0x06
#define TRL_NETWORK_STATE_EXIT				0x07
#define TRL_NETWORK_STATE_LOAD				0x08
#define TRL_NETWORK_STATE_RESET				0x09

#define TRL_NETWORK_STATE_MASTERLEAVE       0x0A

//#define TRL_NETWORK_RESULT_SUCCESS			0x00
//#define TRL_NETWORK_RESULT_FAILURE			0x01
//#define TRL_NETWORK_RESULT_WIRELESSOFF		0x02
//#define TRL_NETWORK_RESULT_WIRELESSOCCUPIED	0x03

#define TRL_NETWORK_COMMAND_NONE			0x00
#define TRL_NETWORK_COMMAND_START			0x01 //PIA SYNC START
#define TRL_NETWORK_COMMAND_RESUME			0x02
#define TRL_NETWORK_COMMAND_PAUSE			0x03
#define TRL_NETWORK_COMMAND_CLOSE			0x04
#define TRL_NETWORK_COMMAND_RESET			0x05
#define TRL_NETWORK_COMMAND_LOAD			0x06
#define TRL_NETWORK_COMMAND_FINISH			0x07
#define TRL_NETWORK_COMMAND_DISCONNECT		0x08
#define TRL_NETWORK_COMMAND_DESTROY			0x09

#define TRL_NETWORK_COMMAND_READY			0x0A
#define TRL_NETWORK_COMMAND_PLAY			0x0B
#define TRL_NETWORK_COMMAND_QUIT			0x0C
//@}

/** @name Global Variable */
//@{
extern u32 g_nTrlNetworkInput;
//@}


#define TRL_NETWROK_NONE 0
#define TRL_NETWORK_IR 0
#define TRL_NETWORK_PIA 1


#if TRL_NETWROK_NONE
#define trlEmuShellNetworkInit(n) ((void)0)
#define trlEmuShellNetworkExit() ((void)0)
#define trlEmuShellNetworkCommand(n) ((void)0)
#define trlEmuShellNetworkCommandNew(n) ((void)0)
#define trlEmuShellNetworkSetState(n) ((void)0)
#define trlEmuShellNetworkUpdateInput() ((void)0)
#define trlEmuShellNetworkGetPlayerName(n ) ((void*)0)
#define trlEmuShellNetworkInputValid() ((void)0)
#define trlEmuShellNetworkGetSelfPlayerState() ((void)0)
#define trlEmuShellNetworkSetErrorState() ((void)0)
#else
/** @brief EmuShell Network Init */
void trlEmuShellNetworkInit(u32 bMaster);
/** @brief EmuShell Network Exit */
void trlEmuShellNetworkExit();
/** @brief EmuShell Network Command */
void trlEmuShellNetworkCommand(u8 nCMD);
/** @brief EmuShell Network Command */
void trlEmuShellNetworkCommandNew(u8 nCMD);
/** @brief EmuShell Network SetState */
void trlEmuShellNetworkSetState(u32 nState);
/** @brief EmuShell Network Update Input */
void trlEmuShellNetworkUpdateInput();
/** @brief EmuShell Network Get Player Name */
const wchar_t* trlEmuShellNetworkGetPlayerName(u32 nID);
/** @brief EmuShell Network Input Sync */
bool trlEmuShellNetworkInputValid();
/** @brief EmuShell Network Get Self Player State */
u32 trlEmuShellNetworkGetSelfPlayerState();
/** @brief EmuShell Network SetErrorState */
void trlEmuShellNetworkSetErrorState(u32 error);
#endif
