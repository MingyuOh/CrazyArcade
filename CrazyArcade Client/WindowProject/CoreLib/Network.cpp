#include "Network.h"

//--------------------------------------------------------------------------------------
// Connect
//--------------------------------------------------------------------------------------
bool Network::Connect(char* ip, int iPort)
{
	SOCKADDR_IN server;
	ZeroMemory(&server, sizeof(SOCKADDR_IN));
	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);
	server.sin_addr.s_addr = inet_addr(ip);

	DWORD dwRet = connect(m_Sock, (sockaddr*)&server, sizeof(SOCKADDR_IN));
	if (dwRet == SOCKET_ERROR)
	{
		// 비동기 정상 반환 = WSAEWOULDBLOCK
		if (WSAGetLastError() != WSAEWOULDBLOCK)
			return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Send
//--------------------------------------------------------------------------------------
int	Network::SendEventMessage(WORD type)
{
	PACKET_HEADER sendEvent;
	ZeroMemory(&sendEvent, PACKET_HEADER_SIZE);

	sendEvent.type = type;
	sendEvent.len = PACKET_HEADER_SIZE;

	int iResult = send(m_Sock, (char*)&sendEvent, sendEvent.len, 0);
	return iResult;
}

int Network::SendChatMessage(SOCKET sock, TCHAR* msg, WORD type)
{
	LOBBY_PACKET sendMessage;
	ZeroMemory(&sendMessage, sizeof(LOBBY_PACKET));

	sendMessage.data.ph.type = type;
	wcscpy_s(sendMessage.data.chatData.msg, msg);
	sendMessage.data.ph.len = sizeof(sendMessage);

	int iResult = send(sock, (char*)&sendMessage, sendMessage.data.ph.len, 0);
	return iResult;
}

int Network::SendChatMessage(TCHAR* msg, WORD type)
{
	LOBBY_PACKET sendMessage;
	ZeroMemory(&sendMessage, sizeof(LOBBY_PACKET));

	sendMessage.data.ph.type = type;
	wcscpy_s(sendMessage.data.chatData.msg, msg);
	sendMessage.data.ph.len = sizeof(sendMessage);

	int iResult = send(m_Sock, (char*)&sendMessage, sendMessage.data.ph.len, 0);
	return iResult;
}

int	Network::SendReady(bool bReady, int playerNumber, WORD type)
{
	LOBBY_PACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(LOBBY_PACKET));

	sendmsg.data.ph.type = type;
	sendmsg.data.ph.len = sizeof(LOBBY_PACKET);
	sendmsg.data.ready = bReady;
	_itoa(playerNumber, &sendmsg.data.playerNumber, 10);

	int iResult = send(m_Sock, (char*)&sendmsg, sendmsg.data.ph.len, 0);
	return iResult;
}

int Network::SendCharacterPosition(eDirection direction, int spriteIndex, POINT_F vPos)
{	
	if (CheckNetworkTransmissionTime() == false)
	{
		return -1;
	}

	USER_POSITION userPos;
	userPos.direction = static_cast<WORD>(direction);
	userPos.spriteIndex = spriteIndex;
	userPos.posX = vPos.fX;
	userPos.posY = vPos.fY;

	GAME_PACKET sendMsg;
	ZeroMemory(&sendMsg, sizeof(sendMsg));

	sendMsg.data.ph.type = PACKET_MOVE_CHARACTER;
	sendMsg.data.ph.len = sizeof(GAME_PACKET);
	memcpy(&sendMsg.data.userData.userPos, &userPos, sizeof(USER_POSITION));

	int iResult = send(m_Sock, (char*)&sendMsg, sendMsg.data.ph.len, 0);
	return iResult;
}

int Network::SendAttack(POINT_F vPos, int iWaterBombPower)
{
	ATTACK_INFO attackInfo;
	attackInfo.waterBombPower = static_cast<WORD>(iWaterBombPower);
	attackInfo.posX = vPos.fX;
	attackInfo.posY = vPos.fY;

	GAME_PACKET sendMsg;
	ZeroMemory(&sendMsg, sizeof(sendMsg));

	sendMsg.data.ph.type = PACKET_ATTACK;
	sendMsg.data.ph.len = sizeof(GAME_PACKET);
	memcpy(&sendMsg.data.userData.attack_info, &attackInfo, sizeof(ATTACK_INFO));

	int iResult = send(m_Sock, (char*)&sendMsg, sendMsg.data.ph.len, 0);
	return iResult;
}

int	Network::SendPlayerGetItem(POINT_F vPos, DWORD index)
{
	ITEM_INFO itemInfo;
	itemInfo.itemIndex = index;
	itemInfo.itemPosX = vPos.fX;
	itemInfo.itemPosY = vPos.fY;

	GAME_PACKET sendMsg;
	ZeroMemory(&sendMsg, sizeof(sendMsg));

	sendMsg.data.ph.type = PACKET_PLAYER_GET_ITEM;
	sendMsg.data.ph.len = sizeof(GAME_PACKET);
	memcpy(&sendMsg.data.gameData.itemData, &itemInfo, sizeof(ITEM_INFO));

	int iResult = send(m_Sock, (char*)&sendMsg, sendMsg.data.ph.len, 0);
	return iResult;
}

