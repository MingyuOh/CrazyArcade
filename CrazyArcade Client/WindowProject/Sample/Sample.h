#pragma once
#include "Core.h"
#include "Map.h"
#include "CharacterManager.h"
#include "Bazzi.h"
#include "IntroScene.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "GameScene.h"

class Sample :public Core
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Sample();
	virtual ~Sample();
};

