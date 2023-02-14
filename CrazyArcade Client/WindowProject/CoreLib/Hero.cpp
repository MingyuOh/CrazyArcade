#include "Hero.h"

//--------------------------------------------------------------------------------------
// Create visual item and ui sprites
//--------------------------------------------------------------------------------------
void Hero::CreateVisualSprites()
{
	Sprite arrowSprite;
	arrowSprite.m_iKey = I_SpriteManager.LoadSprite(_T("Arrow"));
	arrowSprite = *I_SpriteManager.GetPtr(arrowSprite.m_iKey);
	arrowSprite.m_hOffScreenDC = GetOffScreenDC();
	arrowSprite.Load(_T("../../data/UI/Arrow.bmp"), _T("../../data/UI/ArrowMask.bmp"));
	m_VisualSprites.push_back(arrowSprite);
}

//--------------------------------------------------------------------------------------
// Move
//--------------------------------------------------------------------------------------
void Hero::Move()
{
	// Get the current location node in the quadtree.
	Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(GetPosition());

	// Move hero
	MoveUp(pNode);
	MoveDown(pNode);
	MoveLeft(pNode);
	MoveRight(pNode);

	// Set previous node
	m_pPrevNode = pNode;
}

bool Hero::MoveUp(Node* pNode)
{
	if (I_Input.KeyCheck(VK_UP))
	{
		// Hero up
		Up();

		// Hero boundingBox Update
		UpdateBoundingBox();

		// Update quadtree
		RECT rtCollisiontNode = pNode->GetCorner();
		rtCollisiontNode.top -= kObjectHeightSize;
		rtCollisiontNode.bottom -= kObjectHeightSize;
		rtCollisiontNode.left -= kObjectWidthSize;
		rtCollisiontNode.right -= kObjectWidthSize;

		// Collision Tile
		if (CollisionCharacterToObject(rtCollisiontNode, eDirection::UP))
		{
			Down();
			UpdateBoundingBox();
		}

		// Collision Map
		if (GetCollision().CollisionMap(m_pMap->GetBoundingBox().GetBoundingBoxInfo(), GetBoundingBox().GetBoundingBoxInfo()) == MAP_BOUNDARY::UP)
		{
			Down();
			UpdateBoundingBox();
		}

		// Update quadtree
		pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(GetPosition());
		if (pNode != m_pPrevNode)
		{
			m_pMap->GetQuadTree().UpdateQuadTree((Object*)this, m_pPrevNode->GetCorner(), pNode->GetCorner());
		}

#ifdef NETWORK
		// Network action
		I_AsyncSelect.SendCharacterPosition(eDirection::UP, GetSprite()->m_iApplyIndex, GetPosition());
#endif
		return true;
	}
	return false;
}

bool Hero::MoveDown(Node* pNode)
{
	if (I_Input.KeyCheck(VK_DOWN))
	{
		// Hero down
		Down();

		// Hero boundingBox Update
		UpdateBoundingBox();

		// Update quadtree
		RECT rtCollisiontNode = pNode->GetCorner();
		rtCollisiontNode.top += kObjectHeightSize;
		rtCollisiontNode.bottom += kObjectHeightSize;
		rtCollisiontNode.left -= kObjectWidthSize;
		rtCollisiontNode.right -= kObjectWidthSize;

		// Collision Tile
		if (CollisionCharacterToObject(rtCollisiontNode, eDirection::DOWN))
		{
			Up();
			UpdateBoundingBox();
		}

		// Collision Map
		if (GetCollision().CollisionMap(m_pMap->GetBoundingBox().GetBoundingBoxInfo(), GetBoundingBox().GetBoundingBoxInfo()) == MAP_BOUNDARY::DOWN)
		{
			Up();
			UpdateBoundingBox();
		}

		// Update quadtree
		pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(GetPosition());
		if (pNode != m_pPrevNode)
		{
			m_pMap->GetQuadTree().UpdateQuadTree((Object*)this, m_pPrevNode->GetCorner(), pNode->GetCorner());
		}

#ifdef NETWORK
		// Network action
		I_AsyncSelect.SendCharacterPosition(eDirection::DOWN, GetSprite()->m_iApplyIndex, GetPosition());
#endif
		return true;
	}
	return false;
}

