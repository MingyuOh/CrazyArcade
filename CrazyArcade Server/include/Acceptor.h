#pragma once
#include "Thread.h"
#include "User.h"

class Acceptor : public Thread
{
public:
	SOCKET m_ListenSock;
	std::list<User*> m_UserList;
public:
	bool Set(int iPort, char* szIP = NULL); // �����̰� ���� �� �ʱ�ȭ �� �Լ�
	bool Run();								// accept���� �ʿ��� ����� set�̿��� ���� ���ư��°� �� �Լ�
	virtual void AddUser(SOCKET clientSocket, SOCKADDR_IN clientaddr);
public:
	Acceptor();
	virtual ~Acceptor();
};

