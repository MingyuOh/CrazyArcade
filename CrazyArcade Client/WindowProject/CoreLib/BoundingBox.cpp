#include "BoundingBox.h"

bool BoundingBox::UpdateBoundingBox(POINT_F vPos)
{
	float fObjectCenterWidth = kObjectWidthSize * 0.5;
	float fObjectCenterHeight = kObjectHeightSize * 0.5;

	// Set boundingbox
	RECT rtHero;
	rtHero.left = vPos.fX - fObjectCenterWidth;
	rtHero.top = vPos.fY - fObjectCenterHeight;
	rtHero.right = rtHero.left + kObjectWidthSize;
	rtHero.bottom = rtHero.top + kObjectHeightSize;
	m_rtBoundingBox = rtHero;

	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void BoundingBox::SetBoundingBoxInfo(RECT rtBoundingbox)
{
	m_rtBoundingBox = rtBoundingbox;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
RECT BoundingBox::GetBoundingBoxInfo()
{
	return m_rtBoundingBox;
}

BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}
