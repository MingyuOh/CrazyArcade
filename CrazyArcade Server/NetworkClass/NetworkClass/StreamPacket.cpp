#include "StreamPacket.h"
#include "DebugString.h"
#include "Server.h"

// data �� ������ "�ϼ��� ��Ŷ�� �����?" �׷��� �� �ϼ��� ��Ŷ�� �����Ѵٸ� ��ŶǮ�� ������ �� �ִ� ��� �Լ� 
// �ϼ��� ��Ŷ�� ������� ���°��� �ƴϰ� ���۷κ��� �޾Ƽ� �ϼ��� ��Ŷ�� �ɶ����� ��� �޴� ���̴�. 
// �ѹ��� �����Ͱ� 10���� ���� �� �־ 10���� ��Ŷ�� �߰��� �� �ִ�.
void StreamPacket::PutLobbyData(char* data, DWORD dwBytes, User* pUser)
{
	// �ϼ��� ��Ŷ(�� ��������ٰ� ġ��)
	// ������ �� �ִ� ������ �ʿ��ϴ�.

	// ����ϰ� �Ͼ�� �ʴ´�.
	// �޴� ������ �뷮�� �����ϸ�
	if (m_iWritePos + dwBytes >= MAX_RECV_SIZE) // �̰��̸� ���θ޸� ����
	{
		// �ٷ� ����� �ȵǰ� �ܿ����� ī�ǽ��Ѿ��Ѵ�.
		char strTemp[MAX_RECV_SIZE] = { 0, };
		memcpy(strTemp, &m_RecvBuffer[m_iStartPos], m_iReadPos); // m_iStartPos : ��Ŷ�� ����, m_iReadPos : ������ �����Ʈ �����ִ�.
		ZeroMemory(&m_RecvBuffer, sizeof(char) *  MAX_RECV_SIZE); // ��¼�� �ѹ� ����ϱ� ���θ޸𸮷� �ʱ�ȭ�ص� �ȴ�.
		memcpy(&m_RecvBuffer, strTemp, m_iReadPos);
		m_pLobbyPacketData = (LOBBY_PACKET*)m_RecvBuffer;
		m_iWritePos = m_iReadPos; // ��ġ�� �������־���Ѵ�(������� �ٽ� 0���� readpos��ŭ ��� �����̴�.) 
		m_iStartPos = 0;
	}

	// ��¥ �����͸� �ִ� ����
	memcpy(&m_RecvBuffer[m_iWritePos], data, dwBytes);
	m_iWritePos += dwBytes;
	m_iReadPos += dwBytes;

	// m_iStartPos: ������ ��ġ
	// m_iReadPos: ������ ��ġ�κ��� �����Ʈ �޾ҳ�?
	if (m_iReadPos < PACKET_HEADER_SIZE)
		return;


	m_pLobbyPacketData = (LOBBY_PACKET*)&m_RecvBuffer[m_iStartPos]; // ���� UPACKET���� �ؼ��� �� �� �ִ�. ��Ŷ�� ������ �ֱ� �����̴�

	// ������ ��� �߻�
	// 1. ��Ŷ �ϳ��� �ȵȴ�.
	// 2. ��Ŷ�� �� ������ ��������.
	// 3. ��Ŷ�� �Ҽ������� ��������.
	// 1���� ��Ŷ �����ŭ �޾Ҵٸ�
	if (m_pLobbyPacketData->data.ph.len <= m_iReadPos) // ��� �Ѱ��� ��Ŷ���ٴ� ũ�ų� ���ٴ� ����
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
			// I_Pool.Add(packet); // ��� ������ Add�۾� // �ϼ��� ��Ŷ�� �ϳ��� �־���ٸ� �� ���ķκ��� ������ �ؾ��Ѵ�.

			// 1���� ��Ŷ�� ó���ϰ� ���� �ܿ��� ũ��
			m_iReadPos -= m_pLobbyPacketData->data.ph.len;
			// ��Ŷ�� ���� ��ġ
			m_iStartPos += m_pLobbyPacketData->data.ph.len;
			// �ܿ����� ���� ���
			if (addPacket.data.ph.len == dwBytes)
				break;
			// �ܿ����� ��Ŷ ������ ���� ���
			if (m_iReadPos < PACKET_HEADER_SIZE) 
				break;
			m_pLobbyPacketData = (LOBBY_PACKET*)&m_RecvBuffer[m_iStartPos];
		} while (m_iReadPos >= m_pLobbyPacketData->data.ph.len);
	}
}

