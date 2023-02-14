#include "AsyncSelect.h"
#include "LobbyScene.h"
#include "GameScene.h"

bool AsyncSelect::Connect(T_STR ip, int iPort)
{
	int iResult = WSAAsyncSelect(m_Sock, g_hWnd, NETWORK_MSG, FD_CONNECT | FD_READ | FD_CLOSE);
	if (iResult == SOCKET_ERROR)
	{
		return false;
	}

	SOCKADDR_IN server;
	ZeroMemory(&server, sizeof(SOCKADDR_IN));
	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);
	server.sin_addr.s_addr = inet_addr(wtm(ip).c_str());

	int iRet = WSAConnect(m_Sock, (sockaddr*)&server, sizeof(server), NULL, NULL, NULL, NULL);
	if (iRet == SOCKET_ERROR)
	{
		// 비동기 정상 반환 = WSAEWOULDBLOCK
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}
	return true;
}

bool AsyncSelect::Frame()
{
	switch (g_eGameSceneState)
	{
		case eGameSceneState::LOBBY_SCENE:
		{
			for (auto& packet : m_LobbyPacketPool)
			{
				switch (packet.data.ph.type)
				{
					case PACKET_CHAT_MSG:
					{
						int index = SendMessageW(I_LobbyScene.m_hListBoxList[0], LB_ADDSTRING, 0, (LPARAM)packet.data.chatData.msg);
						::SendMessageW(I_LobbyScene.m_hListBoxList[0], LB_SETCURSEL, index, 0);
						::SendMessageW(I_LobbyScene.m_hListBoxList[0], LB_SETCURSEL, -1, 0);
					}break;
					case PACKET_LOBBY_READY:
					{
						
					}break;
				}
			}
			m_LobbyPacketPool.clear();
		}break;
	}
	return true;
}

unsigned int WINAPI AsyncSelect::RecvThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	bool bConnect = true;
	int iRecvByte = 0;
	int iStartByte = 0;
	char szRecvBuffer[MAX_BUFFER_SIZE] = { 0, };
	ZeroMemory(szRecvBuffer, sizeof(char) * MAX_BUFFER_SIZE);

	while (bConnect == true)
	{
		int iLen = 0;
		ZeroMemory(szRecvBuffer, sizeof(char) * MAX_BUFFER_SIZE);
		iLen = recv(sock, &szRecvBuffer[iStartByte], PACKET_HEADER_SIZE - iRecvByte, 0);
		iRecvByte += iLen;
		if (iLen == 0)
		{
			bConnect = false;
			break;
		}
		if (iLen == SOCKET_ERROR)
		{
			iRecvByte = 0;
			continue;
		}
		switch (g_eGameSceneState)
		{
			case eGameSceneState::LOBBY_SCENE:
			{
				LOBBY_PACKET* pPacket = (LOBBY_PACKET*)&szRecvBuffer;
				// 헤더부분 도착
				if (iRecvByte == PACKET_HEADER_SIZE)
				{
					iRecvByte += recvn(sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
				}
				else // 헤더 일부분 도착
				{
					int iAddRecvByte = PACKET_HEADER_SIZE - iRecvByte;
					recvn(sock, szRecvBuffer, iAddRecvByte, 0);
					iRecvByte += recvn(sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
				}
				pPacket = (LOBBY_PACKET*)&szRecvBuffer;
				iStartByte = iRecvByte = 0;
				I_AsyncSelect.m_LobbyPacketPool.push_back(*pPacket);
			}break;
			case eGameSceneState::GAME_SCENE:
			{
				GAME_PACKET* pPacket = (GAME_PACKET*)&szRecvBuffer;
				// 헤더부분 도착
				if (iRecvByte == PACKET_HEADER_SIZE)
				{
					iRecvByte += recvn(sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
				}
				else // 헤더 일부분 도착
				{
					int iAddRecvByte = PACKET_HEADER_SIZE - iRecvByte;
					recvn(sock, szRecvBuffer, iAddRecvByte, 0);
					iRecvByte += recvn(sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
				}
				pPacket = (GAME_PACKET*)&szRecvBuffer;
				iStartByte = iRecvByte = 0;
				I_AsyncSelect.m_GamePacketPool.push_back(*pPacket);
			}break;
		}
	}
	return 0;
}

LRESULT AsyncSelect::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case NETWORK_MSG:
		{
			if (WSAGETSELECTERROR(lParam) != 0)
			{
				MessageBox(g_hWnd, L"접속 종료", L"종료", MB_OK);
				PostQuitMessage(0);
				return S_FALSE;
			}
			WORD dwSelect = WSAGETSELECTEVENT(lParam);
			switch (dwSelect)
			{
				case FD_CONNECT:
				{
					m_bConnect = true;
				}break;
				case FD_CLOSE:
				{
					m_bConnect = false;
				}break;
				case FD_READ:
				{
					RecvMsg();
				}break;
			}
		}
	}
	return S_OK;
}

AsyncSelect::AsyncSelect()
{
}


AsyncSelect::~AsyncSelect()
{
}