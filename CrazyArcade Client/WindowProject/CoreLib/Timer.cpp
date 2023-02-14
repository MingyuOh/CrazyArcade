#include "Timer.h"
float g_fSecPerFrame = 0;

bool Timer::Init()
{
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * MAX_PATH);
	m_dwBeforeTick = timeGetTime();
	m_dwBeforeFixedTick = timeGetTime();
	return true;
}

bool Timer::Frame()
{
	m_dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = m_dwCurrentTick - m_dwBeforeTick;

	g_fSecPerFrame = dwElapseTick / 1000.0f;
	m_fFrameTime += g_fSecPerFrame;
	m_fElapseTick += g_fSecPerFrame;

	if (m_fFrameTime >= 1.0f)
	{
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fFrameTime -= 1.0f;
	}

	m_dwFrameCount++;

	m_dwBeforeTick = m_dwCurrentTick;

	FixedFrame();

	return true;
}

bool Timer::Render()
{
	_stprintf_s(m_csBuffer, L"경과시간 = %10.4f, FPS = %d %10.4f", m_fElapseTick, m_dwFPS, g_fSecPerFrame);
	return true;
}

bool Timer::Release()
{
	return true;
}

bool Timer::FixedFrame()
{
	m_dwElapsedFixedTick = m_dwCurrentTick - m_dwBeforeFixedTick;

	if (m_dwElapsedFixedTick >= FIXED_FRAME_COUNT)
	{
		m_dwBeforeFixedTick = m_dwCurrentTick - (m_dwElapsedFixedTick - FIXED_FRAME_COUNT);
		return true;
	}
	return false;
}

Timer::Timer()
{
	m_dwFPS = 0;
	m_fFrameTime = 0.0f;
	m_fElapseTick = 0.0f;

	m_dwCurrentTick = 0;
	m_dwBeforeTick = 0;
	m_dwFrameCount = 0;

	m_dwBeforeFixedTick = 0;
	m_dwElapsedFixedTick = 0;
}

Timer::~Timer() 
{

}