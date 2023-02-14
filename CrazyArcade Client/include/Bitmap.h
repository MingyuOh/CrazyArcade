#pragma once
#include "CoreSTD.h"

class Bitmap
{
public:
	int m_iIndex;
	T_STR m_szFileName;
	T_STR m_szMaskFileName;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	HDC m_hMemoryDC;
public:
	bool Create(int width, int height);
	// ∫Ò∆Æ∏  ∑ŒµÂ
	bool Load(DWORD dwID);
	bool Load(T_STR szLoadFile);
	bool Draw(HDC hDC, POINT_F pos, RECT rt, DWORD dwBitRaster = SRCCOPY, DRAWTYPE iDrawType = DRAWTYPE::STANDARD);
	bool Draw(HDC hDC, POINT_F pos, RECT rtDesk, RECT rtSource, DRAWTYPE iDrawType = DRAWTYPE::STANDARD);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Bitmap();
	virtual ~Bitmap();
};

