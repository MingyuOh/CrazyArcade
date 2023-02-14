#pragma once
#include "Window.h"
#include "Input.h"
#include "SpriteManager.h"
#include "BitmapManager.h"
#include "CharacterManager.h"
#include "ObjectManager.h"
#include "GameSound.h"

class Core :public Window
{
public:
	HDC m_hScreenDC;
	HDC m_hOffScreenDC;
	HBRUSH m_hbrBack;
	HBRUSH m_hOldBrush;
	HBITMAP m_hOldBitMap;

	HFONT m_DefaultFont;
public:
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool PreRender();
	virtual bool PostRender();

	bool Run();

private:
	bool GameRun();
	bool GameInit();
	bool GameNetwork();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
public:
	Core();
	virtual ~Core();
};

