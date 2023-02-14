#include "BitmapManager.h"

BitmapManager::BitmapManager()
{
	m_iCount = 0;
}

BitmapManager::~BitmapManager()
{
}

BitmapManager& BitmapManager::GetInstance()
{
	static BitmapManager singleton;
	return singleton;
}

bool BitmapManager::Init()
{
	return true;
}

bool BitmapManager::Frame()
{
	return true;
}

bool BitmapManager::Render()
{
	return true;
}

bool BitmapManager::Release()
{
	std::map<int, Bitmap*>::iterator itor;
	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		Bitmap *pData = (*itor).second;
		delete pData;
	}
	m_List.clear();
	return true;
}

// 생성 및 로드
int BitmapManager::Load(T_STR pszFileName)
{
	if (CheckOverlap(pszFileName) != -1)
		return CheckOverlap(pszFileName);
	
	Bitmap *pData = new Bitmap;

	if (pData->Load(pszFileName))
	{
		m_List.insert(make_pair(m_iCount++, pData));
	}

	return m_iCount - 1;
}

// 중복 검사
int BitmapManager::CheckOverlap(T_STR szFileName)
{
	std::map<int, Bitmap*>::iterator itor;
	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		Bitmap *pData = itor->second;
		if (pData->m_szFileName == szFileName.c_str())
			return pData->m_iIndex;
	}
	return -1;
}

Bitmap* BitmapManager::GetPtr(int iIndex)
{
	std::map<int, Bitmap*>::iterator itor;
	itor = m_List.find(iIndex);
	if (itor == m_List.end())
		return NULL;
	Bitmap *pBit = (*itor).second;
	return pBit;
}
