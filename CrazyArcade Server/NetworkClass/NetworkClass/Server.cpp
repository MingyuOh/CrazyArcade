#include "Server.h"
#include "ServerIOCP.h"
#include "DebugString.h"
#include "NetworkGameScene.h"
#include "NetworkLobbyScene.h"

bool Server::Init()
{
	// IOCP 생성
	I_ServerIOCP.Init();
	
	// Mutex 생성
	m_Mutex = CreateMutex(NULL, FALSE, _T("EditMutex"));

	// 전역 게임 데이터 생성
	I_NetworkGameScene.Init();

	// Accept 처리
	if (m_Acceptor.Set(10000) == false)
	{
		return false;
	}

	cout << "크레이지 아케이드 서버 가동" << endl;
	return true;
}

bool Server::Frame()
{
	switch (m_eGameSceneState)
	{
		case eGameSceneState::LOBBY_SCENE:
		{
			I_NetworkLobbyScene.CheckReadyToPlay(m_UserList);
			if (I_NetworkLobbyScene.GetStartGame() == true)
			{
				GameStart();
			}
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			if (I_NetworkGameScene.GetGameState() == false)
			{
				GameOver();
			}
		}break;
	}
	return true;
}

bool Server::Render()
{
	return true;
}

bool Server::Release()
{
	std::list<User*>::iterator iter;
	int iClientUser = m_UserList.size();
	for (iter = m_UserList.begin();
		iter != m_UserList.end();
		iter++)
	{
		User* pUser = (User*)*iter;
		SAFE_DEL(pUser);
	}
	m_UserList.clear();
	CloseHandle(m_Mutex);
	m_Mutex = nullptr;
	return true;
}

void Server::ProcessPacket()
{
	WaitForSingleObject(m_Mutex, INFINITE);

	switch (m_eGameSceneState)
	{
		case eGameSceneState::LOBBY_SCENE:
		{
			for (auto& lobbyPacket : m_StreamPacket.m_LobbyPacketList)
			{
				switch (lobbyPacket.data.ph.type)
				{
					case PACKET_USER_DROP:
					{
						EVENT_PACKET* packet = (EVENT_PACKET*)&lobbyPacket;
						UserDrop(packet);
					}break;
					case PACKET_CHAT_MSG:
					{
						Chat(&lobbyPacket);
					}break;
					case PACKET_LOBBY_READY:
					{
						Ready(&lobbyPacket);
					}break;
				}
			}
			m_StreamPacket.m_LobbyPacketList.clear();
		}break;
		case eGameSceneState::GAME_SCENE:
		{
			for (auto& gamePacket : m_StreamPacket.m_GamePacketList)
			{
				switch (gamePacket.data.ph.type)
				{
					case PACKET_USER_DROP:
					{
						EVENT_PACKET* packet = (EVENT_PACKET*)& gamePacket;
						UserDrop(packet);
					}break;
					case PACKET_SCENE_CHANGE:
					{
						CreateGameData();
					}
					case PACKET_MOVE_CHARACTER:
					{
						MoveCharacter(&gamePacket);
					}break;
					case PACKET_ATTACK:
					{
						Attack(&gamePacket);
					}break;
					case PACKET_PLAYER_GET_ITEM:
					{
						PlayerGetItem(&gamePacket);
					}break;
					case PACKET_GAME_OVER:
					{
						GameOver(&gamePacket);
					}break;
				}
			}
			m_StreamPacket.m_GamePacketList.clear();
		}break;
	}

	ReleaseMutex(m_Mutex);
}

