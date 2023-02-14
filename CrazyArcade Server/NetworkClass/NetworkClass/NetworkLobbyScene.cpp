#include "NetworkLobbyScene.h"

void NetworkLobbyScene::CheckReadyToPlay(const list<User*> userList)
{
	int iReadyUserCount = 0;
	for (auto& user : userList)
	{
		if (user->m_Object.GetReady() == true)
		{
			iReadyUserCount++;
		}
	}

	if (iReadyUserCount >= MAX_READY_USER_COUNT)
	{
		m_bStartGame = true;
		return;
	}
	m_bStartGame = false;
}

void NetworkLobbyScene::FlipSlotData(const int index)
{
	m_bSlotList[index] = !m_bSlotList[index];
}

void NetworkLobbyScene::SetStartGame(const bool bStartGame)
{
	m_bStartGame = bStartGame;
}

bool NetworkLobbyScene::GetStartGame()
{
	return m_bStartGame;
}

bool* NetworkLobbyScene::GetSlotList()
{
	return m_bSlotList;
}

NetworkLobbyScene::NetworkLobbyScene()
{
	m_bStartGame = false;
	memset(m_bSlotList, false, MAX_SLOT_COUNT);
}

NetworkLobbyScene::~NetworkLobbyScene()
{

}