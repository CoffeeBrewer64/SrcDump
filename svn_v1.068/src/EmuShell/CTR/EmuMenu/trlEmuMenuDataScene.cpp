/**
* @file trlEmuMenuDataScene.h
* @author zhfang
* @date 2011.07.02
* @brief trlEmuMenu
*/
#include "../../../trlMacro.h"
#include "../../trlEmuShellStruct.h"
#include "../../../../files/VCM/SND/threeb.csid"
#include "trlEmuMenuDataButton.h"
#include "trlEmuMenuDataLayout.h"
#include "trlEmuMenuDataState.h"
#include "trlEmuMenuDataCallBack.h"
#include "trlEmuMenuDataScene.h"

//////////////
//firsttime w00
trlEmuMenuStateKeyAction cgbvcm_keyaction_firsttime_w00 =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w00btr, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w00btl, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonFirstTime_w00btl,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW00_2_W02, SE_CTR_COMMON_BUTTON } //decide action
		},
		{ //action 2
			eCGBVCMButtonFirstTime_w00btr,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW00_2_W01, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_firsttime_w00 =
{
	2,
	{
		&cgbvcm_bt_firstime_w00btl,
		&cgbvcm_bt_firstime_w00btr
	},
	&cgbvcm_btanim_firsttime,
	&cgbvcm_layout_firsttime,
	&cgbvcm_keyaction_firsttime_w00
};

//////////////
//firsttime w01
trlEmuMenuStateKeyAction cgbvcm_keyaction_firsttime_w01 =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w01btr, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w01btl, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonFirstTime_w01btl,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW01_2_NMain, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonFirstTime_w01btr,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW01_2_ModeChangeNTOA0, SE_CTR_COMMON_OK } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_firsttime_w01 =
{
	2,
	{
		&cgbvcm_bt_firstime_w01btl,
		&cgbvcm_bt_firstime_w01btr
	},
	&cgbvcm_btanim_firsttime,
	&cgbvcm_layout_firsttime,
	&cgbvcm_keyaction_firsttime_w01
};

//////////////
//firsttime w02
trlEmuMenuStateKeyAction cgbvcm_keyaction_firsttime_w02 =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w02btr, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w02btl, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonFirstTime_w02btl,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW02_2_W00, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 2
			eCGBVCMButtonFirstTime_w02btr,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW02_2_W03, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_firsttime_w02 =
{
	2,
	{
		&cgbvcm_bt_firstime_w02btl,
		&cgbvcm_bt_firstime_w02btr
	},
	&cgbvcm_btanim_firsttime,
	&cgbvcm_layout_firsttime,
	&cgbvcm_keyaction_firsttime_w02
};

//////////////
//firsttime w03
trlEmuMenuStateKeyAction cgbvcm_keyaction_firsttime_w03 =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w03btr, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonFirstTime_w03btl, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonFirstTime_w03btl,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW03_2_W02, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 2
			eCGBVCMButtonFirstTime_w03btr,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_FirstTimeW03_2_W01, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_firsttime_w03 =
{
	2,
	{
		&cgbvcm_bt_firstime_w03btl,
		&cgbvcm_bt_firstime_w03btr
	},
	&cgbvcm_btanim_firsttime,
	&cgbvcm_layout_firsttime,
	&cgbvcm_keyaction_firsttime_w03
};

