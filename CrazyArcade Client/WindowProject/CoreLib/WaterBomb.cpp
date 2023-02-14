#include "WaterBomb.h"

//--------------------------------------------------------------------------------------
// Create Waterbomb
//--------------------------------------------------------------------------------------
void WaterBomb::CreateWaterBomb(POINT_F waterBombPos, int iPower, QuadTree* pQuadTree)
{
	// Set Power
	m_iPower = iPower;

	// QuadTree reference
	m_pQuadTree = pQuadTree;

	// Set pos
	SetPosition(waterBombPos);

	// Set object type
	SetObjectType(OBJECT_TYPE::WATER_BOMB);

	// Set center length
	SetObjectCenterLength(POINT_F(kObjectWidthSize * 0.5, kObjectHeightSize * 0.5));

	// Set boundingbox
	RECT rtWaterBombBoundingBox;
	rtWaterBombBoundingBox.left = static_cast<LONG>(waterBombPos.fX - GetObjectCenterLength().fX);
	rtWaterBombBoundingBox.top = static_cast<LONG>(waterBombPos.fY - GetObjectCenterLength().fY);
	rtWaterBombBoundingBox.right = rtWaterBombBoundingBox.left + kObjectWidthSize;
	rtWaterBombBoundingBox.bottom = rtWaterBombBoundingBox.top + kObjectHeightSize;
	GetBoundingBox().SetBoundingBoxInfo(rtWaterBombBoundingBox);

	// Bomb Rect
	RECT rtWaterBomb;
	rtWaterBomb.left = 0;
	rtWaterBomb.top = 0;
	rtWaterBomb.right = kObjectWidthSize;
	rtWaterBomb.bottom = kObjectHeightSize;

	// Create Waterbomb object
	Object::Create(GetOffScreenDC(), waterBombPos, rtWaterBomb, _T("WaterBomb"), _T("../../data/Bomb/Bomb.bmp"), _T("../../data/Bomb/BombMask.bmp"));

	// Create pop sprites
	CreateExplosionSprites();
}

