/**
* @file trlEmuMenuDataAction.cpp
* @author zhfang
* @date 2011.07.02
* @brief trlEmuMenu
*/
#include "../../../trlMacro.h"
#include "../../trlEmuShellStruct.h"
#include "../../trlEmuShellNetWork.h"
#include "../../../../files/VCM/SND/threeb.csid"
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataButton.h"
#include "trlEmuMenuDataScene.h"
#include "trlEmuMenuDataCallBack.h"
#include "trlEmuMenuDataAction.h"

trlEmuMenuAction cgbvcm_action_init =
{
	1, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_nonactive_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_nonactive_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_nonactive_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_nonactive_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	},

};

//////////////////////////
//first time
trlEmuMenuAction cgbvcm_action_firsttime_w00_open =
{
	1, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_firsttime_w00,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		}
	}
};

trlEmuMenuAction cgbvcm_action_firsttime_w00_2_w01 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eFirstTimeMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w01,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		}
	}
};

trlEmuMenuAction cgbvcm_action_firsttime_w00_2_w02 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eFirstTimeMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w02,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_02", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w00}
		}
	}
};

trlEmuMenuAction cgbvcm_action_firsttime_w02_2_w03 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w02,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w02}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w02,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_02", eFirstTimeMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w02}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w03,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_03", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w02}
		}
	}
};

trlEmuMenuAction cgbvcm_action_firsttime_w02_2_w00 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w02,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w02}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w02,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_02", eFirstTimeMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w02}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w00,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w02}
		}
	}
};


trlEmuMenuAction cgbvcm_action_firsttime_w03_2_w02 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w03,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w03}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w03,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_03", eFirstTimeMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w03}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w02,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_02", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w03}
		}
	}
};

trlEmuMenuAction cgbvcm_action_firsttime_w03_2_w01 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w03,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w03}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w03,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_03", eFirstTimeMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w03}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w01,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eFirstTimeMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w03}
		}
	}
};


trlEmuMenuAction cgbvcm_action_firsttime_w01_2_nmain =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eFirstTimeMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		},
		{//step 2
			1,
			{
				{//scene0
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_SetMenuNormalMode},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eNMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonNMain_Resume}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		}
	}
};

trlEmuMenuAction cgbvcm_action_firsttime_w01_2_modechangentoa0 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eFirstTimeMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_firsttime_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eFirstTimeMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_firsttime_w01}
		}
	}
};




/////////////
//main
trlEmuMenuAction cgbvcm_action_mainopen =
{
	2, //total step
	{
		{//step 0
			3,
			{
				{//scene 0
					&cgbvcm_scene_main,
						4,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_VCM_01, (s32)trlEmuMenuCallBack_SetMainDLBtMessage},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_activate_00},
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_activate_00}
					}
				},
				{//scene 2
					&cgbvcm_scene_reset,
						3,
					{						
						{eEmuMenuActionType_SetVisible, "T_Reset_00", NULL},
						{eEmuMenuActionType_SetVisible, "T_Reset_01", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_Reset_02", NULL}
					}
				},
			},
				3,
			{&cgbvcm_scene_reset, &cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonMain_Resume}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_mainclose =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_mainclosex =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)TRL_NETWORK_COMMAND_RESUME, (s32)trlEmuMenuCallBack_NetCommand}

					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

//////////////////////////
//main fade in
trlEmuMenuAction cgbvcm_action_mainfadein =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

//////////////////////////
//normal fade in
trlEmuMenuAction cgbvcm_action_nmainfadein =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};


//////////////////////////
//main fade out
trlEmuMenuAction cgbvcm_action_mainfadeout =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

//////////////////////////
//normal main fade out
trlEmuMenuAction cgbvcm_action_nmainfadeout =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};


//////////////////////////
//save
trlEmuMenuAction cgbvcm_action_saveopen =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_save,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_SaveAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_BeginAnimLoop, "W_SaveLAll_00", eMessageAnim_Bg_loop_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		}
	}
};

trlEmuMenuAction cgbvcm_action_saveback =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_save,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_save,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_SaveAll_00", eMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		}
	}
};

trlEmuMenuAction cgbvcm_action_saveing =
{
	3, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_SaveBtn_00", eMainAnim_focus_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_save,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_save,
						0,
					{
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eMessageAnim_loop_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_save,
						0,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eMessageAnim_loop_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		}
	}
};

trlEmuMenuAction cgbvcm_action_saveokopen =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_save,
						0,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eMessageAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eMessageAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_save,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_SaveAll_00", eMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_saveok,
						4,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_UpdateSavePreview},
						{eEmuMenuActionType_BeginAnim, "W_SaveOKAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_BeginAnimLoop, "W_SaveOKLAll_00", eMessageAnim_Bg_loop_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_saveok,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Effect_00", eMessageAnim_effect_00},
						{eEmuMenuActionType_Playsound, NULL, SE_CTR_THREEB_BACKUP_EFFECT}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
	}
};

