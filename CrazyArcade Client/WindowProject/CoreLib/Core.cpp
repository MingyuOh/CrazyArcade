#include "Core.h"

LRESULT Core::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return I_AsyncSelect.MsgProc(hWnd, msg, wParam, lParam);
}
bool Core::Init() 
{
	return true;
}

bool Core::Frame()
{
	return true;
}

bool Core::Render()
{
	return true;
}

bool Core::Release()
{
	return true;
}

bool Core::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	GameInit();
	while (MessageLoop() == true)
	{
		GameRun();
	}

	GameRelease();
	return true;
}

bool Core::PreRender()
{
	PatBlt(m_hOffScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, PATCOPY);
	return true;
}

bool Core::PostRender()
{
	if (g_bDebug == true)
	{
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(255, 255, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);

		TextOut(m_hOffScreenDC, 0, 0, I_Timer.m_csBuffer, wcslen(I_Timer.m_csBuffer));
	}

	BitBlt(m_hScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

bool Core::GameRun()
{
	GameNetwork();
	GameFrame();
	GameRender();
	return true;
}

bool Core::GameInit()
{
	m_hScreenDC = GetDC(g_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	HBITMAP m_hOffScreenBitMap = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);
	m_hOldBitMap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitMap);

	COLORREF bkColor = RGB(0, 0, 0);
	m_hbrBack = CreateSolidBrush(bkColor);
	m_hOldBrush = (HBRUSH)SelectObject(m_hOffScreenDC, m_hbrBack);

	m_DefaultFont = CreateFont(
		15, 0, 0, FW_THIN, 0, 0, 0, 0,
		HANGEUL_CHARSET, 3, 2, 1, 0,
		L"±Ã¼­"
	);
	SelectObject(m_hOffScreenDC, m_DefaultFont);

	I_Input.Init();
	I_Timer.Init();
	I_GameSound.Init();
	I_AsyncSelect.Init();
	Init();

	return true;
}

bool Core::GameNetwork()
{
	if (I_AsyncSelect.m_bConnect == false && g_eGameSceneState == eGameSceneState::LOBBY_SCENE)
	{
		I_AsyncSelect.Connect(kIPAdreess, 10000);
	}
	return true;
}

bool Core::GameFrame()
{
	I_Input.Frame();
	I_Timer.Frame();

	if (I_Input.KeyCheck(VK_F4) == KEY_PUSH)
	{
		g_bDebug = !g_bDebug;
	}

	Frame();
	return true;
}

bool Core::GameRender()
{
	PreRender();

	Render();
	I_Input.Render();
	I_Timer.Render();

	PostRender();
	return true;
}

bool Core::GameRelease()
{
	SelectObject(m_hOffScreenDC, m_hOldBitMap);
	SelectObject(m_hScreenDC, m_hOldBrush);
	DeleteObject(m_hbrBack);
	DeleteObject(m_DefaultFont);

	ReleaseDC(g_hWnd, m_hScreenDC);
	ReleaseDC(g_hWnd, m_hOffScreenDC);

	I_Input.Release();
	I_Timer.Release();
	Release();

	I_BitmapManager.Release();
	I_SpriteManager.Release();
	I_GameSound.Release();
	I_AsyncSelect.Release();
	return true;
}

Core::Core() 
{
	SAFE_ZERO(m_hScreenDC);
	SAFE_ZERO(m_hOffScreenDC);
	SAFE_ZERO(m_DefaultFont);
	SAFE_ZERO(m_hOldBitMap);
	SAFE_ZERO(m_hOldBrush);
	SAFE_ZERO(m_hbrBack);
}

Core::~Core() {}