//////////////
//scene main
trlEmuMenuStateKeyAction cgbvcm_keyaction_main =
{
	6, //action
	{
		{
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_MainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2ModeChangeATON0, TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, NULL, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{
			eCGBVCMButtonMain_Resume,
				8,// num of onekeyaction
			{
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
#else
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
#endif
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Save, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Load, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Load, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_MainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2ModeChangeATON0, TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2StandBy, SE_CTR_COMMON_RETURN } //decide action
		},
		{
			eCGBVCMButtonMain_Save,
				8,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Load, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Load, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_MainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2ModeChangeATON0, TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2Save, SE_CTR_COMMON_BUTTON } //decide action
		},
		{
			eCGBVCMButtonMain_Reset,
				8,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Save, SE_CTR_THREEB_CURSOR_MOVE },
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
#else
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
#endif
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Load, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Load, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_MainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2ModeChangeATON0, TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2Reset, SE_CTR_COMMON_BUTTON } //decide action
		},
		{
			eCGBVCMButtonMain_Load,
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
				8,// num of onekeyaction
#else
				6,// num of onekeyaction
#endif
			{
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
#endif
				{KEY_LEFT, eEmuMenuKeyActionType_MoveToPre, NULL, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_MoveToPre, NULL, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_MainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2ModeChangeATON0, TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2Load, SE_CTR_COMMON_BUTTON } //decide action
		},
		{
			eCGBVCMButtonMain_DL, //eCGBVCMButtonMain_Change,
				6,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },				
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_MainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2ModeChangeATON0, TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eEmuMenuMainStateChange_Main2DLPPre, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_main =
{
	5,
	{
		&cgbvcm_bt_main_resume,
		&cgbvcm_bt_main_save,
		&cgbvcm_bt_main_reset,
		&cgbvcm_bt_main_load,
		&cgbvcm_bt_main_dl, //&cgbvcm_bt_main_change
	},
	&cgbvcm_btanim_main,
	&cgbvcm_layout_main,
	&cgbvcm_keyaction_main
};

//////////////
//scene save
trlEmuMenuStateKeyAction cgbvcm_keyaction_save =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_SaveYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_SaveNo, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessage_SaveNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_Save2Main, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonMessage_SaveYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_Save2Saveing, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_save =
{
	2,
	{
		&cgbvcm_bt_message_saveno,
			&cgbvcm_bt_message_saveyes
	},
	&cgbvcm_btanim_message,
	&cgbvcm_layout_message,
	&cgbvcm_keyaction_save
};

//////////////
//scene saveing
trlEmuMenuScene cgbvcm_scene_saveing =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_message,
	NULL
};

//////////////
//scene save ok
trlEmuMenuStateKeyAction cgbvcm_keyaction_saveok =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_SaveOk, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_SaveOk, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessage_SaveOk,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_SaveOk2Main, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_saveok =
{
	1,
	{
		&cgbvcm_bt_message_saveok
	},
	&cgbvcm_btanim_message,
	&cgbvcm_layout_message,
	&cgbvcm_keyaction_saveok
};





//////////////
//scene load
trlEmuMenuStateKeyAction cgbvcm_keyaction_load =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_LoadYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_LoadNo, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessage_LoadNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_Load2Main, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonMessage_LoadYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_Load2Loading, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_load =
{
	2,
	{
		&cgbvcm_bt_message_loadno,
			&cgbvcm_bt_message_loadyes
	},
	&cgbvcm_btanim_message,
	&cgbvcm_layout_message,
	&cgbvcm_keyaction_load
};


//////////////
//scene loading
trlEmuMenuScene cgbvcm_scene_loading =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_message,
	NULL
};

//////////////
//scene load ok
trlEmuMenuStateKeyAction cgbvcm_keyaction_loadok =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_LoadOk, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_LoadOk, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessage_LoadOk,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_LoadOk2Main, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_loadok =
{
	1,
	{
		&cgbvcm_bt_message_loadok
	},
	&cgbvcm_btanim_message,
	&cgbvcm_layout_message,
	&cgbvcm_keyaction_loadok
};

//////////////
//scene reset
trlEmuMenuStateKeyAction cgbvcm_keyaction_reset =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_ResetYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_ResetNo, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessage_ResetNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_Reset2Main, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonMessage_ResetYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_Reset2Reseting, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_reset =
{
	2,
	{
		&cgbvcm_bt_message_resetno,
			&cgbvcm_bt_message_resetyes
	},
	&cgbvcm_btanim_message,
	&cgbvcm_layout_message,
	&cgbvcm_keyaction_reset
};


//////////////
//scene reseting
trlEmuMenuScene cgbvcm_scene_reseting =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_message,
	NULL
};

