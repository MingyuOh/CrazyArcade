#include "ServerObj.h"

ServerObj::ServerObj()
{
	InitializeCriticalSection(&m_cs);
}


ServerObj::~ServerObj()
{
	DeleteCriticalSection(&m_cs);
}