//--------------------------------------------------------------------------------------
// Create water bomb sprites
//--------------------------------------------------------------------------------------
void WaterBomb::CreateExplosionSprites()
{
	map<int, tuple<T_STR, T_STR, T_STR>> WaterBombPopSpriteInfoMap
	{
		{ 0, make_tuple(_T("WaterBombExplosion"), _T("../../data/Wave/Explosion.bmp"), _T("../../data/Wave/ExplosionMask.bmp")) },
		{ 1, make_tuple(_T("WaterBombExplosionLeft"), _T("../../data/Wave/ExplosionLeft.bmp"), _T("../../data/Wave/ExplosionLeftMask.bmp")) },
		{ 2, make_tuple(_T("WaterBombExplosionTop"), _T("../../data/Wave/ExplosionTop.bmp"), _T("../../data/Wave/ExplosionTopMask.bmp"))},
		{ 3, make_tuple(_T("WaterBombExplosionRight"), _T("../../data/Wave/ExplosionRight.bmp"), _T("../../data/Wave/ExplosionRightMask.bmp"))},
		{ 4, make_tuple(_T("WaterBombExplosionBottom"), _T("../../data/Wave/ExplosionBottom.bmp"), _T("../../data/Wave/ExplosionBottomMask.bmp"))},
		{ 5, make_tuple(_T("WaterBombExplosionLeftEnd"), _T("../../data/Wave/ExplosionLeftEnd.bmp"), _T("../../data/Wave/ExplosionLeftEndMask.bmp"))},
		{ 6, make_tuple(_T("WaterBombExplosionTopEnd"), _T("../../data/Wave/ExplosionTopEnd.bmp"), _T("../../data/Wave/ExplosionTopEndMask.bmp"))},
		{ 7, make_tuple(_T("WaterBombExplosionRightEnd"), _T("../../data/Wave/ExplosionRightEnd.bmp"), _T("../../data/Wave/ExplosionRightEndMask.bmp"))},
		{ 8, make_tuple(_T("WaterBombExplosionBottomEnd"), _T("../../data/Wave/ExplosionBottomEnd.bmp"), _T("../../data/Wave/ExplosionBottomEndMask.bmp"))}
	};

	// Center explosion sprite
	Sprite newSprite;
	newSprite.m_iKey = I_SpriteManager.LoadSprite(get<0>(WaterBombPopSpriteInfoMap[0]));
	newSprite = *I_SpriteManager.GetPtr(newSprite.m_iKey);
	newSprite.m_hOffScreenDC = GetOffScreenDC();
	newSprite.m_fLifeTime = WATERBOMB_EXPLOSION_TIME;
	newSprite.m_fSecPerRender = newSprite.m_fLifeTime / newSprite.m_iFrameCount;
	newSprite.Load(get<1>(WaterBombPopSpriteInfoMap[0]), get<2>(WaterBombPopSpriteInfoMap[0]));
	m_ExplosionSpriteMap[0].push_back(newSprite);

	int iSpriteCount = WaterBombPopSpriteInfoMap.size();
	int iDivision = (iSpriteCount / 2) + 1;
	int iLoop = iSpriteCount / 2;

	for (int iPower = 0; iPower < m_iPower - 1; iPower++)
	{
		// 4 Direction explosion sprite
		for(int index = 1; index < iLoop + 1; index++)
		{
			newSprite.m_iKey = I_SpriteManager.LoadSprite(get<0>(WaterBombPopSpriteInfoMap[index]));
			newSprite = *I_SpriteManager.GetPtr(newSprite.m_iKey);
			newSprite.m_hOffScreenDC = GetOffScreenDC();
			newSprite.m_fLifeTime = WATERBOMB_EXPLOSION_TIME;
			newSprite.m_fSecPerRender = newSprite.m_fLifeTime / newSprite.m_iFrameCount;
			newSprite.Load(get<1>(WaterBombPopSpriteInfoMap[index]), get<2>(WaterBombPopSpriteInfoMap[index]));

			m_ExplosionSpriteMap[index].push_back(newSprite);
		}
	}

	int iMapIndex = 0;
	// 4 Direction end explosion sprite
	for (int index = iLoop + 1; index < iSpriteCount; index++)
	{
		iMapIndex++;
		newSprite.m_iKey = I_SpriteManager.LoadSprite(get<0>(WaterBombPopSpriteInfoMap[index]));
		newSprite = *I_SpriteManager.GetPtr(newSprite.m_iKey);
		newSprite.m_hOffScreenDC = GetOffScreenDC();
		newSprite.m_fLifeTime = WATERBOMB_EXPLOSION_TIME;
		newSprite.m_fSecPerRender = newSprite.m_fLifeTime / newSprite.m_iFrameCount;
		newSprite.Load(get<1>(WaterBombPopSpriteInfoMap[index]), get<2>(WaterBombPopSpriteInfoMap[index]));

		m_ExplosionSpriteMap[iMapIndex].push_back(newSprite);
	}

	// Set collision rect
	SetWaterBombCollisionRect();

	// Set rendering position
	SetWaterBombRenderPosition();
}

//--------------------------------------------------------------------------------------
// Update water bomb sprites
//--------------------------------------------------------------------------------------
bool WaterBomb::UpdateExplosionSprites(eWaterBombDirection direction, int index)
{
	size_t iDirectionIndex = static_cast<size_t>(direction);

	m_ExplosionSpriteMap[iDirectionIndex].erase(m_ExplosionSpriteMap[iDirectionIndex].begin() + index, m_ExplosionSpriteMap[iDirectionIndex].end());
	m_rtCollisionMap[iDirectionIndex].erase(m_rtCollisionMap[iDirectionIndex].begin() + index, m_rtCollisionMap[iDirectionIndex].end());

	return true;
}

