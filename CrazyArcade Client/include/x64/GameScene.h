#pragma once
#include "SceneManager.h"
#include "CharacterManager.h"
#include "Map.h"
#include "Bazzi.h"
#include "Canvas.h"

#define GAME_WAIT_TIME 5.0f

class GameScene :public Singleton<GameScene>, public SceneManager
{
private:
	Map*			m_pMap;
	vector<Hero*>	m_players;
	vector<Canvas>	m_UIList;
	float			m_fElapsedWaitTime;
	float			m_fElapsedOverTime;
	T_STR			m_szActivationUIName;
	eGameSoundList	m_eResultGameSound;
private:
	bool			m_bNetworkLoadMap;
	float			m_fNetworkDelayTime;
private:
	friend class Singleton<GameScene>;
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
	// Create player
	//--------------------------------------------------------------------------------------
	void			CreatePlayer(int id, POINT_F vPos);
	//--------------------------------------------------------------------------------------
	// Data initialization
	//--------------------------------------------------------------------------------------
	void			InitializationData();
	//--------------------------------------------------------------------------------------
	// Check waiting time to start the game
	//--------------------------------------------------------------------------------------
	bool			CheckWaitTimeToGameStart();
	//--------------------------------------------------------------------------------------
	// Accumulate waiting time to start the game
	//--------------------------------------------------------------------------------------
	void			AccumulateWaitTimeToGameStart();
	//--------------------------------------------------------------------------------------
	// Check waiting time to over the game
	//--------------------------------------------------------------------------------------
	bool			CheckWaitTimeToGameOver();
	//--------------------------------------------------------------------------------------
	// Accumulate waiting time to over the game
	//--------------------------------------------------------------------------------------
	void			AccumulateWaitTimeToGameOver();
	//--------------------------------------------------------------------------------------
	// Game start
	//--------------------------------------------------------------------------------------
	bool			GameStartFrame();
	bool			GameStartRender();
	//--------------------------------------------------------------------------------------
	// Game over
	//--------------------------------------------------------------------------------------
	bool			GameOverFrame();
	bool			GameOverRender();
	//--------------------------------------------------------------------------------------
	// Developer redefinition function
	//--------------------------------------------------------------------------------------
	bool			Init() override;
	bool			Frame() override;
	bool			Render() override;
	bool			Release() override;
	//--------------------------------------------------------------------------------------
	// Network
	//--------------------------------------------------------------------------------------
	bool			NetworkProcess() override;
	void			NetworkCharacterMove(Hero* player, GAME_PACKET packet);
	bool			CheckNetworkDelayTime();
	void			AccumulateNetworkDelayTime();
public:
	GameScene();
	~GameScene();
};
#define I_GameScene GameScene::GetInstance()
