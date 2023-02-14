#pragma once
#include "StreamPacket.h"
#include "NetworkObject.h"

// IOCP�� ����Ϸ��� OVERLAPPED ����ü ������
typedef struct _OVERLAPPEDEX : OVERLAPPED
{
	enum { MODE_RECV = 0, MODE_SEND };
	int m_iFlag;
	_OVERLAPPEDEX()
	{
		m_iFlag = MODE_RECV;
	}
}OVERLAPPEDEX;

typedef struct _USER_SERVER_DATA
{
	OVERLAPPEDEX	m_ov;				// ���� �迭�� ���ۿ��ٰ� �̰��� �ְԵǸ� �̰��� ������ ĳ�����ϰԵǸ� ��������Ʈ���� ������ ã�´�.
	SOCKET			m_Socket;			// ����Ʈ�� ������ ������ ���� �� �ִ�.
	SOCKADDR_IN		m_Useraddr;
	WSABUF			m_wsaBuffer;
	StreamPacket	m_Stream;	// [����]�� �������� �����Ͱ� ������ ���� �ϼ��� ��Ŷ�� ����� �۾� ���� ��ŶǮ�� �־��ش�.
	char			m_strBuffer[2048];  // wsabuffer�� �޾ƶ� ��� ������ ����� ���۰� �ʿ��ϴ�. // ��Ŷ�� �ް��ϴ°��� ����� ���;��Ѵ�.
	int				m_iEvent;			// �̺�Ʈ �迭�� �ε���
}USER_SERVER_DATA;

// IOCP���� ����� ��� ����
class User
{
public:
	USER_SERVER_DATA	m_userServerData;
	T_STR				m_szNickName;
	NetworkObject		m_Object;
public:
	void Dispatch(DWORD dwBytes, LPOVERLAPPED ov); // �޼����� ���� ������ �Ѱ��־���Ѵ�. ��Ŷ�� ���⼭ ���� �ϼ��Ȱ��� ������ �ؾ��Ѵ�.
	void WaitForPacketRecv();
public:
	User(); 
	virtual ~User();
};