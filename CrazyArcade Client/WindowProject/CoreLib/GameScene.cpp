#include "GameScene.h"
#include "LobbyScene.h"

//--------------------------------------------------------------------------------------
// Create background
//--------------------------------------------------------------------------------------
void GameScene::CreateBackGround()
{
	// Create map
	m_pMap = new Map();
	m_pMap->SetOffScreenDC(GetOffScreenDC());
	m_pMap->Init();
#ifdef NETWORK
#else
	m_pMap->Init();
#endif // NETWORK
}

//--------------------------------------------------------------------------------------
// Create background
//--------------------------------------------------------------------------------------
void GameScene::CreateUI()
{
	POINT_F pos = { static_cast<float>(g_rtClient.right / 2 - 210), static_cast<float>(g_rtClient.bottom / 2 - 65) };
	RECT rtUI = { 0, 0, 300, 65 };

	Canvas startUI;
	startUI.Create(GetOffScreenDC(), pos, rtUI, _T("Start"), _T("../../data/UI/Start.bmp"), _T("../../data/UI/StartMask.bmp"));
	m_UIList.push_back(startUI);

	Canvas winUI;
	winUI.Create(GetOffScreenDC(), pos, rtUI, _T("Win"), _T("../../data/UI/Win.bmp"), _T("../../data/UI/WinMask.bmp"));
	m_UIList.push_back(winUI);

	Canvas loseUI;
	loseUI.Create(GetOffScreenDC(), pos, rtUI, _T("Lose"), _T("../../data/UI/Lose.bmp"), _T("../../data/UI/LoseMask.bmp"));
	m_UIList.push_back(loseUI);
}

//--------------------------------------------------------------------------------------
// Create player
//--------------------------------------------------------------------------------------
void GameScene::CreatePlayer(int id, POINT_F vPos)
{
	Hero* newHero = nullptr;
	SAFE_NEW(newHero, Bazzi);
	newHero->SetOffScreenDC(GetOffScreenDC());
	newHero->CreateHero(vPos);
	newHero->SetMap(m_pMap);
	newHero->Init();
	newHero->SetID(id);
#ifdef NETWORK
	if (id == g_iPlayerNumber)
	{
		newHero->SetActivation(true);
	}
#endif // NETWORK

	m_players.push_back(newHero);
}

//--------------------------------------------------------------------------------------
// Data initialization
//--------------------------------------------------------------------------------------
void GameScene::InitializationData()
{
	m_UIList.clear();
	for (auto& player : m_players)
	{
		SAFE_DEL(player);
	}
	m_players.clear();
	SAFE_DEL(m_pMap);
	SAFE_ZERO(m_pMap);
	m_fElapsedWaitTime = 0.0f;
	m_fElapsedOverTime = 0.0f;
	g_bGameStart = false;
	g_bGameOver = false;
	m_bSceneChange = false;
	m_bIsLoad = false;
	m_bInit = false;
	m_szActivationUIName = _T("Start");
	m_eResultGameSound = eGameSoundList::LOSE;
	g_ItemSpawnInfo.clear();
	I_GameSound.m_bOncePlay = false;
}

//--------------------------------------------------------------------------------------
// Check waiting time to start the game
//--------------------------------------------------------------------------------------
bool GameScene::CheckWaitTimeToGameStart()
{
	if (m_fElapsedWaitTime >= GAME_WAIT_TIME)
	{
		g_bGameStart = true;
		return true;
	}

	AccumulateWaitTimeToGameStart();
	return false;
}

//--------------------------------------------------------------------------------------
// Accumulate waiting time to start the game
//--------------------------------------------------------------------------------------
void GameScene::AccumulateWaitTimeToGameStart()
{
	m_fElapsedWaitTime += g_fSecPerFrame;
}

//--------------------------------------------------------------------------------------
// Check waiting time to over the game
//--------------------------------------------------------------------------------------
bool GameScene::CheckWaitTimeToGameOver()
{
	if (m_fElapsedOverTime >= GAME_WAIT_TIME)
	{
		m_bSceneChange = true;
		return true;
	}

	AccumulateWaitTimeToGameOver();
	return false;
}

//--------------------------------------------------------------------------------------
// Accumulate waiting time to over the game
//--------------------------------------------------------------------------------------
void GameScene::AccumulateWaitTimeToGameOver()
{
	m_fElapsedOverTime += g_fSecPerFrame;
}

//--------------------------------------------------------------------------------------
// Game start
//--------------------------------------------------------------------------------------
bool GameScene::GameStartFrame()
{
	if (g_bGameStart == false)
	{
		I_GameSound.PlayOnceInLoopProcess(static_cast<int>(eGameSoundList::START), true, false);
	}

	// Character frame
	for (auto& player : m_players)
	{
		player->Frame();
	}

	if (CheckWaitTimeToGameStart() == true)
	{
		// Map frame
		m_pMap->Frame();
		return true;
	}

	return false;
}

