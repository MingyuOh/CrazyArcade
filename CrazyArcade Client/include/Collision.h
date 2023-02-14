#pragma once
#include "CoreSTD.h"

enum class MAP_BOUNDARY { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class Collision
{
public:
	//--------------------------------------------------------------------------------------
	// Collision rect to rect 
	//--------------------------------------------------------------------------------------
	bool				RectToRect(RECT rt1, RECT rt2);
	//--------------------------------------------------------------------------------------
	// Collision map boundary 
	//--------------------------------------------------------------------------------------
	MAP_BOUNDARY		CollisionMap(RECT rtMap, RECT rtObjectBoundingBox);
public:
	Collision();
	virtual ~Collision();
};

