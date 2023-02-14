#include "LoginScene.h"

//--------------------------------------------------------------------------------------
// Create lobby background
//--------------------------------------------------------------------------------------
void LoginScene::CreateBackGround()
{
	T_STR path = _T("../../data/BackGround/LoginSceneSignInBackGround.bmp");

	// Ingame background
	Create(GetOffScreenDC(), GetPosition(), g_rtClient, _T(""), path, _T(""));

	path = _T("../../data/BackGround/LoginSceneSignUpBackGround.bmp");
	m_SignUpPanel.Create(GetOffScreenDC(), GetPosition(), g_rtClient, _T(""), path, _T(""));
	m_SignUpPanel.GetSprite()->m_vObjectRenderPos = GetPosition();
}

//--------------------------------------------------------------------------------------
// Create UI
//--------------------------------------------------------------------------------------
void LoginScene::CreateUI()
{
	CreateSignUpUI();
	CreateSignInUI();
}

//--------------------------------------------------------------------------------------
// Create sign up UI
//--------------------------------------------------------------------------------------
void LoginScene::CreateSignUpUI()
{
	CreateSignUpResources();
	CreateSignUpButton();
}

void LoginScene::CreateSignUpResources()
{
	HWND hSignUpIDEdit;
	HWND hSignUpPasswordEdit;
	HWND hSignUpPasswordConfirmEdit;
	HWND hSignUpNameEdit;
	HWND hSignUpEmailEdit;

	DWORD style = WS_CHILDWINDOW | WS_BORDER | ES_LEFT;
	hSignUpIDEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		280, 180, 230, 25,
		g_hWnd, (HMENU)0, g_hInstance, NULL);

	style = WS_CHILDWINDOW | WS_BORDER | ES_LEFT | ES_PASSWORD;
	hSignUpPasswordEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		280, 230, 230, 25,
		g_hWnd, (HMENU)10, g_hInstance, NULL);

	style = WS_CHILDWINDOW | WS_BORDER | ES_LEFT | ES_PASSWORD;
	hSignUpPasswordConfirmEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		280, 280, 230, 25,
		g_hWnd, (HMENU)20, g_hInstance, NULL);

	style = WS_CHILDWINDOW | WS_BORDER | ES_LEFT;
	hSignUpNameEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		280, 335, 230, 25,
		g_hWnd, (HMENU)30, g_hInstance, NULL);

	hSignUpEmailEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		280, 385, 230, 25,
		g_hWnd, (HMENU)40, g_hInstance, NULL);

	vector<pair<T_STR, HWND>> editBoxes;
	editBoxes.push_back(make_pair(_T("SignUpID"), hSignUpIDEdit));
	editBoxes.push_back(make_pair(_T("SignUpPassword"), hSignUpPasswordEdit));
	editBoxes.push_back(make_pair(_T("SignUpPasswordConfirm"), hSignUpPasswordConfirmEdit));
	editBoxes.push_back(make_pair(_T("SignUpName"), hSignUpNameEdit));
	editBoxes.push_back(make_pair(_T("SignUpEmail"), hSignUpEmailEdit));

	m_hEditList.insert(make_pair(_T("SignUp"), editBoxes));
}

void LoginScene::CreateSignUpButton()
{
	vector<Button> buttons;
	Button button;
	RECT rtCreateAccountButton = { 280, 432, 280 + 105,  432 + 30 };
	button.CreateButton(_T("CreateAccount"), rtCreateAccountButton);
	buttons.push_back(button);

	RECT rtExitSignUpButton = { 410, 432, 410 + 105,  432 + 30 };
	button.CreateButton(_T("Cancel"), rtExitSignUpButton);
	buttons.push_back(button);

	m_ButtonList.insert(make_pair(_T("SignUp"), buttons));
}

//--------------------------------------------------------------------------------------
// Create sign in UI
//--------------------------------------------------------------------------------------
void LoginScene::CreateSignInUI()
{
	CreateSignInResources();
	CreateSignInButton();
}