trlEmuMenuAction cgbvcm_action_saveokclose =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_saveok,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 1
			1,
			{
				{//scene 1
					&cgbvcm_scene_save,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_SaveOKAll_00", eMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 2
			1,
			{
				{//scene 2
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00},
						{eEmuMenuActionType_BeginAnim, "N_LoadBtn_00", eMainAnim_visible_off_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
		{//step 3
			1,
			{
				{//scene 3
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_focus_00},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonMain_Resume}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_save}
		},
	}
};

//////////////////////////
//load
trlEmuMenuAction cgbvcm_action_loadopen =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_load,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_LoadAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_BeginAnimLoop, "W_LoadLAll_00", eMessageAnim_Bg_loop_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		}
	}
};

trlEmuMenuAction cgbvcm_action_loadback =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_LoadAll_00", eMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		}
	}
};

trlEmuMenuAction cgbvcm_action_loading =
{
	3, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_LoadBtn_00", eMainAnim_focus_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_load,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBakc_LoadFade_To_FadeIn1},
						{eEmuMenuActionType_CallBackWait, NULL, (s32)trlEmuMenuCallBakc_LoadFade_FadeIn1End}
						//{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eMessageAnim_loop_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						0,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eMessageAnim_loop_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		}
	}
};

trlEmuMenuAction cgbvcm_action_loadokopen =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBakc_LoadFade_To_FadeIn2},
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eMessageAnim_loop_00}
						//{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eMessageAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						2,
					{
						{eEmuMenuActionType_CallBackWait, NULL, (s32)trlEmuMenuCallBakc_LoadFade_FadeIn2End},
						{eEmuMenuActionType_BeginAnim, "W_LoadAll_00", eMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_loadok,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_LoadOKAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_BeginAnimLoop, "W_LoadOKLAll_00", eMessageAnim_Bg_loop_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		}
	}
};

trlEmuMenuAction cgbvcm_action_loadokclose =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_loadok,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_load,
						3,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBakc_LoadFade_To_FadeOut},
						{eEmuMenuActionType_CallBackWait, NULL, (s32)trlEmuMenuCallBakc_LoadFade_FadeOutEnd},
						{eEmuMenuActionType_BeginAnim, "W_LoadOKAll_00", eMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_focus_00},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonMain_Resume}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_load}
		},
	}
};

//////////////////////////
//reset
trlEmuMenuAction cgbvcm_action_resetopen =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_reset,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_resetback =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_reset,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_reset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_reseting =
{
	1, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResetBtn_00", eMainAnim_focus_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_reset,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_reset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_resetingclose =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_reset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_close_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main, &cgbvcm_scene_reseting}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eMainAnim_fade_to_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_fade_to_deactivate_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main, &cgbvcm_scene_reseting}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_01}
					}
				},
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main, &cgbvcm_scene_reseting}
		}
	}
};


//////////////////////////
//normal main
trlEmuMenuAction cgbvcm_action_nmainopen0 =
{
	1, //total step
	{
		{//step 0
			3,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_VCM_01, (s32)trlEmuMenuCallBack_SetMainDLBtMessage},
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_activate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene 2
					&cgbvcm_scene_reset,
						3,
					{						
						{eEmuMenuActionType_SetVisible, "T_Reset_00", NULL},
						{eEmuMenuActionType_SetVisible, "T_Reset_01", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_Reset_02", NULL}
					}
				}
			},
				3,
			{&cgbvcm_scene_reset, &cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_nmainopen1 =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eNMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonNMain_Resume}
					}
				}
			},
				1,
			{&cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_nmainclose =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_action_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)TRL_NETWORK_COMMAND_CLOSE, (s32)trlEmuMenuCallBack_NetCommand}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_nmainclosex =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)TRL_NETWORK_COMMAND_CLOSE, (s32)trlEmuMenuCallBack_NetCommand}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};



//////////////////////////
//normal reset
trlEmuMenuAction cgbvcm_action_nresetopen =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nreset,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eNMessageAnim_open_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_nresetback =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nreset,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_nreset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eNMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_nreseting =
{
	1, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResetBtn_00", eNMainAnim_focus_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nreset,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_nreset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_nresetingclose =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nreset,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eNMessageAnim_close_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)TRL_NETWORK_COMMAND_CLOSE, (s32)trlEmuMenuCallBack_NetCommand}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain, &cgbvcm_scene_nreseting}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_fade_to_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eMainAnim_fade_to_deactivate_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain, &cgbvcm_scene_nreseting}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain, &cgbvcm_scene_nreseting}
		}
	}
};


