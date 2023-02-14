#include "Skate.h"

bool Skate::Init()
{
	m_eItemType = eItemType::SKATE;
	T_STR szFilePath = _T("../../data/Item/Skate.bmp");
	T_STR szMaskFilePath = _T("../../data/Item/SkateMask.bmp");

	// Set drawtype
	SetDrawType(eRenderType::CHARACTERDARW);
	Object::Create(GetOffScreenDC(), GetPosition(), GetRect(), _T("Skate"), szFilePath, szMaskFilePath);
	Object::SetObjectIndex(I_ObjManager.Load(this));

	return true;
}

bool Skate::CreateItem(HDC hOffscreenDC, POINT_F vPos)
{
	// Set hdc
	SetOffScreenDC(hOffscreenDC);

	// Set object position
	SetPosition(vPos);

	Item::Init();
	Init();

	return true;
}