bool Server::UserDrop(EVENT_PACKET* pSendUser)
{
	EnterCriticalSection(&m_Acceptor.m_cs);

	int iSendResult = false;
	int playerNumber = atoi(pSendUser->eventData);

	EVENT_PACKET packetMessage;
	ZeroMemory(&packetMessage, sizeof(EVENT_PACKET));
	
	strcpy(packetMessage.eventData, pSendUser->eventData);
	packetMessage.ph.type = PACKET_USER_DROP;
	packetMessage.ph.len = PACKET_HEADER_SIZE + strlen(packetMessage.eventData);

	for (auto& pUser : m_UserList)
	{
		if (pUser->m_Object.GetPlayerNumber() != playerNumber)
		{
			iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&packetMessage, packetMessage.ph.len, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				cout << pUser->m_szNickName.c_str() << " 플레이어에게 " << playerNumber << "번 플레이어 종료 전송 실패!" << endl;
				//break;
			}
		}
		else
		{
			cout <<  pUser->m_szNickName.c_str() << " 플레이어 종료" << endl;
		}
	}

	LeaveCriticalSection(&m_Acceptor.m_cs);
	return true;
}

bool Server::Chat(LOBBY_PACKET* pSendUser)
{
	bool iSendResult = false;
	LOBBY_PACKET packetMessage;
	ZeroMemory(&packetMessage, sizeof(LOBBY_PACKET));

	WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	/*wcscpy_s(pSendUser->data.chatData.msg, pSendUser->pUser->m_szNickName.c_str());
	wcscat_s(pSendUser->data.chatData.msg, L" : ");
	wcscat_s(pSendUser->data.chatData.msg, pSendUser->data.chatData.msg);*/

	for (auto& pUser : m_UserList)
	{
		memcpy(&packetMessage, &pSendUser->data, pSendUser->data.ph.len);
		iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&packetMessage, packetMessage.data.ph.len, 0);
		if (iSendResult == SOCKET_ERROR)
		{
			break;
		}
	}
	LeaveCriticalSection(&m_Acceptor.m_cs);
	return true;
}

bool Server::Ready(LOBBY_PACKET* pSendUser)
{
	//WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	int iSendResult = false;
	LOBBY_PACKET packetMessage;
	ZeroMemory(&packetMessage, sizeof(LOBBY_PACKET));

	packetMessage.data.ph.type = PACKET_LOBBY_READY;
	packetMessage.data.ph.len = sizeof(packetMessage);

	for (auto& pUser : m_UserList)
	{
		// 보낸 사람의 Ready 상태 변경
		if (pUser->m_userServerData.m_Socket == pSendUser->pUser->m_userServerData.m_Socket)
		{
			pUser->m_Object.SetReady(pSendUser->data.ready);
		}
		else // 다른 유저에게 Ready 상태 전송
		{
			memcpy(&packetMessage, &pSendUser->data, pSendUser->data.ph.len);
			iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&packetMessage, packetMessage.data.ph.len, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				wcout << pUser->m_szNickName.c_str() << " 플레이어에게 준비 완료 전송 실패!" << endl;
			}
		}
	}
	wcout << pSendUser->pUser->m_szNickName.c_str() << " 플레이어 준비" << endl;

	LeaveCriticalSection(&m_Acceptor.m_cs);
	return true;
}

void Server::GameStart()
{
	int index = 0;
	int iSendResult = 0;
	map<DWORD, eItemType>::iterator iter;
	EVENT_GAME_INIT packet;

	// Reset game data
	I_NetworkGameScene.ResetGameData();

	for (iter = I_NetworkGameScene.GetRandomSpawnItemData()->begin();
		iter != I_NetworkGameScene.GetRandomSpawnItemData()->end();
		iter++, index++)
	{
		packet.data.tileIndex[index] = iter->first;
		packet.data.itemInfo[index] = static_cast<DWORD>(iter->second);
	}

	packet.ph.type = PACKET_GAME_START;
	packet.ph.len = sizeof(EVENT_GAME_INIT);

	for (auto& pUser : m_UserList)
	{
		itoa(pUser->m_Object.GetPlayerNumber(), &packet.playerNumber, 10);
		iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&packet, packet.ph.len, 0);

		if (iSendResult == SOCKET_ERROR)
		{
			break;
		}
	}

	// 씬 상태 전환
	m_eGameSceneState = eGameSceneState::GAME_SCENE;
	I_NetworkLobbyScene.SetStartGame(false);
	I_NetworkGameScene.SetGameState(true);
	cout << endl << "게임 시작! " << endl;
}

