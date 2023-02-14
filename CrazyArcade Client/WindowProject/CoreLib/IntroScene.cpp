#include "IntroScene.h"

//--------------------------------------------------------------------------------------
// Create lobby background
//--------------------------------------------------------------------------------------
void IntroScene::CreateBackGround()
{
	T_STR path = _T("../../data/BackGround/IntroSceneBackGround.bmp");

	// Ingame background
	Create(GetOffScreenDC(), GetPosition(), g_rtClient, _T(""), path, _T(""));

	path = _T("../../data/BackGround/Logo.bmp");
	m_Logo.Create(GetOffScreenDC(), GetPosition(), g_rtClient, _T(""), path, _T(""));
	m_Logo.GetSprite()->m_vObjectRenderPos = GetPosition();
}

//--------------------------------------------------------------------------------------
// Create UI
//--------------------------------------------------------------------------------------
void IntroScene::CreateUI()
{
	RECT rtStartButton;
	rtStartButton.left = g_rtClient.right / 2 - 80;
	rtStartButton.top = g_rtClient.top + 30;
	rtStartButton.right = rtStartButton.left + 150;
	rtStartButton.bottom = rtStartButton.top + 150;

	vector<Button> buttons;
	Button button;

	button.CreateButton(_T("GameStart"), rtStartButton);
	buttons.push_back(button);
	m_ButtonList.insert(make_pair(_T("Start"), buttons));
}

//--------------------------------------------------------------------------------------
// Developer Redefinition Function
//--------------------------------------------------------------------------------------
bool IntroScene::Init()
{
	CreateBackGround();

	CreateUI();

	SceneManager::Init();

	return true;
}

bool IntroScene::Frame()
{
	if (m_bIsLoad == true)
	{
		Object::Frame();

		if (m_bSceneChange == false)
		{
			for (auto& button : m_ButtonList.at(_T("Start")))
			{
				POINT vCurrentMousePos = I_Input.GetInstance().m_MousePos;
				if (Button::ClickButtonEvent(button, vCurrentMousePos) == true)
				{
					m_bSceneChange = true;
				}
			}
		}
	}
	I_GameSound.Frame();

	return true;
}

bool IntroScene::Render()
{
	if (m_bIsLoad == true)
	{
		I_GameSound.Play(static_cast<int>(eGameSoundList::MAIN), false, true);
		Object::Render();
		if (m_bSceneChange == true)
		{
			if (m_FadeInOut.FadeOut() == true)
			{
				g_eGameSceneState = eGameSceneState::LOGIN_SCENE;
				I_GameSound.Stop(static_cast<int>(eGameSoundList::MAIN));
			}
		}
	}
	else
	{
		I_GameSound.PlayOnceInLoopProcess(static_cast<int>(eGameSoundList::LOGO), false, false);
		m_Logo.Render();
		if (m_FadeInOut.FadeInAndOut() == true)
		{
			m_bIsLoad = true;
		}
	}

	return true;
}

bool IntroScene::Release()
{
	SceneManager::Release();
	return true;
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{

}