//////////////////////////
//modechange w00
trlEmuMenuAction cgbvcm_action_modechange_w00_open =
{
	1, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w00,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eNMessageAnim_open_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{

						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		}
	}
};

trlEmuMenuAction cgbvcm_action_modechange_w00_back =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eNMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 2
			1,
			{

				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		}
	}
};

//////////////////////////
//modechange w1
trlEmuMenuAction cgbvcm_action_modechange_w01_open =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w00,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_00", eNMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w01,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eNMessageAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		}
	}
};

trlEmuMenuAction cgbvcm_action_modechange_w01_back =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eNMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		}
	}
};

trlEmuMenuAction cgbvcm_action_modechange_w01_close =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMessageAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_modechange_w01,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_MSG_01", eNMessageAnim_close_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_Playsound, NULL, SE_CTR_THREEB_MENU_START},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_modechange_w00}
		}
	}
};

//////////////////////////
//modechange nota aton
trlEmuMenuAction cgbvcm_action_modechange_ntoa0 =
{
	1, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_SetMenuAdvMode},
						{eEmuMenuActionType_BeginAnim, "N_BtnAll_00", eNMainAnim_N_to_A_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00},
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_modechange_ntoa1 =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimNoRecursive, "N_BtnAll_00", eMainAnim_N_to_A_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},		
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonMain_Resume}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_modechange_aton0 =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_Playsound, NULL, SE_CTR_THREEB_MENU_START},
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_SetMenuNormalMode},
						{eEmuMenuActionType_BeginAnimNoRecursive, "N_BtnAll_00", eMainAnim_A_to_N_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00},
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};


trlEmuMenuAction cgbvcm_action_modechange_aton1 =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_BtnAll_00", eNMainAnim_A_to_N_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_nmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eNMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonNMain_Resume}
					}
				}
			},
				1,
			{&cgbvcm_scene_nmain}
		}
	}
};


//////////////////////////
//error notformatwait
trlEmuMenuAction errvcm_action_notformatwait_open =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_notformatwait,
						2,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_05, (s32)trlEmuMenuCallBakc_SetErrorMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}
					}
				}
			},
				1,
			{&errvcm_scene_notformatwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&errvcm_scene_notformatwait,
						1,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eErrorAnim_wait_00}
					}
				}
			},
				1,
			{&errvcm_scene_notformatwait}
		}
	}
};

trlEmuMenuAction errvcm_action_notformatwait_close =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_notformatwait,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eErrorAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eErrorAnim_close_00}

					}
				}
			},
				1,
			{&errvcm_scene_notformatwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&errvcm_scene_notformatwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_close_00}

					}
				}
			},
				1,
			{&errvcm_scene_notformatwait}
		}
	}
};

//////////////////////////
//error badformat
trlEmuMenuAction errvcm_action_badformatok_open =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_01, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}

					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		}
	}
};

trlEmuMenuAction errvcm_action_badformatok_beginwait =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eErrorAnim_action_00}

					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		},
		{//step 1
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_06, (s32)trlEmuMenuCallBakc_SetErrorMessageWait}

					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		},
		{//step 2
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}

					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		},
		{//step 3
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						1,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eErrorAnim_wait_00}
					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		}
	}
};

trlEmuMenuAction errvcm_action_badformatok_closewait_done =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eErrorAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eErrorAnim_close_00}

					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		},
		{//step 1
			1,
			{
				{//scene 0
					&errvcm_scene_badformatok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_close_00}
					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		},
		{//step 2
			1,
			{
				{//scene 0
					&errvcm_scene_badformatdone,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_04, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				}
			},
				1,
			{&errvcm_scene_badformatok}
		}
	}
};

trlEmuMenuAction errvcm_action_badformatdone_close =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_badformatdone,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00}
					}
				}
			},
				1,
			{&errvcm_scene_badformatdone}
		}
	}
};

//////////////////////////
//error vfailed
trlEmuMenuAction errvcm_action_vfailedok_open =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_01, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}

					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		}
	}
};

trlEmuMenuAction errvcm_action_vfailedok_beginwait =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eErrorAnim_action_00}

					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		},
		{//step 1
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_06, (s32)trlEmuMenuCallBakc_SetErrorMessageWait}

					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		},
		{//step 2
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}

					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		},
		{//step 3
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						1,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eErrorAnim_wait_00}
					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		}
	}
};

trlEmuMenuAction errvcm_action_vfailedok_closewait_done =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eErrorAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eErrorAnim_close_00}

					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		},
		{//step 1
			1,
			{
				{//scene 0
					&errvcm_scene_vfailedok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_close_00}
					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		},
		{//step 2
			1,
			{
				{//scene 0
					&errvcm_scene_vfaileddone,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_04, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				}
			},
				1,
			{&errvcm_scene_vfailedok}
		}
	}
};

