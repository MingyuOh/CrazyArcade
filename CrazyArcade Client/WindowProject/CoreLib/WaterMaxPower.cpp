#include "WaterMaxPower.h"

bool WaterMaxPower::Init()
{
	m_eItemType = eItemType::WATER_MAX_POWER;
	T_STR szFilePath = _T("../../data/Item/WaterMaxPower.bmp");
	T_STR szMaskFilePath = _T("../../data/Item/WaterMaxPowerMask.bmp");

	// Set drawtype
	SetDrawType(eRenderType::CHARACTERDARW);
	Object::Create(GetOffScreenDC(), GetPosition(), GetRect(), _T("WaterMaxPower"), szFilePath, szMaskFilePath);
	Object::SetObjectIndex(I_ObjManager.Load(this));

	return true;
}

bool WaterMaxPower::CreateItem(HDC hOffscreenDC, POINT_F vPos)
{
	// Set hdc
	SetOffScreenDC(hOffscreenDC);

	// Set object position
	SetPosition(vPos);

	Item::Init();
	Init();

	return true;
}