/**
* @file trlEmuMenuDataFunc.cpp
* @author zhfang
* @date 2011.06.20
* @brief trlEmuMenu
*/
#include <nn/cfg.h>
#include "../../trlEmuShellStruct.h"
#include "../trlEmuShellDlp.h"
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataLayout.h"
#include "trlEmuMenuDataArc.h"
#include "trlEmuMenuDataButton.h"
#include "trlEmuMenuDataScene.h"
#include "trlEmuMenuDataState.h"
#include "trlEmuMenuDataFunc.h"

void trlEmuMenuInitRes()
{
	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_AGB:
	case TRL_EMUCORE_ROMTYPE_CGB:	
		cgbvcm_arc.mArcFileName = L"rom:/VCM/CGBVCM/layout.arc";
		cgbvcm_arc.mLayoutNum = (eCGBVCMLayoutNum - 3); //remove the net layouts 3

		cgbvcm_main_anim.mAnimNum = eMainAnim_close_00;
		cgbvcm_nmain_anim.mAnimNum = eNMainAnim_close_00;
		
		cgbvcm_scene_main.mButtonNum = 4;
		cgbvcm_scene_nmain.mButtonNum = 2;
		
	
		break;
	case TRL_EMUCORE_ROMTYPE_NES:		
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		cgbvcm_arc.mArcFileName = L"rom:/VCM/HVCVCM/VCM_DL/layout.arc";
		cgbvcm_arc.mLayoutNum = (eCGBVCMLayoutNum - 1); //remove the mode change....

		//cgbvcm_main_anim.mAnimNum = eMainAnimNum;
		//cgbvcm_nmain_anim.mAnimNum = eNMainAnimNum;
		cgbvcm_main_anim.mAnimNum = eMainAnim_close_00;
		cgbvcm_nmain_anim.mAnimNum = eNMainAnim_close_00;
		
		cgbvcm_scene_main.mButtonNum = 5;
		cgbvcm_scene_nmain.mButtonNum = 3;
#else
		cgbvcm_arc.mArcFileName = L"rom:/VCM/HVCVCM/Menu/layout.arc";
		cgbvcm_arc.mLayoutNum = (eCGBVCMLayoutNum - 3); //remove the net layouts 3;

		cgbvcm_main_anim.mAnimNum = eMainAnim_close_00;
		cgbvcm_nmain_anim.mAnimNum = eNMainAnim_close_00;
		
		cgbvcm_scene_main.mButtonNum = 4;
		cgbvcm_scene_nmain.mButtonNum = 2;
#endif	
		break;
	}

	if(g_sEmuShellBuffer.nBackupDataSize == 0)
	{
		cgbvcm_layout_message.mLayoutFileName = pCGBVCMLayoutName[eCGBVCMLayout_MessageNoSRAM];
		cgbvcm_layout_nmessage.mLayoutFileName = pCGBVCMLayoutName[eCGBVCMLayout_NMessageNoSRAM];
	}
	else
	{
		cgbvcm_layout_message.mLayoutFileName = pCGBVCMLayoutName[eCGBVCMLayout_Message];
		cgbvcm_layout_nmessage.mLayoutFileName = pCGBVCMLayoutName[eCGBVCMLayout_NMessage];
	}

	//get self name
	{
		nn::cfg::CTR::UserName username;
		nn::cfg::CTR::GetUserName(&username);
		int i;
		for(i=0;i<nn::cfg::CTR::CFG_USER_NAME_LENGTH;i++)
		{
			g_pTrlEmuDLPSelfNameBuf[i] = username.userName[i];
			if(username.userName[i] == 0)
				break;
		}
		g_pTrlEmuDLPSelfNameBuf[i] = 0;
	}
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_CHILD
	cgbvcm_bt_main_load.mEnable = 0;
	cgbvcm_bt_main_save.mEnable = 0;
	cgbvcm_bt_main_reset.mEnable = 0;
	cgbvcm_bt_nmain_reset.mEnable = 0;
