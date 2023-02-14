#pragma once
#include "StreamPacket.h"
#include "NetworkObject.h"

// IOCP를 사용하려면 OVERLAPPED 구조체 재정의
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
	OVERLAPPEDEX	m_ov;				// 유저 배열의 시작에다가 이것을 넣게되면 이것을 가지고 캐스팅하게되면 유저리스트에서 유저를 찾는다.
	SOCKET			m_Socket;			// 디폴트로 유저당 소켓을 넣을 수 있다.
	SOCKADDR_IN		m_Useraddr;
	WSABUF			m_wsaBuffer;
	StreamPacket	m_Stream;	// [관리]한 유저한테 데이터가 들어오는 것을 완성된 패킷을 만드는 작업 만들어서 패킷풀에 넣어준다.
	char			m_strBuffer[2048];  // wsabuffer로 받아라 라고 했지만 사용자 버퍼가 필요하다. // 패킷을 받고하는것이 여기로 들어와야한다.
	int				m_iEvent;			// 이벤트 배열의 인덱스
}USER_SERVER_DATA;

// IOCP까지 고려한 멤버 구성
class User
{
public:
	USER_SERVER_DATA	m_userServerData;
	T_STR				m_szNickName;
	NetworkObject		m_Object;
public:
	void Dispatch(DWORD dwBytes, LPOVERLAPPED ov); // 메세지가 오면 얘한테 넘겨주어야한다. 패킷을 여기서 만들어서 완성된것을 구축을 해야한다.
	void WaitForPacketRecv();
public:
	User(); 
	virtual ~User();
};