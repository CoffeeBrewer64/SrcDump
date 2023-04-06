/**
* @file trlEmuMenuDataButton.cpp
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataButton.h"

trlEmuMenuButtonAnim cgbvcm_btanim_firsttime		=	{	eFirstTimeMessageAnim_focus_00,			eFirstTimeMessageAnim_focus_00,			eFirstTimeMessageAnim_focus_out_00	};
trlEmuMenuButtonAnim cgbvcm_btanim_main				=	{	eMainAnim_focus_00,						eMainAnim_focus_01,						eMainAnim_focus_out_00				};
trlEmuMenuButtonAnim cgbvcm_btanim_message			=	{	eMessageAnim_focus_00,					eMessageAnim_focus_00,					eMessageAnim_focus_out_00			};
trlEmuMenuButtonAnim cgbvcm_btanim_message_nosram	=	{	eMessageNoSRAMAnim_focus_00,			eMessageNoSRAMAnim_focus_00,			eMessageNoSRAMAnim_focus_out_00		};
trlEmuMenuButtonAnim cgbvcm_btanim_nmain			=	{	eNMainAnim_focus_00,					eNMainAnim_focus_01,					eNMainAnim_focus_out_00				};
trlEmuMenuButtonAnim cgbvcm_btanim_nmessage			=	{	eNMessageAnim_focus_00,					eNMessageAnim_focus_00,					eNMessageAnim_focus_out_00			};
trlEmuMenuButtonAnim cgbvcm_btanim_nmessage_nosram	=	{	eNMessageNoSRAMAnim_focus_00,			eNMessageNoSRAMAnim_focus_00,			eNMessageNoSRAMAnim_focus_out_00	};

trlEmuMenuButtonAnim cgbvcm_btanim_messagedl =			{	emessage_DLAnim_focus_00,				emessage_DLAnim_focus_00,				emessage_DLAnim_focus_out_00		};
trlEmuMenuButtonAnim cgbvcm_btanim_childmain =			{	eChildMainAnim_focus_00,				eChildMainAnim_focus_01,				eChildMainAnim_focus_out_00			};			

trlEmuMenuButtonAnim errvcm_btanim_error			=	{	eErrorAnim_focus_00,					eErrorAnim_focus_00,					eErrorAnim_focus_out_00				};

trlEmuMenuButtonAnim cgbvcm_btanim_commonwindow		=	{	eCommonWindowAnim_focus_00,				eCommonWindowAnim_focus_00,				eCommonWindowAnim_focus_out_00		};


trlEmuMenuButton cgbvcm_bt_firstime_w00btl	=	{	"N_MSGLBtn_00",		"B_MSGLBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w00btr	=	{	"N_MSGRBtn_00",		"B_MSGRBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w01btl	=	{	"N_MSGLBtn_01",		"B_MSGLBtn_01",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w01btr	=	{	"N_MSGRBtn_01",		"B_MSGRBtn_01",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w02btl	=	{	"N_MSGLBtn_02",		"B_MSGLBtn_02",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w02btr	=	{	"N_MSGRBtn_02",		"B_MSGRBtn_02",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w03btl	=	{	"N_MSGLBtn_03",		"B_MSGLBtn_03",		1	};
trlEmuMenuButton cgbvcm_bt_firstime_w03btr	=	{	"N_MSGRBtn_03",		"B_MSGRBtn_03",		1	};

trlEmuMenuButton cgbvcm_bt_main_resume		=	{	"N_ResumeBtn_00",		"B_ResumeBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_main_save		=	{	"N_SaveBtn_00",			"B_SaveBtn_00",			1	};
trlEmuMenuButton cgbvcm_bt_main_reset		=	{	"N_ResetBtn_00",		"B_ResetBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_main_load		=	{	"N_LoadBtn_00",			"B_LoadBtn_00",			1	};
trlEmuMenuButton cgbvcm_bt_main_change		=	{	"P_ChangeBtn_00",		"B_ChangeBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_main_dl			=	{	"N_DLBtn_00",			"B_DLBtn_01",			1	};

trlEmuMenuButton cgbvcm_bt_message_saveno	=	{	"N_SaveNoBtn_00",		"B_SaveNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_saveyes	=	{	"N_SaveYesBtn_00",		"B_SaveYesBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_saveok	=	{	"N_SaveOKBtn_00",		"B_SaveOKBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_loadno	=	{	"N_LoadNoBtn_00",		"B_LoadNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_loadyes	=	{	"N_LoadYesBtn_00",		"B_LoadYesBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_loadok	=	{	"N_LoadOKBtn_00",		"B_LoadOKBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_resetno	=	{	"N_ResetNoBtn_00",		"B_ResetNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_resetyes	=	{	"N_ResetYesBtn_00",		"B_ResetYesBtn_00",		1	};

trlEmuMenuButton cgbvcm_bt_message_nosram_saveno	=	{	"N_SaveNoBtn_00",		"B_SaveNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_saveyes	=	{	"N_SaveYesBtn_00",		"B_SaveYesBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_saveok	=	{	"N_SaveOKBtn_00",		"B_SaveOKBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_loadno	=	{	"N_LoadNoBtn_00",		"B_LoadNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_loadyes	=	{	"N_LoadYesBtn_00",		"B_LoadYesBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_loadok	=	{	"N_LoadOKBtn_00",		"B_LoadOKBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_resetno	=	{	"N_ResetNoBtn_00",		"B_ResetNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_message_nosram_resetyes	=	{	"N_ResetYesBtn_00",		"B_ResetYesBtn_00",		1	};


trlEmuMenuButton cgbvcm_bt_nmain_resume		=	{	"N_ResumeBtn_00",		"B_ResumeBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_nmain_reset		=	{	"N_ResetBtn_00",		"B_ResetBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_nmain_change		=	{	"P_ChangeBtn_00",		"B_ChangeBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_nmain_dl			=	{	"N_DLBtn_00",			"B_DLBtn_00",			1	};

trlEmuMenuButton cgbvcm_bt_nmessage_resetno		=	{	"N_ResetNoBtn_00",	"B_ResetNoBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_nmessage_resetyes	=	{	"N_ResetYesBtn_00",	"B_ResetYesBtn_00",		1	};
trlEmuMenuButton cgbvcm_bt_nmessage_msg00btl	=	{	"N_MSGLBtn_00",		"B_MSGLBtn_00",			1	};
trlEmuMenuButton cgbvcm_bt_nmessage_msg00btr	=	{	"N_MSGRBtn_00",		"B_MSGRBtn_00",			1	};
trlEmuMenuButton cgbvcm_bt_nmessage_msg01btl	=	{	"N_MSGNoBtn_01",	"B_MSGLBtn_01",			1	};
trlEmuMenuButton cgbvcm_bt_nmessage_msg01btr	=	{	"N_MSGRBtn_01",		"B_MSGRBtn_01",			1	};

trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg00btl	=	{	"N_MSGLBtn_00",		"B_MSGLBtn_00",			1	};
trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg00btr	=	{	"N_MSGRBtn_00",		"B_MSGRBtn_00",			1	};
trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg01btl	=	{	"N_MSGNoBtn_01",	"B_MSGLBtn_01",			1	};
trlEmuMenuButton cgbvcm_bt_nmessage_nosram_msg01btr	=	{	"N_MSGRBtn_01",		"b_MSGRBtn_01",			1	};


trlEmuMenuButton errvcm_bt_error_no		=	{	"N_ER_YN_NoBtn_00",		"B_ER_YN_NoBtn_00",			1	};
trlEmuMenuButton errvcm_bt_error_yes	=	{	"N_ER_YN_YesBtn_00",	"B_ER_YN_YesBtn_00",		1	};
trlEmuMenuButton errvcm_bt_error_ok		=	{	"N_ER_OKBtn_00",		"B_ER_OKBtn_00",			1	};

trlEmuMenuButton cgbvcm_bt_messagedl_no  = {	"N_DLLBtn_00",	"B_DLLBtn_00",	1};
trlEmuMenuButton cgbvcm_bt_messagedl_yes = {	"N_DLRBtn_00",	"B_DLRBtn_00",	1};

trlEmuMenuButton cgbvcm_bt_commonwindow_ynno  = {	"N_YN_NoBtn_00", "B_YN_NoBtn_00", 1};
trlEmuMenuButton cgbvcm_bt_commonwindow_ynyes = {	"N_YN_YesBtn_00", "B_YN_YesBtn_00", 1};
trlEmuMenuButton cgbvcm_bt_commonwindow_ok = {	"N_OKBtn_00", "B_OKBtn_00", 1};

trlEmuMenuButton cgbvcm_bt_netplaychild_resume = { "N_ResumeBtn_00", "B_ResumeBtn_00", 1 };
trlEmuMenuButton cgbvcm_bt_netplaychild_disconn = { "N_DLBtn_00", "B_DLBtn_00", 1 };