int	Network::SendPlayerDead(int iDeadPlayerNumber)
{
	GAME_PACKET sendMsg;
	ZeroMemory(&sendMsg, sizeof(sendMsg));

	sendMsg.data.ph.type = PACKET_GAME_OVER;
	sendMsg.data.ph.len = sizeof(GAME_PACKET);
	_itoa(iDeadPlayerNumber, &sendMsg.data.gameData.deadPlayerNumber, 10);

	int iResult = send(m_Sock, (char*)&sendMsg, sendMsg.data.ph.len, 0);
	return iResult;
}

int	Network::SendPlayerDrop()
{
	EVENT_PACKET sendMsg;
	ZeroMemory(&sendMsg, sizeof(sendMsg));

	_itoa(g_iPlayerNumber, sendMsg.eventData, 10);
	sendMsg.ph.type = PACKET_USER_DROP;
	sendMsg.ph.len = PACKET_HEADER_SIZE + strlen(sendMsg.eventData);

	int iResult = send(m_Sock, (char*)&sendMsg, sendMsg.ph.len, 0);
	return iResult;
}

//--------------------------------------------------------------------------------------
// Receive
//--------------------------------------------------------------------------------------
int Network::recvn(SOCKET sock, char *buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(sock, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

int Network::RecvMsg()
{
	int iRecvByte = 0;
	int iStartByte = 0;
	char szRecvBuffer[MAX_BUFFER_SIZE] = { 0, };
	ZeroMemory(szRecvBuffer, sizeof(char) * MAX_BUFFER_SIZE);

	int iLen = 0;
	iLen = recv(m_Sock, &szRecvBuffer[iStartByte], PACKET_HEADER_SIZE - iRecvByte, 0);
	iRecvByte += iLen;

	if (iLen == SOCKET_ERROR)
	{
		iRecvByte = 0;
		return -1;
	}

	switch (g_eGameSceneState)
	{
		case eGameSceneState::LOBBY_SCENE:
		{
			LOBBY_PACKET* pPacket = (LOBBY_PACKET*)&szRecvBuffer;
			// 헤더부분 도착
			if (iRecvByte == PACKET_HEADER_SIZE)
			{
				iRecvByte += recvn(m_Sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
			}
			else // 헤더 일부분 도착
			{
				int iAddRecvByte = PACKET_HEADER_SIZE - iRecvByte;
				recvn(m_Sock, szRecvBuffer, iAddRecvByte, 0);
				iRecvByte += recvn(m_Sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
			}
			pPacket = (LOBBY_PACKET*)&szRecvBuffer;
			iStartByte = iRecvByte = 0;
			m_LobbyPacketPool.push_back(*pPacket);
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			GAME_PACKET* pPacket = (GAME_PACKET*)&szRecvBuffer;
			// 헤더부분 도착
			if (iRecvByte == PACKET_HEADER_SIZE)
			{
				iRecvByte += recvn(m_Sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
			}
			else // 헤더 일부분 도착
			{
				int iAddRecvByte = PACKET_HEADER_SIZE - iRecvByte;
				recvn(m_Sock, szRecvBuffer, iAddRecvByte, 0);
				iRecvByte += recvn(m_Sock, &szRecvBuffer[PACKET_HEADER_SIZE], pPacket->data.ph.len - PACKET_HEADER_SIZE, 0);
			}
			pPacket = (GAME_PACKET*)&szRecvBuffer;
			iStartByte = iRecvByte = 0;
			m_GamePacketPool.push_back(*pPacket);
		}break;
	}
	return 0;
}

//--------------------------------------------------------------------------------------
// Check the transmission time to the network.
//--------------------------------------------------------------------------------------
bool Network::CheckNetworkTransmissionTime()
{
	if (I_Timer.m_dwElapsedFixedTick < FIXED_FRAME_COUNT)
	{
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Developer redefinition function
//--------------------------------------------------------------------------------------
bool Network::Init()
{
	WSADATA wsa;
	int error = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (error != 0)
	{
		cout << "Failed WSAStartup" << endl;
		return false;
	}
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET)
		return false;
	return true;
}

bool Network::Frame()
{
	return true;
}

bool Network::Release()
{
	SendPlayerDrop();
	DeleteCriticalSection(&m_cs);
	CloseHandle((HANDLE)m_hThread);
	closesocket(m_Sock);
	WSACleanup();
	return true;
}

Network::Network()
{
	m_iRecvByte = 0;
	m_iStartByte = 0;
	m_bConnect = false;
	ZeroMemory(m_szRecvBuffer, sizeof(char) * MAX_BUFFER_SIZE);
	InitializeCriticalSection(&m_cs);
}

Network::~Network()
{
}