//////////////
//scene normal main
trlEmuMenuStateKeyAction cgbvcm_keyaction_nmain =
{
	4, //action
	{
		{
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2ModeChangeW00, SE_CTR_COMMON_DIALOG }
			},
			{NULL, NULL, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{
			eCGBVCMButtonNMain_Resume,
				6,// num of onekeyaction
			{
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
#else
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
#endif
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2ModeChangeW00, SE_CTR_COMMON_DIALOG }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2StandBy, SE_CTR_COMMON_RETURN } //decide action
		},
		{
			eCGBVCMButtonNMain_Reset,
				6,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
#else
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
#endif
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2ModeChangeW00, SE_CTR_COMMON_DIALOG }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2Reset, SE_CTR_COMMON_BUTTON } //decide action
		},
		{
			eCGBVCMButtonNMain_DL, //eCGBVCMButtonNMain_Change,
				6,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMainClose2StandBy, SE_CTR_COMMON_RETURN },
				{BUTTON_X|BUTTON_R|BUTTON_START|BUTTON_HOLD, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2ModeChangeW00, SE_CTR_COMMON_DIALOG }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NMain2DLPPre, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_nmain =
{
	3,
	{
		&cgbvcm_bt_nmain_resume,
		&cgbvcm_bt_nmain_reset,
		&cgbvcm_bt_nmain_dl //&cgbvcm_bt_nmain_change
	},
	&cgbvcm_btanim_nmain,
	&cgbvcm_layout_nmain,
	&cgbvcm_keyaction_nmain
};

//////////////
//scene normal reset
trlEmuMenuStateKeyAction cgbvcm_keyaction_nreset =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonNMessage_ResetYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonNMessage_ResetNo, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonNMessage_ResetNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NReset2NMain, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonNMessage_ResetYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NReset2NReseting, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_nreset =
{
	2,
	{
		&cgbvcm_bt_nmessage_resetno,
		&cgbvcm_bt_nmessage_resetyes
	},
	&cgbvcm_btanim_nmessage,
	&cgbvcm_layout_nmessage,
	&cgbvcm_keyaction_nreset
};


//////////////
//scene normal reseting
trlEmuMenuScene cgbvcm_scene_nreseting =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_nmessage,
	NULL
};

/////////////
//scene mode change w0
trlEmuMenuStateKeyAction cgbvcm_keyaction_modechange_w00 =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonNMessage_Msg00BtR, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonNMessage_Msg00BtL, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonNMessage_Msg00BtL,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_ModeChangeW00_2_NMain, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 2
			eCGBVCMButtonNMessage_Msg00BtR,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, ECGBVCMStateChange_ModeChangeW00_2_W01, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_modechange_w00 = 
{
	2,
	{
		&cgbvcm_bt_nmessage_msg00btl,
		&cgbvcm_bt_nmessage_msg00btr
	},
	&cgbvcm_btanim_nmessage,
	&cgbvcm_layout_nmessage,
	&cgbvcm_keyaction_modechange_w00
};

/////////////
//scene mode change w1
trlEmuMenuStateKeyAction cgbvcm_keyaction_modechange_w01 =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonNMessage_Msg01BtR, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonNMessage_Msg01BtL, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonNMessage_Msg01BtL,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_ModeChangeW01_2_NMain, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonNMessage_Msg01BtR,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_ModeChangeW01_2_ModeChangeNTOA0, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_modechange_w01 = 
{
	2,
	{
		&cgbvcm_bt_nmessage_msg01btl,
		&cgbvcm_bt_nmessage_msg01btr
	},
	&cgbvcm_btanim_nmessage,
	&cgbvcm_layout_nmessage,
	&cgbvcm_keyaction_modechange_w01
};


/////////////
//scene mode change NTOA
trlEmuMenuScene cgbvcm_scene_modechange_ntoa0 = 
{
	0,
	{},
	NULL,
	&cgbvcm_layout_nmain,
	NULL
};

trlEmuMenuScene cgbvcm_scene_modechange_ntoa1 = 
{
	0,
	{},
	NULL,
	&cgbvcm_layout_main,
	NULL
};

/////////////
//scene mode change ATON
trlEmuMenuScene cgbvcm_scene_modechange_aton0 = 
{
	0,
	{},
	NULL,
	&cgbvcm_layout_main,
	NULL
};

trlEmuMenuScene cgbvcm_scene_modechange_aton1 = 
{
	0,
	{},
	NULL,
	&cgbvcm_layout_nmain,
	NULL
};

