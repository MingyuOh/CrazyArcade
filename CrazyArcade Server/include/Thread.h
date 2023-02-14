#pragma once
#include "Synchronize.h"

// 스레드에서는 기본 크리티컬섹션이 멤버로 있다.
class Thread :public ServerObj
{
public:
	unsigned int m_iThreadID;
	unsigned int m_hThread;
	bool m_bStart;
public:
	virtual bool Run();
	void CreateThread();
	static unsigned int WINAPI HandleRunner(LPVOID arg);
public:
	Thread();
	virtual ~Thread();
};

