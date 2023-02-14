#include "Acceptor.h"
#include "DebugString.h"
#include "Server.h"
#include "ServerIOCP.h"
#include "NetworkLobbyScene.h"

Acceptor::Acceptor()
{
	WSADATA wd;
	WSAStartup(0x202, &wd);
}

Acceptor::~Acceptor()
{
	WSACleanup();
}

bool Acceptor::Set(int iPort, char* szIP)
{
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	if (szIP == NULL)
	{
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		serveraddr.sin_addr.s_addr = inet_addr(szIP);
	}
	serveraddr.sin_port = htons(iPort);

	int iRet = bind(m_ListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	iRet = listen(m_ListenSock, SOMAXCONN);
	CreateThread(); // ������ Ŭ������ �Լ��̴�.
	return true;
}

bool Acceptor::Run()
{
	SOCKET clientSocket;
	SOCKADDR_IN clientaddr;
	int addlen = 0;
	fd_set	RecvSet;
	fd_set	SendSet;

	timeval	Time;
	int		iResult;

	FD_ZERO(&RecvSet);
	FD_ZERO(&SendSet);
	FD_SET(m_ListenSock , &RecvSet);

	//-----------------------------------------------------
	// Select ���ð� ����. 
	//-----------------------------------------------------
	Time.tv_sec = 0;
	Time.tv_usec = 1;

	//-----------------------------------------------------
	// select �Լ��� ȣ���Ͽ� �˻�.
	//-----------------------------------------------------
	iResult = select(0, &RecvSet, &SendSet, 0, &Time);
	
	if (iResult > 0)
	{
		//-----------------------------------------------------
		// ���ӿ�û ó��.
		//-----------------------------------------------------
		if (FD_ISSET(m_ListenSock, &RecvSet))
		{
			addlen = sizeof(clientaddr);
			clientSocket = accept(m_ListenSock, (SOCKADDR*)&clientaddr, &addlen);
			if (clientSocket == INVALID_SOCKET)
			{
				return false;
			}
			cout << "[IP: " << inet_ntoa(clientaddr.sin_addr) << "," << "PORT: " << ntohs(clientaddr.sin_port) << "] ����" << endl;

			AddUser(clientSocket, clientaddr);
			return true;
		}
	}
	else if (SOCKET_ERROR == iResult)
	{
		return false;
	}

	return true;
}

void Acceptor::AddUser(SOCKET clientSocket, SOCKADDR_IN clientaddr)
{
	Synchronize sync(this);
	User* user = new User();
	user->m_userServerData.m_Socket = clientSocket;
	user->m_userServerData.m_Useraddr = clientaddr;
	I_ServerIOCP.AddhandleToIOCP((HANDLE)clientSocket, (ULONG_PTR)user);

	WSAEVENT hEvent = WSACreateEvent();
	ZeroMemory(&(user)->m_userServerData.m_ov, sizeof(user->m_userServerData.m_ov));
	user->m_userServerData.m_ov.m_iFlag = OVERLAPPEDEX::MODE_SEND;
	user->m_userServerData.m_ov.hEvent = hEvent;
	user->m_userServerData.m_iEvent = user->m_userServerData.m_Socket;

	// ������ ���� �߰�
	I_Server.m_iClientCount++;
	I_Server.m_UserList.push_back(user);
	
	// �κ� ��� ���� ���¿� ���� ���� ��ȣ ����
	bool* bLobbySlotList = I_NetworkLobbyScene.GetSlotList();
	for (int index = 0; index < I_Server.m_UserList.size(); index++)
	{
		if (bLobbySlotList[index] == false)
		{
			I_NetworkLobbyScene.FlipSlotData(index);
			user->m_Object.SetPlayerNumber(index);
		}
	}

	int iSendResult = 0;
	LOBBY_PACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(LOBBY_PACKET));

	// �̹� ������ �ִ� ������ �����͸� ������ �������� ����
	for(auto& pUser : I_Server.m_UserList)
	{
		if (pUser->m_userServerData.m_Socket != user->m_userServerData.m_Socket)
		{
			// �ٸ� ������ �÷��̾� ��ȣ �� Ready ����
			itoa(pUser->m_Object.GetPlayerNumber(), &sendmsg.data.playerNumber, 10);
			sendmsg.data.ready = pUser->m_Object.GetReady();
			sendmsg.data.myPacket = false;
			_tcscpy_s(sendmsg.data.chatData.msg, pUser->m_szNickName.c_str());
			sendmsg.data.ph.type = PACKET_CONNECT_LOBBY;
			sendmsg.data.ph.len = sizeof(sendmsg);
			iSendResult = send(user->m_userServerData.m_Socket, (char*)&sendmsg, sendmsg.data.ph.len, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				break;
			}
		}
		else
		{
			itoa(user->m_Object.GetPlayerNumber(), &sendmsg.data.playerNumber, 10);
			sendmsg.data.ready = false;
			sendmsg.data.myPacket = true;
			sendmsg.data.ph.type = PACKET_CONNECT_LOBBY;
			sendmsg.data.ph.len = sizeof(sendmsg);
			user->m_userServerData.m_wsaBuffer.len = sendmsg.data.ph.len;
			user->m_userServerData.m_wsaBuffer.buf = (char*)&sendmsg.data;

			DWORD dwSendByte;
			iSendResult = WSASend(clientSocket, &user->m_userServerData.m_wsaBuffer, 1, &dwSendByte, 0, (LPOVERLAPPED)&user->m_userServerData.m_ov, NULL);
			if (iSendResult == SOCKET_ERROR)
			{
				I_DebugStr.T_ERROR();
			}
		}

	}

	// �̹� ������ �ִ� �������� ������ �˸�
	list<User*> userlist = I_Server.m_UserList;
	for (auto& pUser : userlist)
	{
		if (pUser->m_userServerData.m_Socket != user->m_userServerData.m_Socket)
		{
			sendmsg.data.myPacket = false;
			iSendResult = send(pUser->m_userServerData.m_Socket, (char*)&sendmsg, sendmsg.data.ph.len, 0);

			if (iSendResult == SOCKET_ERROR)
			{
				I_DebugStr.T_ERROR();
			}
		}
	}
}