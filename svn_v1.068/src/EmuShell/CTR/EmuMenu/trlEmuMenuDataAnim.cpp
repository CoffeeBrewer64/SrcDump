/**
* @file trlEmuMenuDataAnim.cpp
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#include "trlEmuMenuDataAnim.h"


////////////////////////
//anims resource
////////////////////////

////////////First Time
char *pFirstTimeMessageAnimNameNew[] =
{
	"FirstTimeMessage_action_00.bclan",
	"FirstTimeMessage_close_00.bclan",
	"FirstTimeMessage_close_01.bclan",
	"FirstTimeMessage_focus_00.bclan",
	"FirstTimeMessage_focus_out_00.bclan",
	"FirstTimeMessage_loop_00.bclan",
	"FirstTimeMessage_loop_close_00.bclan",
	"FirstTimeMessage_loop_open_00.bclan",
	"FirstTimeMessage_open_00.bclan"
};

trlEmuMenuAnim cgbvcm_firsttime_anim =
{
	eFirstTimeMessageNum,
	pFirstTimeMessageAnimNameNew
};

////////////main
char *pMainAnimNameNew[] =
{
	"main_focus_00.bclan",
	"main_focus_out_00.bclan",
	"main_action_00.bclan",
	"main_deactivate_00.bclan",
	"main_deactivate_00.bclan",
	"main_activate_00.bclan",
	"main_visible_on_00.bclan",
	"main_visible_off_00.bclan",
	"main_nonactive_00.bclan",
	"main_fade_in_00.bclan",
	"main_fade_in_00.bclan",
	"main_fade_out_00.bclan",
	"main_fade_to_deactivate_00.bclan",
	"main_focus_01.bclan",
	"main_A_to_N_00.bclan",
	"main_N_to_A_00.bclan",
	"main_close_00.bclan",
	"main_open_00.bclan"
};
trlEmuMenuAnim cgbvcm_main_anim =
{
	eMainAnimNum,
	pMainAnimNameNew
};

////////////message
char *pMessageAnimNameNew[] =
{
	"message_focus_00.bclan",
	"message_focus_out_00.bclan",
	"message_action_00.bclan",
	"message_open_00.bclan",
	"message_close_00.bclan",
	"message_close_01.bclan",
	"message_effect_00.bclan",
	"message_loop_00.bclan",
	"message_loop_open_00.bclan",
	"message_loop_close_00.bclan",
	"message_BG_loop_00.bclan",
};
trlEmuMenuAnim cgbvcm_message_anim =
{
	eMessageAnimNum,
	pMessageAnimNameNew
};

////////////MessageNoSRAM
char *pMessageNoSRAMAnimNameNew[] =
{
	"message_nosram_focus_00.bclan",
	"message_nosram_focus_out_00.bclan",
	"message_nosram_action_00.bclan",
	"message_nosram_open_00.bclan",
	"message_nosram_close_00.bclan",
	"message_nosram_close_01.bclan",
	"message_nosram_effect_00.bclan",
	"message_nosram_loop_00.bclan",
	"message_nosram_loop_open_00.bclan",
	"message_nosram_loop_close_00.bclan",
	"message_nosram_BG_loop_00.bclan",
};
trlEmuMenuAnim cgbvcm_message_nosram_anim =
{
	eMessageNoSRAMAnimNum,
	pMessageNoSRAMAnimNameNew
};


////////////Normal Main
char *pNMainAnimNameNew[] =
{
	"NormalModeMain_A_to_N_00.bclan",
	"NormalModeMain_action_00.bclan",
	"NormalModeMain_activate_00.bclan",
	"NormalModeMain_deactivate_00.bclan",
	"NormalModeMain_fade_in_00.bclan",
	"NormalModeMain_fade_out_00.bclan",
	"NormalModeMain_fade_to_deactivate_00.bclan",
	"NormalModeMain_focus_00.bclan",
	"NormalModeMain_focus_01.bclan",
	"NormalModeMain_focus_out_00.bclan",
	"NormalModeMain_N_to_A_00.bclan",
	"NormalModeMain_nonactive_00.bclan",
	"NormalModeMain_visible_off_00.bclan",
	"NormalModeMain_visible_on_00.bclan",
	"NormalModeMain_close_00.bclan",
	"NormalModeMain_open_00.bclan"
};
trlEmuMenuAnim cgbvcm_nmain_anim =
{
	eNMainAnimNum,
	pNMainAnimNameNew
};

////////////Normal Message
char *pNMessageAnimNameNew[] =
{
	"NormalModeMessage_action_00.bclan",
	"NormalModeMessage_close_00.bclan",
	"NormalModeMessage_close_01.bclan",
	"NormalModeMessage_focus_00.bclan",
	"NormalModeMessage_focus_out_00.bclan",
	"NormalModeMessage_loop_00.bclan",
	"NormalModeMessage_loop_close_00.bclan",
	"NormalModeMessage_loop_open_00.bclan",
	"NormalModeMessage_open_00.bclan"
};
trlEmuMenuAnim cgbvcm_nmessage_anim =
{
	eNMessageAnimNum,
	pNMessageAnimNameNew
};

////////////Normal MessageNoSRAM
char *pNMessageNoSRAMAnimNameNew[] =
{
	"NormalModeMessage_nosram_action_00.bclan",
	"NormalModeMessage_nosram_close_00.bclan",
	"NormalModeMessage_nosram_close_01.bclan",
	"NormalModeMessage_nosram_focus_00.bclan",
	"NormalModeMessage_nosram_focus_out_00.bclan",
	"NormalModeMessage_nosram_loop_00.bclan",
	"NormalModeMessage_nosram_loop_close_00.bclan",
	"NormalModeMessage_nosram_loop_open_00.bclan",
	"NormalModeMessage_nosram_open_00.bclan"
};
trlEmuMenuAnim cgbvcm_nmessage_nosram_anim =
{
	eNMessageNoSRAMAnimNum,
	pNMessageNoSRAMAnimNameNew
};

////////////Mode Change
char *pModeChangeAnimNameNew[] =
{
	"mode_change_B_close_00.bclan",
	"mode_change_B_loop_00.bclan",
	"mode_change_B_open_00.bclan",
	"mode_change_B_to_G_00.bclan",
	"mode_change_G_close_00.bclan",
	"mode_change_G_loop_00.bclan",
	"mode_change_G_open_00.bclan",
	"mode_change_G_to_B_00.bclan"
};
trlEmuMenuAnim cgbvcm_modechange_anim =
{
	eModeChangeAnimNum,
	pModeChangeAnimNameNew
};

////////////Error
char *pErrorAnimNameNew[] =
{
	"ErrorMessage_action_00.bclan",
	"ErrorMessage_close_00.bclan",
	"ErrorMessage_close_01.bclan",
	"ErrorMessage_focus_00.bclan",
	"ErrorMessage_focus_out_00.bclan",
	"ErrorMessage_open_00.bclan",
	"ErrorMessage_wait_00.bclan"
};
trlEmuMenuAnim errvcm_anim_error =
{
	eErrorAnimNum,
	pErrorAnimNameNew
};


////////////Ctrl Change
char *pCtrlChangeAnimNameNew[] =
{
	"ctrl_change_1P_close_00.bclan",
	"ctrl_change_1P_loop_00.bclan",
	"ctrl_change_1P_open_00.bclan",
	"ctrl_change_1P_to_2P_00.bclan",
	"ctrl_change_2P_close_00.bclan",
	"ctrl_change_2P_loop_00.bclan",
	"ctrl_change_2P_open_00.bclan",
	"ctrl_change_2P_to_1P_00.bclan"
};
trlEmuMenuAnim cgbvcm_ctrlchange_anim =
{
	eCtrlChangeAnimNum,
	pCtrlChangeAnimNameNew
};

////////////Home Nix
char *pHomeNixAnimNameNew[] =
{
	"HomeNixSign_InOut.bclan"
};
trlEmuMenuAnim homenix_anim =
{
	eHomeNixAnimNum,
	pHomeNixAnimNameNew
};


////////////Message DL
char *pMessageDLAnimName[] =
{
	"message_DL_action_00.bclan",
	"message_DL_BG_loop_00.bclan",
	"message_DL_close_00.bclan",
	"message_DL_close_01.bclan",
	"message_DL_effect_00.bclan",
	"message_DL_fade_in_00.bclan",
	"message_DL_fade_out_00.bclan",
	"message_DL_focus_00.bclan",
	"message_DL_focus_out_00.bclan",
	"message_DL_loop_00.bclan",
	"message_DL_loop_close_00.bclan",
	"message_DL_loop_open_00.bclan",
	"message_DL_open_00.bclan",
	"message_DL_visible_off_00.bclan",
	"message_DL_visible_on_00.bclan"
};
trlEmuMenuAnim messagedl_anim = 
{
	emessage_DLAnimNum,
	pMessageDLAnimName
};

////////////ChildMain
char *pChildMainAnimName[] =
{
	"ChildMain_A_to_N_00.bclan",
	"ChildMain_action_00.bclan",
	"ChildMain_activate_00.bclan",
	"ChildMain_deactivate_00.bclan",
	"ChildMain_fade_in_00.bclan",
	"ChildMain_fade_out_00.bclan",
	"ChildMain_fade_to_deactivate_00.bclan",
	"ChildMain_focus_00.bclan",
	"ChildMain_focus_01.bclan",
	"ChildMain_focus_out_00.bclan",
	"ChildMain_N_to_A_00.bclan",
	"ChildMain_nonactive_00.bclan",
	"ChildMain_visible_off_00.bclan",
	"ChildMain_visible_on_00.bclan"
};
trlEmuMenuAnim childmain_anim =
{
	eChildMainAnimNum,
	pChildMainAnimName
};

////////////Common Window
char *pCommonWindowAnimName[] = 
{
	"CommonWindow_action_00.bclan",
	"CommonWindow_close_00.bclan",
	"CommonWindow_close_01.bclan",
	"CommonWindow_focus_00.bclan",
	"CommonWindow_focus_out_00.bclan",
	"CommonWindow_open_00.bclan",
	"CommonWindow_wait_00.bclan"
};
trlEmuMenuAnim commonwindow_anim = 
{
	eCommonWindowAnimNum,
	pCommonWindowAnimName
};