//--------------------------------------------------------------------------------------
// Calculation of the collision area
//--------------------------------------------------------------------------------------
bool WaterBomb::CaculateCollisionArea()
{
	// Center
	size_t iDirection = static_cast<size_t>(eWaterBombDirection::CENTER);
	RECT rtCollision = m_rtCollisionMap[iDirection].front();
	Node* pNode = m_pQuadTree->FindNodeInQuadTree(rtCollision);
	m_pQuadTree->DeleteObject(pNode, this);
	HandlingCollidingObject(pNode, eWaterBombDirection::CENTER, 0);

	for (int iPower = 0; iPower < m_iPower; iPower++)
	{
		// Left
		iDirection = static_cast<size_t>(eWaterBombDirection::LEFT);
		if (m_rtCollisionMap[iDirection].size() > iPower)
		{
			rtCollision = m_rtCollisionMap[iDirection][iPower];
			pNode = m_pQuadTree->FindNodeInQuadTree(rtCollision);
			if (CheckNodeRectAndCollisionRect(pNode, rtCollision) == false)
			{
				pNode = nullptr;
			}
			HandlingCollidingObject(pNode, eWaterBombDirection::LEFT, iPower);
		}

		// Top
		iDirection = static_cast<size_t>(eWaterBombDirection::TOP);
		if (m_rtCollisionMap[iDirection].size() > iPower)
		{
			rtCollision = m_rtCollisionMap[iDirection][iPower];
			pNode = m_pQuadTree->FindNodeInQuadTree(rtCollision);
			if (CheckNodeRectAndCollisionRect(pNode, rtCollision) == false)
			{
				pNode = nullptr;
			}
			HandlingCollidingObject(pNode, eWaterBombDirection::TOP, iPower);
		}

		// Right
		iDirection = static_cast<size_t>(eWaterBombDirection::RIGHT);
		if (m_rtCollisionMap[iDirection].size() > iPower)
		{
			rtCollision = m_rtCollisionMap[iDirection][iPower];
			pNode = m_pQuadTree->FindNodeInQuadTree(rtCollision);
			if (CheckNodeRectAndCollisionRect(pNode, rtCollision) == false)
			{
				pNode = nullptr;
			}
			HandlingCollidingObject(pNode, eWaterBombDirection::RIGHT, iPower);
		}

		// Bottom
		iDirection = static_cast<size_t>(eWaterBombDirection::BOTTOM);
		if (m_rtCollisionMap[iDirection].size() > iPower)
		{
			rtCollision = m_rtCollisionMap[iDirection][iPower];
			pNode = m_pQuadTree->FindNodeInQuadTree(rtCollision);
			if (CheckNodeRectAndCollisionRect(pNode, rtCollision) == false)
			{
				pNode = nullptr;
			}
			HandlingCollidingObject(pNode, eWaterBombDirection::BOTTOM, iPower);
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Delete colliding objects and update data
//--------------------------------------------------------------------------------------
bool WaterBomb::HandlingCollidingObject(Node* pNode, eWaterBombDirection direction, int index)
{
	if (pNode == nullptr)
	{
		return UpdateExplosionSprites(direction, index);
	}

	Object* pObject = nullptr;
	for (auto& object : pNode->GetObjectList())
	{
		if (this == object)
		{
			continue;
		}
		pObject = object;

		OBJECT_TYPE eType = object->GetObjectType();
		switch (eType)
		{
			case OBJECT_TYPE::HERO:
			{
				pObject->SetSurvival(false);
			}break;
			case OBJECT_TYPE::WATER_BOMB:
			{
				WaterBomb* pWaterBomb = static_cast<WaterBomb*>(object);
				pWaterBomb->m_fHoldingTime += WATERBOMB_LIFE_TIME;
				pNode->DeleteObjectInNode(object);
			}break;
			case OBJECT_TYPE::ITEM:
			{
				if (pNode->GetTileType() == eTileType::EMPTY)
				{
					pObject->SetSurvival(false);
					pNode->DeleteObjectInNode(object);
				}
			}break;
			case OBJECT_TYPE::TILE:
			{
				pNode->DeleteObjectInNode(object);
				pNode->SetTileType(eTileType::EMPTY);

				Tile* pTile = static_cast<Tile*>(object);
				pTile->SetTileState(true);
				UpdateExplosionSprites(direction, index);
			}break;
			case OBJECT_TYPE::STATIC_OBJECT:
			{
				UpdateExplosionSprites(direction, index);
			}break;
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Check waterbomb elapsetime
//--------------------------------------------------------------------------------------
bool WaterBomb::CheckWaterBombHoldingTime()
{
	if (m_fHoldingTime >= WATERBOMB_LIFE_TIME)
	{
		m_bIsExploded = true;
		I_GameSound.Play(static_cast<int>(eGameSoundList::WAVE), true, false);
		CaculateCollisionArea();
		return false;
	}

	// If waterbombElapsetime is not to exceed disappeartime, Accumulate waterbomb elapsetime
	AccumulateHoldingTime();
	return false;
}

bool WaterBomb::CheckWaterBombExplosionTime()
{
	if (m_fExplosionTime >= WATERBOMB_EXPLOSION_TIME)
	{
		SetSurvival(false);
		for (int iMap = 0; iMap < m_ExplosionSpriteMap.size(); iMap++)
		{
			m_ExplosionSpriteMap[iMap].clear();
		}
		m_ExplosionSpriteMap.clear();
		return true;
	}

	// If waterbombElapsetime is not to exceed disappeartime, Accumulate waterbomb elapsetime
	AccumulateExplosionTime();

	return false;
}

bool WaterBomb::CheckNodeRectAndCollisionRect(Node* pNode, RECT rtCollision)
{
	if (pNode != nullptr)
	{
		if (RectInequality(pNode->GetCorner(), rtCollision) == false)
		{
			return false;
		}
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Accumulate waterbomb elapsetime 
//--------------------------------------------------------------------------------------
void WaterBomb::AccumulateHoldingTime()
{
	m_fHoldingTime += g_fSecPerFrame;
}

void WaterBomb::AccumulateExplosionTime()
{
	m_fExplosionTime += g_fSecPerFrame;
}

//--------------------------------------------------------------------------------------
// Render water bomb pop sprites
//--------------------------------------------------------------------------------------
bool WaterBomb::DrawExplosionSprites()
{
	return true;
}

//--------------------------------------------------------------------------------------
// Developer Redefinition Function
//--------------------------------------------------------------------------------------
bool WaterBomb::Frame()
{
	if (m_bIsExploded == false)
	{
		SetSpriteRect(_T("WaterBomb"), 0.75f);
		Object::Frame();
		return CheckWaterBombHoldingTime();
	}
	else
	{
		if (m_ExplosionSpriteMap.empty() == true)
		{
			return false;
		}

		// Center
		size_t iDirection = static_cast<size_t>(eWaterBombDirection::CENTER);
		for (int iFrame = 0; iFrame < m_ExplosionSpriteMap[iDirection].size(); iFrame++)
		{
			m_ExplosionSpriteMap[iDirection][iFrame].Frame();
		}

		// Left
		iDirection = static_cast<size_t>(eWaterBombDirection::LEFT);
		for (int iFrame = 0; iFrame < m_ExplosionSpriteMap[iDirection].size(); iFrame++)
		{
			m_ExplosionSpriteMap[iDirection][iFrame].Frame();
		}

		// Top
		iDirection = static_cast<size_t>(eWaterBombDirection::TOP);
		for (int iFrame = 0; iFrame < m_ExplosionSpriteMap[iDirection].size(); iFrame++)
		{
			m_ExplosionSpriteMap[iDirection][iFrame].Frame();
		}

		// Right
		iDirection = static_cast<size_t>(eWaterBombDirection::RIGHT);
		for (int iFrame = 0; iFrame < m_ExplosionSpriteMap[iDirection].size(); iFrame++)
		{
			m_ExplosionSpriteMap[iDirection][iFrame].Frame();
		}

		// Bottom
		iDirection = static_cast<size_t>(eWaterBombDirection::BOTTOM);
		for (int iFrame = 0; iFrame < m_ExplosionSpriteMap[iDirection].size(); iFrame++)
		{
			m_ExplosionSpriteMap[iDirection][iFrame].Frame();
		}

		return CheckWaterBombExplosionTime();
	}
}

bool WaterBomb::Render()
{
	if (m_bIsExploded == false)
	{
		Object::Render();
	}
	else
	{
		if (m_ExplosionSpriteMap.empty() == true)
		{
			return false;
		}

		// Center
		size_t iDirection = static_cast<size_t>(eWaterBombDirection::CENTER);
		for (int iRender = 0; iRender < m_ExplosionSpriteMap[iDirection].size(); iRender++)
		{
			m_ExplosionSpriteMap[iDirection][iRender].Render();
		}

		// Left
		iDirection = static_cast<size_t>(eWaterBombDirection::LEFT);
		for (int iRender = 0; iRender < m_ExplosionSpriteMap[iDirection].size(); iRender++)
		{
			m_ExplosionSpriteMap[iDirection][iRender].Render();
		}

		// Top
		iDirection = static_cast<size_t>(eWaterBombDirection::TOP);
		for (int iRender = 0; iRender < m_ExplosionSpriteMap[iDirection].size(); iRender++)
		{
			m_ExplosionSpriteMap[iDirection][iRender].Render();
		}

		// Right
		iDirection = static_cast<size_t>(eWaterBombDirection::RIGHT);
		for (int iRender = 0; iRender < m_ExplosionSpriteMap[iDirection].size(); iRender++)
		{
			m_ExplosionSpriteMap[iDirection][iRender].Render();
		}

		// Bottom
		iDirection = static_cast<size_t>(eWaterBombDirection::BOTTOM);
		for (int iRender = 0; iRender < m_ExplosionSpriteMap[iDirection].size(); iRender++)
		{
			m_ExplosionSpriteMap[iDirection][iRender].Render();
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void WaterBomb::SetWaterBombPower(int fPower)
{
	m_iPower = fPower;
}

void WaterBomb::SetWaterBombCollisionRect()
{
	RECT rtWaterBomb = GetBoundingBox().GetBoundingBoxInfo();

	// Center
	RECT rtCollision = rtWaterBomb;
	size_t iDirection = static_cast<size_t>(eWaterBombDirection::CENTER);
	m_rtCollisionMap[iDirection].push_back(rtCollision);

	for (int iPower = 0; iPower < m_iPower; iPower++)
	{
		// Left
		rtCollision = rtWaterBomb;
		rtCollision.left -= kObjectWidthSize * (iPower + 1);
		rtCollision.right -= kObjectWidthSize * (iPower + 1);
		iDirection = static_cast<size_t>(eWaterBombDirection::LEFT);
		m_rtCollisionMap[iDirection].push_back(rtCollision);

		// Top
		rtCollision = rtWaterBomb;
		rtCollision.top -= kObjectWidthSize * (iPower + 1);
		rtCollision.bottom -= kObjectWidthSize * (iPower + 1);
		iDirection = static_cast<size_t>(eWaterBombDirection::TOP);
		m_rtCollisionMap[iDirection].push_back(rtCollision);

		// Right
		rtCollision = rtWaterBomb;
		rtCollision.left += kObjectWidthSize * (iPower + 1);
		rtCollision.right += kObjectWidthSize * (iPower + 1);
		iDirection = static_cast<size_t>(eWaterBombDirection::RIGHT);
		m_rtCollisionMap[iDirection].push_back(rtCollision);

		// Bottom
		rtCollision = rtWaterBomb;
		rtCollision.top += kObjectWidthSize * (iPower + 1);
		rtCollision.bottom += kObjectWidthSize * (iPower + 1);
		iDirection = static_cast<size_t>(eWaterBombDirection::BOTTOM);
		m_rtCollisionMap[iDirection].push_back(rtCollision);
	}
}

void WaterBomb::SetWaterBombRenderPosition()
{
	POINT_F vExplosionRenderPos = POINT_F(GetBoundingBox().GetBoundingBoxInfo().left, GetBoundingBox().GetBoundingBoxInfo().top);
	size_t iDirection = static_cast<size_t>(eWaterBombDirection::CENTER);

	// Center
	m_ExplosionSpriteMap[iDirection].front().m_vObjectRenderPos = vExplosionRenderPos;

	for (int iPower = 0; iPower < m_iPower; iPower++)
	{
		// Left
		iDirection = static_cast<size_t>(eWaterBombDirection::LEFT);
		m_ExplosionSpriteMap[iDirection][iPower].m_vObjectRenderPos = POINT_F(vExplosionRenderPos.fX - (kObjectWidthSize * (iPower + 1)), vExplosionRenderPos.fY);

		// Top
		iDirection = static_cast<size_t>(eWaterBombDirection::TOP);
		m_ExplosionSpriteMap[iDirection][iPower].m_vObjectRenderPos = POINT_F(vExplosionRenderPos.fX, vExplosionRenderPos.fY - (kObjectHeightSize * (iPower + 1)));

		// Right
		iDirection = static_cast<size_t>(eWaterBombDirection::RIGHT);
		m_ExplosionSpriteMap[iDirection][iPower].m_vObjectRenderPos = POINT_F(vExplosionRenderPos.fX + (kObjectWidthSize * (iPower + 1)), vExplosionRenderPos.fY);

		// Bottom
		iDirection = static_cast<size_t>(eWaterBombDirection::BOTTOM);
		m_ExplosionSpriteMap[iDirection][iPower].m_vObjectRenderPos = POINT_F(vExplosionRenderPos.fX, vExplosionRenderPos.fY + (kObjectHeightSize * (iPower + 1)));
	}
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
int	WaterBomb::GetWaterBombPower()
{
	return m_iPower;
}

bool WaterBomb::GetIsExploded()
{
	return m_bIsExploded;
}

WaterBomb::WaterBomb() :m_fHoldingTime(0.0f), m_iPower(1), m_bIsExploded(false), m_fExplosionTime(0.0f)
{
	m_pQuadTree = nullptr;
}

WaterBomb::~WaterBomb()
{
	SAFE_ZERO(m_pQuadTree);
}
