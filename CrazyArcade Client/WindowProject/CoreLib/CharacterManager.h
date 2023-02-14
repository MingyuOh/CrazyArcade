#pragma once
#include "Hero.h"

class CharacterManager 
{
private:
	map<int, Hero*>				m_HeroList;			// Hero list
	int							m_iCount;			// Hero list count
public:
	static CharacterManager&	GetInstance();
	// ���� �� �ε�
	int							Load(eHeroType heroType, HDC hOffScreenDC);
	// �ߺ� �˻�
	int							CheckOverlap(eHeroType heroType);
	Hero*						GetPtr(int iIndex);
	bool						Release();
private:
	CharacterManager();
	virtual ~CharacterManager();
};
#define I_CharacterManager CharacterManager::GetInstance()