bool Hero::MoveLeft(Node* pNode)
{
	if (I_Input.KeyCheck(VK_LEFT))
	{
		// Hero left
		Left();

		// Hero boundingBox Update
		UpdateBoundingBox();

		// Update quadtree
		RECT rtCollisiontNode = pNode->GetCorner();
		rtCollisiontNode.top -= kObjectHeightSize;
		rtCollisiontNode.bottom -= kObjectHeightSize;
		rtCollisiontNode.left -= kObjectWidthSize;
		rtCollisiontNode.right -= kObjectWidthSize;

		// Collision Tile
		if (CollisionCharacterToObject(rtCollisiontNode, eDirection::LEFT))
		{
			Right();
			UpdateBoundingBox();
		}

		// Collision Map
		if (GetCollision().CollisionMap(m_pMap->GetBoundingBox().GetBoundingBoxInfo(), GetBoundingBox().GetBoundingBoxInfo()) == MAP_BOUNDARY::LEFT)
		{
			Right();
			UpdateBoundingBox();
		}

		pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(GetPosition());
		if (pNode != m_pPrevNode)
		{
			m_pMap->GetQuadTree().UpdateQuadTree((Object*)this, m_pPrevNode->GetCorner(), pNode->GetCorner());
		}

#ifdef NETWORK
		// Network action
		I_AsyncSelect.SendCharacterPosition(eDirection::LEFT, GetSprite()->m_iApplyIndex, GetPosition());
#endif
		return true;
	}
	return false;
}

bool Hero::MoveRight(Node* pNode)
{
	if (I_Input.KeyCheck(VK_RIGHT))
	{
		// Hero right
		Right();

		// Hero boundingBox Update
		UpdateBoundingBox();

		// Update quadtree
		RECT rtCollisiontNode = pNode->GetCorner();
		rtCollisiontNode.top -= kObjectHeightSize;
		rtCollisiontNode.bottom -= kObjectHeightSize;
		rtCollisiontNode.left += kObjectWidthSize;
		rtCollisiontNode.right += kObjectWidthSize;

		// Collision object
		if (CollisionCharacterToObject(rtCollisiontNode, eDirection::RIGHT))
		{
			Left();
			UpdateBoundingBox();
		}

		// Collision Map
		if (GetCollision().CollisionMap(m_pMap->GetBoundingBox().GetBoundingBoxInfo(), GetBoundingBox().GetBoundingBoxInfo()) == MAP_BOUNDARY::RIGHT)
		{
			Left();
			UpdateBoundingBox();
		}

		pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(GetPosition());
		if (pNode != m_pPrevNode)
		{
			m_pMap->GetQuadTree().UpdateQuadTree((Object*)this, m_pPrevNode->GetCorner(), pNode->GetCorner());
		}

#ifdef NETWORK
		// Network action
		I_AsyncSelect.SendCharacterPosition(eDirection::RIGHT, GetSprite()->m_iApplyIndex, GetPosition());
#endif
		return true;
	}
	return false;
}

void Hero::Up()
{
	POINT_F vPos;
	vPos.fX = GetPosition().fX;
	vPos.fY = GetPosition().fY - (m_fHeroSpeed * g_fSecPerFrame);
	SetPosition(vPos);
}

void Hero::Down()
{
	POINT_F vPos;
	vPos.fX = GetPosition().fX;
	vPos.fY = GetPosition().fY + (m_fHeroSpeed * g_fSecPerFrame);
	SetPosition(vPos);
}

void Hero::Right()
{
	POINT_F vPos;
	vPos.fX = GetPosition().fX + (m_fHeroSpeed * g_fSecPerFrame);
	vPos.fY = GetPosition().fY;
	SetPosition(vPos);
}

