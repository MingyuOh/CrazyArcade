#pragma once
#include "Protocol.h"

class ServerObj
{
public:
	CRITICAL_SECTION m_cs;
public:
	ServerObj();
	virtual ~ServerObj();
};

