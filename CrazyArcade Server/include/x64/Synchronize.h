#pragma once
#include "ServerObj.h"

class Synchronize
{
public:
	ServerObj* m_pObj;
public:
	Synchronize(ServerObj* pObj);
	virtual ~Synchronize();
};

