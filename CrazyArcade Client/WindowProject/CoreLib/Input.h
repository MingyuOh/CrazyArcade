#pragma once
#include "CoreSTD.h"

enum Key_State
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD
};

class Input :public Singleton<Input>
{
private:
	friend class Singleton<Input>;
public:
	// Ű����
	DWORD m_dwKeyState[256];
	// ���콺
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;
	short m_sMouseWheelDelta;
	bool m_bDrag;
	POINT m_DownPt;
	POINT m_MovePt;
	bool m_bActiveApp;
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
#define I_Input Input::GetInstance()