#endif

}


///////////////////////////////////
//scene
void trlEmuMenuSceneInit(trlEmuMenuScene *pScene)
{
	pScene->mButtonIndexCur = pScene->mButtonIndexPre = pScene->mButtonIndexDecide = TRL_EMUMENU_BUTTON_NONE;
	pScene->mButtonTouchState = eMenuMenuTouchState_NoTouch;
}


s32 trlEmuMenuSceneMoveButton(trlEmuMenuScene *pScene, s32 newindex)
{
	CButtonSet2 *pButtonSet = pScene->pLayout->mpButtonSet;
	trlEmuMenuButtonAnim *pButtonAnim = pScene->mpButtonAnim;
	if(newindex != TRL_EMUMENU_BUTTON_NONE)
	{
		if(pScene->mpButtons[newindex]->mEnable == 0)
			return TRL_EMUMENU_SCENE_MOVEBUTTON_FAIL;
	}
	if(pScene->mButtonIndexCur != newindex && pScene->mButtonIndexCur != TRL_EMUMENU_BUTTON_NONE)
		pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocusOut);
	if(newindex != TRL_EMUMENU_BUTTON_NONE)
		pButtonSet->bindanim(pScene->mpButtons[newindex]->mpName, pButtonAnim->mAnimFocus);
	if(pScene->mButtonIndexCur != TRL_EMUMENU_BUTTON_NONE)
		pScene->mButtonIndexPre = pScene->mButtonIndexCur;
	pScene->mButtonIndexCur = newindex;
	return TRL_EMUMENU_SCENE_MOVEBUTTON_SUCCESS;
}


///////////////////////////////////
//state change
void trlEmuMenuStateToChange(s32 changeindex)
{
	g_vcmstate_state = eVCMState_Chnage;
	g_vcmstate_changeindex = changeindex;

	g_vcmstatechange_state = EVCMStateChangeState_Init;	
}
void trlEmuMenuStateToNormal()
{
	g_vcmstate_state = eVCMState_Normal;
	g_vcmstate_changeindex = VCM_STATE_CHANGE_NOCHANGE;	
}

void trlEmuMenuChangeState(s32 newstate)
{
	NN_LOG("trlEmuMenuChangeState %d->%d   0x%x\n", g_vcmstate, newstate, vcmmenu_state[newstate]);
	g_vcmstate = newstate;
	{
		trlEmuMenuState *pState = vcmmenu_state[newstate];
		switch(pState->mStateType)
		{
		case eEmuMenuStateType_WaitThread:
			g_vcmstate_thread_state = EVCMStateThreadState_Init;
			break;
		case eEmuMenuStateType_WaitAnim:
			{
				NN_LOG("WaitAnim Begin\n");
				trlEmuMenuStateToChange(VCM_STATE_CHANGE_DEFAULT);
				extern CEmuMenu g_hTrlEmuMenu;
				g_hTrlEmuMenu.RunState_Change();
			}
			break;
		case eEmuMenuStateType_JustGo:
			{
				trlEmuMenuStateToChange(VCM_STATE_CHANGE_DEFAULT);
				extern CEmuMenu g_hTrlEmuMenu;
				g_hTrlEmuMenu.RunState_Change();
			}
			break;
		case eEmuMenuStateType_Select:
			{
				if(pState->pSelectFunc == NULL)
					trlEmuMenuStateToChange(VCM_STATE_CHANGE_DEFAULT);
				else
					trlEmuMenuStateToChange(pState->pSelectFunc());
				extern CEmuMenu g_hTrlEmuMenu;
				g_hTrlEmuMenu.RunState_Change();
			}
		}
	}
}

void trlEmuMenuStateInit()
{
	for(int i=0;i<eEmuMenuStateNum;i++)
	{
		trlEmuMenuScene* pScene = vcmmenu_state[i]->mpScene;
		if(pScene != NULL)
		{
			trlEmuMenuSceneInit(pScene);
		}
	}
}


