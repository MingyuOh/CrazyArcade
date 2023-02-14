#pragma once
// ������ ������� ���ư��Բ� �Ѵ�.
#include "Thread.h"

class PacketPool :public Thread, public Singleton<PacketPool>
{
public:
	std::vector<PACKET> m_list;
public:
	void Add(PACKET packet); // ��ũ�۾��� �ʿ�
	bool Run();
public:
	PacketPool();
	virtual ~PacketPool();
};

#define I_Pool PacketPool::GetInstance()