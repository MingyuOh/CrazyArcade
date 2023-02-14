#include "Object.h"
bool g_bFileLoadCheck = false;

bool Object::Load(T_STR spriteName, T_STR szLoadFile, T_STR szLoadMaskFile)
{
	if (g_bFileLoadCheck == false)
	{
		I_SpriteManager.FileLoad();
		g_bFileLoadCheck = true;
	}

	m_pSprite = new Sprite();
	if (spriteName.empty() == false)
	{
		m_iSpriteKey = I_SpriteManager.LoadSprite(spriteName);
		*m_pSprite = *I_SpriteManager.GetPtr(m_iSpriteKey);
	}
	else
	{
		m_pSprite->m_szSpriteName[0] = L'\0';
	}
	m_pSprite->Load(szLoadFile, szLoadMaskFile);
	return true;
}

bool Object::Create(HDC hOffScreenDC, POINT_F pos, RECT rt, T_STR szSpriteName, T_STR szLoadFile, T_STR szLoadMaskFile)
{
	m_hOffScreenDC = hOffScreenDC;
	m_vPos = pos;
	m_rtObject = rt;

	// Set render position
	UpdateRenderPosition();

	CreateWireframe();
	Load(szSpriteName, szLoadFile, szLoadMaskFile);

	return Init();
}

//--------------------------------------------------------------------------------------
// Create Wireframe
//--------------------------------------------------------------------------------------
bool Object::CreateWireframe()
{
	m_Wireframe.SetOffScreenDC(GetOffScreenDC());
	m_Wireframe.Create(m_rtObject.right - m_rtObject.left, m_rtObject.bottom - m_rtObject.top);

	return true;
}

//--------------------------------------------------------------------------------------
// Color Value process Transparency Function
//--------------------------------------------------------------------------------------
bool Object::ColorKeyDraw(COLORREF color)
{
	TransparentBlt(m_hOffScreenDC, m_vPos.x, m_vPos.y, m_rtObject.right, m_rtObject.bottom, m_pSprite->m_pBitmap->m_hMemoryDC, m_rtObject.left, m_rtObject.top, m_rtObject.right, m_rtObject.bottom, color);
	return true;
}

//--------------------------------------------------------------------------------------
// Update render position
//--------------------------------------------------------------------------------------
void Object::UpdateRenderPosition()
{
	RECT rtBoundingBox = GetBoundingBox().GetBoundingBoxInfo();
	float fWidthLength = ((rtBoundingBox.right - rtBoundingBox.left) * 0.5f) - (m_rtObject.right * 0.5f);

	POINT_F position;
	position.fX = rtBoundingBox.left + fWidthLength;
	position.fY = rtBoundingBox.bottom - m_rtObject.bottom;

	m_vRenderPos.fX = position.fX;
	m_vRenderPos.fY = position.fY;
}

bool Object::Init()
{
	m_pSprite->m_hOffScreenDC = m_hOffScreenDC;
	m_pSprite->m_currentRect = m_rtObject;
	m_pSprite->m_vObjectRenderPos = m_vRenderPos;
	return true;
}

bool Object::Frame()
{
	UpdateRenderPosition();
	m_pSprite->m_vObjectRenderPos = m_vRenderPos;
	m_pSprite->Frame();
	return true;
}

bool Object::Render()
{
	m_pSprite->Render();
	return true;
}

bool Object::Release()
{
	if (m_pSprite != nullptr)
	{
		SAFE_RELEASE(m_pSprite->m_pBitmap);
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void Object::SetOffScreenDC(HDC hScreenDC)
{
	m_hOffScreenDC = hScreenDC;
}

void Object::SetPosition(const POINT_F pos)
{
	m_vPos = pos;
}

void Object::SetRenderPosition(const POINT_F pos)
{
	m_vRenderPos = pos;
}

void Object::SetObjectCenterLength(const POINT_F vLength)
{
	m_vObjectCenterLength = vLength;
}

void Object::SetRect(const RECT rt)
{
	m_rtObject = rt;
}

void Object::SetBitmapKey(const int iBitmapKey)
{
	m_iKey = iBitmapKey;
}

void Object::SetBitmapMaskKey(const int iBitmapMaskKey)
{
	m_iKeyMask = iBitmapMaskKey;
}

void Object::SetDrawType(const eRenderType iDrawType)
{
	m_iDrawType = iDrawType;
}

void Object::SetObjectType(const OBJECT_TYPE eObjectype)
{
	m_eType = eObjectype;
}

void Object::SetObjectName(T_STR objName)
{
	m_pszObjectName = objName;
}

void Object::SetObjectIndex(const int index)
{
	m_iObjectIndex = index;
}

void Object::SetSprite(Sprite* sprite)
{
	m_pSprite = sprite;
}

void Object::SetSpriteRect(T_STR spriteName, float fSpriteLifeTime)
{
	Sprite newSprite;
	newSprite.m_iIndex = I_SpriteManager.LoadSprite(spriteName);
	newSprite = *I_SpriteManager.GetPtr(newSprite.m_iIndex);

	m_pSprite->SetRectArray(newSprite.m_rectList, newSprite.m_iIndex, newSprite.m_bIsLoop, fSpriteLifeTime);
}

void Object::SetSurvival(const bool bSurvival)
{
	m_bIsSurvival = bSurvival;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
HDC	Object::GetOffScreenDC()
{
	return m_hOffScreenDC;
}

POINT_F Object::GetPosition()
{
	return m_vPos;
}

POINT_F Object::GetRenderPosition()
{
	return m_vRenderPos;
}

POINT_F Object::GetObjectCenterLength()
{
	return m_vObjectCenterLength;
}

RECT Object::GetRect()
{
	return m_rtObject;
}

int	Object::GetBitmapKey()
{
	return m_iKey;
}

int	Object::GetBitmapMaskKey()
{
	return m_iKeyMask;
}

eRenderType Object::GetDrawType()
{
	return m_iDrawType;
}

OBJECT_TYPE Object::GetObjectType()
{
	return m_eType;
}

Collision Object::GetCollision()
{
	return m_Collision;
}

BoundingBox& Object::GetBoundingBox()
{
	return m_BoundingBox;
}

Wireframe& Object::GetWireframe()
{
	return m_Wireframe;
}

T_STR Object::GetObjectName()
{
	return m_pszObjectName;
}

int Object::GetObjectIndex()
{
	return m_iObjectIndex;
}

Sprite* Object::GetSprite()
{
	assert(m_pSprite);
	return m_pSprite;
}

bool Object::GetSurvival()
{
	return m_bIsSurvival;
}

Object::Object()
{
	m_pSprite = nullptr;
	m_iKey = -1;
	m_iKeyMask = -1;
	m_iDrawType = eRenderType::STANDARD;
	m_eType = OBJECT_TYPE::NONE;
	m_bIsSurvival = true;
}

Object::~Object() {}