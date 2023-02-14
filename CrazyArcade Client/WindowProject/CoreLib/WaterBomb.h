#pragma once
#include "Object.h"
#include "QuadTree.h"
#include "Item.h"

#define WATERBOMB_LIFE_TIME 3.0f
#define WATERBOMB_EXPLOSION_TIME 0.5f

enum class eWaterBombDirection : int
{
	CENTER = 0,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,

	COUNT = 5
};

class WaterBomb :public Object
{
private:
	map<int, vector<Sprite>>		m_ExplosionSpriteMap;		// WaterBomb explosion sprite list
	map<int, vector<RECT>>			m_rtCollisionMap;			// WaterBomb collision rect
	float							m_fHoldingTime;				// WaterBomb holding time
	int								m_iPower;					// WaterBomb power
	bool							m_bIsExploded;				// WaterBomb whether it exploded
	float							m_fExplosionTime;			// WaterBomb explosion time

	QuadTree*						m_pQuadTree;				// QuadTree
	
public:
	//--------------------------------------------------------------------------------------
	// Create Waterbomb
	//--------------------------------------------------------------------------------------
	void							CreateWaterBomb(POINT_F waterBombPos, int iPower, QuadTree* pQuadTree);
	//--------------------------------------------------------------------------------------
	// Create water bomb sprites
	//--------------------------------------------------------------------------------------
	void							CreateExplosionSprites();
	//--------------------------------------------------------------------------------------
	// Update water bomb sprites
	//--------------------------------------------------------------------------------------
	bool							UpdateExplosionSprites(eWaterBombDirection direction, int index);
	//--------------------------------------------------------------------------------------
	// Calculation of the collision area
	//--------------------------------------------------------------------------------------
	bool							CaculateCollisionArea();
	//--------------------------------------------------------------------------------------
	// Delete colliding objects or update data
	//--------------------------------------------------------------------------------------
	bool							HandlingCollidingObject(Node* pNode, eWaterBombDirection direction, int index);
	//--------------------------------------------------------------------------------------
	// Check waterbomb elapsetime
	//--------------------------------------------------------------------------------------
	bool							CheckWaterBombHoldingTime();
	bool							CheckWaterBombExplosionTime();
	bool							CheckNodeRectAndCollisionRect(Node* pNode, RECT rtCollision);
	//--------------------------------------------------------------------------------------
	// Accumulate waterbomb elapsetime 
	//--------------------------------------------------------------------------------------
	void							AccumulateHoldingTime();
	void							AccumulateExplosionTime();
	//--------------------------------------------------------------------------------------
	// Render water bomb pop sprites
	//--------------------------------------------------------------------------------------
	bool							DrawExplosionSprites();
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void							SetWaterBombPower(int fPower);
	void							SetWaterBombCollisionRect();
	void							SetWaterBombRenderPosition();
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	int								GetWaterBombPower();
	bool							GetIsExploded();
	//--------------------------------------------------------------------------------------
	// Developer Redefinition Function
	//--------------------------------------------------------------------------------------
	bool							Frame();
	bool							Render();
public:
	WaterBomb();
	virtual ~WaterBomb();
};