void LoginScene::CreateSignInResources()
{
	HWND hSignInIDEdit;
	HWND hSignInPasswordEdit;
	HWND test;

	DWORD style = WS_CHILDWINDOW | WS_BORDER | ES_LEFT;
	hSignInIDEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		275, 340, 250, 30,
		g_hWnd, (HMENU)100, g_hInstance, NULL);

	style = WS_CHILDWINDOW | WS_BORDER | ES_LEFT | ES_PASSWORD;
	hSignInPasswordEdit = CreateWindowEx(NULL, L"EDIT", NULL, style,
		275, 400, 250, 30,
		g_hWnd, (HMENU)110, g_hInstance, NULL);

	vector<pair<T_STR, HWND>> editBoxes;
	editBoxes.push_back(make_pair(_T("SignInID"), hSignInIDEdit));
	editBoxes.push_back(make_pair(_T("SignInPassword"), hSignInPasswordEdit));

	m_hEditList.insert(make_pair(_T("SignIn"), editBoxes));
}

void LoginScene::CreateSignInButton()
{
	Button button;
	vector<Button> buttons;

	RECT rtSignInButton = { 275, 437, 275 + 120, 437 + 35 };
	button.CreateButton(_T("SignIn"), rtSignInButton);
	buttons.push_back(button);

	RECT rtSignUpButton = { 443, 265, 443 + 80, 265 + 35 };
	button.CreateButton(_T("SignUp"), rtSignUpButton);
	buttons.push_back(button);

	RECT rtExitButton = { 403, 437, 403 + 120, 437 + 35 };
	button.CreateButton(_T("Exit"), rtExitButton);
	buttons.push_back(button);

	m_ButtonList.insert(make_pair(_T("SignIn"), buttons));
}

