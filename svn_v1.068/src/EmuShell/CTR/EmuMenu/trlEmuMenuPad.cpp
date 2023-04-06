/**
 * @file trlEmuMenuPad.cpp
 * @author zhfang
 * @date 2010.03.26
 * @brief trlEmuMenu Pad
 */
#include <nw/sdk.h>
#include <nw/ut.h>
#include <nn/hid.h>
#include "trlEmuMenuPad.h"

struct ButtonMap
{
    u32 nnBit;
    CEmuMenuPad::Button demoBit;
};

#ifdef NW_PLATFORM_CTR
const ButtonMap s_ButtonMap[] =
{
    { nn::hid::BUTTON_A, CEmuMenuPad::BUTTON_A },
    { nn::hid::BUTTON_B, CEmuMenuPad::BUTTON_B },
    { nn::hid::BUTTON_R, CEmuMenuPad::BUTTON_R },
    { nn::hid::BUTTON_L, CEmuMenuPad::BUTTON_L },
    { nn::hid::BUTTON_X, CEmuMenuPad::BUTTON_X },
    { nn::hid::BUTTON_Y, CEmuMenuPad::BUTTON_Y },    
    { nn::hid::BUTTON_START, CEmuMenuPad::BUTTON_START },
    { nn::hid::BUTTON_DEBUG, CEmuMenuPad::BUTTON_DEBUG },
    { nn::hid::BUTTON_UP, CEmuMenuPad::KEY_UP },
    { nn::hid::BUTTON_DOWN, CEmuMenuPad::KEY_DOWN },
    { nn::hid::BUTTON_LEFT, CEmuMenuPad::KEY_LEFT },
    { nn::hid::BUTTON_RIGHT, CEmuMenuPad::KEY_RIGHT },
	{ nn::hid::BUTTON_EMULATION_UP, CEmuMenuPad::KEY_UP },
    { nn::hid::BUTTON_EMULATION_DOWN, CEmuMenuPad::KEY_DOWN },
    { nn::hid::BUTTON_EMULATION_LEFT, CEmuMenuPad::KEY_LEFT },
    { nn::hid::BUTTON_EMULATION_RIGHT, CEmuMenuPad::KEY_RIGHT },
    { 0, CEmuMenuPad::NONE }
};
#else
const ButtonMap s_ButtonMap[] =
{
    { PAD_BUTTON_A, CEmuMenuPad::BUTTON_A },
    { PAD_BUTTON_B, CEmuMenuPad::BUTTON_B },
    { PAD_BUTTON_R, CEmuMenuPad::BUTTON_R },
    { PAD_BUTTON_L, CEmuMenuPad::BUTTON_L },
    { PAD_BUTTON_X, CEmuMenuPad::BUTTON_X },
    { PAD_BUTTON_Y, CEmuMenuPad::BUTTON_Y },
    { PAD_BUTTON_SELECT, CEmuMenuPad::BUTTON_SELECT },
    { PAD_BUTTON_START, CEmuMenuPad::BUTTON_START },
    { PAD_BUTTON_DEBUG, CEmuMenuPad::BUTTON_DEBUG },
    { PAD_KEY_UP, CEmuMenuPad::KEY_UP },
    { PAD_KEY_DOWN, CEmuMenuPad::KEY_DOWN },
    { PAD_KEY_LEFT, CEmuMenuPad::KEY_LEFT },
    { PAD_KEY_RIGHT, CEmuMenuPad::KEY_RIGHT },
    { 0, CEmuMenuPad::NONE }
};
#endif

#ifdef NW_PLATFORM_CTR
bool g_Initialized = false;
#endif


CEmuMenuPad::CEmuMenuPad()
: m_Button(NONE),
  m_Trigger(NONE),
  m_Release(NONE),
  m_Repeat(NONE),
  m_Lock(NONE),
  m_RepeatCount(0),
  m_StickX(0.0f),
  m_StickY(0.0f)
{
	touchtrigger = 0;
	
}

CEmuMenuPad::~CEmuMenuPad()
{
}

void
CEmuMenuPad::Initialize()
{
#ifdef NW_PLATFORM_CTR
    if (!g_Initialized)
    {
        g_Initialized = true;
        nn::Result result = nn::hid::Initialize();        
    }
#endif
}

void
CEmuMenuPad::Read()
{
    u32 prev = m_Button;
    m_Button = this->ReadButton();

	m_Lock &= m_Button;

	m_Button &= ~m_Lock;

	
    m_Trigger = static_cast<Button>(m_Button & ~prev);
    m_Release = static_cast<Button>(~m_Button & prev);
	
	if (prev != m_Button)
    {
        m_RepeatCount = 0;
    }
    else
    {
        ++m_RepeatCount;
        if (m_RepeatCount == REPEAT_CONTINUE)
        {
            m_RepeatCount = REPEAT_FIRE;
        }
    }

    m_Repeat = (m_RepeatCount == REPEAT_FIRE)? m_Button : m_Trigger;

	this->ReadPosition();

#ifdef NW_PLATFORM_CTR
	nn::hid::CTR::TouchPanelStatus tpStatus;
	nn::hid::CTR::TouchPanelReader tpReader;
	tpReader.ReadLatest(&tpStatus);

	if(tpStatus.touch == 1 && touch == 0)
		touchtrigger = 1;
	else if(tpStatus.touch == 0 && touch == 1)
		touchtrigger = 2;
	else
		touchtrigger = 0;

	touch = tpStatus.touch;
	if(touch != 0)
	{
		touch_x = tpStatus.x;
		touch_y = tpStatus.y;
	}
#else
	touch = 0;
	touch_x = 0;
	touch_y = 0;
#endif



}

CEmuMenuPad::Button
CEmuMenuPad::ReadButton()
{
#ifdef NW_PLATFORM_CTR
    nn::hid::CTR::PadReader padReader;
    nn::hid::CTR::PadStatus padStatus;

    // HIDのパッド情報を読み込み。
    padReader.ReadLatest(&padStatus);
	u32 rawButton = padStatus.hold;

#else
    u32 rawButton = PAD_Read();
#endif

    Button button = NONE;
    for (int i = 0; s_ButtonMap[i].nnBit != 0; ++i)
    {
        if (rawButton & s_ButtonMap[i].nnBit)
        {
            button = static_cast<Button>(button | s_ButtonMap[i].demoBit);
        }
    }

    return button;
}

void
CEmuMenuPad::ReadPosition()
{
    const f32 moveX = 0.02f;
    const f32 moveY = 0.02f;

    u32 button = this->GetTrigger() | this->GetRepeat();

    if (button & KEY_LEFT)
    {
        m_StickX -= moveX;
    }

    if (button & KEY_RIGHT)
    {
        m_StickX += moveX;
    }

    if (button & KEY_UP)
    {
        m_StickY -= moveY;
    }

    if (button & KEY_DOWN)
    {
        m_StickY += moveY;
    }

    m_StickX = nw::ut::Clamp(m_StickX, -1.0f, 1.0f);
    m_StickY = nw::ut::Clamp(m_StickY, -1.0f, 1.0f);
}
