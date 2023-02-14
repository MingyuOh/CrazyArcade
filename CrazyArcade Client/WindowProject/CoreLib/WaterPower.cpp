#include "WaterPower.h"

bool WaterPower::Init()
{
	m_eItemType = eItemType::WATER_POWER;
	T_STR szFilePath = _T("../../data/Item/WaterPower.bmp");
	T_STR szMaskFilePath = _T("../../data/Item/WaterPowerMask.bmp");

	// Set drawtype
	SetDrawType(eRenderType::CHARACTERDARW);
	Object::Create(GetOffScreenDC(), GetPosition(), GetRect(), _T("WaterPower"), szFilePath, szMaskFilePath);
	Object::SetObjectIndex(I_ObjManager.Load(this));

	return true;
}

bool WaterPower::CreateItem(HDC hOffscreenDC, POINT_F vPos)
{
	// Set hdc
	SetOffScreenDC(hOffscreenDC);

	// Set object position
	SetPosition(vPos);

	Item::Init();
	Init();

	return true;
}