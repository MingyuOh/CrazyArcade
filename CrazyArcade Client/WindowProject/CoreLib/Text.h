#pragma once
#include "CoreSTD.h"

typedef struct _color
{
	int r;
	int g;
	int b;
	int a;

	_color()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	_color(int r, int g, int b, int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
}Color;

class Text
{
public:
	HDC		m_hOffScreenDC;
	TCHAR	m_csBuffer[MAX_PATH];
	T_STR	m_szText;
	Color	m_BackgroundColor;
	Color	m_TextColor;
	int		m_Mode;
	int		m_iX;
	int		m_iY;
public:
	void	SetText(HDC hOffScreenDC, T_STR szText, int x, int y);
	void	SetText(HDC hOffScreenDC, Color backGroundColor, Color textColor, T_STR szText, int mode, int x, int y);
	bool	Render();
public:
	Text();
	~Text();
};

