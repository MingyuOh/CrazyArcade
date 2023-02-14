#pragma once
// 스레드 기반으로 돌아가게끔 한다.
#include "Thread.h"

class PacketPool :public Thread, public Singleton<PacketPool>
{
public:
	std::vector<PACKET> m_list;
public:
	void Add(PACKET packet); // 싱크작업이 필요
	bool Run();
public:
	PacketPool();
	virtual ~PacketPool();
};

#define I_Pool PacketPool::GetInstance()