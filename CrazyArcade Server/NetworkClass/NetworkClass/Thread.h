#pragma once
#include "Synchronize.h"

// �����忡���� �⺻ ũ��Ƽ�ü����� ����� �ִ�.
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

