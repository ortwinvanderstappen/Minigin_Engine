#include "MiniginPCH.h"
#include "BasicSoundSystem.h"

#include <audio.h>
#include <thread>

#include "ResourceManager.h"

BasicSoundSystem::BasicSoundSystem() :
	m_SoundQueue{}
{
	m_SoundThread = std::thread([this]()
		{
			while (m_IsRunning)
			{
				ProcessQueue();
			}
		}
	);
}

BasicSoundSystem::~BasicSoundSystem()
{
	if (m_IsRunning)
	{
		m_IsRunning = false;
		m_PlayCondition.notify_one();
		m_SoundThread.join();
	}
}

void BasicSoundSystem::ProcessQueue()
{
	std::unique_lock<std::mutex> threadLock{ m_Mutex };
	if (!m_SoundQueue.empty())
	{
		const std::pair<std::string, int>& pair = m_SoundQueue.front();

		Audio* pSound = dae::ResourceManager::GetInstance().LoadSound(pair.first)->GetAudio();

		if (pSound != nullptr)
		{
			const int volume = std::clamp(pair.second, 0, m_MaxVolume);
			playSoundFromMemory(pSound, volume);
		}

		m_SoundQueue.pop();
	}
	else
	{
		m_PlayCondition.wait(threadLock);
	}
}

void BasicSoundSystem::PlaySound(const std::string& soundName, int volume)
{
	std::lock_guard<std::mutex> threadLock{ m_Mutex };
	if (!m_IsMuted)
	{
		m_SoundQueue.push(std::make_pair(soundName, volume));
		m_PlayCondition.notify_one();
	}
}

void BasicSoundSystem::PlayMusic(const std::string&, const int)
{
	// Unimplemented
}

void BasicSoundSystem::Mute()
{
	m_IsMuted = true;
}

void BasicSoundSystem::Unmute()
{
	m_IsMuted = false;
}
