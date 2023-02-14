#pragma once
#include "ServerObj.h"
#include "WorkThread.h"

#define WORKER_THREAD_COUNT 4

class ServerIOCP :public Singleton<ServerIOCP>, public ServerObj
{
private:
	friend class Singleton<ServerIOCP>;
public:
	HANDLE m_hIOCP;
	WorkThread m_WorkerThread[WORKER_THREAD_COUNT];
public:
	bool		Init();
	bool		Run();
	bool		Release();
	void		AddhandleToIOCP(HANDLE hClientSocket, ULONG_PTR pReturnKey);
public:
	ServerIOCP();
	virtual ~ServerIOCP();
};
#define I_ServerIOCP ServerIOCP::GetInstance()
