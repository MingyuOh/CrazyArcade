#pragma once
#include "Protocol.h"
class Packet
{
public:
	char m_szBuffer[2048];
	UPACKET m_uPacket;
	int m_iWritePos;
	int m_iReadPos;
public:
	Packet();
	virtual ~Packet();
};

