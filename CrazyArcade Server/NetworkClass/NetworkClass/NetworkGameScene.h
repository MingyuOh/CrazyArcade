#pragma once
#include "Constant.h"
#include "User.h"

class NetworkGameScene : public Singleton<NetworkGameScene>
{
private:
	friend class Singleton<NetworkGameScene>;
private:
	FILE*								m_fpRead;
	std::map<int, pair<bool, Vector2>>	m_GameSpawnPosition;
	std::vector<int>					m_TileList;
	std::map<DWORD, eItemType>			m_RandomSpawnItem;
	bool								m_bGameState;
	bool								m_bPlayerCrashToDesktop;
public:
	int									m_iClientCount;
private:
	bool								LoadSpawnPositionData();
	bool								LoadMapData();
	bool								RandomSpawnItems();
public:
	void								ResetGameData();
	void								SetGameState(const bool bGameState);
	void								SetCrashToDesktop(const bool bCrash);

	eItemType							GetItemType(vector<int>* itemCountList);
	map<DWORD, eItemType>*				GetRandomSpawnItemData();
	map<int, pair<bool, Vector2>>*		GetGameSpawnPosition();
	bool								GetGameState();
	bool								GetCrashToDesktop();

	bool								Init();
	bool								Frame();
	bool								Release();
public:
	NetworkGameScene();
	~NetworkGameScene();
};
#define I_NetworkGameScene NetworkGameScene::GetInstance()
