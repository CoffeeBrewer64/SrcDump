/**
* @file trlEmuMenuDataAnim.h
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"
#include "trlEmuMenuData.h"

////////////////////////
//anims resource
////////////////////////

////////////First Time
enum EFirstTimeMessageAnimNew
{
	eFirstTimeMessageAnim_action_00,
	eFirstTimeMessageAnim_close_00,
	eFirstTimeMessageAnim_close_01,
	eFirstTimeMessageAnim_focus_00,
	eFirstTimeMessageAnim_focus_out_00,
	eFirstTimeMessageAnim_loop_00,
	eFirstTimeMessageAnim_loop_close_00,
	eFirstTimeMessageAnim_loop_open_00,
	eFirstTimeMessageAnim_open_00,
	eFirstTimeMessageNum
};
extern trlEmuMenuAnim cgbvcm_firsttime_anim;
////////////main
enum EMainAnimNew
{
	eMainAnim_focus_00 = 0,
	eMainAnim_focus_out_00,
	eMainAnim_action_00,
	eMainAnim_deactivate_00,
	eMainAnim_deactivate_01,
	eMainAnim_activate_00,
	eMainAnim_visible_on_00,
	eMainAnim_visible_off_00,
	eMainAnim_nonactive_00,
	eMainAnim_fade_in_00,
	eMainAnim_fade_in_01,
	eMainAnim_fade_out_00,
	eMainAnim_fade_to_deactivate_00,
	eMainAnim_focus_01,
	eMainAnim_A_to_N_00,
	eMainAnim_N_to_A_00,
	eMainAnim_close_00,
	eMainAnim_open_00,
	eMainAnimNum
};

extern trlEmuMenuAnim cgbvcm_main_anim;

////////////message
enum EMessageAnimNew
{
	eMessageAnim_focus_00 = 0,
	eMessageAnim_focus_out_00,
	eMessageAnim_action_00,
	eMessageAnim_open_00,
	eMessageAnim_close_00,
	eMessageAnim_close_01,
	eMessageAnim_effect_00,
	eMessageAnim_loop_00,
	eMessageAnim_loop_open_00,
	eMessageAnim_loop_close_00,
	eMessageAnim_Bg_loop_00,
	eMessageAnimNum
};

extern trlEmuMenuAnim cgbvcm_message_anim;

////////////MessageNoSRAM
enum EMessageNoSRAMAnimNew
{
	eMessageNoSRAMAnim_focus_00 = 0,
	eMessageNoSRAMAnim_focus_out_00,
	eMessageNoSRAMAnim_action_00,
	eMessageNoSRAMAnim_open_00,
	eMessageNoSRAMAnim_close_00,
	eMessageNoSRAMAnim_close_01,
	eMessageNoSRAMAnim_effect_00,
	eMessageNoSRAMAnim_loop_00,
	eMessageNoSRAMAnim_loop_open_00,
	eMessageNoSRAMAnim_loop_close_00,
	eMessageNoSRAMAnim_Bg_loop_00,
	eMessageNoSRAMAnimNum
};

extern trlEmuMenuAnim cgbvcm_message_nosram_anim;


////////////Normal Main
enum ENMainAnimNew
{
	eNMainAnim_A_to_N_00,
	eNMainAnim_action_00,
	eNMainAnim_activate_00,
	eNMainAnim_deactivate_00,
	eNMainAnim_fade_in_00,
	eNMainAnim_fade_out_00,
	eNMainAnim_fade_to_deactivate_00,
	eNMainAnim_focus_00,
	eNMainAnim_focus_01,
	eNMainAnim_focus_out_00,
	eNMainAnim_N_to_A_00,
	eNMainAnim_nonactive_00,
	eNMainAnim_visible_off_00,
	eNMainAnim_visible_on_00,
	eNMainAnim_close_00,
	eNMainAnim_open_00,
	eNMainAnimNum
};

extern trlEmuMenuAnim cgbvcm_nmain_anim;

////////////Normal Message
enum ENMessageAnimNew
{
	eNMessageAnim_action_00 = 0,
	eNMessageAnim_close_00,
	eNMessageAnim_close_01,
	eNMessageAnim_focus_00,
	eNMessageAnim_focus_out_00,
	eNMessageAnim_loop_00,
	eNMessageAnim_loop_open_00,
	eNMessageAnim_loop_close_00,
	eNMessageAnim_open_00,
	eNMessageAnimNum
};

extern trlEmuMenuAnim cgbvcm_nmessage_anim;

////////////Normal MessageNoSRAM
enum ENMessageNoSRAMAnimNew
{
	eNMessageNoSRAMAnim_action_00 = 0,
	eNMessageNoSRAMAnim_close_00,
	eNMessageNoSRAMAnim_close_01,
	eNMessageNoSRAMAnim_focus_00,
	eNMessageNoSRAMAnim_focus_out_00,
	eNMessageNoSRAMAnim_loop_00,
	eNMessageNoSRAMAnim_loop_open_00,
	eNMessageNoSRAMAnim_loop_close_00,
	eNMessageNoSRAMAnim_open_00,
	eNMessageNoSRAMAnimNum
};

extern trlEmuMenuAnim cgbvcm_nmessage_nosram_anim;

////////////Mode Change
enum EModeChangeAnim
{
	eModeChangeAnim_B_close_00 = 0,
	eModeChangeAnim_B_loop_00,
	eModeChangeAnim_B_open_00,
	eModeChangeAnim_B_to_G_00,
	eModeChangeAnim_G_close_00,
	eModeChangeAnim_G_loop_00,
	eModeChangeAnim_G_open_00,
	eModeChangeAnim_G_to_B_00,
	eModeChangeAnimNum
};

extern trlEmuMenuAnim cgbvcm_modechange_anim;


////////////Error
enum EErrorAnim
{
	eErrorAnim_action_00 = 0,
	eErrorAnim_close_00,
	eErrorAnim_close_01,
	eErrorAnim_focus_00,
	eErrorAnim_focus_out_00,
	eErrorAnim_open_00,
	eErrorAnim_wait_00,
	eErrorAnimNum
};

extern trlEmuMenuAnim errvcm_anim_error;


////////////Mode Change
enum ECtrlChangeAnim
{	
	eCtrlChangeAnim_1P_close_00 = 0,
	eCtrlChangeAnim_1P_loop_00,
	eCtrlChangeAnim_1P_open_00,
	eCtrlChangeAnim_1P_to_2P_00,
	eCtrlChangeAnim_2P_close_00,
	eCtrlChangeAnim_2P_loop_00,
	eCtrlChangeAnim_2P_open_00,
	eCtrlChangeAnim_2P_to_1P_00,
	eCtrlChangeAnimNum
};
extern trlEmuMenuAnim cgbvcm_ctrlchange_anim;

////////////Home Nix
enum EHomeNixAnim
{
	eHomeNixAnim_InOut = 0,
	eHomeNixAnimNum
};

extern trlEmuMenuAnim homenix_anim;

////////////Common Window
enum ECommonWindowAnim
{
	eCommonWindowAnim_action_00,
	eCommonWindowAnim_close_00,
	eCommonWindowAnim_close_01,
	eCommonWindowAnim_focus_00,
	eCommonWindowAnim_focus_out_00,
	eCommonWindowAnim_open_00,
	eCommonWindowAnim_wait_00,
	eCommonWindowAnimNum
};
extern trlEmuMenuAnim commonwindow_anim;

////////////Message DL
enum EMessageDLAnim
{
	emessage_DLAnim_action_00,
	emessage_DLAnim_BG_loop_00,
	emessage_DLAnim_close_00,
	emessage_DLAnim_close_01,
	emessage_DLAnim_effect_00,
	emessage_DLAnim_fade_in_00,
	emessage_DLAnim_fade_out_00,
	emessage_DLAnim_focus_00,
	emessage_DLAnim_focus_out_00,
	emessage_DLAnim_loop_00,
	emessage_DLAnim_loop_close_00,
	emessage_DLAnim_loop_open_00,
	emessage_DLAnim_open_00,
	emessage_DLAnim_visible_off_00,
	emessage_DLAnim_visible_on_00,
	emessage_DLAnimNum
};
extern trlEmuMenuAnim messagedl_anim;

////////////ChildMain
enum EChildMainAnim
{
	eChildMainAnim_A_to_N_00,
	eChildMainAnim_action_00,
	eChildMainAnim_activate_00,
	eChildMainAnim_deactivate_00,
	eChildMainAnim_fade_in_00,
	eChildMainAnim_fade_out_00,
	eChildMainAnim_fade_to_deactivate_00,
	eChildMainAnim_focus_00,
	eChildMainAnim_focus_01,
	eChildMainAnim_focus_out_00,
	eChildMainAnim_N_to_A_00,
	eChildMainAnim_nonactive_00,
	eChildMainAnim_visible_off_00,
	eChildMainAnim_visible_on_00,
	eChildMainAnimNum
};
extern trlEmuMenuAnim childmain_anim;