/////////////
//scene err begin
trlEmuMenuScene errvcm_scene_begin =
{
	0,
	{},
	NULL,
	&errvcm_layout_error,
	NULL
};

/////////////
//scene err end
trlEmuMenuScene errvcm_scene_end =
{
	0,
	{},
	NULL,
	&errvcm_layout_error,
	NULL
};


/////////////
//scene err notformatwait
trlEmuMenuScene errvcm_scene_notformatwait =
{
	0,
	{},
	NULL,
	&errvcm_layout_error,
	NULL
};

/////////////
//scene error badformat ok
trlEmuMenuStateKeyAction errvcm_keyaction_badformat_ok = 
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eERRVCMButtonError_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eErrVCMStateChange_BadFormatOk2BandForamtWait, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene errvcm_scene_badformatok =
{
	1,
	{
		&errvcm_bt_error_ok
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	&errvcm_keyaction_badformat_ok
};

/////////////
//scene error badformat done
trlEmuMenuStateKeyAction errvcm_keyaction_badformat_done = 
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eERRVCMButtonError_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eErrVCMStateChange_BadFormatDone2End, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene errvcm_scene_badformatdone =
{
	1,
	{
		&errvcm_bt_error_ok
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	&errvcm_keyaction_badformat_done
};

/////////////
//scene error vfailed ok
trlEmuMenuStateKeyAction errvcm_keyaction_vfailed_ok = 
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eERRVCMButtonError_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eErrVCMStateChange_VFailedOk2BandForamtWait, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene errvcm_scene_vfailedok =
{
	1,
	{
		&errvcm_bt_error_ok
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	&errvcm_keyaction_vfailed_ok
};

/////////////
//scene error vfailed done
trlEmuMenuStateKeyAction errvcm_keyaction_vfailed_done = 
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eERRVCMButtonError_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eErrVCMStateChange_VFailedDone2End, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene errvcm_scene_vfaileddone =
{
	1,
	{
		&errvcm_bt_error_ok
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	&errvcm_keyaction_vfailed_done
};

/////////////
//scene err opdeniedwait
trlEmuMenuScene errvcm_scene_opdeniedwait =
{
	0,
	{},
	NULL,
	&errvcm_layout_error,
	NULL
};

/////////////
//scene dlp beginpre
trlEmuMenuScene cgbvcm_scene_dlppre =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_messagedl,
	NULL
};

/////////////
//scene dlp begin
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpbegin =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_Yes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_No,	TRL_EMUMENU_SOUND_NOSOUND }
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessageDLYN_Yes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPBegin2DLPConn, SE_CTR_COMMON_BUTTON } //decide action
		},
		{ //action 2
			eCGBVCMButtonMessageDLYN_No,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPBegin2DLPBeginBack, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpbegin =
{
	2,
	{
		&cgbvcm_bt_messagedl_no,
		&cgbvcm_bt_messagedl_yes
	},
	&cgbvcm_btanim_messagedl,
	&cgbvcm_layout_messagedl,
	&cgbvcm_keyaction_dlpbegin,

};

/////////////
//scene dlp back
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpbeginback =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, ECGBVCMStateChange_DLPBeginBack2DLPBegin, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, ECGBVCMStateChange_DLPBeginBack2Main, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpbeginback =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpbeginback
};

/////////////
//scene dlpconn
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpconn =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
			2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_Yes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_No,	TRL_EMUMENU_SOUND_NOSOUND }
			},
		},		
		{ //action 1
			eCGBVCMButtonMessageDLYN_No,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPConn2DLPConnBack, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 2
			eCGBVCMButtonMessageDLYN_Yes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPConn2DLP, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpconn =
{
	2,
	{
		&cgbvcm_bt_messagedl_no,
		&cgbvcm_bt_messagedl_yes
	},
	&cgbvcm_btanim_messagedl,
	&cgbvcm_layout_messagedl,
	&cgbvcm_keyaction_dlpconn
};

/////////////
//scene dlpconnback
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpconnback =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPConnBack2DLPConn, SE_CTR_COMMON_BUTTON } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPConnBack2BackMain, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpconnback =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpconnback
};

