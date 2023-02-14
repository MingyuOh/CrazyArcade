#pragma once
#include "WaterBalloon.h"
#include "WaterPower.h"
#include "WaterMaxPower.h"
#include "Skate.h"

#define TILE_EXPLOSION_TIME 0.4f

class Tile : public Object
{
private:
	//--------------------------------------------------------------------------------------//
	//------------------------------------Tile Type-----------------------------------------//
	//--------------------------------------------------------------------------------------//
	//								None			: -1									//
	//								Empty			: 0										//
	//								Block			: 1										//
	//								Box				: 2										//
	//								Pillar 			: 3										//
	//								Sail 			: 4										//
	//--------------------------------------------------------------------------------------//
	//--------------------------------------------------------------------------------------//
	eTileType	m_eTileType;				// Tile Type
	Sprite		m_ExplosionSprite;			// Explosion sprite
	int			m_iItemIndex;				// Item index
	float		m_fExplosionTime;			// Explosion time
	bool		m_bExistenceItem;			// Whether an item exists in the tile
	bool		m_bIsBroken;				// Tile state
	bool		m_bLoadExplosionSprite;		// Load explosion sprite
public:
	//--------------------------------------------------------------------------------------
	// CreateTile
	//--------------------------------------------------------------------------------------
	bool		CreateTile();
	//--------------------------------------------------------------------------------------
	// Create explosion effect
	//--------------------------------------------------------------------------------------
	void		CreateExplosionEffect();
	//--------------------------------------------------------------------------------------
	// Check explosion time
	//--------------------------------------------------------------------------------------
	bool		CheckExplosionTime();
	//--------------------------------------------------------------------------------------
	// Accumulate waterbomb elapsetime 
	//--------------------------------------------------------------------------------------
	void		AccumulateExplosionTime();
	//--------------------------------------------------------------------------------------
	// Frame
	//--------------------------------------------------------------------------------------
	bool		Frame();
	//--------------------------------------------------------------------------------------
	// Render
	//--------------------------------------------------------------------------------------
	bool		Render();
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void		SetTileType(eTileType eTileType);
	void		SetItemIndex(const int index);
	void		SetTileObject(const RECT rtTile);
	void		SetTileState(const bool bIsBroken);
	void		SetExistenceItem(const bool bExistenceItem);
	void		SetExplosionRenderPosition(POINT_F vPos = POINT_F());
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	eTileType	GetTileType();
	int			GetItemIndex();
	bool		GetTileState();
	bool		GetExistenceItem();
public:
	Tile();
	virtual ~Tile();
};

