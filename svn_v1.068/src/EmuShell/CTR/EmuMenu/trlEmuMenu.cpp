/**
* @file trlEmuMenu.cpp
* @author zhfang
* @date 2010.03.19
* @brief trlEmuMenu
*/
#include "trlEmuMenu.h"
#include <nn/pl.h>
#include <nn/fs.h>
#include <nn/cx.h>
//#include <nw.h>
#include <nw/lyt.h>
#include <nw/font.h>

#include "../../../../files/VCM/SND/threeb.csid"
#include "../../trlEmuShellData.h"
#include "../../trlEmuShellStruct.h"
#include "../../trlEmuShellSuspend.h"
#include "../../trlEmuShellNetwork.h"
#include "../trlEmuShellDLP.h"

using namespace nn::pl;
using namespace nn::fs;
using namespace nn::cx;

#include "trlEmuMenuData.h"
#include "trlEmuMenuDataAnim.h"
#include "trlEmuMenuDataState.h"
#include "trlEmuMenuDataScene.h"
#include "trlEmuMenuDataFunc.h"
#include "trlEmuMenuDataCallBack.h"
#include "trlEmuMenuDataLayout.h"

const s32 SOUND_HEAP_SIZE = 1 * 1024 * 1024;

u32 CEmuMenu::SetNMode()
{
	NN_LOG("Set VCM To Normal\n");
	g_sEmuShellBuffer.nVCMMode = eVCMMode_Normal;	
	trlEmuShellDataUpdateResume();
	return 0;
}
u32 CEmuMenu::SetAMode()
{
	NN_LOG("Set VCM To Advance\n");
	g_sEmuShellBuffer.nVCMMode = eVCMMode_Advance;	
	trlEmuShellDataUpdateResume();
	return 0;
}

void CEmuMenu::Release()
{
	shareFont.RemoveResource();
	graphicsResource.Finalize();

	if(fileLayout.m_Buffer != NULL)
	{
		pDeviceMemoryAllocator->Free(fileLayout.Buffer());
		fileLayout.m_Buffer = NULL;
	}

	if(pFontDrawBuffer != NULL)
	{
		pDeviceMemoryAllocator->Free(pFontDrawBuffer);
		pFontDrawBuffer = NULL;
	}

	//Snd
	{
		m_Heap.Destroy();
		m_ArchivePlayer.Finalize();		
		m_DataManager.Finalize();		
		m_Archive.Close();
	}
}
void CEmuMenu::ReleaseSound()
{
	nw::snd::SoundSystem::Finalize();
	if(m_pMemoryForSoundSystem != NULL)
	{
		pDeviceMemoryAllocator->Free( m_pMemoryForSoundSystem );
		m_pMemoryForSoundSystem = NULL;
	}
}

void CEmuMenu::Release1()
{
	//Snd
	{	
		if(m_pMemoryForInfoBlock != NULL)
		{
			pDeviceMemoryAllocator->Free( m_pMemoryForInfoBlock );
			m_pMemoryForInfoBlock = NULL;
		}
		if(m_pMemoryForSoundDataManager != NULL)
		{
			pDeviceMemoryAllocator->Free( m_pMemoryForSoundDataManager );
			m_pMemoryForSoundDataManager = NULL;
		}
		if(m_pMemoryForSoundArchivePlayer != NULL)
		{
			pDeviceMemoryAllocator->Free( m_pMemoryForSoundArchivePlayer );
			m_pMemoryForSoundArchivePlayer = NULL;
		}
		if(m_pMemoryForSoundHeap != NULL)
		{
			pDeviceMemoryAllocator->Free( m_pMemoryForSoundHeap );
			m_pMemoryForSoundHeap = NULL;
		}
		if(m_pMemoryForStreamBuffer != NULL)
		{
			pDeviceMemoryAllocator->Free( m_pMemoryForStreamBuffer );
			m_pMemoryForStreamBuffer = NULL;
		}
	}
}

void CEmuMenu::Init(nw::os::IAllocator *pAlloctor, nw::os::IAllocator* pDeviceMemoryAllocator)
{
	this->pAlloctor = pAlloctor;
	this->pDeviceMemoryAllocator = pDeviceMemoryAllocator;
	nw::lyt::Initialize(pAlloctor, pDeviceMemoryAllocator);

	pRenderFunc = NULL;
	pSwapBufferFunc = NULL;
	pSaveFunc = NULL;
	pLoadFunc = NULL;
	pResetFunc = NULL;
	pResumeFunc = NULL;

	pFontDrawBuffer = NULL;
	mPad.Initialize();

	nPreviewWidth = 160;
	nPreviewHeight = 144;


	saveanimon = 1;
	loadanimon = 0;
	resetanimon = 0;

	bWaitIconEnable = 1;

	releaseAction = 0;

	graphicsResource.Initialized();

	LoadFade_To_FadeNone();

	bHaveNetError = 0;
	bHaveNetErrorInMenu = 0;

	g_nTrlNetworkClintNum = g_sEmuShellBuffer.funcConfigData("NES", "MultiPlayer", 2) - 1;
	if(g_nTrlNetworkClintNum > 1)
	{
		g_nTrlNetwork4PMsg = 1;
	}
	else
	{
		g_nTrlNetwork4PMsg = 0;
	}
}

void CEmuMenu::InitSound()
{
	nw::snd::SoundSystem::SoundSystemParam param;
	param.autoCreateSoundThread = false;
	size_t workMemSize = nw::snd::SoundSystem::GetRequiredMemSize( param );
	m_pMemoryForSoundSystem = pDeviceMemoryAllocator->Alloc( workMemSize, 4 );			
	nw::snd::SoundSystem::Initialize(
		param,
		reinterpret_cast<uptr>( m_pMemoryForSoundSystem ),
		workMemSize );
}

void CEmuMenu::OpenSoundFile(const char *pSoundFileName)
{
	if ( ! m_Archive.Open( pSoundFileName ) )
	{
		NN_LOG("cannot open bcsar(%s)\n", pSoundFileName );
		NW_ASSERTMSG( 0, "cannot open bcsar(%s)\n", pSoundFileName );
	}

	{
		size_t infoBlockSize = m_Archive.GetHeaderSize();
		m_pMemoryForInfoBlock = pDeviceMemoryAllocator->Alloc( infoBlockSize, 4 );
		if ( ! m_Archive.LoadHeader( m_pMemoryForInfoBlock, infoBlockSize ) )
		{
			NN_LOG("cannot load infoBlock(%s)", pSoundFileName );
			NW_ASSERTMSG( 0, "cannot load infoBlock(%s)", pSoundFileName );
		}
	}

	{
		size_t setupSize = m_DataManager.GetRequiredMemSize( &m_Archive );
		m_pMemoryForSoundDataManager = pDeviceMemoryAllocator->Alloc( setupSize, 4 );
		if(!m_DataManager.Initialize( &m_Archive, m_pMemoryForSoundDataManager, setupSize ))
		{
			NN_LOG("m_DataManager.Initialize bad\n");
		}
	}

	{
		size_t setupSize = m_ArchivePlayer.GetRequiredMemSize( &m_Archive );
		m_pMemoryForSoundArchivePlayer = pDeviceMemoryAllocator->Alloc( setupSize, 32 );
		size_t setupStrmBufferSize =
			m_ArchivePlayer.GetRequiredStreamBufferSize( &m_Archive );
		m_pMemoryForStreamBuffer = pDeviceMemoryAllocator->Alloc( setupStrmBufferSize, 32 );
		bool result = m_ArchivePlayer.Initialize(
			&m_Archive,
			&m_DataManager,
			m_pMemoryForSoundArchivePlayer, setupSize,
			m_pMemoryForStreamBuffer, setupStrmBufferSize );
		if(!result)
		{
			NN_LOG("m_ArchivePlayer.Initialize bad\n");
		}
		NW_ASSERT( result );
	}

	{
		m_pMemoryForSoundHeap = pDeviceMemoryAllocator->Alloc( SOUND_HEAP_SIZE, 4 );
		bool result = m_Heap.Create( m_pMemoryForSoundHeap, SOUND_HEAP_SIZE );
		NW_ASSERT( result );
	}

	for(int i=SE_CTR_COMMON_TOUCH;i<=SE_CTR_THREEB_BACKUP_EFFECT;i++)
	{
		if ( ! m_DataManager.LoadData( i, &m_Heap ) )
			NW_ASSERTMSG( false, "LoadData(0x%x) failed.", i);
	}	
}

void CEmuMenu::PlaySoundMenuOpen()
{
	playsound(SE_CTR_THREEB_MENU_START);
}

void CEmuMenu::playsound(int id)
{
	if(id == TRL_EMUMENU_SOUND_NOSOUND)
		return;
	m_Handle.Stop( 0 );
	nw::snd::SoundStartable::StartResult r = m_ArchivePlayer.StartSound( &m_Handle, id );
	if(!r.IsSuccess ())
	{
		NN_LOG("playsound 0x%x bad = %d\n", id, r.GetCode());
	}
}

