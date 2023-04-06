/**
* @file trlEmuMenuData.h
* @author zhfang
* @date 2011.06.29
* @brief trlEmuMenu
*/
#pragma once
#include "trlEmuMenu.h"

typedef struct
{
	s32 mAnimNum;
	char **mpAnimFileNames;
}trlEmuMenuAnim;

typedef struct
{
	char *mLayoutFileName;
	trlEmuMenuAnim *mpAnim;
	CButtonSet2* mpButtonSet;
}trlEmuMenuLayout;

typedef struct
{
	wchar_t *mArcFileName;
	s32 mLayoutNum;
	trlEmuMenuLayout **mpLayout;
	CEmuMenuFile mArcFile;
}trlEmuMenuArc;

typedef struct
{
	s32 mArcNum;
	trlEmuMenuArc **mpArc;
}trlEmuMenuRes;

extern trlEmuMenuRes g_vcmres;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define TRL_MENU_SCENE_BUTTONNUM_MAX 8

typedef struct
{
	char *mpName;
	char *mpArea;
	s32	 mEnable;
}trlEmuMenuButton;


//#define TRL_MENU_SCENE_BUTTONANIM_NONE -1
typedef struct
{
	s32 mAnimFocus;
	s32 mAnimFocus01;
	s32 mAnimFocusOut;	
}trlEmuMenuButtonAnim;

enum EEmuMenuKeyActionType
{
	eEmuMenuKeyActionType_None = 0,
	eEmuMenuKeyActionType_Move,
	eEmuMenuKeyActionType_MoveToPre,
	eEmuMenuKeyActionType_Decide,
	eEmuMenuKeyActionType_DecideButton,
	eEmuMenuKeyActionType_StateChange,
	eEmuMenuKeyActionType_StateChangeWithSelect,
	eEmuMenuKeyActionType_CallBack
};
#define TRL_EMUMENU_SOUND_NOSOUND 0
typedef s32 (*trlEmuOneKeyActionFunc)();
typedef struct
{
	s32 mKeyCondition;
	s32 mActionType;
	union
	{
		s32 mMoveActionButton;
		s32 mStateChangeIndex;
		s32 mDecideButton;
		trlEmuOneKeyActionFunc mpFunc;
	};
	u32 mSoundIndex;
}trlEmuMenuOneKeyAction;

#define TRL_EMUMENU_BUTTON_NONE -1
#define TRL_EMUMENU_ONEKEYACTION_MAX 8
typedef struct
{
	s32 mCurButtonCondition;
	s32 mOneKeyActionNum;
	trlEmuMenuOneKeyAction mOneKeyActions[TRL_EMUMENU_ONEKEYACTION_MAX];
	trlEmuMenuOneKeyAction mDecideAction;
}trlEmuMenuKeyAction;

#define TRL_EMUMENU_STATEKEYACTION_MAX 8
typedef struct
{
	u32 mKeyActionNum;
	trlEmuMenuKeyAction mKeyActions[TRL_EMUMENU_STATEKEYACTION_MAX];
}trlEmuMenuStateKeyAction;

enum EEmuMenuTouchState
{
	eMenuMenuTouchState_NoTouch = 0,
	eMenuMenuTouchState_PressNoButton,
	eMenuMenuTouchState_PressButton,	
	eMenuMenuTouchState_MoveOutButton	
};
typedef struct 
{	
	s32 mButtonNum;
	trlEmuMenuButton* mpButtons[TRL_MENU_SCENE_BUTTONNUM_MAX];
	trlEmuMenuButtonAnim *mpButtonAnim;

	trlEmuMenuLayout *pLayout;

	trlEmuMenuStateKeyAction *pKeyAction;

	s32 mButtonIndexCur;
	s32 mButtonIndexPre;
	s32 mButtonIndexDecide;
	s32 mButtonTouchState;
}trlEmuMenuScene;

typedef struct
{
	char *mButtonName;
	s32	mAnimIndex;
}trlEmuMenuActionAnim;

enum EEmuMenuActionType
{
	eEmuMenuActionType_SetBtDisable,
	eEmuMenuActionType_SetBtEnable,
	eEmuMenuActionType_BeginAnim,	
	eEmuMenuActionType_BeginAnimNoRecursive,
	eEmuMenuActionType_BeginAnimLoop,
	eEmuMenuActionType_EndAnimLoop,
	eEmuMenuActionType_BeginAnimAll,
	eEmuMenuActionType_SetIndexCur,
	eEmuMenuActionType_NoneButtonIndex,
	eEmuMenuActionType_SetVisible,
	eEmuMenuActionType_SetUnVisible,
	eEmuMenuActionType_BeginAnimOnCurButton,
	eEmuMenuActionType_Playsound,
	eEmuMenuActionType_CallBack,
	eEmuMenuActionType_CallBackWithParam,
	eEmuMenuActionType_CallBackWait,
	eEmuMenuActionStartThread
};


#define TRL_EMUMENU_ACTION_ELEM_PER_SCENE_MAX  8
#define TRL_EMUMENU_ACTION_SCENE_PER_STEP_MAX  4
#define TRL_EMUMENU_ACTION_STEP_PER_ACTION_MAX 6
#define TRL_EMUMENU_ACTION_DRAWSCENE_PER_STEP_MAX 4

