#pragma once
#include "CoreSTD.h"

class Bitmap
{
public:
	int m_iIndex;
	T_STR m_szFileName;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	HDC m_hMemoryDC;
public:
	bool Create(int width, int height);
	// ∫Ò∆Æ∏  ∑ŒµÂ
	bool Load(DWORD dwID);
	bool Load(T_STR szLoadFile);
	bool Draw(HDC hDC, POINT_F pos, RECT rt, DWORD dwBitRaster = SRCCOPY, eRenderType iDrawType = eRenderType::STANDARD);
	bool Draw(HDC hDC, POINT_F pos, RECT rtDesk, RECT rtSource, eRenderType iDrawType = eRenderType::STANDARD);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Bitmap();
	virtual ~Bitmap();
};

