#pragma once
#include "ObjectManager.h"
#include "Input.h"
#include "Map.h"
#include "WaterBomb.h"

//--------------------------------------------------------------------------------------
// Hero Type
//--------------------------------------------------------------------------------------
enum class HERO_TYPE
{ 
	TypeBazzi		= 0,
	TypeUni			= 1,
	TypeKephi		= 2,
	TypeMarid		= 3,
	TypeLodumani	= 4
};

//--------------------------------------------------------------------------------------
// Abstract hero class
//--------------------------------------------------------------------------------------
class Hero : public Object
{
private:
	vector<WaterBomb*>			m_WaterBombList;
	Map*						m_pMap;
	Input*						m_pInput;
	HERO_TYPE					m_HeroType;
	float						m_fHeroSpeed;
	int							m_iIndex;
	int							m_iMaxWaterBombCount;				// WaterBomb Count
	Node*						m_pAttackNode;
public:
	//--------------------------------------------------------------------------------------
	// Create Hero
	//--------------------------------------------------------------------------------------
	virtual void				CreateHero() = 0;
	//--------------------------------------------------------------------------------------
	// Move
	//--------------------------------------------------------------------------------------
	virtual void				Move();
	virtual void				Up();
	virtual void				Down();
	virtual void				Right();
	virtual void				Left();
	//--------------------------------------------------------------------------------------
	// Attack
	//--------------------------------------------------------------------------------------
	virtual void				Attack();
	bool						CheckAttackedNode(Node* pNode);
	//--------------------------------------------------------------------------------------
	// Collision Function
	//--------------------------------------------------------------------------------------
	virtual bool				CollisionMapToCharacter();
	bool						CollisionCharacterToWaterBomb();
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void						SetHeroType(HERO_TYPE heroType);
	void						SetHeroIndex(int iIndex);
	void						SetHeroSpeed(float fSpeed);
	void						SetMap(Map* pTileList);
	void						SetInputInfo(Input* pInput);
	void						SetWaterBombCount(int iWaterBombCount);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	int							GetHeroIndex();
	HERO_TYPE					GetHeroType();
	float						GetHeroSpeed();
	Input*						GetInputInfo();
	int							GetWaterBombCount();
	//--------------------------------------------------------------------------------------
	// Update Method
	//--------------------------------------------------------------------------------------
	virtual bool				UpdateFrame();
	virtual bool				UpdateRender();
	virtual bool				UpdateBoundingBox();
	virtual bool				UpdateWireframe();
	//--------------------------------------------------------------------------------------
	// Developer Redefinition Function
	//--------------------------------------------------------------------------------------
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	Hero();
	virtual ~Hero();
};

