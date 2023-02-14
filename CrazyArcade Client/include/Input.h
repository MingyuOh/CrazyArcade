#pragma once
#include "CoreSTD.h"

enum Key_State
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD
};

class Input
{
public:
	// 키보드
	DWORD m_dwKeyState[256];
	// 마우스
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;
	short m_sMouseWheelDelta;
	bool m_bDrag;
	POINT m_DownPt;
	POINT m_MovePt;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	DWORD KeyCheck(DWORD dwKey);
	Input();
	~Input();
};

