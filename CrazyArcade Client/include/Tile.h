#pragma once
#include "Object.h"

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
	TILETYPE	m_iTileType;			// Tile Type
	bool		m_bCheckBrokenTile;		// Check if the tile is broken
public:
	//--------------------------------------------------------------------------------------
	// CreateTile
	//--------------------------------------------------------------------------------------
	bool		CreateTile();
	//--------------------------------------------------------------------------------------
	// UpdateTile
	//--------------------------------------------------------------------------------------
	bool		UpdateTile();
	//--------------------------------------------------------------------------------------
	// Frame
	//--------------------------------------------------------------------------------------
	bool		Frame();
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void		SetTile(TILETYPE iTileType);
	bool		SetTileCheck(bool bTile);
	void		SetTileObject(const RECT rtTile);
	void		SetTileObject(const RECT rtTile, int iWidthCount, int iHeightCount);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	TILETYPE	GetTile();
	bool		GetTileCheck();
public:
	Tile();
	virtual ~Tile();
};
