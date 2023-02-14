#pragma once
#include "SceneManager.h"
#include "Button.h"

class LoginScene :public Singleton<LoginScene>, public SceneManager, public Window
{
private:
	Object			m_SignUpPanel;
	bool			m_bSignUp;
private:
	friend class Singleton<LoginScene>;
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
	// Create sign up UI
	//--------------------------------------------------------------------------------------
	void			CreateSignUpUI();
	void			CreateSignUpResources();
	void			CreateSignUpButton();
	//--------------------------------------------------------------------------------------
	// Create sign in UI
	//--------------------------------------------------------------------------------------
	void			CreateSignInUI();
	void			CreateSignInResources();
	void			CreateSignInButton();
	//--------------------------------------------------------------------------------------
	// Update
	//--------------------------------------------------------------------------------------
	bool			Update();
	//--------------------------------------------------------------------------------------
	// Update sign up
	//--------------------------------------------------------------------------------------
	bool			UpdateSignUpButton(POINT vCurrentMousePos);
	//--------------------------------------------------------------------------------------
	// Update sign in
	//--------------------------------------------------------------------------------------
	bool			UpdateSignInButton(POINT vCurrentMousePos);
	//--------------------------------------------------------------------------------------
	// Update resources
	//--------------------------------------------------------------------------------------
	bool			UpdateResources() override;
	//--------------------------------------------------------------------------------------
	// Sign in
	//--------------------------------------------------------------------------------------
	void			SignIn();
	//--------------------------------------------------------------------------------------
	// Sign up
	//--------------------------------------------------------------------------------------
	void			SignUp();
	//--------------------------------------------------------------------------------------
	// Reset sign up edit box
	//--------------------------------------------------------------------------------------
	void			ResetSignUpEditBox();
	void			ResetSignUpEditBox(HWND& hIDEdit, HWND& hPasswordEdit,
										HWND& hPasswordConfirmEdit, HWND& hNickNameEdit,
										HWND& hEmailEdit);
	//--------------------------------------------------------------------------------------
	// Get sign up edit box
	//--------------------------------------------------------------------------------------
	void			GetSignUpEditBox(HWND& hIDEdit, HWND& hPasswordEdit, 
									 HWND& hPasswordConfirmEdit, HWND& hNickNameEdit, 
									 HWND& hEmailEdit);
	//--------------------------------------------------------------------------------------
	// Reset sign in edit box
	//--------------------------------------------------------------------------------------
	void			ResetSignInEditBox();
	void			ResetSignInEditBox(HWND& hIDEdit, HWND& hPasswordEdit);
	//--------------------------------------------------------------------------------------
	// Get sign in edit box
	//--------------------------------------------------------------------------------------
	void			GetSignInEditBox(HWND& hIDEdit, HWND& hPasswordEdit);
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	bool			Init() override;
	bool			Frame() override;
	bool			Render() override;
	bool			Release() override;
public:
	LoginScene();
	~LoginScene();
};
#define I_LoginScene LoginScene::GetInstance()
