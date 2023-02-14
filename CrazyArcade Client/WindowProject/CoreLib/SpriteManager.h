#pragma once
#include "Sprite.h"
#include "CoreSTD.h"

class SpriteManager
{
public:
	map<DWORD, Sprite*>			m_spriteList;
	int							m_iFrameCount;
	int							m_iCount;
public:
	static SpriteManager&		GetInstance();
	void						FileLoad();
	int							CheckOverlap(T_STR spriteName);
	Sprite*						GetPtr(int iIndex);
	int							LoadSprite(T_STR spriteName);
	bool						Release();
public:
	SpriteManager();
	~SpriteManager();
};
#define I_SpriteManager SpriteManager::GetInstance()
