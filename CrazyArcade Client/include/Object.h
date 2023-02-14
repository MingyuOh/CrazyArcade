#pragma once
#include "SpriteManager.h"
#include "BitmapManager.h"
#include "CoreSTD.h"
#include "Collision.h"
#include "BoundingBox.h"
#include "Wireframe.h"

enum class OBJECT_TYPE
{
	NONE,
	TILE,
	ITEM,
	WATER_BOMB,
	HERO
};

class Object
{
private:
	HDC				m_hOffScreenDC;			// Back screen buffer
	Sprite*			m_pSprite;				// Sprite
	POINT_F			m_vPos;					// Object position
	POINT_F			m_vRenderPos;			// Object render position
	POINT_F			m_vObjectCenterLength;	// Object center length
	RECT			m_rtObject;				// Object rect
	int				m_iKey;					// Bitmap key
	int				m_iKeyMask;				// BitmapMask key
	DRAWTYPE		m_iDrawType;			// Draw object type
	OBJECT_TYPE		m_eType;				// Object type
	Collision		m_Collision;			// Collision data
	BoundingBox		m_BoundingBox;			// Boundingbox
	Wireframe		m_Wireframe;			// WIreframe

	T_STR			m_pszObjectName;		// Object name
	int				m_iObjectIndex;			// Object index
	int				m_iSpriteKey;			// Object sprite key
public:
	//--------------------------------------------------------------------------------------
	// Create Object
	//--------------------------------------------------------------------------------------
	bool			Create(HDC hOffScreenDC, POINT_F pos, RECT rt, T_STR szSpriteName = _T(""), T_STR szLoadFile = _T(""), T_STR szLoadMaskFile = _T(""));
	//--------------------------------------------------------------------------------------
	// Create Wireframe
	//--------------------------------------------------------------------------------------
	bool			CreateWireframe();
	//--------------------------------------------------------------------------------------
	// Color Value process Transparency Function
	//--------------------------------------------------------------------------------------
	bool			ColorKeyDraw(COLORREF color);
	//--------------------------------------------------------------------------------------
	// Update render position
	//--------------------------------------------------------------------------------------
	void			UpdateRenderPosition();
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void			SetOffScreenDC(HDC hScreenDC);
	void			SetPosition(const POINT_F pos);
	void			SetObjectCenterLength(const POINT_F vLength);
	void			SetRect(const RECT rt);
	void			SetBitmapKey(const int iBitmapKey);
	void			SetBitmapMaskKey(const int iBitmapMaskKey);
	void			SetDrawType(const DRAWTYPE iDrawType);
	void			SetObjectType(const OBJECT_TYPE eObjectype);
	void			SetObjectName(T_STR objName);
	void			SetObjectIndex(const int index);
	void			SetSprite(Sprite* sprite);
	void			SetSpriteRect(T_STR spriteName, float fSpriteLifeTime = 1.0f);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	HDC				GetOffScreenDC();
	POINT_F			GetPosition();
	POINT_F			GetRenderPosition();
	POINT_F			GetObjectCenterLength();
	RECT			GetRect();
	int				GetBitmapKey();
	int				GetBitmapMaskKey();
	DRAWTYPE		GetDrawType();
	OBJECT_TYPE		GetObjectType();
	Collision		GetCollision();
	BoundingBox&	GetBoundingBox();
	Wireframe&		GetWireframe();
	T_STR			GetObjectName();
	int				GetObjectIndex();
	Sprite*			GetSprite();
	//--------------------------------------------------------------------------------------
	// Developer Redefinition Function
	//--------------------------------------------------------------------------------------
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
private:
	bool			Load(T_STR spriteName, T_STR pszLoadFile, T_STR pszLoadMaskFile = NULL);
public:
	Object();
	~Object();
};