void CEmuMenu::LoadShaderResource()
{
	glGetError();
	graphicsResource.StartSetup();
	const wchar_t* resourcePath = 0;
	for (int i = 0;
		(resourcePath = graphicsResource.GetResourcePath(i)) != NULL;
		++i)
	{
		CEmuMenuFile file;
		if (!file.Read(resourcePath, *pAlloctor))
		{
			NW_FATAL_ERROR("can not read lyt resource file.");
		}
		graphicsResource.SetResource(i, file.Buffer(), file.Size());
	}
	graphicsResource.FinishSetup();
	drawInfo.SetGraphicsResource(&graphicsResource);

	drawer.Initialize(graphicsResource);
	nngxUpdateState(NN_GX_STATE_ALL);
}


void CEmuMenu::ReleaseVCMRes()
{
	for(int i=0;i<g_vcmres.mArcNum;i++)
	{
		trlEmuMenuArc *pArc = g_vcmres.mpArc[i];
		for(int j=0;j<pArc->mLayoutNum;j++)
		{
			trlEmuMenuLayout *pLayout = pArc->mpLayout[j];
			if(pLayout->mpButtonSet != NULL)
			{
				delete pLayout->mpButtonSet;
				pLayout->mpButtonSet = NULL;
			}
		}
		if(pArc->mArcFile.m_Buffer != NULL)
		{
			pDeviceMemoryAllocator->Free(pArc->mArcFile.Buffer());
			pArc->mArcFile.m_Buffer = NULL;
		}
	}
}
#if TRL_HOMENIX_UPSCREEN
void CEmuMenu::DrawHomeNix()
{
	if(g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_Open_UP || g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_Anim_UP)
	{
		glFlush();
		glGetError();
		
		glViewport(0, (nn::gx::DISPLAY0_HEIGHT - nn::gx::DISPLAY1_HEIGHT)/2, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT);
		
		drawer.DrawBegin(drawInfo);
		mpButtonSetHomeNix->draw();	
		drawer.DrawEnd(drawInfo);
		nngxUpdateState(NN_GX_STATE_ALL);
		glViewport(0, 0, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
	}
}
#endif

void CEmuMenu::DrawVCM()
{
	glGetError();
	glBindFramebuffer(GL_FRAMEBUFFER, nFrameBufObj1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT);

	trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];
	CButtonSet2 *pButtonSet = pState->mpScene->pLayout->mpButtonSet;
	pButtonSet->InitGX();
	pButtonSet->SetupCamera();
	drawer.DrawBegin(drawInfo);

	//NN_LOG("Draw g_vcmstate_state = %d  g_vcmstate = %d\n", g_vcmstate_state, g_vcmstate);

	switch(g_vcmstate_state)
	{
	case eVCMState_Normal:
		{			
			for(int i=0;i<pState->mBGSceneNum;i++)
			{
				if(pState->mpBGScenes[i]->pLayout->mpButtonSet != NULL)
					pState->mpBGScenes[i]->pLayout->mpButtonSet->draw();
			}
			pState->mpScene->pLayout->mpButtonSet->draw();
			
		}
		break;
	case eVCMState_Chnage:
		{			
			if(g_vcmstate_changeindex != VCM_STATE_CHANGE_NOCHANGE)
			{			
				trlEmuMenuStateChange *pChange = pState->mpStateChanges[g_vcmstate_changeindex];
				if(pChange != NULL && pChange->pMenuAction != NULL)
				{
					trlEmuMenuActionStep *pActionStep = &(pChange->pMenuAction->mActionSteps[g_vcmchange_actionstep]);
					if(pActionStep != NULL)
					{
						for(int i=0;i<pActionStep->mDrawSceneNum;i++)
						{
							if(pActionStep->mpDrawScenes[i]->pLayout->mpButtonSet != NULL)
								pActionStep->mpDrawScenes[i]->pLayout->mpButtonSet->draw();
						}
					}
				}
			}
		}
		break;
	}
	
	if(g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_Open || g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_Anim)
	{		
		mpButtonSetHomeNix->draw();
	}

	
	drawer.DrawEnd(drawInfo);
	nngxUpdateState(NN_GX_STATE_ALL);
}

