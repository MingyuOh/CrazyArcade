#pragma once
#include "Object.h"
#include "Input.h"

class Button :public Object
{
private:
	T_STR		m_szButtonName;
	bool		m_bActivate;
public:
	//--------------------------------------------------------------------------------------
	// Create button
	//--------------------------------------------------------------------------------------
	void		CreateButton(T_STR szButtonName, RECT rt);
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void		SetActivate(const bool bActivate);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	T_STR		GetButtonName();
	bool		GetActivate();
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	//--------------------------------------------------------------------------------------
	// Button event
	//--------------------------------------------------------------------------------------
	static bool	ClickButtonEvent(Button& button, POINT vCurrentMousePos);
	static bool ActiveButton(Button& button, POINT vCurrentMousePos);
public:
	Button();
	~Button();
};

