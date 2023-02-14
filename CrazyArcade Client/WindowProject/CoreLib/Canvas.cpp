#include "Canvas.h"

//--------------------------------------------------------------------------------------
// Create Canvas
//--------------------------------------------------------------------------------------
bool Canvas::Create(HDC hOffScreenDC, POINT_F pos, RECT rt, T_STR szSpriteName, T_STR szLoadFile, T_STR szLoadMaskFile)
{
	this->m_szCanvasName = szSpriteName;
	this->Object::Create(hOffScreenDC, pos, rt, _T(""), szLoadFile, szLoadMaskFile);
	this->GetSprite()->m_vObjectRenderPos = pos;
	return true;
}

//--------------------------------------------------------------------------------------
// Set function
//--------------------------------------------------------------------------------------
void Canvas::SetCanvasName(const T_STR szCanvasName)
{
	m_szCanvasName = szCanvasName;
}

//--------------------------------------------------------------------------------------
// Get function
//--------------------------------------------------------------------------------------
T_STR Canvas::GetCanvasName()
{
	return m_szCanvasName;
}

Canvas::Canvas()
{

}

Canvas::~Canvas()
{

}