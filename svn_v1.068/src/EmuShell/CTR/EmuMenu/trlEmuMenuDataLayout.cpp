/**
* @file trlEmuMenuDataLayout.cpp
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataLayout.h"
////////////////////////
//layout resource
////////////////////////

////////////CGBVCM
char *pCGBVCMLayoutName[] =
{
	"FirstTimeMessage.bclyt",
	"main.bclyt",
	"message.bclyt",
	"message_nosram.bclyt",
	"mode_change.bclyt",
	"NormalModeMain.bclyt",
	"NormalModeMessage.bclyt",
	"NormalModeMessage_nosram.bclyt",
	"ChildMain.bclyt",
	"message_DL.bclyt",
	"Warning_DL.bclyt"
};


trlEmuMenuAnim* pCGBVCMLayoutAnim[] =
{
	&cgbvcm_firsttime_anim,
	&cgbvcm_main_anim,
	&cgbvcm_message_anim,
	&cgbvcm_message_nosram_anim,
	&cgbvcm_modechange_anim,
	&cgbvcm_nmain_anim,
	&cgbvcm_nmessage_anim,
	&cgbvcm_nmessage_nosram_anim,
	&childmain_anim,
	&messagedl_anim,
	NULL												//Warning_DL_anim is null
};

trlEmuMenuLayout cgbvcm_layout_firsttime =			{	pCGBVCMLayoutName[eCGBVCMLayout_FirstTime],			pCGBVCMLayoutAnim[eCGBVCMLayout_FirstTime],		NULL	};
trlEmuMenuLayout cgbvcm_layout_main =				{	pCGBVCMLayoutName[eCGBVCMLayout_Main],				pCGBVCMLayoutAnim[eCGBVCMLayout_Main],			NULL	};
trlEmuMenuLayout cgbvcm_layout_message =			{	pCGBVCMLayoutName[eCGBVCMLayout_Message],			pCGBVCMLayoutAnim[eCGBVCMLayout_Message],		NULL	};
trlEmuMenuLayout cgbvcm_layout_message_nosram =		{	pCGBVCMLayoutName[eCGBVCMLayout_MessageNoSRAM],		pCGBVCMLayoutAnim[eCGBVCMLayout_MessageNoSRAM],	NULL	};
trlEmuMenuLayout cgbvcm_layout_modechange =			{	pCGBVCMLayoutName[eCGBVCMLayout_ModeChange],		pCGBVCMLayoutAnim[eCGBVCMLayout_ModeChange],	NULL	};
trlEmuMenuLayout cgbvcm_layout_nmain =				{	pCGBVCMLayoutName[eCGBVCMLayout_NMain],				pCGBVCMLayoutAnim[eCGBVCMLayout_NMain],			NULL	};
trlEmuMenuLayout cgbvcm_layout_nmessage =			{	pCGBVCMLayoutName[eCGBVCMLayout_NMessage],			pCGBVCMLayoutAnim[eCGBVCMLayout_NMessage],		NULL	};
trlEmuMenuLayout cgbvcm_layout_nmessage_nosram =	{	pCGBVCMLayoutName[eCGBVCMLayout_NMessageNoSRAM],	pCGBVCMLayoutAnim[eCGBVCMLayout_NMessageNoSRAM],NULL	};
trlEmuMenuLayout cgbvcm_layout_childmain =			{	pCGBVCMLayoutName[eCGBVCMLayout_ChildMain],			pCGBVCMLayoutAnim[eCGBVCMLayout_ChildMain],		NULL	};
trlEmuMenuLayout cgbvcm_layout_messagedl =			{	pCGBVCMLayoutName[eCGBVCMLayout_MessageDL],			pCGBVCMLayoutAnim[eCGBVCMLayout_MessageDL],		NULL	};
trlEmuMenuLayout cgbvcm_layout_warningdl =			{	pCGBVCMLayoutName[eCGBVCMLayout_Warning_DL],		pCGBVCMLayoutAnim[eCGBVCMLayout_Warning_DL],	NULL	};

trlEmuMenuLayout* cgbvcm_layout[] =
{
	&cgbvcm_layout_firsttime,
	&cgbvcm_layout_main,
	&cgbvcm_layout_message,
	&cgbvcm_layout_message_nosram,
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_NONE
	&cgbvcm_layout_modechange,
#endif
	&cgbvcm_layout_nmain,
	&cgbvcm_layout_nmessage,
	&cgbvcm_layout_nmessage_nosram,
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
	&cgbvcm_layout_childmain,
	&cgbvcm_layout_messagedl,
	&cgbvcm_layout_warningdl
#endif
};

////////////ERRVCM
char *pERRVCMLayoutName[] =
{
	"ErrorMessage.bclyt"
};
trlEmuMenuAnim* pERRVCMLayoutAnim[] =
{
	&errvcm_anim_error
};
trlEmuMenuLayout errvcm_layout_error =	{	pERRVCMLayoutName[eERRVCMLayout_Message],	pERRVCMLayoutAnim[eERRVCMLayout_Message]	};

trlEmuMenuLayout* errvcm_layout[] =
{
	&errvcm_layout_error
};


////////////HVCVCM ctrl change
char *pHVCVCMCTRLLayoutName[] =
{
	"ctrl_change.bclyt"
};

trlEmuMenuAnim* pHVCVCMLayoutAnim[] =
{
	&cgbvcm_ctrlchange_anim
};

trlEmuMenuLayout hvcvcm_layout_ctrlchange =	{	pHVCVCMCTRLLayoutName[eHVCVCMCTRLLyout_change],	pHVCVCMLayoutAnim[eHVCVCMCTRLLyout_change]	};

trlEmuMenuLayout* hvcvcm_layout[] =
{
	&hvcvcm_layout_ctrlchange
};


////////////Home Nix Sign
char *pHomeNixLayoutName[] =
{
	"HomeNixSign.bclyt"
};
trlEmuMenuAnim* pHomeNixLayoutAnim[] =
{
	&homenix_anim
};
trlEmuMenuLayout homenix_layout_nix =	{	pHomeNixLayoutName[eHOMENIXCTRLLayout],	pHomeNixLayoutAnim[eHOMENIXCTRLLayout]	};

trlEmuMenuLayout* homenix_layout[] =
{
	&homenix_layout_nix
};

////////////Common Window
char *pCommonWindowLayoutName[] =
{
	"CommonWindow.bclyt"
};
trlEmuMenuAnim *pCommonWindowLayoutAnim[] =
{
	&commonwindow_anim
};
trlEmuMenuLayout commonwindow_layout_main = { pCommonWindowLayoutName[eCOMMONWINDOWLayout], pCommonWindowLayoutAnim[eCOMMONWINDOWLayout]};

trlEmuMenuLayout* commonewindow_layout[] =
{
	&commonwindow_layout_main
};