trlEmuMenuAction errvcm_action_vfaileddone_close =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_vfaileddone,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00}
					}
				}
			},
				1,
			{&errvcm_scene_vfaileddone}
		}
	}
};


//////////////////////////
//error opdeniedwait
trlEmuMenuAction errvcm_action_opdeniedwait_open =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&errvcm_scene_opdeniedwait,
						2,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_02, (s32)trlEmuMenuCallBakc_SetErrorMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}
					}
				}
			},
				1,
			{&errvcm_scene_opdeniedwait}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpbeginback2dlpbegin =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbeginback,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eCommonWindowAnim_action_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin, &cgbvcm_scene_netconnconfirm}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbeginback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin, &cgbvcm_scene_dlpbeginback}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpbeginback2backmain =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbeginback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin, &cgbvcm_scene_dlpbeginback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 4
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpbeginback2dlpdlperror =
{
	6, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbeginback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin, &cgbvcm_scene_dlpbeginback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 4
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 5
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				},
			},
			2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};

/////////////////////////
//net conn confirm
trlEmuMenuAction cgbvcm_action_netconnconfirmopen =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_netconnconfirm,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_00, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_netconnconfirm}
		}
	}
};

/////////////////////////
//net conn confirm
trlEmuMenuAction cgbvcm_action_netoppre2dlpdlperror =
{
	1, //total step
	{	
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_07, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};

trlEmuMenuAction cgbvcm_action_netinit2dlpdlperror =
{
	1, //total step
	{	
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						4,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_ReleaseDLP},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_07, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};

trlEmuMenuAction cgbvcm_action_netconnconfirmback =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_netconnconfirm,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eCommonWindowAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_netconnconfirm}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_netconnconfirm,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_netconnconfirm}
		},
		{//step 2
			1,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},
	}
};

trlEmuMenuAction cgbvcm_action_dlpdlperrorclose =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eErrorAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_EnableHomeButton}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		},
		{//step 2
			1,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},
	}
};

trlEmuMenuAction cgbvcm_action_netconnconfirm2netinit =
{
	2, //total step
	{
		{//step 0
			3,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_netconnconfirm,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eCommonWindowAnim_action_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main, &cgbvcm_scene_netconnconfirm}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_netconnconfirm,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_netconnconfirm}
		}
	}
};

trlEmuMenuAction cgbvcm_action_netinit2dlpbegin =
{
	4, //total step
	{	
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						8,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_open_00},
						{eEmuMenuActionType_SetVisible, "N_DLSet_00", NULL},
						{eEmuMenuActionType_SetVisible, "T_DL_title_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "N_DLPlayer_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "N_DLWait_00", NULL},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_InitDLP},
						{eEmuMenuActionType_SetBtDisable, NULL, (s32)(&cgbvcm_bt_messagedl_yes)}

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_DLRFade_00", emessage_DLAnim_visible_on_00},

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_open_00}

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{	
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00}

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpbegin2dlpbeginback =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_action_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_in_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbeginback,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_01, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				},
			},
			3,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin, &cgbvcm_scene_dlpbeginback}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpbegin2dlpdlperror =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				},
			},
			2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpbegin2dlpconn =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_MakeDLPName},
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpbegin}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						5,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetUnVisible, "N_DLSet_00", NULL},
						{eEmuMenuActionType_SetVisible, "N_DLPlayer_00", NULL},
						{eEmuMenuActionType_SetBtEnable, NULL, (s32)(&cgbvcm_bt_messagedl_yes)},
						{eEmuMenuActionType_BeginAnim, "N_DLRFade_00", emessage_DLAnim_visible_off_00},
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpconn2dlpdlperror =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						4,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP},
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}		
	}
};

