#pragma once
#include "Window.h"
#include "Input.h"
#include "Timer.h"

class Core :public Window
{
public:
	Input m_Input;
	Timer m_Timer;

	HDC m_hScreenDC;
	HDC m_hOffScreenDC;
	HBRUSH m_hbrBack;
	HBRUSH m_hOldBrush;
	HBITMAP m_hOldBitMap;
	bool m_bDebug;

	HFONT m_DefaultFont;
public:
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool PreRender();
	virtual bool PostRender();

	bool Run();

private:
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
public:
	Core();
	virtual ~Core();
};

