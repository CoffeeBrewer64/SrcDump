/**
* @file trlEmuMenuDataButton.h
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"

extern trlEmuMenuButtonAnim cgbvcm_btanim_firsttime;
extern trlEmuMenuButtonAnim cgbvcm_btanim_main;
extern trlEmuMenuButtonAnim cgbvcm_btanim_message;
extern trlEmuMenuButtonAnim cgbvcm_btanim_message_nosram;
extern trlEmuMenuButtonAnim cgbvcm_btanim_nmain;
extern trlEmuMenuButtonAnim cgbvcm_btanim_nmessage;
extern trlEmuMenuButtonAnim cgbvcm_btanim_nmessage_nosram;
extern trlEmuMenuButtonAnim errvcm_btanim_error;

extern trlEmuMenuButtonAnim cgbvcm_btanim_messagedl;
extern trlEmuMenuButtonAnim cgbvcm_btanim_childmain;

extern trlEmuMenuButtonAnim cgbvcm_btanim_commonwindow;
extern trlEmuMenuButtonAnim cgbvcm_btanim_commonwindow;
/////////////////
//firsttime
enum ECGBVCMButtonFirstTimeW00
{
	eCGBVCMButtonFirstTime_w00btl = 0,
	eCGBVCMButtonFirstTime_w00btr
};
enum ECGBVCMButtonFirstTimeW01
{
	eCGBVCMButtonFirstTime_w01btl = 0,
	eCGBVCMButtonFirstTime_w01btr
};
enum ECGBVCMButtonFirstTimeW02
{
	eCGBVCMButtonFirstTime_w02btl = 0,
	eCGBVCMButtonFirstTime_w02btr
};
enum ECGBVCMButtonFirstTimeW03
{
	eCGBVCMButtonFirstTime_w03btl =0,
	eCGBVCMButtonFirstTime_w03btr
};

extern trlEmuMenuButton cgbvcm_bt_firstime_w00btl;
extern trlEmuMenuButton cgbvcm_bt_firstime_w00btr;
extern trlEmuMenuButton cgbvcm_bt_firstime_w01btl;
extern trlEmuMenuButton cgbvcm_bt_firstime_w01btr;
extern trlEmuMenuButton cgbvcm_bt_firstime_w02btl;
extern trlEmuMenuButton cgbvcm_bt_firstime_w02btr;
extern trlEmuMenuButton cgbvcm_bt_firstime_w03btl;
extern trlEmuMenuButton cgbvcm_bt_firstime_w03btr;

/////////////////
//dlp main
enum ECGBVCMButtonDLPMain
{
	eCGBVCMButtonDLPMain_Resume = 0,	
	eCGBVCMButtonDLPMain_Reset,
	eCGBVCMButtonDLPMain_DL
};

/////////////////
//main
enum ECGBVCMButtonMain
{
	eCGBVCMButtonMain_Resume = 0,
	eCGBVCMButtonMain_Save,
	eCGBVCMButtonMain_Reset,
	eCGBVCMButtonMain_Load,	
	eCGBVCMButtonMain_DL
};
extern trlEmuMenuButton cgbvcm_bt_main_resume;
extern trlEmuMenuButton cgbvcm_bt_main_save;
extern trlEmuMenuButton cgbvcm_bt_main_reset;
extern trlEmuMenuButton cgbvcm_bt_main_load;
extern trlEmuMenuButton cgbvcm_bt_main_dl;




/////////////////
//message
enum ECGBVCMButtonSave
{
	eCGBVCMButtonMessage_SaveNo = 0,
	eCGBVCMButtonMessage_SaveYes
};
enum ECGBVCMButtonSaveOk
{
	eCGBVCMButtonMessage_SaveOk = 0
};
enum ECGBVCMButtonLoad
{
	eCGBVCMButtonMessage_LoadNo =0,
	eCGBVCMButtonMessage_LoadYes
};
enum ECGBVCMButtonLoadOk
{
	eCGBVCMButtonMessage_LoadOk = 0
};
enum ECGBVCMButtonReset
{
	eCGBVCMButtonMessage_ResetNo = 0,
	eCGBVCMButtonMessage_ResetYes
};

extern trlEmuMenuButton cgbvcm_bt_message_saveno;
extern trlEmuMenuButton cgbvcm_bt_message_saveyes;
extern trlEmuMenuButton cgbvcm_bt_message_saveok;
extern trlEmuMenuButton cgbvcm_bt_message_loadno;
extern trlEmuMenuButton cgbvcm_bt_message_loadyes;
extern trlEmuMenuButton cgbvcm_bt_message_loadok;
extern trlEmuMenuButton cgbvcm_bt_message_resetno;
extern trlEmuMenuButton cgbvcm_bt_message_resetyes;

/////////////////
//message nosram
enum ECGBVCMButtonMessageNoSRAM
{
	eCGBVCMButtonMessageNoSRAM_SaveNo = 0,
	eCGBVCMButtonMessageNoSRAM_SaveYes,
	eCGBVCMButtonMessageNoSRAM_SaveOk,
	eCGBVCMButtonMessageNoSRAM_LoadNo,
	eCGBVCMButtonMessageNoSRAM_LoadYes,
	eCGBVCMButtonMessageNoSRAM_LoadOk,
	eCGBVCMButtonMessageNoSRAM_ResetNo,
	eCGBVCMButtonMessageNoSRAM_ResetYes
};

extern trlEmuMenuButton cgbvcm_bt_message_nosram_saveno;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_saveyes;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_saveok;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_loadno;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_loadyes;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_loadok;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_resetno;
extern trlEmuMenuButton cgbvcm_bt_message_nosram_resetyes;

/////////////////
//normal main
enum ECGBVCMButtonNMain
{
	eCGBVCMButtonNMain_Resume = 0,	
	eCGBVCMButtonNMain_Reset,
	//eCGBVCMButtonNMain_Change
	eCGBVCMButtonNMain_DL
};
extern trlEmuMenuButton cgbvcm_bt_nmain_resume;
extern trlEmuMenuButton cgbvcm_bt_nmain_reset;
//extern trlEmuMenuButton cgbvcm_bt_nmain_change;
extern trlEmuMenuButton cgbvcm_bt_nmain_dl;

/////////////////
//normal message
enum ECGBVCMButtonNMessageReset
{
	eCGBVCMButtonNMessage_ResetNo = 0,
	eCGBVCMButtonNMessage_ResetYes
};

enum ECGBVCMButtonNMessageMsg00
{
	eCGBVCMButtonNMessage_Msg00BtL = 0,
	eCGBVCMButtonNMessage_Msg00BtR
};
enum ECGBVCMButtonNMessageMsg01
{
	eCGBVCMButtonNMessage_Msg01BtL = 0,
	eCGBVCMButtonNMessage_Msg01BtR
};
extern trlEmuMenuButton cgbvcm_bt_nmessage_resetno;
extern trlEmuMenuButton cgbvcm_bt_nmessage_resetyes;
extern trlEmuMenuButton cgbvcm_bt_nmessage_msg00btl;
extern trlEmuMenuButton cgbvcm_bt_nmessage_msg00btr;
extern trlEmuMenuButton cgbvcm_bt_nmessage_msg01btl;
extern trlEmuMenuButton cgbvcm_bt_nmessage_msg01btr;

/////////////////
//normal message no sram
enum ECGBVCMButtonNMessageNoSRAM
{
	eCGBVCMButtonNMessageNoSRAM_Msg00BtL = 0,
	eCGBVCMButtonNMessageNoSRAM_Msg00BtR,
	eCGBVCMButtonNMessageNoSRAM_Msg01BtL,
	eCGBVCMButtonNMessageNoSRAM_Msg01BtR
};
extern trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg00btl;
extern trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg00btr;
extern trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg01btl;
extern trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg01btr;

/////////////////
//error
enum EERRVCMButtonErrorYesNo
{
	eERRVCMButtonError_No = 0,
	eERRVCMButtonError_Yes
};
enum EERRVCMButtonErrorOk
{
	eERRVCMButtonError_Ok = 0
};
extern trlEmuMenuButton errvcm_bt_error_no;
extern trlEmuMenuButton errvcm_bt_error_yes;
extern trlEmuMenuButton errvcm_bt_error_ok;

/////////////////////
//message dl
enum ECGBVCMButtonMessageDLYN
{
	eCGBVCMButtonMessageDLYN_No = 0,
	eCGBVCMButtonMessageDLYN_Yes
};
extern trlEmuMenuButton cgbvcm_bt_messagedl_no;
extern trlEmuMenuButton cgbvcm_bt_messagedl_yes;

/////////////////
//common window
enum ECGBVCMButtonCommonWindowYN
{
	eCGBVCMButtonCommonWindow_YNNo = 0,
	eCGBVCMButtonCommonWindow_YNYes
};
enum ECGBVCMButtonCommonWindowOk
{
	eCGBVCMButtonCommonWindow_Ok = 0
};
extern trlEmuMenuButton cgbvcm_bt_commonwindow_ynno;
extern trlEmuMenuButton cgbvcm_bt_commonwindow_ynyes;
extern trlEmuMenuButton cgbvcm_bt_commonwindow_ok;

/////////////////
//netplay child
enum ECGBVCMButtonNetPlayChild
{
	eCGBVCMButtonNetPlayChild_Resume = 0,
	eCGBVCMButtonNetPlayChild_Disconn
};
extern trlEmuMenuButton cgbvcm_bt_netplaychild_resume;
extern trlEmuMenuButton cgbvcm_bt_netplaychild_disconn;