trlEmuMenuAction cgbvcm_action_dlpconn2dlpconnback =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{						
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_in_00}
						//{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_action_00},
						//{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				},
				{//scene 1
					&cgbvcm_scene_dlpconnback,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_01, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn, &cgbvcm_scene_dlpconnback}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpconnback2dlpconn =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconnback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn, &cgbvcm_scene_dlpconnback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpconnback2backmain =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconnback,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn, &cgbvcm_scene_dlpconnback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 4
			1,
			{
				{//scene 1
					&cgbvcm_scene_dlpconn,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpconnback2dlpdlperror =
{
	6, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconnback,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn, &cgbvcm_scene_dlpconnback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 4
			1,
			{
				{//scene 1
					&cgbvcm_scene_dlpconn,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 5
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpconn2dlp =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpconn,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_DLRBtn_00", emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpconn}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						6,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},						
						{eEmuMenuActionType_SetUnVisible, "N_DLPlayer_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_DL_title_00", NULL},
						{eEmuMenuActionType_SetVisible, "N_DLWait_00", NULL},
						{eEmuMenuActionType_SetBtDisable, NULL, (s32)(&cgbvcm_bt_messagedl_yes)},
						{eEmuMenuActionType_BeginAnim, "N_DLRFade_00", emessage_DLAnim_visible_on_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_BeginTrans},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlp2dlpnetinit =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_PiaCommonInit}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlp2dlpdlperror = 
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlp2dlpback =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{						
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_in_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_dlpback,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_01, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp, &cgbvcm_scene_dlpback}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpback2dlp =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp, &cgbvcm_scene_dlpback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpback2backmain =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpback,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp, &cgbvcm_scene_dlpback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 4
			1,
			{
				{//scene 1
					&cgbvcm_scene_dlp,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpback2dlpdlperror =
{
	6, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpback,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLP}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp, &cgbvcm_scene_dlpback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 4
			1,
			{
				{//scene 1
					&cgbvcm_scene_dlp,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlp}
		},
		{//step 5
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpnetinit2dlps =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_SetNetMode},
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_00}

					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlps2dlpdlperror = 
{
	1, //total step
	{	
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpdlperror,
						4,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_08, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_SetNoneNetMode}
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpdlperror}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpnetinit2dlpnetinitback =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						1,
					{						
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_in_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_dlpnetinitback,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_01, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit, &cgbvcm_scene_dlpnetinitback}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpnetinitback2dlpnetinit =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinitback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit, &cgbvcm_scene_dlpnetinitback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
					}
				},
			},
			2,
				{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnetinitback2backmain =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinitback,
						4,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseNet},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseDLPWarning},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Init4PMessage}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit, &cgbvcm_scene_dlpnetinitback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 4
			1,
			{
				{//scene 1
					&cgbvcm_scene_dlpnetinit,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_EnableHomeButton}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnetinitback2dlps =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinitback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit, &cgbvcm_scene_dlpnetinitback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnetinit,
						2,
					{	
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlp,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		},
		{//step 4
			1,
			{
				{//scene 1
					&cgbvcm_scene_dlpnetinit,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpnetinit}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlps2dlpwait =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						3,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eChildMainAnim_activate_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_in_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpwait,
						6,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_InitNetChild},						
						{eEmuMenuActionType_SetUnVisible, "N_DLSet_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "N_DLPlayer_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_DL_title_00", NULL},
						{eEmuMenuActionType_SetVisible, "N_DLWait_00", NULL},						
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						3,
					{
						{eEmuMenuActionType_SetBtDisable, NULL, (s32)(&cgbvcm_bt_messagedl_yes)},
						{eEmuMenuActionType_BeginAnim, "N_DLRFade_00", emessage_DLAnim_visible_on_00},
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00}

					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpwait2dlpchilderror =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00},

					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchilderror,
						3,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseNet},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_10, (s32)trlEmuMenuCallBakc_SetErrorMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpchilderror}
		}
	}
};



trlEmuMenuAction cgbvcm_action_dlpwait2dlpwaitback =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_action_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_in_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwaitback,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_01, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				},
			},
			3,
				{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait, &cgbvcm_scene_dlpwaitback}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpwaitback2dlpwait =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwaitback,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eCommonWindowAnim_action_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait, &cgbvcm_scene_dlpwaitback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwaitback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				3,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait, &cgbvcm_scene_dlpwaitback}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, emessage_DLAnim_focus_out_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
					}
				},
			},
			2,
				{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", emessage_DLAnim_fade_out_00}
					}
				},
			},
			2,
				{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		}
		
	}
};

trlEmuMenuAction cgbvcm_action_dlpwaitback2dlpchildendwait =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwaitback,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eCommonWindowAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwaitback}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwaitback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwaitback}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						3,
					{						
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseNet},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_05, (s32)trlEmuMenuCallBakc_SetDLPMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpendwait}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpwaitback2dlpchilderror =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwaitback,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwaitback}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchilderror,
						3,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseNet},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_10, (s32)trlEmuMenuCallBakc_SetErrorMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpchilderror}
		}
	}
};



