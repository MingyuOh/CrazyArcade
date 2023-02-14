#include "Bazzi.h"

void Bazzi::CreateHero(POINT_F vPos)
{
	T_STR szFilePath = _T("../../data/Character/Bazzi.bmp");
	T_STR szMaskFilePath = _T("../../data/Character/BazziMask.bmp");
	
	// Set object distance from origin to midpoint
	SetObjectCenterLength(POINT_F(kObjectWidthSize * 0.5, kObjectHeightSize * 0.5));

	// Set rect
	RECT rt;
	rt.left = 123;	// posX
	rt.top = 0;		// posY
	rt.right = 46;	// width
	rt.bottom = 62; // height
	SetRect(rt);

	// Set position
	SetPosition(vPos);

	// Set boundingbox
	RECT rtHero;
	rtHero.left = GetPosition().fX - GetObjectCenterLength().fX;
	rtHero.top = GetPosition().fY - GetObjectCenterLength().fY;
	rtHero.right = rtHero.left + kObjectWidthSize;
	rtHero.bottom = rtHero.top + kObjectHeightSize;
	GetBoundingBox().SetBoundingBoxInfo(rtHero);

	// Set BazziSpeed
	SetHeroSpeed(kHeroBazziSpeed);

	// Set drawtype
	SetDrawType(eRenderType::CHARACTERDARW);
	Object::Create(GetOffScreenDC(), GetPosition(), GetRect(), _T(""), szFilePath, szMaskFilePath);
	Object::SetObjectIndex(I_ObjManager.Load(this));

	GetWireframe().SetDrawPointList(rtHero);

	CreateMotionSprites();

	CreateVisualSprites();
}

//--------------------------------------------------------------------------------------
// Create other sprites
//--------------------------------------------------------------------------------------
void Bazzi::CreateMotionSprites()
{
	vector<tuple<T_STR, T_STR, T_STR>> motionSpriteList
	{
		make_tuple(_T("BazziWait"), _T("../../data/Character/BazziWait.bmp"), _T("../../data/Character/BazziWaitMask.bmp")),
		make_tuple(_T("BazziReady"), _T("../../data/Character/BazziReady.bmp"), _T("../../data/Character/BazziReadyMask.bmp")),
		make_tuple(_T("BazziTrap"), _T("../../data/Character/BazziTrap.bmp"), _T("../../data/Character/BazziTrapMask.bmp")),
		make_tuple(_T("BazziDead"), _T("../../data/Character/BazziDead.bmp"), _T("../../data/Character/BazziDeadMask.bmp")),
	};
	int index = 0;
	
	// SetSpriteRect 함수 없애고 아래 내용을 sprite화 해야함
	// Bazzi wait sprite
	Sprite newSprite;
	newSprite.m_iKey = I_SpriteManager.LoadSprite(get<0>(motionSpriteList[index]));
	newSprite = *I_SpriteManager.GetPtr(newSprite.m_iKey);
	newSprite.m_hOffScreenDC = GetOffScreenDC();
	newSprite.m_fLifeTime = 7.2f;
	newSprite.m_fSecPerRender = newSprite.m_fLifeTime / newSprite.m_iFrameCount;
	newSprite.Load(get<1>(motionSpriteList[index]), get<2>(motionSpriteList[index]));
	SetMotionSprite(newSprite);
	index++;

	// Bazzi ready sprite
	newSprite.m_iKey = I_SpriteManager.LoadSprite(get<0>(motionSpriteList[index]));
	newSprite = *I_SpriteManager.GetPtr(newSprite.m_iKey);
	newSprite.m_hOffScreenDC = GetOffScreenDC();
	newSprite.m_fLifeTime = 2.5f;
	newSprite.m_fSecPerRender = newSprite.m_fLifeTime / newSprite.m_iFrameCount;
	newSprite.Load(get<1>(motionSpriteList[index]), get<2>(motionSpriteList[index]));
	SetMotionSprite(newSprite);
	index++;

	// Bazzi trap and dead sprite
	for (index; index < motionSpriteList.size(); index++)
	{
		float fAnimTime = (index % 2 != 0) ? kHeroTrapAnimLifeTime : kHeroDeadAnimLifeTime;
		newSprite.m_iKey = I_SpriteManager.LoadSprite(get<0>(motionSpriteList[index]));
		newSprite = *I_SpriteManager.GetPtr(newSprite.m_iKey);
		newSprite.m_hOffScreenDC = GetOffScreenDC();
		newSprite.m_fLifeTime = fAnimTime;
		newSprite.m_fSecPerRender = newSprite.m_fLifeTime / newSprite.m_iFrameCount;
		newSprite.Load(get<1>(motionSpriteList[index]), get<2>(motionSpriteList[index]));

		SetMotionSprite(newSprite);
	}
}

//--------------------------------------------------------------------------------------
// Create visual item and ui sprites
//--------------------------------------------------------------------------------------
void Bazzi::CreateVisualSprites()
{
	Hero::CreateVisualSprites();
}

//--------------------------------------------------------------------------------------
// Move
//--------------------------------------------------------------------------------------
bool Bazzi::MoveUp(Node* pNode)
{
	bool bPressKey = Hero::MoveUp(pNode);
	if (bPressKey == true)
	{
		SetSpriteRect(L"BazziMoveUp", kHeroAnimLifeTime);
	}
	return bPressKey;
}

bool Bazzi::MoveDown(Node* pNode)
{
	bool bPressKey = Hero::MoveDown(pNode);
	if (bPressKey == true)
	{
		SetSpriteRect(L"BazziMoveDown", kHeroAnimLifeTime);
	}
	return bPressKey;
}

bool Bazzi::MoveLeft(Node* pNode)
{
	bool bPressKey = Hero::MoveLeft(pNode);
	if (bPressKey == true)
	{
		SetSpriteRect(L"BazziMoveLeft", kHeroAnimLifeTime);
	}
	return bPressKey;
}

bool Bazzi::MoveRight(Node* pNode)
{
	bool bPressKey = Hero::MoveRight(pNode);
	if (bPressKey == true)
	{
		SetSpriteRect(L"BazziMoveRight", kHeroAnimLifeTime);
	}
	return bPressKey;
}

Bazzi::Bazzi()
{
}


Bazzi::~Bazzi()
{
}
