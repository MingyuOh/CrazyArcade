#pragma once
#include "NetworkSTD.h"

enum class eDirection : DWORD
{
	DEFAULT = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

class NetworkObject
{
private:
	int			m_iPlayerNumber;
	bool		m_bReady;
	Vector2		m_vPos;
	eDirection	m_eDirection;
public:
	bool		Create();

	void		SetSpawnPosition();
	void		SetPlayerNumber(const int number);
	void		SetPosition(const Vector2 vPos);
	void		SetReady(const bool bReady);

	int			GetPlayerNumber();
	Vector2		GetPosition();
	bool		GetReady();
public:
	NetworkObject();
	~NetworkObject();
};