trlEmuMenuAction cgbvcm_action_dlps2dlpok =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpok,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_03, (s32)trlEmuMenuCallBakc_SetDLPMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlps2dlperrorok =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlperrorok,
						3,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseNet},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_09, (s32)trlEmuMenuCallBakc_SetErrorMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlperrorok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlps2dlpstandby =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlps,
						1,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_EndDLPMenu}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlps2dlpnstandby =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlps,
						1,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_EndDLPMenu}
					}
				}
			},
				1,
			{&cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpok2dlpstandby =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpok,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_EndDLPMenu},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpok2dlpnstandby =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpok,
						2,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_EndDLPMenu},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}


					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpok2dlperror =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpok}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpwait2dlpchildstandby =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", emessage_DLAnim_loop_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", emessage_DLAnim_loop_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_DLAll_00", emessage_DLAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpwait}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						3,
					{
						{eEmuMenuActionType_SetUnVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_out_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						3,
					{	
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eChildMainAnim_deactivate_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 4
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpstandby2dlperror =
{
	3, //total step
	{
		{//step 1
			3,
			{
				{//scene 0
					&cgbvcm_scene_main,
						5,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_VCM_02, (s32)trlEmuMenuCallBack_SetMainDLBtMessage},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00},
					}
				},
				{//scene 2
					&cgbvcm_scene_reset,
						3,
					{						
						{eEmuMenuActionType_SetUnVisible, "T_Reset_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_Reset_01", NULL},
						{eEmuMenuActionType_SetVisible, "T_Reset_02", NULL}
					}
				}
			},
				3,
			{&cgbvcm_scene_reset, &cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{						
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpstandby2dlpnerror =
{
	3, //total step
	{
		{//step 1
			3,
			{
				{//scene 0
					&cgbvcm_scene_main,
						5,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_VCM_02, (s32)trlEmuMenuCallBack_SetMainDLBtMessage},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene 2
					&cgbvcm_scene_reset,
						3,
					{						
						{eEmuMenuActionType_SetUnVisible, "T_Reset_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_Reset_01", NULL},
						{eEmuMenuActionType_SetVisible, "T_Reset_02", NULL}
					}
				}
			},
				3,
			{&cgbvcm_scene_reset, &cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{						
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpmain2dlperror =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnmain2dlperror =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpmain_open =
{
	2, //total step
	{
		{//step 0
			3,
			{
				{//scene 0
					&cgbvcm_scene_main,
						5,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_VCM_02, (s32)trlEmuMenuCallBack_SetMainDLBtMessage},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_activate_00},
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						4,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eNMainAnim_activate_00},
					}
				},
				{//scene 2
					&cgbvcm_scene_reset,
						3,
					{						
						{eEmuMenuActionType_SetUnVisible, "T_Reset_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_Reset_01", NULL},
						{eEmuMenuActionType_SetVisible, "T_Reset_02", NULL}
					}
				}
			},
				3,
			{&cgbvcm_scene_reset, &cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonMain_Resume}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnmain_open =
{
	2, //total step
	{
		{//step 0
			3,
			{
				{//scene 0
					&cgbvcm_scene_main,
						5,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_VCM_02, (s32)trlEmuMenuCallBack_SetMainDLBtMessage},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eMainAnim_activate_00},
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						4,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eNMainAnim_activate_00},
					}
				},
				{//scene 2
					&cgbvcm_scene_reset,
						3,
					{						
						{eEmuMenuActionType_SetUnVisible, "T_Reset_00", NULL},
						{eEmuMenuActionType_SetUnVisible, "T_Reset_01", NULL},
						{eEmuMenuActionType_SetVisible, "T_Reset_02", NULL}
					}
				}
			},
				3,
			{&cgbvcm_scene_reset, &cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eNMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonNMain_Resume}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpnmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildmain_open =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eChildMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eChildMainAnim_activate_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_ResumeBtn_00", eChildMainAnim_focus_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_SetIndexCur, NULL, eCGBVCMButtonNetPlayChild_Resume}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpmain_close =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}

					}
				},
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						5,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)PLAYER_COMMAND_CLOSEMENU, (s32)trlEmuMenuCallBack_NetSetState}

					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00},

					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnmain_close =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}

					}
				},
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpnmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						5,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)PLAYER_COMMAND_CLOSEMENU, (s32)trlEmuMenuCallBack_NetSetState}

					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00},
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpnmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildmain_close =
{
	2, //total step
	{
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eChildMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						5,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eChildMainAnim_focus_out_00},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)PLAYER_COMMAND_CLOSEMENU, (s32)trlEmuMenuCallBack_NetSetState}

					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpothermenu_open =
{
	5, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_activate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{						
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpothermenu}
		},
		{//step 4
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpothermenu}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnothermenu_open =
{
	5, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_activate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_04, (s32)trlEmuMenuCallBakc_SetDLPMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpothermenu}
		},
		{//step 4
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpothermenu}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpothermenu2dlperror =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpothermenu}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpothermenu_close =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 4
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnothermenu_close =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 4
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildothermenu_open =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eChildMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eChildMainAnim_activate_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_in_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
						//{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_04, (s32)trlEmuMenuCallBakc_SetDLPMessageWait},
						
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchilderrors_open =
{
	2, //total step
	{
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						4,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eChildMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eChildMainAnim_activate_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 1
			1,
			{
				{//scene0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_in_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildothermenu2dlpchilderrors =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchilderrors2dlpchilderror =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchilderror,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_WaitAll_00", eErrorAnim_open_00}
						
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpchilderror}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildothermenu_close =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 2
			1,
			{
				{//scene0
					&cgbvcm_scene_dlpchildmain,
						2,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_out_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 3
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eChildMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eChildMainAnim_deactivate_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 4
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildend_open =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eChildMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_in_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_12, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpend}
		}
	}

};

trlEmuMenuAction cgbvcm_action_dlpend_open =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_12, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpend}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpreset_open =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						2,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 2
			1,
			{
				{//scene1
					&cgbvcm_scene_dlpreset,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpnend_open =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpnmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpnmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_12, (s32)trlEmuMenuCallBakc_SetDLPMessageYN},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpend}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpnreset_open =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_action_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpnmain}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpnmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpreset,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_open_00},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpreset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildend_close1 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpend}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eChildMainAnim_fade_out_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpchildmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eChildMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpchildmain}
		}
	}
};




