#include "NetworkObject.h"
#include "NetworkGameScene.h"

bool NetworkObject::Create()
{
	SetSpawnPosition();
	return true;
}

void NetworkObject::SetPlayerNumber(const int number)
{
	m_iPlayerNumber = number;
}

void NetworkObject::SetSpawnPosition()
{
	srand((unsigned int)time(NULL));

	int index = 0;
	map<int, pair<bool, Vector2>>* pSpawnPosition = I_NetworkGameScene.GetGameSpawnPosition();

	do {
		index = rand() % pSpawnPosition->size();
		if (pSpawnPosition->at(index).first == true)
		{
			continue;
		}

		pSpawnPosition->at(index).first = !pSpawnPosition->at(index).first;
		m_vPos = pSpawnPosition->at(index).second;
		break;

	} while (true);
}

void NetworkObject::SetPosition(const Vector2 vPos)
{
	m_vPos = vPos;
}

void NetworkObject::SetReady(const bool bReady)
{
	m_bReady = bReady;
}

int	NetworkObject::GetPlayerNumber()
{
	return m_iPlayerNumber;
}

Vector2 NetworkObject::GetPosition()
{
	return m_vPos;
}

bool NetworkObject::GetReady()
{
	return m_bReady;
}

NetworkObject::NetworkObject()
{
	m_eDirection = eDirection::DEFAULT;
	m_iPlayerNumber = 0;
	m_bReady = false;
}

NetworkObject::~NetworkObject()
{
}