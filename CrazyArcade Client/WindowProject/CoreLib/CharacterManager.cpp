#include "CharacterManager.h"
#include "Bazzi.h"
#include "Uni.h"

CharacterManager& CharacterManager::GetInstance()
{
	static CharacterManager characterSingleton;
	return characterSingleton;
}

// 생성 및 로드
int CharacterManager::Load(eHeroType heroType, HDC hOffScreenDC)
{
	if (CheckOverlap(heroType) != -1)
		return CheckOverlap(heroType);
	
	Hero* pHero = NULL;
	if (heroType == eHeroType::TypeBazzi)
	{
		SAFE_NEW(pHero, Bazzi);
	}
	else if (heroType == eHeroType::TypeUni)
	{
		SAFE_NEW(pHero, Uni);
	}

	POINT_F vPos = { 0,0 };
	pHero->SetOffScreenDC(hOffScreenDC);
	pHero->CreateHero(vPos);
	m_HeroList.insert(make_pair(m_iCount++, pHero));

	return m_iCount - 1;
}

// 중복 검사
int CharacterManager::CheckOverlap(eHeroType heroType)
{
	std::map<int, Hero*>::iterator itor;
	for (itor = m_HeroList.begin(); itor != m_HeroList.end(); itor++)
	{
		Hero* pData = itor->second;
		if (pData->GetHeroType() == heroType)
			return pData->GetHeroIndex();
	}
	return -1;
}

Hero* CharacterManager::GetPtr(int iIndex)
{
	std::map<int, Hero*>::iterator itor;
	itor = m_HeroList.find(iIndex);
	if (itor == m_HeroList.end())
		return NULL;
	Hero* pData = (*itor).second;
	return pData;
}

bool CharacterManager::Release()
{
	std::map<int, Hero*>::iterator itor;
	for (itor = m_HeroList.begin(); itor != m_HeroList.end(); itor++)
	{
		Hero *pData = (*itor).second;
		delete pData;
	}
	m_HeroList.clear();
	return true;
}

CharacterManager::CharacterManager() :m_iCount(0)
{
}


CharacterManager::~CharacterManager()
{
}