trlEmuMenuAction cgbvcm_action_dlpreset_close1 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpreset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		},		
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpmain}
		}
	}

};

trlEmuMenuAction cgbvcm_action_dlpend_close1 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpend}
		},		
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnreset_close1 =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpreset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpreset}
		},		
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpnmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpnmain}
		}
	}
};



trlEmuMenuAction cgbvcm_action_dlpnend_close1 =
{
	3, //total step
	{		
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_01}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpend}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpnmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpnmain}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlpend_close =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpend}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)PLAYER_COMMAND_QUIT, (s32)trlEmuMenuCallBack_NetSetState}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpend}
		},
	}
};

trlEmuMenuAction cgbvcm_action_dlpreset2dlperror =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpreset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpend2dlperror =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				},
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				}
			},
				3,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpend}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpend}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpreset_close =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eMainAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpreset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnreset_close =
{
	4, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpnmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eNMainAnim_focus_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpnmain, &cgbvcm_scene_dlpreset}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpreset,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ResetAll_00", eMessageAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpreset}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "W_MsgBg_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "T_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildothermenutodlpchildendwait =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						2,
					{
						{eEmuMenuActionType_EndAnimLoop, "P_LoadingAll_00", eCommonWindowAnim_wait_00},
						{eEmuMenuActionType_BeginAnim, "P_LoadingAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpend}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						2,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_07, (s32)trlEmuMenuCallBakc_SetDLPMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpendwait}
		}
	}
};
trlEmuMenuAction cgbvcm_action_dlpchildendtochildendwait =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpend}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)PLAYER_COMMAND_QUIT, (s32)trlEmuMenuCallBack_NetSetState},
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_08, (s32)trlEmuMenuCallBakc_SetDLPMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpendwait}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildend2dlpchilderrors =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpend}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpchildend2dlpchildothermenu =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpend,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_YN_All_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpend}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpothermenu,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpchildmain, &cgbvcm_scene_dlpothermenu}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpendok_open =
{
	1, //total step
	{
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendok,
						4,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_06, (s32)trlEmuMenuCallBakc_SetDLPMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_SetNoneNetMode}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpendok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpendok_close =
{
	1, //total step
	{
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpendok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpendok2standby =
{
	4,
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpendok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},			
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Convert4PMessage}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnendok2standby =
{
	4,
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlpendok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Convert4PMessage}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
	}
};


trlEmuMenuAction cgbvcm_action_dlpendwait_open =
{
	2, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						2,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)HVC_WND_08, (s32)trlEmuMenuCallBakc_SetDLPMessageWait},
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpendwait}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpendwait_close =
{
	1, //total step
	{
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpendwait}
		}
	}
};


