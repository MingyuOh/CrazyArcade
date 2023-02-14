#include "Map.h"
//--------------------------------------------------------------------------------------
// Create Map
//--------------------------------------------------------------------------------------
bool Map::CreateMap()
{
	T_STR path = _T("../../data/BackGround/InGameBackGround.bmp");
	T_STR name = _T("InGameBackGround");

	// Set object distance from origin to midpoint
	SetObjectCenterLength(POINT_F(kMapMaxWidthSize * 0.5, kMapMaxHeightSize * 0.5));

	// Map boundingbox
	RECT rtMapBoundingBox;
	rtMapBoundingBox.left = kMapMinWidthSize;
	rtMapBoundingBox.top = kMapMinHeightSize;
	rtMapBoundingBox.right = kMapMinWidthSize + (kMapRealColumnLength * kObjectWidthSize);
	rtMapBoundingBox.bottom = kMapMinHeightSize + (kMapRealRowLength * kObjectWidthSize);
	GetBoundingBox().SetBoundingBoxInfo(rtMapBoundingBox);

	// Ingame background
	Create(GetOffScreenDC(), GetPosition(), g_rtClient, _T(""), path, _T(""));

	// Create tile
	CreateTileMap();

#ifdef NETWORK
	// Network create item
	NetworkCreateItemInMap();
#else
	// Create item
	CreateItemInMap();
#endif

	// Create quadtree
	CreateQuadTree();

	// Create map wireframe
	CreateWireframe();

	return true;
}

