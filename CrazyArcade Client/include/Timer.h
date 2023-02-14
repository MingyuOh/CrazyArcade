#pragma once
#include "CoreSTD.h"

class Timer
{
public:
	float m_fElapseTick;
	float m_fFrameTime;
	DWORD m_dwFPS;
	
	DWORD m_dwBeforeTick;
	DWORD m_dwFrameCount;
	TCHAR m_csBuffer[MAX_PATH];
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Timer();
	~Timer();
};