/////////////
//scene dlpconnquit
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpconnquit =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_Ok,
				0,// num of onekeyaction
			{},
			//{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPConnQuit2DLPBegin, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpconnquit =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_main,
	NULL
};

/////////////
//scene dlp
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlp =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
			1,// num of onekeyaction
			{
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_No,	TRL_EMUMENU_SOUND_NOSOUND }
			},
		},		
		{ //action 1
			eCGBVCMButtonMessageDLYN_No,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLP2DLPBack, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlp =
{
	2,
	{
		&cgbvcm_bt_messagedl_no,
		&cgbvcm_bt_messagedl_yes
	},
	&cgbvcm_btanim_messagedl,
	&cgbvcm_layout_messagedl,
	&cgbvcm_keyaction_dlp
};

/////////////
//scene dlpback
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpback =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPBack2DLP, SE_CTR_COMMON_BUTTON } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPBack2BackMain, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpback =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpback
};


/////////////
//scene dlp net init
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpnetinit =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
			1,// num of onekeyaction
			{
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_No,	TRL_EMUMENU_SOUND_NOSOUND }
			},
		},		
		{ //action 1
			eCGBVCMButtonMessageDLYN_No,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNetInit2DLPNetInitBack, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpnetinit =
{
	2,
	{
		&cgbvcm_bt_messagedl_no,
		&cgbvcm_bt_messagedl_yes
	},
	&cgbvcm_btanim_messagedl,
	&cgbvcm_layout_messagedl,
	&cgbvcm_keyaction_dlpnetinit
};

/////////////
//scene dlp net init back
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpnetinitback =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNetInitBack2DLPNetInit, SE_CTR_COMMON_BUTTON } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNetInitBack2BackMain, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpnetinitback =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpnetinitback
};

/////////////
//scene dlps
trlEmuMenuScene cgbvcm_scene_dlps =
{
	0,
	{},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	NULL
};

/////////////
//scene dlp wait
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpwait =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
			1,// num of onekeyaction
			{
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessageDLYN_No,	TRL_EMUMENU_SOUND_NOSOUND }
			},
		},		
		{ //action 1
			eCGBVCMButtonMessageDLYN_No,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPWait2DLPWaitBack, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpwait =
{
	2,
	{
		&cgbvcm_bt_messagedl_no,
		&cgbvcm_bt_messagedl_yes
	},
	&cgbvcm_btanim_messagedl,
	&cgbvcm_layout_messagedl,
	&cgbvcm_keyaction_dlpwait
};

/////////////
//scene dlp wait back
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpwaitback =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPWaitBack2DLPWait, SE_CTR_COMMON_BUTTON } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,			
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPWaitBack2DLPChildEndWait, SE_CTR_COMMON_RETURN } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpwaitback =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpwaitback
};

/////////////
//scene dlp ok
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpok =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChangeWithSelect, (s32)trlEmuMenuCallBack_DLPOkSelect, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpok =
{
	1,
	{
		&cgbvcm_bt_commonwindow_ok		
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpok
};
/////////////
//scene dlp child standby
trlEmuMenuScene cgbvcm_scene_dlpchildstandby =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_childmain,
	NULL
};
/////////////
//scene dlp standby
trlEmuMenuScene cgbvcm_scene_dlpstandby =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_main,
	NULL
};

