#pragma once
#include "AsyncSelect.h"

class Window
{
public:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	RECT m_rtClient;
	RECT m_rtWindow;
	HBRUSH m_hbrOldBlueBack;
public:
	bool MessageLoop();
	bool SetWindow(HINSTANCE hInstance, TCHAR* gameName, int iX = 0, int iY = 0, int iWidth = 800, int iHeight = 600);
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Window();
	virtual ~Window();
};

