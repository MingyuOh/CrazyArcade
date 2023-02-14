#pragma once
#include "SceneManager.h"
#include "Canvas.h"

class IntroScene : public Singleton<IntroScene>, public SceneManager
{
private:
	Canvas			m_Logo;
	Button			m_StartButton;
private:
	friend class Singleton<IntroScene>;
public:
	//--------------------------------------------------------------------------------------
	// Create login background
	//--------------------------------------------------------------------------------------
	void			CreateBackGround() override;
	//--------------------------------------------------------------------------------------
	// Create login UI
	//--------------------------------------------------------------------------------------
	void			CreateUI() override;
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	bool			Init() override;
	bool			Frame() override;
	bool			Render() override;
	bool			Release() override;
public:
	IntroScene();
	~IntroScene();
};
#define I_IntroScene IntroScene::GetInstance()
