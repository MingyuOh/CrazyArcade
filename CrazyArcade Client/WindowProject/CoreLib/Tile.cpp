#include "Tile.h"

//--------------------------------------------------------------------------------------
// CreateTile
//--------------------------------------------------------------------------------------
bool Tile::CreateTile()
{
	Sprite sprite;
	T_STR szFilePath = L"../../data/Tile/";
	T_STR szMaskFilePath = _T("../../data/Tile/");
	T_STR szTileName = _T("");
	T_STR szMaskName = _T("Mask");
	T_STR szExtention = L".bmp";

	switch(m_eTileType)
	{
		case eTileType::BLOCK:
		{
			szTileName = L"Block";
			CreateExplosionEffect();
			SetObjectType(OBJECT_TYPE::TILE);
			break;
		}
		case eTileType::BOX:
		{
			szTileName = L"Box";
			CreateExplosionEffect();
			SetObjectType(OBJECT_TYPE::TILE);
			break;
		}
		case eTileType::PILLAR:
		{
			szTileName = L"Pillar";
			SetObjectType(OBJECT_TYPE::STATIC_OBJECT);
			break;
		}
		case eTileType::SAIL:
		{
			szTileName = L"Sail";
			SetObjectType(OBJECT_TYPE::STATIC_OBJECT);
			break;
		}
		case eTileType::STATIC:
		{
			RECT rect = { 0, 0, kObjectWidthSize, kObjectHeightSize };
			SetTileObject(rect);
			SetObjectType(OBJECT_TYPE::STATIC_OBJECT);
			return false;
		}
		default:
		{
			RECT rect = { 0, 0, kObjectWidthSize, kObjectHeightSize };
			SetTileObject(rect);
			return false;
		}
	}

	sprite.m_iIndex = I_SpriteManager.LoadSprite(szTileName.c_str());
	sprite = *I_SpriteManager.GetPtr(sprite.m_iIndex);

	SetTileObject(sprite.m_rectList.front());

	szFilePath += szTileName;
	szFilePath += szExtention;

	szMaskFilePath += szTileName;
	szMaskFilePath += szMaskName;
	szMaskFilePath += szExtention;

	Object::Create(Object::GetOffScreenDC(), Object::GetPosition(), Object::GetRect(), szTileName, szFilePath, szMaskFilePath);

	SetExplosionRenderPosition(GetRenderPosition());

	return true;
}

//--------------------------------------------------------------------------------------
// Create explosion effect
//--------------------------------------------------------------------------------------
void Tile:: CreateExplosionEffect()
{
	m_ExplosionSprite.m_iIndex = I_SpriteManager.LoadSprite(_T("ObstacleExplosion"));
	m_ExplosionSprite = *I_SpriteManager.GetPtr(m_ExplosionSprite.m_iIndex);
	m_ExplosionSprite.m_hOffScreenDC = GetOffScreenDC();
	m_ExplosionSprite.m_fLifeTime = TILE_EXPLOSION_TIME;
	m_ExplosionSprite.m_fSecPerRender = m_ExplosionSprite.m_fLifeTime / m_ExplosionSprite.m_iFrameCount;
	m_ExplosionSprite.Load(_T("../../data/Tile/ObstacleExplosion.bmp"), _T("../../data/Tile/ObstacleExplosionMask.bmp"));
}

//--------------------------------------------------------------------------------------
// Check explosion time
//--------------------------------------------------------------------------------------
bool Tile::CheckExplosionTime()
{
	if (m_fExplosionTime >= TILE_EXPLOSION_TIME)
	{
		SetTileType(eTileType::EMPTY);
		SetSurvival(false);
		return false;
	}
	AccumulateExplosionTime();
	return true;
}

//--------------------------------------------------------------------------------------
// Accumulate waterbomb elapsetime 
//--------------------------------------------------------------------------------------
void Tile::AccumulateExplosionTime()
{
	m_fExplosionTime += g_fSecPerFrame;
}

//--------------------------------------------------------------------------------------
// Frame
//--------------------------------------------------------------------------------------
bool Tile::Frame()
{
	if (m_bIsBroken == true && GetObjectType() == OBJECT_TYPE::TILE)
	{
		if (CheckExplosionTime() == true)
		{
			m_ExplosionSprite.Frame();
		}
	}
	else
	{
		Object::Frame();
	}
	
	return true;
}

//--------------------------------------------------------------------------------------
// Render
//--------------------------------------------------------------------------------------
bool Tile::Render()
{
	if (m_bIsBroken == true && GetObjectType() == OBJECT_TYPE::TILE)
	{
		m_ExplosionSprite.Render();
	}
	else
	{
		Object::Render();
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void Tile::SetTileType(eTileType eTileType)
{
	m_eTileType = eTileType;
}
void Tile::SetItemIndex(const int index)
{
	m_iItemIndex = index;
}

void Tile::SetTileObject(const RECT rtTile)
{
	SetRect(rtTile);

	// Set boundingbox
	RECT rtTileBoundingBox;
	rtTileBoundingBox.left = rtTile.left + static_cast<LONG>(GetPosition().fX - GetObjectCenterLength().fX);
	rtTileBoundingBox.top = rtTile.top + static_cast<LONG>(GetPosition().fY - GetObjectCenterLength().fY);
	rtTileBoundingBox.right = rtTileBoundingBox.left + kObjectWidthSize;
	rtTileBoundingBox.bottom = rtTileBoundingBox.top + kObjectHeightSize;
	GetBoundingBox().SetBoundingBoxInfo(rtTileBoundingBox);
}

void Tile::SetTileState(const bool bIsBroken)
{
	m_bIsBroken = bIsBroken;
}

void Tile::SetExistenceItem(const bool bExistenceItem)
{
	m_bExistenceItem = bExistenceItem;
}

void Tile::SetExplosionRenderPosition(POINT_F vPos)
{
	if (m_eTileType == eTileType::BLOCK || m_eTileType == eTileType::BOX)
	{
		m_ExplosionSprite.m_vObjectRenderPos = vPos;
	}
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
eTileType Tile::GetTileType()
{
	return m_eTileType;
}

int Tile::GetItemIndex()
{
	return m_iItemIndex;
}

bool Tile::GetTileState()
{
	return m_bIsBroken;
}

bool Tile::GetExistenceItem()
{
	return m_bExistenceItem;
}

Tile::Tile()
{
	m_eTileType	= eTileType::NONE;
	m_iItemIndex = -1;
	m_fExplosionTime = 0.0f;
	m_bExistenceItem = false;
	m_bIsBroken = false;
	m_bLoadExplosionSprite = false;
}

Tile::~Tile()
{
}
