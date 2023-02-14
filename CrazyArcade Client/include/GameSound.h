#pragma once
#include "Core.h"
//#include "fmod.hpp"
//#include "fmod_errors.h"
#include "CoreSTD.h"

using namespace FMOD;
const int g_iMaxSound = 12;
class GameSound :public Core
{
public:
	FMOD::System*	m_pSystem;
	FMOD::Sound*	m_pSound[g_iMaxSound];	//사운드
	FMOD::Channel*  m_pChannel[g_iMaxSound];//채널
											//TCHAR			m_szBuffer[260];
	int				m_iSoundList;
public:
	int Load(char* pLoadName);
	void	Play(int iIndex, bool bPlay);
	void	PlayEffect(int iIndex);
	void	Stop(int iIndex);
	void	Volume(int index, float fVolume, bool bUP);
	void	Paused(int iIndex);
public:
	GameSound();
	~GameSound();

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
};

