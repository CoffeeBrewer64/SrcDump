/**
 * @file trlEmuMenu.h
 * @author zhfang
 * @date 2010.03.19
 * @brief trlEmuMenu
 */
#pragma once
#include "../../../trlHeader.h"
#include "../../../trlMacro.h"
#include "../../trlEmuShellStruct.h"
#include "../../trlEmuShellNetWork.h"
#include <nw/ut.h>
#include <nw/lyt.h>
#include <nw/snd.h>
#include "trlEmuMenuButtonSet.h"
#include "trlEmuMenuPad.h"

class CEmuMenuAlloctor: public nw::os::IAllocator
{
public:
	CEmuMenuAlloctor()
	{
		pAllocFunc = NULL;
		pFreeFunc = NULL;
	}
	CEmuMenuAlloctor(void* (*pAllocFunc)(size_t, u8), void  (*pFreeFunc)(void*))
	{
		this->pAllocFunc = pAllocFunc;
		this->pFreeFunc = pFreeFunc;
	}
	void SetAlloc(void* (*pAllocFunc)(size_t, u8), void  (*pFreeFunc)(void*))
	{
		this->pAllocFunc = pAllocFunc;
		this->pFreeFunc = pFreeFunc;
	}
	virtual void* Alloc(size_t size, u8 alignment)
	{
		return pAllocFunc(size, alignment);
	}
	virtual void  Free(void* memory)
	{
		pFreeFunc(memory);
	}
private:
	void* (*pAllocFunc)(size_t, u8);
	void  (*pFreeFunc)(void*);
};

class CEmuMenuFile
{
public:
    CEmuMenuFile()
      : m_Buffer(NULL), m_Size(0)
    {
    }

    bool Read(const wchar_t* fileName, nw::os::IAllocator& allocator)
    {
        NW_ASSERT(m_Buffer == NULL);

        nn::fs::FileReader fileReader(fileName);
        if (fileReader.GetSize() <= 0)
        {
            return false;
        }

        this->m_Size = static_cast<u32>(fileReader.GetSize());
        this->m_Buffer = static_cast<u8*>(allocator.Alloc(this->m_Size, 128));
        if (this->m_Buffer == NULL)
        {
            this->m_Size = 0;
            return false;
        }

        fileReader.Read(this->m_Buffer, this->m_Size);
        fileReader.Finalize();

        return true;
    }

    u8* Buffer()
    {
        return this->m_Buffer;
    }

    u32 Size()
    {
        return this->m_Size;
    }

public:
    u8* m_Buffer;
    u32 m_Size;
};


enum EEmuMenuRunVCMReslut
{
	eRunVCMReslut_Continue = 0,
	eRunVCMReslut_End
};
class CEmuMenu
{
public:
	~CEmuMenu()
	{
		Release();
	}

	void OpenVCMRes();
	void ReleaseVCMRes();

	void VCMForceMenuInit();
	void VCMForceError();
	void VCMForceGo();
	void UpdateVCM();
	void DrawVCM();
#if TRL_HOMENIX_UPSCREEN
	void DrawHomeNix();
#endif
	void RunState_Normal();
	void RunState_Normal_WaitButton();
	void RunState_Change();
	s32 RunVCM();
	void UpdatePad();
	void UpdateHomeNix();

	void Init(nw::os::IAllocator *pAlloctor, nw::os::IAllocator* pDeviceMemoryAllocator);	
	void LoadShaderResource();
	void InitSound();
	void OpenSoundFile(const char *pSoundFileName);
	void OpenFile(const wchar_t *pFileName);

	void Convert4PMessage();

	s32 beInOpenTouchArea(s32 x, s32 y);  //return 0: not in  1: in

	#define VCM_MAINMSG_MAX 0x50
	wchar_t *pMainMessage[VCM_MAINMSG_MAX];
	u32 pMainMessageLength[VCM_MAINMSG_MAX];
	float pMainMessageScale[VCM_MAINMSG_MAX];	
	s32 OpenLanguageFile(const wchar_t *pFileName, const wchar_t *pScaleName);


	#define VCM_ERRORMSG_MAX 0x20
	wchar_t *pErrorMessage[VCM_ERRORMSG_MAX];
	u32		pErrorMessageLength[VCM_ERRORMSG_MAX];
	float pErrorMsgScale[VCM_ERRORMSG_MAX];	
	s32 OpenErrLanguageFile(const wchar_t *pFileName, const wchar_t *pScaleName);

	#define VCM_MESSAGEWINDOW_MSG_MAX 0x20
	wchar_t *pMessageWindowMessage[VCM_MESSAGEWINDOW_MSG_MAX];
	u32		pMessageWindowMessageLength[VCM_MESSAGEWINDOW_MSG_MAX];
	float pMessageWindowMsgScale[VCM_MESSAGEWINDOW_MSG_MAX];	
	s32 OpenMessageWindowLanguageFile(const wchar_t *pFileName, const wchar_t *pScaleName);

	void Release();
	void ReleaseSound();
	void Release1();

#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
	void ClearWarningDL();
	void DrawWarningDL();
	void UpdateWarningDL();
#endif

