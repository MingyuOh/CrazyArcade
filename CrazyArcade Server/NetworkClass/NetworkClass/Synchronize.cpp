#include "Synchronize.h"

Synchronize::Synchronize(ServerObj* pObj)
{
	m_pObj = pObj;
	if (pObj != NULL)
		EnterCriticalSection(&m_pObj->m_cs);
}


Synchronize::~Synchronize()
{
	if (m_pObj != NULL)
		LeaveCriticalSection(&m_pObj->m_cs);
}
