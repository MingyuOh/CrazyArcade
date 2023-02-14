#include "ServerIOCP.h"

ServerIOCP::ServerIOCP()
{
	m_hIOCP = NULL;
}


ServerIOCP::~ServerIOCP()
{
}


bool ServerIOCP::Init()
{
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, WORKER_THREAD_COUNT);
	for (int iThread = 0; iThread < WORKER_THREAD_COUNT; iThread++)
		m_WorkerThread[iThread].CreateThread();
	return true;
}

bool ServerIOCP::Run()
{
	return true;
}

bool ServerIOCP::Release()
{
	return true;
}

void ServerIOCP::AddhandleToIOCP(HANDLE hClientSocket, ULONG_PTR pReturnKey)
{
	::CreateIoCompletionPort(hClientSocket, m_hIOCP, pReturnKey, 0);
}