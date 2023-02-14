#include "Bitmap.h"

Bitmap::Bitmap() {}

Bitmap::~Bitmap() {}

bool Bitmap::Create(int width, int height)
{
	HDC hScreenDC = GetDC(g_hWnd);
	m_hMemoryDC = CreateCompatibleDC(hScreenDC);
	m_hBitmap = CreateCompatibleBitmap(m_hMemoryDC, width, height);
	if (m_hBitmap == NULL)
	{
		return false;
	}
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);

	ReleaseDC(g_hWnd, hScreenDC);
	return true;

}

bool Bitmap::Load(DWORD dwID)
{
	m_hBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(dwID));
	if (m_hBitmap == NULL)
	{
		return false;
	}
	HDC hScreenDC = GetDC(g_hWnd);
	m_hMemoryDC = CreateCompatibleDC(hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);

	ReleaseDC(g_hWnd, hScreenDC);
	return true;
}

bool Bitmap::Load(T_STR szLoadFile)
{
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, szLoadFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_szFileName = szLoadFile.c_str();
	if (m_hBitmap == NULL)
		return false;
	HDC hScreenDC = GetDC(g_hWnd);
	m_hMemoryDC = CreateCompatibleDC(hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);

	ReleaseDC(g_hWnd, hScreenDC);
	return true;
  }

bool Bitmap::Draw(HDC hDC, POINT_F pos, RECT rt, DWORD dwBitRaster, eRenderType iDrawType)
{
	switch (iDrawType)
	{
		case eRenderType::STANDARD:
		{
			BitBlt(hDC, static_cast<int>(pos.fX), static_cast<int>(pos.fY), rt.right, rt.bottom, m_hMemoryDC, rt.left, rt.top, dwBitRaster);
		}break;
		case eRenderType::EXPENDDRAW:
		{
			StretchBlt(hDC, pos.x, pos.y, rt.right, rt.bottom, m_hMemoryDC, rt.left, rt.top, rt.right, rt.bottom, SRCCOPY);
		}break;
		case eRenderType::CHARACTERDARW:
		{
			// Ä³¸¯ÅÍ
			BitBlt(hDC, static_cast<int>(pos.fX), static_cast<int>(pos.fY), rt.right, rt.bottom, m_hMemoryDC, rt.left, rt.top, dwBitRaster);
		}break;
	}

	return true;
}

bool Bitmap::Draw(HDC hDC, POINT_F pos, RECT rtDesk, RECT rtSource, eRenderType iDrawType)
{
	return true;
}

bool Bitmap::Init()
{
	return true;
}

bool Bitmap::Frame()
{
	return true;
}

bool Bitmap::Render()
{
	return true;
}

bool Bitmap::Release()
{
	SelectObject(m_hMemoryDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	ReleaseDC(g_hWnd, m_hMemoryDC);
	
	return true;
}