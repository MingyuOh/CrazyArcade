#pragma once
#include "NetworkSTD.h"

#define PACKET_CHAT_MSG 1000			  // ��ȭ�� �Է� ����.
#define PACKET_CHAT_NAME_REQ 1001 // �䱸 // ��ȭ�� �Է��ض�.
#define PACKET_CHAT_NAME_ACK 1002 // ���� // ��ȭ�� �Է� ����.
#define PACKET_USER_ADMISSION 1003
#define PACKET_USER_DROP 1004
#define PACKET_GAME_START    2000
#define PACKET_GAME_END    3000
#define PACKET_CREATE_CHARACTER    4000
#define PACKET_MOVE_CHARACTER    5000

#define PACKET_HEADER_SIZE 4

#pragma pack(push, 1)

typedef struct
{
	WORD len;	// ������ ũ��
	WORD type;	// ������ ����
}PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char msg[2048];
}UPACKET, *P_UPACKET;

typedef struct {
	WORD	direction; //4 ����
	float	posX;
	float	posY;
}USER_POSITION;

// ĳ���� ��ġ���� ��Ŷ
typedef struct
{
	PACKET_HEADER ph;
	USER_POSITION heroPos;
}PACKET_HERO_POS, *P_PACKET_HERO_POS;

// ��Ŷ ���� ����(�ϳ��� ��Ŷ�� �ϼ�)
class User;
typedef struct
{
	UPACKET packet; // �������� ���޵Ȱ�
	User* pUser;    // �������� ���°���(�ʿ��� ����: �̰����� ��Ŷ���μ����� ó���Ѵ�. �������� �˷�����ϱ� �����̴�.)
}PACKET; // �����κ��� ��Ŷ�� �����ߴ°� ��°� PACKET


#pragma pack(pop)