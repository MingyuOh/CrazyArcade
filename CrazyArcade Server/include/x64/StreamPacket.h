#pragma once
#include "Protocol.h"
#define MAX_RECV_SIZE 10000

class StreamPacket
{
public:
	std::list<LOBBY_PACKET>	m_LobbyPacketList;
	std::list<GAME_PACKET>	m_GamePacketList;
	char m_RecvBuffer[MAX_RECV_SIZE];
	LOBBY_PACKET*	m_pLobbyPacketData;
	GAME_PACKET*	m_pGamePacketData;
	int m_iWritePos;
	int	m_iReadPos;
	int m_iStartPos;
public:
	void PutLobbyData(char* data, DWORD dwBytes, User* pUser);
	void PutGameData(char* data, DWORD dwBytes, User* pUser);
public:
	StreamPacket();
	~StreamPacket();
};

