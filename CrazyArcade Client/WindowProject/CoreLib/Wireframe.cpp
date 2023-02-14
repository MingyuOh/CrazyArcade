#include "Wireframe.h"

Wireframe::Wireframe()
{
	Init();
}

Wireframe::Wireframe(HDC hdc) : m_hOffScreenDC(hdc) 
{
	Init();
}

Wireframe::~Wireframe()
{
	Release();
}

//--------------------------------------------------------------------------------------
// Create Function
//--------------------------------------------------------------------------------------
void Wireframe::Create(DWORD width, DWORD height)
{
	SetWidthSize(width);
	SetHeightSize(height);
	m_pBitmap = new Bitmap();
	m_pBitmap->Create(static_cast<int>(m_dwWidth), static_cast<int>(m_dwHeight));
}

//--------------------------------------------------------------------------------------
// Draw Function
//--------------------------------------------------------------------------------------
void Wireframe::Draw()
{
	HGDIOBJ original = NULL;
	original = SelectObject(m_hOffScreenDC, GetStockObject(DC_PEN));
	SetDCPenColor(m_hOffScreenDC, RGB(255, 0, 255));

	for (int index = 0; index < m_rtDrawPointList.size(); index++)
	{
		MoveToEx(m_hOffScreenDC, m_rtDrawPointList[index].left, m_rtDrawPointList[index].top, NULL);
		LineTo(m_hOffScreenDC, m_rtDrawPointList[index].right, m_rtDrawPointList[index].top);
		LineTo(m_hOffScreenDC, m_rtDrawPointList[index].right, m_rtDrawPointList[index].bottom);
		LineTo(m_hOffScreenDC, m_rtDrawPointList[index].left, m_rtDrawPointList[index].bottom);
		LineTo(m_hOffScreenDC, m_rtDrawPointList[index].left, m_rtDrawPointList[index].top);
	}
	DeleteObject(original);
}

//--------------------------------------------------------------------------------------
// Init Function
//--------------------------------------------------------------------------------------
bool Wireframe::Init()
{
	m_hOffScreenDC = NULL;
	m_rtDrawPointList.clear();
	m_dwWidth = -1;
	m_dwHeight = -1;

	return true;
}

//--------------------------------------------------------------------------------------
// Render Function
//--------------------------------------------------------------------------------------
bool Wireframe::Render()
{
	if (g_bDebug == true)
	{
		Draw();
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Release Function
//--------------------------------------------------------------------------------------
bool Wireframe::Release()
{
	m_hOffScreenDC = NULL;
	m_rtDrawPointList.clear();
	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void Wireframe::SetOffScreenDC(HDC hScreenDC)
{
	m_hOffScreenDC = hScreenDC;
}
void Wireframe::SetDrawPointList(vector<RECT> rtDrawPointList)
{
	m_rtDrawPointList = rtDrawPointList;
}
void  Wireframe::SetDrawPointList(RECT rtDrawPoint)
{
	m_rtDrawPointList.push_back(rtDrawPoint);
}

void Wireframe::SetPenColor(COLORREF rgb)
{
	SetDCPenColor(m_hOffScreenDC, rgb);
}
void Wireframe::SetWidthSize(DWORD width)
{
	m_dwWidth = width;
}

void Wireframe::SetHeightSize(DWORD height)
{
	m_dwHeight = height;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
HDC	Wireframe::GetOffScreenDC()
{
	return m_hOffScreenDC;
}
vector<RECT>& Wireframe::GetDrawPointList()
{
	return m_rtDrawPointList;
}

DWORD Wireframe::GetWidthSize()
{
	return m_dwWidth;
}

DWORD Wireframe::GetHeightSize()
{
	return m_dwHeight;
}