void Server::GameOver()
{
	/*int index = 0;
	int iSendResult = 0;
	EVENT_PACKET packet;
	ZeroMemory(&packet, sizeof(EVENT_PACKET));

	for (auto& pUser : m_UserList)
	{
		iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&packet, packet.ph.len, 0);

		if (iSendResult == SOCKET_ERROR)
		{
			break;
		}
	}*/

	// 씬 상태 전환
	m_eGameSceneState = eGameSceneState::LOBBY_SCENE;
	I_NetworkLobbyScene.SetStartGame(false);
	
	cout << endl << "게임 종료! " << endl;
}

bool Server::CreateGameData()
{
	I_NetworkGameScene.m_iClientCount++;
	if (I_NetworkGameScene.m_iClientCount < 2)
	{
		return false;
	}

	//WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	GAME_PACKET packet;
	ZeroMemory(&packet, sizeof(GAME_PACKET));

	packet.data.ph.type = PACKET_CREATE_CHARACTER;
	packet.data.ph.len = sizeof(GAME_PACKET);

	packet.data.userData.userPos.direction = (DWORD)eDirection::DEFAULT;

	int playerIndex = 1;
	for (auto& user : m_UserList)
	{
		int playerNumber = 1;
		user->m_Object.Create();
		packet.data.userData.userPos.spriteIndex = user->m_Object.GetPlayerNumber();
		packet.data.userData.userPos.posX = user->m_Object.GetPosition().x;
		packet.data.userData.userPos.posY = user->m_Object.GetPosition().y;

		// 생성된 데이터를 모두에게 통지
		for (auto& recvUser : m_UserList)
		{
			int iSendResult = send(recvUser->m_userServerData.m_Socket, (char*)&packet, packet.data.ph.len, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				cout << recvUser->m_szNickName.c_str() << "플레이어에게 게임 데이터 전송 실패!" << endl;
			}
			cout << playerIndex << "번째 캐릭터 생성 정보를 " << playerNumber++ << "플레이어에게 게임 데이터 전송 완료" << endl;
		}
		playerIndex++;
	}

	LeaveCriticalSection(&m_Acceptor.m_cs);
	return true;
}

bool Server::MoveCharacter(GAME_PACKET* pSendUser)
{
	//WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	GAME_PACKET packetMsg;
	ZeroMemory(&packetMsg, sizeof(GAME_PACKET));

	for (auto& pUser : m_UserList)
	{
		if (pUser->m_userServerData.m_Socket != pSendUser->pUser->m_userServerData.m_Socket)
		{
			int iSendResult = 0;
			memcpy(&packetMsg, pSendUser, pSendUser->data.ph.len);
			iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&packetMsg, packetMsg.data.ph.len, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				break;
			}
		}
		else
		{
			cout << pUser->m_Object.GetPlayerNumber() + 1 << "번 플레이어 이동: " 
				<< "x: " << pSendUser->data.userData.userPos.posX << ", " 
				<< "y: " << pSendUser->data.userData.userPos.posY << endl;
		}
	}
	LeaveCriticalSection(&m_Acceptor.m_cs);

	return true;
}

bool Server::Attack(GAME_PACKET* pSendUser)
{
	//WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	GAME_PACKET PacketMsg;
	ZeroMemory(&PacketMsg, sizeof(GAME_PACKET));

	for (auto& pUser : m_UserList)
	{
		if (pUser->m_userServerData.m_Socket != pSendUser->pUser->m_userServerData.m_Socket)
		{
			int iSendResult = 0;
			memcpy(&PacketMsg, pSendUser, pSendUser->data.ph.len);
			iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&PacketMsg, PacketMsg.data.ph.len, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				break;
			}
		}
		else
		{
			cout << pUser->m_Object.GetPlayerNumber() + 1 << "번 플레이어 공격: "
				<< "x: " << pSendUser->data.userData.attack_info.posX << ", "
				<< "y: " << pSendUser->data.userData.attack_info.posY << endl;
		}
	}
	LeaveCriticalSection(&m_Acceptor.m_cs);

	return true;
}

