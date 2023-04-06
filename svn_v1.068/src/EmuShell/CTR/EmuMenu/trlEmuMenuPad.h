/**
 * @file trlEmuMenuPad.h
 * @author zhfang
 * @date 2010.03.26
 * @brief trlEmuMenu Pad
 */
#pragma once

#include <nw/sdk.h>
#include <nn/hid.h>
#include <nw/math.h>

class CEmuMenuPad
{
public:
    enum Button
    {
        BUTTON_A          = 1 << 0,
        BUTTON_B          = 1 << 1,
        BUTTON_R          = 1 << 2,
        BUTTON_L          = 1 << 3,
        BUTTON_X          = 1 << 4,
        BUTTON_Y          = 1 << 5,
        BUTTON_SELECT     = 1 << 6,
        BUTTON_START      = 1 << 7,
        BUTTON_DEBUG      = 1 << 8,
        KEY_UP            = 1 << 9,
        KEY_DOWN          = 1 << 10,
        KEY_LEFT          = 1 << 11,
        KEY_RIGHT         = 1 << 12,
        NONE = 0
    };
    CEmuMenuPad();
    ~CEmuMenuPad();
    void Initialize();
    void Read();

	u32 GetMenuButton() const
	{
		return m_Button;
	}
    u32 GetButton() const
    {
        return m_Button;
    }
    u32 GetTrigger() const
    {
        return m_Trigger;
    }
    u32 GetRelease() const
    {
        return m_Release;
    }
    u32 GetRepeat() const
    {
        return m_Repeat;
    }
    const nw::math::VEC2 GetPosition() const
    {
        return nw::math::VEC2(m_StickX, m_StickY);
    }
	
	u8 GetTouchTrigger() const  //1 touch: 2:release 0:...
	{
		return touchtrigger;
	}

	u8 GetTouch() const
	{
		return touch;
	}

	u16 GetTouchX() const
	{
		return touch_x;
	}
	u16 GetTouchY() const
	{
		return touch_y;
	}

	void Lock(u32 locked)
	{
		m_Lock |= locked;

		m_Button &= ~m_Lock;
		m_Trigger &= ~m_Lock;
		m_Release &= ~m_Lock;
	}

private:
    Button ReadButton();
    void ReadPosition();

    u32 m_Button;
    u32 m_Trigger;
    u32 m_Release;
    u32 m_Repeat;
	u32 m_Lock;
    u32 m_RepeatCount;
    f32 m_StickX;
    f32 m_StickY;

	u8 touch;
	u8 touchtrigger;
	u16 touch_x;
	u16 touch_y;

    static const u32 REPEAT_FIRE = 12;
    static const u32 REPEAT_CONTINUE = REPEAT_FIRE + 2;
};
