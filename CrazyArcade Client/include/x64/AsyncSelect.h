#pragma once
#include "Network.h"

class AsyncSelect :public Singleton<AsyncSelect>, public Network
{
private:
	friend class Singleton<AsyncSelect>;
public:
	bool	Connect(T_STR ip, int iPort);
	bool	Frame() override;
public:
	static unsigned int WINAPI RecvThread(LPVOID arg);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	AsyncSelect();
	virtual ~AsyncSelect();
};
#define I_AsyncSelect AsyncSelect::GetInstance()