/////////////
//scene dlp main
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpmain =
{
	4, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
			7,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, NULL, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonDLPMain_Resume,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPStandBy, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 2
			eCGBVCMButtonDLPMain_Reset,
			5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPReset, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 3
			eCGBVCMButtonDLPMain_DL,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonDLPMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPMain2DLPEnd, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpmain =
{
	3,
	{
		&cgbvcm_bt_main_resume,
		&cgbvcm_bt_main_reset,
		&cgbvcm_bt_main_dl
	},
	&cgbvcm_btanim_main,
	&cgbvcm_layout_main,
	&cgbvcm_keyaction_dlpmain
};

//////////////
//scene dlp normal main
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpnmain =
{
	4, //action
	{
		{
			TRL_EMUMENU_BUTTON_NONE,
				7,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{
			eCGBVCMButtonNMain_Resume,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Decide, NULL, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPStandBy, SE_CTR_COMMON_RETURN } //decide action
		},
		{
			eCGBVCMButtonNMain_Reset,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_DL, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPReset, SE_CTR_COMMON_BUTTON } //decide action
		},
		{
			eCGBVCMButtonNMain_DL, //eCGBVCMButtonNMain_Change,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Reset, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNMain_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPNMain2DLPEnd, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpnmain =
{
	3,
	{
		&cgbvcm_bt_nmain_resume,
		&cgbvcm_bt_nmain_reset,
		&cgbvcm_bt_nmain_dl
	},
	&cgbvcm_btanim_nmain,
	&cgbvcm_layout_nmain,
	&cgbvcm_keyaction_dlpnmain
};

/////////////
//scene dlp end
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpend =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPEnd2DLPMain, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPEnd2DLPEndS, SE_CTR_COMMON_OK } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpend =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpend
};


/////////////
//scene dlp reset
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpreset =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_ResetYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonMessage_ResetNo, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonMessage_ResetNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChangeWithSelect, (s32)trlEmuMenuCallBack_DLPResetNoSelect, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonMessage_ResetYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChangeWithSelect, (s32)trlEmuMenuCallBack_DLPResetYesSelect, SE_CTR_COMMON_OK } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpreset =
{
	2,
	{
		&cgbvcm_bt_message_resetno,
			&cgbvcm_bt_message_resetyes
	},
	&cgbvcm_btanim_message,
	&cgbvcm_layout_message,
	&cgbvcm_keyaction_dlpreset
};

/////////////
//scene dlp endS
trlEmuMenuScene cgbvcm_scene_dlpends =
{
	0,
	{},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	NULL
};

/////////////
//scene dlp endok
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpendok =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChangeWithSelect, (s32)trlEmuMenuCallBack_DLPEndOkSelect, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpendok =
{
	1,
	{
		&cgbvcm_bt_commonwindow_ok
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpendok
};

/////////////
//scene dlp end wait
trlEmuMenuScene cgbvcm_scene_dlpendwait =
{
	0,
	{},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	NULL
};

/////////////
//scene dlp othermenu
trlEmuMenuScene cgbvcm_scene_dlpothermenu =
{
	0,
	{},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	NULL
};

/////////////
//scene dlp child error
trlEmuMenuScene cgbvcm_scene_dlpchilderror =
{
	0,
	{
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	NULL
};

/////////////
//scene error badformat ok
trlEmuMenuStateKeyAction errvcm_keyaction_dlperrorok = 
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				8,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },

			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eERRVCMButtonError_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChangeWithSelect, (s32)trlEmuMenuCallBack_DLPErrorOkSelect, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlperrorok =
{
	1,
	{
		&errvcm_bt_error_ok
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	&errvcm_keyaction_dlperrorok
};

/////////////
//scene dlp allleave
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpallleaveok =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPAllLeaveOk2DLPBegin, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpallleaveok =
{
	1,
	{
		&cgbvcm_bt_commonwindow_ok
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlpallleaveok
};

/////////////
//scene dlp have leaveok
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlphaveleaveok =
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_Ok, TRL_EMUMENU_SOUND_NOSOUND },
			},
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChangeWithSelect, (s32)trlEmuMenuCallBack_DLPHaveLeaveOkSelect, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlphaveleaveok =
{
	1,
	{
		&cgbvcm_bt_commonwindow_ok
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_dlphaveleaveok
};

trlEmuMenuScene cgbvcm_scene_dlphaveleaveend =
{
	0,
	{
	},
	NULL,
	&commonwindow_layout_main,
	NULL
};

trlEmuMenuScene cgbvcm_scene_dlperror =
{
	0,
	{
	},
	NULL,
	&commonwindow_layout_main,
	NULL
};

trlEmuMenuScene cgbvcm_scene_dlperrorend =
{
	0,
	{
	},
	NULL,
	&commonwindow_layout_main,
	NULL
};

/////////////
//scene net op pre
trlEmuMenuScene cgbvcm_scene_netoppre =
{
	0,
	{},
	NULL,
	&cgbvcm_layout_main,
	NULL
};

/////////////
//scene net dlp dlp error
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpdlperror = 
{
	2, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
#if TRL_VCM_MSG_DEBUG
				3,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{KEY_LEFT, eEmuMenuKeyActionType_CallBack, (s32)trlEmuMenuCallBack_ChangeErrorMessage, TRL_EMUMENU_SOUND_NOSOUND },
			},
#else
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eERRVCMButtonError_Ok, TRL_EMUMENU_SOUND_NOSOUND },
			},
