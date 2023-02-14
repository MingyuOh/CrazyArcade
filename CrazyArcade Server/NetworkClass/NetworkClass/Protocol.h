#pragma once
#include "NetworkSTD.h"
#include "Constant.h"

#define PACKET_CHAT_MSG 1000
#define PACKET_USER_DROP 1001
#define PACKET_SCENE_CHANGE 1002
#define PACKET_CONNECT_LOBBY 2000
#define PACKET_LOBBY_READY 2001
#define PACKET_GAME_START 3000
#define PACKET_CREATE_CHARACTER 3001
#define PACKET_MOVE_CHARACTER 3002
#define PACKET_ATTACK 3003
#define PACKET_PLAYER_GET_ITEM 3004
#define PACKET_GAME_OVER 3005

#define PACKET_HEADER_SIZE 4

#pragma pack(push, 1)

class User;
typedef struct packet_header
{
	WORD len;	// 데이터 크기
	WORD type;	// 데이터 종류
}PACKET_HEADER;

// Lobby
typedef struct _chatData
{
	TCHAR msg[MAX_PATH];
}CHAT_DATA;

typedef struct lpacket
{
	PACKET_HEADER ph;
	bool myPacket;
	bool ready;
	char playerNumber;
	CHAT_DATA chatData;
}LPACKET, *P_LPACKET;

typedef struct lobby_packet
{
	LPACKET data;
	User* pUser;
}LOBBY_PACKET;

// Game
typedef struct user_position
{
	WORD	direction;
	WORD	spriteIndex;
	float	posX;
	float	posY;
}USER_POSITION;

typedef struct attack_info
{
	WORD waterBombPower;
	float posX;
	float posY;
}ATTACK_INFO;

typedef struct user_data
{
	ATTACK_INFO attack_info;
	USER_POSITION userPos;
}USER_DATA;

typedef struct game_init_data
{
	DWORD itemInfo[kItemTotalCount];
	DWORD tileIndex[kItemTotalCount];
}GAME_INIT_DATA;

typedef struct item_info
{
	DWORD itemIndex;
	float itemPosX;
	float itemPosY;
}ITEM_INFO;

typedef struct game_data
{
	char deadPlayerNumber;
	ITEM_INFO itemData;
}GAME_DATA;

typedef struct gpacket
{
	PACKET_HEADER ph;
	USER_DATA userData;
	GAME_DATA gameData;
}GPACKET,*P_GPACKET;

typedef struct game_packet
{
	GPACKET data;
	User* pUser;
}GAME_PACKET;

// Event
typedef struct event_packet
{
	PACKET_HEADER ph;
	char eventData[MAX_PATH];
}EVENT_PACKET;

typedef struct event_game_init
{
	PACKET_HEADER ph;
	char playerNumber;
	GAME_INIT_DATA data;
}EVENT_GAME_INIT;

#pragma pack(pop)