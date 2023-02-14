#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_iObjectCount = 0;
}

ObjectManager::~ObjectManager()
{
}

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager objSingleton;
	return objSingleton;
}

int ObjectManager::Load(Object* obj)
{
	std::map<int, Object*>::iterator itor;
	if (CheckOverlap(obj->GetObjectName()) != -1)
	{
		return CheckOverlap(obj->GetObjectName());
	}
	Object* pData = new Object;
	pData = obj;

	m_objectList.insert(make_pair(m_iObjectCount++, pData));

	return m_iObjectCount - 1;
}

int ObjectManager::CheckOverlap(T_STR objName)
{
	std::map<int, Object*>::iterator itor;
	for (itor = m_objectList.begin(); itor != m_objectList.end(); itor++)
	{
		Object* pData = itor->second;
		if (pData->GetObjectName() == objName)
		{
			return pData->GetObjectIndex();
		}
	}
	return -1;
}

Object* ObjectManager::GetPtr(int iIndex)
{
	std::map<int, Object*>::iterator itor;
	itor = m_objectList.find(iIndex);
	if (itor == m_objectList.end())
	{
		return nullptr;
	}
	Object* pBit = itor->second;
	return pBit;
}

bool ObjectManager::Release()
{
	std::map<int, Object*>::iterator itor;
	for (itor = m_objectList.begin(); itor != m_objectList.end(); itor++)
	{
		Object* rData = itor->second;
		delete rData;
	}
	m_objectList.clear();
	return true;
}