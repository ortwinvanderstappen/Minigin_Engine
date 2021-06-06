#include "MiniginPCH.h"
#include "BasicSoundSystem.h"

#include <audio.h>
#include <thread>

#include "ResourceManager.h"

BasicSoundSystem::BasicSoundSystem() :
	m_SoundQueue{},
	m_Volume(m_MaxVolume / 2)
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
	if (!m_SoundQueue.empty())
	{
		const std::pair<std::string, int>& pair = m_SoundQueue.front();
		Audio* pSound = minigen::ResourceManager::GetInstance().LoadSound(pair.first)->GetAudio();

		if (pSound != nullptr)
		{
			const int volume = std::clamp(pair.second, 0, m_MaxVolume);
			playSoundFromMemory(pSound, volume);
		}

		std::unique_lock<std::mutex> threadLock{ m_Mutex };
		m_SoundQueue.pop();
	}
	else
	{
		std::unique_lock<std::mutex> threadLock{ m_Mutex };
		m_PlayCondition.wait(threadLock);
	}
}

void BasicSoundSystem::PlaySound(const std::string& soundName)
{
	if (!m_IsMuted)
	{
		m_SoundQueue.push(std::make_pair(soundName, m_Volume));
		m_PlayCondition.notify_one();
	}
}

void BasicSoundSystem::Mute()
{
	m_IsMuted = true;
}

void BasicSoundSystem::Unmute()
{
	m_IsMuted = false;
}

int BasicSoundSystem::GetVolume() const
{
	return m_Volume;
}

void BasicSoundSystem::SetVolume(int volume)
{
	m_Volume = volume;
}