void CEmuMenu::RunState_Normal_WaitButton()
{
	trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];
	trlEmuMenuScene *pScene = pState->mpScene;
	CButtonSet2 *pButtonSet = pScene->pLayout->mpButtonSet;
	trlEmuMenuButtonAnim *pButtonAnim = pScene->mpButtonAnim;
	
	//wait anim to end
	if(!pButtonSet->animisend(pButtonAnim->mAnimFocus))
		return;
	if(!pButtonSet->animisend(pButtonAnim->mAnimFocus01))
		return;
	if(!pButtonSet->animisend(pButtonAnim->mAnimFocusOut))
		return;

	s32 touchselect = TRL_EMUMENU_BUTTON_NONE;
	s32 decideselect = TRL_EMUMENU_BUTTON_NONE;

	//button
	if(pScene->mButtonIndexDecide != TRL_EMUMENU_BUTTON_NONE)
	{
		NN_LOG("pScene->mButtonIndexDecide != TRL_EMUMENU_BUTTON_NONE %d\n", pScene->mButtonIndexDecide);
		decideselect = pScene->mButtonIndexDecide;
		pScene->mButtonIndexDecide = TRL_EMUMENU_BUTTON_NONE;
	}
	else
	{
		if(mPad.GetTouch() == 0 && mPad.GetTouchTrigger() == 0)
		{
			if(pScene->mButtonTouchState == eMenuMenuTouchState_PressButton)
			{
				NN_LOG("pScene->mButtonTouchState == eMenuMenuTouchState_PressButton %d\n", pScene->mButtonIndexDecide);
				decideselect = pScene->mButtonIndexCur;
				pScene->mButtonTouchState = eMenuMenuTouchState_NoTouch;
				if(decideselect != TRL_EMUMENU_BUTTON_NONE)
				{
					if(pScene->mpButtons[decideselect]->mEnable == 0)
					{
						pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocusOut);
						pScene->mButtonIndexCur = TRL_EMUMENU_BUTTON_NONE;
						decideselect = TRL_EMUMENU_BUTTON_NONE;
					}
				}
			}
			else if(pScene->mButtonTouchState == eMenuMenuTouchState_MoveOutButton)
			{
				pScene->mButtonIndexCur = TRL_EMUMENU_BUTTON_NONE;
				pScene->mButtonTouchState = eMenuMenuTouchState_NoTouch;
			}
			else
			{
				pScene->mButtonTouchState = eMenuMenuTouchState_NoTouch;
				//NN_LOG("touchselect = %d  pScene->mButtonIndexCur = %d\n", touchselect, pScene->mButtonIndexCur);
				//NN_LOG("mPad.GetButton() = 0x%x\n", mPad.GetButton());

				trlEmuMenuStateKeyAction *pStateKeyAction = pScene->pKeyAction;		
				for(int i=0;i<pStateKeyAction->mKeyActionNum;i++)
				{
					trlEmuMenuKeyAction *pKeyAction = &(pStateKeyAction->mKeyActions[i]);
					if(pKeyAction->mCurButtonCondition == pScene->mButtonIndexCur)
					{
						u32 holdbutton = mPad.GetButton()|BUTTON_HOLD;
						u32 trigbutton = mPad.GetTrigger();
						for(int j=0;j<pKeyAction->mOneKeyActionNum;j++)
						{
							trlEmuMenuOneKeyAction *pOneKeyAction = &(pKeyAction->mOneKeyActions[j]);
							if((pOneKeyAction->mKeyCondition&BUTTON_HOLD) != 0  && (pOneKeyAction->mKeyCondition&holdbutton) == pOneKeyAction->mKeyCondition)
							{
								mPad.Lock(pOneKeyAction->mKeyCondition &(~BUTTON_HOLD));
							}
							else if( trigbutton != 0 && (pOneKeyAction->mKeyCondition & trigbutton) == pOneKeyAction->mKeyCondition)
							{
								s8 nBeOtherKey = 0;
								for(int k=0;k<pKeyAction->mOneKeyActionNum;k++)
								{
									if(k == j)
										continue;
									trlEmuMenuOneKeyAction *pOtherOneKeyAction = &(pKeyAction->mOneKeyActions[k]);
									if ((pOneKeyAction->mKeyCondition & pOtherOneKeyAction->mKeyCondition) == pOneKeyAction->mKeyCondition)
									{
										if((pOtherOneKeyAction->mKeyCondition & holdbutton) != (pOneKeyAction->mKeyCondition|BUTTON_HOLD))
											nBeOtherKey = 1;
									}
								}
								if(nBeOtherKey == 1)
									continue;
								mPad.Lock(pOneKeyAction->mKeyCondition);
							}
							else
								continue;
							
							switch(pOneKeyAction->mActionType)
							{
							case eEmuMenuKeyActionType_Move:
								if(trlEmuMenuSceneMoveButton(pScene, pOneKeyAction->mMoveActionButton) == TRL_EMUMENU_SCENE_MOVEBUTTON_SUCCESS)
									playsound(pOneKeyAction->mSoundIndex);
								break;
							case eEmuMenuKeyActionType_MoveToPre:
								playsound(pOneKeyAction->mSoundIndex);
								trlEmuMenuSceneMoveButton(pScene, pScene->mButtonIndexPre);
								break;
							case eEmuMenuKeyActionType_Decide:
								playsound(pOneKeyAction->mSoundIndex);
								NN_LOG("eEmuMenuKeyActionType_Decide  %d\n", pScene->mButtonIndexCur);
								decideselect = pScene->mButtonIndexCur;
								break;
							case eEmuMenuKeyActionType_DecideButton:
								playsound(pOneKeyAction->mSoundIndex);
								if(pOneKeyAction->mDecideButton != TRL_EMUMENU_BUTTON_NONE)
								{
									if(pScene->mpButtons[pOneKeyAction->mDecideButton]->mEnable == 1)
									{
										if(pScene->mButtonIndexCur != TRL_EMUMENU_BUTTON_NONE)
											pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocusOut);
										pScene->mButtonIndexDecide = pScene->mButtonIndexCur = pOneKeyAction->mDecideButton;
										pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocus);
									}
								}
								break;
							case eEmuMenuKeyActionType_StateChange:
								playsound(pOneKeyAction->mSoundIndex);
								trlEmuMenuStateToChange(pOneKeyAction->mStateChangeIndex);
								break;
							case eEmuMenuKeyActionType_StateChangeWithSelect:
								NN_LOG("eEmuMenuKeyActionType_StateChangeWithSelect\n");
								playsound(pOneKeyAction->mSoundIndex);
								trlEmuMenuStateToChange(pOneKeyAction->mpFunc());
								break;
							case eEmuMenuKeyActionType_CallBack:
								if(pOneKeyAction->mpFunc != NULL)
									pOneKeyAction->mpFunc();
							}
							break;
						}
						break;
					}			
				}
			}
		}//touch ...	
		else if(mPad.GetTouchTrigger() == 1 || mPad.GetTouchTrigger() == 2 || mPad.GetTouch() == 1)
		{
			s16 x = mPad.GetTouchX() - 160;
			s16 y = (120 -mPad.GetTouchY());
			for(int i=0;i<pScene->mButtonNum;i++)
			{
				if(pButtonSet->inPaneArea(pScene->mpButtons[i]->mpArea, x, y) == 1 && pScene->mpButtons[i]->mEnable == 1)
				{
					touchselect = i;
					break;
				}
			}	
			//NN_LOG("touchselect = %d  pScene->mButtonIndexCur = %d\n", touchselect, pScene->mButtonIndexCur);
			if(mPad.GetTouchTrigger() == 1)
			{
				NN_LOG("press touchselect = %d  pScene->mButtonIndexCur = %d\n", touchselect, pScene->mButtonIndexCur);
				if(touchselect != TRL_EMUMENU_BUTTON_NONE)
				{
					pScene->mButtonTouchState = eMenuMenuTouchState_PressButton;
					if(touchselect != pScene->mButtonIndexCur)
					{
						if(pScene->mButtonIndexCur != TRL_EMUMENU_BUTTON_NONE)
							pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocusOut);				
						pButtonSet->bindanim(pScene->mpButtons[touchselect]->mpName, pButtonAnim->mAnimFocus);
						if(pScene->mButtonIndexCur != TRL_EMUMENU_BUTTON_NONE)
							pScene->mButtonIndexPre = pScene->mButtonIndexCur;
					}
					else
						pButtonSet->bindanim(pScene->mpButtons[touchselect]->mpName, pButtonAnim->mAnimFocus01);					
					pScene->mButtonIndexCur = touchselect;

					playsound(SE_CTR_COMMON_TOUCH);				
				}
				else
				{
					pScene->mButtonTouchState = eMenuMenuTouchState_PressNoButton;
				}
			}
			else if(mPad.GetTouchTrigger() == 2)
			{
				NN_LOG("release touchselect = %d  pScene->mButtonIndexCur = %d\n", touchselect, pScene->mButtonIndexCur);			
				if(pScene->mButtonTouchState == eMenuMenuTouchState_PressButton)
				{
					if(touchselect == pScene->mButtonIndexCur)
					{						
						decideselect = touchselect;
					}
					else
					{
						playsound(SE_CTR_COMMON_TOUCHOUT);
						pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocusOut);
						pScene->mButtonIndexCur = TRL_EMUMENU_BUTTON_NONE;
					}
				}			
				else if(pScene->mButtonTouchState == eMenuMenuTouchState_MoveOutButton)
				{
					pScene->mButtonIndexCur = TRL_EMUMENU_BUTTON_NONE;
				}
				pScene->mButtonTouchState = eMenuMenuTouchState_NoTouch;
			}
			else if(mPad.GetTouch() == 1)
			{
				NN_LOG("move touchselect = %d  pScene->mButtonIndexCur = %d\n", touchselect, pScene->mButtonIndexCur);
				if(pScene->mButtonTouchState == eMenuMenuTouchState_NoTouch)
				{
					pScene->mButtonTouchState = eMenuMenuTouchState_PressNoButton;
				}
				else if(pScene->mButtonTouchState != eMenuMenuTouchState_PressNoButton)
				{
					if(touchselect != pScene->mButtonIndexCur)
					{
						if(pScene->mButtonTouchState == eMenuMenuTouchState_PressButton)
						{
							playsound(SE_CTR_COMMON_TOUCHOUT);
							pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocusOut);
							pScene->mButtonTouchState = eMenuMenuTouchState_MoveOutButton;
							NN_LOG("MOVE out\n");
						}
					}
					else
					{
						if(pScene->mButtonTouchState == eMenuMenuTouchState_MoveOutButton)
						{
							playsound(SE_CTR_COMMON_TOUCHIN);
							pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pButtonAnim->mAnimFocus);
							pScene->mButtonTouchState = eMenuMenuTouchState_PressButton;
							NN_LOG("MOVE in\n");
						}
					}
				}			
			}
		}
	}

	if(decideselect != TRL_EMUMENU_BUTTON_NONE)
	{
		NN_LOG("decideselect = %d\n", decideselect);
		trlEmuMenuStateKeyAction *pStateKeyAction = pScene->pKeyAction;
		for(int i=0;i<pStateKeyAction->mKeyActionNum;i++)
		{
			trlEmuMenuKeyAction *pKeyAction = &(pStateKeyAction->mKeyActions[i]);
			if(pKeyAction->mCurButtonCondition == decideselect)
			{
				trlEmuMenuOneKeyAction *pDecideAction = &(pKeyAction->mDecideAction);
				playsound(pDecideAction->mSoundIndex);
				switch(pDecideAction->mActionType)
				{
				case eEmuMenuKeyActionType_Move:
					trlEmuMenuSceneMoveButton(pScene, pDecideAction->mMoveActionButton);
					break;
				case eEmuMenuKeyActionType_MoveToPre:
					trlEmuMenuSceneMoveButton(pScene, pScene->mButtonIndexPre);
				case eEmuMenuKeyActionType_StateChange:
					trlEmuMenuStateToChange(pDecideAction->mStateChangeIndex);
					break;
				case eEmuMenuKeyActionType_StateChangeWithSelect:
					NN_LOG("eEmuMenuKeyActionType_StateChangeWithSelect\n");					
					trlEmuMenuStateToChange(pDecideAction->mpFunc());
					break;
				}
				break;
			}
		}
	}
}

void CEmuMenu::RunState_Normal()
{
	trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];
	switch(pState->mStateType)
	{
	case eEmuMenuStateType_WaitButton:
		RunState_Normal_WaitButton();
		break;
	case eEmuMenuStateType_WaitButtonWithProcCall:
		if(pState->pProcFunc != NULL)
			pState->pProcFunc();
		RunState_Normal_WaitButton();
		break;
	case eEmuMenuStateType_WaitButtonWithProcSelect:
		{
			s32 r = eEmuMenuCallBackState_Wait;
			RunState_Normal_WaitButton();
			if(g_vcmstate_state == eVCMState_Normal)
			{
				if(pState->pProcFunc != NULL)
					r = pState->pProcFunc();
				if(r != eEmuMenuCallBackState_Wait)
					trlEmuMenuStateToChange(r);
			}
		}
		break;	
	case eEmuMenuStateType_WaitProc:
		{
			s32 r = pState->pProcFunc();
			if(r != eEmuMenuCallBackState_Wait)
			{
				trlEmuMenuStateToChange(r);
			}
		}
		break;
	case eEmuMenuStateType_WaitThread:
		{
			if(pState->pStartThreadFunc == NULL)
			{
				static int ct = 0;
				ct++;
				if(ct > 120)
				{
					ct = 0;
					trlEmuMenuStateToChange(0);
				}
			}
			else
			{
				switch(g_vcmstate_thread_state)
				{
				case EVCMStateThreadState_Init:
					pState->pStartThreadFunc();
					g_vcmstate_thread_state = EVCMStateThreadState_Wait;
					break;
				case EVCMStateThreadState_Wait:
					if(trlEmuMenuCallBack_EndProc() == TRL_EMUMENU_CALLBACK_END)
					{
						g_vcmstate_thread_state = EVCMStateThreadState_End;
					}
					break;
				case EVCMStateThreadState_End:
					trlEmuMenuStateToChange(0);
					g_vcmstate_thread_state = EVCMStateThreadState_Init;
					break;
				}
			}
		}
		break;
	case eEmuMenuStateType_WaitAnim:
		{
			NN_LOG("WaitAnim Begin\n");
			trlEmuMenuStateToChange(VCM_STATE_CHANGE_DEFAULT);
			RunState_Change();
		}
		break;
	case eEmuMenuStateType_WaitInfi:
		break;
	case eEmuMenuStateType_Wait:
		break;
	case eEmuMenuStateType_Select:		
		break;
	}
}

