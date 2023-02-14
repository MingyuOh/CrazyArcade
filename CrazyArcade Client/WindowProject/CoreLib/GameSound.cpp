#include "GameSound.h"

void GameSound::LoadAllGameSound()
{
	Load("../../data/Sound/logo.mp3");
	Load("../../data/Sound/main_scene.mp3");
	Load("../../data/Sound/lobby_scene.mp3");
	Load("../../data/Sound/ingame_scene.mp3");
	Load("../../data/Sound/game_start.mp3");
	Load("../../data/Sound/win.mp3");
	Load("../../data/Sound/lose.mp3");
	Load("../../data/Sound/pt_in_rect.mp3");
	Load("../../data/Sound/click.mp3");
	Load("../../data/Sound/bomb_set.mp3");
	Load("../../data/Sound/wave.mp3");
	Load("../../data/Sound/eat_item.mp3");
	Load("../../data/Sound/player_die.mp3");
}

int	GameSound::Load(char* pLoadName)
{
	m_pSystem->createSound(pLoadName, FMOD_DEFAULT, 0, &m_pSound[m_iSoundList++]);
	return m_iSoundList - 1;
}

void GameSound::Play(int iIndex, bool bPlay, bool bLoop)
{
	bool playing = false;
	if (bPlay == false)
	{
		if (m_pChannel[iIndex] != NULL)
		{
			m_pChannel[iIndex]->isPlaying(&playing);
		}
	}

	if (playing == false)
	{
		if (bLoop == true)
		{
			m_pSound[iIndex]->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			m_pSound[iIndex]->setMode(FMOD_LOOP_OFF);
		}

		m_pSystem->playSound(m_pSound[iIndex], NULL, false, &m_pChannel[iIndex]);
	}
}

void GameSound::PlayOnceInLoopProcess(int iIndex, bool bPlay, bool bLoop)
{
	if (m_bOncePlay == false)
	{
		Play(iIndex, bPlay, bLoop);
		m_bOncePlay = true;
	}
}

void GameSound::PlayEffect(int iIndex)
{
	bool playing = false;
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
	if (m_pChannel[iIndex] != NULL)
	{
		m_pChannel[iIndex]->isPlaying(&playing);
	}
	if (playing)
	{
		Stop(iIndex);
	}
	m_pSystem->playSound(m_pSound[iIndex], NULL, false, &m_pChannel[iIndex]);
	fCurrentVolume = 0.5f;
	m_pChannel[iIndex]->setVolume(fCurrentVolume);
}
void GameSound::Stop(int iIndex)
{
	m_pChannel[iIndex]->stop();
}

void GameSound::Volume(int index, float fVolume, bool bUP)
{
	float fCurrentVolume;
	m_pChannel[index]->getVolume(&fCurrentVolume);
	if (bUP == true)
	{
		fCurrentVolume += fVolume;
		if (fCurrentVolume > 1.0f)
			fCurrentVolume = 1.0f;
	}
	else
	{
		fCurrentVolume -= fVolume;
		if (fCurrentVolume < 0.0f)
			fCurrentVolume = 0.0f;
	}
	m_pChannel[index]->setVolume(fCurrentVolume);
}

void GameSound::Paused(int iIndex)
{
	bool paused;
	m_pChannel[iIndex]->getPaused(&paused);
	m_pChannel[iIndex]->setPaused(!paused);
}

bool GameSound::Init()
{
	//FMOD 시스템 초기화
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	LoadAllGameSound();
	return true;
}

bool GameSound::Frame()
{
	m_pSystem->update();
	return true;
}
bool GameSound::Render()
{
	return true;
}
bool GameSound::Release()
{
	for (int iSound = 0; iSound < static_cast<int>(eGameSoundList::COUNT); iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}

GameSound::GameSound()
{
	m_bOncePlay = false;
}

GameSound::~GameSound()
{
}
