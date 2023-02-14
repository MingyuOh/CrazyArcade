#pragma once
#include "Protocol.h"
#include "Timer.h"

class Network
{
public:
	SOCKET m_Sock;
	bool m_bConnect;
	char m_szRecvBuffer[MAX_BUFFER_SIZE];
	int m_iRecvByte;
	int m_iStartByte;
	unsigned int m_hThread;
	unsigned int m_ThreadID;
	CRITICAL_SECTION m_cs;
public:
	list<LOBBY_PACKET>	m_LobbyPacketPool;
	list<GAME_PACKET>	m_GamePacketPool;
public:
	//--------------------------------------------------------------------------------------
	// Connect
	//--------------------------------------------------------------------------------------
	virtual bool		Connect(char* ip, int iPort);
	//--------------------------------------------------------------------------------------
	// Send
	//--------------------------------------------------------------------------------------
	int					SendEventMessage(WORD type);
	int					SendChatMessage(TCHAR* msg, WORD type);
	int					SendChatMessage(SOCKET sock, TCHAR* msg, WORD type);
	int					SendReady(bool bReady, int playerNumber, WORD type);
	int					SendCharacterPosition(eDirection direction, int spriteIndex, POINT_F vPos);
	int					SendAttack(POINT_F vPos, int iWaterBombPower);
	int					SendPlayerGetItem(POINT_F vPos, DWORD index);
	int					SendPlayerDead(int iDeadPlayerNumber);
	int					SendPlayerDrop();
	//--------------------------------------------------------------------------------------
	// Receive
	//--------------------------------------------------------------------------------------
	int					RecvMsg();
	static int			recvn(SOCKET sock, char* buf, int len, int flags);
	//--------------------------------------------------------------------------------------
	// Check the transmission time to the network.
	//--------------------------------------------------------------------------------------
	bool				CheckNetworkTransmissionTime();
	//--------------------------------------------------------------------------------------
	// Message event
	//--------------------------------------------------------------------------------------
	virtual void		MsgEvent(MSG msg) {};
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Release();
public:
	Network();
	virtual ~Network();
};