void CEmuMenu::RunState_Change()
{
	if(g_vcmstate_changeindex == VCM_STATE_CHANGE_NOCHANGE)
	{
		trlEmuMenuStateToNormal();
		return;
	}
	//NN_LOG("RunState_Change g_vcmstate = %d g_vcmstate_changeindex = %d g_vcmstatechange_state = %d g_vcmchange_actionstep = %d\n", g_vcmstate, g_vcmstate_changeindex, g_vcmstatechange_state, g_vcmchange_actionstep);

	trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];
	trlEmuMenuStateChange *pChange = pState->mpStateChanges[g_vcmstate_changeindex];

	if(pChange == NULL)
	{
		NN_LOG("there is a NULL change g_vcmstate = %d g_vcmstate_changeindex = %d\n", g_vcmstate, g_vcmstate_changeindex);
		trlEmuMenuStateToNormal();
		return;
	}	
	trlEmuMenuAction* pAction = pChange->pMenuAction;
	trlEmuMenuActionStep *pActionStep;

	if(pAction == NULL)
		g_vcmstatechange_state = EVCMStateChangeState_End;

	while(1)
	{
		switch(g_vcmstatechange_state)
		{
		case EVCMStateChangeState_Init:
			{
				g_vcmchange_actionstep = 0;
				g_vcmstatechange_state = EVCMStateChangeState_StepInit;
			}			
		case EVCMStateChangeState_StepInit:
			{
				//NN_LOG("RunState_Change g_vcmstate = %d g_vcmstate_changeindex = %d g_vcmchange_actionstep = %d\n", g_vcmstate, g_vcmstate_changeindex, g_vcmchange_actionstep);
				pActionStep = &(pAction->mActionSteps[g_vcmchange_actionstep]);
				for(int i=0;i<pActionStep->mSceneNum;i++)
				{
					trlEmuMenuActionScene *pActionScene = &(pActionStep->mActionScene[i]);
					trlEmuMenuScene *pScene = pActionScene->mpScene;
					CButtonSet2 *pButtonSet = pScene->pLayout->mpButtonSet;
					for(int j=0;j<pActionScene->mActionNum;j++)
					{
						trlEmuMenuActionElem *pActionElem = &(pActionScene->mActions[j]);
						switch(pActionElem->mActionType)
						{
						case eEmuMenuActionType_SetVisible:
							if(pButtonSet != NULL)
								if(pButtonSet->search(pActionElem->mButtonName) != NULL)
									pButtonSet->search(pActionElem->mButtonName)->SetVisible(true);
							break;
						case eEmuMenuActionType_SetUnVisible:
							if(pButtonSet != NULL)
								if(pButtonSet->search(pActionElem->mButtonName) != NULL)
									pButtonSet->search(pActionElem->mButtonName)->SetVisible(false);
							break;
						case eEmuMenuActionType_BeginAnim:
							if(pButtonSet != NULL)
								pButtonSet->bindanim(pActionElem->mButtonName, pActionElem->mAnimIndex);
							break;
						case eEmuMenuActionType_SetBtDisable:
							if(pActionElem->mAnimIndex != 0)
							{
								trlEmuMenuButton *pButton = (trlEmuMenuButton*)pActionElem->mAnimIndex;
								pButton->mEnable = 0;
							}
							break;
						case eEmuMenuActionType_SetBtEnable:
							if(pActionElem->mAnimIndex != 0)
							{
								trlEmuMenuButton *pButton = (trlEmuMenuButton*)pActionElem->mAnimIndex;
								pButton->mEnable = 1;
							}
							break;
						case eEmuMenuActionType_BeginAnimNoRecursive:
							if(pButtonSet != NULL)
								pButtonSet->bindanim(pActionElem->mButtonName, pActionElem->mAnimIndex, 0, 0);
							break;
						case eEmuMenuActionType_BeginAnimLoop:
							if(pButtonSet != NULL)
								pButtonSet->bindanim(pActionElem->mButtonName, pActionElem->mAnimIndex, 1);
							break;
						case eEmuMenuActionType_EndAnimLoop:
							if(pButtonSet != NULL)
								pButtonSet->unbindanim(pActionElem->mButtonName, pActionElem->mAnimIndex);
							break;
						case eEmuMenuActionType_BeginAnimAll:
							if(pButtonSet != NULL)
								pButtonSet->bindanimall(pActionElem->mAnimIndex);
							break;
						case eEmuMenuActionType_SetIndexCur:
							pScene->mButtonIndexCur = pScene->mButtonIndexPre = pActionElem->mSetValue;
							pScene->mButtonTouchState = eMenuMenuTouchState_NoTouch;
							break;
						case eEmuMenuActionType_NoneButtonIndex:
							pScene->mButtonIndexDecide = pScene->mButtonIndexCur = pScene->mButtonIndexPre = TRL_EMUMENU_BUTTON_NONE;
							break;
						case eEmuMenuActionType_BeginAnimOnCurButton:
							{
								//NN_LOG("eEmuMenuActionType_BeginAnimOnCurButton  %s\n",pScene->mpButtons[pScene->mButtonIndexCur]->mpName);
								if(pScene->mButtonIndexCur != TRL_EMUMENU_BUTTON_NONE)
									pButtonSet->bindanim(pScene->mpButtons[pScene->mButtonIndexCur]->mpName, pActionElem->mAnimIndex);
							}
							break;
						case eEmuMenuActionType_CallBack:
							if(pActionElem->mpActionFunc != NULL)
								pActionElem->mpActionFunc();
							break;
						case eEmuMenuActionType_CallBackWithParam:
							if(pActionElem->mpActionFuncWithParam != NULL)
								pActionElem->mpActionFuncWithParam(pActionElem->mFuncParam);
							break;
						case eEmuMenuActionType_Playsound:
							playsound(pActionElem->mSoundIndex);
							break;
						case eEmuMenuActionStartThread:
							break;
						}
					}
				}			
			}
			g_vcmstatechange_state = EVCMStateChangeState_StepRun;
			break;
		case EVCMStateChangeState_StepRun:
			{
				s32 endflag = 1;
				pActionStep = &(pAction->mActionSteps[g_vcmchange_actionstep]);
				for(int i=0;i<pActionStep->mSceneNum;i++)
				{
					//NN_LOG("EVCMStateChangeState_StepRun i = %d\n", i);
					trlEmuMenuActionScene *pActionScene = &(pActionStep->mActionScene[i]);
					trlEmuMenuScene *pScene = pActionScene->mpScene;
					CButtonSet2 *pButtonSet = pScene->pLayout->mpButtonSet;
					for(int j=0;j<pActionScene->mActionNum;j++)
					{
						//NN_LOG("EVCMStateChangeState_StepRun j = %d\n", j);
						trlEmuMenuActionElem *pActionElem = &(pActionScene->mActions[j]);
						switch(pActionElem->mActionType)
						{
						case eEmuMenuActionType_BeginAnim:
						case eEmuMenuActionType_BeginAnimAll:
						case eEmuMenuActionType_BeginAnimOnCurButton:
						case eEmuMenuActionType_BeginAnimNoRecursive:
							if(pButtonSet != NULL)
								if(!pButtonSet->animisend(pActionElem->mAnimIndex))
								{
									//NN_LOG("EVCMStateChangeState_StepRun step = %d, scene = %d, action = %d  not end\n", g_vcmchange_actionstep, i, j);
									endflag = 0;
								}
							break;
						case eEmuMenuActionType_CallBackWait:
							if(pActionElem->mpWaitFunc != NULL)
							{
								if(pActionElem->mpWaitFunc() ==TRL_EMUMENU_ACTION_WAITFUNC_WAIT)
									endflag = 0;
							}
						case eEmuMenuActionStartThread:
							break;
						}
						//NN_LOG("EVCMStateChangeState_StepRun j = %d end\n", j);
						if(endflag == 0)
							break;
					}
					//NN_LOG("EVCMStateChangeState_StepRun i = %d end\n", i);
					if(endflag == 0)
						break;
				}
				if(endflag == 1)
				{
					g_vcmstatechange_state = EVCMStateChangeState_StepEnd;
				}
				else
					break;
			}
			break;
		case EVCMStateChangeState_StepEnd:
			{
				g_vcmchange_actionstep++;
				if(g_vcmchange_actionstep >= pAction->mStepNum)
				{
					g_vcmstatechange_state = EVCMStateChangeState_End;
				}
				else
				{
					g_vcmstatechange_state = EVCMStateChangeState_StepInit;
					break;
				}
			}			
		case EVCMStateChangeState_End:
			{
				g_vcmchange_actionstep = 0;			
				trlEmuMenuStateToNormal();
				trlEmuMenuChangeState(pChange->mNewState);
			}
			break;
		}	
		if(g_vcmstatechange_state == EVCMStateChangeState_End || 
			g_vcmstatechange_state == EVCMStateChangeState_StepRun)
			break;
	}
}