	void DrawSwitchIcon();
	void UpdateSwitchIcon0();
	s32 UpdateSwitchIcon1(s32 index, s32 bDraw = 1);
	//set the switch icon bg by dotbydot mode or normal mode
	s32 UpdateSwitchIconBG(u32 dotbydot);

	void SetSaveDate(u32 *year, u32 *month, u32 *day){ pSaveYear = year;pSaveMonth = month;pSaveDay = day;}
	void SetSavePicture(u16* pAddr) { pSavePreview = pAddr;}
	void SetFrameBuffer0(GLuint nFrame) { nFrameBufObj0 = nFrame; }
	void SetFrameBuffer1(GLuint nFrame) { nFrameBufObj1 = nFrame; }
	void SetSaveFunc(s32 (*pFunc)(u32));
	void SetLoadFunc(s32 (*pFunc)(u32));	
	void SetResetFunc(void (*pFunc)(void));
	void SetResumeFunc(void (*pFunc)(void));	

	void SetSaveAnim(u32 onoff){saveanimon = onoff;};
	void SetLoadAnim(u32 onoff){loadanimon = onoff;};
	void SetResetAnim(u32 onoff){resetanimon = onoff;};

	void SetWaitIconEnable(u32 enable){bWaitIconEnable = enable;};

	enum EModeChangeState
	{
		eModeChangeStateInit,  
		eModeChangeStateBOpen, 
		eModeChangeStateBLoop, 
		eModeChangeStateBClose,
		eModeChangeStateBTOG, 
		eModeChangeStateGOpen, 
		eModeChangeStateGLoop, 
		eModeChangeStateGClose,
		eModeChangeStateGTOB   
	};
public:

	s32 bHaveNetError;
	s32 bHaveNetErrorInMenu;
protected:
	u32 saveanimon;
	u32 loadanimon;
	u32 resetanimon;
	u32 bWaitIconEnable;


	enum ELoadFadeState
	{
		eLoadFadeStateFadeNone = 0,
		eLoadFadeStateFadeIn1,
		eLoadFadeStateFadeIn1End,
		eLoadFadeStateFadeIn2,
		eLoadFadeStateFadeWait,
		eLoadFadeStateFadeOut
	};
	ELoadFadeState mLoadFadeState;

	u32 nLoadFadeIn1Max;
	u32 nLoadFadeIn2Max;
	u32 nLoadFadeOutMax;
	u32 nLoadFadeWaitMax;
	u32 nLoadFadeCt;

	void updateLoadFade();
public:
	void LoadFade_To_FadeIn1()
	{
		nLoadFadeCt = 0;
		mLoadFadeState = eLoadFadeStateFadeIn1;
	}
	void LoadFade_To_FadeIn1End()
	{
		nLoadFadeCt = 0;
		mLoadFadeState = eLoadFadeStateFadeIn1End;
	}
	void LoadFade_To_FadeIn2()
	{
		nLoadFadeCt = 0;
		mLoadFadeState = eLoadFadeStateFadeIn2;
	}
	void LoadFade_To_FadeWait()
	{
		mLoadFadeState = eLoadFadeStateFadeWait;
	}
	void LoadFade_To_FadeOut()
	{
		if(mLoadFadeState == eLoadFadeStateFadeWait)
		{
			nLoadFadeCt = 0;
			mLoadFadeState = eLoadFadeStateFadeOut;
		}
	}

	u32 LoadFade_FadeIn1End()
	{
		if(mLoadFadeState != eLoadFadeStateFadeIn1)
			return 1;
		return 0;
	}
	u32 LoadFade_FadeIn2End()
	{
		if(mLoadFadeState != eLoadFadeStateFadeIn2)
			return 1;
		return 0;
	}
	u32 LoadFade_FadeOutEnd()
	{
		if(mLoadFadeState != eLoadFadeStateFadeOut)
			return 1;
		return 0;
	}
	void LoadFade_To_FadeNone()
	{
		mLoadFadeState = eLoadFadeStateFadeNone;
	}

public:
	void SetLoadFadeParam(u32 fadein1, u32 fadein2, u32 fadewait, u32 fadeout)
	{
		nLoadFadeIn1Max = fadein1;
		nLoadFadeIn2Max = fadein2;
		nLoadFadeWaitMax = fadewait;
		nLoadFadeOutMax = fadeout;
	}

	f32 GetLoadFadeParam(u32 menuFade);
	u32 GetLoadFadeFlag();
protected:



public:
	

protected:




