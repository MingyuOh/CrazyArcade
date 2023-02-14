#pragma once
#include "Protocol.h"
#define MAX_RECV_SIZE 10000

class StreamPacket
{
public:
	std::list<PACKET> m_PacketList;
	typedef std::list<PACKET>::iterator m_PackItor;
	char m_RecvBuffer[MAX_RECV_SIZE]; // ��Ʈ�� ��Ŷ�� ���۰� ũ�� �ϳ������� �־�� �Ѵ�.
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