//--------------------------------------------------------------------------------------
// Create Tile Map
//--------------------------------------------------------------------------------------
bool Map::CreateTileMap()
{
	// Create map size
	m_pTileList.resize(kMapPixelCount);

	// Create tile(16 by 16 - real object : 15 by 13 )
	eTileType iTileArray[kMapPixelCount] =
	{
		eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::EMPTY, eTileType::EMPTY, eTileType::BLOCK, eTileType::EMPTY, eTileType::EMPTY, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::PILLAR, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::BOX, eTileType::BOX, eTileType::EMPTY, eTileType::BOX, eTileType::BOX, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::PILLAR, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::STATIC, eTileType::SAIL, eTileType::STATIC, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BOX, eTileType::BOX, eTileType::BOX, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::PILLAR, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::EMPTY, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::PILLAR, eTileType::BLOCK, eTileType::NONE,
		eTileType::BLOCK, eTileType::EMPTY, eTileType::EMPTY, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::BLOCK, eTileType::EMPTY, eTileType::EMPTY, eTileType::BLOCK, eTileType::NONE,
		eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE,
		eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE,
		eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE, eTileType::NONE
	};

	// Set Tiling
	int iCol = 0;
	int iRow = 0;
	int iWidth = kObjectWidthSize;
	int iHeight = kObjectHeightSize;
	POINT startPos = { kMapStartPosX, kMapStartPosY };
	POINT_F centerLength = POINT_F(kObjectWidthSize * 0.5, kObjectHeightSize * 0.5);
	for (int iMap = 0; iMap < m_pTileList.size(); iMap++)
	{
		m_pTileList[iMap] = new Tile();
		m_pTileList[iMap]->SetOffScreenDC(GetOffScreenDC());

		// Set object distance from origin to midpoint
		m_pTileList[iMap]->SetObjectCenterLength(centerLength);

		POINT_F pos;
		pos.fX = static_cast<float>(startPos.x) + centerLength.fX;
		pos.fY = static_cast<float>(startPos.y) + centerLength.fY;

		// Set Posision
		if (iCol != 0)
		{
			pos.fX = pos.fX + iCol * iWidth;
		}
		if (iRow != 0)
		{
			pos.fY = pos.fY + iRow * iHeight;
		}
		iCol++;
		m_pTileList[iMap]->SetPosition(pos);

		// Set Tile Type
		m_pTileList[iMap]->SetTileType(iTileArray[iMap]);

		// Create Tile
		m_pTileList[iMap]->CreateTile();

		// Reset column value and Increase row value
		if (iCol >= kMapMaxColumnLength)
		{
			iCol = 0;
			iRow++;
		}

		if (m_pTileList[iMap]->GetTileType() == eTileType::SAIL)
		{
			m_pPostRenderTile = m_pTileList[iMap];
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Create QuadTree Function
//--------------------------------------------------------------------------------------
bool Map::CreateQuadTree()
{
	LONG lWidth = kMapMaxWidthSize - kMapMinWidthSize;
	LONG lHeight = kMapMaxHeightSize - kMapMinHeightSize;

	bool bSucceedBuild = m_QuadTree.Build(lWidth, lHeight);
	if (bSucceedBuild == true)
	{
		m_QuadTree.SetMapTilesInfoToQuadtree(m_pTileList, m_ItemMap);
		return m_QuadTree.ConvertQuadtreeToMapTileInfo();
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Create item
//--------------------------------------------------------------------------------------
bool Map::CreateItemInMap()
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
			int index = rand() % kMapTotalTileCount;
			bool bDuplicationIndex = false;
			for (auto & prevIndex : prevInsertIndexes)
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
			if (m_pTileList[index]->GetTileType() == eTileType::BLOCK
				|| m_pTileList[index]->GetTileType() == eTileType::BOX)
			{
				eItemType itemType = Item::GetItemType(&itemCountList);
				switch (itemType)
				{
					case eItemType::WATER_BALLOON:
					{
						Item* waterBalloon = new WaterBalloon();
						waterBalloon->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
						m_pTileList.at(index)->SetExistenceItem(true);
						m_pTileList.at(index)->SetItemIndex(index);
						m_ItemMap[index] = waterBalloon;
					}break;
					case eItemType::WATER_POWER:
					{
						Item* waterPower = new WaterPower();
						waterPower->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
						m_pTileList.at(index)->SetExistenceItem(true);
						m_pTileList.at(index)->SetItemIndex(index);
						m_ItemMap[index] = waterPower;
					}break;
					case eItemType::SKATE:
					{
						Item* skate = new Skate();
						skate->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
						m_pTileList.at(index)->SetExistenceItem(true);
						m_pTileList.at(index)->SetItemIndex(index);
						m_ItemMap[index] = skate;
					}break;
					case eItemType::WATER_MAX_POWER:
					{
						Item* waterMaxPowerBalloon = new WaterMaxPower();
						waterMaxPowerBalloon->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
						m_pTileList.at(index)->SetExistenceItem(true);
						m_pTileList.at(index)->SetItemIndex(index);
						m_ItemMap[index] = waterMaxPowerBalloon;
					}break;
				}
			}
			else
			{
				continue;
			}

			prevInsertIndexes.push_back(index);
			bIsInsert = true;
		} while (bIsInsert == false);
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Create Wireframe Function
//--------------------------------------------------------------------------------------
bool Map::CreateWireframe()
{
	GetWireframe().SetDrawPointList(m_QuadTree.GetLeafNodePosition());

	return true;
}

//--------------------------------------------------------------------------------------
// Update Map
//--------------------------------------------------------------------------------------
void Map::UpdateMap()
{
	UpdateTile();
	UpdateItem();
}

//--------------------------------------------------------------------------------------
// Update Tile
//--------------------------------------------------------------------------------------
void Map::UpdateTile()
{
	// Update Tile
	for (int iMap = 0; iMap < m_pTileList.size(); iMap++)
	{
		// Delete a tile or compare tile types
		if (m_pTileList[iMap] == nullptr 
			|| m_pTileList[iMap]->GetTileType() <= eTileType::EMPTY
			|| DeleteTile(iMap) == true)
		{
			continue;
		}

		// Activates an item in the same location as the tile depending on the tile state
		ActivateItem(iMap);

		m_pTileList[iMap]->Frame();
	}
}

//--------------------------------------------------------------------------------------
// Update Item
//--------------------------------------------------------------------------------------
void Map::UpdateItem()
{
	// Update Item
	map<int, Item*>::iterator iter;
	for (iter = m_ItemMap.begin(); iter != m_ItemMap.end();)
	{
		// Deleted if item is lost by character or water balloon
		if (iter->second->GetSurvival() == false)
		{
			Item* delItem = iter->second;
			m_ItemMap.erase(iter++);
			SAFE_DEL(delItem);
		}
		else
		{
			if (iter->second->GetActivation() == true)
			{
				iter->second->Frame();
			}
			++iter;
		}
	}
}

//--------------------------------------------------------------------------------------
// Update render map
//--------------------------------------------------------------------------------------
void Map::UpdateRenderMap()
{
	UpdateRenderTile();
	UpdateRenderItem();
}

//--------------------------------------------------------------------------------------
// Update render tile
//--------------------------------------------------------------------------------------
void Map::UpdateRenderTile()
{
	// Tile Render
	for (int iMap = 0; iMap < m_pTileList.size(); iMap++)
	{
		if (m_pTileList[iMap] == nullptr 
			|| m_pTileList[iMap]->GetTileType() <= eTileType::EMPTY 
			|| m_pTileList[iMap]->GetTileType() == eTileType::SAIL)
		{
			continue;
		}
		m_pTileList[iMap]->Render();
	}
}

//--------------------------------------------------------------------------------------
// Update render item
//--------------------------------------------------------------------------------------
void Map::UpdateRenderItem()
{
	// Item Render
	for (auto& item : m_ItemMap)
	{
		if (item.second != nullptr && item.second->GetActivation())
		{
			item.second->Render();
		}
	}
}

//--------------------------------------------------------------------------------------
// Update render position
//--------------------------------------------------------------------------------------
void Map::UpdateRenderPosition()
{
	// Set boundingbox
	RECT rtMapRenderBoundingBox;
	rtMapRenderBoundingBox.left = 0;
	rtMapRenderBoundingBox.top = 0;
	rtMapRenderBoundingBox.right = g_rtClient.right;
	rtMapRenderBoundingBox.bottom = g_rtClient.bottom;

	POINT_F position;
	position.fX = 0.0f;
	position.fY = 0.0f;

	SetRenderPosition(position);
}

//--------------------------------------------------------------------------------------
// Delete tile
//--------------------------------------------------------------------------------------
bool Map::DeleteTile(int index)
{
	if (m_pTileList[index]->GetSurvival() == false)
	{
		Tile* delTile = m_pTileList[index];
		m_pTileList.erase(m_pTileList.begin() + index);
		SAFE_DEL(delTile);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Activate item
//--------------------------------------------------------------------------------------
void Map::ActivateItem(int index)
{
	// List updated according to broken tiles
	if (m_pTileList[index]->GetTileState() == true)
	{
		if (m_pTileList[index]->GetExistenceItem() == true)
		{
			int iItemIndex = m_pTileList[index]->GetItemIndex();
			if (m_ItemMap.find(iItemIndex) != m_ItemMap.end())
			{
				m_ItemMap.at(iItemIndex)->SetActivation(true);
			}
		}
	}
}

//--------------------------------------------------------------------------------------
// Set function
//--------------------------------------------------------------------------------------
void Map::InsertItemSpawnInfo(const int index, const eItemType itemType)
{
	g_ItemSpawnInfo.insert(make_pair(index, itemType));
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
vector<Tile*>& Map::GetTileList()
{
	return m_pTileList;
}

QuadTree& Map::GetQuadTree()
{
	return m_QuadTree;
}

//--------------------------------------------------------------------------------------
// Developer Redefinition Function
//--------------------------------------------------------------------------------------
bool Map::Init()
{
	// Create Map
	CreateMap();

	return true;
}

bool Map::Frame()
{
	// Ingame Map Frame
	Object::Frame();

	// Tile Update Frame
	UpdateMap();

	return true;
}

bool Map::PreRender()
{
	// Ingame map render;
	Object::Render();

	// Update map
	UpdateRenderMap();

	// Wireframe render
	GetWireframe().Render();

	return true;
}

bool Map::PostRender()
{
	assert(m_pPostRenderTile);
	m_pPostRenderTile->Render();
	return true;
}

bool Map::Release()
{
	Object::Release();

	return true;
}

//--------------------------------------------------------------------------------------
// Network
//--------------------------------------------------------------------------------------
bool Map::NetworkCreateItemInMap()
{
	map<int, eItemType>::iterator iter;
	for (iter = g_ItemSpawnInfo.begin();
		iter != g_ItemSpawnInfo.end();
		iter++)
	{
		int index = iter->first;
		eItemType itemType = iter->second;

		// Insert item in tile
		switch (itemType)
		{
			case eItemType::WATER_BALLOON:
			{
				Item* waterBalloon = new WaterBalloon();
				waterBalloon->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
				m_pTileList.at(index)->SetExistenceItem(true);
				m_pTileList.at(index)->SetItemIndex(index);
				m_ItemMap[index] = waterBalloon;
			}break;
			case eItemType::WATER_POWER:
			{
				Item* waterPower = new WaterPower();
				waterPower->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
				m_pTileList.at(index)->SetExistenceItem(true);
				m_pTileList.at(index)->SetItemIndex(index);
				m_ItemMap[index] = waterPower;
			}break;
			case eItemType::SKATE:
			{
				Item* skate = new Skate();
				skate->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
				m_pTileList.at(index)->SetExistenceItem(true);
				m_pTileList.at(index)->SetItemIndex(index);
				m_ItemMap[index] = skate;
			}break;
			case eItemType::WATER_MAX_POWER:
			{
				Item* waterMaxPowerBalloon = new WaterMaxPower();
				waterMaxPowerBalloon->CreateItem(GetOffScreenDC(), m_pTileList[index]->GetPosition());
				m_pTileList.at(index)->SetExistenceItem(true);
				m_pTileList.at(index)->SetItemIndex(index);
				m_ItemMap[index] = waterMaxPowerBalloon;
			}break;
		}
	}

	return true;
}

Map::Map()
{
	m_pPostRenderTile = nullptr;
}


Map::~Map()
{
}
