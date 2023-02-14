#include "Text.h"

void Text::SetText(HDC hOffScreenDC, T_STR szText, int x, int y)
{
	m_BackgroundColor = Color(255, 0, 0, 0);
	m_TextColor = Color(255, 255, 255, 0);
	m_Mode = TRANSPARENT;

	m_hOffScreenDC = hOffScreenDC;
	m_szText = szText;
	m_iX = x;
	m_iY = y;
}

void Text::SetText(HDC hOffScreenDC, Color backGroundColor, Color textColor, T_STR szText, int mode, int x, int y)
{
	m_hOffScreenDC = hOffScreenDC;
	m_BackgroundColor = backGroundColor;
	m_TextColor = textColor;
	m_szText = szText;
	m_Mode = mode;
	m_iX = x;
	m_iY = y;
}

bool Text::Render()
{
	_stprintf_s(m_csBuffer, L"%s", m_szText.c_str());

	SetBkColor(m_hOffScreenDC, RGB(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b));
	SetTextColor(m_hOffScreenDC, RGB(m_TextColor.r, m_TextColor.g, m_TextColor.b));
	SetBkMode(m_hOffScreenDC, m_Mode);
	
	TextOut(m_hOffScreenDC, m_iX, m_iY, m_csBuffer, wcslen(m_csBuffer));
	return true;
}

Text::Text()
{
	SAFE_ZERO(m_hOffScreenDC);
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * MAX_PATH);
	m_szText = _T("");
	m_Mode = TRANSPARENT;
	m_iX = 0;
	m_iY = 0;
}

Text::~Text()
{

}