bool GameScene::GameStartRender()
{
	// Game start ui rendering
	if (CheckWaitTimeToGameStart() == false)
	{
		for (auto& ui : m_UIList)
		{
			if (ui.GetCanvasName() == m_szActivationUIName)
			{
				ui.Render();
				break;
			}
		}
	}

	if (m_bIsLoad == false)
	{
		if (m_FadeInOut.FadeIn() == true)
		{
			m_bIsLoad = true;
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Game over
//--------------------------------------------------------------------------------------
bool GameScene::GameOverFrame()
{
	if (g_bGameOver == true)
	{
		I_GameSound.Stop(static_cast<int>(eGameSoundList::INGAME));
		I_GameSound.PlayOnceInLoopProcess(static_cast<int>(m_eResultGameSound), true, false);
		// Character frame
		for (auto& player : m_players)
		{
			player->Frame();
		}

		CheckWaitTimeToGameOver();

		return true;
	}

	return false;
}

bool GameScene::GameOverRender()
{
#ifdef NETWORK
	// Game over ui rendering
	if (g_bGameOver == true)
	{
		if (CheckWaitTimeToGameOver() == false)
		{
			for (auto& ui : m_UIList)
			{
				if (ui.GetCanvasName() == m_szActivationUIName)
				{
					ui.Render();
					break;
				}
			}
		}
	}
#else
	// Game over ui rendering
	if (g_bGameOver == true)
	{
		if (CheckWaitTimeToGameOver() == false)
		{
			for (auto& ui : m_UIList)
			{
				if (ui.GetCanvasName() == _T("Lose"))
				{
					ui.Render();
					break;
				}
			}
		}
	}
#endif

	if (m_bIsLoad == true)
	{
		if (m_bSceneChange == true)
		{
			if (m_FadeInOut.FadeOut() == true)
			{
				g_eGameSceneState = eGameSceneState::LOBBY_SCENE;
				InitializationData();
			}
		}
	}
	return true;
}

bool GameScene::Init()
{
	SceneManager::Init();
	I_GameSound.Play(static_cast<int>(eGameSoundList::INGAME), true, true);

	// Create map
	CreateBackGround();

	// Create UI
	CreateUI();

	return true;
}

bool GameScene::Frame()
{
	ExecuteInit();
#ifdef NETWORK
	NetworkProcess();
#endif
	GameStartFrame();
	GameOverFrame();

	return true;
}

bool GameScene::Render()
{
	// Map backround rendering
	m_pMap->PreRender();

	// Character rendering
	for (auto& player : m_players)
	{
		player->Render();
	}

	// Map rendering
	m_pMap->PostRender();

	GameStartRender();

	GameOverRender();
	
	return true;
}

bool GameScene::Release()
{
	m_pMap->Release();
	for (auto& player : m_players)
	{
		player->Release();
	}
	m_players.clear();
	return true;
}

//--------------------------------------------------------------------------------------
// Network
//--------------------------------------------------------------------------------------
bool GameScene::NetworkProcess()
{
	list<GAME_PACKET> packetPool = I_AsyncSelect.m_GamePacketPool;
	for (auto& packet : packetPool)
	{
		switch (packet.data.ph.type)
		{
			case PACKET_USER_DROP:
			{
				EVENT_PACKET* dropPacket = (EVENT_PACKET*)&packet;
				g_iDropPlayerNumber = atoi(dropPacket->eventData);
				for (int index = 0; index < m_players.size(); index++)
				{
					if (m_players[index]->GetID() == g_iDropPlayerNumber)
					{
						SAFE_DEL(m_players[index]);
						m_players.erase(m_players.begin() + index);
					}
					else
					{
						m_players[index]->SetActivation(false);
					}
				}
				m_szActivationUIName = _T("Win");
				I_GameSound.m_bOncePlay = false;
				g_bGameOver = true;
			}break;
			case PACKET_CREATE_CHARACTER:
			{
				POINT_F vPos;
				vPos.fX = packet.data.userData.userPos.posX;
				vPos.fY = packet.data.userData.userPos.posY;

				// Create player
				CreatePlayer(packet.data.userData.userPos.spriteIndex, vPos);

			}break;
			case PACKET_MOVE_CHARACTER:
			{
				for (auto& anotherPlayer : m_players)
				{
					// 상대방 캐릭터만 패킷으로 이동 처리
					if (anotherPlayer->GetID() != g_iPlayerNumber)
					{
						NetworkCharacterMove(anotherPlayer, packet);
					}
				}
			}break;
			case PACKET_ATTACK:
			{
				for (auto& anotherPlayer : m_players)
				{
					if (anotherPlayer->GetID() != g_iPlayerNumber)
					{
						WaterBomb* addWaterBomb = new WaterBomb();
						POINT_F vPos(packet.data.userData.attack_info.posX, packet.data.userData.attack_info.posY);

						addWaterBomb->SetOffScreenDC(GetOffScreenDC());
						addWaterBomb->SetDrawType(eRenderType::CHARACTERDARW);
						addWaterBomb->CreateWaterBomb(vPos, packet.data.userData.attack_info.waterBombPower, &m_pMap->GetQuadTree());
						anotherPlayer->InsertWaterBomb(addWaterBomb);

						Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(vPos);
						m_pMap->GetQuadTree().AddInQuadTree(pNode, (Object*)addWaterBomb);
					}
				}
			}break;
			case PACKET_PLAYER_GET_ITEM:
			{
				POINT_F vPos;
				vPos.fX = packet.data.gameData.itemData.itemPosX;
				vPos.fY = packet.data.gameData.itemData.itemPosY;

				Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(vPos);
				if (pNode->GetObjectList().empty() == false)
				{
					Object* pObject = pNode->GetObjectList().at(packet.data.gameData.itemData.itemIndex);
					m_pMap->GetQuadTree().DeleteObject(pNode, pObject);
					pObject->SetSurvival(false);
				}
			}break;
			case PACKET_GAME_OVER:
			{
				int iDeadPlayerNumber = atoi(&packet.data.gameData.deadPlayerNumber);
				for (auto& player : m_players)
				{
					 // 어떤 캐릭터가 사망했는지 확인
					if (player->GetID() == iDeadPlayerNumber)
					{
						player->SetDead(true);
					}

					// 승/패 UI 설정
					if (iDeadPlayerNumber != g_iPlayerNumber) // 상대 캐릭터 사망
					{
						m_szActivationUIName = _T("Win");
						m_eResultGameSound = eGameSoundList::WIN;
					}
					else // 내 캐릭터 사망
					{
						m_szActivationUIName = _T("Lose");
						m_eResultGameSound = eGameSoundList::LOSE;
					}
					I_GameSound.m_bOncePlay = false;
				}
			}break;
		}
	}
	I_AsyncSelect.m_GamePacketPool.clear();

	return true;
}

void GameScene::NetworkCharacterMove(Hero* player, GAME_PACKET packet)
{
	// Set Position
	player->SetPosition(POINT_F(packet.data.userData.userPos.posX, packet.data.userData.userPos.posY));

	// Set bounding box
	player->UpdateBoundingBox();

	// Set sprite
	eDirection direction = static_cast<eDirection>(packet.data.userData.userPos.direction);
	switch (direction)
	{
		case eDirection::UP:
		{
			player->SetSpriteRect(L"BazziMoveUp", kHeroAnimLifeTime);
		}break;
		case eDirection::DOWN:
		{
			player->SetSpriteRect(L"BazziMoveDown", kHeroAnimLifeTime);
		}break;
		case eDirection::LEFT:
		{
			player->SetSpriteRect(L"BazziMoveLeft", kHeroAnimLifeTime);
		}break;
		case eDirection::RIGHT:
		{
			player->SetSpriteRect(L"BazziMoveRight", kHeroAnimLifeTime);
		}break;
	}
	player->GetSprite()->m_currentRect = player->GetSprite()->m_rectList[packet.data.userData.userPos.spriteIndex];

	// Update quadtree object information
	Node* pNode = m_pMap->GetQuadTree().FindNodeInQuadTree(player->GetPosition());
	if (pNode != player->GetPreviousNode())
	{
		m_pMap->GetQuadTree().UpdateQuadTree((Object*)player, player->GetPreviousNode()->GetCorner(), pNode->GetCorner());
		player->SetPreviousNode(pNode);
	}
}

bool GameScene::CheckNetworkDelayTime()
{
	if (m_fNetworkDelayTime >= NETWORK_GAME_INIT_DELAY_TIME)
	{
		return true;
	}

	AccumulateNetworkDelayTime();
	return false;
}

void GameScene::AccumulateNetworkDelayTime()
{
	m_fNetworkDelayTime += g_fSecPerFrame;
}

GameScene::GameScene()
{
	SAFE_ZERO(m_pMap);
	m_fElapsedWaitTime = 0.0f;
	m_fElapsedOverTime = 0.0f;
	m_szActivationUIName = _T("Start");
	m_eResultGameSound = eGameSoundList::LOSE;

	m_bNetworkLoadMap = false;
	m_fNetworkDelayTime = 0.0f;
}

GameScene::~GameScene()
{

}