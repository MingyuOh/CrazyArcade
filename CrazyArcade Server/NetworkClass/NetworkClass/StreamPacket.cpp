#include "StreamPacket.h"
#include "DebugString.h"
#include "Server.h"

// data 를 가지고서 "완성된 패킷을 만들어?" 그러면 이 완성된 패킷이 존재한다면 패킷풀에 저장할 수 있는 기능 함수 
// 완성된 패킷이 만들어져 오는것이 아니고 버퍼로부터 받아서 완성된 패킷이 될때까지 계속 받는 것이다. 
// 한번에 데이터가 10개가 들어올 수 있어서 10개의 패킷이 추가될 수 있다.
void StreamPacket::PutLobbyData(char* data, DWORD dwBytes, User* pUser)
{
	// 완성된 패킷(이 만들어졌다고 치면)
	// 저장할 수 있는 구조가 필요하다.

	// 빈번하게 일어나지 않는다.
	// 받는 버퍼의 용량이 부족하면
	if (m_iWritePos + dwBytes >= MAX_RECV_SIZE) // 이거이면 제로메모리 하자
	{
		// 바로 지우면 안되고 잔여량을 카피시켜야한다.
		char strTemp[MAX_RECV_SIZE] = { 0, };
		memcpy(strTemp, &m_RecvBuffer[m_iStartPos], m_iReadPos); // m_iStartPos : 패킷의 시작, m_iReadPos : 시작의 몇바이트 들어와있다.
		ZeroMemory(&m_RecvBuffer, sizeof(char) *  MAX_RECV_SIZE); // 어쩌다 한번 지우니까 제로메모리로 초기화해도 된다.
		memcpy(&m_RecvBuffer, strTemp, m_iReadPos);
		m_pLobbyPacketData = (LOBBY_PACKET*)m_RecvBuffer;
		m_iWritePos = m_iReadPos; // 위치를 갱신해주어야한다(지우고나서 다시 0부터 readpos만큼 썼기 때문이다.) 
		m_iStartPos = 0;
	}

	// 진짜 데이터를 넣는 과정
	memcpy(&m_RecvBuffer[m_iWritePos], data, dwBytes);
	m_iWritePos += dwBytes;
	m_iReadPos += dwBytes;

	// m_iStartPos: 버퍼의 위치
	// m_iReadPos: 버퍼의 위치로부터 몇바이트 받았냐?
	if (m_iReadPos < PACKET_HEADER_SIZE)
		return;


	m_pLobbyPacketData = (LOBBY_PACKET*)&m_RecvBuffer[m_iStartPos]; // 이제 UPACKET으로 해석을 할 수 있다. 패킷의 시작이 있기 때문이다

	// 세가지 경우 발생
	// 1. 패킷 하나도 안된다.
	// 2. 패킷이 딱 정수로 떨어진다.
	// 3. 패킷이 소수점으로 떨어진다.
	// 1개의 패킷 사이즈만큼 받았다면
	if (m_pLobbyPacketData->data.ph.len <= m_iReadPos) // 적어도 한개의 패킷보다는 크거나 같다는 조건
	{
		do {
			LOBBY_PACKET addPacket;
			ZeroMemory(&addPacket, sizeof(LOBBY_PACKET));
			memcpy(&addPacket.data, &m_RecvBuffer[m_iStartPos], m_pLobbyPacketData->data.ph.len);
			addPacket.pUser = pUser;

			if (pUser != NULL)
			{
				I_Server.m_StreamPacket.m_LobbyPacketList.push_back(addPacket);
			}
			// I_Pool.Add(packet); // 모든 유저가 Add작업 // 완성된 패킷을 하나를 넣어놨다면 그 이후로부터 연산을 해야한다.

			// 1개의 패킷을 처리하고 남은 잔여량 크기
			m_iReadPos -= m_pLobbyPacketData->data.ph.len;
			// 패킷의 시작 위치
			m_iStartPos += m_pLobbyPacketData->data.ph.len;
			// 잔여량이 없을 경우
			if (addPacket.data.ph.len == dwBytes)
				break;
			// 잔여량이 패킷 헤더모다 작을 경우
			if (m_iReadPos < PACKET_HEADER_SIZE) 
				break;
			m_pLobbyPacketData = (LOBBY_PACKET*)&m_RecvBuffer[m_iStartPos];
		} while (m_iReadPos >= m_pLobbyPacketData->data.ph.len);
	}
}

