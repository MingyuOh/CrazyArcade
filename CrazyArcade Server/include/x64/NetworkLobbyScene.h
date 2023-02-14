#pragma once
#include "User.h"

#define MAX_READY_USER_COUNT 2
#define MAX_SLOT_COUNT 8

class NetworkLobbyScene : public Singleton<NetworkLobbyScene>
{
private:
	friend class Singleton<NetworkLobbyScene>;
private:
	bool	m_bSlotList[MAX_SLOT_COUNT];
	bool	m_bStartGame;
public:
	void	CheckReadyToPlay(const list<User*> userList);
	void	FlipSlotData(const int index);

	void	SetStartGame(const bool bStartGame);

	bool	GetStartGame();
	bool*	GetSlotList();
public:
	NetworkLobbyScene();
	~NetworkLobbyScene();
};
#define I_NetworkLobbyScene NetworkLobbyScene::GetInstance()
