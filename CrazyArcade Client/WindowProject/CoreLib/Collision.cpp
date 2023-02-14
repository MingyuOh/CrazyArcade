#include "Collision.h"

//--------------------------------------------------------------------------------------
// Collision rect to point 
//--------------------------------------------------------------------------------------
bool Collision::RectToPoint(RECT rect, POINT point)
{
	if (rect.left <= point.x && rect.right >= point.x 
		&& rect.top <= point.y && rect.bottom >= point.y)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Collision rect to rect 
//--------------------------------------------------------------------------------------
bool Collision::RectToRect(RECT rt1, RECT rt2)
{
	LONG lFirstRectWidth = rt1.right - rt1.left;
	LONG lSecondRectWidth = rt2.right - rt2.left;
	LONG lFirstRectHeight = rt1.bottom - rt1.top;
	LONG lSecondRectHeight = rt2.bottom - rt2.top;
	LONG lFirstRectToSecondRectWidth = (rt1.right <= rt2.right) ? (rt2.right - rt1.left) : (rt1.right - rt2.left);
	LONG lFirstRectToSecondRectHeight = (rt1.bottom <= rt2.bottom) ? (rt2.bottom - rt1.top) : (rt1.bottom - rt2.top);

	if (lFirstRectWidth + lSecondRectWidth > lFirstRectToSecondRectWidth &&
		lFirstRectHeight + lSecondRectHeight > lFirstRectToSecondRectHeight)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Collision map boundary 
//--------------------------------------------------------------------------------------
MAP_BOUNDARY Collision::CollisionMap(RECT rtMap, RECT rtObjectBoundingBox)
{
	if (rtMap.top > rtObjectBoundingBox.top)
	{
		return MAP_BOUNDARY::UP;
	}
	if (rtMap.bottom < rtObjectBoundingBox.bottom)
	{
		return MAP_BOUNDARY::DOWN;
	}
	if (rtMap.left > rtObjectBoundingBox.left)
	{
		return MAP_BOUNDARY::LEFT;
	}
	if (rtMap.right < rtObjectBoundingBox.right)
	{
		return MAP_BOUNDARY::RIGHT;
	}
}

Collision::Collision()
{
}


Collision::~Collision()
{
}
