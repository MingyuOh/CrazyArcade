#pragma once
//#include "fmod.hpp"
//#include "fmod_errors.h"
#include "CoreSTD.h"

using namespace FMOD;

enum class eGameSoundList : int
{
	LOGO = 0,
	MAIN,
	LOBBY,
	INGAME,
	START,
	WIN,
	LOSE,
	POINT_RECT,
	CLICK,
	BOMB_SET,
	WAVE,
	EAT_ITEM,
	PLAYER_DIE,

	COUNT = 13
};

class GameSound : public Singleton<GameSound>
{
private:
	friend class Singleton<GameSound>;
public:
	FMOD::System*	m_pSystem;
	FMOD::Sound*	m_pSound[static_cast<int>(eGameSoundList::COUNT)];	//사운드
	FMOD::Channel*  m_pChannel[static_cast<int>(eGameSoundList::COUNT)];//채널
	int				m_iSoundList;
	bool			m_bOncePlay;
public:
	void	LoadAllGameSound();
	int		Load(char* pLoadName);
	void	Play(int iIndex, bool bPlay, bool bLoop);
	void	PlayOnceInLoopProcess(int iIndex, bool bPlay, bool bLoop);
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
#define I_GameSound GameSound::GetInstance()