void CEmuMenu::UpdateVCM()
{
	switch(g_vcmstate_state)
	{
	case eVCMState_Normal:
		{
			trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];
			pState->mpScene->pLayout->mpButtonSet->update();
			for(int i=0;i<pState->mBGSceneNum;i++)
			{
				if(pState->mpBGScenes[i]->pLayout->mpButtonSet != NULL)
					pState->mpBGScenes[i]->pLayout->mpButtonSet->update();
			}
		}
		break;
	case eVCMState_Chnage:
		{
			//zhfang test			
			if(g_vcmstate_changeindex == VCM_STATE_CHANGE_NOCHANGE)			
				return;
			trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];			
			trlEmuMenuStateChange *pChange = pState->mpStateChanges[g_vcmstate_changeindex];
			if(pChange == NULL)
				return;
			if(pChange->pMenuAction == NULL)
				return;
			trlEmuMenuActionStep *pActionStep = &(pChange->pMenuAction->mActionSteps[g_vcmchange_actionstep]);
			if(pActionStep == NULL)
				return;
			for(int i=0;i<pActionStep->mDrawSceneNum;i++)
			{
				if(pActionStep->mpDrawScenes[i]->pLayout->mpButtonSet != NULL)
					pActionStep->mpDrawScenes[i]->pLayout->mpButtonSet->update();
			}
		}
		break;
	}
}
void CEmuMenu::VCMForceMenuInit()
{
	trlEmuMenuChangeState(eEmuMenuState_Init);
}
void CEmuMenu::VCMForceError()
{
	trlEmuMenuChangeState(eEmuMenuState_Error_Begin);	
}
void CEmuMenu::VCMForceGo()
{
	g_vcmstate_go = VCM_STATE_FORCE_GO;
	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
	{
		if(g_vcmstate == eEmuMenuState_StandBy)
			g_vcmstate = eEmuMenuState_DLPStandBy;
	}
}


void CEmuMenu::UpdateHomeNix()
{
	mpButtonSetHomeNix->update();
	switch(g_bTrlEmuMenuHomeNixState)
	{
	case eTrlEmuShell_HomeNixState_None:		
		break;
	case eTrlEmuShell_HomeNixState_Open:		
		if(mpButtonSetHomeNix != NULL)
			mpButtonSetHomeNix->bindanim("HomeNixSign_00", eHomeNixAnim_InOut);		
		g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_Anim;
		break;
	case eTrlEmuShell_HomeNixState_Anim:		
		if(mpButtonSetHomeNix->animisend(eHomeNixAnim_InOut))
		{
			g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_None;			
		}
		break;
	case eTrlEmuShell_HomeNixState_Open_UP:		
		if(mpButtonSetHomeNix != NULL)
			mpButtonSetHomeNix->bindanim("HomeNixSign_00", eHomeNixAnim_InOut);		
		g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_Anim_UP;
		break;
	case eTrlEmuShell_HomeNixState_Anim_UP:		
		if(mpButtonSetHomeNix->animisend(eHomeNixAnim_InOut))
		{
			g_bTrlEmuMenuHomeNixState = eTrlEmuShell_HomeNixState_None;			
		}
		break;
	}
}

void CEmuMenu::UpdatePad()
{
	mPad.Read();
}

s32 CEmuMenu::RunVCM()
{
	//NN_LOG("RunVCM g_vcmstate = %d g_vcmstate_state = %d\n", g_vcmstate, g_vcmstate_state);

	//if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_ERROR)// ||(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_ERROR))
	//{
	//	if(bHaveNetError == 0)
	//	{
	//		NN_LOG("Net Error In Menu g_sEmuShellBuffer.nNetworkState = %d\n", g_sEmuShellBuffer.nNetworkState);			
	//		bHaveNetErrorInMenu = 1;
	//		bHaveNetError = 1;
	//		trlEmuMenuChangeState(eEmuMenuState_DLPError);
	//	}
	//}

	trlEmuMenuState *pState = vcmmenu_state[g_vcmstate];
	UpdatePad();

	switch(g_vcmstate_state)
	{
	case eVCMState_Normal:
		if(g_vcmstate_go == VCM_STATE_FORCE_GO)
		{
			g_vcmstate_go = VCM_STATE_NO_FORCE_GO;
			if(pState->pSelectFunc != NULL)
				trlEmuMenuStateToChange(pState->pSelectFunc());
			else			
				trlEmuMenuStateToChange(VCM_STATE_CHANGE_DEFAULT);
			RunState_Change();
		}
		else
		{
			RunState_Normal();			
		}
		break;
	case eVCMState_Chnage:
		RunState_Change();
		break;
	}
	UpdateVCM();

	
	UpdateHomeNix();

	updateLoadFade();

	DrawVCM();
	m_ArchivePlayer.Update();
	
	//NN_LOG("RunVCM g_vcmstate_state = %d  pState->mStateType = %d\n", g_vcmstate_state, pState->mStateType);	
	switch(g_vcmstate_state)
	{
	case eVCMState_Normal:
		{
			pState = vcmmenu_state[g_vcmstate];
			switch(pState->mStateType)
			{
			case eEmuMenuStateType_Wait:
				{
					if(g_bTrlEmuMenuHomeNixState == eTrlEmuShell_HomeNixState_None)
					{
						return eRunVCMReslut_End;
					}
					else
						return eRunVCMReslut_Continue;
				}
			default:
				return eRunVCMReslut_Continue;
			}
		}		
	case eVCMState_Chnage:
		return eRunVCMReslut_Continue;
	default:
		return eRunVCMReslut_Continue;
	}
}


void CEmuMenu::OpenVCMRes()
{
	trlEmuMenuInitRes();
	{
		nn::Result r;
		s32 nSize;
		r = InitializeSharedFont();

		void *pPLFont = GetSharedFontAddress();
		if(!shareFont.SetResource(pPLFont))
		{
			NN_LOG("font fail\n");
		}
		nSize = nw::font::ResFont::GetDrawBufferSize(pPLFont);
		NN_LOG("DrawBuffer Size = %d\n", nSize);
		pFontDrawBuffer = pDeviceMemoryAllocator->Alloc(nSize);
		shareFont.SetDrawBuffer(pFontDrawBuffer);
	}
	glGetError();

	for(int i=0;i<g_vcmres.mArcNum;i++)
	{
		trlEmuMenuArc *pArc = g_vcmres.mpArc[i];		
		if(!pArc->mArcFile.Read(pArc->mArcFileName, *pDeviceMemoryAllocator))
		{
			NW_FATAL_ERROR("can not open layout archive.\n");
		}
		for(int j=0;j<pArc->mLayoutNum;j++)
		{
			trlEmuMenuLayout *pLayout = pArc->mpLayout[j];
			pLayout->mpButtonSet = new CButtonSet2(pArc->mArcFile.Buffer(), pLayout->mLayoutFileName, &drawInfo, &drawer, &shareFont);
			//NN_LOG("OpenVCMRes %s\n", pLayout->mLayoutFileName);
			
			trlEmuMenuAnim *pAnim = pLayout->mpAnim;
			if(pAnim != NULL)
			{
				for(int k=0;k<pAnim->mAnimNum;k++)
				{
					//NN_LOG("OpenVCMRes %s\n", pAnim->mpAnimFileNames[k]);
					pLayout->mpButtonSet->addanim(pAnim->mpAnimFileNames[k]);
				}
			}
		}
	}
	trlEmuMenuStateInit();
}

void CEmuMenu::OpenFile(const wchar_t *pFileName)
{
	NN_UNUSED_VAR(pFileName);
	mpButtonSetMain = cgbvcm_layout_main.mpButtonSet;
	mpButtonSetNMain = cgbvcm_layout_nmain.mpButtonSet;
	mpButtonSetMessage = cgbvcm_layout_message.mpButtonSet;
	mpButtonSetNMessage = cgbvcm_layout_nmessage.mpButtonSet;
	mpButtonSetFirstTime = cgbvcm_layout_firsttime.mpButtonSet;

	mpButtonSetMessageWindow = commonwindow_layout_main.mpButtonSet;

	mpButtonSetError = errvcm_layout_error.mpButtonSet;

	mpButtonSetHomeNix = homenix_layout_nix.mpButtonSet;

#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
	mpButtonSetChildMain = cgbvcm_layout_childmain.mpButtonSet;
#endif


	
	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_NES)
	{
		mpButtonSetModeChange = hvcvcm_layout_ctrlchange.mpButtonSet;
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		mpButtonSetMessageDL = cgbvcm_layout_messagedl.mpButtonSet;
		mpButtonSetWarningDL = cgbvcm_layout_warningdl.mpButtonSet;
#endif
	}
	else
	{
#if TRL_NETTYPE == TRL_EMUCORE_NETTYPE_NONE
		mpButtonSetModeChange = cgbvcm_layout_modechange.mpButtonSet;
#endif
	}

	mModeChangeState = eModeChangeStateInit;
}

