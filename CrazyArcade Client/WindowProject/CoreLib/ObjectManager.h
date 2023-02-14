#pragma once
#include "Object.h"

class ObjectManager
{
private:
	map<int, Object*>		m_objectList;
	int						m_iObjectCount;
public:
	static ObjectManager&	GetInstance();
	int						Load(Object* obj);
	int						CheckOverlap(T_STR objName);
	Object*					GetPtr(int iIndex);
	bool					Release();
private:
	ObjectManager();
	virtual ~ObjectManager();
};
#define I_ObjManager ObjectManager::GetInstance()
