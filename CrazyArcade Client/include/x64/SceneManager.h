#pragma once
#include "Window.h"
#include "Input.h"
#include "Button.h"
#include "Canvas.h"
#include "DataBase.h"
#include "FadeInOut.h"

class SceneManager abstract :public Object, public Window
{
public:
	map<T_STR, vector<pair<T_STR, HWND>>>	m_hEditList;
	vector<HWND>							m_hButtonList;
	vector<HWND>							m_hListBoxList;
	map<T_STR, vector<Button>>				m_ButtonList;
	vector<pair<bool, Canvas>>				m_CanvasList;
	FadeInOut								m_FadeInOut;
	bool									m_bInit;
	bool									m_bIsLoad;
	bool									m_bSceneChange;
protected:
	//--------------------------------------------------------------------------------------
	// Create background
	//--------------------------------------------------------------------------------------
	virtual void		CreateBackGround() abstract;
	//--------------------------------------------------------------------------------------
	// Create background
	//--------------------------------------------------------------------------------------
	virtual void		CreateUI() abstract;
	//--------------------------------------------------------------------------------------
	// Update resources
	//--------------------------------------------------------------------------------------
	virtual bool		UpdateResources();
	//--------------------------------------------------------------------------------------
	// Update render Position
	//--------------------------------------------------------------------------------------
	void				UpdateRenderPosition() override;
	//--------------------------------------------------------------------------------------
	// Executes Init once when the scene is called
	//--------------------------------------------------------------------------------------
	bool				ExecuteInit();

	HWND				GetEditBox(T_STR szLargeCategory, T_STR szSmallCartegory);
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	//--------------------------------------------------------------------------------------
	// Network
	//--------------------------------------------------------------------------------------
	virtual bool		NetworkProcess();
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
public:
	SceneManager();
	~SceneManager();
};