void Hero::Left()
{
	POINT_F vPos;
	vPos.fX = GetPosition().fX - (m_fHeroSpeed * g_fSecPerFrame);
	vPos.fY = GetPosition().fY;
	SetPosition(vPos);
}

//--------------------------------------------------------------------------------------
// Attack
//--------------------------------------------------------------------------------------
void Hero::Attack()
{
	if (I_Input.KeyCheck(VK_SPACE) == KEY_PUSH)
	{
		if (m_iWaterBombCount <= m_WaterBombList.size() || GetSurvival() == false)
		{
			return;
		}

		Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(this->GetPosition());
		for (const auto& object : pNode->GetObjectList())
		{
			if (object->GetObjectType() == OBJECT_TYPE::WATER_BOMB)
			{
				return;
			}
		}

		// Play sound
		I_GameSound.Play(static_cast<int>(eGameSoundList::BOMB_SET), true, false);

		WaterBomb* addWaterBomb = new WaterBomb();
		addWaterBomb->SetOffScreenDC(GetOffScreenDC());													// Set offscreenDC
		addWaterBomb->SetDrawType(eRenderType::CHARACTERDARW);											// Set rendertype
		addWaterBomb->CreateWaterBomb(pNode->GetPos(), m_iWaterBombPower, &m_pMap->GetQuadTree());		// Create waterbomb
		m_WaterBombList.push_back(addWaterBomb);														// Insert waterbomb

		m_pMap->GetQuadTree().AddInQuadTree(pNode, (Object*)addWaterBomb);								// Insert waterbomb in QuadTree

#ifdef NETWORK
		// Network action
		I_AsyncSelect.SendAttack(pNode->GetPos(), m_iWaterBombPower);
#endif
	}
}

