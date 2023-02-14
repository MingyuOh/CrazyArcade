#include "LobbyScene.h"

//--------------------------------------------------------------------------------------
// Create lobby background
//--------------------------------------------------------------------------------------
void LobbyScene::CreateBackGround()
{
	T_STR path = _T("../../data/BackGround/LobbySceneBackGround.bmp");
	T_STR spriteName = _T("LobbySceneBackGround");

	// Lobby background
	Create(GetOffScreenDC(), GetPosition(), g_rtClient, _T(""), path, _T(""));
}

//--------------------------------------------------------------------------------------
// Create UI
//--------------------------------------------------------------------------------------
void LobbyScene::CreateUI()
{
	CreateResources();
	CreatePanel();
	CreateButton();
}

//--------------------------------------------------------------------------------------
// Create sign in UI
//--------------------------------------------------------------------------------------
void LobbyScene::CreateResources()
{
	HWND hEdit;
	HWND hButton;
	HWND hListBox;

	DWORD style = WS_CHILDWINDOW | ES_LEFT | ES_MULTILINE | ES_NOHIDESEL | ES_AUTOVSCROLL;
	hEdit = CreateWindow(L"EDIT", NULL, style,
		188, g_rtClient.bottom - 75, 220, 20,
		g_hWnd, (HMENU)200, g_hInstance, NULL);

	style = WS_CHILD;
	hButton = CreateWindow(L"BUTTON", L"<-", style,
		415, g_rtClient.bottom - 80, 30, 30,
		g_hWnd, (HMENU)210, g_hInstance, NULL);

	style = WS_CHILD | ES_AUTOVSCROLL | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOSEL;
	hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL, style,
		25, 410, 420, 110,
		g_hWnd, (HMENU)220, g_hInstance, NULL);

	vector<pair<T_STR, HWND>> editBox;
	editBox.push_back(make_pair(_T("ChattingInput"), hEdit));
	m_hEditList.insert(make_pair(_T("Lobby"), editBox));
	m_hButtonList.push_back(hButton);
	m_hListBoxList.push_back(hListBox);
}

void LobbyScene::CreatePanel()
{
	Canvas firstPlayerReadyUI;
	RECT rtFirstPlayerReady = { 0, 0, 56, 15 };
	POINT_F vFristPlayerReadyPos(48.0f, 217.0f);
	firstPlayerReadyUI.Create(GetOffScreenDC(), vFristPlayerReadyPos, rtFirstPlayerReady, _T("Ready1"), _T("../../data/UI/Ready.bmp"), _T(""));
	m_CanvasList.push_back(make_pair(false, firstPlayerReadyUI));

	Canvas secondPlayerReadyUI;
	RECT rtSecondPlayerReady = { 0, 0, 56, 15 };
	POINT_F vSecondPlayerReadyPos(155.0f, 217.0f);
	secondPlayerReadyUI.Create(GetOffScreenDC(), vSecondPlayerReadyPos, rtSecondPlayerReady, _T("Ready2"), _T("../../data/UI/Ready.bmp"), _T(""));
	m_CanvasList.push_back(make_pair(false, secondPlayerReadyUI));
}

void LobbyScene::CreateButton()
{
	Button button;
	vector<Button> buttons;

	RECT rtReadyButton;
	rtReadyButton.left = g_rtClient.right / 2 + 116;
	rtReadyButton.top = g_rtClient.bottom - 104;
	rtReadyButton.right = rtReadyButton.left + 185;
	rtReadyButton.bottom = rtReadyButton.top + 50;

	button.CreateButton(_T("Ready"), rtReadyButton);
	buttons.push_back(button);

	RECT rtBackButton;
	rtBackButton.left = 15;
	rtBackButton.top = g_rtClient.bottom - 25;
	rtBackButton.right = rtBackButton.left + 28;
	rtBackButton.bottom = rtBackButton.top + 20;

	button.CreateButton(_T("Back"), rtBackButton);
	buttons.push_back(button);

	m_ButtonList.insert(make_pair(_T("Lobby"), buttons));
}

//--------------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------------
bool LobbyScene::UpdateFrame()
{
	if (m_bSceneChange == false)
	{
		POINT vCurrentMousePos = I_Input.m_MousePos;
		UpdateButton(vCurrentMousePos);
	}
	return true;
}

