#pragma once
#include "Thread.h"

class WorkThread :public Thread
{
public:
	bool m_bLoop;
public:
	bool Init();
	bool Run();
	bool Release();
public:
	WorkThread();
	virtual ~WorkThread();
};