trlEmuMenuAction cgbvcm_action_dlperrorok_open =
{
	1, //total step
	{	
		{//step 2
			1,
			{

				{//scene 0
					&cgbvcm_scene_dlperrorok,
						2,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlperrorok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnerrorok_open =
{
	3, //total step
	{
		{//step 0
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_activate_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_activate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_activate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 1
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_in_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_in_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlperrorok,
						4,
					{
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_CloseNet},
						{eEmuMenuActionType_CallBackWithParam, (char*)ERR_MSG_09, (s32)trlEmuMenuCallBakc_SetErrorMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlperrorok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlperrorokclose =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlperrorok,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eErrorAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlperrorok}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlperrorok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlperrorok}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_SetVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_SetVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 3
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 4
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Convert4PMessage}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpnerrorokclose =
{
	5, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlperrorok,
						1,
					{
						{eEmuMenuActionType_BeginAnimOnCurButton, NULL, eErrorAnim_action_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlperrorok}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlperrorok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_ER_OKAll_00", eErrorAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_dlperrorok}
		},
		{//step 2
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						3,
					{
						{eEmuMenuActionType_SetVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_fade_out_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						3,
					{
						{eEmuMenuActionType_SetVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_SetUnVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_fade_out_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 3
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_00}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_Fade_00", eNMainAnim_deactivate_00},
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 4
			2,
			{
				{//scene0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Convert4PMessage}
					}
				},
				{//scene1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_SetVisible,"N_BtnAll_00", NULL},
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpallleaveok_open1 =
{
	1, //total step
	{
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpallleaveok,
						3,
					{
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_CallBackWithParam, (char*)WND_MSG_10, (s32)trlEmuMenuCallBakc_SetDLPMessageOK},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpallleaveok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpallleaveok_open =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpendwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpallleaveok,
						4,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)WND_MSG_10, (s32)trlEmuMenuCallBakc_SetDLPMessageOK},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_AllLeaveOk},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpallleaveok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveerrorok_open =
{
	2, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpendwait,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_WaitAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpendwait}
		},
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpallleaveok,
						4,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)WND_MSG_10, (s32)trlEmuMenuCallBakc_SetDLPMessageOK},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_AllLeaveOk},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlpallleaveok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlpallleaveok_close =
{
	2, //total step
	{
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpallleaveok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpallleaveok}
		},
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlpbegin,
						0,
					{
						//{eEmuMenuActionType_BeginAnim, "N_BtnAll_00", eMultiMainAnim_open_00}
					}
				}
			},
				1,
			{&cgbvcm_scene_dlpbegin}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveleaveok_open1 =
{
	1, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlphaveleaveok,
						3,
					{
						{eEmuMenuActionType_CallBackWithParam, (char*)WND_MSG_09, (s32)trlEmuMenuCallBakc_SetDLPMessageOK},
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlphaveleaveok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveleaveok_open =
{
	1, //total step
	{	
		{//step 1
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlphaveleaveok,
						2,
					{	
						{eEmuMenuActionType_NoneButtonIndex, NULL, NULL},
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_open_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpmain, &cgbvcm_scene_dlphaveleaveok}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveleaveok_close =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlphaveleaveok,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpstandby, &cgbvcm_scene_dlphaveleaveok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eMainAnim_fade_to_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_fade_to_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_01},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Convert4PMessage}
					}
				},
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveleaveok_nclose =
{
	3, //total step
	{
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlphaveleaveok,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)TRL_NETWORK_COMMAND_CLOSE, (s32)trlEmuMenuCallBack_NetCommand}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpstandby, &cgbvcm_scene_dlphaveleaveok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eMainAnim_fade_to_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_fade_to_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_01},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_Convert4PMessage}
					}
				},
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_main, &cgbvcm_scene_nmain}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveerrorok_close =
{
	3, //total step
	{
		{//step 0
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlphaveleaveok,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBackWithParam, (char*)TRL_NETWORK_COMMAND_CLOSE, (s32)trlEmuMenuCallBack_NetCommand}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpstandby, &cgbvcm_scene_dlphaveleaveok}
		},
		{//step 1
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						2,
					{
						{eEmuMenuActionType_SetVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_BeginAnimAll, NULL, eMainAnim_fade_to_deactivate_00}
					}
				},
				{//scene 1
					&cgbvcm_scene_nmain,
						2,
					{
						{eEmuMenuActionType_SetVisible, "T_HomeMsg_00", NULL},
						{eEmuMenuActionType_BeginAnimAll, NULL, eNMainAnim_fade_to_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		},
		{//step 2
			2,
			{
				{//scene 0
					&cgbvcm_scene_main,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eMainAnim_deactivate_01}
					}
				},
				{//scene 0
					&cgbvcm_scene_nmain,
						1,
					{
						{eEmuMenuActionType_BeginAnim, "N_TouchMsg_00", eNMainAnim_deactivate_00}
					}
				}
			},
				2,
			{&cgbvcm_scene_nmain, &cgbvcm_scene_main}
		}
	}
};

trlEmuMenuAction cgbvcm_action_dlphaveleaveok_close1 =
{
	1, //total step
	{
		{//step 2
			1,
			{
				{//scene 0
					&cgbvcm_scene_dlphaveleaveok,
						2,
					{
						{eEmuMenuActionType_BeginAnim, "W_OKAll_00", eCommonWindowAnim_close_00},
						{eEmuMenuActionType_CallBack, NULL, (s32)trlEmuMenuCallBack_ErrorHaveLeaveOk}
					}
				}
			},
				2,
			{&cgbvcm_scene_dlpstandby, &cgbvcm_scene_dlphaveleaveok}
		}
	}
};