bool LobbyScene::UpdateRender()
{
	Object::Render();
	for (auto& player : m_players)
	{
		player->Render();
		RenderNickName();
	}

	for (auto& readyUI : m_CanvasList)
	{
		if (readyUI.first == true)
		{
			readyUI.second.Render();
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Update resources
//--------------------------------------------------------------------------------------
bool LobbyScene::UpdateResources()
{
	if (g_eGameSceneState == eGameSceneState::LOBBY_SCENE && m_bSceneChange == false)
	{
		for (auto& editBox : m_hEditList.at(_T("Lobby")))
		{
			ShowWindow(editBox.second, SW_SHOW);
		}

		for (auto& listBox : m_hListBoxList)
		{
			ShowWindow(listBox, SW_SHOW);
		}

		for (auto& button : m_hButtonList)
		{
			ShowWindow(button, SW_SHOW);
		}
	}
	else
	{
		for (auto& editBox : m_hEditList.at(_T("Lobby")))
		{
			ShowWindow(editBox.second, SW_HIDE);
		}

		for (auto& listBox : m_hListBoxList)
		{
			ShowWindow(listBox, SW_HIDE);
		}

		for (auto& button : m_hButtonList)
		{
			ShowWindow(button, SW_HIDE);
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Update sign up
//--------------------------------------------------------------------------------------
bool LobbyScene::UpdateButton(POINT vCurrentMousePos)
{
	for (auto& button : m_ButtonList.at(_T("Lobby")))
	{
		if (Button::ClickButtonEvent(button, vCurrentMousePos) == true)
		{
			// Ready button
			if (button.GetButtonName() == _T("Ready"))
			{
				for (int index = 0; index < m_CanvasList.size(); index++)
				{
					if (g_iPlayerNumber == index)
					{
						m_CanvasList[index].first = !m_CanvasList[index].first;
						bool bReady = m_CanvasList[index].first;
#ifdef NETWORK
						I_AsyncSelect.SendReady(bReady, g_iPlayerNumber, PACKET_LOBBY_READY);
#else
						g_eGameSceneState = eGameSceneState::GAME_SCENE;
						I_GameSound.Stop(static_cast<int>(eGameSoundList::LOBBY));
						ResetLobbyScene();
#endif
						break;
					}
				}
			}

			// Back button
			if (button.GetButtonName() == _T("Back"))
			{
				m_bSceneChange = !m_bSceneChange;
				I_AsyncSelect.Release();
				m_eSceneStateEvent = eGameSceneState::LOGIN_SCENE;
				I_GameSound.Stop(static_cast<int>(eGameSoundList::LOBBY));
				UpdateResources();
			}
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Render nickname
//--------------------------------------------------------------------------------------
void LobbyScene::RenderNickName()
{
	for (auto& textUI : m_TextUIList)
	{
		textUI.Render();
	}
}

//--------------------------------------------------------------------------------------
// Reset lobby scene data
//--------------------------------------------------------------------------------------
void LobbyScene::ResetLobbyScene()
{
	for (auto& ui : m_CanvasList)
	{
		ui.first = false;
	}
	m_bSceneChange = false;
	m_bIsLoad = false;
}

//--------------------------------------------------------------------------------------
// Developer Redefinition Function
//--------------------------------------------------------------------------------------
bool LobbyScene::Init()
{
	SceneManager::Init();

	CreateBackGround();

	CreateUI();

	return true;
}

bool LobbyScene::Frame()
{
	ExecuteInit();
	I_GameSound.PlayOnceInLoopProcess(static_cast<int>(eGameSoundList::LOBBY), false, true);
#ifdef NETWORK
	NetworkProcess();
	NetworkCheckDropPlayerState();
#endif
	if (m_bIsLoad == true)
	{
		Object::Frame();

		for (auto& player : m_players)
		{
			player->Frame();
		}

		UpdateFrame();
	}

	return true;
}

bool LobbyScene::Render()
{
	if (m_bIsLoad == true)
	{
		UpdateRender();
		if (m_bSceneChange == true)
		{
			if (m_FadeInOut.FadeOut() == true)
			{
				g_eGameSceneState = m_eSceneStateEvent;
				I_GameSound.Stop(static_cast<int>(eGameSoundList::LOBBY));
				I_GameSound.m_bOncePlay = false;
#ifdef NETWORK
				I_AsyncSelect.SendEventMessage(PACKET_SCENE_CHANGE);
#endif
				ResetLobbyScene();
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

bool LobbyScene::Release()
{
	SceneManager::Release();

	for (auto& readyUI : m_CanvasList)
	{
		if (readyUI.first == true)
		{
			readyUI.second.Release();
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Network
//--------------------------------------------------------------------------------------
bool LobbyScene::NetworkProcess()
{
	for (auto& packet : I_AsyncSelect.m_LobbyPacketPool)
	{
		switch (packet.data.ph.type)
		{
			case PACKET_USER_DROP:
			{
				EVENT_PACKET* dropPacket = (EVENT_PACKET*)&packet;
				int iDropPlayerNumber = atoi(dropPacket->eventData);
				for (int index = 0; index < m_players.size(); index++)
				{
					if (m_players[index]->GetID() == iDropPlayerNumber)
					{
						SAFE_DEL(m_players[index]);
						m_players.erase(m_players.begin() + index);
					}
				}
			}break;
			case PACKET_GAME_START:
			{
				EVENT_GAME_INIT* pPacket = (EVENT_GAME_INIT*)&packet;
				int index = 0;
				eItemType itemType = eItemType::NONE;

				for (int iCount = 0; iCount < kItemTotalCount; iCount++)
				{
					index = pPacket->data.tileIndex[iCount];
					itemType = static_cast<eItemType>(pPacket->data.itemInfo[iCount]);
					g_ItemSpawnInfo.insert(make_pair(index, itemType));
				}
				m_eSceneStateEvent = eGameSceneState::GAME_SCENE;
				m_bSceneChange = !m_bSceneChange;
				UpdateResources();
			}break;
			case PACKET_LOBBY_READY:
			{
				int index = atoi(&packet.data.playerNumber);
				m_CanvasList[index].first = packet.data.ready;
			}break;
			case PACKET_CONNECT_LOBBY:
			{
				int iSlot = atoi(&packet.data.playerNumber);

				Hero* newPlayer = nullptr;
				SAFE_NEW(newPlayer, Bazzi);
				newPlayer->SetOffScreenDC(GetOffScreenDC());
				newPlayer->CreateHero();
				newPlayer->SetID(iSlot);
				newPlayer->SetUserData(I_DB.GetCurrentUser());

				POINT_F vPos;
				if (iSlot == 0)
				{
					vPos.fX = 45.0f;
					vPos.fY = 125.0f;
					newPlayer->SetLobbyPosition(vPos);
				}
				else
				{
					vPos.fX = 155.0f;
					vPos.fY = 125.0f;
					newPlayer->SetLobbyPosition(vPos);
				}

				// Set boundingbox
				RECT rtHero;
				rtHero.left = newPlayer->GetPosition().fX;
				rtHero.top = newPlayer->GetPosition().fY;
				rtHero.right = rtHero.left + kObjectWidthSize;
				rtHero.bottom = rtHero.top + kObjectHeightSize;
				newPlayer->GetBoundingBox().SetBoundingBoxInfo(rtHero);

				m_players.push_back(newPlayer);

				if (packet.data.myPacket == true)
				{
					g_iPlayerNumber = atoi(&packet.data.playerNumber);
				}
			}break;
			case PACKET_CHAT_MSG:
			{
				int index = SendMessageW(I_LobbyScene.m_hListBoxList[0], LB_ADDSTRING, 0, (LPARAM)packet.data.chatData.msg);
				::SendMessageW(I_LobbyScene.m_hListBoxList[0], LB_SETCURSEL, index, 0);
				::SendMessageW(I_LobbyScene.m_hListBoxList[0], LB_SETCURSEL, -1, 0);
			}break;
		}
	}

	I_AsyncSelect.m_LobbyPacketPool.clear();

	return true;
}

bool LobbyScene::NetworkCheckDropPlayerState()
{
	if (g_iDropPlayerNumber != NETWORK_NOT_DROP_PLAYER)
	{
		for (int index = 0; index < m_players.size(); index++)
		{
			if (m_players[index]->GetID() == g_iDropPlayerNumber)
			{
				SAFE_DEL(m_players[index]);
				m_players.erase(m_players.begin() + index);
				g_iDropPlayerNumber = NETWORK_NOT_DROP_PLAYER;
				return true;
			}
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Window message
//--------------------------------------------------------------------------------------
LRESULT LobbyScene::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 200:
		{
			LOBBY_PACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			for (auto& editBox : m_hEditList.at(_T("Lobby")))
			{
				if (editBox.first == _T("ChattingInput"))
				{
					SendMessageA(editBox.second, WM_GETTEXT, MAX_PATH, (LPARAM)packet.data.chatData.msg);
					packet.data.ph.len = PACKET_HEADER_SIZE + sizeof(packet);
					packet.data.ph.type = PACKET_CHAT_MSG;
					I_AsyncSelect.SendChatMessage(packet.data.chatData.msg, packet.data.ph.type);

					SendMessageA(editBox.second, WM_SETTEXT, 0, (LPARAM)"");
				}
			}
		}break;
		}
	}break;
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	{
	case 100:
	case 300:
	{
		HDC hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(255, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
	}break;
	}break;
	}

	I_Input.MsgProc(hWnd, msg, wParam, lParam);

	return TRUE;
}

LobbyScene::LobbyScene()
{
	m_eSceneStateEvent = eGameSceneState::LOBBY_SCENE;
}

LobbyScene::~LobbyScene()
{

}