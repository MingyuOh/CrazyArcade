#pragma once
#include "Hero.h"

class Bazzi :public Hero
{
public:
	//--------------------------------------------------------------------------------------
	// Create Hero
	//--------------------------------------------------------------------------------------
	void			CreateHero(POINT_F vPos = { 0, 0 }) override;
	//--------------------------------------------------------------------------------------
	// Create other sprites
	//--------------------------------------------------------------------------------------
	void			CreateMotionSprites() override;
	//--------------------------------------------------------------------------------------
	// Create visual item and ui sprites
	//--------------------------------------------------------------------------------------
	void				CreateVisualSprites() override;
	//--------------------------------------------------------------------------------------
	// Move
	//--------------------------------------------------------------------------------------
	bool			MoveUp(Node* pNode) override;
	bool			MoveDown(Node* pNode) override;
	bool			MoveLeft(Node* pNode) override;
	bool			MoveRight(Node* pNode) override;
public:
	Bazzi();
	virtual ~Bazzi();
};

