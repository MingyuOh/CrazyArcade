#pragma once
#include "ObjectManager.h"
#include "Input.h"
#include "Map.h"
#include "WaterBomb.h"
#include "AsyncSelect.h"
#include "User.h"

//--------------------------------------------------------------------------------------
// Hero type
//--------------------------------------------------------------------------------------
enum class eHeroType : int
{ 
	TypeBazzi		= 0,
	TypeUni			= 1
};

//--------------------------------------------------------------------------------------
// Hero Motion type
//--------------------------------------------------------------------------------------
enum class eHeroMotionType : int
{
	STANDARD	= -1,
	WAIT		= 0,
	READY		= 1,
	TRAP		= 2,
	DEAD		= 3
};

//--------------------------------------------------------------------------------------
// Abstract hero class
//--------------------------------------------------------------------------------------
class Hero : public Object
{
private:
	vector<WaterBomb*>			m_WaterBombList;
	vector<Sprite>				m_MotionSprites;
	vector<Sprite>				m_VisualSprites;
	Map*						m_pMap;
	Node*						m_pPrevNode;
	eHeroType					m_HeroType;
	User*						m_pUserData;
	float						m_fHeroSpeed;
	float						m_fLifeTime;
	int							m_iIndex;
	int							m_iWaterBombPower;
	int							m_iWaterBombCount;
	int							m_iSpeedCount;
	bool						m_bIsDead;
	bool						m_bActivation;
private: // Network
	int							m_iHeroID;
	eDirection					m_eAction;
public:
	//--------------------------------------------------------------------------------------
	// Create Hero
	//--------------------------------------------------------------------------------------
	virtual void				CreateHero(POINT_F vPos = { 0, 0 }) abstract;
	//--------------------------------------------------------------------------------------
	// Create other sprites
	//--------------------------------------------------------------------------------------
	virtual void				CreateMotionSprites() abstract;
	//--------------------------------------------------------------------------------------
	// Create visual item and ui sprites
	//--------------------------------------------------------------------------------------
	virtual void				CreateVisualSprites();
	//--------------------------------------------------------------------------------------
	// Move
	//--------------------------------------------------------------------------------------
	virtual void				Move();
	virtual	bool				MoveUp(Node* pNode);
	virtual bool				MoveDown(Node* pNode);
	virtual bool				MoveLeft(Node* pNode);
	virtual bool				MoveRight(Node* pNode);
	void						Up();
	void						Down();
	void						Right();
	void						Left();
	//--------------------------------------------------------------------------------------
	// Attack
	//--------------------------------------------------------------------------------------
	virtual void				Attack();
	//--------------------------------------------------------------------------------------
	// Collision function
	//--------------------------------------------------------------------------------------
	bool						CollisionCharacterToObject(RECT rtCollisiontNode, eDirection eDirection);
	bool						CollisionCharacterToCharacter(Node* pNode, Object* object, int index);
	bool						CollisionCharacterToItem(Node* pNode, Object* object, int index);
	//--------------------------------------------------------------------------------------
	// Set function
	//--------------------------------------------------------------------------------------
	void						SetHeroType(eHeroType heroType);
	void						SetHeroIndex(int iIndex);
	void						SetHeroSpeed(float fSpeed);
	void						SetMap(Map* pTileList);
	void						SetWaterBombCount(int iWaterBombCount);
	void						SetDead(const bool bIsDead);
	void						SetMotionSprite(const Sprite newSprtie);
	void						SetLobbyPosition(const POINT_F vPos);
	void						SetPreviousNode(Node* pNode);
	void						SetID(const int id);
	void						SetActivation(const bool bActivation);
	void						SetUserData(User* userData);
	void						InsertWaterBomb(WaterBomb* pWaterBomb);
	//--------------------------------------------------------------------------------------
	// Get function
	//--------------------------------------------------------------------------------------
	int							GetHeroIndex();
	eHeroType					GetHeroType();
	float						GetHeroSpeed();
	int							GetWaterBombCount();
	bool						GetDead();
	POINT_F						GetLobbyPosition();
	Node*						GetPreviousNode();
	int							GetID();
	bool						GetActivation();
	User*						GetUserData();
	//--------------------------------------------------------------------------------------
	// Update method
	//--------------------------------------------------------------------------------------
	virtual bool				UpdateFrame();
	virtual bool				UpdateRender();
	virtual bool				UpdateBoundingBox();
	virtual bool				UpdateWireframe();
	bool						UpdateWaterBomb();
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	bool						Init();
	bool						Frame();
	bool						Render();
	bool						Release();
public:
	Hero();
	virtual ~Hero();
};

