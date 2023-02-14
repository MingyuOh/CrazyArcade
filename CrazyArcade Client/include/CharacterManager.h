#pragma once
#include "Hero.h"

class CharacterManager 
{
private:
	map<int, Hero*>				m_HeroList;			// Hero list
	int							m_iCount;			// Hero list count
public:
	static CharacterManager&	GetInstance();
	// 생성 및 로드
	int							Load(HERO_TYPE heroType, HDC hOffScreenDC);
	// 중복 검사
	int							CheckOverlap(HERO_TYPE heroType);
	Hero*						GetPtr(int iIndex);
	bool						Release();
private:
	CharacterManager();
	virtual ~CharacterManager();
};
#define I_CharacterManager CharacterManager::GetInstance()