//--------------------------------------------------------------------------------------
// Collision function
//--------------------------------------------------------------------------------------
bool Hero::CollisionCharacterToObject(RECT rtCollisiontNode, eDirection eDirection)
{
	for (int iLoop = 0; iLoop < 3; iLoop++)
	{
		RECT rtCollision = rtCollisiontNode;
		switch (eDirection)
		{
			case eDirection::UP:
			case eDirection::DOWN:
			{
				rtCollision.left += kObjectWidthSize * iLoop;
				rtCollision.right += kObjectWidthSize * iLoop;
			}break;
			case eDirection::LEFT:
			case eDirection::RIGHT:
			{
				rtCollision.top += kObjectHeightSize * iLoop;
				rtCollision.bottom += kObjectHeightSize * iLoop;
			}break;
		}

		Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(rtCollision);
		if (pNode != nullptr)
		{
			vector<Object*> objectList = pNode->GetObjectList();
			for (int index = 0; index < objectList.size(); index++)
			{
				Object* object = objectList[index];
				// 자기 자신 또는 (현재 위치에서 물풍선을 놓았을때) 충돌처리 하지 않는다.
				if (object == this || (pNode == m_pPrevNode && object->GetObjectType() == OBJECT_TYPE::WATER_BOMB))
				{
					continue;
				}

				if (GetCollision().RectToRect(GetBoundingBox().GetBoundingBoxInfo(), object->GetBoundingBox().GetBoundingBoxInfo()))
				{

					switch (object->GetObjectType())	
					{
						case OBJECT_TYPE::HERO:
						{
							// Collsion another player caught in the trap
							return CollisionCharacterToCharacter(pNode, object, index);
						}
						case OBJECT_TYPE::ITEM:
						{
							// Collision item
							return CollisionCharacterToItem(pNode, object, index);
						}
						case OBJECT_TYPE::WATER_BOMB:
						case OBJECT_TYPE::TILE:
						case OBJECT_TYPE::STATIC_OBJECT:
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
	//return bResult;
}

bool Hero::CollisionCharacterToCharacter(Node* pNode, Object* object, int index)
{
	if (object->GetSurvival() == false)
	{
		I_GameSound.Play(static_cast<int>(eGameSoundList::PLAYER_DIE), true, false);
		Hero* pHero = static_cast<Hero*>(object);
		pHero->m_bIsDead = true;
		pNode->DeleteObjectInNode(object);
#ifdef NETWORK
		I_AsyncSelect.SendPlayerDead(pHero->GetID());
		m_bActivation = false;
#endif // NETWORK
	}
	return false;

}

bool Hero::CollisionCharacterToItem(Node* pNode, Object* object, int index)
{
	// Does not collide with items when character is trapped in a trap
	if (GetSurvival() == false && pNode->GetTileType() == eTileType::EMPTY)
	{
		return false;
	}

	Item* item = static_cast<Item*>(object);
	if (item->GetActivation() == true)
	{
		// Play sound
		I_GameSound.Play(static_cast<int>(eGameSoundList::EAT_ITEM), true, false);

		// Delte item in quadtree
		pNode->DeleteObjectInNode(object);

#ifdef NETWORK
		I_AsyncSelect.SendPlayerGetItem(pNode->GetPos(), index);
#endif // NETWORK

		switch (item->GetItemType())
		{
			case eItemType::WATER_BALLOON:
			{
				if (m_iWaterBombCount < kHeroMaxWaterBombCount)
				{
					m_iWaterBombCount += 1;
				}
			}break;
			case eItemType::WATER_POWER:
			{
				if (m_iWaterBombPower < kHeroMaxWaterPowerCount)
				{
					m_iWaterBombPower += 1;
				}
			}break;
			case eItemType::WATER_MAX_POWER:
			{
				m_iWaterBombPower = kHeroMaxWaterPowerCount;
			}break;
			case eItemType::SKATE:
			{
				if (m_iSpeedCount < kHeroMaxSpeedCount)
				{
					m_iSpeedCount += 1;
					m_fHeroSpeed = m_fHeroSpeed + 3.0f * m_iSpeedCount;
				}
			}break;
		}
		object->SetSurvival(false);
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void Hero::SetHeroType(eHeroType heroType)
{
	m_HeroType = heroType;
}

void Hero::SetHeroIndex(int iIndex)
{
	m_iIndex = iIndex;
}

void Hero::SetHeroSpeed(float fSpeed)
{
	m_fHeroSpeed = fSpeed;
}

void Hero::SetMap(Map* pMap)
{
	m_pMap = pMap;
}

void Hero::SetWaterBombCount(int iWaterBombCount)
{
	m_iWaterBombCount = iWaterBombCount;
}

void Hero::SetDead(const bool bIsDead)
{
	m_bIsDead = bIsDead;
}

void Hero::SetMotionSprite(const Sprite newSprtie)
{
	m_MotionSprites.push_back(newSprtie);
}

void Hero::SetLobbyPosition(const POINT_F vPos)
{
	SetPosition(vPos);
}

void Hero::SetPreviousNode(Node* pNode)
{
	if (pNode != nullptr)
	{
		m_pPrevNode = pNode;
	}
}

void Hero::SetID(const int id)
{
	m_iHeroID = id;
}

void Hero::SetActivation(const bool bActivation)
{
	m_bActivation = bActivation;
}

void Hero::SetUserData(User* pUserData)
{
	m_pUserData = pUserData;
}

void Hero::InsertWaterBomb(WaterBomb* pWaterBomb)
{
	m_WaterBombList.push_back(pWaterBomb);
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
int Hero::GetHeroIndex()
{
	return m_iIndex;
}

eHeroType Hero::GetHeroType()
{
	return m_HeroType;
}

float Hero::GetHeroSpeed()
{
	return m_fHeroSpeed;
}

int	Hero::GetWaterBombCount()
{
	return m_iWaterBombCount;
}

POINT_F Hero::GetLobbyPosition()
{
	return GetPosition();
}

bool Hero::GetDead()
{
	return m_bIsDead;
}

Node* Hero::GetPreviousNode()
{
	return m_pPrevNode;
}

int	Hero::GetID()
{
	return m_iHeroID;
}

bool Hero::GetActivation()
{
	return m_bActivation;
}

User* Hero::GetUserData()
{
	return m_pUserData;
}

//--------------------------------------------------------------------------------------
// Update Method
//--------------------------------------------------------------------------------------
bool Hero::UpdateFrame()
{
	switch (g_eGameSceneState)
	{
		case eGameSceneState::LOBBY_SCENE:
		{
			UpdateRenderPosition();
			m_MotionSprites[static_cast<size_t>(eHeroMotionType::WAIT)].m_vObjectRenderPos = GetRenderPosition();
			m_MotionSprites[static_cast<size_t>(eHeroMotionType::WAIT)].Frame();
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			if (g_bGameStart == false)
			{
				UpdateRenderPosition();
				m_MotionSprites[static_cast<size_t>(eHeroMotionType::READY)].m_vObjectRenderPos = GetRenderPosition();
				m_MotionSprites[static_cast<size_t>(eHeroMotionType::READY)].Frame();
			}
			else
			{
				if (GetSurvival() == false)
				{
					if (m_bIsDead == true)
					{
						m_MotionSprites[static_cast<size_t>(eHeroMotionType::DEAD)].m_vObjectRenderPos = GetRenderPosition();
						if (m_MotionSprites[static_cast<size_t>(eHeroMotionType::DEAD)].m_rectList.empty() == true)
						{
							g_bGameOver = true;
						}
						else
						{
							m_MotionSprites[static_cast<size_t>(eHeroMotionType::DEAD)].Frame();
						}
					}
					else
					{
						UpdateRenderPosition();
						m_MotionSprites[static_cast<size_t>(eHeroMotionType::TRAP)].m_vObjectRenderPos = GetRenderPosition();
						m_fHeroSpeed = kHeroBazziSpeed / 4.0f;
						m_fLifeTime += g_fSecPerFrame;
						if (m_fLifeTime >= kHeroTrapLifeTime)
						{
							I_GameSound.Play(static_cast<int>(eGameSoundList::PLAYER_DIE), true, false);
							m_bIsDead = true;
#ifdef NETWORK
							I_AsyncSelect.SendPlayerDead(m_iHeroID);
#endif //NETWORK
						}
						else
						{
							m_MotionSprites[static_cast<size_t>(eHeroMotionType::TRAP)].Frame();
						}
					}
				}
				else
				{
					Object::Frame();
				}

				// Waterbomb
				UpdateWaterBomb();
			}

		
#ifdef NETWORK
			if (m_iHeroID == g_iPlayerNumber && g_bGameOver == false)
			{
				for (auto& visualSprite : m_VisualSprites)
				{
					POINT_F vPos;
					vPos.fX = GetRenderPosition().fX + (GetObjectCenterLength().fX / 2.0f);
					vPos.fY = GetRenderPosition().fY - (GetObjectCenterLength().fY * 1.5f);

					visualSprite.m_vObjectRenderPos = vPos;
					visualSprite.Frame();
				}
			}
#else
			for (auto& visualSprite : m_VisualSprites)
			{
				POINT_F vPos;
				vPos.fX = GetPosition().fX;
				vPos.fY = GetPosition().fY + kObjectHeightSize;

				visualSprite.m_vObjectRenderPos = vPos;
				visualSprite.Frame();
			}
#endif // NETWORK

			// Wireframe
			UpdateWireframe();
		}break;
	}
	return true;
}

bool Hero::UpdateRender()
{
	switch (g_eGameSceneState)
	{
		case eGameSceneState::LOBBY_SCENE:
		{
			m_MotionSprites[static_cast<size_t>(eHeroMotionType::WAIT)].Render();
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			if (g_bGameStart == false)
			{
				m_MotionSprites[static_cast<size_t>(eHeroMotionType::READY)].Render();
			}
			else
			{
				// Watebomb
				for (int iBomb = 0; iBomb < m_WaterBombList.size(); iBomb++)
				{
					m_WaterBombList[iBomb]->Render();
				}

				if (GetSurvival() == false)
				{
					if (m_bIsDead == true)
					{
						if (g_bGameOver == false)
						{
							m_MotionSprites[static_cast<size_t>(eHeroMotionType::DEAD)].Render();
						}
					}
					else
					{
						m_MotionSprites[static_cast<size_t>(eHeroMotionType::TRAP)].Render();
					}
				}
				else
				{
					Object::Render();
				}
			}

#ifdef NETWORK
			if (m_iHeroID == g_iPlayerNumber && g_bGameOver == false)
			{
				for (auto& visualSprite : m_VisualSprites)
				{
					visualSprite.Render();
				}
			}
#else
			for (auto& visualSprite : m_VisualSprites)
			{
				POINT_F vPos;
				vPos.fX = GetPosition().fX;
				vPos.fY = GetPosition().fY + kObjectHeightSize;

				visualSprite.m_vObjectRenderPos = vPos;
				visualSprite.Frame();
			}
#endif // NETWORK

			// Wireframe Render
			GetWireframe().Render();
		}break;
	}

	return true;
}

bool Hero::UpdateBoundingBox()
{
	float fObjectCenterWidth = kObjectWidthSize * 0.5;
	float fObjectCenterHeight = kObjectHeightSize * 0.5;

	// Set boundingbox
	RECT rtHero;
	rtHero.left = GetPosition().fX - fObjectCenterWidth;
	rtHero.top = GetPosition().fY - fObjectCenterHeight;
	rtHero.right = rtHero.left + kObjectWidthSize;
	rtHero.bottom = rtHero.top + kObjectHeightSize;
	GetBoundingBox().SetBoundingBoxInfo(rtHero);

	return true;
}

bool Hero::UpdateWireframe()
{
	vector<RECT> rtWireframeArray;
	RECT rtWireFrame = GetBoundingBox().GetBoundingBoxInfo();
	GetWireframe().GetDrawPointList().clear();
	rtWireframeArray.push_back(rtWireFrame);
	GetWireframe().SetDrawPointList(rtWireframeArray);
	return true;
}

bool Hero::UpdateWaterBomb()
{
	for (int iBomb = 0; iBomb < m_WaterBombList.size(); iBomb++)
	{
		// waterbomb time check
		if (m_WaterBombList[iBomb]->Frame() || m_WaterBombList[iBomb]->GetSurvival() == false)
		{
			WaterBomb* delWaterBomb = m_WaterBombList[iBomb];
			m_WaterBombList.erase(m_WaterBombList.begin() + iBomb);
			delete delWaterBomb;
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Developer Redefinition Function
//--------------------------------------------------------------------------------------
bool Hero::Init()
{
	SetObjectType(OBJECT_TYPE::HERO);
	Object::Init();

	// Add hero in Quadtree
	Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(GetPosition());
	m_pMap->GetQuadTree().AddInQuadTree(pNode, (Object*)this);
	m_pPrevNode = pNode;

	return true;
}

bool Hero::Frame()
{
#ifdef NETWORK
	if (m_bIsDead == false && g_bGameStart == true && m_bActivation == true)
	{
		// Hero Move
		Move();

		// Hero Attack
		Attack();
	}
#else // !NETWORK
	if (m_bIsDead == false && g_bGameStart == true)
	{
		// Hero Move
		Move();

		// Hero Attack
		Attack();
	}
#endif

	// Hero data update
	UpdateFrame();

	return true;
}

bool Hero::Render()
{
	// Hero data update
	UpdateRender();

	return true;
}

bool Hero::Release()
{
	Object::Release();
	return true;
}

Hero::Hero()
{
	m_HeroType = eHeroType::TypeBazzi;
	m_iWaterBombCount = 1;
	m_iWaterBombPower = 1;
	m_iSpeedCount = 1;
	m_fHeroSpeed = 0.0f;
	m_fLifeTime = 0.0f;
	m_iIndex = 0;
	m_pMap = nullptr;
	m_pPrevNode = nullptr;
	m_bIsDead = false;
	SetObjectType(OBJECT_TYPE::HERO);
	m_bActivation = false;
	SAFE_ZERO(m_pUserData);

	// Network
	m_iHeroID = -1;
	m_eAction = eDirection::DEFAULT;
}


Hero::~Hero()
{
}
