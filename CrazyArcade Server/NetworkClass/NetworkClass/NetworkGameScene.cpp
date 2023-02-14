#include "NetworkGameScene.h"

bool NetworkGameScene::LoadSpawnPositionData()
{
	fopen_s(&m_fpRead, "../../data/Spawn.txt", "r");

	if (m_fpRead == nullptr)
	{
		return false;
	}

	TCHAR name[MAX_PATH] = { 0, };
	int index = 0;
	Vector2 vPos;

	while (!feof(m_fpRead))
	{
		fwscanf_s(m_fpRead, L"%s", &name, _countof(name));
		fscanf_s(m_fpRead, "%f", &vPos.x);
		fscanf_s(m_fpRead, "%f\n", &vPos.y);

		m_GameSpawnPosition.insert(make_pair(index++, make_pair(false, vPos)));
	}
	fclose(m_fpRead);
	SAFE_ZERO(m_fpRead);

	return true;
}

bool NetworkGameScene::LoadMapData()
{
	fopen_s(&m_fpRead, "../../data/Map.txt", "r");

	if (m_fpRead == nullptr)
	{
		return false;
	}
	int data = 0;
	while (!feof(m_fpRead))
	{
		fscanf_s(m_fpRead, "%d", &data);
		m_TileList.push_back(data);
	}

	fclose(m_fpRead);
	SAFE_ZERO(m_fpRead);

	return true;
}

bool NetworkGameScene::RandomSpawnItems()
{
	srand((unsigned int)time(NULL));

	vector<int> itemCountList;
	vector<int> prevInsertIndexes;
	itemCountList.resize(static_cast<size_t>(eItemType::COUNT) - 1);

	for (int iItem = 0; iItem < kItemTotalCount; iItem++)
	{
		bool bIsInsert = false;

		do
		{
			// Check duplicate index
			DWORD index = rand() % kMapTotalTileCount;
			bool bDuplicationIndex = false;
			for (auto& prevIndex : prevInsertIndexes)
			{
				if (prevIndex == index)
				{
					bDuplicationIndex = true;
					break;
				}
			}
			if (bDuplicationIndex == true)
			{
				continue;
			}

			// Insert item in tile
			if (static_cast<eTileType>(m_TileList[index]) == eTileType::BLOCK
				|| static_cast<eTileType>(m_TileList[index]) == eTileType::BOX)
			{
				eItemType itemType = GetItemType(&itemCountList);
				m_RandomSpawnItem.insert(make_pair(index, itemType));
			}
			else
			{
				continue;
			}

			prevInsertIndexes.push_back(index);
			bIsInsert = true;
		} while (bIsInsert == false);
	}

	cout << "랜덤 아이템 스폰 정보" << endl;
	cout << "(0: WATER_BALLOON, 1: WATER_POWER, 2: WATER_MAX_POWER, 3: SKATE)" << endl;
	int index = 0;
	for (auto& spawnItemInfo : m_RandomSpawnItem)
	{
		cout << "[" << index++ << "번째 아이템 정보]";
		cout << "Index: ";
		cout << spawnItemInfo.first << ", " << "ItemType: " << (DWORD)spawnItemInfo.second << endl;
	}

	return true;
}

void NetworkGameScene::ResetGameData()
{
	// Reset item spawn data
	m_RandomSpawnItem.clear();
	RandomSpawnItems();

	// Reset character spawn data
	std::map<int, pair<bool, Vector2>>::iterator iter;
	for (iter = m_GameSpawnPosition.begin();
		iter != m_GameSpawnPosition.end();
		iter++)
	{
		iter->second.first = false;
	}

	// Reset game element data
	m_bGameState = false;
	m_iClientCount = 0;
}

void NetworkGameScene::SetGameState(const bool bGameState)
{
	m_bGameState = bGameState;
}

void NetworkGameScene::SetCrashToDesktop(const bool bCrash)
{
	m_bPlayerCrashToDesktop = bCrash;
}

eItemType NetworkGameScene::GetItemType(vector<int>* itemCountList)
{
	int index = 0;
	if (itemCountList->at(index) < kItemMaxWaterBalloonCount)
	{
		itemCountList->at(index)++;
		return eItemType::WATER_BALLOON;
	}
	index++;

	if (itemCountList->at(index) < kItemMaxWaterPowerCount)
	{
		itemCountList->at(index)++;
		return eItemType::WATER_POWER;
	}
	index++;

	if (itemCountList->at(index) < kItemMaxSkateCount)
	{
		itemCountList->at(index)++;
		return eItemType::SKATE;
	}
	index++;

	if (itemCountList->at(index) < kItemMaxWaterMaxPowerCount)
	{
		itemCountList->at(index)++;
		return eItemType::WATER_MAX_POWER;
	}
}

map<int, pair<bool, Vector2>>* NetworkGameScene::GetGameSpawnPosition()
{
	return &m_GameSpawnPosition;
}

map<DWORD, eItemType>* NetworkGameScene::GetRandomSpawnItemData()
{
	return &m_RandomSpawnItem;
}

bool NetworkGameScene::GetGameState()
{
	return m_bGameState;
}

bool NetworkGameScene::GetCrashToDesktop()
{
	return m_bPlayerCrashToDesktop;
}

bool NetworkGameScene::Init()
{
	// Load spawn position data
	LoadSpawnPositionData();

	// Load map data and random spawn item 
	LoadMapData();


	return true;
}

bool NetworkGameScene::Frame()
{
	return true;
}

bool NetworkGameScene::Release()
{
	return true;
}

NetworkGameScene::NetworkGameScene()
{
	SAFE_ZERO(m_fpRead);
	m_iClientCount = 0;
	m_bGameState = false;
	m_bPlayerCrashToDesktop = false;
}

NetworkGameScene::~NetworkGameScene()
{

}