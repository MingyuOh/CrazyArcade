#include "User.h"
#include "Server.h"

User::User()
{
	m_szNickName = _T("");
}

User::~User()
{

}

void User::Dispatch(DWORD dwBytes, LPOVERLAPPED ov)
{
	if (dwBytes == 0)
		return;
	OVERLAPPEDEX* pOv = (OVERLAPPEDEX*)ov;
	if (pOv->m_iFlag == OVERLAPPEDEX::MODE_RECV)
	{
		switch (I_Server.m_eGameSceneState)
		{
		case eGameSceneState::LOBBY_SCENE:
		{
			this->m_userServerData.m_Stream.PutLobbyData(m_userServerData.m_wsaBuffer.buf, dwBytes, this);
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			this->m_userServerData.m_Stream.PutGameData(m_userServerData.m_wsaBuffer.buf, dwBytes, this);
		}break;
		}
		
	}
	WaitForPacketRecv();
}

void User::WaitForPacketRecv()
{
	DWORD cbTransfered;
	DWORD flags = 0;
	m_userServerData.m_ov.m_iFlag = OVERLAPPEDEX::MODE_RECV;
	m_userServerData.m_wsaBuffer.buf = m_userServerData.m_strBuffer;
	m_userServerData.m_wsaBuffer.len = 4096;
	int iRet = WSARecv(this->m_userServerData.m_Socket, &m_userServerData.m_wsaBuffer, 1, &cbTransfered, &flags, (LPOVERLAPPED)&m_userServerData.m_ov, NULL);
	if (iRet == SOCKET_ERROR)
	{
		if (GetLastError() != WSA_IO_PENDING)
		{
			exit(1);
		}
	}
}