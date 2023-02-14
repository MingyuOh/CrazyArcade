#include "Button.h"

//--------------------------------------------------------------------------------------
// Create button
//--------------------------------------------------------------------------------------
void Button::CreateButton(T_STR szButtonName, RECT rt)
{
	m_szButtonName = szButtonName;
	GetBoundingBox().SetBoundingBoxInfo(rt);
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void Button::SetActivate(const bool bActivate)
{
	m_bActivate = bActivate;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
T_STR Button::GetButtonName()
{
	return m_szButtonName;
}

bool Button::GetActivate()
{
	return	m_bActivate;
}

//--------------------------------------------------------------------------------------
// Developer redefinition function
//--------------------------------------------------------------------------------------
bool Button::Init()
{
	return true;
}

bool Button::Frame()
{
	return true;
}

bool Button::Render()
{
	return true;
}

bool Button::Release()
{
	return true;
}

//--------------------------------------------------------------------------------------
// Button event
//--------------------------------------------------------------------------------------
bool Button::ClickButtonEvent(Button& button, POINT vCurrentMousePos)
{
	if (ActiveButton(button, vCurrentMousePos) == true)
	{
		if (I_Input.GetInstance().m_dwMouseState[0] == Key_State::KEY_PUSH)
		{
			I_GameSound.Play(static_cast<int>(eGameSoundList::CLICK), false, false);
			return true;
		}
	}
	return false;
}

bool Button::ActiveButton(Button& button, POINT vCurrentMousePos)
{
	if (button.GetCollision().RectToPoint(button.GetBoundingBox().GetBoundingBoxInfo(), vCurrentMousePos))
	{
		if (button.GetActivate() == false)
		{
			I_GameSound.Play(static_cast<int>(eGameSoundList::POINT_RECT), false, false);
			button.SetActivate(true);
			return true;
		}
		return true;
	}
	else
	{
		button.SetActivate(false);
	}
	return false;
}

Button::Button()
{
	m_szButtonName = _T("");
	m_bActivate = false;
}

Button::~Button()
{

}