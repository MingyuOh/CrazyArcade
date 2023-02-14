#pragma once
#include "Thread.h"
#include "User.h"

class Acceptor : public Thread
{
public:
	SOCKET m_ListenSock;
	std::list<User*> m_UserList;
public:
	bool Set(int iPort, char* szIP = NULL); // 윈속이건 뭐건 다 초기화 할 함수
	bool Run();								// accept에서 필요한 기능이 set이였다 실제 돌아가는건 이 함수
	virtual void AddUser(SOCKET clientSocket, SOCKADDR_IN clientaddr);
public:
	Acceptor();
	virtual ~Acceptor();
};

