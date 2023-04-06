/**
 * @file trlEmuShellInput_CTR.h
 * @author zhfang, chentian
 * @date 2011.03.31
 * @brief TRL Emulate - EmuShell Input Module for CTR
 */
#include "..\trlEmuShellInput.h"
#include "..\trlEmuShellMenu.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellNetwork.h"
#include <nn\mic.h>
#include <nn\hid.h>
#include <nn\hid\CTR\hid_PadReaderForVc.h>
using namespace nn::hid::CTR;

/** @name Macro Define */
//@{
#define MIC_SIGNED8BIT_DEFAULTAMP_LIMIT 5
//@}

/** @name Global Variable */
//@{
s8		g_nTrlInputMicBuffer[nn::mic::BUFFER_ALIGNMENT_SIZE] NN_ATTRIBUTE_ALIGN(nn::mic::BUFFER_ALIGNMENT_ADDRESS);
size_t	g_nTrlInputMicSamplingLength;
u8		g_nTrlInputMicGain;
u8		g_nTrlInputMicMin;
bool	g_bTrlInputMicHaveStart;
//@}

/** @brief EmuShell Input Update Mic */
inline void trlEmuShellInputBeginMic()
{
	if(g_bTrlInputMicHaveStart == false)
	{
		nn::Result result;
		result = nn::mic::StartSampling(nn::mic::SAMPLING_TYPE_SIGNED_8BIT, nn::mic::SAMPLING_RATE_8180, 0, g_nTrlInputMicSamplingLength, true);
		if ( result.IsFailure() )
		{
			if ( result != nn::mic::CTR::ResultShellClose() )
				NN_UTIL_PANIC_IF_FAILED(result);
		}
		else
			g_bTrlInputMicHaveStart = true;
	}
}

/** @brief EmuShell Input Init Device */
void trlEmuShellInputInitDevice()
{
	// Init HID
	NN_UTIL_PANIC_IF_FAILED(nn::hid::CTR::Initialize());

#if TRL_MIC
	// Init MIC
	NN_UTIL_PANIC_IF_FAILED(nn::mic::Initialize());
	NN_UTIL_PANIC_IF_FAILED(nn::mic::SetBuffer(g_nTrlInputMicBuffer, nn::mic::BUFFER_ALIGNMENT_SIZE));

	size_t size;
	NN_UTIL_PANIC_IF_FAILED(nn::mic::GetSamplingBufferSize(&size));
	g_nTrlInputMicSamplingLength = size / sizeof(s16);
	NN_UTIL_PANIC_IF_FAILED(nn::mic::GetAmpGain(&g_nTrlInputMicGain));
	NN_UTIL_PANIC_IF_FAILED(nn::mic::SetAmpGain(nn::mic::AMP_GAIN_DEFAULT_VALUE));
	NN_UTIL_PANIC_IF_FAILED(nn::mic::SetAmp(true));

	g_nTrlInputMicMin = trlEmuShellDataGetConfigData("NES", "MIC_MIN", MIC_SIGNED8BIT_DEFAULTAMP_LIMIT);
	if(g_nTrlInputMicMin < MIC_SIGNED8BIT_DEFAULTAMP_LIMIT)
		g_nTrlInputMicMin = MIC_SIGNED8BIT_DEFAULTAMP_LIMIT;
	{
		s32 upper,lower;
		if(nn::mic::GetForbiddenArea(&upper, &lower, nn::mic::SAMPLING_TYPE_SIGNED_8BIT, nn::mic::AMP_GAIN_DEFAULT_VALUE))
		{
			if(lower < 0)
				lower = -lower;
			if(g_nTrlInputMicMin < upper)
				g_nTrlInputMicMin = upper;
			if(g_nTrlInputMicMin < lower)
				g_nTrlInputMicMin = lower;
		}
		else
			NN_LOG("nn::mic::GetForbiddenArea return false\n");
	}
	// Start MIC
	g_bTrlInputMicHaveStart = false;
	trlEmuShellInputBeginMic();
#endif
}

/** @brief EmuShell Input Exit Device */
void trlEmuShellInputExitDevice()
{
#if TRL_MIC
	if(g_bTrlInputMicHaveStart == true)
	{
		nn::Result result = nn::mic::StopSampling();
		if ( result.IsFailure() )
			if ( result != nn::mic::CTR::ResultShellClose() )
				NN_UTIL_PANIC_IF_FAILED(result);
	}

	NN_UTIL_PANIC_IF_FAILED(nn::mic::SetAmp(false));
	NN_UTIL_PANIC_IF_FAILED(nn::mic::SetAmpGain(g_nTrlInputMicGain));
	NN_UTIL_PANIC_IF_FAILED(nn::mic::ResetBuffer());
	NN_UTIL_PANIC_IF_FAILED(nn::mic::Finalize());
#endif

	nn::hid::CTR::Finalize();
}

