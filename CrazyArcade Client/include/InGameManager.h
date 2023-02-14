#pragma once
#include "WaterBomb.h"
#include "Map.h"
#include "Hero.h"

class InGameManager
{
public:
	vector<WaterBomb>	waterBombList;
	shared_ptr<Map>		pMap;
	shared_ptr<Hero>	player1;
	shared_ptr<Hero>	player2;
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
public:
	InGameManager();
	~InGameManager();
};
#define I_InGameManager InGameManager::GetInstance()
