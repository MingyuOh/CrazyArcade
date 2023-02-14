#pragma once
#include "SceneManager.h"
#include "Canvas.h"

class StartScene : public Singleton<StartScene>, public SceneManager
{
private:
	Canvas			m_Logo;
	Button			m_StartButton;
private:
	friend class Singleton<StartScene>;
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
	StartScene();
	~StartScene();
};
#define I_StartScene StartScene::GetInstance()