void StreamPacket::PutGameData(char* data, DWORD dwBytes, User* pUser)
{
	// 완성된 패킷(이 만들어졌다고 치면)
	// 저장할 수 있는 구조가 필요하다.

	// 빈번하게 일어나지 않는다.
	// 받는 버퍼의 용량이 부족하면
	if (m_iWritePos + dwBytes >= MAX_RECV_SIZE) // 이거이면 제로메모리 하자
	{
		// 바로 지우면 안되고 잔여량을 카피시켜야한다.
		char strTemp[MAX_RECV_SIZE] = { 0, };
		memcpy(strTemp, &m_RecvBuffer[m_iStartPos], m_iReadPos); // m_iStartPos : 패킷의 시작, m_iReadPos : 시작의 몇바이트 들어와있다.
		ZeroMemory(&m_RecvBuffer, sizeof(char) * MAX_RECV_SIZE); // 어쩌다 한번 지우니까 제로메모리로 초기화해도 된다.
		memcpy(&m_RecvBuffer, strTemp, m_iReadPos);
		m_pGamePacketData = (GAME_PACKET*)m_RecvBuffer;
		m_iWritePos = m_iReadPos; // 위치를 갱신해주어야한다(지우고나서 다시 0부터 readpos만큼 썼기 때문이다.) 
		m_iStartPos = 0;
	}

	// 진짜 데이터를 넣는 과정
	memcpy(&m_RecvBuffer[m_iWritePos], data, dwBytes);
	m_iWritePos += dwBytes;
	m_iReadPos += dwBytes;

	// m_iStartPos: 버퍼의 위치
	// m_iReadPos: 버퍼의 위치로부터 몇바이트 받았냐?
	if (m_iReadPos < PACKET_HEADER_SIZE)
		return;


	m_pGamePacketData = (GAME_PACKET*)&m_RecvBuffer[m_iStartPos]; // 이제 UPACKET으로 해석을 할 수 있다. 패킷의 시작이 있기 때문이다

	// 세가지 경우 발생
	// 1. 패킷 하나도 안된다.
	// 2. 패킷이 딱 정수로 떨어진다.
	// 3. 패킷이 소수점으로 떨어진다.
	// 1개의 패킷 사이즈만큼 받았다면
	if (m_pGamePacketData->data.ph.len <= m_iReadPos) // 적어도 한개의 패킷보다는 크거나 같다는 조건
	{
		do {
			GAME_PACKET addPacket;
			ZeroMemory(&addPacket, sizeof(GAME_PACKET));
			memcpy(&addPacket.data, &m_RecvBuffer[m_iStartPos], m_pGamePacketData->data.ph.len);
			addPacket.pUser = pUser;

			if (pUser != NULL)
			{
				I_Server.m_StreamPacket.m_GamePacketList.push_back(addPacket);
			}
			// I_Pool.Add(packet); // 모든 유저가 Add작업 // 완성된 패킷을 하나를 넣어놨다면 그 이후로부터 연산을 해야한다.

			// 1개의 패킷을 처리하고 남은 잔여량 크기
			m_iReadPos -= m_pGamePacketData->data.ph.len;
			// 패킷의 시작 위치
			m_iStartPos += m_pGamePacketData->data.ph.len;
			// 잔여량이 없을 경우
			if (addPacket.data.ph.len == dwBytes)
			{
				break;
			}
			// 잔여량이 패킷 헤더모다 작을 경우
			if (m_iReadPos < PACKET_HEADER_SIZE)
			{
				break;
			}
			m_pGamePacketData = (GAME_PACKET*)&m_RecvBuffer[m_iStartPos];
		} while (m_iReadPos >= m_pGamePacketData->data.ph.len);
	}
}

StreamPacket::StreamPacket()
{
	ZeroMemory(m_RecvBuffer, sizeof(char) * MAX_RECV_SIZE);
	m_iWritePos = 0;
	m_iReadPos = 0;
	m_iStartPos = 0;
	m_pLobbyPacketData = nullptr;
	m_pGamePacketData = nullptr;
}

StreamPacket::~StreamPacket()
{
}