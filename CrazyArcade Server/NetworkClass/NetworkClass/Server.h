#pragma once
#include "Constant.h"
#include "Acceptor.h"

class Server :public Singleton<Server>
{
private:
	friend class Singleton<Server>;
public:
	StreamPacket			m_StreamPacket;
	std::list<User*>		m_UserList;
	HANDLE					m_Mutex;
	WSABUF					m_wsaBuffer;
	Acceptor				m_Acceptor;
	eGameSceneState			m_eGameSceneState;
	int						m_iClientCount;
	int						m_iEventCount; // 이벤트 배열의 개수
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	void		ProcessPacket();

	bool		UserDrop(EVENT_PACKET* pSendUser);

	bool		Chat(LOBBY_PACKET* pSendUser);
	bool		Ready(LOBBY_PACKET* pSendUser);
	void		GameStart();
	void		GameOver();

	bool		CreateGameData();
	bool		MoveCharacter(GAME_PACKET* pSendUser);
	bool		Attack(GAME_PACKET* pSendUser);
	bool		PlayerGetItem(GAME_PACKET* pSendUser);
	bool		GameOver(GAME_PACKET* pSendUser);
public:
	User*		GetUser(int iIndex);
	bool		DelUser(int iIndex);
public:
	Server();
	~Server();
};
#define I_Server Server::GetInstance()