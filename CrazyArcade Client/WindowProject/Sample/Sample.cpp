#include "Sample.h"

bool Sample::Init()
{
	// Create login scene
	I_IntroScene.SetOffScreenDC(m_hOffScreenDC);
	I_IntroScene.Init();

	// Set login scene screenDC
	I_LoginScene.SetOffScreenDC(m_hOffScreenDC);

	// Set lobby scene screenDC
	I_LobbyScene.SetOffScreenDC(m_hOffScreenDC);

	// Set game scene screenDC
	I_GameScene.SetOffScreenDC(m_hOffScreenDC);

	return true;
}

bool Sample::Frame()
{
	switch (g_eGameSceneState)
	{
		case eGameSceneState::INTRO_SCENE:
		{
			I_IntroScene.Frame();
		}break;
		case eGameSceneState::LOGIN_SCENE:
		{
			I_LoginScene.Frame();
		}break;
		case eGameSceneState::LOBBY_SCENE:
		{
			I_LobbyScene.Frame();
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			I_GameScene.Frame();
		}break;
	}
	return true;
}

bool Sample::Render()
{
	switch (g_eGameSceneState)
	{
		case eGameSceneState::INTRO_SCENE:
		{
			I_IntroScene.Render();
		}break;
		case eGameSceneState::LOGIN_SCENE:
		{
			I_LoginScene.Render();
		}break;
		case eGameSceneState::LOBBY_SCENE:
		{
			I_LobbyScene.Render();
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			I_GameScene.Render();
		}break;
	}
	return true;
}

bool Sample::Release()
{
	I_IntroScene.Release();
	I_LoginScene.Release();
	I_LobbyScene.Release();
	return true;
}

LRESULT Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return I_AsyncSelect.MsgProc(hWnd, msg, wParam, lParam);
}

Sample::Sample()
{
}

Sample::~Sample()
{
}
GAME_VER1(Crazy Arcade)
