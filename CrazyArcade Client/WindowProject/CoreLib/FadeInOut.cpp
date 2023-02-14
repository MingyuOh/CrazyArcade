#include "FadeInOut.h"
#include <wingdi.h>

//--------------------------------------------------------------------------------------
// Fade in
//--------------------------------------------------------------------------------------
bool FadeInOut::FadeIn()
{
	if (m_bFadeIn == true)
	{
		m_fAlpha -= g_fSecPerFrame * FADE_SPEED;
		if (m_fAlpha <= MIN_ALPHA_VALUE)
		{
			m_fAlpha = MIN_ALPHA_VALUE;
			m_bFadeIn = !m_bFadeIn;
			m_bFadeOut = !m_bFadeOut;
			PatBlt(m_hOffScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, BLACKNESS);
			return true;
		}
		m_Blend.SourceConstantAlpha = static_cast<BYTE>(m_fAlpha);
		Render();
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Fade out
//--------------------------------------------------------------------------------------
bool FadeInOut::FadeOut()
{
	if (m_bFadeOut == true)
	{
		m_fAlpha += g_fSecPerFrame * FADE_SPEED;
		if (m_fAlpha >= MAX_ALPHA_VALUE)
		{
			m_fAlpha = MAX_ALPHA_VALUE;
			m_bFadeIn = !m_bFadeIn;
			m_bFadeOut = !m_bFadeOut;
			PatBlt(m_hOffScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, BLACKNESS);
			return true;
		}
		m_Blend.SourceConstantAlpha = static_cast<BYTE>(m_fAlpha);
		Render();
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Fade in and out
//--------------------------------------------------------------------------------------
bool FadeInOut::FadeInAndOut()
{
	if (FadeIn() == true)
	{
		FadeOut();
		if (m_bFadeOut == false)
		{
			m_fAlpha = MIN_ALPHA_VALUE;
			m_bFadeIn = !m_bFadeIn;
			m_bFadeOut = !m_bFadeOut;
			PatBlt(m_hOffScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, BLACKNESS);
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Create fade in-out elements
//--------------------------------------------------------------------------------------
bool FadeInOut::Create()
{
	m_Bitmap.Create(g_rtClient.right, g_rtClient.bottom);
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_OVER;
	m_Blend.SourceConstantAlpha = m_fAlpha;

	return true;
}

//--------------------------------------------------------------------------------------
// Developer Redefinition Function
//--------------------------------------------------------------------------------------
bool FadeInOut::Render()
{
	AlphaBlend(
		m_hOffScreenDC,
		0, 0,
		g_rtClient.right, g_rtClient.bottom,
		m_Bitmap.m_hMemoryDC,
		0, 0,
		g_rtClient.right, g_rtClient.bottom,
		m_Blend);
	return true;
}

bool FadeInOut::Release()
{
	m_Bitmap.Release();
	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void FadeInOut::SetOffScreenDC(HDC hOffScreenDC)
{
	m_hOffScreenDC = hOffScreenDC;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
bool FadeInOut::GetFadeIn()
{
	return m_bFadeIn;
}

bool FadeInOut::GetFadeOut()
{
	return m_bFadeOut;
}

FadeInOut::FadeInOut()
{
	m_hOffScreenDC = nullptr;
	m_bFadeIn = true;
	m_bFadeOut = false;
	m_fAlpha = 255.0f;
	m_bToggle = false;
}

FadeInOut::~FadeInOut()
{
}