/** @brief EmuShell Input Update Button */
inline void trlEmuShellInputUpdateButton()
{
	u32 nPrev = g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE];
	PadReaderForVc sPad;
	PadStatus sPadStatus;
	sPad.ReadLatest(&sPadStatus);

	sPadStatus.hold |= sPadStatus.trigger;
	if(g_nTrlEmuMenuSwitchGBColorState == MENU_SWITCHGBCOLOR_CLOSED)
		sPadStatus.hold |= ((sPadStatus.hold & (BUTTON_Y))>>9);
	sPadStatus.hold |= ((sPadStatus.hold & (BUTTON_X))>>9);
	sPadStatus.hold |= ((sPadStatus.hold & PLUS_BUTTON_EMULATION_MASK)>>24);
	if((sPadStatus.hold & (BUTTON_RIGHT|BUTTON_LEFT)) == (BUTTON_RIGHT|BUTTON_LEFT))
		sPadStatus.hold &= ~BUTTON_RIGHT;
	if((sPadStatus.hold & (BUTTON_UP|BUTTON_DOWN)) == (BUTTON_UP|BUTTON_DOWN))
		sPadStatus.hold &= ~BUTTON_DOWN;

	g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] = sPadStatus.hold;
	g_nTrlInputButton[TRL_INPUT_BUTTON_TRIGGER] = (g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] & ~nPrev);
	g_nTrlInputButton[TRL_INPUT_BUTTON_RELEASE] = (~g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] & nPrev);
	g_nTrlInputButton[TRL_INPUT_BUTTON_HOLD] = (g_nTrlInputButton[TRL_INPUT_BUTTON_VALUE] & nPrev);
}

/** @brief EmuShell Input Update Touch */
inline void trlEmuShellInputUpdateTouch()
{
	TouchPanelStatus tpStatus;
	TouchPanelReader tpReader;
	tpReader.ReadLatest(&tpStatus);

	if(tpStatus.touch != g_nTrlInputTouch[TRL_INPUT_TOUCH_VALUE])
	{
		g_nTrlInputTouch[TRL_INPUT_TOUCH_TRIGGER] = tpStatus.touch;	
		g_nTrlInputTouch[TRL_INPUT_TOUCH_RELEASE] = g_nTrlInputTouch[TRL_INPUT_TOUCH_VALUE];
	}
	else
	{
		g_nTrlInputTouch[TRL_INPUT_TOUCH_TRIGGER] = 0;
		g_nTrlInputTouch[TRL_INPUT_TOUCH_RELEASE] = 0;
	}

	g_nTrlInputTouch[TRL_INPUT_TOUCH_VALUE] = tpStatus.touch;
	if(g_nTrlInputTouch[TRL_INPUT_TOUCH_VALUE] != 0)
	{
		g_nTrlInputTouch[TRL_INPUT_TOUCH_X] = tpStatus.x;
		g_nTrlInputTouch[TRL_INPUT_TOUCH_Y] = tpStatus.y;
	}
}

/** @brief EmuShell Input Update Mic */
inline u32 trlEmuShellInputUpdateMic()
{
#if TRL_MIC
	if(g_bTrlInputMicHaveStart == false)
	{
		trlEmuShellInputBeginMic();
		return 0x00000000;
	}
	else
	{
    uptr nSrc;
    NN_UTIL_PANIC_IF_FAILED(nn::mic::GetLastSamplingAddress(&nSrc));
    u32 nOffs = nSrc - reinterpret_cast<uptr>(g_nTrlInputMicBuffer);
	if ( (g_nTrlInputMicBuffer[nOffs] >g_nTrlInputMicMin && g_nTrlInputMicBuffer[nOffs]< nn::mic::TYPE_SIGNED_8BIT_GUARANTEED_INPUT_MAX)
		|| (g_nTrlInputMicBuffer[nOffs] < -g_nTrlInputMicMin && g_nTrlInputMicBuffer[nOffs]> nn::mic::TYPE_SIGNED_8BIT_GUARANTEED_INPUT_MIN)
		)
		return 0x80000000;
	else
		return 0x00000000;
	}
#else
	return 0x00000000;
#endif	
}

/** @brief EmuShell Input Update */
u32 trlEmuShellInputUpdate()
{
	trlEmuShellInputUpdateButton();
	trlEmuShellInputUpdateTouch();
	trlEmuShellInputAdvanceFunction();

	
#if TRL_MIC

#if !TRL_NETWORK_PIA_WITH_MIC
	extern u8 g_nNesInputMic;	
	g_nNesInputMic = (trlEmuShellInputUpdateMic()>>(32 - 3));

	if(g_sEmuShellBuffer.nNetworkState != TRL_NETWORK_STATE_NONE)
		g_nNesInputMic = 0;


	extern u32 g_nNesEmuSwitchPlayer;
	if(!g_nNesEmuSwitchPlayer)
		g_nNesInputMic = 0;
#else
	if(g_sEmuShellBuffer.nNetworkState == TRL_NETWORK_STATE_NONE){
		extern u32 g_nNesEmuSwitchPlayer;
		if(!g_nNesEmuSwitchPlayer){
			extern u8 g_nNesInputMic;
			g_nNesInputMic = 0;
		}
		else
			trlEmuShellInputUpdateMicrophone();
	}
#endif

#endif

	return trlEmuShellInputGetGameButton();
}

#if TRL_NETWORK_PIA_WITH_MIC
void trlEmuShellInputUpdateMicrophone()
{
	extern u8 g_nNesInputMic;	
	g_nNesInputMic = (trlEmuShellInputUpdateMic()>>(32 - 3));
}
#endif

