#include "Window.h"
#include "QuadTree.h"

Window *g_pWindow = NULL;
HWND g_hWnd;
HINSTANCE g_hInstance;
RECT g_rtClient;
RECT g_rtWindow;
bool g_bDebug = false;
bool g_bActiveApp = true;
bool g_bGameOver = false;
bool g_bGameStart = false;
eGameSceneState g_eGameSceneState = eGameSceneState::INTRO_SCENE;
map<int, eItemType> g_ItemSpawnInfo;

bool Window::MessageLoop()
{
	MSG msg;
	// �޼���ť�� �޼����� ������ ���
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg);// �޼��� ����
		DispatchMessage(&msg);// ���������ν��� ȣ��
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_ACTIVATEAPP:
		{
			g_bActiveApp = (BOOL)wParam; //wParam�� TRUE�� ������ Ȱ��ȭ.
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	}

	LRESULT lRet = g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


bool Window::SetWindow(HINSTANCE hInstance, TCHAR* gameName, int iX, int iY, int iWidth, int iHeight)
{
	RECT rt = { 0, 0, iWidth, iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	m_hInstance = hInstance;
	g_hInstance = hInstance;
	WNDCLASSEXW wcexw;
	wcexw.cbClsExtra = 0;
	wcexw.cbWndExtra = 0;
	wcexw.cbSize = sizeof(WNDCLASSEX);
	wcexw.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcexw.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcexw.hIcon = NULL;
	wcexw.hIconSm = NULL;
	wcexw.hInstance = m_hInstance;
	wcexw.lpfnWndProc = WndProc;
	wcexw.lpszClassName = L"GAME";
	wcexw.lpszMenuName = NULL;
	wcexw.style = CS_HREDRAW | CS_VREDRAW;

	// ������ �̷� ������ �������״� �������(�ü������)
	if (RegisterClassEx(&wcexw) == false)
	{
		cout << "������ ���� ����" << endl;
		return false;
	}

	m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"Game",
		gameName,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		iX, iY,
		rt.right - rt.left, 
		rt.bottom - rt.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
		);
	g_hWnd = m_hWnd;
	ShowWindow(m_hWnd, SW_SHOW);

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	g_rtClient = m_rtClient;
	g_rtWindow = m_rtWindow;

	return true;
}

LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

Window::Window()
{
	g_pWindow = this;
}


Window::~Window()
{
}