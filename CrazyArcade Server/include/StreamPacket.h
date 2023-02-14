#pragma once
#include "Protocol.h"
#define MAX_RECV_SIZE 10000

class StreamPacket
{
public:
	std::list<PACKET> m_PacketList;
	typedef std::list<PACKET>::iterator m_PackItor;
	char m_RecvBuffer[MAX_RECV_SIZE]; // 스트림 패킷의 버퍼가 크게 하나정도는 있어야 한다.
	UPACKET* m_pPacketData;
	UPACKET	m_PacketData;
	int m_iWritePos;
	int	m_iReadPos;
	int m_iStartPos;
public:
	void Put(char* data, DWORD dwBytes, User* pUser);
public:
	StreamPacket();
	~StreamPacket();
};