#define TRL_EMUMENU_ACTION_WAITFUNC_WAIT 0
#define TRL_EMUMENU_ACTION_WAITFUNC_DONE 1
typedef void (*trlEmuMenuActionFunc)();
typedef void (*trlEmuMenuActionFuncWithParam)(s32);
typedef s32 (*trlEmuMenuWaitFunc)();
typedef struct
{
	s32 mActionType;
	union
	{
		char* mButtonName;
		s32	  mFuncParam;
	};
	union
	{
		s32 mAnimIndex;
		s32 mSetValue;
		s32 mSoundIndex;
		trlEmuMenuActionFunc mpActionFunc;
		trlEmuMenuActionFuncWithParam mpActionFuncWithParam;
		trlEmuMenuWaitFunc	mpWaitFunc;
	};
}trlEmuMenuActionElem;
typedef struct
{
	trlEmuMenuScene *mpScene;
	s32 mActionNum;
	trlEmuMenuActionElem mActions[TRL_EMUMENU_ACTION_ELEM_PER_SCENE_MAX];
}trlEmuMenuActionScene;

typedef struct
{
	s32 mSceneNum;
	trlEmuMenuActionScene mActionScene[TRL_EMUMENU_ACTION_SCENE_PER_STEP_MAX];
	s32 mDrawSceneNum;
	trlEmuMenuScene *mpDrawScenes[TRL_EMUMENU_ACTION_DRAWSCENE_PER_STEP_MAX];
}trlEmuMenuActionStep;

typedef struct
{
	s32 mStepNum;
	trlEmuMenuActionStep mActionSteps[TRL_EMUMENU_ACTION_STEP_PER_ACTION_MAX];
}trlEmuMenuAction;


#define TRL_MENU_BGSCENE_PER_STATE_MAX 2
enum EEmuMenuStateType
{
	eEmuMenuStateType_WaitButton = 0,
	eEmuMenuStateType_WaitButtonWithProcCall,
	eEmuMenuStateType_WaitButtonWithProcSelect,
	eEmuMenuStateType_WaitThread,
	eEmuMenuStateType_WaitProc,	
	eEmuMenuStateType_WaitAnim,	
	eEmuMenuStateType_WaitInfi,
	eEmuMenuStateType_Select,
	eEmuMenuStateType_JustGo,
	eEmuMenuStateType_Wait
};

#define TRL_MENU_SCENE_IN_ACTION_MAX 4
typedef struct
{
	s32 mOriginState;
	s32 mNewState;	
	trlEmuMenuAction* pMenuAction;
	s32 mSceneNum;
	trlEmuMenuScene *mpScenes[TRL_MENU_SCENE_IN_ACTION_MAX];

}trlEmuMenuStateChange;


#define TRL_MENU_STATECHANGE_MAX TRL_MENU_SCENE_BUTTONNUM_MAX
typedef s32 (*trlEmuMenuStateProcFunc)();
typedef struct
{
	s32 mState;
	s32 mStateType;
	trlEmuMenuScene *mpScene;

	s32 mBGSceneNum;
	trlEmuMenuScene *mpBGScenes[TRL_MENU_BGSCENE_PER_STATE_MAX];
	
	union
	{
		trlEmuMenuStateProcFunc pStartThreadFunc;
		trlEmuMenuStateProcFunc pSelectFunc;
		trlEmuMenuStateProcFunc pProcFunc;
	};
	
	//if the state type is eEmuMenuStateType_WaitButton, then one button with one statechange
	//if the state type is eEmuMenuStateType_WaitThread, then thread Success with statechangs mpStateChanges[0], thread Fail with mpStateChanges[1], 
	//if the state type is eEmuMenuStateType_WaitAnim, then only one change...
	trlEmuMenuStateChange *mpStateChanges[TRL_MENU_STATECHANGE_MAX];
}trlEmuMenuState;


enum EVCMStateState
{
	eVCMState_Normal,
	eVCMState_Chnage
};

enum EVCMStateChangeState
{
	EVCMStateChangeState_Init,
	EVCMStateChangeState_StepInit,
	EVCMStateChangeState_StepRun,
	EVCMStateChangeState_StepEnd,
	EVCMStateChangeState_End
};
extern s32 g_vcmstatechange_state;
extern s32 g_vcmstate_state;
extern s32 g_vcmstate;
extern s32 g_vcmstate_go;
#define VCM_STATE_CHANGE_NOCHANGE  -1
#define VCM_STATE_CHANGE_DEFAULT 0
#define VCM_STATE_NO_FORCE_GO 0
#define VCM_STATE_FORCE_GO 1
extern s32 g_vcmstate_changeindex ;
enum EVCMStateThreadState
{
	EVCMStateThreadState_Init = 0,
	EVCMStateThreadState_Wait,
	EVCMStateThreadState_End
};
extern s32 g_vcmstate_thread_state;
extern s32 g_vcmchange_actionstep;
extern trlEmuMenuState* vcmmenu_state[];

enum EVCMStateNetMode
{
	eVCMStateNetMode_None = 0,
	eVCMStateNetMode_Net
};
extern s32 g_vcmstate_netmode;

extern s32 g_vcm_specialplayer;
