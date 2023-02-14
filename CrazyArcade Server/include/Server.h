#pragma once
#include "User.h"
#include "Acceptor.h"

class Server :public Singleton<Server>
{
private:
	friend class Singleton<Server>;
public:
	StreamPacket						m_StreamPacket;
	std::list<User*>					m_UserList;
	typedef std::list<User*>::iterator  m_ListItor;
	int									m_iClientNumber;
	HANDLE								m_Mutex;
	int									m_iEventCount; // �̺�Ʈ �迭�� ����
	WSABUF								m_wsaBuffer;
public:
	Acceptor							m_Acceptor;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	void		ProcessPacket();
public:
	User*		GetUser(int iIndex);
	bool		DelUser(int iIndex);
public:
	Server();
	~Server();
};
#define I_Server Server::GetInstance()