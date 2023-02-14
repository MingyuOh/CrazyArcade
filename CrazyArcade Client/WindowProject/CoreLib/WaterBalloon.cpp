#include "WaterBalloon.h"

bool WaterBalloon::Init()
{
	m_eItemType = eItemType::WATER_BALLOON;
	T_STR szFilePath = _T("../../data/Item/WaterBalloon.bmp");
	T_STR szMaskFilePath = _T("../../data/Item/WaterBalloonMask.bmp");

	// Set drawtype
	SetDrawType(eRenderType::CHARACTERDARW);
	Object::Create(GetOffScreenDC(), GetPosition(), GetRect(), _T("WaterBalloon"), szFilePath, szMaskFilePath);
	Object::SetObjectIndex(I_ObjManager.Load(this));

	return true;
}

bool WaterBalloon::CreateItem(HDC hOffscreenDC, POINT_F vPos)
{
	// Set hdc
	SetOffScreenDC(hOffscreenDC);

	// Set object position
	SetPosition(vPos);

	Item::Init();
	Init();

	return true;
}