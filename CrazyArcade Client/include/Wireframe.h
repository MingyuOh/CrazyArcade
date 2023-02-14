#pragma once
#include "CoreSTD.h"
#include "BitmapManager.h"

class Wireframe
{
private:
	HDC				m_hOffScreenDC;			// Back screen buffer
	vector<RECT>	m_rtDrawPointList;		// Wireframe rect informaition
	HGDIOBJ			m_objOriginal;			// Using pen
	Bitmap*			m_pBitmap;				// Bitmap
	bool			m_bActiveWireframe;		// Current wireframe state
	DWORD			m_dwWidth;				// Wireframe width size
	DWORD			m_dwHeight;				// Wireframe height size
public:
	//--------------------------------------------------------------------------------------
	// Create Function
	//--------------------------------------------------------------------------------------
	void			Create(DWORD width, DWORD height);
	//--------------------------------------------------------------------------------------
	// Init Function
	//--------------------------------------------------------------------------------------
	bool			Init();
	//--------------------------------------------------------------------------------------
	// Render Function
	//--------------------------------------------------------------------------------------
	bool			Render();
	//--------------------------------------------------------------------------------------
	// Release Function
	//--------------------------------------------------------------------------------------
	bool			Release();
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void			SetOffScreenDC(HDC hScreenDC);
	void			SetDrawPointList(vector<RECT> rtDrawPointList);
	void			SetDrawPointList(RECT rtDrawPoint);
	void			SetPenColor(COLORREF rgb);
	void			SetActiveWireframe(bool isActive);
	void			SetWidthSize(DWORD width);
	void			SetHeightSize(DWORD height);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	HDC				GetOffScreenDC();
	vector<RECT>&	GetDrawPointList();
	DWORD			GetWidthSize();
	DWORD			GetHeightSize();
	bool			GetActiveWireframe();
private:
	//--------------------------------------------------------------------------------------
	// Draw Function
	//--------------------------------------------------------------------------------------
	void			Draw();
public:
	Wireframe();
	Wireframe(HDC hdc);
	~Wireframe();
};
