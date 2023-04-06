/**
* @file trlEmuMenuDataLayout.h
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#pragma once
#include "../../../trlMacro.h"
#include "../../trlEmuShellStruct.h"
#include "../../trlEmuShellNetWork.h"
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"

////////////////////////
//layout resource
////////////////////////

////////////CGBVCM
enum ECGBVCMLayout
{
	eCGBVCMLayout_FirstTime = 0,
	eCGBVCMLayout_Main,
	eCGBVCMLayout_Message,
	eCGBVCMLayout_MessageNoSRAM,
	eCGBVCMLayout_ModeChange,
	eCGBVCMLayout_NMain,
	eCGBVCMLayout_NMessage,
	eCGBVCMLayout_NMessageNoSRAM,
	eCGBVCMLayout_ChildMain,
	eCGBVCMLayout_MessageDL,
	eCGBVCMLayout_Warning_DL,
	//eCGBVCMLayout_MultiMain,
	//eCGBVCMLayout_MultiMain2,
	//eCGBVCMLayout_MultiMain3,
	//eCGBVCMLayout_MessageWindow,
	eCGBVCMLayoutNum
};

extern trlEmuMenuLayout cgbvcm_layout_firsttime;
extern trlEmuMenuLayout cgbvcm_layout_main;
extern trlEmuMenuLayout cgbvcm_layout_message;
extern trlEmuMenuLayout cgbvcm_layout_message_nosram;
extern trlEmuMenuLayout cgbvcm_layout_modechange;
extern trlEmuMenuLayout cgbvcm_layout_nmain;
extern trlEmuMenuLayout cgbvcm_layout_nmessage;
extern trlEmuMenuLayout cgbvcm_layout_nmessage_nosram;

//extern trlEmuMenuLayout cgbvcm_layout_multimain;
//extern trlEmuMenuLayout cgbvcm_layout_multimain2;
//extern trlEmuMenuLayout cgbvcm_layout_multimain3;

extern trlEmuMenuLayout cgbvcm_layout_childmain;
extern trlEmuMenuLayout cgbvcm_layout_messagedl;
extern trlEmuMenuLayout cgbvcm_layout_warningdl;



extern trlEmuMenuLayout commonwindow_layout_main;

extern char *pCGBVCMLayoutName[];
extern trlEmuMenuLayout* cgbvcm_layout[];
////////////ERRVCM
enum EERRVCMLayout
{
	eERRVCMLayout_Message = 0,
	eERRVCMLayoutNum
};

extern trlEmuMenuLayout errvcm_layout_error;

extern trlEmuMenuLayout* errvcm_layout[];

////////////HVCVCM
enum EHVCVCMCTRLLayout
{
	eHVCVCMCTRLLyout_change = 0,
	eHVCVCMCTRLLyoutNum
};
extern trlEmuMenuLayout hvcvcm_layout_ctrlchange;
extern trlEmuMenuLayout* hvcvcm_layout[];

////////////HVCVCM
enum EHOMENIXCTRLLayout
{
	eHOMENIXCTRLLayout = 0,
	eHOMENIXCTRLLayoutNum
};
extern trlEmuMenuLayout homenix_layout_nix;
extern trlEmuMenuLayout* homenix_layout[];

////////////Common Window
enum ECOMMONWINDOWLayout
{
	eCOMMONWINDOWLayout = 0,
	eCOMMONWINDOWLayoutNum
};
extern trlEmuMenuLayout commonwindow_layout_main;
extern trlEmuMenuLayout* commonewindow_layout[];