#endif
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eERRVCMButtonError_Ok,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPDLPError2StandBy, SE_CTR_COMMON_OK } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_dlpdlperror =
{
	1,
	{
		&errvcm_bt_error_ok
	},
	&errvcm_btanim_error,
	&errvcm_layout_error,
	&cgbvcm_keyaction_dlpdlperror
};

/////////////
//scene net conn confirm
trlEmuMenuStateKeyAction cgbvcm_keyaction_netconnconfirm =
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
#if TRL_VCM_MSG_DEBUG
				3,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },
				{KEY_LEFT, eEmuMenuKeyActionType_CallBack, (s32)trlEmuMenuCallBack_ChangeCommonWNDMessage, TRL_EMUMENU_SOUND_NOSOUND },
			},
#else
				2,// num of onekeyaction
			{
				{BUTTON_A, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNYes, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_DecideButton, eCGBVCMButtonCommonWindow_YNNo, TRL_EMUMENU_SOUND_NOSOUND },

			},
#endif
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonCommonWindow_YNNo,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NetConnConfirm2Main, SE_CTR_COMMON_CANCEL } //decide action
		},
		{ //action 2
			eCGBVCMButtonCommonWindow_YNYes,
				0,// num of onekeyaction
			{},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_NetConnConfirm2NetInit, SE_CTR_COMMON_OK } //decide action
		}
	}
};
trlEmuMenuScene cgbvcm_scene_netconnconfirm =
{
	2,
	{
		&cgbvcm_bt_commonwindow_ynno,
		&cgbvcm_bt_commonwindow_ynyes
	},
	&cgbvcm_btanim_commonwindow,
	&commonwindow_layout_main,
	&cgbvcm_keyaction_netconnconfirm
};

/////////////
//scene netplay child
trlEmuMenuStateKeyAction cgbvcm_keyaction_dlpchildmain = 
{
	3, //action
	{
		{ //action 0
			TRL_EMUMENU_BUTTON_NONE,
				7,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_LEFT, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_RIGHT, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPChildMain2DLPChildStandBy, SE_CTR_COMMON_RETURN }
			},			
			{NULL, eEmuMenuKeyActionType_None, NULL, TRL_EMUMENU_SOUND_NOSOUND } //decide action
		},
		{ //action 1
			eCGBVCMButtonNetPlayChild_Resume,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Disconn, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Disconn, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPChildMain2DLPChildStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPChildMain2DLPChildStandBy, SE_CTR_COMMON_RETURN } //decide action
		},
		{ //action 2
			eCGBVCMButtonNetPlayChild_Disconn,
				5,// num of onekeyaction
			{
				{KEY_UP, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{KEY_DOWN, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_A, eEmuMenuKeyActionType_Decide, NULL, TRL_EMUMENU_SOUND_NOSOUND },
				{BUTTON_B, eEmuMenuKeyActionType_Move, eCGBVCMButtonNetPlayChild_Resume, SE_CTR_THREEB_CURSOR_MOVE },
				{BUTTON_X, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPChildMain2DLPChildStandBy, SE_CTR_COMMON_RETURN }
			},
			{NULL, eEmuMenuKeyActionType_StateChange, eCGBVCMStateChange_DLPChildMain2DLPChildEnd, SE_CTR_COMMON_BUTTON } //decide action
		}
	}
};

trlEmuMenuScene cgbvcm_scene_dlpchildmain =
{
	2,
	{
		&cgbvcm_bt_netplaychild_resume,
		&cgbvcm_bt_netplaychild_disconn
	},
	&cgbvcm_btanim_childmain,
	&cgbvcm_layout_childmain,
	&cgbvcm_keyaction_dlpchildmain
};
