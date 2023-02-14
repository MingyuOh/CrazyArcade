#include "WorkThread.h"
#include "ServerIOCP.h"
#include "Server.h"
#include "DebugString.h"

WorkThread::WorkThread()
{
	m_bLoop = true;
}

WorkThread::~WorkThread()
{
	m_bLoop = false;
}

bool WorkThread::Init()
{
	return true;
}

bool WorkThread::Run()
{
	DWORD		 bytesTransfer;
	ULONG_PTR	 keyValue;
	LPOVERLAPPED overlapped;
	BOOL		 rReturn;

	while (m_bLoop)
	{
		rReturn = ::GetQueuedCompletionStatus(I_ServerIOCP.m_hIOCP, &bytesTransfer, &keyValue, &overlapped, INFINITE);
		User* pSession = reinterpret_cast<User*>(keyValue);

		if (pSession == 0)
		{
			continue;
		}

		if (rReturn == TRUE && bytesTransfer != 0 && overlapped != 0)
		{
			pSession->Dispatch(bytesTransfer, overlapped);
		}
		else
		{
			if (keyValue != 0 && GetLastError() != ERROR_OPERATION_ABORTED)
			{
				// 소켓을 삭제 유저 삭제
				if (bytesTransfer == 0)
				{
					if (rReturn == FALSE)
					{
						cout << pSession->m_szNickName.c_str() << "비동기 소켓 오류" << endl;
					}
					// 클라이언트 접속 종료
					I_Server.DelUser(pSession->m_userServerData.m_iEvent);
					continue;
				}
			}
		}
		I_Server.ProcessPacket();
	}
	return true;
}

bool WorkThread::Release()
{
	return true;
}
