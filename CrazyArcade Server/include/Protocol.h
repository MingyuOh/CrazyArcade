#pragma once
#include "NetworkSTD.h"

#define PACKET_CHAT_MSG 1000			  // 대화명 입력 전송.
#define PACKET_CHAT_NAME_REQ 1001 // 요구 // 대화명 입력해라.
#define PACKET_CHAT_NAME_ACK 1002 // 응답 // 대화명 입력 전송.
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
	WORD len;	// 데이터 크기
	WORD type;	// 데이터 종류
}PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char msg[2048];
}UPACKET, *P_UPACKET;

typedef struct {
	WORD	direction; //4 방향
	float	posX;
	float	posY;
}USER_POSITION;

// 캐릭터 위치정보 패킷
typedef struct
{
	PACKET_HEADER ph;
	USER_POSITION heroPos;
}PACKET_HERO_POS, *P_PACKET_HERO_POS;

// 패킷 저장 단위(하나의 패킷이 완성)
class User;
typedef struct
{
	UPACKET packet; // 유저한테 전달된것
	User* pUser;    // 누구한테 오는건지(필요한 이유: 이것으로 패킷프로세스를 처리한다. 누구인지 알려줘야하기 때문이다.)
}PACKET; // 누구로부터 패킷이 도착했는가 라는게 PACKET


#pragma pack(pop)