//--------------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------------
bool LoginScene::Update()
{
	POINT vCurrentMousePos = I_Input.m_MousePos;

	if (m_bSceneChange == false)
	{
		if (m_bSignUp == true)
		{
			UpdateSignUpButton(vCurrentMousePos);
		}
		else
		{
			UpdateSignInButton(vCurrentMousePos);
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Update sign up
//--------------------------------------------------------------------------------------
bool LoginScene::UpdateSignUpButton(POINT vCurrentMousePos)
{
	for (auto& button : m_ButtonList.at(_T("SignUp")))
	{
		if (Button::ClickButtonEvent(button, vCurrentMousePos) == true)
		{
			// 계정 생성 버튼
			if (button.GetButtonName() == _T("CreateAccount"))
			{
				SignUp();
			}

			// 취소 버튼
			if (button.GetButtonName() == _T("Cancel"))
			{
				ResetSignUpEditBox();
			}

			m_bSignUp = false;
			UpdateResources();
			Sleep(100);
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Update sign in
//--------------------------------------------------------------------------------------
bool LoginScene::UpdateSignInButton(POINT vCurrentMousePos)
{
	for (auto& button : m_ButtonList.at(_T("SignIn")))
	{
		if (Button::ClickButtonEvent(button, vCurrentMousePos) == true)
		{
			// 회원가입 버튼
			if (button.GetButtonName() == _T("SignUp"))
			{
				m_bSignUp = true;
				UpdateResources();
			}

			// 로그인 버튼
			if (button.GetButtonName() == _T("SignIn"))
			{
				SignIn();
			}

			// 취소 버튼
			if (button.GetButtonName() == _T("Exit"))
			{
				// 프로그램 종료
				SendMessage(g_hWnd, WM_CLOSE, NULL, NULL);
			}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Update edit box
//--------------------------------------------------------------------------------------
bool LoginScene::UpdateResources()
{
	if (g_eGameSceneState == eGameSceneState::LOGIN_SCENE && m_bSceneChange == false)
	{
		for (auto& signUpEditBox : m_hEditList.at(_T("SignUp")))
		{
			ShowWindow(signUpEditBox.second, (m_bSignUp == true) ? SW_SHOW : SW_HIDE);
		}

		for (auto& signInEditBox : m_hEditList.at(_T("SignIn")))
		{
			ShowWindow(signInEditBox.second, (m_bSignUp == true) ? SW_HIDE : SW_SHOW);
		}
	}
	else
	{
		for (auto& signUpEditBox : m_hEditList.at(_T("SignUp")))
		{
			ShowWindow(signUpEditBox.second, SW_HIDE);
		}

		for (auto& signInEditBox : m_hEditList.at(_T("SignIn")))
		{
			ShowWindow(signInEditBox.second, SW_HIDE);
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Sign in
//--------------------------------------------------------------------------------------
void LoginScene::SignIn()
{
	TCHAR account[MAX_PATH] = { 0, };
	TCHAR password[MAX_PATH] = { 0, };

	HWND hIDEdit = nullptr, hPasswordEdit = nullptr;
	GetSignInEditBox(hIDEdit, hPasswordEdit);


	SendMessageW(hIDEdit, WM_GETTEXT, MAX_PATH, (LPARAM)account);
	SendMessageW(hPasswordEdit, WM_GETTEXT, MAX_PATH, (LPARAM)password);

	if (I_DB.SignIn(account, password) == true)
	{
		ResetSignInEditBox();
		m_bSceneChange = true;
		UpdateResources();
	}
	else
	{
		// 잘못된 패널 렌더링
	}
}

//--------------------------------------------------------------------------------------
// Sign up
//--------------------------------------------------------------------------------------
void LoginScene::SignUp()
{
	TCHAR account[MAX_PATH] = { 0, };
	TCHAR password[MAX_PATH] = { 0, };
	TCHAR passwordConfirm[MAX_PATH] = { 0, };
	TCHAR nickName[MAX_PATH] = { 0, };
	TCHAR email[MAX_PATH] = { 0, };

	HWND hIDEdit = nullptr, hPasswordEdit = nullptr, hPasswordConfirmEdit = nullptr, 
		hNickNameEdit = nullptr, hEmailEdit = nullptr;
	GetSignUpEditBox(hIDEdit, hPasswordEdit, hPasswordConfirmEdit, hNickNameEdit, hEmailEdit);

	SendMessageW(hIDEdit, WM_GETTEXT, MAX_PATH, (LPARAM)account);
	SendMessageW(hPasswordEdit, WM_GETTEXT, MAX_PATH, (LPARAM)password);
	SendMessageW(hPasswordConfirmEdit, WM_GETTEXT, MAX_PATH, (LPARAM)passwordConfirm);
	SendMessageW(hNickNameEdit, WM_GETTEXT, MAX_PATH, (LPARAM)nickName);
	SendMessageW(hEmailEdit, WM_GETTEXT, MAX_PATH, (LPARAM)email);

	// 계정 중복 처리
	if (I_DB.CheckDuplicationAccount(account) == true)
	{
		// UI Show

		return;
	}

	// 비밀번호 검증
	if (I_DB.VerifyPassword(password, passwordConfirm) == false)
	{
		// UI Show

		return;
	}

	// 닉네임 중복 처리
	if (I_DB.CheckDuplicationNickName(nickName) == true)
	{
		// UI Show

		return;
	}

	User user;
	user.CreateUser(account, password, nickName, email);
	if (I_DB.SignUp(user) == true)
	{
		I_DB.InsertUser(user);
		ResetSignUpEditBox(hIDEdit, hPasswordEdit, hPasswordConfirmEdit, hNickNameEdit, hEmailEdit);
	}

}

//--------------------------------------------------------------------------------------
// Reset sign up edit box
//--------------------------------------------------------------------------------------
void LoginScene::ResetSignUpEditBox()
{
	HWND hIDEdit = GetEditBox(_T("SignUp"), _T("SignUpID"));
	HWND hPasswordEdit = GetEditBox(_T("SignUp"), _T("SignUpPassword"));
	HWND hPasswordConfirmEdit = GetEditBox(_T("SignUp"), _T("SignUpPasswordConfirm"));
	HWND hNickNameEdit = GetEditBox(_T("SignUp"), _T("SignUpName"));
	HWND hEmailEdit = GetEditBox(_T("SignUp"), _T("SignUpEmail"));

	SetWindowText(hIDEdit, NULL);
	SetWindowText(hPasswordEdit, NULL);
	SetWindowText(hPasswordConfirmEdit, NULL);
	SetWindowText(hNickNameEdit, NULL);
	SetWindowText(hEmailEdit, NULL);
}

//--------------------------------------------------------------------------------------
// Reset sign up edit box
//--------------------------------------------------------------------------------------
void LoginScene::ResetSignUpEditBox(HWND& hIDEdit, HWND& hPasswordEdit, HWND& hPasswordConfirmEdit, HWND& hNickNameEdit, HWND& hEmailEdit)
{
	hIDEdit = GetEditBox(_T("SignUp"), _T("SignUpID"));
	hPasswordEdit = GetEditBox(_T("SignUp"), _T("SignUpPassword"));
	hPasswordConfirmEdit = GetEditBox(_T("SignUp"), _T("SignUpPasswordConfirm"));
	hNickNameEdit = GetEditBox(_T("SignUp"), _T("SignUpName"));
	hEmailEdit = GetEditBox(_T("SignUp"), _T("SignUpEmail"));

	SetWindowText(hIDEdit, NULL);
	SetWindowText(hPasswordEdit, NULL);
	SetWindowText(hPasswordConfirmEdit, NULL);
	SetWindowText(hNickNameEdit, NULL);
	SetWindowText(hEmailEdit, NULL);
}

//--------------------------------------------------------------------------------------
// Get sign up edit box
//--------------------------------------------------------------------------------------
void LoginScene::GetSignUpEditBox(HWND& hIDEdit, HWND& hPasswordEdit, HWND& hPasswordConfirmEdit, HWND& hNickNameEdit, HWND& hEmailEdit)
{
	hIDEdit = GetEditBox(_T("SignUp"), _T("SignUpID"));
	hPasswordEdit = GetEditBox(_T("SignUp"), _T("SignUpPassword"));
	hPasswordConfirmEdit = GetEditBox(_T("SignUp"), _T("SignUpPasswordConfirm"));
	hNickNameEdit = GetEditBox(_T("SignUp"), _T("SignUpName"));
	hEmailEdit = GetEditBox(_T("SignUp"), _T("SignUpEmail"));

	assert(hIDEdit);
	assert(hPasswordEdit);
	assert(hPasswordConfirmEdit);
	assert(hNickNameEdit);
	assert(hEmailEdit);
}

//--------------------------------------------------------------------------------------
// Reset sign in edit box
//--------------------------------------------------------------------------------------
void LoginScene::ResetSignInEditBox()
{
	HWND hIDEdit = GetEditBox(_T("SignIn"), _T("SignInID"));
	HWND hPasswordEdit = GetEditBox(_T("SignIn"), _T("SignInPassword"));

	SetWindowText(hIDEdit, NULL);
	SetWindowText(hPasswordEdit, NULL);
}

void LoginScene::ResetSignInEditBox(HWND& hIDEdit, HWND& hPasswordEdit)
{
	hIDEdit = GetEditBox(_T("SignIn"), _T("SignInID"));
	hPasswordEdit = GetEditBox(_T("SignIn"), _T("SignInPassword"));

	SetWindowText(hIDEdit, NULL);
	SetWindowText(hPasswordEdit, NULL);
}

//--------------------------------------------------------------------------------------
// Get sign in edit box
//--------------------------------------------------------------------------------------
void LoginScene::GetSignInEditBox(HWND& hIDEdit, HWND& hPasswordEdit)
{
	hIDEdit = GetEditBox(_T("SignIn"), _T("SignInID"));
	hPasswordEdit = GetEditBox(_T("SignIn"), _T("SignInPassword"));

	assert(hIDEdit);
	assert(hPasswordEdit);
}

//--------------------------------------------------------------------------------------
// Developer redefinition function
//--------------------------------------------------------------------------------------
bool LoginScene::Init()
{
	SceneManager::Init();

	CreateBackGround();

	CreateUI();

	I_DB.LoadUserData();

	return true;
}

bool LoginScene::Frame()
{
	ExecuteInit();
	I_GameSound.Play(static_cast<int>(eGameSoundList::MAIN), false, true);
	if (m_bIsLoad == true)
	{
		Update();
	}

	return true;
}

bool LoginScene::Render()
{
	if(m_bIsLoad == true)
	{
		if (m_bSignUp == true)
		{
			m_SignUpPanel.Render();
		}
		else
		{
			Object::Render();
			if (m_bSceneChange == true)
			{
				if (m_FadeInOut.FadeOut() == true)
				{
					g_eGameSceneState = eGameSceneState::LOBBY_SCENE;
					I_GameSound.Stop(static_cast<int>(eGameSoundList::MAIN));
					I_GameSound.m_bOncePlay = false;
					m_bSceneChange = false;
					m_bIsLoad = false;
				}
			}
		}
	}
	else
	{
		Object::Render();
		if (m_FadeInOut.FadeIn() == true)
		{
			UpdateResources();
			m_bIsLoad = true;
		}
	}

	return true;
}

bool LoginScene::Release()
{
	SceneManager::Release();

	for (auto& edits : m_hEditList)
	{
		for (auto& editBox : edits.second)
		{
			editBox.first = _T("");
			SAFE_DEL(editBox.second);
		}
	}
	return true;
}

LoginScene::LoginScene()
{
	m_bSignUp = false;
	m_bInit = false;
}

LoginScene::~LoginScene()
{

}