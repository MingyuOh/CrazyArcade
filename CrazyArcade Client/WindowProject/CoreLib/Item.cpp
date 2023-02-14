#include "Item.h"

//--------------------------------------------------------------------------------------
// Create item
//--------------------------------------------------------------------------------------
bool Item::Init()
{
	// Set Object type
	SetObjectType(OBJECT_TYPE::ITEM);

	// Set object distance from origin to midpoint
	SetObjectCenterLength(POINT_F(kObjectWidthSize * 0.5, kObjectHeightSize * 0.5));

	// Set rect
	RECT rt;
	rt.left = 0;
	rt.top = 0;	
	rt.right = 40;
	rt.bottom = 50;
	SetRect(rt);

	// Set boundingbox
	RECT rtItem;
	rtItem.left = GetPosition().fX - GetObjectCenterLength().fX;
	rtItem.top = GetPosition().fY - GetObjectCenterLength().fY;
	rtItem.right = rtItem.left + kObjectWidthSize;
	rtItem.bottom = rtItem.top + kObjectHeightSize;
	GetBoundingBox().SetBoundingBoxInfo(rtItem);

	GetWireframe().SetDrawPointList(rtItem);
	return true;
}

//--------------------------------------------------------------------------------------
// Frame
//--------------------------------------------------------------------------------------
bool Item::Frame()
{
	SetSpriteRect(GetSprite()->m_szSpriteName, 1.0f);
	Object::Frame();

	return true;
}

//--------------------------------------------------------------------------------------
// Render
//--------------------------------------------------------------------------------------
bool Item::Render()
{
	Object::Render();
	return true;
}

//--------------------------------------------------------------------------------------
// Release
//--------------------------------------------------------------------------------------
bool Item::Release()
{
	Object::Release();
	return true;
}

//--------------------------------------------------------------------------------------
// Set function
//--------------------------------------------------------------------------------------
void Item::SetActivation(const bool isActivation)
{
	m_bIsActivitation = isActivation;
}

//--------------------------------------------------------------------------------------
// Get function
//--------------------------------------------------------------------------------------
bool Item::GetActivation()
{
	return m_bIsActivitation;
}

eItemType Item::GetItemType()
{
	return m_eItemType;
}

eItemType Item::GetItemType(vector<int>* itemCountList)
{
	int index = 0;
	if (itemCountList->at(index) < kItemMaxWaterBalloonCount)
	{
		itemCountList->at(index)++;
		return eItemType::WATER_BALLOON;
	}
	index++;

	if (itemCountList->at(index) < kItemMaxWaterPowerCount)
	{
		itemCountList->at(index)++;
		return eItemType::WATER_POWER;
	}
	index++;

	if (itemCountList->at(index) < kItemMaxSkateCount)
	{
		itemCountList->at(index)++;
		return eItemType::SKATE;
	}
	index++;

	if (itemCountList->at(index) < kItemMaxWaterMaxPowerCount)
	{
		itemCountList->at(index)++;
		return eItemType::WATER_MAX_POWER;
	}
}

Item::Item()
{
	m_eItemType = eItemType::NONE;
	m_bIsActivitation = false;
}

Item::~Item()
{

}