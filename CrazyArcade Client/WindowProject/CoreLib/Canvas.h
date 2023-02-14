#pragma once
#include "Object.h"

class Canvas :public Object
{
private:
	T_STR		m_szCanvasName;
public:
	//--------------------------------------------------------------------------------------
	// Create Canvas
	//--------------------------------------------------------------------------------------
	bool		Create(HDC hOffScreenDC, POINT_F pos, RECT rt, T_STR szSpriteName = _T(""), T_STR szLoadFile = _T(""), T_STR szLoadMaskFile = _T("")) override;
	//--------------------------------------------------------------------------------------
	// Set function
	//--------------------------------------------------------------------------------------
	void		SetCanvasName(const T_STR szCanvasName);
	//--------------------------------------------------------------------------------------
	// Get function
	//--------------------------------------------------------------------------------------
	T_STR		GetCanvasName();
public:
	Canvas();
	~Canvas();
};

