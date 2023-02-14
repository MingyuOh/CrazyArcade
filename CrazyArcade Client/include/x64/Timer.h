#pragma once
#include "CoreSTD.h"

class Timer :public Singleton<Timer>
{
private:
	friend class Singleton<Timer>;
public:
	float	m_fElapseTick;
	float	m_fFrameTime;
	DWORD	m_dwFPS;
	DWORD	m_dwCurrentTick;
	DWORD	m_dwBeforeTick;
	DWORD	m_dwFrameCount;
	DWORD	m_dwBeforeFixedTick;
	DWORD	m_dwElapsedFixedTick;
	TCHAR	m_csBuffer[MAX_PATH];
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	FixedFrame();
public:
	Timer();
	~Timer();
};
#define I_Timer Timer::GetInstance()