void StreamPacket::PutGameData(char* data, DWORD dwBytes, User* pUser)
{
	// �ϼ��� ��Ŷ(�� ��������ٰ� ġ��)
	// ������ �� �ִ� ������ �ʿ��ϴ�.

	// ����ϰ� �Ͼ�� �ʴ´�.
	// �޴� ������ �뷮�� �����ϸ�
	if (m_iWritePos + dwBytes >= MAX_RECV_SIZE) // �̰��̸� ���θ޸� ����
	{
		// �ٷ� ����� �ȵǰ� �ܿ����� ī�ǽ��Ѿ��Ѵ�.
		char strTemp[MAX_RECV_SIZE] = { 0, };
		memcpy(strTemp, &m_RecvBuffer[m_iStartPos], m_iReadPos); // m_iStartPos : ��Ŷ�� ����, m_iReadPos : ������ �����Ʈ �����ִ�.
		ZeroMemory(&m_RecvBuffer, sizeof(char) * MAX_RECV_SIZE); // ��¼�� �ѹ� ����ϱ� ���θ޸𸮷� �ʱ�ȭ�ص� �ȴ�.
		memcpy(&m_RecvBuffer, strTemp, m_iReadPos);
		m_pGamePacketData = (GAME_PACKET*)m_RecvBuffer;
		m_iWritePos = m_iReadPos; // ��ġ�� �������־���Ѵ�(������� �ٽ� 0���� readpos��ŭ ��� �����̴�.) 
		m_iStartPos = 0;
	}

	// ��¥ �����͸� �ִ� ����
	memcpy(&m_RecvBuffer[m_iWritePos], data, dwBytes);
	m_iWritePos += dwBytes;
	m_iReadPos += dwBytes;

	// m_iStartPos: ������ ��ġ
	// m_iReadPos: ������ ��ġ�κ��� �����Ʈ �޾ҳ�?
	if (m_iReadPos < PACKET_HEADER_SIZE)
		return;


	m_pGamePacketData = (GAME_PACKET*)&m_RecvBuffer[m_iStartPos]; // ���� UPACKET���� �ؼ��� �� �� �ִ�. ��Ŷ�� ������ �ֱ� �����̴�

	// ������ ��� �߻�
	// 1. ��Ŷ �ϳ��� �ȵȴ�.
	// 2. ��Ŷ�� �� ������ ��������.
	// 3. ��Ŷ�� �Ҽ������� ��������.
	// 1���� ��Ŷ �����ŭ �޾Ҵٸ�
	if (m_pGamePacketData->data.ph.len <= m_iReadPos) // ��� �Ѱ��� ��Ŷ���ٴ� ũ�ų� ���ٴ� ����
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
			// I_Pool.Add(packet); // ��� ������ Add�۾� // �ϼ��� ��Ŷ�� �ϳ��� �־���ٸ� �� ���ķκ��� ������ �ؾ��Ѵ�.

			// 1���� ��Ŷ�� ó���ϰ� ���� �ܿ��� ũ��
			m_iReadPos -= m_pGamePacketData->data.ph.len;
			// ��Ŷ�� ���� ��ġ
			m_iStartPos += m_pGamePacketData->data.ph.len;
			// �ܿ����� ���� ���
			if (addPacket.data.ph.len == dwBytes)
			{
				break;
			}
			// �ܿ����� ��Ŷ ������ ���� ���
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