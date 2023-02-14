#include "Thread.h"

Thread::Thread()
{
	m_iThreadID = 0;
	m_bStart = false;
	m_hThread = 0;
}


Thread::~Thread()
{
	// accept°¡ Á×À¸¸é ½º·¹µåµµ ¼Ò¸ê
	CloseHandle((HANDLE)m_hThread);
}

bool Thread::Run()
{
	return true;
}

unsigned int WINAPI Thread::HandleRunner(LPVOID arg)
{
	Thread* pThread = (Thread*)arg;
	if (pThread != NULL)
		pThread->Run();
	return 0;
}

void Thread::CreateThread()
{
	if (m_bStart == true)
	{
		return;
	} 

	m_hThread = _beginthreadex(NULL, 0, HandleRunner, this, 0, &m_iThreadID);
	m_bStart = true;
}
