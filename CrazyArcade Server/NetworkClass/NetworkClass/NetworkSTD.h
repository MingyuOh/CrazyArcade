#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <process.h>
#include <time.h>
#include <tchar.h>
using namespace std;

#pragma comment(lib, "NetworkLib.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment (lib, "winmm.lib")

typedef std::basic_string<TCHAR>	T_STR;
typedef std::basic_string<CHAR>		C_STR;
typedef std::vector<T_STR>			T_STR_VECTOR;

//////////////////////////////////////////////
// 열거형
//////////////////////////////////////////////
enum class eGameSceneState : int
{
	START_SCENE = 0,
	LOGIN_SCENE,
	LOBBY_SCENE,
	GAME_SCENE
};

enum class eTileType : int
{
	NONE = -1,
	STATIC = 0,
	EMPTY = 1,
	BLOCK = 2,
	BOX = 3,
	PILLAR = 4,
	SAIL = 5
};

enum class eItemType : int
{
	NONE = 0,
	WATER_BALLOON,
	WATER_POWER,
	WATER_MAX_POWER,
	SKATE,

	COUNT = 5
};

//////////////////////////////////////////////
// 구조체
//////////////////////////////////////////////
typedef struct vector2 
{
	float x;
	float y;
	vector2()
	{
		x = 0; y = 0;
	}
	vector2(float x, float y)
	{
		this->x = x; this->y = y;
	}
}Vector2;

//////////////////////////////////////////////
// 싱글톤
//////////////////////////////////////////////
template<class T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T thisSigletonInstance;
		return thisSigletonInstance;
	}
};

//////////////////////////////////////////////
// 객체 및 배열 할당과 삭제 및 소멸 매크로
//////////////////////////////////////////////
#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif