#pragma once
#include "NetworkSTD.h"

static std::map<int, pair<bool, Vector2>> g_GameSpawnPosition;

static bool LoadSpawnPosData()
{
	FILE* fpRead = NULL;
	fopen_s(&fpRead, "../../../data/Spawn.txt", "r");

	if (fpRead == nullptr)
	{
		return false;
	}

	TCHAR name[MAX_PATH] = { 0, };
	int index = 0;
	Vector2 vPos;

	while (1)
	{
		fscanf_s(fpRead, "%f", &vPos.x);
		fscanf_s(fpRead, "%f\n", &vPos.y);

		g_GameSpawnPosition.insert(make_pair(index++, make_pair(false, vPos)));
	}

	return true;
}