s32 CEmuMenu::OpenMessageWindowLanguageFile(const wchar_t *pFileName, const wchar_t *pScaleName)
{
	CEmuMenuFile file;
	if (!file.Read(pFileName, *pAlloctor))
	{
		NW_FATAL_ERROR("can not read lang file.");
		return 0;
	}
	

	CEmuMenuFile scalefile;
	float *pScale;
	if (!scalefile.Read(pScaleName, *pAlloctor))
	{
		NW_FATAL_ERROR("can not read scalefile file.");
		pScale = 0;		
	}
	else
		pScale = (float*)scalefile.Buffer();
	int bufferct = 0;

	wchar_t *pStr = (wchar_t*)file.Buffer();

	char temp[16];
	int ct = 0;
	bufferct = 1;
	while(bufferct < file.Size()/2)
	{
		int strlen = bufferct;
		while(strlen < file.Size()/2 && pStr[strlen] != 0)
			strlen++;
		strlen -= bufferct;

		float fscale = 1.0f;
		if(pScale != NULL)
			fscale = pScale[ct];

		sprintf(temp, "%d", ct);
		mpButtonSetMessageWindow->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);

		pMessageWindowMessage[ct] = pStr + bufferct;
		pMessageWindowMessageLength[ct] = strlen;
		pMessageWindowMsgScale[ct] = fscale;
		ct++;
		if(ct >= VCM_MESSAGEWINDOW_MSG_MAX)
			break;
		bufferct += strlen;
		if(bufferct < file.Size()/2)
			bufferct++;
	}
	NN_LOG("OpenMessageWindowLanguageFile have %d message\n", ct);
	pAlloctor->Free(scalefile.Buffer());
	//pAlloctor->Free(file.Buffer()); //don't free this, it be used later
	return 1;
}

s32 CEmuMenu::OpenErrLanguageFile(const wchar_t *pFileName, const wchar_t *pScaleName)
{	
	CEmuMenuFile file;
	if (!file.Read(pFileName, *pAlloctor))
	{
		NW_FATAL_ERROR("can not read lang file.");
		return 0;
	}
	

	CEmuMenuFile scalefile;
	float *pScale;
	if (!scalefile.Read(pScaleName, *pAlloctor))
	{
		NW_FATAL_ERROR("can not read scalefile file.");
		pScale = 0;		
	}
	else
		pScale = (float*)scalefile.Buffer();
	int bufferct = 0;

	wchar_t *pStr = (wchar_t*)file.Buffer();

	char temp[16];
	int ct = 0;
	bufferct = 1;
	while(bufferct < file.Size()/2)
	{
		int strlen = bufferct;
		while(strlen < file.Size()/2 && pStr[strlen] != 0)
			strlen++;
		strlen -= bufferct;

		float fscale = 1.0f;
		if(pScale != NULL)
			fscale = pScale[ct];

		sprintf(temp, "%d", ct);
		mpButtonSetError->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);

		pErrorMessage[ct] = pStr + bufferct;
		pErrorMessageLength[ct] = strlen;
		pErrorMsgScale[ct] = fscale;
		ct++;
		if(ct >= VCM_ERRORMSG_MAX)
			break;
		bufferct += strlen;
		if(bufferct < file.Size()/2)
			bufferct++;
	}
	pAlloctor->Free(scalefile.Buffer());
	//pAlloctor->Free(file.Buffer()); //don't free this, it be used later
	return 1;
}

s32 CEmuMenu::OpenLanguageFile(const wchar_t *pFileName, const wchar_t *pScaleName)
{	
	CEmuMenuFile file;
	if (!file.Read(pFileName, *pAlloctor))
	{
		NW_FATAL_ERROR("can not read lang file.");
		return 0;
	}
	

	CEmuMenuFile scalefile;
	float *pScale;
	if (!scalefile.Read(pScaleName, *pAlloctor))
	{
		NW_FATAL_ERROR("can not read scalefile file.");
		pScale = 0;		
	}
	else
		pScale = (float*)scalefile.Buffer();
	int bufferct = 0;

	wchar_t *pStr = (wchar_t*)file.Buffer();

	char temp[16];
	int ct = 0;
	bufferct = 1;
	while(bufferct < file.Size()/2)
	{
		int strlen = bufferct;
		while(strlen < file.Size()/2 && pStr[strlen] != 0)
			strlen++;
		strlen -= bufferct;

		float fscale = 1.0f;
		if(pScale != NULL)
			fscale = pScale[ct];

		sprintf(temp, "%d", ct);

		mpButtonSetMain->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);
		mpButtonSetMessage->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);

		mpButtonSetNMain->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);
		mpButtonSetNMessage->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);

#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		mpButtonSetWarningDL->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);
		mpButtonSetMessageDL->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);
		mpButtonSetChildMain->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);
#endif

		mpButtonSetModeChange->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);
		mpButtonSetFirstTime->SetStringByUserStr(temp, pStr + bufferct, strlen, fscale);

		pMainMessage[ct] = pStr + bufferct;
		pMainMessageLength[ct] = strlen;
		pMainMessageScale[ct] = fscale;
		ct++;

		bufferct += strlen;
		if(bufferct < file.Size()/2)
			bufferct++;
	}
	pAlloctor->Free(scalefile.Buffer());
	pAlloctor->Free(file.Buffer());	
	return 1;
}

void CEmuMenu::Convert4PMessage()
{
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
	NN_LOG("Convert4PMessage  %d\n", g_nTrlNetwork4PMsg);
	
	int beginmsg,endmsg;
	int msg_4p;
	beginmsg = HVC_VCM_00;
	endmsg = HVC_VCM_END;
	char temp[16];
	for(int i=beginmsg;i<=endmsg;i++)
	{
		msg_4p = i;
		if(g_nTrlNetwork4PMsg == 1)
		{
			msg_4p = i + HVC_VCM_4P_00 - HVC_VCM_00;
		}
			
		sprintf(temp, "%d", i);
		mpButtonSetMain->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);
		mpButtonSetMessage->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);

		mpButtonSetNMain->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);
		mpButtonSetNMessage->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);


		mpButtonSetWarningDL->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);
		mpButtonSetMessageDL->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);
		mpButtonSetChildMain->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);


		mpButtonSetModeChange->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);
		mpButtonSetFirstTime->SetStringByUserStr(temp, pMainMessage[msg_4p],pMainMessageLength[msg_4p], pMainMessageScale[msg_4p]);
	}
#endif
}

s32 CEmuMenu::beInOpenTouchArea(s32 x, s32 y)
{	
	if(mpButtonSetMain != NULL)
	{
		return mpButtonSetMain->inPaneAreaSpecial("B_MsgBg_00", x - 160 , 120 - y);
	}
	return 0;
}



void CEmuMenu::updateLoadFade()
{	
	if(mLoadFadeState == eLoadFadeStateFadeNone)
		return;
	nLoadFadeCt++;
	switch(mLoadFadeState)
	{
	case eLoadFadeStateFadeIn1:
		if(nLoadFadeCt >= nLoadFadeIn1Max)
		{
			LoadFade_To_FadeIn1End();
		}
		break;
	case eLoadFadeStateFadeIn1End:
		break;
	case eLoadFadeStateFadeIn2:
		if(nLoadFadeCt >= nLoadFadeIn2Max)
		{
			LoadFade_To_FadeWait();
		}
		break;
	case eLoadFadeStateFadeWait:
		if(nLoadFadeCt >= nLoadFadeWaitMax)
		{
			LoadFade_To_FadeOut();
		}
		break;
	case eLoadFadeStateFadeOut:
		if(nLoadFadeCt >= nLoadFadeOutMax)
		{
			LoadFade_To_FadeNone();
		}
		break;
	}
}

f32 CEmuMenu::GetLoadFadeParam(u32 menuFade)
{
	switch(mLoadFadeState)
	{
	case eLoadFadeStateFadeNone:
		return menuFade*1.0f/10.0f;
	case eLoadFadeStateFadeIn1:
		return menuFade*(1.0f - nLoadFadeCt*1.0f/nLoadFadeIn1Max)/10.0f;
	case eLoadFadeStateFadeIn1End:
		return 0.0f;
	case eLoadFadeStateFadeIn2:
		return nLoadFadeCt*1.0/nLoadFadeIn2Max;
	case eLoadFadeStateFadeWait:
		return 1.0f;
	case eLoadFadeStateFadeOut:		
		return 1.0 - nLoadFadeCt*1.0/nLoadFadeOutMax*(1-menuFade*1.0f/10.0f);
	}
	return 1.0f;
}

u32 CEmuMenu::GetLoadFadeFlag()
{
	switch(mLoadFadeState)
	{
	case eLoadFadeStateFadeNone:
		return 0;
	case eLoadFadeStateFadeIn1:
		return 0;
	case eLoadFadeStateFadeIn1End:
		return 1;
	case eLoadFadeStateFadeIn2:
		return 0;
	case eLoadFadeStateFadeWait:
		return 0;
	case eLoadFadeStateFadeOut:		
		return 0;
	}
	return 0;
}


void CEmuMenu::UpdateSwitchIcon0()
{
	if(mpButtonSetModeChange->bUpdate)
	mpButtonSetModeChange->update();
}

