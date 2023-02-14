#include "Sprite.h"

bool Sprite::Load(T_STR pszFileName, T_STR pszFileMaskName)
{
	if (pszFileName.empty() == true)
	{
		return false;
	}

	m_iKey = I_BitmapManager.Load(pszFileName);
	m_pBitmap = I_BitmapManager.GetPtr(m_iKey);
	m_pBitmap->m_iIndex = m_iKey;
	if (pszFileMaskName.empty() == false)
	{
		m_iKeyMask = I_BitmapManager.Load(pszFileMaskName);
		m_pBitmapMask = I_BitmapManager.GetPtr(m_iKeyMask);
		m_pBitmapMask->m_iIndex = m_iKeyMask;
	}
	return true;
}

void Sprite::SetRectArray(vector<RECT> rtArray, int index, bool isLoop, float fLifeTime)
{
	if (m_rectList.empty() == false)
	{
		m_rectList.clear();
	}

	m_rectList = rtArray;
	m_iIndex = index;
	m_bIsLoop = isLoop;
	m_fLifeTime = fLifeTime;
	m_iFrameCount = m_rectList.size();
	m_fSecPerRender = m_fLifeTime / m_iFrameCount;
}

void Sprite::Update()
{
	m_fCurrentTime += g_fSecPerFrame;
	if (m_fCurrentTime >= m_fSecPerRender)
	{
		if (++m_iApplyIndex >= m_iFrameCount)
		{
			m_iApplyIndex = 0;
			if (m_bIsLoop == false)
			{
				AnimationFrame(m_iFrameCount - 1);
				m_rectList.clear();
			}
		}
		m_fCurrentTime = 0.0f;
	}
	AnimationFrame(m_iApplyIndex);
}

void Sprite::AnimationFrame(int iApplyIndex)
{
	if (m_rectList.empty() == false)
	{
		m_currentRect = m_rectList[iApplyIndex];
	}
}

RECT Sprite::GetDrawRect(int iUV)
{
	return m_rectList[m_iCurrentFrame];
}

//--------------------------------------------------------------------------------------
// Init
//--------------------------------------------------------------------------------------
bool Sprite::Init()
{
	return true;
}

//--------------------------------------------------------------------------------------
// Frame
//--------------------------------------------------------------------------------------
bool Sprite::Frame()
{
	Update();
	return true;
}

//--------------------------------------------------------------------------------------
// Render
//--------------------------------------------------------------------------------------
bool Sprite::Render()
{
	if (m_pBitmapMask != NULL)
	{
		m_pBitmapMask->Draw(m_hOffScreenDC, m_vObjectRenderPos, m_currentRect, SRCAND);
		m_pBitmap->Draw(m_hOffScreenDC, m_vObjectRenderPos, m_currentRect, SRCINVERT);
		m_pBitmapMask->Draw(m_hOffScreenDC, m_vObjectRenderPos, m_currentRect, SRCINVERT);
	}
	else
	{
		m_pBitmap->Draw(m_hOffScreenDC, m_vObjectRenderPos, m_currentRect, SRCCOPY);
	}
	return true;
}

Sprite::Sprite()
{
	m_iIndex = 0; 
	m_fLifeTime = 1.0f;
	m_iKey = -1;
	m_iKeyMask = -1; 
	m_fCurrentTime = 0.0f;
	m_iCurrentFrame = 0;
	m_iApplyIndex = 0;
	m_bIsLoop = false;
	m_hOffScreenDC = nullptr;
	m_pBitmap = nullptr;
	m_pBitmapMask = nullptr;
}

Sprite::~Sprite()
{
}
