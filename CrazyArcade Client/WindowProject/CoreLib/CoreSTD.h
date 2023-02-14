#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define NETWORK
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <list>
#include <queue>
#include <cassert>
#include <process.h>
#include "Constant.h"
#include "Helper.h"
#include "..\\..\\include\fmod\fmod.hpp"
using namespace std;

#pragma comment(lib, "CoreLib.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmod64_vc.lib")
#pragma comment(lib, "ws2_32.lib")

//--------------------------------------------------------------------------------------
// Enum variable
//--------------------------------------------------------------------------------------
enum class eGameSceneState : int
{
	INTRO_SCENE = 0,
	LOGIN_SCENE,
	LOBBY_SCENE,
	GAME_SCENE
};

enum class eDirection : WORD
{
	DEFAULT = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

enum class eRenderType : int
{
	STANDARD = 0,
	EXPENDDRAW = 1,
	CHARACTERDARW = 2
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

enum class eSceneType : int
{
	LOGIN = 0,
	LOBBY,
	INGAME,
};

//--------------------------------------------------------------------------------------
// Global variable
//--------------------------------------------------------------------------------------
extern HWND					g_hWnd;
extern HINSTANCE			g_hInstance;
extern float				g_fSecPerFrame;
extern RECT					g_rtClient;
extern RECT					g_rtWindow;
extern bool					g_bDebug;
extern bool					g_bCheckFileLoad;
extern bool					g_bActiveApp;
extern bool					g_bGameStart;
extern bool					g_bGameOver;
extern eGameSceneState		g_eGameSceneState;
extern map<int, eItemType>	g_ItemSpawnInfo;

//--------------------------------------------------------------------------------------
// Structure
//--------------------------------------------------------------------------------------
struct POINT_F : public POINT
{
	FLOAT fX;
	FLOAT fY;

	POINT_F()
	{
		x = 0; y = 0;
		fX = 0.0f, fY = 0.0f;
	}

	POINT_F(FLOAT fX, FLOAT fY)
	{
		x = 0; y = 0;
		this->fX = fX, this->fY = fY;
	}

	POINT_F(LONG x, LONG y, FLOAT fX, FLOAT fY)
	{
		this->x = x; this->y = y;
		this->fX = fX; this->fY = fY;
	}

	POINT_F& operator=(const POINT_F point)
	{
		this->x = point.x;
		this->y = point.y;
		this->fX = point.fX;
		this->fY = point.fY;

		return *this;
	}

};

struct RectUV
{
	POINT_F uv[4];
};

//--------------------------------------------------------------------------------------
// Define
//--------------------------------------------------------------------------------------
#define EPSILON						0.001
#define PI							3.141592654
#define DegreeToRadian(degree)		((degree) * ((PI) / (180.0)))
#define RadianToDegree(radian)		((radian) * ((180.0f) / (PI)))
#define SAMPLE_BUFFER_SIZE			16 
#define KEYSTATECOUNT				256
#define randstep(min, max)			(min + ((float)max - (float)min) * (rand() / (float)RAND_MAX))
#define MAX_BUFFER_SIZE				2048		
#define FIXED_FRAME_COUNT			15

//--------------------------------------------------------------------------------------
// Macros to assign and delete objects and arrays
//--------------------------------------------------------------------------------------
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
#define SAFE_NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };

#endif

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char>  C_STR;
typedef vector<basic_string<TCHAR>>		TCHAR_STRING_VECTOR;
typedef vector<DWORD>					DWORD_VECTOR;

static std::wstring mtw(std::string str)
{
	std::wstring ret = std::wstring(str.begin(), str.end());
	return  ret;
}
static std::string wtm(std::wstring str)
{
	return  std::string(str.begin(), str.end());
}

static char* GetWtM(WCHAR* data)
{
	char retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		data, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength, // 대상
		NULL, NULL);
	return retData;
}
static bool GetWtM(WCHAR* src, char* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1,  //  소스
		pDest, iLength, // 대상
		NULL, NULL);
	if (iRet == 0) return false;
	return true;
}
static WCHAR* GetMtW(char* data)
{
	WCHAR retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength); // 대상
	return retData;
}
static bool GetMtW(char* pSrc, WCHAR* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1,  //  소스
		pDest, iLength); // 대상		
	if (iRet == 0) return false;
	return true;
}
static void PRINT(char* fmt, ...) // 나열연산자
{
	va_list arg;
	va_start(arg, fmt);
	char buf[256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	printf("\n=====> %s", buf);
	va_end(arg);
}


//--------------------------------------------------------------------------------------
// Game run
//--------------------------------------------------------------------------------------
#define GAME_START int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
#define GAME_RUN(gameName, x, y, width, height) Sameple sample; if(sample.SetWindow(hInstance, L#gameName, x, y, width, height)) { sample.Run(); }
#define GAME_END }
#define GAME_SHORT_RUN(gameName) Sample sample; if(sample.SetWindow(hInstance, L#gameName)) { sample.Run(); }

#define GAME(gameName, x, y, width, height) GAME_START; GAME_RUN(gameName, x, y, width, height); GAME_END
#define GAME_VER1(gameName) GAME_START; GAME_SHORT_RUN(gameName); GAME_END