bool Server::PlayerGetItem(GAME_PACKET* pSendUser)
{
	//WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	GAME_PACKET PacketMsg;
	ZeroMemory(&PacketMsg, sizeof(GAME_PACKET));

	for (auto& pUser : m_UserList)
	{
		if (pUser->m_userServerData.m_Socket != pSendUser->pUser->m_userServerData.m_Socket)
		{
			int iSendResult = 0;
			memcpy(&PacketMsg, pSendUser, pSendUser->data.ph.len);
			iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&PacketMsg, PacketMsg.data.ph.len, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				cout << "아이템 획득 정보 전달 실패!" << endl;
				break;
			}
		}
		else
		{
			cout << pUser->m_Object.GetPlayerNumber() + 1 << "번 플레이어 아이템 획득" << endl;
		}
	}
	LeaveCriticalSection(&m_Acceptor.m_cs);

	return true;
}

bool Server::GameOver(GAME_PACKET* pSendUser)
{
	//WaitForSingleObject(m_Mutex, INFINITE);
	EnterCriticalSection(&m_Acceptor.m_cs);

	GAME_PACKET PacketMsg;
	ZeroMemory(&PacketMsg, sizeof(GAME_PACKET));

	for (auto& pUser : m_UserList)
	{
		int iSendResult = 0;
		pUser->m_Object.SetReady(false);
		memcpy(&PacketMsg, pSendUser, pSendUser->data.ph.len);
		iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&PacketMsg, PacketMsg.data.ph.len, 0);

		if (iSendResult == SOCKET_ERROR)
		{
			cout << "사망 정보 전달 실패!" << endl;
			break;
		}
	}
	I_NetworkGameScene.SetGameState(false);
	cout << pSendUser->data.gameData.deadPlayerNumber - '0' << "번 플레이어 사망" << endl;
	LeaveCriticalSection(&m_Acceptor.m_cs);

	return true;
}

User* Server::GetUser(int iIndex)
{
	WaitForSingleObject(m_Mutex, INFINITE);
	std::list<User*>::iterator	iter;
	int iClientUser = m_UserList.size();
	for (iter = m_UserList.begin();
		iter != m_UserList.end();
		iter++)
	{
		User* pUser = (User*)*iter;
		if (pUser->m_userServerData.m_iEvent == iIndex)
		{
			ReleaseMutex(m_Mutex);
			return pUser;
		}
	}
	ReleaseMutex(m_Mutex);
	return nullptr;
}

bool Server::DelUser(int iIndex)
{
	// 방에서 나감
	WaitForSingleObject(m_Mutex, INFINITE);
	std::list<User*>::iterator iter;

	for (iter = m_UserList.begin();
		iter != m_UserList.end();
		iter++)
	{
		User* pUser = (User*)*iter;
		if (pUser->m_userServerData.m_iEvent == iIndex)
		{
			cout << "[IP: " << inet_ntoa(pUser->m_userServerData.m_Useraddr.sin_addr) << "," << "PORT: " << ntohs(pUser->m_userServerData.m_Useraddr.sin_port) << "] 종료" << endl;
			closesocket(pUser->m_userServerData.m_Socket);
			
			int index = pUser->m_Object.GetPlayerNumber();
			I_NetworkLobbyScene.FlipSlotData(index);
			m_UserList.erase(iter++);
			m_iClientCount--;
			break;
		}
	}
	ReleaseMutex(m_Mutex);
	return true;
}

Server::Server()
{
	m_iClientCount = 0;
	m_iEventCount = 0;
	m_eGameSceneState = eGameSceneState::LOBBY_SCENE;
}

Server::~Server()
{
}