	enum EMenuState
	{
		eMenuStateOpening = 0,
		eMenuStateMain,
		eMenuStateMainAction,
		eMenuStateResetOpening,
		eMenuStateResetMain,
		eMenuStateResetAction,
		eMenuStateResetingOpening,
		eMenuStateReseting,
		eMenuStateResetingSilence,
		eMenuStateResetClose0,
		eMenuStateResetClose1,
		eMenuStateResetClose2,
		eMenuStateResetBack,
		eMenuStateResetBack1,
		eMenuStateClosing,
		eMenuStateClosing1,
		eMenuStateSaveOpening,
		eMenuStateSaveMain,
		eMenuStateSaveAction,
		eMenuStateSaveingOpening,
		eMenuStateSaveing,
		eMenuStateSaveingSilence,
		eMenuStateSaveEnd,
		eMenuStateSaveEnd1,
		eMenuStateSaveEnd2,
		eMenuStateSaveEffect,
		eMenuStateSaveEndConfirm,
		eMenuStateSaveEndConfirmAction,
		eMenuStateSaveClose,
		eMenuStateSaveClose1,
		eMenuStateSaveBack,
		eMenuStateSaveBack1,
		eMenuStateLoadOpening,
		eMenuStateLoadMain,
		eMenuStateLoadAction,
		eMenuStateLoadingOpening,
		eMenuStateLoadingSilence,
		eMenuStateLoading,
		eMenuStateLoadEnd,
		eMenuStateLoadEnd1,
		eMenuStateLoadEnd2,
		eMenuStateLoadEndConfirm,
		eMenuStateLoadEndConfirmAction,
		eMenuStateLoadClose,
		eMenuStateLoadClose1,
		eMenuStateLoadBack,
		eMenuStateLoadBack1
	};



	CEmuMenuFile fileLayout;

	nw::os::IAllocator *pAlloctor;
	nw::os::IAllocator *pDeviceMemoryAllocator;
	nw::lyt::GraphicsResource graphicsResource;
	nw::lyt::DrawInfo drawInfo;
	nw::lyt::Drawer drawer;

	CButtonSet2* mpButtonSetMain;
	CButtonSet2* mpButtonSetMessage;
	CButtonSet2* mpButtonSetModeChange;
	CButtonSet2* mpButtonSetNMain;
	CButtonSet2* mpButtonSetNMessage;
	CButtonSet2* mpButtonSetFirstTime;
	CButtonSet2* mpButtonSetMessageWindow;
	CButtonSet2* mpButtonSetError;
	CButtonSet2* mpButtonSetHomeNix;

#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
	CButtonSet2* mpButtonSetWarningDL;
	CButtonSet2* mpButtonSetMessageDL;
	CButtonSet2* mpButtonSetChildMain;
#endif

	EMenuState mMenuState;
	
	EModeChangeState mModeChangeState;

	

	CEmuMenuPad mPad;

public:
	u32 beHaveSave;
public:
	u32 beNormal;
	u32 beFirst;
public:
	s32 bSaveSuccess;
	s32 bLoadSuccess;
private:

	nw::snd::RomSoundArchive		m_Archive;
	nw::snd::SoundArchivePlayer		m_ArchivePlayer;
	nw::snd::SoundDataManager		m_DataManager;
    nw::snd::SoundHeap				m_Heap;
    nw::snd::SoundHandle			m_Handle;


	void* m_pMemoryForSoundSystem;
    void* m_pMemoryForInfoBlock;
    void* m_pMemoryForSoundDataManager;
    void* m_pMemoryForSoundArchivePlayer;
    void* m_pMemoryForSoundHeap;
    void* m_pMemoryForStreamBuffer;

	void playsound(int id);
public:

	
	u32 SetNMode();
	u32 SetAMode();


protected:

	#define ERR_MSG_00 4
	#define ERR_MSG_01 5
	#define ERR_MSG_02 6
	#define ERR_MSG_03 7
	#define ERR_MSG_04 8
	#define ERR_MSG_05 9
	#define ERR_MSG_06 10
	#define ERR_MSG_07 11
	#define ERR_MSG_08 12
	#define ERR_MSG_09 13
	#define ERR_MSG_10 14
	#define ERR_MSG_11 15

public:
	void SetMainMessage(char *name, u32 msg_no);

	void SetErrorMessageYN(u32 msg_no);
	void SetErrorMessageOK(u32 msg_no);
	void SetErrorMessageWait(u32 msg_no);

	void SetDLPMessageYN(u32 msg_no);
	void SetDLPMessageOK(u32 msg_no);
	void SetDLPMessageWait(u32 msg_no);
private:	
	

	void (*pRenderFunc)(void);
	void (*pSwapBufferFunc)(const s32, const bool);

	void L2BConvert(u32* pLine, u32* pBlock, u32 nWidth, u32 nHeight);

	GLuint nFrameBufObj0, nFrameBufObj1;
	u16 *pSavePreview;
	u32 *pSaveYear, *pSaveMonth, *pSaveDay;
	u16 nPreviewWidth, nPreviewHeight;
public:
	void SetPreviewSize(u16 width, u16 height){nPreviewWidth = width;nPreviewHeight = height;};
	s32 (*pSaveFunc)(u32);
	s32 (*pLoadFunc)(u32);
	s32 (*pDeleteFunc)(u32);
	void (*pResetFunc)(void);
	void (*pResumeFunc)(void);
	void updateSavePreview();
	void ChangeCtrlChangeTexutre();
private:
	u32 releaseAction;

	nw::font::ResFont shareFont;
	void *pFontDrawBuffer;
public:
	void PlaySoundMenuOpen();
};
