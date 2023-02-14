#include "SpriteManager.h"

SpriteManager::SpriteManager() :m_iCount(0), m_iFrameCount(0)
{
}


SpriteManager::~SpriteManager()
{
}


SpriteManager& SpriteManager::GetInstance()
{
	static SpriteManager spriteSingleton;
	return spriteSingleton;
}

// 중복 체크
int SpriteManager::CheckOverlap(T_STR spriteName)
{
	std::map<DWORD, Sprite*>::iterator itor;
	for (itor = m_spriteList.begin(); itor != m_spriteList.end(); itor++)
	{
		Sprite* pData = itor->second;
		if (wcscmp(pData->m_szSpriteName, spriteName.c_str()) == 0)
		{
			return pData->m_iIndex;
		}
	}
	return -1;
}

// 파일 전체 로드
void SpriteManager::FileLoad()
{
	FILE* fpRead = NULL;
	fopen_s(&fpRead, "../../data/Sprites.txt", "r");

	TCHAR tmpName[MAX_PATH] = {0, };
	RECT rect = { 0, };
	if (fpRead == NULL)
	{
		return;
	}

	while (1)
	{
		Sprite* pData = new Sprite();
		fwscanf_s(fpRead, L"%s", tmpName, _countof(tmpName));
		fscanf_s(fpRead, "%d", &pData->m_iFrameCount);
		fscanf_s(fpRead, "%d\n", &pData->m_bIsLoop);

		if (pData->m_iFrameCount == 0)
		{
			delete pData;
			break;
		}
		wcscpy_s(pData->m_szSpriteName, tmpName);

		for (int iCnt = 0; iCnt < pData->m_iFrameCount; iCnt++)
		{
			if (fscanf_s(fpRead, "%d %d %d %d\n", &rect.left, &rect.top, &rect.right, &rect.bottom) != EOF)
			{
				pData->m_rectList.push_back(rect);
			}
		}
		// 인덱스 저장
		pData->m_iIndex = m_iCount;
		m_spriteList.insert(make_pair(m_iCount++, pData));
	}

	fclose(fpRead);
}

Sprite* SpriteManager::GetPtr(int iIndex)
{
	std::map<DWORD, Sprite*>::iterator itor;
	itor = m_spriteList.find(iIndex);
	if (itor == m_spriteList.end())
	{
		return NULL;
	}
	Sprite* pSprite = itor->second;
	return pSprite;
}

int SpriteManager::LoadSprite(T_STR spriteName)
{
	if (CheckOverlap(spriteName.c_str()) != -1)
	{
		return CheckOverlap(spriteName);
	}
	return m_iCount - 1;
}

bool SpriteManager::Release()
{
	return true;
}