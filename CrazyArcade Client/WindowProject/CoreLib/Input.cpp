#include "Input.h"

Input::Input()
{
	m_bDrag = false;
}


Input::~Input()
{
}

bool Input::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);

	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);
	return true;
}

bool Input::Frame()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);

	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
		{
			if (m_dwMouseState[iButton] == KEY_PUSH)
				m_dwMouseState[iButton] = KEY_HOLD;
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP)
		{
			if (m_dwMouseState[iButton] == KEY_UP)
				m_dwMouseState[iButton] = KEY_FREE;
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}

	return true;
}

bool Input::Render() 
{
	/*TCHAR buffer[256];
	_stprintf_s(buffer, L"x = %d, y = %d \n", m_MousePos.x, m_MousePos.y);
	OutputDebugString(buffer);*/
	return true;
}

bool Input::Release()
{
	return true;
}

DWORD Input::KeyCheck(DWORD dwKey)
{
	if (g_bActiveApp == true)
	{
		SHORT sKey = GetAsyncKeyState(dwKey);
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[dwKey] == KEY_FREE)
				m_dwKeyState[dwKey] = KEY_PUSH;
			else
				m_dwKeyState[dwKey] = KEY_HOLD;
		}
		else
		{
			if (m_dwKeyState[dwKey] == KEY_PUSH || m_dwKeyState[dwKey] == KEY_HOLD)
				m_dwKeyState[dwKey] = KEY_UP;
			else
				m_dwKeyState[dwKey] = KEY_FREE;
		}
		return m_dwKeyState[dwKey];
	}
}

void Input::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEWHEEL:
	{
		m_sMouseWheelDelta = HIWORD(wParam);
	}break;
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		m_MovePt.x = x - m_DownPt.x;
		m_MovePt.y = y - m_DownPt.y;
	}break;
	case WM_LBUTTONDOWN:
	{
		m_dwMouseState[0] = KEY_PUSH;
		m_bDrag = true;
		m_DownPt.x = LOWORD(lParam);
		m_DownPt.y = HIWORD(lParam);
	}break;
	case WM_LBUTTONUP:
	{
		m_dwMouseState[0] = KEY_UP;
		m_bDrag = false;
	}break;
	case WM_MBUTTONDOWN:
	{
		m_dwMouseState[1] = KEY_PUSH;
	}break;
	case WM_MBUTTONUP:
	{
		m_dwMouseState[1] = KEY_UP;
	}break;
	case WM_RBUTTONDOWN:
	{
		m_dwMouseState[2] = KEY_PUSH;
	}break;
	case WM_RBUTTONUP:
	{
		m_dwMouseState[2] = KEY_UP;
	}break;
	}
}