s32 CEmuMenu::UpdateSwitchIconBG(u32 dotbydot)
{
	if(mpButtonSetModeChange->search("icon_moniBBG_00") != NULL)
	{
		if(dotbydot)
		{
			mpButtonSetModeChange->search("icon_moniBBG_00")->SetVisible(false);
			mpButtonSetModeChange->search("icon_moniBBG_01")->SetVisible(true);
		}
		else
		{
			mpButtonSetModeChange->search("icon_moniBBG_00")->SetVisible(true);
			mpButtonSetModeChange->search("icon_moniBBG_01")->SetVisible(false);
		}
	}
	return 0;
}

s32 CEmuMenu::UpdateSwitchIcon1(s32 index, s32 bDraw)
{
	glGetError();
	if(bDraw == 1)
	{
		if(mModeChangeState == eModeChangeStateInit)//init
		{
			if(index == eModeChangeStateBOpen)
			{
				mModeChangeState = eModeChangeStateBOpen;
				mpButtonSetModeChange->bindanimall(eModeChangeAnim_B_open_00);
			}
			else if(index == eModeChangeStateGOpen)
			{
				mModeChangeState = eModeChangeStateGOpen;
				mpButtonSetModeChange->bindanimall(eModeChangeAnim_G_open_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateBOpen)//opening
		{
			if(mpButtonSetModeChange->animisend(eModeChangeAnim_B_open_00))
			{
				mpButtonSetModeChange->unbindanim(eModeChangeAnim_B_open_00);
				mModeChangeState = eModeChangeStateBLoop;
				mpButtonSetModeChange->bUpdate=false;
				//mpButtonSetModeChange->bindanimall(eModeChangeAnim_B_loop_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateGOpen)//opening
		{
			if(mpButtonSetModeChange->animisend(eModeChangeAnim_G_open_00))
			{
				mpButtonSetModeChange->unbindanim(eModeChangeAnim_G_open_00);
				mModeChangeState = eModeChangeStateGLoop;
				mpButtonSetModeChange->bUpdate=false;
				//mpButtonSetModeChange->bindanimall(eModeChangeAnim_G_loop_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateBLoop)
		{
			if(index == eModeChangeStateBClose)
			{
				//mpButtonSetModeChange->unbindanim(eModeChangeAnim_B_loop_00);
				mModeChangeState = eModeChangeStateBClose;
				mpButtonSetModeChange->bUpdate=true;
				mpButtonSetModeChange->bindanimall(eModeChangeAnim_B_close_00);
			}
			else if(index == eModeChangeStateBTOG)
			{
				//mpButtonSetModeChange->unbindanim(eModeChangeAnim_B_loop_00);
				mModeChangeState = eModeChangeStateBTOG;
				mpButtonSetModeChange->bUpdate=true;
				mpButtonSetModeChange->bindanimall(eModeChangeAnim_B_to_G_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateGLoop)
		{
			if(index == eModeChangeStateGClose)
			{
				//mpButtonSetModeChange->unbindanim(eModeChangeAnim_G_loop_00);
				mModeChangeState = eModeChangeStateGClose;
				mpButtonSetModeChange->bUpdate=true;
				mpButtonSetModeChange->bindanimall(eModeChangeAnim_G_close_00);
			}
			else if(index == eModeChangeStateGTOB)
			{
				//mpButtonSetModeChange->unbindanim(eModeChangeAnim_G_loop_00);
				mModeChangeState = eModeChangeStateGTOB;
				mpButtonSetModeChange->bUpdate=true;
				mpButtonSetModeChange->bindanimall(eModeChangeAnim_G_to_B_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateBTOG)
		{
			if(mpButtonSetModeChange->animisend(eModeChangeAnim_B_to_G_00))
			{
				mpButtonSetModeChange->unbindanim(eModeChangeAnim_B_to_G_00);
				mModeChangeState = eModeChangeStateGLoop;
				mpButtonSetModeChange->bUpdate=false;
				//mpButtonSetModeChange->bindanimall(eModeChangeAnim_G_loop_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateGTOB)
		{
			if(mpButtonSetModeChange->animisend(eModeChangeAnim_G_to_B_00))
			{
				mpButtonSetModeChange->unbindanim(eModeChangeAnim_G_to_B_00);
				mModeChangeState = eModeChangeStateBLoop;
				mpButtonSetModeChange->bUpdate=false;
				//mpButtonSetModeChange->bindanimall(eModeChangeAnim_B_loop_00);
			}
		}
		else if(mModeChangeState == eModeChangeStateBClose)
		{
			if(mpButtonSetModeChange->animisend(eModeChangeAnim_B_close_00))
			{
				mpButtonSetModeChange->unbindanim(eModeChangeAnim_B_close_00);
				mModeChangeState = eModeChangeStateInit;
			}
		}
		else if(mModeChangeState == eModeChangeStateGClose)
		{
			if(mpButtonSetModeChange->animisend(eModeChangeAnim_G_close_00))
			{
				mpButtonSetModeChange->unbindanim(eModeChangeAnim_G_close_00);
				mModeChangeState = eModeChangeStateInit;
			}
		}
		if(mModeChangeState == eModeChangeStateInit)//init
		{
			return 1;
		}
		else if(mModeChangeState == eModeChangeStateBLoop)
		{
			return 1;
		}
		else if(mModeChangeState == eModeChangeStateGLoop)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		if(mModeChangeState == eModeChangeStateInit)//init
		{
			if(index == eModeChangeStateBOpen)
			{
				mModeChangeState = eModeChangeStateBOpen;
			}
			else if(index == eModeChangeStateGOpen)
			{
				mModeChangeState = eModeChangeStateGOpen;
			}
		}
		else if(mModeChangeState == eModeChangeStateBOpen)//opening
		{
			mModeChangeState = eModeChangeStateBLoop;
		}
		else if(mModeChangeState == eModeChangeStateGOpen)//opening
		{
			mModeChangeState = eModeChangeStateGLoop;
		}
		else if(mModeChangeState == eModeChangeStateBLoop)
		{
			if(index == eModeChangeStateBClose)
			{
				mModeChangeState = eModeChangeStateBClose;
			}
			else if(index == eModeChangeStateBTOG)
			{
				mModeChangeState = eModeChangeStateBTOG;
			}
		}
		else if(mModeChangeState == eModeChangeStateGLoop)
		{
			if(index == eModeChangeStateGClose)
			{
				mModeChangeState = eModeChangeStateGClose;
			}
			else if(index == eModeChangeStateGTOB)
			{
				mModeChangeState = eModeChangeStateGTOB;
			}
		}
		else if(mModeChangeState == eModeChangeStateBTOG)
		{
			mModeChangeState = eModeChangeStateGLoop;
		}
		else if(mModeChangeState == eModeChangeStateGTOB)
		{
			mModeChangeState = eModeChangeStateBLoop;
		}
		else if(mModeChangeState == eModeChangeStateBClose)
		{
			mModeChangeState = eModeChangeStateInit;
		}
		else if(mModeChangeState == eModeChangeStateGClose)
		{
			mModeChangeState = eModeChangeStateInit;
		}
		if(mModeChangeState == eModeChangeStateInit)//init
		{
			return 1;
		}
		else if(mModeChangeState == eModeChangeStateBLoop)
		{
			return 1;
		}
		else if(mModeChangeState == eModeChangeStateGLoop)
		{
			return 1;
		}
		return 0;
	}
}

void CEmuMenu::DrawSwitchIcon()
{
	glFlush();
	glGetError();
	mpButtonSetModeChange->InitGX();
	mpButtonSetModeChange->SetupCamera();
	nngxUpdateState(NN_GX_STATE_ALL);
	drawer.DrawBegin(drawInfo);
	mpButtonSetModeChange->draw();
	drawer.DrawEnd(drawInfo);
	nngxUpdateState(NN_GX_STATE_ALL);
}

#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
void CEmuMenu::UpdateWarningDL()
{
	if(g_bTrlEmuDLPNoticeDraw == true && g_bTrlEmuDLPNotice == true)
	{
		if(mpButtonSetWarningDL->bUpdate)
			mpButtonSetWarningDL->update();
	}
}

void CEmuMenu::ClearWarningDL()
{
	static int flag  = 0;
	if(g_bTrlEmuDLPNotice == true)
	{
		flag = 1;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		if(flag == 1)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		flag = 0;
	}
}

void CEmuMenu::DrawWarningDL()
{	
	if(g_bTrlEmuDLPNoticeDraw == true && g_bTrlEmuDLPNotice == true)
	{	
		glFlush();
		glGetError();
		mpButtonSetWarningDL->InitGX();
		mpButtonSetWarningDL->SetupCamera();
		nngxUpdateState(NN_GX_STATE_ALL);
		drawer.DrawBegin(drawInfo);
		mpButtonSetWarningDL->draw();
		drawer.DrawEnd(drawInfo);
		nngxUpdateState(NN_GX_STATE_ALL);
	}	
}
#endif

void CEmuMenu::SetSaveFunc(s32 (*pFunc)(u32))
{
	pSaveFunc = pFunc;
}

void CEmuMenu::SetLoadFunc(s32 (*pFunc)(u32))
{
	pLoadFunc = pFunc;
}

void CEmuMenu::SetResumeFunc(void (*pFunc)(void))
{
	pResumeFunc = pFunc;
}

void CEmuMenu::SetResetFunc(void (*pFunc)(void))
{
	pResetFunc = pFunc;
}

void CEmuMenu::SetMainMessage(char *name, u32 msg_no)
{
	NN_LOG("SetMainMessage %d\n", msg_no);
	mpButtonSetMain->SetStringByName(name, pMainMessage[msg_no]);
	mpButtonSetNMain->SetStringByName(name, pMainMessage[msg_no]);
}

void CEmuMenu::SetErrorMessageYN(u32 msg_no)
{
	NN_LOG("SetErrorMessageYN %d\n", msg_no);
	mpButtonSetError->SetStringByUserStr("YN_MSG", pErrorMessage[msg_no], pErrorMessageLength[msg_no], pErrorMsgScale[msg_no]);
}
void CEmuMenu::SetErrorMessageOK(u32 msg_no)
{
	NN_LOG("SetErrorMessageOK %d\n", msg_no);
	mpButtonSetError->SetStringByUserStr("OK_MSG", pErrorMessage[msg_no], pErrorMessageLength[msg_no], pErrorMsgScale[msg_no]);	
}
void CEmuMenu::SetErrorMessageWait(u32 msg_no)
{
	NN_LOG("SetErrorMessageWait %d\n", msg_no);
	mpButtonSetError->SetStringByUserStr("WAIT_MSG", pErrorMessage[msg_no], pErrorMessageLength[msg_no], pErrorMsgScale[msg_no]);
}

void CEmuMenu::SetDLPMessageYN(u32 msg_no)
{
	//NN_LOG("SetDLPMessageYN %d  strlen = %d sacle = %f\n", msg_no, pMessageWindowMessageLength[msg_no], pMessageWindowMsgScale[msg_no]);
	mpButtonSetMessageWindow->SetStringByUserStr("YN_MSG", pMessageWindowMessage[msg_no], pMessageWindowMessageLength[msg_no], pMessageWindowMsgScale[msg_no]);
}
void CEmuMenu::SetDLPMessageOK(u32 msg_no)
{
	//NN_LOG("SetDLPMessageOK %d  strlen = %d sacle = %f\n", msg_no, pMessageWindowMessageLength[msg_no], pMessageWindowMsgScale[msg_no]);
	mpButtonSetMessageWindow->SetStringByUserStr("OK_MSG", pMessageWindowMessage[msg_no], pMessageWindowMessageLength[msg_no], pMessageWindowMsgScale[msg_no]);	
}
void CEmuMenu::SetDLPMessageWait(u32 msg_no)
{
	//NN_LOG("SetDLPMessageWait %d  strlen = %d sacle = %f\n", msg_no, pMessageWindowMessageLength[msg_no], pMessageWindowMsgScale[msg_no]);
	mpButtonSetMessageWindow->SetStringByUserStr("WAIT_MSG", pMessageWindowMessage[msg_no], pMessageWindowMessageLength[msg_no], pMessageWindowMsgScale[msg_no]);
}

void CEmuMenu::L2BConvert(u32* pLine, u32* pBlock, u32 nWidth, u32 nHeight)
{
	nWidth >>= 1;
	u32* pLineCur = pLine;
	for(u32 h=0; h<nHeight; h+=8)
	{
		for(u32 w=0; w<nWidth; w+=4, pLineCur += 4)
		{
			u32* pLineCur2 = pLineCur;
			for(u32 h1=0; h1<2; ++h1)
			{
				for(u32 w1=0; w1<2; ++w1, pLineCur2 += 2)
				{
					u32* pLineCur3 = pLineCur2;
					for(u32 h2=0; h2<2; ++h2)
					{
						for(u32 w2=0; w2<2; ++w2, ++pLineCur3, pBlock+=2)
						{
							pBlock[0] = pLineCur3[0] | 0x00010001;
							pBlock[1] = pLineCur3[nWidth] | 0x00010001;
						}
						pLineCur3 = pLineCur2 + nWidth*2;
					}
				}
				pLineCur2 = pLineCur + nWidth*4;
			}
		}
		pLineCur = pLine + nWidth*(h+8);
	}
}

#include "trlEmuMenuDataArc.h"

void CEmuMenu::ChangeCtrlChangeTexutre()
{
	nw::lyt::ArcResourceAccessor resAcc;
	resAcc.Attach(hvcvcm_arc.mArcFile.Buffer(), ".");
	u32 sizea = 0;
	u32* imageresa;
	u32 sizeb = 0;
	u32* imageresb;

	nw::lyt::TextureInfo texinfo;
	nw::lyt::Picture *pPic;
	nw::lyt::TexMap texmap;

	
	imageresa = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "1p.bclim", &sizea);
	imageresb = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "1p_nes.bclim", &sizeb);
	if(sizea == sizeb)	
		memcpy(imageresa, imageresb, sizea);
	imageresa = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "1p_baloon.bclim", &sizea);
	imageresb = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "1p_baloon_nes.bclim", &sizeb);
	if(sizea == sizeb)	
		memcpy(imageresa, imageresb, sizea);	

	imageresa = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "2p.bclim", &sizea);
	imageresb = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "2p_nes.bclim", &sizeb);
	if(sizea == sizeb)	
		memcpy(imageresa, imageresb, sizea);	
	imageresa = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "2p_baloon.bclim", &sizea);
	imageresb = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "2p_baloon_nes.bclim", &sizeb);
	if(sizea == sizeb)	
		memcpy(imageresa, imageresb, sizea);
}

void CEmuMenu::updateSavePreview()
{
	if(beHaveSave)
	{
		NN_LOG("updateSavePreview behaveSave\n");
		mpButtonSetMessage->search("T_Save_00")->SetVisible(true);
		mpButtonSetMessage->search("T_Save_01")->SetVisible(true);
		mpButtonSetMessage->search("T_Save_02")->SetVisible(false);
		mpButtonSetMain->search("T_LoadBtn_02")->SetVisible(true);
	}
	else
	{
		NN_LOG("updateSavePreview no behaveSave\n");
		mpButtonSetMessage->search("T_Save_00")->SetVisible(false);
		mpButtonSetMessage->search("T_Save_01")->SetVisible(false);
		mpButtonSetMessage->search("T_Save_02")->SetVisible(true);
		mpButtonSetMain->search("T_LoadBtn_02")->SetVisible(false);
	}

	nw::lyt::TextBox *pTb;
	pTb = (nw::lyt::TextBox*)mpButtonSetMain->search("T_LoadBtn_02");
	if(pTb != NULL)
	{
		if(pTb->GetString() != NULL)
			pTb->SetString(pTb->GetString());
	}

	pTb = (nw::lyt::TextBox*)mpButtonSetMessage->search("T_Save_01");
	if(pTb != NULL)
		if(pTb->GetString() != NULL)
			pTb->SetString(pTb->GetString());

	pTb = (nw::lyt::TextBox*)mpButtonSetMessage->search("T_Load_00");
	if(pTb != NULL)
		if(pTb->GetString() != NULL)
			pTb->SetString(pTb->GetString());


	if(beHaveSave)
	{
		nw::lyt::Pane *pPane;
		nw::lyt::TexMap texMap;

		pPane = mpButtonSetMain->search("P_Preview_00");
		texMap = pPane->GetMaterial()->GetTexMap(0);
		texMap.SetSize(nPreviewWidth, nPreviewHeight);
		pPane->GetMaterial()->SetTexMap(0, texMap);

		pPane = mpButtonSetMessage->search("P_LoadPreview_00");
		texMap = pPane->GetMaterial()->GetTexMap(0);
		texMap.SetSize(nPreviewWidth, nPreviewHeight);
		pPane->GetMaterial()->SetTexMap(0, texMap);

		/*pPane = mpButtonSetMessage->search("P_SavePreview_00");
		texMap = pPane->GetMaterial()->GetTexMap(0);
		texMap.SetSize(nPreviewWidth, nPreviewHeight);
		pPane->GetMaterial()->SetTexMap(0, texMap);*/

		pPane = mpButtonSetMessage->search("P_SaveOKPrev_00");
		texMap = pPane->GetMaterial()->GetTexMap(0);
		texMap.SetSize(nPreviewWidth, nPreviewHeight);
		pPane->GetMaterial()->SetTexMap(0, texMap);

		/*pPane = mpButtonSetMessage->search("P_LoadOKPrev_00");
		texMap = pPane->GetMaterial()->GetTexMap(0);
		texMap.SetSize(nPreviewWidth, nPreviewHeight);
		pPane->GetMaterial()->SetTexMap(0, texMap);*/

		nw::lyt::ArcResourceAccessor resAcc;
		resAcc.Attach(cgbvcm_arc.mArcFile.Buffer(), ".");
		u32 size = 0;
		u32* imageres = (u32*)resAcc.GetResource(nw::lyt::res::RESOURCETYPE_TEXTURE, "bg_00.bclim", &size);
		if(imageres != NULL && pSavePreview != NULL)
			L2BConvert((u32*)pSavePreview, imageres, 256, 256);
	}
}
